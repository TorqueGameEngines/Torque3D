function Verve::create( %this )
{
   exec("data/Verve/gui/verveCinematic.gui");
   
   exec("data/Verve/scripts/server/verveCinematicController.cs");
   exec("data/Verve/scripts/server/verveCinematicTrigger.cs");
   exec("data/Verve/scripts/server/vervePathTutorialData.cs");
   
   if(isObject(DatablockFilesList))
   {
      DatablockFilesList.add( "data/Verve/scripts/datablocks/verve/VerveActorData.cs" );
      DatablockFilesList.add( "data/Verve/scripts/datablocks/verve/VervePathTutorialData.cs" );
   }
}

function Verve::destroy( %this )
{
   
}