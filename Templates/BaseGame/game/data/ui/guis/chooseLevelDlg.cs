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

//----------------------------------------
function ChooseLevelDlg::onWake( %this )
{
   if(!isObject(LevelListEntries))
      new ArrayObject(LevelListEntries){};
      
   LevelList.clearRows();
   LevelListEntries.empty();
   
   ChooseLevelWindow->CurrentPreview.setBitmap("data/ui/images/no-preview");
   ChooseLevelWindow->LevelDescriptionLabel.visible = false;
   ChooseLevelWindow->LevelDescription.visible = false;
   
   %assetQuery = new AssetQuery();
   AssetDatabase.findAssetType(%assetQuery, "LevelAsset");
      
   %count = %assetQuery.getCount();
   
   if(%count == 0 && !IsDirectory("tools"))
   {
      //We have no levels found. Prompt the user to open the editor to the default level if the tools are present
      MessageBoxOK("Error", "No levels were found in any modules. Please ensure you have modules loaded that contain gameplay code and level files.", 
         "Canvas.popDialog(ChooseLevelDlg); if(isObject(ChooseLevelDlg.returnGui) && ChooseLevelDlg.returnGui.isMethod(\"onReturnTo\")) ChooseLevelDlg.returnGui.onReturnTo();");
         
      %assetQuery.delete();
      return;
   }
   
   for(%i=0; %i < %count; %i++)
	{
	   %assetId = %assetQuery.getAsset(%i);
	   
	   if(AssetDatabase.getAssetModule(%assetId).ModuleId $= "ToolsModule")
	      continue;
      
      %levelAsset = AssetDatabase.acquireAsset(%assetId);
      
      %file = %levelAsset.getLevelPath();
      
      if ( !isFile(%file @ ".mis") && !isFile(%file @ ".mis.dso") &&!isFile(%file) )
         continue;
         
      // Skip our new level/mission if we arent choosing a level
      // to launch in the editor.
      if ( !%this.launchInEditor )
      {
         %fileName = fileName(%file);
         if (strstr(%fileName, "newMission.mis") > -1 || strstr(%fileName, "newLevel.mis") > -1)
            continue;      
      }
                  
      %this.addLevelAsset( %levelAsset );
   }
   
   // Also add the new level mission as defined in the world editor settings
   // if we are choosing a level to launch in the editor.
   if ( %this.launchInEditor )
   {
      %this.addMissionFile( "tools/levels/DefaultEditorLevel.mis" );
   }

   for(%i=0; %i < LevelListEntries.count(); %i++)
   {
      %levelEntry = LevelListEntries.getKey(%i);
      
      LevelList.addRow(getField(%levelEntry, 0), "", -1, -30);
   }
   
   LevelList.setSelected(0);
   LevelList.onChange();
   
   if(!$pref::HostMultiPlayer)
      LevelSelectTitle.setText("SINGLE PLAYER");
   else
      LevelSelectTitle.setText("CREATE SERVER");
   
   ChooseLevelButtonHolder.setActive();
}

function ChooseLevelButtonHolder::onWake(%this)
{
   %this-->goButton.set("btn_a", "Return", "Start Level", "ChooseLevelDlg.beginLevel();");
   %this-->backButton.set("btn_b", "Escape", "Back", "ChooseLevelDlg.backOut();");
}

function ChooseLevelDlg::onSleep( %this )
{
   // This is set from the outside, only stays true for a single wake/sleep
   // cycle.
   %this.launchInEditor = false;
}

function ChooseLevelDlg::addMissionFile( %this, %file )
{
   %levelName = fileBase(%file);
   %levelDesc = "A Torque level";

   %LevelInfoObject = getLevelInfo(%file);

   if (%LevelInfoObject != 0)
   {
      if(%LevelInfoObject.levelName !$= "")
         %levelName = %LevelInfoObject.levelName;
      else if(%LevelInfoObject.name !$= "")
         %levelName = %LevelInfoObject.name;

      if (%LevelInfoObject.desc0 !$= "")
         %levelDesc = %LevelInfoObject.desc0;
         
      if (%LevelInfoObject.preview !$= "")
         %levelPreview = %LevelInfoObject.preview;
         
      %LevelInfoObject.delete();
   }

   LevelListEntries.add( %levelName TAB %file TAB %levelDesc TAB %levelPreview );
}

function ChooseLevelDlg::addLevelAsset( %this, %levelAsset )
{
   %file = %levelAsset.getAssetId();
   
   %levelName = %levelAsset.LevelName;
   %levelDesc = %levelAsset.description;
   %levelPreview = %levelAsset.levelPreviewImage;
   
   LevelListEntries.add( %levelName TAB %file TAB %levelDesc TAB %levelPreview );
}

function LevelList::onChange(%this)
{
   %index = %this.getSelectedRow();
   
   %levelEntry = LevelListEntries.getKey(%index);
   
   // Get the name
   ChooseLevelWindow->LevelName.text = getField(%levelEntry, 0);
   
   // Get the level file
   $selectedLevelAsset = getField(%levelEntry, 1);
   
   // Find the preview image
   %levelPreview = getField(%levelEntry, 3);
   
   // Test against all of the different image formats
   // This should probably be moved into an engine function
   if (isFile(%levelPreview @ ".png") ||
       isFile(%levelPreview @ ".jpg") ||
       isFile(%levelPreview @ ".bmp") ||
       isFile(%levelPreview @ ".gif") ||
       isFile(%levelPreview @ ".jng") ||
       isFile(%levelPreview @ ".mng") ||
       isFile(%levelPreview @ ".tga"))
      ChooseLevelWindow->CurrentPreview.setBitmap(%previewFile);
   else
      ChooseLevelWindow->CurrentPreview.setBitmap("data/ui/images/no-preview");

   // Get the description
   %levelDesc = getField(%levelEntry, 2);
   
   if(%levelDesc !$= "")
   {
      ChooseLevelWindow->LevelDescriptionLabel.setVisible(true);
      ChooseLevelWindow->LevelDescription.setVisible(true);
      ChooseLevelWindow->LevelDescription.setText(%levelDesc);
   }
   else
   {
      ChooseLevelWindow->LevelDescriptionLabel.setVisible(false);
      ChooseLevelWindow->LevelDescription.setVisible(false);
   }
   
}

// Do this onMouseUp not via Command which occurs onMouseDown so we do
// not have a lingering mouseUp event lingering in the ether.
function ChooseLevelDlg::beginLevel(%this)
{
   // So we can't fire the button when loading is in progress.
   if ( isObject( ServerGroup ) )
      return;

   // Launch the chosen level with the editor open?
   if ( ChooseLevelDlg.launchInEditor )
   {
      activatePackage( "BootEditor" );
      ChooseLevelDlg.launchInEditor = false; 
      StartGame("", "SinglePlayer");
   }
   else
   {
      StartGame(); 
   }
}

function ChooseLevelDlg::backOut(%this)
{
   Canvas.popDialog(ChooseLevelDlg);
   if(isObject(ChooseLevelDlg.returnGui) && ChooseLevelDlg.returnGui.isMethod("onReturnTo"))    
      ChooseLevelDlg.returnGui.onReturnTo();  
}
