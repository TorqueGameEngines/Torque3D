//-----------------------------------------------------------------------------
// Module creation functions.
//-----------------------------------------------------------------------------

function badBehaviour::create( %this )
{
}

function badBehaviour::destroy( %this )
{
   
}

function badBehaviour::initClient( %this )
{
   %this.queueExec("scripts/server/behaviorTreeManager.cs");
   %this.queueExec("scripts/server/badBot.cs");
   %this.queueExec("scripts/server/botMatch.cs");
}

