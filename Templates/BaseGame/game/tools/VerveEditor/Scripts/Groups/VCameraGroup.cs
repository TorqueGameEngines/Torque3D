//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------
    
new ScriptObject( VCameraGroupPropertyList )
{
    SuperClass  = "VEditorPropertyList";
    Parent      = "VSceneObjectGroupPropertyList";
};

//-----------------------------------------------------------------------------

function VCameraGroup::GetAddTrackMenu( %this )
{
    %contextMenu = $VerveEditor::VGroup::ContextMenu[%this.getClassName()];
    if ( !isObject( %contextMenu ) )
    {
        %contextMenu = new PopupMenu()
        {
            SuperClass = "VerveWindowMenu";
            
            IsPopup  = true;
            
            Label    = "VCameraGroupAddTrackMenu";
            Position = 0;
            
            Item[0] = "Add Animation Track"    TAB "" TAB "VerveEditor::AddTrack( \"VShapeAnimationTrack\" );";
            Item[1] = "Add Camera Shake Track" TAB "" TAB "VerveEditor::AddTrack( \"VCameraShakeTrack\" );";
            Item[2] = "Add Motion Track"       TAB "" TAB "VerveEditor::AddTrack( \"VMotionTrack\" );";
            Item[3] = "Add Post Effect Track"  TAB "" TAB "VerveEditor::AddTrack( \"VPostEffectToggleTrack\" );";
            Item[4] = "Add Script Event Track" TAB "" TAB "VerveEditor::AddTrack( \"VScriptEventTrack\" );";
            Item[5] = "Add Sound Effect Track" TAB "" TAB "VerveEditor::AddTrack( \"VSoundEffectTrack\" );";
        };
        %contextMenu.Init();
        
        // Cache.
        $VerveEditor::VGroup::ContextMenu[%this.getClassName()] = %contextMenu;
    }
    
    // Enable/Disable Adding Tracks.
    %contextMenu.enableItem( 0, %this.CanAdd( "VShapeAnimationTrack" ) );
    %contextMenu.enableItem( 1, %this.CanAdd( "VCameraShakeTrack" ) );
    %contextMenu.enableItem( 2, %this.CanAdd( "VMotionTrack" ) );
    %contextMenu.enableItem( 3, %this.CanAdd( "VPostEffectToggleTrack" ) );
    %contextMenu.enableItem( 4, %this.CanAdd( "VScriptEventTrack" ) );
    %contextMenu.enableItem( 5, %this.CanAdd( "VSoundEffectTrack" ) );
    
    // Return Menu.
    return %contextMenu;
}

function VCameraGroup::isValid( %this )
{
    // Valid?
    return VTorque::isCameraObject( %this.getSceneObject() );
}