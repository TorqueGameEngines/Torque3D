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
#include "Verve/Extension/Animation/VShapeAnimationTrack.h"
#include "Verve/Extension/Animation/VShapeAnimationEvent.h"
#include "Verve/Core/VGroup.h"

#include "console/consoleTypes.h"

//-----------------------------------------------------------------------------
IMPLEMENT_CONOBJECT( VShapeAnimationTrack );
//-----------------------------------------------------------------------------

VShapeAnimationTrack::VShapeAnimationTrack( void ) :
        mThreadIndex( 0 )
{
    setLabel( "AnimationTrack" );
}

//-----------------------------------------------------------------------------

void VShapeAnimationTrack::initPersistFields()
{
   docsURL;
    Parent::initPersistFields();

    addField( "ThreadIndex", TypeS32, Offset( mThreadIndex, VShapeAnimationTrack ), "The index of the Animation Thread to play." );
}

//-----------------------------------------------------------------------------
//
// Controller Methods.
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// 
// VShapeAnimationTrack::onControllerEvent( pEvent );
// 
// When the controller's state changes, this method is called. If the
// controller is paused, or stops playing, then the animation will cease to
// play. If the controller resumes play, the animation will continue.
// 
// For a full list of possible events, see the 'eControllerEventType'
// declaration in VController.h.
// 
//-----------------------------------------------------------------------------
bool VShapeAnimationTrack::onControllerEvent( VController::eControllerEventType pEvent )
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
        case VController::k_EventPlay :
            {

                // Play Animation.
                VTorque::setAnimationTimeScale( getSceneObject(), mThreadIndex, ( ( isControllerPlayingForward() ) ? 1.f : -1.f ) );

            } break;

        case VController::k_EventPause :
        case VController::k_EventStop :
            {

                // Stop Animation.
                VTorque::setAnimationTimeScale( getSceneObject(), mThreadIndex, 0.f );

            } break;
    }

    return true;
}

//-----------------------------------------------------------------------------
// 
// VShapeAnimationTrack::onControllerReset( pTime, pForward );
// 
// Reset the animation state of the target object. If there is a Next Event,
// then the animation is positioned accordingly.
// 
//-----------------------------------------------------------------------------
void VShapeAnimationTrack::onControllerReset( const S32 &pTime, const bool &pForward )
{
    VTorque::SceneObjectType *object = getSceneObject();
    if ( !object )
    {
        // Parent Call.
        Parent::onControllerReset( pTime, pForward );
        return;
    }

    VShapeAnimationEvent *event;
    if ( getCurrentEvent( event ) )
    {
        // Stop Animation.
        VTorque::stopAnimation( object, mThreadIndex );
    }

    // Parent Call.
    Parent::onControllerReset( pTime, pForward );

    if ( getCurrentEvent( event ) )
    {
        // Play Animation.
        VTorque::playAnimation( object, mThreadIndex, event->mAnimationData );

        // Set Position.
        VTorque::setAnimationPosition( object, mThreadIndex, event->getAnimationPosition( pTime ) );

        // Stop Animation.
        VTorque::setAnimationTimeScale( object, mThreadIndex, 0.f );
    }
}

#ifdef VT_EDITOR
//-----------------------------------------------------------------------------
//
// Debug Methods.
//
//-----------------------------------------------------------------------------

DefineEngineMethod( VShapeAnimationTrack, updateTrack, void, (),, "( void ) - Update the Track.\n"
                                                              "@return No return value." )
{
    for ( ITreeNode *node = object->mChildNode; node != NULL; node = node->mSiblingNextNode )
    {
        VShapeAnimationEvent *currEvent = ( VShapeAnimationEvent* )node;
        VShapeAnimationEvent *nextEvent = ( VShapeAnimationEvent* )node->mSiblingNextNode;
        if ( !currEvent->mAutoDuration )
        {
            // Skip.
            continue;
        }

        if ( VTorque::isAnimationLooping( object->getSceneObject(), currEvent->mAnimationData ) )
        {
            if ( !nextEvent )
            {
                // Update Duration.
                currEvent->setDuration( object->getControllerDuration() - currEvent->getTriggerTime() );
            }
            else
            {
                // Update Duration.
                currEvent->setDuration( mAbs( nextEvent->getTriggerTime() - currEvent->getTriggerTime() ) );
            }
        }
        else
        {
            // Update Duration.
            currEvent->setDuration( ( S32 )( 1000 * VTorque::getAnimationDuration( object->getSceneObject(), currEvent->mAnimationData ) ) );
        }
    }
}
#endif
