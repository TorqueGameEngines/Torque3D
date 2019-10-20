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
      
   if(!isObject(ImportAssetTree))
      new GuiTreeViewCtrl(ImportAssetTree);
      
   if(!isObject(AssetBrowser_NavPrevHistoryList))
   {
      new ArrayObject(AssetBrowser_NavPrevHistoryList);
   }
   if(!isObject(AssetBrowser_NavForeHistoryList))
   {
      new ArrayObject(AssetBrowser_NavForeHistoryList);
   }
      
   %this.importingFilesArray = new ArrayObject();
   %this.importAssetUnprocessedListArray = new ArrayObject();
   %this.importAssetFinalListArray = new ArrayObject();
   
   %this.isReImportingAsset = false;
   %this.coreModulesFilter = false;
   %this.toolsModulesFilter = false;
   %this.onlyShowModulesWithAssets = false;
   %this.treeFilterMode = "list";
   
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
    
   AssetBrowser.loadFilters();
}

function AssetBrowser::viewToolsModulesFilter(%this)
{
   %oldVal = EditorSettings.value("Assets/Browser/showToolsModule", false);
   %newVal = !%oldVal;
   
   BrowserVisibilityPopup.checkItem(1,%newVal);
   
   EditorSettings.setValue("Assets/Browser/showToolsModule", %newVal);
    
   AssetBrowser.loadFilters();
}

function AssetBrowser::viewPopulatedModulesFilter(%this)
{
   %oldVal = EditorSettings.value("Assets/Browser/showOnlyPopulatedModule", false);
   %newVal = !%oldVal;
   
   BrowserVisibilityPopup.checkItem(2,%newVal);
   
   EditorSettings.setValue("Assets/Browser/showOnlyPopulatedModule", %newVal);
    
   AssetBrowser.loadFilters();
}

function AssetBrowser::toggleShowingFolders(%this)
{
   %oldVal = EditorSettings.value("Assets/Browser/showFolders", false);
   %newVal = !%oldVal;
   
   BrowserVisibilityPopup.checkItem(4,%newVal);
   
   EditorSettings.setValue("Assets/Browser/showFolders", %newVal);
    
   AssetBrowser.loadFilters();
}

function AssetBrowser::toggleShowingEmptyFolders(%this)
{
   %oldVal = EditorSettings.value("Assets/Browser/showEmptyFolders", false);
   %newVal = !%oldVal;
   
   BrowserVisibilityPopup.checkItem(5,%newVal);
   
   EditorSettings.setValue("Assets/Browser/showEmptyFolders", %newVal);
    
   AssetBrowser.loadFilters();
}

function AssetBrowser::viewListFilter(%this)
{
   %this.treeFilterMode = "list";
   AssetBrowser.loadFilters();
}

function AssetBrowser::viewTagsFilter(%this)
{
   %this.treeFilterMode = "tags";
   AssetBrowser.loadFilters();
}

function AssetBrowser::toggleAssetTypeFilter(%assetTypeIdx)
{
   %isChecked = AssetTypeListPopup.isItemChecked(%assetTypeIdx);
   AssetTypeListPopup.checkItem(%assetTypeIdx, !%isChecked);
}

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
   
   if(%selectCallback $= "")
   {
      //we're not in selection mode, so just hide the select button
      %this-->SelectButton.setHidden(true);  
   }
   else
   {
      %this-->SelectButton.setHidden(false); 
   }
   
   //AssetBrowser_importAssetWindow.setVisible(0);
   //AssetBrowser_importAssetConfigWindow.setVisible(0);
   AssetBrowser.loadFilters();
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
      
   // it may seem goofy why the checkbox can't be instanciated inside the container
   // reason being its because we need to store the checkbox ctrl in order to make changes
   // on it later in the function. 
   
   
   %previewSize = %this.previewSize SPC %this.previewSize;
   %previewBounds = 20;
   
   %container = new GuiControl(){
      profile = "ToolsGuiDefaultProfile";
      Position = "0 0";
      Extent = %previewSize.x + %previewBounds SPC %previewSize.y + %previewBounds + 24;
      HorizSizing = "right";
      VertSizing = "bottom";
      isContainer = "1";
      assetName = %assetName;
      moduleName = %moduleName;
      assetType = %assetType;
   };

   %tooltip = %assetName;
   
   %doubleClickCommand = "AssetBrowser.editAsset( "@%assetDesc@" );";
   
   if(%assetType $= "ShapeAsset")
   {
      %this.previewData.assetName = %assetDesc.assetName;
      %this.previewData.assetPath = %assetDesc.scriptFile;
      %this.previewData.doubleClickCommand = %doubleClickCommand;
      
      %this.previewData.previewImage = "tools/assetBrowser/art/componentIcon";
      
      %this.previewData.assetFriendlyName = %assetDesc.friendlyName;
      %this.previewData.assetDesc = %assetDesc.description;
      %this.previewData.tooltip = %assetDesc.friendlyName @ "\n" @ %assetDesc;
   
      %previewButton = new GuiObjectView()
      {
         className = "AssetPreviewControl";
         internalName = %matName;
         HorizSizing = "right";
         VertSizing = "bottom";
         Profile = "ToolsGuiDefaultProfile";
         position = "7 4";
         extent = %previewSize;
         MinExtent = "8 8";
         canSave = "1";
         Visible = "1";
         tooltipprofile = "ToolsGuiToolTipProfile";
         hovertime = "1000";
         Margin = "0 0 0 0";
         Padding = "0 0 0 0";
         AnchorTop = "1";
         AnchorBottom = "0";
         AnchorLeft = "1";
         AnchorRight = "0";
         renderMissionArea = "0";
         GizmoProfile = "GlobalGizmoProfile";
         cameraZRot = "0";
         forceFOV = "0";
         gridColor = "0 0 0 0";
         renderNodes = "0";
         renderObjBox = "0";
         renderMounts = "0";
         renderColMeshes = "0";
         selectedNode = "-1";
         sunDiffuse = "255 255 255 255";
         sunAmbient = "180 180 180 255";
         timeScale = "1.0";
         fixedDetail = "0";
         orbitNode = "0";
         
         new GuiBitmapButtonCtrl()
         {
            HorizSizing = "right";
            VertSizing = "bottom";
            profile = "ToolsGuiButtonProfile";
            position = "0 0";
            extent = %previewSize;
            Variable = "";
            buttonType = "ToggleButton";
            bitmap = "tools/materialEditor/gui/cubemapBtnBorder";
            groupNum = "0";
            text = "";
         }; 
      };
      
      %assetQuery = new AssetQuery();
      %numAssetsFound = AssetDatabase.findAllAssets(%assetQuery);
      
      for( %i=0; %i < %numAssetsFound; %i++)
      {
          %assetId = %assetQuery.getAsset(%i);
          %name = AssetDatabase.getAssetName(%assetId);
          
          if(%name $= %assetName)
          {
            %asset = AssetDatabase.acquireAsset(%assetId);
            
            %previewButton.setModel(%asset.fileName);
            //%previewButton.refreshShape();
            //%previewButton.currentDL = 0;
            //%previewButton.fitToShape();
            
            break;
          }
      }
   }
   else
   {
      //Build out the preview
      %buildCommand = %this @ ".build" @ %assetType @ "Preview(" @ %assetDesc @ "," @ %this.previewData @ ");";
      eval(%buildCommand);
      
      //debug dump
      %tooltip = %this.previewData.tooltip;
      %assetName = %this.previewData.assetName;
      %previewImage = %this.previewData.previewImage;
      %doubleClickCommand = %this.previewData.doubleClickCommand;
      
      %previewButton = new GuiBitmapButtonCtrl()
      {
         className = "AssetPreviewControl";
         internalName = %this.previewData.assetName;
         HorizSizing = "right";
         VertSizing = "bottom";
         profile = "ToolsGuiButtonProfile";
         position = "10 4";
         extent = %previewSize;
         buttonType = "PushButton";
         bitmap = %this.previewData.previewImage;
         Command = "";
         text = "";
         useStates = false;
         
         new GuiBitmapButtonCtrl()
         {
               HorizSizing = "right";
               VertSizing = "bottom";
               profile = "ToolsGuiButtonProfile";
               position = "0 0";
               extent = %previewSize;
               Variable = "";
               buttonType = "toggleButton";
               bitmap = "tools/materialEditor/gui/cubemapBtnBorder";
               groupNum = "0";
               text = "";
            }; 
      }; 
   }
   
   %previewBorder = new GuiButtonCtrl(){
         class = "AssetPreviewButton";
         internalName = %this.previewData.assetName@"Border";
         HorizSizing = "right";
         VertSizing = "bottom";
         profile = "ToolsGuiThumbHighlightButtonProfile";
         position = "0 0";
         extent = %previewSize.x + %previewBounds SPC %previewSize.y + 24;
         Variable = "";
         buttonType = "radioButton";
         tooltip = %this.previewData.tooltip;
         Command = "AssetBrowser.updateSelection( $ThisControl.getParent().assetName, $ThisControl.getParent().moduleName );"; 
		   altCommand = %this.previewData.doubleClickCommand;
         groupNum = "0";
         useMouseEvents = true;
         text = "";
         icon = %this.previewData.previewImage;
   };
   
   %previewNameCtrl = new GuiTextEditCtrl(){
         position = 0 SPC %previewSize.y + %previewBounds - 16;
         profile = ToolsGuiTextEditCenterProfile;
         extent = %previewSize.x + %previewBounds SPC 16;
         text = %this.previewData.assetName;
         originalAssetName = %this.previewData.assetName; //special internal field used in renaming assets
         internalName = "AssetNameLabel";
         class = "AssetNameField";
         active = false;
      };
   
   %container.add(%previewButton);  
   %container.add(%previewBorder); 
   %container.add(%previewNameCtrl);
   
   // add to the gui control array
   AssetBrowser-->assetList.add(%container);
   
   // add to the array object for reference later
   AssetPreviewArray.add( %previewButton, %this.previewData.previewImage );
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

function AssetBrowser::loadFolders(%this, %path, %parentId)
{
   //utilize home dir project setting here
   %paths = getDirectoryList(%path);
   for(%i=0; %i < getFieldCount(%paths); %i++)
   {
      %childPath = getField(%paths, %i);
      
      %folderCount = getTokenCount(%childPath, "/");
      
      for(%f=0; %f < %folderCount; %f++)
      {
         %folderName = getToken(%childPath, "/", %f);
         
         //we don't need to display the shadercache folder
         if(%parentId == 1 && %folderName $= "shaderCache")
            continue;
         
         %iconIdx = 1;
         
         if(ModuleDatabase.findModule(%folderName) !$= "")
            %iconIdx = 0;
         
         %searchFoldersText = AssetBrowserFolderSearchFilter.getText();
         if(%searchFoldersText !$= "Search Folders...")
         {
            if(strstr(strlwr(%folderName), strlwr(%searchFoldersText)) != -1)
            {
               %folderID = AssetBrowser-->filterTree.insertItem(%parentId, %folderName, %path, "", %iconIdx, %iconIdx);
         
            %this.loadFolders(%path @ "/" @ %folderName, %folderID);  
            }
         }
         else
         {
            %folderID = AssetBrowser-->filterTree.insertItem(%parentId, %folderName, %path, "", %iconIdx, %iconIdx);
         
            %this.loadFolders(%path @ "/" @ %folderName, %folderID);
         }
      }
   }
}

function AssetBrowser::loadFilters( %this )
{
   AssetBrowser-->filterTree.clear();

   AssetBrowser-->filterTree.buildIconTable( "tools/classIcons/Prefab" @
                                             ":tools/classIcons/SimSet");
   
   %dataItem = AssetBrowser-->filterTree.insertItem(0, "Data");
   %this.loadFolders("Data", %dataItem);
   
   //If set to, show core
   if(%this.coreModulesFilter)
   {
      %coreItem = AssetBrowser-->filterTree.insertItem(0, "Core");
      %this.loadFolders("Core", %coreItem);
   }
   
   //If set to, show tools
   if(%this.toolsModulesFilter)
   {
      %toolsItem = AssetBrowser-->filterTree.insertItem(0, "Tools");
      %this.loadFolders("Tools", %toolsItem);
   }

   //AssetBrowser-->filterTree.insertItem(0, "Data");
   
   //get it alllll
   /*%directoryDump = getDirectoryList("data", -1);
   
   %dirs = getFieldCount(%directoryDump);
   
   for(%i=0; %i < %dirs; %i++)
   {
      %folderName = getToken(%assetBasePath, "/", %f);

      %folderID = AssetBrowser-->filterTree.findChildItemByName(%prevFolderID, %folderName);

      if(%folderID == -1 || %folderID == 0)
      {
         %pathCache = "";
         
         for(%c=0; %c < %f; %c++)
         {
            %pathCache = %c == 0 ? getToken(%assetBasePath, "/", %c) : %pathCache @ "/" @ getToken(%assetBasePath, "/", %c);
         }
         
         %folderID = AssetBrowser-->filterTree.insertItem(%prevFolderID, %folderName, %pathCache, "", 1, 1);
      }
   }*/
   
   AssetPreviewArray.empty();
   
   /*%assetQuery = new AssetQuery();
   %numAssetsFound = AssetDatabase.findAllAssets(%assetQuery);
   
   for( %i=0; %i < %numAssetsFound; %i++)
   {
       %assetId = %assetQuery.getAsset(%i);
       
       %assetPath = makeRelativePath(AssetDatabase.getAssetFilePath(%assetId));
       
       //clean up the path
       %assetPath = strreplace(%assetPath, "\\\\", "\\");
       %assetPath = strreplace(%assetPath, "\\", "\\");
       %assetPath = strreplace(%assetPath, "//", "\\");
       
       %assetBasePath = filePath(%assetPath);
       
       %foldersCount = getTokenCount(%assetBasePath, "/");
       
       //Build our directory structure
       %prevFolderID = 0;
       for(%f=0; %f < %foldersCount; %f++)
       {
         %folderName = getToken(%assetBasePath, "/", %f);

         %folderID = AssetBrowser-->filterTree.findChildItemByName(%prevFolderID, %folderName);

         if(%folderID == -1 || %folderID == 0)
         {
            %pathCache = "";
            
            for(%c=0; %c < %f; %c++)
            {
               %pathCache = %c == 0 ? getToken(%assetBasePath, "/", %c) : %pathCache @ "/" @ getToken(%assetBasePath, "/", %c);
            }
            
            %folderID = AssetBrowser-->filterTree.insertItem(%prevFolderID, %folderName, %pathCache, "", 1, 1);
         }

         %prevFolderID = %folderID;
       }
       
      //first, get the asset's module, as our major categories
      %module = AssetDatabase.getAssetModule(%assetId);
      
      %moduleName = %module.moduleId;
      
      %moduleGroup = %module.Group;
      if((%moduleGroup $= "Core" || %moduleGroup $= "Tools") && !%this.coreModulesFilter)
         continue;
      
      //first, see if this module Module is listed already
      /*%moduleItemId = AssetBrowser-->filterTree.findItemByName(%moduleName);
      
      //if(%moduleItemId == 0)
      //   %moduleItemId = AssetBrowser-->filterTree.insertItem(1, %moduleName, "", "", 1, 1);
         
      %assetType = AssetDatabase.getAssetCategory(%assetId);
      
      if(%assetType $= "")
      {
         %assetType = AssetDatabase.getAssetType(%assetId);
         if(%assetType $= "")
            %assetType = "Misc";
      }
      
      if(AssetBrowser.assetTypeFilter !$= "" && AssetBrowser.assetTypeFilter !$= %assetType)
         continue;
      
      %assetTypeId = AssetBrowser-->filterTree.findChildItemByName(%moduleItemId, %assetType);
      
      if(%assetTypeId == 0)
         %assetTypeId = AssetBrowser-->filterTree.insertItem(%moduleItemId, %assetType);*/
   //}

   AssetBrowser-->filterTree.buildVisibleTree(true);
   
   /*if(%this.treeFilterMode $= "list")
   {
      //First, build our our list of active modules
      %modulesList = ModuleDatabase.findModules(true);
      
      for(%i=0; %i < getWordCount(%modulesList); %i++)
      {
         %moduleName = getWord(%modulesList, %i).ModuleId;
         
         %moduleGroup = getWord(%modulesList, %i).Group;
         if((%moduleGroup $= "Core" || %moduleGroup $= "Tools") && !%this.coreModulesFilter)
            continue;
         
         %moduleItemId = AssetBrowser-->filterTree.findItemByName(%moduleName);
         
         if(%moduleItemId == 0)
            %moduleItemId = AssetBrowser-->filterTree.insertItem(1, %moduleName, "", "", 1, 1); 
      }

      //Next, go through and list the asset categories
      %assetQuery = new AssetQuery();
      %numAssetsFound = AssetDatabase.findAllAssets(%assetQuery);
      
      for( %i=0; %i < %numAssetsFound; %i++)
      {
          %assetId = %assetQuery.getAsset(%i);
          
         //first, get the asset's module, as our major categories
         %module = AssetDatabase.getAssetModule(%assetId);
         
         %moduleName = %module.moduleId;
         
         %moduleGroup = %module.Group;
         if((%moduleGroup $= "Core" || %moduleGroup $= "Tools") && !%this.coreModulesFilter)
            continue;
         
         //first, see if this module Module is listed already
         %moduleItemId = AssetBrowser-->filterTree.findItemByName(%moduleName);
         
         if(%moduleItemId == 0)
            %moduleItemId = AssetBrowser-->filterTree.insertItem(1, %moduleName, "", "", 1, 1);
            
         %assetType = AssetDatabase.getAssetCategory(%assetId);
         
         if(%assetType $= "")
         {
            %assetType = AssetDatabase.getAssetType(%assetId);
            if(%assetType $= "")
               %assetType = "Misc";
         }
         
         if(AssetBrowser.assetTypeFilter !$= "" && AssetBrowser.assetTypeFilter !$= %assetType)
            continue;
         
         %assetTypeId = AssetBrowser-->filterTree.findChildItemByName(%moduleItemId, %assetType);
         
         if(%assetTypeId == 0)
            %assetTypeId = AssetBrowser-->filterTree.insertItem(%moduleItemId, %assetType);
      }

      AssetBrowser-->filterTree.buildVisibleTree(true);
   }
   else if(%this.treeFilterMode $= "tags")
   {
      
   }*/
   
   //%this.collapseTree();
   
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
   
   AssetBrowser.expandTreeToAddress(AssetBrowser.currentAddress);
   
   %selectedItem = AssetBrowser.getFolderTreeItemFromAddress(AssetBrowser.currentAddress);
   AssetBrowser-->filterTree.scrollVisibleByObjectId(%selectedItem);
   
   AssetBrowser-->filterTree.buildVisibleTree(); 
}

// create category and update current material if there is one
function AssetBrowser::createFilter( %this, %filter )
{
   if( %filter $= %existingFilters )
   {
      MessageBoxOK( "Error", "Can not create blank filter.");
      return;
   }
      
   for( %i = AssetBrowser.staticFilterObjects; %i < AssetBrowser-->filterArray.getCount() ; %i++ )
   {
      %existingFilters = AssetBrowser-->filterArray.getObject(%i).getObject(0).filter;
      if( %filter $= %existingFilters )
      {
         MessageBoxOK( "Error", "Can not create two filters of the same name.");
         return;
      }
   }
   %container = new GuiControl(){
      profile = "ToolsGuiDefaultProfile";
      Position = "0 0";
      Extent = "128 18";
      HorizSizing = "right";
      VertSizing = "bottom";
      isContainer = "1";
         
      new GuiCheckBoxCtrl(){
         Profile = "ToolsGuiCheckBoxListProfile";
         position = "5 1";
         Extent = "118 18";
         Command = "";
         groupNum = "0";
         buttonType = "ToggleButton";
         text = %filter @ " ( " @ MaterialFilterAllArray.countKey(%filter) @ " )";
         filter = %filter;
         Command = "AssetBrowser.preloadFilter();";
      };
   };
   
   AssetBrowser-->filterArray.add( %container );
   
   // if selection exists, lets reselect it to refresh it
   if( isObject(AssetBrowser.selectedMaterial) )
      AssetBrowser.updateSelection( AssetBrowser.selectedMaterial, AssetBrowser.selectedPreviewImagePath );
   
   // material category text field to blank
   AssetBrowser_addFilterWindow-->tagName.setText("");
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

function AssetBrowser::collapseTree(%this)
{
   %modulesList = ModuleDatabase.findModules(true);
      
   for(%i=0; %i < getWordCount(%modulesList); %i++)
   {
      %moduleName = getWord(%modulesList, %i).ModuleId;
      
      %moduleGroup = getWord(%modulesList, %i).Group;
      if((%moduleGroup $= "Core" || %moduleGroup $= "Tools") && !%this.coreModulesFilter)
         continue;
      
      %moduleItemId = AssetBrowser-->filterTree.findItemByName(%moduleName);
      
      AssetBrowser-->filterTree.expandItem(%moduleItemId, false);
   }
   
   AssetBrowser-->filterTree.expandItem(1, true);
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
			%moduleItemId = AssetBrowser-->filterTree.insertItem(1, %module.moduleId, "", "", 1, 1);
			
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
      EditFolderPopup.showPopup(Canvas);  
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
         //get the parent, and thus our module
         %moduleId = %this.getParentItem(%itemId);
         
         //set the module value for creation info
         AssetBrowser.selectedModule = %this.getItemText(%moduleId);
         
         if(%this.getItemText(%itemId) $= "ComponentAsset")
         {
            AddNewComponentAssetPopup.showPopup(Canvas);
            //Canvas.popDialog(AssetBrowser_newComponentAsset); 
	         //AssetBrowser_newComponentAsset-->AssetBrowserModuleList.setText(AssetBrowser.selectedModule);
         }
         else if(%this.getItemText(%itemId) $= "ScriptAsset")
         {
            EditAssetCategoryPopup.showPopup(Canvas);
         }
      }
   }
   else if( %this.getSelectedItemsCount() > 0 && %itemId == 1)
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
      AssetPreviewSizePopup.checkItem(2, false);
   }
   
   EditorSettings.setValue("Assets/Browser/previewTileSize", %size);
      
   %this.refreshPreviews();
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
   
   %breadcrumbPath = %this.getItemValue(%itemId);
   if(%breadcrumbPath !$= "")
      %breadcrumbPath = %breadcrumbPath @ "/" @ %this.getItemText(%itemId);
   else
      %breadcrumbPath = %this.getItemText(%itemId);
      
   AssetBrowser.navigateTo(%breadcrumbPath);
}

function AssetBrowser::rebuildAssetArray(%this)
{
   %breadcrumbPath = AssetBrowser.currentAddress;
   
   // we have to empty out the list; so when we create new guicontrols, these dont linger
   AssetBrowser-->assetList.deleteAllObjects();
   AssetPreviewArray.empty();

   %assetArray = new ArrayObject();
   
   //First, Query for our assets
   %assetQuery = new AssetQuery();
   %numAssetsFound = AssetDatabase.findAllAssets(%assetQuery);
  
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
			
			/*if(%this.getItemText(%itemId) $= %assetType || (%assetType $= "" && %this.getItemText(%itemId) $= "Misc")
			   || %moduleItemId == 1)
			{*/
				//stop adding after previewsPerPage is hit
				%assetName = AssetDatabase.getAssetName(%assetId);
				
				%searchText = AssetBrowserSearchFilter.getText();
				if(%searchText !$= "Search Assets...")
				{
					if(strstr(strlwr(%assetName), strlwr(%searchText)) != -1)
						%assetArray.add( %moduleName, %assetId);
				}
				else
				{
					//got it.	
					%assetArray.add( %moduleName, %assetId );
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
		
   AssetBrowser_FooterText.text = %assetArray.count() @ " Assets";
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
   
   AssetBrowser.loadFilters();
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
   
   AssetBrowser.loadFilters();
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
   if(AssetBrowser.currentAddress $= %address)
      return;
      
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

   //find our folder tree and action on it tree
   %folderId = AssetBrowser.getFolderTreeItemFromAddress(%address);
   
   %oldAddress = AssetBrowser.currentAddress;   
   AssetBrowser.currentAddress = %address;
   AssetBrowser.selectedItem = %folderId;
   
   AssetBrowser-->filterTree.clearSelection();
   AssetBrowser-->filterTree.selectItem(%folderId);
   
   //remove any history records that are 'newer' than this one
   if(%historyNav $= "")
   {
      AssetBrowser_NavForeHistoryList.empty();  
      
      if(%oldAddress !$= "") 
         AssetBrowser_NavPrevHistoryList.push_front(%oldAddress);
   }
   
   //refresh the nav buttons to display the history
   %backButtonHistory = "";
   for(%i=0; %i < AssetBrowser_NavPrevHistoryList.Count(); %i++)
   {
      %prevAddress = AssetBrowser_NavPrevHistoryList.getKey(%i);
      %backButtonHistory = %i==0 ? %prevAddress @ "\n" : %backButtonHistory @ %prevAddress @ "\n";
   }
   
   AssetBrowser_NavigateBackBtn.tooltip = %backButtonHistory;
   
   %foreButtonHistory = "";
   for(%i=0; %i < AssetBrowser_NavForeHistoryList.Count(); %i++)
   {
      %prevAddress = AssetBrowser_NavForeHistoryList.getKey(%i);
      %foreButtonHistory = %i==0 ? %prevAddress @ "\n" : %foreButtonHistory @ %prevAddress @ "\n";
   }
   
   AssetBrowser_NavigateForwardBtn.tooltip = %foreButtonHistory;
   
   %module = AssetBrowser.getModuleFromAddress(%address);
   if(%module !$= "")
   {
      //legit module, so set it as current target
      AssetBrowser.SelectedModule = %module.moduleId;
   }
   
   %this.rebuildAssetArray();
}

function AssetBrowser::navigateHistoryForward(%this)
{
   if(AssetBrowser_NavForeHistoryList.count() == 0)
      return;
      
   %newAddress = AssetBrowser_NavForeHistoryList.getKey(0);
   %prevHistory = AssetBrowser.currentAddress;
      
   AssetBrowser_NavPrevHistoryList.push_front(%prevHistory);
   AssetBrowser_NavForeHistoryList.pop_front();
   
   %this.navigateTo(%newAddress, true);
}

function AssetBrowser::navigateHistoryBack(%this)
{
   if(AssetBrowser_NavPrevHistoryList.count() == 0)
      return;
      
   %newAddress = AssetBrowser_NavPrevHistoryList.getKey(0);
   %foreHistory = AssetBrowser.currentAddress;
      
   AssetBrowser_NavForeHistoryList.push_front(%foreHistory);
   AssetBrowser_NavPrevHistoryList.pop_front();
   
   %this.navigateTo(%newAddress, true);
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

function AssetBrowser::getModuleFromAddress(%this, %address)
{
   //break down the address
   %folderCount = getTokenCount(%address, "/");
      
   for(%f=0; %f < %folderCount; %f++)
   {
      %folderName = getToken(%address, "/", %f);

      %module = ModuleDatabase.findModule(%folderName);
      if(%module !$= "")
         return %module;
   }
   
   return "";
}

//AssetBrowser.getFolderTreeItemFromAddress(AssetBrowser.currentAddress);
function AssetBrowser::getFolderTreeItemFromAddress(%this, %address)
{
   //break down the address
   %folderCount = getTokenCount(%address, "/");

   %curItem = 0;
   %rebuiltPath = "";
   for(%f=0; %f < %folderCount; %f++)
   {
      %folderName = getToken(%address, "/", %f);
      %curItem = AssetBrowser-->filterTree.findChildItemByName(%curItem, %folderName);
   }
   
   return %curItem;
}

function AssetBrowser::expandTreeToAddress(%this, %address)
{
   //break down the address
   %folderCount = getTokenCount(%address, "/");
   AssetBrowser-->filterTree.expandItem(0);

   %curItem = 0;
   %rebuiltPath = "";
   for(%f=0; %f < %folderCount; %f++)
   {
      %folderName = getToken(%address, "/", %f);
      %curItem = AssetBrowser-->filterTree.findChildItemByName(%curItem, %folderName);
      AssetBrowser-->filterTree.expandItem(%curItem);
   }
}
//
//
//
function AssetBrowser::createNewFolder(%this)
{
   %newFolderIdx = "";
   %matched = true;
   %newFolderPath = "";
   while(%matched == true)
   {
      %newFolderPath = AssetBrowser.currentAddress @ "/NewFolder" @ %newFolderIdx;
      if(!isDirectory(%newFolderPath))
      {
         %matched = false;
      }
      else
      {
         %newFolderIdx++;         
      }
   }
   
   //make a dummy file
   %file = new FileObject();
   %file.openForWrite(%newFolderPath @ "/test");
   %file.close();
   
   fileDelete(%newFolderPath @ "/test");
   
   //refresh the directory
   %this.loadFilters();
   %this.rebuildAssetArray();
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
   
   if(%assetType $= "ImageAsset")
   {
      echo("WorldEditor::onControlDropped - dropped an ImageAsset onto the editor window. Todo: Implement dropping image/material into scene");  
   }
   else if(%assetType $= "ShapeAsset")
   {
      echo("DROPPED A SHAPE ON THE EDITOR WINDOW!"); 
      
      %staticShapeObjDef = AssetDatabase.acquireAsset("Core_GameObjects:StaticShapeObject");
      
      %newEntity = %staticShapeObjDef.createObject();
      
      %newEntity.position = %pos;
      %newEntity-->MeshComponent.MeshAsset = %module @ ":" @ %asset;
      
      %newEntity.dirtyGameObject = true; //because if we're specifically setting the mesh asset, it's dirty
      
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
   }
   
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
   
   if(%parent == 1)
   {
      //we're a module entry, cool
      %targetModuleName = %this.getItemText(%item);
      echo("DROPPED IT ON MODULE " @ %targetModuleName);   
      
      if(%moduleName !$= %targetModuleName)
      {
         //we're trying to move the asset to a different module!
         MessageBoxYesNo( "Move Asset", "Do you wish to move asset " @ %assetName @ " to module " @ %targetModuleName @ "?", 
               "AssetBrowser.moveAsset("@%assetName@", "@%targetModuleName@");", "");  
      }
   }
}