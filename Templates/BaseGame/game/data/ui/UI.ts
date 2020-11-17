
// The general flow of a gane - server's creation, loading and hosting clients, and then destruction is as follows:

// First, a client will always create a server in the event that they want to host a single player
// game. Torque3D treats even single player connections as a soft multiplayer game, with some stuff
// in the networking short-circuited to sidestep around lag and packet transmission times.

// initServer() is called, loading the default server scripts.
// After that, if this is a dedicated server session, initDedicated() is called, otherwise initClient is called
// to prep a playable client session.

// When a local game is started - a listen server - via calling StartGame() a server is created and then the client is
// connected to it via createAndConnectToLocalServer().

function UI::onCreate( %this )
{
}

function UI::onDestroy( %this )
{
}

function UI::initServer(%this){}

function UI::onCreateGameServer(%this){}

function UI::onDestroyGameServer(%this){}

function UI::initClient(%this)
{
   //Load UI stuff
   //we need to load this because some of the menu profiles use the sounds here
   //%this.queueExec("./datablocks/guiSounds.ts");
   
   //Profiles
   %this.queueExec("./scripts/profiles.ts");
   
   //Now gui files
   %this.queueExec("./scripts/menuInputButtons.ts");
   
   %this.queueExec("./guis/mainMenu.ts");
   %this.queueExec("./guis/mainMenu.gui");
   
   %this.queueExec("./guis/chooseLevelDlg.ts");
   %this.queueExec("./guis/chooseLevelDlg.gui");
   
   %this.queueExec("./guis/joinServerMenu.ts");
   %this.queueExec("./guis/joinServerMenu.gui");
   
   %this.queueExec("./guis/loadingGui.gui");
   
   %this.queueExec("./guis/optionsMenu.ts");
   %this.queueExec("./guis/optionsMenu.gui");
   
   %this.queueExec("./guis/pauseMenu.ts");
   %this.queueExec("./guis/pauseMenu.gui");
   
   %this.queueExec("./guis/remapDlg.gui");
   %this.queueExec("./guis/remapConfirmDlg.gui");
   
   %this.queueExec("./guis/profiler.ts");
   %this.queueExec("./guis/profiler.gui");
   
   %this.queueExec("./guis/netGraphGui.gui");
   %this.queueExec("./guis/RecordingsDlg.gui");
   
   %this.queueExec("./guis/guiMusicPlayer.ts");
   %this.queueExec("./guis/guiMusicPlayer.gui");
   
   %this.queueExec("./guis/startupGui.ts");
   %this.queueExec("./guis/startupGui.gui");
   
   // Load Editor Dialogs
   %this.queueExec("./guis/messageBoxDlg.gui");
   
   //Load scripts
   %this.queueExec("./scripts/controlsMenu.ts");
   %this.queueExec("./scripts/messageBoxes.ts");
   %this.queueExec("./scripts/help.ts");
   %this.queueExec("./scripts/cursors.ts");
   %this.queueExec("./scripts/utility.ts");
}

function UI::onCreateClientConnection(%this){}

function UI::onDestroyClientConnection(%this){}