//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------

function VerveEditor::InitGroupScripts()
{
    // Core.
    exec( "./VGroup.cs" );
    
    // Built In.
    exec( "./VCameraGroup.cs" );
    exec( "./VDirectorGroup.cs" );
    exec( "./VLightObjectGroup.cs" );
    exec( "./VParticleEffectGroup.cs" );
    exec( "./VSceneObjectGroup.cs" );
    exec( "./VSpawnSphereGroup.cs" );
    
    // Custom.
    // Exec Custom Group Scripts.
    
    // Unique Group List.
    $VerveEditor::UniqueGroupList = "VDirectorGroup";
}
VerveEditor::InitGroupScripts();
