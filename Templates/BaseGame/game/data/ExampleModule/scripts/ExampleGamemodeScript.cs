//-----------------------------------------------------------------------------
// The server has started up so do some game start up
//-----------------------------------------------------------------------------

//This file implements game mode logic for an Example gamemode. The primary functions:
//ExampleGameMode::onMissionStart
//ExampleGameMode::onMissionReset
//ExampleGameMode::onMissionEnd
//Are the primary hooks for the server to start, restart and end any active gamemodes
//onMissionStart, for example is called from core/clientServer/scripts/server/levelLoad.cs
//It's called once the server has successfully loaded the level, and has parsed
//through any active scenes to get GameModeNames defined by them. It then iterates
//over them and calls these callbacks to envoke gamemode behaviors. This allows multiple
//gamemodes to be in effect at one time. Modules can implement as many gamemodes as you want.
//
//For levels that can be reused for multiple gammodes, the general setup would be a primary level file
//with the Scene in it having the main geometry, weapons, terrain, etc. You would then have subScenes that
//each contain what's necessary for the given gamemode, such as a subScene that just adds the flags and capture
//triggers for a CTF mode. The subscene would then have it's GameModeName defined to run the CTF gamemode logic
//and the levelLoad code will execute it.

function ExampleGameMode::onCreateGame()
{
   // Note: The Game object will be cleaned up by MissionCleanup.  Therefore its lifetime is
   // limited to that of the mission.
   new ScriptObject(ExampleGameMode){};

   return ExampleGameMode;
}

//This function is called when the level finishes loading. It sets up the initial configuration, variables and
//spawning and dynamic objects, timers or rules needed for the gamemode to run
function ExampleGameMode::onMissionStart(%this)
{
   //set up the game and game variables
   %this.initGameVars();

   if (%this.running)
   {
      error("onMissionStart: End the game first!");
      return;
   }

   // Start the game timer
   if (%this.duration)
      %this.gameSchedule = schedule(%this.duration * 1000, "onGameDurationEnd");
      
   %this.running = true;
}

//This function is called when the level ends. It can be envoked due to the gamemode ending
//but is also kicked off when the game server is shut down as a form of cleanup for anything the gamemode
//created or is managing like the above mentioned dynamic objects or timers
function ExampleGameMode::onMissionEnded(%this)
{
   if (!%this.running)
   {
      error("onMissionEnded: No game running!");
      return;
   }

   // Stop any game timers
   cancel(%this.gameSchedule);

   %this.running = false;
}

//This function is called in the event the server resets and is used to re-initialize the gamemode
function ExampleGameMode::onMissionReset(%this)
{
   // Called by resetMission(), after all the temporary mission objects
   // have been deleted.
   %this.initGameVars();
}

//This sets up our gamemode's duration time
function ExampleGameMode::initGameVars(%this)
{
   // Set the gameplay parameters
   %this.duration = 30 * 60;
}

//This is called when the timer runs out, allowing the gamemode to end
function ExampleGameMode::onGameDurationEnd(%this)
{
   //we don't end if we're currently editing the level
   if (%this.duration && !(EditorIsActive() && GuiEditorIsActive()))
      %this.onMissionEnded();
}

//This is called to actually spawn a control object for the player to utilize
//A player character, spectator camera, etc.
function ExampleGameMode::spawnControlObject(%this, %client)
{
   //In this example, we just spawn a camera
   if (!isObject(%client.camera))
   {
      if(!isObject(Observer))
      {
         datablock CameraData(Observer)
         {
            mode = "Observer";
         };  
      }
      
      %client.camera = spawnObject("Camera", Observer);
   }

   // If we have a camera then set up some properties
   if (isObject(%client.camera))
   {
      MissionCleanup.add( %this.camera );
      %client.camera.scopeToClient(%client);

      %client.setControlObject(%client.camera);

      %client.camera.setTransform("0 0 1 0 0 0 0");
   }
}

//This is called when the client has initially established a connection to the game server
//It's used for setting up anything ahead of time for the client, such as loading in client-passed
//config stuffs, saved data or the like that should be handled BEFORE the client has actually entered
//the game itself
function ExampleGameMode::onClientConnect(%this, %client)
{
}

//This is called when a client enters the game server. It's used to spawn a player object
//set up any client-specific properties such as saved configs, values, their name, etc
//These callbacks are activated in core/clientServer/scripts/server/levelDownload.cs
function ExampleGameMode::onClientEnterGame(%this, %client)
{
   //Set the player name based on the client's connection data
   %client.setPlayerName(%client.connectData);
   
   %this.spawnControlObject(%client);
}

//This is called when the player leaves the game server. It's used to clean up anything that
//was spawned or setup for the client when it connected, in onClientEnterGame
//These callbacks are activated in core/clientServer/scripts/server/levelDownload.cs
function ExampleGameMode::onClientLeaveGame(%this, %client)
{
   // Cleanup the camera
   if (isObject(%client.camera))
      %client.camera.delete();
}

//This is called when the player has connected and finaly setup is done and control is handed
//over to the client. It allows a point to special-case setting the client's canvas content
//(Such as a gamemode-specific GUI) or setting up gamemode-specific keybinds/control schemes
function ExampleGameMode::onInitialControlSet(%this)
{
   
}