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
#include "Verve/Extension/GUI/VFadeEvent.h"

//-----------------------------------------------------------------------------
IMPLEMENT_CONOBJECT( VFadeEvent );
//-----------------------------------------------------------------------------

VFadeEvent::VFadeEvent( void )
{
    setLabel( "FadeEvent" );
}

//-----------------------------------------------------------------------------
//
// Callback Methods.
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// 
// VFadeEvent::onTrigger( pTime, pDelta );
// 
// Start the fade sequence if a valid fade control can be found.
// 
//-----------------------------------------------------------------------------
void VFadeEvent::onTrigger( const S32 &pTime, const S32 &pDelta )
{
    Parent::onTrigger( pTime, pDelta );

    // Fetch GUI Control.
    VFadeControl *fadeControl;
    if ( !Sim::findObject( "VFadeControlGUI", fadeControl ) )
    {
        // Invalid.
        return;
    }

    // Start Fade.
    fadeControl->start( getFadeType(), mDuration );

    // Set Elapsed Time.
    fadeControl->mElapsedTime = mAbs( pTime - getStartTime() );
}

//-----------------------------------------------------------------------------
// 
// VFadeEvent::onComplete( pTime, pDelta );
// 
// Tidy up the fade control once the event has finished.
// 
//-----------------------------------------------------------------------------
void VFadeEvent::onComplete( const S32 &pTime, const S32 &pDelta )
{
    Parent::onTrigger( pTime, pDelta );

    // Fetch GUI Control.
    VFadeControl *fadeControl;
    if ( !Sim::findObject( "VFadeControlGUI", fadeControl ) )
    {
        // Invalid.
        return;
    }

    // Set Elapsed Time.
    fadeControl->mElapsedTime = mDuration;
}

//-----------------------------------------------------------------------------
//
// Property Methods.
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// 
// VFadeEvent::getFadeType();
// 
// Returns the type of fade (in or out) that this event will use. Zero and Even
// indices will Fade Out, while Odd numbers will Fade In.
// 
//-----------------------------------------------------------------------------
VFadeControl::eFadeType VFadeEvent::getFadeType( void )
{
    if ( !isControllerPlayingForward() )
    {
        return ( getIndex() % 2 == 0 ) ? VFadeControl::k_TypeOut : VFadeControl::k_TypeIn;
    }

    return ( getIndex() % 2 == 0 ) ? VFadeControl::k_TypeIn : VFadeControl::k_TypeOut;
}