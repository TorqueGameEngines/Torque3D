function AssetImportConfigEditor::onWake(%this)
{
   %this.refresh();
}

function AssetImportConfigEditor::refresh(%this)
{
   AssetImportConfigList.clear();
   
   ImportAssetWindow.reloadImportOptionConfigs();
   setupImportConfigSettingsList();
   
   for(%i=0; %i < ImportAssetWindow.importConfigsList.count(); %i++)
   {
      %configName = ImportAssetWindow.importConfigsList.getKey(%i);  
      AssetImportConfigList.addRow(%i, %configName);
   }
   
   if(ESettingsWindow.isAwake())
      ESettingsWindow.refresh();
      
   if(AssetImportCtrl.isAwake())
      ImportAssetConfigList.setSelected(0);
}

function AssetImportConfigEditor::apply(%this)
{
   AssetImportSettings.write();
}

function AssetImportConfigList::onSelect( %this, %id, %text )
{
   ImportOptionsConfigList.clearFields();
   ImportOptionsConfigList.setAutoUpdate(false); //we don't want to be updating every time we add a field in here
   
   %this.currentConfig = %text;
   
   %this.populateConfigListByGroup("General");
   %this.populateConfigListByGroup("Meshes");
   %this.populateConfigListByGroup("Materials");
   %this.populateConfigListByGroup("Animations");
   %this.populateConfigListByGroup("Images");
   %this.populateConfigListByGroup("Collision");
   %this.populateConfigListByGroup("Sound");
   
   ImportOptionsConfigList.update();  
}

function AssetImportConfigList::populateConfigListByGroup(%this, %groupName)
{
   AssetImportConfigEditorInspector.startGroup(%groupName);
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
         AssetImportConfigEditorInspector.addSettingsField(%settingName, %labelName, %type, %tooltip, %defaultValue, %dataValues);
      }
   }
   AssetImportConfigEditorInspector.endGroup();
}

function AssetImportConfigEditorInspector::addSettingsField(%this, %settingsFieldName, %labelText, %fieldType, %tooltip, %fieldValue, %fieldData)
{
   %moddedSettingsFieldName = strreplace(%settingsFieldName, "/", "-");
   
   %configGroup = AssetImportConfigList.currentConfig;
   
   %value = AssetImportSettings.value(%configGroup @ "/" @ %settingsFieldName);
   if(%value $= "")
      %value = %fieldValue;
      
   //%this.addCallbackField(%moddedSettingsFieldName, %labelText, %fieldType, "", %value, %fieldData, %this @ ".changeEditorSetting");
   %this.addCallbackField(%moddedSettingsFieldName, %labelText, %fieldType, "", %value, %fieldData, "changeEditorSetting");
}

function AssetImportConfigEditorInspector::changeEditorSetting(%this, %varName, %value)
{
   %varName = strreplace(%varName, "-", "/");
   
   echo("Set " @ %varName @ " to be " @ %value);  
   
   %configGroup = AssetImportConfigList.currentConfig;
   
   %oldValue = AssetImportSettings.value(%configGroup @ "/" @ %varName, %value);
   
   AssetImportSettings.setValue(%configGroup @ "/" @ %varName, %value);
   
   if(%oldValue !$= %value)
   {
      %scollPos = ImportAssetConfigEditorScroll.getScrollPosition();
      ImportAssetConfigEditorWindow.populateConfigList(ImportAssetWindow.activeImportConfig); 
      ImportAssetConfigEditorScroll.setScrollPosition(%scollPos.x, %scollPos.y);
   }
}

function AssetImportConfigEditorInspector::setDefaultValuesByGroup(%this, %groupName)
{
   %configList = ImportAssetConfigSettingsList;
   
   for(%i=0; %i < %configList.count(); %i++)
   {
      %settingName = getField(%configList.getKey(%i),0);
      if(startsWith(%settingName, %groupName @ "/"))
      {
         %defaultValue = getField(%configList.getValue(%i), 0);
         AssetImportSettings.setValue(%settingName, %defaultValue);
      }
   }
}

function AssetImportConfigEditorInspector::ToggleImportMesh(%this, %fieldName, %newValue, %ownerObject)
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

function AssetImportConfigEditor::addNewConfig(%this)
{
   //Ensure our list is set up
   setupImportConfigSettingsList();
   
   ImportAssetNewConfigEditorWindow.setVisible(1);
   ImportAssetNewConfigEditorWindow.selectWindow();
}

function AssetImportConfigEditor::createNewImportConfig(%this)
{
   %configName = AssetImportNewConfigName.getText();
   %configList = ImportAssetConfigSettingsList;
   
   AssetImportSettings.beginGroup(%configName);
   
   AssetImportConfigEditorInspector.setDefaultValuesByGroup("General");
   AssetImportConfigEditorInspector.setDefaultValuesByGroup("Meshes");
   AssetImportConfigEditorInspector.setDefaultValuesByGroup("Materials");
   AssetImportConfigEditorInspector.setDefaultValuesByGroup("Animations");
   AssetImportConfigEditorInspector.setDefaultValuesByGroup("Collision");
   AssetImportConfigEditorInspector.setDefaultValuesByGroup("Images");
   AssetImportConfigEditorInspector.setDefaultValuesByGroup("Sounds");
   
   AssetImportSettings.endGroup();
   
   %success = AssetImportSettings.write();
   
   ImportAssetNewConfigEditorWindow.setVisible(0);
   
   %this.refresh();
}

function AssetImportConfigEditor::deleteConfig(%this)
{
   %callback = "AssetImportConfigEditor.onDeleteConfig();";
   toolsMessageBoxOKCancel("Delete Import Config", "This will delete the " @ AssetImportConfigList.currentConfig @ " config. Continue?", %callback, "");
}

function AssetImportConfigEditor::onDeleteConfig(%this)
{
   %configGroup = AssetImportConfigList.currentConfig;
   
   AssetImportConfigEditorInspector.removeSettingsByGroup("General");
   AssetImportConfigEditorInspector.removeSettingsByGroup("Meshes");
   AssetImportConfigEditorInspector.removeSettingsByGroup("Materials");
   AssetImportConfigEditorInspector.removeSettingsByGroup("Animations");
   AssetImportConfigEditorInspector.removeSettingsByGroup("Collision");
   AssetImportConfigEditorInspector.removeSettingsByGroup("Images");
   AssetImportConfigEditorInspector.removeSettingsByGroup("Sounds");
}

function AssetImportConfigEditorInspector::removeSettingsByGroup(%this, %groupName)
{
   %configList = ImportAssetConfigSettingsList;
   
   %configGroup = AssetImportConfigList.currentConfig;
   
   for(%i=0; %i < %configList.count(); %i++)
   {
      %settingName = getField(%configList.getKey(%i),0);
      if(startsWith(%settingName, %groupName @ "/"))
      {
         %defaultValue = getField(%configList.getValue(%i), 0);
         
         %targetSetting = %configGroup @ "/" @ %settingName;
         
         AssetImportSettings.remove(%configGroup @ "/" @ %settingName);
      }
   }
   
   %success = AssetImportSettings.write();
   AssetImportConfigEditor.refresh();
}