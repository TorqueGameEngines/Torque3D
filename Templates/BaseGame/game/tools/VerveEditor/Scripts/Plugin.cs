//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------

// Verve Editor
new ScriptObject( VerveEditorPlugin )
{
    SuperClass = "EditorPlugin";
};

//-----------------------------------------------------------------------------

function VerveEditorPlugin::onWorldEditorStartup( %this )
{
    //----------------------------------------------------------------------
    //
    // Editor Toggles
    //
    //----------------------------------------------------------------------
    
    // Add ourselves to the window menu.
    %accel = EditorGui.addToEditorsMenu( "Verve Editor", "", VerveEditorPlugin );

    // Add ourselves to the ToolsToolbar
    %tooltip = "Verve Editor (" @ %accel @ ")";
   
    // Add ourselves to the ToolsToolbar
    EditorGui.addToToolsToolbar( "VerveEditorPlugin", "VerveEditorPluginPalette", expandFilename( "tools/VerveEditor/GUI/Images/btn_Palette" ), %tooltip );

    // Find and Store the Button.
    %this.ToolbarButton = ToolsToolbarArray.findObjectByInternalName( "VerveEditorPluginPalette", false );
    %this.ToolbarButton.ButtonType = "ToggleButton";
    
    // Extend Width.
    %extent = EWToolsToolbar.getExtent();
    EWToolsToolbar.setExtent( ( getWord( %extent, 0 ) + 33 ) SPC getWord( %extent, 1 ) );
}

function VerveEditorPlugin::setEditorFunction( %this )
{
    if ( %this.ToolbarButton.getValue() )
    {
        // Launch Editor.
        VerveEditor::LaunchEditor();
    }
    else
    {
        VerveEditorWindow.onWindowClose();
    }
    
    // Maintain Last Editor.
    return false;
}

function VerveEditorPlugin::onDeactivated( %this )
{
    // Unchecked Box?
    if ( %this.ToolbarButton.getValue() )
    {
        return;
    }
}