function RealisticVFX::onCreate(%this)
{
   return;
   if(isObject(DatablockFilesList))
   {
      DatablockFilesList.add( "data/RalisticVFX/Datablocks/LifeLikeEmitters.cs" );
      DatablockFilesList.add( "data/RalisticVFX/Datablocks/LifeLikeExp_ComplexLarge.cs" );
      DatablockFilesList.add( "data/RalisticVFX/Datablocks/LifeLikeExp_ComplexSmall.cs" );
      DatablockFilesList.add( "data/RalisticVFX/Datablocks/LifeLikeExp_FirebombLarge.cs" );
      DatablockFilesList.add( "data/RalisticVFX/Datablocks/LifeLikeExp_FirebombSmall.cs" );
      DatablockFilesList.add( "data/RalisticVFX/Datablocks/LifeLikeExp_Flak.cs" );
      DatablockFilesList.add( "data/RalisticVFX/Datablocks/LifeLikeExp_Flashbang.cs" );
      DatablockFilesList.add( "data/RalisticVFX/Datablocks/LifeLikeExp_GroundHitLarge.cs" );
      DatablockFilesList.add( "data/RalisticVFX/Datablocks/LifeLikeExp_GroundHitSmall.cs" );
      DatablockFilesList.add( "data/RalisticVFX/Datablocks/LifeLikeExp_SimpleLarge.cs" );
      DatablockFilesList.add( "data/RalisticVFX/Datablocks/LifeLikeExp_SimpleSmall.cs" );
   }
}

function RealisticVFX::onDestroy(%this)
{
}

