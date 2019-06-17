// aiPlayerDatablocks.cs
// breaks out the datablocks for aiguard.cs to make them easier to edit.
// also manages the trigger controller

//////////////////////////////////////
//
// TRIGGER CONTROLLER
// This code handles the placing and behavior of aiSoldierTriggers
/////////////////////////////////////////

datablock TriggerData(guardTrigger)
{
   tickPeriodMS = 100;
};

////////////////////////////////////////
//This is the default datablock for the Guard.
//I changed the stock datablock name from those used in AIPLAYER.CS
//I did this to allow me to create different classes of bots with their own
//thinking and reaction routines for each class.
///////////////////////////////////
//
//You can specifiy as many datablocks as you have characters.
//The first variable after PlayerData must be a unique name. The second variable (after the semicolon) 
//must be a valid body type.

datablock PlayerData(DemoPlayer : DefaultPlayerData)
{
   maxDamage = 100;

   maxForwardSpeed = 14;
   maxBackwardSpeed = 13;
   maxSideSpeed = 13;

   //The art used by this datablock
   shapeFile = "data/Soldier/Shapes/soldier_Rigged.DAE";//"art/shapes/actors/Soldier/soldier_rigged.DAE";

   //Set the bot's inventory so it can use different weapons
   maxInv[Rifle] = 1;
   maxInv[BulletAmmo] = 1000;
   maxInv[RocketLauncher] = 1;   
   maxInv[RocketLauncherAmmo] = 1000;
   maxInv[GrenadeLauncher] = 1;
   maxInv[GrenadeLauncherAmmo] = 1000;

   maxInvRifle = "1";
   maxInvBulletAmmo = "1000";   
   maxInvGrenadeLauncher = "1";
   maxInvGrenadeLauncherAmmo = "1000";
   maxInvRocketLauncher = "1";   
   maxInvRocketLauncherAmmo = "1000";
};

