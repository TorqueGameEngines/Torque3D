new SimGroup(AssetBrowserPreviewCache);

//AssetBrowser.addToolbarButton
function AssetBrowser::addToolbarButton(%this)
{
	%filename = expandFilename("tools/gui/images/stencilIcons/menuGrid");
	%button = new GuiBitmapButtonCtrl() {
		canSaveDynamicFields = "0";
		internalName = AssetBrowserBtn;
		Enabled = "1";
		isContainer = "0";
		Profile = "ToolsGuiButtonProfile";
		HorizSizing = "right";
		VertSizing = "bottom";
		position = "180 0";
		Extent = "25 19";
		MinExtent = "8 2";
		canSave = "1";
		Visible = "1";
		Command = "AssetBrowser.ShowDialog();";
		tooltipprofile = "ToolsGuiToolTipProfile";
		ToolTip = "Asset Browser";
		hovertime = "750";
		bitmap = %filename;
		bitmapMode = "Stretched";
		buttonType = "PushButton";
		groupNum = "0";
		useMouseEvents = "0";
	};
	ToolsToolbarArray.add(%button);
	EWToolsToolbar.setExtent((25 + 8) * (ToolsToolbarArray.getCount()) + 12 SPC "33");
}
//
function AssetBrowser::onAdd(%this)
{
}

function AssetBrowser::onWake(%this)
{
   // manage preview array
   if(!isObject(AssetPreviewArray))
      new ArrayObject(AssetPreviewArray);
      
   if(!isObject(%this.dirHandler))
      %this.dirHandler = makedirectoryHandler(AssetBrowser-->filterTree, "cache,shaderCache", ""); 
      
   AssetBrowser-->filterTree.buildIconTable( ":tools/classIcons/Prefab:tools/classIcons/Prefab" @
                                             ":tools/classIcons/SimSet:tools/classIcons/SimSet");
      
   %this.isReImportingAsset = false;
   
   %this.coreModulesFilter = false;
   %this.toolsModulesFilter = false;
   %this.onlyShowModulesWithAssets = false;
   
   %this.folderPanelState = true;
   %this.folderPanelSplit = 0;
   
   %this.templateFilesPath = "tools/assetBrowser/scripts/templateFiles/";
   
   //First, build our our list of active modules
   %modulesList = ModuleDatabase.findModules(true);
   
   AssetBrowser-->previewSlider.setValue(EditorSettings.value("Assets/Browser/previewTileSize", "1.0"));
   
   AssetBrowser-->filterAssetsButton.setActive(true); 
}

function contentTreeTabBook::onTabSelected(%this, %tabText, %tabIndex)
{
   if(%tabText $= "Content")
   {
      //Force it to navigate to current active directory, which also rebuilds the
      //tree
      AssetBrowser.dirHandler.navigateTo(AssetBrowser.dirHandler.currentAddress);
   }
   else
   {
      AssetBrowser-->filterTree.clear();
      AssetBrowser-->filterTree.buildVisibleTree(true);
   }
}

//Filters
function AssetBrowser::showFilterPopup(%this)
{
   BrowserVisibilityPopup.showPopup(Canvas);
}

function AssetBrowser::viewCoreModulesFilter(%this)
{
   %oldVal = EditorSettings.value("Assets/Browser/showCoreModule", false);
   %newVal = !%oldVal;
   
   %this.coreModulesFilter = %newVal;
   
   BrowserVisibilityPopup.checkItem(0,%newVal);
   
   EditorSettings.setValue("Assets/Browser/showCoreModule", %newVal);
    
   AssetBrowser.loadDirectories();
}

function AssetBrowser::viewToolsModulesFilter(%this)
{
   %oldVal = EditorSettings.value("Assets/Browser/showToolsModule", false);
   %newVal = !%oldVal;
   
   %this.toolsModulesFilter = %newVal;
   
   BrowserVisibilityPopup.checkItem(1,%newVal);
   
   EditorSettings.setValue("Assets/Browser/showToolsModule", %newVal);
    
   AssetBrowser.loadDirectories();
}

function AssetBrowser::viewPopulatedModulesFilter(%this)
{
   %oldVal = EditorSettings.value("Assets/Browser/showOnlyPopulatedModule", false);
   %newVal = !%oldVal;
   
   BrowserVisibilityPopup.checkItem(2,%newVal);
   
   EditorSettings.setValue("Assets/Browser/showOnlyPopulatedModule", %newVal);
    
   AssetBrowser.loadDirectories();
}

function AssetBrowser::toggleShowingFolders(%this)
{
   %oldVal = EditorSettings.value("Assets/Browser/showFolders", false);
   %newVal = !%oldVal;
   
   BrowserVisibilityPopup.checkItem(4,%newVal);
   
   EditorSettings.setValue("Assets/Browser/showFolders", %newVal);
    
   AssetBrowser.loadDirectories();
}

function AssetBrowser::toggleShowingEmptyFolders(%this)
{
   %oldVal = EditorSettings.value("Assets/Browser/showEmptyFolders", false);
   %newVal = !%oldVal;
   
   BrowserVisibilityPopup.checkItem(5,%newVal);
   
   EditorSettings.setValue("Assets/Browser/showEmptyFolders", %newVal);
    
   AssetBrowser.refresh();
}

function AssetBrowser::toggleAssetTypeFilter(%this, %assetTypeIdx)
{
   %isChecked = AssetTypeListPopup.isItemChecked(%assetTypeIdx);
   
   //Clear existing filters
   if(%assetTypeIdx == 0)
   {
      for(%i=0; %i < AssetFilterTypeList.Count() + 1; %i++)
      {
         AssetTypeListPopup.checkItem(%i, false);  
      }
      
      AssetTypeListPopup.checkItem(0, true);
   }
   else
   {
      if(%isChecked)
      {
         %anyOtherFilters = false;
         for(%i=1; %i < AssetFilterTypeList.Count() + 1; %i++)
         {
            if(%assetTypeIdx == %i)
               continue;
               
            if(AssetTypeListPopup.isItemChecked(%i))
            {
               %anyOtherFilters = true;
               break;  
            }
         }
      }
      
      if(%isChecked && !%anyOtherFilters)
      {
         for(%i=0; %i < AssetFilterTypeList.Count() + 1; %i++)
         {
            AssetTypeListPopup.checkItem(%i, false);  
         }
      
         AssetTypeListPopup.checkItem(0, true);
      }
      else
      {
         AssetTypeListPopup.checkItem(0, false);
         AssetTypeListPopup.checkItem(%assetTypeIdx, !%isChecked);
      }
   }
   
   //Update the displayed search text!
   //First, clear out the old type search term
   for(%i=0; %i < AssetSearchTerms.count(); %i++)
   {
      %action = AssetSearchTerms.getKey(%i);

      if(%action $= "type")
      {
         AssetSearchTerms.erase(%i);
         %i--;
      }
   }
   
   //Update our search terms
   %newSearchPhrase = "";
   for(%i=0; %i < AssetFilterTypeList.Count() + 1; %i++)
   {
      %isChecked = AssetTypeListPopup.isItemChecked(%i);
      
      if(!%isChecked)
         continue;
      
      %itemText = AssetTypeListPopup.getItemText(%i);
      if(%itemText $= "All")
         continue;
         
      AssetSearchTerms.add("type", %itemText);
   }
   
   %this.updateSearchTextFromFilter();
   
   %this.rebuildAssetArray();
}

//
function AssetBrowser::selectAsset( %this, %asset )
{
   if(AssetBrowser.selectCallback !$= "")
   {
      // The callback function should be ready to intake the returned material
      //eval("materialEd_previewMaterial." @ %propertyField @ " = " @ %value @ ";");
      if( AssetBrowser.returnType $= "name" )
      {
         eval( "" @ AssetBrowser.selectCallback @ "(" @ %name  @ ");");
      }
      else
      {
         %command = "" @ AssetBrowser.selectCallback @ "(\"" @ %asset  @ "\");";
         eval(%command);
      }
   }
   else
   {
      //try just setting the asset
      %this.changeAsset();
   }
   
   Inspector.refresh();
   
   AssetBrowser.hideDialog();
}

function AssetBrowser::showDialog( %this, %AssetTypeFilter, %selectCallback, %targetObj, %fieldName, %returnType)
{
   // Set the select callback
   AssetBrowser.selectCallback = %selectCallback;
   AssetBrowser.returnType = %returnType;
   AssetBrowser.assetTypeFilter = %AssetTypeFilter;
   AssetBrowser.fieldTargetObject = %targetObj;
   AssetBrowser.fieldTargetName = %fieldName;

   Canvas.pushDialog(AssetBrowser);
   AssetBrowser.setVisible(1);
   AssetBrowserWindow.setVisible(1);
   AssetBrowserWindow.selectWindow();
   
   //If we're special-case filtering(like for selecting a given type), then ignore our normal
   //visibility filter
   if(%AssetTypeFilter !$= "")
   {
      AssetBrowser-->filterAssetsButton.setActive(false);
   }
   else
   {
      AssetBrowser-->filterAssetsButton.setActive(true);  
   }
   
   if(%selectCallback $= "")
   {
      //we're not in selection mode, so just hide the select button
      %this-->SelectButton.setHidden(true);  
      %this.selectMode = 0;
   }
   else
   {
      %this-->SelectButton.setHidden(false); 
      %this.selectMode = 1;
   }

   AssetBrowser.loadDirectories();
}

function AssetBrowser::hideDialog( %this )
{
   AssetBrowser.setVisible(1);
   AssetBrowserWindow.setVisible(1);
   Canvas.popDialog(AssetBrowser_addModule);
   Canvas.popDialog(ImportAssetWindow);
   
   Canvas.popDialog(AssetBrowser);
}

function AssetBrowser::buildAssetPreview( %this, %asset, %moduleName )
{
   if(!isObject(%this.previewData))
   {
      %this.previewData = new ScriptObject();      
   }
   
   AssetPreviewArray.empty();
   
   %previewImage = "core/art/warnmat";
   
   if(/*%moduleName !$= "" && */ModuleDatabase.findModule(%moduleName, 1) !$= "")
   {
      %assetDesc = AssetDatabase.acquireAsset(%asset);
      %assetName = AssetDatabase.getAssetName(%asset);
      %assetType = AssetDatabase.getAssetType(%asset);
   }
   else
   {
      //special-case entry
      if(getFieldCount(%asset) > 1)
      {
         %specialType = getField(%asset,0);
         
         /*if(%specialType $= "Folder")
         {
            
         }
         else if(%specialType $= "Datablock")
         {
            %sdfasdgah = true;  
         }*/
         %assetType = %specialType;
         %assetName = getField(%asset, 1);
         %sdfasdgah = true;  
         
         if(%assetType $= "Folder")
         {
            %fullPath = %moduleName !$= "" ? %moduleName @ "/" @ %assetName : %assetName;
            %fullPath = strreplace(%fullPath, "/", "_");
            
            if(isObject(%fullPath))
               %assetDesc = %fullPath;
            else
               %assetDesc = new ScriptObject(%fullPath);
               
            %assetDesc.dirPath = %moduleName;
            %assetDesc.assetName = %assetName;
            %assetDesc.description = %moduleName @ "/" @ %assetName;
            %assetDesc.assetType = %assetType;
         }
         else if(%assetType $= "Datablock")
         {
            %assetDesc = %assetName;
            %assetDesc.assetType = %assetType;
         }
         else if(%assetType $= "LooseFile")
         {
            %fullPath = %moduleName !$= "" ? %moduleName @ "/" @ %assetName : %assetName;
            %fullPath = strreplace(%fullPath, "/", "_");
            %fullPath = strreplace(%fullPath, ".", "-");
            
            if(isObject(%fullPath))
               %assetDesc = %fullPath;
            else
               %assetDesc = new ScriptObject(%fullPath);
               
            %assetDesc.dirPath = %moduleName;
            %assetDesc.assetName = %assetName;
            %assetDesc.description = %moduleName @ "/" @ %assetName;
            %assetDesc.assetType = %assetType;
         }
         else if(%assetType $= "Prefab")
         {
            %fullPath = %moduleName !$= "" ? %moduleName @ "/" @ %assetName : %assetName;
            %fullPath = strreplace(%fullPath, "/", "_");
            %fullPath = strreplace(%fullPath, ".", "-");
            
            if(isObject(%fullPath))
               %assetDesc = %fullPath;
            else
               %assetDesc = new ScriptObject(%fullPath);
               
            %assetDesc.dirPath = %moduleName;
            %assetDesc.assetName = %assetName;
            %assetDesc.description = %moduleName @ "/" @ %assetName;
            %assetDesc.assetType = %assetType;
         }
      }
      /*%fullPath = %moduleName !$= "" ? %moduleName @ "/" @ %assetName : %assetName;
      %fullPath = strreplace(%fullPath, "/", "_");
      
      if(isObject(%fullPath))
         %assetDesc = %fullPath;
      else
         %assetDesc = new ScriptObject(%fullPath);
         
      %assetDesc.dirPath = %moduleName;
      %assetDesc.assetName = %assetName;
      %assetDesc.description = %moduleName @ "/" @ %assetName;
      %assetDesc.assetType = %assetType;*/
      
      //%assetName = %asset;
      //%assetType = "Folder";
   }

   %previewSize = 100 SPC 100;
   %previewBounds = 20;
   
   %tooltip = %assetName;
   
   %doubleClickCommand = "AssetBrowser.editAsset( "@%assetDesc@" );";
   
   /*if(%assetType $= "ShapeAsset")
   {
      %previewButton = AssetPreviewButtonsTemplate-->ShapeAssetPreviewButton.deepClone();
   }
   else
   {
      %previewButton = AssetPreviewButtonsTemplate-->GeneralAssetPreviewButton.deepClone();
   }*/
   
   %textBottomPad = 20;
   
   %previewButton = new GuiIconButtonCtrl()
   {
      class = "AssetBrowserPreviewButton";
      useMouseEvents = true;
      iconLocation = "Center";
      sizeIconToButton = true;
      makeIconSquare = true;
      textLocation = "Bottom";
      extent = %previewSize.x SPC %previewSize.y + %textBottomPad;
      buttonType = "RadioButton";
      profile = ToolsGuiDefaultProfile;
   };
   
   %previewScaleSize = AssetBrowser-->previewSlider.getValue();
   
   if(%previewScaleSize $= "")
   {
      %previewScaleSize = 1;
      AssetBrowser-->previewSlider.setValue(1);
   }
   
   if(%previewScaleSize == 0)
   {
      %previewButton.iconLocation = "Left";
      %previewButton.textLocation = "Right";
      %previewButton.extent = "120 20";
   }
   else
   {
      %size = %previewSize.x * %previewScaleSize;
      %previewButton.extent.x = %size;
      %previewButton.extent.y = %size + %textBottomPad;
   }
   
   //%previewButton.extent = %previewSize.x + %previewBounds SPC %previewSize.y + %previewBounds + 24;
   %previewButton.assetName = %assetName;
   %previewButton.moduleName = %moduleName;
   %previewButton.assetType = %assetType;
   
   //Build out the preview
   %buildCommand = %this @ ".build" @ %assetType @ "Preview(\"" @ %assetDesc @ "\"," @ %this.previewData @ ");";
   eval(%buildCommand);
   
   //debug dump
   %tooltip = %this.previewData.tooltip;
   %assetName = %this.previewData.assetName;
   %previewImage = %this.previewData.previewImage;
   %doubleClickCommand = %this.previewData.doubleClickCommand;
   
   %previewButton.assetName = %assetName;
   %previewButton.moduleName = %moduleName;
   %previewButton.assetType = %assetType;
   
   %previewButton.iconBitmap = %this.previewData.previewImage;
   
   %previewButton.profile = "AssetBrowserPreview" @ %previewButton.assetType;
   %previewButton.tooltip = %this.previewData.tooltip;
   %previewButton.Command = "AssetBrowser.updateSelection( $ThisControl.assetName, $ThisControl.moduleName );";
   %previewButton.altCommand = %doubleClickCommand;
   
   %previewButton.text = %this.previewData.assetName;
   %previewButton.text.originalAssetName = %this.previewData.assetName;

   // add to the gui control array
   AssetBrowser-->assetList.add(%previewButton);
   
   // add to the array object for reference later
   AssetPreviewArray.add( %previewButton, %this.previewData.previewImage );
}

function AssetBrowser::refresh(%this)
{
   if(!%this.dirty)
   {
      %this.dirty = true;
      
      %this.schedule(1, "doRefresh");
   }
}

function AssetBrowser::doRefresh(%this)
{
   if(%this.dirty)
   {
      %this.navigateTo(%this.dirHandler.currentAddress);  
      
      //Forces a clean collapse of the tree for any not-really-exposed items
      %dataItem = AssetBrowser-->filterTree.findItemByName("Data");

      AssetBrowser-->filterTree.expandItem(%dataItem, false);
      AssetBrowser-->filterTree.expandItem(%dataItem);
      
      %this.dirty = false;
   }
}
//
//
/*function AssetPreviewButton::onClick(%this)
{
   echo("CLICKED AN ASSET PREVIEW BUTTON");
}

function AssetPreviewButton::onDoubleClick(%this)
{
   echo("DOUBLE CLICKED AN ASSET PREVIEW BUTTON");
}*/
//
//

function assetBrowserPreviewSlider::onMouseDragged(%this)
{
   EditorSettings.setValue("Assets/Browser/previewTileSize", %this.getValue());
   AssetBrowser.refresh();  
}

function AssetBrowser::loadDirectories( %this )
{
   AssetBrowser-->filterTree.clear();
   
   %dataItem = AssetBrowser-->filterTree.insertItem(0, "Content");
   AssetBrowser-->filterTree.collectionsIdx = AssetBrowser-->filterTree.insertItem(1, "Collections");
   
   AssetBrowser-->filterTree.modulesIdx = AssetBrowser-->filterTree.insertItem(1, "Modules");
   
   %dataItem = AssetBrowser-->filterTree.insertItem(AssetBrowser-->filterTree.modulesIdx, "Data");
   AssetBrowser-->filterTree.tagsIdx = AssetBrowser-->filterTree.insertItem(1, "Tags");
   AssetBrowser-->filterTree.creatorIdx = AssetBrowser-->filterTree.insertItem(1, "Creator");
   
   %this.dirHandler.loadFolders("Data", %dataItem);
   
   %this.loadCollectionSets();
   
   %this.loadTags();
   
   %this.loadCreatorClasses();
   
   //If set to, show core
   if(EditorSettings.value("Assets/Browser/showCoreModule", false) == 1)
   {
      %coreItem = AssetBrowser-->filterTree.insertItem(AssetBrowser-->filterTree.modulesIdx, "Core");
      %this.dirHandler.loadFolders("Core", %coreItem);
   }
   
   //If set to, show tools
   if(EditorSettings.value("Assets/Browser/showToolsModule", false) == 1)
   {
      %toolsItem = AssetBrowser-->filterTree.insertItem(AssetBrowser-->filterTree.modulesIdx, "Tools");
      %this.dirHandler.loadFolders("Tools", %toolsItem);
   }
   
   //Add Non-Asset Scripted Objects. Datablock, etc based
   /*%category = getWord( %breadcrumbPath, 1 );                  
   %dataGroup = "DataBlockGroup";
   
   if(%dataGroup.getCount() != 0)
   {
      %scriptedItem = AssetBrowser-->filterTree.insertItem(1, "Scripted");
      
      for ( %i = 0; %i < %dataGroup.getCount(); %i++ )
      {
         %obj = %dataGroup.getObject(%i);
         // echo ("Obj: " @ %obj.getName() @ " - " @ %obj.category );
         
         //if ( %obj.category $= "" && %obj.category == 0 )
         //   continue;
         
         %dbFilename = %obj.getFileName();
         %dbFilePath = filePath(%dbFilename);
         
         if(%breadcrumbPath $= %dbFilePath)
         {
         
         //if ( %breadcrumbPath $= "" )
         //{         
            %catItem = AssetBrowser-->filterTree.findItemByName(%obj.category);
            
            if(%catItem == 0)
               AssetBrowser-->filterTree.insertItem(%scriptedItem, %obj.category, "scripted");
            /*%ctrl = %this.findIconCtrl( %obj.category );
            if ( %ctrl == -1 )
            {
               %this.addFolderIcon( %obj.category );
            }*/
         //}
         /*else if ( %breadcrumbPath $= %obj.category )
         {            
            AssetBrowser-->filterTree.insertItem(%scriptedItem, %obj.getName());
         }*/
         //}
      //}
  // }
   
   AssetPreviewArray.empty();
   
   AssetBrowser-->filterTree.buildVisibleTree(true);
   
   //Remove any modules that have no assets if we have that filter on
   if(%this.onlyShowModulesWithAssets)
   {
      for(%i=0; %i < getWordCount(%modulesList); %i++)
      {
         %moduleName = getWord(%modulesList, %i).ModuleId;
         
         %moduleItemId = AssetBrowser-->filterTree.findItemByName(%moduleName);
         
         if(AssetBrowser-->filterTree.isParentItem(%moduleItemId) == false)
            AssetBrowser-->filterTree.removeItem(%moduleItemId);
      }
   }
  
   //special handling for selections
   if(AssetBrowser.newModuleId !$= "")
   {
      AssetBrowser-->filterTree.clearSelection();
      %newModuleItem = AssetBrowser-->filterTree.findItemByName(AssetBrowser.newModuleId);
      AssetBrowser-->filterTree.selectItem(%newModuleItem);
      AssetBrowser.newModuleId = ""; 
   }
   
   //%dataItem = AssetBrowser-->filterTree.findItemByName("Data");
   //AssetBrowser-->filterTree.expandItem(%dataItem);
   
   AssetBrowser.dirHandler.expandTreeToAddress(AssetBrowser.dirHandler.currentAddress);
   
   %selectedItem = AssetBrowser.dirHandler.getFolderTreeItemFromAddress(AssetBrowser.dirHandler.currentAddress);
   AssetBrowser-->filterTree.scrollVisibleByObjectId(%selectedItem);
   
   AssetBrowser-->filterTree.buildVisibleTree(true); 
   
   AssetBrowser.refresh();
}

function AssetBrowser::updateSelection( %this, %asset, %moduleName )
{
   /*%isAssetBorder = 0;
   eval("%isAssetBorder = isObject(AssetBrowser-->"@%asset@"Border);");
   if( %isAssetBorder )
   {
      eval( "AssetBrowser-->"@%asset@"Border.setStateOn(1);");
   }
      
   %isAssetBorderPrevious = 0;
   eval("%isAssetBorderPrevious = isObject(AssetBrowser-->"@%this.prevSelectedMaterialHL@"Border);");
   if( %isAssetBorderPrevious )
   {
      eval( "AssetBrowser-->"@%this.prevSelectedMaterialHL@"Border.setStateOn(0);");
   }*/
   
   //If we had an existing selected assetDef, clear the reference
   if(isObject(AssetBrowser.selectedAssetDef))
      AssetDatabase.releaseAsset(AssetBrowser.selectedAssetDef.getAssetId());
   
   //AssetBrowser.selectedMaterial = %asset;
   AssetBrowser.selectedAsset = %moduleName@":"@%asset;
   
   //If it's got slashes, it's a path so it's actually a folder item, not an asset
   if(strstr(%moduleName, "/") != -1)
      return;
      
   //Otherwise, it's an asset so we'll select the definition while we're at it
   AssetBrowser.selectedAssetDef = AssetDatabase.acquireAsset(AssetBrowser.selectedAsset);
   //AssetBrowser.selectedPreviewImagePath = %previewImagePath;
   
   //%this.prevSelectedMaterialHL = %asset;
}

function AssetBrowser::loadCollectionSets(%this)
{
   //Process any datablocks and populate their lists categories as tags as well
   %collectionsItem = AssetBrowser-->filterTree.collectionsIdx;
   
   %collectionsCount = AssetBrowserCollectionSets.value("CollectionSetCount", 0);
   
   for ( %i = 0; %i < %collectionsCount; %i++ )
   {
      %collection = AssetBrowserCollectionSets.value("Collection"@%i, "");
      %collectionName = getField(%collection, 0);
      %collectionTerm = getField(%collection, 1);
      
      AssetBrowser-->filterTree.insertItem(%collectionsItem, %collectionName, %collectionTerm);
   }
}

function AssetBrowser::setCollectionSetActive(%this, %collectionSet)
{
   AssetBrowserSearchFilter.setText(%collectionSet);
   AssetBrowserSearchFilter.onReturn();
}

function AssetBrowser::loadTags(%this)
{
   //Process any datablocks and populate their lists categories as tags as well
   %dataGroup = "DataBlockGroup";
   %tagItem = AssetBrowser-->filterTree.tagsIdx;
   
   for ( %i = 0; %i < %dataGroup.getCount(); %i++ )
   {
      %obj = %dataGroup.getObject(%i);
      // echo ("Obj: " @ %obj.getName() @ " - " @ %obj.category );
      
      if ( %obj.category $= "" && %obj.category == 0 )
         continue;
         
      %tagChildItem = AssetBrowser-->filterTree.findChildItemByName(%tagItem, %obj.category);
      if(%tagChildItem == 0)
      {
         //Didn't already exist, so register it in
         AssetBrowser-->filterTree.insertItem(%tagItem, %obj.category);
      }
   }
}

function AssetBrowser::setTagActive(%this, %tag)
{
   %found = false;
   
   for(%i=0; %i < AssetSearchTerms.count(); %i++)
   {
      %action = AssetSearchTerms.getKey(%i);
      %word = AssetSearchTerms.getValue(%i);
      
      if(%action $= "tag" && %word $= %tag)
      {
         //If we found it, we just remove it from our list, toggling it off
         AssetSearchTerms.erase(%i);
         %found = true;
      }
   }
   
   //If we didn't find it, we're going to add it into our list
   if(!%found)
   {
      AssetSearchTerms.add("tag", %tag);
   }
   
   %this.updateSearchTextFromFilter();
   
   %this.rebuildAssetArray();
}

function AssetBrowser::loadCreatorClasses(%this)
{
   // Just so we can recall this method for testing changes
   // without restarting.
   if ( isObject( %this.creatorClassArray ) )
      %this.creatorClassArray.delete();
      
   %this.creatorClassArray = new ArrayObject();
   %this.creatorClassArray.caseSensitive = true; 
   //%this.setListView( true );
   
   %this.beginCreatorGroup( "Environment" );
   
      /*// Removed Prefab as there doesn't really seem to be a point in creating a blank one
      //%this.registerMissionObject( "Prefab",              "Prefab" );
      %this.registerMissionObject( "SkyBox",              "Sky Box" );
      %this.registerMissionObject( "CloudLayer",          "Cloud Layer" );
      %this.registerMissionObject( "BasicClouds",         "Basic Clouds" );
      %this.registerMissionObject( "ScatterSky",          "Scatter Sky" );
      %this.registerMissionObject( "Sun",                 "Basic Sun" );
      %this.registerMissionObject( "Lightning" );
      %this.registerMissionObject( "WaterBlock",          "Water Block" );
      %this.registerMissionObject( "SFXEmitter",          "Sound Emitter" );
      %this.registerMissionObject( "Precipitation" );
      %this.registerMissionObject( "ParticleEmitterNode", "Particle Emitter" );
      
      // Legacy features. Users should use Ground Cover and the Forest Editor.   
      //%this.registerMissionObject( "fxShapeReplicator",   "Shape Replicator" );
      //%this.registerMissionObject( "fxFoliageReplicator", "Foliage Replicator" );
      
      %this.registerMissionObject( "PointLight",          "Point Light" );
      %this.registerMissionObject( "SpotLight",           "Spot Light" );
      %this.registerMissionObject( "GroundCover",         "Ground Cover" );
      %this.registerMissionObject( "TerrainBlock",        "Terrain Block" );
      %this.registerMissionObject( "GroundPlane",         "Ground Plane" );
      %this.registerMissionObject( "WaterPlane",          "Water Plane" );
      %this.registerMissionObject( "PxCloth",             "Cloth" );
      %this.registerMissionObject( "ForestWindEmitter",   "Wind Emitter" );
               
      %this.registerMissionObject( "DustEmitter", "Dust Emitter" );
      %this.registerMissionObject( "DustSimulation", "Dust Simulation" );
      %this.registerMissionObject( "DustEffecter", "Dust Effecter" );*/
      
   %this.endCreatorGroup();

   %this.beginCreatorGroup( "Level" );
   
      /*%this.registerMissionObject( "MissionArea",  "Mission Area" );
      %this.registerMissionObject( "Path" );
      %this.registerMissionObject( "Marker",       "Path Node" );
      %this.registerMissionObject( "Trigger" );
      %this.registerMissionObject( "PhysicalZone", "Physical Zone" );
      %this.registerMissionObject( "Camera" );
      %this.registerMissionObject( "LevelInfo",    "Level Info" );
      %this.registerMissionObject( "TimeOfDay",    "Time of Day" );
      %this.registerMissionObject( "Zone",         "Zone" );
      %this.registerMissionObject( "Portal",       "Zone Portal" );
      %this.registerMissionObject( "SpawnSphere",  "Player Spawn Sphere", "PlayerDropPoint" );
      %this.registerMissionObject( "SpawnSphere",  "Observer Spawn Sphere", "ObserverDropPoint" );
      %this.registerMissionObject( "SFXSpace",      "Sound Space" );
      %this.registerMissionObject( "OcclusionVolume", "Occlusion Volume" );*/
      
   %this.endCreatorGroup();
   
   %this.beginCreatorGroup( "System" );
   
      //%this.registerMissionObject( "SimGroup" );
      //%this.registerMissionObject( "AIPathGroup" );
      
   %this.endCreatorGroup();  

   %this.beginCreatorGroup( "ExampleObjects" );
   
      //%this.registerMissionObject( "RenderObjectExample" );
      //%this.registerMissionObject( "RenderMeshExample" );
      //%this.registerMissionObject( "RenderShapeExample" );
      
   %this.endCreatorGroup(); 
   
   %this.creatorClassArray.sortk();
}

function AssetBrowser::beginCreatorGroup(%this, %group)
{
   %this.currentCreatorGroup = %group; 
   
   AssetBrowser-->filterTree.insertItem(AssetBrowser-->filterTree.creatorIdx, %group);
}

function AssetBrowser::endCreatorGroup(%this, %group)
{
   %this.currentCreatorGroup = "";
}

function AssetBrowser::addCreatorClass(%this, %class, %name, %buildfunc)
{
   if( !isClass(%class) )
      return;
      
   if ( %name $= "" )
      %name = %class;
      
   if ( %this.currentCreatorGroup !$= "" && %group $= "" )
      %group = %this.currentCreatorGroup;
   
   if ( %class $= "" || %group $= "" )
   {
      warn( "AssetBrowser::addCreatorClass, invalid parameters!" );
      return;  
   }

   %args = new ScriptObject();
   %args.val[0] = %class;
   %args.val[1] = %name;
   %args.val[2] = %buildfunc;
   
   %this.creatorClassArray.push_back( %group, %args );
}
//
//needs to be deleted with the persistence manager and needs to be blanked out of the matmanager
//also need to update instances... i guess which is the tricky part....
function AssetBrowser::showDeleteDialog( %this )
{
   %material = AssetBrowser.selectedAsset;
   %secondFilter = "MaterialFilterMappedArray";
   %secondFilterName = "Mapped";
   
   for( %i = 0; %i < MaterialFilterUnmappedArray.count(); %i++ )
   {
      if( MaterialFilterUnmappedArray.getValue(%i) $= %material )
      {
         %secondFilter = "MaterialFilterUnmappedArray";
         %secondFilterName = "Unmapped";
         break;
      }
   }
   
   if( isObject( %material ) )
   {
      toolsMessageBoxYesNoCancel("Delete Material?", 
         "Are you sure you want to delete<br><br>" @ %material.getName() @ "<br><br> Material deletion won't take affect until the engine is quit.", 
         "AssetBrowser.deleteMaterial( " @ %material @ ", " @ %secondFilter @ ", " @ %secondFilterName @" );", 
         "", 
         "" );
   }
}

function AssetBrowser::deleteMaterial( %this, %materialName, %secondFilter, %secondFilterName )
{
   if( !isObject( %materialName ) )
      return;
   
   for( %i = 0; %i <= MaterialFilterAllArray.countValue( %materialName ); %i++)
   {
      %index = MaterialFilterAllArray.getIndexFromValue( %materialName );
      MaterialFilterAllArray.erase( %index );
   }
   MaterialFilterAllArrayCheckbox.setText("All ( " @ MaterialFilterAllArray.count() - 1 @ " ) ");
   
   %checkbox = %secondFilter @ "Checkbox";
   for( %k = 0; %k <= %secondFilter.countValue( %materialName ); %k++)
   {
      %index = %secondFilter.getIndexFromValue( %materialName );
      %secondFilter.erase( %index );
   }
   %checkbox.setText( %secondFilterName @ " ( " @ %secondFilter.count() - 1 @ " ) ");
   
   for( %i = 0; %materialName.getFieldValue("materialTag" @ %i) !$= ""; %i++ )
   {
      %materialTag = %materialName.getFieldValue("materialTag" @ %i);
         
         for( %j = AssetBrowser.staticFilterObjects; %j < AssetBrowser-->filterArray.getCount() ; %j++ )
         {
            if( %materialTag $= AssetBrowser-->filterArray.getObject(%j).getObject(0).filter )
            {
               %count = getWord( AssetBrowser-->filterArray.getObject(%j).getObject(0).getText(), 2 );
               %count--;
               AssetBrowser-->filterArray.getObject(%j).getObject(0).setText( %materialTag @ " ( "@ %count @ " )");
            }
         }
      
   }
   
   UnlistedMaterials.add( "unlistedMaterials", %materialName );
   
   if( %materialName.getFilename() !$= "" && 
         %materialName.getFilename() !$= "tools/gui/AssetBrowser.ed.gui" &&
         %materialName.getFilename() !$= "tools/materialEditor/scripts/materialEditor.ed.cs" )
   {
      AssetBrowserPerMan.removeObjectFromFile(%materialName);
      AssetBrowserPerMan.saveDirty();
   }
      
   AssetBrowser.preloadFilter();
}

function AssetBrowser::thumbnailCountUpdate(%this)
{
   $Pref::AssetBrowser::ThumbnailCountIndex = AssetBrowser-->materialPreviewCountPopup.getSelected();
   AssetBrowser.LoadFilter( AssetBrowser.currentFilter, AssetBrowser.currentStaticFilter );
}

function AssetBrowser::toggleTagFilterPopup(%this)
{
	if(TagFilterWindow.visible)
		TagFilterWindow.visible = false;
	else
		TagFilterWindow.visible = true;
		
	return;
   %assetQuery = new AssetQuery();
   %numAssetsFound = AssetDatabase.findAllAssets(%assetQuery);
   
   for( %i=0; %i < %numAssetsFound; %i++)
   {
	    %assetId = %assetQuery.getAsset(%i);
		
		//first, get the asset's module, as our major categories
		%module = AssetDatabase.getAssetModule(%assetId);
		
		%moduleName = %module.moduleId;
		
		//check that we don't re-add it
		%moduleItemId = AssetBrowser-->filterTree.findItemByName(%moduleName);
		
		if(%moduleItemId == -1 || %moduleItemId == 0)
			%moduleItemId = AssetBrowser-->filterTree.insertItem(1, %module.moduleId, "", "", 1, 2);
			
		//now, add the asset's category
		%assetType = AssetDatabase.getAssetCategory(%assetId);
		
		%checkBox = new GuiCheckBoxCtrl()
		{
			canSaveDynamicFields = "0";
			isContainer = "0";
			Profile = "ToolsGuiCheckBoxListProfile";
			HorizSizing = "right";
			VertSizing = "bottom";
			Position = "0 0";
			Extent = (%textLength * 4) @ " 18";
			MinExtent = "8 2";
			canSave = "1";
			Visible = "1";
			Variable = %var;
			tooltipprofile = "ToolsGuiToolTipProfile";
			hovertime = "1000";
			text = %text;
			groupNum = "-1";
			buttonType = "ToggleButton";
			useMouseEvents = "0";
			useInactiveState = "0";
			Command = %cmd;
		};
		
		TagFilterList.add(%checkBox);
   }	
}

function AssetBrowser::changeAsset(%this)
{
   //alright, we've selectd an asset for a field, so time to set it!
   %cmd = %this.fieldTargetObject @ "." @ %this.fieldTargetName @ "=\"" @ %this.selectedAsset @ "\";";
   echo("Changing asset via the " @ %cmd @ " command");
   eval(%cmd);
   
   //Flag us as dirty for editing purposes
   EWorldEditor.setSceneAsDirty();
}

function AssetBrowser::reImportAsset(%this)
{
   //Find out what type it is
   %assetDef = AssetDatabase.acquireAsset(EditAssetPopup.assetId);
   %assetType = AssetDatabase.getAssetType(EditAssetPopup.assetId);
      
   if(%assetType $= "ShapeAsset" || %assetType $= "ImageAsset" || %assetType $= "SoundAsset")
   {
      AssetBrowser.isAssetReImport = true;
      AssetBrowser.reImportingAssetId = EditAssetPopup.assetId;
      
      %reimportingPath = %assetDef.originalFilePath;
      
      //first, double-check we have an originating file. if we don't then we need to basically go out looking for it
      if(!isFile(%assetDef.originalFilePath))
      {
         //if(%assetType $= "ImageAsset")
         //   %filters = "";
            
         %dlg = new OpenFileDialog()
         {
            Filters = "(All Files (*.*)|*.*|";
            DefaultFile = %currentFile;
            ChangePath = false;
            MustExist = true;
            MultipleFiles = false;
            forceRelativePath = false;
         };
            
         if ( %dlg.Execute() )
         {
            %reimportingPath = %dlg.FileName;
         }
         
         %dlg.delete();
      }
      
      AssetBrowser.onBeginDropFiles();
      AssetBrowser.onDropFile(%reimportingPath);
      AssetBrowser.onEndDropFiles();
      
      %module = AssetDatabase.getAssetModule(EditAssetPopup.assetId);
      
      //get the selected module data
      ImportAssetModuleList.setText(%module.ModuleId);
   }
}

//
//
// RMB context popups
function AssetBrowserPreviewButton::onRightClick(%this)
{
   AssetBrowser.selectedAssetPreview = %this;
   EditAssetPopup.assetId = %this.moduleName @ ":" @ %this.assetName;
   EditAssetPopup.assetType = %this.assetType;
   %assetType = %this.assetType;
   
   //Do some enabling/disabling of options depending on asset type
   EditAssetPopup.enableItem(0, true);
   EditAssetPopup.enableItem(7, true);
   
   //Is it an editable type?
   if(%assetType $= "ImageAsset" /*|| %assetType $= "GameObjectAsset"*/ || %assetType $= "CppAsset" || %assetType $= "SoundAsset")
   {
      EditAssetPopup.enableItem(0, false);
   }
   
   //Is it an importable type?
   if(%assetType $= "GameObjectAsset" || %assetType $= "ComponentAsset" || %assetType $= "GUIAsset" || %assetType $= "LevelAsset"
       || %assetType $= "MaterialAsset" || %assetType $= "ParticleAsset"  || %assetType $= "PostEffectAsset" || %assetType $= "ScriptAsset"
       || %assetType $= "StateMachineAsset")
   {
      EditAssetPopup.enableItem(7, false);
   }
   
   if(%assetType $= "LevelAsset")
      EditLevelAssetPopup.showPopup(Canvas);  
   else if(%assetType $= "Folder")
   {
      EditFolderPopup.dirPath = %this.moduleName @ "/" @ %this.assetName;
      EditFolderPopup.showPopup(Canvas);  
   }
   else
      EditAssetPopup.showPopup(Canvas);  
      
   if(%assetType $= "Folder")
   {
      EditAssetPopup.assetId = %this.moduleName @ "/" @ %this.assetName;
   }
}

//function AssetListPanel::onRightMouseDown(%this)
function AssetListPanelInputs::onRightMouseDown(%this)
{
   AddNewAssetPopup.showPopup(Canvas);
}

function AssetBrowserFilterTree::onRightMouseDown(%this, %itemId)
{
   %count = %this.getSelectedItemsCount();
   
   %itemText = %this.getItemText(%itemId);
   %parentItem = %this.getParentItem(%itemId);
   if(%parentItem == %this.tagsIdx)
   {
   }
   else if(%parentItem == %this.collectionsIdx)
   {
      EditCollectionSets.showPopup(Canvas); 
      AssetBrowser.selectedCollectionSet = %itemText;
   }
   else if(%parentItem == %this.creatorIdx)
   {
   }
   else
   {
      if( %this.getSelectedItemsCount() > 0 && (%itemText !$= "Data" && %itemText !$= "Core" && %itemText !$= "Tools"))
      {
         //AddNewAssetPopup.showPopup(Canvas);  
         
         //We have something clicked, so figure out if it's a sub-filter or a module filter, then push the correct
         //popup menu
         %parentItem = %this.getParentItem(%itemId);
         if(%this.getItemText(%parentItem) $= "Data") //if it's a data module, continue
         {
            //find out if it's a folder or a module!
            if(ModuleDatabase.findModule(%itemText))
            {
               //yep, module, push the all-inclusive popup  
               EditModulePopup.showPopup(Canvas); 
               //also set the module value for creation info
               AssetBrowser.selectedModule = %itemText;
            }
            else
            {
               EditNonModulePopup.showPopup(Canvas);
               EditNonModulePopup.targetFolder = %itemText;
            }
         }
         else
         {
            EditFolderPopup.showPopup(Canvas);
            EditFolderPopup.assetType = "Folder";  
         }
      }
      else if(%itemText $= "Data")
      {
         AddNewModulePopup.showPopup(Canvas);
      }
      else if(%itemText $= "Tools")
      {
         AddNewToolPopup.showPopup(Canvas);
      }
   }
}

//
//
//
function AssetBrowser::openAssetSettings(%this)
{
   ESettingsWindow.toggleEditorSettings();
   %assetEditIndex = ESettingsWindowList.findTextIndex("Asset Editing");
   ESettingsWindowList.setSelectedRow( %assetEditIndex );
}

function AssetBrowser::showVisibiltyOptions(%this)
{
   BrowserVisibilityPopup.showPopup(Canvas);
}

function AssetBrowser::saveCurrentFiltersAsCollection(%this)
{
   %colSetName = CreateNewCollectionSetCtrl-->collectionSetName.getText();
   
   if(%colSetName $= "")
   {
      error("Collection Sets require a name!");  
   }
   
   %collectionsCount = AssetBrowserCollectionSets.value("CollectionSetCount", 0);
   %collectionsCount += 1;
   
   AssetBrowserCollectionSets.setValue("CollectionSetCount", %collectionsCount);
   
   %collection = %colSetName TAB AssetBrowserSearchFilter.getText();
   
   AssetBrowserCollectionSets.setValue("Collection"@%collectionsCount-1, %collection);
   
   %success = AssetBrowserCollectionSets.write();
   
   AssetBrowser.loadDirectories();
}

function AssetBrowser::deleteCollectionSet(%this)
{
   %collectionsCount = AssetBrowserCollectionSets.value("CollectionSetCount", 0);
   %tempCollectionListCount = 0;
   
   %found = false;
   for ( %i = 0; %i < %collectionsCount; %i++ )
   {
      %collection = AssetBrowserCollectionSets.value("Collection"@%i, "");
      %collectionName = getField(%collection, 0);
      %collectionTerm = getField(%collection, 1);
      
      if(AssetBrowser.selectedCollectionSet !$= %collectionName)
      {
         %tempCollectionList[%tempCollectionListCount] = %collection;
         %tempCollectionListCount++;
      }
   }
   
   AssetBrowserCollectionSets.setValue("CollectionSetCount", %tempCollectionListCount);
   for(%i=0; %i < %collectionsCount; %i++)
   {
      if(%i < %tempCollectionListCount)
         AssetBrowserCollectionSets.setValue("Collection"@%i, %tempCollectionList[%i]);  
      else
         AssetBrowserCollectionSets.remove("Collection"@%i);  
   }
   
   AssetBrowserCollectionSets.write();
   
   %this.loadDirectories();
}

function AssetBrowser::refreshPreviews(%this)
{
   AssetBrowserFilterTree.onSelect(AssetBrowser.selectedItem);
}

function AssetBrowserFilterTree::onSelect(%this, %itemId)
{
	if(%itemId == 1)
		//can't select root
		return;
		
   //process special cases
   %parentItem = %this.getParentItem(%itemId);
   if(%parentItem == %this.tagsIdx)
   {
      //we selected a tag, so deal with that 
      AssetBrowser.setTagActive(%this.getItemText(%itemId));
   }
   else if(%parentItem == %this.collectionsIdx)
   {
      //A collection set was selected
      AssetBrowser.setCollectionSetActive(%this.getItemValue(%itemId));
   }
   else if(%parentItem == %this.creatorIdx)
   {
      //One of the creator folders was selected
      %creatorGroup = %this.getItemText(%itemId);
      for ( %i = 0; %i < %this.creatorClassArray.count(); %i++ )
      {
         %group = %array.getKey( %i );

         if ( %group $= %creatorGroup )
         {
            %args = %array.getValue( %i );
            %class = %args.val[0];
            %name = %args.val[1];
            %func = %args.val[2];

            //%this.addMissionObjectIcon( %class, %name, %func );                                             
            echo("Populating Creator Group! " @ %group @ " for class: " @ %class);
         }               
      }
   }
   else
   {
      //Make sure we have an actual module selected!
      %parentId = %this.getParentItem(%itemId);
      
      %name = %this.getItemText(%itemId);
      
      %breadcrumbPath = %this.getItemValue(%itemId);
      if(%breadcrumbPath !$= "")
         %breadcrumbPath = %breadcrumbPath @ "/" @ %this.getItemText(%itemId);
      else
         %breadcrumbPath = %this.getItemText(%itemId);
         
      if(%breadcrumbPath $= "")
         %breadcrumbPath = AssetBrowser.dirHandler.currentAddress;
         
      AssetBrowser.navigateTo(%breadcrumbPath);
   }
}

function AssetBrowser::rebuildAssetArray(%this)
{
   if(!%this.previewArrayDirty)
   {
      %this.previewArrayDirty = true;
      %this.schedule(16, "doRebuildAssetArray");
   }
}

function AssetBrowser::doRebuildAssetArray(%this)
{
   if(!%this.previewArrayDirty)
      return;
   
   %breadcrumbPath = AssetBrowser.dirHandler.currentAddress;
   
   // we have to empty out the list; so when we create new guicontrols, these dont linger
   AssetBrowser-->assetList.deleteAllObjects();
   AssetPreviewArray.empty();

   if(isObject(%assetArray))
      %assetArray.delete();
      
   %assetArray = new ArrayObject();
   
   //First, Query for our assets
   %assetQuery = new AssetQuery();
   %numAssetsFound = AssetDatabase.findAllAssets(%assetQuery);

   %finalAssetCount = 0;
   
    //now, we'll iterate through, and find the assets that are in this module, and this category
    for( %i=0; %i < %numAssetsFound; %i++)
    {
	    %assetId = %assetQuery.getAsset(%i);
	    
	    %assetPath = makeRelativePath(AssetDatabase.getAssetFilePath(%assetId));
       %assetBasePath = filePath(%assetPath);
       
       //clean up the path
       %assetBasePath = strreplace(%assetBasePath, "//", "/");
       
       %searchActive = AssetSearchTerms.count() != 0;
       if(%assetBasePath $= %breadcrumbPath || (%searchActive && startsWith(%assetBasePath,%breadcrumbPath)))
       {
          //first, get the asset's module, as our major categories
		    %module = AssetDatabase.getAssetModule(%assetId);
		    %moduleName = %module.moduleId;
		    
		    //it's good, so test that the category is right!
			%assetType = AssetDatabase.getAssetCategory(%assetId);
			if(%assetType $= "")
			{
			   %assetType = AssetDatabase.getAssetType(%assetId);
			}
			
			/*%validType = false;
         
         if(AssetBrowser.assetTypeFilter $= "")
         {
            if(AssetTypeListPopup.isItemChecked(0))
            {
               %validType = true;
            }
            else
            {
               for(%f=1; %f < AssetFilterTypeList.Count(); %f++)
               {
                  %isChecked = AssetTypeListPopup.isItemChecked(%f+1);  
                  
                  if(%isChecked)
                  {
                     %filterTypeName = AssetFilterTypeList.getKey(%f);
                     
                     if(%activeTypeFilterList $= "")
                        %activeTypeFilterList = %filterTypeName;
                     else
                        %activeTypeFilterList = %activeTypeFilterList @ ", " @ %filterTypeName;
                        
                     if(%filterTypeName @ "Asset" $= %assetType)
                     {
                        %validType = true;
                        break;  
                     }
                  }
               }
            }
            
            if(!%validType)
               continue;
         }
         else
         {
            if(%assetType !$= AssetBrowser.assetTypeFilter)
               continue;  
         }*/
			
         //stop adding after previewsPerPage is hit
         %assetName = AssetDatabase.getAssetName(%assetId);

         if(%searchActive)
         {
            if(matchesSearch(%assetName, %assetType))
            {
               %assetArray.add( %moduleName, %assetId);
                  
               if(%assetType !$= "Folder")
                  %finalAssetCount++;
                  
               continue;
            }
         }
         else
         {
            if(AssetBrowser.assetTypeFilter !$= "")
            {
               if(AssetBrowser.assetTypeFilter $= %assetType)
               {
                  %assetArray.add( %moduleName, %assetId );
                  
                  if(%assetType !$= "Folder")
                     %finalAssetCount++;
               }
            }
            else
            {
               //got it.	
               %assetArray.add( %moduleName, %assetId );
               
               if(%assetType !$= "Folder")
                  %finalAssetCount++;
            }
         }
      }
   }
   
   //Add folders
   if(EditorSettings.value("Assets/Browser/showFolders", true) == true)
   {
      %folders = getDirectoryList(%breadcrumbPath);
      for(%f=0; %f < getFieldCount(%folders); %f++)
      {
         %folderName = getField(%folders, %f);
         
         %searchActive = AssetSearchTerms.count() != 0;
         if(%searchActive)
         {
            if(matchesSearch(%folderName, "Folder", ""))
            {
               %assetArray.add( %breadcrumbPath, "Folder" TAB %folderName );
               continue;
            }
         }
         else
         {
            //got it.	
            if(%folderName $= "shaderCache" || %folderName $= "cache" || %folderName $= ".git")
               continue;
               
            if(!%this.coreModulesFilter && %folderName $= "core" && %breadcrumbPath $= "")
               continue;
               
            if(!%this.toolsModulesFilter && %folderName $= "tools" && %breadcrumbPath $= "")
               continue;
               
            %assetArray.add( %breadcrumbPath, "Folder" TAB %folderName );
         }
      }
   }

   //Add Non-Asset Scripted Objects. Datablock, etc based
   if(AssetBrowser.assetTypeFilter $= "")
   {
      %category = getWord( %breadcrumbPath, 1 );                  
      %dataGroup = "DataBlockGroup";
      
      for ( %i = 0; %i < %dataGroup.getCount(); %i++ )
      {
         %obj = %dataGroup.getObject(%i);
         // echo ("Obj: " @ %obj.getName() @ " - " @ %obj.category );
         
         //if ( %obj.category $= "" && %obj.category == 0 )
         //   continue;
         
         %dbFilename = %obj.getFileName();
         %dbFilePath = filePath(%dbFilename);
         
         %searchActive = AssetSearchTerms.count() != 0;
         if(%searchActive)
         {
            if(startsWith(%dbFilePath, %breadcrumbPath))
            {
               %dbName = %obj.getName();
               if(matchesSearch(%dbName, "Datablock"))
               {
                  %assetArray.add( %dbFilename, "Datablock" TAB %dbName );
               }  
            }
         }
         else if(%dbFilePath $= %breadcrumbPath)
         {
            %dbName = %obj.getName();
            %assetArray.add( %dbFilename, "Datablock" TAB %dbName );
            
            /*%catItem = AssetBrowser-->filterTree.findItemByName(%obj.category);
            
            if(%catItem == 0)
               AssetBrowser-->filterTree.insertItem(%scriptedItem, %obj.category, "scripted");*/
            /*%ctrl = %this.findIconCtrl( %obj.category );
            if ( %ctrl == -1 )
            {
               %this.addFolderIcon( %obj.category );
            }*/
         }
      }
      
      
      %this.getLooseFilesInDir();
      
      %looseFiles = ABLooseFileArray.count();
      for( %i=0; %i < %looseFiles; %i++)
      {
         %looseFileFullPath = ABLooseFileArray.getKey(%i);
         %looseFilePath = filePath(%looseFileFullPath);
         %looseFileName = fileName(%looseFileFullPath);
         
         %assetArray.add( %looseFilePath, "LooseFile" TAB %looseFileName );
      }
         
      //Prefabs
      %expr = "*.prefab";
      %fullPrefabPath = findFirstFile( %breadcrumbPath @ "/" @ %expr );
      
      while ( %fullPrefabPath !$= "" )
      {         
         %prefabPath = filePath(%fullPrefabPath);
         %prefabName = fileName(%fullPrefabPath);
         
         %searchActive = AssetSearchTerms.count() != 0;
         if(%searchActive)
         {
            if(startsWith(%prefabPath, %breadcrumbPath))
            {
               if(matchesSearch(%prefabName, "Prefab"))
               {
                  %assetArray.add( %prefabPath, "Prefab" TAB %prefabName );
               }  
            }
         }
         else if(%prefabPath $= %breadcrumbPath)
         {
            %assetArray.add( %prefabPath, "Prefab" TAB %prefabName );
         }

         %fullPrefabPath = findNextFile( %breadcrumbPath @ "/" @ %expr );
      }
   }
	
   for(%i=0; %i < %assetArray.count(); %i++)
		AssetBrowser.buildAssetPreview( %assetArray.getValue(%i), %assetArray.getKey(%i) );  
		
   AssetBrowser_FooterText.text = %finalAssetCount @ " Assets";
   
   %activeTypeFilterList = "";
   if(AssetBrowser.assetTypeFilter $= "")
   {
      if(!AssetTypeListPopup.isItemChecked(0))
      {
         for(%f=1; %f < AssetFilterTypeList.Count(); %f++)
         {
            %isChecked = AssetTypeListPopup.isItemChecked(%f+1);  
            
            if(%isChecked)
            {
               %filterTypeName = AssetFilterTypeList.getKey(%f);
               
               if(%activeTypeFilterList $= "")
                  %activeTypeFilterList = %filterTypeName;
               else
                  %activeTypeFilterList = %activeTypeFilterList @ ", " @ %filterTypeName;
            }
         }
      }
   }
   else
   {
      %activeTypeFilterList = AssetBrowser.assetTypeFilter;
   }
   
   if(%activeTypeFilterList !$= "")
      AssetBrowser_FooterText.text = AssetBrowser_FooterText.text @ " | Active Type Filters: " @ %activeTypeFilterList;
      
   %this.previewArrayDirty = false;
}

//
//
// Search
function AssetBrowser::updateSearchTextFromFilter(%this)
{
   AssetSearchTerms.sortk();
   
   //Update the displayed search text!
   %newSearchPhrase = "";
   %currentAction = "";
   %actionCount = 0;
   for(%i=0; %i < AssetSearchTerms.count(); %i++)
   {
      %action = AssetSearchTerms.getKey(%i);
      %word = AssetSearchTerms.getValue(%i);
      
      if(%action !$= %currentAction)
      {
         if(%actionCount != 0)
         {
            if(%action !$= "")
               %newSearchPhrase = %newSearchPhrase @ ";" @ %action @ ":" @ %word;
            else
               %newSearchPhrase = %newSearchPhrase @ ";" @ %word;
         }
         else
         {
            if(%action !$= "")
               %newSearchPhrase = %action @ ":" @ %word;
            else
               %newSearchPhrase = %word;
         }
            
         %actionCount++;
      }
      else
      {
         %newSearchPhrase = %newSearchPhrase @ "," @ %word;
      }
      
      %currentAction = %action;
   }
   
   AssetBrowserSearchFilter.setText(%newSearchPhrase);
}

function AssetBrowser::processSearchFilter(%this)
{
   AssetSearchTerms.empty();
      
   %searchText = AssetBrowserSearchFilter.getText();
   
   %termCount = getTokenCount(%searchText, ";");
   for(%s=0; %s < %termCount; %s++)
   {
      %term = getToken(%searchText, ";", %s);
      
      %phraseCount = getTokenCount(%term, ":");
      
      if(%phraseCount == 2)
      {
         //action/words split
         %action = getToken(%term, ":", 0);  
         %words = getToken(%term, ":", 1);  
      }
      else
      {
         %action = "";
         %words = getToken(%term, ":", 0);
      }
      
      %wordCount = getTokenCount(%words, ",");
      for(%w=0; %w < %wordCount; %w++)
      {
         %word = getToken(%words, ",", %w);
         AssetSearchTerms.add(%action, %word);
      }
   }
}

//Takes an item and compares it against the parsed search language
//This is written to be inclusive, rather than exclusive
function matchesSearch(%assetName, %assetType)
{
   if(AssetSearchTerms.count() == 0)
      return true;
      
   %matchTags = false;
   %matchType = false;
   %matchName = false;
   
   %needsTag = false;
   %needsType = false;
   %needsName = false;
   for(%i=0; %i < AssetSearchTerms.count(); %i++)
   {
      %action = AssetSearchTerms.getKey(%i);
      %word = AssetSearchTerms.getValue(%i);
      
      if(%action $= "tag" && %matchTags == false)
      {
         %needsTag = true;
         if(%assetType $= "Datablock")
         {
            if(%assetName.category $= %word)
               %matchTags = true;
         }
         else
         {
            if(%assetName.tags !$= %word)
               %matchTags = true;
         }
      }
      else if(%action $= "type" && %matchType == false)
      {
         %needsType = true;
         if(%assetType $= %word)
            %matchType = true;
      }
      else if(%action $= "" && %matchName == false)
      {
         %needsName = true;
         if(strstr(strlwr(%assetName), strlwr(%word)) != -1)
            %matchName = true;  
      }
   }
   
   if(((%needsTag && %matchTags) || !%needsTag) && 
      ((%needsType && %matchType) || !%needsType) && 
      ((%needsName && %matchName) || !%needsName))
      return true;
   else
      return false;  
}

//
//
// Search Filters
function AssetBrowserSearchFilterTxt::onWake( %this )
{
   /*%filter = %this.treeView.getFilterText();
   if( %filter $= "" )
      %this.setText( "\c2Filter..." );
   else
      %this.setText( %filter );*/
}

function AssetBrowserSearchFilterTxt::onGainFirstResponder( %this )
{
   %this.selectAllText();
}

// When Enter is pressed in the filter text control, pass along the text of the control
// as the treeview's filter.
function AssetBrowserFolderSearchFilter::onReturn( %this )
{
   %text = %this.getText();
   if( %text $= "" )
      %this.reset();
   
   AssetBrowser.refresh();
}

function AssetBrowserFolderSearchFilter::onEdited(%this)
{
   if(AssetBrowserFolderSearchFilter.getText() $= "")
   {
      AssetBrowser-->folderSearchBtn.setBitmap("tools/gui/images/stencilIcons/zoom.png");
   }
   else
   {
      AssetBrowser-->folderSearchBtn.setBitmap("tools/gui/images/stencilIcons/cross.png");
   }
}

function AssetBrowserSearchFilter::onEdited(%this)
{
   AssetBrowserSearchFilter.updateButton();
}

function AssetBrowserSearchFilter::onReturn( %this )
{
   %text = %this.getText();
   if( %text $= "" )
      %this.reset();
      
   AssetBrowserSearchFilter.updateButton();
      
   AssetBrowser.processSearchFilter();
   
   AssetBrowser.rebuildAssetArray();
}

function AssetBrowserSearchFilter::updateButton(%this)
{
   if(%this.getText() $= "")
   {
      AssetBrowser-->assetSearchBtn.setBitmap("tools/gui/images/stencilIcons/zoom.png");
   }
   else
   {
      AssetBrowser-->assetSearchBtn.setBitmap("tools/gui/images/stencilIcons/cross.png");
   }
}

function AssetBrowserFolderSearchFilter::reset( %this )
{
   %this.setText( "" );
   AssetBrowser-->folderSearchBtn.setBitmap("tools/gui/images/stencilIcons/zoom.png");
   //AssetBrowser.refresh();
}

function AssetBrowserSearchFilter::reset( %this )
{
   %this.setText( "" );
   AssetBrowser-->assetSearchBtn.setBitmap("tools/gui/images/stencilIcons/zoom.png");
   //AssetBrowser.rebuildAssetArray();
}

function AssetBrowserFolderSearchBtn::onClick( %this )
{
   AssetBrowserFolderSearchFilter.reset();
   AssetBrowser.refresh();
}

function AssetBrowserAssetSearchBtn::onClick( %this )
{
   AssetBrowserSearchFilter.reset();
   AssetBrowser.processSearchFilter();
   
   AssetBrowser.rebuildAssetArray();
}

//
//
// Navigation
function AssetBrowser::navigateTo(%this, %address, %historyNav)
{
   //Sanitize
   if(startsWith(%address, "/"))
      %address = strreplace(%address, "/", "");
      
   //Don't bother navigating if it's to the place we already are
   if(%this.dirHandler.currentAddress !$= %address)
   {
      %this.dirHandler.navigateTo(%address, %historyNav);
         
      //%this.updateNavigationBreadcrumb(%address);
      
      %this.lastValidNavPath = %address;
      %this-->navPath.setText(%address);
      
      %module = %this.dirHandler.getModuleFromAddress(%address);
      if(%module !$= "")
      {
         //legit module, so set it as current target
         %this.SelectedModule = %module.moduleId;
      }
      
      if(%this.hasLooseFilesInDir())
      {
         %this-->AutoImportAssetButton.visible = true;
      }
      else
      {
          %this-->AutoImportAssetButton.visible = false; 
      }
   }
   
   %this.rebuildAssetArray();
   %this.refresh();
}

function AssetBrowser::navigateHistoryForward(%this)
{
   %this.dirHandler.navigateHistoryForward();
   
   %this.updateNavigationBreadcrumb();
   
   %address = %this.dirHandler.currentAddress;
   
   %module = AssetBrowser.dirHandler.getModuleFromAddress(%address);
   if(%module !$= "")
   {
      //legit module, so set it as current target
      %this.SelectedModule = %module.moduleId;
   }
   
   %this.lastValidNavPath = %address;
   %this-->navPath.setText(%address);
   
   %this.rebuildAssetArray();
}

function AssetBrowser::navigateHistoryBack(%this)
{
   %this.dirHandler.navigateHistoryBack();
      
   %this.updateNavigationBreadcrumb();
   
   %address = %this.dirHandler.currentAddress;
   
   %module = %this.dirHandler.getModuleFromAddress(%address);
   if(%module !$= "")
   {
      //legit module, so set it as current target
      %this.SelectedModule = %module.moduleId;
   }
   
   %this.lastValidNavPath = %address;
   %this-->navPath.setText(%address);
   
   %this.rebuildAssetArray();
}

function AssetBrowser::updateNavigationBreadcrumb(%this, %address)
{
   //clear the breadcrumb bar
   AssetBrowser_BreadcrumbBar.clear();
   
   //break down the address
   %folderCount = getTokenCount(%address, "/");
      
   %rebuiltPath = "";
   for(%f=0; %f < %folderCount; %f++)
   {
      %folderName = getToken(%address, "/", %f);
      
      %rebuiltPath = %f == 0 ? %folderName : %rebuiltPath @ "/" @ %folderName;
      
      %folderNavButton = new GuiButtonCtrl()
      {
         profile = ToolsGuiButtonProfile;
         text = %folderName;
         command = "AssetBrowser.navigateTo(\"" @ %rebuiltPath @ "\");";
         extent = "100" SPC AssetBrowser_BreadcrumbBar.extent.y;
      };
      
      AssetBrowser_BreadcrumbBar.add(%folderNavButton);
      
      if(%f != %folderCount-1)
      {
         %folderSpacerButton = new GuiBitmapButtonCtrl()
         {
            profile = ToolsGuiButtonProfile;
            bitmap = "tools/gui/images/rightArrowWhite";
            bitmapMode = "Centered";
            extent = "25" SPC AssetBrowser_BreadcrumbBar.extent.y;
            //command = "AssetBrowser.navigateTo(\"" @ %rebuiltPath @ "\");";
         };
         
         AssetBrowser_BreadcrumbBar.add(%folderSpacerButton);
      }
   }

   //refresh the nav buttons to display the history
   %backButtonHistory = "";
   for(%i=0; %i < AssetBrowser.dirHandler.prevHistoryList.Count(); %i++)
   {
      %prevAddress = AssetBrowser.dirHandler.prevHistoryList.getKey(%i);
      %backButtonHistory = %i==0 ? %prevAddress @ "\n" : %backButtonHistory @ %prevAddress @ "\n";
   }
   
   AssetBrowser_NavigateBackBtn.tooltip = %backButtonHistory;
   
   %foreButtonHistory = "";
   for(%i=0; %i < AssetBrowser.dirHandler.foreHistoryList.Count(); %i++)
   {
      %prevAddress = AssetBrowser.dirHandler.foreHistoryList.getKey(%i);
      %foreButtonHistory = %i==0 ? %prevAddress @ "\n" : %foreButtonHistory @ %prevAddress @ "\n";
   }
   
   AssetBrowser_NavigateForwardBtn.tooltip = %foreButtonHistory;
}

function assetBrowserNavPath::onReturn(%this)
{
   %newPath = %this.getText();
   if(isDirectory(%newPath))
   {
      AssetBrowser.lastValidNavPath =  %newPath;
      AssetBrowser.navigateTo(%newPath); 
   }
   else
   {
      %this.setText(AssetBrowser.lastValidNavPath);
      AssetBrowser.navigateTo(AssetBrowser.lastValidNavPath);
   }
}
//
//
//
function AssetBrowser::reloadModules(%this)
{
   ModuleDatabase.unloadGroup("Game");
   
   %modulesList = ModuleDatabase.findModules();
   
   %count = getWordCount(%modulesList);
   
   for(%i=0; %i < %count; %i++)
   {
      %moduleId = getWord(%modulesList, %i).ModuleId;
      ModuleDatabase.unloadExplicit(%moduleId);
   }

   ModuleDatabase.scanModules();
   
   %modulesList = ModuleDatabase.findModules();
   
   %count = getWordCount(%modulesList);
   
   for(%i=0; %i < %count; %i++)
   {
      %moduleId = getWord(%modulesList, %i).ModuleId;
      ModuleDatabase.loadExplicit(%moduleId);
   }
   
   //ModuleDatabase.loadGroup("Game");
}

//
//
//
function AssetBrowser::toggleFolderCollapseButton(%this)
{
   %this.folderPanelState = !%this.folderPanelState;
   
   //If we're collapsing
   if(!%this.folderPanelState)
   {
      //Store the original
      %this.folderPanelSplit = AssetBrowser_MainSplit.splitPoint.x;
      
      //collapse it
      AssetBrowser_MainSplit.setSplitPoint(AssetBrowser_MainSplit.splitterSize SPC AssetBrowser_MainSplit.splitPoint.y);
   }
   else
   {
      //restore the original
      AssetBrowser_MainSplit.setSplitPoint(%this.folderPanelSplit SPC AssetBrowser_MainSplit.splitPoint.y);
   }  
}
//
//
// Drag n drop
function AssetBrowserPreviewButton::onMouseDragged(%this)
{
   %payload = %this.clone();
   %payload.position = "0 0";
   //%payload.class = "AssetPreviewControl";
   
   /*%payload = new GuiBitmapButtonCtrl();
   //%payload.assignFieldsFrom( %this );
   %payload.assetName = %this.assetName;
   %payload.assetType = %this.assetType ;
   %payload.moduleName = %this.moduleName;
   %payload.class = "AssetPreviewControl";
   %payload.position = "0 0";
   %payload.dragSourceControl = %this;
   %payload.bitmap = %this.icon;
   %payload.extent.x /= 2;
   %payload.extent.y /= 2;*/
   
   %xOffset = getWord( %payload.extent, 0 ) / 2;
   %yOffset = getWord( %payload.extent, 1 ) / 2;
   
   // Compute the initial position of the GuiDragAndDrop control on the cavas based on the current
   // mouse cursor position.
   
   %cursorpos = Canvas.getCursorPos();
   %xPos = getWord( %cursorpos, 0 ) - %xOffset;
   %yPos = getWord( %cursorpos, 1 ) - %yOffset;
   
   if(!isObject(EditorDragAndDropLayer))
   {
      new GuiControl(EditorDragAndDropLayer)
      {
         position = "0 0";
         extent = Canvas.extent;
      };
   }
   
   // Create the drag control.
   %ctrl = new GuiDragAndDropControl()
   {
      canSaveDynamicFields    = "0";
      Profile                 = "GuiSolidDefaultProfile";
      HorizSizing             = "right";
      VertSizing              = "bottom";
      Position                = %xPos SPC %yPos;
      extent                  = %payload.extent;
      MinExtent               = "4 4";
      canSave                 = "1";
      Visible                 = "1";
      hovertime               = "1000";

      // Let the GuiDragAndDropControl delete itself on mouse-up.  When the drag is aborted,
      // this not only deletes the drag control but also our payload.
      deleteOnMouseUp         = true;
      
      useWholeCanvas = true;

      // To differentiate drags, use the namespace hierarchy to classify them.
      // This will allow a color swatch drag to tell itself apart from a file drag, for example.
      class                   = "AssetPreviewControlType_AssetDrop";
   };
   
   // Add the temporary color swatch to the drag control as the payload.
   %ctrl.add( %payload );
   
   // Start drag by adding the drag control to the canvas and then calling startDragging().
   //Canvas.getContent().add( %ctrl );
   EditorDragAndDropLayer.add(%ctrl);
   Canvas.pushDialog(EditorDragAndDropLayer);
   
   %ctrl.startDragging( %xOffset, %yOffset );
   
   Canvas.repaint();
}

function AssetBrowserPreviewButton::onControlDragCancelled(%this)
{
   Canvas.popDialog(EditorDragAndDropLayer);
}

function AssetBrowserPreviewButton::onControlDropped( %this, %payload, %position )
{
   Canvas.popDialog(EditorDragAndDropLayer);
   
   if( !%payload.parentGroup.isInNamespaceHierarchy( "AssetPreviewControlType_AssetDrop" ) )
      return;

   // If dropped on same button whence we came from,
   // do nothing.

   if( %payload.dragSourceControl == %this )
      return;
      
   %assetType = %payload.assetType;
   %assetName = %payload.assetName;
   %moduleName = %payload.moduleName;
   
   %targetAssetName = %this.assetName;
   %targetAssetType = %this.assetType;
   %targetModuleName = %this.moduleName;

   if( %payload.dragSourceControl.class $= "AssetPreviewButton" && %targetAssetType $= "Folder")
   {
      %destination = %targetModuleName @ "/" @ %targetAssetName;
      
      if(%assetType $= "Folder")
      {
         %originFolder = %moduleName @ "/" @ %assetName;
         %destination = %destination @ "/" @ %assetName;
         
         //Do any cleanup required given the type
         if(AssetBrowser.isMethod("moveFolder"))
            eval(AssetBrowser @ ".moveFolder(\""@%originFolder@"\",\""@%destination@"\");");
      }
      else
      {
         %assetId = %moduleName @ ":" @ %assetName;
         %assetDef = AssetDatabase.acquireAsset(%assetId);
         %assetType = AssetDatabase.getAssetType(%assetId);
         
         //Do any cleanup required given the type
         if(AssetBrowser.isMethod("move"@%assetType))
         {
            %command = AssetBrowser @ ".move" @ %assetType @ "(" @ %assetDef @ ",\"" @ %destination @ "\");";
            eval(AssetBrowser @ ".move" @ %assetType @ "(" @ %assetDef @ ",\"" @ %destination @ "\");");
         }
      }
      
      AssetBrowser.refresh();
   }
}

function EWorldEditor::onControlDropped( %this, %payload, %position )
{
   Canvas.popDialog(EditorDragAndDropLayer);
   
   // Make sure this is a color swatch drag operation.
   if( !%payload.parentGroup.isInNamespaceHierarchy( "AssetPreviewControlType_AssetDrop" ) )
      return;

   // If dropped on same button whence we came from,
   // do nothing.

   if( %payload.dragSourceControl == %this )
      return;

   %assetType = %payload.assetType;
   
   %pos = EWCreatorWindow.getCreateObjectPosition(); //LocalClientConnection.camera.position; 
   %module = %payload.moduleName;
   %asset = %payload.assetName;
   
   if(AssetBrowser.isMethod("on" @ %assetType @ "EditorDropped"))
   {
      if(%assetType $= "Datablock")
      {
         %buildCommand = AssetBrowser @ ".on" @ %assetType @ "EditorDropped(" @ %asset @ ",\"" @ %position @ "\");";
      }
      else
      {
         %assetDef = AssetDatabase.acquireAsset(%module @ ":" @ %asset);
         %buildCommand = AssetBrowser @ ".on" @ %assetType @ "EditorDropped(" @ %assetDef @ ",\"" @ %position @ "\");";
      }
      eval(%buildCommand);
   }
   
   /*if(%assetType $= "ImageAsset")
   {
      echo("WorldEditor::onControlDropped - dropped an ImageAsset onto the editor window. Todo: Implement dropping image/material into scene");  
   }
   else if(%assetType $= "ShapeAsset")
   {
      echo("DROPPED A SHAPE ON THE EDITOR WINDOW!"); 
      
      /*%staticShapeObjDef = AssetDatabase.acquireAsset("Core_GameObjects:StaticShapeObject");
      
      %newEntity = %staticShapeObjDef.createObject();
      
      %newEntity.position = %pos;
      %newEntity-->MeshComponent.MeshAsset = %module @ ":" @ %asset;
      
      %newEntity.dirtyGameObject = true; //because if we're specifically setting the mesh asset, it's dirty*/
      
      /*%newEntity = new TSStatic()
      {
         position = %pos;
         shapeAsset = %module @ ":" @ %asset;
      };
      
      getScene(0).add(%newEntity);
      
      EWorldEditor.clearSelection();
      EWorldEditor.selectObject(%newEntity);
   }
   else if(%assetType $= "MaterialAsset")
   {
      echo("WorldEditor::onControlDropped - dropped an MaterialAsset onto the editor window. Todo: Implement dropping image/material into scene"); 
   }
   else if(%assetType $= "GameObjectAsset")
   {
      echo("WorldEditor::onControlDropped - dropped an GameObjectAsset onto the editor window.");  
      
      %goAssetDef = AssetDatabase.acquireAsset(%module @ ":" @%asset);
      
      AssetBrowser.dragAndDropGameObjectAsset(%goAssetDef, EWorldEditor);
   }
   else if(%assetType $= "ComponentAsset")
   {
      %newEntity = new Entity()
      {
         position = %pos;
      };
      
      %assetDef = AssetDatabase.acquireAsset(%module @ ":" @ %asset);
      
      if(%assetDef.componentClass $= "Component")
         eval("$tmpVar = new " @ %assetDef.componentClass @ "() { class = " @ %assetDef.componentName @ "; }; %newEntity.add($tmpVar);");
      else
         eval("$tmpVar = new " @ %assetDef.componentClass @ "() {}; %newEntity.add($tmpVar);");
         
      getScene(0).add(%newEntity);
      
      EWorldEditor.clearSelection();
      EWorldEditor.selectObject(%newEntity);
   }
   else if(%assetType $= "ScriptAsset") //do we want to do it this way?
   {
      %newEntity = new Entity()
      {
         position = %pos;
         class = %asset;
      };

      getScene(0).add(%newEntity);
      
      EWorldEditor.clearSelection();
      EWorldEditor.selectObject(%newEntity);
   }*/
   
   EWorldEditor.isDirty = true;
}

function AssetBrowserFilterTree::onControlDropped( %this, %payload, %position )
{
   Canvas.popDialog(EditorDragAndDropLayer);
   
   if( !%payload.parentGroup.isInNamespaceHierarchy( "AssetPreviewControlType_AssetDrop" ) )
      return;
      
   %assetType = %payload.assetType;
   %assetName = %payload.assetName;
   %moduleName = %payload.moduleName;
   
   echo("DROPPED A " @ %assetType @ " ON THE ASSET BROWSER NAVIGATION TREE!");
   
   %item = %this.getItemAtPosition(%position);
   
   echo("DROPPED IT ON ITEM " @ %item);
   
   %parent = %this.getParentItem(%item);
   
   if(%item != 1)
   {
      //we're a folder entry, cool
      %path = %this.getItemValue(%item) @ "/" @ %this.getItemText(%item);
      echo("DROPPED IT ON PATH " @ %path);  
      
      if(%path !$= AssetBrowser.dirHandler.CurrentAddress)
      {
         //we're trying to move the asset to a different module!
         //toolsMessageBoxYesNo( "Move Asset", "Do you wish to move asset " @ %assetName @ " to " @ %path @ "?", 
         //      "AssetBrowser.moveAsset(\""@ %moduleName @ ":" @ %assetName @"\", \""@%path@"\");", ""); 
         
         if(%assetType $= "Folder")
         {
            %originFolder = %moduleName @ "/" @ %assetName;
            %path = %path @ "/" @ %assetName;
            
            //Do any cleanup required given the type
            if(AssetBrowser.isMethod("moveFolder"))
               eval(AssetBrowser @ ".moveFolder(\""@%originFolder@"\",\""@%path@"\");");
         }
         else
         {
            %assetId = %moduleName @ ":" @ %assetName;
            %assetDef = AssetDatabase.acquireAsset(%assetId);
            %assetType = AssetDatabase.getAssetType(%assetId);
            
            //Do any cleanup required given the type
            if(AssetBrowser.isMethod("move"@%assetType))
            {
               %command = AssetBrowser @ ".move" @ %assetType @ "(" @ %assetDef @ ",\"" @ %path @ "\");";
               eval(AssetBrowser @ ".move" @ %assetType @ "(" @ %assetDef @ ",\"" @ %path @ "\");");
            }
         }
      }
   }
}

function AssetBrowserFilterTree::onDragDropped( %this )
{
   %asdgadfhg =true;
}

function AssetBrowser::hasLooseFilesInDir(%this)
{
   //First, wipe out any files inside the folder first
   %file = findFirstFileMultiExpr( %this.dirHandler.currentAddress @ "/*.*", false);
   
   %aq = new AssetQuery();

   while( %file !$= "" )
   {      
      if(!strIsMatchExpr("*.asset.taml", %file) && !strIsMatchExpr("*.taml", %file) && !strIsMatchExpr("*.cached.dts", %file))
      {
         %assetsFound = AssetDatabase.findAssetLooseFile(%aq, %file);
         
         if(%assetsFound == 0)
         {
            %ext = fileExt(%file);
            if(isShapeFormat(%ext) || isImageFormat(%ext) || isSoundFormat(%ext))
            {
               %aq.delete();
               return true; 
            }
         }
      }
      
      %file = findNextFileMultiExpr( %this.dirHandler.currentAddress @ "/*.*" );
   }
   
   %aq.delete();
   return false;
}

function AssetBrowser::autoImportSimpleLooseFiles(%this)
{
   %importer = new AssetImporter();
   
   //First, wipe out any files inside the folder first
   %file = findFirstFileMultiExpr( %this.dirHandler.currentAddress @ "/*.*", false);
   
   %aq = new AssetQuery();

   while( %file !$= "" )
   {      
      if(!strIsMatchExpr("*.asset.taml", %file) && !strIsMatchExpr("*.taml", %file) && !strIsMatchExpr("*.cached.dts", %file))
      {
         %assetsFound = AssetDatabase.findAssetLooseFile(%aq, %file);
         
         if(%assetsFound == 0)
         {
            %ext = fileExt(%file);
            if(isShapeFormat(%ext) || isImageFormat(%ext) || isSoundFormat(%ext))
            {
               %assetId = %importer.autoImportFile(%file);  
            }
         }
      }
      
      %file = findNextFileMultiExpr( %this.dirHandler.currentAddress @ "/*.*" );
   }
   
   %aq.delete();
   %importer.delete(); 
   
   %this.refresh();
}

function AssetBrowser::getLooseFilesInDir(%this)
{
   if(!isObject(ABLooseFileArray))
      new ArrayObject(ABLooseFileArray);
      
   ABLooseFileArray.empty();
   
   %showLooseFiles = EditorSettings.value("Assets/Browser/showLooseFiles", false);
   if(%showLooseFiles == false)
      return;
      
   //First, wipe out any files inside the folder first
   %file = findFirstFileMultiExpr( %this.dirHandler.currentAddress @ "/*.*", false);
   
   %aq = new AssetQuery();

   while( %file !$= "" )
   {      
      if(!strIsMatchExpr("*.asset.taml", %file) && !strIsMatchExpr("*.taml", %file) && !strIsMatchExpr("*.cached.dts", %file))
      {
         %assetsFound = AssetDatabase.findAssetLooseFile(%aq, %file);
         
         if(%assetsFound == 0)
         {
            ABLooseFileArray.add(%file);
         }
      }
      
      %file = findNextFileMultiExpr( %this.dirHandler.currentAddress @ "/*.*" );
   }
   
   %aq.delete();
   return false;
}
//
//
function AssetBrowser::importLooseFiles(%this)
{
   echo("Adding loose files at directory " @ %this.dirHandler.currentAddress);
   LooseFileAuditWindow.showDialog(%this.dirHandler.currentAddress);  
}