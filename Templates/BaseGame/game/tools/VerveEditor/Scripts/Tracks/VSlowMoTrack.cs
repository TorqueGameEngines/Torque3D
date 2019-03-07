//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------
    
new ScriptObject( VSlowMoTrackPropertyList )
{
    SuperClass  = "VEditorPropertyList";
    Parent      = "VObjectPropertyList";
};
    
//-----------------------------------------------------------------------------

function VSlowMoTrack::CreateEvent( %this )
{
    // Create Event.
    return new VSlowMoEvent();
}