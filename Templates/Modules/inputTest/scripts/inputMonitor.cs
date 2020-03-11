
function InputMonitorDlg::onWake(%this)
{
   if ((%this.maxLines $= "") || (%this.maxLines < 10))
      %this.maxLines = 500;
   if (%this.axisDeadzone $= "")
      %this.axisDeadzone = 0.1;

   if (!isObject(InputEventVector))
      new MessageVector(InputEventVector);

   InputEventVector.clear();
   EventVectorCtrl.attach(InputEventVector);
   
   %this.updateDevicesLine();
}

function InputMonitorDlg::updateDevicesLine(%this)
{
   %sdlDevices = 0;
   if (isMethod("SDLInputManager", "numJoysticks"))
      %sdlDevices = SDLInputManager::numJoysticks();
   %openDevices = 0;
   for (%i = 0; %i < %sdlDevices; %i++)
   {
      %openState = SDLInputManager::getDeviceOpenState(%i);
      if (%openState > 0)
         %openDevices++;
   }
   %this.setDevicesLine(%openDevices, %sdlDevices);
}

function InputMonitorDlg::setDevicesLine(%this, %openDevices, %sdlDevices)
{
   %text = %openDevices @ " of " @ %sdlDevices @ " Joystick devices opened";
   %this-->devicesLine.setText(%text);
}

function InputMonitorCtrl::onInputEvent(%this, %device, %action, %state)
{
   %text = %device @ ", " @ %action @ (%state ? " Make" : " Break");

   if (InputEventVector.getNumLines() > InputMonitorDlg.maxLines)
      InputEventVector.popFrontLine();
   InputEventVector.pushBackLine(%text, 0);

   // Test for the reserved keystrokes:
   if (%device $= "keyboard")
   {
      // Cancel...
      if (%action $= "escape")
      {
         Canvas.popDialog(InputMonitorDlg);
         return;
      }
      // Settings...
      if ((%action $= "f2") && %state)
      {
         Canvas.popDialog(InputMonitorDlg);
         Canvas.pushDialog(JoystickSettingsDlg);
      }
   }
}

function InputMonitorCtrl::onAxisEvent(%this, %device, %action, %axisValue)
{
   if (mAbs(%axisValue) < InputMonitorDlg.axisDeadzone)
   {
      if (%this.lastZero[%device@%action])
         return;
      %this.lastZero[%device@%action] = true;
      %axisValue = 0;
   }
   else
      %this.lastZero[%device@%action] = false;

   %text = %device @ ", " @ %action SPC %axisValue;

   if (InputEventVector.getNumLines() > InputMonitorDlg.maxLines)
      InputEventVector.popFrontLine();
   InputEventVector.pushBackLine(%text, 0);
}
