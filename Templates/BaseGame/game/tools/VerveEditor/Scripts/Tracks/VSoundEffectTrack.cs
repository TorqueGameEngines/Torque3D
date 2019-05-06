//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------

new ScriptObject( VSoundEffectTrackPropertyList )
{
    SuperClass  = "VEditorPropertyList";
    Parent      = "VObjectPropertyList";
};

//-----------------------------------------------------------------------------

function VSoundEffectTrack::CreateEvent( %this )
{
    // Create Event.
    return new VSoundEffectEvent();
}