function PauseMenuList::onAdd(%this)
{
   %this.addRow("Options", "openPauseMenuOptions", -1, -30);
   %this.addRow("Exit to Menu", "pauseMenuExitToMenu", -1, -30);
   %this.addRow("Exit to Desktop", "pauseMenuExitToDesktop", -1, -30);  
}

function PauseMenu::onWake(%this)
{
   $timescale = 0;
   
   PauseButtonHolder.setActive();
}


function PauseMenu::onSleep(%this)
{
   $timescale = 1;
}

function PauseMenu::onReturnTo(%this)
{
   PauseMenuList.hidden = false;
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
   %this-->goButton.set("A", "Enter", "OK", "PauseMenuList.activateRow();", true);
   %this-->backButton.set("B", "Esc", "Back", "Canvas.popDialog();");
}