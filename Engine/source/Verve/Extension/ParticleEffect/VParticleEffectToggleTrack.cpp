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
#include "Verve/Extension/ParticleEffect/VParticleEffectToggleTrack.h"
#include "Verve/Extension/ParticleEffect/VParticleEffectToggleEvent.h"

//-----------------------------------------------------------------------------
IMPLEMENT_CONOBJECT( VParticleEffectToggleTrack );
//-----------------------------------------------------------------------------

VParticleEffectToggleTrack::VParticleEffectToggleTrack( void )
{
    setLabel( "ToggleTrack" );
}

//-----------------------------------------------------------------------------
//
// Controller Methods.
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// 
// VParticleEffectToggleTrack::onControllerReset( pTime, pForward );
// 
// Enable or Disable the particle effect after a reset.
// 
//-----------------------------------------------------------------------------
void VParticleEffectToggleTrack::onControllerReset( const S32 &pTime, const bool &pForward )
{
    // Default Reset.
    Parent::onControllerReset( pTime, pForward );

    VParticleEffectToggleEvent  *event;
    VTorque::ParticleEffectType *particleEffect;
    if ( getSceneObject( particleEffect ) && getPreviousEvent( event ) )
    {
        // Turn On?
        const bool turnOn = ( event->mEventType == VSharedEnum::k_ActionTurnOn );

        // Toggle the Particle Effect.
        VTorque::setParticleEffectOn( particleEffect, turnOn );
    }
}