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
   %yesNoList = "No\tYes";
   %onOffList = "Off\tOn";
   %highMedLow = "Low\tMedium\tHigh";
   %anisoFilter = "Off\t4\t8\t16";
   OptionsMenuSettingsList.addOptionRow("Shadow Quality", "High\tMedium\tLow\tNone", false, "", -1, -30);
   OptionsMenuSettingsList.addOptionRow("Soft Shadow Quality", %highMedLow, false, "", -1, -30);
   OptionsMenuSettingsList.addOptionRow("Mesh Quality", %highMedLow, false, "", -1, -30);
   OptionsMenuSettingsList.addOptionRow("Texture Quality", %highMedLow, false, "", -1, -30);
   OptionsMenuSettingsList.addOptionRow("Terrain Quality", %highMedLow, false, "", -1, -30);
   OptionsMenuSettingsList.addOptionRow("Decal Lifetime", %highMedLow, false, "", -1, -30);
   OptionsMenuSettingsList.addOptionRow("Ground Cover Density", %highMedLow, false, "", -1, -30);
   OptionsMenuSettingsList.addOptionRow("Shader Quality", %highMedLow, false, "", -1, -30);
   OptionsMenuSettingsList.addOptionRow("Anisotropic Filtering", %anisoFilter, false, "", -1, -30);
   OptionsMenuSettingsList.addOptionRow("Anti-Aliasing", "4\t2\t1\tOff", false, "", -1, -30);
   OptionsMenuSettingsList.addOptionRow("Refresh Rate", "75\t60\t30", false, "", -1, -30);
   OptionsMenuSettingsList.addOptionRow("Parallax", %onOffList, false, "", -1, -30);
   OptionsMenuSettingsList.addOptionRow("Water Reflections", %onOffList, false, "", -1, -30);
   OptionsMenuSettingsList.addOptionRow("SSAO", %onOffList, false, "", -1, -30);
   OptionsMenuSettingsList.addOptionRow("Depth of Field", %onOffList, false, "", -1, -30);
   OptionsMenuSettingsList.addOptionRow("Vignette", %onOffList, false, "", -1, -30);
   OptionsMenuSettingsList.addOptionRow("Light Rays", %onOffList, false, "", -1, -30);
}

function OptionsMenu::onWake(%this)
{
   MainMenuButtonList.hidden = true;
   
   %this.pageTabIndex = 0;
   %tab = %this.getTab();
   %tab.performClick();
}

function OptionsButtonHolder::onWake(%this)
{
   %this.refresh();
}

function OptionsButtonHolder::refresh(%this)
{
   OptionsButtonHolder.add(GamepadButtonsGui);
   
   GamepadButtonsGui.clearButtons();
   
   GamepadButtonsGui.setButton(0, "LB", "", "Prev Tab", "OptionsMenu.prevTab();", true);
   GamepadButtonsGui.setButton(1, "RB", "", "Next Tab", "OptionsMenu.nextTab();", true);
   GamepadButtonsGui.setButton(2, "Start", "Enter", "Apply", "OptionsMenu.apply();");
   GamepadButtonsGui.setButton(3, "B", "Esc", "Back", "OptionsMenu.backOut();");
   GamepadButtonsGui.setButton(7, "Back", "R", "Reset", "OptionsMenu.backOut();");
   
   GamepadButtonsGui.refreshButtons();
}

function OptionsMenuSettingsList::onChange(%this)
{
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
   
   %resolutionList = getScreenResolutionList();
   //OptionsMenuSettingsList.addOptionsRow("Resolution", %yesNoList, false, "", 0, -15);
   OptionsMenuSettingsList.addOptionRow("Resolution", %resolutionList, false, "screenResolutionOptionChanged", -1, -30);
}

function _makePrettyResString( %resString, %giveAspectRation )
{
   %width = getWord( %resString, $WORD::RES_X );
   %height = getWord( %resString, $WORD::RES_Y );
   
   %aspect = %width / %height;
   %aspect = mRound( %aspect * 100 ) * 0.01;            
   
   switch$( %aspect )
   {
      case "1.33":
         %aspect = "4:3";
      case "1.78":
         %aspect = "16:9";
      default:
         %aspect = "";
   }
   
   %outRes = %width @ " x " @ %height;
   if ( %giveAspectRation && %aspect !$= "" )
      %outRes = %outRes @ "  (" @ %aspect @ ")";
      
   return %outRes;   
}

function getScreenResolutionList()
{
   %returnsList = "";
   
   %resCount = Canvas.getModeCount();
   for (%i = 0; %i < %resCount; %i++)
   {
      %testResString = Canvas.getMode( %i );
      %testRes = _makePrettyResString( %testResString );
      
      //sanitize
      %found = false;
      %retCount = getTokenCount(%returnsList, "\t");
      for (%x = 0; %x < %retCount; %x++)
      {
         %existingEntry = getToken(%returnsList, "\t", %x);
         if(%existingEntry $= %testRes)
         {
            %found = true;
            break;  
         }
      }
      
      if(%found)
         continue;
                     
      if(%i != 0)
         %returnsList = %returnsList @ "\t" @ %testRes;
      else
         %returnsList = %testRes;
   }
   
   return %returnsList;
}

function screenResolutionOptionChanged()
{
   echo("Resolution Changed to: " @ OptionsMenuSettingsList.getCurrentOption(0));
}

function OptionsMenu::populateGraphicsSettingsList(%this)
{
   %this.pageTabIndex = 1;
   OptionsMenuSettingsList.clearRows();
   
   %yesNoList = "No\tYes";
   %onOffList = "Off\tOn";
   %highMedLow = "Low\tMedium\tHigh";
   %anisoFilter = "Off\t4\t8\t16";
   OptionsMenuSettingsList.addOptionRow("Shadow Quality", "High\tMedium\tLow\tNone", false, "", -1, -30);
   OptionsMenuSettingsList.addOptionRow("Soft Shadow Quality", %highMedLow, false, "", -1, -30);
   OptionsMenuSettingsList.addOptionRow("Mesh Quality", %highMedLow, false, "", -1, -30);
   OptionsMenuSettingsList.addOptionRow("Texture Quality", %highMedLow, false, "", -1, -30);
   OptionsMenuSettingsList.addOptionRow("Terrain Quality", %highMedLow, false, "", -1, -30);
   OptionsMenuSettingsList.addOptionRow("Decal Lifetime", %highMedLow, false, "", -1, -30);
   OptionsMenuSettingsList.addOptionRow("Ground Cover Density", %highMedLow, false, "", -1, -30);
   OptionsMenuSettingsList.addOptionRow("Shader Quality", %highMedLow, false, "", -1, -30);
   OptionsMenuSettingsList.addOptionRow("Anisotropic Filtering", %anisoFilter, false, "", -1, -30);
   OptionsMenuSettingsList.addOptionRow("Anti-Aliasing", "4\t2\t1\tOff", false, "", -1, -30);
   OptionsMenuSettingsList.addOptionRow("Refresh Rate", "75\t60\t30", false, "", -1, -30);
   OptionsMenuSettingsList.addOptionRow("Parallax", %onOffList, false, "", -1, -30);
   OptionsMenuSettingsList.addOptionRow("Water Reflections", %onOffList, false, "", -1, -30);
   OptionsMenuSettingsList.addOptionRow("SSAO", %onOffList, false, "", -1, -30);
   OptionsMenuSettingsList.addOptionRow("Depth of Field", %onOffList, false, "", -1, -30);
   OptionsMenuSettingsList.addOptionRow("Vignette", %onOffList, false, "", -1, -30);
   OptionsMenuSettingsList.addOptionRow("Light Rays", %onOffList, false, "", -1, -30);
}

function OptionsMenu::populateAudioSettingsList(%this)
{
   %this.pageTabIndex = 2;
   OptionsMenuSettingsList.clearRows();
   
   %yesNoList = "Yes\tNo";
   OptionsMenuSettingsList.addOptionRow("Audio Device", %yesNoList, false, "", -1, -15);
}

function OptionsMenu::populateKeyboardMouseSettingsList(%this)
{
   %this.pageTabIndex = 3;
   OptionsMenuSettingsList.clearRows();
   
   OptionsMenuSettingsList.addOptionRow("Forward", "W", false, "", -1, -15);
}

function OptionsMenu::populateGamepadSettingsList(%this)
{
   %this.pageTabIndex = 4;
   OptionsMenuSettingsList.clearRows();
}

function OptionsMenuList::activateRow(%this)
{
   OptionsMenuSettingsList.setFirstResponder();
}

function OptionsMenuList::backOut(%this)
{
   OptionsMenuList.setFirstResponder();
}

function OptionsMenuOKButton::onClick(%this)
{
    //save the settings and then back out
    eval(OptionsMenu.currentMenu@"::apply();");
    OptionsMenu.backOut();
}

//
//
function OptionsMenuSettingsList::backOut(%this)
{
   OptionsMenuList.setFirstResponder();
}
//
//

function OptionsMenuCancelButton::onClick(%this)
{
    //we don't save, so just back out of the menu 
    OptionsMenu.backOut();
}

function OptionsMenuDefaultsButton::onClick(%this)
{
    //we don't save, so go straight to backing out of the menu    
    eval(OptionsMenu.currentMenu@"::applyDefaults();");
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
    %option = TAMLRead("data/ui/guis/graphicsMenuSettingsCtrl.taml");
    
    if(!isMethod(%settingsGroup, "get") || !isMethod(%settingsGroup, "set"))
    {
      error("OptionsMenu::addSettingsOption - unrecognized settings group of: " @ %settingsGroup @ ". Did not have proper getter/setter");
      return "";
    }
    
    %option-->nameText.text = %optionName;
    %option-->SettingText.text = eval(%settingsGroup@"::"@"get();");
    %option.qualitySettingGroup = %settingsGroup;
    %option.targetVar = %targetVar;

    %arrayTarget.add(%option);

    return %option;
}

function OptionsMenu::addSliderOption(%this, %arrayTarget, %optionName, %variable, %range, %ticks, %value, %class)
{
    %option = TAMLRead("data/ui/guis/graphicsMenuSettingsSlider.taml");
    
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

//
function OptionsMenuForwardSetting::onClick(%this)
{
   //we need to advance through the value list, unless it's the end, in which case we do nothing  
   echo("Move forward in the list!");
   
   %settingCtrl = %this.getParent();
   %settingsList = eval(%settingCtrl.qualitySettingGroup@"::getList();");
   %settingsListCount = getTokenCount(%settingsList, ",");
   %currentSetting = %settingCtrl-->SettingText.text;
   
   //We consider 'custom' to be the defacto end of the list. The only way back is to go lower
   if(%currentSetting $= "Custom")
      return;
      
   %currentSettingIdx = OptionsMenu.getCurrentIndexFromSetting(%settingCtrl);
   
   if(%currentSettingIdx != %settingsListCount-1)
   {
      %currentSettingIdx++;
      
      //advance by one
      %newSetting = getToken(%settingsList, ",", %currentSettingIdx);
      eval(%settingCtrl.qualitySettingGroup@"::set(\""@%newSetting@"\");");
      %settingCtrl-->SettingText.setText( %newSetting );
      
      if(%currentSettingIdx == %settingsListCount)
      {
         //if we hit the end of the list, disable the forward button  
      }
   }
}

function OptionsMenuBackSetting::onClick(%this)
{
   //we need to advance through the value list, unless it's the end, in which case we do nothing  
   echo("Move back in the list!");
   
   %settingCtrl = %this.getParent();
   %settingsList = eval(%settingCtrl.qualitySettingGroup@"::getList();");
   %settingsListCount = getTokenCount(%settingsList, ",");
   %currentSetting = %settingCtrl-->SettingText.text;
   
   %currentSettingIdx = OptionsMenu.getCurrentIndexFromSetting(%settingCtrl);
   
   if(%currentSettingIdx != 0)
   {
      %currentSettingIdx--;
      
      //advance by one
      %newSetting = getToken(%settingsList, ",", %currentSettingIdx);
      eval(%settingCtrl.qualitySettingGroup@"::set(\""@%newSetting@"\");");
      %settingCtrl-->SettingText.setText( %newSetting );
      
      if(%currentSettingIdx == %settingsListCount)
      {
         //if we hit the end of the list, disable the forward button  
      }
   }
}

function OptionsMenu::getCurrentIndexFromSetting(%this, %settingCtrl)
{
   %settingsList = eval(%settingCtrl.qualitySettingGroup@"::getList();");
   %settingsListCount = getTokenCount(%settingsList, ",");
   %currentSetting = %settingCtrl-->SettingText.text;
   
   for ( %i=0; %i < %settingsListCount; %i++ )
   {
      %level = getToken(%settingsList, ",", %i);
      
      //find our current level
      if(%currentSetting $= %level)
      {
         return %i;
      }
   }
   
   return -1;
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