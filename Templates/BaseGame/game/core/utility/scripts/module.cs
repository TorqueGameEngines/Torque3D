$traceModuleCalls=false;
$reportModuleFileConflicts=true;
if (!isObject(ExecFilesList))
   new ArrayObject(ExecFilesList);
  
function callOnModules(%functionName, %moduleGroup)
{
   //clear per module group file execution chain
   ExecFilesList.empty();
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
   
   %execFilecount = ExecFilesList.count();
   for (%i=0;%i<%execFilecount;%i++)
   {
        %filename = ExecFilesList.getKey(%i);
        exec(%filename);
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

function SimSet::getModulePath(%scopeSet)
{
   %name = %scopeSet.getName();
   %moduleDef = ModuleDatabase.findModule(%name);
     
   if(isObject(%moduleDef))
      return %moduleDef.ModulePath;
   
   return "";
}

function SimSet::registerDatablock(%scopeSet, %datablockFilePath, %isExclusive)
{
   if ($traceModuleCalls)
      warn("SimSet::registerDatablock");
   %name = %scopeSet.getName();
   %moduleDef = ModuleDatabase.findModule(%name, 1);
     
   if(!isObject(%moduleDef))
   {
      error("Module::registerDatablock() - unable to find a module with the moduleID of " @ %name);
      return;
   }
   
   if(!isObject(DatablockFilesList))
   {
      error("Module::registerDatablock() - DatablockFilesList array object doesn't exist!");
      return;
   }
   
   %relativePath = makeRelativePath(%datablockFilePath);
   
   %fullPath = pathConcat(%moduleDef.ModulePath, %relativePath);
   ///go through all entries
   %locked = false;
   %dbFilecount = DatablockFilesList.count();
   for (%i=0;%i<%dbFilecount;%i++)
   {
        %check = DatablockFilesList.getKey(%i);
        //look for a substring match
        %isMatch = strIsMatchExpr("*"@ %datablockFilePath,%check );
        if (%isMatch)
        {
            //check if we're already locked in
            //and kill off any duplicates
            //do note that doing it in this order means setting exclusive twice
            //allows one to override exclusive with exclusive
            %locked = DatablockFilesList.getValue(%i);

            if ((!%locked && !%isExclusive)&&($reportModuleFileConflicts))
                error("found" SPC %datablockFilePath SPC "duplicate file!");
            if (!%locked || (%locked && %isExclusive))
            { // Replacing an existing entry, update in-place
                DatablockFilesList.setKey(%fullPath, %i);
                DatablockFilesList.setValue(%isExclusive, %i);
                %locked = true; //Done, but don't return and bypass trace logging below
            }
            break;
        }
   }
   //if we're not locked, go ahead and add it to the pile
   if (!%locked)
       DatablockFilesList.add(%fullPath,%isExclusive);
   if ($traceModuleCalls)
      DatablockFilesList.echo();
}

function SimSet::unRegisterDatablock(%scopeSet, %datablockFilePath)
{
   if ($traceModuleCalls)
      warn("SimSet::unRegisterDatablock");
   %name = %scopeSet.getName();
   %moduleDef = ModuleDatabase.findModule(%name, 1);
     
   if(!isObject(%moduleDef))
   {
      error("Module::unRegisterDatablock() - unable to find a module with the moduleID of " @ %name);
      return;
   }
   
   if(!isObject(DatablockFilesList))
   {
      error("Module::unRegisterDatablock() - DatablockFilesList array object doesn't exist!");
      return;
   }
   
   %relativePath = makeRelativePath(%datablockFilePath);
   
   %fullPath = pathConcat(%moduleDef.ModulePath, %relativePath);
   ///go through all entries
   %locked = false;
   %dbFilecount = DatablockFilesList.count();
   for (%i=0;%i<%dbFilecount;%i++)
   {
        %check = DatablockFilesList.getKey(%i);
        //look for a substring match
        %isMatch = strIsMatchExpr("*"@ %datablockFilePath,%check );
        if (%isMatch)
        {
            //check if we're already locked in. if not, kill it.
            %locked = DatablockFilesList.getValue(%i);
            if (!%locked)
            {
                DatablockFilesList.erase(%i);
            }
        }
   }
   if ($traceModuleCalls)
      DatablockFilesList.echo();
}

function SimSet::queueExec(%scopeSet, %execFilePath, %isExclusive)
{
   if ($traceModuleCalls)
      warn("SimSet::queueExec");
   %name = %scopeSet.getName();
   %moduleDef = ModuleDatabase.findModule(%name, 1);
     
   if(!isObject(%moduleDef))
   {
      error("Module::queueExec() - unable to find a module with the moduleID of " @ %name);
      return;
   }
   
   if(!isObject(ExecFilesList))
   {
      error("Module::queueExec() - ExecFilesList array object doesn't exist!");
      return;
   }
   
   if ($traceModuleCalls)
      warn("module root path="@ makeRelativePath(%moduleDef.ModulePath));
  
   %fullPath = pathConcat(%moduleDef.ModulePath, %execFilePath);
   ///go through all entries
   %locked = false;
   %execFilecount = ExecFilesList.count();
   for (%i=0;%i<%execFilecount;%i++)
   {
        %check = ExecFilesList.getKey(%i);
        //look for a substring match
        %isMatch = strIsMatchExpr("*"@ %execFilePath,%check );
        if (%isMatch)
        {
            //check if we're already locked in
            //and kill off any duplicates
            //do note that doing it in this order means setting exclusive twice
            //allows one to override exclusive with exclusive
            %locked = ExecFilesList.getValue(%i);
            if ((!%locked && !%isExclusive)&&($reportModuleFileConflicts))
                error("found" SPC %execFilePath SPC "duplicate file!");
            if (!%locked || (%locked && %isExclusive))
            { // Replacing an existing entry, update in-place
                ExecFilesList.setKey(%fullPath, %i);
                ExecFilesList.setValue(%isExclusive, %i);
                %locked = true; //Done, but don't return and bypass trace logging below
            }
            break;
        }
   }
   //if we're not locked, go ahead and add it to the pile
   if (!%locked)
       ExecFilesList.add(%fullPath,%isExclusive);
   if ($traceModuleCalls)       
      ExecFilesList.echo();
}

function SimSet::unQueueExec(%scopeSet, %execFilePath)
{
   if ($traceModuleCalls)
      warn("SimSet::unRegisterDatablock");
   %name = %scopeSet.getName();
   %moduleDef = ModuleDatabase.findModule(%name, 1);
     
   if(!isObject(%moduleDef))
   {
      error("Module::unRegisterDatablock() - unable to find a module with the moduleID of " @ %name);
      return;
   }
   
   if(!isObject(ExecFilesList))
   {
      error("Module::unRegisterDatablock() - ExecFilesList array object doesn't exist!");
      return;
   }
   
   %relativePath = makeRelativePath(%execFilePath);
   
   %fullPath = pathConcat(%moduleDef.ModulePath, %relativePath);
   ///go through all entries
   %locked = false;
   %execFilecount = ExecFilesList.count();
   for (%i=0;%i<%execFilecount;%i++)
   {
        %check = ExecFilesList.getKey(%i);
        //look for a substring match
        %isMatch = strIsMatchExpr("*"@ %execFilePath,%check );
        if (%isMatch)
        {
            //check if we're already locked in. if not, kill it.
            %locked = ExecFilesList.getValue(%i);
            if (!%locked)
            {
                ExecFilesList.erase(%i);
            }
        }
   }
   if ($traceModuleCalls)
      ExecFilesList.echo();
}