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
#include "Verve/Torque/TMotion.h"
#include "Verve/VPath/VPath.h"

//-----------------------------------------------------------------------------

// Sync the local connection when editing path objects?
// Note: This was originally done so that editing was very smooth, but it turns
//       out that any lag was due to errors in the pathing operations
//       themselves. If issues persist, then uncomment this definition and you
//       might see a marked improvement in performance while editing in Verve.
//#define VT_SYNC_LOCALCLIENT

//-----------------------------------------------------------------------------
//
// Utility Methods.
//
//-----------------------------------------------------------------------------

NetObject *getClientObject( NetObject *pObject )
{
    if ( !pObject )
    {
        return NULL;
    }

    NetConnection *toServer = NetConnection::getConnectionToServer();
    NetConnection *toClient = NetConnection::getLocalClientConnection();
    if ( !toServer || !toClient )
    {
        return NULL;
    }

    const S32 ghostIndex = toClient->getGhostIndex( pObject );
    if ( ghostIndex == -1 )
    {
        return NULL;
    }

    return toServer->resolveGhost( ghostIndex );
}

void _attachPathObject( VPath *pPath, SceneObject *pObject, const bool &pForward, const bool &pRelative, const S32 &pStartNodeIndex, const S32 &pEndNodeIndex, const String &pOrientation, const String &pOrientationData )
{
    if ( pOrientation == String::EmptyString )
    {
        // Attach Object.
        pPath->attachObject( pObject, pForward, 0.f, pRelative, pStartNodeIndex, pEndNodeIndex );
        // Quit.
        return;
    }

    // Fetch Orientation.
    const VPathObject::eOrientationType type = VPathObject::getOrientationTypeEnum( pOrientation );

    switch ( type )
    {
        case VPathObject::k_OrientationFree :
        case VPathObject::k_OrientationInterpolate :
        case VPathObject::k_OrientationToPath :
            {
                // Attach Object.
                pPath->attachObject( pObject, pForward, 0.f, pRelative, pStartNodeIndex, pEndNodeIndex, type, NULL );

            } break;

        case VPathObject::k_OrientationToObject : 
            {
                // Fetch Object.
                SceneObject *lookAtObject = dynamic_cast<SceneObject*>( Sim::findObject( pOrientationData ) );
                // Valid Object?
                if ( lookAtObject != NULL )
                {
                    // Attach Object.
                    pPath->attachObject( pObject, pForward, 0.f, pRelative, pStartNodeIndex, pEndNodeIndex, type, (void*)lookAtObject );
                }

            } break;

        case VPathObject::k_OrientationToPoint:
            {
                // Fetch Point.
                Point3F lookAtPoint( 0.f, 0.f, 0.f );
                if ( dSscanf( pOrientationData, "%g %g %g", &lookAtPoint.x, &lookAtPoint.y, &lookAtPoint.z ) == 3 )
                {
                    // Attach Object.
                    pPath->attachObject( pObject, pForward, 0.f, pRelative, pStartNodeIndex, pEndNodeIndex, type, (void*)lookAtPoint );
                }

            } break;
    }
}

//-----------------------------------------------------------------------------
//
// Path Methods.
//
//-----------------------------------------------------------------------------

bool VTorque::isMovable( SimObject *pObject )
{
    return ( dynamic_cast<SceneObjectType*>( pObject ) != NULL );
}

bool VTorque::isPath( SimObject *pObject )
{
    return ( dynamic_cast<PathObjectType*>( pObject ) != NULL );
}

bool VTorque::isPathObjectAttached( PathObjectType *pPath, SceneObjectType *pObject )
{
    if ( !pPath || !pObject )
    {
        // Sanity!
        return false;
    }

    // Return.
    return pPath->isObjectAttached( pObject );
}

F32 VTorque::getPathNodeLength( PathObjectType *pPath, const S32 &pNode )
{
    if ( !pPath )
    {
        // Sanity!
        return false;
    }

    // Normalize Node Index.
    S32 nodeIndex = pNode;
    pPath->normalizeNodeIndex( nodeIndex );

    // Fetch Node.
    VPathNode *node = pPath->getNode( nodeIndex );

    // Return Length.
    return node->getLength();
}

void VTorque::attachPathObject( PathObjectType *pPath, SceneObjectType *pObject, const bool &pForward, const bool &pRelative, const S32 &pStartNodeIndex, const S32 &pEndNodeIndex, const String &pOrientation, const String &pOrientationData )
{
    if ( !pPath || !pObject )
    {
        // Sanity!
        return;
    }
    
    // Attach Object.
    _attachPathObject( pPath, pObject, pForward, pRelative, pStartNodeIndex, pEndNodeIndex, pOrientation, pOrientationData );

#if defined( VT_EDITOR ) && defined( VT_SYNC_LOCALCLIENT )

    // Fetch the client Path.
    VPath *clientPath = dynamic_cast<VPath*>( getClientObject( pPath ) );
    SceneObjectType *clientObject = dynamic_cast<SceneObjectType*>( getClientObject( pObject ) );
    if ( clientPath && clientObject )
    {
        // Attach Object.
        _attachPathObject( clientPath, clientObject, pForward, pRelative, pStartNodeIndex, pEndNodeIndex, pOrientation, pOrientationData );
    }

#endif
}

void VTorque::detachPathObject( PathObjectType *pPath, SceneObjectType *pObject )
{
    if ( !pPath || !pObject )
    {
        // Sanity!
        return;
    }

    // Detach Object.
    pPath->detachObject( pObject );

#if defined( VT_EDITOR ) && defined( VT_SYNC_LOCALCLIENT )

    // Fetch the client Path.
    VPath *clientPath = dynamic_cast<VPath*>( getClientObject( pPath ) );
    SceneObjectType *clientObject = dynamic_cast<SceneObjectType*>( getClientObject( pObject ) );
    if ( clientPath && clientObject )
    {
        // Detach Object.
        clientPath->detachObject( clientObject );
    }

#endif
}

void VTorque::setPathObjectActive( PathObjectType *pPath, SceneObjectType *pObject, const bool &pActive )
{
    if ( !pPath || !pObject )
    {
        // Sanity!
        return;
    }

    // Update Object State.
    pPath->setPathObjectActive( pObject, pActive );

#if defined( VT_EDITOR ) && defined( VT_SYNC_LOCALCLIENT )

    // Fetch the client Path.
    VPath *clientPath = dynamic_cast<VPath*>( getClientObject( pPath ) );
    SceneObjectType *clientObject = dynamic_cast<SceneObjectType*>( getClientObject( pObject ) );
    if ( clientPath && clientObject )
    {
        // Update Object State.
        clientPath->setPathObjectActive( clientObject, pActive );
    }

#endif
}

void VTorque::setPathObjectInterp( PathObjectType *pPath, SceneObjectType *pObject, const F32 &pInterp )
{
    if ( !pPath || !pObject )
    {
        // Sanity!
        return;
    }

    // Update Path Object Interp.
    pPath->setPathObjectInterp( pObject, pInterp );

#if defined( VT_EDITOR ) && defined( VT_SYNC_LOCALCLIENT )

    // Fetch the client Path.
    VPath *clientPath = dynamic_cast<VPath*>( getClientObject( pPath ) );
    SceneObjectType *clientObject = dynamic_cast<SceneObjectType*>( getClientObject( pObject ) );
    if ( clientPath && clientObject )
    {
        // Apply the same action.
        clientPath->setPathObjectInterp( clientObject, pInterp );
    }

#endif
}

void VTorque::setPathObjectOffset( PathObjectType *pPath, SceneObjectType *pObject, const Point3F &pOffset )
{
    if ( !pPath || !pObject )
    {
        // Sanity!
        return;
    }

    // Update Path Object Offset.
    pPath->setPathObjectOffset( pObject, pOffset );

#if defined( VT_EDITOR ) && defined( VT_SYNC_LOCALCLIENT )

    // Fetch the client Path.
    VPath *clientPath = dynamic_cast<VPath*>( getClientObject( pPath ) );
    SceneObjectType *clientObject = dynamic_cast<SceneObjectType*>( getClientObject( pObject ) );
    if ( clientPath && clientObject )
    {
        // Apply the same action.
        clientPath->setPathObjectOffset( clientObject, pOffset );
    }

#endif
}

void VTorque::setPathObjectSpeed( PathObjectType *pPath, SceneObjectType *pObject, const F32 &pSpeed )
{
    if ( !pPath || !pObject )
    {
        // Sanity!
        return;
    }

    // Update Path Speed.
    pPath->setPathObjectSpeed( pObject, pSpeed );

#if defined( VT_EDITOR ) && defined( VT_SYNC_LOCALCLIENT )

    // Fetch the client Path.
    VPath *clientPath = dynamic_cast<VPath*>( getClientObject( pPath ) );
    SceneObjectType *clientObject = dynamic_cast<SceneObjectType*>( getClientObject( pObject ) );
    if ( clientPath && clientObject )
    {
        // Apply the same action.
        clientPath->setPathObjectSpeed( clientObject, pSpeed );
    }

#endif
}

void VTorque::setPathObjectOrientation( PathObjectType *pPath, SceneObjectType *pObject, const String &pOrientation, const String &pOrientationData )
{
    if ( !pPath || !pObject )
    {
        // Sanity!
        return;
    }

    // Set the orientation mode.
    // Note: Call the console method so we don't have to handle all the different modes here.
    Con::executef( pPath, "setPathObjectOrientationMode", pObject->getIdString(), pOrientation, pOrientationData );

#if defined( VT_EDITOR ) && defined( VT_SYNC_LOCALCLIENT )

    // TODO: Handle synching the client path immediately.

#endif

    /*
    // Set the Default Mode.
    if ( pOrientation == String::EmptyString )
    {
        // Apply Mode.
        pPath->setPathObjectOrientationMode( pObject, VPathObject::k_OrientationToPath );
        return;
    }

    // Fetch Orientation.
    const VPathObject::eOrientationType type = VPathObject::getOrientationTypeEnum( pOrientation );

    switch ( type )
    {
        case VPathObject::k_OrientationFree :
        case VPathObject::k_OrientationInterpolate :
        case VPathObject::k_OrientationToPath :
            {

                // Apply Mode.
                pPath->setPathObjectOrientationMode( pObject, type );

            } break;

        case VPathObject::k_OrientationToObject : 
            {

                // Fetch Object.
                SceneObjectType *lookAtObject;
                if ( !Sim::findObject( pOrientationData, lookAtObject ) )
                {
                    // Invalid Object.
                    return;
                }

                // Apply Mode.
                pPath->setPathObjectOrientationMode( pObject, type, lookAtObject );

            } break;

        case VPathObject::k_OrientationToPoint:
            {

                // Fetch Point.
                Point3F lookAtPoint( 0.f, 0.f, 0.f );
                dSscanf( pOrientationData, "%g %g %g", &lookAtPoint.x, &lookAtPoint.y, &lookAtPoint.z );

                // Apply Mode.
                pPath->setPathObjectOrientationMode( pObject, type, lookAtPoint );

            } break;
    }
    */
}

void VTorque::setPathObjectForward( PathObjectType *pPath, SceneObjectType *pObject, const bool &pForward )
{
    if ( !pPath || !pObject )
    {
        // Sanity!
        return;
    }

    // Update Path Object Forward.
    pPath->setPathObjectForward( pObject, pForward );

#if defined( VT_EDITOR ) && defined( VT_SYNC_LOCALCLIENT )

    // Fetch the client Path.
    VPath *clientPath = dynamic_cast<VPath*>( getClientObject( pPath ) );
    SceneObjectType *clientObject = dynamic_cast<SceneObjectType*>( getClientObject( pObject ) );
    if ( clientPath && clientObject )
    {
        // Apply the same action.
        clientPath->setPathObjectForward( clientObject, pForward );
    }

#endif
}

void VTorque::setPathObjectNode( PathObjectType *pPath, SceneObjectType *pObject, const S32 &pNode )
{
    if ( !pPath || !pObject )
    {
        // Sanity!
        return;
    }

    // Update Object Current Node.
    pPath->setPathObjectNode( pObject, pNode );

#if defined( VT_EDITOR ) && defined( VT_SYNC_LOCALCLIENT )

    // Fetch the client Path.
    VPath *clientPath = dynamic_cast<VPath*>( getClientObject( pPath ) );
    SceneObjectType *clientObject = dynamic_cast<SceneObjectType*>( getClientObject( pObject ) );
    if ( clientPath && clientObject )
    {
        // Update Object Current Node.
        clientPath->setPathObjectNode( clientObject, pNode );
    }

#endif
}

void VTorque::setPathObjectEndNode( PathObjectType *pPath, SceneObjectType *pObject, const S32 &pNode )
{
    if ( !pPath || !pObject )
    {
        // Sanity!
        return;
    }

    // Update Object End Node.
    pPath->setPathObjectEndNode( pObject, pNode );

#if defined( VT_EDITOR ) && defined( VT_SYNC_LOCALCLIENT )

    // Fetch the client Path.
    VPath *clientPath = dynamic_cast<VPath*>( getClientObject( pPath ) );
    SceneObjectType *clientObject = dynamic_cast<SceneObjectType*>( getClientObject( pObject ) );
    if ( clientPath && clientObject )
    {
        // Update Object End Node.
        clientPath->setPathObjectEndNode( clientObject, pNode );
    }

#endif
}