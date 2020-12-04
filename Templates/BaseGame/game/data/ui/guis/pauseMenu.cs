function PauseMenu::onWake(%this)
{
   if($Server::ServerType $= "SinglePlayer")
   {
      $timescale = 0;
      
      sfxSetChannelVolume( $SimAudioType, $pref::SFX::channelVolume[ 0 ] );
   }
   
   PauseMenuList.hidden = false;
   PauseMenuList.setFirstResponder();
   PauseButtonHolder.setActive();
   
   PauseMenuList.clearRows();
   
   if($Tools::loaded && EditorIsActive())
   {
      PauseMenuList.addRow("Exit Editor", "fastLoadWorldEdit", -1, -30); 
   }
   
   PauseMenuList.addRow("Options", "openPauseMenuOptions", -1, -30);
   PauseMenuList.addRow("Exit to Menu", "pauseMenuExitToMenu", -1, -30);
   PauseMenuList.addRow("Exit to Desktop", "pauseMenuExitToDesktop", -1, -30); 
}


function PauseMenu::onSleep(%this)
{
   if($Server::ServerType $= "SinglePlayer")
   {
      $timescale = 1;
      sfxSetChannelVolume( $SimAudioType, $pref::SFX::channelVolume[ $SimAudioType ] );
   }
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