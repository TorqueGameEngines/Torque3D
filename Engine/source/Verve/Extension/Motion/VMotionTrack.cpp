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
#include "Verve/Extension/Motion/VMotionTrack.h"
#include "Verve/Extension/Motion/VMotionEvent.h"

#include "console/consoleTypes.h"

//-----------------------------------------------------------------------------
IMPLEMENT_CONOBJECT( VMotionTrack );
//-----------------------------------------------------------------------------

VMotionTrack::VMotionTrack( void ) : 
        mDataReference( String::EmptyString ),
        mOrientationMode( "FREE" ),
        mOrientationData( String::EmptyString ),
        mRelative( false )
{
    setLabel( "MotionTrack" );
}

void VMotionTrack::initPersistFields()
{
   docsURL;
    Parent::initPersistFields();

    addField( "Reference", TypeRealString, Offset( mDataReference, VMotionTrack ), "The name of the data field referencing the object to be attached to the path." );

    addProtectedField( "OrientationMode", TypeRealString, Offset( mOrientationMode, VMotionTrack ), &setOrientationMode, &defaultProtectedGetFn, "The orientation mode of the object attached to the path." );
    addProtectedField( "OrientationData", TypeRealString, Offset( mOrientationData, VMotionTrack ), &setOrientationData, &defaultProtectedGetFn, "The name of the data field holding the orientation data (used for Orientation Modes, ToObject & ToPoint)." );
    addField( "Relative",                 TypeBool,       Offset( mRelative,        VMotionTrack ), "Attach the object with an offset based on its initial position." );
}

//-----------------------------------------------------------------------------
//
// Controller Methods.
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// 
// VMotionTrack::onControllerEvent( pEvent );
// 
// When the controller's state changes, this method is called. If the
// controller is paused, then the path object will cease to move. If the
// controller resumes play, the object will continue on its path.
// 
// For a full list of possible events, see the 'eControllerEventType'
// declaration in VController.h.
// 
//-----------------------------------------------------------------------------
bool VMotionTrack::onControllerEvent( VController::eControllerEventType pEvent )
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

    // Fetch Path & Reference Object.
    VTorque::PathObjectType  *path   = getPath();
    VTorque::SceneObjectType *object = getSceneObject();
    if ( !path || !object || !VTorque::isPathObjectAttached( path, object ) )
    {
        // Invalid.
        return true;
    }

    switch ( pEvent )
    {
        case VController::k_EventPlay :
            {

                // Continue Advancing.
                VTorque::setPathObjectActive( path, object, true );

            } break;

        case VController::k_EventPause :
            {

                // Stop Advancing.
                VTorque::setPathObjectActive( path, object, false );

            } break;

        case VController::k_EventStop :
            {

                // Detach the Object.
                detachObject();

            } break;
    }

    return true;
}

//-----------------------------------------------------------------------------
// 
// VMotionTrack::onControllerReset( pTime, pForward );
// 
// Reposition the path object on the path appropriately. The position is
// interpolated between two nodes, the last node and the next node. These
// correspond to the last and current events.
// 
//-----------------------------------------------------------------------------
void VMotionTrack::onControllerReset( const S32 &pTime, const bool &pForward )
{
    // Parent Reset.
    Parent::onControllerReset( pTime, pForward );

    // Valid Track?
    // Note: We must have at least 2 Events/Nodes to path.
    if ( size() < 2 )
    {
        // Invalid.
        return;
    }

    // Get Object References.
    VController              *controller = getController();
    VTorque::PathObjectType  *path       = getPath();
    VTorque::SceneObjectType *object     = getSceneObject();
    if ( !controller || !path || !object )
    {
        // Invalid Object(s).
        return;
    }

    // Attached?
    if ( !VTorque::isPathObjectAttached( path, object ) )
    {
        // No, Attach Now.
        attachObject();
    }

    // Reset Object.
    resetObject( pTime );
}

//-----------------------------------------------------------------------------
//
// Reference Methods.
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//
// VMotionTrack::getPath();
// 
// Returns the path that this track is referencing.
//
//-----------------------------------------------------------------------------
VTorque::PathObjectType *VMotionTrack::getPath( void )
{
    // Fetch the Controller.
    VController *controller = getController();
    if ( !controller )
    {
        // Invalid Controller.
        return NULL;
    }

    // Evalulate the Data Field.
    String fieldValue;
    if ( controller->getDataValue( mDataReference, fieldValue ) )
    {
        // Return Object.
        return dynamic_cast<VTorque::PathObjectType*>( Sim::findObject( fieldValue ) );
    }

    // No Data!
    return NULL;
}

//-----------------------------------------------------------------------------
//
// VMotionTrack::attachObject();
// 
// Attach the underlying Scene Object to the target Path at the first Node.
// Default settings are applied and must be updated after the object is
// attached.
//
//-----------------------------------------------------------------------------
void VMotionTrack::attachObject( void )
{
    // Get Object References.
    VTorque::PathObjectType  *path   = getPath();
    VTorque::SceneObjectType *object = getSceneObject();
    if ( !path || !object )
    {
        // Invalid Object(s).
        return;
    }

    // Object Attached?
    if ( VTorque::isPathObjectAttached( path, object ) )
    {
        // Already Attached.
        return;
    }

    // Fetch Forwards.
    const bool &forward = isControllerPlayingForward();
    // Select the Node.
    const S32 node = ( forward ) ? 0 : ( size() - 1 );

    // Fetch the value from the controller data table.
    String orientationDataValue = String::EmptyString;
    if ( mOrientationData != String::EmptyString
         && !getController()->getDataValue( mOrientationData, orientationDataValue ) )
    {
        // Sanity!
        Con::warnf( "Unable to located the value for the given orientation data key, '%s'", mOrientationData.c_str() );
        // Clear.
        orientationDataValue = String::EmptyString;
    }

    // Attach Object.
    VTorque::attachPathObject( path, object, forward, mRelative, node, -1, mOrientationMode, orientationDataValue );
}

//-----------------------------------------------------------------------------
//
// VMotionTrack::detachObject( void );
// 
// 
//
//-----------------------------------------------------------------------------
void VMotionTrack::detachObject( void )
{
    // Get Object References.
    VTorque::PathObjectType  *path   = getPath();
    VTorque::SceneObjectType *object = getSceneObject();
    if ( !path || !object )
    {
        // Invalid Object(s).
        return;
    }

    // Object Attached?
    if ( !VTorque::isPathObjectAttached( path, object ) )
    {
        // Not Attached.
        return;
    }

    // Detach.
    VTorque::detachPathObject( path, object );
}

//-----------------------------------------------------------------------------
//
// VMotionTrack::resetObject( pTime );
// 
// 
//
//-----------------------------------------------------------------------------
void VMotionTrack::resetObject( const S32 &pTime )
{
    // Get Object References.
    VTorque::PathObjectType  *path   = getPath();
    VTorque::SceneObjectType *object = getSceneObject();
    if ( !path || !object )
    {
        // Invalid Object(s).
        return;
    }

    // Fetch Controller Info.
    const bool &isPlaying        = isControllerPlaying();
    const bool &isPlayingForward = isControllerPlayingForward();
    const bool &isLooping        = isControllerLooping();

    // Init Variables.
    bool objectActive = false;
    F32  objectInterp = 0.f;
    F32  objectSpeed  = 0.f;
    S32  srcNodeIndex = 0;
    S32  dstNodeIndex = 0;

    VMotionEvent *event;
    if ( !getNextEvent( event ) || event->getTriggerTime() == pTime )
    {
        // Note: This case deals with a target time that is greater than the
        //       trigger time of the Last Event on this track. It will clamp
        //       the position of the object to the corresponding node of the
        //       Last Event.

        // Note: If pTime is exactly equal to the Next Event's trigger time,
        //       then it will set the Source Node to the Last Node and
        //       set its Interp to 0.f - which is incorrect!
        if ( !event || event->getTriggerTime() != pTime  )
        {
            // Fetch the Last Event.
            getPreviousEvent( event );
        }

        // Set the Info.
        objectInterp = 0.f;
        objectSpeed  = event->getObjectSpeed();
        srcNodeIndex = event->getNodeIndex();
        dstNodeIndex = srcNodeIndex;
    }
    else if ( !event->getPreviousEvent() )
    {
        // Note: This case deals with a target time that is less than the
        //       trigger time of the First Event on this track. It will clamp
        //       the position of the object to the corresponding node of the
        //       First Event.

        // Set the Info.
        objectInterp = 0.f;
        objectSpeed  = event->getObjectSpeed();
        srcNodeIndex = event->getNodeIndex();
        dstNodeIndex = srcNodeIndex;
    }
    else
    {
        // Note: This case deals with a target time that is between two Events
        //       on this track. It will position the object on the path,
        //       between the two nodes corresponding to the Events.

        // Fetch the Last Event.
        VMotionEvent *lastEvent;
        getPreviousEvent( lastEvent );

        // Set the Info.
        objectActive = isPlaying;
        objectInterp = calculateInterp( pTime );
        objectSpeed  = lastEvent->getObjectSpeed();
        srcNodeIndex = event->getNodeIndex( ( isPlayingForward ) ? -1 : 1 );
        dstNodeIndex = event->getNodeIndex();
    }

    // Set Active.
    VTorque::setPathObjectActive( path, object, objectActive );

    // Set Forward.
    VTorque::setPathObjectForward( path, object, isPlayingForward );

    // Set Speed.
    VTorque::setPathObjectSpeed( path, object, objectSpeed );

    // Set Current Node.
    VTorque::setPathObjectNode( path, object, srcNodeIndex );

    // Set End Node.
    VTorque::setPathObjectEndNode( path, object, ( ( isLooping ) ? -1 : ( size() - 1 ) ) );

    // Set Interp.
    VTorque::setPathObjectInterp( path, object, objectInterp );
}

//-----------------------------------------------------------------------------
//
// Static Field Methods.
//
//-----------------------------------------------------------------------------

bool VMotionTrack::setOrientationMode( void *pObject, const char *pArray, const char *pData )
{
    // Fetch Track.
    VMotionTrack *track = static_cast<VMotionTrack*>( pObject );

    // Store Data.
    track->mOrientationMode = pData;

    VTorque::PathObjectType  *path   = track->getPath();
    VTorque::SceneObjectType *object = track->getSceneObject();
    if ( VTorque::isPathObjectAttached( path, object ) )
    {
        // Set Orientation Mode.
        VTorque::setPathObjectOrientation( path, object, track->mOrientationMode, track->mOrientationData );
    }

    return false;
}

bool VMotionTrack::setOrientationData( void *pObject, const char *pArray, const char *pData )
{
    // Fetch Track.
    VMotionTrack *track = static_cast<VMotionTrack*>( pObject );

    // Store Data.
    track->mOrientationData = pData;

    VTorque::PathObjectType  *path   = track->getPath();
    VTorque::SceneObjectType *object = track->getSceneObject();
    if ( VTorque::isPathObjectAttached( path, object ) )
    {
        // Set Orientation Mode.
        VTorque::setPathObjectOrientation( path, object, track->mOrientationMode, track->mOrientationData );
    }

    return false;
}

#ifdef VT_EDITOR
//-----------------------------------------------------------------------------
//
// Debug Methods.
//
//-----------------------------------------------------------------------------

DefineEngineMethod( VMotionTrack, getPath, S32, (),, "( void ) - Get the path object this track references.\n"
                                                 "@return Returns the SimObjectID for the object." )
{
    // Fetch Path.
    SimObject *pathReference = object->getPath();

    // Return.
    return ( pathReference ) ? pathReference->getId() : 0;
}
#endif
