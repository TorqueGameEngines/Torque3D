//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------

function VerveEditor::InitEventScripts()
{
    // Core.
    exec( "./VEvent.cs" );
    
    // Built-In.
    exec( "./VCameraShakeEvent.cs" );
    exec( "./VDirectorEvent.cs" );
    exec( "./VFadeEvent.cs" );
    exec( "./VLightObjectAnimationEvent.cs" );
    exec( "./VLightObjectToggleEvent.cs" );
    exec( "./VMotionEvent.cs" );
    exec( "./VParticleEffectToggleEvent.cs" );
    exec( "./VPostEffectToggleEvent.cs" );
    exec( "./VSceneJumpEvent.cs" );
    exec( "./VScriptEvent.cs" );
    exec( "./VShapeAnimationEvent.cs" );
    exec( "./VSlowMoEvent.cs" );
    exec( "./VSoundEffectEvent.cs" );
    exec( "./VSpawnSphereSpawnTargetEvent.cs" );
    
    // Custom.
    // Exec Custom Event Scripts.
}
VerveEditor::InitEventScripts();
