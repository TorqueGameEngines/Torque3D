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
#include "Verve/Extension/PostEffect/VPostEffectToggleEvent.h"
#include "Verve/Extension/PostEffect/VPostEffectToggleTrack.h"
#include "Verve/Extension/Camera/VCameraGroup.h"

#include "console/consoleTypes.h"

//-----------------------------------------------------------------------------
IMPLEMENT_CONOBJECT( VPostEffectToggleEvent );
//-----------------------------------------------------------------------------

VPostEffectToggleEvent::VPostEffectToggleEvent( void ) : 
        mEventType( VSharedEnum::k_ActionTurnOn )
{
    setLabel( "ToggleEvent" );
}

void VPostEffectToggleEvent::initPersistFields()
{
   docsURL;
    Parent::initPersistFields();

    addField( "Action", TYPEID<VActionToggle>(), Offset( mEventType, VPostEffectToggleEvent ) );
}

//-----------------------------------------------------------------------------
//
// Callback Methods.
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// 
// VPostEffectToggleEvent::onTrigger( pTime, pDelta );
// 
// Only enable this effect if the parent group is currently active. 
// 
//-----------------------------------------------------------------------------
void VPostEffectToggleEvent::onTrigger( const S32 &pTime, const S32 &pDelta )
{
    Parent::onTrigger( pTime, pDelta );

    // Fetch Parent Objects.
    VCameraGroup           *group;
    VPostEffectToggleTrack *track;
    if ( ( !getGroup( group ) || !group->isActive() ) || !getTrack( track ) )
    {
        // Quit.
        return;
    }

    // Turn On?
    const bool turnOn = ( mEventType == VSharedEnum::k_ActionTurnOn );

    // Enable Effect.
    VTorque::setPostEffectOn( track->getPostEffect(), turnOn );
}
