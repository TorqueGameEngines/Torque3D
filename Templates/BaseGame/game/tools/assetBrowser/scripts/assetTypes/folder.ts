function AssetBrowser::createNewFolder(%this)
{
   AssetBrowser_newFolderNameTxt.text = "NewFolder";
   Canvas.pushDialog(AssetBrowser_newFolder);
}

function AssetBrowser::doCreateNewFolder(%this)
{
   %newFolderName = AssetBrowser_newFolderNameTxt.getText();
   
   if(%newFolderName $= "")
      %newFolderName = "NewFolder";
      
   if(SelectAssetPath.isAwake())
   {
      %currentAddressPath = SelectAssetPath-->folderTree.getItemValue(SelectAssetPath.selectedTreeItem) @ "/" @ SelectAssetPath-->folderTree.getItemText(SelectAssetPath.selectedTreeItem);
   }
   else
   {
      %currentAddressPath = AssetBrowser.dirHandler.currentAddress;
   }
      
   %newFolderIdx = "";
   %matched = true;
   %newFolderPath = "";
   while(%matched == true)
   {
      %newFolderPath = %currentAddressPath @ "/" @ %newFolderName @ %newFolderIdx;
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
   
   //On the off chance we're trying to select a path, we'll update the select path window too
   if(SelectAssetPath.isAwake())
      SelectAssetPath.showDialog(%newFolderPath, SelectAssetPath.callback);
}

function AssetBrowser::buildFolderPreview(%this, %assetDef, %previewData)
{
   %previewData.assetName = %assetDef.assetName;
   %previewData.assetPath = %assetDef.dirPath;
   
   %previewData.previewImage = "tools/assetBrowser/art/folderIcon";
   
   //%previewData.assetFriendlyName = %assetDef.assetName;
   %previewData.assetDesc = %assetDef.description;
   %previewData.tooltip = %assetDef.dirPath;
   %previewData.doubleClickCommand = "AssetBrowser.schedule(10, \"navigateTo\",\""@ %assetDef.dirPath @ "/" @ %assetDef.assetName @"\");";//browseTo %assetDef.dirPath / %assetDef.assetName
}

function AssetBrowser::renameFolder(%this, %folderPath, %newFolderName)
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
   
   %copiedSuccess = %this.dirHandler.copyFolder(%fullPath, %basePath @ "/" @ %newFolderName);
   %this.dirHandler.deleteFolder(%fullPath);
   
   %this.loadDirectories();
   
   AssetDatabase.addModuleDeclaredAssets(%moduleId);
}

function AssetBrowser::moveFolder(%this, %folderPath, %newFolderPath)
{
   %fullPath = makeFullPath(%folderPath);
   %newFullPath = makeFullPath(%newFolderPath);
   
   %fullPath = strreplace(%fullPath, "//", "/");
   %newFullPath = strreplace(%newFullPath, "//", "/");
   
   %count = getTokenCount(%fullPath, "/");
   %basePath = getTokens(%fullPath, "/", 0, %count-2);
   %oldName = getToken(%fullPath, "/", %count-1);
   
   %copiedSuccess = %this.dirHandler.copyFolder(%fullPath, %newFullPath);
   %this.dirHandler.deleteFolder(%fullPath);
   
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

function AssetBrowser::deleteFolder(%this, %folderPath)
{
   %this.dirHandler.deleteFolder(%folderPath);
   
   %this.refresh();
}