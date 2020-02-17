function AssetBrowser::createGUIAsset(%this)
{
   %moduleName = AssetBrowser.newAssetSettings.moduleName;
   %modulePath = "data/" @ %moduleName;
      
   %assetName = AssetBrowser.newAssetSettings.assetName;
   
   %assetPath = AssetBrowser.dirHandler.currentAddress @ "/";
   
   %tamlpath = %assetPath @ %assetName @ ".asset.taml";
   %guipath = %assetPath @ %assetName @ ".gui";
   %scriptPath = %assetPath @ %assetName @ ".cs";
   
   %asset = new GUIAsset()
   {
      AssetName = %assetName;
      versionId = 1;
      scriptFile = %assetName @ ".cs";
      guiFile = %assetName @ ".gui";
   };
   
   TamlWrite(%asset, %tamlpath);
   
   %file = new FileObject();
   %templateFile = new FileObject();
   
   %guiTemplateCodeFilePath = %this.templateFilesPath @ "guiFile.gui.template";
   
   if(%file.openForWrite(%guipath) && %templateFile.openForRead(%guiTemplateCodeFilePath))
   {
      while( !%templateFile.isEOF() )
      {
         %line = %templateFile.readline();
         %line = strreplace( %line, "@@", %assetName );
         
         %file.writeline(%line);
         echo(%line);
      }
      
      %file.close();
      %templateFile.close();
   }
   else
   {
      %file.close();
      %templateFile.close();
      
      warnf("CreateGUIAsset - Something went wrong and we couldn't write the GUI file!");
   }
   
   %scriptTemplateCodeFilePath = %this.templateFilesPath @ "guiFile.cs.template";
   
   if(%file.openForWrite(%scriptPath) && %templateFile.openForRead(%scriptTemplateCodeFilePath))
   {
      while( !%templateFile.isEOF() )
      {
         %line = %templateFile.readline();
         %line = strreplace( %line, "@@", %assetName );
         
         %file.writeline(%line);
         echo(%line);
      }
      
      %file.close();
      %templateFile.close();
   }
   else
   {
      %file.close();
      %templateFile.close();
      
      warnf("CreateGUIAsset - Something went wrong and we couldn't write the GUI script file!");
   }
   
	//load the gui
	exec(%guipath);
	exec(%scriptPath);
	
	%moduleDef = ModuleDatabase.findModule(%moduleName, 1);
	AssetDatabase.addDeclaredAsset(%moduleDef, %tamlpath);

	AssetBrowser.loadFilters();
	
	%treeItemId = AssetBrowserFilterTree.findItemByName(%moduleName);
	%smItem = AssetBrowserFilterTree.findChildItemByName(%treeItemId, "GUIs");
	
	AssetBrowserFilterTree.onSelect(%smItem);
	
	return %tamlpath;  
}

function AssetBrowser::inspectImportingGUIAsset(%this, %assetItem)
{
   AssetImportCtrl-->NewAssetsInspector.startGroup("GUI");
   
   AssetImportCtrl-->NewAssetsInspector.addField("GUIFile", "GUI File Path", "filename", "Intended usage case of this image. Used to map to material slots and set up texture profiles.", "", 
                                                      "", %assetItem);
                                                      
   //Make this a callback so that if it's set we can callback to a validator function
   //This function(and others for other asset types) would check if the loosefile audit window is open, and if it is, remove the file from the list
   AssetImportCtrl-->NewAssetsInspector.addField("ScriptFile", "Script File Path", "filename", "Intended usage case of this image. Used to map to material slots and set up texture profiles.", "", 
                                                      "", %assetItem);                                                  
   AssetImportCtrl-->NewAssetsInspector.endGroup();                                                
}

function AssetBrowser::editGUIAsset(%this, %assetDef)
{
   if(!isObject(%assetDef.assetName))
   {
      exec(%assetDef.GUIFilePath);
      exec(%assetDef.mScriptFilePath);
   }
   
   GuiEditContent(%assetDef.assetName);  
}

//Renames the asset
function AssetBrowser::renameGUIAsset(%this, %assetDef, %newAssetName)
{
   %newScriptLooseFilename = renameAssetLooseFile(%assetDef.scriptFile, %newAssetName);
   
   if(!%newScriptLooseFilename $= "")
      return;
      
   %newGUILooseFilename = renameAssetLooseFile(%assetDef.guiFile, %newAssetName);
   
   if(!%newGUILooseFilename $= "")
      return;
      
   %assetDef.scriptFile = %newScriptLooseFilename;
   %assetDef.guiFile = %newGUILooseFilename;
   %assetDef.saveAsset();
   
   renameAssetFile(%assetDef, %newAssetName);
}

//Deletes the asset
function AssetBrowser::deleteGUIAsset(%this, %assetDef)
{
   AssetDatabase.deleteAsset(%assetDef.getAssetId(), true);
}

//Moves the asset to a new path/module
function AssetBrowser::moveGUIAsset(%this, %assetDef, %destination)
{
   %currentModule = AssetDatabase.getAssetModule(%assetDef.getAssetId());
   %targetModule = AssetBrowser.getModuleFromAddress(%destination);
   
   %newAssetPath = moveAssetFile(%assetDef, %destination);
   
   if(%newAssetPath $= "")
      return false;

   moveAssetLooseFile(%assetDef.guifile, %destination);
   moveAssetLooseFile(%assetDef.scriptFile, %destination);
   
   AssetDatabase.removeDeclaredAsset(%assetDef.getAssetId());
   AssetDatabase.addDeclaredAsset(%targetModule, %newAssetPath);
}


function AssetBrowser::buildGUIAssetPreview(%this, %assetDef, %previewData)
{
   %previewData.assetName = %assetDef.assetName;
   %previewData.assetPath = %assetDef.GUIFilePath;
   %previewData.doubleClickCommand = "";
   
   %previewData.previewImage = "tools/assetBrowser/art/guiIcon";
   
   %previewData.assetFriendlyName = %assetDef.assetName;
   %previewData.assetDesc = %assetDef.description;
   %previewData.tooltip = %assetDef.assetName;
}