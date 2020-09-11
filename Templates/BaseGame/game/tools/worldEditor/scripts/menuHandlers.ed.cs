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

$Pref::WorldEditor::FileSpec = "Torque Mission Files (*.mis)|*.mis|All Files (*.*)|*.*|";

//////////////////////////////////////////////////////////////////////////
// File Menu Handlers
//////////////////////////////////////////////////////////////////////////

function EditorFileMenu::onMenuSelect(%this)
{
   %this.enableItem(2, EditorIsDirty());
}

//////////////////////////////////////////////////////////////////////////

// Package that gets temporarily activated to toggle editor after mission loading.
// Deactivates itself.
package BootEditor {

function GameConnection::initialControlSet( %this )
{
   Parent::initialControlSet( %this );
   
   toggleEditor( true );
   deactivatePackage( "BootEditor" );
}

};

//////////////////////////////////////////////////////////////////////////

/// Checks the various dirty flags and returns true if the 
/// mission or other related resources need to be saved.  
function EditorIsDirty()
{
   // We kept a hard coded test here, but we could break these
   // into the registered tools if we wanted to.
   %isDirty =  ( isObject( "ETerrainEditor" ) && ( ETerrainEditor.isMissionDirty || ETerrainEditor.isDirty ) )
               || ( isObject( "EWorldEditor" ) && EWorldEditor.isDirty )
               || ( isObject( "ETerrainPersistMan" ) && ETerrainPersistMan.hasDirty() );
   
   // Give the editor plugins a chance to set the dirty flag.
   for ( %i = 0; %i < EditorPluginSet.getCount(); %i++ )
   {
      %obj = EditorPluginSet.getObject(%i);
      %isDirty |= %obj.isDirty(); 
   }
   
   return %isDirty;
}

/// Clears all the dirty state without saving.
function EditorClearDirty()
{
   EWorldEditor.isDirty = false;
   ETerrainEditor.isDirty = false;
   ETerrainEditor.isMissionDirty = false;
   ETerrainPersistMan.clearAll();
   
   for ( %i = 0; %i < EditorPluginSet.getCount(); %i++ )
   {
      %obj = EditorPluginSet.getObject(%i);
      %obj.clearDirty();      
   }
}

function EditorQuitGame()
{
   if( EditorIsDirty())
   {
      toolsMessageBoxYesNoCancel("Level Modified", "Would you like to save your changes before quitting?", "EditorSaveMissionMenu(); quit();", "quit();", "" );
   }
   else
      quit();
}

function EditorExitMission()
{  
   if( EditorIsDirty())
   {
      toolsMessageBoxYesNoCancel("Level Modified", "Would you like to save your changes before exiting?", "EditorDoExitMission(true);", "EditorDoExitMission(false);", "");
   }
   else
      EditorDoExitMission(false);
}

function EditorDoExitMission(%saveFirst)
{
   if(%saveFirst)
   {
      EditorSaveMissionMenu();
   }
   else
   {
      EditorClearDirty();
   }

   %mainMenuGUI = ProjectSettings.value("UI/mainMenuName");
   if (isObject( %mainMenuGUI ))
      Editor.close( %mainMenuGUI );

   disconnect();
}

function EditorOpenTorsionProject( %projectFile )
{
   // Make sure we have a valid path to the Torsion installation.
   
   %torsionPath = EditorSettings.value( "WorldEditor/torsionPath" );
   if( !isFile( %torsionPath ) )
   {
      toolsMessageBoxOK(
         "Torsion Not Found",
         "Torsion not found at '" @ %torsionPath @ "'.  Please set the correct path in the Editor Settings."
      );
      return;
   }
   
   // Determine the path to the .torsion file.
   
   if( %projectFile $= "" )
   {
      %projectName = fileBase( getExecutableName() );
      %projectFile = makeFullPath( %projectName @ ".torsion" );
      if( !isFile( %projectFile ) )
      {
         %projectFile = findFirstFile( "*.torsion", false );
         if( !isFile( %projectFile ) )
         {
            toolsMessageBoxOK(
               "Project File Not Found",
               "Cannot find .torsion project file in '" @ getMainDotCsDir() @ "'."
            );
            return;
         }
      }
   }
   
   // Open the project in Torsion.
   
   shellExecute( %torsionPath, "\"" @ %projectFile @ "\"" );
}

function EditorOpenFileInTorsion( %file, %line )
{
   // Make sure we have a valid path to the Torsion installation.
   
   %torsionPath = EditorSettings.value( "WorldEditor/torsionPath" );
   if( !isFile( %torsionPath ) )
   {
      toolsMessageBoxOK(
         "Torsion Not Found",
         "Torsion not found at '" @ %torsionPath @ "'.  Please set the correct path in the Editor Settings."
      );
      return;
   }
   
   // If no file was specified, take the current mission file.
   
   if( %file $= "" )
      %file = makeFullPath( $Server::MissionFile );
  
   // Open the file in Torsion.
   
   %args = "\"" @ %file;
   if( %line !$= "" )
      %args = %args @ ":" @ %line;
   %args = %args @ "\"";
   
   shellExecute( %torsionPath, %args );
}

function EditorOpenDeclarationInTorsion( %object )
{
   %fileName = %object.getFileName();
   if( %fileName $= "" )
      return;
      
   EditorOpenFileInTorsion( makeFullPath( %fileName ), %object.getDeclarationLine() );
}

function EditorNewLevel( %level )
{
   %saveFirst = false;
   if ( EditorIsDirty() )
   {
      error(knob);
      %saveFirst = toolsMessageBox("Mission Modified", "Would you like to save changes to the current mission \"" @
         $Server::MissionFile @ "\" before creating a new mission?", "SaveDontSave", "Question") == $MROk;
   }
      
   if(%saveFirst)
      EditorSaveMission();

   // Clear dirty flags first to avoid duplicate dialog box from EditorOpenMission()
   if( isObject( Editor ) )
   {
      EditorClearDirty();
      Editor.getUndoManager().clearAll();
   }

   if( %level $= "" )
   {
      %level = "ToolsModule:DefaultEditorLevel";
   }

   if( !$missionRunning )
   {
      activatePackage( "BootEditor" );
      StartGame( %level );
   }
   else
      EditorOpenMission(%level);

   //EWorldEditor.isDirty = true;
   //ETerrainEditor.isDirty = true;
   EditorGui.saveAs = true;
}

function EditorSaveAsDefaultLevel()
{
   toolsMessageBoxYesNo("Save as Default?", "This will save the currently active root scene as the default level the editor loads when it is opened. Continue?",
      "doEditorSaveAsDefaultLevel();", "");
}

function doEditorSaveAsDefaultLevel()
{
   %success = getScene(0).save("tools/levels/DefaultEditorLevel.mis");
}

function EditorResetDefaultLevel()
{
   toolsMessageBoxYesNo("Reset Default?", "This will reset the default level for the editor back to the original. Continue?",
      "doEditorResetDefaultLevel();", "");
}

function doEditorResetDefaultLevel()
{
   %templatePath = makeFullPath("tools/levels/EditorTemplateLevel.mis");
   %defaultPath = makeFullPath("tools/levels/DefaultEditorLevel.mis");
   
   %fileCopy = -1;
   if(isFile(%templatePath) && isFile(%defaultPath))
      %fileCopy = pathCopy(%templatePath, %defaultPath, false);
}

function EditorSaveMissionMenu()
{
   if(EditorGui.saveAs)
      AssetBrowser.setupCreateNewAsset("LevelAsset", AssetBrowser.selectedModule, "EditorSaveMissionAs");
   else
      EditorSaveMission();
}

function EditorSaveMission()
{
   // just save the mission without renaming it
   
   // first check for dirty and read-only files:
   if((EWorldEditor.isDirty || ETerrainEditor.isMissionDirty) && !isWriteableFileName($Server::MissionFile))
   {
      toolsMessageBox("Error", "Mission file \""@ $Server::MissionFile @ "\" is read-only.  Continue?", "Ok", "Stop");
      return false;
   }
   if(ETerrainEditor.isDirty)
   {
      // Find all of the terrain files
      initContainerTypeSearch($TypeMasks::TerrainObjectType);

      while ((%terrainObject = containerSearchNext()) != 0)
      {
         if (!isWriteableFileName(%terrainObject.terrainFile))
         {
            if (toolsMessageBox("Error", "Terrain file \""@ %terrainObject.terrainFile @ "\" is read-only.  Continue?", "Ok", "Stop") == $MROk)
               continue;
            else
               return false;
         }
      }
   }
  
   // now write the terrain and mission files out:

   if(EWorldEditor.isDirty || ETerrainEditor.isMissionDirty)
      getScene(0).save($Server::MissionFile);
   if(ETerrainEditor.isDirty)
   {
      // Find all of the terrain files
      initContainerTypeSearch($TypeMasks::TerrainObjectType);

      while ((%terrainObject = containerSearchNext()) != 0)
      {
         if(%terrainObject.terrainAsset !$= "")
         {
            //we utilize a terrain asset, so we'll update our dependencies while we're at it
            %terrainObject.saveAsset();
         }
         else
         {
            %terrainObject.save(%terrainObject.terrainFile);
         }
      }
   }

   ETerrainPersistMan.saveDirty();
      
   // Give EditorPlugins a chance to save.
   for ( %i = 0; %i < EditorPluginSet.getCount(); %i++ )
   {
      %obj = EditorPluginSet.getObject(%i);
      if ( %obj.isDirty() )
         %obj.onSaveMission( $Server::MissionFile );      
   } 
   
   //Save out the PostFX config
   PostFXManager::savePresetHandler( $Server::LevelAsset.getPostFXPresetPath() );
   
   EditorClearDirty();
   
   EditorGui.saveAs = false;
   
   return true;
}

function EditorSaveMissionAs( %levelAsset )
{
   // If we didn't get passed a new mission name then
   // prompt the user for one.
   if ( %levelAsset $= "" )
      return;
      
   %levelAssetDef = AssetDatabase.acquireAsset(%levelAsset);
   %assetType = AssetDatabase.getAssetType(%levelAsset);
      
   if(%assetType !$= "LevelAsset")
   {
      error("Somehow tried to save a non-level asset as a level? " @ %levelAsset);
      return;
   }
               
   %missionName = %levelAssetDef.getLevelPath();
               
   if( fileExt( %missionName ) !$= ".mis" )
      %missionName = %missionName @ ".mis";
      
   //Update to be our active
   $Server::MissionFile = %missionName;
   $Server::LevelAsset = %levelAssetDef;
   
   //Update the scene name to comply to the new level's name
   GetRootScene().name = %levelAssetDef.AssetName;
   
   //Do the save
   EditorSaveMission();
   
   //Last, we're going to load the level proper in the editor
   updateEditorRecentLevelsList(%levelAsset);
   
   //If we've opened a valid level, clear the saveAs tag as it's not really applicable now
   EditorGui.saveAs = false;
}

function EditorAutoSaveMission()
{
   // just save the mission without renaming it
   
   if($Editor::AutoSaveIndex $= "" || $Editor::AutoSaveIndex $= "5")
      $Editor::AutoSaveIndex = 1;
   else
      $Editor::AutoSaveIndex++;
      
   %autosaveFileName = "tools/autosave/" @ fileBase($Server::MissionFile) @ "_autosave" @ $Editor::AutoSaveIndex @ fileExt($Server::MissionFile);
   
   // first check for dirty and read-only files:
   if((EWorldEditor.isDirty || ETerrainEditor.isMissionDirty) && !isWriteableFileName(%autosaveFileName))
   {
      return false;
   }
   
   //TODO: Make Autosave work with terrains
   /*if(ETerrainEditor.isDirty)
   {
      // Find all of the terrain files
      initContainerTypeSearch($TypeMasks::TerrainObjectType);

      while ((%terrainObject = containerSearchNext()) != 0)
      {
         if (!isWriteableFileName(%terrainObject.terrainFile))
         {
            if (toolsMessageBox("Error", "Terrain file \""@ %terrainObject.terrainFile @ "\" is read-only.  Continue?", "Ok", "Stop") == $MROk)
               continue;
            else
               return false;
         }
      }
   }*/
  
   // now write the terrain and mission files out:

   if(EWorldEditor.isDirty || ETerrainEditor.isMissionDirty)
      getScene(0).save(%autosaveFileName);
      
   //TODO: Make Autosave work with terrains
   /*if(ETerrainEditor.isDirty)
   {
      // Find all of the terrain files
      initContainerTypeSearch($TypeMasks::TerrainObjectType);

      while ((%terrainObject = containerSearchNext()) != 0)
      {
         if(%terrainObject.terrainAsset !$= "")
         {
            //we utilize a terrain asset, so we'll update our dependencies while we're at it
            %terrainObject.saveAsset();
         }
         else
         {
            %terrainObject.save(%terrainObject.terrainFile);
         }
      }
   }

   ETerrainPersistMan.saveDirty();*/
      
   // Give EditorPlugins a chance to save.
   for ( %i = 0; %i < EditorPluginSet.getCount(); %i++ )
   {
      %obj = EditorPluginSet.getObject(%i);
      if ( %obj.isDirty() )
         %obj.onSaveMission( %autosaveFileName );      
   } 
   
   %autosaveInterval = EditorSettings.value("WorldEditor/AutosaveInterval", "5");
   %autosaveInterval = %autosaveInterval * 60000; //convert to milliseconds from minutes
   EditorGui.autosaveSchedule = schedule( %autosaveInterval, 0, "EditorAutoSaveMission" );
   
   return true;
}

function EditorOpenMission(%levelAsset)
{
   if( EditorIsDirty())
   {
      // "EditorSaveBeforeLoad();", "getLoadFilename(\"*.mis\", \"EditorDoLoadMission\");"
      if(toolsMessageBox("Mission Modified", "Would you like to save changes to the current mission \"" @
         $Server::MissionFile @ "\" before opening a new mission?", SaveDontSave, Question) == $MROk)
      {
         if(! EditorSaveMission())
            return;
      }
   }

   if(%levelAsset $= "")
   {
      AssetBrowser.showDialog("LevelAsset", "EditorOpenMission", "", "", "");
      return;
   }
   else
   {
      //If we got the actual assetdef, just roll with it
      %levelAssetId = "";
      if(isObject(%levelAsset))
      {
         %assetDef = %levelAsset;
         %levelAssetId = %assetDef.getAssetId();
      }
      else
      {
         //parse it out if its
         %assetDef = AssetDatabase.acquireAsset(%levelAsset);
         %levelAssetId = %levelAsset;
      }
      
      updateEditorRecentLevelsList(%levelAssetId);
      
      %filename = %assetDef.getLevelPath();
      
      if(%filename $= "")
      {
         error("Selected Level Asset doesn't have a valid levelFile path!");
         return;
      }
      
      //We cool, so dereference the def because we don't need it the rest of the way
      AssetDatabase.releaseAsset(%levelAssetId);
   }
      
   // close the current editor, it will get cleaned up by MissionCleanup
   if( isObject( "Editor" ) )
      Editor.close( LoadingGui );

   EditorClearDirty();

   // If we haven't yet connnected, create a server now.
   // Otherwise just load the mission.

   if( !$missionRunning )
   {
      activatePackage( "BootEditor" );
      StartGame( %levelAssetId );
   }
   else
   {
      loadMission( %levelAssetId, true ) ;
   
      pushInstantGroup();

      // recreate and open the editor
      Editor::create();
      MissionCleanup.add( Editor );
      MissionCleanup.add( Editor.getUndoManager() );
      EditorGui.loadingMission = true;
      Editor.open();
   
      popInstantGroup();
   }
   
   //If we've opened a valid level, clear the saveAs tag as it's not really applicable now
   EditorGui.saveAs = false;
}

function EditorOpenSceneAppend(%levelAsset)
{
   //Load the asset's level file
   exec(%levelAsset.getLevelPath());
   
   //We'll assume the scene name and assetname are the same for now
   %sceneName = %levelAsset.AssetName;
   %scene = nameToID(%sceneName);
   if(isObject(%scene))
   {
      //Append it to our scene heirarchy
      $scenesRootGroup.add(%scene);
   }
}

function MakeSelectionASublevel()
{
   /*%size = EWorldEditor.getSelectionSize();
   if ( %size == 0 )
      return;
      
   //Make a new Scene object
      
   for(%i=0; %i < %size; %i++)
   {
      
   }
   %a = EWorldEditor.getSelectedObject(0);
   %b = EWorldEditor.getSelectedObject(1);*/
}

function updateEditorRecentLevelsList(%levelAssetId)
{
   EditorSettings.setValue("WorldEditor/lastEditedLevel", %levelAssetId);
      
   //update the recent levels list
   %recentLevels = EditorSettings.value("WorldEditor/recentLevelsList");
   %recentCount = getTokenCount(%recentLevels, ",");
   
   %updatedRecentList = %levelAssetId;
   
   %updatedRecentCount = 1;
   for(%i=0; %i < %recentCount; %i++)
   {
      %recentEntry = getToken(%recentLevels, ",", %i);
      
      if(%levelAssetId $= %recentEntry)
         continue;
      
      %updatedRecentList = %updatedRecentList @ "," @ %recentEntry;
      
      %updatedRecentCount++;
      
      if(%updatedRecentCount == 10)
         break;
   }
   
   EditorSettings.setValue("WorldEditor/recentLevelsList", %updatedRecentList);
   
   updateRecentLevelsListing();
}

function EditorExportToCollada()
{

   %dlg = new SaveFileDialog()
   {
      Filters        = "COLLADA Files (*.dae)|*.dae|";
      DefaultPath    = $Pref::WorldEditor::LastPath;
      DefaultFile    = "";
      ChangePath     = false;
      OverwritePrompt   = true;
   };

   %ret = %dlg.Execute();
   if ( %ret )
   {
      $Pref::WorldEditor::LastPath = filePath( %dlg.FileName );
      %exportFile = %dlg.FileName;
   }

   if( fileExt( %exportFile ) !$= ".dae" )
      %exportFile = %exportFile @ ".dae";

   %dlg.delete();

   if ( !%ret )
      return;

   if ( EditorGui.currentEditor.getId() == ShapeEditorPlugin.getId() )
      ShapeEdShapeView.exportToCollada( %exportFile );
   else
      EWorldEditor.colladaExportSelection( %exportFile );
}

function EditorMakePrefab()
{

   %dlg = new SaveFileDialog()
   {
      Filters        = "Prefab Files (*.prefab)|*.prefab|";
      DefaultPath    = $Pref::WorldEditor::LastPath;
      DefaultFile    = "";
      ChangePath     = false;
      OverwritePrompt   = true;
   };
         
   %ret = %dlg.Execute();
   if ( %ret )
   {
      $Pref::WorldEditor::LastPath = filePath( %dlg.FileName );
      %saveFile = %dlg.FileName;
   }
   
   if( fileExt( %saveFile ) !$= ".prefab" )
      %saveFile = %saveFile @ ".prefab";
   
   %dlg.delete();
   
   if ( !%ret )
      return;
   
   EWorldEditor.makeSelectionPrefab( %saveFile );    
   
   EditorTree.buildVisibleTree( true );  
}

function EditorExplodePrefab()
{
   //echo( "EditorExplodePrefab()" );  
   EWorldEditor.explodeSelectedPrefab();
   EditorTree.buildVisibleTree( true );
}

function makeSelectedAMesh(%assetId)
{
   
   /*%dlg = new SaveFileDialog()
   {
      Filters        = "Collada file (*.dae)|*.dae|";
      DefaultPath    = $Pref::WorldEditor::LastPath;
      DefaultFile    = "";
      ChangePath     = false;
      OverwritePrompt   = true;
   };
         
   %ret = %dlg.Execute();
   if ( %ret )
   {
      $Pref::WorldEditor::LastPath = filePath( %dlg.FileName );
      %saveFile = %dlg.FileName;
   }
   
   if( fileExt( %saveFile ) !$= ".dae" )
      %saveFile = %saveFile @ ".dae";
   
   %dlg.delete();
   
   if ( !%ret )
      return;*/
      
   %assetDef = AssetDatabase.acquireAsset(%assetId);
   
   %assetPath = AssetDatabase.getAssetPath(%assetId);
   %filePath = %assetPath @ "/" @ %assetDef.AssetName @ ".dae";
   
   %fileName = fileName(%filePath);
   
   %assetDef.fileName = %fileName;
   %assetDef.saveAsset();
   
   %success = EWorldEditor.makeSelectionAMesh( %filePath );  
   
   AssetDatabase.refreshAsset(%assetId);  
   
   if(%success)
   {
      //ok, cool it worked, so clear out the old 
      //First, get our center of the currently selected objects
      %selectionCenter = EWorldEditor.getSelectionCentroid();
      
      //Next, for safety purposes(and convenience!) we'll make them a prefab aping off the filepath/name provided
      //TODO: Make this an editor option
      %prefabPath = %assetPath @ "/" @ %assetDef.AssetName @ ".prefab";
      EWorldEditor.makeSelectionPrefab(%prefabPath, true);
      
      //Next, nuke 'em
      EditorMenuEditDelete();
      
      //now make a new static  
      %newStatic = new TSStatic()
      {
         shapeAsset = %assetId;
         position = %selectionCenter;
      };
      
      getRootScene().add(%newStatic);
   }
   
   EditorTree.buildVisibleTree( true );  
}

function EditorTakeControlOfEntity()
{
   %object = EWorldEditor.getSelectedObject(0);
   switchCamera(localClientConnection, %object);
   switchControlObject(localClientConnection, %object);  
}

function EditorMount()
{
   echo( "EditorMount" );
   
   %size = EWorldEditor.getSelectionSize();
   if ( %size != 2 )
      return;
      
   %a = EWorldEditor.getSelectedObject(0);
   %b = EWorldEditor.getSelectedObject(1);
   
   //%a.mountObject( %b, 0 );
   EWorldEditor.mountRelative( %a, %b );
}

function EditorUnmount()
{
   echo( "EditorUnmount" );
   
   %obj = EWorldEditor.getSelectedObject(0);
   %obj.unmount();   
}

//------------------------------------------------------------------------
function updateRecentLevelsListing()
{
   %recentLevels = EditorSettings.value("WorldEditor/recentLevelsList");
   %recentCount = getTokenCount(%recentLevels, ",");
   
   for(%i=0; %i < %recentCount; %i++)
   {
      %recentEntry = getToken(%recentLevels, ",", %i);
      
      %command = "schedule(32,0, \"EditorOpenMission\", \"" @ %recentEntry @ "\");";
      RecentLevelsPopupMenu.item[%i] = %recentEntry TAB "" TAB %command;
   }
   
   RecentLevelsPopupMenu.reloadItems();
}

//////////////////////////////////////////////////////////////////////////
// View Menu Handlers
//////////////////////////////////////////////////////////////////////////

function EditorViewMenu::onMenuSelect( %this )
{
   %this.checkItem( 1, EWorldEditor.renderOrthoGrid );
}

//////////////////////////////////////////////////////////////////////////
// Edit Menu Handlers
//////////////////////////////////////////////////////////////////////////

function EditorEditMenu::onMenuSelect( %this )
{      
   // UndoManager is in charge of enabling or disabling the undo/redo items.
   Editor.getUndoManager().updateUndoMenu( %this );
   
   // SICKHEAD: It a perfect world we would abstract 
   // cut/copy/paste with a generic selection object 
   // which would know how to process itself.         
   
   // Give the active editor a chance at fixing up
   // the state of the edit menu.
   // Do we really need this check here?
   if ( isObject( EditorGui.currentEditor ) )
      EditorGui.currentEditor.onEditMenuSelect( %this );   
}

//////////////////////////////////////////////////////////////////////////

function EditorMenuEditDelete()
{
   if ( isObject( EditorGui.currentEditor ) )
      EditorGui.currentEditor.handleDelete();      
}

function EditorMenuEditDeselect()
{
   if ( isObject( EditorGui.currentEditor ) )
      EditorGui.currentEditor.handleDeselect();  
}

function EditorMenuEditCut()
{
   if ( isObject( EditorGui.currentEditor ) )
      EditorGui.currentEditor.handleCut();  
}

function EditorMenuEditCopy()
{
   if ( isObject( EditorGui.currentEditor ) )
      EditorGui.currentEditor.handleCopy();  
}

function EditorMenuEditPaste()
{
   if ( isObject( EditorGui.currentEditor ) )
      EditorGui.currentEditor.handlePaste();  
}

//////////////////////////////////////////////////////////////////////////
// Window Menu Handler
//////////////////////////////////////////////////////////////////////////

function EditorToolsMenu::onSelectItem(%this, %id)
{
   %toolName = getField( %this.item[%id], 2 );  

   EditorGui.setEditor(%toolName, %paletteName  );
   
   %this.checkRadioItem(0, %this.getItemCount(), %id);
   return true;
}

function EditorToolsMenu::setupDefaultState(%this)
{
   Parent::setupDefaultState(%this);
}

//////////////////////////////////////////////////////////////////////////
// Camera Menu Handler
//////////////////////////////////////////////////////////////////////////

function EditorCameraMenu::onSelectItem(%this, %id, %text)
{
   if(%id == 0 || %id == 1)
   {
      // Handle the Free Camera/Orbit Camera toggle
      %this.checkRadioItem(0, 1, %id);
   }

   return Parent::onSelectItem(%this, %id, %text);
}

function EditorCameraMenu::setupDefaultState(%this)
{
   // Set the Free Camera/Orbit Camera check marks
   %this.checkRadioItem(0, 1, 0);
   Parent::setupDefaultState(%this);
}

function EditorFreeCameraTypeMenu::onSelectItem(%this, %id, %text)
{
   // Handle the camera type radio
   %this.checkRadioItem(0, 2, %id);

   return Parent::onSelectItem(%this, %id, %text);
}

function EditorFreeCameraTypeMenu::setupDefaultState(%this)
{
   // Set the camera type check marks
   %this.checkRadioItem(0, 2, 0);
   Parent::setupDefaultState(%this);
}

function EditorCameraSpeedMenu::onSelectItem(%this, %id, %text)
{   
   // Grab and set speed
   %speed = getField( %this.item[%id], 2 ); 
   $Camera::movementSpeed = %speed;
   
   // Update Editor
   %this.checkRadioItem(0, 6, %id);
   
   // Update Toolbar TextEdit
   EWorldEditorCameraSpeed.setText( $Camera::movementSpeed );
   
   // Update Toolbar Slider
   CameraSpeedDropdownCtrlContainer-->Slider.setValue( $Camera::movementSpeed );
   
   return true;
}
function EditorCameraSpeedMenu::setupDefaultState(%this)
{
   // Setup camera speed gui's. Both menu and editorgui
   %this.setupGuiControls();
   
   //Grab and set speed
   %defaultSpeed = EditorSettings.value("LevelInformation/levels/" @ EditorGui.levelName @ "/cameraSpeed");
   if( %defaultSpeed $= "" )
   {
      // Update Editor with default speed
      %defaultSpeed = 25;
   }
   $Camera::movementSpeed = %defaultSpeed;
   
   // Update Toolbar TextEdit
   EWorldEditorCameraSpeed.setText( %defaultSpeed );
   
   // Update Toolbar Slider
   CameraSpeedDropdownCtrlContainer-->Slider.setValue( %defaultSpeed );
   
   Parent::setupDefaultState(%this);
}

function EditorCameraSpeedMenu::setupGuiControls(%this)
{
   // Default levelInfo params
   %minSpeed = 5;
   %maxSpeed = 200;
   
   %speedA = EditorSettings.value("LevelInformation/levels/" @ EditorGui.levelName @ "/cameraSpeedMin");
   %speedB = EditorSettings.value("LevelInformation/levels/" @ EditorGui.levelName @ "/cameraSpeedMax");
   if( %speedA < %speedB )
   {         
      if( %speedA == 0 )
      {
         if( %speedB > 1 )
            %minSpeed = 1;
         else
            %minSpeed = 0.1;
      }
      else
      {
         %minSpeed = %speedA;
      }

      %maxSpeed = %speedB;
   }
   
   // Set up the camera speed items
   %inc = ( (%maxSpeed - %minSpeed) / (%this.getItemCount() - 1) );
   for( %i = 0; %i < %this.getItemCount(); %i++)
      %this.item[%i] = setField( %this.item[%i], 2, (%minSpeed + (%inc * %i)));
   
   // Set up min/max camera slider range
   eval("CameraSpeedDropdownCtrlContainer-->Slider.range = \"" @ %minSpeed @ " " @ %maxSpeed @ "\";");
}

//////////////////////////////////////////////////////////////////////////
// Tools Menu Handler
//////////////////////////////////////////////////////////////////////////
function EditorUtilitiesMenu::onSelectItem(%this, %id, %text)
{
   return Parent::onSelectItem(%this, %id, %text);
}

//////////////////////////////////////////////////////////////////////////
// World Menu Handler Object Menu
//////////////////////////////////////////////////////////////////////////

function EditorWorldMenu::onMenuSelect(%this)
{
   %selSize = EWorldEditor.getSelectionSize();
   %lockCount = EWorldEditor.getSelectionLockCount();
   %hideCount = EWorldEditor.getSelectionHiddenCount();
   
   %this.enableItem(0, %lockCount < %selSize);  // Lock Selection
   %this.enableItem(1, %lockCount > 0);  // Unlock Selection
   %this.enableItem(3, %hideCount < %selSize);  // Hide Selection
   %this.enableItem(4, %hideCount > 0);  // Show Selection
   %this.enableItem(6, %selSize > 1 && %lockCount == 0);  // Align bounds
   %this.enableItem(7, %selSize > 1 && %lockCount == 0);  // Align center
   %this.enableItem(9, %selSize > 0 && %lockCount == 0);  // Reset Transforms
   %this.enableItem(10, %selSize > 0 && %lockCount == 0);  // Reset Selected Rotation
   %this.enableItem(11, %selSize > 0 && %lockCount == 0);  // Reset Selected Scale
   %this.enableItem(12, %selSize > 0 && %lockCount == 0);  // Transform Selection
   %this.enableItem(14, %selSize > 0 && %lockCount == 0);  // Drop Selection
   
   %this.enableItem(17, %selSize > 0); // Make Prefab
   %this.enableItem(18, %selSize > 0); // Explode Prefab   
   
   %this.enableItem(20, %selSize > 1); // Mount
   %this.enableItem(21, %selSize > 0); // Unmount
}

//////////////////////////////////////////////////////////////////////////

function EditorDropTypeMenu::onSelectItem(%this, %id, %text)
{
   // This sets up which drop script function to use when
   // a drop type is selected in the menu.
   EWorldEditor.dropType = getField(%this.item[%id], 2);
   
   %this.checkRadioItem(0, (%this.getItemCount() - 1), %id);
   
   return true;
}

function EditorDropTypeMenu::setupDefaultState(%this)
{
   // Check the radio item for the currently set drop type.
   
   %numItems = %this.getItemCount();
   
   %dropTypeIndex = 0;
   for( ; %dropTypeIndex < %numItems; %dropTypeIndex ++ )
      if( getField( %this.item[ %dropTypeIndex ], 2 ) $= EWorldEditor.dropType )
         break;
 
   // Default to screenCenter if we didn't match anything.        
   if( %dropTypeIndex > (%numItems - 1) )
      %dropTypeIndex = 4;
   
   %this.checkRadioItem( 0, (%numItems - 1), %dropTypeIndex );
      
   Parent::setupDefaultState(%this);
}

//////////////////////////////////////////////////////////////////////////

function EditorSnapToMenu::onSelectItem(%this, %id, %text)
{
    EWorldEditor.SnapTo(%id);
}

function EditorSnapToMenu::setupDefaultState(%this)
{
    Parent::setupDefaultState(%this);
}

function WorldEditor::snapTo(%this, %id)
{
    if(%this.getSelectionSize() > 2)
    {
        error("Please select two objects before selecting a Snap To function.");
        return;
    }

    %objTarget = %this.getSelectedObject(0);  
    %objToSnap = %this.getSelectedObject(%this.getSelectionSize()-1);

    switch$(%id)
    {
    case 0:
        %objToSnap.setTransform(setWord(%objToSnap.getTransform(), 0, getWord(%objTarget.getTransform(), 0)));
    case 1:
        %objTargetXEdge = getWord(%objTarget.getTransform(), 0) + getWord(%objTarget.getObjectBox(), 0);
        %objToSnapXEdge = %objTargetXEdge - getWord(%objToSnap.getObjectBox(), 3);
        %objToSnap.setTransform(setWord(%objToSnap.getTransform(), 0, %objToSnapXEdge));
    case 2:
        %objTargetXEdge = getWord(%objTarget.getTransform(), 0) + getWord(%objTarget.getObjectBox(), 3);
        %objToSnapXEdge = %objTargetXEdge - getWord(%objToSnap.getObjectBox(), 0);
        %objToSnap.setTransform(setWord(%objToSnap.getTransform(), 0, %objToSnapXEdge));
    case 3:    
        %objToSnap.setTransform(setWord(%objToSnap.getTransform(), 1, getWord(%objTarget.getTransform(), 1)));    
    case 4:    
        %objTargetXEdge = getWord(%objTarget.getTransform(), 1) + getWord(%objTarget.getObjectBox(), 1);    
        %objToSnapXEdge = %objTargetXEdge - getWord(%objToSnap.getObjectBox(), 4);    
        %objToSnap.setTransform(setWord(%objToSnap.getTransform(), 1, %objToSnapXEdge));    
    case 5:    
        %objTargetXEdge = getWord(%objTarget.getTransform(), 1) + getWord(%objTarget.getObjectBox(), 4);    
        %objToSnapXEdge = %objTargetXEdge - getWord(%objToSnap.getObjectBox(), 1);    
        %objToSnap.setTransform(setWord(%objToSnap.getTransform(), 1, %objToSnapXEdge));    
    case 6:    
        %objToSnap.setTransform(setWord(%objToSnap.getTransform(), 2, getWord(%objTarget.getTransform(), 2)));    
    case 7:    
        %objTargetXEdge = getWord(%objTarget.getTransform(), 2) + getWord(%objTarget.getObjectBox(), 2);    
        %objToSnapXEdge = %objTargetXEdge - getWord(%objToSnap.getObjectBox(), 5);    
        %objToSnap.setTransform(setWord(%objToSnap.getTransform(), 2, %objToSnapXEdge));    
    case 8:    
        %objTargetXEdge = getWord(%objTarget.getTransform(), 2) + getWord(%objTarget.getObjectBox(), 5);    
        %objToSnapXEdge = %objTargetXEdge - getWord(%objToSnap.getObjectBox(), 2);    
        %objToSnap.setTransform(setWord(%objToSnap.getTransform(), 2, %objToSnapXEdge));    
    }    
}

//////////////////////////////////////////////////////////////////////////

function EditorAlignBoundsMenu::onSelectItem(%this, %id, %text)
{
   // Have the editor align all selected objects by the selected bounds.
   EWorldEditor.alignByBounds(getField(%this.item[%id], 2));
   
   return true;
}

function EditorAlignBoundsMenu::setupDefaultState(%this)
{
   // Allow the parent to set the menu's default state
   Parent::setupDefaultState(%this);
}

//////////////////////////////////////////////////////////////////////////

function EditorAlignCenterMenu::onSelectItem(%this, %id, %text)
{
   // Have the editor align all selected objects by the selected axis.
   EWorldEditor.alignByAxis(getField(%this.item[%id], 2));
   
   return true;
}

function EditorAlignCenterMenu::setupDefaultState(%this)
{
   // Allow the parent to set the menu's default state
   Parent::setupDefaultState(%this);
}
