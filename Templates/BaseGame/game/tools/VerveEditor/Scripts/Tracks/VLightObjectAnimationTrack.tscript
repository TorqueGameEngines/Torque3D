//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------

new ScriptObject( VLightObjectAnimationTrackPropertyList )
{
    SuperClass  = "VEditorPropertyList";
    Parent      = "VObjectPropertyList";
    
    Group[0]    = "Animation Track";
    Field[0, 0] = "AnimationData";
    Type[0, 0]  = "VLightAnimationDataEnum";
};

//-----------------------------------------------------------------------------

function VLightObjectAnimationTrack::CreateEvent( %this )
{
    // Create Event.
    return new VLightObjectAnimationEvent();
}