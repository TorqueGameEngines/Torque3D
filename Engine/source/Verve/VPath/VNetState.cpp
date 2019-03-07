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
#include "VNetState.h"

//-----------------------------------------------------------------------------

U32 VNetState::gInvalidMask = 0;

//-----------------------------------------------------------------------------

VNetState::VNetState() :
        mMask( 0 )
{
}

VNetState::~VNetState( void )
{
    for ( VNetState::iterator itr = begin(); itr != end(); itr++ )
    {
        // Fetch info.
        VNetStateInfo *state = ( *itr );
        // Delete State.
        delete state;
    }

    // Clear.
    clear();
}

//-----------------------------------------------------------------------------
//
// Connection Methods.
//
//-----------------------------------------------------------------------------

bool VNetState::isConnection( NetConnection *pConnection )
{
    for ( VNetState::iterator itr = begin(); itr != end(); itr++ )
    {
        VNetStateInfo *state = ( *itr );
        if ( state->Connection == pConnection )
        {
            // Valid.
            return true;
        }
    }

    // Invalid.
    return false;
}

void VNetState::addConnection( NetConnection *pConnection )
{
    // Init State.
    VNetStateInfo *state = new VNetStateInfo( pConnection, mMask );
    // Add.
    push_back( state );
}

void VNetState::clearConnection( NetConnection *pConnection )
{
    for ( VNetState::iterator itr = begin(); itr != end(); itr++ )
    {
        VNetStateInfo *state = ( *itr );
        if ( state->Connection == pConnection )
        {
            // Delete.
            delete state;
            // Erase.
            erase( itr );
            // Quit.
            return;
        }
    }
}

//-----------------------------------------------------------------------------
//
// Mask Methods.
//
//-----------------------------------------------------------------------------

VNetStateInfo *VNetState::getState( NetConnection *pConnection )
{
    for ( VNetState::iterator itr = begin(); itr != end(); itr++ )
    {
        VNetStateInfo *state = ( *itr );
        if ( state->Connection == pConnection )
        {
            return state;
        }
    }

    return NULL;
}

void VNetState::setMaskBits( const U32 &pMask )
{
    // Apply Mask.
    mMask |= pMask;

    for ( VNetState::iterator itr = begin(); itr != end(); itr++ )
    {
        // Fetch info.
        VNetStateInfo *state = ( *itr );
        // Apply Mask.
        state->Mask |= pMask;
    }
}

void VNetState::clearMaskBits( const U32 &pMask )
{
    // Clear Mask.
    mMask &= ~pMask;

    for ( VNetState::iterator itr = begin(); itr != end(); itr++ )
    {
        // Fetch info.
        VNetStateInfo *state = ( *itr );
        // Clear Mask.
        state->Mask &= ~pMask;
    }
}