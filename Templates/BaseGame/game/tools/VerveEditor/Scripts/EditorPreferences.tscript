//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------

function VerveEditor::LaunchEditorPreferences()
{
    if ( !isObject( VerveEditorPreferenceGui ) )
    {
        // Load the GUI.
        exec ( "~/VerveEditor/GUI/VerveEditorPreferences.gui" );
    }
    
    // Awake?
    if ( VerveEditorPreferenceGui.isAwake() )
    {
        // Sanity!.
        return;
    }
    
    // Launch.
    VerveEditorWindow.pushDialog( VerveEditorPreferenceGui );
}

function VerveEditor::CloseEditorPreferences()
{
    // Close.
    VerveEditorWindow.popDialog( VerveEditorPreferenceGui );
}