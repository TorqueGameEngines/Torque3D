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
// The client portion of the client/server mission loading process
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
$pref::Client::EnableDatablockCache = true;
$pref::Client::DatablockCacheFilename = "data/cache/client/datablock_cache_c.dbc";

function clientCmdMissionStartPhase1_LoadCache(%seq, %levelAsset)
{
  if ($pref::Client::EnableDatablockCache && $loadFromDatablockCache)
  {
    if (!$pref::Video::disableVerticalSync)
    {
      warn("Disabling Vertical Sync during datablock cache load to avoid significant slowdown.");
      $AFX_tempDisableVSync = true;

      $pref::Video::disableVerticalSync = true;
      Canvas.resetVideoMode();
    }

    echo("<<<< Loading Datablocks From Cache >>>>");
    if (ServerConnection.loadDatablockCache_Begin())
    {
      schedule(10, 0, "updateLoadDatablockCacheProgress", %seq, %levelAsset);
    }
  }
}

function updateLoadDatablockCacheProgress(%seq, %levelAsset)
{
   if (ServerConnection.loadDatablockCache_Continue())
   {
      $loadDatablockCacheProgressThread = schedule(10, 0, "updateLoadDatablockCacheProgress", %seq, %levelAsset);
      return;
   }
 
   if ($AFX_tempDisableVSync)
   {
     warn("Restoring Vertical Sync setting.");
     $AFX_tempDisableVSync = false;

     $pref::Video::disableVerticalSync = false;
     Canvas.resetVideoMode();
   }

   echo("<<<< Finished Loading Datablocks From Cache >>>>");
   clientCmdMissionStartPhase2(%seq, %levelAsset);
}

function updateLoadDatablockCacheProgress(%seq, %levelAsset)
{
   if (ServerConnection.loadDatablockCache_Continue())
   {
      $loadDatablockCacheProgressThread = schedule(10, 0, "updateLoadDatablockCacheProgress", %seq, %levelAsset);
      return;
   }
 
   if ($AFX_tempDisableVSync)
   {
     warn("Restoring Vertical Sync setting.");
     $AFX_tempDisableVSync = false;

     $pref::Video::disableVerticalSync = false;
     Canvas.resetVideoMode();
   }

   echo("<<<< Finished Loading Datablocks From Cache >>>>");
   clientCmdMissionStartPhase2(%seq, %levelAsset);
}

function clientCmdMissionStartPhase1(%seq, %levelAsset, %cache_crc)
{
   %levelAssetDef = AssetDatabase.acquireAsset(%levelAsset);
   
   // These need to come after the cls.
   echo ("*** New Mission: " @ %levelAssetDef.levelName);
   echo ("*** Phase 1: Download Datablocks & Targets");
   
   $Client::LevelAsset = %levelAssetDef;
   $Client::MissionFile = %levelAssetDef.getLevelPath();
   $pref::ReflectionProbes::CurrentLevelPath = filePath($Client::MissionFile) @ "/" @ fileBase($Client::MissionFile) @ "/probes/";
   
   //Prep the postFX stuff
   // Load the post effect presets for this mission.
   %path = %levelAssetDef.getPostFXPresetPath();

   if ( isScriptFile( %path ) )
   {
      postFXManager::loadPresetHandler( %path ); 
      $PostFXManager::currentPreset = %path;
   }
   else
   {
      PostFXManager::settingsApplyDefaultPreset();
   }
   
  $loadFromDatablockCache = false;
  if ($pref::Client::EnableDatablockCache)
  {
    %cache_filename = $pref::Client::DatablockCacheFilename;

    // if cache CRC is provided, check for validity
    if (%cache_crc !$= "")
    {
      // check for existence of cache file
      if (isFile(%cache_filename))
      { 
        // here we are not comparing the CRC of the cache itself, but the CRC of
        // the server cache (stored in the header) when these datablocks were
        // transmitted.
        %my_cache_crc = extractDatablockCacheCRC(%cache_filename);
        echo("<<<< client cache CRC:" SPC %my_cache_crc SPC ">>>>");
        echo("<<<< comparing CRC codes:" SPC "s:" @ %cache_crc SPC "c:" @ %my_cache_crc SPC ">>>>");
        if (%my_cache_crc == %cache_crc)
        {
          echo("<<<< cache CRC codes match, datablocks will be loaded from local cache. >>>>");
          $loadFromDatablockCache = true;
        }
        else
        {
          echo("<<<< cache CRC codes differ, datablocks will be transmitted and cached. >>>>" SPC %cache_crc);
          setDatablockCacheCRC(%cache_crc);
        }
      }
      else
      {
        echo("<<<< client datablock cache does not exist, datablocks will be transmitted and cached. >>>>");
        setDatablockCacheCRC(%cache_crc);
      }
    }
    else
    {
      echo("<<<< server datablock caching is disabled, datablocks will be transmitted. >>>>");
    }
    if ($loadFromDatablockCache)
    {
      // skip datablock transmission and initiate a cache load
      commandToServer('MissionStartPhase1Ack_UseCache', %seq);
      return;
    }
  }
  else if (%cache_crc !$= "")
  {
    echo("<<<< client datablock caching is disabled, datablocks will be transmitted. >>>>");
  }
  
   onMissionDownloadPhase("LOADING DATABLOCKS");
   
   commandToServer('MissionStartPhase1Ack', %seq);
}

function onDataBlockObjectReceived(%index, %total)
{
   onMissionDownloadProgress(%index / %total);
}

//----------------------------------------------------------------------------
// Phase 2
//----------------------------------------------------------------------------
function clientCmdMissionStartPhase2(%seq, %levelAsset)
{
   onPhaseComplete();
   echo ("*** Phase 2: Download Ghost Objects");
   
   onMissionDownloadPhase("LOADING OBJECTS");
   
   commandToServer('MissionStartPhase2Ack', %seq);
}

function onGhostAlwaysStarted(%ghostCount)
{
   $ghostCount = %ghostCount;
   $ghostsRecvd = 0;
}

function onGhostAlwaysObjectReceived()
{
   $ghostsRecvd++;
   onMissionDownloadProgress($ghostsRecvd / $ghostCount);
}  

//----------------------------------------------------------------------------
// Phase 3
//----------------------------------------------------------------------------
function clientCmdMissionStartPhase3(%seq, %levelAsset)
{
   onPhaseComplete();
   StartClientReplication();
   
   %levelAssetDef = AssetDatabase.acquireAsset(%levelAsset);
   
   // Load the static mission decals.
   if(isFile(%levelAssetDef.getDecalsPath()))
      decalManagerLoad( %levelAssetDef.getDecalsPath() );
   
   echo ("*** Phase 3: Mission Lighting");
   $MSeq = %seq;
   $Client::LevelAsset = %levelAssetDef;
   $Client::MissionFile = %levelAssetDef.getLevelPath();

   // Need to light the mission before we are ready.
   // The sceneLightingComplete function will complete the handshake 
   // once the scene lighting is done.
   if (lightScene("sceneLightingComplete", ""))
   {
      echo("Lighting mission....");
      schedule(1, 0, "updateLightingProgress");
      
      onMissionDownloadPhase("LIGHTING MISSION");
      
      $lightingMission = true;
   }
}

function updateLightingProgress()
{
   onMissionDownloadProgress($SceneLighting::lightingProgress);
   if ($lightingMission)
      $lightingProgressThread = schedule(1, 0, "updateLightingProgress");
}

function sceneLightingComplete()
{
   echo("Mission lighting done");
   $lightingMission = false;
   
   //Bake probes
   %boxProbeIds = parseMissionGroupForIds("BoxEnvironmentProbe", "");
   %sphereProbeIds = parseMissionGroupForIds("SphereEnvironmentProbe", "");
   %skylightIds = parseMissionGroupForIds("Skylight", "");
   
   %probeIds = rtrim(ltrim(%boxProbeIds SPC %sphereProbeIds));
   %probeIds = rtrim(ltrim(%probeIds SPC %skylightIds));
   %probeCount = getWordCount(%probeIds);
   
   $pref::ReflectionProbes::CurrentLevelPath = filePath($Client::MissionFile) @ "/" @ fileBase($Client::MissionFile) @ "/probes/";
   //ProbeBin.processProbes();
   
   onPhaseComplete("STARTING MISSION");
   
   // The is also the end of the mission load cycle.
   commandToServer('MissionStartPhase3Ack', $MSeq);
}

//----------------------------------------------------------------------------
// Helper functions
//----------------------------------------------------------------------------
function connect(%server)
{
   %conn = new GameConnection(ServerConnection);
   RootGroup.add(ServerConnection);
   %conn.setConnectArgs($pref::Player::Name, $ConncetInfoKey);
   %conn.setJoinPassword($Client::Password);
   %conn.connect(%server);
}

function onMissionDownloadPhase(%phase)
{
   if ( !isObject( LoadingProgress ) )
      return;
      
   LoadingProgress.setValue(0);
   LoadingProgressTxt.setValue(%phase);
   Canvas.repaint();
}

function onMissionDownloadProgress(%progress)
{
   if ( !isObject( LoadingProgress ) )
      return;
      
   LoadingProgress.setValue(%progress);
   Canvas.repaint(33);
}

function onPhaseComplete(%text)
{
   if ( !isObject( LoadingProgress ) )
      return;
	  
   if(%text !$= "")
      LoadingProgressTxt.setValue(%text);
      
   LoadingProgress.setValue( 1 );
   Canvas.repaint();
}