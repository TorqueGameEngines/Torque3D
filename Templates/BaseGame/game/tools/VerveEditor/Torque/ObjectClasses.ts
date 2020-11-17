//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//
// Torque3D
//
//-----------------------------------------------------------------------------

function VTorque::isSceneObject( %object )
{
    return ( isObject( %object ) && %object.isMemberOfClass( "SceneObject" ) );
}

function VTorque::isCameraObject( %object )
{
    return ( isObject( %object ) && %object.isMemberOfClass( "GameBase" ) );
}

function VTorque::getLightObjectClass()
{
    return "LightBase";        
}

function VTorque::isLightObject( %object )
{
    return ( isObject( %object ) && %object.isMemberOfClass( "LightBase" ) );
}

function VTorque::isSpawnSphereObject( %object )
{
    return ( isObject( %object ) && %object.isMemberOfClass( "SpawnSphere" ) );
}

function VTorque::getParticleEffectClass()
{
    return "ParticleEmitterNode";        
}

function VTorque::isParticleEffect( %object )
{
    return ( isObject( %object ) && %object.isMemberOfClass( "ParticleEmitterNode" ) );        
}