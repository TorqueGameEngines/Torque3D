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

function OptionsMenu::onWake(%this)
{
    OptionsMain.hidden = false;
    ControlsMenu.hidden = true;
    GraphicsMenu.hidden = true;
    AudioMenu.hidden = true;
    CameraMenu.hidden = true;
    ScreenBrightnessMenu.hidden = true;
    
    OptionsOKButton.hidden = false;
    OptionsCancelButton.hidden = false;
    OptionsDefaultsButton.hidden = false;
    
    OptionsMenu.tamlReader = new Taml();
    
    OptionsSettingStack.clear();
   
   %array = OptionsSettingStack;
   %array.clear();
   
   %keyboardMenuBtn = new GuiButtonCtrl(){
      text = "Keyboard and Mouse";
      profile = GuiMenuButtonProfile;
      extent = %array.extent.x SPC "35";
   };
   
   %controllerMenuBtn = new GuiButtonCtrl(){
      text = "Controller";
      profile = GuiMenuButtonProfile;
      extent = %array.extent.x SPC "35";
      command="DisplayMenu::loadSettings();";
   };
   
   %displayMenuBtn = new GuiButtonCtrl(){
      text = "Display";
      profile = GuiMenuButtonProfile;
      extent = %array.extent.x SPC "35";
      command="DisplayMenu::loadSettings();";
   };
   
   %graphicsMenuBtn = new GuiButtonCtrl(){
      text = "Graphics";
      profile = GuiMenuButtonProfile;
      extent = %array.extent.x SPC "35";
      command="GraphicsMenu::loadSettings();";
   };
   
   %audioMenuBtn = new GuiButtonCtrl(){
      text = "Audio";
      profile = GuiMenuButtonProfile;
      extent = %array.extent.x SPC "35";
      command="AudioMenu::loadSettings();";
   };
   
   %gameplayMenuBtn = new GuiButtonCtrl(){
      text = "Gameplay";
      profile = GuiMenuButtonProfile;
      extent = %array.extent.x SPC "35";
   };
   
   %array.add(%keyboardMenuBtn);
   %array.add(%controllerMenuBtn);
   %array.add(%displayMenuBtn);
   %array.add(%graphicsMenuBtn);
   %array.add(%audioMenuBtn);
   %array.add(%gameplayMenuBtn);
   
   //We programmatically set up our settings here so we can do some prepwork on the fields/controls
   //Presets
   /*OptionsMenu.addSettingOption(%array, "Preset", "High", ShadowQualityList, $pref::Video::Resolution);
   
   //AA
   OptionsMenu.addSettingOption(%array, "AntiAliasing", "FXAA 4x", ShadowQualityList, $pref::Video::Resolution);
   
   //Lighting
   OptionsMenu.addSettingOption(%array, "Shadow Quality", "High", ShadowQualityList, $pref::Video::Resolution);
   OptionsMenu.addSettingOption(%array, "Shadow Caching", "On", ShadowQualityList, $pref::Video::Resolution);
   OptionsMenu.addSettingOption(%array, "Soft Shadows", "High", ShadowQualityList, $pref::Video::Resolution);
   
   //Models and Textures
   OptionsMenu.addSettingOption(%array, "Level of Detail", "High", ShadowQualityList, $pref::Video::Resolution);
   OptionsMenu.addSettingOption(%array, "Texture Quality", "High", ShadowQualityList, $pref::Video::Resolution);
   OptionsMenu.addSettingOption(%array, "Material Quality", "High", ShadowQualityList, $pref::Video::Resolution);
   OptionsMenu.addSettingOption(%array, "Terrain Detail", "High", ShadowQualityList, $pref::Video::Resolution);
   OptionsMenu.addSettingOption(%array, "Decal Lifetime", "High", ShadowQualityList, $pref::Video::Resolution);
   OptionsMenu.addSettingOption(%array, "Ground Clutter Density", "High", ShadowQualityList, $pref::Video::Resolution);
   
   //Effects
   OptionsMenu.addSettingOption(%array, "HDR", "On", ShadowQualityList, $pref::Video::Resolution);
   OptionsMenu.addSettingOption(%array, "Parallax", "On", ShadowQualityList, $pref::Video::Resolution);
   OptionsMenu.addSettingOption(%array, "Ambient Occlusion", "On", ShadowQualityList, $pref::Video::Resolution);
   OptionsMenu.addSettingOption(%array, "Light Rays", "On", ShadowQualityList, $pref::Video::Resolution);
   OptionsMenu.addSettingOption(%array, "Depth of Field", "On", ShadowQualityList, $pref::Video::Resolution);
   OptionsMenu.addSettingOption(%array, "Vignetting", "On", ShadowQualityList, $pref::Video::Resolution);
   OptionsMenu.addSettingOption(%array, "Water Reflections", "On", ShadowQualityList, $pref::Video::Resolution);
   
   OptionsMenu.addSettingOption(%array, "Anisotropic Filtering", "16x", ShadowQualityList, $pref::Video::Resolution);*/
}

function OptionsMenuOKButton::onClick(%this)
{
    //save the settings and then back out
    
    OptionsMenu.backOut();
}

function OptionsMenuCancelButton::onClick(%this)
{
    //we don't save, so go straight to backing out of the menu    
    OptionsMenu.backOut();
}

function OptionsMenuDefaultsButton::onClick(%this)
{
    //we don't save, so go straight to backing out of the menu    
    OptionsMenu.backOut();
}

function ControlsSettingsMenuButton::onClick(%this)
{
    OptionsMain.hidden = true;
    ControlsMenu.hidden = false;
    
    KeyboardControlPanel.hidden = false;
    MouseControlPanel.hidden = true;
    
    ControlsMenu.reload();
}

function GraphicsSettingsMenuButton::onClick(%this)
{
    OptionsMain.hidden = true;
    GraphicsMenu.hidden = false;
}

function CameraSettingsMenuButton::onClick(%this)
{
    OptionsMain.hidden = true;
    CameraMenu.hidden = false;
    
    CameraMenu.loadSettings();
}

function AudioSettingsMenuButton::onClick(%this)
{
    OptionsMain.hidden = true;
    AudioMenu.hidden = false;
    AudioMenu.loadSettings();
}

function ScreenBrSettingsMenuButton::onClick(%this)
{
    OptionsMain.hidden = true;
    ScreenBrightnessMenu.hidden = false;
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

function OptionsMenu::addSettingOption(%this, %arrayTarget, %optionName, %defaultValue, %settingsGroup, %targetVar)
{
    %option = TAMLRead("data/ui/scripts/guis/graphicsMenuSettingsCtrl.taml");
    
    %option-->nameText.text = %optionName;
    %option-->SettingText.text = %defaultValue;
    %option.qualitySettingGroup = %settingsGroup;
    %option.targetVar = %targetVar;
    
    %option.init();

    %arrayTarget.add(%option);

    return %option;
}

function OptionsMenu::addSliderOption(%this, %arrayTarget, %optionName, %variable, %range, %ticks, %value, %class)
{
    %option = TAMLRead("data/ui/scripts/guis/graphicsMenuSettingsSlider.taml");
    
    %option-->nameText.text = %optionName;

    %arrayTarget.add(%option);
    
    if(%range !$= "")
    {
       %option-->slider.range = %range;
    }
    
    if(%ticks !$= "")
    {
       %option-->slider.ticks = %ticks;
    }
    
    if(%variable !$= "")
    {
       %option-->slider.variable = %variable;
    }
    
    if(%value !$= "")
    {
       %option-->slider.setValue(%value);
    }
    
    if(%class !$= "")
    {
       %option-->slider.className = %class;
    }
    else
        %option-->slider.className = OptionsMenuSlider;
        
    %option-->slider.snap = true;
    
    %option-->slider.onValueSet();

    return %option;
}

function OptionsMenuSlider::onMouseDragged(%this)
{
   %this.onValueSet();
}

function OptionsMenuSlider::onValueSet(%this)
{
   %this.getParent().getParent()-->valueText.setText(mRound(%this.value * 10));  
}

function FOVOptionSlider::onMouseDragged(%this)
{
   %this.onValueSet();
}

function FOVOptionSlider::onValueSet(%this)
{
   %this.getParent().getParent()-->valueText.setText(mRound(%this.value));
}

function OptionsMenuForwardSetting::onClick(%this)
{
   //we need to advance through the value list, unless it's the end, in which case we do nothing  
   echo("Move forward in the list!");
   
   %settingCtrl = %this.getParent();
   for ( %i=0; %i < %settingCtrl.qualitySettingGroup.getCount(); %i++ )
   {
      %level = %settingCtrl.qualitySettingGroup.getObject( %i );
      
      if(%settingCtrl.selectedLevel == %i)
      {
         //k, shift it  
         if(%i == %settingCtrl.qualitySettingGroup.getCount() - 1)
         {
            //oh, we're at the end. Do nothing.
            return;  
         }
         else
         {
            %newLevel = %settingCtrl.qualitySettingGroup.getObject( %i + 1 );
            %settingCtrl-->SettingText.setText( %newLevel.displayName );
            OptionsPreviewCtrl.bitmap = %newLevel.previewImage;
            %settingCtrl.selectedLevel = %i + 1;
            return;
         }
      }
   }
}

function OptionsMenuBackSetting::onClick(%this)
{
   //we need to advance through the value list, unless it's the end, in which case we do nothing  
   echo("Move back in the list!");
   
   %settingCtrl = %this.getParent();
   for ( %i=0; %i < %settingCtrl.qualitySettingGroup.getCount(); %i++ )
   {
      %level = %settingCtrl.qualitySettingGroup.getObject( %i );
      
      if(%settingCtrl.selectedLevel == %i)
      {
         //k, shift it  
         if(%i == 0)
         {
            //oh, we're at the end. Do nothing.
            return;  
         }
         else
         {
            %newLevel = %settingCtrl.qualitySettingGroup.getObject( %i - 1 );
            %settingCtrl-->SettingText.setText( %newLevel.displayName );
            %settingCtrl.selectedLevel = %i - 1;
            return;
         }
      }
   }
}

/// Returns true if the current quality settings equal
/// this graphics quality level.
function OptionsMenuSettingLevel::isCurrent( %this )
{
   // Test each pref to see if the current value
   // equals our stored value.
   
   for ( %i=0; %i < %this.count(); %i++ )
   {
      %pref = %this.getKey( %i );
      %value = %this.getValue( %i );
      
      %prefVarValue = getVariable( %pref );
      if ( getVariable( %pref ) !$= %value )
         return false;
   }
   
   return true;
}
// =============================================================================
// CAMERA MENU
// =============================================================================
function CameraMenu::onWake(%this)
{
    
}

function CameraMenu::apply(%this)
{
   setFOV($pref::Player::defaultFov);  
}

function CameraMenu::loadSettings(%this)
{
   CameraMenuOptionsArray.clear();
   
   %option = OptionsMenu.addSettingOption(CameraMenuOptionsArray);
   %option-->nameText.setText("Invert Vertical");
   %option.qualitySettingGroup = InvertVerticalMouse;
   %option.init();
   
   %option = OptionsMenu.addSliderOption(CameraMenuOptionsArray, "0.1 1", 8, "$pref::Input::VertMouseSensitivity", $pref::Input::VertMouseSensitivity);
   %option-->nameText.setText("Vertical Sensitivity");
   
   %option = OptionsMenu.addSliderOption(CameraMenuOptionsArray, "0.1 1", 8, "$pref::Input::HorzMouseSensitivity", $pref::Input::HorzMouseSensitivity);
   %option-->nameText.setText("Horizontal Sensitivity");
   
   %option = OptionsMenu.addSliderOption(CameraMenuOptionsArray, "0.1 1", 8, "$pref::Input::ZoomVertMouseSensitivity", $pref::Input::ZoomVertMouseSensitivity);
   %option-->nameText.setText("Zoom Vertical Sensitivity");

   %option = OptionsMenu.addSliderOption(CameraMenuOptionsArray, "0.1 1", 8, "$pref::Input::ZoomHorzMouseSensitivity", $pref::Input::ZoomHorzMouseSensitivity);
   %option-->nameText.setText("Zoom Horizontal Sensitivity");
   
   %option = OptionsMenu.addSliderOption(CameraMenuOptionsArray, "65 90", 25, "$pref::Player::defaultFov", $pref::Player::defaultFov, FOVOptionSlider);
   %option-->nameText.setText("Field of View");
   
   CameraMenuOptionsArray.refresh();
}

function CameraMenuOKButton::onClick(%this)
{
   //save the settings and then back out
    CameraMenu.apply();
    OptionsMenu.backOut();
}

function CameraMenuDefaultsButton::onClick(%this)
{
   
}
// =============================================================================
// AUDIO MENU
// =============================================================================
$AudioTestHandle = 0;
// Description to use for playing the volume test sound.  This isn't
// played with the description of the channel that has its volume changed
// because we know nothing about the playback state of the channel.  If it
// is paused or stopped, the test sound would not play then.
$AudioTestDescription = new SFXDescription()
{
   sourceGroup = AudioChannelMaster;
};

function AudioMenu::loadSettings(%this)
{
   // Audio
   //OptAudioHardwareToggle.setStateOn($pref::SFX::useHardware);
   //OptAudioHardwareToggle.setActive( true );
   
   %this-->OptAudioVolumeMaster.setValue( $pref::SFX::masterVolume );
   %this-->OptAudioVolumeShell.setValue( $pref::SFX::channelVolume[ $GuiAudioType] );
   %this-->OptAudioVolumeSim.setValue( $pref::SFX::channelVolume[ $SimAudioType ] );
   %this-->OptAudioVolumeMusic.setValue( $pref::SFX::channelVolume[ $MusicAudioType ] );
   
   AudioMenuSoundDriver.clear();
   %buffer = sfxGetAvailableDevices();
   %count = getRecordCount( %buffer );   
   for(%i = 0; %i < %count; %i++)
   {
      %record = getRecord(%buffer, %i);
      %provider = getField(%record, 0);
      
      if ( AudioMenuSoundDriver.findText( %provider ) == -1 )
            AudioMenuSoundDriver.add( %provider, %i );
   }
   
   AudioMenuSoundDriver.sort();

   %selId = AudioMenuSoundDriver.findText($pref::SFX::provider);
	if ( %selId == -1 )
		AudioMenuSoundDriver.setFirstSelected();
   else
	   AudioMenuSoundDriver.setSelected( %selId );
}

function AudioMenu::loadDevices(%this)
{
   if(!isObject(SoundDeviceGroup))
   {
      new SimGroup( SoundDeviceGroup );
   }
   else
   {
      SoundDeviceGroup.clear();
   }
   
   %buffer = sfxGetAvailableDevices();
   %count = getRecordCount( %buffer );
   for (%i = 0; %i < %count; %i++)
   {
      %record = getRecord(%buffer, %i);
      %provider = getField(%record, 0);
      %device = getField(%record, 1);
         
      if($pref::SFX::provider !$= %provider)
         continue;
      
      %setting = new ArrayObject()
      {
         class = "OptionsMenuSettingLevel";
         caseSensitive = true;
         
         displayName = %device;
         
         key["$pref::SFX::Device"] = %device;
      };
      
      SoundDeviceGroup.add(%setting);
   }
}

function AudioMenu::apply(%this)
{
   sfxSetMasterVolume( $pref::SFX::masterVolume );
   
   sfxSetChannelVolume( $GuiAudioType, $pref::SFX::channelVolume[ $GuiAudioType ] );
   sfxSetChannelVolume( $SimAudioType, $pref::SFX::channelVolume[ $SimAudioType ] );
   sfxSetChannelVolume( $MusicAudioType, $pref::SFX::channelVolume[ $MusicAudioType ] );
   
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

function AudioMenuOKButton::onClick(%this)
{
   //save the settings and then back out
    AudioMenu.apply();
    OptionsMenu.backOut();
}

function AudioMenuDefaultsButton::onClick(%this)
{
   sfxInit();
   AudioMenu.loadSettings();
}

function OptAudioUpdateMasterVolume( %volume )
{
   if( %volume == $pref::SFX::masterVolume )
      return;
      
   sfxSetMasterVolume( %volume );
   $pref::SFX::masterVolume = %volume;
   
   if( !isObject( $AudioTestHandle ) )
      $AudioTestHandle = sfxPlayOnce( AudioChannel, "art/sound/ui/volumeTest.wav" );
}

function OptAudioUpdateChannelVolume( %description, %volume )
{
   %channel = sfxGroupToOldChannel( %description.sourceGroup );
   
   if( %volume == $pref::SFX::channelVolume[ %channel ] )
      return;

   sfxSetChannelVolume( %channel, %volume );
   $pref::SFX::channelVolume[ %channel ] = %volume;
   
   if( !isObject( $AudioTestHandle ) )
   {
      $AudioTestDescription.volume = %volume;
      $AudioTestHandle = sfxPlayOnce( $AudioTestDescription, "art/sound/ui/volumeTest.wav" );
   }
}

function AudioMenuSoundDriver::onSelect( %this, %id, %text )
{
   // Skip empty provider selections.   
   if ( %text $= "" )
      return;
      
   $pref::SFX::provider = %text;
   AudioMenuSoundDevice.clear();
   
   %buffer = sfxGetAvailableDevices();
   %count = getRecordCount( %buffer );   
   for(%i = 0; %i < %count; %i++)
   {
      %record = getRecord(%buffer, %i);
      %provider = getField(%record, 0);
      %device = getField(%record, 1);
      
      if (%provider !$= %text)
         continue;
            
       if ( AudioMenuSoundDevice.findText( %device ) == -1 )
            AudioMenuSoundDevice.add( %device, %i );
   }

   // Find the previous selected device.
   %selId = AudioMenuSoundDevice.findText($pref::SFX::device);
   if ( %selId == -1 )
      AudioMenuSoundDevice.setFirstSelected();
   else
   AudioMenuSoundDevice.setSelected( %selId );
}

function AudioMenuSoundDevice::onSelect( %this, %id, %text )
{
   // Skip empty selections.
   if ( %text $= "" )
      return;
      
   $pref::SFX::device = %text;
   
   if ( !sfxCreateDevice(  $pref::SFX::provider, 
                           $pref::SFX::device, 
                           $pref::SFX::useHardware,
                           -1 ) )                              
      error( "Unable to create SFX device: " @ $pref::SFX::provider 
                                             SPC $pref::SFX::device 
                                             SPC $pref::SFX::useHardware );                                             
}

//==============================================================================
// DISPLAY MENU
//==============================================================================
function DisplayMenu::loadSettings()
{
   OptionsSettingStack.clear();
   
   OptionsMenu.addSettingOption(OptionsSettingStack, "Resolution", "1024 x 768", "", $pref::Video::Resolution);
   OptionsMenu.addSettingOption(OptionsSettingStack, "Full Screen", "Off", "", $pref::Video::FullScreen);
   OptionsMenu.addSettingOption(OptionsSettingStack, "Refresh Rate", "60", "", $pref::Video::RefreshRate);
   OptionsMenu.addSettingOption(OptionsSettingStack, "VSync", "Off", "", $pref::Video::Vsync);
   
   OptionsMenu.addSliderOption(OptionsSettingStack, "Field of View", $pref::Video::FOV, "65 120", 55, 75);
   
   OptionsMenu.addSliderOption(OptionsSettingStack, "Brightness", $pref::Video::Brightness, "0 1", 10, 5);
   OptionsMenu.addSliderOption(OptionsSettingStack, "Contrast", $pref::Video::Contrast, "0 1", 10, 5);
}

//==============================================================================
// GRAPHICS MENU
//==============================================================================
function GraphicsMenu::loadSettings()
{
   OptionsSettingStack.clear();
   
   OptionsMenu.addSettingOption(OptionsSettingStack, "Shadow Quality", "High", "", $pref::Video::Resolution);
   OptionsMenu.addSettingOption(OptionsSettingStack, "Shadow Caching", "Off", "", $pref::Video::FullScreen);
   OptionsMenu.addSettingOption(OptionsSettingStack, "Soft Shadows", "60", "", $pref::Video::RefreshRate);
   
   OptionsMenu.addSettingOption(OptionsSettingStack, "Model Detail", "Off", "", $pref::Video::Vsync);
   OptionsMenu.addSliderOption(OptionsSettingStack, "Texture Detail", $pref::Video::FOV, "65 120", 55, 75);
   OptionsMenu.addSettingOption(OptionsSettingStack, "Terrain Detail", "Off", "", $pref::Video::Vsync);
   OptionsMenu.addSettingOption(OptionsSettingStack, "Decal Lifetime", "Off", "", $pref::Video::Vsync);
   OptionsMenu.addSettingOption(OptionsSettingStack, "Ground Clutter Density", "Off", "", $pref::Video::Vsync);
   
   OptionsMenu.addSettingOption(OptionsSettingStack, "Material Quality", "Off", "", $pref::Video::Vsync);
   OptionsMenu.addSettingOption(OptionsSettingStack, "HDR", "Off", "", $pref::Video::Vsync);   
   OptionsMenu.addSettingOption(OptionsSettingStack, "Parallax", "Off", "", $pref::Video::Vsync);
   OptionsMenu.addSettingOption(OptionsSettingStack, "Ambient Occlusion", "Off", "", $pref::Video::Vsync);
   OptionsMenu.addSettingOption(OptionsSettingStack, "Light Rays", "Off", "", $pref::Video::Vsync);
   OptionsMenu.addSettingOption(OptionsSettingStack, "Depth of Field", "Off", "", $pref::Video::Vsync);
   OptionsMenu.addSettingOption(OptionsSettingStack, "Vignetting", "Off", "", $pref::Video::Vsync);
   OptionsMenu.addSettingOption(OptionsSettingStack, "Water Reflections", "Off", "", $pref::Video::Vsync);
   OptionsMenu.addSettingOption(OptionsSettingStack, "Anti Aliasing", "Off", "", $pref::Video::Vsync);
   OptionsMenu.addSettingOption(OptionsSettingStack, "Anisotropic Filtering", "Off", "", $pref::Video::Vsync);
}

//==============================================================================
// AUDIO MENU
//==============================================================================
function AudioMenu::loadSettings()
{
   OptionsSettingStack.clear();
   
   OptionsMenu.addSliderOption(OptionsSettingStack, "Master Volume", $pref::Video::Brightness, "0 1", 10, 5);
   OptionsMenu.addSliderOption(OptionsSettingStack, "Menu Volume", $pref::Video::Brightness, "0 1", 10, 5);
   OptionsMenu.addSliderOption(OptionsSettingStack, "Effects Volume", $pref::Video::Brightness, "0 1", 10, 5);
   OptionsMenu.addSliderOption(OptionsSettingStack, "Music Volume", $pref::Video::Brightness, "0 1", 10, 5);
}