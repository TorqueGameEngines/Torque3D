function AssetBrowser::createGUIAsset(%this)
{
   %moduleName = AssetBrowser.newAssetSettings.moduleName;
   %modulePath = "data/" @ %moduleName;
      
   %assetName = AssetBrowser.newAssetSettings.assetName;
   
   %assetPath = AssetBrowser.currentAddress @ "/";
   
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

function AssetBrowser::editGUIAsset(%this, %assetDef)
{
   if(!isObject(%assetDef.assetName))
   {
      exec(%assetDef.GUIFilePath);
      exec(%assetDef.mScriptFilePath);
   }
   
   GuiEditContent(%assetDef.assetName);  
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