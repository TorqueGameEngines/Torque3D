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
#include "Verve/Core/VEvent.h"
#include "Verve/Core/VGroup.h"
#include "Verve/Core/VTrack.h"

#include "console/consoleTypes.h"
#include "math/mMathFn.h"

//-----------------------------------------------------------------------------
IMPLEMENT_CONOBJECT( VEvent );
//-----------------------------------------------------------------------------

VEvent::VEvent( void ) : 
        mIsPlaying( false ),
        mTriggered( false ),
        mTriggerTime( 0 ),
        mDuration( 0 )
{
    setLabel( "DefaultEvent" );
}

void VEvent::initPersistFields()
{
   docsURL;
    Parent::initPersistFields();

    addProtectedField( "TriggerTime", TypeS32, Offset( mTriggerTime, VEvent ), &setTriggerTime, &defaultProtectedGetFn, "The time that this event is triggered." );
    addProtectedField( "Duration",    TypeS32, Offset( mDuration,    VEvent ), &setDuration,    &defaultProtectedGetFn, "The total duration that this event plays for." );
}

//-----------------------------------------------------------------------------
//
// Controller Methods.
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// 
// VEvent::onControllerReset( pTime, pForward );
// 
// Reset the status of the event. If the given time is between the event's
// start and finish times, then the isPlaying flag will be true. This means
// that the event is free to be triggered upon playback.
// 
//-----------------------------------------------------------------------------
void VEvent::onControllerReset( const S32 &pTime, const bool &pForward )
{
    // Reset Status.
    mIsPlaying = ( pTime > mTriggerTime && pTime < ( mTriggerTime + mDuration ) );
    mTriggered = false;
}

//-----------------------------------------------------------------------------
// 
// VEvent::onControllerUpdate( pTime, pDelta )
// 
// Integrate is only called when this event is the Next Event for the parent
// track. For each track, there is only ever *one* event being integrated - the
// event that needs to be triggered next.
//
// If the event has a duration greater than 0, then this event will continue to
// integrate until its time is up, or the controller finishes playing
// (whichever happens first).
// 
// If a value of true is returned, then this event will continue to integrate
// until a value of false is returned to the parent track. When this happens,
// this event ceases to be the track's Next Event and will not continue
// updating.
// 
//-----------------------------------------------------------------------------
bool VEvent::onControllerUpdate( const S32 &pTime, const S32 &pDelta )
{
    if ( !isEnabled() )
    {
        return false;
    }

    const S32  newTime    = ( pTime + pDelta );
    const S32 &startTime  = getStartTime();
    const S32 &finishTime = getFinishTime();

    if ( !mIsPlaying || !mTriggered )
    {
        if ( !mIsPlaying )
        {
            if ( ( pDelta > 0 && newTime < startTime )
                 || ( pDelta < 0 && newTime > startTime ) )
            {
                // Not Time to Trigger.
                return true;
            }

            if ( ( pDelta > 0 && pTime > startTime )
                 || ( pDelta < 0 && pTime < startTime ) )
            {
                //AssertFatal( false, "VEvent::onControllerUpdate() - Event has been skipped." );
                return false;
            }
        }

        if ( !mTriggered )
        {
            // Play and Trigger.
            mIsPlaying = ( mDuration > 0 );
            mTriggered = true;

            // Callback.
            onTrigger( pTime, pDelta );

            if ( mDuration == 0 )
            {
                // Stop Integrating.
                return false;
            }

            // Return Here.
            // Note: If Duration is non-zero this event will continue to update
            //       so that VEvent:: onUpdate is processed for the full event
            //       duration.
            return ( mDuration != 0 );
        }
    }

    // Complete?
    const bool isComplete = ( ( pDelta > 0 && newTime > finishTime )
                               || ( pDelta < 0 && newTime < finishTime ) );

    if ( !isComplete )
    {
        // Callback.
        onUpdate( pTime, pDelta );
    }
    else
    {
        // Complete.
        mIsPlaying = false;

        // Callback.
        onComplete( pTime, pDelta );
    }

    // Continue?
    return !isComplete;
}

//-----------------------------------------------------------------------------
//
// Callback Methods.
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// 
// VEvent::onTrigger( pTime, pDelta );
// 
// This method is called when an event is due to be triggered. This method is
// meant to be overloaded by derived classes.
// 
// For examples of what an event might do, please refer to some of the included
// events with Verve.
// 
//-----------------------------------------------------------------------------
void VEvent::onTrigger( const S32 &pTime, const S32 &pDelta )
{
    // Void.
}

//-----------------------------------------------------------------------------
// 
// VEvent::onUpdate( pTime, pDelta );
// 
// This method is called each tick once an event has been triggered and ceases
// to be called when it is completed. This method is meant to be overloaded by
// derived classes.
// 
//-----------------------------------------------------------------------------
void VEvent::onUpdate( const S32 &pTime, const S32 &pDelta )
{
    // Void.
}

//-----------------------------------------------------------------------------
// 
// VEvent::onComplete( pTime, pDelta );
// 
// This method is called once an event has finished being updated. It is not
// called on events that have a duration of 0. This method is meant to be
// overloaded by derived classes.
// 
//-----------------------------------------------------------------------------
void VEvent::onComplete( const S32 &pTime, const S32 &pDelta )
{
    // Void.
}

//-----------------------------------------------------------------------------
//
// Property Methods.
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// 
// VEvent::getGroup();
// 
// Returns the parent group.
// 
//-----------------------------------------------------------------------------
VGroup *VEvent::getGroup( void )
{
    VTrack *track = getTrack();
    if ( track )
    {
        return track->getGroup();
    }

    return NULL;
}

//-----------------------------------------------------------------------------
// 
// VEvent::getTrack();
// 
// Returns the parent track.
// 
//-----------------------------------------------------------------------------
VTrack *VEvent::getTrack( void )
{
    return dynamic_cast<VTrack*>( mParentNode );
}

//-----------------------------------------------------------------------------
// 
// VEvent::getNextEvent();
// 
// Returns the next event.
// 
//-----------------------------------------------------------------------------
VEvent *VEvent::getNextEvent( void )
{
    if ( !isControllerPlayingForward() )
    {
        return dynamic_cast<VEvent*>( mSiblingPrevNode );
    }

    return dynamic_cast<VEvent*>( mSiblingNextNode );
}

//-----------------------------------------------------------------------------
// 
// VEvent::getPreviousEvent();
// 
// Returns the previous event.
// 
//-----------------------------------------------------------------------------
VEvent *VEvent::getPreviousEvent( void )
{
    if ( !isControllerPlayingForward() )
    {
        return dynamic_cast<VEvent*>( mSiblingNextNode );
    }

    return dynamic_cast<VEvent*>( mSiblingPrevNode );
}

//-----------------------------------------------------------------------------
// 
// VEvent::getStartTime();
// 
// Returns the time, in milliseconds, that the event is due to trigger.
// 
//-----------------------------------------------------------------------------
S32 VEvent::getStartTime( void )
{
    return ( mTriggerTime + ( !isControllerPlayingForward() * mDuration ) );
}

//-----------------------------------------------------------------------------
// 
// VEvent::getFinishTime();
// 
// Returns the time, in milliseconds, that the event will cease updating.
// 
//-----------------------------------------------------------------------------
S32 VEvent::getFinishTime( void )
{
    return ( mTriggerTime + ( isControllerPlayingForward() * mDuration ) );
}

//-----------------------------------------------------------------------------
// 
// VEvent::setTriggerTime( pTime );
// 
// Apply the given trigger time to the object.
// 
// If the project was built using the VT_EDITOR preprocessor argument, then
// the validity of the passed value is verified. It also cannot be changed
// while the controller is playing.
// 
//-----------------------------------------------------------------------------
void VEvent::setTriggerTime( const S32 &pTime )
{
#ifdef VT_EDITOR

    VTrack *track = getTrack();
    if ( !track )
    {
        // Apply Time.
        mTriggerTime = pTime;

        return;
    }

    if ( track->isControllerPlaying() )
    {
        // Don't Change While Playing.
        return;
    }

    /*
    // Check For Overlap.
    for ( ITreeNode *node = mChildNode; node != NULL; node = node->mSiblingNextNode )
    {
        VEvent *event = ( VEvent* )node;
        if ( event == this )
        {
            // Skip.
            continue;
        }

        const U32 startTime  = getStartTime();
        const U32 finishTime = getFinishTime();

        if ( ( pTime > startTime && pTime < finishTime )
             || ( ( pTime + mDuration ) > startTime && ( pTime + mDuration ) < finishTime )
             || ( pTime < startTime && ( pTime + mDuration ) > finishTime ) )
        {
            // Overlap!
            return;
        }
    }
    */

    // Apply Time.
    mTriggerTime = mClamp( pTime, 0, getControllerDuration() );

    // Sort Events.
    track->sort();

    // Reset Track.
    track->onControllerReset( getControllerTime(), isControllerPlayingForward() );

#else

    // Apply Time.
    mTriggerTime = pTime;

#endif
}

//-----------------------------------------------------------------------------
// 
// VEvent::setDuration( pDuration );
// 
// Apply the given duration time to the object.
// 
// If the project was built using the VT_EDITOR preprocessor argument, then
// the validity of the passed value is verified. It also cannot be changed
// while the controller is playing.
// 
//-----------------------------------------------------------------------------
void VEvent::setDuration( const S32 &pDuration )
{
#ifdef VT_EDITOR

    if ( isControllerPlaying() )
    {
        // Don't Change While Playing.
        return;
    }

#endif

    // Apply Duration.
    mDuration = pDuration;
}
