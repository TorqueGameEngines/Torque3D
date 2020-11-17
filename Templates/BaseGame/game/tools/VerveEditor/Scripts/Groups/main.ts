//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------

function VerveEditor::InitGroupScripts()
{
    // Core.
    exec( "./VGroup.ts" );
    
    // Built In.
    exec( "./VCameraGroup.ts" );
    exec( "./VDirectorGroup.ts" );
    exec( "./VLightObjectGroup.ts" );
    exec( "./VParticleEffectGroup.ts" );
    exec( "./VSceneObjectGroup.ts" );
    exec( "./VSpawnSphereGroup.ts" );
    
    // Custom.
    // Exec Custom Group Scripts.
    
    // Unique Group List.
    $VerveEditor::UniqueGroupList = "VDirectorGroup";
}
VerveEditor::InitGroupScripts();
