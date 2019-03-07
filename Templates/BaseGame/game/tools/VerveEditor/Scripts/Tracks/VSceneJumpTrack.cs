//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------
    
new ScriptObject( VSceneJumpTrackPropertyList )
{
    SuperClass  = "VEditorPropertyList";
    Parent      = "VObjectPropertyList";
};
    
//-----------------------------------------------------------------------------

function VSceneJumpTrack::CreateEvent( %this )
{
    // Create Event.
    return new VSceneJumpEvent();
}