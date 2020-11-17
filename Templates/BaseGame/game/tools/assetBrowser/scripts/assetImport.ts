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
   AssetImportCtrl.setHidden(false);
   
   ImportAssetWindow.allowAutoImport = true; //special-case override for if we want to force a manual import process
   
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
   ImportAssetWindow.importer.resetImportSession(true);
   //ImportAssetWindow.importingFilesArray.empty();
   
   %this.importTempDirHandler.deleteFolder("tools/assetBrowser/importTemp/*/");
   
   if(ImportAssetWindow.isAwake())
      ImportAssetWindow.refresh();
      
   //ImportAssetItems.empty();
      
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
   
   %this.importer.targetPath = AssetImportTargetAddress.getText();
   %this.importer.targetModuleId = AssetImportTargetModule.getText();
   
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

function getAssetTypeByFilename(%filePath)
{
   %fileExt = fileExt( %filePath );
   
   //add it to our array!
   if(isImageFormat(%fileExt))
      return "ImageAsset";
   else if( isShapeFormat(%fileExt))
      return "ShapeAsset";
   else if( isSoundFormat(%fileExt))
      return "SoundAsset";
   else if( %fileExt $= ".cs" || %fileExt $= ".cs.dso" )
      return "ScriptAsset";
   else if( %fileExt $= ".gui" || %fileExt $= ".gui.dso" )
      return "GUIAsset";
   else if (%fileExt $= ".zip")
      return "zip";
   else if( %fileExt $= "")
      return "folder";
   
   return "";
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
      
   ImportAssetWindow.importer.addImportingFile(%filePath);
      
   /*%fileExt = fileExt( %filePath );
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
   }*/
      
   //Used to keep tabs on what files we were trying to import, used mainly in the event of
   //adjusting configs and needing to completely reprocess the import
   //ensure we're not doubling-up on files by accident
   //if(ImportAssetWindow.importingFilesArray.getIndexFromKey(%filePath) == -1)
   //   ImportAssetWindow.importingFilesArray.add(%filePath);
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
   
   %assetName = strreplace( %assetName, " ", "_" );
   
   //Add to our main list
   %assetItem = new AssetImportObject()
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
   };
   
   ImportAssetWindow.importer.addImportingAssetItem(%assetItem, %parentAssetItem);
   
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
/*function importLooseFile(%filePath, %forceAutoImport)
{
   %assetType = getAssetTypeByFilename(%filePath);
   
   if(%forceAutoImport)
   {
      //If we're attempting to fast-track the import, check that that's even an option
      if(ImportAssetWindow.importConfigsList.count() == 0 || 
      EditorSettings.value("Assets/AssetImporDefaultConfig") $= "" || 
      EditorSettings.value("Assets/AutoImport", false) == false)
      {
         toolsMessageBoxOK("Unable to AutoImport", "Attempted to import a loose file " @ %filePath @ " with AutoImport but was unable to either due to lacking a valid import config, or the editor settings are not set to auto import.");
         return false;      
      }
      
      if(%assetType $= "folder" || %assetType $= "zip")
      {
         toolsMessageBoxOK("Unable to AutoImport", "Unable to auto import folders or zips at this time");
         return false; 
      }
      
      if(%assetType $= "")
      {
         toolsMessageBoxOK("Unable to AutoImport", "Unable to auto import unknown file type for file " @ %filePath);
         return false; 
      }
   }
   
   %assetItem = AssetBrowser.addImportingAsset(%assetType, %filePath, "", "");
   ImportAssetItems.add(%assetItem);
   
   if(%forceAutoImport)
   {
      %targetModule = AssetBrowser.dirHandler.getModuleFromAddress(filePath(%filePath)).ModuleId;
      AssetImportTargetModule.text = %targetModule;
      
      %assetItem.moduleName = %targetModule;
      
      %assetName = %assetItem.assetName;
      
      AssetBrowser.dirHandler.currentAddress = filePath(%filePath);
      
      //skip the refresh delay, we'll force it here
      ImportAssetWindow.doRefresh();
      
      ImportAssetItems.empty();
      
      if(ImportAssetWindow.hasImportIssues)
         return false;
   }
   
   $importedLooseFileAsset = %assetItem.moduleName @ ":" @ %assetItem.assetName;
   
   return true;
}*/

//
function assetImportUpdatePath(%newPath)
{
   AssetBrowser.navigateTo(%newPath);
   AssetImportTargetAddress.text = %newPath;
   AssetImportTargetModule.text = AssetBrowser.dirHandler.getModuleFromAddress(AssetBrowser.dirHandler.currentAddress).ModuleId;
}

//
/*function ImportAssetWindow::processImportAssets(%this, %assetItem)
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
}*/

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
   ImportAssetWindow.importer.processImportingAssets();
   //%this.processImportAssets();
   
   //ImportAssetWindow.hasImportIssues = %this.validateAssets();
   
   ImportAssetWindow.importer.validateImportingAssets();
   
   AssetImportCtrl-->NewAssetsTree.clear();
   AssetImportCtrl-->NewAssetsTree.insertItem(0, "Importing Assets");
   
   for(%i=0; %i < ImportAssetWindow.importer.getAssetItemCount(); %i++)
   {
      %assetItem = ImportAssetWindow.importer.getAssetItem(%i);
      
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
   
   if(%ImportActionSummary !$= "")
      warn(%ImportActionSummary);
   
   AssetImportSummarization.Text = %ImportActionSummary;
   
   //If we have a valid config file set and we've set to auto-import, and we have no
   //issues for importing, then go ahead and run the import immediately, don't
   //bother showing the window.
   //If any of these conditions fail, we'll display the import window so it can be handled
   //by the user
   if(ImportAssetWindow.importConfigsList.count() != 0 
      && EditorSettings.value("Assets/AssetImporDefaultConfig") !$= "" 
      && EditorSettings.value("Assets/AutoImport", false) == true
      && ImportAssetWindow.hasImportIssues == false
      && ImportAssetWindow.allowAutoImport)
   {
      AssetImportCtrl.setHidden(true);
      ImportAssetWindow.visible = false;
      
      //Go ahead and check if we have any issues, and if not, run the import!
      ImportAssetWindow.importer.ImportAssets();
      ImportAssetWindow.importer.resetImportSession(true);
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
      toolsMessageBoxOK( "Warning", "No base import config. Please create an import configuration set to simplify asset importing.");
   }
   
   %this.dirty = false;
   
   AssetBrowser.refresh();
}

function ImportAssetWindow::refreshAssetItem(%this, %assetItem, %parentTreeIdx)
{
    if(!isObject(%assetItem) || %assetItem.skip)
      return;
      
   %assetType = %assetItem.assetType;
   %filePath = %assetItem.filePath;
   %assetName = %assetItem.assetName;
   
   //Once validated, attempt any fixes for issues
   ImportAssetWindow.importer.resolveAssetItemIssues(%assetItem);
   
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
      
   if(%parentTreeIdx $= "")
      %parentTreeIdx = 1;
      
   %assetItem.treeIdx = AssetImportCtrl-->NewAssetsTree.insertItem(%parentTreeIdx, %assetName, %assetItem, "", %iconIdx, %iconIdx+1);

   for(%i=0; %i < ImportAssetWindow.importer.getAssetItemChildCount(%assetItem); %i++)
   {
      %childAssetItem = ImportAssetWindow.importer.getAssetItemChild(%assetItem, %i);
      %this.refreshAssetItem(%childAssetItem, %assetItem.treeIdx);
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
   AssetImportCtrl-->NewAssetsInspector.addField("statusInfo", "Status Info", "string", "", %assetItem.statusInfo, "", %assetItem);
   
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
   
   %this.importer.deleteImportingAsset(ImportAssetActions.assetItem);
   
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
   %fileName = fileName(%filePath);
   
   if(%fileExt $= ".dts" && endsWith(%fileName, ".cached"))
      return "";
      
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
function ImportAssetWindow::ImportAssets(%this)
{
   //get the selected module data
   if(%this.importer.targetModuleId $= "")
   {
      %moduleName = AssetImportTargetModule.getText();
      
      %module = ModuleDatabase.findModule(%moduleName, 1);
      
      if(!isObject(%module))
      {
         toolsMessageBoxOK( "Error!", "No module selected. You must select or create a module for the assets to be added to.");
         return;
      }
      
      Canvas.pushDialog( EditorLoadingGui );
      Canvas.repaint();
   
      %this.importer.targetModuleId = %moduleName;
   }
   
   %this.importer.targetPath = AssetImportTargetAddress.getText();
   
   %this.importer.importAssets();
   
   //force an update of any and all modules so we have an up-to-date asset list
   AssetBrowser.refresh();
   Canvas.popDialog(AssetImportCtrl);
   AssetBrowser.isAssetReImport = false;
   
   %this.importer.resetImportSession(true);
   
   Canvas.popDialog( EditorLoadingGui );
   
   //do the actual importing, now!
   /*%assetCount = ImportAssetItems.count();

   
   
   %this.doImportAssets();
   
   //force an update of any and all modules so we have an up-to-date asset list
   AssetBrowser.refresh();
   Canvas.popDialog(AssetImportCtrl);
   AssetBrowser.isAssetReImport = false;*/
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
