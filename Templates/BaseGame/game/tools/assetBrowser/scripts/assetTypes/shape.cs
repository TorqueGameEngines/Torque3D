function AssetBrowser::createShapeAsset(%this)
{
   %moduleName = AssetBrowser.newAssetSettings.moduleName;
   %modulePath = "data/" @ %moduleName;
      
   %assetName = AssetBrowser.newAssetSettings.assetName;
   
   %assetPath = AssetBrowser.dirHandler.currentAddress @ "/";
   
   %tamlpath = %assetPath @ %assetName @ ".asset.taml";
   %shapeFilePath = %assetPath @ %assetName @ ".dae";
   
   %asset = new ShapeAsset()
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
	%smItem = AssetBrowserFilterTree.findChildItemByName(%treeItemId, "ShapeAsset");
	
	AssetBrowserFilterTree.onSelect(%smItem);
	
	return %tamlpath;
}

function AssetBrowser::editShapeAsset(%this, %assetDef)
{
   %this.hideDialog();
   ShapeEditorPlugin.openShapeAsset(%assetDef);    
}

function AssetBrowser::deleteShapeAsset(%this, %assetDef)
{
   
}

function AssetBrowser::prepareImportShapeAsset(%this, %assetItem)
{
   ImportActivityLog.add("Preparing Shape for Import: " @ %assetItem.assetName);
   
   %fileExt = fileExt(%assetItem.filePath);
   
   if(!isObject(%assetItem.shapeInfo))
   {
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
         GetShapeInfo(%assetItem.filePath, %shapeInfo, false);
      }
      
      %assetItem.shapeInfo = %shapeInfo;
   }

   %shapeCount = %assetItem.shapeInfo._meshCount;
   %shapeItem = %assetItem.shapeInfo.findItemByName("Meshes");
   
   //%shapeId = ImportAssetTree.findItemByObjectId(%assetItem);
   
   if(getAssetImportConfigValue("Meshes/ImportMesh", "1") == 1 && %shapeCount > 0)
   {
   }
   
   %animCount = %assetItem.shapeInfo._animCount;
   %animItem = %assetItem.shapeInfo.findItemByName("Animations");
   
   if(getAssetImportConfigValue("Animations/ImportAnimations", "1") == 1 && %animCount > 0)
   {
   }

   %matCount = %assetItem.shapeInfo._materialCount;
   %matItem = %assetItem.shapeInfo.findItemByName("Materials");
   
   ImportActivityLog.add("   Shape Info: Mesh Count: " @ %shapeCount @ " | Material Count: " @ %matCount @ " | Anim Count: " @ %animCount);
   
   if(getAssetImportConfigValue("Materials/ImportMaterials", "1") == 1 && %matCount > 0)
   {
      %materialItem = %assetItem.shapeInfo.getChild(%matItem);
      processShapeMaterialInfo(%assetItem, %materialItem);
      
      %materialItem = %assetItem.shapeInfo.getNextSibling(%materialItem);
      while(%materialItem != 0)
      {
         processShapeMaterialInfo(%assetItem, %materialItem);
            
         %materialItem = %assetItem.shapeInfo.getNextSibling(%materialItem);
      }
   }
}

function AssetBrowser::importShapeAsset(%this, %assetItem)
{
   %moduleName = AssetImportTargetModule.getText();
   
   %assetType = %assetItem.AssetType;
   %filePath = %assetItem.filePath;
   %assetName = %assetItem.assetName;
   %assetImportSuccessful = false;
   %assetId = %moduleName@":"@%assetName;
   
   %assetPath = AssetBrowser.dirHandler.currentAddress @ "/";
   %assetFullPath = %assetPath @ fileName(%filePath);
   
   %newAsset = new ShapeAsset()
   {
      assetName = %assetName;
      versionId = 1;
      fileName = fileName(%filePath);
      originalFilePath = %filePath;
      isNewShape = true;
   };
   
   //check dependencies
   %dependencySlotId = 0;
   for(%i=0; %i < %assetItem.childAssetItems.count(); %i++)
   {
      %childAssetItem = %assetItem.childAssetItems.getKey(%i);
      
      if(!isObject(%childAssetItem) || %childAssetItem.skip || %childAssetItem.processed == false)
         continue;

      %depAssetType = %childAssetItem.assetType;
      if(%childAssetItem.assetType $= "MaterialAsset")
      {
         %matSet = "%newAsset.materialSlot"@%dependencySlotId@"=\"@Asset="@%moduleName@":"@%childAssetItem.assetName@"\";";
         eval(%matSet);
         %dependencySlotId++;
      }
      else if(%depAssetType $= "AnimationAsset")
      {
         %matSet = "%newAsset.animationSequence"@%dependencySlotId@"=\"@Asset="@%moduleName@":"@%childAssetItem.assetName@"\";";
         eval(%matSet);
         %dependencySlotId++;
      }
   }
   
   %assetImportSuccessful = TAMLWrite(%newAsset, %assetPath @ %assetName @ ".asset.taml"); 
   
   //and copy the file into the relevent directory
   if(filePath(%filePath) !$= filePath(%assetFullPath))
   {
      %doOverwrite = !AssetBrowser.isAssetReImport;
      if(!pathCopy(%filePath, %assetFullPath, %doOverwrite))
      {
         error("Unable to import asset: " @ %filePath);
      }
   }
   
   %constructor = ShapeEditor.findConstructor( %assetFullPath );
   
   if(!isObject(%constructor))
      %constructor = ShapeEditor.createConstructor(%assetFullPath);
   
   //We'll update any relevent bits to the ShapeConstructor here
   $TSShapeConstructor::neverImportMat = "";
   
   if(getAssetImportConfigValue("Materials/IgnoreMaterials", "") !$= "")
   {
      %ignoreMaterialList = getAssetImportConfigValue("Materials/IgnoreMaterials", "");
      %ignoredMatNamesCount = getTokenCount(%ignoreMaterialList, ",;");
      for(%i=0; %i < %ignoredMatNamesCount; %i++)
      {
         if(%i==0)
            $TSShapeConstructor::neverImportMat = getToken(%ignoreMaterialList, ",;", %i);
         else
            $TSShapeConstructor::neverImportMat = $TSShapeConstructor::neverImportMat TAB getToken(%ignoreMaterialList, ",;", %i);
      }
   } 
   
   if(getAssetImportConfigValue("Materials/DoUpAxisOverride", "") $= "1")
      %constructor.upAxis = getAssetImportConfigValue("Meshes/UpAxisOverride", "Z_AXIS");
      
   if(getAssetImportConfigValue("Meshes/DoScaleOverride", "0") $= "1")
      %constructor.unit = getAssetImportConfigValue("Meshes/ScaleOverride", "1");
   else
      %constructor.unit = -1;

   %constructor.lodType = getAssetImportConfigValue("Meshes/LODType", "0");
   //%constructor.singleDetailSize = getAssetImportConfigValue("Meshes/convertLeftHanded", "0");
   %constructor.alwaysImport = getAssetImportConfigValue("Meshes/ImportedNodes", "");
   %constructor.neverImport = getAssetImportConfigValue("Meshes/IgnoreNodes", "");
   %constructor.alwaysImportMesh = getAssetImportConfigValue("Meshes/ImportMeshes", "");
   %constructor.neverImportMesh = getAssetImportConfigValue("Meshes/IgnoreMeshes", "");   
   %constructor.ignoreNodeScale = getAssetImportConfigValue("Meshes/IgnoreNodeScale", "0"); 
   %constructor.adjustCenter = getAssetImportConfigValue("Meshes/AdjustCenter", "0");  
   %constructor.adjustFloor = getAssetImportConfigValue("Meshes/AdjustFloor", "0");  
   
   %constructor.convertLeftHanded = getAssetImportConfigValue("Meshes/convertLeftHanded", "0");
   %constructor.calcTangentSpace = getAssetImportConfigValue("Meshes/calcTangentSpace", "0");
   %constructor.genUVCoords = getAssetImportConfigValue("Meshes/genUVCoords", "0");
   %constructor.flipUVCoords = getAssetImportConfigValue("Meshes/flipUVCoords", "0");
   %constructor.findInstances = getAssetImportConfigValue("Meshes/findInstances", "0");
   %constructor.limitBoneWeights = getAssetImportConfigValue("Meshes/limitBoneWeights", "0");
   %constructor.joinIdenticalVerts = getAssetImportConfigValue("Meshes/joinIdenticalVerts", "0");
   %constructor.reverseWindingOrder = getAssetImportConfigValue("Meshes/reverseWindingOrder", "0");
   %constructor.invertNormals = getAssetImportConfigValue("Meshes/invertNormals", "0");   
   %constructor.removeRedundantMats = getAssetImportConfigValue("Meshes/removeRedundantMats", "0");
   %constructor.animTiming = getAssetImportConfigValue("Animations/animTiming", "Seconds");
   %constructor.animFPS = getAssetImportConfigValue("Animations/animFPS", "2");
   
   %constructor.neverImportMat = $TSShapeConstructor::neverImportMat;
   ShapeEditor.saveConstructor( %constructor );
   
   //now, force-load the file if it's collada
   /*%fileExt = fileExt(%assetFullPath);
   if(isSupportedFormat(getSubStr(%fileExt,1)))
   {
      %tempShape = new TSStatic()
      {
         shapeName = %assetFullPath;
      };
      
      %tempShape.delete();
   }*/
   
   %moduleDef = ModuleDatabase.findModule(%moduleName,1);
         
   if(!AssetBrowser.isAssetReImport)
      AssetDatabase.addDeclaredAsset(%moduleDef, %assetPath @ %assetName @ ".asset.taml");
   else
      AssetDatabase.refreshAsset(%assetId);
}

function AssetBrowser::buildShapeAssetPreview(%this, %assetDef, %previewData)
{
   %previewData.assetName = %assetDef.assetName;
   %previewData.assetPath = %assetDef.fileName;

   %previewData.previewImage = "tools/assetBrowser/art/genericAssetIcon";//%assetDef.fileName;
   
   %previewData.assetFriendlyName = %assetDef.assetName;
   %previewData.assetDesc = %assetDef.description;
   %previewData.tooltip = "Asset Name: " @ %assetDef.assetName @ "\n" @ 
                           "Asset Type: Shape Asset\n" @ 
                           "Asset Definition ID: " @  %assetDef @ "\n" @ 
                           "Shape File path: " @ %assetDef.getShapeFile();
                           
   if(%this.selectMode)
      %previewData.doubleClickCommand = "AssetBrowser.selectAsset( AssetBrowser.selectedAsset );";
   else
      %previewData.doubleClickCommand = "AssetBrowser.editAsset( "@%assetDef@" );";
}

function AssetBrowser::onShapeAssetEditorDropped(%this, %assetDef, %position)
{
   //echo("DROPPED A SHAPE ON THE EDITOR WINDOW!"); 

   %targetPosition = EWorldEditor.unproject(%position SPC 1000);
   %camPos = LocalClientConnection.camera.getPosition();
   %rayResult = containerRayCast(%camPos, %targetPosition, -1);
   
   %pos = EWCreatorWindow.getCreateObjectPosition();

   if(%rayResult != 0)
   {
      %pos = getWords(%rayResult, 1, 3);
   }
   else
   {
      %pos = "0 0 0";  
   }
   
   %assetId = %assetDef.getAssetId();
   
   %newStatic = new TSStatic()
   {
      position = %pos;
      shapeAsset = %assetId;
   };
   
   getScene(0).add(%newStatic);
   
   EWorldEditor.clearSelection();
   EWorldEditor.selectObject(%newStatic);
      
   EWorldEditor.isDirty = true;
   
}

function GuiInspectorTypeShapeAssetPtr::onControlDropped( %this, %payload, %position )
{
   Canvas.popDialog(EditorDragAndDropLayer);
   
   // Make sure this is a color swatch drag operation.
   if( !%payload.parentGroup.isInNamespaceHierarchy( "AssetPreviewControlType_AssetDrop" ) )
      return;

   %assetType = %payload.assetType;
   
   if(%assetType $= "ShapeAsset")
   {
      //echo("DROPPED A SHAPE ON A SHAPE ASSET COMPONENT FIELD!");  
      
      %module = %payload.moduleName;
      %asset = %payload.assetName;
      
      %targetComponent = %this.targetObject;
      %targetComponent.shapeAsset = %module @ ":" @ %asset;
      
      //Inspector.refresh();
   }
   
   EWorldEditor.isDirty = true;
}

function processShapeMaterialInfo(%assetItem, %materialItem)
{
   %matName = %assetItem.shapeInfo.getItemText(%materialItem);
   
   %filePath = %assetItem.shapeInfo.getItemValue(%materialItem);
   if(%filePath !$= "")
   {
      if(!isFile(%filePath))
      {
         //could be a stale path reference, such as if it was downloaded elsewhere. Trim to just the filename and see
         //if we can find it there
         %shapePathBase = filePath(%assetItem.filePath);
         
         %filename = fileName(%filePath);
         
         %suffixPos = strpos(strlwr(%filename), " (not found)", 0);
         %filename = getSubStr(%filename, 0, %suffixPos);
         
         %imageFileName = %shapePathBase @ "/" @ %filename;
         if(isFile(%imageFileName))
            %filePath = %imageFileName;
      }
   
      %matAssetItem = AssetBrowser.addImportingAsset("MaterialAsset", "", %assetItem, %matName);
      AssetBrowser.addImportingAsset("ImageAsset", %filePath, %matAssetItem);
   }
   else
   {
      //check to see if it's actually just a flat color
      if(getWordCount(%filePath) == 4 && getWord(%filePath, 0) $= "Color:")
      {
         AssetBrowser.addImportingAsset("MaterialAsset", %matName, %assetItem);
      }
      else
      {
         //we need to try and find our material, since the shapeInfo wasn't able to find it automatically
         %filePath = findImageFile(filePath(%assetItem.filePath), %matName);
         if(%filePath !$= "" && isFile(%filePath))
            AssetBrowser.addImportingAsset("MaterialAsset", %filePath, %assetItem);
         else
            AssetBrowser.addImportingAsset("MaterialAsset", filePath(%assetItem.filePath) @ "/" @ %matName, %assetItem);
      }
   }  
}