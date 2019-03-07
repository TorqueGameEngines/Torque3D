//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------

function VerveEditor::InitTrackScripts()
{
    // Core.
    exec( "./VTrack.cs" );
    
    // Built-In.
    exec( "./VCameraShakeTrack.cs" );
    exec( "./VDirectorTrack.cs" );
    exec( "./VFadeTrack.cs" );
    exec( "./VLightObjectAnimationTrack.cs" );
    exec( "./VLightObjectToggleTrack.cs" );
    exec( "./VMotionTrack.cs" );
    exec( "./VParticleEffectToggleTrack.cs" );
    exec( "./VPostEffectToggleTrack.cs" );
    exec( "./VSceneJumpTrack.cs" );
    exec( "./VScriptEventTrack.cs" );
    exec( "./VShapeAnimationTrack.cs" );
    exec( "./VSlowMoTrack.cs" );
    exec( "./VSoundEffectTrack.cs" );
    exec( "./VSpawnSphereSpawnTargetTrack.cs" );
    
    // Custom.
    // Exec Custom Track Scripts.
    
    // Non-Unique Group List.
    $VerveEditor::NonUniqueTrackList = "VTrack VPostEffectToggleTrack VSoundEffectTrack";
}
VerveEditor::InitTrackScripts();
