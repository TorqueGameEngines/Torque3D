
//Builds the preview data of the asset for the Asset Browser
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

//Some last-step setup for the creation of the new asset before we do the actual making
//This is generally intended to just set up any type-specific fields for creation
function AssetBrowser::setupCreateNew_Asset(%this)
{
}

//Performs the actual creation of the asset, including loose file copy or generation
function AssetBrowser::create_Asset(%this)
{
}

//This is a pre-process step to prepare the asset item for import
function AssetBrowser::prepareImport_Asset(%this, %assetItem)
{
   
}

//Performs the action of actually importing the asset item
function AssetBrowser::import_Asset(%this, %assetDef)
{
}

//Editing the asset
function AssetBrowser::edit_Asset(%this, %assetDef)
{
}

//Duplicates the asset
function AssetBrowser::duplicate_Asset(%this, %assetDef, %targetModule)
{
}

//Renames the asset
function AssetBrowser::rename_Asset(%this, %assetDef, %newAssetName)
{
}

//Deletes the asset
function AssetBrowser::delete_Asset(%this, %assetDef)
{
}

//Moves the asset to a new path/module
function AssetBrowser::move_Asset(%this, %assetDef, %destinationFolder)
{
}

//Drag and drop action onto a GUI control
function AssetBrowser::dragAndDrop_Asset(%this, %assetDef, %dropTarget)
{
   if(!isObject(%dropTarget))
      return;
}

//Even for when 
function AssetBrowser::on_AssetEditorDropped(%this, %assetDef, %position)
{
}

//Clicking of the button for the asset type inspector field
function GuiInspectorType_AssetPtr::onClick( %this, %fieldName )
{
   //Get our data
   %obj = %this.getInspector().getInspectObject(0);
}

//Drag and droppin onto the asset type inspector field
function GuiInspectorType_AssetPtr::onControlDropped( %this, %payload, %position )
{
   
}