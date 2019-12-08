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
      %assetDef = AssetDatabase.acquireAsset(EditAssetPopup.assetId);
      
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
   
   AssetBrowser.selectedAssetPreview-->AssetNameLabel.setActive(true);
   AssetBrowser.selectedAssetPreview-->AssetNameLabel.setFirstResponder();
}

function AssetBrowser::performRenameAsset(%this, %originalAssetName, %newName)
{
   //if the name is different to the asset's original name, rename it!
   if(%originalAssetName !$= %newName)
   {
      if(EditAssetPopup.assetType !$= "Folder")
      {
         %moduleName = AssetBrowser.selectedModule;
         
         //do a rename!
         %success = AssetDatabase.renameDeclaredAsset(%moduleName @ ":" @ %originalAssetName, %moduleName @ ":" @ %newName);
         
         if(%success)
            echo("AssetBrowser - renaming of asset " @ %moduleName @ ":" @ %originalAssetName @ " to " @ %moduleName @ ":" @ %newName @ " was a success.");
         else 
            echo("AssetBrowser - renaming of asset " @ %moduleName @ ":" @ %originalAssetName @ " to " @ %moduleName @ ":" @ %newName @ " was a failure.");
         
         if(%success)
         {
            %newAssetId = %moduleName @ ":" @ %newName;
            %assetPath = AssetDatabase.getAssetFilePath(%newAssetId);
            
            //Rename any associated files as well
            %assetDef = AssetDatabase.acquireAsset(%newAssetId);
            %assetType = %assetDef.getClassName();
            
            //rename the file to match
            %path = filePath(%assetPath);
            
            //Do the rename command
            %buildCommand = %this @ ".rename" @ %assetType @ "(" @ %assetDef @ "," @ %newAssetId @ ");";
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
         eval(%this @ ".moveFolder("@EditAssetPopup.assetId@",\""@%destination@"\");");
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

//------------------------------------------------------------

function AssetBrowser::duplicateAsset(%this, %targetModule)
{
   if(%targetModule $= "")
   {
      //we need a module to duplicate to first
      Canvas.pushDialog(AssetBrowser_selectModule);
      AssetBrowser_selectModule.callback = "AssetBrowser.duplicateAsset";
      return;
   }
   
   %assetDef = AssetDatabase.acquireAsset(EditAssetPopup.assetId);
   %assetType = AssetDatabase.getAssetType(EditAssetPopup.assetId);
   
   //this acts as a redirect based on asset type and will enact the appropriate function
   //so for a GameObjectAsset, it'll become %this.duplicateGameObjectAsset(%assetDef, %targetModule);
   //and call to the tools/assetBrowser/scripts/assetTypes/gameObject.cs file for implementation
   if(%this.isMethod("duplicate"@%assetType))
      eval(%this @ ".duplicate"@%assetType@"("@%assetDef@","@%targetModule@");");
}

function AssetBrowser::deleteAsset(%this)
{
   //Find out what type it is
   //%assetDef = AssetDatabase.acquireAsset(EditAssetPopup.assetId);
   //%assetType = %assetDef.getClassName();
   
   MessageBoxOKCancel("Warning!", "This will delete the selected content and the files associated to it, do you wish to continue?", 
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