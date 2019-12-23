function AssetBrowser::build_AssetPreview(%this, %assetDef, %previewData)
{
   %previewData.assetName = %assetDef.assetName;
   %previewData.assetPath = "";
   %previewData.doubleClickCommand = "";
   
   %previewData.previewImage = "tools/assetBrowser/art/gameObjectIcon";
   
   %previewData.assetFriendlyName = %assetDef.gameObjectName;
   %previewData.assetDesc = %assetDef.description;
   %previewData.tooltip = %assetDef.gameObjectName;
}

function AssetBrowser::prepareImport_Asset(%this, %assetItem)
{
   
}

function AssetBrowser::setupCreateNew_Asset(%this)
{
}

function AssetBrowser::create_Asset(%this)
{
}

function AssetBrowser::import_Asset(%this, %assetDef)
{
}

function AssetBrowser::edit_Asset(%this, %assetDef)
{
}

function AssetBrowser::duplicate_Asset(%this, %assetDef, %targetModule)
{
}

function AssetBrowser::rename_Asset(%this, %assetDef, %newAssetName)
{
}

function AssetBrowser::delete_Asset(%this, %assetDef)
{
}

function AssetBrowser::move_Asset(%this, %assetDef, %destinationFolder)
{
}

function AssetBrowser::dragAndDrop_Asset(%this, %assetDef, %dropTarget)
{
   if(!isObject(%dropTarget))
      return;
}

function AssetBrowser::on_AssetEditorDropped(%this, %assetDef, %position)
{
}

function GuiInspectorType_AssetPtr::onClick( %this, %fieldName )
{
   //Get our data
   %obj = %this.getInspector().getInspectObject(0);
}

function GuiInspectorType_AssetPtr::onControlDropped( %this, %payload, %position )
{
   
}