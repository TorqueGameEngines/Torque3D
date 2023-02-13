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
#include "Verve/Extension/GUI/VFadeTrack.h"
#include "Verve/Extension/GUI/VFadeEvent.h"

//-----------------------------------------------------------------------------
IMPLEMENT_CONOBJECT( VFadeTrack );
//-----------------------------------------------------------------------------

VFadeTrack::VFadeTrack( void )
{
    setLabel( "FadeTrack" );
}

//-----------------------------------------------------------------------------
//
// Controller Methods.
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// 
// VFadeTrack::onControllerEvent( pEvent );
// 
// When the controller's state changes, this method is called. If the
// controller is paused, or stops playing, then the fade control will cease
// playing. If the controller resumes play, the fade control will continue.
// 
// For a full list of possible events, see the 'eControllerEventType'
// declaration in VController.h.
// 
//-----------------------------------------------------------------------------
bool VFadeTrack::onControllerEvent( VController::eControllerEventType pEvent )
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

    // Fetch the next Event.
    VFadeEvent *event;
    if ( !getNextEvent( event ) )
    {
        // No Event.
        return true;
    }

    // Fetch GUI Control.
    VFadeControl *fadeControl = dynamic_cast<VFadeControl*>( Sim::findObject( "VFadeControlGui" ) );
    if ( !fadeControl )
    {
        // No Control.
        return true;
    }

    switch ( pEvent )
    {
        case VController::k_EventPlay:
            {
                // Play?
                const S32 &time = getControllerTime();
                fadeControl->mActive = ( time > event->getTriggerTime()
                                         && time < event->getFinishTime() ) ;

            } break;

        case VController::k_EventPause :
        case VController::k_EventStop :
            {

                // Pause.
                fadeControl->mActive = false;

            } break;
    }

    return true;
}

//-----------------------------------------------------------------------------
// 
// VFadeTrack::onControllerReset( pTime, pForward );
// 
// Reset the fade state of the fade control.
// 
//-----------------------------------------------------------------------------
void VFadeTrack::onControllerReset( const S32 &pTime, const bool &pForward )
{
    Parent::onControllerReset( pTime, pForward );

    // Fetch GUI Control.
    VFadeControl *fadeControl;
    if ( !Sim::findObject( "VFadeControlGUI", fadeControl ) )
    {
        // Invalid.
        return;
    }

    VFadeEvent *event;
    if ( !getNextEvent( event ) )
    {
        // No Events.
        return;
    }

    // Apply Settings.
    fadeControl->mActive      = false;
    fadeControl->mFadeType    = event->getFadeType();
    fadeControl->mDuration    = event->getDuration();
    fadeControl->mElapsedTime = getMax( pTime - event->getTriggerTime(), 0 );
}