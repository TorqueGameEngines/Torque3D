//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------

function VerveEditor::InitInspectorFieldScripts()
{
    exec( "./TypeBool.cs" );
    exec( "./TypeData.cs" );
    exec( "./TypeEnum.cs" );
    exec( "./TypeString.cs" );
    
    exec( "./TypeVCameraGroupEnum.cs" );
    exec( "./TypeVCommandEnum.cs" );
    exec( "./TypeVControllerDataEnum.cs" );
    exec( "./TypeVGroupEnum.cs" );
    exec( "./TypeVLightAnimationDataEnum.cs" );
    exec( "./TypeVPathOrientationModeEnum.cs" );
    exec( "./TypeVPostEffectEnum.cs" );
    exec( "./TypeVSceneEnum.cs" );
    exec( "./TypeVSFXProfileEnum.cs" );
    exec( "./TypeVShapeAnimationEnum.cs" );
    exec( "./TypeToggleEnum.cs" );
}
VerveEditor::InitInspectorFieldScripts();