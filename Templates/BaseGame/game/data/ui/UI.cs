
// The general flow of a gane - server's creation, loading and hosting clients, and then destruction is as follows:

// First, a client will always create a server in the event that they want to host a single player
// game. Torque3D treats even single player connections as a soft multiplayer game, with some stuff
// in the networking short-circuited to sidestep around lag and packet transmission times.

// initServer() is called, loading the default server scripts.
// After that, if this is a dedicated server session, initDedicated() is called, otherwise initClient is called
// to prep a playable client session.

// When a local game is started - a listen server - via calling StartGame() a server is created and then the client is
// connected to it via createAndConnectToLocalServer().

function UI::create( %this )
{
   if ($Server::Dedicated)
      return;
   
   // Use our prefs to configure our Canvas/Window
   configureCanvas();
}

function UI::destroy( %this )
{
}

function UI::initServer(%this){}

function UI::onCreateServer(%this){}

function UI::onDestroyServer(%this){}

function UI::initClient(%this)
{
   //Load UI stuff
   //we need to load this because some of the menu profiles use the sounds here
   exec("./datablocks/guiSounds.cs");
   
   //Profiles
   exec("./scripts/profiles.cs");
   
   //Now gui files
   exec("./guis/mainMenu.gui");
   exec("./guis/mainMenu.cs");
   
   exec("./guis/chooseLevelDlg.gui");
   exec("./guis/chooseLevelDlg.cs");
   
   exec("./guis/joinServerMenu.gui");
   exec("./guis/joinServerMenu.cs");
   
   exec("./guis/loadingGui.gui");
   
   exec("./guis/optionsMenu.gui");
   exec("./guis/optionsMenu.cs");
   
   exec("./guis/pauseMenu.gui");
   exec("./guis/pauseMenu.cs");
   
   exec("./guis/remapDlg.gui");
   exec("./guis/remapConfirmDlg.gui");
   
   exec("./guis/profiler.gui");
   exec("./guis/profiler.cs");
   
   exec("./guis/netGraphGui.gui");
   exec("./guis/RecordingsDlg.gui");
   
   //exec("./guis/FileDialog.gui");
   //exec("./guis/FileDialog.cs");
   
   exec("./guis/guiMusicPlayer.gui");
   exec("./guis/guiMusicPlayer.cs");
   
   exec("./guis/startupGui.gui");
   exec("./guis/startupGui.cs");
   
   //Load scripts
   exec("./scripts/optionsList.cs");
   exec("./scripts/graphicsMenu.cs");
   exec("./scripts/controlsMenu.cs");
   exec("./scripts/messageBoxes.cs");
   exec("./scripts/help.cs");
   exec("./scripts/cursors.cs");
   
   //exec("./scripts/GuiTreeViewCtrl.cs");
   
   loadStartup();
}

function UI::onCreateClientConnection(%this){}

function UI::onDestroyClientConnection(%this){}