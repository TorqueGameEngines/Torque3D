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
#include "VActorStateTable.h"
#include "VActor.h"

//-----------------------------------------------------------------------------

bool VActorStateTable::isRegisteredState( VActorState *pState )
{
    for ( tStateConstIterator itr = mStateVector.begin(); itr != mStateVector.end(); itr++ )
    {
        // Target State?
        if ( ( *itr ).State == pState )
        {
            // Yes.
            return true;
        }
    }

    // No.
    return false;
}

void VActorStateTable::clear( void )
{
    // Clear the States.
    mLastState    = NULL;
    mCurrentState = NULL;

    // Clear the State Vector.
    mStateVector.clear();
};

void VActorStateTable::sort( void )
{
    mStateVector.sort( &_onSortCallback );
}

void VActorStateTable::registerState( VActorState *pState, const F32 &pPriority )
{
    // Already a State?
    if ( isRegisteredState( pState ) )
    {
        // Exit Now.
        return;
    }

    // Create the Reference.
    sStateRef entry;
    entry.State    = pState;
    entry.Priority = pPriority;

    // Push to Back.
    mStateVector.push_back( entry );

    // Set Current?
    if ( mStateVector.size() == 1 )
    {
        // Set State.
        setState( pState );
    }
};

void VActorStateTable::setState( VActorState *pState )
{
    if ( !mObject || !pState || pState == mCurrentState )
    {
        // Invalid.
        return;
    }

    if ( mCurrentState )
    {
        // Exit.
        exit();

        // Exit the Old State.
        mCurrentState->exit( mObject );
    }

    // Update States.
    mLastState    = mCurrentState;
    mCurrentState = pState;

    // Enter.
    enter();

    // Enter the New State.
    pState->enter( mObject );
};

VActorState *VActorStateTable::execute( void )
{
    if ( !mObject || !mCurrentState )
    {
        // Invalid.
        return NULL;
    }

    for ( tStateConstIterator itr = mStateVector.begin(); itr != mStateVector.end(); itr++ )
    {
        // Fetch State Reference.
        const sStateRef &stateRef = ( *itr );

        // Enter State?
        if ( stateRef.State->execute( mObject ) )
        {
            // Set the State.
            setState( stateRef.State );

            // Return.
            return stateRef.State;
        }
    }

    // No Valid Entries, Ouch!
    Con::warnf( "VActorStateTable::execute() - No Valid Entries." );

    // Return Current State.
    return mCurrentState;
}

S32 QSORT_CALLBACK VActorStateTable::_onSortCallback( const VActorStateTable::sStateRef *pA, const VActorStateTable::sStateRef *pB )
{
    if ( pB->Priority > pA->Priority )
    {
        return 1;
    }
    else if ( pB->Priority < pA->Priority )
    {
        return -1;
    }

    return 0;
}