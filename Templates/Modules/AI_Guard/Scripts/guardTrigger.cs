
function guardTrigger::onEnterTrigger(%this, %trigger, %obj)
{
  echo(%trigger @ " has been triggered!");
  // we've been triggered.  Now check to see if the player triggered the trigger
  // we don't want other enemies to keep spawing more enemies!
  %tgtid = AIPlayer::GetClosestPlayer(%trigger);
         //echo("nearest human is " @ %tgtid);
  // check to see if the player triggered this.  
  if (%tgtid == %obj)
  {
      // if triggerMany is set, then we shouldn't do anything.  (or do something different.)
      // if you want a trigger to always spawn an enemy, set the trigger's triggerMany value to "true"
      // default behavior is to trigger once.
     if (!%trigger.triggerMany && !%trigger.doneOnce)
     {

         // set the spawnGroup variable to pass on to the spawn function
         %spawnGroup = %trigger.spawnGroup;

         // let the game know we've already been triggered once.
         %trigger.doneOnce = true;

         // spawn the group        
         AIPlayer::spawnByGroup(%spawnGroup);

     }
     else
     {
        // we've been triggered before.  Don't do anything
        // If you wanted to do something different, this is where you would put it.
     }
  }
}