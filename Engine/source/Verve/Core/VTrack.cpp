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
#include "Verve/Core/VTrack.h"
#include "Verve/Core/VGroup.h"
#include "Verve/Core/VController.h"
#include "math/mMath.h"

//-----------------------------------------------------------------------------
IMPLEMENT_CONOBJECT( VTrack );
//-----------------------------------------------------------------------------

VTrack::VTrack( void ) :
        mNextEvent( NULL )
{
    setLabel( "DefaultTrack" );
}

//-----------------------------------------------------------------------------
//
// Tree Methods.
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// 
// VTrack::onAttach();
// 
// This callback subscribes this object to the controller's event signal.
// 
//-----------------------------------------------------------------------------
void VTrack::onAttach( void )
{
    Parent::onAttach();

    // Valid Controller?
    if ( getController() )
    {
        // Subscribe to Updates.
        getController()->getControllerUpdateSignal().notify( this, &VTrack::onControllerUpdate );

        // Subscribe to Events.
        getController()->getControllerEventSignal().notify( this, &VTrack::onControllerEvent );
    }
}

//-----------------------------------------------------------------------------
// 
// VTrack::onAttach();
// 
// This callback removes this object from the controller's event signal
// notification list.
// 
//-----------------------------------------------------------------------------
void VTrack::onDetach( void )
{
    // Valid Controller?
    if ( getController() )
    {
        // Remove Update Notification.
        getController()->getControllerUpdateSignal().remove( this, &VTrack::onControllerUpdate );

        // Remove Event Notification.
        getController()->getControllerEventSignal().remove( this, &VTrack::onControllerEvent );
    }

    Parent::onDetach();
}

//-----------------------------------------------------------------------------
//
// Controller Methods.
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// 
// VTrack::onControllerUpdate( pTime, pDelta );
// 
// The Next Event is integrated until has finished its execution. Once it has
// finished, the next event to be triggered becomes the Current Event. Doing
// this means that only one event is ever checked to see if it should be
// triggered.
// 
//-----------------------------------------------------------------------------
void VTrack::onControllerUpdate( const S32 &pTime, const S32 &pDelta )
{
    if ( !isEnabled() || !mNextEvent )
    {
        // Don't Update.
        return;
    }

    // Update Next Event.
    while ( !mNextEvent->onControllerUpdate( pTime, pDelta ) )
    {
        // Next Event?
        if ( !updateNextEvent() )
        {
            // No Valid Events.
            mNextEvent = NULL;
            break;
        }
    }
}

//-----------------------------------------------------------------------------
// 
// VTrack::onControllerEvent( pEvent );
// 
// When the controller's state changes, this method is called. If the
// controller is reset the virtual method, onControllerReset is called.
// 
// For a full list of possible events, see the 'eControllerEventType'
// declaration in VController.h.
// 
//-----------------------------------------------------------------------------
bool VTrack::onControllerEvent( VController::eControllerEventType pEvent )
{
    if ( !getController() )
    {
        AssertFatal( false, "VTrack::onControllerEvent() - Invalid Controller." );
        return false;
    }

    // Enabled?
    if ( !isEnabled() )
    {
        // Continue Processing Events.
        return true;
    }

    switch( pEvent )
    {
        case VController::k_EventReset :
            {

                // Reset.
                onControllerReset( getControllerTime(), isControllerPlayingForward() );

            } break;
    }

    // Continue Processing Events.
    return true;
}

//-----------------------------------------------------------------------------
// 
// VTrack::onControllerReset( pTime, pForward );
// 
// Reset the status of the track. The Next Event is allocated here.
// 
//-----------------------------------------------------------------------------
void VTrack::onControllerReset( const S32 &pTime, const bool &pForward )
{
    // Clear Next Event.
    mNextEvent = NULL;

    for ( ITreeNode *node = mChildNode; node != NULL; node = node->mSiblingNextNode )
    {
        VEvent *event = ( VEvent* )node;

        // Reset Event.
        event->onControllerReset( pTime, pForward );

        if ( ( event->isPlaying() )
             || ( pForward && event->getTriggerTime() >= pTime ) )
        {
            if ( !mNextEvent )
            {
                // Use as Next Event.
                mNextEvent = event;
            }
        }
        else if ( !pForward && pTime >= event->getTriggerTime() )
        {
            VEvent *nextEvent = ( VEvent* )node->mSiblingNextNode;
            if ( !nextEvent || pTime < nextEvent->getTriggerTime() )
            {
                // Use as Next Event.
                mNextEvent = event;
            }
        }
    }
}

//-----------------------------------------------------------------------------
//
// Reference Methods.
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// 
// VTrack::sort();
// 
// Sort the track's events by the event's trigger time.
// 
//-----------------------------------------------------------------------------
void VTrack::sort( void )
{
    const S32 count = size();
    for ( S32 j = 0; j < count; j++ )
    {
        for ( ITreeNode *node = mChildNode; node != NULL; node = node->mSiblingNextNode )
        {
            VEvent *eventA = ( VEvent* )node;
            VEvent *eventB = ( VEvent* )node->mSiblingNextNode;
            if ( !eventB )
            {
                // No Node.
                break;
            }

            // Swap?
            if ( eventA->getTriggerTime() > eventB->getTriggerTime() )
            {
                // Get Outer Siblings.
                ITreeNode *prevNode = eventA->mSiblingPrevNode;
                ITreeNode *nextNode = eventB->mSiblingNextNode;
                
                if ( eventA->mParentNode && eventA->mParentNode->mChildNode == eventA )
                {
                    // New Child Node.
                    eventA->mParentNode->mChildNode = eventB;
                }

                //
                // Move A.
                eventA->mSiblingPrevNode = eventB;
                eventA->mSiblingNextNode = nextNode;

                if ( nextNode )
                {
                    // Update Outer Sibling.
                    nextNode->mSiblingPrevNode = eventA;
                }

                //
                // Move B.

                eventB->mSiblingPrevNode = prevNode;
                eventB->mSiblingNextNode = eventA;

                if ( prevNode )
                {
                    // Update Outer Sibling.
                    prevNode->mSiblingNextNode = eventB;
                }
            }
        }
    }
}

//-----------------------------------------------------------------------------
// 
// VTrack::updateNextEvent( pForward );
// 
// Point mNextEvent to the next valid event in the track's sequence.
// 
//-----------------------------------------------------------------------------
bool VTrack::updateNextEvent( void )
{
    if ( !mNextEvent )
    {
        // Invalid Event.
        return false;
    }

    while ( ( mNextEvent = mNextEvent->getNextEvent() ) != NULL )
    {
        if ( mNextEvent->isEnabled() )
        {
            // Valid Event.
            return true;
        }
    }

    // Invalid Event.
    return false;
}

//-----------------------------------------------------------------------------
//
// Property Methods.
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// 
// VTrack::getGroup();
// 
// Returns the Track's parent group.
// 
//-----------------------------------------------------------------------------
VGroup *VTrack::getGroup( void )
{
    return dynamic_cast<VGroup*>( mParentNode );
}

//-----------------------------------------------------------------------------
// 
// VTrack::getNextEvent();
// 
// Returns the Event that the Track is currently observing.
// 
//-----------------------------------------------------------------------------
VEvent *VTrack::getNextEvent( void )
{
    return mNextEvent;
}

//-----------------------------------------------------------------------------
// 
// VTrack::getCurrentEvent();
// 
// Returns the Event that the Track is currently observing and playing. This
// will only ever be non-null when the track is observing an Event that has a
// non-zero duration and has been triggered.
// 
//-----------------------------------------------------------------------------
VEvent *VTrack::getCurrentEvent( void )
{
    if ( mNextEvent && mNextEvent->isPlaying() )
    {
        return mNextEvent;
    }

    return NULL;
}

//-----------------------------------------------------------------------------
// 
// VTrack::getPreviousEvent();
// 
// Returns the Event that the Track was last intergrating.
// 
//-----------------------------------------------------------------------------
VEvent *VTrack::getPreviousEvent( void )
{
    if ( mNextEvent )
    {
        return mNextEvent->getPreviousEvent();
    }

    if ( !isControllerPlayingForward() )
    {
        return dynamic_cast<VEvent*>( getChild() );
    }

    return dynamic_cast<VEvent*>( getLastChild() );
}

//-----------------------------------------------------------------------------
// 
// VTrack::calclateInterp( pTime );
// 
// This method returns the interp time between or within events. If the given
// time is between two events, the return time is:
//
//     ( pTime - last_event_finish_time )
//                         / ( next_event_start_time - last_event_finish_time )
// 
// If the given time is within an event, the return time is:
//
//     ( pTime - event_start_time ) / ( event_duration )
//
// The value returned here is between 0.0 and 1.0.
// 
//-----------------------------------------------------------------------------
F32 VTrack::calculateInterp( S32 pTime )
{
    if ( !isControllerPlayingForward() )
    {
        return ( 1.f - _calculateInterp( pTime ) );
    }

    return _calculateInterp( pTime );
}

F32 VTrack::_calculateInterp( S32 pTime )
{
    // Fetch Duration.
    const S32 sequenceDuration = getControllerDuration();
    if ( sequenceDuration == 0 || pTime == sequenceDuration )
    {
        // Sanity!
        return 1.f;
    }

    if ( !mChildNode )
    {
        // Quick Interp.
        return F32( pTime / sequenceDuration );
    }

    // Last Time.
    S32 lastTime = 0;

    VEvent *walk = ( VEvent* )mChildNode;
    while ( walk )
    {
        const S32 startTime  = walk->getStartTime();
        const S32 finishTime = walk->getFinishTime();

        if ( pTime < startTime )
        {
            return ( F32( pTime - lastTime ) / F32( startTime - lastTime ) );
        }

        // Update Last Time.
        lastTime = startTime;

        if ( pTime < finishTime )
        {
            return ( F32( pTime - lastTime ) / F32( finishTime - lastTime ) );
        }

        // Update Last Time.
        lastTime = finishTime;

        // Fetch Next Node.
        walk = ( VEvent* )walk->mSiblingNextNode;
    }

    // Return.
    return ( F32( pTime - lastTime ) / F32( sequenceDuration - lastTime ) );
}