//options settings

//Screen and Display menu
//Renderer Mode
//Screen resolution
//Windowed/fullscreen(borderless?)
//VSync

//Screen brightness
//screen brightness
//screen gamma

//Lighting Menu
//Shadow Distance(Distance shadows are drawn to. Also affects shadowmap slices)
//Shadow Quality(Resolution of shadows rendered, setting to none disables dynamic shadows)
//Soft Shadows(Whether shadow softening is used)
//Shadow caching(If the lights enable it, shadow caching is activated)
//Light Draw Distance(How far away lights are still drawn. Doesn't impact vector lights like the sun)

//Mesh and Textures Menu
//Draw distance(Overall draw distance) -slider
//Object draw distance(Draw distance from small/unimportant objects) -slider
//Mesh quality
//Texture quality
//Foliage draw distance
//Terrain Quality
//Decal Quality

//Effects Menu
//Parallax
//HDR
//Light shafts
//Motion Blur
//Depth of Field
//SSAO
//AA(ModelXAmount)[defualt is FXAA]
//Anisotropic filtering

//Keybinds

//Camera
//horizontal mouse sensitivity
//vert mouse sensitivity
//invert vertical
//zoom mouse sensitivities(both horz/vert)
//headbob
//FOV

function OptionsMenuSettingsList::onAdd(%this)
{
}

function OptionsMenu::onWake(%this)
{
   MainMenuButtonList.hidden = true;
   
   %this.pageTabIndex = 0;
   %tab = %this.getTab();
   %tab.performClick();
   
   OptionsButtonHolder.setActive();
}

function OptionsButtonHolder::onWake(%this)
{
   %this-->prevTabButton.set("btn_l", "", "Prev Tab", "OptionsMenu.prevTab();", true);
   %this-->nextTabButton.set("btn_r", "", "Next Tab", "OptionsMenu.nextTab();", true);
   %this-->resetButton.set("btn_back", "R", "Reset", "OptionsMenu.resetToDefaults();");
   %this-->applyButton.set("btn_start", "Return", "Apply", "OptionsMenu.apply();");
   %this-->backButton.set("btn_b", "Escape", "Back", "OptionsMenu.backOut();");
}

function OptionsMenu::apply(%this)
{
   if(%this.pageTabIndex == 0)
   {
      %this.applyDisplaySettings();
   }
   else if(%this.pageTabIndex == 1)
   {
      %this.applyGraphicsSettings();
   }
   else if(%this.pageTabIndex == 2)
   {
      %this.applyAudioSettings();
   }
   else if(%this.pageTabIndex == 3 || %this.pageTabIndex == 4)
   {
      %prefPath = getPrefpath();
      
      %actionMapCount = ActionMapGroup.getCount();
   
      %actionMapList = "";
      %append = false;
      for(%i=0; %i < %actionMapCount; %i++)
      {
         %actionMap = ActionMapGroup.getObject(%i);
         
         if(%actionMap == GlobalActionMap.getId())
            continue;
         
         %actionMap.save( %prefPath @ "/keybinds.cs", %append );
         
         if(%append != true)
            %append = true; 
      }
   }
   
   %prefPath = getPrefpath();
   export("$pref::*", %prefPath @ "/clientPrefs.cs", false);
}

function OptionsMenu::resetToDefaults(%this)
{
   MessageBoxOKCancel("", "This will set the graphical settings back to the auto-detected defaults. Do you wish to continue?", "AutodetectGraphics();", "");
}

function OptionsMenuSettingsList::onChange(%this)
{
   %optionName = %this.getRowLabel(%this.getSelectedRow());
   %tooltipText = %this.getTooltip(%this.getSelectedRow());
   
   OptionName.setText(%optionName);
   OptionDescription.setText(%tooltipText);
   return;
   
   OptionsMenuSettingsList.clearOptions();

   %currentRowText = %this.getRowLabel(%this.getSelectedRow());
   
   if(%currentRowText $= "Display")
   {
      OptionsMenuList.populateDisplaySettingsList();
   }
   else if(%currentRowText $= "Graphics")
   {
      OptionsMenuList.populateGraphicsSettingsList();
   }
   else if(%currentRowText $= "Audio")
   {
      OptionsMenuList.populateAudioSettingsList();
   }
   else if(%currentRowText $= "Keyboard + Mouse")
   {
      OptionsMenuList.populateKeyboardMouseSettingsList();
   }
   else if(%currentRowText $= "Gamepad")
   {
      OptionsMenuList.populateGamepadSettingsList();
   }
   
   
}

function OptionsMenu::prevTab(%this)
{
   %this.pageTabIndex--;
   if(%this.pageTabIndex < 0)
      %this.pageTabIndex = 4;
      
   %tabBtn = %this.getTab();
   %tabBtn.performClick();
}

function OptionsMenu::nextTab(%this)
{
   %this.pageTabIndex++;
   if(%this.pageTabIndex > 4)
      %this.pageTabIndex = 0;
      
   %tabBtn = %this.getTab();
   %tabBtn.performClick();
}

function OptionsMenu::getTab(%this)
{
   if(%this.pageTabIndex == 0)
      return %this-->DisplayButton;
   else if(%this.pageTabIndex == 1)
      return %this-->GraphicsButton;
   else if(%this.pageTabIndex == 2)
      return %this-->AudioButton;
   else if(%this.pageTabIndex == 3)
      return %this-->KBMButton;
   else if(%this.pageTabIndex == 4)
      return %this-->GamepadButton;
   else 
      return %this-->DisplayButton;
}

function OptionsMenu::populateDisplaySettingsList(%this)
{
   %this.pageTabIndex = 0;
   OptionsMenuSettingsList.clearRows();
   
   OptionName.setText("");
   OptionDescription.setText("");
   
   OptionsMenuSettingsList.addOptionRow("Display API", "D3D11\tOpenGL", false, "", -1, -30, true, "The display API used for rendering.", $pref::Video::displayDevice);
   
   %numDevices = Canvas.getMonitorCount();
   %devicesList = "";
   for(%i = 0; %i < %numDevices; %i++)
   {
      %device = (%i+1) @ " - " @ Canvas.getMonitorName(%i);
      if(%i==0)
         %devicesList = %device;
      else
         %devicesList = %devicesList @ "\t" @ %device;
   }
   
   %selectedDevice = getField(%devicesList, $pref::Video::deviceId);
   OptionsMenuSettingsList.addOptionRow("Display Device", %devicesList, false, "onDisplayModeChange", -1, -30, true, "The display devices the window should be on.", %selectedDevice);
      
   if (%numDevices > 1)
      OptionsMenuSettingsList.setRowEnabled(1, true);
   else
      OptionsMenuSettingsList.setRowEnabled(1, false);
   
   %mode = getField($Video::ModeTags, $pref::Video::deviceMode);
   OptionsMenuSettingsList.addOptionRow("Window Mode", $Video::ModeTags, false, "onDisplayModeChange", -1, -30, true, "", %mode);
   
   %resolutionList = getScreenResolutionList($pref::Video::deviceId, $pref::Video::deviceMode);
   OptionsMenuSettingsList.addOptionRow("Resolution", %resolutionList, false, "onDisplayResChange", -1, -30, true, "Resolution of the game window", _makePrettyResString( $pref::Video::mode ));
   
   //If they're doing borderless, the window resolution must match the display resolution
   if(%mode !$= "Borderless")
      OptionsMenuSettingsList.setRowEnabled(3, true);
   else
      OptionsMenuSettingsList.setRowEnabled(3, false);
   
   OptionsMenuSettingsList.addOptionRow("VSync", "No\tYes", false, "", -1, -30, true, "", convertBoolToYesNo(!$pref::Video::disableVerticalSync));


   %refreshList = getScreenRefreshList($pref::Video::mode);
   OptionsMenuSettingsList.addOptionRow("Refresh Rate", %refreshList, false, "", -1, -30, true, "", $pref::Video::RefreshRate);
   
   //move to gameplay tab
   OptionsMenuSettingsList.addSliderRow("Field of View", 75, 5, "65 100", "", -1, -30);
   
   OptionsMenuSettingsList.addSliderRow("Brightness", 0.5, 0.1, "0 1", "", -1, -30);
   OptionsMenuSettingsList.addSliderRow("Contrast", 0.5, 0.1, "0 1", "", -1, -30);
   
   OptionsMenuSettingsList.refresh();
}

function OptionsMenu::applyDisplaySettings(%this)
{
	%newDevice     = OptionsMenuSettingsList.getCurrentOption(0);
							
   // Change the device.
   if ( %newDevice !$= $pref::Video::displayDevice )
   {
      if ( %testNeedApply )
         return true;
         
      $pref::Video::displayDevice = %newDevice;
      if( %newAdapter !$= getDisplayDeviceInformation() )
         MessageBoxOK( "Change requires restart", "Please restart the game for a display device change to take effect." );
   }
   
   updateDisplaySettings();
   
   echo("Exporting client prefs");
   %prefPath = getPrefpath();
   export("$pref::*", %prefPath @ "/clientPrefs.cs", false);
}

function OptionsMenu::populateGraphicsSettingsList(%this)
{
   %this.pageTabIndex = 1;
   OptionsMenuSettingsList.clearRows();
   
   OptionName.setText("");
   OptionDescription.setText("");
   
   %yesNoList = "No\tYes";
   %onOffList = "Off\tOn";
   %highMedLow = "Low\tMedium\tHigh";
   %anisoFilter = "Off\t4\t8\t16";
   %aaFilter = "Off\t1\t2\t4";
   OptionsMenuSettingsList.addOptionRow("Lighting Quality", getQualityLevels(LightingQualityList), false, "", -1, -30, true, "Amount and drawdistance of local lights", getCurrentQualityLevel(LightingQualityList));
   OptionsMenuSettingsList.addOptionRow("Shadow Quality", getQualityLevels(ShadowQualityList), false, "", -1, -30, true, "Shadow revolution quality", getCurrentQualityLevel(ShadowQualityList));
   OptionsMenuSettingsList.addOptionRow("Soft Shadow Quality", getQualityLevels(SoftShadowList), false, "", -1, -30, true, "Amount of softening applied to shadowmaps", getCurrentQualityLevel(SoftShadowList));
   OptionsMenuSettingsList.addOptionRow("Mesh Quality", getQualityLevels(MeshQualityGroup), false, "", -1, -30, true, "Fidelity of rendering of mesh objects", getCurrentQualityLevel(MeshQualityGroup));
   OptionsMenuSettingsList.addOptionRow("Object Draw Distance", getQualityLevels(MeshDrawDistQualityGroup), false, "", -1, -30, true, "Dictates if and when static objects fade out in the distance", getCurrentQualityLevel(MeshDrawDistQualityGroup));
   OptionsMenuSettingsList.addOptionRow("Texture Quality", getQualityLevels(TextureQualityGroup), false, "", -1, -30, true, "Fidelity of textures", getCurrentQualityLevel(TextureQualityGroup));
   OptionsMenuSettingsList.addOptionRow("Terrain Quality", getQualityLevels(TerrainQualityGroup), false, "", -1, -30, true, "Quality level of terrain objects", getCurrentQualityLevel(TerrainQualityGroup));
   OptionsMenuSettingsList.addOptionRow("Decal Lifetime", getQualityLevels(DecalLifetimeGroup), false, "", -1, -30, true, "How long decals are rendered", getCurrentQualityLevel(DecalLifetimeGroup));
   OptionsMenuSettingsList.addOptionRow("Ground Cover Density", getQualityLevels(GroundCoverDensityGroup), false, "", -1, -30, true, "Density of ground cover items, such as grass", getCurrentQualityLevel(GroundCoverDensityGroup));
   OptionsMenuSettingsList.addOptionRow("Shader Quality", getQualityLevels(ShaderQualityGroup), false, "", -1, -30, true, "Dictates the overall shader quality level, adjusting what features are enabled.", getCurrentQualityLevel(ShaderQualityGroup));
   OptionsMenuSettingsList.addOptionRow("Anisotropic Filtering", %anisoFilter, false, "", -1, -30, true, "Amount of Anisotropic Filtering on textures, which dictates their sharpness at a distance", $pref::Video::defaultAnisotropy);
   OptionsMenuSettingsList.addOptionRow("Anti-Aliasing", %aaFilter, false, "", -1, -30, true, "Amount of Post-Processing Anti-Aliasing applied to rendering", $pref::Video::AA);
   OptionsMenuSettingsList.addOptionRow("Parallax", %onOffList, false, "", -1, -30, true, "Whether the surface parallax shader effect is enabled", convertBoolToOnOff(!$pref::Video::disableParallaxMapping));
   OptionsMenuSettingsList.addOptionRow("Water Reflections", %onOffList, false, "", -1, -30, true, "Whether water reflections are enabled", convertBoolToOnOff(!$pref::Water::disableTrueReflections));
   OptionsMenuSettingsList.addOptionRow("SSAO", %onOffList, false, "", -1, -30, true, "Whether Screen-Space Ambient Occlusion is enabled", convertBoolToOnOff($pref::PostFX::EnableSSAO));
   OptionsMenuSettingsList.addOptionRow("Depth of Field", %onOffList, false, "", -1, -30, true, "Whether the Depth of Field effect is enabled", convertBoolToOnOff($pref::PostFX::EnableDOF));
   OptionsMenuSettingsList.addOptionRow("Vignette", %onOffList, false, "", -1, -30, true, "Whether the vignette effect is enabled", convertBoolToOnOff($pref::PostFX::EnableVignette));
   OptionsMenuSettingsList.addOptionRow("Light Rays", %onOffList, false, "", -1, -30, true, "Whether the light rays effect is enabled", convertBoolToOnOff($pref::PostFX::EnableLightRays));
   
   OptionsMenuSettingsList.refresh();
}

function OptionsMenu::applyGraphicsSettings(%this)
{
   LightingQualityList.applySetting(OptionsMenuSettingsList.getCurrentOption(0));
   ShadowQualityList.applySetting(OptionsMenuSettingsList.getCurrentOption(1));
   SoftShadowList.applySetting(OptionsMenuSettingsList.getCurrentOption(2));
   
   MeshQualityGroup.applySetting(OptionsMenuSettingsList.getCurrentOption(3));
   MeshDrawDistQualityGroup.applySetting(OptionsMenuSettingsList.getCurrentOption(4));
   TextureQualityGroup.applySetting(OptionsMenuSettingsList.getCurrentOption(5));
   TerrainQualityGroup.applySetting(OptionsMenuSettingsList.getCurrentOption(6));
   DecalLifetimeGroup.applySetting(OptionsMenuSettingsList.getCurrentOption(7));
   GroundCoverDensityGroup.applySetting(OptionsMenuSettingsList.getCurrentOption(8));
   ShaderQualityGroup.applySetting(OptionsMenuSettingsList.getCurrentOption(9));
   
   //Update Textures
   reloadTextures();

   //Update lighting
   // Set the light manager.  This should do nothing 
   // if its already set or if its not compatible.   
   //setLightManager( $pref::lightManager );   
   
   $pref::PostFX::EnableSSAO = convertOptionToBool(OptionsMenuSettingsList.getCurrentOption(14));
   $pref::PostFX::EnableDOF = convertOptionToBool(OptionsMenuSettingsList.getCurrentOption(15));
   $pref::PostFX::EnableVignette = convertOptionToBool(OptionsMenuSettingsList.getCurrentOption(16));
   $pref::PostFX::EnableLightRays = convertOptionToBool(OptionsMenuSettingsList.getCurrentOption(17));
   
   PostFXManager.settingsEffectSetEnabled(SSAOPostFx, $pref::PostFX::EnableSSAO);
   PostFXManager.settingsEffectSetEnabled(DOFPostEffect, $pref::PostFX::EnableDOF);
   PostFXManager.settingsEffectSetEnabled(LightRayPostFX, $pref::PostFX::EnableLightRays);
   PostFXManager.settingsEffectSetEnabled(vignettePostFX, $pref::PostFX::EnableVignette);
   
   $pref::Video::disableParallaxMapping = !convertOptionToBool(OptionsMenuSettingsList.getCurrentOption(12));
   
   //water reflections
   $pref::Water::disableTrueReflections = !convertOptionToBool(OptionsMenuSettingsList.getCurrentOption(13));
   
   // Check the anisotropic filtering.   
   %level = OptionsMenuSettingsList.getCurrentOption(10);
   if ( %level != $pref::Video::defaultAnisotropy )
   {
      if ( %testNeedApply )
         return true;
                                 
      $pref::Video::defaultAnisotropy = %level;
   }

   %newFSAA = OptionsMenuSettingsList.getCurrentOption(11);
   if (%newFSAA $= "off")
      %newFSAA = 0;
   if (%newFSAA !$= $pref::Video::AA)
   {
      $pref::Video::AA = %newFSAA;
      configureCanvas();
   }

   echo("Exporting client prefs");
   %prefPath = getPrefpath();
   export("$pref::*", %prefPath @ "/clientPrefs.cs", false);
}   

function updateDisplaySettings()
{
   //Update the display settings now
   %deviceName = OptionsMenuSettingsList.getCurrentOption(1);
   %newDeviceID = getWord(%deviceName, 0) - 1;
   %deviceModeName = OptionsMenuSettingsList.getCurrentOption(2);
   %newDeviceMode = 0;
   foreach$(%modeName in $Video::ModeTags)
   {
      if (%deviceModeName $= %modeName)
         break;
      else
         %newDeviceMode++;
   }

   %newRes = getWord(OptionsMenuSettingsList.getCurrentOption(3), 0) SPC getWord(OptionsMenuSettingsList.getCurrentOption(3), 2);
   %newBpp = 32; // ... its not 1997 anymore.
	%newFullScreen = %deviceModeName $= "Fullscreen" ? true : false;
	%newRefresh    = OptionsMenuSettingsList.getCurrentOption(5);
	%newVsync = !convertOptionToBool(OptionsMenuSettingsList.getCurrentOption(4));	
	%newFSAA = $pref::Video::AA;
	
   // Build the final mode string.
	%newMode = %newRes SPC %newFullScreen SPC %newBpp SPC %newRefresh SPC %newFSAA;
	
   // Change the video mode.   
   if (  %newMode !$= $pref::Video::mode || %newDeviceID != $pref::Video::deviceId ||
         %newVsync != $pref::Video::disableVerticalSync || %newDeviceMode != $pref::Video::deviceMode)
   {
      if ( %testNeedApply )
         return true;

      //****Edge Case Hack
      // If we're in fullscreen mode and switching to a different monitor at the
      // same resolution and maintaining fullscreen, GFX...WindowTarget::resetMode()
      // will early-out because there is no "mode change" and the monitor change
      // will not get applied. Instead of modifying platform code, we're going to
      // move onto the new monitor in borderless and immediately switch to FS.
      if (%newFullScreen && $pref::Video::FullScreen &&
         ($pref::Video::Resolution $= %newRes) && ($pref::Video::deviceId != %newDeviceID))
      {
         $pref::Video::deviceId = %newDeviceID;
         $pref::Video::deviceMode = $Video::ModeBorderless;
         %tmpModeStr = Canvas.getMonitorMode(%newDeviceID, 0);
         Canvas.setVideoMode(%tmpModeStr.x, %tmpModeStr.y, false, 32, getWord(%tmpModeStr, $WORD::REFRESH), %aa);
      }

      $pref::Video::mode = %newMode;
      $pref::Video::disableVerticalSync = %newVsync;
      $pref::Video::deviceId = %newDeviceID;
      $pref::Video::deviceMode = %newDeviceMode;
      $pref::Video::Resolution = %newRes;
      $pref::Video::FullScreen = %newFullScreen;
      $pref::Video::RefreshRate = %newRefresh;
      $pref::Video::AA = %newFSAA;
      configureCanvas();
   }
}

function OptionsMenu::populateAudioSettingsList(%this)
{
   %this.pageTabIndex = 2;
   OptionsMenuSettingsList.clearRows();
   
   OptionName.setText("");
   OptionDescription.setText("");
   
   %buffer = sfxGetAvailableDevices();
   %count = getRecordCount( %buffer );  
   %audioDriverList = "";
    
   $currentAudioProvider = $currentAudioProvider $= "" ? $pref::SFX::provider : $currentAudioProvider;
   
   for(%i = 0; %i < %count; %i++)
   {
      %record = getRecord(%buffer, %i);
      %provider = getField(%record, 0);
      %device = getField(%record, 1);
      
      //When the client is actually running, we don't care about null audo devices
      if(%provider $= "null")
         continue;
      
      if(%audioProviderList $= "")
         %audioProviderList = %provider;
      else 
         %audioProviderList = %audioProviderList @ "\t" @ %provider;
         
      if(%provider $= $currentAudioProvider)
      {
         if(%audioDeviceList $= "")
            %audioDeviceList = %device;
         else 
            %audioDeviceList = %audioDeviceList @ "\t" @ %device;  
      }
         
   }
   
   OptionsMenuSettingsList.addOptionRow("Audio Provider", %audioProviderList, false, "audioProviderChanged", -1, -15, true, "", $currentAudioProvider);
   OptionsMenuSettingsList.addOptionRow("Audio Device", %audioDeviceList, false, "", -1, -15, true, $pref::SFX::device);
   
   OptionsMenuSettingsList.addSliderRow("Master Volume", $pref::SFX::masterVolume, 0.1, "0 1", "", -1, -30);
   OptionsMenuSettingsList.addSliderRow("GUI Volume", $pref::SFX::channelVolume[ $GuiAudioType], 0.1, "0 1", "", -1, -30);
   OptionsMenuSettingsList.addSliderRow("Effects Volume", $pref::SFX::channelVolume[ $SimAudioType ], 0.1, "0 1", "", -1, -30);
   OptionsMenuSettingsList.addSliderRow("Music Volume", $pref::SFX::channelVolume[ $MusicAudioType ], 0.1, "0 1", "", -1, -30);
   
   OptionsMenuSettingsList.refresh();
}

function audioProviderChanged()
{
   //Get the option we have set for the provider
   %provider = OptionsMenuSettingsList.getCurrentOption(0);
   $currentAudioProvider = %provider;
   
   //And now refresh the list to get the correct devices
   OptionsMenu.populateAudioSettingsList();
}

function OptionsMenu::applyAudioSettings(%this)
{
   $pref::SFX::masterVolume = OptionsMenuSettingsList.getValue(2);
   sfxSetMasterVolume( $pref::SFX::masterVolume );
   
   $pref::SFX::channelVolume[ $GuiAudioType ] = OptionsMenuSettingsList.getValue(3);
   $pref::SFX::channelVolume[ $SimAudioType ] = OptionsMenuSettingsList.getValue(4);
   $pref::SFX::channelVolume[ $MusicAudioType ] = OptionsMenuSettingsList.getValue(5);
   
   sfxSetChannelVolume( $GuiAudioType, $pref::SFX::channelVolume[ $GuiAudioType ] );
   sfxSetChannelVolume( $SimAudioType, $pref::SFX::channelVolume[ $SimAudioType ] );
   sfxSetChannelVolume( $MusicAudioType, $pref::SFX::channelVolume[ $MusicAudioType ] );
   
   $pref::SFX::provider = OptionsMenuSettingsList.getCurrentOption(0);
   $pref::SFX::device = OptionsMenuSettingsList.getCurrentOption(1);
   
   if ( !sfxCreateDevice(  $pref::SFX::provider, 
                           $pref::SFX::device, 
                           $pref::SFX::useHardware,
                           -1 ) )                              
      error( "Unable to create SFX device: " @ $pref::SFX::provider 
                                             SPC $pref::SFX::device 
                                             SPC $pref::SFX::useHardware );        

   if( !isObject( $AudioTestHandle ) )
   {
      sfxPlay(menuButtonPressed);  
   }
}

function OptionsMenu::populateKeyboardMouseSettingsList(%this)
{
   %this.pageTabIndex = 3;
   OptionsMenuSettingsList.clearRows();
   
   OptionName.setText("");
   OptionDescription.setText("");
   
   $remapListDevice = "keyboard";
   fillRemapList();
   
   OptionsMenuSettingsList.refresh();
}

function OptionsMenu::populateGamepadSettingsList(%this)
{
   %this.pageTabIndex = 4;
   OptionsMenuSettingsList.clearRows();
   
   OptionName.setText("");
   OptionDescription.setText("");
   
   $remapListDevice = "gamepad";
   fillRemapList();
   
   OptionsMenuSettingsList.refresh();
}

function OptionsMenuList::activateRow(%this)
{
   OptionsMenuSettingsList.setFirstResponder();
}

function OptionsMenu::backOut(%this)
{
   //save the settings and then back out
   if(OptionsMain.hidden == false)
   {
      //we're not in a specific menu, so we're actually exiting
      Canvas.popDialog(OptionsMenu);

      if(isObject(OptionsMenu.returnGui) && OptionsMenu.returnGui.isMethod("onReturnTo"))
         OptionsMenu.returnGui.onReturnTo();
   }
   else
   {
      OptionsMain.hidden = false;
      ControlsMenu.hidden = true;
      GraphicsMenu.hidden = true;
      CameraMenu.hidden = true;
      AudioMenu.hidden = true;
      ScreenBrightnessMenu.hidden = true;
   }
}

function convertOptionToBool(%val)
{
   if(%val $= "yes" || %val $= "on")
      return 1;
   else 
      return 0;
}

function convertBoolToYesNo(%val)
{
   if(%val == 1)
      return "Yes";
   else 
      return "No";
}

function convertBoolToOnOff(%val)
{
   if(%val == 1)
      return "On";
   else 
      return "Off";
}

function onDisplayModeChange(%val)
{  
   // The display device (monitor) or screen mode has changed. Refill the
   // resolution list with only available options.
   %deviceName = OptionsMenuSettingsList.getCurrentOption(1);
   %newDeviceID = getWord(%deviceName, 0) - 1;
   %deviceModeName = OptionsMenuSettingsList.getCurrentOption(2);
   %newDeviceMode = 0;
   foreach$(%modeName in $Video::ModeTags)
   {
      if (%deviceModeName $= %modeName)
         break;
      else
         %newDeviceMode++;
   }
   %resolutionList = getScreenResolutionList(%newDeviceID, %newDeviceMode);

   // If we're switching to borderless, default to monitor res
   if (%newDeviceMode == $Video::ModeBorderless)
      %newRes = getWords(Canvas.getMonitorRect(%newDeviceID), 2);
   else
   {  // Otherwise, if our old resolution is still in the list, attempt to reset it.
      %oldRes = getWord(OptionsMenuSettingsList.getCurrentOption(3), 0) SPC getWord(OptionsMenuSettingsList.getCurrentOption(3), 2);

      %found = false;
      %retCount = getFieldCount(%resolutionList);
      for (%i = 0; %i < %retCount; %i++)
      {
         %existingEntry = getField(%resolutionList, %i);
         if ((%existingEntry.x $= %oldRes.x) && (%existingEntry.z $= %oldRes.y))
         {
            %found = true;
            %newRes = %oldRes;
            break;  
         }
      }

      if (!%found)
      {  // Pick the best resoltion available for the device and mode
         %newRes = Canvas.getBestCanvasRes(%newDeviceID, %newDeviceMode);
      }
   }
   
   if(%newDeviceMode == $Video::ModeBorderless)
      OptionsMenuSettingsList.setRowEnabled(3, false);
   else
      OptionsMenuSettingsList.setRowEnabled(3, true);
      
   OptionsMenuSettingsList.setOptions(3, %resolutionList);
   OptionsMenuSettingsList.selectOption(3, _makePrettyResString(%newRes));
}

function onDisplayResChange(%val)
{  // The resolution has changed. Setup refresh rates available at this res.
   %newRes = getWord(OptionsMenuSettingsList.getCurrentOption(3), 0) SPC getWord(OptionsMenuSettingsList.getCurrentOption(3), 2);
   %refreshList = getScreenRefreshList(%newRes);

   // If our old rate still exists, select it
   %oldRate = OptionsMenuSettingsList.getCurrentOption(5);
   %retCount = getFieldCount(%refreshList);
   for (%i = 0; %i < %retCount; %i++)
   {
      %existingEntry = getField(%refreshList, %i);
      %newRate = %existingEntry;
      if (%existingEntry $= %oldRate)
         break;  
   }

   OptionsMenuSettingsList.setOptions(5, %refreshList);
   OptionsMenuSettingsList.selectOption(5, %newRate);
}