function AssetBrowser::createScriptAsset(%this)
{
   %moduleName = AssetBrowser.newAssetSettings.moduleName;
   %modulePath = "data/" @ %moduleName;
      
   %assetName = AssetBrowser.newAssetSettings.assetName;  
   
   %assetPath = AssetBrowser.dirHandler.currentAddress @ "/";    
   
   %tamlpath = %assetPath @ %assetName @ ".asset.taml";
   %scriptPath = %assetPath @ %assetName @ ".cs";
   
   %asset = new ScriptAsset()
   {
      AssetName = %assetName;
      versionId = 1;
      scriptFile = %assetName @ ".cs";
   };
   
   TamlWrite(%asset, %tamlpath);
   
   %moduleDef = ModuleDatabase.findModule(%moduleName, 1);
	AssetDatabase.addDeclaredAsset(%moduleDef, %tamlpath);
	
	%file = new FileObject();
   
   if(%file.openForWrite(%scriptPath))
	{
		%file.close();
	}
   
	return %tamlpath;
}

function AssetBrowser::editScriptAsset(%this, %assetDef)
{
   %scriptFile = %assetDef.scriptFile;
   
   EditorOpenFileInTorsion(makeFullPath(%scriptFile), 0);
}

function AssetBrowser::duplicateScriptAsset(%this, %assetDef, %targetModule)
{
}

function AssetBrowser::importScriptAsset(%this, %assetId)
{
}

function AssetBrowser::onScriptAssetEditorDropped(%this, %assetDef, %position)
{
   if(!isObject(%dropTarget))
      return;
}

function AssetBrowser::renameScriptAsset(%this, %assetDef, %newAssetName)
{
   %assetId = %assetDef.getAssetID();
   
   %module = AssetDatabase.getAssetModule(%assetId);
   
   %scriptPath = %assetDef.scriptFile;
   %newScriptPath = filePath(%scriptPath) @ "/" @ %newAssetName @ fileExt(%scriptPath);
   %copiedSuccess = pathCopy(%scriptPath, %newScriptPath);
   
   %looseFilepath = fileName(%newScriptPath);
   
   %assetDef.scriptFile = "\"@AssetFile=" @ %looseFilepath @ "\"";
   %assetDef.saveAsset();
   
   AssetDatabase.renameDeclaredAsset("\"" @ %module @ ":" @ %newAssetName @ "\"");
   
   //%assetFilePath = makeFullPath(AssetDatabase.getAssetFilePath(%assetId));
   //%newAssetFilePath = %newFullPath @ "/" @ fileName(%assetFilePath);
   //%copiedSuccess = pathCopy(%assetFilePath, %newAssetFilePath);
   
   fileDelete(%scriptPath);
   
   //ModuleDatabase.unloadExplicit(%module.getModuleId());
   //ModuleDatabase.loadExplicit(%module.getModuleId());
}

function AssetBrowser::deleteScriptAsset(%this, %assetDef)
{
   %assetId = %assetDef.getAssetID();
   
   %module = AssetDatabase.getAssetModule(%assetId);
   
   %assetFilePath = makeFullPath(AssetDatabase.getAssetFilePath(%assetId));
   %scriptPath = %assetDef.scriptFile;
   
   fileDelete(%assetFilePath);
   fileDelete(%scriptPath);
   
   //they're different moduels now, so we gotta unload/reload both
   ModuleDatabase.unloadExplicit(%module.getModuleId());
   ModuleDatabase.unloadExplicit(%newModule.getModuleId());
}

function AssetBrowser::moveScriptAsset(%this, %assetDef, %destination)
{
   %newFullPath = makeFullPath(%destination);
   
   %assetId = %assetDef.getAssetID();
   
   %module = AssetDatabase.getAssetModule(%assetId);
   
   %assetFilePath = makeFullPath(AssetDatabase.getAssetFilePath(%assetId));
   %newAssetFilePath = %newFullPath @ "/" @ fileName(%assetFilePath);
   %copiedSuccess = pathCopy(%assetFilePath, %newAssetFilePath);
   
   %scriptPath = %assetDef.scriptFile;
   %newScriptPath = %newFullPath @ "/" @ fileName(%scriptPath);
   %copiedSuccess = pathCopy(%scriptPath, %newScriptPath);
   
   fileDelete(%assetFilePath);
   fileDelete(%scriptPath);
   
   //thrash the modules and reload them
   %newModule = %this.dirHandler.getModuleFromAddress(%newFullPath);
   
   //if we didn't move modules, then we don't need to do anything other than refresh the assets within it
   if(%module == %newModule)
   {
      //only do a refresh to update asset loose file paths
      AssetDatabase.refreshAllAssets();
   }
   else
   {
      //they're different moduels now, so we gotta unload/reload both
      ModuleDatabase.unloadExplicit(%module.getModuleId());
      ModuleDatabase.loadExplicit(%module.getModuleId());
      
      ModuleDatabase.unloadExplicit(%newModule.getModuleId());
      ModuleDatabase.loadExplicit(%newModule.getModuleId());
   }
}

function AssetBrowser::buildScriptAssetPreview(%this, %assetDef, %previewData)
{
   %previewData.assetName = %assetDef.assetName;
   %previewData.assetPath = %assetDef.scriptFile;
   %previewData.doubleClickCommand = "EditorOpenFileInTorsion( \""@%previewData.assetPath@"\", 0 );";
   
   if(%assetDef.isServerSide)
      %previewData.previewImage = "tools/assetBrowser/art/serverScriptIcon";
   else
      %previewData.previewImage = "tools/assetBrowser/art/clientScriptIcon";
   
   %previewData.assetFriendlyName = %assetDef.assetName;
   %previewData.assetDesc = %assetDef.description;
   %previewData.tooltip = %assetDef.assetName;
}

function GuiInspectorTypeScriptAssetPtr::onClick( %this, %fieldName )
{
   //Get our data
   %obj = %this.getInspector().getInspectObject(0);
}