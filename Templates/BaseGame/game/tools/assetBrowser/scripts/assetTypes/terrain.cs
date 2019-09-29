function AssetBrowser::createTerrainAsset(%this)
{
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