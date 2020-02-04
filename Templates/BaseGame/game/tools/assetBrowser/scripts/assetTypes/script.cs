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

//Renames the asset
function AssetBrowser::renameScriptAsset(%this, %assetDef, %newAssetName)
{
   %newFilename = renameAssetLooseFile(%assetDef.scriptFile, %newAssetName);
   
   if(!%newFilename $= "")
      return;

   %assetDef.scriptFile = %newFilename;
   %assetDef.saveAsset();
   
   renameAssetFile(%assetDef, %newAssetName);
}

//Deletes the asset
function AssetBrowser::deleteScriptAsset(%this, %assetDef)
{
   AssetDatabase.deleteAsset(%assetDef.getAssetId(), true);
}

//Moves the asset to a new path/module
function AssetBrowser::moveScriptAsset(%this, %assetDef, %destination)
{
   %currentModule = AssetDatabase.getAssetModule(%assetDef.getAssetId());
   %targetModule = AssetBrowser.getModuleFromAddress(%destination);
   
   %newAssetPath = moveAssetFile(%assetDef, %destination);
   
   if(%newAssetPath $= "")
      return false;

   moveAssetLooseFile(%assetDef.scriptFile, %destination);
   
   AssetDatabase.removeDeclaredAsset(%assetDef.getAssetId());
   AssetDatabase.addDeclaredAsset(%targetModule, %newAssetPath);
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