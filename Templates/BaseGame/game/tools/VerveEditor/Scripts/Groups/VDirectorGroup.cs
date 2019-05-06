//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------
    
new ScriptObject( VDirectorGroupPropertyList )
{
    SuperClass  = "VEditorPropertyList";
    Parent      = "VGroupPropertyList";
};

//-----------------------------------------------------------------------------

function VDirectorGroup::PopulateBuildStack( %this, %stack )
{
    Parent::PopulateBuildStack( %this, %stack );
    
    // Create Director Track Checkbox.
    %directorTrackCheckBox = %stack.CreateCheckbox( "DirectorTrackToggle", "Add Director Track:" );
    %directorTrackCheckBox.setStateOn( true );
}

function VDirectorGroup::ResolveBuildStack( %this, %stack )
{
    Parent::ResolveBuildStack( %this, %stack, %groupObject );
    
    // Find the Track Toggle.
    %directorTrackCheckBox = %stack.findObjectByInternalName( "DirectorTrackToggle", true );
    if ( isObject( %directorTrackCheckBox ) && %directorTrackCheckBox.getValue() == true )
    {
        // Create the Director Track.
        %directorTrackCheckBox = VerveEditor::AddTrack( "VDirectorTrack", %this, false );
    }
}

//-----------------------------------------------------------------------------

function VDirectorGroup::GetAddTrackMenu( %this )
{
    %contextMenu = $VerveEditor::VGroup::ContextMenu[%this.getClassName()];
    if ( !isObject( %contextMenu ) )
    {
        %contextMenu = new PopupMenu()
        {
            SuperClass = "VerveWindowMenu";
            
            IsPopup  = true;
            
            Label    = "VGroupAddTrackMenu";
            Position = 0;
            
            Item[0] = "Add Director Track"     TAB "" TAB "VerveEditor::AddTrack( \"VDirectorTrack\" );";
            Item[1] = "Add Fade Track"         TAB "" TAB "VerveEditor::AddTrack( \"VFadeTrack\" );";
            Item[2] = "Add Scene Jump Track"   TAB "" TAB "VerveEditor::AddTrack( \"VSceneJumpTrack\" );";
            Item[3] = "Add Script Event Track" TAB "" TAB "VerveEditor::AddTrack( \"VScriptEventTrack\" );";
            Item[4] = "Add Slow Mo Track"      TAB "" TAB "VerveEditor::AddTrack( \"VSlowMoTrack\" );";
            Item[5] = "Add Sound Effect Track" TAB "" TAB "VerveEditor::AddTrack( \"VSoundEffectTrack\" );";
        };
        %contextMenu.Init();
        
        // Cache.
        $VerveEditor::VGroup::ContextMenu[%this.getClassName()] = %contextMenu;
    }
    
    // Enable/Disable Adding Tracks.
    %contextMenu.enableItem( 0, %this.CanAdd( "VDirectorTrack" ) );
    %contextMenu.enableItem( 1, %this.CanAdd( "VFadeTrack" ) );
    %contextMenu.enableItem( 2, %this.CanAdd( "VSceneJumpTrack" ) );
    %contextMenu.enableItem( 3, %this.CanAdd( "VScriptEventTrack" ) );
    %contextMenu.enableItem( 4, %this.CanAdd( "VSlowMoTrack" ) );
    %contextMenu.enableItem( 5, %this.CanAdd( "VSoundEffectTrack" ) );
    
    // Return Menu.
    return %contextMenu;
}