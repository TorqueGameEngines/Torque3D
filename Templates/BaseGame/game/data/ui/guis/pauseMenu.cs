function PauseMenuList::onAdd(%this)
{
   %this.addRow("Options", "openPauseMenuOptions", -1, -30);
   %this.addRow("Exit to Menu", "pauseMenuExitToMenu", -1, -30);
   %this.addRow("Exit to Desktop", "pauseMenuExitToDesktop", -1, -30);  
}

function PauseMenu::onWake(%this)
{
   $timescale = 0;
   
   PauseMenuList.hidden = false;
   PauseMenuList.setFirstResponder();
   PauseButtonHolder.setActive();
}


function PauseMenu::onSleep(%this)
{
   $timescale = 1;
}

function PauseMenu::onReturnTo(%this)
{
   PauseMenuList.hidden = false;
   PauseMenuList.setFirstResponder();
   PauseButtonHolder.setActive();
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
   %this-->goButton.set("btn_a", "Return", "OK", "PauseMenuList.activateRow();", true);
   %this-->backButton.set("btn_b", "Escape", "Back", "Canvas.popDialog();");
}