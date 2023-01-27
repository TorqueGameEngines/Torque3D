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
#include "VActorData.h"

#include "console/consoleTypes.h"
#include "core/stream/bitStream.h"

//-----------------------------------------------------------------------------
IMPLEMENT_CO_DATABLOCK_V1( VActorData );
//-----------------------------------------------------------------------------

VActorData::VActorData( void ) :
        mMaxStepHeight( 1.f ),
        mRunSpeed( 6.f ),
        mSubmergeCoverage( 0.25f )
{
    // Setup Shadowing.
    shadowSize = 256;
    shadowProjectionDistance = 14.0f;

    VECTOR_SET_ASSOCIATION( mAnimationSequenceList );
    VECTOR_SET_ASSOCIATION( mPhysicsList );
}

VActorData::~VActorData( void )
{
    // Void.
}

void VActorData::initPersistFields()
{
   docsURL;
    Parent::initPersistFields();

    addField( "MaxStepHeight",    TypeF32, Offset( mMaxStepHeight,    VActorData ) );
    addField( "RunSpeed",         TypeF32, Offset( mRunSpeed,         VActorData ) );

    addField( "SubmergeCoverage", TypeF32, Offset( mSubmergeCoverage, VActorData ) );
}

//-----------------------------------------------------------------------------

bool VActorData::initAnimationSequenceList( const S32 &pSize, const sAnimationSequence *pTable )
{
    if ( !mShape )
    {
        // Sanity!
        return false;
    }

    // Clear the List.
    mAnimationSequenceList.clear();

    // Initialise each Animation Sequence.
    for ( U32 i = 0; i < pSize; i++ )
    {
        // Fetch Sequence Definition.
        const sAnimationSequence &animSequenceDef = pTable[i];

        // Update Animation Details.
        sAnimationSequence animSequence = animSequenceDef;
        // Find Sequence.
        animSequence.Sequence = mShape->findSequence( animSequenceDef.Name );

        // Store.
        mAnimationSequenceList.push_back( animSequence );
    }

    return true;
}

bool VActorData::initAnimationTransitionList( const S32 &pSize, const sAnimationTransition *pTable )
{
    if ( !mShape )
    {
        // Sanity!
        return false;
    }

    // Clear the List.
    mAnimationTransitionList.clear();

    // Store each Animation Transition.
    for ( U32 i = 0; i < pSize; i++ )
    {
        // Store.
        mAnimationTransitionList.push_back( pTable[i] );
    }

    return true;
}

bool VActorData::initPhysicsStateList( const S32 &pSize, const sPhysicsState *pTable )
{
    // Clear the List.
    mPhysicsList.clear();

    // Initialise each Animation Sequence.
    for ( U32 i = 0; i < pSize; i++ )
    {
        // Store.
        mPhysicsList.push_back( pTable[i] );
    }

    return true;
}

//-----------------------------------------------------------------------------

void VActorData::packData( BitStream *pStream )
{
    Parent::packData( pStream );

    pStream->write( mMaxStepHeight );
    pStream->write( mRunSpeed );

    pStream->write( mSubmergeCoverage );
}

void VActorData::unpackData( BitStream *pStream )
{
    Parent::unpackData( pStream );

    pStream->read( &mMaxStepHeight );
    pStream->read( &mRunSpeed );

    pStream->read( &mSubmergeCoverage );
}

//-----------------------------------------------------------------------------

S32 VActorData::getAnimationSequence( const U32 &pIndex )
{
    // Iterate over the Registered Animations.
    for ( tAnimationSequenceVector::iterator itr = mAnimationSequenceList.begin(); itr != mAnimationSequenceList.end(); itr++ )
    {
        // Fetch Sequence Defintion.
        const sAnimationSequence &animSequence = ( *itr );

        // Target Index?
        if ( animSequence.Index == pIndex )
        {
            // Return Sequence ID.
            return animSequence.Sequence;
        }
    }

    // Invalid Sequence.
    return -1;
};
