//------------------------------------------------------------------------------
// Fields that will be saved to settings
$Assimp::textFields = "lodType" TAB "singleDetailSize" TAB "materialPrefix" TAB
   "alwaysImport" TAB "neverImport" TAB "alwaysImportMesh" TAB "neverImportMesh"
   TAB "upAxis" TAB "scale" TAB "animTiming" TAB "animFPS";

$Assimp::checkboxFields = "overrideUpAxis" TAB "overrideScale" TAB "ignoreNodeScale"
   TAB "adjustCenter" TAB "adjustFloor" TAB "forceUpdateMaterials" TAB "convertLeftHanded"
   TAB "calcTangentSpace" TAB "removeRedundantMats" TAB "genUVCoords" TAB
   "transformUVCoords" TAB "flipUVCoords" TAB "findInstances" TAB "limitBoneWeights"
   TAB "joinIdenticalVerts" TAB "reverseWindingOrder" TAB "invertNormals";
//------------------------------------------------------------------------------

function ShapeImportTreeView::refresh(%this, %what)
{
   %shapeRoot = %this.getFirstRootItem();
   %materialsRoot = %this.getNextSibling(%shapeRoot);
   %animRoot = %this.getNextSibling(%materialsRoot);

   // Refresh nodes
   if ((%what $= "all") || (%what $= "nodes"))
   {
      // Indicate whether nodes will be ignored on import
      %this._alwaysImport = strreplace(AssimpImportDlg-->alwaysImport.getText(), ";", "\t");
      %this._neverImport = strreplace(AssimpImportDlg-->neverImport.getText(), ";", "\t");
      %this._alwaysImportMesh = strreplace(AssimpImportDlg-->alwaysImportMesh.getText(), ";", "\t");
      %this._neverImportMesh = strreplace(AssimpImportDlg-->neverImportMesh.getText(), ";", "\t");
      %this.refreshNode(%this.getChild(%shapeRoot));
   }

   // Refresh materials
   if ((%what $= "all") || (%what $= "materials"))
   {
      %matPrefix = AssimpImportDlg-->materialPrefix.getText();
      %id = %this.getChild(%materialsRoot);
      while (%id > 0)
      {
         %baseName = %this.getItemValue(%id);
         %name = %matPrefix @ %baseName;

         // Indicate whether material name is already mapped
         %this.editItem(%id, %name, %baseName);
         %mapped = getMaterialMapping(%name);
         if (%mapped $= "")
         {
            %this.setItemTooltip(%id, "A new material will be mapped to this name");
            %this.setItemImages(%id, %this._imageMaterial, %this._imageMaterial);
         }
         else
         {
            %this.setItemTooltip(%id, %mapped SPC "is already mapped to this material name");
            %this.setItemImages(%id, %this._imageExMaterial, %this._imageExMaterial);
         }

         %id = %this.getNextSibling(%id);
      }
   }

   // Refresh animations
   if ((%what $= "all") || (%what $= "animations"))
   {
      %id = %this.getChild(%animRoot);
      while (%id > 0)
      {
         %this.setItemImages(%id, %this._imageAnim, %this._imageAnim);
         %id = %this.getNextSibling(%id);
      }
   }
}

function ShapeImportTreeView::refreshNode(%this, %id)
{
   while (%id > 0)
   {
      switch$ (%this.getItemValue(%id))
      {
         case "mesh":
            // Check if this mesh will be ignored on import
            if (strIsMatchMultipleExpr(%this._alwaysImportMesh, %this.getItemText(%id)) ||
               !strIsMatchMultipleExpr(%this._neverImportMesh, %this.getItemText(%id)) )
            {
               %this.setItemTooltip(%id, "");
               %this.setItemImages(%id, %this._imageMesh, %this._imageMesh);
            }
            else
            {
               %this.setItemTooltip(%id, "This mesh will be ignored on import");
               %this.setItemImages(%id, %this._imageExNode, %this._imageExNode);
            }

         case "light":
            %this.setItemImages(%id, %this._imageLight, %this._imageLight);

         case "node":
            // Check if this node will be ignored on import
            if (strIsMatchMultipleExpr(%this._alwaysImport, %this.getItemText(%id)) ||
               !strIsMatchMultipleExpr(%this._neverImport, %this.getItemText(%id)) )
            {
               %this.setItemTooltip(%id, "");
               %this.setItemImages(%id, %this._imageNode, %this._imageNode);
            }
            else
            {
               %this.setItemTooltip(%id, "This node will be ignored on import");
               %this.setItemImages(%id, %this._imageExNode, %this._imageExNode);
            }
      }

      // recurse through children and siblings
      %this.refreshNode(%this.getChild(%id));
      %id = %this.getNextSibling(%id);
   }
}

function ShapeImportTreeView::onDefineIcons(%this)
{
   // Set the tree view icon indices and texture paths
   %this._imageNone = 0;
   %this._imageNode = 1;
   %this._imageMesh = 2;
   %this._imageMaterial = 3;
   %this._imageLight = 4;
   %this._imageAnimation = 5;
   %this._imageExNode = 6;
   %this._imageExMaterial = 7;

   %icons = ":" @                                                    // no icon
            "tools/gui/images/ColladaImport/iconNode:" @             // normal node
            "tools/gui/images/ColladaImport/iconMesh:" @             // mesh
            "tools/gui/images/ColladaImport/iconMaterial:" @         // new material
            "tools/gui/images/ColladaImport/iconLight:" @            // light
            "tools/gui/images/ColladaImport/iconAnimation:" @        // sequence
            "tools/gui/images/ColladaImport/iconIgnoreNode:" @       // ignored node
            "tools/gui/images/ColladaImport/iconExistingMaterial";   // existing material

   %this.buildIconTable( %icons );
}

function AssimpImportDlg::updateOverrideUpAxis(%this, %override)
{
   %this-->overrideUpAxis.setStateOn(%override);
   %this-->upAxis.setActive(%override);
   if (!%override)
      %this-->upAxis.setText(ShapeImportTreeView._upAxis);
}

function AssimpImportDlg::updateOverrideScale(%this, %override)
{
   %this-->overrideScale.setStateOn(%override);
   %this-->scale.setActive(%override);
   if (!%override)
      %this-->scale.setText(ShapeImportTreeView._unit);
}

function AssimpImportDlg::initFromConstructor(%this)
{
   if (%this.constructor.upAxis !$= "DEFAULT")
   {
      %this-->upAxis.setText(%this.constructor.upAxis);
      %this.updateOverrideUpAxis(true);
   }
   else
      %this.updateOverrideUpAxis(false);

   if (%this.constructor.unit > 0)
   {
      %this-->scale.setText(%this.constructor.unit);
      %this.updateOverrideScale(true);
   }
   else
      %this.updateOverrideScale(false);

   %this-->lodType.setText(%this.constructor.lodType);
   %this-->singleDetailSize.setText(%this.constructor.singleDetailSize);
   %this-->materialPrefix.setText(%this.constructor.matNamePrefix);
   %this-->alwaysImport.setText(strreplace(%this.constructor.alwaysImport, "\t", ";"));
   %this-->neverImport.setText(strreplace(%this.constructor.neverImport, "\t", ";"));
   %this-->alwaysImportMesh.setText(strreplace(%this.constructor.alwaysImportMesh, "\t", ";"));
   %this-->neverImportMesh.setText(strreplace(%this.constructor.neverImportMesh, "\t", ";"));
   %this-->ignoreNodeScale.setStateOn(%this.constructor.ignoreNodeScale);
   %this-->adjustCenter.setStateOn(%this.constructor.adjustCenter);
   %this-->adjustFloor.setStateOn(%this.constructor.adjustFloor);
   %this-->forceUpdateMaterials.setStateOn(%this.constructor.forceUpdateMaterials);

   %this-->animTiming.setText(%this.constructor.animTiming);
   %this-->animFPS.setText(%this.constructor.animFPS);

   %this-->convertLeftHanded.setStateOn(%this.constructor.convertLeftHanded);
   %this-->calcTangentSpace.setStateOn(%this.constructor.calcTangentSpace);
   %this-->genUVCoords.setStateOn(%this.constructor.genUVCoords);
   %this-->transformUVCoords.setStateOn(%this.constructor.transformUVCoords);
   %this-->flipUVCoords.setStateOn(%this.constructor.flipUVCoords);
   %this-->findInstances.setStateOn(%this.constructor.findInstances);
   %this-->limitBoneWeights.setStateOn(%this.constructor.limitBoneWeights);
   %this-->joinIdenticalVerts.setStateOn(%this.constructor.joinIdenticalVerts);
   %this-->reverseWindingOrder.setStateOn(%this.constructor.reverseWindingOrder);
   %this-->invertNormals.setStateOn(%this.constructor.invertNormals);
   %this-->removeRedundantMats.setStateOn(%this.constructor.removeRedundantMats);
}

function AssimpImportDlg::initFromDefaults(%this)
{
   %this.updateOverrideUpAxis(false);
   %this.updateOverrideScale(false);

   %this-->lodType.setText("TrailingNumber");
   %this-->singleDetailSize.setText("2");
   %this-->materialPrefix.setText("");
   %this-->alwaysImport.setText("");
   %this-->neverImport.setText("");
   %this-->alwaysImportMesh.setText("");
   %this-->neverImportMesh.setText("");
   %this-->ignoreNodeScale.setStateOn(0);
   %this-->adjustCenter.setStateOn(0);
   %this-->adjustFloor.setStateOn(0);
   %this-->forceUpdateMaterials.setStateOn(0);

   %this-->animTiming.setText("Seconds");
   %this-->animFPS.setText("30");

   %this-->convertLeftHanded.setStateOn(0);
   %this-->calcTangentSpace.setStateOn(0);
   %this-->genUVCoords.setStateOn(0);
   %this-->transformUVCoords.setStateOn(0);
   %this-->flipUVCoords.setStateOn(1);
   %this-->findInstances.setStateOn(0);
   %this-->limitBoneWeights.setStateOn(0);
   %this-->joinIdenticalVerts.setStateOn(1);
   %this-->reverseWindingOrder.setStateOn(1);
   %this-->invertNormals.setStateOn(0);
   %this-->removeRedundantMats.setStateOn(1);
}

function AssimpImportDlg::saveToConstructor(%this)
{
   // Store values from GUI
   if (%this-->overrideUpAxis.getValue())
      %this.constructor.upAxis = %this-->upAxis.getText();
   else
      %this.constructor.upAxis = "DEFAULT";

   if (%this-->overrideScale.getValue())
      %this.constructor.unit = %this-->scale.getText();
   else
      %this.constructor.unit = -1;

   %this.constructor.lodType = %this-->lodType.getText();
   %this.constructor.singleDetailSize = %this-->singleDetailSize.getText();
   %this.constructor.matNamePrefix = %this-->materialPrefix.getText();
   %this.constructor.alwaysImport = strreplace(%this-->alwaysImport.getText(), ";", "\t");
   %this.constructor.neverImport = strreplace(%this-->neverImport.getText(), ";", "\t");
   %this.constructor.alwaysImportMesh = strreplace(%this-->alwaysImportMesh.getText(), ";", "\t");
   %this.constructor.neverImportMesh = strreplace(%this-->neverImportMesh.getText(), ";", "\t");
   %this.constructor.ignoreNodeScale = %this-->ignoreNodeScale.getValue();
   %this.constructor.adjustCenter = %this-->adjustCenter.getValue();
   %this.constructor.adjustFloor = %this-->adjustFloor.getValue();
   %this.constructor.forceUpdateMaterials = %this-->forceUpdateMaterials.getValue();

   %this.constructor.animTiming = %this-->animTiming.getText();
   %this.constructor.animFPS = %this-->animFPS.getText();

   %this.constructor.convertLeftHanded = %this-->convertLeftHanded.getValue();
   %this.constructor.calcTangentSpace = %this-->calcTangentSpace.getValue();
   %this.constructor.genUVCoords = %this-->genUVCoords.getValue();
   %this.constructor.transformUVCoords = %this-->transformUVCoords.getValue();
   %this.constructor.flipUVCoords = %this-->flipUVCoords.getValue();
   %this.constructor.findInstances = %this-->findInstances.getValue();
   %this.constructor.limitBoneWeights = %this-->limitBoneWeights.getValue();
   %this.constructor.joinIdenticalVerts = %this-->joinIdenticalVerts.getValue();
   %this.constructor.reverseWindingOrder = %this-->reverseWindingOrder.getValue();
   %this.constructor.invertNormals = %this-->invertNormals.getValue();
   %this.constructor.removeRedundantMats = %this-->removeRedundantMats.getValue();
}

function AssimpImportDlg::showDialog(%this, %shapePath, %cmd)
{
   %this.settingVersion = 1.0;
   %this.path = %shapePath;
   %this.cmd = %cmd;

   // Check for an existing TSShapeConstructor object. Need to exec the script
   // manually as the resource may not have been loaded yet
   %csPath = filePath(%this.path) @ "/" @ fileBase(%this.path) @ ".cs";
   if (isFile(%csPath))
      exec(%csPath);

   %this.constructor = ShapeEditor.findConstructor(%this.path);

   // Only show the import dialog if required. Note that 'GetShapeInfo' will
   // fail if the source file is missing, or a cached.dts is available.
   $assimp::forceLoad = EditorSettings.value("forceLoadDAE");
   if (!GetShapeInfo(%shapePath, "ShapeImportTreeView"))
   {
      eval(%cmd);
      $assimp::forceLoad = false;
      return;
   }
   $assimp::forceLoad = false;

   // Initialise GUI
   ShapeImportTreeView.onDefineIcons();

   // Window Title
   %this-->window.text = "Shape Import:" SPC %this.path;

   // Fill Popups
   %this-->upAxis.clear();
   %this-->upAxis.add("X_AXIS", 1);
   %this-->upAxis.add("Y_AXIS", 2);
   %this-->upAxis.add("Z_AXIS", 3);

   %this-->lodType.clear();
   %this-->lodType.add("DetectDTS", 1);
   %this-->lodType.add("SingleSize", 2);
   %this-->lodType.add("TrailingNumber", 3);

   %this-->animTiming.clear();
   %this-->animTiming.add("Frames", 0);
   %this-->animTiming.add("Seconds", 1);
   %this-->animTiming.add("Milliseconds", 1000);

   // Set model details
   %this-->nodes.setText(ShapeImportTreeView._nodeCount);
   %this-->meshes.setText(ShapeImportTreeView._meshCount);
   %this-->lights.setText(ShapeImportTreeView._lightCount);
   %this-->materials.setText(ShapeImportTreeView._materialCount);
   %this-->polygons.setText(ShapeImportTreeView._polygonCount);
   %this-->animations.setText(ShapeImportTreeView._animCount);
   %this-->textures.setText(ShapeImportTreeView._textureCount);
   %this-->vertices.setText(ShapeImportTreeView._vertCount);
   %metaText = (ShapeImportTreeView._metaTagCount == 0) ? "No Records" : ShapeImportTreeView._metaTagCount;
   %this-->metadata.setText(%metaText);

   if (%this.constructor > 0)
      %this.initFromConstructor();
   else
   {
      %this.initFromDefaults();

      // If there's a default settings file for the file type, load it
      %defaultSISPath = EditorSettings.value("defaultSettingsPath", "Tools");
      %settingsFile = %defaultSISPath @ "/" @ getSubStr(fileExt(%shapePath),1) @ ".sis";
      if (isFile(%settingsFile))
         %this.loadSettingsFrom(%settingsFile);
   }

   Canvas.pushDialog(%this);

   ShapeImportTreeView.refresh("all");
}

function AssimpImportDlg::onLoadSettings(%this)
{
   %defaultSISPath = EditorSettings.value("defaultSettingsPath", "Tools");
   %dlg = new OpenFileDialog()
   {
      Filters        = "Shape Import Settings (*.sis)|*.sis|";
      DefaultPath    = %defaultSISPath;
      DefaultFile    = "";
      ChangePath     = false;
      MustExist      = true;
   };
            
   %ret = %dlg.Execute();
   if ( %ret )
      %fileName = %dlg.FileName;
      
   %dlg.delete();
   if ( !%ret )
      return; 

   %this.loadSettingsFrom(%fileName);
}

function AssimpImportDlg::onSaveSettings(%this)
{
   %defaultSISPath = EditorSettings.value("defaultSettingsPath", "Tools");
   %dlg = new SaveFileDialog()
   {
      Filters        = "Shape Import Settings (*.sis)|*.sis|";
      DefaultPath    = %defaultSISPath;
      DefaultFile    = "";
      ChangePath     = false;
      MustExist      = true;
   };
         
   %ret = %dlg.Execute();
   if ( %ret )
   {
      %saveFile = %dlg.FileName;
      if(fileExt( %saveFile ) !$= ".sis")
         %saveFile = %saveFile @ ".sis";
   }
   
   %dlg.delete();
   
   if (!%ret)
      return;

   %this.saveSettingsTo(%saveFile);
}

function AssimpImportDlg::onCancel(%this)
{
   Canvas.popDialog(%this);
   ShapeImportTreeView.clear();
}

function AssimpImportDlg::onOK(%this)
{
   Canvas.popDialog(%this);
   ShapeImportTreeView.clear();

   if (%this.needsSave())
   {
      if (!isObject(%this.constructor))
      {  // Create a new TSShapeConstructor object
         %this.constructor = ShapeEditor.createConstructor(%this.path);
      }
   }
   
   if (%this.constructor > 0)
   {
      %this.saveToConstructor();
      // Save new settings to file
      ShapeEditor.saveConstructor(%this.constructor);
   }

   // Load the shape (always from the DAE)
   $assimp::forceLoad = true;
   eval(%this.cmd);
   $assimp::forceLoad = false;
}

function AssimpImportDlg::needsSave(%this)
{
   if ((%this-->overrideUpAxis.getValue() != 0)      ||
      (%this-->overrideScale.getValue() != 0)        ||
      (%this-->lodType.getText() !$= "DetectDTS")    ||
      (%this-->singleDetailSize.getText() !$= "2")   ||
      (%this-->materialPrefix.getText() !$= "")      ||
      (%this-->alwaysImport.getText() !$= "")        ||
      (%this-->neverImport.getText() !$= "")         ||
      (%this-->alwaysImportMesh.getText() !$= "")    ||
      (%this-->neverImportMesh.getText() !$= "")     ||
      (%this-->ignoreNodeScale.getValue() != 0)      ||
      (%this-->adjustCenter.getValue() != 0)         ||
      (%this-->adjustFloor.getValue() != 0)          ||
      (%this-->forceUpdateMaterials.getValue() != 0))
      return true;

   if ((%this-->animTiming.getText() !$= "Seconds")  ||
      (%this-->animFPS.getText() !$= "30")           ||
      (%this-->convertLeftHanded.getValue() != 0)    ||
      (%this-->calcTangentSpace.getValue() != 0)     ||
      (%this-->genUVCoords.getValue() != 0)          ||
      (%this-->transformUVCoords.getValue() != 0)    ||
      (%this-->flipUVCoords.getValue() != 1)         ||
      (%this-->findInstances.getValue() != 0)        ||
      (%this-->limitBoneWeights.getValue() != 0)     ||
      (%this-->joinIdenticalVerts.getValue() != 1)   ||
      (%this-->reverseWindingOrder.getValue() != 1)  ||
      (%this-->invertNormals.getValue() != 0)        ||
      (%this-->removeRedundantMats.getValue() != 1))
      return true;

   return false;
}

function AssimpImportDlg::loadSettingsFrom(%this, %filename)
{
   %fileObj = new FileObject();
   if (!%fileObj.OpenForRead(%fileName))
   {
      error("Error opening file to write settings (" @ %fileName @ ").");
      %fileObj.delete();
      return;
   }

   %line = %fileObj.ReadLine();
   if (getSubStr(%line, 0, 4) !$= "SISV")
      return; // ? not sis file

   while( !%fileObj.isEOF() )
   {
      %line = %fileObj.ReadLine();
      %key = getField(%line, 0);
      %data = getFields(%line, 1);
      %ctrl = %this.findObjectByInternalName(%key, true);
      if (isObject(%ctrl))
      {
         %name = %ctrl.getClassName();
         if (%ctrl.getClassName() $= "GuiCheckBoxCtrl")
            %ctrl.setStateOn(%data);
         else
            %ctrl.setText(%data);
      }
   }

   %this.updateOverrideUpAxis(%this-->overrideUpAxis.getValue());
   %this.updateOverrideScale(%this-->overrideScale.getValue());

   %fileObj.close();
   %fileObj.delete();
}

function AssimpImportDlg::saveSettingsTo(%this, %filename)
{
   %fileObj = new FileObject();
   if (!%fileObj.openForWrite(%fileName))
   {
      error("Error opening file to write settings (" @ %fileName @ ").");
      %fileObj.delete();
      return;
   }
   %fileObj.writeLine("SISV" @ %this.settingVersion);

   foreach$ (%key in $Assimp::textFields)
   {
      %ctrl = %this.findObjectByInternalName(%key, true);
      if (isObject(%ctrl))
      {
         %data = %ctrl.getText();
         %fileObj.writeLine(%key TAB %data);
      }
   }

   foreach$ (%key in $Assimp::checkboxFields)
   {
      %ctrl = %this.findObjectByInternalName(%key, true);
      if (isObject(%ctrl))
      {
         %data = %ctrl.getValue();
         %fileObj.writeLine(%key TAB %data);
      }
   }

   %fileObj.close();
   %fileObj.delete();
}