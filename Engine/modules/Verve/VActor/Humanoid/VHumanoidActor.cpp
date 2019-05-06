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
#include "VHumanoidActor.h"

#include "core/stream/bitStream.h"

//-----------------------------------------------------------------------------
IMPLEMENT_CO_NETOBJECT_V1( VHumanoidActor );
//-----------------------------------------------------------------------------

VHumanoidActor::VHumanoidActor( void )
{
    // Void.
}

VHumanoidActor::~VHumanoidActor( void )
{
    // Void.
}




//-----------------------------------------------------------------------------
//
// Initialisation Methods.
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//
// VHumanoidActor::onNewDataBlock( pDataBlock );
//
// ...
//
//-----------------------------------------------------------------------------
bool VHumanoidActor::onNewDataBlock( GameBaseData *pDataBlock, bool pReload )
{
    // Store DataBlock Reference.
    mDataBlock = dynamic_cast<VHumanoidActorData*>( pDataBlock );

    // Valid Data?
    if ( !mDataBlock || !Parent::onNewDataBlock( pDataBlock, pReload ) )
    {
        // Invalid Data.
        return false;
    }

    // Initialise the Controllers.
    if ( !initAnimationController() || !initPhysicsController() )
    {
        // Invalid.
        return false;
    }

    // Initialise the Base Animation Thread.
    mAnimationController.initBaseAnimation( VHumanoidActorData::k_IdleAnimation, 0.f, 1.f );
    // Initialise the Arm Animation Thread.
    mAnimationController.initArmAnimation( VHumanoidActorData::k_ArmsUpDownAnimation, 0.5f, 1.f );

    /*
    // Initialise Head Threads.
    initAnimationSequence( VHumanoidActorData::k_HeadHorizontalAnimation, mHeadAnimation.HThread, 0.5f );
    initAnimationSequence( VHumanoidActorData::k_HeadVerticalAnimation,   mHeadAnimation.VThread, 0.5f );
    */

    // Valid Data.
    return true;
}




//-----------------------------------------------------------------------------
//
// Update Methods.
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//
// VHumanoidActor::processTick( pMove );
//
// ...
//
//-----------------------------------------------------------------------------
void VHumanoidActor::processTick( const Move *pMove )
{
    // Parent Call.
    Parent::processTick( pMove );

    // Update Physics.
    mPhysicsController.update( TickSec, pMove );

    // Update Container.
    updateContainer();
}

//-----------------------------------------------------------------------------
//
// VHumanoidActor::interpolateTick( pDelta );
//
// ...
//
//-----------------------------------------------------------------------------
void VHumanoidActor::interpolateTick( F32 pDelta )
{
    // Parent Call.
    Parent::interpolateTick( pDelta );

    // Update Physics.
    mPhysicsController.interpolateTick( pDelta );
}

//-----------------------------------------------------------------------------
//
// VHumanoidActor::advanceTime( pDelta );
//
// ...
//
//-----------------------------------------------------------------------------
void VHumanoidActor::advanceTime( F32 pDelta )
{
    // Parent Call.
    Parent::advanceTime( pDelta );

    // Valid Animation Controller?
    if ( getAnimationController() )
    {
        // Update Animations.
        getAnimationController()->update( pDelta );
    }
}

//-----------------------------------------------------------------------------
//
// VHumanoidActor::packUpdate( pConnection, pMask, pStream );
//
// ...
//
//-----------------------------------------------------------------------------
U32 VHumanoidActor::packUpdate( NetConnection *pConnection, U32 pMask, BitStream *pStream )
{
    // Parent Call.
    U32 retMask = Parent::packUpdate( pConnection, pMask, pStream );

    // Physics Controller?
    if ( pStream->writeFlag( pMask & PhysicsMask ) )
    {
        // Pack Physics.
        retMask &= mPhysicsController.packUpdate( pConnection, pMask, pStream );
    }

    return retMask;
}

//-----------------------------------------------------------------------------
//
// VHumanoidActor::unpackUpdate( pConnection, pStream );
//
// ...
//
//-----------------------------------------------------------------------------
void VHumanoidActor::unpackUpdate( NetConnection *pConnection, BitStream *pStream )
{
    // Parent Call.
    Parent::unpackUpdate( pConnection, pStream );

    // Physics Controller?
    if ( pStream->readFlag() )
    {
        // Unpack Physics.
        mPhysicsController.unpackUpdate( pConnection, pStream );
    }
}




//-----------------------------------------------------------------------------
//
// Animation Methods.
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//
// VHumanoidActor::initAnimationController();
//
// ...
//
//-----------------------------------------------------------------------------
bool VHumanoidActor::initAnimationController( void )
{
    // Reference Object.
    mAnimationController.setObject( this );
    // Initialise.
    return mAnimationController.initAnimationTable();
}

//-----------------------------------------------------------------------------
//
// VHumanoidActor::getAnimationController();
//
// ...
//
//-----------------------------------------------------------------------------
VActorAnimationController *VHumanoidActor::getAnimationController( void )
{
    return &mAnimationController;
}




//-----------------------------------------------------------------------------
//
// VHumanoidActor::initPhysicsController();
//
// ...
//
//-----------------------------------------------------------------------------
bool VHumanoidActor::initPhysicsController( void )
{
    // Initialise.
    return mPhysicsController.initPhysicsController( this );
}

//-----------------------------------------------------------------------------
//
// VHumanoidActor::getAnimationController();
//
// ...
//
//-----------------------------------------------------------------------------
VActorPhysicsController *VHumanoidActor::getPhysicsController( void )
{
    return &mPhysicsController;
}