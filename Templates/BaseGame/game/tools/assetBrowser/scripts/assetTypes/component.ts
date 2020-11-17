function AssetBrowser::createComponentAsset(%this)
{
   %moduleName = AssetBrowser.newAssetSettings.moduleName;
   %modulePath = "data/" @ %moduleName;
      
   %assetName = AssetBrowser.newAssetSettings.assetName;
   
   %tamlpath = %modulePath @ "/components/" @ %assetName @ ".asset.taml";
   %scriptPath = %modulePath @ "/components/" @ %assetName @ ".cs";
   
   %asset = new ComponentAsset()
   {
      AssetName = %assetName;
      versionId = 1;
      componentName = %assetName;
      componentClass = AssetBrowser.newAssetSettings.parentClass;
      friendlyName = AssetBrowser.newAssetSettings.friendlyName;
      componentType = AssetBrowser.newAssetSettings.componentGroup;
      description = AssetBrowser.newAssetSettings.description;
      scriptFile = %assetName @ ".cs";
   };
   
   TamlWrite(%asset, %tamlpath);
   
   %file = new FileObject();
	%templateFile = new FileObject();
	
   %templateCodeFilePath = %this.templateFilesPath @ "componentFile.cs.template";
   
   if(%file.openForWrite(%scriptPath) && %templateFile.openForRead(%templateCodeFilePath))
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
      
      warnf("CreateComponentAsset - Something went wrong and we couldn't write the Component script file!");
   }
	
	Canvas.popDialog(AssetBrowser_newComponentAsset);
	
	%moduleDef = ModuleDatabase.findModule(%moduleName, 1);
	AssetDatabase.addDeclaredAsset(%moduleDef, %tamlpath);

	AssetBrowser.loadFilters();
	
	%treeItemId = AssetBrowserFilterTree.findItemByName(%moduleName);
	%smItem = AssetBrowserFilterTree.findChildItemByName(%treeItemId, "ComponentAsset");
	
	AssetBrowserFilterTree.onSelect(%smItem);
	
	return %tamlpath;
}

function AssetBrowser::editComponentAsset(%this, %assetDef)
{
   %scriptFile = %assetDef.scriptFile;
   
   EditorOpenFileInTorsion(makeFullPath(%scriptFile), 0);
}

function AssetBrowser::duplicateComponentAsset(%this, %assetId)
{
   
}

function AssetBrowser::renameComponentAsset(%this, %assetDef, %newAssetId, %originalName, %newName)
{
   %assetPath = AssetDatabase.getAssetFilePath(%newAssetId);
   
   //rename the file to match
   %path = filePath(%assetPath);
         
   %oldScriptFilePath = %assetDef.scriptFile;
   %scriptFilePath = filePath(%assetDef.scriptFile);
   %scriptExt = fileExt(%assetDef.scriptFile);
   
   %newScriptFileName = %scriptFilePath @ "/" @ %newName @ %scriptExt;
   %newAssetFile = %path @ "/" @ %newName @ ".asset.taml";
   
   %assetDef.componentName = %newName;
   %assetDef.scriptFile = %newScriptFileName;
   
   TamlWrite(%assetDef, %newAssetFile);
   fileDelete(%assetPath);
   
   pathCopy(%oldScriptFilePath, %newScriptFileName);
   fileDelete(%oldScriptFilePath);
   
   //Go through our scriptfile and replace the old namespace with the new
   %editedFileContents = "";
   
   %file = new FileObject();
   if ( %file.openForRead( %newScriptFileName ) ) 
   {
      while ( !%file.isEOF() ) 
      {
         %line = %file.readLine();
         %line = trim( %line );
         
         %editedFileContents = %editedFileContents @ strreplace(%line, %originalAssetName, %newName) @ "\n";
      }
      
      %file.close();
   }
   
   if(%editedFileContents !$= "")
   {
      %file.openForWrite(%newScriptFileName);
      
      %file.writeline(%editedFileContents);
      
      %file.close();
   }
   
   exec(%newScriptFileName);   
}

//not used
function AssetBrowser::importComponentAsset(%this, %assetId)
{
   
}

function AssetBrowser::buildComponentAssetPreview(%this, %assetDef, %previewData)
{
   %previewData.assetName = %assetDef.assetName;
   %previewData.assetPath = %assetDef.scriptFile;
   %previewData.doubleClickCommand = "EditorOpenFileInTorsion( "@%previewData.assetPath@", 0 );";
   
   %previewData.previewImage = "tools/assetBrowser/art/componentIcon";
   
   %previewData.assetFriendlyName = %assetDef.friendlyName;
   %previewData.assetDesc = %assetDef.description;
   %previewData.tooltip = %assetDef.friendlyName @ "\n" @ %assetDef;
}