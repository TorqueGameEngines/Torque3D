
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
   //exec("./datablocks/guiSounds.cs");
   
   //Profiles
   exec("./scripts/profiles.cs");
   
   //Now gui files
   exec("./guis/guiGamepadButton.cs");
   exec("./guis/guiGamepadButton.gui");
   
   exec("./guis/mainMenu.cs");
   exec("./guis/mainMenu.gui");
   
   exec("./guis/chooseLevelDlg.cs");
   exec("./guis/chooseLevelDlg.gui");
   
   exec("./guis/joinServerMenu.cs");
   exec("./guis/joinServerMenu.gui");
   
   exec("./guis/loadingGui.gui");
   
   exec("./guis/optionsMenu.cs");
   exec("./guis/optionsMenu.gui");
   
   exec("./guis/pauseMenu.cs");
   exec("./guis/pauseMenu.gui");
   
   exec("./guis/remapDlg.gui");
   exec("./guis/remapConfirmDlg.gui");
   
   exec("./guis/profiler.cs");
   exec("./guis/profiler.gui");
   
   exec("./guis/netGraphGui.gui");
   exec("./guis/RecordingsDlg.gui");
   
   exec("./guis/guiMusicPlayer.cs");
   exec("./guis/guiMusicPlayer.gui");
   
   exec("./guis/startupGui.cs");
   exec("./guis/startupGui.gui");
   
   // Load Editor Dialogs
   exec("./guis/messageBoxDlg.gui");
   
   //Load scripts
   exec("./scripts/controlsMenu.cs");
   exec("./scripts/messageBoxes.cs");
   exec("./scripts/help.cs");
   exec("./scripts/cursors.cs");
   exec("./scripts/utility.cs");
   exec("./scripts/default.keybinds.cs");
   
   exec("./guis/menuGraphics.gui");
   exec("./guis/menuGraphics.cs");
   
   loadStartup();
}

function UI::onCreateClientConnection(%this){}

function UI::onDestroyClientConnection(%this){}