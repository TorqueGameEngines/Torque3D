//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------

new ScriptObject( VSpawnSphereSpawnTargetTrackPropertyList )
{
    SuperClass  = "VEditorPropertyList";
    Parent      = "VObjectPropertyList";
    
    Group[0]    = "Spawn Target Track";
    Field[0, 0] = "DespawnOnLoop";
    Field[0, 1] = "DespawnOnStop";
};

//-----------------------------------------------------------------------------

function VSpawnSphereSpawnTargetTrack::CreateEvent( %this )
{
    // Create Event.
    return new VSpawnSphereSpawnTargetEvent();
}