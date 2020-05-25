function MainMenuGui::onAdd(%this)
{
   GamepadButtonsGui.initMenuButtons();
}

function MainMenuGui::onWake(%this)
{
   MainMenuButtonList.hidden = false; 
}

function MainMenuGui::onSleep(%this)
{
}

function MainMenuButtonHolder::onWake(%this)
{
   %this.refresh();
}

function MainMenuButtonHolder::refresh(%this)
{
   %this.add(GamepadButtonsGui);
   
   GamepadButtonsGui.clearButtons();
   
   //GamepadButtonsGui.setButton(2, "A", "Select", "Go", "echo(\"FART\");");
   //GamepadButtonsGui.setButton(3, "B", "Esc", "Back", "");
   
   GamepadButtonsGui.refreshButtons();
}

function MainMenuButtonList::onAdd(%this)
{
   MainMenuButtonList.addRow("Single Player", "openSinglePlayerMenu", 0);
   MainMenuButtonList.addRow("Create Server", "openMultiPlayerMenu", 4, -15);
   MainMenuButtonList.addRow("Join Server", "openJoinServerMenu", 4, -15);
   MainMenuButtonList.addRow("Options", "openOptionsMenu", 6, -15);
   MainMenuButtonList.addRow("Open World Editor", "openWorldEditorBtn", 6, -15);
   MainMenuButtonList.addRow("Open GUI Editor", "openGUIEditorBtn", 6, -15);
   MainMenuButtonList.addRow("Exit Game", "quit", 8, -15);
}

function UIMenuButtonList::onInputEvent(%this, %device, %action, %state)
{
   if(%state)
      GamepadButtonsGui.processInputs(%device, %action);
}

function UIMenuButtonList::onAxisEvent(%this, %device, %action, %axisVal)
{
   GamepadButtonsGui.processAxisEvent(%device, %action);
}

function openSinglePlayerMenu()
{
   $pref::HostMultiPlayer=false;
   Canvas.pushDialog(ChooseLevelDlg);
   ChooseLevelDlg.returnGui = MainMenuGui; 
   MainMenuButtonList.hidden = true; 
   MainMenuAppLogo.setBitmap("data/ui/images/Torque-3D-logo");
}

function openMultiPlayerMenu()
{
   $pref::HostMultiPlayer=true;
   Canvas.pushDialog(ChooseLevelDlg);
   ChooseLevelDlg.returnGui = MainMenuGui; 
   MainMenuButtonList.hidden = true; 
   MainMenuAppLogo.setBitmap("data/ui/images/Torque-3D-logo");
}

function openJoinServerMenu()
{
   Canvas.pushDialog(JoinServerMenu);
   JoinServerMenu.returnGui = MainMenuGui; 
   MainMenuButtonList.hidden = true; 
}

function openOptionsMenu()
{
   Canvas.pushDialog(OptionsMenu);
   OptionsMenu.returnGui = MainMenuGui; 
   MainMenuButtonList.hidden = true; 
   MainMenuAppLogo.setBitmap("data/ui/images/Torque-3D-logo");
}

function openWorldEditorBtn()
{
   fastLoadWorldEdit(1);
}

function openGUIEditorBtn()
{
   fastLoadGUIEdit(1);
}

function MainMenuGui::onReturnTo(%this)
{
   MainMenuButtonList.hidden = false;
   MainMenuAppLogo.setBitmap("data/ui/images/Torque-3D-logo-shortcut");
}