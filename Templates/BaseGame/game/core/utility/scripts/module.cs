function callOnModules(%functionName, %moduleGroup)
{
   //Get our modules so we can exec any specific client-side loading/handling
   %modulesList = ModuleDatabase.findModules(false);
   for(%i=0; %i < getWordCount(%modulesList); %i++)
   {
      %module = getWord(%modulesList, %i);
      
      if(%moduleGroup !$= "")
      {
         if(%module.group !$= %moduleGroup)
            continue;  
      }
      
      if(isObject(%module.scopeSet) && %module.scopeSet.isMethod(%functionName))
      {
         eval(%module.scopeSet @ "." @ %functionName @ "();");
      }
   }   
}

function loadModuleMaterials(%moduleGroup)
{
   //Get our modules so we can exec any specific client-side loading/handling
   %modulesList = ModuleDatabase.findModules(false);
   for(%i=0; %i < getWordCount(%modulesList); %i++)
   {
      %module = getWord(%modulesList, %i);
      
      if(%moduleGroup !$= "")
      {
         if(%module.group !$= %moduleGroup)
            continue;  
      }
      
      %modulePath = %module.ModulePath;
      
      // Load any materials files for which we only have DSOs.

      for( %file = findFirstFile( %modulePath @ "/*/materials.cs.dso" );
           %file !$= "";
           %file = findNextFile( %modulePath @ "/*/materials.cs.dso" ))
      {
         // Only execute, if we don't have the source file.
         %csFileName = getSubStr( %file, 0, strlen( %file ) - 4 );
         if( !isFile( %csFileName ) )
            exec( %csFileName );
      }

      // Load all source material files.

      for( %file = findFirstFile( %modulePath @ "/*/materials.cs" );
           %file !$= "";
           %file = findNextFile( %modulePath @ "/*/materials.cs" ))
      {
         exec( %file );
      }
   }
}