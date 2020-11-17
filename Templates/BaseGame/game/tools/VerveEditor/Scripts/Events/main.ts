//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------

function VerveEditor::InitEventScripts()
{
    // Core.
    exec( "./VEvent.ts" );
    
    // Built-In.
    exec( "./VCameraShakeEvent.ts" );
    exec( "./VDirectorEvent.ts" );
    exec( "./VFadeEvent.ts" );
    exec( "./VLightObjectAnimationEvent.ts" );
    exec( "./VLightObjectToggleEvent.ts" );
    exec( "./VMotionEvent.ts" );
    exec( "./VParticleEffectToggleEvent.ts" );
    exec( "./VPostEffectToggleEvent.ts" );
    exec( "./VSceneJumpEvent.ts" );
    exec( "./VScriptEvent.ts" );
    exec( "./VShapeAnimationEvent.ts" );
    exec( "./VSlowMoEvent.ts" );
    exec( "./VSoundEffectEvent.ts" );
    exec( "./VSpawnSphereSpawnTargetEvent.ts" );
    
    // Custom.
    // Exec Custom Event Scripts.
}
VerveEditor::InitEventScripts();
