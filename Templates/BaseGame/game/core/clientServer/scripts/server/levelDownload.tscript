//-----------------------------------------------------------------------------
// Copyright (c) 2012 GarageGames, LLC
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Mission Loading
// The server portion of the client/server mission loading process
//-----------------------------------------------------------------------------
//--------------------------------------------------------------------------
// Loading Phases:
// Phase 1: Transmit Datablocks
//          Transmit targets
// Phase 2: Transmit Ghost Objects
// Phase 3: Start Game
//
// The server invokes the client MissionStartPhase[1-3] function to request
// permission to start each phase.  When a client is ready for a phase,
// it responds with MissionStartPhase[1-3]Ack.

//----------------------------------------------------------------------------
// Phase 1 
//----------------------------------------------------------------------------
$Pref::Server::EnableDatablockCache = true;
$pref::Server::DatablockCacheFilename = "data/cache/server/datablock_cache_c.dbc";
function GameConnection::loadMission(%this)
{
  %cache_crc = "";

  if ($Pref::Server::EnableDatablockCache)
  {
    if (!isDatablockCacheSaved())
    {
      echo("<<<< saving server datablock cache >>>>");
      %this.saveDatablockCache();
    }

    if (isFile($Pref::Server::DatablockCacheFilename))
    {
      %cache_crc = getDatablockCacheCRC();
      echo("    <<<< sending CRC to client:" SPC %cache_crc SPC ">>>>");
    }
  }
   // Send over the information that will display the server info
   // when we learn it got there, we'll send the data blocks
   %this.currentPhase = 0;
   if (%this.isAIControlled())
   {
      // Cut to the chase...
      theLevelInfo.onEnterGame(%this);
   }
   else
   {
      commandToClient(%this, 'MissionStartPhase1', $missionSequence, $Server::LevelAsset.getAssetId(), %cache_crc);
         
      echo("*** Sending mission load to client: " @ $Server::LevelAsset.getAssetId());
   }
}

function serverCmdMissionStartPhase1Ack_UseCache(%client, %seq)
{
  echo("<<<< client will load datablocks from a cache >>>>");
  echo("    <<<< skipping datablock transmission >>>>");

  // Make sure to ignore calls from a previous mission load
  if (%seq != $missionSequence || !$MissionRunning)
    return;
  if (%client.currentPhase != 0)
    return;
  %client.currentPhase = 1;

  // Start with the CRC
  %client.setMissionCRC( $missionCRC );

  %client.onBeginDatablockCacheLoad($missionSequence);
}

function GameConnection::onBeginDatablockCacheLoad( %this, %missionSequence )
{
   // Make sure to ignore calls from a previous mission load
   if (%missionSequence != $missionSequence)
      return;
   if (%this.currentPhase != 1)
      return;
   %this.currentPhase = 1.5;
   commandToClient(%this, 'MissionStartPhase1_LoadCache', $missionSequence, $Server::LevelAsset.getAssetId());
}

function serverCmdMissionStartPhase1Ack(%client, %seq)
{
   // Make sure to ignore calls from a previous mission load
   if (%seq != $missionSequence || !$MissionRunning || %client.currentPhase != 0)
      return;

   %client.currentPhase = 1;

   // Start with the CRC
   %client.setMissionCRC( $missionCRC );

   // Send over the datablocks...
   // OnDataBlocksDone will get called when have confirmation
   // that they've all been received.
   %client.transmitDataBlocks($missionSequence);
}

function GameConnection::onDataBlocksDone( %this, %missionSequence )
{
   // Make sure to ignore calls from a previous mission load
   if (%missionSequence != $missionSequence || %this.currentPhase != 1)
      return;

   %this.currentPhase = 1.5;

   // On to the next phase
   commandToClient(%this, 'MissionStartPhase2', $missionSequence, $Server::LevelAsset.getAssetId());
}

//----------------------------------------------------------------------------
// Phase 2
//----------------------------------------------------------------------------
function serverCmdMissionStartPhase2Ack(%client, %seq)
{
   // Make sure to ignore calls from a previous mission load
   if (%seq != $missionSequence || !$MissionRunning || %client.currentPhase != 1.5)
      return;

   %client.currentPhase = 2;
   
   // Update mod paths, this needs to get there before the objects.
   %client.transmitPaths();

   // Start ghosting objects to the client
   %client.activateGhosting();
}

function GameConnection::clientWantsGhostAlwaysRetry(%client)
{
   if($MissionRunning)
      %client.activateGhosting();
}

function GameConnection::onGhostAlwaysFailed(%client)
{
}

function GameConnection::onGhostAlwaysObjectsReceived(%client)
{
   // Ready for next phase.
   commandToClient(%client, 'MissionStartPhase3', $missionSequence, $Server::LevelAsset.getAssetId());
}

//----------------------------------------------------------------------------
// Phase 3
//----------------------------------------------------------------------------
function serverCmdMissionStartPhase3Ack(%client, %seq)
{
   // Make sure to ignore calls from a previous mission load
   if(%seq != $missionSequence || !$MissionRunning || %client.currentPhase != 2)
      return;

   %client.currentPhase = 3;
   
   // Server is ready to drop into the game
   %entityIds = parseMissionGroupForIds("Entity", "");
   %entityCount = getWordCount(%entityIds);
   
   for(%i=0; %i < %entityCount; %i++)
   {
      %entity = getWord(%entityIds, %i);
      
      for(%e=0; %e < %entity.getCount(); %e++)
      {
         %child = %entity.getObject(%e);
         if(%child.getCLassName() $= "Entity")
            %entityIds = %entityIds SPC %child.getID();  
      }
      
      %entity.notify("onClientConnect", %client);
   }
   
   %hasGameMode = callGamemodeFunction("onClientEnterGame", %client);
   
   //if that also failed, just spawn a camera
   if(%hasGameMode == 0)
   {
      //No Game mode class for the level info, so just spawn a default camera
      // Set the control object to the default camera
      if (!isObject(%client.camera))
      {
         //if (isDefined("$Game::DefaultCameraClass"))
            %client.camera = spawnObject("Camera", Observer);
      }

      // If we have a camera then set up some properties
      if (isObject(%client.camera))
      {
         MissionCleanup.add( %client.camera );
         %client.camera.scopeToClient(%client);

         %client.setControlObject(%client.camera);

         %client.camera.setTransform("0 0 1 0 0 0 0");
      }
   }
   
   %client.startMission();
}