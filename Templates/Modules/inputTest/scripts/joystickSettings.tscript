
function JoystickSettingsDlg::onWake(%this)
{
   %this.updateDevices();
}

function JoystickSettingsDlg::closeSettings(%this)
{
   Canvas.popDialog(%this);
   Canvas.pushDialog(InputMonitorDlg);
}

function JoystickSettingsDlg::updateDevices(%this)
{
   %this-->deviceArray.deleteAllObjects();
   %sdlDevices = 0;
   if (isMethod("SDLInputManager", "numJoysticks"))
      %sdlDevices = SDLInputManager::numJoysticks();

   for (%i = 0; %i < %sdlDevices; %i++)
   {
      %guiCtrl = DevicePrototype.deepClone();
      %this-->deviceArray.addGuiControl(%guiCtrl);
      %guiCtrl.visible = true;
      %guiCtrl.canSave = false;

      %openState = SDLInputManager::getDeviceOpenState(%i);
      if (%openState > 0)
      {
         %torqueInst = SDLInputManager::getTorqueInstFromDevice(%i);
         %stateStr = "Opened as " @ %torqueInst;
      }
      else
         %stateStr = "Closed";
      %guiCtrl->DeviceOpen.setText(%stateStr);

      if (%openState == 2)
         %deviceName = SDLInputManager::ControllerNameForIndex(%i);
      else
         %deviceName = SDLInputManager::JoystickNameForIndex(%i);
      %guiCtrl->DeviceName.setText(%deviceName);

      %guidStr = SDLInputManager::JoystickGetGUID(%i);
      %guiCtrl->DeviceGUID.setText("GUID: " @ %guidStr);

      // Note: all of the device values could be retrieved individually with:
      // SDLInputManager::JoystickNumAxes(%i), SDLInputManager::JoystickNumButtons(%i),
      // SDLInputManager::JoystickNumHats(%i), SDLInputManager::JoystickNumBalls(%i),
      // SDLInputManager::JoystickIsHaptic(%i), SDLInputManager::JoystickPowerLevel(%i)
      // 
      %deviceSpecs = SDLInputManager::JoystickGetSpecs(%i);
      %vendorId = SDLInputManager::GetVendor(%i);
      %productId = SDLInputManager::GetProduct(%i);
      %productVersion = SDLInputManager::GetProductVersion(%i);
      %specStr = getField(%deviceSpecs,0) @ " Axes, " @ getField(%deviceSpecs, 1) @ " Buttons, ";
      %specStr = %specStr @ getField(%deviceSpecs, 2) @ " POV Hats, " @ getField(%deviceSpecs, 3) @ " Trackballs, ";
      if (getField(%deviceSpecs, 5))
         %specStr = %specStr @ "Haptic, ";
      %powerLevel = getField(%deviceSpecs, 6);
      if (%powerLevel $= "Wired")
         %specStr = %specStr @ "Wired";
      else
         %specStr = %specStr @ "Battery: " @ %powerLevel;
      %guiCtrl->DeviceSpecs.setText(%specStr);

      %isController = getField(%deviceSpecs, 4);
      %deviceType = getField(%deviceSpecs, 7);
      %details = "Type: " @ %deviceType @ ", Vendor ID: " @ %vendorId;
      %details = %details @ ", Product ID: " @ %productId @ ", Version: " @ %productVersion;
      %guiCtrl->DeviceDetails.setText(%details);

      // Setup Buttons
      if (%openState > 0)
      {
         %guiCtrl->button2.setText("Close Device");
         %guiCtrl->button2.visible = true;
         %guiCtrl->button2.command = "SDLInputManager::closeDevice(" @ %i @ ");";
         if (%openState == 2)
         {
            %guiCtrl->button1.setText("Open as Joystick");
            %guiCtrl->button1.visible = true;
            %guiCtrl->button1.command = "SDLInputManager::openAsJoystick(" @ %i @ ");";
         }
         else
         {
            %guiCtrl->button1.setText("Open as Game Controller");
            %guiCtrl->button1.visible = true;
            %guiCtrl->button1.command = "SDLInputManager::openAsController(" @ %i @ ");";
         }
      }
      else
      {
         %guiCtrl->button1.setText("Open as Joystick");
         %guiCtrl->button1.visible = true;
         %guiCtrl->button1.command = "SDLInputManager::openAsJoystick(" @ %i @ ");";

         %guiCtrl->button2.setText("Open as Game Controller");
         %guiCtrl->button2.visible = true;
         %guiCtrl->button2.command = "SDLInputManager::openAsController(" @ %i @ ");";
      }

      // After the command executes, refresh this device list
      %guiCtrl->button1.command = %guiCtrl->button1.command @ "JoystickSettingsDlg.updateDevices();";
      %guiCtrl->button2.command = %guiCtrl->button2.command @ "JoystickSettingsDlg.updateDevices();";
   }
}
