function AssetBrowser::prepareImportSpriteAsset(%this, %assetItem)
{
   %assetItem.processed = true;
   
   refreshImportAssetWindow();
}

function AssetBrowser::inspectImportingSpriteAsset(%this, %assetItem)
{
}

function AssetBrowser::importSpriteAsset(%this, %assetItem)
{
   %moduleName = AssetImportTargetModule.getText();
   
   %assetType = %assetItem.AssetType;
   %filePath = %assetItem.filePath;
   %assetName = %assetItem.assetName;
   %assetImportSuccessful = false;
   %assetId = %moduleName@":"@%assetName;
   
   %assetPath = AssetBrowser.dirHandler.currentAddress @ "/";
   
   %assetFullPath = %assetPath @ "/" @ fileName(%filePath);
   
   %newAsset = new SpriteAsset()
   {
      assetName = %assetName;
      versionId = 1;
      imageFile = fileName(%filePath);
      originalFilePath = %filePath;
   };
   
   %assetImportSuccessful = TAMLWrite(%newAsset, %assetPath @ "/" @ %assetName @ ".asset.taml"); 
   
   //and copy the file into the relevent directory
   %doOverwrite = !AssetBrowser.isAssetReImport;
   if(!pathCopy(%filePath, %assetFullPath, %doOverwrite))
   {
      error("Unable to import asset: " @ %filePath);
      return;
   }
   
   %moduleDef = ModuleDatabase.findModule(%moduleName,1);
         
   if(!AssetBrowser.isAssetReImport)
      AssetDatabase.addDeclaredAsset(%moduleDef, %assetPath @ "/" @ %assetName @ ".asset.taml");
   else
      AssetDatabase.refreshAsset(%assetId);
}

function AssetBrowser::buildSpriteAssetPreview(%this, %assetDef, %previewData)
{
   %previewData.assetName = %assetDef.assetName;
   %previewData.assetPath = %assetDef.scriptFile;
   %imageFilePath = %assetDef.getSpriteFilename();
   
   if(isFile(%imageFilePath))
      %previewData.previewImage = %imageFilePath;
   else
      %previewData.previewImage = "core/rendering/images/unavailable";
  
   %previewData.assetFriendlyName = %assetDef.assetName;
   %previewData.assetDesc = %assetDef.description; 
   
   %info = %assetDef.getSpriteInfo();
   
   %previewData.tooltip = "Asset Name: " @ %assetDef.assetName @ "\n" @
      "Asset Type: Sprite Asset\n" @ 
      "Asset Definition ID: " @ %assetDef @ "\n" @
	  "Format: " @ getWord(%info, 0) @ "\n" @
      "Dimensions: " @ getWord(%info, 1) SPC "x" SPC getWord(%info, 2) @ "\n" @
	  "Frames: " @ getWord(%info,3) @ "\n" @
	  "Custom Frames: " @ getWord(%info,4);
}

//Renames the asset
function AssetBrowser::renameSpriteAsset(%this, %assetDef, %newAssetName)
{
   %newFilename = renameAssetLooseFile(%assetDef.spriteFile, %newAssetName);
   
   if(!%newFilename $= "")
      return;

   %assetDef.spriteFile = %newFilename;
   %assetDef.saveAsset();
   
   renameAssetFile(%assetDef, %newAssetName);
}

//Duplicates the asset
function AssetBrowser::duplicateSpriteAsset(%this, %assetDef, %newAssetName)
{
   %duplicatedAsset = duplicateAssetFile(%assetDef, %newAssetName);
   
   %newFilename = duplicateAssetLooseFile(%assetDef.spriteFile, %newAssetName);
   
   if(!%newFilename $= "")
      return;
      
   %module = AssetBrowser.dirHandler.getModuleFromAddress(%duplicatedAsset);
      
   %dupAssetDef = AssetDatabase.acquireAsset(%module.ModuleId @ ":" @ %newAssetName);

   %dupAssetDef.spriteFile = fileName(%newFilename);
   %dupAssetDef.saveAsset();
}

//Deletes the asset
function AssetBrowser::deleteSpriteAsset(%this, %assetDef)
{
   AssetDatabase.deleteAsset(%assetDef.getAssetId(), true);
}

//Moves the asset to a new path/module
function AssetBrowser::moveSpriteAsset(%this, %assetDef, %destination)
{
   %currentModule = AssetDatabase.getAssetModule(%assetDef.getAssetId());
   %targetModule = AssetBrowser.getModuleFromAddress(%destination);
   
   %newAssetPath = moveAssetFile(%assetDef, %destination);
   
   if(%newAssetPath $= "")
      return false;

   moveAssetLooseFile(%assetDef.spriteFile, %destination);
   
   AssetDatabase.removeDeclaredAsset(%assetDef.getAssetId());
   AssetDatabase.addDeclaredAsset(%targetModule, %newAssetPath);
}

function GuiInspectorTypeSpriteAssetPtr::onControlDropped( %this, %payload, %position )
{
   Canvas.popDialog(EditorDragAndDropLayer);
   
   // Make sure this is a color swatch drag operation.
   if( !%payload.parentGroup.isInNamespaceHierarchy( "AssetPreviewControlType_AssetDrop" ) )
      return;

   %assetType = %payload.dragSourceControl.parentGroup.assetType;
   
   if(%assetType $= "SpriteAsset")
   {
      echo("DROPPED A IMAGE ON AN SPRITE ASSET COMPONENT FIELD!");  
   }
   
   EWorldEditor.isDirty = true;
}
