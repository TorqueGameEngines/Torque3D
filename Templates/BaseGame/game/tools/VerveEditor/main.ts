//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------

function InitializeVerveEditor()
{
   $Verve::UseSeparateWindow = true;
   
    // Preferences.
    exec( "./DefaultPrefs.ts" );
    
    // GUI.
    exec( "./GUI/GuiProfiles.ts" );
    exec( "./GUI/VerveEditorGroupBuilder.gui" );
    exec( "./GUI/VerveEditorImportPathNodes.gui" );
    
    // Scripts.
    exec( "./Scripts/Plugin.ts" );
    exec( "./Scripts/Utility.ts" );
    
    exec( "./Scripts/EditorControls.ts" );
    exec( "./Scripts/EditorHistory.ts" );
    exec( "./Scripts/EditorMenu.ts" );
    exec( "./Scripts/EditorPreferences.ts" );
    exec( "./Scripts/EditorWindow.ts" );
    exec( "./Scripts/Persistence.ts" );
    exec( "./Scripts/ScrollNotify.ts" );
    exec( "./Scripts/VObject.ts" );
    
    exec( "./Scripts/Inspector/main.ts" );
    
    exec( "./Scripts/Controller/main.ts" );
    exec( "./Scripts/Groups/main.ts" );
    exec( "./Scripts/Tracks/main.ts" );
    exec( "./Scripts/Events/main.ts" );
    
    exec( "./Torque/main.ts" );
    
    // Register Events.
    VerveEditor::RegisterEvent( "VGroupObjectUpdate" );
}

function DestroyVerveEditor()
{
    // Ensure the Editor has Shutdown.
    if ( isObject( VerveEditorWindow ) )
    {
        // Prompt for Save.
        VerveEditor::SavePrompt();
        
        // Reset.
        VerveEditor::Reset();
        
        // Delete the Window.
        VerveEditorWindow.delete();
    }
}

function ToggleVerveEditor( %value )
{
    if ( %value && $Verve::UseSeparateWindow )
    {
        if ( !isObject( VerveEditorWindow ) )
        {
            VerveEditor::LaunchEditor();
        }
        else
        {
            VerveEditorWindow.onWindowClose();
        }
    }
}

function VerveEditor::LaunchEditor()
{
    // Launch Window.
    %mainScreen = VerveEditorWindow::Open();
    
    if ( !isObject( VerveEditorGui ) )
    {
        // Load the GUI.
        exec ( "./GUI/VerveEditor.gui" );
    }
    
    // Apply GUI.
    if($Verve::UseSeparateWindow)
      %mainScreen.setContent( VerveEditorGUI );
   else
   {
      %mainScreen.add(VerveEditorGUI);
      VerveEditorGUI.position.y = VerveEditorGUI.Position.y + 20;
      EditorGUI.add(%mainScreen);
   }
    
    // Clear History.
    VerveEditor::ClearHistory();
    
    // Update Window Title.
    if($Verve::UseSeparateWindow)
      VerveEditorWindow.UpdateWindowTitle();
    
    // Update Selection.
    VerveEditor::OnSelectionUpdate();
    
    // Update Sizes.
    VerveEditor::UpdateSizes();
}

function VerveEditor::ResetController()
{
    // Delete.
    VerveEditor::DeleteController();
    // Create.
    return VerveEditor::CreateController();
}

function VerveEditor::DeleteController()
{
    // Current Controller?
    if ( isObject( $VerveEditor::Controller ) )
    {
        // Stop but do not Reset.
        $VerveEditor::Controller.stop( false );
        // Delete the Controller.
        $VerveEditor::Controller.delete();
        // Deleted?
        return !isObject( $VerveEditor::Controller );
    }
    
    // No Deletion.
    return false;
}

function VerveEditor::CreateController()
{
    // Current Controller?
    if ( !isObject( VerveEditorController ) )
    {
        // Create Controller.
        $VerveEditor::Controller = new VController( VerveEditorController );
    }

    // Return ID.
    return $VerveEditor::Controller;
}

function VerveEditor::Refresh()
{
    if ( !isObject( $VerveEditor::Controller ) )
    {
        return;
    }
    
    // Clear Selection.
    VerveEditor::ClearSelection();
    
    // Delete Existing Controls.
    VerveEditor::DeleteControls();
    
    // Sort Groups & Tracks.
    $VerveEditor::Controller.sortGroups();
    $VerveEditor::Controller.sortTracks();
    
    %groupSet   = $VerveEditor::Controller;
    %groupCount = %groupSet.getCount();
    for ( %i = 0; %i < %groupCount; %i++ )
    {
        // Update Controls.
        %groupSet.getObject( %i ).Refresh();
    }
    
    // Update Window Title.
    VerveEditorWindow.UpdateWindowTitle();
    
    // Update Duration.
    VerveEditor::UpdateDuration();
    
    // Update Sizes.
    VerveEditor::UpdateSizes();
    
    // Update Selection.
    VerveEditor::OnSelectionUpdate();
}

function VerveEditor::UpdateSizes()
{
    VerveEditorGroupNotify.UpdateSize();
    VerveEditorTrackNotify.UpdateSize();
    VerveEditorTimeNotify.UpdateSize();
}

function VerveEditor::UpdateDuration( %duration )
{
    if ( %duration !$= "" )
    {
        // Update Duration.
        $VerveEditor::Controller.setFieldValue( "Duration", %duration );
    }
    
    // Update Duration.
    VerveEditorTimeLine.updateDuration();
    VerveEditorTrackTimeLine.updateDuration();
    
    // Update Sizes.
    VerveEditorGroupNotify.UpdateSize();
    VerveEditorTrackNotify.UpdateSize();
    VerveEditorTimeNotify.UpdateSize();
}

package VerveEditorSaveIntercept
{
    function EditorSaveMission()
    {
        // Reset.
        VerveEditor::Reset();
        
        // Perform the Save.
        Parent::EditorSaveMission();
    }
};

function VerveEditor::Reset()
{
    // Valid Controller?
    if ( isObject( $VerveEditor::Controller ) )
    {
        // Reset.
        $VerveEditor::Controller.Reset();
        
        // Stop.
        $VerveEditor::Controller.Stop();
    }
}