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
   %this.importAssetUnprocessedListArray.empty();
   %this.importAssetFinalListArray.empty();
   
   ImportAssetWindow.assetHeirarchyChanged = false;
   
   //prep the import control
   Canvas.pushDialog(AssetImportCtrl);
   AssetImportCtrl.setHidden(true);

   ImportAssetTree.clear();
   ImportAssetTree.insertItem(0, "Importing Assets");
   AssetBrowser.unprocessedAssetsCount = 0;
}

function AssetBrowser::onDropFile( %this, %filePath )
{
   if(!%this.isVisible())
      return;
      
   %fileExt = fileExt( %filePath );
   //add it to our array!
   if(isImageFormat(%fileExt))
      %this.addImportingAsset("Image", %filePath);
   else if( isShapeFormat(%fileExt))
      %this.addImportingAsset("Model", %filePath);
   else if( isSoundFormat(%fileExt))
      %this.addImportingAsset("Sound", %filePath);
   else if( %fileExt $= ".cs" || %fileExt $= ".cs.dso" )
      %this.addImportingAsset("Script", %filePath);
   else if( %fileExt $= ".gui" || %fileExt $= ".gui.dso" )
      %this.addImportingAsset("GUI", %filePath);
   else if (%fileExt $= ".zip")
      %this.onDropZipFile(%filePath);
      
   //Used to keep tabs on what files we were trying to import, used mainly in the event of
   //adjusting configs and needing to completely reprocess the import
   //ensure we're not doubling-up on files by accident
   if(%this.importingFilesArray.getIndexFromKey(%filePath) == -1)
      %this.importingFilesArray.add(%filePath);
}

function AssetBrowser::onDropZipFile(%this, %filePath)
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
         %this.importAssetListArray.add("Image", %filePath);
      else if( (%fileExt $= ".dae") || (%fileExt $= ".dts"))
         %this.importAssetListArray.add("Model", %filePath);
      else if( (%fileExt $= ".ogg") || (%fileExt $= ".wav") || (%fileExt $= ".mp3"))
         %this.importAssetListArray.add("Sound", %filePath);
      else if( (%fileExt $= ".gui") || (%fileExt $= ".gui.dso"))
         %this.importAssetListArray.add("GUI", %filePath);
      //else if( (%fileExt $= ".cs") || (%fileExt $= ".dso"))
      //   %this.importAssetListArray.add("Script", %filePath);
      else if( (%fileExt $= ".mis"))
         %this.importAssetListArray.add("Level", %filePath);
         
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
   
   %hasIssues = ImportAssetWindow.validateAssets();
   
   //If we have a valid config file set and we've set to auto-import, and we have no
   //issues for importing, then go ahead and run the import immediately, don't
   //bother showing the window.
   //If any of these conditions fail, we'll display the import window so it can be handled
   //by the user
   if(ImportAssetWindow.importConfigsList.count() != 0 && 
      EditorSettings.value("Assets/AssetImporDefaultConfig") !$= "" && 
      EditorSettings.value("Assets/AutoImport", false) == true
      && %hasIssues == false)
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

   // Update object library
   GuiFormManager::SendContentMessage($LBCreateSiderBar, %this, "refreshAll 1");
   
   if(ImportAssetWindow.importConfigsList.count() == 0)
   {
      MessageBoxOK( "Warning", "No base import config. Please create an import configuration set to simplify asset importing.");
   }
}
//
//
//

function AssetBrowser::reloadImportingFiles(%this)
{
   //Effectively, we re-import the files we were trying to originally. We'd only usually do this in the event we change our import config
   %this.onBeginDropFiles();
   
   for(%i=0; %i < %this.importingFilesArray.count(); %i++)
   {
      %this.onDropFile(%this.importingFilesArray.getKey(%i));
   }
    
   %this.onEndDropFiles();  
}

function AssetBrowser::ImportTemplateModules(%this)
{
   //AssetBrowser_ImportModule
   Canvas.pushDialog(AssetBrowser_ImportModuleTemplate);
   AssetBrowser_ImportModuleTemplateWindow.visible = true;   
   
   AssetBrowser_ImportModuleTemplateList.clear();
   
   //ModuleDatabase.scanModules("../../../../../../Templates/Modules/");
   
   %pattern = "../../../../../../Templates/Modules//*//*.module";   
   %file = findFirstFile( %pattern );

   while( %file !$= "" )
   {      
      echo("FOUND A TEMPLATE MODULE! " @ %file);
      %file = findNextFile( %pattern );
   }
   
   /*%moduleCheckbox = new GuiCheckBoxCtrl()
   {
      text = "Testadoo";
      moduleId = "";
   };
   
   AssetBrowser_ImportModuleTemplateList.addRow("0", "Testaroooooo");
   AssetBrowser_ImportModuleTemplateList.addRow("1", "Testadoooooo");*/
}

function AssetBrowser_ImportModuleTemplateList::onSelect(%this, %selectedRowIdx, %text)
{
   echo("Selected row: " @ %selectedRowIdx @ " " @ %text);
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
   };

   //little bit of interception here
   if(%assetItem.assetType $= "Model")
   {
      %fileExt = fileExt(%assetItem.filePath);
      %shapeInfo = new GuiTreeViewCtrl();
      if(%fileExt $= ".dae")
      {
         enumColladaForImport(%assetItem.filePath, %shapeInfo, false);  
      }
      else if(%fileExt $= ".dts")
      {
         %shapeInfo.insertItem(0, "Shape", 1);
         %shapeInfo.insertItem(0, "Animations", 0);
      }
      else
      {
         %success = GetShapeInfo(%assetItem.filePath, %shapeInfo);
      }
      
      %assetItem.shapeInfo = %shapeInfo;
      
      %shapeCount = %assetItem.shapeInfo._meshCount;
      
      %animCount = %assetItem.shapeInfo._animCount;
      
      //If the model has shapes AND animations, then it's a normal shape with embedded animations
      //if it has shapes and no animations it's a regular static mesh
      //if it has no shapes and animations, it's a special case. This means it's a shape animation only file so it gets flagged as special
      if(%shapeCount == 0 && %animCount != 0)
      {
         %assetItem.assetType = "Animation";
      }
      else if(%shapeCount == 0 && %animCount == 0)
      {
         //either it imported wrong or it's a bad file we can't read. Either way, don't try importing it
         error("Error - attempted to import a model file with no shapes or animations! Model in question was: " @ %filePath);
         
         %assetItem.delete();
         return 0;
      }
   }
   
   if(%assetType $= "Material")
   {
      %assetItem.generatedAsset = true;  
   }
   
   if(%parentAssetItem $= "")
   {
      ImportAssetTree.insertObject(1, %assetItem);
      
      //%assetItem.parentDepth = 0;
      //%this.importAssetNewListArray.add(%assetItem);
      //%this.importAssetUnprocessedListArray.add(%assetItem);
   }
   else
   {
      %parentid = ImportAssetTree.findItemByObjectId(%parentAssetItem);
      ImportAssetTree.insertObject(%parentid, %assetItem);
   }
   
   %this.unprocessedAssetsCount++;
   
   ImportAssetWindow.assetValidationList.add(%assetItem);
   
   return %assetItem;
}

function AssetBrowser::importLegacyGame(%this)
{
   
}

function AssetBrowser::importNewAssetFile(%this)
{
   %dlg = new OpenFileDialog()
   {
      Filters        = "Shape Files(*.dae, *.cached.dts)|*.dae;*.cached.dts|Images Files(*.jpg,*.png,*.tga,*.bmp,*.dds)|*.jpg;*.png;*.tga;*.bmp;*.dds|Any Files (*.*)|*.*|";
      DefaultPath    = $Pref::WorldEditor::LastPath;
      DefaultFile    = "";
      ChangePath     = false;
      OverwritePrompt = true;
      forceRelativePath = false;
      //MultipleFiles = true;
   };

   %ret = %dlg.Execute();
   
   if ( %ret )
   {
      $Pref::WorldEditor::LastPath = filePath( %dlg.FileName );
      %fullPath = %dlg.FileName;
      %file = fileBase( %fullPath );
   }   
   
   %dlg.delete();
   
   if ( !%ret )
      return;
      
   AssetBrowser.onBeginDropFiles();
   AssetBrowser.onDropFile(%fullPath);
   AssetBrowser.onEndDropFiles();
}

//
function ImportAssetButton::onClick(%this)
{
   ImportAssetsPopup.showPopup(Canvas);
}
//

//
function ImportAssetWindow::onWake(%this)
{
   //We've woken, meaning we're trying to import assets
   //Lets refresh our list
   if(!ImportAssetWindow.isVisible())
      return;
   
   if(!isObject(AssetImportSettings))
   {
      new Settings(AssetImportSettings) 
      { 
         file = $AssetBrowser::importConfigsFile; 
      };
   }
   AssetImportSettings.read();
   
   %this.reloadImportOptionConfigs();
   
   if(!isObject(%this.assetValidationList))
   {
      %this.assetValidationList = new ArrayObject();
   }
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
      
   ImportAssetConfigList.setSelected(%importConfigIdx);
}

function ImportAssetWindow::setImportOptions(%this, %configName)
{
   //Todo, editor + load from files for preconfigs
   
   //General
   %optionsObj.treatWarningsAsErrors = false;
   %optionsObj.ignoreDuplicateAssets = false;
   
   //Meshes
   %optionsObj.ImportMesh = true;
   %optionsObj.UpAxisOverride = "Z_AXIS";
   %optionsObj.OverrideScale = 1.0;
   %optionsObj.IgnoreNodeScale = false;
   %optionsObj.AdjustCenter = false;
   %optionsObj.AdjustFloor = false;
   %optionsObj.CollapseSubmeshes = false;
   %optionsObj.LODType = "TrailingNumber";
   %optionsObj.TrailingNumber = 2;
   %optionsObj.ImportedNodes = "";
   %optionsObj.IgnoreNodes = "";
   %optionsObj.ImportMeshes = "";
   %optionsObj.IgnoreMeshes = "";
   
   //Materials
   %optionsObj.ImportMaterials = true;
   %optionsObj.CreateComposites = true;
   
   //Animations
   %optionsObj.ImportAnimations = true;
   %optionsObj.SeparateAnimations = true;
   %optionsObj.SeparateAnimationPrefix = "";
   
   //Collision
   %optionsObj.GenerateCollisions = true;
   %optionsObj.GenCollisionType = "CollisionMesh";
   %optionsObj.CollisionMeshPrefix = "Collision";
   %optionsObj.GenerateLOSCollisions = true;
   %optionsObj.GenLOSCollisionType = "CollisionMesh";
   %optionsObj.LOSCollisionMeshPrefix = "LOS";
   
   //Images
   %optionsObj.ImageType = "Diffuse";
   %optionsObj.DiffuseTypeSuffixes = "_ALBEDO,_DIFFUSE,_ALB,_DIF,_COLOR,_COL";
   %optionsObj.NormalTypeSuffixes = "_NORMAL,_NORM";
   %optionsObj.SpecularTypeSuffixes = "_SPECULAR,_SPEC";
   %optionsObj.MetalnessTypeSuffixes = "_METAL,_MET,_METALNESS,_METALLIC";
   %optionsObj.RoughnessTypeSuffixes = "_ROUGH,_ROUGHNESS";
   %optionsObj.SmoothnessTypeSuffixes = "_SMOOTH,_SMOOTHNESS";
   %optionsObj.AOTypeSuffixes = "_AO,_AMBIENT,_AMBIENTOCCLUSION";
   %optionsObj.CompositeTypeSuffixes = "_COMP,_COMPOSITE";
   %optionsObj.TextureFilteringMode = "Bilinear";
   %optionsObj.UseMips = true;
   %optionsObj.IsHDR = false;
   %optionsObj.Scaling = 1.0;
   %optionsObj.Compressed = true;
   
   //Sounds
   %optionsObj.VolumeAdjust = 1.0;
   %optionsObj.PitchAdjust = 1.0;
   %optionsObj.Compressed = false;
}

//
function ImportAssetWindow::processNewImportAssets(%this, %id)
{
   while(%id > 0)
   {
      %assetItem = ImportAssetTree.getItemObject(%id);
      
      if(isObject(%assetItem) && %assetItem.processed == false)
      {
         //%assetConfigObj = ImportAssetWindow.activeImportConfig.clone();
         //%assetConfigObj.assetIndex = %i;

         //sanetize before modifying our asset name(suffix additions, etc)      
         if(%assetItem.assetName !$= %assetItem.cleanAssetName)
            %assetItem.assetName = %assetItem.cleanAssetName;
            
         //%assetConfigObj.assetName = %assetItem.assetName;
         
         if(%assetItem.assetType $= "Model")
         {
            AssetBrowser.prepareImportShapeAsset(%assetItem);
         }
         else if(%assetItem.assetType $= "Animation")
         {
            //if we don't have our own file, that means we're gunna be using our parent shape's file so reference that
            if(!isFile(%assetItem.filePath))
            {
               %assetItem.filePath = %assetItem.parentAssetItem.filePath;
            }
         }
         else if(%assetItem.assetType $= "Material")
         {
            AssetBrowser.prepareImportMaterialAsset(%assetItem);
         } 
         else if(%assetItem.assetType $= "Image")
         {
            AssetBrowser.prepareImportImageAsset(%assetItem);
         }
         
         %assetItem.processed = true;
      }
      
      if(ImportAssetTree.isParentItem(%id))
      {
         %childItem = ImportAssetTree.getChild(%id);
         
         //recurse!
         %this.processNewImportAssets(%childItem); 
      }

      //It's possible we restructured our asset heirarchy(generated assets being parents, etc
      //If that's happened, we need to back out of the current processing and restart to ensure we catch everything
      if(ImportAssetWindow.assetHeirarchyChanged)
         %id = -1;  //breaks the loop
      else
         %id = ImportAssetTree.getNextSibling(%id);
   }
   
   //We have a forced break out of the loop, so lets check if it's because the heirarchy changed.
   //If so, reprocess
   /*if(%id == -1 && ImportAssetWindow.assetHeirarchyChanged)
   {
      ImportAssetWindow.refresh();
   }*/
}

function ImportAssetWindow::findImportingAssetByName(%this, %assetName)
{
   %id = ImportAssetTree.getChild(1);
   
   return %this._findImportingAssetByName(%id, %assetName);
}

function ImportAssetWindow::_findImportingAssetByName(%this, %id, %assetName)
{
   while(%id > 0)
   {
      %assetItem = ImportAssetTree.getItemObject(%id);
      
      if(isObject(%assetItem) && %assetItem.cleanAssetName $= %assetName)
      {
         return %assetItem;
      }
      
      if(ImportAssetTree.isParentItem(%id))
      {
         %childItem = ImportAssetTree.getChild(%id);
         
         //recurse!
         %ret = %this._findImportingAssetByName(%childItem, %assetName);
         if(%ret != 0)
            return %ret;
      }

      %id = ImportAssetTree.getNextSibling(%id);
   }
   
   return 0;
}

function ImportAssetWindow::parseImageSuffixes(%this, %assetItem)
{
   //diffuse
   %suffixCount = getTokenCount(getAssetImportConfigValue("Images/DiffuseTypeSuffixes", ""), ",;");
   for(%sfx = 0; %sfx < %suffixCount; %sfx++)
   {
      %suffixToken = getToken(getAssetImportConfigValue("Images/DiffuseTypeSuffixes", ""), ",;", %sfx);
      if(strIsMatchExpr("*"@%suffixToken, %assetItem.AssetName))
      {
         %assetItem.imageSuffixType = %suffixToken;
         return "diffuse";
      }
   }
   
   //normal
   %suffixCount = getTokenCount(getAssetImportConfigValue("Images/NormalTypeSuffixes", ""), ",;");
   for(%sfx = 0; %sfx < %suffixCount; %sfx++)
   {
      %suffixToken = getToken(getAssetImportConfigValue("Images/NormalTypeSuffixes", ""), ",;", %sfx);
      if(strIsMatchExpr("*"@%suffixToken, %assetItem.AssetName))
      {
         %assetItem.imageSuffixType = %suffixToken;
         return "normal";
      }
   }
   
   //roughness
   %suffixCount = getTokenCount(getAssetImportConfigValue("Images/RoughnessTypeSuffixes", ""), ",;");
   for(%sfx = 0; %sfx < %suffixCount; %sfx++)
   {
      %suffixToken = getToken(getAssetImportConfigValue("Images/RoughnessTypeSuffixes", ""), ",;", %sfx);
      if(strIsMatchExpr("*"@%suffixToken, %assetItem.AssetName))
      {
         %assetItem.imageSuffixType = %suffixToken;
         return "roughness";
      }
   }
   
   //Ambient Occlusion
   %suffixCount = getTokenCount(getAssetImportConfigValue("Images/AOTypeSuffixes", ""), ",;");
   for(%sfx = 0; %sfx < %suffixCount; %sfx++)
   {
      %suffixToken = getToken(getAssetImportConfigValue("Images/AOTypeSuffixes", ""), ",;", %sfx);
      if(strIsMatchExpr("*"@%suffixToken, %assetItem.AssetName))
      {
         %assetItem.imageSuffixType = %suffixToken;
         return "AO";
      }
   }
   
   //metalness
   %suffixCount = getTokenCount(getAssetImportConfigValue("Images/MetalnessTypeSuffixes", ""), ",;");
   for(%sfx = 0; %sfx < %suffixCount; %sfx++)
   {
      %suffixToken = getToken(getAssetImportConfigValue("Images/MetalnessTypeSuffixes", ""), ",;", %sfx);
      if(strIsMatchExpr("*"@%suffixToken, %assetItem.AssetName))
      {
         %assetItem.imageSuffixType = %suffixToken;
         return "metalness";
      }
   }
   
   //composite
   %suffixCount = getTokenCount(getAssetImportConfigValue("Images/CompositeTypeSuffixes", ""), ",;");
   for(%sfx = 0; %sfx < %suffixCount; %sfx++)
   {
      %suffixToken = getToken(getAssetImportConfigValue("Images/CompositeTypeSuffixes", ""), ",;", %sfx);
      if(strIsMatchExpr("*"@%suffixToken, %assetItem.AssetName))
      {
         %assetItem.imageSuffixType = %suffixToken;
         return "composite";
      }
   }
   
   //specular
   /*%suffixCount = getTokenCount(ImportAssetWindow.activeImportConfig.SpecularTypeSuffixes, ",;");
   for(%sfx = 0; %sfx < %suffixCount; %sfx++)
   {
      %suffixToken = getToken(ImportAssetWindow.activeImportConfig.SpecularTypeSuffixes, ",;", %sfx);
      if(strIsMatchExpr("*"@%suffixToken, %assetItem.AssetName))
      {
         %assetItem.imageSuffixType = %suffixToken;
         return "specular";
      }
   }*/
   
   return "";
}

function ImportAssetWindow::parseImagePathSuffixes(%this, %filePath)
{
   //diffuse
   %diffuseSuffixes = getAssetImportConfigValue("Images/DiffuseTypeSuffixes", "");
   %suffixCount = getTokenCount(%diffuseSuffixes, ",;");
   for(%sfx = 0; %sfx < %suffixCount; %sfx++)
   {
      %suffixToken = getToken(%diffuseSuffixes, ",;", %sfx);
      if(strIsMatchExpr("*"@%suffixToken, %filePath))
      {
         return "diffuse";
      }
   }
   
   //normal
   %suffixCount = getTokenCount(ImportAssetWindow.activeImportConfig.NormalTypeSuffixes, ",;");
   for(%sfx = 0; %sfx < %suffixCount; %sfx++)
   {
      %suffixToken = getToken(ImportAssetWindow.activeImportConfig.NormalTypeSuffixes, ",;", %sfx);
      if(strIsMatchExpr("*"@%suffixToken, %filePath))
      {
         return "normal";
      }
   }
   
   //roughness
   %suffixCount = getTokenCount(ImportAssetWindow.activeImportConfig.RoughnessTypeSuffixes, ",;");
   for(%sfx = 0; %sfx < %suffixCount; %sfx++)
   {
      %suffixToken = getToken(ImportAssetWindow.activeImportConfig.RoughnessTypeSuffixes, ",;", %sfx);
      if(strIsMatchExpr("*"@%suffixToken, %filePath))
      {
         return "roughness";
      }
   }
   
   //Ambient Occlusion
   %suffixCount = getTokenCount(ImportAssetWindow.activeImportConfig.AOTypeSuffixes, ",;");
   for(%sfx = 0; %sfx < %suffixCount; %sfx++)
   {
      %suffixToken = getToken(ImportAssetWindow.activeImportConfig.AOTypeSuffixes, ",;", %sfx);
      if(strIsMatchExpr("*"@%suffixToken, %filePath))
      {
         return "AO";
      }
   }
   
   //metalness
   %suffixCount = getTokenCount(ImportAssetWindow.activeImportConfig.MetalnessTypeSuffixes, ",;");
   for(%sfx = 0; %sfx < %suffixCount; %sfx++)
   {
      %suffixToken = getToken(ImportAssetWindow.activeImportConfig.MetalnessTypeSuffixes, ",;", %sfx);
      if(strIsMatchExpr("*"@%suffixToken, %filePath))
      {
         return "metalness";
      }
   }
   
   //composite
   %suffixCount = getTokenCount(ImportAssetWindow.activeImportConfig.CompositeTypeSuffixes, ",;");
   for(%sfx = 0; %sfx < %suffixCount; %sfx++)
   {
      %suffixToken = getToken(ImportAssetWindow.activeImportConfig.CompositeTypeSuffixes, ",;", %sfx);
      if(strIsMatchExpr("*"@%suffixToken, %filePath))
      {
         return "composite";
      }
   }
   
   //specular
   %suffixCount = getTokenCount(ImportAssetWindow.activeImportConfig.SpecularTypeSuffixes, ",;");
   for(%sfx = 0; %sfx < %suffixCount; %sfx++)
   {
      %suffixToken = getToken(ImportAssetWindow.activeImportConfig.SpecularTypeSuffixes, ",;", %sfx);
      if(strIsMatchExpr("*"@%suffixToken, %filePath))
      {
         return "specular";
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
   //Go through and process any newly, unprocessed assets
   %id = ImportAssetTree.getChild(1);
   
   ImportAssetWindow.assetHeirarchyChanged = false;
   AssetBrowser.importAssetFinalListArray.empty();
   
   %this.processNewImportAssets(%id);
   
   %this.indentCount = 0;
   
   %this.validateAssets();
   
   ImportingAssetList.clear();
   
   if(AssetBrowser.importAssetUnprocessedListArray.count() == 0)
   {
      //We've processed them all, prep the assets for actual importing
      //Initial set of assets
      %id = ImportAssetTree.getChild(1);
      
     //recurse!
      %this.refreshChildItem(%id);   
   }
   else
   {
      //Continue processing
      %this.refresh();  
   }
}

function ImportAssetWindow::refreshChildItem(%this, %id)
{
   while (%id > 0)
   {
      %assetItem = ImportAssetTree.getItemObject(%id);
      
      if(!isObject(%assetItem) || %assetItem.skip)
      {
         %id = ImportAssetTree.getNextSibling(%id);
         continue;  
      }
      
      %assetType = %assetItem.assetType;
      %filePath = %assetItem.filePath;
      %assetName = %assetItem.assetName;
      
      //Once validated, attempt any fixes for issues
      %this.resolveIssue(%assetItem);
      
      //Make sure we size correctly
      ImportingAssetList.extent.x = ImportingAssetList.getParent().extent.x - 15;
      
      //create!
      %width = mRound(mRound(ImportingAssetList.extent.x) / 2);
      %height = 20;
      %indent = %this.indentCount * 16;
      %toolTip = "";
      
      %iconPath = "tools/gui/images/iconInformation";
      %configCommand = "ImportAssetOptionsWindow.editImportSettings(" @ %assetItem @ ");";
      
      if(%assetType $= "Model" || %assetType $= "Animation" || %assetType $= "Image" || %assetType $= "Sound")
      {
         if(%assetItem.status $= "Error")
         {
            %iconPath = "tools/gui/images/iconError";
         }
         else if(%assetItem.status $= "Warning")
         {
            %iconPath = "tools/gui/images/iconWarn";
         }
         
         %configCommand = "ImportAssetOptionsWindow.fixIssues(" @ %assetItem @ ");";
            
            if(%assetItem.statusType $= "DuplicateAsset" || %assetItem.statusType $= "DuplicateImportAsset")
               %assetName = %assetItem.assetName @ " <Duplicate Asset>";
      }
      else
      {
         if(%assetItem.status $= "Error")
         {
            %iconPath = "tools/gui/images/iconError";
         }
         else if(%assetItem.status $= "Warning")
         {
            %iconPath = "tools/gui/images/iconWarn";
         }
         
         %configCommand = "";//"ImportAssetOptionsWindow.fixIssues(" @ %assetItem @ ");";
            
            if(%assetItem.statusType $= "DuplicateAsset" || %assetItem.statusType $= "DuplicateImportAsset")
               %assetName = %assetItem.assetName @ " <Duplicate Asset>";
      }
      
      %toolTip = %assetItem.statusInfo;
      
      %inputCellPos = %indent;
      %inputCellWidth = (ImportingAssetList.extent.x * 0.3) - %indent;
      
      %filePathBtnPos = %inputCellPos + %inputCellWidth - %height;
      
      %assetNameCellPos = %inputCellPos + %inputCellWidth;
      %assetNameCellWidth = ImportingAssetList.extent.x * 0.3;
      
      %assetTypeCellPos = %assetNameCellPos + %assetNameCellWidth;
      %assetTypeCellWidth = ImportingAssetList.extent.x * 0.3;
      
      %configBtnPos = %assetTypeCellPos + %assetTypeCellWidth - (%height * 2);
      %configBtnWidth = %height;
      
      %delBtnPos = %assetTypeCellPos + %assetTypeCellWidth - %height;
      %delBtnWidth = %height;
      
      %inputField = %filePath;
      
      //Check if it's a generated type, like materials
      %inputPathProfile = ToolsGuiTextEditProfile;
      %generatedField = false;
      if(%assetItem.generatedAsset)
      {
         %generatedField = true;
         %inputField = "(Generated)";
      }
      else
      {
         //nope, so check that it's a valid file path. If not, flag it as such
         if(%assetItem.status $= "Error")
         {
            if(!isFile(%filePath))
            {
               %inputField = "File not found!";
               %inputPathProfile = ToolsGuiTextEditErrorProfile;
            }
         }
      }
      
      %importEntry = new GuiControl()
      {
         position = "0 0";
         extent = ImportingAssetList.extent.x SPC %height;
         horzSizing = "width";
         vertSizing = "bottom";
         
         new GuiTextEditCtrl()
         {
            Text = %inputField; 
            position = %inputCellPos SPC "0";
            extent = %inputCellWidth SPC %height;
            internalName = "InputPath";
            active = false;
            profile = %inputPathProfile;
            horzSizing = "width";
            vertSizing = "bottom";
         };
         
         new GuiButtonCtrl()
         {
            position = %filePathBtnPos SPC "0";
            extent = %height SPC %height;
            command = "ImportAssetWindow.findMissingFile(" @ %assetItem @ ");";
            text = "...";
            internalName = "InputPathButton";
            tooltip = %toolTip;
            visible = !%generatedField;
            horzSizing = "width";
            vertSizing = "bottom";
         };
         
         new GuiTextEditCtrl()
         {
           Text = %assetName; 
           position = %assetNameCellPos SPC "0";
           extent = %assetNameCellWidth SPC %height;
           internalName = "AssetName";
           horzSizing = "width";
            vertSizing = "bottom";
         };
         
         new GuiTextEditCtrl()
         {
           Text = %assetType; 
           position = %assetTypeCellPos SPC "0";
           extent = %assetTypeCellWidth SPC %height;
           active = false;
           internalName = "AssetType";
           horzSizing = "width";
            vertSizing = "bottom";
         };
         
         new GuiBitmapButtonCtrl()
         {
            position = %configBtnPos SPC "0";
            extent = %height SPC %height;
            command = "ImportAssetWindow.importResolution(" @ %assetItem @ ");";
            bitmap = %iconPath;
            tooltip = %toolTip;
            horzSizing = "width";
            vertSizing = "bottom";
         };
         new GuiBitmapButtonCtrl()
         {
            position = %delBtnPos SPC "0";
            extent = %height SPC %height;
            command = "ImportAssetWindow.deleteImportingAsset(" @ %assetItem @ ");";
            bitmap = "tools/gui/images/iconDelete";
            horzSizing = "width";
            vertSizing = "bottom";
         };
      };
      
      ImportingAssetList.add(%importEntry);
      AssetBrowser.importAssetFinalListArray.add(%assetItem);
      
      if(ImportAssetTree.isParentItem(%id))
      {
         %this.indentCount++;  
         
         %childItem = ImportAssetTree.getChild(%id);
         
         //recurse!
         %this.refreshChildItem(%childItem); 
      }

      %id = ImportAssetTree.getNextSibling(%id);
   }
   
   %this.indentCount--;
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

//
function ImportAssetWindow::validateAssets(%this)
{
   //Clear any status
   %this.resetAssetsValidationStatus();
   
   ImportAssetWindow.importIssues = false;
   
   %id = ImportAssetTree.getChild(1);
   %hasIssues = %this.validateAsset(%id);
   
   if(ImportAssetWindow.importIssues == false)
      return false;
   else
      return true;
}

function ImportAssetWindow::validateAsset(%this, %id)
{
   
   %moduleName = ImportAssetModuleList.getText();
   
   while (%id > 0)
   {
      %assetItem = ImportAssetTree.getItemObject(%id);
      
      if(!isObject(%assetItem) || %assetItem.skip)
      {
         %id = ImportAssetTree.getNextSibling(%id);
         continue;  
      }
      
      //First, check the obvious: name collisions. We should have no asset that shares a similar name.
      //If we do, prompt for it be renamed first before continuing
      %hasCollision = %this.checkAssetsForCollision(%assetItem);
      
      //Ran into a problem, so end checks on this one and move on
      if(%hasCollision)
      {
         %id = ImportAssetTree.getNextSibling(%id);
         continue;  
      }
      
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
      }
      
      if(%assetItem.status $= "Warning")
      {
         if(getAssetImportConfigValue("General/WarningsAsErrors", "0") == 1)
         {
            %assetItem.status = "error";
         }
      }
      
      if(%assetItem.status $= "error")
         ImportAssetWindow.importIssues = true;
      
      if(ImportAssetTree.isParentItem(%id))
      {
         %childItem = ImportAssetTree.getChild(%id);
         
         //recurse!
         %this.validateAsset(%childItem); 
      }

      %id = ImportAssetTree.getNextSibling(%id);
   }
}


function ImportAssetWindow::resetAssetsValidationStatus(%this)
{
   %id = ImportAssetTree.getChild(1);
   
   %this.resetAssetValidationStatus(%id);
}

function ImportAssetWindow::resetAssetValidationStatus(%this, %id)
{
   %moduleName = ImportAssetModuleList.getText();
  
   %id = ImportAssetTree.getChild(%id);
   while (%id > 0)
   {
      %assetItem = ImportAssetTree.getItemObject(%id);
      
      if(!isObject(%assetItem) || %assetItem.skip)
      {
         %id = ImportAssetTree.getNextSibling(%id);
         continue;  
      }
      
      %assetItem.status = "";
      %assetItem.statusType = "";
      %assetItem.statusInfo = "";

      if(ImportAssetTree.isParentItem(%id))
      {
         %childItem = ImportAssetTree.getChild(%id);
         
         //recurse!
         %this.resetAssetValidationStatus(%childItem); 
      }

      %id = ImportAssetTree.getNextSibling(%id);
   }
}

function ImportAssetWindow::checkAssetsForCollision(%this, %assetItem)
{
   %id = ImportAssetTree.getChild(1);
   
   return %this.checkAssetForCollision(%assetItem, %id);
}

function ImportAssetWindow::checkAssetForCollision(%this, %assetItem, %id)
{
   %moduleName = ImportAssetModuleList.getText();
  
   %id = ImportAssetTree.getChild(%id);
   while (%id > 0)
   {
      %assetItemB = ImportAssetTree.getItemObject(%id);
      
      if(!isObject(%assetItemB) || %assetItemB.skip)
      {
         %id = ImportAssetTree.getNextSibling(%id);
         continue;  
      }
   
      if( (%assetItem.assetName $= %assetItemB.assetName) && (%assetItem.getId() != %assetItemB.getId()) )
      {
         //yup, a collision, prompt for the change and bail out
         %assetItem.status = "Warning";
         %assetItem.statusType = "DuplicateImportAsset";
         %assetItem.statusInfo = "Duplicate asset names found with importing assets!\nAsset \"" @ 
            %assetItemB.assetName @ "\" of type \"" @ %assetItemB.assetType @ "\" and \"" @
            %assetItem.assetName @ "\" of type \"" @ %assetItem.assetType @ "\" have matching names.\nPlease rename one of them and try again!";

         return true;
      }
      
      if(ImportAssetTree.isParentItem(%id))
      {
         %childItem = ImportAssetTree.getChild(%id);
         
         //recurse!
         %this.checkAssetForCollision(%assetItem, %childItem); 
      }

      %id = ImportAssetTree.getNextSibling(%id);
   }
   
   return false;
}

//
function ImportAssetWindow::deleteImportingAsset(%this, %assetItem)
{
   %item = ImportAssetTree.findItemByObjectId(%assetItem);
   
   ImportAssetTree.removeAllChildren(%item);
   ImportAssetTree.removeItem(%item);

   schedule(10, 0, "refreshImportAssetWindow");
   //ImportAssetWindow.refresh();
   ImportAssetOptionsWindow.setVisible(0);
}

//
function ImportAssetWindow::ImportAssets(%this)
{
   //do the actual importing, now!
   %assetCount = AssetBrowser.importAssetFinalListArray.count();
   
   //get the selected module data
   %moduleName = ImportAssetModuleList.getText();
   
   %module = ModuleDatabase.findModule(%moduleName, 1);
   
   if(!isObject(%module))
   {
      MessageBoxOK( "Error!", "No module selected. You must select or create a module for the assets to be added to.");
      return;
   }
   
   %id = ImportAssetTree.getChild(1);
   
   %this.doImportAssets(%id);
   
   //force an update of any and all modules so we have an up-to-date asset list
   AssetBrowser.loadFilters();
   AssetBrowser.refreshPreviews();
   Canvas.popDialog(AssetImportCtrl);
   AssetBrowser.isAssetReImport = false;
}

function ImportAssetWindow::doImportAssets(%this, %id)
{
   while(%id > 0)
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
      
      if(%assetType $= "Image")
      {
         AssetBrowser.importImageAsset(%assetItem);
      }
      else if(%assetType $= "Model")
      {
         AssetBrowser.importShapeAsset(%assetItem);
      }
      else if(%assetType $= "Animation")
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
      else if(%assetType $= "Sound")
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
      else if(%assetType $= "Material")
      {
         AssetBrowser.importMaterialAsset(%assetItem);
      }
      else if(%assetType $= "Script")
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
      else if(%assetType $= "GUI")
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
}

function ImportAssetWindow::Close(%this)
{
   //Some cleanup
   AssetBrowser.importingFilesArray.empty();
   
   Canvas.popDialog();  
}

function ImportAssetWindow::resolveIssue(%this, %assetItem)
{
   //Ok, we actually have a warning, so lets resolve
   if(%assetItem.statusType $= "DuplicateImportAsset" || %assetItem.statusType $= "DuplicateAsset")
   {
      %resolutionAction = getAssetImportConfigValue("General/DuplicatAutoResolution", "AutoPrune");
      
      if(%resolutionAction $= "AutoPrune")
      {
         %this.deleteImportingAsset(%assetItem);
      }
      else if(%resolutionAction $= "AutoRename")
      {
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
   if(%assetItem.assetType $= "Model")
      %filters = "Shape Files(*.dae, *.cached.dts)|*.dae;*.cached.dts";
   else if(%assetItem.assetType $= "Image")
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
   
   if(%assetItem.assetType $= "Image")
   {
      //See if we have anything important to update for our material parent(if we have one)
      %treeItem = ImportAssetTree.findItemByObjectId(%assetItem);
      %parentItem = ImportAssetTree.getParentItem(%treeItem);
      
      if(%parentItem != 0)
      {
         %parentAssetItem = ImportAssetTree.getItemObject(%parentItem);
         if(%parentAssetItem.assetType $= "Material")
         {
            AssetBrowser.prepareImportMaterialAsset(%parentAssetItem);              
         }
      }
   }
   
   ImportAssetWindow.refresh();
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
