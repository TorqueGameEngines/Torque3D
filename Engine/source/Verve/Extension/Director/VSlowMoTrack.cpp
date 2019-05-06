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
#include "Verve/Extension/Director/VSlowMoTrack.h"

//-----------------------------------------------------------------------------
IMPLEMENT_CONOBJECT( VSlowMoTrack );
//-----------------------------------------------------------------------------

VSlowMoTrack::VSlowMoTrack( void )
{
    setLabel( "SlowMoTrack" );
}

//-----------------------------------------------------------------------------
//
// Controller Methods.
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// 
// VSlowMoTrack::onControllerEvent( pEvent );
// 
// ...
// 
// For a full list of possible events, see the 'eControllerEventType'
// declaration in VController.h.
// 
//-----------------------------------------------------------------------------
bool VSlowMoTrack::onControllerEvent( VController::eControllerEventType pEvent )
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
        case VController::k_EventStop :
            {

                // Reset Time Scale.
                getController()->setTimeScale( ( isControllerPlayingForward() ) ? 1.f : -1.f );

            } break;
    }

    return true;
}

//-----------------------------------------------------------------------------
// 
// VSlowMoTrack::onControllerReset( pTime, pForward );
// 
// ...
// 
//-----------------------------------------------------------------------------
void VSlowMoTrack::onControllerReset( const S32 &pTime, const bool &pForward )
{
    // Parent Reset.
    Parent::onControllerReset( pTime, pForward );

    // Reset Time Scale.
    getController()->setTimeScale( ( pForward ) ? 1.f : -1.f );
}