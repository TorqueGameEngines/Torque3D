function AssetBrowser::setupCreateNewLevelAsset(%this)
{
   NewAssetPropertiesInspector.startGroup("Level");
   NewAssetPropertiesInspector.addField("LevelName", "Level Name", "String",  "Human-readable name of new level", "", "", %this.newAssetSettings);
   NewAssetPropertiesInspector.addField("levelPreviewImage", "Level Preview Image", "Image",  "Preview Image for the level", "", "", %this.newAssetSettings);

   NewAssetPropertiesInspector.endGroup();
}

function AssetImporter::importLevelAsset(%this, %assetItem)
{
}

function AssetBrowser::createLevelAsset(%this)
{
   %moduleName = AssetBrowser.newAssetSettings.moduleName;
   %modulePath = "data/" @ %moduleName;
   
   %assetName = AssetBrowser.newAssetSettings.assetName;
   
   %assetPath = AssetBrowser.dirHandler.currentAddress @ "/";
   
   %tamlpath = %assetPath @ %assetName @ ".asset.taml";
   %levelPath = %assetPath @ %assetName @ ".mis";
   
   %asset = new LevelAsset()
   {
      AssetName = %assetName;
      versionId = 1;
      LevelFile = %assetName @ ".mis";
      DecalsFile = %assetName @ ".mis.decals";
      PostFXPresetFile = %assetName @ ".postfxpreset.cs";
      ForestFile = %assetName @ ".forest";
      NavmeshFile = %assetName @ ".nav";
      LevelName = AssetBrowser.newAssetSettings.levelName;
      AssetDescription = AssetBrowser.newAssetSettings.description;
      PreviewImage = AssetBrowser.newAssetSettings.levelPreviewImage;
   };
   
   TamlWrite(%asset, %tamlpath);
   
   //Special-case where if we're doing a save-as action, it'll base on the current scene.
   //Otherwise we're doing a basic create action, so just base it off our editor's default
   if(EditorGui.saveAs)
   {
      getRootScene().save(%levelPath);
   }
   else if(!pathCopy("tools/levels/DefaultEditorLevel.mis", %levelPath, false))
   {
      echo("Unable to copy template level file!");
   }
   
   replaceInFile(%levelPath, "EditorTemplateLevel", %assetName);
   
   //Generate the associated files
   DecalManagerSave( %assetPath @ %asset.DecalsFile );
   PostFXManager::savePresetHandler( %assetPath @ %asset.PostFXPresetFile );

	%moduleDef = ModuleDatabase.findModule(%moduleName, 1);
	%addSuccess = AssetDatabase.addDeclaredAsset(%moduleDef, %tamlpath);

	AssetBrowser.refresh();
	
	%treeItemId = AssetBrowserFilterTree.findItemByName(%moduleName);
	%smItem = AssetBrowserFilterTree.findChildItemByName(%treeItemId, "Levels");
	
	AssetBrowserFilterTree.onSelect(%smItem);
	
	return %tamlpath;  
}

function AssetBrowser::editLevelAsset(%this, %assetDef)
{
   schedule( 1, 0, "EditorOpenMission", %assetDef);
}

//Renames the asset
function AssetBrowser::renameLevelAsset(%this, %assetDef, %newAssetName)
{
   %newFilename = renameAssetLooseFile(%assetDef.LevelFile, %newAssetName);
   
   if(!%newFilename $= "")
      return;
      
   //TODO the other loose files
      
   %assetDef.LevelFile = %newFilename;
   %assetDef.saveAsset();
   
   renameAssetFile(%assetDef, %newAssetName);
}

//Duplicates the asset
function AssetBrowser::duplicateLevelAsset(%this, %assetDef, %newAssetName)
{
   %duplicatedAsset = duplicateAssetFile(%assetDef, %newAssetName);
   
   %newFilename = duplicateAssetLooseFile(%assetDef.LevelFile, %newAssetName);
   
   if(!%newFilename $= "")
      return;
      
   %module = AssetBrowser.dirHandler.getModuleFromAddress(%duplicatedAsset);
      
   %dupAssetDef = AssetDatabase.acquireAsset(%module.ModuleId @ ":" @ %newAssetName);

   %dupAssetDef.LevelFile = fileName(%newFilename);
   %dupAssetDef.saveAsset();
}

//Deletes the asset
function AssetBrowser::deleteLevelAsset(%this, %assetDef)
{
   AssetDatabase.deleteAsset(%assetDef.getAssetId(), true);
}

//Moves the asset to a new path/module
function AssetBrowser::moveLevelAsset(%this, %assetDef, %destination)
{
   %currentModule = AssetDatabase.getAssetModule(%assetDef.getAssetId());
   %targetModule = AssetBrowser.getModuleFromAddress(%destination);
   
   %newAssetPath = moveAssetFile(%assetDef, %destination);
   
   if(%newAssetPath $= "")
      return false;

   moveAssetLooseFile(%assetDef.LevelFile, %destination);
   
   AssetDatabase.removeDeclaredAsset(%assetDef.getAssetId());
   AssetDatabase.addDeclaredAsset(%targetModule, %newAssetPath);
}
   
function AssetBrowser::buildLevelAssetPreview(%this, %assetDef, %previewData)
{
   %previewData.assetName = %assetDef.assetName;
   %previewData.assetPath = %assetDef.getLevelPath();
   %previewData.doubleClickCommand = "schedule( 1, 0, \"EditorOpenMission\", "@%assetDef@");";
   
   %levelPreviewImage = %assetDesc.PreviewImage;
         
   if(isFile(%levelPreviewImage))
      %previewData.previewImage = %levelPreviewImage;
   else
      %previewData.previewImage = "tools/assetBrowser/art/levelIcon";
   
   %previewData.assetFriendlyName = %assetDef.assetName;
   %previewData.assetDesc = %assetDef.description;
   %previewData.tooltip = "Asset Name: " @ %assetDef.assetName @ "\n" @
      "Asset Type: Level Asset\n" @ 
      "Asset Definition ID: " @ %assetDef @ "\n" @ 
      "Level File path: " @ %assetDef.getLevelPath(); 
}