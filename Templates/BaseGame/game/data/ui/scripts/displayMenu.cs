function DisplayMenu::loadSettings()
{
   OptionsMenu.currentMenu = "DisplayMenu";
   OptionsSettingStack.clear();
   
   %APICount = getTokenCount(GraphicsDriverSetting::getList(),",");
   if(%APICount > 1)
      OptionsMenu.addSettingOption(OptionsSettingStack, "Diplay API", "", "GraphicsDriverSetting");
   
   OptionsMenu.addSettingOption(OptionsSettingStack, "Screen Resolution", "", "ScreenResolutionSetting");
   OptionsMenu.addSettingOption(OptionsSettingStack, "Fullscreen", "", "FullscreenSetting");
   OptionsMenu.addSettingOption(OptionsSettingStack, "VSync", "", "VSyncSetting");
   
   OptionsMenu.addSliderOption(OptionsSettingStack, "Field of View", $pref::Video::FOV, "65 120", 55, 75);
   
   OptionsMenu.addSliderOption(OptionsSettingStack, "Brightness", $pref::Video::Brightness, "0 1", 10, 5);
   OptionsMenu.addSliderOption(OptionsSettingStack, "Contrast", $pref::Video::Contrast, "0 1", 10, 5);
   
   GraphicsSettingsCache.empty();
}

function DisplayMenu::apply(%this)
{
   //Loop through the settings cache and actually apply the values
   %cachedSettingCount = GraphicsSettingsCache.count();
   
   for(%i=0; %i < %cachedSettingCount; %i++)
   {
      %var = GraphicsSettingsCache.getKey(%i);  
      %val = GraphicsSettingsCache.getValue(%i);
      
      if(%var $= "$pref::Video::displayDevice")
      {
         MessageBoxOK( "Change requires restart", "Please restart the game for a display device change to take effect." );
      }
      
      setVariable(%var, %val);
   }
      
   //Update the display settings now
   $pref::Video::Resolution = getWord( $pref::Video::Resolution, 0 ) SPC getWord( $pref::Video::Resolution, 2 );
	
   /*if ( %newFullScreen $= "false" )
	{
      // If we're in windowed mode switch the fullscreen check
      // if the resolution is bigger than the desktop.
      %deskRes    = getDesktopResolution();      
      %deskResX   = getWord(%deskRes, $WORD::RES_X);
      %deskResY   = getWord(%deskRes, $WORD::RES_Y);
	   if (  getWord( %newRes, $WORD::RES_X ) > %deskResX || 
	         getWord( %newRes, $WORD::RES_Y ) > %deskResY )
      {
         $pref::Video::FullScreen = "true";
         GraphicsMenuFullScreen.setStateOn( true );
      }
	}*/

   // Build the final mode string.
	%newMode = $pref::Video::Resolution SPC $pref::Video::FullScreen SPC 32 SPC $pref::Video::RefreshRate SPC $pref::Video::AA;
	
   // Change the video mode.   
   /*if (  %newMode !$= $pref::Video::mode || 
         %newVsync != $pref::Video::disableVerticalSync )
   {
      if ( %testNeedApply )
         return true;*/

      $pref::Video::mode = %newMode;
      //$pref::Video::disableVerticalSync = %newVsync;      
      configureCanvas();
   //}
   
   echo("Exporting client prefs");
   %prefPath = getPrefpath();
   export("$pref::*", %prefPath @ "/clientPrefs.cs", false);
}
//
function GraphicsDriverSetting::set(%setting)
{
   switch$(%setting)
   {
      case "D3D11":
         GraphicsMenu::set("$pref::Video::displayDevice", "D3D11");
      case "OpenGL":
         GraphicsMenu::set("$pref::Video::displayDevice", "OpenGL");
      default:
         GraphicsMenu::set("$pref::Video::displayDevice", "OpenGL");
   }
}

function GraphicsDriverSetting::get()
{
   if($pref::Video::displayDevice $= "D3D11")
      return "D3D11";
   else if($pref::Video::displayDevice $= "OpenGL")
      return "OpenGL";
   else
      return "Unknown";
}

function GraphicsDriverSetting::getList()
{
   %returnsList = "";
   %buffer = getDisplayDeviceList();
   %deviceCount = getFieldCount( %buffer );   
   %numAdapters = GFXInit::getAdapterCount();
   
   %count = 0;
   for(%i = 0; %i < %deviceCount; %i++)
   {
      %deviceDesc = getField(%buffer, %i);
      
      if(%deviceDesc $= "GFX Null Device")
         continue;
         
      for( %i = 0; %i < %numAdapters; %i ++ )
      {
         if( GFXInit::getAdapterName( %i ) $= %deviceDesc )
         {
            %deviceName = GFXInit::getAdapterType( %i );
            break;
         }
      }
         
      if(%count != 0)
         %returnsList = %returnsList @ "," @ %deviceName;
      else
         %returnsList = %deviceName;
         
      %count++;
   }

   return %returnsList;
}

//
function ScreenResolutionSetting::set(%setting)
{
   GraphicsMenu::set("$pref::Video::Resolution", %setting);
}

function ScreenResolutionSetting::get()
{
   return _makePrettyResString( $pref::Video::Resolution );
}

function ScreenResolutionSetting::getList()
{
   %returnsList = "";
   
   %resCount = Canvas.getModeCount();
   for (%i = 0; %i < %resCount; %i++)
   {
      %testResString = Canvas.getMode( %i );
      %testRes = _makePrettyResString( %testResString );
      
      //sanitize
      %found = false;
      %retCount = getTokenCount(%returnsList, ",");
      for (%x = 0; %x < %retCount; %x++)
      {
         %existingEntry = getToken(%returnsList, ",", %x);
         if(%existingEntry $= %testRes)
         {
            %found = true;
            break;  
         }
      }
      
      if(%found)
         continue;
                     
      if(%i != 0)
         %returnsList = %returnsList @ "," @ %testRes;
      else
         %returnsList = %testRes;
   }
   
   return %returnsList;
}

//
function FullscreenSetting::set(%setting)
{
   switch$(%setting)
   {
      case "On":
         GraphicsMenu::set("$pref::Video::FullScreen", "1");
      case "Off":
         GraphicsMenu::set("$pref::Video::FullScreen", "0");
      default:
         GraphicsMenu::set("$pref::Video::FullScreen", "0");
   }
}

function FullscreenSetting::get()
{
   if($pref::Video::FullScreen == 1)
      return "On";
   else if($pref::Video::FullScreen == 0)
      return "Off";
   else
      return "Custom";
}

function FullscreenSetting::getList()
{
   return "Off,On";
}

//
function VSyncSetting::set(%setting)
{
   switch$(%setting)
   {
      case "On":
         GraphicsMenu::set("$pref::Video::disableVerticalSync", "0");
      case "Off":
         GraphicsMenu::set("$pref::Video::disableVerticalSync", "1");
      default:
         GraphicsMenu::set("$pref::Video::disableVerticalSync", "1");
   }
}

function VSyncSetting::get()
{
   if($pref::Video::disableVerticalSync == 0)
      return "On";
   else if($pref::Video::disableVerticalSync == 1)
      return "Off";
   else
      return "Custom";
}

function VSyncSetting::getList()
{
   return "Off,On";
}