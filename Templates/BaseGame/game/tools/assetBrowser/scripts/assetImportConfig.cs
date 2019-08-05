function ImportAssetConfigList::onSelect( %this, %id, %text )
{
   //Apply our settings to the assets
   echo("Changed our import config!");
   AssetBrowser.importAssetUnprocessedListArray.empty();
   AssetBrowser.importAssetUnprocessedListArray.duplicate(AssetBrowser.importAssetNewListArray);
   AssetBrowser.importAssetFinalListArray.empty();
   
   ImportAssetWindow.activeImportConfigIndex = %id;
   ImportAssetWindow.activeImportConfig = ImportAssetWindow.importConfigsList.getKey(%id);
   
   AssetBrowser.reloadImportingFiles();
}

function setupImportConfigSettingsList()
{
   if(!isObject(ImportAssetConfigSettingsList))
   {
      new ArrayObject(ImportAssetConfigSettingsList);
   
      ImportAssetConfigSettingsList.addNewConfigSetting("Mesh/ImportMesh", "Import Mesh", "bool", "", "1", "", "ToggleImportMesh");
      ImportAssetConfigSettingsList.addNewConfigSetting("Meshes/DoUpAxisOverride", "Do Up-axis Override", "bool", "", "0", "");
      ImportAssetConfigSettingsList.addNewConfigSetting("Meshes/UpAxisOverride", "Up-axis Override", "list", "", "Z_AXIS", "X_AXIS,Y_AXIS,Z_AXIS");
      ImportAssetConfigSettingsList.addNewConfigSetting("Meshes/ScaleOverride", "Do Scale Override", "bool", "", "0", "");
      ImportAssetConfigSettingsList.addNewConfigSetting("Meshes/ScaleOverride", "Scale Override", "float", "", "1", "");
      ImportAssetConfigSettingsList.addNewConfigSetting("Meshes/IgnoreNodeScale", "Ignore Node Scale", "bool", "", "0", "");
      ImportAssetConfigSettingsList.addNewConfigSetting("Meshes/AdjustCenter", "Adjust Center", "bool", "", "0", "");
      ImportAssetConfigSettingsList.addNewConfigSetting("Meshes/AdjustFloor", "Adjust Floor", "bool", "", "0", "");
      ImportAssetConfigSettingsList.addNewConfigSetting("Meshes/CollapseSubmeshes", "Collapse Submeshes", "bool", "", "0", "");
      ImportAssetConfigSettingsList.addNewConfigSetting("Meshes/LODType", "LOD Type", "list", "", "TrailingNumber", "TrailingNumber,DetectDTS");
      //ImportAssetConfigSettingsList.addNewConfigSetting("TrailingNumber", "Trailing Number", "float", "", "2", "", "Mesh");
      ImportAssetConfigSettingsList.addNewConfigSetting("Meshes/ImportedNodes", "Imported Nodes", "command", "", "", "");
      ImportAssetConfigSettingsList.addNewConfigSetting("Meshes/IgnoreNodes", "Ignore Nodes", "command", "", "", "");
      ImportAssetConfigSettingsList.addNewConfigSetting("Meshes/ImportMeshes", "Import Meshes", "command", "", "", "");
      ImportAssetConfigSettingsList.addNewConfigSetting("Meshes/IgnoreMeshes", "Imported Meshes", "command", "", "", "");
      
      //Materials
      ImportAssetConfigSettingsList.addNewConfigSetting("Materials/ImportMaterials", "Import Materials", "bool", "", "1", "");
      ImportAssetConfigSettingsList.addNewConfigSetting("Materials/CreateComposites", "Create Composites", "bool", "", "1", "");
      ImportAssetConfigSettingsList.addNewConfigSetting("Materials/UseDiffuseSuffixOnOriginImage", "Use Diffuse Suffix for Origin Image", "bool", "", "1", "");
      ImportAssetConfigSettingsList.addNewConfigSetting("Materials/UseExistingMaterials", "Use Existing Materials", "bool", "", "1", "");
      ImportAssetConfigSettingsList.addNewConfigSetting("Materials/IgnoreMaterials", "Ignore Materials", "command", "", "", "");
      
      //Animations
      ImportAssetConfigSettingsList.addNewConfigSetting("Animations/ImportAnimations", "Import Animations", "bool", "", "1", "");
      ImportAssetConfigSettingsList.addNewConfigSetting("Animations/SeparateAnimations", "Separate Animations", "bool", "", "1", "");
      ImportAssetConfigSettingsList.addNewConfigSetting("Animations/SeparateAnimationPrefix", "Separate Animation Prefix", "string", "", "", "");
      
      //Collision
      ImportAssetConfigSettingsList.addNewConfigSetting("Collision/GenerateCollisions", "Generate Collisions", "bool", "", "1", "");
      ImportAssetConfigSettingsList.addNewConfigSetting("Collision/GenCollisionType", "Generate Collision Type", "list", "", "CollisionMesh", "CollisionMesh,ConvexHull");
      ImportAssetConfigSettingsList.addNewConfigSetting("Collision/CollisionMeshPrefix", "CollisionMesh Prefix", "string", "", "Col", "");
      ImportAssetConfigSettingsList.addNewConfigSetting("Collision/GenerateLOSCollisions", "Generate LOS Collisions", "bool", "", "1", "");
      ImportAssetConfigSettingsList.addNewConfigSetting("Collision/GenLOSCollisionType", "Generate LOS Collision Type", "list", "", "CollisionMesh", "CollisionMesh,ConvexHull");
      ImportAssetConfigSettingsList.addNewConfigSetting("Collision/LOSCollisionMeshPrefix", "LOS CollisionMesh Prefix", "string", "", "LOS", "");
      
      //Images
      ImportAssetConfigSettingsList.addNewConfigSetting("Images/ImageType", "Image Type", "list", "", "N/A", "N/A,Diffuse,Normal,Specular,Metalness,Roughness,AO,Composite,GUI");
      ImportAssetConfigSettingsList.addNewConfigSetting("Images/DiffuseTypeSuffixes", "Diffuse Type Suffixes", "command", "", "_ALBEDO,_DIFFUSE,_ALB,_DIF,_COLOR,_COL", "");
      ImportAssetConfigSettingsList.addNewConfigSetting("Images/NormalTypeSuffixes", "Normal Type Suffixes", "command", "", "_NORMAL,_NORM", "");
      
      ImportAssetConfigSettingsList.addNewConfigSetting("Images/MetalnessTypeSuffixes", "Metalness Type Suffixes", "command", "", "_METAL,_MET,_METALNESS,_METALLIC", "");
      ImportAssetConfigSettingsList.addNewConfigSetting("Images/RoughnessTypeSuffixes", "Roughness Type Suffixes", "command", "", "_ROUGH,_ROUGHNESS", "");
      ImportAssetConfigSettingsList.addNewConfigSetting("Images/SmoothnessTypeSuffixes", "Smoothness Type Suffixes", "command", "", "_SMOOTH,_SMOOTHNESS", "");
      ImportAssetConfigSettingsList.addNewConfigSetting("Images/AOTypeSuffixes", "AO Type Suffixes", "command", "", "_AO,_AMBIENT,_AMBIENTOCCLUSION", "");
      ImportAssetConfigSettingsList.addNewConfigSetting("Images/CompositeTypeSuffixes", "Composite Type Suffixes", "command", "", "_COMP,_COMPOSITE", "");
      
      ImportAssetConfigSettingsList.addNewConfigSetting("Images/TextureFilteringMode", "Texture Filtering Mode", "list", "", "Bilinear", "None,Bilinear,Trilinear");
      ImportAssetConfigSettingsList.addNewConfigSetting("Images/UseMips", "Use Mipmaps", "bool", "", "1", "");
      ImportAssetConfigSettingsList.addNewConfigSetting("Images/IsHDR", "Is HDR", "bool", "", "0", "");
      ImportAssetConfigSettingsList.addNewConfigSetting("Images/Scaling", "Scaling", "float", "", "1.0", "");
      ImportAssetConfigSettingsList.addNewConfigSetting("Images/Compressed", "Is Compressed", "bool", "", "1", "");
      ImportAssetConfigSettingsList.addNewConfigSetting("Images/GenerateMaterialOnImport", "Generate Material On Import", "bool", "", "1", "");
      ImportAssetConfigSettingsList.addNewConfigSetting("Images/PopulateMaterialMaps", "Populate Material Maps", "bool", "", "1", "");

      //Sounds
      ImportAssetConfigSettingsList.addNewConfigSetting("Sounds/VolumeAdjust", "Volume Adjustment", "float", "", "1.0", "");
      ImportAssetConfigSettingsList.addNewConfigSetting("Sounds/PitchAdjust", "Pitch Adjustment", "float", "", "1.0", "");
      ImportAssetConfigSettingsList.addNewConfigSetting("Sounds/Compressed", "Is Compressed", "bool", "", "0", "");
   }
}

function ImportAssetConfigSettingsList::addNewConfigSetting(%this, %settingName, %settingFieldLabel, %type, %tooltip, %defaultValue, %fieldData)
{
   %this.add(%settingName TAB %settingFieldLabel TAB %type TAB %tooltip, %defaultValue TAB %fieldData);
}

function ImportAssetOptionsWindow::findMissingFile(%this, %assetItem)
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
function ImportAssetOptionsWindow::editImportSettings(%this, %assetItem)
{
   ImportAssetOptionsWindow.setVisible(1);
   ImportAssetOptionsWindow.selectWindow();
   
   ImportOptionsList.clearFields();
   
   %assetType = %assetItem.assetType;
   %filePath = %assetItem.filePath;
   %assetName = %assetItem.assetName;
   %assetConfigObj = %assetItem.importConfig;
   
   ImportOptionsList.startGroup("Asset");
   ImportOptionsList.addField("AssetName", "Asset Name", "string", "", "NewAsset", "", %assetItem);
   ImportOptionsList.endGroup();
   
   if(%assetType $= "Model")
   {
      //Get the shape info, so we know what we're doing with the mesh
      %shapeInfo = GetShapeInfo(%filePath);
      %meshItem = %shapeInfo.findItemByName("Meshes");
      %matItem = %shapeInfo.findItemByName("Materials");
      
      %meshCount = %shapeInfo.getItemValue(%meshItem);
      %matCount = %shapeInfo.getItemValue(%matItem);
      
      %firstMat = %shapeInfo.getChild(%matItem);
      echo("Mesh's first material texture path is: " @ %shapeInfo.getItemValue(%firstMat));
            
      if(%meshCount > 0)
      {
         ImportOptionsList.startGroup("Mesh");
         
         ImportOptionsList.addField("AutogenCollisions", "Auto-gen Collisions", "bool", "", "0", "", %assetConfigObj);
         ImportOptionsList.addField("CollapseSubmeshes", "Collapse Submeshes", "bool", "", "0", "", %assetConfigObj);
         ImportOptionsList.addField("UpAxisOverride", "Up-Axis Override", "list", "", "Z_AXIS", "Z_AXIS,Y_AXIS,X_AXIS", %assetConfigObj);
         ImportOptionsList.addField("OverrideScale", "Override Scale", "float", "", "1.0", "", %assetConfigObj);
         ImportOptionsList.addField("IgnoreNodeScale", "IgnoreNodeScaling", "bool", "", "0", "", %assetConfigObj);
         ImportOptionsList.addField("AdjustCenter", "Adjust Center", "bool", "", "0", "", %assetConfigObj);
         ImportOptionsList.addField("CollapseSubmeshes", "Collapse Submeshes", "bool", "", "0", "", %assetConfigObj);
         ImportOptionsList.addField("AdjustFloor", "Adjust Floor", "bool", "", "0", "", %assetConfigObj);
         ImportOptionsList.addField("LODType", "LOD Type", "list", "", "TrailingNumber", "TrailingNumber,DetectDTS", %assetConfigObj);
         ImportOptionsList.endGroup();
      }
      
      if(%matItem > 0)
      {
         ImportOptionsList.startGroup("Material");
         ImportOptionsList.addCallbackField("ImportMaterials", "Import Materials", "bool", "", "1", "", "ImportMaterialsChanged", %assetConfigObj);
         ImportOptionsList.addField("UseExistingMaterials", "Use Existing Materials", "bool", "", "1", "", %assetConfigObj);
         ImportOptionsList.endGroup();
      }
   }
   else if(%assetType $= "Material")
   {
      ImportOptionsList.startGroup("Material");
      ImportOptionsList.addField("CreateComposites", "Create Composite Textures", "bool", "", "1", "", %assetConfigObj);
      ImportOptionsList.endGroup();
   }
   else if(%assetType $= "Image")
   {
      ImportOptionsList.startGroup("Formatting");
      ImportOptionsList.addField("ImageType", "Image Type", "string", "", "Diffuse", "", %assetConfigObj);
      ImportOptionsList.addField("TextureFiltering", "Texture Filtering", "list", "", "Bilinear", "None,Bilinear,Trilinear", %assetConfigObj);
      ImportOptionsList.addField("UseMips", "Use Mips", "bool", "", "1", "", %assetConfigObj);
      ImportOptionsList.addField("IsHDR", "Is HDR", "bool", "", "0", "", %assetConfigObj);
      ImportOptionsList.endGroup();
      
      ImportOptionsList.startGroup("Scaling");
      ImportOptionsList.addField("Scaling", "Scaling", "float", "", "1.0", "", %assetConfigObj);
      ImportOptionsList.endGroup();
      
      ImportOptionsList.startGroup("Compression");
      ImportOptionsList.addField("IsCompressed", "Is Compressed", "bool", "", "1", "", %assetConfigObj);
      ImportOptionsList.endGroup();
      
      ImportOptionsList.startGroup("Material");
      ImportOptionsList.addField("GenerateMaterialOnImport", "Generate Material On Import", "bool", "", "1", "", %optionsObj);
      ImportOptionsList.addField("PopulateMaterialMaps", "Populate Material Maps", "bool", "", "1", "", %optionsObj);
      ImportOptionsList.addField("UseDiffuseSuffixOnOriginImg", "Use Diffuse Suffix for Origin Image", "bool", "", "1", "", %optionsObj);
      ImportOptionsList.addField("UseExistingMaterials", "Use Existing Materials", "bool", "", "1", "", %optionsObj);
      ImportOptionsList.addField("IgnoreMaterials", "Ignore Importing Materials that fit these naming convention.", "command", "", "1", "", %optionsObj);
      ImportOptionsList.endGroup();
   }
   else if(%assetType $= "Sound")
   {
      ImportOptionsList.startGroup("Adjustment");
      ImportOptionsList.addField("VolumeAdjust", "VolumeAdjustment", "float", "", "1.0", "", %assetConfigObj);
      ImportOptionsList.addField("PitchAdjust", "PitchAdjustment", "float", "", "1.0", "", %assetConfigObj);
      ImportOptionsList.endGroup();
      
      ImportOptionsList.startGroup("Compression");
      ImportOptionsList.addField("IsCompressed", "Is Compressed", "bool", "", "1", "", %assetConfigObj);
      ImportOptionsList.endGroup();
   }
}

function ImportAssetOptionsWindow::deleteImportingAsset(%this, %assetItem)
{
   %item = ImportAssetTree.findItemByObjectId(%assetItem);
   
   ImportAssetTree.removeAllChildren(%item);
   ImportAssetTree.removeItem(%item);

   schedule(10, 0, "refreshImportAssetWindow");
   //ImportAssetWindow.refresh();
   ImportAssetOptionsWindow.setVisible(0);
}

function ImportAssetOptionsWindow::saveAssetOptions(%this)
{
   ImportAssetWindow.refresh();
   ImportAssetOptionsWindow.setVisible(0);   
}

function ImportOptionsList::ImportMaterialsChanged(%this, %fieldName, %newValue, %ownerObject)
{
   echo("CHANGED IF OUR IMPORTED MATERIALS WERE HAPPENING!");
}

function getAssetImportConfigValue(%fieldName, %defaultValue)
{
   if(ImportAssetWindow.activeImportConfig $= "")
      return "";
   
   return AssetImportSettings.value(ImportAssetWindow.activeImportConfig @ "/" @ %fieldName, %defaultValue);
}

function ImportAssetConfigEditorWindow::populateConfigList(%this, %configName)
{
   //Ensure our config list is set up
   setupImportConfigSettingsList();
   
   AssetImportConfigName.setText(%configName);
   
   ImportOptionsConfigList.clearFields();
   
   %this.populateConfigListByGroup("Meshes");
   %this.populateConfigListByGroup("Materials");
   %this.populateConfigListByGroup("Animations");
   %this.populateConfigListByGroup("Images");
   %this.populateConfigListByGroup("Collision");
   %this.populateConfigListByGroup("Sound");
   
   /*ImportOptionsConfigList.addCallbackField("ImportMesh", "Import Mesh", "bool", "", "1", "", "ToggleImportMesh", %optionsObj);
   ImportOptionsConfigList.addField("DoUpAxisOverride", "Do Up-axis Override", "bool", "", "0", "", %optionsObj);
   ImportOptionsConfigList.addField("UpAxisOverride", "Up-axis Override", "list", "", "Z_AXIS", "X_AXIS,Y_AXIS,Z_AXIS", %optionsObj);
   ImportOptionsConfigList.addField("DoScaleOverride", "Do Scale Override", "bool", "", "0", "", %optionsObj);
   ImportOptionsConfigList.addField("ScaleOverride", "Scale Override", "float", "", "1", "", %optionsObj);
   ImportOptionsConfigList.addField("IgnoreNodeScale", "Ignore Node Scale", "bool", "", "0", "", %optionsObj);
   ImportOptionsConfigList.addField("AdjustCenter", "Adjust Center", "bool", "", "0", "", %optionsObj);
   ImportOptionsConfigList.addField("AdjustFloor", "Adjust Floor", "bool", "", "0", "", %optionsObj);
   ImportOptionsConfigList.addField("CollapseSubmeshes", "Collapse Submeshes", "bool", "", "0", "", %optionsObj);
   ImportOptionsConfigList.addField("LODType", "LOD Type", "list", "", "TrailingNumber", "TrailingNumber,DetectDTS", %optionsObj);
   //ImportOptionsConfigList.addField("TrailingNumber", "Trailing Number", "float", "", "2", "", %optionsObj, "Mesh");
   ImportOptionsConfigList.addField("ImportedNodes", "Imported Nodes", "command", "", "", "", %optionsObj);
   ImportOptionsConfigList.addField("IgnoreNodes", "Ignore Nodes", "command", "", "", "", %optionsObj);
   ImportOptionsConfigList.addField("ImportMeshes", "Import Meshes", "command", "", "", "", %optionsObj);
   ImportOptionsConfigList.addField("IgnoreMeshes", "Imported Meshes", "command", "", "", "", %optionsObj);
   ImportOptionsConfigList.endGroup();
   
   //Materials
   ImportOptionsConfigList.startGroup("Material");
   ImportOptionsConfigList.addField("ImportMaterials", "Import Materials", "bool", "", "1", "", %optionsObj);
   ImportOptionsConfigList.addField("CreateComposites", "Create Composites", "bool", "", "1", "", %optionsObj);
   ImportOptionsConfigList.addField("UseDiffuseSuffixOnOriginImg", "Use Diffuse Suffix for Origin Image", "bool", "", "1", "", %optionsObj);
   ImportOptionsConfigList.addField("UseExistingMaterials", "Use Existing Materials", "bool", "", "1", "", %optionsObj);
   ImportOptionsConfigList.addField("IgnoreMaterials", "Ignore Materials", "command", "", "", "", %optionsObj);
   ImportOptionsConfigList.endGroup();
   
   //Animations
   ImportOptionsConfigList.startGroup("Animations");
   ImportOptionsConfigList.addField("ImportAnimations", "Import Animations", "bool", "", "1", "", %optionsObj);
   ImportOptionsConfigList.addField("SeparateAnimations", "Separate Animations", "bool", "", "1", "", %optionsObj);
   ImportOptionsConfigList.addField("SeparateAnimationPrefix", "Separate Animation Prefix", "string", "", "", "", %optionsObj);
   ImportOptionsConfigList.endGroup();
   
   //Collision
   ImportOptionsConfigList.startGroup("Collision");
   ImportOptionsConfigList.addField("GenerateCollisions", "Generate Collisions", "bool", "", "1", "", %optionsObj);
   ImportOptionsConfigList.addField("GenCollisionType", "Generate Collision Type", "list", "", "CollisionMesh", "CollisionMesh,ConvexHull", %optionsObj);
   ImportOptionsConfigList.addField("CollisionMeshPrefix", "CollisionMesh Prefix", "string", "", "Col", "", %optionsObj);
   ImportOptionsConfigList.addField("GenerateLOSCollisions", "Generate LOS Collisions", "bool", "", "1", "", %optionsObj);
   ImportOptionsConfigList.addField("GenLOSCollisionType", "Generate LOS Collision Type", "list", "", "CollisionMesh", "CollisionMesh,ConvexHull", %optionsObj);
   ImportOptionsConfigList.addField("LOSCollisionMeshPrefix", "LOS CollisionMesh Prefix", "string", "", "LOS", "", %optionsObj);
   ImportOptionsConfigList.endGroup();
   
   //Images
   ImportOptionsConfigList.startGroup("Image");
   ImportOptionsConfigList.addField("ImageType", "Image Type", "list", "", "N/A", "N/A,Diffuse,Normal,Specular,Metalness,Roughness,AO,Composite,GUI", %optionsObj);
   ImportOptionsConfigList.addField("DiffuseTypeSuffixes", "Diffuse Type Suffixes", "command", "", "_ALBEDO,_DIFFUSE,_ALB,_DIF,_COLOR,_COL", "", %optionsObj);
   ImportOptionsConfigList.addField("NormalTypeSuffixes", "Normal Type Suffixes", "command", "", "_NORMAL,_NORM", "", %optionsObj);
   
   if(EditorSettings.lightingModel $= "Legacy")
   {
      ImportOptionsConfigList.addField("SpecularTypeSuffixes", "Specular Type Suffixes", "command", "", "_SPECULAR,_SPEC", "", %optionsObj);
   }
   else
   {
      ImportOptionsConfigList.addField("MetalnessTypeSuffixes", "Metalness Type Suffixes", "command", "", "_METAL,_MET,_METALNESS,_METALLIC", "", %optionsObj);
      ImportOptionsConfigList.addField("RoughnessTypeSuffixes", "Roughness Type Suffixes", "command", "", "_ROUGH,_ROUGHNESS", "", %optionsObj);
      ImportOptionsConfigList.addField("SmoothnessTypeSuffixes", "Smoothness Type Suffixes", "command", "", "_SMOOTH,_SMOOTHNESS", "", %optionsObj);
      ImportOptionsConfigList.addField("AOTypeSuffixes", "AO Type Suffixes", "command", "", "_AO,_AMBIENT,_AMBIENTOCCLUSION", "", %optionsObj);
      ImportOptionsConfigList.addField("CompositeTypeSuffixes", "Composite Type Suffixes", "command", "", "_COMP,_COMPOSITE", "", %optionsObj);
   }
   
   ImportOptionsConfigList.addField("TextureFilteringMode", "Texture Filtering Mode", "list", "", "Bilinear", "None,Bilinear,Trilinear", %optionsObj);
   ImportOptionsConfigList.addField("UseMips", "Use Mipmaps", "bool", "", "1", "", %optionsObj);
   ImportOptionsConfigList.addField("IsHDR", "Is HDR", "bool", "", "0", "", %optionsObj);
   ImportOptionsConfigList.addField("Scaling", "Scaling", "float", "", "1.0", "", %optionsObj);
   ImportOptionsConfigList.addField("Compressed", "Is Compressed", "bool", "", "1", "", %optionsObj);
   ImportOptionsConfigList.addField("GenerateMaterialOnImport", "Generate Material On Import", "bool", "", "1", "", %optionsObj);
   ImportOptionsConfigList.addField("PopulateMaterialMaps", "Populate Material Maps", "bool", "", "1", "", %optionsObj);
   ImportOptionsConfigList.endGroup();
   
   //Sounds
   ImportOptionsConfigList.startGroup("Sound");
   ImportOptionsConfigList.addField("VolumeAdjust", "Volume Adjustment", "float", "", "1.0", "", %optionsObj);
   ImportOptionsConfigList.addField("PitchAdjust", "Pitch Adjustment", "float", "", "1.0", "", %optionsObj);
   ImportOptionsConfigList.addField("Compressed", "Is Compressed", "bool", "", "0", "", %optionsObj);
   ImportOptionsConfigList.endGroup();*/
}

function ImportAssetConfigEditorWindow::populateConfigListByGroup(%this, %groupName)
{
   ImportOptionsConfigList.startGroup(%groupName);
   for(%i=0; %i < ImportAssetConfigSettingsList.count(); %i++)
   {
      %settingName = getField(ImportAssetConfigSettingsList.getKey(%i),0);
      if(startsWith(%settingName, %groupName@"/"))
      {
         %labelName = getField(ImportAssetConfigSettingsList.getKey(%i), 1);
         %type = getField(ImportAssetConfigSettingsList.getKey(%i), 2);
         %tooltip = getField(ImportAssetConfigSettingsList.getKey(%i), 3);
         
         %defaultValue = getField(ImportAssetConfigSettingsList.getValue(%i), 0);
         %dataValues = getField(ImportAssetConfigSettingsList.getValue(%i), 1);
         ImportOptionsConfigList.addSettingsField(%settingName, %labelName, %type, %tooltip, %defaultValue, %dataValues);
      }
   }
   ImportOptionsConfigList.endGroup();
}

function ImportAssetConfigEditorWindow::addNewConfig(%this)
{
   //Ensure our list is set up
   setupImportConfigSettingsList();
   
   ImportAssetNewConfigEditorWindow.setVisible(1);
   ImportAssetNewConfigEditorWindow.selectWindow();
   
   %configName = AssetImportConfigName.getText();
   
   AssetImportSettings.beginGroup(%configName);
   
   //Meshes
   AssetImportSettings.setValue("Meshes/ImportMesh", "1");
   AssetImportSettings.setValue("Meshes/DoUpAxisOverride", "0");
   AssetImportSettings.setValue("Meshes/UpAxisOverride", "Z_AXIS");
   AssetImportSettings.setValue("Meshes/DoScaleOverride", "0");
   AssetImportSettings.setValue("Meshes/ScaleOverride", "1.0");
   AssetImportSettings.setValue("Meshes/IgnoreNodeScale", "0");
   AssetImportSettings.setValue("Meshes/AdjustCenter", "0");
   AssetImportSettings.setValue("Meshes/AdjustFloor", "0");
   AssetImportSettings.setValue("Meshes/CollapseSubmeshes", "0");
   AssetImportSettings.setValue("Meshes/LODType", "TrailingNumber");
   AssetImportSettings.setValue("Meshes/ImportedNodes", "");
   AssetImportSettings.setValue("Meshes/IgnoreNodes", "");
   AssetImportSettings.setValue("Meshes/ImportMeshes", "");
   AssetImportSettings.setValue("Meshes/IgnoreMeshes", "");
   
   //Materials
   AssetImportSettings.setValue("Materials/ImportMaterials", "1");
   AssetImportSettings.setValue("Materials/IgnoreMaterials", "");
   AssetImportSettings.setValue("Materials/CreateComposites", "1");
   AssetImportSettings.setValue("Materials/UseDiffuseSuffixOnOriginImage", "1");
   AssetImportSettings.setValue("Materials/UseExistingMaterials", "1");
   
   //Animations
   AssetImportSettings.setValue("Animations/ImportAnimations", "1");
   AssetImportSettings.setValue("Animations/SeparateAnimations", "1");
   AssetImportSettings.setValue("Animations/SeparateAnimationPrefix", "");
   
   //Collision
   AssetImportSettings.setValue("Collision/GenerateCollisions", "1");
   AssetImportSettings.setValue("Collision/GenCollisionType", "CollisionMesh");
   AssetImportSettings.setValue("Collision/CollisionMeshPrefix", "Col");
   AssetImportSettings.setValue("Collision/GenerateLOSCollisions", "1");
   AssetImportSettings.setValue("Collision/GenLOSCollisionType", "CollisionMesh");
   AssetImportSettings.setValue("Collision/LOSCollisionMeshPrefix", "LOS");
   
   //Images
   AssetImportSettings.setValue("Images/ImageType", "N/A");
   AssetImportSettings.setValue("Images/DiffuseTypeSuffixes", "_ALBEDO;_DIFFUSE;_ALB;_DIF;_COLOR;_COL;_BASECOLOR;_BASE_COLOR");
   AssetImportSettings.setValue("Images/NormalTypeSuffixes", "_NORMAL;_NORM");
   AssetImportSettings.setValue("Images/MetalnessTypeSuffixes", "_METAL;_MET;_METALNESS;_METALLIC");
   AssetImportSettings.setValue("Images/RoughnessTypeSuffixes", "_ROUGH;_ROUGHNESS");
   AssetImportSettings.setValue("Images/SmoothnessTypeSuffixes", "_SMOOTH;_SMOOTHNESS");
   AssetImportSettings.setValue("Images/AOTypeSuffixes", "_AO;_AMBIENT;_AMBIENTOCCLUSION");
   AssetImportSettings.setValue("Images/CompositeTypeSuffixes", "_COMP;_COMPOSITE");
   AssetImportSettings.setValue("Images/TextureFilteringMode", "Bilinear");
   AssetImportSettings.setValue("Images/UseMips", "1");
   AssetImportSettings.setValue("Images/IsHDR", "0");
   AssetImportSettings.setValue("Images/Scaling", "1.0");
   AssetImportSettings.setValue("Images/Compressed", "1");
   AssetImportSettings.setValue("Images/GenerateMaterialOnImport", "1");
   AssetImportSettings.setValue("Images/PopulateMaterialMaps", "1");
   
   //Sounds
   AssetImportSettings.setValue("Sounds/VolumeAdjust", "1.0");
   AssetImportSettings.setValue("Sounds/PitchAdjust", "1.0");
   AssetImportSettings.setValue("Sounds/Compressed", "0");
   
   AssetImportSettings.endGroup();
   
   //Hook in the UI
   //%this.populateConfigList(%optionsObj);
}

function ImportAssetConfigEditorWindow::editConfig(%this)
{
   //Ensure our list is set up
   ImportAssetConfigEditorWindow.setVisible(1);
   ImportAssetConfigEditorWindow.selectWindow();
   
   %this.populateConfigList(ImportAssetWindow.activeImportConfig);
}

function ImportAssetConfigEditorWindow::deleteConfig(%this)
{
   for(%i=0; %i < %configList.count(); %i++)
   {
      
   }
   ImportAssetWindow.importConfigsList.erase(ImportAssetWindow.activeImportConfigIndex);
   ImportAssetConfigList.setSelected(0); //update it
   
   ImportAssetConfigEditorWindow.saveAssetOptionsConfig();
}

function ImportAssetConfigEditorWindow::saveAssetOptionsConfig(%this)
{
   %success = AssetImportSettings.write();
   
   ImportAssetConfigEditorWindow.setVisible(0);
   ImportAssetWindow.reloadImportOptionConfigs();
}

function ImportAssetConfigEditorWindow::createNewImportConfig(%this)
{
   %configName = AssetImportNewConfigName.getText();
   %configList = ImportAssetConfigSettingsList;
   
   AssetImportSettings.beginGroup(%configName);
   
   for(%i=0; %i < %configList.count(); %i++)
   {
      %settingName = getField(%configList.getKey(%i),0);
      if(startsWith(%settingName, "Meshes/"))
      {
         %defaultValue = getField(%configList.getValue(%i), 0);
         AssetImportSettings.setValue(%settingName, %defaultValue);
      }
   }
   
   for(%i=0; %i < %configList.count(); %i++)
   {
      %settingName = getField(%configList.getKey(%i),0);
      if(startsWith(%settingName, "Materials/"))
      {
         %defaultValue = getField(%configList.getValue(%i), 0);
         AssetImportSettings.setValue(%settingName, %defaultValue);
      }
   }
   
   for(%i=0; %i < %configList.count(); %i++)
   {
      %settingName = getField(%configList.getKey(%i),0);
      if(startsWith(%settingName, "Animations/"))
      {
         %defaultValue = getField(%configList.getValue(%i), 0);
         AssetImportSettings.setValue(%settingName, %defaultValue);
      }
   }
   
   for(%i=0; %i < %configList.count(); %i++)
   {
      %settingName = getField(%configList.getKey(%i),0);
      if(startsWith(%settingName, "Collision/"))
      {
         %defaultValue = getField(%configList.getValue(%i), 0);
         AssetImportSettings.setValue(%settingName, %defaultValue);
      }
   }
   
   for(%i=0; %i < %configList.count(); %i++)
   {
      %settingName = getField(%configList.getKey(%i),0);
      if(startsWith(%settingName, "Images/"))
      {
         %defaultValue = getField(%configList.getValue(%i), 0);
         AssetImportSettings.setValue(%settingName, %defaultValue);
      }
   }

   for(%i=0; %i < %configList.count(); %i++)
   {
      %settingName = getField(%configList.getKey(%i),0);
      if(startsWith(%settingName, "Sounds/"))
      {
         %defaultValue = getField(%configList.getValue(%i), 0);
         AssetImportSettings.setValue(%settingName, %defaultValue);
      }
   }
   
   AssetImportSettings.endGroup();
   
   %success = AssetImportSettings.write();
   
   ImportAssetNewConfigEditorWindow.setVisible(0);
}

function ImportOptionsConfigList::addSettingsField(%this, %settingsFieldName, %labelText, %fieldType, %tooltip, %fieldValue, %fieldData)
{
   %moddedSettingsFieldName = strreplace(%settingsFieldName, "/", "-");
   
   %value = AssetImportSettings.value(%settingsFieldName);
   if(%value $= "")
      %value = %fieldValue;
   
   %this.addCallbackField(%moddedSettingsFieldName, %labelText, %fieldType, "", %value, %fieldData, "changeEditorSetting");
}

function ImportOptionsConfigList::changeEditorSetting(%this, %varName, %value)
{
   %varName = strreplace(%varName, "-", "/");
   
   echo("Set " @ %varName @ " to be " @ %value);  
   
   AssetImportSettings.setValue(%varName, %value);
   
   %success = AssetImportSettings.write();
}

function ImportOptionsConfigList::ToggleImportMesh(%this, %fieldName, %newValue, %ownerObject)
{
   %this.setFieldEnabled("DoUpAxisOverride", %newValue);
   %this.setFieldEnabled("UpAxisOverride", %newValue);
   %this.setFieldEnabled("DoScaleOverride", %newValue);
   %this.setFieldEnabled("ScaleOverride", %newValue);
   %this.setFieldEnabled("IgnoreNodeScale", %newValue);
   %this.setFieldEnabled("AdjustCenter", %newValue);
   %this.setFieldEnabled("AdjustFloor", %newValue);
   %this.setFieldEnabled("CollapseSubmeshes", %newValue);
   %this.setFieldEnabled("LODType", %newValue);   
   %this.setFieldEnabled("ImportedNodes", %newValue);
   %this.setFieldEnabled("IgnoreNodes", %newValue);
   %this.setFieldEnabled("ImportMeshes", %newValue);
   %this.setFieldEnabled("IgnoreMeshes", %newValue);
}