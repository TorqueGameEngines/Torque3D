function AssetBrowser::createCubemapAsset(%this)
{
   Canvas.pushDialog(CubemapEditor);
   return;
   
   %moduleName = AssetBrowser.newAssetSettings.moduleName;
   %modulePath = "data/" @ %moduleName;
      
   %assetName = AssetBrowser.newAssetSettings.assetName;
   
   %tamlpath = %modulePath @ "/cubemaps/" @ %assetName @ ".asset.taml";
   %shapeFilePath = %modulePath @ "/cubemaps/" @ %assetName @ ".dae";
   
   %asset = new CubemapAsset()
   {
      AssetName = %assetName;
      versionId = 1;
      friendlyName = AssetBrowser.newAssetSettings.friendlyName;
      description = AssetBrowser.newAssetSettings.description;
      fileName = %assetName @ ".dae";
   };
   
   TamlWrite(%asset, %tamlpath);
   
   Canvas.popDialog(AssetBrowser_newComponentAsset);
	
	%moduleDef = ModuleDatabase.findModule(%moduleName, 1);
	AssetDatabase.addDeclaredAsset(%moduleDef, %tamlpath);

	AssetBrowser.loadFilters();
	
	%treeItemId = AssetBrowserFilterTree.findItemByName(%moduleName);
	%smItem = AssetBrowserFilterTree.findChildItemByName(%treeItemId, "CubemapAsset");
	
	AssetBrowserFilterTree.onSelect(%smItem);
	
	return %tamlpath;
}

function AssetBrowser::editCubemapAsset(%this, %assetDef)
{
   %this.hideDialog();
   CubemapEditor.openCubemapAsset(%assetDef);    
}

function GuiInspectorTypeCubemapAssetPtr::onControlDropped( %this, %payload, %position )
{
   Canvas.popDialog(EditorDragAndDropLayer);
   
   // Make sure this is a color swatch drag operation.
   if( !%payload.parentGroup.isInNamespaceHierarchy( "AssetPreviewControlType_AssetDrop" ) )
      return;

   %assetType = %payload.dragSourceControl.parentGroup.assetType;
   
   if(%assetType $= "CubemapAsset")
   {
      echo("DROPPED A CUBEMAP ON A CUBEMAP ASSET COMPONENT FIELD!");  
      
      %module = %payload.dragSourceControl.parentGroup.moduleName;
      %asset = %payload.dragSourceControl.parentGroup.assetName;
      
      %targetComponent = %this.ComponentOwner;
      %targetComponent.CubemapAsset = %module @ ":" @ %asset;
      
      //Inspector.refresh();
   }
   
   EWorldEditor.isDirty = true;
}