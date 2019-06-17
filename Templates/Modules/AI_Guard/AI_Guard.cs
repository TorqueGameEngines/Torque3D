function AI_Guard::onCreate(%this)
{
   exec("./Scripts/aiPlayer.cs");
   exec("./Scripts/guardTrigger.cs");
   
   if(isObject(DatablockFilesList))
   {
      DatablockFilesList.add( "data/AI_Guard/Datablocks/aiPlayerDatablocks.cs" );
      DatablockFilesList.add( "data/AI_Guard/Datablocks/aiPlayerMarker.cs" );
   }
}

function AI_Guard::onDestroy(%this)
{
}

