function AssetBrowser::buildFolderPreview(%this, %assetDef, %previewData)
{
   %previewData.assetName = %assetDef.assetName;
   %previewData.assetPath = %assetDef.dirPath;
   
   //%previewData.previewImage = "tools/assetBrowser/art/folderIcon";
   %previewData.previewImage = "tools/gui/images/folder";
   
   //%previewData.assetFriendlyName = %assetDef.assetName;
   %previewData.assetDesc = %assetDef.description;
   %previewData.tooltip = %assetDef.dirPath;
   %previewData.doubleClickCommand = "AssetBrowser.navigateTo(\""@ %assetDef.dirPath @ "/" @ %assetDef.assetName @"\")";//browseTo %assetDef.dirPath / %assetDef.assetName
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
   
   %module = AssetBrowser.getModuleFromAddress(AssetBrowser.currentAddress);
   %moduleId = %module.ModuleId;
   
   AssetDatabase.removeDeclaredAssets(%moduleId);
   
   %copiedSuccess = pathCopy(%fullPath, %basePath @ "/" @ %newFolderName);
   %this.deleteFolder(%fullPath);
   
   AssetDatabase.addModuleDeclaredAssets(%moduleId);
}

function AssetBrowser::deleteFolder(%this, %folderPath)
{
   doDeleteFolder(%folderPath);
   
   %this.loadFilters();
}

function doDeleteFolder(%folderPath)
{
   %fullPath = makeFullPath(%folderPath);
   
   //First, wipe out any files inside the folder first
   %file = findFirstFileMultiExpr( %fullPath @ "/*.*", true);

   while( %file !$= "" )
   {      
      %success = fileDelete( %file );
      
      if(!%success)
      {
         error("doDeleteFolder - unable to delete file " @ %file);
         return;         
      }
      
      %file = findNextFileMultiExpr( %fullPath @ "/*.*" );
   }
   
   //next, walk through and delete any subfolders that may be remaining
   while(fileDelete(%fullPath) == 0)
   {
      //We couldn't delete the folder, so get a directory list and recurse through it, deleteing them as we go
      %paths = getDirectoryList(%fullPath);
      for(%i=0; %i < getFieldCount(%paths); %i++)
      {
         %childPath = getField(%paths, %i);
         doDeleteFolder(%fullPath @ "/" @ %childPath);
      }
   }  
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
   
   %copiedSuccess = pathCopy(%fullPath, %newFullPath @ "/" @ %newFolderName);
   %this.deleteFolder(%fullPath);
}