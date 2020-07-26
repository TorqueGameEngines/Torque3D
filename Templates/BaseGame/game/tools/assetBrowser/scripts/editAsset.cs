function AssetBrowser_editAsset::saveAsset(%this)
{
   %file = AssetDatabase.getAssetFilePath(%this.editedAssetId);
   %success = TamlWrite(AssetBrowser_editAsset.editedAsset, %file);
   
   AssetBrowser.loadFilters();

   Canvas.popDialog(AssetBrowser_editAsset);
}

function AssetBrowser::editAsset(%this, %assetDef)
{
   //Find out what type it is
   //If the passed-in definition param is blank, then we're likely called via a popup
   if(%assetDef $= "")
   {
      if(AssetDatabase.isDeclaredAsset(EditAssetPopup.assetId))
      {
         %assetDef = AssetDatabase.acquireAsset(EditAssetPopup.assetId);
      }
      else
      {
         //if it's not a valid asset at all, then it's probably a folder
         %folder = strreplace(EditAssetPopup.assetId, ":", "/");
         if(isDirectory(%folder))
         {
            AssetBrowser.navigateTo(%folder);
         }
      }
   }
      
      
   %assetType = %assetDef.getClassName();
   
   //Build out the edit command
   %buildCommand = %this @ ".edit" @ %assetType @ "(" @ %assetDef @ ");";
   eval(%buildCommand);
}

function AssetBrowser::appendSubLevel(%this)
{
   %assetDef = AssetDatabase.acquireAsset(EditAssetPopup.assetId);
   %assetType = %assetDef.getClassName();
      
   schedule( 1, 0, "EditorOpenSceneAppend", %assetDef);
}

function AssetBrowser::editAssetInfo(%this)
{
   Canvas.pushDialog(AssetBrowser_editAsset); 
   
   %assetDef = AssetDatabase.acquireAsset(EditAssetPopup.assetId);
   
   eval("AssetBrowser.tempAsset = new " @ %assetDef.getClassName() @ "();");
   AssetBrowser.tempAsset.assignFieldsFrom(%assetDef);
   
   AssetEditInspector.inspect(AssetBrowser.tempAsset);  
   AssetBrowser_editAsset.editedAssetId = EditAssetPopup.assetId;
   AssetBrowser_editAsset.editedAsset = AssetBrowser.tempAsset;
   
   //remove some of the groups we don't need:
   for(%i=0; %i < AssetEditInspector.getCount(); %i++)
   {
      %caption = AssetEditInspector.getObject(%i).caption;
      
      if(%caption $= "Ungrouped" || %caption $= "Object" || %caption $= "Editing" 
         || %caption $= "Persistence" || %caption $= "Dynamic Fields")
      {
         AssetEditInspector.remove(AssetEditInspector.getObject(%i));
         %i--;
      }
   }
}

//------------------------------------------------------------

function AssetBrowser::refreshAsset(%this, %assetId)
{
   if(%assetId $= "")
   {
      //if we have no passed-in asset ID, we're probably going through the popup menu, so get our edit popup id  
      %assetId = EditAssetPopup.assetId;
   }
   
   AssetDatabase.refreshAsset(%assetId);
   %this.refresh();
}

//------------------------------------------------------------

function AssetBrowser::renameAsset(%this)
{
   //Find out what type it is
   //%assetDef = AssetDatabase.acquireAsset(EditAssetPopup.assetId);
   
   %curFirstResponder = AssetBrowser.getFirstResponder();
   
   if(%curFirstResponder != 0)
      %curFirstResponder.clearFirstResponder();
   
   if(EditFolderPopup.visible == false)
   {
      AssetBrowser.selectedAssetPreview-->AssetNameLabel.setActive(true);
      AssetBrowser.selectedAssetPreview-->AssetNameLabel.setFirstResponder();
   }
}

function AssetBrowser::performRenameAsset(%this, %originalAssetName, %newName)
{
   //if the name is different to the asset's original name, rename it!
   if(%originalAssetName !$= %newName)
   {
      %moduleName = AssetBrowser.selectedModule;
      
      if(EditAssetPopup.assetType !$= "Folder")
      {
         if(%this.isMethod("rename" @ EditAssetPopup.assetType))
         {
            %oldAssetId = %moduleName @ ":" @ %originalAssetName;
            %assetDef = AssetDatabase.acquireAsset(%oldAssetId);
            
            //Do the rename command
            %buildCommand = %this @ ".rename" @ EditAssetPopup.assetType @ "(" @ %assetDef @ "," @ %newName @ ");";
            eval(%buildCommand);
         }
      }
      else
      {
         %buildCommand = %this @ ".renameFolder(\"" @ EditAssetPopup.assetId @ "\",\"" @ %newName @ "\");";
         eval(%buildCommand);      
      }
   }
   
   //Make sure everything is refreshed
   %this.refresh();
   
   //Update the selection to immediately jump to the new asset
   AssetBrowser-->filterTree.clearSelection();
   %ModuleItem = AssetBrowser-->filterTree.findItemByName(%moduleName);
   %assetTypeId = AssetBrowser-->filterTree.findChildItemByName(%ModuleItem, %assetType);
   
   AssetBrowser-->filterTree.selectItem(%assetTypeId);
   
   %selectedItem = AssetBrowser-->filterTree.getSelectedItem();
   AssetBrowser-->filterTree.scrollVisibleByObjectId(%selectedItem);
   
   AssetBrowser-->filterTree.buildVisibleTree(); 
}

function renameAssetFile(%assetDef, %newName)
{
   %assetId = %assetDef.getAssetID();
   %module = AssetDatabase.getAssetModule(%assetId);
   %moduleId = %module.moduleId;
   
   %assetPath = AssetDatabase.getAssetFilePath(%assetId);
   
   %newPath = filePath(%assetPath) @ "/" @ %newName @ ".asset.taml";
   %copiedSuccess = pathCopy(%assetPath, %newPath);
   
   if(!%copiedSuccess)
      return "";
   
   %deleteSuccess = fileDelete(%assetPath);
   
   if(!%deleteSuccess)
      return "";
      
   //Remove the old declaration
   AssetDatabase.removeDeclaredAsset(%assetId);
   //Add with the new file
   AssetDatabase.addDeclaredAsset(%module, %newPath);
   
   //Perform the rename in the file/system itself
   AssetDatabase.renameDeclaredAsset(%assetId, %moduleId @ ":" @ %newName);
}

function renameAssetLooseFile(%file, %newName)
{
   %newPath = filePath(%file) @ "/" @ %newName @ fileExt(%file);
   %copiedSuccess = pathCopy(%file, %newPath);
   
   if(!%copiedSuccess)
      return "";
   
   %deleteSuccess = fileDelete(%file);
   
   if(!%deleteSuccess)
      return "";
   
   return fileName(%newPath);
}


function AssetNameField::onReturn(%this)
{
   %this.clearFirstResponder();
   %this.setActive(false);
   
   AssetBrowser.performRenameAsset(%this.originalAssetName, %this.getText());
}

//------------------------------------------------------------
function AssetBrowser::moveAsset(%this, %assetId, %destination)
{
   if(EditAssetPopup.assetType $= "Folder")
   {
      //Do any cleanup required given the type
      if(%this.isMethod("moveFolder"))
         eval(%this @ ".moveFolder("@%assetId@",\""@%destination@"\");");
   }
   else
   {
      %assetDef = AssetDatabase.acquireAsset(%assetId);
      %assetType = AssetDatabase.getAssetType(%assetId);
      
      //Do any cleanup required given the type
      if(%this.isMethod("move"@%assetType))
      {
         %command = %this @ ".move" @ %assetType @ "(" @ %assetDef @ ",\"" @ %destination @ "\");";
         eval(%this @ ".move" @ %assetType @ "(" @ %assetDef @ ",\"" @ %destination @ "\");");
      }
   }
   
   %this.refresh();
}

function moveAssetFile(%assetDef, %destinationPath)
{
   %assetPath = makeFullPath(AssetDatabase.getAssetFilePath(%assetDef.getAssetId()));
   %assetFilename = fileName(%assetPath);
   
   %newAssetPath = %destination @ "/" @ %assetFilename;
   
   %copiedSuccess = pathCopy(%assetPath, %destination @ "/" @ %assetFilename);
   
   if(!%copiedSuccess)
      return "";
      
   %deleteSuccess = fileDelete(%assetPath);
   
   if(!%deleteSuccess)
      return "";
      
   return %newAssetPath;
}

function moveAssetLooseFile(%file, %destinationPath)
{
   %filename = fileName(%file);
   
   %copiedSuccess = pathCopy(%file, %destinationPath @ "/" @ %filename);
   
   if(!%copiedSuccess)
      return false;
      
   %deleteSuccess = fileDelete(%file);
   return %deleteSuccess;
}

//------------------------------------------------------------

function AssetBrowser::duplicateAsset(%this)
{
   %assetDef = AssetDatabase.acquireAsset(EditAssetPopup.assetId);
   %assetType = AssetDatabase.getAssetType(EditAssetPopup.assetId);
   
   %trailingNum = getTrailingNumber(%assetDef.assetName);
   if(%trailingNum != -1)
   {
      %trailingNum++;
      %newName = stripTrailingNumber(%assetDef.assetName) @ (%trailingNum);
   }
   else
   {
      %newName = stripTrailingNumber(%assetDef.assetName) @ "1";
   }
   
   AssetBrowser_assetNameEditTxt.text = %newName;
   
   AssetBrowser_assetNameEdit.callback = "AssetBrowser.doDuplicateAsset();";
   
   if(EditorSettings.value("AssetManagement/Assets/promptOnRename", "1") == 1)
      Canvas.pushDialog(AssetBrowser_assetNameEdit);
   else
      eval(AssetBrowser_assetNameEdit.callback);
}

function AssetBrowser::doDuplicateAsset(%this)
{
   %assetDef = AssetDatabase.acquireAsset(EditAssetPopup.assetId);
   %assetType = AssetDatabase.getAssetType(EditAssetPopup.assetId);
   
   if(AssetBrowser_assetNameEditTxt.text !$= "" && AssetBrowser_assetNameEditTxt.text !$= %assetDef.assetName)
   {
      //this acts as a redirect based on asset type and will enact the appropriate function
      //so for a GameObjectAsset, it'll become %this.duplicateGameObjectAsset(%assetDef, %targetModule);
      //and call to the tools/assetBrowser/scripts/assetTypes/gameObject.cs file for implementation
      if(%this.isMethod("duplicate"@%assetType))
         eval(%this @ ".duplicate"@%assetType@"("@%assetDef@","@AssetBrowser_assetNameEditTxt.text@");");
         
      AssetBrowser.refresh();
   }
}

function duplicateAssetFile(%assetDef, %newAssetName)
{
   %assetPath = makeFullPath(AssetDatabase.getAssetFilePath(%assetDef.getAssetId()));
   %assetFilepath = filePath(%assetPath);
   %assetFileExt = fileExt(%assetPath);
   
   %newAssetPath = %assetFilepath @ "/" @ %newAssetName @ ".asset.taml";
   
   %copiedSuccess = pathCopy(%assetPath, %newAssetPath);
   
   if(!%copiedSuccess)
      return "";
      
   replaceInFile(%newAssetPath, %assetDef.assetName, %newAssetName);
   
   %module = AssetBrowser.dirHandler.getModuleFromAddress(%newAssetPath);
      
   //Add with the new file
   AssetDatabase.addDeclaredAsset(%module, %newAssetPath);
      
   return %newAssetPath;
}

function duplicateAssetLooseFile(%file, %newFilename)
{
   %filePath = filePath(%file);
   %fileExt = fileExt(%file);
   
   %newPath = %filePath @ "/" @ %newFilename @ %fileExt;
   %copiedSuccess = pathCopy(%file, %newPath);
   
   if(!%copiedSuccess)
      return "";

   return %newPath;
}


//------------------------------------------------------------

function AssetBrowser::deleteAsset(%this)
{
   //Find out what type it is
   //%assetDef = AssetDatabase.acquireAsset(EditAssetPopup.assetId);
   //%assetType = %assetDef.getClassName();
   
   toolsMessageBoxOKCancel("Warning!", "This will delete the selected content and the files associated to it, do you wish to continue?", 
      "AssetBrowser.confirmDeleteAsset();", "");
}

function AssetBrowser::confirmDeleteAsset(%this)
{
   %currentSelectedItem = AssetBrowserFilterTree.getSelectedItem();
   %currentItemParent = AssetBrowserFilterTree.getParentItem(%currentSelectedItem);
   
   if(EditFolderPopup.visible)
   {
      if(EditFolderPopup.dirPath !$= "")
         %folderPath = EditFolderPopup.dirPath;
      else
         %folderPath = AssetBrowserFilterTree.getItemValue(%currentSelectedItem) @ "/" @ AssetBrowserFilterTree.getItemText(%currentSelectedItem);
         
      if(%this.isMethod("deleteFolder"))
         eval(%this @ ".deleteFolder(\""@%folderPath@"\");");
   }   
   else
   {
      %assetDef = AssetDatabase.acquireAsset(EditAssetPopup.assetId);
      %assetType = AssetDatabase.getAssetType(EditAssetPopup.assetType);
      
      if(!isObject(%assetDef))
         return;
      
      //Do any cleanup required given the type
      if(%this.isMethod("delete"@%assetType))
         eval(%this @ ".delete"@%assetType@"("@%assetDef@");");
      
      AssetDatabase.deleteAsset(EditAssetPopup.assetId, true, false);
   }

   %this.refresh();
}

//------------------------------------------------------------
function AssetBrowser::updateAssetReference(%this, %targetPath, %oldAssetId, %newAssetId)
{
   //assetbrowser.updateAssetReference("data/pbr/levels", "pbr:material_ball", "TreeTest:TestTree");
   //this will go through every file in the game directory and swap the assetIDs to update the reference in the event something was renamed, or something was moved
   //This is potentially disastrous and break a lot of things if done hapazardly, so be careful
   %fullPath = makeFullPath(%targetPath);
   
   //First, wipe out any files inside the folder first
   %file = findFirstFileMultiExpr( %fullPath @ "/*.*", true);
   %fileObj = new FileObject();
   
   new ArrayObject(lineCache);

   while( %file !$= "" )
   {      
      lineCache.empty();
      
      %fileModified = false;
      if(%fileObj.openForRead(%file))
      {
         while( !%fileObj.isEOF() )
         {
            %unModLine = %fileObj.readLine();
            %line = strreplace( %unModLine, %oldAssetId, %newAssetId );
            
            if(%unModLine !$= %line)
               %fileModified = true;
               
            lineCache.add(%line);
         }
      }
      
      if(%fileModified && %fileObj.openForWrite(%file))
      {
         for(%i=0; %i<lineCache.count(); %i++)
         {
            %line = lineCache.getKey(%i);

            %fileObj.writeline(%line);
         }
         
         %fileObj.close();
      }
      
      %file = findNextFileMultiExpr( %fullPath @ "/*.*" );
   }
   
   lineCache.delete();
   %fileObj.delete();
}