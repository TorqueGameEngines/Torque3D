
// The general flow of a gane - server's creation, loading and hosting clients, and then destruction is as follows:

// First, a client will always create a server in the event that they want to host a single player
// game. Torque3D treats even single player connections as a soft multiplayer game, with some stuff
// in the networking short-circuited to sidestep around lag and packet transmission times.

// initServer() is called, loading the default server scripts.
// After that, if this is a dedicated server session, initDedicated() is called, otherwise initClient is called
// to prep a playable client session.

// When a local game is started - a listen server - via calling StartGame() a server is created and then the client is
// connected to it via createAndConnectToLocalServer().

function FPSGameplay::onCreate( %this )
{
}

function FPSGameplay::onDestroy( %this )
{
}

function FPSGameplay::initServer(%this)
{
   //server scripts
   exec("./scripts/server/aiPlayer.cs");
   exec("./scripts/server/camera.cs");
   exec("./scripts/server/chat.cs");
   exec("./scripts/server/cheetah.cs");
   exec("./scripts/server/commands.cs");
   exec("./scripts/server/centerPrint.cs");
   exec("./scripts/server/deathMatchGame.cs");
   exec("./scripts/server/health.cs");
   exec("./scripts/server/inventory.cs");
   exec("./scripts/server/item.cs");
   exec("./scripts/server/player.cs");
   exec("./scripts/server/projectile.cs");
   exec("./scripts/server/proximityMine.cs");
   exec("./scripts/server/radiusDamage.cs");
   exec("./scripts/server/shapeBase.cs");
   exec("./scripts/server/spawn.cs");
   exec("./scripts/server/teleporter.cs");
   exec("./scripts/server/triggers.cs");
   exec("./scripts/server/turret.cs");
   exec("./scripts/server/vehicle.cs");
   exec("./scripts/server/vehicleWheeled.cs");
   exec("./scripts/server/VolumetricFog.cs");
   exec("./scripts/server/weapon.cs");
   exec("./scripts/server/physicsShape.cs");
}

function FPSGameplay::onCreateGameServer(%this)
{
   %this.registerDatablock("./datablocks/audioProfiles.cs");
   %this.registerDatablock("./datablocks/audioData.cs");
   %this.registerDatablock("./datablocks/sounds.cs");
   %this.registerDatablock("./datablocks/aiPlayer.cs");
   %this.registerDatablock("./datablocks/brushes.cs");
   %this.registerDatablock("./datablocks/environment.cs");
   %this.registerDatablock("./datablocks/health.cs");   
   %this.registerDatablock("./datablocks/lights.cs");
   
   %this.registerDatablock("./datablocks/managedDatablocks.cs");
   %this.registerDatablock("./datablocks/managedDecalData.cs");
   %this.registerDatablock("./datablocks/managedForestItemData.cs");
   %this.registerDatablock("./datablocks/managedItemData.cs");
   %this.registerDatablock("./datablocks/managedParticleData.cs");
   %this.registerDatablock("./datablocks/managedParticleEmiterData.cs");
   
   %this.registerDatablock("./datablocks/markers.cs");
   %this.registerDatablock("./datablocks/particles.cs");
   %this.registerDatablock("./datablocks/physics.cs");
   %this.registerDatablock("./datablocks/player.cs");
   %this.registerDatablock("./datablocks/ribbons.cs");
   %this.registerDatablock("./datablocks/rigidShape.cs");
   %this.registerDatablock("./datablocks/teleporter.cs");
   %this.registerDatablock("./datablocks/triggers.cs");
   %this.registerDatablock("./datablocks/weapon.cs");
   
   %this.registerDatablock("./datablocks/vehicles/cheetahCar.cs");
   
   %this.registerDatablock("./datablocks/weapons/grenadefx.cs");
   %this.registerDatablock("./datablocks/weapons/Lurker.cs");
   %this.registerDatablock("./datablocks/weapons/ProxMine.cs");
   %this.registerDatablock("./datablocks/weapons/Ryder.cs");
   %this.registerDatablock("./datablocks/weapons/Turret.cs");
}

function FPSGameplay::onDestroyGameServer(%this)
{
}

function FPSGameplay::initClient(%this)
{
   exec("data/FPSGameplay/scripts/client/gameProfiles.cs");
      
   exec("data/FPSGameplay/scripts/client/inputCommands.cs");
   
   //guis
   exec("./guis/chatHud.gui");
   exec("./guis/playerList.gui");
   exec("./guis/playGui.gui");
   exec("./guis/hudlessGui.gui");
   
   exec("data/FPSGameplay/scripts/client/playGui.cs");
   exec("data/FPSGameplay/scripts/client/hudlessGui.cs");
   
   exec("data/FPSGameplay/scripts/client/message.cs");
   exec("data/FPSGameplay/scripts/client/chatHud.cs");
   exec("data/FPSGameplay/scripts/client/clientCommands.cs");
   exec("data/FPSGameplay/scripts/client/messageHud.cs");
   exec("data/FPSGameplay/scripts/client/playerList.cs");
   exec("data/FPSGameplay/scripts/client/centerPrint.cs");
   exec("data/FPSGameplay/scripts/client/recordings.cs");
   
   exec("data/FPSGameplay/scripts/client/screenshot.cs");
}

function FPSGameplay::onCreateClientConnection(%this)
{
   //client scripts
   $KeybindPath = "data/FPSGameplay/scripts/client/default.keybinds.cs";
   exec($KeybindPath);
   
   %prefPath = getPrefpath();
   if(isFile(%prefPath @ "/keybinds.cs"))
      exec(%prefPath @ "/keybinds.cs");
}

function FPSGameplay::onDestroyClientConnection(%this)
{
}