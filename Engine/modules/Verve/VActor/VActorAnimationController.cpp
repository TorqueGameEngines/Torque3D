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
#include "VActorAnimationController.h"

#include "VActor.h"
#include "VActorData.h"
#include "VActorAnimationStates.h"

//-----------------------------------------------------------------------------

VActorAnimationController::VActorAnimationController( void ) :
        mObject( NULL )
{
    // Void.
}

VActorAnimationController::~VActorAnimationController( void )
{
    // Clear Table.
    mAnimationTable.clear();
}




//-----------------------------------------------------------------------------
//
// Initialisation Methods.
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//
// VActorAnimationController::initAnimationTable();
//
// ...
//
//-----------------------------------------------------------------------------
bool VActorAnimationController::initAnimationTable( void )
{
    // Valid Object?
    if ( !isValidObject() )
    {
        // No, Quit Now.
        return false;
    }

    // Clear the Table.
    mAnimationTable.clear();

    // Fetch Sequence List.
    VActorData::tAnimationSequenceVector *sequenceList = getObject()->getDataBlock()->getAnimationList();

    // Initialise the Animation States.
    for ( VActorData::tAnimationSequenceVector::iterator itr = sequenceList->begin();
          itr != sequenceList->end();
          itr++ )
    {
        // Fetch Sequence Definition.
        const VActorData::sAnimationSequence &animSequence = ( *itr );

        // Valid State?
        if ( animSequence.State )
        {
            // Register Animation.
            mAnimationTable.registerState( animSequence.State, animSequence.Priority );
        }
    }

    // Sort the Table.
    mAnimationTable.sort();

    // Valid.
    return true;
}

//-----------------------------------------------------------------------------
//
// VActorAnimationController::initAnimation( pThread, pIndex, pPosition, pTimeScale );
//
// ...
//
//-----------------------------------------------------------------------------
bool VActorAnimationController::initAnimation( sAnimationRef &pAnimation, const U32 &pIndex, const F32 &pPosition, const F32 &pTimeScale )
{
    // Valid Object & Sequence?
    if ( !isValidObject() || !isAnimationSequence( pIndex ) )
    {
        // No, Quit Now.
        return false;
    }

    // Store as Current Animation.
    pAnimation.Index = pIndex;

    // Initialise Thread.
    return initAnimationThread( pAnimation.Thread, pAnimation.Index, pPosition, pTimeScale );
}

//-----------------------------------------------------------------------------
//
// VActorAnimationController::initAnimationThread( pThread, pIndex, pPosition, pTimeScale );
//
// ...
//
//-----------------------------------------------------------------------------
bool VActorAnimationController::initAnimationThread( TSThread *&pThread, const U32 &pIndex, const F32 &pPosition, const F32 &pTimeScale )
{
    // Valid Object & Sequence?
    if ( !isValidObject() || !isAnimationSequence( pIndex ) )
    {
        // No, Quit Now.
        return false;
    }

    // Valid Thread?
    if ( !pThread )
    {
        // Create a Thread.
        pThread = getShapeInstance()->addThread();
    }

    // Init the Sequence.
    getShapeInstance()->setSequence( pThread, getAnimationSequence( pIndex ), pPosition );

    // Set Initial Time Scale.
    getShapeInstance()->setTimeScale( pThread, pTimeScale );

    // Valid.
    return true;
}

//-----------------------------------------------------------------------------
//
// VActorAnimationController::initBaseAnimation( pThread, pIndex, pPosition, pTimeScale );
//
// ...
//
//-----------------------------------------------------------------------------
bool VActorAnimationController::initBaseAnimation( const U32 &pIndex, const F32 &pPosition, const F32 &pTimeScale )
{
    return initAnimation( mBaseAnimation, pIndex, pPosition, pTimeScale );
}




//-----------------------------------------------------------------------------
//
// Accessor Methods.
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//
// VActorAnimationController::isValidObject();
//
// ...
//
//-----------------------------------------------------------------------------
bool VActorAnimationController::isValidObject( void )
{
    return ( mObject != NULL && mObject->getDataBlock() != NULL );
}

//-----------------------------------------------------------------------------
//
// VActorAnimationController::getObject();
//
// ...
//
//-----------------------------------------------------------------------------
VActor *VActorAnimationController::getObject( void )
{
    return mObject;
}

//-----------------------------------------------------------------------------
//
// VActorAnimationController::setObject( pObject );
//
// ...
//
//-----------------------------------------------------------------------------
void VActorAnimationController::setObject( VActor *pObject )
{
    // Set Object.
    mObject = pObject;

    // Set Table's Reference.
    mAnimationTable.setObject( pObject );
}

//-----------------------------------------------------------------------------
//
// VActorAnimationController::getShape();
//
// ...
//
//-----------------------------------------------------------------------------
const TSShape *VActorAnimationController::getShape( void )
{
    if ( !isValidObject() )
    {
        return NULL;
    }

    return mObject->getShape();
}

//-----------------------------------------------------------------------------
//
// VActorAnimationController::getShapeInstance();
//
// ...
//
//-----------------------------------------------------------------------------
TSShapeInstance *VActorAnimationController::getShapeInstance( void )
{
    if ( !isValidObject() )
    {
        return NULL;
    }

    return mObject->getShapeInstance();
}




//-----------------------------------------------------------------------------
//
// Animation Methods
//
//-----------------------------------------------------------------------------

void VActorAnimationController::update( const F32 &pDelta )
{
    // Valid Objects?
    if ( !isValidObject() )
    {
        // No, Quit Now.
        return;
    }

    // Update Animation State.
    mAnimationTable.execute();

    // Advance Threads.
    getShapeInstance()->advanceTime( pDelta, mBaseAnimation.Thread );
}

//-----------------------------------------------------------------------------
//
// VActorAnimationController::isAnimationSequence( pIndex );
//
// ...
//
//-----------------------------------------------------------------------------
bool VActorAnimationController::isAnimationSequence( const U32 &pIndex )
{
    return ( getAnimationSequence( pIndex ) != -1 );
}

//-----------------------------------------------------------------------------
//
// VActorAnimationController::getAnimationSequence( pIndex );
//
// ...
//
//-----------------------------------------------------------------------------
S32 VActorAnimationController::getAnimationSequence( const U32 &pIndex )
{
    // Valid Object?
    if ( !mObject || !mObject->getDataBlock() )
    {
        // No, Invalid Sequence.
        return -1;
    }

    // Return Sequence.
    return mObject->getDataBlock()->getAnimationSequence( pIndex );
}

//-----------------------------------------------------------------------------
//
// VActorAnimationController::getAnimation( pIndex );
//
// ...
//
//-----------------------------------------------------------------------------
U32 VActorAnimationController::getAnimation( void )
{
    // Base Animation Initialised?
    if ( !mBaseAnimation.Thread )
    {
        // Null.
        return U32_MAX;
    }

    // Return Current Animation.
    return mBaseAnimation.Index;
}

//-----------------------------------------------------------------------------
//
// VActorAnimationController::setAnimation( pIndex );
//
// ...
//
//-----------------------------------------------------------------------------
void VActorAnimationController::setAnimation( const U32 &pIndex )
{
    // Base Animation Initialised?
    if ( !mBaseAnimation.Thread || mBaseAnimation.Index == pIndex )
    {
        // Don't Update.
        return;
    }

    // Store as Current Animation.
    mBaseAnimation.Index = pIndex;

    // Fetch the Sequence.
    const S32 &sequence = getAnimationSequence( pIndex );

    // Valid?
    if ( sequence != -1 )
    {
        // Play the Sequence.
        getShapeInstance()->transitionToSequence( mBaseAnimation.Thread, sequence, 0.f, 0.15f, true );
        //getShapeInstance()->setSequence( mBaseAnimation.Thread, sequence, 0.f );
    }
}