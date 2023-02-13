//-----------------------------------------------------------------------------
// Verve
// Copyright (C) 2014 - Violent Tulip
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//-----------------------------------------------------------------------------
#include "Verve/Extension/Game/VSpawnSphereSpawnTargetTrack.h"
#include "Verve/Torque/TSpawnSphere.h"

//-----------------------------------------------------------------------------
IMPLEMENT_CONOBJECT( VSpawnSphereSpawnTargetTrack );
//-----------------------------------------------------------------------------

VSpawnSphereSpawnTargetTrack::VSpawnSphereSpawnTargetTrack( void )
{
   mDespawnOnStop = false;
   mDespawnOnLoop = false;
   setLabel( "SpawnTargetTrack" );
}

void VSpawnSphereSpawnTargetTrack::initPersistFields()
{
   docsURL;
    // Parent Call.
    Parent::initPersistFields();

    addField( "DespawnOnLoop", TypeBool, Offset( mDespawnOnLoop, VSpawnSphereSpawnTargetTrack ), "Despawn all targets when the Controller loops?" );
    addField( "DespawnOnStop", TypeBool, Offset( mDespawnOnStop, VSpawnSphereSpawnTargetTrack ), "Despawn all targets when the Controller stops playing?" );
}

//-----------------------------------------------------------------------------
//
// Controller Methods.
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// 
// VSpawnSphereSpawnTargetTrack::onControllerEvent( pEvent );
// 
// For a full list of possible events, see the 'eControllerEventType'
// declaration in VController.h.
// 
//-----------------------------------------------------------------------------
bool VSpawnSphereSpawnTargetTrack::onControllerEvent( VController::eControllerEventType pEvent )
{
    if ( !Parent::onControllerEvent( pEvent ) )
    {
        // Skip.
        return false;
    }

    // Enabled?
    if ( !isEnabled() )
    {
        // Continue Processing Events.
        return true;
    }

    switch ( pEvent )
    {
        case VController::k_EventLoop :
            {
                if ( mDespawnOnLoop )
                {
                    despawnTargets();
                }

            } break;

        case VController::k_EventStop :
            {
                if ( mDespawnOnStop )
                {
                    despawnTargets();
                }

            } break;
    }

    return true;
}

//-----------------------------------------------------------------------------
//
// Spawn Methods.
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// 
// VSpawnSphereSpawnTargetTrack::spawnTarget( pTime, pForward );
// 
// Spawn an Object.
// 
//-----------------------------------------------------------------------------
void VSpawnSphereSpawnTargetTrack::spawnTarget( void )
{
    VTorque::SpawnSphereType *object;
    if ( !getSceneObject( object ) )
    {
        return;
    }

    // Spawn the Object.
    SimObject *spawnedObject = object->spawnObject();

    // Scene Object?
    VTorque::SceneObjectType *sceneObject = dynamic_cast<VTorque::SceneObjectType*>( spawnedObject );
    if ( sceneObject )
    {
        sceneObject->setPosition( object->getPosition() );
    }

    // Valid?
    if ( spawnedObject )
    {
        // Add Reference.
        mSpawnList.addObject( spawnedObject );
    }
}

//-----------------------------------------------------------------------------
// 
// VSpawnSphereSpawnTargetTrack::despawnTargets();
// 
// Despawn all of the objects spawned by this track.
// 
//-----------------------------------------------------------------------------
void VSpawnSphereSpawnTargetTrack::despawnTargets( void )
{
    while( mSpawnList.size() > 0 )
    {
        // Fetch the Last Object
        SimObject *object = mSpawnList.last();
        // Remove it.
        mSpawnList.popObject();

        // Delete the Object.
        object->deleteObject();
    }
}
