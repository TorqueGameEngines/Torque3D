function AssetBrowser::createNewDatablock(%this)
{
   AssetBrowser_newFolderNameTxt.text = "NewFolder";
   Canvas.pushDialog(AssetBrowser_newFolder);
}

function AssetBrowser::doCreateNewDatablock(%this)
{
   %newFolderName = AssetBrowser_newFolderNameTxt.getText();
   
   if(%newFolderName $= "")
      %newFolderName = "NewFolder";
      
   %newFolderIdx = "";
   %matched = true;
   %newFolderPath = "";
   while(%matched == true)
   {
      %newFolderPath = AssetBrowser.dirHandler.currentAddress @ "/" @ %newFolderName @ %newFolderIdx;
      if(!isDirectory(%newFolderPath))
      {
         %matched = false;
      }
      else
      {
         %newFolderIdx++;         
      }
   }
   
   //make a dummy file
   %file = new FileObject();
   %file.openForWrite(%newFolderPath @ "/test");
   %file.close();
   
   fileDelete(%newFolderPath @ "/test");
   
   //refresh the directory
   AssetBrowser.loadDirectories();
   
   %this.navigateTo(%newFolderPath);
}

function AssetBrowser::buildDatablockPreview(%this, %assetDef, %previewData)
{
   %previewData.assetName = %assetDef;
   %previewData.assetPath = "";
   
   %previewData.previewImage = "tools/assetBrowser/art/datablockIcon";
   
   //%previewData.assetFriendlyName = %assetDef.assetName;
   %previewData.assetDesc = %assetDef;
   %previewData.tooltip = %assetDef;
   %previewData.doubleClickCommand = "AssetBrowser.schedule(10, \"spawnDatablockObject\",\""@ %assetDef @"\");";//browseTo %assetDef.dirPath / %assetDef.assetName
}

function spawnDatablockObject(%datablock)
{
   %name = %datablock.getName();
   %class = %datablock.getClassName();
   %cmd = %class @ "::create(" @ %name @ ");";
      
   %shapePath = ( %datablock.shapeFile !$= "" ) ? %datablock.shapeFile : %datablock.shapeName;
   %createCmd = "EWCreatorWindow.createObject( \\\"" @ %cmd @ "\\\" );";
   return eval("showImportDialog( \"" @ %shapePath @ "\", \"" @ %createCmd @ "\" );");
}

function AssetBrowser::renameDatablock(%this, %folderPath, %newFolderName)
{
   %fullPath = makeFullPath(%folderPath);
   %newFullPath = makeFullPath(%folderPath);
   
   %fullPath = strreplace(%fullPath, "//", "/");
   
   %count = getTokenCount(%fullPath, "/");
   %basePath = getTokens(%fullPath, "/", 0, %count-2);
   %oldName = getToken(%fullPath, "/", %count-1);
   
   //We need to ensure that no files are 'active' while we try and clean up behind ourselves with the delete action
   //so, we nix any assets active for the module, do the delete action on the old folder, and then re-acquire our assets.
   //This will have the added benefit of updating paths for asset items
   
   %module = AssetBrowser.dirHandler.getModuleFromAddress(AssetBrowser.dirHandler.currentAddress);
   %moduleId = %module.ModuleId;
   
   AssetDatabase.removeDeclaredAssets(%moduleId);
   
   %copiedSuccess = %this.dirHandler.copyDatablock(%fullPath, %basePath @ "/" @ %newFolderName);
   %this.dirHandler.deleteDatablock(%fullPath);
   
   %this.loadDirectories();
   
   AssetDatabase.addModuleDeclaredAssets(%moduleId);
}

function AssetBrowser::moveDatablock(%this, %folderPath, %newFolderPath)
{
   %fullPath = makeFullPath(%folderPath);
   %newFullPath = makeFullPath(%newFolderPath);
   
   %fullPath = strreplace(%fullPath, "//", "/");
   %newFullPath = strreplace(%newFullPath, "//", "/");
   
   %count = getTokenCount(%fullPath, "/");
   %basePath = getTokens(%fullPath, "/", 0, %count-2);
   %oldName = getToken(%fullPath, "/", %count-1);
   
   %copiedSuccess = %this.dirHandler.copyDatablock(%fullPath, %newFullPath);
   %this.dirHandler.deleteDatablock(%fullPath);
   
   %this.loadDirectories();
   
   //thrash the modules and reload them
   %oldModule = %this.dirHandler.getModuleFromAddress(%folderPath);
   %newModule = %this.dirHandler.getModuleFromAddress(%newFolderPath);
   
   //if we didn't move modules, then we don't need to do anything other than refresh the assets within it
   if(%oldModule == %newModule)
   {
      //only do a refresh to update asset loose file paths
      AssetDatabase.refreshAllAssets();
   }
   else
   {
      //they're different moduels now, so we gotta unload/reload both
      ModuleDatabase.unloadExplicit(%oldModule.getModuleId());
      ModuleDatabase.loadExplicit(%oldModule.getModuleId());
      
      ModuleDatabase.unloadExplicit(%newModule.getModuleId());
      ModuleDatabase.loadExplicit(%newModule.getModuleId());
   }
}

function AssetBrowser::deleteDatablock(%this, %folderPath)
{
   %this.dirHandler.deleteDatablock(%folderPath);
   
   %this.refresh();
}

function AssetBrowser::onDatablockEditorDropped(%this, %assetDef, %position)
{
   %targetPosition = EWorldEditor.unproject(%position SPC 1000);
   %camPos = LocalClientConnection.camera.getPosition();
   %rayResult = containerRayCast(%camPos, %targetPosition, -1);
   
   %pos = EWCreatorWindow.getCreateObjectPosition();

   if(%rayResult != 0)
   {
      %pos = getWords(%rayResult, 1, 3);
   }
   else
   {
      %pos = "0 0 0";  
   }
   
   %newObj = spawnDatablockObject(%assetDef);
   %newObj.position = %pos;
}