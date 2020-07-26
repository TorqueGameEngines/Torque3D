function MainMenuGui::onAdd(%this)
{
   $activeControllerName = "K&M"; //default input type
}

function MainMenuGui::onWake(%this)
{
   MainMenuButtonList.hidden = false; 
   MainMenuButtonHolder.setActive();
}

function MainMenuGui::onSleep(%this)
{
   MainMenuButtonHolder.hidden = true;
}

function MainMenuButtonHolder::onWake(%this)
{
   %this-->goButton.set("btn_a", "Return", "Go", "MainMenuButtonList.activateRow();");
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

function openSinglePlayerMenu()
{
   $pref::HostMultiPlayer=false;
   Canvas.pushDialog(ChooseLevelDlg);
   ChooseLevelDlg.returnGui = MainMenuGui; 
   MainMenuButtonList.hidden = true; 
   MainMenuButtonHolder.hidden = true;
}

function openMultiPlayerMenu()
{
   $pref::HostMultiPlayer=true;
   Canvas.pushDialog(ChooseLevelDlg);
   ChooseLevelDlg.returnGui = MainMenuGui; 
   MainMenuButtonList.hidden = true; 
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
   MainMenuButtonList.setFirstResponder();
   MainMenuButtonHolder.setActive();
}