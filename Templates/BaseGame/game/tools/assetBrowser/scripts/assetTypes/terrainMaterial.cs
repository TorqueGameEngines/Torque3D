function AssetBrowser::createTerrainMaterialAsset(%this)
{
}

function AssetBrowser::editTerrainMaterialAsset(%this, %assetDef)
{
}

function AssetBrowser::duplicateTerrainMaterialAsset(%this, %assetDef, %targetModule)
{
}

function AssetBrowser::importTerrainMaterialAsset(%this, %assetDef)
{
}

function AssetBrowser::dragAndDropTerrainMaterialAsset(%this, %assetDef, %dropTarget)
{
   if(!isObject(%dropTarget))
      return;
}

function AssetBrowser::renameTerrainMaterialAsset(%this, %assetDef, %newAssetId, %originalName, %newName)
{
}

function AssetBrowser::deleteTerrainMaterialAsset(%this, %assetDef)
{
}

function AssetBrowser::buildTerrainMaterialAssetPreview(%this, %assetDef, %previewData)
{
   %previewData.assetName = %assetDef.assetName;
   %previewData.assetPath = "";
   %previewData.doubleClickCommand = "";
   
   %previewData.previewImage = "tools/assetBrowser/art/gameObjectIcon";
   
   %previewData.assetFriendlyName = %assetDef.gameObjectName;
   %previewData.assetDesc = %assetDef.description;
   %previewData.tooltip = %assetDef.gameObjectName;
}

function GuiInspectorTypeTerrainMaterialAssetPtr::onClick( %this, %fieldName )
{
   //Get our data
   %obj = %this.getInspector().getInspectObject(0);
}

function GuiInspectorTypeTerrainMaterialAssetPtr::onControlDropped( %this, %payload, %position )
{
   
}