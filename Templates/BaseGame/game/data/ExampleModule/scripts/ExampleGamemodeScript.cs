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

//This function is called when the level finishes loading. It sets up the initial configuration, variables and
//spawning and dynamic objects, timers or rules needed for the gamemode to run
function ExampleGameMode::onMissionStart()
{
   //set up the game and game variables
   ExampleGameMode::initGameVars();

   if ($Game::Running)
   {
      error("onMissionStart: End the game first!");
      return;
   }

   // Start the game timer
   if ($Game::Duration)
      $Game::Schedule = schedule($Game::Duration * 1000, "onGameDurationEnd");
      
   $Game::Running = true;
   
   $Game = ExampleGameMode;
}

//This function is called when the level ends. It can be envoked due to the gamemode ending
//but is also kicked off when the game server is shut down as a form of cleanup for anything the gamemode
//created or is managing like the above mentioned dynamic objects or timers
function ExampleGameMode::onMissionEnded()
{
   if (!$Game::Running)
   {
      error("onMissionEnded: No game running!");
      return;
   }

   // Stop any game timers
   cancel($Game::Schedule);

   $Game::Running = false;
   $Game = "";
}

//This function is called in the event the server resets and is used to re-initialize the gamemode
function ExampleGameMode::onMissionReset()
{
   // Called by resetMission(), after all the temporary mission objects
   // have been deleted.
   ExampleGameMode::initGameVars();
}

//This sets up our gamemode's duration time
function ExampleGameMode::initGameVars()
{
   // Set the gameplay parameters
   $Game::Duration = 30 * 60;
}

//This is called when the timer runs out, allowing the gamemode to end
function ExampleGameMode::onGameDurationEnd()
{
   //we don't end if we're currently editing the level
   if ($Game::Duration && !(EditorIsActive() && GuiEditorIsActive()))
      ExampleGameMode::onMissionEnded();
}

//This is called when a client enters the game server. It's used to spawn a player object
//set up any client-specific properties such as saved configs, values, their name, etc
//These callbacks are activated in core/clientServer/scripts/server/levelDownload.cs
function ExampleGameMode::onClientEnterGame(%client)
{
   //Set the player name based on the client's connection data
   %client.setPlayerName(%client.connectData);

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

//This is called when the player leaves the game server. It's used to clean up anything that
//was spawned or setup for the client when it connected, in onClientEnterGame
//These callbacks are activated in core/clientServer/scripts/server/levelDownload.cs
function ExampleGameMode::onClientLeaveGame(%client)
{
   // Cleanup the camera
   if (isObject(%client.camera))
      %client.camera.delete();

}