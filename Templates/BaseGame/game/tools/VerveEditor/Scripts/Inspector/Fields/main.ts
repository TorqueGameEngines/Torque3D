//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------

function VerveEditor::InitInspectorFieldScripts()
{
    exec( "./TypeBool.ts" );
    exec( "./TypeData.ts" );
    exec( "./TypeEnum.ts" );
    exec( "./TypeString.ts" );
    
    exec( "./TypeVCameraGroupEnum.ts" );
    exec( "./TypeVCommandEnum.ts" );
    exec( "./TypeVControllerDataEnum.ts" );
    exec( "./TypeVGroupEnum.ts" );
    exec( "./TypeVLightAnimationDataEnum.ts" );
    exec( "./TypeVPathOrientationModeEnum.ts" );
    exec( "./TypeVPostEffectEnum.ts" );
    exec( "./TypeVSceneEnum.ts" );
    exec( "./TypeVSFXProfileEnum.ts" );
    exec( "./TypeVShapeAnimationEnum.ts" );
    exec( "./TypeToggleEnum.ts" );
}
VerveEditor::InitInspectorFieldScripts();