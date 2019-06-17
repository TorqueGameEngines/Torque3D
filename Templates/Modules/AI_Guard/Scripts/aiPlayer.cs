//The aiPlayer.cs file creates a guard-style bot that can also be pathed.
//The guard uses a simple state machine to control it's actions.

//The bots actions are as follows:
//Dead:					The bot stops all activity and is dead.
//Guarding: 		When guarding the bot scans for new targets, and when one is found it switches to 'Attacking'
//Attacking: 		The guard tries to close with the target while firing and checking for target updates.
//Holding:			When the bot loses a target it will go into a holding pattern. While holding the bot's FOV
//							is enhanced. The bot holds for a set number of cycles before changing it's action state to
//							'Returning'
//Returning:		The bot tries to return to it's original position. While returning the guard looks for new targets
//							and checks it motion relattive to it's last movement to determine if it is stuck.
//							If it is stuck the bot tries to move is a random direction to try and clear the obstacle.
//							(Not always a foolproof solution, but in a simple environment it works well enough.)
//Defending:		When a bot takes damage it's status is set to defending. The bot sidesteps and then
//							goes into a holding pattern. This does two things. It enhances the bots FOV and it scans for
//							targets. Plus it will have the bot return to it's original position if there is no
//							perceivable threat in range.
//NoTarget			This is set when the bot loses sight or perception of it's targets. This is used to help
//							clear the bots aim and other housekeeping functions

//The following are global variables used to set the guards basic settings.
$AI_GUARD_ENABLED = true;						//Whether Guard bots are loaded during mission loading.
$AI_GUARD_MARKER_HIDE = true;				//Turns marker hiding on or off - useful when editing maps.
$AI_GUARD_WEAPON = "Lurker";				//Which weapon do you want the guard to use
$AI_GUARD_ENDLESS_AMMO = true;			//When set to true the guard will replenish its ammo perpetually
$AI_GUARD_WEAPON_USES_AMMO = true;  //Set this to false for energy weapons that do not use ammo
$AI_GUARD_SIDESTEP = 20;						//This value helps determine how far a bot sidesteps when he is stuck.
																		//The computer picks a random number between 1 and $AI_GUARD_SIDESTEP
																		//The value is then subtracted by half it's value to create a left/right
																		//and forward/back component. So the effective range is really -10 to +10
																		//with the default setting of 20
$AI_GUARD_DETECT_ITEM_RANGE = 50;   //Sets how far around itself a bot will look for items to pick up
$AI_GUARD_HOLDCNT_MAX = 10;					//The number of think cycles that the bot will 'hold' for before trying to
																		//return to his post.
$AI_GUARD_FIREDELAY = 1000;					//How long the bot waits between firing bursts.
$AI_GUARD_ENHANCED_FOV_TIME = 2000;	//How long the bots field of vision is enhanced to 360 for.
$AI_GUARD_FOV = 200;				        //The guards field of vision
$AI_GUARD_ENHANCED_DEFENDING_TIME = 5000;           //How long the bot gets a 360 FOV and a longer detect distance for after being sniped.
$AI_GUARD_ENHANCED_DEFENDING_DISTANCE = 100;        //Detect distance after being sniped.
$AI_GUARD_DETECT_DISTANCE = 50;			//The range at which a guardbot will start reacting to a client target
$AI_GUARD_IGNORE_DISTANCE = 40;		//The range at which the bot ignores a client and will not fire on it.
$AI_GUARD_MAX_DISTANCE = 5;		//The bot will stop and try to stay at this distance or less from the player.
$AI_GUARD_RANGED_MAX_DISTANCE = 15;		//Bots flagged as ranged will stop and try to stay at this distance or less from the player.
$AI_GUARD_MAX_PACE = 12;            //The maximum range the mobs pace away from their guard point. (works like AI_GUARD_SIDESTEP)
$AI_GUARD_MIN_PACE = 1.5;            //The minimum range the mobs pace away from their guard point.
$AI_GUARD_PACE_SPEED = 0.5;         //Set the speed of the mob while pacing (1.0 is 100%, 0.5 is 50%)
$AI_GUARD_PACE_TIME = 4;         //Sets how many think cycles the bot has to travel to it's location (or stand at 
                                        //it's location if it's already there) before getting another one to move to, random between 1 and this number.
$AI_GUARD_LOS_TIME = 100;           //The amount of time after the bot loses sight of player that it will get their position.
                                            //This helps the bot turn sharp corners. Set it to 1 or 0 if you don't want the bot to cheat.
$AI_GUARD_LOS_BYPASS = 3;           //The distance at which positions will not have line of sight tests done on them.
                                            //This is needed because the bot can not see the area around its feet.
$AI_GUARD_CORNERING =  0.8;			//How close the bot will attempt to take corners. If the bot is having problems with corners,
                                            //adjust this value, $AI_GUARD_LOS_TIME and $AI_GUARD_LOS_BYPASS as needed (will vary based on run speed).
$AI_GUARD_SCANTIME       = 500;			//The quickest time between think cycles.
$AI_GUARD_MAX_ATTENTION = 10; 		  //This number and $AI_GUARD_SCANTIME are multiplied to set the delay in the
																		//thinking loop. Used to free up processor time on bots out of the mix.
$AI_GUARD_CREATION_DELAY = 3000;			//How long a bot waits after creation before his think cycles are controlled by
																		//his attention rate. (Used to help free up think cycles on bots while misison
																		//finishes loading.
$AI_GUARD_TRIGGER_DOWN =  100;			//How long the bot holds down the trigger when firing. Use longer pulses for
																		//pray and spray type weapons.
$AI_GUARD_DEFAULTRESPAWN = true;		//Controls whether guards respawn automatically or not if their marker does not have
																		//dynamic 'respawn' variable set in it.
$AI_GUARD_RESPAWN_DELAY = 18000;		//Determines how long a bot goes in between death and respawning.
$AI_GUARD_ENHANCEFOV_CHANCE = 25; 	//There is a 1 in x chance that guard will see 360 deg vision to prevent it
																		//from being snuck up on.
$AI_GUARD_SEEK_HEALTH_LVL = 65;			//This sets at what damage level a bot will attempt to look for a health pack nearby.
$AI_GUARD_CHAR_TYPE = DemoPlayer;          //This is the default datablock that is spawned as the bot unless another is specified on the node

//The onReachDestination function is responsible for setting the bots 'action'
//state to the appropriate setting depending on what action the bot was following
//to reach the destination.
function DemoPlayer::onReachDestination(%this, %obj)
{
  	//Picks an appropriate set of actions based on the bots 'action' variable
  	switch$(%obj.action)
  	{
  		//If the bot is attacking when it reaches it's target it will go into a hold.
  		case "Attacking":
  			%obj.action="Holding";
  		//If the bot is returning it has two possible scenarios for reaching a destination
  		//The first case is the the bot sidestepped and has reached it's sidestep location.
  		//If that is the case, then the bot goes into a quick hold. (Which sets the bot to
  		//only hold for 1 cycle before returning to his post.)
  		//The other alternative is that the bot has returned as is back at it's original position.
  		//If this is the case, then the bot's transform is set to match that of it's marker's
  		//transformation.
  		//This will cause a snapping into position - but it ensures that your guard always faces the
  		//direction you want it to when it returns to it's post.
  		//(It also helps to make sure that your markers are set as close to the ground as possible.
  		//Otherwise your bots will hop up and drop from the sky when they return to post.)
  		case "Returning":
  		  //If the bot is pathed have it move to the next node on its path
  		  if (%obj.path !$= "")
  		  {
  			   //Check if the bot's guarding
  			   if (%obj.doesGuard $= "guard")
  			   {
  			        if (%obj.returningPos == %obj.marker.getposition())
  			        {
  			            %obj.moveToNextNode(%this.returningPath);
  			        }
  			        else
  			        {
  			            %obj.path = "";
  			            %obj.doesGuard = "";
  			        }
  			   }
  			   else
  			      %obj.moveToNextNode(%this.returningPath);
  		  }
  		  else
  		  {
  			if (%obj.doesGuard $= "guard")
  			   %basedist = vectorDist(%obj.getposition(), %obj.marker.getposition());
  			else
  			   %basedist = vectorDist(%obj.getposition(), %obj.returningPos);
  			//if the bot is close to his original position then set it's action to
  			//Guarding and set it to it's original facing and position.
  			if(%basedist < 1.0)
  				{
  					%obj.action = "Guarding";
  					//Set the bots returning position to its marker if it's guarding
  					if (%obj.doesGuard $= "guard")
  					   %obj.settransform(%obj.marker.gettransform());
  					else
  					   %obj.settransform(%obj.returningTrans);
  					%obj.clearaim();
  				}
  				//if the bot is away from his post, then he must have gotten here
  				//as a result of sidestepping so set him to do a quick hold to scan
  				//for targets then return to post.
  				else
  				{
  					//Sets holdcnt to 1 less than the max. Ensures that the bot only holds for 1 cycle.
  					//before trying to return.
  					%obj.holdcnt=$AI_GUARD_HOLDCNT_MAX-1;
  					%obj.action="Holding";
  				}
  		  }
  		//The bot was defending and sidestepped. So set him to 'hold' to check for targets
  		//and to prepare to return to post if no targets are found.
  		case "Defending":
  			%obj.action = "Holding";

			case "RetrievingItem":
				%obj.holdcnt=$AI_GUARD_HOLDCNT_MAX-1;
  			%obj.action="Holding";
  	}
}

//The OnDamage function sets the bots action to 'Dead' and starts the respawn process
//if called for.
function DemoPlayer::OnDamage(%this, %obj, %delta)
{
   	if (%obj.action !$="GetHealth")
   	{
   	   	if (%obj.action !$= "Attacking" && %obj.action !$= "Defending" && %obj.getstate() !$="Dead")
   	   	{
   			%obj.enhancedefending(%obj);
   	   	}
   	   	%obj.action = "Defending";
   	}

   	if(%obj.getstate() $="Dead")
   		%obj.action="Dead";

   	if(%obj.getState() $= "Dead" && %obj.respawn == true)
   		{
   			//%obj.delaybeforerespawn(%obj.botname, %obj.marker);
   			%this.player = 0;
   		}
}

//The delay before respawn function is set to wait a specified duration before
//respawning an AIPlayer
function AIPlayer::DelayBeforeRespawn(%this, %name, %marker)
{
		%this.respawntrigger = %this.schedule($AI_GUARD_RESPAWN_DELAY,"spawn", %name, %marker);
}

//The LoadEntities function replaces the markers placed in the map with the AI bots during the
//mission loading.
function AIPlayer::LoadEntities()
{
   //Check to see if the AIPlayers are to be loaded.
   if ($AI_GUARD_ENABLED == true)
   {
      echo("Loading Guard entities...");
      //This performs a search for all items within the radius from the starting point.
      //All of the items that match "AIPlayerMarker" trigger a bot to be placed at the 
      //position of the marker found.
      %position = "0 0 0";
      %radius = 100000.0;
      InitContainerRadiusSearch(%position, %radius, $TypeMasks::StaticObjectType);
      %i=0;
      while ((%targetObject = containerSearchNext()) != 0)
      {
         if(%targetobject.getclassname() $= "StaticShape")
         {
            if (%targetobject.getDataBlock().getName() $= "AIPlayerMarker")
            {
               %i++;

               // Let's check to see if the marker specifies a datablock.
               // if so, we spawn that datablock model instead of the default
               if (%targetObject.block $= "")
               {
                  %block = $AI_GUARD_CHAR_TYPE;
               }
               else
               {
                  %block = %targetObject.block;
               }
               %player = AIPlayer::spawnAtMarker("Guard" @ %i, %targetobject, %block);
            }
         }
      }
   }
   else
   {
      echo("Guard entities disabled...");
   }

   //This determines whether to hide or not hide the markers during mission loading.
   //It's helpful to have the markers visible when editing the map and fine tuning the bot
   //placement.
   //This search is identical to the one above, only it hides the markers if found.
   if ($AI_GUARD_MARKER_HIDE == true)
   {
      echo("Hiding Guard markers...");
      %position = "0 0 0";
      %radius = 100000.0;
      InitContainerRadiusSearch(%position, %radius, $TypeMasks::StaticObjectType);
      while ((%targetObject = containerSearchNext()) != 0)
      {
         if(%targetobject.getclassname() $= "StaticShape")
         {
            if (%targetobject.getDataBlock().getName() $= "AIPlayerMarker")
               %targetobject.setAllMeshesHidden(true);	
         }
      }
   }
}

function AIPlayer::spawnByGroup(%spawnGroup)
{
 echo ("spawning group " @ %spawnGroup);

 //echo("Loading soldiers!");

 //This performs a search for all items within the radius from the starting point.
 //All of the items that match "AIPlayerMarker" trigger a bot to be placed at the 
 //position of the marker found.

  %position = "0 0 0";
  %radius = 100000.0;
  InitContainerRadiusSearch(%position, %radius, $TypeMasks::StaticObjectType);
  %i=0;
  while ((%targetObject = containerSearchNext()) != 0)
  	{
  		if(%targetobject.getclassname() $= "StaticShape")
      {
         if (%targetobject.getDataBlock().getName() $= "AIPlayerMarker")
         {
            %i++;
            echo("target's spawn is " @ %targetObject.spawnGroup);
            if (%targetObject.spawnGroup $= %spawnGroup)
            {
               // we're in the correct spawn group!

               // Let's check to see if the marker specifies a datablock.
               // if so, we spawn that datablock model instead of the default
               if (%targetObject.block $= "")
               {
                  %block = $AI_GUARD_CHAR_TYPE;
               }
               else
               {
                  %block = %targetObject.block;
               }

               // let's spawn some bad guys!
               %player = AIPlayer::spawnAtMarker("Guard" @ %i, %targetobject, %block);
            }
         }
      }
  	}
   //This determines whether to hide or not hide the markers during mission loading.
   //It's helpful to have the markers visible when editing the map and fine tuning the bot
   //placement.
   //This search is identical to the one above, only it hides the markers if found.
   if ($AI_GUARD_MARKER_HIDE == true)
   {
   echo("Hiding Guard markers...");
   %position = "0 0 0";
     %radius = 100000.0;
   InitContainerRadiusSearch(%position, %radius, $TypeMasks::StaticObjectType);
     while ((%targetObject = containerSearchNext()) != 0)
      {
            if(%targetobject.getclassname() $= "StaticShape")
         {
         if (%targetobject.getDataBlock().getName() $= "AIPlayerMarker")
         {
            if (%targetObject.spawnGroup $= %spawnGroup)
            %targetobject.setAllMeshesHidden(true);	
         }
         }
     }
   }
}

//This function sets the bots aim to the current target, and 'pulls' the trigger
//of the weapon of the bot to begin the firing sequence.
function AIPlayer::openfire(%this, %obj, %tgt)
{
	//If the bot is dead or the target is dead then let's bail out of here.
	if (%obj.getState() $= "Dead" || %tgt.player.getstate() $="Dead")
	{
	 	%obj.firing = false;
	 	%obj.NoTarget();
	}
	else
	{
	//We've got two live ones. So let's kill something.
	//The firing variable is set while firing and is cleared at the end of the delay cycle.
	//This is done to allow the use of a firing delay - and prevent a bot from firing again
	//prematurely.
	if(!%obj.firing)
	{
   	//Gets the range to target - rtt
   	%rtt=vectorDist(%obj.getposition(), %tgt.player.getposition());

   	//If the target is within our ignore distance then we will attack.
   	if(%rtt < $AI_GUARD_IGNORE_DISTANCE)
   	{
	 	if(%obj.fireLater <= 0 && %obj.getAimLocation() != %tgt.player.getposition())    //Fix for premature firing
	 	{
	 	    %obj.fireLater++;
	 	    return;
	 	}
   			//Sets the firing variable to true
   			%obj.firing = true;

   			if($AI_GUARD_WEAPON_USES_AMMO)
   				{
   				if($AI_GUARD_ENDLESS_AMMO == true)
   					{
   						%obj.incinventory(%obj.botWeapon @"Ammo",100);
   					}
   				}

 			  //'Pulls' the trigger on the bot gun.
 			  %obj.setImageTrigger(0,true);
   		  //This sets a delay of $AI_GUARD_TRIGGER_DOWN length to hold the trigger down for.
   		  %this.trigger = %this.schedule($AI_GUARD_TRIGGER_DOWN,"ceasefire", %obj);
   	}
   	else
   	{
	 	//There was a target when openfire was called, but now they're out of range so
	 	//we have no target. Call NoTarget to clear the bots aim.
	 	%obj.NoTarget(%obj);
   	}
    }
  }
}

//This simply clears the bots aim to have it look forward relative to it's movement.
function AIPlayer::NoTarget(%this, %obj)
{
	%obj.clearaim();
}

//Ceasefire is called by the openfire function after the set delay to
//hold the trigger down is met.
function AIPlayer::ceasefire(%this, %obj)
{
   //Turns off the trigger, or lets off of it.  
   %obj.setImageTrigger(0,false);
   //This sets the delay between when we let off the trigger and how soon it will
   //be before we allow the bot to fire again.
   %this.ceasefiretrigger = %this.schedule($AI_GUARD_FIREDELAY,"delayfire", %obj);
}

//delayfire is called to clear the firing variable. Clearing this allows
//the bot to fire again in the openfire function.
function AIPlayer::delayfire(%this, %obj)
{
	//this is the end of the firing cycle
	%obj.firing = false;
}


//-----------------------------------------------------------------------------
// AIPlayer static functions
//-----------------------------------------------------------------------------

//This is the spawn function for the bot.
function AIPlayer::spawn(%this, %name, %obj, %block)
{
   if (%obj.block $= "")
   {
      %block = $AI_GUARD_CHAR_TYPE;
   }
   else
   {
      %block = %obj.block;
   }

   // Create the demo player object
   %player = new AIPlayer() {
   dataBlock = %block;

   //The marker is the AIPlayer marker object that the guard is associated with.
   //The marker object is kept with the player data because it's location, and
   //dynamic variable values are used in several functions. This also allows the addition
   //of future dynamic variables without having to change the spawn/respawn functions to
   //access them.
   marker = %obj;
   botname = %name;
   //Sets the bot's field of vision
   fov = $AI_GUARD_FOV;
   //Sets the bot's detect distance
   detdis = $AI_GUARD_DETECT_DISTANCE;
   //Sets the bot's returning position and transform
   returningPos = %obj.getposition();
   returningTrans = %obj.gettransform();
   //Sets the bot not to return to a path as soon as it is loaded
   //The pathed bots will go to there paths at another point
   returningPath = 0;
   //Fix for premature firing
   fireLater = 0;
   //Sets the bot's pacing
   pace = $AI_GUARD_PACE_TIME;
   //The pathname variable is a dynamic variable set during map editing.
   //This allows the designer to attach each bot to a seperate path
   path = %obj.pathname;
   //Is the bot using a ranged weapon
   weapRange = %obj.range;
   //Does the bot return to its spawn point
   doesGuard = %obj.doesReturn;
   //Sets whether the bot is AI or not
   isbot=true;
   //Thinking variables
   //Firing tells whether or not we're in the midst of a firing sequence.
   firing = false;
   //The 'action' variable holds the state of the bot - which controls how it
   //thinks.
   holdcnt = $AI_GUARD_HOLDCNT_MAX-1;
   action = "Holding";
   //The bots starting attention level is set to half of it's range.
   attentionlevel = $AI_GUARD_MAX_ATTENTION/2;

   //Oldpos holds the position of the bot at the end of it's last 'think' cycle
   //This is used to help determine if a bot is stuck or not.
   oldpos = %obj.getposition();
   //Added for bots use different weapons
   botWeapon = $AI_GUARD_WEAPON;
   };

   MissionCleanup.add(%player);

   // if the field is not blank, set the weapon variable to the weapon
   // otherwise, use default.
   if (%obj.Weapon !$= "")
   {
      %player.botWeapon = %obj.Weapon;
   }

   //Sets the name displayed in the hud above the bot. Commented out be default.
   //%player.setShapeName(%name);
   //is called to set the bots beginning inventory.
   %player.EquipBot(%player);
   //Sets the bot's initial position to that of it's marker.
   %player.setTransform(%obj.gettransform());

  	//The following cluster of if-thens sets whether the bot will respawn or not
  	//based on it's markers dynamic variable - or the default respawn variable setting.
   if (%obj.respawn $= "" )
   	{
   		%player.respawn=$AI_GUARD_DEFAULTRESPAWN;
   	}
   	else
   	{
   		if (%obj.respawn == true)
   			%player.respawn=true;
   		else
   			%player.respawn=false;
   	}

   if (%obj.pathname !$= "")
   {
   		%player.schedule($AI_GUARD_CREATION_DELAY,"followPath", %obj.pathname, -1);
   }

   //Sets the bot to begin thinking after waiting the length of $AI_GUARD_CREATION_DELAY
   %player.schedule($AI_GUARD_CREATION_DELAY,"Think", %player);

   return %player;
}

//This sets the bots beginning equipment and inventory
function AIPlayer::EquipBot(%this, %obj)
{
   echo("equipingBot");
   //This adds a weapon to the bots inventory.
   %obj.incinventory(%obj.botWeapon,1);
   //This mounts the weapon on the bot.
   %obj.mountImage(%obj.botWeapon @ "Image",0);
   echo(%obj.botWeapon);
   %obj.use(%obj.botWeapon);
   if($AI_GUARD_WEAPON_USES_AMMO == true)
   	{
   	//This sets the bots beginning inventory of ammo.
 	 	%obj.setInventory(%obj.botWeapon @ "Ammo",100);
 		}
}

//The EnhanceFOV function temporarily gives the bot a 360 degree field of vision
//This is used to emulate the bot looking around at different times. Namely when
//'Holding'.
function AIPlayer::EnhanceFOV(%this, %obj)
{
	//Is the botFOV already 360 degrees? If not then we'll set it, and set the schedule to
	//turn it back off.
	if (%obj.fov != 360)
	{
		//Sets the field of vision to 360 deg.
		%obj.fov = 360;
		//Starts the timer to disable the enhanced FOV
		%this.fovtrigger = %this.schedule($AI_GUARD_ENHANCED_FOV_TIME, "restorefov", %obj);
}
}

//Restore FOV sets the bot's FOV back to it's regular default setting.
function AIPlayer::restoreFOV(%this, %obj)
{
	%obj.fov = $AI_GUARD_FOV;
}

//Enhances the defending mob's FOV and detect distance after being hit.
function AIPlayer::EnhanceDefending(%this, %obj)
{
	if (%obj.detdis == $AI_GUARD_DETECT_DISTANCE)
	{
		%obj.detdis = $AI_GUARD_ENHANCED_DEFENDING_DISTANCE;
		%this.distancetrigger = %this.schedule($AI_GUARD_ENHANCED_DEFENDING_TIME, "restoreDefending", %obj);
	}

	%obj.fov = 360;
	%this.fovtrigger = %this.schedule($AI_GUARD_ENHANCED_DEFENDING_TIME, "restorefov", %obj);
}

//Restores the defending mob's detect distance.
function AIPlayer::restoreDefending(%this, %obj)
{
	%obj.detdis = $AI_GUARD_DETECT_DISTANCE;
}

//Spawn at marker is called by LoadEntities, and calls the spawn function to
//create the bots and place them at their starting positions.
function AIPlayer::spawnAtMarker(%name, %obj, %block)
{
   if (!isObject(%obj))
      return;
   %player = AIPlayer::spawn(%this, %name, %obj, %block);
   return %player;
}

//AITargeting

//Return the angle of a vector in relation to world origin
function AIPlayer::getAngleofVector(%this, %vec)
{
	%vector = VectorNormalize(%vec);
	%vecx = getWord(%vector,0);
	%vecy = getWord(%vector,1);
	if(%vecx >= 0 && %vecy >= 0)
		%quad = 1;
	else
		if(%vecx >= 0 && %vecy < 0)
	  	%quad = 2;
	  else
	  	if(%vecx < 0 && %vecy < 0)
	    	%quad = 3;
	    else 
	    	%quad = 4;
	%angle = mATan(%vecy/%vecx, -1);
	%degangle = mRadToDeg(%angle);
	switch(%quad)
	{
		case 1:
	  	%angle = %degangle-90;
	  case 2:
	  	%angle = %degangle+270;
	  case 3:
	  	%angle = %degangle+90;
	  case 4:
	  	%angle = %degangle+450;
	}
  if (%angle < 0)  %angle = %angle + 360;
  return %angle;
}
                                                        
//This is another function taken from code off of garagegames.
//The only mods I made to it was to add the extra check to ensure that the
//angle is within the 0-360 range.
function AIPlayer::check2DAngletoItem(%this, %obj, %item)
{
	%eyeVec = VectorNormalize(%this.getEyeVector());
	%eyeangle = %this.getAngleofVector(%eyeVec);
	%posVec = VectorSub(%item.getPosition(), %obj.getPosition());
	%posangle = %this.getAngleofVector(%posVec);
	%angle = %posangle - %eyeAngle;
	%angle = %angle ? %angle : %angle * -1;
  if (%angle < 0)  %angle = %angle + 360;
	return %angle;
}

//This is another function taken from code off of garagegames.
//The only mods I made to it was to add the extra check to ensure that the
//angle is within the 0-360 range.
function AIPlayer::check2DAngletoTarget(%this, %obj, %tgt)
{
	%eyeVec = VectorNormalize(%this.getEyeVector());
	%eyeangle = %this.getAngleofVector(%eyeVec);
	%posVec = VectorSub(%tgt.player.getPosition(), %obj.getPosition());
	%posangle = %this.getAngleofVector(%posVec);
	%angle = %posangle - %eyeAngle;
	%angle = %angle ? %angle : %angle * -1;
  if (%angle < 0)  %angle = %angle + 360;
	return %angle;
}

//The 'Think' function is the brains of the bot.
//The bot performs certain actions based on what it's current 'action' state is.
//The bot thinks on a scheduled basis. How fast the bot 'thinks' is determined by
//the bots attention level and its default scan time. (There are a few cases in the think
//function below where the schedule is shortened - but only to make the 'thinking' more
//realistic and to cut down on duplicating chunks of code.

function AIPlayer::Think(%this, %obj)
{
	//This cancels the current schedule - just to make sure that things are kept neat and tidy.
	cancel(%this.ailoop);
	
	//If the bot is dead, then there's no need to think or do anything. So let's bail out.
	if (!%obj || %obj.getstate() $="Dead")
		return;

	%prevaction=%obj.action;
		
	if (%obj.action !$="RetrievingItem" && %obj.action !$="Dead")
	{
		if (%obj.getdamagelevel() > $AI_GUARD_SEEK_HEALTH_LVL) 
		{
			%this.enhancefov(%obj);
			%hlth= %this.getclosestiteminsightandrange(%obj, "HealthPatch");

			if(%hlth > 0)
			{
				%obj.action="GetHealth";
			}		

			if($AI_GUARD_WEAPON_USES_AMMO == true)
			{
				if(%obj.getInventory(%obj.botWeapon @ "Ammo") == 0)
				{
					%this.enhancefov(%obj);
					%ammostr = %obj.botWeapon @ "Ammo";
					%i_ammo= %this.getclosestiteminsightandrange(%obj, %ammostr );
					if(%i_ammo > 0)
					{
						%obj.action="GetAmmo";		
					}
				}
			}
		} 		

		//The switch$ takes the value of the bots action variable and then chooses what code to run
		//according to what value it is.
		switch$(%obj.action)
		{
			//The bot is 'dead' so lets clear his aim, and turn off his firing variable.
			case "Dead":
				%obj.clearaim();
				%obj.firing = false;

			//This is the bots default position. While guarding the bot will only do 2 things.
			//The first is that the bot will run a random check to see if it can enhance it's fov.
			//This is thrown in to prevent bots from having a perpetual blind spot, but still limits
			//their field of vision for the majority of the time.
			//The other thing the bot does is to check for nearby targets. If found the bot goes into attack mode.
			case "Guarding":
				//The bot will enhance it's FOV if it picks a 1 from a range of 1 to $AI_GUARD_ENHANCEFOV_CHANCE
				%chance = getRandom(($AI_GUARD_ENHANCEFOV_CHANCE-1)) +1;
				if (%chance == 1 ) 
					%this.enhancefov(%obj);

				%obj.fireLater = 0;
				%obj.lostest = 0;

				//The bot checks for the nearest valid target if any.
				%tgtid = %this.GetClosestHumanInSightandRange(%obj);
				//If %tgtid >= 0 then a target is in sight and range.
				if(%tgtid >= 0)
				{
					//Set the bots action to 'Attacking' and set it to attack quickly.
					%obj.action = "Attacking";
					//This is one instance where the bots thinking is sped up to enable the bot
					//to react more quickly as seems appropriate.
					%this.ailoop=%this.schedule(100,"Think" , %obj);
				}
				else
				{
					//Check if the bot's pathed and if not, pace if it's time to pace
					if (%obj.path $= "")
					{
						if(%obj.pace == 0)
						{
							%obj.pace = getRandom(($AI_GUARD_PACE_TIME-1)) +1;
							%this.pacing(%obj);
						}
						else
						{
							%obj.pace--;
						}
					}
					//There are no targets so continue guarding and call the scheduler to have the bot think
					//at it's regular interval
					%this.ailoop=%this.schedule($AI_GUARD_SCANTIME * %obj.attentionlevel  ,"Think" , %obj);
				}

			//The bot has been told that there is a target in sight and range and is set to attack it.
			//While attacking the bot's attention level is kept at it's lowest value (Quickest thinking)
			//The bot looks for the nearest target in sight. If the target is found the bot will aim at the
			//target, set it's move destination to the position of the target, and then openfire on the target.
			case "Attacking":
				//Set the bot's move speed back to normal
				%obj.setMoveSpeed(1.0);
				//Maintain a low attention value to keep the bot thinking quickly while attacking.
				%obj.attentionlevel=1;
				//Get the id of the nearest valid target
				%tgtid = %this.GetClosestHumanInSightandRange(%obj);
				//If %tgtid>0 then there is a valid target
				if(%tgtid >=0)
				{
					//Make sure that we keep ourself in attack mode since we have a target in sight.
					%obj.action = "Attacking";
					//Get the current player object from the client value set in %tgtid
					%tgt = ClientGroup.getobject(%tgtid);
					//Set the bot to aim at the target.
					//(The code uses the VectorAdd to adjust the aim of the bot to correct for the
					//bot trying to shoot at the targets feet.)
					%obj.setAimObject(%tgt.player, "0 0 1");

					%dest = %tgt.player.getposition();

					%basedist = vectorDist(%obj.getposition(), %dest);

					//Check if the bot is flagged as using a ranged weapon, then check if the bot is already close
					//enough to the target or needs to be closer
					if (%obj.weapRange $= "ranged")
					{
						if(%basedist > $AI_GUARD_RANGED_MAX_DISTANCE)
						{
							%this.moveDestinationA = %dest;
							%this.dontMoveAlongTheWall(%obj);
						}
					}
					//Check if the bot is already close enough to the target or needs to be closer
					else
					{
						if(%basedist > $AI_GUARD_MAX_DISTANCE)
						{
							%this.moveDestinationA = %dest;
							%this.dontMoveAlongTheWall(%obj);
						}
					}
					//Tells the bot to start shooting the target.
					%obj.openfire(%obj, %tgt);
					//Tells the scheduler to have us think again 
					%this.ailoop=%this.schedule($AI_GUARD_SCANTIME * %obj.attentionlevel  ,"Think" , %obj);
				}
				else
				{
					//There was no target found, so set our action to NoTarget.
					%obj.action="NoTarget";
					//Again this sets the scheduler to have us think quickly to have the bot
					//react to the loss of it's attack target
					%this.ailoop=%this.schedule(100  ,"Think" , %obj);
				}

			//When a bot loses it's target, or when the bot reaches it's destination as the result of
			//a sidestep the bot will go into a 'hold'
			//During a hold the bot will have enhanced FOV (to emulate scanning around for targets.)
			//The bot will look for targets in range and attack if found.
			//If no target is found the bot will increase it's holdcnt by 1. When the bot reaches it's
			//maximum holdcnt value it will attempt to return to it's base position.
			case "Holding":
				//Set the bot's move speed back to normal
				%obj.setMoveSpeed(1.0);
				//Enhance the bot's FOV
				%this.enhancefov(%obj);
				//Checks for targets - (See the above code for full details of this section of code)
				%tgtid = %this.GetClosestHumanInSightandRange(%obj);
				if(%tgtid >=0)
				{
					%obj.holdcnt=0;
					%obj.action = "Attacking";
					%this.ailoop=%this.schedule(100,"Think" , %obj);
				}
				else
				{
					//There was no target found, so we need to have the bot continue to 'hold'
					//for a little bit before doing anything else.

					//Increase the holdcnt variable by one
					%obj.holdcnt++;
					%obj.fireLater = 0;

					%basedist = vectorDist(%this.getposition(), %this.moveDestinationA);
					if (%basedist > 0.5)
						%this.dontMoveAlongTheWall(%obj);

					//Check to see if we've passed our threshold of waiting
					if (%obj.holdcnt > $AI_GUARD_HOLDCNT_MAX)
					{
						//Set holdcnt back to 0 for the next time we need it.
						%obj.holdcnt=0;

						//Set the bot to return to where it last saw the player if it's not pathed
						if (%obj.path $= "")
						{
							//Reset returning positions for guard bots
							if (%obj.doesGuard $= "guard")
							{
								%obj.returningPos = %obj.marker.getposition();
								%obj.returningTrans = %obj.marker.gettransform();
							}

							%this.moveDestinationA = %obj.returningPos;
							%this.dontMoveAlongTheWall(%obj);
						}
						//Set the bot to return to its path since it is pathed
						else
						{
							if (%obj.returningPath != 0)
							{
								if (%obj.doesGuard $= "guard")
								{
									%this.moveDestinationA = %obj.returningPos;
									%this.dontMoveAlongTheWall(%obj);
								}
								else
								{
									%this.movtrigg = %this.schedule(100, "followPath", %obj.path, -1);
								}
							}
							else
							{
								%obj.returningPath = 1;
							}
						}

						//Set the bot action to 'Returning'
						%obj.action="Returning";
						//Sets the bots oldpos to that of the position it's returning to
						//This is done this way due to the fact that we've been holding
						//and our position hasn't been changing. So we want to be sure that
						//our bot doesn't think that it's stuck as soon as it tries to return.
						%obj.oldpos = %obj.returningPos;
						//We've waited long enough, so let's quickthink and go into 'Return' mode
						%this.ailoop=%this.schedule(100, "Think" , %obj);
					}
					else
					{
						//Start the bot moving to its return point while it's still in holding mode
						%this.moveDestinationA = %obj.returningPos;
						%this.dontMoveAlongTheWall(%obj);

						%obj.clearaim();
						%this.ailoop=%this.schedule($AI_GUARD_SCANTIME * %obj.attentionlevel  ,"Think" , %obj);
					}
				}

			//In Return mode the bot will do the following.
			//It looks for the nearest target in sight and will attack it.
			//It does not check for people sneaking up behind it, nor does it enhance it's FOV.
			//If a target is found the bot will attack.
			//If no target is found, the bot is still in the process of returning so we check to see
			//if the bot is stuck. Stuck in the case means that the bot hase moved a distance of less than
			//1 unit since the last time it thought.
			//If the bot is stuck, sidestep is called to have the bot try to move a different direction
			//The bot is then set to go into 'Holding' but with it's holdcnt set to 1 less than it's maximum.
			//This essentially means that the bot will sidestep, and go into hold for one cycle in which to check
			//targets and then try to return again if there is nothing to attack.
			//If the bot is not stuck and there are no targets, then the bots aim is set to point towards it's
			//destination of it's spawn point. (This is done to prevent the bot from pointing to the position
			//of it's last sidestep while returning.)
			case "Returning":
				//Set the bot's move speed back to normal
				%obj.setMoveSpeed(1.0);
				//The next line can be commented out if desired. I chose to put it in so that the
				//bots would try to return in a timely manner rather than having them wait too long
				//between thinks to see if they were stuck.
				%obj.attentionlevel=$AI_GUARD_MAX_ATTENTION/2;

				//The next few lines again have the bot check for a target and attack if need be.
				%tgtid = %this.GetClosestHumanInSightandRange(%obj);
				if(%tgtid >=0)
				{
					%obj.action = "Attacking";
					%this.ailoop=%this.schedule(100,"Think" , %obj);
				}
				else
				{
					//There was no target so we're still returning. So now check for a pathed or stuck bot
					//This gets a value depicting the distance from the bots last known move point
					%movedist=vectorDist(%obj.getposition(), %obj.oldpos);
					//If the bot hasn't moved more than 1 unit we're probably stuck.
					//Remember - this is only checked for while returning - not guarding
					if (%movedist <1.0)
					{
						//Set our holdcnt to 1 less than the maximum so we only hold for 1 cycle
						%obj.holdcnt=$AI_GUARD_HOLDCNT_MAX-1;
						//Call sidestep to pick a new move destination near the bot
						%this.sidestep(%obj);
					}
					else
					{
						//Check to make sure the bot is not pathed
						if (%obj.path $= "")
						{
							//We're returning and we're not stuck. So make sure we're looking the direction we're running.
							//Check if the bot is guarding
							if (%obj.doesGuard $= "guard")
							{
								%obj.setAimLocation(%obj.marker.getposition());
							}
							else
							{
								%obj.setAimLocation(%obj.returningPos);
							}
						}
					}
				}
				//Set our oldpos to match our current position so that next time we cycle through
				//we'll know if we're going anywhere or not
				%obj.oldpos = %obj.getposition();
				//Scedhule ourselves to think at our regular interval
				%this.ailoop = %this.schedule($AI_GUARD_SCANTIME * %obj.attentionlevel, "Think", %obj);

			//When a bot takes damage his state is set to defending.
			//A bot that is defending will have it's attention set to it's lowest level
			//It will sidestep to try to avoid the danger, and to throw some randomness into it's
			//movement. The bot will then go into a quick hold of 1 count.
			case "Defending":
				//Set the bot's move speed back to normal
				%obj.setMoveSpeed(1.0);
				//Set the hldcnt to 1 less than the max
				%obj.holdcnt=$AI_GUARD_HOLDCNT_MAX-1;			
				//Set the bot to it's highest awareness
				%obj.attentionlevel=1;
				//Sidestep to a random position
				%this.sidestep(%obj);
				//Set our action to 'Holding'
				%obj.action="Holding";
				//Set a quick think schedule to start us looking for targets quickly.
				%this.ailoop=%this.schedule(100 ,"Think" , %obj);

			//NoTarget is set when a bot loses it's target while attacking.
			//It causes a bot's firing variable to be reset, sets the holdcnt to 0
			//so that when we go into a hold we will do so for the full duration
			case "NoTarget":
				//Clear the firing variable
				%obj.firing = false;
				//Clear holdcnt
				%obj.holdcnt=0;
				//Set our action to 'Holding'
				%obj.action = "Holding";
				//Quick think to start us looking for our lost target.
				%this.ailoop=%this.schedule(100  ,"Think" , %obj);

			case "GetHealth":
				%hlth= %this.getclosestiteminsightandrange(%obj, "HealthPatch");
				if(%hlth > 0)
				{
					%obj.action="RetrievingItem";
					%dest=%hlth.getposition();
					%obj.setmovedestination(%dest);
					%this.enhancefov(%obj);
				}
				else
				{
					%obj.action=%prevaction;
				}
				%this.ailoop=%this.schedule(100  ,"Think" , %obj);

			case "GetAmmo":
				%ammostr = %obj.botWeapon @"Ammo";
				%i_ammo= %this.getclosestiteminsightandrange(%obj, %ammostr );
				if(%i_ammo > 0)
				{
					%obj.action="RetrievingItem";
					%dest=%i_ammo.getposition();
					%obj.setmovedestination(%dest);
					%this.enhancefov(%obj);
				}
				else
				{
					%obj.action=%prevaction;
				}

				%this.ailoop=%this.schedule(100  ,"Think" , %obj);

			case "RetrievingItem":
				%obj.setMoveSpeed(1.0);
				%obj.attentionlevel=$AI_GUARD_MAX_ATTENTION/2;
				%tgtid = %this.GetClosestHumanInSightandRange(%obj);
				if(%tgtid >=0)
				{
					%obj.action = "RetrievingItem";
					%obj.attentionlevel=1;
					%tgtid = %this.GetClosestHumanInSightandRange(%obj);
					if(%tgtid >=0)
					{
						%tgt = ClientGroup.getobject(%tgtid);
						%obj.setAimObject(%tgt.player, "0 0 1");
						%obj.openfire(%obj, %tgt);
					}
					else
					{
						%obj.firing = false;
					}
				}
				else
				{
					%movedist=vectorDist(%obj.getposition(), %obj.oldpos);
					if (%movedist <1.0)
					{
						%obj.holdcnt=$AI_GUARD_HOLDCNT_MAX-1;
					
						%this.sidestep(%obj);
					}
					else
					{
						%obj.setaimlocation(%obj.getmovedestination());
					}
				}
				%obj.oldpos=%obj.getposition();
				%this.ailoop=%this.schedule($AI_GUARD_SCANTIME * %obj.attentionlevel  ,"Think" , %obj);
				
			default:
				%obj.action="Holding";
				%this.ailoop=%this.schedule(100  ,"Think" , %obj);
		}	
	}
	//If you want to see the bots thinking processes in action then uncomment the
	//line below. It will then set the hud above the bot to show it's current
	//action/attention level/damage/ammo
	//(Used during testing, but kind of fun to watch when you have
	//several bots on the map at a time to see how things are working out.)

	//%objname= %obj.action @ ":"@ %this.attentionlevel @ ":" @ %obj.getdamagelevel() @ ":" @ %obj.getInventory(%obj.botWeapon @ "Ammo") ;
	//%obj.setshapename(%objname);

	//Clear aim if attention hits max.
	if (%this.attentionlevel == $AI_GUARD_MAX_ATTENTION)
		%obj.clearaim();
}

//Causes AIPlayer to slowly pace around their current location
function AIPlayer::Pacing(%this, %obj)
{
    //%xrand and %yrand are set to be a random number that is equal to -1/2$AI_GUARD_MAX_PACE and +1/2$AI_GUARD_MAX_PACE
    %xrand = getRandom(1,$AI_GUARD_MAX_PACE)-$AI_GUARD_MAX_PACE/2;
    %yrand = getRandom(1,$AI_GUARD_MAX_PACE)-$AI_GUARD_MAX_PACE/2;

    while(%xrand > -$AI_GUARD_MIN_PACE && %xrand < $AI_GUARD_MIN_PACE)
    {
        %xrand = getRandom(1,$AI_GUARD_MAX_PACE)-$AI_GUARD_MAX_PACE/2;
    }
    while(%yrand > -$AI_GUARD_MIN_PACE && %yrand < $AI_GUARD_MIN_PACE)
    {
        %yrand = getRandom(1,$AI_GUARD_MAX_PACE)-$AI_GUARD_MAX_PACE/2;
    }

    //%newloc is first set to the bots current position
    %newLoc = %obj.getTransform();

    //Set the bots returning position to its marker if it's guarding
    if (%obj.doesGuard $= "guard")
      %obj.returningPos = %obj.marker.getposition();

    //If the is away from its returning position, go back to it so it doesn't wander too far away
    %basedist = vectorDist(%obj.getposition(), %obj.returningPos);
    if(%basedist > $AI_GUARD_MIN_PACE)
	{
        %newLoc = %obj.returningTrans;
	}
    else
    {
        //Word(0) of %newloc (which is the x value) is set to equal it's original value plus the value
        //of %xrand. The -/+ aspect of this equivalates to a left/right direction.
        %newLoc = setWord(%newLoc, 0, (getWord(%newLoc, 0) + (%xrand)));
        //Word(1) of %newloc (which is the y value) is set to equal it's original value plus the value
        //of %yrand. The -/+ aspect of this equivalates to a forward/back direction.
        %newLoc = setWord(%newLoc, 1, (getWord(%newLoc, 1) + (%yrand)));

        %basedist = vectorDist(%obj.getposition(), %newLoc);
        //If the target location is very close, don't preform a line of sight test
        if(%basedist > $AI_GUARD_LOS_BYPASS)
        {
            //Line of sight test for the position the bot wants to pace to
            %eyeTrans = %obj.getEyeTransform();
            %eyeEnd = %newLoc;
            %searchResult = containerRayCast(%eyeTrans, %eyeEnd, $TypeMasks::PlayerObjectType | $TypeMasks::StaticTSObjectType |
            $TypeMasks::TerrainObjectType | $TypeMasks::ItemObjectType | $TypeMasks::InteriorObjectType | $TypeMasks::StaticObjectType, %obj);
            %foundObject = getword(%searchResult,0);

            if (%foundObject > 0)
            {
		        %this.pacing(%obj);
		        return;
            }
        }
    }
    //Set the bot to move at a different speed than normal while pacing
    %obj.setMoveSpeed($AI_GUARD_PACE_SPEED);
    //Set the bot to look in the direction that it is moving.
    %obj.setaimlocation(%newLoc);
    //Set the bot to move towards the new position.
    %obj.setMoveDestination(%newLoc);
}

//Sidestep is used to find a random spot near the bot and attempt to have them move towards it.
function AIPlayer::SideStep(%this, %obj)
{
    //%xrand and %yrand are set to be a random number that is equal to -1/2$AI_GUARD_SIDESTEP and +1/2$AI_GUARD_SIDESTEP
    %xrand = getRandom(1,$AI_GUARD_SIDESTEP)-$AI_GUARD_SIDESTEP/2;
    %yrand = getRandom(1,$AI_GUARD_SIDESTEP)-$AI_GUARD_SIDESTEP/2;
    //%newloc is first set to the bots current position
    %newLoc = %obj.getTransform();
    //Word(0) of %newloc (which is the x value) is set to equal it's original value plus the value
    //of %xrand. The -/+ aspect of this equivalates to a left/right direction.
    %newLoc = setWord(%newLoc, 0, (getWord(%newLoc, 0) + (%xrand)));
    //Word(1) of %newloc (which is the y value) is set to equal it's original value plus the value
    //of %yrand. The -/+ aspect of this equivalates to a forward/back direction.
    %newLoc = setWord(%newLoc, 1, (getWord(%newLoc, 1) + (%yrand)));

    //If the bot is pathed, get ready to move to the correct node
    if (%obj.path !$= "")
    {
        if (%this.returningPath == 1)
        {
            %this.returningPath = 2;
        }
    }

    //If there's a target, keep aiming at it while sidestepping
    %tgtid = %this.GetClosestHumanInSightandRange(%obj);
    if(%tgtid >= 0)
    {
      	%tgt = ClientGroup.getobject(%tgtid);
      	%obj.setAimObject(%tgt.player, "0 0 1");

      	%basedist = vectorDist(%obj.getposition(), %newLoc);
      	//If the target location is very close and we have a target player, don't preform a line of sight test
      	if(%basedist > $AI_GUARD_LOS_BYPASS)
      	{
			//Line of sight test for the position the bot wants to sidestep to
			%eyeTrans = %obj.getEyeTransform();
			%eyeEnd = %newLoc;
			%searchResult = containerRayCast(%eyeTrans, %eyeEnd, $TypeMasks::PlayerObjectType | $TypeMasks::StaticTSObjectType |
			$TypeMasks::TerrainObjectType | $TypeMasks::ItemObjectType | $TypeMasks::InteriorObjectType | $TypeMasks::StaticObjectType, %obj);
			%foundObject = getword(%searchResult,0);

			if (%foundObject > 0)
			{
				%this.sidestep(%obj);
				return;
			}
      	}
    }
    //There is no target
    else
    {
		//Line of sight test for the position the bot wants to sidstep to
		%eyeTrans = %obj.getEyeTransform();
		%eyeEnd = %newLoc;
		%searchResult = containerRayCast(%eyeTrans, %eyeEnd, $TypeMasks::PlayerObjectType | $TypeMasks::StaticTSObjectType |
		$TypeMasks::TerrainObjectType | $TypeMasks::ItemObjectType | $TypeMasks::InteriorObjectType | $TypeMasks::StaticObjectType, %obj);
		%foundObject = getword(%searchResult,0);

		if (%foundObject > 0)
		{
			%this.sidestep(%obj);
			return;
		}
		//Set the bot to look in the direction that it is moving.
		else
		{
			%obj.setaimlocation(%newloc);
		}
    }
    //Set the bot to move towards the new position.
    %obj.setMoveDestination(%newLoc);
}

function AIPlayer::CheckLOStoItem(%this, %obj, %item)
{
	%basedist = vectorDist(%obj.getposition(), %item.getposition());
	//If the target item is very close, don't preform a line of sight test
	if(%basedist > $AI_GUARD_LOS_BYPASS)
	{
		%eyeTrans = %obj.getEyeTransform();
		//%eyeEnd = %item.getposition();
		%eyeEnd = %item.getWorldBoxCenter();
		%searchResult = containerRayCast(%eyeTrans, %eyeEnd, $TypeMasks::TerrainObjectType |
		$TypeMasks::InteriorObjectType | $TypeMasks::ItemObjectType | $TypeMasks::PlayerObjectType |
		$TypeMasks::StaticTSObjectType | $TypeMasks::StaticObjectType , %obj);
		%foundObject = getword(%searchResult,0);

		if(%foundObject == %item)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return true;
	}
}

//This is another function taken from code found on garagegames.
//It checks to see if there are any static objects blocking the view
//from the AIPlayer to the target.
function AIPlayer::CheckLOS(%this, %obj, %tgt)
{
	%eyeTrans = %obj.getEyeTransform();
	%eyeEnd = %tgt.player.getEyeTransform();
	%searchResult = containerRayCast(%eyeTrans, %eyeEnd, $TypeMasks::PlayerObjectType | $TypeMasks::StaticTSObjectType |
	$TypeMasks::TerrainObjectType | $TypeMasks::ItemObjectType | $TypeMasks::InteriorObjectType | $TypeMasks::StaticObjectType, %obj);
	%foundObject = getword(%searchResult,0);

	if (%foundObject > 0)
	{
		if(%foundObject.getType() & $TypeMasks::PlayerObjectType)
		{
			//Get the target's location and set it as the bot's return point
			%obj.returningPos = %tgt.player.getposition();
			%obj.returningTrans = %tgt.player.gettransform();
			%obj.lostest = 1;
			return true;
		}
		else
		{
			//If the bot just lost sight of the player, get the player's position a short time after that
			if(%obj.lostest == 1)
			{
			  	%obj.lostest = 0;
			  	%this.lostrigger = %this.schedule($AI_GUARD_LOS_TIME,"getnewguardposition", %obj, %tgt);
			}
			return false;
		}
	}
}

//Get the player's position a short time after sight is lost
function AIPlayer::GetNewGuardPosition(%this, %obj, %tgt)
{
  %obj.returningPos = %tgt.player.getposition();
  %obj.returningTrans = %tgt.player.gettransform();
}

function AIPlayer::GetClosestHumanInSightandRange(%this, %obj)
{
	%dist=0;
	%index = -1;    //sets the initial index value to -1  The index is the id number of the nearest
							 //human target found
	%botpos = %this.getposition();		//The bots current position
	%count = ClientGroup.getCount();		//The number of clients to check

	//The for-next loop cycles through all of the valid clients
	for(%i=0; %i < %count; %i++)
	{
		%client = ClientGroup.getobject(%i);		//Get the client info for the client at index %i
		
		//If the client is invalid then the function bails out returning a -1 value, for no target found.
		if (%client.player !$= "" && %client.player > 0)	
		{
			//The following line just changes the %client to %tgt to make it easier to follow the code below
			%tgt = %client;

			%playpos = %client.player.getposition();		//Assigns the player position to a variable

			%tempdist = vectorDist(%playpos, %botpos);	    //Determine the distance from the bot to the target

			//The first test we perform is to see if the target is within the bots range
			//Is target in range? If not bail out of checking to see if its in view.
			if (%tempdist <= %obj.detdis)
			{

				//Lower attentionlevel to increase response time...
				%this.attentionlevel--;

				//Prevent the attention level from dropping below 1
				if(%this.attentionlevel < 1) %this.attentionlevel = 1;

				//The second check is to see if the target is within the FOV of the bot.
				//Is the target within the fov field of vision of the bot?
				if(%this.Istargetinview(%obj, %tgt, %obj.fov))
				{

					//Lower attentionlevel to increase response time...
					%this.attentionlevel--;

					//Prevent the attention level from dropping below 1
					if(%this.attentionlevel < 1) %this.attentionlevel = 1;

					//The third check we run is to see if there is anything blocking the
					//target from the bot.
					if(%this.CheckLOS(%obj, %tgt))
					{
						//We lower the bots attention level again, to further increase it's
						//response time, this effectively means that the bot will respnd faster to
						//objects that are both in range and in plain sight.
						%this.attentionlevel--;

						//Prevent the attention level from dropping below 1
						if(%this.attentionlevel < 1) %this.attentionlevel = 1;

						//If there is a current target, then check the distance to the new target as
						//compared to the current set target. If the new target is closest, then set
						//the index and tempdistance to the new target.
						if(%tempdist < %dist || %dist == 0)
						{
							%dist = %tempdist;
							%index = %i;
						}
					}
				}
			}
		}
		else
		{
			//If there are no targets in view, then the bots attention will slowly lapse and increase
			//This will slow down how fast the bot thinks and how often it checks for threats.
			%this.attentionlevel = %this.attentionlevel + 0.5;
			if(%this.attentionlevel > $AI_GUARD_MAX_ATTENTION) %this.attentionlevel = $AI_GUARD_MAX_ATTENTION;
		}
	}

	return %index;
}

function AIPlayer::GetClosestItemInSightandRange(%this, %obj, %itemname)
{
	%dist=0;
	%index = -1; 
	%botpos = %this.getposition();
	InitContainerRadiusSearch(%botpos, $AI_GUARD_DETECT_ITEM_RANGE, $TypeMasks::ItemObjectType);
  	while ((%item = containerSearchNext()) != 0)
  	{
 		if (%item.getDataBlock().getName() $= %itemname)
     	{
			%itempos = %item.getposition();
			%tempdist = vectorDist(%itempos, %botpos);

			if(%this.IsIteminview(%obj, %item, %obj.fov))
			{
				if(%this.CheckLOStoItem(%obj, %item))
				{
					if(%tempdist < %dist || %dist == 0)
					{
						%dist = %tempdist;
						%index = %item;
					}
  				}
			}
		}
	}
	return %index;
}

//This function checks to see if the target supplied is within the bots FOV
function AIPlayer::IsItemInView(%this, %obj, %item, %fov)
{
	%ang = %this.check2dangletoitem(%obj, %item);
	%visleft = 360 - (%fov/2);
	%visright = %fov/2;
	if (%ang > %visleft || %ang < %visright)
	{
		return true;
	}
	else
	{
		return false;
	}
}	

//This function checks to see if the target supplied is within the bots FOV
function AIPlayer::IsTargetInView(%this, %obj, %tgt, %fov)
{
	%ang = %this.check2dangletotarget(%obj, %tgt);
	%visleft = 360 - (%fov/2);
	%visright = %fov/2;
	if (%ang > %visleft || %ang < %visright)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//Check if the location the bot is moving to is in sight.
//And if it's not, move somwhere that is in sight (if there's a better place).
function AIPlayer::dontMoveAlongTheWall(%this, %obj)
{
    //Save the original destination to another variable for later use
    %this.moveDestinationB = %this.moveDestinationA;

    if (%this.checkMovementLos(%obj))
	{
        return;
	}
    else
    {
        //Word(0) of %this.moveDestinationB (which is the x value) is set to equal the value of %this.moveDestinationA's Word(0).
        %this.moveDestinationB = setWord(%this.moveDestinationB, 0, (getWord(%this.moveDestinationA, 0)));
        //Word(1) of %this.moveDestinationB (which is the y value) is set to equal the value of %this.getposition()'s Word(1).
        %this.moveDestinationB = setWord(%this.moveDestinationB, 1, (getWord(%this.getposition(), 1)));

	    if (%this.checkMovementLos(%obj))
        {
            //Add AI_GUARD_CORNERING's value to the destination's value
            %this.moveDestinationB = setWord(%this.moveDestinationB, 0, (getWord(%this.moveDestinationA, 0) + $AI_GUARD_CORNERING));
            %this.moveDestinationB = setWord(%this.moveDestinationB, 1, (getWord(%this.getposition(), 1) + $AI_GUARD_CORNERING));

            if (%this.checkMovementLos(%obj))
			{
                return;
			}
            else
            {
                //Or else subtracts AI_GUARD_CORNERING's value from the destination's value
                %this.moveDestinationB = setWord(%this.moveDestinationB, 0, (getWord(%this.moveDestinationA, 0) - $AI_GUARD_CORNERING));
                %this.moveDestinationB = setWord(%this.moveDestinationB, 1, (getWord(%this.getposition(), 1) - $AI_GUARD_CORNERING));
                %obj.setmovedestination(%this.moveDestinationB);
            }
        }
	    else
        {
            //Word(0) of %this.moveDestinationB (which is the x value) is set to equal the value of %this.getposition()'s Word(0).
            %this.moveDestinationB = setWord(%this.moveDestinationB, 0, (getWord(%this.getposition(), 0)));
            //Word(1) of %this.moveDestinationB (which is the y value) is set to equal the value of %this.moveDestinationA's Word(1).
            %this.moveDestinationB = setWord(%this.moveDestinationB, 1, (getWord(%this.moveDestinationA, 1)));

	        if (%this.checkMovementLos(%obj))
            {
                //Add AI_GUARD_CORNERING's value to the destination's value
                %this.moveDestinationB = setWord(%this.moveDestinationB, 0, (getWord(%this.getposition(), 0) + $AI_GUARD_CORNERING));
                %this.moveDestinationB = setWord(%this.moveDestinationB, 1, (getWord(%this.moveDestinationA, 1) + $AI_GUARD_CORNERING));

                if (%this.checkMovementLos(%obj))
				{
                    return;
				}
                else
                {
                    //Or else subtracts AI_GUARD_CORNERING's value from the destination's value
                    %this.moveDestinationB = setWord(%this.moveDestinationB, 0, (getWord(%this.getposition(), 0) - $AI_GUARD_CORNERING));
                    %this.moveDestinationB = setWord(%this.moveDestinationB, 1, (getWord(%this.moveDestinationA, 1) - $AI_GUARD_CORNERING));
                    %obj.setmovedestination(%this.moveDestinationB);
                }
            }
		    else
			{
			    %obj.setmovedestination(%this.moveDestinationA);
			}
	    }
    }
}

//Line of sight test for the position the bot wants to move to
function AIPlayer::checkMovementLos(%this, %obj)
{
    %eyeTrans = %obj.getEyeTransform();
    %eyeEnd = %this.moveDestinationB;
    %searchResult = containerRayCast(%eyeTrans, %eyeEnd, $TypeMasks::StaticTSObjectType | $TypeMasks::TerrainObjectType |
    $TypeMasks::ItemObjectType | $TypeMasks::InteriorObjectType | $TypeMasks::StaticObjectType, %obj);
    %foundObject = getword(%searchResult,0);

    if (%foundObject == 0)
    {
        //Check to make sure the bot isn't already extremly close to its dstination
        %basedist = vectorDist(%obj.getposition(), %this.moveDestinationB);

	    if (%basedist > 0.5)
        {
		    %obj.setmovedestination(%this.moveDestinationB);
            return true;
        }
        else
        {
            return false;
        }
    }

    else
    {
        return false;
    }
}

// Gets the closest player to object. Used by the trigger to determine if a player triggered it.
function AIPlayer::GetClosestPlayer(%this, %obj)
{
	%dist=0;
	%index = -1; //sets the initial index value to -1  The index is the id number of the nearest
							 //human target found
	%botpos = %this.getposition();		//The bots current position
	%count = ClientGroup.getCount();		//The number of clients to check

	//The for-next loop cycles through all of the valid clients
	for(%i=0; %i < %count; %i++)
	{
		%client = ClientGroup.getobject(%i);		//Get the client info for the client at index %i
		
			//If the client is invalid then the function bails out returning a -1 value, for no
		//target found.
		if (%client.player !$= "" && %client.player > 0)	
		 {
		    %index = %client.player;
		 }
	}
}

//-----------------------------------------------------------------------------
// Pathed AI Functions
//-----------------------------------------------------------------------------

//Start the bot following a path
function AIPlayer::followPath(%this, %path, %node, %obj)
{
   //Check if the bot is pathed
   if (!isObject(%path))
   {
      %this.path = "";
      return;
   }

   %dist = 0;
   %tempdist = 0;
   %index = -1;
   %botpos = %this.getposition();
   %count = %path.getCount();
   //Cycle through all nodes on this path and set the closest node as the bot's current location
   while ((%node = %count) != 0)
   {
     	%nodepos = %this.path.getObject(%count - 1).getposition();
		%tempdist = vectorDist(%nodepos, %botpos);

		if(%tempdist < %dist || %dist == 0)
		{
			%dist = %tempdist;
			%index = %node;
		}
     	%count--;
   }
   %index = %index - 1;
   %this.moveToNode(%index);

   if (%index > %path.getCount() - 1)
   {
      %this.targetNode = %path.getCount() - 1;
   }
   else
   {
      %this.targetNode = %index;
   }
}

function AIPlayer::moveToNextNode(%this, %obj)
{
   //See if the bot just sidesteped
   if (%this.returningPath == 2)
   {
      //Set returningPath back to 1 for other functions
      %this.returningPath = 1;
      %this.moveToNode(%this.currentNode);
      return;
   }

   //See where the bot is and where it should be going
   if (%this.targetNode < 0 || %this.currentNode < %this.targetNode)
   {
      if (%this.currentNode < %this.path.getCount() - 1)
      {
         %this.moveToNode(%this.currentNode + 1);
      }
      else
      {
         %this.moveToNode(0);
      }
   }
   else
   {
      if (%this.currentNode == 0)
      {
         %this.moveToNode(%this.path.getCount() - 1);
      }
      else
      {
         %this.moveToNode(%this.currentNode - 1);
      }
   }
}

function AIPlayer::moveToNode(%this, %index, %obj)
{
   //Move to the given path node index
   %this.currentNode = %index;
   %node = %this.path.getObject(%index);
   %this.setMoveDestination(%node.getTransform());
   %this.targetNode = %this.currentNode + 1;

   //Make the bot face the node it's moving to
   %this.setAimLocation(%this.path.getObject(%this.currentNode).getposition());
}
