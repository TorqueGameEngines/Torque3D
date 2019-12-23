function AssetBrowser::createTerrainMaterialAsset(%this)
{
   %moduleName = AssetBrowser.newAssetSettings.moduleName;
   %modulePath = "data/" @ %moduleName;
      
   %assetName = AssetBrowser.newAssetSettings.assetName;      
   
   %assetType = AssetBrowser.newAssetSettings.assetType;
   %assetPath = AssetBrowser.dirHandler.currentAddress @ "/";    
   
   %tamlpath = %assetPath @ %assetName @ ".asset.taml";
   %scriptPath = %assetPath @ %assetName @ ".cs";
   
   %asset = new TerrainMaterialAsset()
   {
      AssetName = %assetName;
      versionId = 1;
      scriptFile = %assetName @ ".cs";
      materialDefinitionName = %assetName;
   };
   
   TamlWrite(%asset, %tamlpath);
   
   %moduleDef = ModuleDatabase.findModule(%moduleName, 1);
	AssetDatabase.addDeclaredAsset(%moduleDef, %tamlpath);
	
	AssetDatabase.acquireAsset("\"" @ %moduleName @ ":" @ %assetName @ "\"");

	AssetBrowser.refresh();
	
	//AssetBrowserFilterTree.onSelect(%smItem);
	
	%file = new FileObject();
	%templateFile = new FileObject();
	
	%templateFilePath = %this.templateFilesPath @ "terrainMaterial.cs.template";
   
   if(%file.openForWrite(%scriptPath) && %templateFile.openForRead(%templateFilePath))
   {
      while( !%templateFile.isEOF() )
      {
         %line = %templateFile.readline();
         %line = strreplace( %line, "@", %assetName );
         
         %file.writeline(%line);
         //echo(%line);
      }
      
      %file.close();
      %templateFile.close();
   }
   else
   {
      %file.close();
      %templateFile.close();
      
      warnf("CreateNewTerrainMaterialAsset - Something went wrong and we couldn't write thescript file!");
   }
   
   //If we've got the terrain mat editor open, go ahead and update it all
   TerrainMaterialDlg.onWake();
   
	return %tamlpath;
}

function AssetBrowser::editTerrainMaterialAsset(%this, %assetDef)
{
   TerrainMaterialDlg.show(0, 0, 0);
   TerrainMaterialDlg.setActiveMaterial(%assetDef.assetName);
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
   
   %previewData.previewImage = "tools/assetBrowser/art/terrainMaterialIcon";
   
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