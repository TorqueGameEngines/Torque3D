function AssetBrowser::createMaterialAsset(%this)
{
   %assetName = AssetBrowser.newAssetSettings.assetName;
   
   %moduleName = AssetBrowser.newAssetSettings.moduleName;
   %modulePath = "data/" @ %moduleName;
   
   %assetPath = AssetBrowser.dirHandler.currentAddress @ "/";   
   
   %tamlpath = %assetPath @ %assetName @ ".asset.taml";
   %sgfPath = %assetPath @ %assetName @ ".sgf";
   
   %asset = new MaterialAsset()
   {
      AssetName = %assetName;
      versionId = 1;
      shaderData = "";
      shaderGraph = %sgfPath;
   };
   
   TamlWrite(%asset, %tamlpath);
   
   %moduleDef = ModuleDatabase.findModule(%moduleName, 1);
	AssetDatabase.addDeclaredAsset(%moduleDef, %tamlpath);

	AssetBrowser.loadFilters();
	
	%treeItemId = AssetBrowserFilterTree.findItemByName(%moduleName);
	%smItem = AssetBrowserFilterTree.findChildItemByName(%treeItemId, "Materials");
	
	AssetBrowserFilterTree.onSelect(%smItem);
   
	return %tamlpath;
}

function AssetBrowser::editMaterialAsset(%this, %assetDef)
{
   %assetDef.materialDefinitionName.reload();
   
   EditorGui.setEditor(MaterialEditorPlugin);
   
   MaterialEditorGui.currentMaterial = %assetDef.materialDefinitionName;
   MaterialEditorGui.setActiveMaterial( %assetDef.materialDefinitionName );
   
   AssetBrowser.hideDialog();
}

function AssetBrowser::prepareImportMaterialAsset(%this, %assetItem)
{
   //Iterate over to find appropriate images for
         
   //Fetch just the fileBase name
   %fileDir = filePath(%assetItem.filePath);
   %fileName = fileBase(%assetItem.filePath);
   %fileExt = fileExt(%assetItem.filePath);
   
   //Check if we need to filter this material out or not
   if(getAssetImportConfigValue("Materials/IgnoreMaterials", "") !$= "")
   {
      %ignoredMatNamesCount = getTokenCount(getAssetImportConfigValue("Materials/IgnoreMaterials", ""), ",;");
      for(%i=0; %i < %ignoredMatNamesCount; %i++)
      {
        %ignoreName = getToken(getAssetImportConfigValue("Materials/IgnoreMaterials", ""), ",;", %i);
        
        if(strIsMatchExpr(%ignoreName, %fileName))
        {
            //We fit the bill, ignore this material and skip it
            %assetItem.skip = true;
            return;  
        }
      }
   }
   
   if(getAssetImportConfigValue("Materials/PopulateMaterialMaps", "1") == 1)
   {
      %materialItemId = ImportAssetTree.findItemByObjectId(%assetItem);
      
      if(%assetItem.diffuseImageAsset $= "")
      {
         %diffuseTypeSuffixes = getAssetImportConfigValue("Images/DiffuseTypeSuffixes", "");
         
         %targetFilePath = %this.findMaterialMapFileWSuffix(%fileDir, %fileName, %fileExt, %diffuseTypeSuffixes);
         
         if(%targetFilePath !$= "")
         {
            %diffuseAsset = AssetBrowser.addImportingAsset("Image", %targetFilePath, %assetItem);
            %assetItem.diffuseImageAsset = %diffuseAsset;
         }
         else if(getAssetImportConfigValue("Materials/AlwaysPresentImageMaps", "0") == 1)
         {
            //In the event we don't have this image asset, but we DO wish to always display the field(affording when names don't aline with
            //the material name), then we go ahead and create a blank entry
            %suff = getTokenCount(%diffuseTypeSuffixes, ",;") == 0 ? "_albedo" : getToken(%diffuseTypeSuffixes, ",;", 0);
            %diffuseAsset = AssetBrowser.addImportingAsset("Image", %assetItem.AssetName @ %suff, %assetItem);
            %assetItem.diffuseImageAsset = %diffuseAsset;
         }
      }
      
      //Now, iterate over our comma-delimited suffixes to see if we have any matches. We'll use the first match in each case, if any.
      if(%assetItem.normalImageAsset $= "")
      {
         %normalTypeSuffixes = getAssetImportConfigValue("Images/NormalTypeSuffixes", "");
         
         //First, normal map
         %targetFilePath = %this.findMaterialMapFileWSuffix(%fileDir, %fileName, %fileExt, %normalTypeSuffixes);
         
         if(%targetFilePath !$= "")
         {
            %normalAsset = AssetBrowser.addImportingAsset("Image", %targetFilePath, %assetItem);
            %assetItem.normalImageAsset = %normalAsset;
         }
         else if(getAssetImportConfigValue("Materials/AlwaysPresentImageMaps", "0") == 1)
         {
            //In the event we don't have this image asset, but we DO wish to always display the field(affording when names don't aline with
            //the material name), then we go ahead and create a blank entry
            %suff = getTokenCount(%normalTypeSuffixes, ",;") == 0 ? "_normal" : getToken(%normalTypeSuffixes, ",;", 0);
            %normalAsset = AssetBrowser.addImportingAsset("Image", %assetItem.AssetName @ %suff, %assetItem);
            %assetItem.normalImageAsset = %normalAsset;
         }
      }
      
      if(%assetItem.metalImageAsset $= "")
      {
         %metalnessTypeSuffixes = getAssetImportConfigValue("Images/MetalnessTypeSuffixes", "");
         
         %targetFilePath = %this.findMaterialMapFileWSuffix(%fileDir, %fileName, %fileExt, %metalnessTypeSuffixes);
         
         if(%targetFilePath !$= "")
         {
            %metalAsset = AssetBrowser.addImportingAsset("Image", %targetFilePath, %assetItem);
            %assetItem.metalImageAsset = %metalAsset;
         }
         else if(getAssetImportConfigValue("Materials/AlwaysPresentImageMaps", "0") == 1)
         {
            //In the event we don't have this image asset, but we DO wish to always display the field(affording when names don't aline with
            //the material name), then we go ahead and create a blank entry
            %suff = getTokenCount(%metalnessTypeSuffixes, ",;") == 0 ? "_metalness" : getToken(%metalnessTypeSuffixes, ",;", 0);
            %metalAsset = AssetBrowser.addImportingAsset("Image", %assetItem.AssetName @ %suff, %assetItem);
            %assetItem.metalImageAsset = %metalAsset;
         }
      }
      
      if(%assetItem.roughnessImageAsset $= "")
      {
         %roughnessTypeSuffixes = getAssetImportConfigValue("Images/RoughnessTypeSuffixes", "");
         
         %targetFilePath = %this.findMaterialMapFileWSuffix(%fileDir, %fileName, %fileExt, %roughnessTypeSuffixes);
         
         if(%targetFilePath !$= "")
         {
            %roughnessAsset = AssetBrowser.addImportingAsset("Image", %targetFilePath, %assetItem);
            %assetItem.roughnessImageAsset = %roughnessAsset;
         }
         else if(getAssetImportConfigValue("Materials/AlwaysPresentImageMaps", "0") == 1)
         {
            //In the event we don't have this image asset, but we DO wish to always display the field(affording when names don't aline with
            //the material name), then we go ahead and create a blank entry
            %suff = getTokenCount(%roughnessTypeSuffixes, ",;") == 0 ? "_roughness" : getToken(%roughnessTypeSuffixes, ",;", 0);
            %roughnessAsset = AssetBrowser.addImportingAsset("Image", %assetItem.AssetName @ %suff, %assetItem);
            %assetItem.roughnessImageAsset = %roughnessAsset;
         }
      }
      
      if(%assetItem.smoothnessImageAsset $= "")
      {
         %smoothnessTypeSuffixes = getAssetImportConfigValue("Images/SmoothnessTypeSuffixes", "");
         
         %targetFilePath = %this.findMaterialMapFileWSuffix(%fileDir, %fileName, %fileExt, %smoothnessTypeSuffixes);
         
         if(%targetFilePath !$= "")
         {
            %smoothnessAsset = AssetBrowser.addImportingAsset("Image", %targetFilePath, %assetItem);
            %assetItem.SmoothnessImageAsset = %smoothnessAsset;
         }
         else if(getAssetImportConfigValue("Materials/AlwaysPresentImageMaps", "0") == 1)
         {
            //In the event we don't have this image asset, but we DO wish to always display the field(affording when names don't aline with
            //the material name), then we go ahead and create a blank entry
            %suff = getTokenCount(%smoothnessTypeSuffixes, ",;") == 0 ? "_smoothness" : getToken(%smoothnessTypeSuffixes, ",;", 0);
            %smoothnessAsset = AssetBrowser.addImportingAsset("Image", %assetItem.AssetName @ %suff, %assetItem);
            %assetItem.SmoothnessImageAsset = %smoothnessAsset;
         }
      }
      
      if(%assetItem.AOImageAsset $= "")
      {
         %aoTypeSuffixes = getAssetImportConfigValue("Images/AOTypeSuffixes", "");
         
         %targetFilePath = %this.findMaterialMapFileWSuffix(%fileDir, %fileName, %fileExt, %aoTypeSuffixes);
         
         if(%targetFilePath !$= "")
         {
            %AOAsset = AssetBrowser.addImportingAsset("Image", %targetFilePath, %assetItem);
            %assetItem.AOImageAsset = %AOAsset;
         }
         else if(getAssetImportConfigValue("Materials/AlwaysPresentImageMaps", "0") == 1)
         {
            //In the event we don't have this image asset, but we DO wish to always display the field(affording when names don't aline with
            //the material name), then we go ahead and create a blank entry
            %suff = getTokenCount(%aoTypeSuffixes, ",;") == 0 ? "_AO" : getToken(%aoTypeSuffixes, ",;", 0);
            %AOAsset = AssetBrowser.addImportingAsset("Image", %assetItem.AssetName @ %suff, %assetItem);
            %assetItem.AOImageAsset = %AOAsset;
         }
      }
      
      if(%assetItem.compositeImageAsset $= "")
      {
         %compositeTypeSuffixes = getAssetImportConfigValue("Images/CompositeTypeSuffixes", "");
         
         %targetFilePath = %this.findMaterialMapFileWSuffix(%fileDir, %fileName, %fileExt, %compositeTypeSuffixes);
         
         if(%targetFilePath !$= "")
         {
            %compositeAsset = AssetBrowser.addImportingAsset("Image", %targetFilePath, %assetItem);
            %assetItem.compositeImageAsset = %compositeAsset;
         }
         else if(getAssetImportConfigValue("Materials/AlwaysPresentImageMaps", "0") == 1)
         {
            //In the event we don't have this image asset, but we DO wish to always display the field(affording when names don't aline with
            //the material name), then we go ahead and create a blank entry
            %suff = getTokenCount(%compositeTypeSuffixes, ",;") == 0 ? "_composite" : getToken(%compositeTypeSuffixes, ",;", 0);
            %compositeAsset = AssetBrowser.addImportingAsset("Image", %assetItem.AssetName @ %suff, %assetItem);
            %assetItem.compositeImageAsset = %compositeAsset;
         }
      }
      
      //If after the above we didn't find any, check to see if we should be generating one
      if(%assetItem.compositeImageAsset $= "" && 
         (%assetItem.roughnessImageAsset !$= "" || %assetItem.AOImageAsset !$= "" || %assetItem.metalnessImageAsset !$= "") &&
         getAssetImportConfigValue("Materials/CreateComposites", "1") == 1 &&
         getAssetImportConfigValue("Materials/AlwaysPresentImageMaps", "0") == 0)
      {
         %assetItem.roughnessImageAsset.skip = true;
         %assetItem.AOImageAsset.skip = true;
         %assetItem.metalnessImageAsset.skip = true;
         
         %compositeAssetPath = AssetBrowser.dirHandler.currentAddress @ "/";
         %saveAsPath = %compositeAssetPath @ "/" @ %assetItem.assetName @ "_composite.png";
         %compositeAsset = AssetBrowser.addImportingAsset("Image", "", %assetItem, %assetItem.assetName @ "_composite");
         %compositeAsset.generatedAsset = true;
         %compositeAsset.filePath = %saveAsPath;
         
         %assetItem.compositeImageAsset = %compositeAsset;
      }
   }
   
   %assetItem.processed = true;
}

function AssetBrowser::findMaterialMapFileWSuffix(%this, %fileDir, %filename, %fileExt, %suffixesList)
{
   %listCount = getTokenCount(%suffixesList, ",;");
   
   %foundFile = 0;
   %filePath = "";
   for(%i=0; %i < %listCount; %i++)
   {
      %entryText = getToken(%suffixesList, ",;", %i);
      
      if(%fileExt $= "")
      {
         %filePath = findFirstFile(%fileDir @ "/" @ %filename @ %entryText @ ".*");
         %foundFile = isFile(%filePath);
      }
      else
      {
         %filePath = %fileDir @ "/" @ %filename @ %entryText @ %fileExt;
         %foundFile = isFile(%filePath);
      }
      
      if(%foundFile)
      {
         return %filePath;
      }
   }
   
   return "";
}

function AssetBrowser::importMaterialAsset(%this, %assetItem)
{
   %moduleName = AssetImportTargetModule.getText();
   
   %assetType = %assetItem.AssetType;
   %filePath = %assetItem.filePath;
   %assetName = %assetItem.assetName;
   %assetImportSuccessful = false;
   %assetId = %moduleName@":"@%assetName;
   
   %assetPath = AssetBrowser.dirHandler.currentAddress @ "/";
   %tamlpath = %assetPath @ %assetName @ ".asset.taml";
   %sgfPath = %assetPath @ %assetName @ ".sgf";
   %scriptPath = %assetPath @ %assetName @ ".cs";
   
   %newAsset = new MaterialAsset()
   {
      assetName = %assetName;
      versionId = 1;
      shaderGraph = %sgfPath;
      scriptFile = %assetName @ ".cs";
      originalFilePath = %filePath;
      materialDefinitionName = %assetName;
   };
   
   //check dependencies
   %importItem = ImportAssetTree.findItemByObjectId(%assetItem);
   if(ImportAssetTree.isParentItem(%importItem))
   {
        %imageSlot = 0;
        %childId = ImportAssetTree.getChild(%importItem);
        while(%childId > 0)
        {
            %dependencyAssetItem = ImportAssetTree.getItemObject(%childId);
            
            if(%dependencyAssetItem.skip)
            {
               %childId = ImportAssetTree.getNextSibling(%childId);
               continue;
            }
            
            %depAssetType = %dependencyAssetItem.assetType;
            if(%depAssetType $= "Image")
            {
               %matSet = "%newAsset.imageMap"@%imageSlot@"=\"@Asset="@%moduleName@":"@%dependencyAssetItem.assetName@"\";";
               eval(%matSet);
            }
            
            %childId = ImportAssetTree.getNextSibling(%childId);  
            %imageSlot++;
        }
   }
   
   %assetImportSuccessful = TamlWrite(%newAsset, %tamlpath);
   
   //if we're set to save a composite image, we do that first
   if(getAssetImportConfigValue("Materials/CreateComposites", "1") == 1)
   {
      //don't save a composite if we've already got one bound
      if(%assetItem.compositeImageAsset !$= "" && %assetItem.compositeImageAsset.generatedAsset)
      {
         if(%assetItem.roughnessImageAsset !$= "" || %assetItem.AOImageAsset !$= "" || %assetItem.metalnessImageAsset !$= "")
         {
            %channelKey = "0 1 2 3";
            
            saveCompositeTexture(%assetItem.AOImageAsset.filePath,
                                 %assetItem.roughnessImageAsset.filePath,
                                 %assetItem.metalnessImageAsset.filePath,"",
                                 %channelKey, 
                                 %assetItem.compositeImageAsset.filePath); 
                                 
            %compositeAssetId = %moduleName @ ":" @ assetItem.compositeImageAsset.assetName;
            AssetDatabase.refreshAsset(%compositeAssetId);
         }
      }
   }
   
   %file = new FileObject();

   if(%file.openForWrite(%scriptPath))
   {
      %file.writeline("//--- OBJECT WRITE BEGIN ---");
      %file.writeline("singleton Material(" @ %assetName @ ") {");
      
      //TODO: pass along the shape's target material for this just to be sure
      %file.writeLine("   mapTo = \"" @ %assetName @ "\";"); 
      
      if(%assetItem.diffuseImageAsset !$= "")
      {
         %diffuseAssetPath = %assetPath @ fileName(%assetItem.diffuseImageAsset.filePath);
         %file.writeline("   DiffuseMap[0] = \"" @ %diffuseAssetPath @"\";");
         %file.writeline("   DiffuseMapAsset[0] = \"" @ %moduleName @ ":" @ %assetItem.diffuseImageAsset.assetName @"\";");
      }
      if(%assetItem.normalImageAsset)
      {
         %normalAssetPath = %assetPath @ fileName(%assetItem.normalImageAsset.filePath);
         %file.writeline("   NormalMap[0] = \"" @ %normalAssetPath @"\";");
         %file.writeline("   NormalMapAsset[0] = \"" @ %moduleName @ ":" @ %assetItem.normalImageAsset.assetName @"\";");
      }
      if(%assetItem.roughnessImageAsset && %assetItem.roughnessImageAsset.skip == false)
      {
         %roughAssetPath = %assetPath @ fileName(%assetItem.roughnessImageAsset.filePath);
         %file.writeline("   RoughMap[0] = \"" @ %roughAssetPath @"\";");
         %file.writeline("   RoughMapAsset[0] = \"" @ %moduleName @ ":" @ %assetItem.roughnessImageAsset.assetName @"\";");
      }
      if(%assetItem.smoothnessImageAsset && %assetItem.smoothnessImageAsset.skip == false)
      {
         %smoothnessAssetPath = %assetPath @ fileName(%assetItem.smoothnessImageAsset.filePath);
         %file.writeline("   SmoothnessMap[0] = \"" @ %smoothnessAssetPath @"\";");
         %file.writeline("   SmoothnessMapAsset[0] = \"" @ %moduleName @ ":" @ %assetItem.smoothnessImageAsset.assetName @"\";");
      }
      if(%assetItem.metalnessImageAsset && %assetItem.metalnessImageAsset.skip == false)
      {
         %metalAssetPath = %assetPath @ fileName(%assetItem.metalnessImageAsset.filePath);
         %file.writeline("   MetalMap[0] = \"" @ %metalAssetPath @"\";");
         %file.writeline("   MetalMapAsset[0] = \"" @ %moduleName @ ":" @ %assetItem.metalnessImageAsset.assetName @"\";");
      }
      if(%assetItem.AOImageAsset && %assetItem.AOImageAsset.skip == false)
      {
         %AOAssetPath = %assetPath @ fileName(%assetItem.AOImageAsset.filePath);
         %file.writeline("   AOMap[0] = \"" @ %AOAssetPath @"\";");
         %file.writeline("   AOMapAsset[0] = \"" @ %moduleName @ ":" @ %assetItem.AOImageAsset.assetName @"\";");
      }
      if(%assetItem.PBRConfigMapImageAsset)
      {
         %file.writeline("   PBRConfigMap[0] = \"" @ %assetItem.compositeImageAsset.filePath @"\";");
         %file.writeline("   PBRConfigMapAsset[0] = \"" @ %moduleName @ ":" @ %assetItem.compositeImageAsset.assetName @"\";");
      }
      %file.writeline("};");
      %file.writeline("//--- OBJECT WRITE END ---");
      
      %file.close();
   }
   
   %moduleDef = ModuleDatabase.findModule(%moduleName,1);
         
   if(!AssetBrowser.isAssetReImport)
      AssetDatabase.addDeclaredAsset(%moduleDef, %assetPath @ "/" @ %assetName @ ".asset.taml");
   else
      AssetDatabase.refreshAsset(%assetId);
}

function AssetBrowser::buildMaterialAssetPreview(%this, %assetDef, %previewData)
{
   %previewData.assetName = %assetDef.materialDefinitionName;
   %previewData.assetPath = %assetDef.scriptFile;

   //Lotta prepwork
   %previewData.doubleClickCommand = %assetDef@".materialDefinitionName.reload(); "
                                   @ "$Tools::materialEditorList = \"\";"
                                   @ "EWorldEditor.clearSelection();"
                                   @ "MaterialEditorGui.currentObject = 0;"
                                   @ "MaterialEditorGui.currentMode = \"asset\";"
                                   @ "MaterialEditorGui.currentMaterial = "@%assetDef@".materialDefinitionName;"
                                   @ "MaterialEditorGui.setActiveMaterial( "@%assetDef@".materialDefinitionName );"
                                   @ "EditorGui.setEditor(MaterialEditorPlugin); "
                                   @ "AssetBrowser.hideDialog();";
   
   %test = %assetDef.materialDefinitionName.diffuseMapAsset[0];
   
   if(isFile(%assetDef.materialDefinitionName.diffuseMap[0]))
      %previewData.previewImage = %assetDef.materialDefinitionName.diffuseMap[0];
   else if(%assetDef.materialDefinitionName.diffuseMapAsset[0] !$= "")
   {
      %imgAsset = AssetDatabase.acquireAsset(%assetDef.materialDefinitionName.diffuseMapAsset[0]);
      %previewData.previewImage = %imgAsset.getImageFilename();
   }
   else
      %previewData.previewImage = "tools/assetBrowser/art/materialIcon";
   
   %previewData.assetFriendlyName = %assetDef.assetName;
   %previewData.assetDesc = %assetDef.description;
   %previewData.tooltip = %assetDef.friendlyName @ "\n" @ %assetDef;
}

function AssetBrowser::onMaterialAssetEditorDropped(%this, %assetDef, %position)
{
   //echo("DROPPED A SHAPE ON THE EDITOR WINDOW!"); 
   //first, see if we hit a static shape
   %mask = $TypeMasks::StaticObjectType | $TypeMasks::StaticShapeObjectType | $TypeMasks::TerrainObjectType;
   
   %targetPosition = EWorldEditor.unproject(%position SPC 1000);
   %camPos = LocalClientConnection.camera.getPosition();
   %rayResult = materialRayCast(%camPos, %targetPosition, -1, 0, false);
   
   %validTarget = false;
   if(%rayResult != 0)
   {
      %obj = getWord(%rayResult, 0);
      if(%obj.isMemberOfClass("TSStatic"))
      {
         //oh, cool a valid target! 
         %obj.materialSlot0 = %assetDef.getAssetId();
         echo("MaterialSlot0 set to " @ %assetDef.getAssetId());
      }
   }

   EWorldEditor.isDirty = true;
   
}

function GuiInspectorTypeMaterialAssetPtr::onControlDropped( %this, %payload, %position )
{
   Canvas.popDialog(EditorDragAndDropLayer);
   
   // Make sure this is a color swatch drag operation.
   if( !%payload.parentGroup.isInNamespaceHierarchy( "AssetPreviewControlType_AssetDrop" ) )
      return;

   %assetType = %payload.dragSourceControl.parentGroup.assetType;
   %module = %payload.dragSourceControl.parentGroup.moduleName;
   %assetName = %payload.dragSourceControl.parentGroup.assetName;
   
   if(%assetType $= "MaterialAsset")
   {
      echo("DROPPED A MATERIAL ON A MATERIAL ASSET COMPONENT FIELD!");  
      //%assetDef = AssetDatabase.acquireAsset(%module @ ":" @ %assetName);
      
      %this.setMaterialAsset(%module @ ":" @ %assetName);
   }
   
   EWorldEditor.isDirty = true;
}
