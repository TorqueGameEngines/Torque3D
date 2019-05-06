//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------

new ScriptObject( VLightObjectToggleTrackPropertyList )
{
    SuperClass  = "VEditorPropertyList";
    Parent      = "VObjectPropertyList";
};

//-----------------------------------------------------------------------------

function VLightObjectToggleTrack::CreateEvent( %this )
{
    // Create Event.
    return new VLightObjectToggleEvent();
}