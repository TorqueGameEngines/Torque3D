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

function ImportAssetConfigEditorWindow::populateConfigList(%this, %optionsObj)
{
   AssetImportConfigName.setText(%optionsObj.Name);
   
   ImportOptionsConfigList.clearFields();
   
   ImportOptionsConfigList.startGroup("Mesh");
   ImportOptionsConfigList.addSettingsField("Mesh/ImportMesh", "Import Mesh", "bool", "Should meshes be imported", "");
   ImportOptionsConfigList.endGroup();
   
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

function ImportAssetConfigEditorWindow::addNewConfig(%this)
{
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
   ImportAssetConfigEditorWindow.setVisible(1);
   ImportAssetConfigEditorWindow.selectWindow();
   
   %this.populateConfigList(ImportAssetWindow.activeImportConfig);
}

function ImportAssetConfigEditorWindow::deleteConfig(%this)
{
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

function ImportOptionsConfigList::addSettingsField(%this, %settingsFieldName, %labelText, %fieldType, %tooltip, %fieldData)
{
   %moddedSettingsFieldName = strreplace(%settingsFieldName, "/", "-");
   
   %this.addCallbackField(%moddedSettingsFieldName, %labelText, %fieldType, "", AssetImportSettings.value(%settingsFieldName), %fieldData, "changeEditorSetting");
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