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
}

function ESettingsWindow::onWake( %this )
{
   new ArrayObject(SettingsPageList);
   %this.addSettingsPage("Axis", "Axis Gizmo");
   %this.addSettingsPage("General", "General Settings");
   %this.addSettingsPage("Camera", "Camera Settings");
   %this.addSettingsPage("SceneEditor", "Scene Editor");
   %this.addSettingsPage("ShapeEditor", "Shape Editor");
   %this.addSettingsPage("NavEditor", "Navigation Editor");
   
   ESettingsWindowList.setSelectedById( 1 );
}

function ESettingsWindow::hideDialog( %this )
{
   %this.setVisible(false);
}

function ESettingsWindow::ToggleVisibility()
{
   if ( ESettingsWindow.visible  )
   {
      ESettingsWindow.setVisible(false);
      EditorSettings.write();
   }
   else
   {
      ESettingsWindow.setVisible(true);
      ESettingsWindow.selectWindow();
      ESettingsWindow.setCollapseGroup(false);
   }
   
   ESettingsWindowList.setSelectedById( 1 );
}

/*function ESettingsWindow::addTabPage( %this, %page )
{
   ESettingsWindowTabBook.add( %page );
   ESettingsWindowList.addRow( ESettingsWindowTabBook.getSelectedPage(), %page.text );
   ESettingsWindowList.sort(0);
}*/

function ESettingsWindow::addSettingsPage(%this, %settingsPageName, %settingsPageText)
{
   SettingsPageList.add(%settingsPageName, %settingsPageText);
   
   ESettingsWindowList.addRow( SettingsPageList.count(), %settingsPageText );
   ESettingsWindowList.sort(0);
}

//-----------------------------------------------------------------------------

function ESettingsWindowList::onSelect( %this, %id, %text )
{
   SettingsInspector.clearFields();
   %pageName = SettingsPageList.getKey(SettingsPageList.getIndexFromValue(%text));
   eval("ESettingsWindow.get" @ %pageName @ "Settings();");
}

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

//Read/write field functions
function SettingsInspector::addSettingsField(%this, %settingsFieldName, %labelText, %fieldType, %tooltip, %fieldData)
{
   %moddedSettingsFieldName = strreplace(%settingsFieldName, "/", "-");
   %this.addCallbackField(%moddedSettingsFieldName, %labelText, %fieldType, "", EditorSettings.value(%settingsFieldName), %fieldData, "changeEditorSetting");
}

function SettingsInspector::changeEditorSetting(%this, %varName, %value)
{
   %varName = strreplace(%varName, "-", "/");
   
   echo("Set " @ %varName @ " to be " @ %value);  
   
   EditorSettings.setValue(%varName, %value);
   
   %id = ESettingsWindowList.getSelectedRow();
   ESettingsWindowList.setSelectedRow(%id);
}