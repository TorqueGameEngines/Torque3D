//-----------------------------------------------------------------------------
// Copyright (c) 2012 GarageGames, LLC
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//-----------------------------------------------------------------------------
function initializeAssetBrowser()
{
   echo(" % - Initializing Asset Browser");  
   
   $AssetBrowser::importConfigsFile = "tools/assetBrowser/assetImportConfigs.xml";
   $AssetBrowser::collectionSetsFile = "tools/assetBrowser/searchCollectionSets.xml";
   $AssetBrowser::currentImportConfig = "";
   
   if(!isObject(AssetFilterTypeList))
   {
      new ArrayObject(AssetFilterTypeList);

      AssetFilterTypeList.add("All");
      AssetFilterTypeList.add("ComponentAsset");
      AssetFilterTypeList.add("CppAsset");
      AssetFilterTypeList.add("CubemapAsset");
      AssetFilterTypeList.add("GameObjectAsset");
      AssetFilterTypeList.add("GUIAsset");
      AssetFilterTypeList.add("ImageAsset");
      AssetFilterTypeList.add("LevelAsset");
      AssetFilterTypeList.add("MaterialAsset");
      AssetFilterTypeList.add("ParticleAsset");
      AssetFilterTypeList.add("PostFXAsset");
      AssetFilterTypeList.add("ScriptAsset");
      AssetFilterTypeList.add("ShapeAsset");
      AssetFilterTypeList.add("ShapeAnimationAsset");
      AssetFilterTypeList.add("SoundAsset");
      AssetFilterTypeList.add("StateMachineAsset");
      AssetFilterTypeList.add("TerrainAsset");
      AssetFilterTypeList.add("TerrainMaterialAsset");
   }
   
   exec("./scripts/profiles.cs");
   
   exec("./guis/assetBrowser.gui");
   exec("./guis/addModuleWindow.gui");
   exec("./guis/gameObjectCreator.gui");
   exec("./guis/newAsset.gui");
   exec("./guis/newComponentAsset.gui");
   exec("./guis/editAsset.gui");
   exec("./guis/assetImport.gui");
   exec("./guis/assetImportConfigEditor.gui");
   exec("./guis/selectModule.gui");
   exec("./guis/selectPath.gui");
   exec("./guis/editModule.gui");
   exec("./guis/importTemplateModules.gui");
   exec("./guis/assetPreviewButtonsTemplate.gui");
   exec("./guis/newFolder.gui");
   exec("./guis/assetImportLog.gui");
   exec("./guis/looseFileAudit.gui");
   exec("./guis/assetNameEdit.gui");
   exec("./guis/createNewCollectionSet.gui");

   exec("./scripts/assetBrowser.cs");
   exec("./scripts/popupMenus.cs");
   exec("./scripts/addModuleWindow.cs");
   exec("./scripts/assetImport.cs");
   exec("./scripts/assetImportConfig.cs");
   exec("./scripts/gameObjectCreator.cs");
   exec("./scripts/newAsset.cs");
   exec("./scripts/editAsset.cs");
   exec("./scripts/editModule.cs");   
   exec("./scripts/selectModule.cs");   
   exec("./scripts/assetImportConfigEditor.cs");  
   exec("./scripts/directoryHandling.cs");
   exec("./scripts/selectPath.cs");
   exec("./scripts/looseFileAudit.cs");
   
   //Processing for the different asset types
   exec("./scripts/assetTypes/component.cs"); 
   exec("./scripts/assetTypes/cpp.cs");
   exec("./scripts/assetTypes/gameObject.cs");   
   exec("./scripts/assetTypes/gui.cs");
   exec("./scripts/assetTypes/image.cs");  
   exec("./scripts/assetTypes/level.cs"); 
   exec("./scripts/assetTypes/material.cs");   
   exec("./scripts/assetTypes/postFX.cs");
   exec("./scripts/assetTypes/script.cs");
   exec("./scripts/assetTypes/shape.cs");
   exec("./scripts/assetTypes/shapeAnimation.cs"); 
   exec("./scripts/assetTypes/sound.cs"); 
   exec("./scripts/assetTypes/stateMachine.cs");   
   exec("./scripts/assetTypes/cubemap.cs");  
   exec("./scripts/assetTypes/folder.cs");  
   exec("./scripts/assetTypes/terrain.cs");
   exec("./scripts/assetTypes/terrainMaterial.cs");  
   exec("./scripts/assetTypes/datablockObjects.cs");  
   exec("./scripts/assetTypes/looseFiles.cs"); 
   exec("./scripts/assetTypes/prefab.cs"); 
   
   new ScriptObject( AssetBrowserPlugin )
   {
      superClass = "EditorPlugin";
   };
   
   Input::GetEventManager().subscribe( AssetBrowser, "BeginDropFiles" );
   Input::GetEventManager().subscribe( AssetBrowser, "DropFile" );
   Input::GetEventManager().subscribe( AssetBrowser, "EndDropFiles" );
   
   AssetBrowserPlugin.initSettings();
   
   if(!isObject(AssetImportSettings))
   {
      new Settings(AssetImportSettings) 
      { 
         file = $AssetBrowser::importConfigsFile; 
      };
   }
   AssetImportSettings.read();
   
   ImportAssetWindow.reloadImportOptionConfigs();
   
   //CollectionSets
   if(!isObject(AssetBrowserCollectionSets))
   {
      new Settings(AssetBrowserCollectionSets) 
      { 
         file = $AssetBrowser::collectionSetsFile; 
      };
   }
   AssetBrowserCollectionSets.read();
   
   if(!isObject(ImportAssetWindow.importTempDirHandler))
      ImportAssetWindow.importTempDirHandler = makedirectoryHandler(0, "", "");
      
   if(!isObject(ImportActivityLog))
      new ArrayObject(ImportActivityLog);
      
   if(!isObject(AssetSearchTerms))
      new ArrayObject(AssetSearchTerms);
      
   ImportAssetWindow.importingFilesArray = new ArrayObject();
      
   ImportAssetWindow.importer = new AssetImporter();
      
   AssetBrowser.buildPopupMenus();
   
   //Force everything to initialize if other things need to reference it's behavior before we're displayed(usually other tools)
   AssetBrowser.showDialog();
   AssetBrowser.hideDialog();
}

function AssetBrowserPlugin::onWorldEditorStartup( %this )
{ 
   // Add ourselves to the toolbar.
   AssetBrowser.addToolbarButton();
}

function AssetBrowserPlugin::initSettings( %this )
{
   EditorSettings.beginGroup( "Assets", true );

   EditorSettings.setDefaultValue( "AssetImporDefaultConfig",    "DefaultConfig" );
   EditorSettings.setDefaultValue( "AutoImport", 1 );
   
   EditorSettings.beginGroup( "Browser" );
   
   EditorSettings.setDefaultValue( "showCoreModule", 0 );
   EditorSettings.setDefaultValue( "showToolsModule", 0 );
   EditorSettings.setDefaultValue( "showOnlyPopulatedModule", 0 );
   EditorSettings.setDefaultValue( "showFolders", 1 );
   EditorSettings.setDefaultValue( "showEmptyFolders", 1 );
   EditorSettings.setDefaultValue( "previewTileSize", 1.0 );
   
   EditorSettings.endGroup();
   EditorSettings.endGroup();

   EditorSettings.beginGroup( "AssetManagement", true );
   EditorSettings.beginGroup( "Assets" );

   EditorSettings.setDefaultValue( "promptOnRename", 1 );
   
   EditorSettings.endGroup();
   EditorSettings.endGroup();
}

function TSStatic::onConstructField(%this, %fieldName, %fieldLabel, %fieldTypeName, %fieldDesc, %fieldDefaultVal, %fieldDataVals, %callbackName, %ownerObj)
{
   %inspector = %this.getParent();
   %makeCommand = %this @ ".build" @ %fieldTypeName @ "Field(\""@ %fieldName @ "\",\"" @ %fieldLabel @ "\",\"" @ %fieldDesc @ "\",\"" @ 
            %fieldDefaultVal @ "\",\"" @ %fieldDataVals @ "\",\"" @ %inspector @ "." @ %callbackName @ "\",\"" @ %ownerObj @"\");";
   eval(%makeCommand);
}