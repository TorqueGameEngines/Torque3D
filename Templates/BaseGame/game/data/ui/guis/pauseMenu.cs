function PauseMenuList::onAdd(%this)
{
   %this.addRow("Options", "openPauseMenuOptions", -1, -30);
   %this.addRow("Exit to Menu", "pauseMenuExitToMenu", -1, -30);
   %this.addRow("Exit to Desktop", "pauseMenuExitToDesktop", -1, -30);  
}

function PauseMenu::onWake(%this)
{
   $timescale = 0;
}


function PauseMenu::onSleep(%this)
{
   $timescale = 1;
}

function PauseMenu::onReturnTo(%this)
{
   PauseMenuList.hidden = false;
   PauseButtonHolder.refresh();
}

function openPauseMenuOptions()
{
   Canvas.pushDialog(OptionsMenu);
   OptionsMenu.returnGui = PauseMenu; 
   PauseMenuList.hidden = true;
}

function pauseMenuExitToMenu()
{
   PauseMenuList.hidden = true;
   MessageBoxOKCancel("Exit?", "Do you wish to exit to the Main Menu?", "escapeFromGame();", "PauseMenu.onReturnTo();");
}

function pauseMenuExitToDesktop()
{
   PauseMenuList.hidden = true;
   MessageBoxOKCancel("Exit?", "Do you wish to exit to the desktop?", "quit();", "PauseMenu.onReturnTo();");
}

function PauseButtonHolder::onWake(%this)
{
   %this.refresh();
}

function PauseButtonHolder::refresh(%this)
{
   PauseButtonHolder.add(GamepadButtonsGui);
   
   GamepadButtonsGui.clearButtons();
   
   GamepadButtonsGui.setButton(2, "A", "", "", "", true);
   GamepadButtonsGui.setButton(3, "B", "Esc", "Back", "Canvas.popDialog();");
   
   GamepadButtonsGui.refreshButtons();
}