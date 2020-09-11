function AssetBrowser::createCubemapAsset(%this)
{
   Canvas.pushDialog(CubemapEditor);
   return;
   
   %moduleName = AssetBrowser.newAssetSettings.moduleName;
   %modulePath = "data/" @ %moduleName;
      
   %assetName = AssetBrowser.newAssetSettings.assetName;
   %assetPath = AssetBrowser.dirHandler.currentAddress @ "/";  
   
   %tamlpath = %assetPath @ %assetName @ ".asset.taml";
   %shapeFilePath = %assetPath @ %assetName @ ".dae";
   
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

//Renames the asset
function AssetBrowser::renameCubemapAsset(%this, %assetDef, %newAssetName)
{
   /*%newCodeLooseFilename = renameAssetLooseFile(%assetDef.codefile, %newAssetName);
   
   if(!%newCodeLooseFilename $= "")
      return;
      
   %newHeaderLooseFilename = renameAssetLooseFile(%assetDef.headerFile, %newAssetName);
   
   if(!%newHeaderLooseFilename $= "")
      return;
      
   %assetDef.codefile = %newCodeLooseFilename;
   %assetDef.headerFile = %newHeaderLooseFilename;
   %assetDef.saveAsset();
   
   renameAssetFile(%assetDef, %newAssetName);*/
}

//Deletes the asset
function AssetBrowser::deleteCubemapAsset(%this, %assetDef)
{
   AssetDatabase.deleteAsset(%assetDef.getAssetId(), true);
}

//Moves the asset to a new path/module
function AssetBrowser::moveCubemapAsset(%this, %assetDef, %destination)
{
   /*%currentModule = AssetDatabase.getAssetModule(%assetDef.getAssetId());
   %targetModule = AssetBrowser.getModuleFromAddress(%destination);
   
   %newAssetPath = moveAssetFile(%assetDef, %destination);
   
   if(%newAssetPath $= "")
      return false;

   moveAssetLooseFile(%assetDef.codeFile, %destination);
   moveAssetLooseFile(%assetDef.headerFile, %destination);
   
   AssetDatabase.removeDeclaredAsset(%assetDef.getAssetId());
   AssetDatabase.addDeclaredAsset(%targetModule, %newAssetPath);*/
}

function GuiInspectorTypeCubemapAssetPtr::onControlDropped( %this, %payload, %position )
{
   Canvas.popDialog(EditorDragAndDropLayer);
   
   // Make sure this is a color swatch drag operation.
   if( !%payload.parentGroup.isInNamespaceHierarchy( "AssetPreviewControlType_AssetDrop" ) )
      return;

   %assetType = %payload.assetType;
   
   if(%assetType $= "CubemapAsset")
   {
      echo("DROPPED A CUBEMAP ON A CUBEMAP ASSET COMPONENT FIELD!");  
      
      %module = %payload.moduleName;
      %asset = %payload.assetName;
      
      %targetComponent = %this.object;
      %targetComponent.CubemapAsset = %module @ ":" @ %asset;
      
      //Inspector.refresh();
   }
   
   EWorldEditor.isDirty = true;
}