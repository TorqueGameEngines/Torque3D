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
   
   /*%this-->OptAudioVolumeMaster.setValue( $pref::SFX::masterVolume );
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
	   AudioMenuSoundDriver.setSelected( %selId );*/
	   
   OptionsSettingStack.clear();
   
   OptionsMenu.addSliderOption(OptionsSettingStack, "Master Volume", $pref::Video::Brightness, "0 1", 10, 5);
   OptionsMenu.addSliderOption(OptionsSettingStack, "Menu Volume", $pref::Video::Brightness, "0 1", 10, 5);
   OptionsMenu.addSliderOption(OptionsSettingStack, "Effects Volume", $pref::Video::Brightness, "0 1", 10, 5);
   OptionsMenu.addSliderOption(OptionsSettingStack, "Music Volume", $pref::Video::Brightness, "0 1", 10, 5);
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
      $AudioTestHandle = sfxPlayOnce( AudioChannel, "data/ui/sounds/volumeTest.wav" );
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
      $AudioTestHandle = sfxPlayOnce( $AudioTestDescription, "data/ui/sounds/volumeTest.wav" );
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