//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------

new ScriptObject( VPostEffectToggleTrackPropertyList )
{
    SuperClass  = "VEditorPropertyList";
    Parent      = "VObjectPropertyList";
    
    Group[0]    = "VPostEffectToggleTrack";
    Field[0, 0] = "PostEffect";
    Type[0, 0]  = "VPostEffectEnum";
};

//-----------------------------------------------------------------------------

function VPostEffectToggleTrack::CreateEvent( %this )
{
    // Create Event.
    return new VPostEffectToggleEvent();
}