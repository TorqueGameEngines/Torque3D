function AssetBrowser::createTerrainAsset(%this)
{
   %moduleName = AssetBrowser.newAssetSettings.moduleName;
   %modulePath = "data/" @ %moduleName;
      
   %assetName = AssetBrowser.newAssetSettings.assetName;      
   
   %assetType = AssetBrowser.newAssetSettings.assetType;
   %assetPath = AssetBrowser.currentAddress @ "/";   
   
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

//AssetDatabase.acquireAsset("pbr:NewTerrain");
function TerrainAsset::saveAsset(%this)
{
   %matDepIdx = 0;
   while(%this.getFieldValue("terrainMaterialAsset", %matDepIdx) !$= "")
   {
      %this.setFieldValue("terrainMaterialAsset", "", %matDepIdx);
   }
   
   %filePath = AssetDatabase.getAssetFilePath(%this.getAssetId());
   
   %mats = ETerrainEditor.getMaterials();
   
   %assetQuery = new AssetQuery();
   AssetDatabase.findAssetType(%assetQuery, "TerrainMaterialAsset");
        
   %count = %assetQuery.getCount();
      
   %matDepIdx = 0;
   for( %i = 0; %i < getRecordCount( %mats ); %i++ )
   {
      %matInternalName = getRecord( %mats, %i );
      
      for(%m=0; %m < %count; %m++)
      {
         %assetId = %assetQuery.getAsset(%m);
         
         %terrMatAssetDef = AssetDatabase.acquireAsset(%assetId);
         
         if(%terrMatAssetDef.materialDefinitionName $= %matInternalName)
         {
            %this.setFieldValue("terrainMaterialAsset", "@Asset=" @ %assetId, %matDepIdx); 
            %matDepIdx++;
         }
      }	
   }
	%assetQuery.delete();	  
   
   TAMLWrite(%this, %filePath);
}