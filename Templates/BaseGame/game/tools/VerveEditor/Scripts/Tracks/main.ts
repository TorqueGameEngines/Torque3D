//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------

function VerveEditor::InitTrackScripts()
{
    // Core.
    exec( "./VTrack.ts" );
    
    // Built-In.
    exec( "./VCameraShakeTrack.ts" );
    exec( "./VDirectorTrack.ts" );
    exec( "./VFadeTrack.ts" );
    exec( "./VLightObjectAnimationTrack.ts" );
    exec( "./VLightObjectToggleTrack.ts" );
    exec( "./VMotionTrack.ts" );
    exec( "./VParticleEffectToggleTrack.ts" );
    exec( "./VPostEffectToggleTrack.ts" );
    exec( "./VSceneJumpTrack.ts" );
    exec( "./VScriptEventTrack.ts" );
    exec( "./VShapeAnimationTrack.ts" );
    exec( "./VSlowMoTrack.ts" );
    exec( "./VSoundEffectTrack.ts" );
    exec( "./VSpawnSphereSpawnTargetTrack.ts" );
    
    // Custom.
    // Exec Custom Track Scripts.
    
    // Non-Unique Group List.
    $VerveEditor::NonUniqueTrackList = "VTrack VPostEffectToggleTrack VSoundEffectTrack";
}
VerveEditor::InitTrackScripts();
