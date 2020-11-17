function AssetBrowser::buildPopupMenus(%this)
{
   if( !isObject( AddNewModulePopup ) )
   {
      new PopupMenu( AddNewModulePopup )
      {
         superClass = "MenuBuilder";
         class = "EditorWorldMenu";
         isPopup = true;
         
         item[ 0 ] = "Create New Module" TAB "" TAB "AssetBrowser.CreateNewModule();";
         item[ 1 ] = "Refresh Module Dependencies" TAB "" TAB "AssetBrowser.RefreshModuleDependencies();";
      };
      
      AddNewModulePopup.enableItem(1, false);
   }
   
   if( !isObject( EditAssetPopup ) )
   {
      new PopupMenu( EditAssetPopup )
      {
         superClass = "MenuBuilder";
         class = "EditorWorldMenu";
         //isPopup = true;

         item[ 0 ] = "Edit Asset" TAB "" TAB "AssetBrowser.editAsset();";
         item[ 1 ] = "Rename Asset" TAB "" TAB "AssetBrowser.renameAsset();";
         item[ 2 ] = "Refresh Asset" TAB "" TAB "AssetBrowser.refreshAsset();";
         item[ 3 ] = "Asset Properties" TAB "" TAB "AssetBrowser.editAssetInfo();";
         item[ 4 ] = "-";
         Item[ 5 ] = "Duplicate Asset" TAB "" TAB "AssetBrowser.duplicateAsset();";
         item[ 6 ] = "-";
         item[ 7 ] = "Re-Import Asset" TAB "" TAB "AssetBrowser.reImportAsset();";
         item[ 8 ] = "-";
         item[ 9 ] = "Delete Asset" TAB "" TAB "AssetBrowser.deleteAsset();";

         jumpFileName = "";
         jumpLineNumber = "";
      };
   }
   
   if( !isObject( EditLevelAssetPopup ) )
   {
      new PopupMenu( EditLevelAssetPopup )
      {
         superClass = "MenuBuilder";
         class = "EditorWorldMenu";
         //isPopup = true;

         item[ 0 ] = "Edit Level" TAB "" TAB "AssetBrowser.editAsset();";
         item[ 1 ] = "Append as Sublevel" TAB "" TAB "AssetBrowser.appendSublevel();";
         item[ 2 ] = "Rename Asset" TAB "" TAB "AssetBrowser.renameAsset();";
         item[ 3 ] = "Refresh Asset" TAB "" TAB "AssetBrowser.refreshAsset();";
         item[ 4 ] = "Asset Properties" TAB "" TAB "AssetBrowser.editAssetInfo();";
         item[ 5 ] = "-";
         Item[ 6 ] = "Duplicate Asset" TAB "" TAB "AssetBrowser.duplicateAsset();";
         item[ 7 ] = "-";
         //item[ 8 ] = "Re-Import Asset" TAB "" TAB "AssetBrowser.reImportAsset();";
         //item[ 9 ] = "-";
         item[ 8 ] = "Delete Asset" TAB "" TAB "AssetBrowser.deleteAsset();";

         jumpFileName = "";
         jumpLineNumber = "";
      };
   }
   
   if( !isObject( AddNewComponentAssetPopup ) )
   {
      new PopupMenu( AddNewComponentAssetPopup )
      {
         superClass = "MenuBuilder";
         class = "EditorWorldMenu";
         //isPopup = true;

         //item[ 0 ] = "Create Component" TAB "" TAB "Canvas.pushDialog(AssetBrowser_newComponentAsset); AssetBrowser_newComponentAsset-->NewComponentPackageList.setText(AssetBrowser.selectedModule);";
         item[ 0 ] = "Component" TAB "" TAB "AssetBrowser.setupCreateNewAsset(\"ComponentAsset\", AssetBrowser.selectedModule);";
         
         //list other common component types here to shortcut the creation process
      };
   }
   
   if( !isObject( AddNewScriptAssetPopup ) )
   {
      %this.AddNewScriptAssetPopup = new PopupMenu( AddNewScriptAssetPopup )
      {
         superClass = "MenuBuilder";
         class = "EditorWorldMenu";
         //isPopup = true;

         //item[ 0 ] = "Create Component" TAB AddNewComponentAssetPopup;
         item[ 0 ] = "Create Script" TAB "" TAB "AssetBrowser.setupCreateNewAsset(\"ScriptAsset\", AssetBrowser.selectedModule);";
         item[ 1 ] = "Create State Machine" TAB "" TAB "AssetBrowser.setupCreateNewAsset(\"StateMachineAsset\", AssetBrowser.selectedModule);";
         //item[ 3 ] = "-";
         //item[ 3 ] = "Create Game Object" TAB "" TAB "AssetBrowser.createNewGameObjectAsset(\"NewGameObject\", AssetBrowser.selectedModule);";
      };
      //%this.AddNewScriptAssetPopup.insertSubMenu(0, "Create Component", AddNewComponentAssetPopup);
   }
   
   if( !isObject( AddNewArtAssetPopup ) )
   {
      %this.AddNewArtAssetPopup = new PopupMenu( AddNewArtAssetPopup )
      {
         superClass = "MenuBuilder";
         class = "EditorWorldMenu";
         //isPopup = true;

         item[ 0 ] = "Create Material" TAB "" TAB "AssetBrowser.setupCreateNewAsset(\"MaterialAsset\", AssetBrowser.selectedModule);";//"createNewMaterialAsset(\"NewMaterial\", AssetBrowser.selectedModule);";
         item[ 1 ] = "Create Terrain Material" TAB "" TAB "AssetBrowser.setupCreateNewAsset(\"TerrainMaterialAsset\", AssetBrowser.selectedModule);";//"AssetBrowser.createNewImageAsset(\"NewImage\", AssetBrowser.selectedModule);";
         item[ 2 ] = "Create Image" TAB "" TAB "AssetBrowser.setupCreateNewAsset(\"ImageAsset\", AssetBrowser.selectedModule);";//"AssetBrowser.createNewImageAsset(\"NewImage\", AssetBrowser.selectedModule);";
         item[ 3 ] = "-";
         item[ 4 ] = "Create Terrain Data" TAB "" TAB "AssetBrowser.setupCreateNewAsset(\"TerrainAsset\", AssetBrowser.selectedModule);";
         item[ 5 ] = "-";         
         item[ 6 ] = "Create Shape" TAB "" TAB "AssetBrowser.setupCreateNewAsset(\"Shape\", AssetBrowser.selectedModule);";
         item[ 7 ] = "Create Shape Animation" TAB "" TAB "AssetBrowser.setupCreateNewAsset(\"ShapeAnimationAsset\", AssetBrowser.selectedModule);";//"AssetBrowser.createNewShapeAnimationAsset(\"NewShapeAnimation\", AssetBrowser.selectedModule);";
         item[ 8 ] = "-";
         item[ 9 ] = "Create GUI" TAB "" TAB "AssetBrowser.setupCreateNewAsset(\"GUIAsset\", AssetBrowser.selectedModule);";//"AssetBrowser.createNewGUIAsset(\"NewGUI\", AssetBrowser.selectedModule);";
         item[ 10 ] = "-";
         item[ 11 ] = "Create Post Effect" TAB "" TAB "AssetBrowser.setupCreateNewAsset(\"PostEffectAsset\", AssetBrowser.selectedModule);";//"AssetBrowser.createNewPostEffectAsset(\"NewPostEffect\", AssetBrowser.selectedModule);";
         item[ 12 ] = "-";
         item[ 13 ] = "Create Sound" TAB "" TAB "AssetBrowser.setupCreateNewAsset(\"SoundAsset\", AssetBrowser.selectedModule);";//"AssetBrowser.createNewSoundAsset(\"NewSound\", AssetBrowser.selectedModule);";
         item[ 14 ] = "-";
         item[ 15 ] = "Create Particle Effect" TAB "" TAB "AssetBrowser.setupCreateNewAsset(\"ParticleEffectAsset\", AssetBrowser.selectedModule);";//"AssetBrowser.createNewParticleEffectAsset(\"NewParticleEffect\", AssetBrowser.selectedModule);";
         item[ 16 ] = "-";
         item[ 17 ] = "Create Cubemap" TAB "" TAB "AssetBrowser.setupCreateNewAsset(\"CubemapAsset\", AssetBrowser.selectedModule);";
      };
   }
   
   if( !isObject( AddNewCppAssetPopup ) )
   {
      %this.AddNewCppAssetPopup = new PopupMenu( AddNewCppAssetPopup )
      {
         superClass = "MenuBuilder";
         class = "EditorWorldMenu";
         //isPopup = true;

         /*item[ 0 ] = "Create Static Class" TAB "" TAB "AssetBrowser.setupCreateNewAsset(\"CppStaticClassAsset\", AssetBrowser.selectedModule);";
         item[ 1 ] = "Create Regular Class" TAB "" TAB "AssetBrowser.setupCreateNewAsset(\"CppRegularClassAsset\", AssetBrowser.selectedModule);";
         item[ 2 ] = "Create GameObject Class" TAB "" TAB "AssetBrowser.setupCreateNewAsset(\"CppGameObjectAsset\", AssetBrowser.selectedModule);";
         item[ 3 ] = "Create Component Class" TAB "" TAB "AssetBrowser.setupCreateNewAsset(\"CppComponentAsset\", AssetBrowser.selectedModule);";
         item[ 4 ] = "Create Script Class" TAB "" TAB "AssetBrowser.setupCreateNewAsset(\"CppScriptClass\", AssetBrowser.selectedModule);";*/
         
         item[ 0 ] = "Create C++ Class" TAB "" TAB "AssetBrowser.setupCreateNewAsset(\"CppAsset\", AssetBrowser.selectedModule);";
      };
      //%this.AddNewScriptAssetPopup.insertSubMenu(0, "Create Component", AddNewComponentAssetPopup);
   }
      
   if( !isObject( AddNewAssetPopup ) )
   {
      %this.AddNewAssetPopup = new PopupMenu( AddNewAssetPopup )
      {
         superClass = "MenuBuilder";
         class = "EditorWorldMenu";
         
         item[0] = "Create Folder" TAB "" TAB "AssetBrowser.CreateNewFolder();";
         item[1] = "-";
         item[2] = "Create Code Asset" TAB AddNewScriptAssetPopup;
         item[3] = "-";
         item[4] = "Create Art Asset" TAB AddNewArtAssetPopup;
         item[5] = "-";
         item[6] = "Create Level" TAB "" TAB "AssetBrowser.setupCreateNewAsset(\"LevelAsset\", AssetBrowser.selectedModule);";//"AssetBrowser.createNewLevelAsset(\"NewLevel\", AssetBrowser.selectedModule);";
         item[7] = "-";
         item[8] = "Create C++ Asset" TAB AddNewCppAssetPopup;
         item[9] = "-";
         item[10] = "Create New Module" TAB "" TAB "AssetBrowser.CreateNewModule();";
         item[11] = "-";
         item[12] = "Import Loose Files" TAB "" TAB "AssetBrowser.importLooseFiles();";
      
      };
   }
   
   if( !isObject( EditModulePopup ) )
   {
      new PopupMenu( EditModulePopup )
      {
         superClass = "MenuBuilder";
         class = "EditorWorldMenu";
         //isPopup = true;
         
         item[ 0 ] = "New Asset" TAB AddNewAssetPopup;
         item[ 1 ] = "Reload Module" TAB "" TAB "AssetBrowser.reloadModule();";
         Item[ 2 ] = "Edit Module" TAB "" TAB "AssetBrowser.editModuleScript();";
         Item[ 3 ] = "-";
         Item[ 4 ] = "Module Properties" TAB "" TAB "AssetBrowser.editModuleInfo();";
         Item[ 5 ] = "-";
         Item[ 6 ] = "Duplicate Module" TAB "" TAB "AssetBrowser.copyModule();";
         Item[ 7 ] = "-";
         Item[ 8 ] = "Delete Module" TAB "" TAB "AssetBrowser.deleteModule();";
         item[ 9 ] = "-";
         item[ 10 ] = "Import Loose Files" TAB "" TAB "AssetBrowser.importLooseFiles();";
      };
   }
   
   if( !isObject( EditNonModulePopup ) )
   {
      new PopupMenu( EditNonModulePopup )
      {
         superClass = "MenuBuilder";
         class = "EditorWorldMenu";
         //isPopup = true;
         
         item[ 0 ] = "Turn Folder into Module" TAB "" TAB "AssetBrowser.ConvertFolderIntoModule();";
      };
   }
   
   //Some assets are not yet ready/implemented, so disable their creation here
   AddNewArtAssetPopup.enableItem(6, false); //shape
   AddNewArtAssetPopup.enableItem(7, false); //shape animation
   AddNewArtAssetPopup.enableItem(13, false); //sound asset
   AddNewArtAssetPopup.enableItem(15, false); //particle effect
   
   if( !isObject( EditFolderPopup ) )
   {
      new PopupMenu( EditFolderPopup )
      {
         superClass = "MenuBuilder";
         class = "EditorWorldMenu";
         //isPopup = true;

         Item[ 0 ] = "Create" TAB AddNewAssetPopup;
         item[ 1 ] = "-";
         item[ 2 ] = "Rename Folder" TAB "" TAB "AssetBrowser.renameAsset();";
         Item[ 3 ] = "Duplicate Folder" TAB "" TAB "AssetBrowser.duplicateAsset();";
         item[ 4 ] = "-";
         item[ 5 ] = "Delete Folder" TAB "" TAB "AssetBrowser.deleteAsset();";
         item[ 6 ] = "-";
         item[ 7 ] = "Import Loose Files" TAB "" TAB "AssetBrowser.importLooseFiles();";
      };
   }
   
   if( !isObject( EditAssetCategoryPopup ) )
   {
      new PopupMenu( EditAssetCategoryPopup )
      {
         superClass = "MenuBuilder";
         class = "EditorWorldMenu";
         //isPopup = true;
         
         item[ 0 ] = "Toggle Autoloading of Script Assets" TAB "" TAB "AssetBrowser.toggleAutoloadAsset(\"Script\");";
      };
   }
   
   if( !isObject( AssetTypeListPopup ) )
   {
      new PopupMenu( AssetTypeListPopup )
      {
         superClass = "MenuBuilder";
         class = "EditorWorldMenu";
         //isPopup = true;
         
         radioSelection = false;
      };
      
      AssetTypeListPopup.addItem(0, AssetFilterTypeList.getKey(0) TAB "" TAB "AssetBrowser.toggleAssetTypeFilter(" @ 0 @ ");");
      AssetTypeListPopup.addItem(1, "-");
      
      for(%i=1; %i < AssetFilterTypeList.Count(); %i++)
      {
         %assetTypeName = AssetFilterTypeList.getKey(%i);
         AssetTypeListPopup.addItem(%i+1, %assetTypeName TAB "" TAB "AssetBrowser.toggleAssetTypeFilter(" @ %i + 1 @ ");");
      }
   }
   
   //Browser visibility menu
   if( !isObject( BrowserVisibilityPopup ) )
   {
      new PopupMenu( BrowserVisibilityPopup )
      {
         superClass = "MenuBuilder";
         class = "EditorWorldMenu";
         //isPopup = true;
         
         item[ 0 ] = "Toggle Show Core Modules" TAB "" TAB "AssetBrowser.viewCoreModulesFilter();";
         item[ 1 ] = "Toggle Show Tools Modules" TAB "" TAB "AssetBrowser.viewToolsModulesFilter();";
         item[ 2 ] = "Toggle Only Show Modules with Assets" TAB "" TAB "AssetBrowser.viewPopulatedModulesFilter();";
         Item[ 3 ] = "-";
         item[ 4 ] = "Show Folders" TAB "" TAB "AssetBrowser.toggleShowingFolders();";
         item[ 5 ] = "Show Empty Folders" TAB "" TAB "AssetBrowser.toggleShowingEmptyFolders();";
         item[ 6 ] = "-";
         item[ 7 ] = "Filter by Asset Type" TAB AssetTypeListPopup;
         item[ 8 ] = "-";
         item[ 9 ] = "Enable Auto-refresh" TAB "" TAB "AssetBrowser.toggleAutorefresh();";
      };
      
      BrowserVisibilityPopup.enableItem(5, false);
      BrowserVisibilityPopup.enableItem(9, false);
   }
   
   //
   
   //Import Legacy menus
   if( !isObject( ImportAssetsPopup ) )
   {
      new PopupMenu( ImportAssetsPopup )
      {
         superClass = "MenuBuilder";
         class = "EditorWorldMenu";
         
         item[ 0 ] = "Import Project Loose Files" TAB "" TAB "AssetBrowser.importLooseFiles();";
         Item[ 1 ] = "-";
         item[ 2 ] = "Import new assets" TAB "" TAB "Canvas.pushDialog(AssetImportCtrl);";
      };
   }
   
   if( !isObject( EditGameObjectAssetPopup ) )
   {
      new PopupMenu( EditGameObjectAssetPopup )
      {
         superClass = "MenuBuilder";
         class = "EditorWorldMenu";
         //isPopup = true;
         
         item[ 0 ] = "Open GameObject Editor" TAB "" TAB "echo(\"Not yet implemented.\");";
         item[ 1 ] = "Edit GameObject Script" TAB "" TAB "AssetBrowser.editGameObjectAssetScript(AssetDatabase.acquireAsset(EditGameObjectAssetPopup.assetId));";
         item[ 2 ] = "-";
         item[ 3 ] = "Apply Instance to GameObject" TAB "" TAB "AssetBrowser.applyInstanceToGameObject(AssetDatabase.acquireAsset(EditGameObjectAssetPopup.assetId));";
         item[ 4 ] = "Reset Instance to GameObject" TAB "" TAB "echo(\"Not yet implemented.\");";
         item[ 5 ] = "-";
         item[ 6 ] = "Create Child GameObject" TAB "" TAB "echo(\"Not yet implemented.\");";
      };
   }
   
   //Asset Import Resolution menus
   if( !isObject( ImportAssetResolutionsPopup ) )
   {
      %this.ImportAssetResolutionsPopup = new PopupMenu( ImportAssetResolutionsPopup )
      {
         superClass = "MenuBuilder";
         class = "EditorWorldMenu";
         
         item[0] = "Use original Asset for duplicates" TAB "" TAB "";
         item[1] = "Override duplicate with new Asset" TAB "" TAB "";
         item[2] = "-";
         item[3] = "Rename Asset" TAB "" TAB "";
         item[4] = "-";
         item[5] = "Find missing file" TAB "" TAB "ImportAssetWindow.findMissingFile(ImportAssetResolutionsPopup.assetItem);";
         item[6] = "-";
         item[7] = "Edit Asset properties" TAB "" TAB "";
      
      };
   }

   //
   // Import Asset Actions
   //
   if( !isObject( ImportAssetMaterialMaps ) )
   {
      %this.ImportAssetActions = new PopupMenu( ImportAssetMaterialMaps )
      {
         superClass = "MenuBuilder";
         class = "EditorWorldMenu";
         
         item[0] = "Add Color Map" TAB "" TAB "ImportAssetWindow.addMaterialMap(\"Color\");";
         item[1] = "Add Normal Map" TAB "" TAB "ImportAssetWindow.addMaterialMap(\"Normal\");";
         item[2] = "Add Composite Map" TAB "" TAB "ImportAssetWindow.addMaterialMap(\"Composite\");";
         item[3] = "Add Metalness Map" TAB "" TAB "ImportAssetWindow.addMaterialMap(\"Metalness\");";
         item[4] = "Add AO Map" TAB "" TAB "ImportAssetWindow.addMaterialMap(\"AO\");";
         item[5] = "Add Roughness Map" TAB "" TAB "ImportAssetWindow.addMaterialMap(\"Roughness\");";
         item[6] = "Add Glow Map" TAB "" TAB "ImportAssetWindow.addMaterialMap(\"Glow\");";
         Item[7] = "-";
         Item[8] = "Add Existing Image Asset" TAB "" TAB "ImportAssetWindow.addExistingImageAsset();";
      };
   }
   
   if( !isObject( ImportAssetActions ) )
   {
      %this.ImportAssetActions = new PopupMenu( ImportAssetActions )
      {
         superClass = "MenuBuilder";
         class = "EditorWorldMenu";
         
         item[0] = "Add New Asset" TAB "" TAB "ImportAssetWindow.addNewImportingAsset();";
         item[1] = "Import Existing File as Asset" TAB "" TAB "ImportAssetWindow.importExistingFile();";
         item[2] = "-";
         item[3] = "Add Reference to Existing Asset" TAB "" TAB "ImportAssetWindow.addRefExistingAsset();";
         item[4] = "-";
         item[5] = "Remove asset" TAB "" TAB "ImportAssetWindow.removeImportingAsset();";
      };
   }
   
   if( !isObject( AddNewToolPopup ) )
   {
      new PopupMenu( AddNewToolPopup )
      {
         superClass = "MenuBuilder";
         class = "EditorWorldMenu";
         isPopup = true;
         
         item[ 0 ] = "Create New Editor Tool" TAB "" TAB "AssetBrowser.createNewEditorTool(AddNewToolPopup.targetFolder);";
      };
      
      AddNewModulePopup.enableItem(1, false);
   }
   
   if( !isObject( EditCollectionSets ) )
   {
      new PopupMenu( EditCollectionSets )
      {
         superClass = "MenuBuilder";
         class = "EditorWorldMenu";
         //isPopup = true;
         
         item[ 0 ] = "Delete Collection Set" TAB "" TAB "AssetBrowser.deleteCollectionSet();";
      };
   }
}

function AddNewScriptAssetPopupMenu::onSelectItem(%this, %id, %text)
{   
   return true;
}
function AddNewScriptAssetPopupMenu::setupDefaultState(%this)
{
   // Setup camera speed gui's. Both menu and editorgui
   %this.setupGuiControls();
   
   Parent::setupDefaultState(%this);
}

function AddNewScriptAssetPopupMenu::setupGuiControls(%this)
{
}
