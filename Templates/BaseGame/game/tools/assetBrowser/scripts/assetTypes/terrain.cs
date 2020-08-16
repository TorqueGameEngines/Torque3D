function AssetBrowser::setupCreateNewTerrainAsset(%this)
{
   NewAssetPropertiesInspector.startGroup("Terrain");
   NewAssetPropertiesInspector.addField("resolution", "Terrain Texture Resolution", "list",  "Is this script used on the server?", "1024", "256,512,1024,2048,4096", %this.newAssetSettings);
   NewAssetPropertiesInspector.addField("genWithNoise", "Generate Terrain With Noise", "bool",  "Is this script used on the server?", "0", "2", %this.newAssetSettings);
   NewAssetPropertiesInspector.endGroup();
}

function AssetBrowser::createTerrainAsset(%this)
{
   %moduleName = AssetBrowser.newAssetSettings.moduleName;
   %modulePath = "data/" @ %moduleName;
      
   %assetName = AssetBrowser.newAssetSettings.assetName;      
   
   %assetType = AssetBrowser.newAssetSettings.assetType;
   %assetPath = AssetBrowser.dirHandler.currentAddress @ "/";  
   
   //Ensure anything we generate goes into the right directory
   $pref::Directories::Terrain = %assetPath;
   
   %tamlpath = %assetPath @ %assetName @ ".asset.taml";
   %terPath = %assetPath @ %assetName @ ".ter";
   
   %asset = new TerrainAsset()
   {
      AssetName = %assetName;
      versionId = 1;
      terrainFile = %assetName @ ".ter";
      resolution = %this.newAssetSettings.resolution;
      genWithNoise = %this.newAssetSettings.genWithNoise;
   };
   
   TamlWrite(%asset, %tamlpath);
   
   %moduleDef = ModuleDatabase.findModule(%moduleName, 1);
	AssetDatabase.addDeclaredAsset(%moduleDef, %tamlpath);

	AssetBrowser.refresh();
	
	//
	$createdTerrainBlock = TerrainBlock::createNew( %assetName, %this.newAssetSettings.resolution, "", %this.newAssetSettings.genWithNoise );
	
	$createdTerrainBlock.terrainAsset = %moduleName @ ":" @ %assetName;
	$createdTerrainBlock.terrainFile = "";
   
	return %tamlpath;
}

//Called if we create the terrain asset as a launch-prompt action of any of the editors
function createTerrainBlock(%assetId)
{
   %assetDef = AssetDatabase.acquireAsset(%assetId);
   
   if( %assetDef.genWithNoise )
      ETerrainEditor.isDirty = true;
      
   if(!isObject($createdTerrainBlock))
   {
      $createdTerrainBlock = new TerrainBlock() { terrainAsset = %assetId; };  
      //$createdTerrainBlock = new TerrainBlock() { terrainFile = %assetDef.terrainFile; };  
   }

   if( isObject( $createdTerrainBlock ) )
   {
      getRootScene().add($createdTerrainBlock);
      
      // Submit an undo action. 
      MECreateUndoAction::submit($createdTerrainBlock);
   
      assert( isObject( EWorldEditor ), 
         "ObjectBuilderGui::processNewObject - EWorldEditor is missing!" );

      // Select it in the editor.
      EWorldEditor.clearSelection();
      EWorldEditor.selectObject($createdTerrainBlock);

      // When we drop the selection don't store undo
      // state for it... the creation deals with it.
      EWorldEditor.dropSelection( true );
   }
   else
   {
      
   }
   //
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
   %previewData.tooltip = "Asset Name: " @ %assetDef.assetName @ "\n" @
      "Asset Type: Terrain Asset\n" @ 
      "Asset Definition ID: " @ %assetDef; 
}

function GuiInspectorTypeTerrainAssetPtr::onClick( %this, %fieldName )
{
   //Get our data
   %obj = %this.getInspector().getInspectObject(0);
}

function GuiInspectorTypeTerrainAssetPtr::onControlDropped( %this, %payload, %position )
{
   
}