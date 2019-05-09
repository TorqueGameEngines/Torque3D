//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------

function InitializeVerveEditor()
{
   $Verve::UseSeparateWindow = true;
   
    // Preferences.
    exec( "./DefaultPrefs.cs" );
    
    // GUI.
    exec( "./GUI/GuiProfiles.cs" );
    exec( "./GUI/VerveEditorGroupBuilder.gui" );
    exec( "./GUI/VerveEditorImportPathNodes.gui" );
    
    // Scripts.
    exec( "./Scripts/Plugin.cs" );
    exec( "./Scripts/Utility.cs" );
    
    exec( "./Scripts/EditorControls.cs" );
    exec( "./Scripts/EditorHistory.cs" );
    exec( "./Scripts/EditorMenu.cs" );
    exec( "./Scripts/EditorPreferences.cs" );
    exec( "./Scripts/EditorWindow.cs" );
    exec( "./Scripts/Persistence.cs" );
    exec( "./Scripts/ScrollNotify.cs" );
    exec( "./Scripts/VObject.cs" );
    
    exec( "./Scripts/Inspector/main.cs" );
    
    exec( "./Scripts/Controller/main.cs" );
    exec( "./Scripts/Groups/main.cs" );
    exec( "./Scripts/Tracks/main.cs" );
    exec( "./Scripts/Events/main.cs" );
    
    exec( "./Torque/main.cs" );
    
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