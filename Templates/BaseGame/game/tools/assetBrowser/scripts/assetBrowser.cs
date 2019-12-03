new SimGroup(AssetBrowserPreviewCache);

//AssetBrowser.addToolbarButton
function AssetBrowser::addToolbarButton(%this)
{
	%filename = expandFilename("tools/gui/images/iconOpen");
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
		bitmapMode = "Centered";
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
      
   %this.importingFilesArray = new ArrayObject();
   %this.importAssetUnprocessedListArray = new ArrayObject();
   %this.importAssetFinalListArray = new ArrayObject();
   %this.isReImportingAsset = false;
   
   %this.coreModulesFilter = false;
   %this.toolsModulesFilter = false;
   %this.onlyShowModulesWithAssets = false;
   
   %this.folderPanelState = true;
   %this.folderPanelSplit = 0;
   
   %this.templateFilesPath = "tools/assetBrowser/scripts/templateFiles/";
   
   //First, build our our list of active modules
   %modulesList = ModuleDatabase.findModules(true);
   
   %nonDefaultModuleCount = 0;
   
   for(%i=0; %i < getWordCount(%modulesList); %i++)
   {
      %moduleName = getWord(%modulesList, %i).ModuleId;
      
      %moduleGroup = getWord(%modulesList, %i).Group;
      if((%moduleGroup $= "Core" || %moduleGroup $= "Tools") && !%this.coreModulesFilter)
         continue;
         
      %nonDefaultModuleCount++;
   }
   
   if(%nonDefaultModuleCount == 0)
   {
      MessageBoxYesNo( "Import Template Content?",
         "You have no modules or content. Do you want to import a module from the template content?",
         "AssetBrowser.ImportTemplateModules();", "" );
   }
   
   %this.setPreviewSize(EditorSettings.value("Assets/Browser/previewTileSize", "small"));
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
   
   BrowserVisibilityPopup.checkItem(0,%newVal);
   
   EditorSettings.setValue("Assets/Browser/showCoreModule", %newVal);
    
   AssetBrowser.refresh();
}

function AssetBrowser::viewToolsModulesFilter(%this)
{
   %oldVal = EditorSettings.value("Assets/Browser/showToolsModule", false);
   %newVal = !%oldVal;
   
   BrowserVisibilityPopup.checkItem(1,%newVal);
   
   EditorSettings.setValue("Assets/Browser/showToolsModule", %newVal);
    
   AssetBrowser.refresh();
}

function AssetBrowser::viewPopulatedModulesFilter(%this)
{
   %oldVal = EditorSettings.value("Assets/Browser/showOnlyPopulatedModule", false);
   %newVal = !%oldVal;
   
   BrowserVisibilityPopup.checkItem(2,%newVal);
   
   EditorSettings.setValue("Assets/Browser/showOnlyPopulatedModule", %newVal);
    
   AssetBrowser.refresh();
}

function AssetBrowser::toggleShowingFolders(%this)
{
   %oldVal = EditorSettings.value("Assets/Browser/showFolders", false);
   %newVal = !%oldVal;
   
   BrowserVisibilityPopup.checkItem(4,%newVal);
   
   EditorSettings.setValue("Assets/Browser/showFolders", %newVal);
    
   AssetBrowser.refresh();
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
      AssetBrowser.toggleAssetTypeFilter(0);  
   }
   
   if(%selectCallback $= "")
   {
      //we're not in selection mode, so just hide the select button
      %this-->SelectButton.setHidden(true);  
   }
   else
   {
      %this-->SelectButton.setHidden(false); 
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

function AssetBrowser::buildPreviewArray( %this, %asset, %moduleName )
{
   if(!isObject(%this.previewData))
   {
      %this.previewData = new ScriptObject();      
   }
   
   AssetPreviewArray.empty();
   
   %previewImage = "core/art/warnmat";
   
   if(ModuleDatabase.findModule(%moduleName, 1) !$= "")
   {
      %assetDesc = AssetDatabase.acquireAsset(%asset);
      %assetName = AssetDatabase.getAssetName(%asset);
      %assetType = AssetDatabase.getAssetType(%asset);
      
   }
   else
   {
      %fullPath = %moduleName !$= "" ? %moduleName @ "/" @ %asset : %asset;
      %fullPath = strreplace(%fullPath, "/", "_");
      
      if(isObject(%fullPath))
      
         %assetDesc = %fullPath;
      else
         %assetDesc = new ScriptObject(%fullPath);
         
      %assetDesc.dirPath = %moduleName;
      %assetDesc.assetName = %asset;
      %assetDesc.description = %moduleName @ "/" @ %asset;
      %assetDesc.assetType = "Folder";
      
      %assetName = %asset;
      %assetType = "Folder";
   }

   %previewSize = %this.previewSize SPC %this.previewSize;
   %previewBounds = 20;
   
   %tooltip = %assetName;
   
   %doubleClickCommand = "AssetBrowser.editAsset( "@%assetDesc@" );";
   
   if(%assetType $= "ShapeAsset")
   {
      %previewButton = AssetPreviewButtonsTemplate-->ShapeAssetPreviewButton.deepClone();
   }
   else
   {
      %previewButton = AssetPreviewButtonsTemplate-->GeneralAssetPreviewButton.deepClone();
   }
   
   %previewButton.extent = %previewSize.x + %previewBounds SPC %previewSize.y + %previewBounds + 24;
   %previewButton.assetName = %assetName;
   %previewButton.moduleName = %moduleName;
   %previewButton.assetType = %assetType;
   
   //Build out the preview
   %buildCommand = %this @ ".build" @ %assetType @ "Preview(" @ %assetDesc @ "," @ %this.previewData @ ");";
   eval(%buildCommand);
   
   //debug dump
   %tooltip = %this.previewData.tooltip;
   %assetName = %this.previewData.assetName;
   %previewImage = %this.previewData.previewImage;
   %doubleClickCommand = %this.previewData.doubleClickCommand;
   
   if(%assetType $= "ShapeAsset")
   {
      %previewButton-->shapeAssetView.setModel(%previewImage);
      %previewButton-->shapeAssetView.extent = %previewSize;
   }
   else
   {
      %previewButton-->assetPreviewImage.bitmap = %this.previewData.previewImage;
      %previewButton-->assetPreviewImage.extent = %previewSize;
   }
   
   %previewButton-->AssetPreviewBorderButton.extent = %previewSize;
   
   //%previewButton-->AssetPreviewButton.internalName = %this.previewData.assetName@"Border";
   %previewButton-->AssetPreviewButton.extent = %previewSize.x + %previewBounds SPC %previewSize.y + 24;
   %previewButton-->AssetPreviewButton.tooltip = %this.previewData.tooltip;
   %previewButton-->AssetPreviewButton.Command = "AssetBrowser.updateSelection( $ThisControl.getParent().assetName, $ThisControl.getParent().moduleName );";
   %previewButton-->AssetPreviewButton.altCommand = %this.previewData.doubleClickCommand;
   //%previewButton-->AssetPreviewButton.icon = %this.previewData.previewImage;
   
   %previewButton-->AssetNameLabel.position = 0 SPC %previewSize.y + %previewBounds - 16;
   %previewButton-->AssetNameLabel.extent = %previewSize.x + %previewBounds SPC 16;
   %previewButton-->AssetNameLabel.text = %this.previewData.assetName;
   %previewButton-->AssetNameLabel.originalAssetName = %this.previewData.assetName;

   // add to the gui control array
   AssetBrowser-->assetList.add(%previewButton);
   
   // add to the array object for reference later
   AssetPreviewArray.add( %previewButton, %this.previewData.previewImage );
}

function AssetBrowser::refresh(%this)
{
   %this.navigateTo(%this.dirHandler.currentAddress);  
}
//
//
function AssetPreviewButton::onClick(%this)
{
   echo("CLICKED AN ASSET PREVIEW BUTTON");
}

function AssetPreviewButton::onDoubleClick(%this)
{
   echo("DOUBLE CLICKED AN ASSET PREVIEW BUTTON");
}
//
//

function AssetBrowser::loadDirectories( %this )
{
   AssetBrowser-->filterTree.clear();
   
   %dataItem = AssetBrowser-->filterTree.insertItem(0, "Data");
   %this.dirHandler.loadFolders("Data", %dataItem);
   
   //If set to, show core
   if(%this.coreModulesFilter)
   {
      %coreItem = AssetBrowser-->filterTree.insertItem(0, "Core");
      %this.dirHandler.loadFolders("Core", %coreItem);
   }
   
   //If set to, show tools
   if(%this.toolsModulesFilter)
   {
      %toolsItem = AssetBrowser-->filterTree.insertItem(0, "Tools");
      %this.dirHandler.loadFolders("Tools", %toolsItem);
   }
   
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
   
   %dataItem = AssetBrowser-->filterTree.findItemByName("Data");
   AssetBrowser-->filterTree.expandItem(%dataItem);
   
   AssetBrowser.dirHandler.expandTreeToAddress(AssetBrowser.dirHandler.currentAddress);
   
   %selectedItem = AssetBrowser.dirHandler.getFolderTreeItemFromAddress(AssetBrowser.dirHandler.currentAddress);
   AssetBrowser-->filterTree.scrollVisibleByObjectId(%selectedItem);
   
   AssetBrowser-->filterTree.buildVisibleTree(); 
   
   AssetBrowser.refresh();
}

function AssetBrowser::updateSelection( %this, %asset, %moduleName )
{
   //If we're navigating a folder, just nav to it and be done
   /*if(isDirectory(%moduleName))
   {
      AssetBrowser.navigateTo(%moduleName @ "/" @ %asset);
      return;
   }*/
   
   %isAssetBorder = 0;
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
   }
   
   AssetBrowser.selectedMaterial = %asset;
   AssetBrowser.selectedAsset = %moduleName@":"@%asset;
   AssetBrowser.selectedAssetDef = AssetDatabase.acquireAsset(AssetBrowser.selectedAsset);
   //AssetBrowser.selectedPreviewImagePath = %previewImagePath;
   
   %this.prevSelectedMaterialHL = %asset;
}

//
//needs to be deleted with the persistence manager and needs to be blanked out of the matmanager
//also need to update instances... i guess which is the tricky part....
function AssetBrowser::showDeleteDialog( %this )
{
   %material = AssetBrowser.selectedMaterial;
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
      MessageBoxYesNoCancel("Delete Material?", 
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
function AssetPreviewButton::onRightClick(%this)
{
   AssetBrowser.selectedAssetPreview = %this.getParent();
   EditAssetPopup.assetId = %this.getParent().moduleName @ ":" @ %this.getParent().assetName;
   EditAssetPopup.assetType = %this.getParent().assetType;
   %assetType = %this.getParent().assetType;
   
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
      EditFolderPopup.dirPath = %this.getParent().assetPath;
      EditFolderPopup.showPopup(Canvas);  
   }
   else
      EditAssetPopup.showPopup(Canvas);  
      
   if(%assetType $= "Folder")
   {
      EditAssetPopup.assetId = %this.getParent().moduleName @ "/" @ %this.getParent().assetName;
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
   if( %this.getSelectedItemsCount() > 0 && %itemId != 1)
   {
      //AddNewAssetPopup.showPopup(Canvas);  
      
      //We have something clicked, so figure out if it's a sub-filter or a module filter, then push the correct
      //popup menu
      if(%this.getParentItem(%itemId) == 1)
      {
         //yep, module, push the all-inclusive popup  
         EditModulePopup.showPopup(Canvas); 
         //also set the module value for creation info
         AssetBrowser.selectedModule = %this.getItemText(%itemId);
      }
      else
      {
         EditFolderPopup.showPopup(Canvas);
         EditFolderPopup.assetType = "Folder";  
      }
   }
   else if(%itemId == 1)
   {
      AddNewModulePopup.showPopup(Canvas);
   }
}

//
//
//
function AssetBrowser::showVisibiltyOptions(%this)
{
   BrowserVisibilityPopup.showPopup(Canvas);
}

function AssetBrowser::showFilterOptions(%this)
{
   
}

//
//
// Preview tile handling
function AssetBrowser::setPreviewSize(%this, %size)
{
   AssetPreviewSizePopup.checkItem(0, false);
   AssetPreviewSizePopup.checkItem(1, false);
   AssetPreviewSizePopup.checkItem(2, false);
   
   %this.previewSize = 80; //default to small
   
   if(%size $= "Small")
   {
      %this.previewSize = 80;
      AssetPreviewSizePopup.checkItem(0, true);
   }
   else if(%size $= "Medium")
   {
      %this.previewSize = 120;
      AssetPreviewSizePopup.checkItem(1, true);
   }
   else if(%size $= "Large")
   {
      %this.previewSize = 160;
      AssetPreviewSizePopup.checkItem(2, true);
   }
   
   EditorSettings.setValue("Assets/Browser/previewTileSize", %size);
      
   %this.rebuildAssetArray();
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

function AssetBrowser::rebuildAssetArray(%this)
{
   %breadcrumbPath = AssetBrowser.dirHandler.currentAddress;
   
   // we have to empty out the list; so when we create new guicontrols, these dont linger
   AssetBrowser-->assetList.deleteAllObjects();
   AssetPreviewArray.empty();

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
       
       if(%assetBasePath $= %breadcrumbPath)
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
			
			%validType = false;
         
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
         }
			
			/*if(%this.getItemText(%itemId) $= %assetType || (%assetType $= "" && %this.getItemText(%itemId) $= "Misc")
			   || %moduleItemId == 1)
			{*/
				//stop adding after previewsPerPage is hit
				%assetName = AssetDatabase.getAssetName(%assetId);
				
				%searchText = AssetBrowserSearchFilter.getText();
				if(%searchText !$= "Search Assets...")
				{
					if(strstr(strlwr(%assetName), strlwr(%searchText)) != -1)
					{
						%assetArray.add( %moduleName, %assetId);
						
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
			//}
       }
   }
   
   //Add folders
   if(EditorSettings.value("Assets/Browser/showFolders", true) == true)
   {
      %folders = getDirectoryList(%breadcrumbPath);
      for(%f=0; %f < getFieldCount(%folders); %f++)
      {
         %folderName = getField(%folders, %f);
         
         %searchText = AssetBrowserSearchFilter.getText();
         if(%searchText !$= "Search Assets...")
         {
            if(strstr(strlwr(%folderName), strlwr(%searchText)) != -1)
                     %assetArray.add( %breadcrumbPath, %folderName );
         }
         else
         {
            //got it.	
            %assetArray.add( %breadcrumbPath, %folderName );
         }
      }
   }

	AssetBrowser.currentPreviewPage = 0;
	AssetBrowser.totalPages = 1;
	
	for(%i=0; %i < %assetArray.count(); %i++)
		AssetBrowser.buildPreviewArray( %assetArray.getValue(%i), %assetArray.getKey(%i) );  
		
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
      
      if(!%validType)
         continue;
   }
   else
   {
      %activeTypeFilterList = AssetBrowser.assetTypeFilter;
   }
   
   if(%activeTypeFilterList !$= "")
      AssetBrowser_FooterText.text = AssetBrowser_FooterText.text @ " | Active Type Filters: " @ %activeTypeFilterList;
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

function AssetBrowserSearchFilter::onReturn( %this )
{
   %text = %this.getText();
   if( %text $= "" )
      %this.reset();
   
   AssetBrowser.rebuildAssetArray();
}

function AssetBrowserFolderSearchFilter::reset( %this )
{
   %this.setText( "Search Folders..." );
   
   AssetBrowser.refresh();
}

function AssetBrowserSearchFilter::reset( %this )
{
   %this.setText( "Search Assets..." );
   
   AssetBrowser.rebuildAssetArray();
}

function AssetBrowser_ClearFolderFilterBtn::onClick( %this )
{
   AssetBrowserFolderSearchFilter.reset();
}

function AssetBrowser_ClearAssetFilterBtn::onClick( %this )
{
   AssetBrowserSearchFilter.reset();
}

//
//
// Navigation
function AssetBrowser::navigateTo(%this, %address, %historyNav)
{
   //Don't bother navigating if it's to the place we already are
   if(AssetBrowser.dirHandler.currentAddress !$= %address)
   {
      AssetBrowser.dirHandler.navigateTo(%address, %historyNav);
         
      %this.updateNavigationBreadcrumb(%address);
      
      %module = AssetBrowser.dirHandler.getModuleFromAddress(%address);
      if(%module !$= "")
      {
         //legit module, so set it as current target
         AssetBrowser.SelectedModule = %module.moduleId;
      }
   }
   
   %this.rebuildAssetArray();
}

function AssetBrowser::navigateHistoryForward(%this)
{
   %this.dirHandler.navigateHistoryForward();
   
   %this.updateNavigationBreadcrumb();
   
   %module = AssetBrowser.dirHandler.getModuleFromAddress(%address);
   if(%module !$= "")
   {
      //legit module, so set it as current target
      AssetBrowser.SelectedModule = %module.moduleId;
   }
   
   %this.rebuildAssetArray();
}

function AssetBrowser::navigateHistoryBack(%this)
{
   %this.dirHandler.navigateHistoryBack();
      
   %this.updateNavigationBreadcrumb();
   
   %module = AssetBrowser.dirHandler.getModuleFromAddress(%address);
   if(%module !$= "")
   {
      //legit module, so set it as current target
      AssetBrowser.SelectedModule = %module.moduleId;
   }
   
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
function AssetPreviewButton::onMouseDragged(%this)
{
   %payload = new GuiBitmapButtonCtrl();
   %payload.assignFieldsFrom( %this );
   %payload.className = "AssetPreviewControl";
   %payload.position = "0 0";
   %payload.dragSourceControl = %this;
   %payload.bitmap = %this.icon;
   %payload.extent.x /= 2;
   %payload.extent.y /= 2;
   
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
}

function AssetPreviewButton::onControlDragCancelled(%this)
{
   Canvas.popDialog(EditorDragAndDropLayer);
}

function AssetPreviewButton::onControlDropped( %this, %payload, %position )
{
   Canvas.popDialog(EditorDragAndDropLayer);
   
   // Make sure this is a color swatch drag operation.
   if( !%payload.parentGroup.isInNamespaceHierarchy( "AssetPreviewControlType_AssetDrop" ) )
      return;

   // If dropped on same button whence we came from,
   // do nothing.

   if( %payload.dragSourceControl == %this )
      return;

   // If a swatch button control is dropped onto this control,
   // copy it's color.

   if( %payload.isMemberOfClass( "AssetPreviewButton" ) )
   {
      // If the swatch button is part of a color-type inspector field,
      // remember the inspector field so we can later set the color
      // through it.

      if( %this.parentGroup.isMemberOfClass( "GuiInspectorTypeColorI" ) )
         %this.parentGroup.apply( ColorFloatToInt( %payload.color ) );
      else if( %this.parentGroup.isMemberOfClass( "GuiInspectorTypeColorF" ) )
         %this.parentGroup.apply( %payload.color );
      else
         %this.setColor( %payload.color );
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

   %assetType = %payload.dragSourceControl.parentGroup.assetType;
   
   %pos = EWCreatorWindow.getCreateObjectPosition(); //LocalClientConnection.camera.position; 
   %module = %payload.dragSourceControl.parentGroup.moduleName;
   %asset = %payload.dragSourceControl.parentGroup.assetName;
   
   if(AssetBrowser.isMethod("on" @ %assetType @ "EditorDropped"))
   {
      %assetDef = AssetDatabase.acquireAsset(%module @ ":" @ %asset);
      %buildCommand = AssetBrowser @ ".on" @ %assetType @ "EditorDropped(" @ %assetDef @ ",\"" @ %position @ "\");";
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
      
   %assetType = %payload.dragSourceControl.parentGroup.assetType;
   %assetName = %payload.dragSourceControl.parentGroup.assetName;
   %moduleName = %payload.dragSourceControl.parentGroup.moduleName;
   
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
         MessageBoxYesNo( "Move Asset", "Do you wish to move asset " @ %assetName @ " to " @ %path @ "?", 
               "AssetBrowser.moveAsset(\""@ %moduleName @ ":" @ %assetName @"\", \""@%path@"\");", "");  
      }
   }
}

function AssetBrowserFilterTree::onDragDropped( %this )
{
   %asdgadfhg =true;
}
