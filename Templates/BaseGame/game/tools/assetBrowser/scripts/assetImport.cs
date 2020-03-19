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

function ImportAssetWindow::showDialog(%this)
{
   //prep the import control
   Canvas.pushDialog(AssetImportCtrl);
   AssetImportCtrl.setHidden(true);
      
   ImportAssetWindow.assetHeirarchyChanged = false;
   
   %defaultConfig = EditorSettings.value("Assets/AssetImporDefaultConfig", "");
   if(%defaultConfig !$= "")
   {
      %defaultConfigIdx = ImportAssetConfigList.findText(%defaultConfig);
      ImportAssetConfigList.setSelected(%defaultConfigIdx);
   }
   else
   {
      ImportAssetConfigList.setSelected(0);
   }

   %this.dirty = false;
}

function ImportAssetWindow::Close(%this)
{
   //Some cleanup
   ImportAssetWindow.importingFilesArray.empty();
   
   %this.importTempDirHandler.deleteFolder("tools/assetBrowser/importTemp/*/");
   
   if(ImportAssetWindow.isAwake())
      ImportAssetWindow.refresh();
      
   ImportAssetItems.empty();
      
   Canvas.popDialog();  
}
//
function ImportAssetWindow::onWake(%this)
{
   //We've woken, meaning we're trying to import assets
   //Lets refresh our list
   if(!ImportAssetWindow.isVisible())
      return;
      
   AssetImportSettings.read();
   
   %this.reloadImportOptionConfigs();
   
   AssetImportCtrl-->NewAssetsTree.buildIconTable( ":tools/classIcons/TSStatic:tools/classIcons/TSStatic" @
                                             ":tools/classIcons/material:tools/classIcons/material"@
                                             ":tools/classIcons/GuiBitmapCtrl:tools/classIcons/GuiBitmapCtrl"@
                                             ":tools/classIcons/SFXEmitter:tools/classIcons/SFXEmitter"@
                                             ":tools/gui/images/iconWarn:tools/gui/images/iconWarn"@
                                             ":tools/gui/images/iconError:tools/gui/images/iconError");
   
   AssetImportTargetAddress.text = AssetBrowser.dirHandler.currentAddress;
   AssetImportTargetModule.text = AssetBrowser.dirHandler.getModuleFromAddress(AssetBrowser.dirHandler.currentAddress).ModuleId;
   ImportAssetConfigList.setSelected(0);
   
   ImportActivityLog.empty();
   
   %this.refresh();
}

//
//
function isImageFormat(%fileExt)
{
   if( (%fileExt $= ".png") || (%fileExt $= ".jpg") || (%fileExt $= ".bmp") || (%fileExt $= ".dds") || (%fileExt $= ".tif"))
      return true;
      
   return false;
}

function isShapeFormat(%fileExt)
{
   if( (%fileExt $= ".dae") || 
   (%fileExt $= ".dts") || 
   (%fileExt $= ".fbx") || 
   (%fileExt $= ".gltf") || 
   (%fileExt $= ".glb") || 
   (%fileExt $= ".obj") || 
   (%fileExt $= ".blend"))
      return true;
      
   return false;
}

function isSoundFormat(%fileExt)
{
   if( (%fileExt $= ".ogg") || (%fileExt $= ".wav") || (%fileExt $= ".mp3"))
      return true;
      
   return false;
}

function getImageInfo(%file)
{
   //we're going to populate a GuiTreeCtrl with info of the inbound image file
}

//This lets us go and look for a image at the importing directory as long as it matches the material name
function findImageFile(%path, %materialName, %type)
{
   
   if(isFile(%path @ "/" @ %materialName @ ".jpg"))
      return %path @ "/" @ %materialName @ ".jpg";
   else if(isFile(%path @ "/" @ %materialName @ ".png"))
      return %path @ "/" @ %materialName @ ".png";
   else if(isFile(%path @ "/" @ %materialName @ ".dds"))
      return %path @ "/" @ %materialName @ ".dds";
   else if(isFile(%path @ "/" @ %materialName @ ".tif"))
      return %path @ "/" @ %materialName @ ".tif";
}

function AssetBrowser::onBeginDropFiles( %this )
{   
   if(!AssetBrowser.isAwake())
      return;
      
   error("% DragDrop - Beginning files dropping.");
   if(!ImportAssetWindow.isAwake())
      ImportAssetWindow.showDialog();
}

function AssetBrowser::onDropFile( %this, %filePath )
{
   if(!%this.isVisible())
      return;
      
   %fileExt = fileExt( %filePath );
   //add it to our array!
   if(isImageFormat(%fileExt))
      %assetItem = %this.addImportingAsset("ImageAsset", %filePath);
   else if( isShapeFormat(%fileExt))
      %assetItem = %this.addImportingAsset("ShapeAsset", %filePath);
   else if( isSoundFormat(%fileExt))
      %assetItem = %this.addImportingAsset("SoundAsset", %filePath);
   else if( %fileExt $= ".cs" || %fileExt $= ".cs.dso" )
      %assetItem = %this.addImportingAsset("ScriptAsset", %filePath);
   else if( %fileExt $= ".gui" || %fileExt $= ".gui.dso" )
      %assetItem = %this.addImportingAsset("GUIAsset", %filePath);
   else if (%fileExt $= ".zip")
      %this.onDropZipFile(%filePath);
   else if( %fileExt $= "")
      %this.onDropFolder(%filePath);
      
   if(%assetItem !$= "")
   {
      SessionImportAssetItems.add(%assetItem);
      ImportAssetItems.add(%assetItem);
   }
      
   //Used to keep tabs on what files we were trying to import, used mainly in the event of
   //adjusting configs and needing to completely reprocess the import
   //ensure we're not doubling-up on files by accident
   if(ImportAssetWindow.importingFilesArray.getIndexFromKey(%filePath) == -1)
      ImportAssetWindow.importingFilesArray.add(%filePath);
}

function AssetBrowser::onDropZipFile(%this, %filePath)
{
   if(!%this.isVisible())
      return;
      
   %zip = new ZipObject();
   %zip.openArchive(%filePath);
   %count = %zip.getFileEntryCount();
   
   echo("Dropped in a zip file with" SPC %count SPC "files inside!");
   
   for (%i = 0; %i < %count; %i++)
   {
      %fileEntry = %zip.getFileEntry(%i);
      %fileFrom = getField(%fileEntry, 0);
      
      //First, we wanna scan to see if we have modules to contend with. If we do, we'll just plunk them in wholesale
      //and not process their contents.
      
      //If not modules, it's likely an art pack or other mixed files, so we'll import them as normal
      /*if( (%fileExt $= ".png") || (%fileExt $= ".jpg") || (%fileExt $= ".bmp") || (%fileExt $= ".dds") )
         %this.importAssetListArray.add("ImageAsset", %filePath);
      else if( (%fileExt $= ".dae") || (%fileExt $= ".dts"))
         %this.importAssetListArray.add("ShapeAsset", %filePath);
      else if( (%fileExt $= ".ogg") || (%fileExt $= ".wav") || (%fileExt $= ".mp3"))
         %this.importAssetListArray.add("SoundAsset", %filePath);
      else if( (%fileExt $= ".gui") || (%fileExt $= ".gui.dso"))
         %this.importAssetListArray.add("GUIAsset", %filePath);
      //else if( (%fileExt $= ".cs") || (%fileExt $= ".dso"))
      //   %this.importAssetListArray.add("Script", %filePath);
      else if( (%fileExt $= ".mis"))
         %this.importAssetListArray.add("LevelAsset", %filePath);*/
         
      // For now, if it's a .cs file, we'll assume it's a behavior.
      //if (fileExt(%fileFrom) !$= ".cs")
      //   continue;
      
      %fileTo = expandFilename("^tools/assetBrowser/importTemp/") @ %fileFrom;
      %zip.extractFile(%fileFrom, %fileTo);
      //exec(%fileTo);
   }
   
   %zip.delete();
   
   //Next, we loop over the files and import them
}

function AssetBrowser::onDropFolder(%this, %filePath)
{
   if(!%this.isVisible())
      return;
      
   %zip = new ZipObject();
   %zip.openArchive(%filePath);
   %count = %zip.getFileEntryCount();
   
   echo("Dropped in a zip file with" SPC %count SPC "files inside!");
   
   return;
   for (%i = 0; %i < %count; %i++)
   {
      %fileEntry = %zip.getFileEntry(%i);
      %fileFrom = getField(%fileEntry, 0);
      
      //First, we wanna scan to see if we have modules to contend with. If we do, we'll just plunk them in wholesale
      //and not process their contents.
      
      //If not modules, it's likely an art pack or other mixed files, so we'll import them as normal
      if( (%fileExt $= ".png") || (%fileExt $= ".jpg") || (%fileExt $= ".bmp") || (%fileExt $= ".dds") )
         %this.importAssetListArray.add("ImageAsset", %filePath);
      else if( (%fileExt $= ".dae") || (%fileExt $= ".dts"))
         %this.importAssetListArray.add("ShapeAsset", %filePath);
      else if( (%fileExt $= ".ogg") || (%fileExt $= ".wav") || (%fileExt $= ".mp3"))
         %this.importAssetListArray.add("SoundAsset", %filePath);
      else if( (%fileExt $= ".gui") || (%fileExt $= ".gui.dso"))
         %this.importAssetListArray.add("GUIAsset", %filePath);
      //else if( (%fileExt $= ".cs") || (%fileExt $= ".dso"))
      //   %this.importAssetListArray.add("Script", %filePath);
      else if( (%fileExt $= ".mis"))
         %this.importAssetListArray.add("LevelAsset", %filePath);
         
      // For now, if it's a .cs file, we'll assume it's a behavior.
      if (fileExt(%fileFrom) !$= ".cs")
         continue;
      
      %fileTo = expandFilename("^game/behaviors/") @ fileName(%fileFrom);
      %zip.extractFile(%fileFrom, %fileTo);
      exec(%fileTo);
   }
}

function AssetBrowser::onEndDropFiles( %this )
{
   if(!%this.isVisible())
      return;
      
   ImportAssetWindow.refresh();
}

//
//
//
function AssetBrowser::reloadImportingFiles(%this)
{
   //Effectively, we re-import the files we were trying to originally. We'd only usually do this in the event we change our import config
   %this.onBeginDropFiles();
   
   for(%i=0; %i < ImportAssetWindow.importingFilesArray.count(); %i++)
   {
      %this.onDropFile(ImportAssetWindow.importingFilesArray.getKey(%i));
   }
    
   %this.onEndDropFiles();  
}

function AssetBrowser::addImportingAsset( %this, %assetType, %filePath, %parentAssetItem, %assetNameOverride )
{
   //In some cases(usually generated assets on import, like materials) we'll want to specifically define the asset name instead of peeled from the filePath
   if(%assetNameOverride !$= "")
      %assetName = %assetNameOverride;
   else
      %assetName = fileBase(%filePath);
      
   //We don't get a file path at all if we're a generated entry, like materials
   //if we have a file path, though, then sanitize it
   if(%filePath !$= "")
      %filePath = filePath(%filePath) @ "/" @ fileBase(%filePath) @ fileExt(%filePath);
   
   %moduleName = AssetBrowser.SelectedModule;
   ImportAssetModuleList.text = %moduleName;
   
   //Add to our main list
   %assetItem = new ScriptObject()
   {
      assetType = %assetType;
      filePath = %filePath;
      assetName = %assetName;
      cleanAssetName = %assetName; 
      moduleName = %moduleName;
      dirty  = true;
      parentAssetItem = %parentAssetItem;
      status = "";
      statusType = "";
      statusInfo = "";
      skip = false;
      processed = false;
      generatedAsset = false;
      childAssetItems = new ArrayObject(){};
   };
   
   if(%parentAssetItem !$= "")
   {
      ImportActivityLog.add("Added Child Importing Asset to " @ %parentAssetItem.assetName);
   }
   else
   {
      ImportActivityLog.add("Added Importing Asset");
   }
   
   ImportActivityLog.add("   Asset Info: Name: " @ %assetName @ " | Type: " @ %assetType);
   
   if(%filePath !$= "")
      ImportActivityLog.add("   File: " @ %filePath);
   
   if(%parentAssetItem $= "")
   {
      %asd = true;
   }
   else
   {
      %parentAssetItem.childAssetItems.add(%assetItem);
   }
   
   ImportAssetWindow.refresh();
   
   return %assetItem;
}

function ImportAssetWindow::reloadImportOptionConfigs(%this)
{
   if(!isObject(ImportAssetWindow.importConfigsList))
      ImportAssetWindow.importConfigsList = new ArrayObject();
   else
      ImportAssetWindow.importConfigsList.empty();
      
   ImportAssetConfigList.clear();
   
   %xmlDoc = new SimXMLDocument();
   if(%xmlDoc.loadFile($AssetBrowser::importConfigsFile))
   {
      //StateMachine element
      if(!%xmlDoc.pushFirstChildElement("AssetImportSettings"))
      {
         error("Invalid Import Configs file");
         return;  
      }
      
      //Config Groups
      %configCount = 0;
      %hasGroup = %xmlDoc.pushFirstChildElement("Group");
      while(%hasGroup)
      {
         %configName = %xmlDoc.attribute("name");
         
         ImportAssetWindow.importConfigsList.add(%configName);
         ImportAssetConfigList.add(%configName);
         
         %hasGroup = %xmlDoc.nextSiblingElement("Group");
      }

      %xmlDoc.popElement();
   }
   
   %xmlDoc.delete();
   
   %importConfigIdx = ImportAssetWindow.activeImportConfigIndex;
   if(%importConfigIdx $= "")
      %importConfigIdx = 0;
      
   //ImportAssetConfigList.setSelected(%importConfigIdx);
}

//
function importLooseFile(%filePath, %forceAutoImport)
{
   if(%forceAutoImport)
   {
      //If we're attempting to fast-track the import, check that that's even an option
      if(ImportAssetWindow.importConfigsList.count() == 0 || 
      EditorSettings.value("Assets/AssetImporDefaultConfig") $= "" || 
      EditorSettings.value("Assets/AutoImport", false) == false)
         return false;      
   }
   %assetItem = AssetBrowser.addImportingAsset("ImageAsset", %filePath, "", "");
   ImportAssetItems.add(%assetItem);
   
   if(%forceAutoImport)
   {
      AssetImportTargetModule.text = AssetBrowser.dirHandler.getModuleFromAddress(filePath(%filePath)).ModuleId;
      
      //skip the refresh delay, we'll force it here
      ImportAssetWindow.doRefresh();
      
      if(ImportAssetWindow.hasImportIssues)
         return false;
   }
   
   $importedLooseFileAsset = %assetItem.moduleName @ ":" @ %assetItem.assetName;
   
   return true;
}

//
function assetImportUpdatePath(%newPath)
{
   AssetBrowser.navigateTo(%newPath);
   AssetImportTargetAddress.text = %newPath;
   AssetImportTargetModule.text = AssetBrowser.dirHandler.getModuleFromAddress(AssetBrowser.dirHandler.currentAddress).ModuleId;
}

//
function ImportAssetWindow::processImportAssets(%this, %assetItem)
{
   if(!isObject(%assetItem))
   {
      //Zero this out
      ImportAssetWindow.assetHeirarchyChanged = false;
      
      for(%i=0; %i < ImportAssetItems.count(); %i++)
      {
         %assetItem = ImportAssetItems.getKey(%i);
         
         if(!isObject(%assetItem) || %assetItem.skip )
            return;
            
         if(%assetItem.processed == false)
         {
            //sanetize before modifying our asset name(suffix additions, etc)      
            if(%assetItem.assetName !$= %assetItem.cleanAssetName)
               %assetItem.assetName = %assetItem.cleanAssetName;
            
            if(%assetItem.assetType $= "AnimationAsset")
            {
               //if we don't have our own file, that means we're gunna be using our parent shape's file so reference that
               if(!isFile(%assetItem.filePath))
               {
                  %assetItem.filePath = %assetItem.parentAssetItem.filePath;
               }
            }
            
            if(AssetBrowser.isMethod("prepareImport" @ %assetItem.assetType))
            {
               %command = AssetBrowser @ ".prepareImport" @ %assetItem.assetType @ "(" @ %assetItem @ ");";
               eval(%command);
            }
            
            %assetItem.processed = true;
         }
         
         %this.processImportAssets(%assetItem);
      }
   }
   else
   {
      for(%i=0; %i < %assetItem.childAssetItems.count(); %i++)
      {
         %childAssetItem = %assetItem.childAssetItems.getKey(%i);
         
         if(!isObject(%childAssetItem) || %childAssetItem.skip)
            return;
            
         if(%childAssetItem.processed == false)
         {
            //sanetize before modifying our asset name(suffix additions, etc)      
            if(%childAssetItem.assetName !$= %childAssetItem.cleanAssetName)
               %childAssetItem.assetName = %childAssetItem.cleanAssetName;
            
            if(%childAssetItem.assetType $= "AnimationAsset")
            {
               //if we don't have our own file, that means we're gunna be using our parent shape's file so reference that
               if(!isFile(%childAssetItem.filePath))
               {
                  %childAssetItem.filePath = %childAssetItem.parentAssetItem.filePath;
               }
            }
            
            if(AssetBrowser.isMethod("prepareImport" @ %childAssetItem.assetType))
            {
               %command = AssetBrowser @ ".prepareImport" @ %childAssetItem.assetType @ "(" @ %childAssetItem @ ");";
               eval(%command);
            }
            
            %childAssetItem.processed = true;
         }
         
         %this.processImportAssets(%childAssetItem);
      }
   }
   
   //If our hierarchy changed, it's because we did so during processing
   //so we'll loop back through again until everything has been processed
   if(ImportAssetWindow.assetHeirarchyChanged)
      %this.processImportAssets();
}

function ImportAssetWindow::findImportingAssetByName(%this, %assetName, %assetItem)
{
   if(!isObject(%assetItem))
   {
      for(%i=0; %i < ImportAssetItems.count(); %i++)
      {
         %assetItem = ImportAssetItems.getKey(%i);
         
         if(!isObject(%assetItem))
            return;
            
         if(isObject(%assetItem) && %assetItem.cleanAssetName $= %assetName)
         {
            return %assetItem;
         }
         
         %ret = %this.findImportingAssetByName(%assetName, %assetItem);
         if(%ret !$= "")
            return %ret;
      }
   }
   else
   {
      for(%i=0; %i < %assetItem.childAssetItems.count(); %i++)
      {
         %childAssetItem = %assetItem.childAssetItems.getKey(%i);
         
         if(!isObject(%childAssetItem))
            return;
            
         if(isObject(%childAssetItem) && %childAssetItem.cleanAssetName $= %assetName)
         {
            return %childAssetItem;
         }
         
         %ret = %this.findImportingAssetByName(%assetName, %childAssetItem);
         if(%ret !$= "")
            return %ret;
      }
   }
   
   return "";
}

function refreshImportAssetWindow()
{
   ImportAssetWindow.refresh();  
}

function ImportAssetWindow::refresh(%this)
{
   if(!%this.dirty)
   {
      %this.dirty = true;
      
      %this.schedule(16, "doRefresh");
   }
}

function ImportAssetWindow::doRefresh(%this)
{
   %this.ImportingAssets = 0;
   %this.FetchedAssets = 0;
   %this.prunedDuplicateAssets = 0;
   %this.autoRenamedAssets = 0;
   
   //Go through and process any newly, unprocessed assets
   %this.processImportAssets();
   
   ImportAssetWindow.hasImportIssues = %this.validateAssets();
   
   AssetImportCtrl-->NewAssetsTree.clear();
   AssetImportCtrl-->NewAssetsTree.insertItem(0, "Importing Assets");
   
   for(%i=0; %i < ImportAssetItems.count(); %i++)
   {
      %assetItem = ImportAssetItems.getKey(%i);
      
      %this.refreshAssetItem(%assetItem);
   }
   
   AssetImportCtrl-->NewAssetsTree.buildVisibleTree(true);
   
   %ImportActionSummary = "";
   
   if(%this.ImportingAssets != 0)
   {
      %ImportActionSummary = %ImportActionSummary SPC %this.ImportingAssets @ " Imported|";
   }
   if(%this.FetchedAssets != 0)
   {
      %ImportActionSummary = %ImportActionSummary SPC %this.FetchedAssets @ " Fetched|";
   }
   if(%this.prunedDuplicateAssets != 0)
   {
      %ImportActionSummary = %ImportActionSummary SPC %this.prunedDuplicateAssets @ " Duplicates Pruned|";
   }
   if(%this.autoRenamedAssets != 0)
   {
      %ImportActionSummary = %ImportActionSummary SPC %this.autoRenamedAssets @ " Auto Renamed|";
   }
   
   warn(%ImportActionSummary);
   
   AssetImportSummarization.Text = %ImportActionSummary;
   
   //If we have a valid config file set and we've set to auto-import, and we have no
   //issues for importing, then go ahead and run the import immediately, don't
   //bother showing the window.
   //If any of these conditions fail, we'll display the import window so it can be handled
   //by the user
   if(ImportAssetWindow.importConfigsList.count() != 0 && 
      EditorSettings.value("Assets/AssetImporDefaultConfig") !$= "" && 
      EditorSettings.value("Assets/AutoImport", false) == true
      && ImportAssetWindow.hasImportIssues == false)
   {
      AssetImportCtrl.setHidden(true);
      ImportAssetWindow.visible = false;
      
      //Go ahead and check if we have any issues, and if not, run the import!
      ImportAssetWindow.ImportAssets();
   }
   else
   {
      //we have assets to import, so go ahead and display the window for that now
      AssetImportCtrl.setHidden(false);
      ImportAssetWindow.visible = true;
      ImportAssetWindow.selectWindow();
   }
   
   if(ImportAssetWindow.hasImportIssues && getAssetImportConfigValue("General/PreventImportWithErrors", "0") == 1)
   {
      DoAssetImportButton.enabled = false;  
   }
   else
   {
      DoAssetImportButton.enabled = true;  
   }

   if(ImportAssetWindow.importConfigsList.count() == 0)
   {
      MessageBoxOK( "Warning", "No base import config. Please create an import configuration set to simplify asset importing.");
   }
   
   %this.dirty = false;
}

function ImportAssetWindow::refreshAssetItem(%this, %assetItem)
{
    if(!isObject(%assetItem) || %assetItem.skip)
      return;
      
   %assetType = %assetItem.assetType;
   %filePath = %assetItem.filePath;
   %assetName = %assetItem.assetName;
   
   //Once validated, attempt any fixes for issues
   %this.resolveIssue(%assetItem);
   
   //create!
   %toolTip = "";
   
   if(%assetType $= "ShapeAsset" || %assetType $= "AnimationAsset" || %assetType $= "ImageAsset" || %assetType $= "SoundAsset")
   {
      if(%assetItem.status $= "Error")
      {
         %iconIdx = 11;
      }
      else if(%assetItem.status $= "Warning")
      {
         %iconIdx = 9;
      }
      
      %configCommand = "ImportAssetOptionsWindow.fixIssues(" @ %assetItem @ ");";
         
      if(%assetItem.statusType $= "DuplicateAsset" || %assetItem.statusType $= "DuplicateImportAsset")
         %assetName = %assetItem.assetName @ " <Duplicate Asset>";
   }
   else
   {
      if(%assetItem.status $= "Error")
      {
         %iconIdx = 11;
      }
      else if(%assetItem.status $= "Warning")
      {
         %iconIdx = 9;
      }
      
      if(%assetItem.statusType $= "DuplicateAsset" || %assetItem.statusType $= "DuplicateImportAsset")
         %assetName = %assetItem.assetName @ " <Duplicate Asset>";
   }
   
   %toolTip = %assetItem.statusInfo;

   if(%assetItem.status $= "")
   {
      if(%assetType $= "ShapeAsset")
         %iconIdx = 1;
      else if(%assetType $= "MaterialAsset")
         %iconIdx = 3;
      else if(%assetType $= "ImageAsset")
         %iconIdx = 5;
      else if(%assetType $= "SoundAsset")
         %iconIdx = 7;
   }
      
   %parentTreeIdx = %assetItem.parentAssetItem.treeIdx;
   if(%parentTreeIdx $= "")
      %parentTreeIdx = 1;
      
   %assetItem.treeIdx = AssetImportCtrl-->NewAssetsTree.insertItem(%parentTreeIdx, %assetName, %assetItem, "", %iconIdx, %iconIdx+1);

   for(%i=0; %i < %assetItem.childAssetItems.count(); %i++)
   {
      %childAssetItem = %assetItem.childAssetItems.getKey(%i);
      %this.refreshAssetItem(%childAssetItem);
   }
}

//
function NewAssetsViewTree::onSelect(%this, %itemId)
{
	if(%itemId == 1)
		//can't select root
		return;
		
   %assetItem = %this.getItemValue(%itemId);
   
   AssetImportCtrl-->NewAssetsInspector.clearFields();
   
   AssetImportCtrl-->NewAssetsInspector.startGroup("General");
   AssetImportCtrl-->NewAssetsInspector.addField("assetName", "Asset Name", "string", "", %assetItem.assetName, "", %assetItem);
   AssetImportCtrl-->NewAssetsInspector.addField("assetType", "Asset Type", "string", "", %assetItem.assetType, "", %assetItem);
   
   if(!%assetItem.generatedAsset)
      AssetImportCtrl-->NewAssetsInspector.addField("filePath", "File Path", "fileName", "", %assetItem.filePath, "", %assetItem);
   
   //AssetImportCtrl-->NewAssetsInspector.addField("assetName", "Asset Name", "string", "", %assetItem.assetName, "", %assetItem);
   //AssetImportCtrl-->NewAssetsInspector.addField("assetName", "Asset Name", "string", "", %assetItem.assetName, "", %assetItem);
   
   AssetImportCtrl-->NewAssetsInspector.addField("status", "Status", "string", "", %assetItem.status, "", %assetItem);
   AssetImportCtrl-->NewAssetsInspector.endGroup();
   
   AssetImportCtrl-->NewAssetsInspector.setFieldEnabled("assetType", false);
   
   if(AssetBrowser.isMethod("inspectImporting" @ %assetItem.assetType))
   {
      %command = "AssetBrowser.inspectImporting" @ %assetItem.assetType @ "(" @ %assetItem @ ");"; 
      eval(%command); 
   }
   //AssetImportCtrl-->NewAssetsInspector.setFieldEnabled("status", false);
   
   /*moduleName = %moduleName;
   dirty  = true;
   parentAssetItem = %parentAssetItem;
   status = "";
   statusType = "";
   statusInfo = "";
   skip = false;
   processed = false;
   generatedAsset = false;*/
}

function NewAssetsViewTree::onRightMouseDown(%this, %itemId)
{
   ImportAssetActions.enableItem(1, true);
   
   if( %itemId != 1 && %itemId != -1)
   {
      %assetItem = %this.getItemValue(%itemId);
      
      if(%assetItem.assetType $= "MaterialAsset")
      {
         %contextPopup = ImportAssetMaterialMaps;
         
         for(%i=0; %i < 7; %i++)
         {
            %contextPopup.enableItem(%i, true);
         }
         
         if(isObject(%assetItem.diffuseImageAsset))
            %contextPopup.enableItem(0, false);
            
         if(isObject(%assetItem.normalImageAsset))
            %contextPopup.enableItem(1, false);
            
         if(isObject(%assetItem.compositeImageAsset))
            %contextPopup.enableItem(2, false);
      }
      else
      {
         %contextPopup = ImportAssetActions;  
      }
      %contextPopup.showPopup(Canvas);
      %contextPopup.assetItem = %assetItem;
      %contextPopup.itemId = %itemId;
   }
   else
   {
      ImportAssetActions.showPopup(Canvas);
   }
}

function NewAssetsPanelInputs::onRightMouseDown(%this)
{
   NewAssetsViewTree::onRightMouseDown(0, -1);
}

//
function ImportAssetWindow::removeImportingAsset(%this)
{
   ImportActivityLog.add("Removing Asset from Import");
   
   %this.deleteImportingAsset(ImportAssetActions.assetItem);
   
   //ImportAssetWindow.refresh();
}

function ImportAssetWindow::addNewImportingAsset(%this, %filterType)
{
   %filter = "Any Files (*.*)|*.*|";
   
   if(%filterType $= "Sound" || %filterType $= "")
      %filter = "Sound Files(*.wav, *.ogg)|*.wav;*.ogg|" @ %filter;
   if(%filterType $= "Image" || %filterType $= "")
      %filter = "Images Files(*.jpg,*.png,*.tga,*.bmp,*.dds)|*.jpg;*.png;*.tga;*.bmp;*.dds|" @ %filter;
   if(%filterType $= "Shape" || %filterType $= "")
      %filter = "Shape Files(*.dae, *.cached.dts)|*.dae;*.cached.dts|" @ %filter;
      
   //get our item depending on which action we're trying for
   if(ImportAssetActions.visible)
      %parentAssetItem = ImportAssetActions.assetItem;
   else if(ImportAssetMaterialMaps.visible)
      %parentAssetItem = ImportAssetMaterialMaps.assetItem;
      
   %defaultPath = filePath(%parentAssetItem.filePath) @ "/";
      
   %dlg = new OpenFileDialog()
   {
      Filters = %filter;
      DefaultFile = %defaultPath;
      ChangePath = false;
      MustExist = true;
      MultipleFiles = false;
      forceRelativePath = false;
   };
      
   if ( %dlg.Execute() )
   {
      %filePath = %dlg.FileName;
   }
   
   %dlg.delete();
   
   if(%filePath $= "")
      return "";
   
   //AssetBrowser.onDropFile( %path );
   
   %fileExt = fileExt( %filePath );
   //add it to our array!
   if(isImageFormat(%fileExt))
      %type = "ImageAsset";
   else if( isShapeFormat(%fileExt))
      %type = "ShapeAsset";
   else if( isSoundFormat(%fileExt))
      %type = "SoundAsset";
   else if( %fileExt $= ".cs" || %fileExt $= ".cs.dso" )
      %type = "ScriptAsset";
   else if( %fileExt $= ".gui" || %fileExt $= ".gui.dso" )
      %type = "GUIAsset";
      
   %newAssetItem = AssetBrowser.addImportingAsset(%type, %filePath, %parentAssetItem);
      
   //Used to keep tabs on what files we were trying to import, used mainly in the event of
   //adjusting configs and needing to completely reprocess the import
   //ensure we're not doubling-up on files by accident
   if(%this.importingFilesArray.getIndexFromKey(%filePath) == -1)
      %this.importingFilesArray.add(%filePath);
         
   AssetBrowser.onEndDropFiles();
   
   return %newAssetItem;
}

function ImportAssetWindow::addMaterialMap(%this, %map)
{
   %newAssetItem = %this.addNewImportingAsset("Image");
   
   %newAssetItem.ImageType = %map;
}

//
function ImportAssetWindow::importResolution(%this, %assetItem)
{
   if(%assetItem.status !$= "Error" && %assetItem.status !$= "Warning")
   {
      //If nothing's wrong, we just edit it
      ImportAssetOptionsWindow.editImportSettings(%assetItem);
      return;
   }
   else
   {
      ImportAssetResolutionsPopup.assetItem = %assetItem;
      if(%assetItem.statusType $= "DuplicateAsset" || %assetItem.statusType $= "DuplicateImportAsset")
      {
         ImportAssetResolutionsPopup.enableItem(3, false); //Rename
         ImportAssetResolutionsPopup.enableItem(5, false); //Find Missing
      }
      else if(%assetItem.statusType $= "MissingFile")
      {
         ImportAssetResolutionsPopup.enableItem(0, false); //Use Orig
         ImportAssetResolutionsPopup.enableItem(1, false); //Use Dupe
         ImportAssetResolutionsPopup.enableItem(3, false); //Rename
      }
   }
   
   ImportAssetResolutionsPopup.showPopup(Canvas);  
}

function ImportAssetWindow::validateAssets(%this, %assetItem)
{
   ImportAssetWindow.importIssues = false;
   
   //Clear any status
   %this.resetAssetsValidationStatus();
   
   for(%i=0; %i < ImportAssetItems.count(); %i++)
   {
      %assetItem = ImportAssetItems.getKey(%i);
      
      %this.validateAsset(%assetItem);
   }
   
   if(ImportAssetWindow.importIssues == false)
      return false;
   else
      return true;
}

function ImportAssetWindow::validateAsset(%this, %assetItem)
{
   %moduleName = AssetImportTargetModule.getText();
   
   if(!isObject(%assetItem) || %assetItem.skip)
   {
      return; 
   }
   
   //First, check the obvious: name collisions. We should have no asset that shares a similar name.
   //If we do, prompt for it be renamed first before continuing
   %hasCollision = %this.checkAssetsForCollision(%assetItem);
   
   //Ran into a problem, so end checks on this one and move on
   if(%hasCollision)
      return;
   
   //No collisions of for this name in the importing assets. Now, check against the existing assets in the target module
   if(!AssetBrowser.isAssetReImport)
   {
      %assetQuery = new AssetQuery();
      
      %numAssetsFound = AssetDatabase.findAllAssets(%assetQuery);

      %foundCollision = false;
      for( %f=0; %f < %numAssetsFound; %f++)
      {
         %assetId = %assetQuery.getAsset(%f);
          
         //first, get the asset's module, as our major categories
         %module = AssetDatabase.getAssetModule(%assetId);
         
         %testModuleName = %module.moduleId;
         
         //These are core, native-level components, so we're not going to be messing with this module at all, skip it
         if(%moduleName !$= %testModuleName)
            continue;

         %testAssetName = AssetDatabase.getAssetName(%assetId);
         
         if(%testAssetName $= %assetItem.assetName)
         {
            %foundCollision = true;
            
            %assetItem.status = "error";
            %assetItem.statusType = "DuplicateAsset";
            %assetItem.statusInfo = "Duplicate asset names found with the target module!\nAsset \"" @ 
            %assetItem.assetName @ "\" of type \"" @ %assetItem.assetType @ "\" has a matching name.\nPlease rename it and try again!";
               
            ImportActivityLog.add("Error! Asset " @ %assetItem.assetName @ " has an identically named asset in the target module");

            break;
         }
      }
      
      if(%foundCollision == true)
      {
         //yup, a collision, prompt for the change and bail out
         /*MessageBoxOK( "Error!", "Duplicate asset names found with the target module!\nAsset \"" @ 
            %assetItemA.assetName @ "\" of type \"" @ %assetItemA.assetType @ "\" has a matching name.\nPlease rename it and try again!");*/
            
         //%assetQuery.delete();
         //return false;
      }
      
      //Clean up our queries
      %assetQuery.delete();
   }
      
   //Check if we were given a file path(so not generated) but somehow isn't a valid file
   if(%assetItem.filePath !$= ""  && !%assetItem.generatedAsset && !isFile(%assetItem.filePath))
   {
      %assetItem.status = "error";
      %assetItem.statusType = "MissingFile";
      %assetItem.statusInfo = "Unable to find file to be imported. Please select asset file.";
      
      ImportActivityLog.add("Error! Asset " @ %assetItem.filePath @ " was not found");
   }
   
   if(%assetItem.status $= "Warning")
   {
      if(getAssetImportConfigValue("General/WarningsAsErrors", "0") == 1)
      {
         %assetItem.status = "error";
         
         ImportActivityLog.add("Warnings treated as errors!");
      }
   }
   
   if(%assetItem.status $= "error")
      ImportAssetWindow.importIssues = true;
      
   for(%i=0; %i < %assetItem.childAssetItems.count(); %i++)
   {
      %childAssetItem = %assetItem.childAssetItems.getKey(%i);
      
      %this.validateAsset(%childAssetItem);
   }
}
//

function ImportAssetWindow::resetAssetsValidationStatus(%this, %assetItem)
{
   if(!isObject(%assetItem))
   {
      for(%i=0; %i < ImportAssetItems.count(); %i++)
      {
         %assetItem = ImportAssetItems.getKey(%i);
         
         if(!isObject(%assetItem) || %assetItem.skip)
            continue;
            
         %assetItem.status = "";
         %assetItem.statusType = "";
         %assetItem.statusInfo = "";
         
         if(%assetItem.childAssetItems.count() != 0)
            %this.resetAssetsValidationStatus(%assetItem);
      }
   }
   else
   {
      for(%i=0; %i < %assetItem.childAssetItems.count(); %i++)
      {
         %childAssetItem = %assetItem.childAssetItems.getKey(%i);
         
         if(!isObject(%childAssetItem) || %childAssetItem.skip)
            continue;
            
         %childAssetItem.status = "";
         %childAssetItem.statusType = "";
         %childAssetItem.statusInfo = "";
         
         if(%childAssetItem.childAssetItems.count() != 0)
            %this.resetAssetsValidationStatus(%childAssetItem);
      }
   }
}

function ImportAssetWindow::checkAssetsForCollision(%this, %assetItemToCheck, %assetItem)
{
   %result = false;
   
   if(!isObject(%assetItem))
   {
      for(%i=0; %i < ImportAssetItems.count(); %i++)
      {
         %assetItem = ImportAssetItems.getKey(%i);
         
         if(!isObject(%assetItem) || %assetItem.skip)
            continue;
            
         if( (%assetItemToCheck.assetName $= %assetItem.assetName) && (%assetItemToCheck.getId() != %assetItem.getId()) )
         {
            //yup, a collision, prompt for the change and bail out
            %assetItemToCheck.status = "Warning";
            %assetItemToCheck.statusType = "DuplicateImportAsset";
            %assetItemToCheck.statusInfo = "Duplicate asset names found with importing assets!\nAsset \"" @ 
               %assetItem.assetName @ "\" of type \"" @ %assetItem.assetType @ "\" and \"" @
               %assetItemToCheck.assetName @ "\" of type \"" @ %assetItemToCheck.assetType @ "\" have matching names.\nPlease rename one of them and try again!";
               
            ImportActivityLog.add("Warning! Asset " @ %assetItemToCheck.assetName @ ", type " @ %assetItemToCheck.assetType @ " has a naming collisions with asset " @ %assetItem.assetName @ ", type " @ %assetItem.assetType);

            return true;
         }
         
         if(%assetItem.childAssetItems.count() != 0)
         {
            //recurse!
            %result = %this.checkAssetsForCollision(%assetItemToCheck, %assetItem); 
         }
            
         if(%result)
            return %result;
      }
   }
   else
   {
      for(%i=0; %i < %assetItem.childAssetItems.count(); %i++)
      {
         %childAssetItem = %assetItem.childAssetItems.getKey(%i);
         
         if(!isObject(%childAssetItem) || %childAssetItem.skip)
            continue;
            
         if( (%assetItemToCheck.assetName $= %childAssetItem.assetName) && (%assetItemToCheck.getId() != %childAssetItem.getId()) )
         {
            //yup, a collision, prompt for the change and bail out
            %assetItemToCheck.status = "Warning";
            %assetItemToCheck.statusType = "DuplicateImportAsset";
            %assetItemToCheck.statusInfo = "Duplicate asset names found with importing assets!\nAsset \"" @ 
               %childAssetItem.assetName @ "\" of type \"" @ %childAssetItem.assetType @ "\" and \"" @
               %assetItemToCheck.assetName @ "\" of type \"" @ %assetItemToCheck.assetType @ "\" have matching names.\nPlease rename one of them and try again!";
               
            ImportActivityLog.add("Warning! Asset " @ %assetItemToCheck.assetName @ ", type " @ %assetItemToCheck.assetType @ " has a naming collisions with asset " @ %childAssetItem.assetName @ ", type " @ %childAssetItem.assetType);

            return true;
         }
         
         if(%childAssetItem.childAssetItems.count() != 0)
         {
            //recurse!
            %result = %this.checkAssetsForCollision(%assetItemToCheck, %childAssetItem); 
         }
         
         if(%result)
            return %result;
      }
   }
   
   return result;
}

//
function ImportAssetWindow::deleteImportingAsset(%this, %assetItem)
{
   if(%assetItem.parentAssetItem !$= "")
   {
      %idx = %assetItem.parentAssetItem.childAssetItems.getIndexFromKey(%assetItem);
      %assetItem.parentAssetItem.childAssetItems.erase(%idx);
      
      ImportActivityLog.add("Deleting Importing Asset " @ %assetItem.assetName @ " from it's parent item: " @ %assetItem.parentAssetItem);
   }

   ImportActivityLog.add("Deleting Importing Asset " @ %assetItem.assetName @ " and all it's child items");
   
   %idx = ImportAssetItems.getIndexFromKey(%assetItem);
   ImportAssetItems.erase(%idx);
   
   schedule(10, 0, "refreshImportAssetWindow");
}

//
function ImportAssetWindow::ImportAssets(%this)
{
   //do the actual importing, now!
   %assetCount = ImportAssetItems.count();
   
   //get the selected module data
   %moduleName = AssetImportTargetModule.getText();
   
   %module = ModuleDatabase.findModule(%moduleName, 1);
   
   if(!isObject(%module))
   {
      MessageBoxOK( "Error!", "No module selected. You must select or create a module for the assets to be added to.");
      return;
   }
   
   %this.doImportAssets();
   
   //force an update of any and all modules so we have an up-to-date asset list
   AssetBrowser.refresh();
   Canvas.popDialog(AssetImportCtrl);
   AssetBrowser.isAssetReImport = false;
}

function ImportAssetWindow::doImportAssets(%this, %assetItem)
{
   %moduleName = AssetImportTargetModule.getText();
   
   if(%assetItem $= "")
   {
      for(%i=0; %i < ImportAssetItems.count(); %i++)
      {
         %assetItem = ImportAssetItems.getKey(%i);
         
         if(!isObject(%assetItem) || %assetItem.skip)
            continue;  
         
         %assetType = %assetItem.AssetType;
         %filePath = %assetItem.filePath;
         %assetName = %assetItem.assetName;
         %assetImportSuccessful = false;
         %assetId = %moduleName@":"@%assetName;
         
         %command = "AssetBrowser.import" @ %assetType @ "(" @ %assetItem @ ");";
         eval(%command);
         
         //recurse if needed
         %this.doImportAssets(%assetItem);
      }
   }
   else
   {
      for(%i=0; %i < %assetItem.childAssetItems.count(); %i++)
      {
         %childAssetItem = %assetItem.childAssetItems.getKey(%i);
         
         if(!isObject(%childAssetItem) || %childAssetItem.skip)
            continue;  
         
         %assetType = %childAssetItem.AssetType;
         %filePath = %childAssetItem.filePath;
         %assetName = %childAssetItem.assetName;
         %assetImportSuccessful = false;
         %assetId = %moduleName@":"@%assetName;
         
         %command = "AssetBrowser.import" @ %assetType @ "(" @ %childAssetItem @ ");";
         eval(%command);
         
         //recurse if needed
         %this.doImportAssets(%childAssetItem);
      }
   }
}

function ImportAssetWindow::doImportAsset(%this, %assetItem)
{
   %assetItem = ImportAssetTree.getItemObject(%id);
      
   if(!isObject(%assetItem) || %assetItem.skip)
   {
      %id = ImportAssetTree.getNextSibling(%id);
      continue;  
   }
   
   %assetType = %assetItem.AssetType;
   %filePath = %assetItem.filePath;
   %assetName = %assetItem.assetName;
   %assetImportSuccessful = false;
   %assetId = %moduleName@":"@%assetName;
   
   if(%assetType $= "ImageAsset")
   {
      AssetBrowser.importImageAsset(%assetItem);
   }
   else if(%assetType $= "ShapeAsset")
   {
      AssetBrowser.importShapeAsset(%assetItem);
   }
   else if(%assetType $= "AnimationAsset")
   {
      %assetPath = "data/" @ %moduleName @ "/ShapeAnimations";
      %assetFullPath = %assetPath @ "/" @ fileName(%filePath);
      
      %newAsset = new ShapeAnimationAsset()
      {
         assetName = %assetName;
         versionId = 1;
         fileName = %assetFullPath;
         originalFilePath = %filePath;
         animationFile = %assetFullPath;
         animationName = %assetName;
         startFrame = 0;
         endFrame = -1;
         padRotation = false;
         padTransforms = false;
      };

      %assetImportSuccessful = TAMLWrite(%newAsset, %assetPath @ "/" @ %assetName @ ".asset.taml"); 
      
      //and copy the file into the relevent directory
      %doOverwrite = !AssetBrowser.isAssetReImport;
      if(!pathCopy(%filePath, %assetFullPath, %doOverwrite))
      {
         error("Unable to import asset: " @ %filePath);
      }
   }
   else if(%assetType $= "SoundAsset")
   {
      %assetPath = "data/" @ %moduleName @ "/Sounds";
      %assetFullPath = %assetPath @ "/" @ fileName(%filePath);
      
      %newAsset = new SoundAsset()
      {
         assetName = %assetName;
         versionId = 1;
         fileName = %assetFullPath;
         originalFilePath = %filePath;
      };
      
      %assetImportSuccessful = TAMLWrite(%newAsset, %assetPath @ "/" @ %assetName @ ".asset.taml"); 
      
      //and copy the file into the relevent directory
      %doOverwrite = !AssetBrowser.isAssetReImport;
      if(!pathCopy(%filePath, %assetFullPath, %doOverwrite))
      {
         error("Unable to import asset: " @ %filePath);
      }
   }
   else if(%assetType $= "MaterialAsset")
   {
      AssetBrowser.importMaterialAsset(%assetItem);
   }
   else if(%assetType $= "ScriptAsset")
   {
      %assetPath = "data/" @ %moduleName @ "/Scripts";
      %assetFullPath = %assetPath @ "/" @ fileName(%filePath);
      
      %newAsset = new ScriptAsset()
      {
         assetName = %assetName;
         versionId = 1;
         scriptFilePath = %assetFullPath;
         isServerSide = true;
         originalFilePath = %filePath;
      };
      
      %assetImportSuccessful = TAMLWrite(%newAsset, %assetPath @ "/" @ %assetName @ ".asset.taml"); 
      
      //and copy the file into the relevent directory
      %doOverwrite = !AssetBrowser.isAssetReImport;
      if(!pathCopy(%filePath, %assetFullPath, %doOverwrite))
      {
         error("Unable to import asset: " @ %filePath);
      }
   }
   else if(%assetType $= "GUIAsset")
   {
      %assetPath = "data/" @ %moduleName @ "/GUIs";
      %assetFullPath = %assetPath @ "/" @ fileName(%filePath);
      
      %newAsset = new GUIAsset()
      {
         assetName = %assetName;
         versionId = 1;
         GUIFilePath = %assetFullPath;
         scriptFilePath = "";
         originalFilePath = %filePath;
      };
      
      %assetImportSuccessful = TAMLWrite(%newAsset, %assetPath @ "/" @ %assetName @ ".asset.taml"); 
      
      //and copy the file into the relevent directory
      %doOverwrite = !AssetBrowser.isAssetReImport;
      if(!pathCopy(%filePath, %assetFullPath, %doOverwrite))
      {
         error("Unable to import asset: " @ %filePath);
      }
   }
   
   if(%assetImportSuccessful)
   {
      %moduleDef = ModuleDatabase.findModule(%moduleName,1);
      
      if(!AssetBrowser.isAssetReImport)
         AssetDatabase.addDeclaredAsset(%moduleDef, %assetPath @ "/" @ %assetName @ ".asset.taml");
      else
         AssetDatabase.refreshAsset(%assetId);
   }
   
   if(ImportAssetTree.isParentItem(%id))
   {
      %childItem = ImportAssetTree.getChild(%id);
      
      //recurse!
      %this.doImportAssets(%childItem); 
   }

   %id = ImportAssetTree.getNextSibling(%id);
}

function ImportAssetWindow::resolveIssue(%this, %assetItem)
{
   //Ok, we actually have a warning, so lets resolve
   if(%assetItem.statusType $= "DuplicateImportAsset" || %assetItem.statusType $= "DuplicateAsset")
   {
      %resolutionAction = getAssetImportConfigValue("General/DuplicatAutoResolution", "AutoPrune");
      
      %humanReadableStatus = %assetItem.statusType $= "DuplicateImportAsset" ? "Duplicate Import Asset" : "Duplicate Asset";
      
      if(%resolutionAction $= "AutoPrune")
      {
         %this.deleteImportingAsset(%assetItem);
         %this.prunedDuplicateAssets++;
         
         ImportActivityLog.add("Asset " @ %assetItem.assetName @ " was Autopruned due to " @ %humanReadableStatus);
      }
      else if(%resolutionAction $= "AutoRename")
      {
         ImportActivityLog.add("Asset " @ %assetItem.assetName @ " was Auto-Renamed due to " @ %humanReadableStatus);
         
         %noNum = stripTrailingNumber(%assetItem.assetName);
         %num = getTrailingNumber(%assetItem.assetName);
         
         if(%num == -1)
         {
            %assetItem.assetName = %noNum @ "1";  
         }
         else
         {
            %num++;
            %assetItem.assetName = %noNum @ %num; 
         }
         
         ImportActivityLog.add("   New name is " @ %assetItem.assetName);
         
         %this.autoRenamedAssets++;
      }
   }
   else if(%assetItem.statusType $= "MissingFile")
   {
      if(getAssetImportConfigValue("General/AutomaticallyPromptMissingFiles", "0") == 1)
      {
         %this.findMissingFile(%assetItem);
      }
   }
}

function ImportAssetWindow::findMissingFile(%this, %assetItem)
{
   if(%assetItem.assetType $= "ShapeAsset")
      %filters = "Shape Files(*.dae, *.cached.dts)|*.dae;*.cached.dts";
   else if(%assetItem.assetType $= "ImageAsset")
      %filters = "Images Files(*.jpg,*.png,*.tga,*.bmp,*.dds)|*.jpg;*.png;*.tga;*.bmp;*.dds";
      
   %dlg = new OpenFileDialog()
   {
      Filters        = %filters;
      DefaultPath    = $Pref::WorldEditor::LastPath;
      DefaultFile    = "";
      ChangePath     = true;
      OverwritePrompt = true;
      forceRelativePath = false;
      fileName="";
      //MultipleFiles = true;
   };

   %ret = %dlg.Execute();
   
   if ( %ret )
   {
      $Pref::WorldEditor::LastPath = filePath( %dlg.FileName );
      %fullPath = %dlg.FileName;//makeRelativePath( %dlg.FileName, getMainDotCSDir() );
   }   
   
   %dlg.delete();
   
   if ( !%ret )
      return;
      
   %assetItem.filePath = %fullPath;
   %assetItem.assetName = fileBase(%assetItem.filePath);
   
   /*if(%assetItem.assetType $= "ImageAsset")
   {
      //See if we have anything important to update for our material parent(if we have one)
      %treeItem = ImportAssetTree.findItemByObjectId(%assetItem);
      %parentItem = ImportAssetTree.getParentItem(%treeItem);
      
      if(%parentItem != 0)
      {
         %parentAssetItem = ImportAssetTree.getItemObject(%parentItem);
         if(%parentAssetItem.assetType $= "MaterialAsset")
         {
            AssetBrowser.prepareImportMaterialAsset(%parentAssetItem);              
         }
      }
   }*/
   
   ImportAssetWindow.refresh();
}
//

//
function ImportAssetWindow::toggleLogWindow()
{
   if(AssetBrowserImportLog.isAwake())
   {
      Canvas.popDialog(AssetBrowserImportLog);
      return;
   }
   else
   {
      Canvas.pushDialog(AssetBrowserImportLog);
   }
      
   ImportLogTextList.clear();
   for(%i=0; %i < ImportActivityLog.count(); %i++)
   {
      ImportLogTextList.addRow(%i, ImportActivityLog.getKey(%i));
   }
}
//

//
function ImportAssetModuleList::onWake(%this)
{
   %this.refresh();
}

function ImportAssetModuleList::refresh(%this)
{
   %this.clear();
   
   //First, get our list of modules
   %moduleList = ModuleDatabase.findModules();
   
   %count = getWordCount(%moduleList);
   for(%i=0; %i < %count; %i++)
   {
      %moduleName = getWord(%moduleList, %i);
      %this.add(%moduleName.ModuleId, %i);  
   }
}
//
