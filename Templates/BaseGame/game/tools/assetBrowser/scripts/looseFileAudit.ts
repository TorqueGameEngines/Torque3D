function LooseFileAuditWindow::buildPopupMenus(%this)
{
   //
   // Import Asset Actions
   //
   //done with any valid image format file
   if( !isObject( ImageLooseFilePopup ) )
   {
      %this.ImportAssetActions = new PopupMenu( ImageLooseFilePopup )
      {
         superClass = "MenuBuilder";
         class = "EditorWorldMenu";
         
         item[0] = "Make an Image Asset" TAB "" TAB "LooseFileAuditWindow.importImage();";
      };
   }
   
   //Done with .cs files
   if( !isObject( ScriptLooseFilePopup ) )
   {
      %this.ImportAssetActions = new PopupMenu( ScriptLooseFilePopup )
      {
         superClass = "MenuBuilder";
         class = "EditorWorldMenu";
         
         item[0] = "Make a Script Asset" TAB "" TAB "LooseFileAuditWindow.importScript();";
         item[1] = "Make a PostFX Asset" TAB "" TAB "LooseFileAuditWindow.importPostFX();";
         item[2] = "Make a Material Asset" TAB "" TAB "LooseFileAuditWindow.importMaterial();";
         item[3] = "Make a Terrain Material Asset" TAB "" TAB "LooseFileAuditWindow.importTerrMat();";
         item[4] = "Make a Particle Asset" TAB "" TAB "LooseFileAuditWindow.importParticle();";
         item[5] = "Make a Explosion Asset" TAB "" TAB "LooseFileAuditWindow.importExplosion();";
         item[6] = "Make a Forest Brush Asset" TAB "" TAB "LooseFileAuditWindow.importForest();";
      };
   }  
   
   ScriptLooseFilePopup.enableItem(4, false);
   ScriptLooseFilePopup.enableItem(5, false);   
   ScriptLooseFilePopup.enableItem(6, false);
   
   if( !isObject( ShapeLooseFilePopup ) )
   {
      %this.ImportAssetActions = new PopupMenu( ShapeLooseFilePopup )
      {
         superClass = "MenuBuilder";
         class = "EditorWorldMenu";
         
         item[0] = "Make a Shape Asset" TAB "" TAB "LooseFileAuditWindow.importShape();";
         item[1] = "Make a Shape Animation Asset" TAB "" TAB "LooseFileAuditWindow.importShapeAnimation();";
      };
   }
   
   if( !isObject( DecalLooseFilePopup ) )
   {
      %this.ImportAssetActions = new PopupMenu( DecalLooseFilePopup )
      {
         superClass = "MenuBuilder";
         class = "EditorWorldMenu";
         
         item[0] = "Make a Decal Asset" TAB "" TAB "LooseFileAuditWindow.importDecal();";
      };
   }
   
   if( !isObject( TerrainLooseFilePopup ) )
   {
      %this.ImportAssetActions = new PopupMenu( TerrainLooseFilePopup )
      {
         superClass = "MenuBuilder";
         class = "EditorWorldMenu";
         
         item[0] = "Make a Terrain Data Asset" TAB "" TAB "LooseFileAuditWindow.importTerrain();";
      };
   }
   
   if( !isObject(SoundLooseFilePopup ) )
   {
      %this.ImportAssetActions = new PopupMenu( SoundLooseFilePopup )
      {
         superClass = "MenuBuilder";
         class = "EditorWorldMenu";
         
         item[0] = "Make a Sound Asset" TAB "" TAB "LooseFileAuditWindow.importSound();";
      };
   }
   
   if( !isObject(LevelLooseFilePopup ) )
   {
      %this.ImportAssetActions = new PopupMenu( LevelLooseFilePopup )
      {
         superClass = "MenuBuilder";
         class = "EditorWorldMenu";
         
         item[0] = "Make a Level Asset" TAB "" TAB "LooseFileAuditWindow.importLevel();";
      };
   }
   
   if( !isObject(GUILooseFilePopup ) )
   {
      %this.ImportAssetActions = new PopupMenu( GUILooseFilePopup )
      {
         superClass = "MenuBuilder";
         class = "EditorWorldMenu";
         
         item[0] = "Make a GUI Asset" TAB "" TAB "LooseFileAuditWindow.importGUI();";
      };
   }
}

function LooseFileAuditWindow::showDialog(%this, %address)
{
   LooseFileAuditWindow.buildPopupMenus();
   
   Canvas.pushDialog(LooseFileAudit);
   
   %this.currentAddress = %address;
   
   %this.refresh();
}

function LooseFileAuditWindow::refresh(%this)
{
   LooseFileList.clear();
   LooseFileList.insertItem(0, "Loose Files");
   
   //First, wipe out any files inside the folder first
   %file = findFirstFileMultiExpr( %this.currentAddress @ "/*.*", false);
   
   %aq = new AssetQuery();

   while( %file !$= "" )
   {      
      //%filename = fileName(%file);
      //%filePath = filePath(%file);
      if(!strIsMatchExpr("*.asset.taml", %file) && !strIsMatchExpr("*.taml", %file))
      {
         %assetsFound = AssetDatabase.findAssetLooseFile(%aq, %file);
         
         if(%assetsFound == 0)
         {
            LooseFileList.insertItem(1, %file); 
         }
      }
      
      %file = findNextFileMultiExpr( %this.currentAddress @ "/*.*" );
   }
   
   LooseFileList.buildVisibleTree(true);
   LooseFileList.expandItem(0);
   
   %aq.delete();
}

function LooseFileList::onRightMouseDown(%this, %itemId)
{
   LooseFileList.itemPath = %this.getItemText(%itemId);
   LooseFileList.selectedItem = %itemId;
   
   %ext = fileExt(LooseFileList.itemPath);
   if(isImageFormat(%ext))
   {
        ImageLooseFilePopup.showPopup(Canvas);
   }
   else if(%ext $= ".cs")
   {
        ScriptLooseFilePopup.showPopup(Canvas);
   }
   else if(isShapeFormat(%ext))
   {
        ShapeLooseFilePopup.showPopup(Canvas);
   }
   else if(%ext $= ".mis")
   {
        LevelLooseFilePopup.showPopup(Canvas);
   }
   else if(isSoundFormat(%ext))
   {
        SoundLooseFilePopup.showPopup(Canvas);
   }
   else if(%ext $= ".ter")
   {
        TerrainLooseFilePopup.showPopup(Canvas);
   }
   else if(%ext $= ".gui")
   {
        GUILooseFilePopup.showPopup(Canvas);
   }
}

//
//
function LooseFileAuditWindow::importImage(%this)
{
   if(!ImportAssetWindow.isAwake())
      ImportAssetWindow.showDialog();
      
   %assetItem = AssetBrowser.addImportingAsset("ImageAsset", LooseFileList.itemPath, "", "");
   ImportAssetItems.add(%assetItem);
   LooseFileList.removeItem(LooseFileList.selectedItem, false);
   LooseFileList.buildVisibleTree(true);
   LooseFileList.expandItem(0);
}

function LooseFileAuditWindow::importScript(%this)
{
   if(!ImportAssetWindow.isAwake())
      ImportAssetWindow.showDialog();
      
   AssetBrowser.addImportingAsset("ScriptAsset", LooseFileList.itemPath, "", "");
   LooseFileList.removeItem(LooseFileList.selectedItem, false);
   LooseFileList.buildVisibleTree(true);
   LooseFileList.expandItem(0);
}

function LooseFileAuditWindow::importGUI(%this)
{
   if(!ImportAssetWindow.isAwake())
      ImportAssetWindow.showDialog();
      
   ImportAssetWindow.allowAutoImport = false;
      
   AssetBrowser.addImportingAsset("GUIAsset", LooseFileList.itemPath, "", "");
   LooseFileList.removeItem(LooseFileList.selectedItem, false);
   LooseFileList.buildVisibleTree(true);
   LooseFileList.expandItem(0);
}

function LooseFileAuditWindow::importLevel(%this)
{
   if(!ImportAssetWindow.isAwake())
      ImportAssetWindow.showDialog();
      
   ImportAssetWindow.allowAutoImport = false;
   
   AssetBrowser.addImportingAsset("LevelAsset", LooseFileList.itemPath, "", "");
   LooseFileList.removeItem(LooseFileList.selectedItem, false);
   LooseFileList.buildVisibleTree(true);
   LooseFileList.expandItem(0);
}

function LooseFileAuditWindow::importSound(%this)
{
   if(!ImportAssetWindow.isAwake())
      ImportAssetWindow.showDialog();
      
   AssetBrowser.addImportingAsset("SoundAsset", LooseFileList.itemPath, "", "");
   LooseFileList.removeItem(LooseFileList.selectedItem, false);
   LooseFileList.buildVisibleTree(true);
   LooseFileList.expandItem(0);
}

function LooseFileAuditWindow::importTerrain(%this)
{
   if(!ImportAssetWindow.isAwake())
      ImportAssetWindow.showDialog();
      
   AssetBrowser.addImportingAsset("TerrainAsset", LooseFileList.itemPath, "", "");
   LooseFileList.removeItem(LooseFileList.selectedItem, false);
   LooseFileList.buildVisibleTree(true);
   LooseFileList.expandItem(0);
   
}

function LooseFileAuditWindow::importTerrMat(%this)
{
   if(!ImportAssetWindow.isAwake())
      ImportAssetWindow.showDialog();
      
   AssetBrowser.addImportingAsset("TerrainMaterialAsset", LooseFileList.itemPath, "", "");
   LooseFileList.removeItem(LooseFileList.selectedItem, false);
   LooseFileList.buildVisibleTree(true);
   LooseFileList.expandItem(0);
}

function LooseFileAuditWindow::importShape(%this)
{
   if(!ImportAssetWindow.isAwake())
      ImportAssetWindow.showDialog();
      
   AssetBrowser.addImportingAsset("ShapeAsset", LooseFileList.itemPath, "", "");
   LooseFileList.removeItem(LooseFileList.selectedItem, false);
   LooseFileList.buildVisibleTree(true);
   LooseFileList.expandItem(0);
}

function LooseFileAuditWindow::importShapeAnimation(%this)
{
   if(!ImportAssetWindow.isAwake())
      ImportAssetWindow.showDialog();
      
   AssetBrowser.addImportingAsset("ShapeAnimationAsset", LooseFileList.itemPath, "", "");
   LooseFileList.removeItem(LooseFileList.selectedItem, false);
   LooseFileList.buildVisibleTree(true);
   LooseFileList.expandItem(0);
}

function LooseFileAuditWindow::importPostFX(%this)
{
   if(!ImportAssetWindow.isAwake())
      ImportAssetWindow.showDialog();
      
   AssetBrowser.addImportingAsset("PostEffectAsset", LooseFileList.itemPath, "", "");
   LooseFileList.removeItem(LooseFileList.selectedItem, false);
   LooseFileList.buildVisibleTree(true);
   LooseFileList.expandItem(0);
}

function LooseFileAuditWindow::importMaterial(%this)
{
   if(!ImportAssetWindow.isAwake())
      ImportAssetWindow.showDialog();
      
   AssetBrowser.addImportingAsset("MaterialAsset", LooseFileList.itemPath, "", "");
   LooseFileList.removeItem(LooseFileList.selectedItem, false);
   LooseFileList.buildVisibleTree(true);
   LooseFileList.expandItem(0);
}