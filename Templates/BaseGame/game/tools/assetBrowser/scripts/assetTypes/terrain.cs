function AssetBrowser::createTerrainAsset(%this)
{
   %moduleName = AssetBrowser.newAssetSettings.moduleName;
   %modulePath = "data/" @ %moduleName;
      
   %assetName = AssetBrowser.newAssetSettings.assetName;      
   
   %assetType = AssetBrowser.newAssetSettings.assetType;
   %assetPath = AssetBrowser.dirHandler.currentAddress @ "/";   
   
   %tamlpath = %assetPath @ %assetName @ ".asset.taml";
   %terPath = %assetPath @ %assetName @ ".ter";
   
   %asset = new TerrainAsset()
   {
      AssetName = %assetName;
      versionId = 1;
      terrainFile = %assetName @ ".ter";
   };
   
   TamlWrite(%asset, %tamlpath);
   
   %moduleDef = ModuleDatabase.findModule(%moduleName, 1);
	AssetDatabase.addDeclaredAsset(%moduleDef, %tamlpath);

	AssetBrowser.loadFilters();
	
	AssetBrowserFilterTree.onSelect(%smItem);
	
	//Save out a basic terrain block here
	%terrBlock = new TerrainBlock() { terrainFile = %terPath; };
	%terrBlock.save(%terPath);
	%terrBlock.delete();
   
	return %tamlpath;
}

function AssetBrowser::editTerrainAsset(%this, %assetDef)
{
}

function AssetBrowser::duplicateTerrainAsset(%this, %assetDef, %targetModule)
{
}

function AssetBrowser::importTerrainAsset(%this, %assetDef)
{
}

function AssetBrowser::dragAndDropTerrainAsset(%this, %assetDef, %dropTarget)
{
   if(!isObject(%dropTarget))
      return;
}

function AssetBrowser::renameTerrainAsset(%this, %assetDef, %newAssetId, %originalName, %newName)
{
}

function AssetBrowser::deleteTerrainAsset(%this, %assetDef)
{
}

function AssetBrowser::buildTerrainAssetPreview(%this, %assetDef, %previewData)
{
   %previewData.assetName = %assetDef.assetName;
   %previewData.assetPath = "";
   %previewData.doubleClickCommand = "";
   
   %previewData.previewImage = "tools/assetBrowser/art/gameObjectIcon";
   
   %previewData.assetFriendlyName = %assetDef.gameObjectName;
   %previewData.assetDesc = %assetDef.description;
   %previewData.tooltip = %assetDef.gameObjectName;
}

function GuiInspectorTypeTerrainAssetPtr::onClick( %this, %fieldName )
{
   //Get our data
   %obj = %this.getInspector().getInspectObject(0);
}

function GuiInspectorTypeTerrainAssetPtr::onControlDropped( %this, %payload, %position )
{
   
}