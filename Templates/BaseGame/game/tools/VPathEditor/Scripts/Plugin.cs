//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------

new ScriptObject( VPathEditorPlugin )
{
    SuperClass = "EditorPlugin";
};

//-----------------------------------------------------------------------------

function VPathEditorPlugin::onWorldEditorStartup( %this )
{
    //----------------------------------------------------------------------
    //
    // Editor Init
    //
    //----------------------------------------------------------------------
    
    EditorGui.add( EVPathEditor );
    EVPathEditor.setVisible( false );
    
    %this.EditorMap = new ActionMap();
    %this.EditorMap.bindCmd( keyboard, "backspace", "EVPathEditor.onDeleteKey();", "" );
    %this.EditorMap.bindCmd( keyboard, "delete",    "EVPathEditor.onDeleteKey();", "" );
    %this.EditorMap.bindCmd( keyboard, "1",         "EVPathEditorSelectButton.performClick();", "" );
    %this.EditorMap.bindCmd( keyboard, "2",         "EVPathEditorMoveButton.performClick();",   "" );
    %this.EditorMap.bindCmd( keyboard, "3",         "EVPathEditorRotateButton.performClick();", "" );
    %this.EditorMap.bindCmd( keyboard, "4",         "EVPathEditorScaleButton.performClick();",  "" );
    
    //----------------------------------------------------------------------
    //
    // Editor Toggles
    //
    //----------------------------------------------------------------------
    
    // Add ourselves to the window menu.
    %accel = EditorGui.addToEditorsMenu( "Path Editor", "", VPathEditorPlugin );

    // Add ourselves to the ToolsToolbar
    %tooltip = "Path Editor (" @ %accel @ ")";
    EditorGui.addToToolsToolbar( "VPathEditorPlugin", "VPathEditorPalette", expandFilename( "tools/VPathEditor/GUI/Images/btn_Palette" ), %tooltip );

    // Find and Store the Button.
    %this.ToolbarButton = ToolsToolbarArray.findObjectByInternalName( "VPathEditorPalette", false );
    
    // Extend Width.
    %extent = EWToolsToolbar.getExtent();
    EWToolsToolbar.setExtent( ( getWord( %extent, 0 ) + 33 ) SPC getWord( %extent, 1 ) );
    
    //----------------------------------------------------------------------
    //
    // Initialise Toolbar
    //
    //----------------------------------------------------------------------
    
    if ( !isObject( VPathEditorToolbar ) )
    {
        exec( "~/VPathEditor/GUI/VPathEditorToolbar.gui" );
    }
    
    // Add Toolbar.
    EditorGuiToolbar.add( VPathEditorToolbar );
    
    // Populate Type Menu.
    VPathEditorToolbarPathTypeMenu.clear();
    VPathEditorToolbarPathTypeMenu.add( "BEZIER", 0 );
    VPathEditorToolbarPathTypeMenu.add( "LINEAR", 1 );
    VPathEditorToolbarPathTypeMenu.setFirstSelected();
    
    //----------------------------------------------------------------------
    //
    // Initialise Editor Palette
    //
    //----------------------------------------------------------------------
    
    if ( !isObject( VPathEditorPalette ) )
    {
        exec( "~/VPathEditor/GUI/VPathEditorPalette.gui" );
    }
    
    // Use Existing Group Number + 1.
    %groupNum = ToolsPaletteArray.getObject( ToolsPaletteArray.getCount() - 1 ).GroupNum + 1;
    
    %paletteGroup = VPathEditorPalette;
    while ( VPathEditorPalette.getCount() > 0 )
    {
        // Fetch Button.
        %paletteButton = %paletteGroup.getObject( 0 );
        
        // Setup.
        %paletteButton.Visible     = false;
        %paletteButton.GroupNum    = %groupNum;
        %paletteButton.PaletteName = VPathEditorPalette;
        
        // Add To Palette Array.
        ToolsPaletteArray.addGuiControl( %paletteButton );
    }
    
    //----------------------------------------------------------------------
    //
    // Initialise Library
    //
    //----------------------------------------------------------------------
    
    EWCreatorWindow.registerMissionObject( "VPath", "VPath", "", "Level" );
}

//EditorGui.setEditor(\"VPathEditorPlugin\");
function VPathEditorPlugin::onActivated( %this )
{
    if ( !isObject( EVPathEditor ) )
    {
        return;
    }
    
    // Display Editor.
    EVPathEditor.setVisible( true );
    EVPathEditor.makeFirstResponder( true );
    EditorGui.bringToFront( EVPathEditor );
    VPathEditorToolbar.setVisible( true );
    VPathTreeView.open( GetServerPathSet(), true );
    
    // Sync Gizmo.
    %this.syncGizmo();
    
    // Enable Map.
    %this.EditorMap.push();
    
    // Valid Selection?
    if ( EWorldEditor.getSelectionSize() )
    {
        %selection = EWorldEditor.getSelectedObject( 0 );
        if ( isObject( %selection ) && %selection.isMemberOfClass( "VPath" ) )
        {
            // Select Object.
            EVPathEditor.setSelection( %selection );
        }
    }
    
    // Parent Call.
    Parent::onActivated( %this );
}

function VPathEditorPlugin::onDeactivated( %this )
{
    // Hide Editor.
    EVPathEditor.setVisible( false );
    VPathEditorToolbar.setVisible( false );
    
    // Disable Map.
    %this.EditorMap.pop();
    
    // Parent Call.
    Parent::onDeactivated( %this );
}

function VPathEditorPlugin::isDirty( %this )
{
    return EVPathEditor.isDirty;
}

function VPathEditorPlugin::clearDirty( %this )
{
    EVPathEditor.isDirty = false;
}

function VPathEditorPlugin::syncGizmo( %this )
{
    switch$( GlobalGizmoProfile.Mode )
    {
        case "None"   : EVPathEditorSelectButton.performClick();
        case "Move"   : EVPathEditorMoveButton.performClick();
        case "Rotate" : EVPathEditorRotateButton.performClick();
        case "Scale"  : EVPathEditorScaleButton.performClick();
    }
}