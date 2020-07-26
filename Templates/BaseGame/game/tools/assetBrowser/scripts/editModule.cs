//
function AssetBrowser::ConvertFolderIntoModule(%this, %folderName)
{
   if(!isDirectory("data/" @ %folderName))
      return;
      
   AssetBrowser_AddModule-->moduleName.text = %folderName;
   AssetBrowser_addModuleWindow.callbackFunction = "AssetBrowser.loadDirectories();";
   
   AssetBrowser_addModuleWindow.CreateNewModule();
}

function AssetBrowser::CreateNewModule(%this)
{
   Canvas.pushDialog(AssetBrowser_AddModule); 
   AssetBrowser_addModuleWindow.selectWindow();  
   
   AssetBrowser_addModuleWindow.callbackFunction = "AssetBrowser.promptNewModuleFolders();";
}

function AssetBrowser::promptNewModuleFolders(%this)
{
   toolsMessageBoxYesNo("Create Folders?", 
         "Do you want to create some common folders for organization of your new Module?", 
         "AssetBrowser.makeModuleFolders();",  //if yes, make the foldesr
         "AssetBrowser.loadDirectories();");  //if no, just refresh
}

function AssetBrowser::makeModuleFolders(%this)
{
   %moduleId = AssetBrowser.newModuleId;
   %moduleDef = ModuleDatabase.findModule(%moduleId);
   %modulePath = %moduleDef.ModulePath;
   
   %count = 0;
   %defaultModuleFolders[%count++] = "datablocks";
   %defaultModuleFolders[%count++] = "terrains";
   %defaultModuleFolders[%count++] = "postFXs";
   %defaultModuleFolders[%count++] = "levels";
   %defaultModuleFolders[%count++] = "shapes";
   %defaultModuleFolders[%count++] = "guis";
   %defaultModuleFolders[%count++] = "scripts";
   %defaultModuleFolders[%count++] = "scripts/client";
   %defaultModuleFolders[%count++] = "scripts/server";
   
   for(%i=0; %i <= %count; %i++)
   {
      %this.dirHandler.createFolder(%modulePath @ "/" @ %defaultModuleFolders[%i]);
   }
   
   AssetBrowser.loadDirectories();
}

function AssetBrowser::createNewEditorTool(%this)
{
   Canvas.pushDialog(AssetBrowser_AddModule); 
   AssetBrowser_addModuleWindow.selectWindow(); 
   
   AssetBrowser_addModuleWindow.callbackFunction = "AssetBrowser.loadDirectories();";
   
   AssetBrowser_addModuleWindow.CreateNewModule();
}

function AssetBrowser_editModule::saveModule(%this)
{
   //Check what special actions we may need to do, such as renames
   %moduleDef = ModuleDatabase.findModule(AssetBrowser.selectedModule, 1);
   
   %oldModuleName = %moduleDef.ModuleID;
   
   if(%oldModuleName !$= AssetBrowser.tempModule.ModuleID)
   {      
      //rename the script file and script namespaces
      %oldScriptFilePath = "data/" @ %oldModuleName @ "/" @ %moduleDef.scriptFile;
      %newscriptFilePath = "data/" @ AssetBrowser.tempModule.ModuleID @ "/";
      %scriptExt = fileExt(%moduleDef.scriptFile);
      
      %newScriptFileName = %newscriptFilePath @ "/" @ AssetBrowser.tempModule.ModuleID @ %scriptExt;
      %newScriptFileOldName = %newscriptFilePath @ "/" @ %oldModuleName @ %scriptExt;
      
      %moduleDef.ModuleId = AssetBrowser.tempModule.ModuleID;
      %moduleDef.scriptFile = AssetBrowser.tempModule.ModuleID @ %scriptExt;
      
      ModuleDatabase.copyModule(%moduleDef, AssetBrowser.tempModule.ModuleID, "data/" @ AssetBrowser.tempModule.ModuleID);
      
      //Go through our scriptfile and replace the old namespace with the new
      %editedFileContents = "";
      
      %file = new FileObject();
      if ( %file.openForRead( %newScriptFileOldName ) ) 
      {
         while ( !%file.isEOF() ) 
         {
            %line = %file.readLine();
            %line = trim( %line );
            
            %editedFileContents = %editedFileContents @ strreplace(%line, %oldModuleName, AssetBrowser.tempModule.ModuleID) @ "\n";
         }
         
         %file.close();
      }
      
      if(%editedFileContents !$= "")
      {
         %file.openForWrite(%newScriptFileName);
         
         %file.writeline(%editedFileContents);
         
         %file.close();
      }
      
      %success = fileDelete(%newScriptFileOldName);
      
      ModuleDatabase.unloadExplicit(%oldModuleName);
      
      %success = fileDelete("data/" @ %oldModuleName);
      
      ModuleDatabase.loadExplicit(AssetBrowser.tempModule.ModuleID);
   }
   
   //Now, update the module file itself
   //%file = ModuleDatabase.getAssetFilePath(%moduleDef.ModuleID);
   //%success = TamlWrite(AssetBrowser_editAsset.editedAsset, %file);
   
   AssetBrowser.loadFilters();

   Canvas.popDialog(AssetBrowser_editModule);
}

function AssetBrowser::editModuleInfo(%this)
{
   Canvas.pushDialog(AssetBrowser_editModule); 
   
   %moduleDef = ModuleDatabase.findModule(AssetBrowser.selectedModule, 1);
   
   AssetBrowser.tempModule = new ModuleDefinition();
   AssetBrowser.tempModule.assignFieldsFrom(%moduleDef);
   
   AssetBrowser_editModule.editedModuleId = AssetBrowser.selectedModule;
   AssetBrowser_editModule.editedModule = AssetBrowser.tempModule;
   
    /// Module configuration.
   ModuleEditInspector.startGroup("General");
   ModuleEditInspector.addField("ModuleId", "ModuleId", "string", "", AssetBrowser.tempModule.ModuleId, "", AssetBrowser.tempModule);
   ModuleEditInspector.addField("VersionId", "VersionId", "string", "", AssetBrowser.tempModule.VersionId, "", AssetBrowser.tempModule);
   ModuleEditInspector.addField("BuildId", "BuildId", "string", "", AssetBrowser.tempModule.BuildId, "", AssetBrowser.tempModule);
   ModuleEditInspector.addField("enabled", "enabled", "bool", "", AssetBrowser.tempModule.enabled, "", AssetBrowser.tempModule);
   ModuleEditInspector.addField("Description", "Description", "command", "", AssetBrowser.tempModule.Description, "", AssetBrowser.tempModule);
   ModuleEditInspector.addField("Group", "Group", "string", "", AssetBrowser.tempModule.Group, "", AssetBrowser.tempModule);
   ModuleEditInspector.endGroup();
   
   ModuleEditInspector.startGroup("Management");
   ModuleEditInspector.addField("Synchronized", "Synchronized", "bool", "", AssetBrowser.tempModule.Synchronized, "", AssetBrowser.tempModule);
   ModuleEditInspector.addField("Deprecated", "Deprecated", "bool", "", AssetBrowser.tempModule.Deprecated, "", AssetBrowser.tempModule);
   ModuleEditInspector.addField("CriticalMerge", "CriticalMerge", "bool", "", AssetBrowser.tempModule.CriticalMerge, "", AssetBrowser.tempModule);
   ModuleEditInspector.addField("OverrideExistingObjects", "OverrideExistingObjects", "bool", "", AssetBrowser.tempModule.OverrideExistingObjects, "", AssetBrowser.tempModule);
   ModuleEditInspector.endGroup();
   
   ModuleEditInspector.startGroup("Meta");
   ModuleEditInspector.addField("Author", "Author", "string", "", AssetBrowser.tempModule.Author, "", AssetBrowser.tempModule);
   ModuleEditInspector.addField("Type", "Type", "string", "", AssetBrowser.tempModule.Type, "", AssetBrowser.tempModule);
   ModuleEditInspector.endGroup();
   
   ModuleEditInspector.startGroup("Script");
   ModuleEditInspector.addField("ScriptFile", "ScriptFile", "string", "", AssetBrowser.tempModule.ScriptFile, "", AssetBrowser.tempModule);
   ModuleEditInspector.addField("CreateFunction", "CreateFunction", "string", "", AssetBrowser.tempModule.CreateFunction, "", AssetBrowser.tempModule);
   ModuleEditInspector.addField("DestroyFunction", "DestroyFunction", "string", "", AssetBrowser.tempModule.DestroyFunction, "", AssetBrowser.tempModule);
   ModuleEditInspector.endGroup();
   
   ModuleEditInspector.startGroup("Dependencies");
   ModuleEditInspector.addField("ModuleDependencies", "Module Dependencies", "ModuleDependenciesButton", "", "", "", AssetBrowser.tempModule);
   ModuleEditInspector.endGroup();
}

function AssetBrowser::editModuleScript(%this)
{
   %moduleDef = ModuleDatabase.findModule(AssetBrowser.selectedModule, 1);
   
   %scriptFile = %moduleDef.ModuleScriptFilePath;
   
   EditorOpenFileInTorsion(makeFullPath(%scriptFile), 0);
}

function AssetBrowser::renameModule(%this)
{
   
}

function AssetBrowser::reloadModule(%this)
{
   ModuleDatabase.unregisterModule(AssetBrowser.SelectedModule, 1);
   ModuleDatabase.loadExplicit(AssetBrowser.SelectedModule);
}

function AssetBrowser::deleteModule(%this)
{
   
}

function AssetBrowser::RefreshModuleDependencies(%this, %moduleDef)
{
   //Iterate through all our modules
   
   //then, iterate through the module's assets
   
   //if an asset has a module that isn't us, queue that into the dependencies list  
   
   //AssetBrowser.RefreshModuleDependencies(16823);
   %modulePath = filePath(%moduleDef.ModuleFilePath);
   
   %filePattern = "*.cs" TAB "*.taml" TAB "*.mis";
   
   //First, wipe out any files inside the folder first
   %file = makeFullPath(findFirstFileMultiExpr( %filePattern, true));
   %fileObj = new FileObject();
   
   %modulesList = ModuleDatabase.findModules(false);
   
   new ArrayObject(moduleDepList);

   while( %file !$= "" )
   {      
      if(startsWith(%file, %modulePath))
      {
         if(%fileObj.openForRead(%file))
         {
            while( !%fileObj.isEOF() )
            {
               %line = %fileObj.readLine();
               
               if(%line $= "")
                  continue;
               
               for(%i=0; %i < getWordCount(%modulesList); %i++)
               {
                  %moduleName = getWord(%modulesList, %i).moduleID;
                  
                  //if(%moduleName $= %moduleDef.moduleID)
                  //   continue;
                     
                  %hasMatch = strIsMatchExpr( "*"@%moduleName@":*", %line );
                  
                  if(%hasMatch)
                  {
                     moduleDepList.add(%moduleName);
                  }
               }
            }
         }
      }
      
      %file = makeFullPath(findNextFileMultiExpr( %filePattern ));
   }
   
   %fileObj.delete();
}