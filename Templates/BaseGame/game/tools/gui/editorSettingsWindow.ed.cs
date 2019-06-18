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

function ESettingsWindow::startup( %this )
{
   new ArrayObject(EditorSettingsPageList);
   new ArrayObject(GameSettingsPageList);
   
   %this.addEditorSettingsPage("Axis", "Axis Gizmo");
   %this.addEditorSettingsPage("General", "General Settings");
   %this.addEditorSettingsPage("Camera", "Camera Settings");
   %this.addEditorSettingsPage("SceneEditor", "Scene Editor");
   %this.addEditorSettingsPage("ShapeEditor", "Shape Editor");
   %this.addEditorSettingsPage("NavEditor", "Navigation Editor");
   %this.addEditorSettingsPage("Theme", "Theme");
   
   %this.addGameSettingsPage("GameGeneral", "General");
   %this.addGameSettingsPage("Gameplay", "Gameplay");
   %this.addGameSettingsPage("Paths", "Paths");
   %this.addGameSettingsPage("UI", "UI");
   %this.addGameSettingsPage("LevelDefaults", "Level Defaults");
   %this.addGameSettingsPage("GameOptions", "Game Options");
   %this.addGameSettingsPage("AssetManagement", "Asset Management");
   
   %this.mode = "Editor";
}

function ESettingsWindow::onWake( %this )
{
   
}

function ESettingsWindow::hideDialog( %this )
{
   %this.setVisible(false);
}

function ESettingsWindow::ToggleVisibility()
{
   if ( ESettingsWindow.visible )
   {
      ESettingsWindow.setVisible(false);
   }
   else
   {
      ESettingsWindow.setVisible(true);
      ESettingsWindow.selectWindow();
      ESettingsWindow.setCollapseGroup(false);
      
      ESettingsWindowList.clear();
   }
   
   ESettingsWindowList.setSelectedById( 1 );
}

function ESettingsWindow::toggleProjectSettings(%this)
{
   %this.ToggleVisibility();
   
   %count = GameSettingsPageList.count();
   for(%i=0; %i < %count; %i++)
   {
      %settingsPageText = GameSettingsPageList.getValue(%i);
      ESettingsWindowList.addRow( %i, %settingsPageText );
   }
   ESettingsWindowList.sort(0);
   
   %this.mode = "Project";
   ESettingsWindow.text = "Game Project Settings";
   
   ESettingsWindowList.setSelectedById( 1 );
}

function ESettingsWindow::toggleEditorSettings(%this)
{
   %this.ToggleVisibility();
   
   %count = EditorSettingsPageList.count();
   for(%i=0; %i < %count; %i++)
   {
      %settingsPageText = EditorSettingsPageList.getValue(%i);
      ESettingsWindowList.addRow( %i, %settingsPageText );
   }
   ESettingsWindowList.sort(0);
   
   %this.mode = "Editor";
   ESettingsWindow.text = "Editor Settings";
   
   ESettingsWindowList.setSelectedById( 1 );
}

function ESettingsWindow::addEditorSettingsPage(%this, %settingsPageName, %settingsPageText)
{
   EditorSettingsPageList.add(%settingsPageName, %settingsPageText);
}

function ESettingsWindow::addGameSettingsPage(%this, %settingsPageName, %settingsPageText)
{
   GameSettingsPageList.add(%settingsPageName, %settingsPageText);
}

//-----------------------------------------------------------------------------

function ESettingsWindowList::onSelect( %this, %id, %text )
{
   SettingsInspector.clearFields();
   
   if(ESettingsWindow.mode $= "Editor")
      %pageName = EditorSettingsPageList.getKey(EditorSettingsPageList.getIndexFromValue(%text));
   else
      %pageName = GameSettingsPageList.getKey(GameSettingsPageList.getIndexFromValue(%text));
      
   eval("ESettingsWindow.get" @ %pageName @ "Settings();");
}

//Read/write field functions
function SettingsInspector::addSettingsField(%this, %settingsFieldName, %labelText, %fieldType, %tooltip, %fieldData)
{
   %moddedSettingsFieldName = strreplace(%settingsFieldName, "/", "-");
   
   if(ESettingsWindow.mode $= "Editor")
      %this.addCallbackField(%moddedSettingsFieldName, %labelText, %fieldType, "", EditorSettings.value(%settingsFieldName), %fieldData, "changeEditorSetting");
   else
      %this.addCallbackField(%moddedSettingsFieldName, %labelText, %fieldType, "", ProjectSettings.value(%settingsFieldName), %fieldData, "changeEditorSetting");
}

function SettingsInspector::changeEditorSetting(%this, %varName, %value)
{
   %varName = strreplace(%varName, "-", "/");
   
   echo("Set " @ %varName @ " to be " @ %value);  
   
   if(ESettingsWindow.mode $= "Editor")
      EditorSettings.setValue(%varName, %value);
   else
      ProjectSettings.setValue(%varName, %value);
   
   //%id = ESettingsWindowList.getSelectedRow();
   //ESettingsWindowList.setSelectedRow(%id);
   
   if(ESettingsWindow.mode $= "Editor")
      %success = EditorSettings.write();
   else
      %success = ProjectSettings.write();
}

function GuiInspectorVariableGroup::buildOptionsSettingField(%this, %fieldName, %fieldLabel, %fieldDesc, %fieldDefaultVal, %fieldDataVals, %ownerObj)
{
   %extent = 200;
   
   %fieldCtrl = %this.createInspectorField();
   
   %fieldCtrl.setHeightOverride(true, 200);
   
   %extent = %this.stack.getExtent();
   
   %width = mRound(%extent/2);
   %height = 20;
   %inset = 10;
   
   %editControl = new GuiPopUpMenuCtrl() {
      class = "guiInspectorListField";
      maxPopupHeight = "200";
      sbUsesNAColor = "0";
      reverseTextList = "0";
      bitmapBounds = "16 16";
      maxLength = "1024";
      Margin = "0 0 0 0";
      Padding = "0 0 0 0";
      AnchorTop = "1";
      AnchorBottom = "0";
      AnchorLeft = "1";
      AnchorRight = "0";
      isContainer = "0";
      Profile = "ToolsGuiPopUpMenuProfile";
      HorizSizing = "right";
      VertSizing = "bottom";
      Position = %fieldCtrl.edit.position;
      Extent = %fieldCtrl.edit.extent;
      MinExtent = "8 2";
      canSave = "1";
      Visible = "1";
      tooltipprofile = "ToolsGuiToolTipProfile";
      tooltip = %tooltip;
      text = %fieldDefaultVal;
      hovertime = "1000";
      ownerObject = %ownerObj;
      fieldName = %fieldName;
   };
   
   //set the field value
   if(getSubStr(%this.fieldName, 0, 1) $= "$")
   {
      if(%fieldName $= "")
         %editControl.setText(%fieldName);
   }
   else
   {
      //regular variable
      %setCommand = %editControl @ ".setText(" @ %ownerObj @ "." @ %fieldName @ ");";
      eval(%setCommand);
   }
   
   %listCount = getTokenCount(%fieldDataVals, ",");
   
   for(%i=0; %i < %listCount; %i++)
   {
      %entryText = getToken(%fieldDataVals, ",", %i);
      %editControl.add(%entryText); 
   }

   %fieldCtrl.setCaption(%fieldLabel);
   %fieldCtrl.setEditControl(%editControl);

   %this.addInspectorField(%fieldCtrl);
}

//
// COMMON EDITOR SETTINGS
//
function ESettingsWindow::getAxisSettings(%this)
{
   SettingsInspector.startGroup("Gizmo");
   SettingsInspector.addSettingsField("AxisGizmo/mouseRotateScalar", "Rotate Scalar", "float", "");
   SettingsInspector.addSettingsField("AxisGizmo/mouseScaleScalar", "Scale Scalar", "float", "");
   SettingsInspector.addSettingsField("AxisGizmo/renderWhenUsed", "Render When Manipulated", "bool", "");
   SettingsInspector.addSettingsField("AxisGizmo/renderInfoText", "Render Tool Text", "bool", "");
   SettingsInspector.endGroup();
   
   SettingsInspector.startGroup("Grid");
   SettingsInspector.addSettingsField("AxisGizmo/Grid/renderPlane", "Render Plane", "bool", "");
   SettingsInspector.addSettingsField("AxisGizmo/Grid/renderPlaneHashes", "Render Plane Hashes", "bool", "");
   SettingsInspector.addSettingsField("AxisGizmo/Grid/planeDim", "Plane Size", "float", "");
   SettingsInspector.addSettingsField("AxisGizmo/Grid/gridColor", "Plane Color", "colorI", "");
   SettingsInspector.endGroup();
}  

function ESettingsWindow::getGeneralSettings(%this)
{
   SettingsInspector.startGroup("Paths");
   SettingsInspector.addSettingsField("WorldEditor/newLevelFile", "New Level", "filename", "");
   SettingsInspector.addSettingsField("WorldEditor/torsionPath", "Torsion Path", "filename", "");
   SettingsInspector.endGroup();
   
   SettingsInspector.startGroup("Theme");
   SettingsInspector.addSettingsField("WorldEditor/Theme/backgroundColor", "Background Color", "colorI", "");
   SettingsInspector.addSettingsField("WorldEditor/Theme/windowTitleBGColor", "Window Title Color", "colorI", "");
   SettingsInspector.addSettingsField("WorldEditor/Theme/windowTitleFontColor", "Window Title Text Color", "colorI", "");
   SettingsInspector.addSettingsField("WorldEditor/Theme/mainTextColor", "Main Text Color", "colorI", "");
   SettingsInspector.endGroup();
}  

function ESettingsWindow::getCameraSettings(%this)
{
   SettingsInspector.startGroup("Mouse Control");
   SettingsInspector.addSettingsField("Camera/invertYAxis", "Invert Y Axis", "bool", "");
   SettingsInspector.addSettingsField("Camera/invertXAxis", "Invert X Axis", "bool", "");
   SettingsInspector.endGroup();
   
   //Based on currently loaded level(rootScene)
   SettingsInspector.startGroup(EditorSettings.value("WorldEditor/newLevelFile") @ " Camera");
   SettingsInspector.addSettingsField("WorldEditor/newLevelFile", "Camera Speed Min", "float", "");
   SettingsInspector.addSettingsField("WorldEditor/torsionPath", "Camera Speed Max", "200", "");
   SettingsInspector.endGroup();
}  

function ESettingsWindow::getNavEditorSettings(%this)
{
   SettingsInspector.startGroup("Test Spawn");
   SettingsInspector.addSettingsField("WorldEditor/newLevelFile", "Spawn Class", "list", "", "AIPlayer");
   SettingsInspector.addSettingsField("WorldEditor/torsionPath", "Datablock", "string", "");
   SettingsInspector.endGroup();
   
   SettingsInspector.startGroup("Colors");
   SettingsInspector.addSettingsField("WorldEditor/newLevelFile", "Hover Spline", "colorI", "");
   SettingsInspector.addSettingsField("WorldEditor/torsionPath", "Select Spline", "colorI", "");
   SettingsInspector.endGroup();
}

function ESettingsWindow::getSceneEditorSettings(%this)
{
   SettingsInspector.startGroup("Render");
   SettingsInspector.addSettingsField("WorldEditor/Render/renderObjHandle", "Object Icons", "bool", "");
   SettingsInspector.addSettingsField("WorldEditor/Render/renderObjText", "Object Text", "bool", "");
   SettingsInspector.addSettingsField("WorldEditor/Render/showMousePopupInfo", "Mouse Popup Info", "bool", "");
   SettingsInspector.addSettingsField("WorldEditor/Render/renderPopupBackground", "Popup Menu Background", "bool", "");
   SettingsInspector.endGroup();
   
   SettingsInspector.startGroup("Colors");
   SettingsInspector.addSettingsField("WorldEditor/Grid/gridColor", "Grid Major", "colorI", "");
   SettingsInspector.addSettingsField("WorldEditor/Grid/gridMinorColor", "Grid Minor", "colorI", "");
   SettingsInspector.addSettingsField("WorldEditor/Grid/gridOriginColor", "Grid Origin", "colorI", "");
   SettingsInspector.addSettingsField("WorldEditor/Color/dragRectColor", "Drag Rect", "colorI", "");
   SettingsInspector.addSettingsField("WorldEditor/Color/objectTextColor", "Object Text", "colorI", "");
   SettingsInspector.addSettingsField("WorldEditor/Color/popupTextColor", "Popup Text", "colorI", "");
   SettingsInspector.addSettingsField("WorldEditor/Color/popupBackgroundColor", "Popup Back", "colorI", "");
   SettingsInspector.endGroup();
   
   SettingsInspector.startGroup("Misc");
   SettingsInspector.addSettingsField("WorldEditor/forceLoadDAE", "Force Load DAE", "bool", "");
   SettingsInspector.addSettingsField("WorldEditor/Tools/dropAtScreenCenterScalar", "Screen Center Scalar", "float", "");
   SettingsInspector.addSettingsField("WorldEditor/Tools/dropAtScreenCenterMax", "Screen Center Max", "float", "");
   SettingsInspector.endGroup();
}

function ESettingsWindow::getShapeEditorSettings(%this)
{
   SettingsInspector.startGroup("Colors");
   SettingsInspector.addSettingsField("WorldEditor/newLevelFile", "Sun Diffuse", "colorI", "");
   SettingsInspector.addSettingsField("WorldEditor/newLevelFile", "Sun Ambient", "colorI", "");
   SettingsInspector.addSettingsField("WorldEditor/newLevelFile", "Background", "colorI", "");
   SettingsInspector.endGroup();
   
   SettingsInspector.startGroup("Grid");
   SettingsInspector.addSettingsField("WorldEditor/newLevelFile", "Grid Size", "float", "");
   SettingsInspector.addSettingsField("WorldEditor/newLevelFile", "Grid Dimension", "vector2", "");
   SettingsInspector.endGroup();
}

function ESettingsWindow::getThemeSettings(%this)
{
   SettingsInspector.startGroup("Colors");
   SettingsInspector.addSettingsField("Theme/headerColor", "Headerbar Color", "ColorI", "");
   SettingsInspector.addSettingsField("Theme/windowBackgroundColor", "Window Background Color", "ColorI", "");
   
   SettingsInspector.addSettingsField("Theme/tabsColor", "Tabs Color", "ColorI", "");
   SettingsInspector.addSettingsField("Theme/tabsHLColor", "Tabs Highlight Color", "ColorI", "");
   SettingsInspector.addSettingsField("Theme/tabsSELColor", "Tabs Selected Color", "ColorI", "");
   
   SettingsInspector.addSettingsField("Theme/dividerDarkColor", "Divider Dark Color", "ColorI", "");
   SettingsInspector.addSettingsField("Theme/dividerMidColor", "Divider Mid Color", "ColorI", "");
   SettingsInspector.addSettingsField("Theme/dividerLightColor", "Divider Light Color", "ColorI", "");
   
   SettingsInspector.addSettingsField("Theme/headerTextColor", "Header Text Color", "ColorI", "");
   
   SettingsInspector.addSettingsField("Theme/fieldTextColor", "Field Text Color", "ColorI", "");
   SettingsInspector.addSettingsField("Theme/fieldTextHLColor", "Field Text Highlight Color", "ColorI", "");
   SettingsInspector.addSettingsField("Theme/fieldTextSELColor", "Field Text Selected Color", "ColorI", "");
   
   SettingsInspector.addSettingsField("Theme/fieldBGColor", "Field Background Color", "ColorI", "");
   SettingsInspector.addSettingsField("Theme/fieldBGHLColor", "Field Background Highlight Color", "ColorI", "");
   SettingsInspector.addSettingsField("Theme/fieldBGSELColor", "Field Background Selected Color", "ColorI", "");
   
   SettingsInspector.addSettingsField("Theme/tooltipBGColor", "Tooltip Background Color", "ColorI", "");
   SettingsInspector.addSettingsField("Theme/tooltipTextColor", "Tooltip Text Highlight Color", "ColorI", "");
   SettingsInspector.addSettingsField("Theme/tooltipDivColor", "Tooltip Divider Color", "ColorI", "");
   SettingsInspector.endGroup();
} 
//
// COMMON GAME SETTINGS
//
function ESettingsWindow::getGameGeneralSettings(%this)
{
   SettingsInspector.startGroup("General");
   SettingsInspector.addSettingsField("General/ProjectName", "Project Name", "string", "");
   SettingsInspector.endGroup();
} 

function ESettingsWindow::getPathsSettings(%this)
{
   SettingsInspector.startGroup("Paths");
   SettingsInspector.addSettingsField("Paths/splashImagePath", "Splash Image", "filename", "");
   SettingsInspector.addSettingsField("Paths/iconImagePath", "Icon Image", "filename", "");
   SettingsInspector.addSettingsField("Paths/missingTexturePath", "Missing Texture Image", "filename", "");
   SettingsInspector.addSettingsField("Paths/noMaterialPath", "No Material Image", "filename", "");
   SettingsInspector.addSettingsField("Paths/errorMaterialMath", "Error Material Image", "filename", "");
   SettingsInspector.endGroup();
} 

function ESettingsWindow::getUISettings(%this)
{
   SettingsInspector.startGroup("UI");
   SettingsInspector.addSettingsField("UI/playGUIName", "Play GUI Name", "string", "");
   SettingsInspector.addSettingsField("UI/mainMenuName", "Main Menu GUI Name", "string", "");
   SettingsInspector.endGroup();
} 

function ESettingsWindow::getAssetManagementSettings(%this)
{
   SettingsInspector.startGroup("Modules");
   SettingsInspector.addSettingsField("AssetManagement/Modules/coreModulePath", "Core Module Path", "string", "");
   SettingsInspector.addSettingsField("AssetManagement/Modules/gameDataModulePath", "Game Data Module Path", "string", "");
   SettingsInspector.addSettingsField("AssetManagement/Modules/moduleExtension", "Module Extension", "string", "");
   SettingsInspector.endGroup();
   
   SettingsInspector.startGroup("Assets");
   SettingsInspector.addSettingsField("AssetManagement/Assets/assetExtension", "Asset Extension", "string", "");
   SettingsInspector.addSettingsField("AssetManagement/Assets/datablockCaching", "Cache Datablocks", "bool", "");
   //SettingsInspector.addSettingsField("AssetManagement/Assets/moduleExtension", "Module Extension", "string", "");
   SettingsInspector.endGroup();
} 

function ESettingsWindow::getGameplaySettings(%this)
{
   SettingsInspector.startGroup("Game Modes");
   SettingsInspector.addSettingsField("Gameplay/GameModes/defaultModeName", "Default Gamemode Name", "string", "");
   SettingsInspector.endGroup();
} 

function ESettingsWindow::getGameOptionsSettings(%this)
{
   SettingsInspector.startGroup("Options Settings");
   SettingsInspector.addSettingsField("Options/optionsList", "OptionsList", "OptionsSetting", "");
   SettingsInspector.endGroup();
} 