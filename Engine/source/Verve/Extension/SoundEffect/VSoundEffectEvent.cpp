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
#include "Verve/Core/VGroup.h"
#include "Verve/Extension/SoundEffect/VSoundEffectEvent.h"
#include "Verve/Extension/SoundEffect/VSoundEffectTrack.h"

#include "console/consoleTypes.h"

//-----------------------------------------------------------------------------
IMPLEMENT_CONOBJECT( VSoundEffectEvent );
//-----------------------------------------------------------------------------

VSoundEffectEvent::VSoundEffectEvent( void ) : 
        mSoundEffect( NULL )
{
    setLabel( "SoundEvent" );
}

void VSoundEffectEvent::initPersistFields()
{
   docsURL;
    Parent::initPersistFields();

    addProtectedField( "SoundEffect", TYPEID<VTorque::SoundEffectType>(), Offset( mSoundEffect, VSoundEffectEvent ), &setSoundData, &defaultProtectedGetFn, "" );
}

//-----------------------------------------------------------------------------
//
// Callback Methods.
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// 
// VSoundEffectEvent::onTrigger( pTime, pDelta );
// 
// Play the target sound effect. If this track belongs to a SceneObjectGroup,
// then the sound will play with the reference object's transform. If this is
// not the case, then a 2D sound will be played.
// 
//-----------------------------------------------------------------------------
void VSoundEffectEvent::onTrigger( const S32 &pTime, const S32 &pDelta )
{
    Parent::onTrigger( pTime, pDelta );

    // Fetch Track.
    VSoundEffectTrack *track;
    if ( !getTrack( track ) )
    {
        return;
    }

    // Position & Pitch.
    U32 position = mAbs( ( pTime + pDelta ) - getStartTime() );
    F32 pitch    = mFabs( getControllerTimeScale() );
    if ( position < SFXStartBuffer )
    {
        // Zero.
        position = 0;
    }

    VSceneObjectGroup *group;
    if ( getGroup( group ) )
    {
        // Play Sound With Reference.
        track->mSource = VTorque::playSound( mSoundEffect, group->getSceneObject(), position, pitch );
    }
    else
    {
        // Play Sound.
        track->mSource = VTorque::playSound( mSoundEffect, position, pitch );
    }
}

//-----------------------------------------------------------------------------
//
// Property Methods.
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// 
// VSoundEffectEvent::setDuration( pDuration );
// 
// This event's duration is always set to the sound object's duration.
// 
//-----------------------------------------------------------------------------
void VSoundEffectEvent::setDuration( const S32 &pDuration )
{
    // Clear Duration.
    mDuration = VTorque::getSoundDuration( mSoundEffect );
}

//-----------------------------------------------------------------------------
//
// Static Field Methods.
//
//-----------------------------------------------------------------------------

bool VSoundEffectEvent::setSoundData( void *pObject, const char *pArray, const char *pData )
{
    // Fetch Event.
    VSoundEffectEvent *event = static_cast<VSoundEffectEvent*>( pObject );

    // Use Object.
    event->mSoundEffect = dynamic_cast<VTorque::SoundEffectType*>( Sim::findObject( pData ) );

    // Set Duration.
    event->setDuration( 0 );

    return false;
}
