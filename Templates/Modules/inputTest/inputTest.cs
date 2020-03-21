//-----------------------------------------------------------------------------
// Module creation functions.
//-----------------------------------------------------------------------------

function inputTest::create( %this )
{
}

function inputTest::destroy( %this )
{
   
}

function inputTest::initClient( %this )
{
   exec("./scripts/customProfiles.cs");
   exec("./scripts/inputMonitor.cs");
   exec("./scripts/gui/inputMonitor.gui");
   exec("./scripts/joystickSettings.cs");
   exec("./scripts/gui/joystickSettings.gui");

   if (isObject(MainMenuGui))
   {
      %testBtn = new GuiButtonCtrl() {
         text = "Input Event Monitor";
         groupNum = "-1";
         buttonType = "PushButton";
         useMouseEvents = "0";
         position = "0 0";
         extent = "200 40";
         minExtent = "8 8";
         horizSizing = "right";
         vertSizing = "bottom";
         profile = "GuiBlankMenuButtonProfile";
         visible = "1";
         active = "1";
         command = "Canvas.pushDialog(InputMonitorDlg);";
         tooltipProfile = "GuiToolTipProfile";
         isContainer = "0";
         canSave = "0";
         canSaveDynamicFields = "0";
      };

      if (!isObject(MMTestContainer))
      {
         new GuiDynamicCtrlArrayControl(MMTestContainer) {
            colCount = "0";
            colSize = "200";
            rowCount = "0";
            rowSize = "40";
            rowSpacing = "2";
            colSpacing = "0";
            frozen = "0";
            autoCellSize = "0";
            fillRowFirst = "1";
            dynamicSize = "1";
            padding = "0 0 0 0";
            position = "0 0";
            extent = "200 40";
            minExtent = "8 2";
            horizSizing = "right";
            vertSizing = "bottom";
            profile = "GuiDefaultProfile";
            visible = "1";
            active = "1";
            tooltipProfile = "GuiToolTipProfile";
            hovertime = "1000";
            isContainer = "1";
            canSave = "0";
            canSaveDynamicFields = "0";
         };
         MainMenuGui.add(MMTestContainer);
      }

      MMTestContainer.add(%testBtn);
   }
}

function onSDLDeviceConnected(%sdlIndex, %deviceName, %deviceType)
{
   echo("onSDLDeviceConnected(" @ %sdlIndex @ ", \"" @ %deviceName @ "\", \"" @ %deviceType @ "\") - Called");

   // Note: This is called before the device is automatically processed to allow
   // overrides, so refreshing the gui needs to happen after the device has been opened
   if (JoystickSettingsDlg.isAwake())
      JoystickSettingsDlg.schedule(250, "updateDevices");
   if (InputMonitorDlg.isAwake())
      InputMonitorDlg.schedule(250, "updateDevicesLine");
}

function onSDLDeviceDisconnected(%sdlIndex)
{
   echo("onSDLDeviceDisconnected(" @ %sdlIndex @ ") - Called");

   if (JoystickSettingsDlg.isAwake())
      JoystickSettingsDlg.schedule(250, "updateDevices");
   if (InputMonitorDlg.isAwake())
      InputMonitorDlg.schedule(250, "updateDevicesLine");
}

function listAllGCMappings()
{  // Lists all game controller device mappings that are currently installed
   %numMappings = SDLInputManager::GameControllerNumMappings();
   for (%i = 0; %i < %numMappings; %i++)
      echo(SDLInputManager::GameControllerMappingForIndex(%i));
}
