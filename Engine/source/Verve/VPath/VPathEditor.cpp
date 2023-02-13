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
#include "torqueConfig.h"

#ifdef TORQUE_TOOLS
#include "VPathEditor.h"

#include "console/consoleTypes.h"
#include "gfx/gfxDrawUtil.h"
#include "gfx/primBuilder.h"
#include "gui/worldEditor/worldEditor.h"
#include "math/mathUtils.h"
#include "sim/netConnection.h"

//-----------------------------------------------------------------------------

static F32     gProjectDistance   = 2000.f;
static F32     gSelectionDistance = 2.f;

static ColorI  gPathColor( 255, 255, 255 );
static ColorI  gPathColorSel( 0, 255, 255 );
static ColorI  gNodeLookAtPointColor( 255, 127, 39 );

//-----------------------------------------------------------------------------

// Implement the Edit Mode enum list.
ImplementEnumType( VPathEditorMode, "" )
    { VPathEditor::k_Gizmo,      "GIZMO"      },
    { VPathEditor::k_AddNode,    "ADDNODE"    },
    { VPathEditor::k_DeleteNode, "DELETENODE" },
EndImplementEnumType;

//-----------------------------------------------------------------------------
IMPLEMENT_CONOBJECT( VPathEditor );
//-----------------------------------------------------------------------------

VPathEditor::VPathEditor( void ) :
        mIsDirty( false ),
        mEditMode( k_Gizmo ),
        mEditWeight( false ),
        mEditWeightHandle( -1 )
{
    // Void.
}

bool VPathEditor::onAdd( void )
{
    if ( !Parent::onAdd() )
    {
        return false;
    }

    // Assign Gizmo Name.
    mGizmo->assignName( "VPathEditorGizmo" );

    return true;
}

bool VPathEditor::onWake( void )
{
    // Clear Selection.
    updateSelection( NULL, -1 );

    // Return Parent Value.
    return Parent::onWake();
}

void VPathEditor::initPersistFields()
{
   docsURL;
    addField( "IsDirty",  TypeBool,           Offset( mIsDirty,  VPathEditor ) );
    addField( "EditMode", TYPEID<EditMode>(), Offset( mEditMode, VPathEditor ) );

    Parent::initPersistFields();
}

//-----------------------------------------------------------------------------
//
// Gui Events
//
//-----------------------------------------------------------------------------

void VPathEditor::on3DMouseDown( const Gui3DMouseEvent &pEvent )
{
    // Using the Gizmo?
    if ( mEditMode != k_Gizmo )
    {
        // No, Quit Now.
        return;
    }

    // Gizmo Event.
    mGizmo->on3DMouseDown( pEvent );

    if ( isValidSelection() )
    {
        // Store Node Information.
        pushNodeEdit();

        switch( mGizmoProfile->mode )
        {
            case MoveMode:
            case RotateMode:
                {
                    if ( mGizmo->getSelection() != Gizmo::None )
                    {
                        // Using Gizmo.
                        return;
                    }

                } break;

            case ScaleMode:
                {
                    if ( isEditingWeight( pEvent ) )
                    {
                        // Editing Weights.
                        return;
                    }

                } break;
        }
    }
    else if ( mSelection.Path )
    {
        // Store Path Information.
        pushPathEdit();

        if ( mGizmo->getSelection() != Gizmo::None )
        {
            // Using Gizmo.
            return;
        }
    }

    // Update Selection.
    if ( !updateSelection( pEvent ) )
    {
        // Clear Selection.
        updateSelection( NULL, -1 );
    }
}

void VPathEditor::on3DMouseUp( const Gui3DMouseEvent &pEvent )
{
    switch ( mEditMode )
    {
        case k_Gizmo :
            {
                // Gizmo Event.
                mGizmo->on3DMouseUp( pEvent );

                // Handle History Actions.
                popPathEdit();
                popNodeEdit();

                // Clear Editing.
                mEditWeight = false;

            } break;

        case k_AddNode :
            {
                if ( mSelection.Path != NULL )
                {
                    // Add New!
                    addNode( pEvent );

                    // Dirty.
                    mIsDirty = true;
                }

            } break;

        case k_DeleteNode :
            {
                // Update Selection.
                if ( updateSelection( pEvent ) )
                {
                    if ( isValidSelection() )
                    {
                        // Delete Node.
                        deleteNode( mSelection.Node );

                        // Dirty.
                        mIsDirty = true;
                    }

                    // Clear Node Selection.
                    updateSelection( mSelection.Path, -1 );
                }

            } break;
    }
}

void VPathEditor::on3DMouseMove( const Gui3DMouseEvent &pEvent )
{
    // Update?
    if ( mEditMode != k_Gizmo || !mSelection.Path )
    {
        return;
    }

    // Update Gizmo?
    if ( mSelection.Node == -1 || mGizmoProfile->mode != ScaleMode )
    {
        // Gizmo Event.
        mGizmo->on3DMouseMove( pEvent );
    }
}

void VPathEditor::on3DMouseDragged( const Gui3DMouseEvent &pEvent )
{
    // Update?
    if ( mEditMode != k_Gizmo || !mSelection.Path )
    {
        return;
    }

    // Update Gizmo?
    if ( mSelection.Node == -1 || mGizmoProfile->mode != ScaleMode )
    {
        // Gizmo Event.
        mGizmo->on3DMouseDragged( pEvent );

        // Handle Gizmo?
        if ( mGizmo->getSelection() == Gizmo::None )
        {
            // Return.
            return;
        }
    }

    // Editing the Path?
    if ( mSelection.Node == -1 )
    {
        switch ( mGizmoProfile->mode )
        {
            case MoveMode :
                {
                    // Fetch Node Position.
                    const Point3F oldPosition = mSelection.Path->getPosition();
                    // Determine New Position.
                    const Point3F newPosition = ( oldPosition + mGizmo->getOffset() );

                    // Apply New Position.
                    setPathPosition( newPosition );

                    // Dirty.
                    mIsDirty        = true;
                    mPathEdit.Dirty = true;

                } break;
            /*
            case RotateMode :
                {

                    // Rotation Delta.
                    MatrixF deltaRotation( EulerF( mGizmo->getDeltaRot() ) );

                    // Fetch Current Transform.
                    MatrixF mat = mSelection.Path->getTransform();
                    mat.mul( deltaRotation );

                    // Apply New Transform.
                    setPathTransform( mat );

                    // Dirty.
                    mIsDirty        = true;
                    mPathEdit.Dirty = true;

                } break;

            case ScaleMode :
                {

                    // Apply New Scale.
                    setPathScale( mGizmo->getScale() );

                    // Dirty.
                    mIsDirty        = true;
                    mPathEdit.Dirty = true;

                } break;
            */
        }
    }

    // No, Editing a Node
    else
    {
        switch ( mGizmoProfile->mode )
        {
            case MoveMode :
                {

                    // Fetch Node.
                    VPathNode *node = mSelection.Path->getNode( mSelection.Node );

                    // Fetch Node Position.
                    const Point3F oldPosition = node->getLocalPosition();

                    // Invert Transform.
                    MatrixF pathTransform = mSelection.Path->getTransform();
                    pathTransform.setPosition( Point3F::Zero );
                    pathTransform.inverse();

                    Point3F deltaPosition = mGizmo->getOffset();
                    pathTransform.mulP( deltaPosition );

                    // Apply New Position.
                    setNodePosition( mSelection.Node, ( oldPosition + deltaPosition ) );

                } break;

            case RotateMode :
                {

                    // Fetch Node.
                    VPathNode *node = mSelection.Path->getNode( mSelection.Node );

                    // Invert Transform.
                    MatrixF pathTransform = mSelection.Path->getTransform();
                    pathTransform.setPosition( Point3F::Zero );
                    pathTransform.inverse();

                    // Rotation Delta.
                    MatrixF deltaRotation( EulerF( mGizmo->getDeltaRot() ) );
                    pathTransform.mul( deltaRotation );

                    // Fetch Current Transform.
                    MatrixF mat = node->getWorldTransform();
                    mat.mul( deltaRotation );

                    // Construct Quat.
                    QuatF newRotation;
                    newRotation.set( mat );

                    // Apply New Rotation.
                    setNodeRotation( mSelection.Node, newRotation );

                } break;

            case ScaleMode :
                {

                    if ( isEditingWeight() )
                    {
                        // Edit Weight.
                        updateWeight( pEvent );
                    }

                } break;
        }
    }
}

//-----------------------------------------------------------------------------
//
// Reference Methods.
//
//-----------------------------------------------------------------------------

VPath *VPathEditor::getClientPath( VPath *pPath )
{
    if ( !pPath )
    {
        return NULL;
    }

    NetConnection *toServer = NetConnection::getConnectionToServer();
    NetConnection *toClient = NetConnection::getLocalClientConnection();
    if ( !toServer || !toClient )
    {
        return NULL;
    }

    const S32 ghostIndex = toClient->getGhostIndex( pPath );
    if ( ghostIndex == -1 )
    {
        return NULL;
    }

    return dynamic_cast<VPath*>( toServer->resolveGhost( ghostIndex ) );
}

//-----------------------------------------------------------------------------
//
// Selection Methods.
//
//-----------------------------------------------------------------------------

bool VPathEditor::updateSelection( const Gui3DMouseEvent &pEvent )
{
    const Point3F pt0 = pEvent.pos;
    const Point3F pt1 = pEvent.pos + pEvent.vec * gProjectDistance;

    RayInfo ri;
    if ( !gServerContainer.collideBox( pt0, pt1, MarkerObjectType, &ri ) )
    {
        // No Object.
        return false;
    }

    VPath *path = dynamic_cast<VPath*>( ri.object );
    if ( !path )
    {
        // No Path Object.
        return false;
    }

    // No Node.
    S32 nodeIndex = -1;

    for ( VPathNodeIterator itr = path->mNodeList.begin(); itr != path->mNodeList.end(); itr++ )
    {
        VPathNode *node = ( *itr );

        Point3F projPosition;
        project( node->getWorldPosition(), &projPosition );

        if ( projPosition.z <= 0.0f )
        {
            continue;
        }

        const Point2I rectHalfSize( 8, 8 );
        const Point2I screenPosition( ( S32 )projPosition.x, ( S32 )projPosition.y );
        const RectI   screenRect( screenPosition - rectHalfSize, 2 * rectHalfSize );

        // Mouse Close Enough?
        if ( screenRect.pointInRect( pEvent.mousePoint ) )
        {
            // Select Node.
            nodeIndex = ( itr - path->mNodeList.begin() );
        }
    }

    // Set Selection.
    updateSelection( path, nodeIndex );

    // Valid Selection.
    return true;
}

void VPathEditor::updateSelection( VPath *pPathObject, const S32 &pNodeIndex )
{
    // Store Selection.
    mSelection.Path = pPathObject;
    mSelection.Node = pNodeIndex;

    // Quick Update.
    updateSelection();

    // Return Buffer.
    char buffer[2][32];
    dSprintf( buffer[0], sizeof( buffer[0] ), "%d", ( pPathObject ) ? pPathObject->getId() : 0 );
    dSprintf( buffer[1], sizeof( buffer[1] ), "%d", pNodeIndex );

    // Callback.
    Con::executef( this, "onUpdateSelection", buffer[0], buffer[1] );
}

void VPathEditor::updateSelection( void )
{
    if ( !isValidSelection() )
    {
        // No Further Updates.
        return;
    }

    // Fetch Node.
    VPathNode *node = mSelection.Path->getNode( mSelection.Node );

    // Fetch Node Rotation Matrix.
    MatrixF mat;
    node->getWorldRotation().setMatrix( &mat );

    // Determine Tangent Axis.
    Point3F pt0(  VPath::gBezierAxis * node->getWeight() );
    Point3F pt1( -VPath::gBezierAxis * node->getWeight() );

    // Rotate Axis.
    mat.mulP( pt0 );
    mat.mulP( pt1 );

    // Offset Points.
    pt0 += node->getWorldPosition();
    pt1 += node->getWorldPosition();

    // Store Points.
    mSelection.TangentHandle[0] = pt0;
    mSelection.TangentHandle[1] = pt1;
}

DefineEngineMethod( VPathEditor, clearSelection, void, (),, "( void )" )
{
    // Clear Selection.
    object->updateSelection( NULL, -1 );
}

DefineEngineMethod(VPathEditor, setSelection, void, (SceneObject* sceneObject, S32 nodeIndex), (nullAsType<SceneObject*>(), -1), "( pObject, [pNodeIndex] )")
{
   if (sceneObject == nullptr)
   {
      Con::errorf("VPathEditor::setSelection() - Unable to select target Object.");
      return;
   }
    // Fetch Path.
    VPath *path = dynamic_cast<VPath*>(sceneObject);
    if ( !path )
    {
        Con::errorf( "VPathEditor::setSelection() - Unable to select target Object." );
        return;
    }

    object->updateSelection( path, nodeIndex);
}

DefineEngineMethod( VPathEditor, isValidSelection, bool, (),, "( void )" )
{
    return object->isValidSelection();
}

DefineEngineMethod( VPathEditor, getSelectedPath, S32, (),, "( void )" )
{
    // Fetch Path.
    VPath *path = object->mSelection.Path;

    // Return ID.
    return ( path ) ? path->getId() : 0;
}

DefineEngineMethod( VPathEditor, getSelectedNode, S32, (),, "( void )" )
{
    // Return Node Index.
    return ( object->mSelection.Path ) ? object->mSelection.Node : -1;
}

DefineEngineMethod( VPathEditor, deleteSelection, void, (),, "( void )" )
{
    // Valid Selection?
    if ( object->isValidSelection() )
    {
        object->deleteNode( object->mSelection.Node );
    }
}

//-----------------------------------------------------------------------------
//
// Weight Editing Methods.
//
//-----------------------------------------------------------------------------

bool VPathEditor::isEditingWeight( const Gui3DMouseEvent &pEvent )
{
    if ( !isValidSelection() || mSelection.Path->mPathType != VPath::k_PathBezier )
    {
        // False.
        mEditWeight = false;

        // Invalid Selection.
        return false;
    }

    const Point3F pt0 = pEvent.pos;
    const Point3F pt1 = pEvent.pos + pEvent.vec * gProjectDistance;

    // Min Index.
    S32 minNode     = -1;
    F32 minDistance = F32_MAX;

    for ( S32 i = 0; i < 2; i++ )
    {
        Point3F pt;
        if ( !Utility::FindNearestPointOnLine( mSelection.TangentHandle[i], pt0, pt1, &pt ) )
        {
            // Skip.
            continue;
        }

        // Distance.
        const F32 ptDistance = ( pt - mSelection.TangentHandle[i] ).len();
        if ( ptDistance < minDistance )
        {
            // Store Index.
            minNode = i;

            // Store Distance.
            minDistance = ptDistance;
        }
    }

    if ( minDistance > gSelectionDistance )
    {
        // False.
        mEditWeight = false;

        // Too Far Away.
        return false;
    }

    // True.
    mEditWeight       = true;
    mEditWeightHandle = minNode;

    return true;
}

void VPathEditor::updateWeight( const Gui3DMouseEvent &pEvent )
{
    if ( !isEditingWeight() )
    {
        // Woops!
        return;
    }

    // Fetch Current Node.
    VPathNode *node    = mSelection.Path->getNode( mSelection.Node );
    Point3F    nodePos = node->getWorldPosition();

    // Fetch Node Transform.
    MatrixF mat = node->getWorldTransform();

    // Fetch the Normal.
    const VectorF planeNormal = mat.getColumn3F( 0 );

    // Construct Plane.
    const PlaneF plane( nodePos, planeNormal );

    Point3F iPt;
    if ( plane.intersect( pEvent.pos, pEvent.vec, &iPt ) )
    {
/*
        // Fetch Edit Vector.
        VectorF tangentVect( mSelection.TangentHandle[mEditWeightHandle] - nodePos );
        tangentVect.normalize();

        // Fetch Mouse Vector.
        VectorF mouseVec( iPt - nodePos );
        F32 mouseDist = mouseVec.len();
        mouseVec.normalize();

        // Find the Angles.
        F32 tangentAngle = mAtan2( -tangentVect.z, tangentVect.x );
        F32 mouseAngle   = mAtan2( -mouseVec.z, mouseVec.x );

        // Determine Sign.
        const S32 sign = ( planeNormal.y > 0.f ) ? -1.f : 1.f;

        // Delta Rotation..
        const QuatF deltaRotation( AngAxisF( planeNormal, sign * ( mouseAngle - tangentAngle ) ) );

        // Calculate New Rotation.
        QuatF newRotation;
        newRotation.mul( nodePos, deltaRotation ); 

        // Apply Rotation.
        setNodeRotation( mSelection.Node, newRotation );
*/
/*
        // Fetch Edit Vector.
        VectorF handleVec( mSelection.TangentHandle[mEditWeightHandle] - nodePos );
        handleVec.normalize();

        // Fetch Mouse Vector.
        VectorF mouseVec( iPt - nodePos );
        mouseVec.normalize();

        // Find the Angles.
        F32 handleAngle = Utility::GetPitch( handleVec ); //mAtan2( -handleVec.z, handleVec.x );
        F32 mouseAngle  = Utility::GetPitch( mouseVec );  //mAtan2( -mouseVec.z, mouseVec.x );

        // Determine Sign.
        const S32 sign = ( planeNormal.y > 0.f ) ? -1.f : 1.f;

        // Delta Rotation.
        MatrixF rotMat;
        AngAxisF::RotateY( sign * ( mouseAngle - handleAngle ), &rotMat );

        // Rotate.
        mat.mul( rotMat );

        QuatF newRotation;
        newRotation.set( mat );

        // Apply Rotation.
        setNodeRotation( mSelection.Node, newRotation );
*/
        // Apply Weight.
        setNodeWeight( mSelection.Node, ( iPt - nodePos ).len() );
    }
}

//-----------------------------------------------------------------------------
//
// Path Editing Methods.
//
//-----------------------------------------------------------------------------

void VPathEditor::setPathPosition( const Point3F &pPosition )
{
    // Fetch Paths.
    VPath *serverPath = mSelection.Path;
    VPath *clientPath = getClientPath( serverPath );

    // Update Position.
    serverPath->setPosition( pPosition );
    clientPath->setPosition( pPosition );

    // Update Selection.
    updateSelection();
}

void VPathEditor::setPathRotation( const QuatF &pRotation )
{
    // Determine the Matrix.
    MatrixF mat;
    pRotation.setMatrix( &mat );
    mat.setPosition( mSelection.Path->getPosition() );

    // Update Transform.
    setPathTransform( mat );
}

void VPathEditor::setPathTransform( const MatrixF &pTransform )
{
    // Fetch Paths.
    VPath *serverPath = mSelection.Path;
    VPath *clientPath = getClientPath( serverPath );

    // Update Transform.
    serverPath->setTransform( pTransform );
    clientPath->setTransform( pTransform );

    // Update Selection.
    updateSelection();
}

void VPathEditor::setPathScale( const VectorF &pScale )
{
    // Fetch Paths.
    VPath *serverPath = mSelection.Path;
    VPath *clientPath = getClientPath( serverPath );

    // Fetch Current Scale.
    VectorF scale = serverPath->getScale();
    scale.convolve( pScale );

    // Update Scale.
    serverPath->setScale( scale );
    clientPath->setScale( scale );

    // Update Selection.
    updateSelection();
}

//-----------------------------------------------------------------------------
//
// Node Editing Methods.
//
//-----------------------------------------------------------------------------

bool VPathEditor::getPointOnPath( VPath *pPath, const Gui3DMouseEvent &pEvent, S32 &pNode, MatrixF &pTransform )
{
    if ( pPath->getNodeCount() < 2 )
    {
        // Start / End Points.
        const Point3F pt0 = pEvent.pos;
        const Point3F pt1 = pEvent.pos + pEvent.vec * gProjectDistance;

        // Create Intersection Plane.
        const PlaneF plane( pPath->getPosition(), VPath::gBezierUp );

        // Intersection Point.
        Point3F intersectionPoint;
        if ( !plane.intersect( pEvent.pos, pEvent.vec, &intersectionPoint ) )
        {
            // No Intersection.
            return false;
        }

        // I'th Node.
        pNode = pPath->getNodeCount();
        // Set Identity.
        pTransform.identity();
        // Set Position.
        pTransform.setPosition( intersectionPoint );

        // Return.
        return true;
    }

    switch ( pPath->mPathType )
    {
        case VPath::k_PathLinear : 
            {

                return getPointOnLinearPath( pPath, pEvent, pNode, pTransform );

            } break;

        case VPath::k_PathBezier :
            {

                return getPointOnBezierPath( pPath, pEvent, pNode, pTransform );

            } break;
    }

    return false;
}

bool VPathEditor::getPointOnLinearPath( VPath *pPath, const Gui3DMouseEvent &pEvent, S32 &pNode, MatrixF &pTransform )
{
    // Start / End Points.
    const Point3F pt0 = pEvent.pos;
    const Point3F pt1 = pEvent.pos + pEvent.vec * gProjectDistance;

    S32 minNode = -1;
    F32 minDistance = F32_MAX;
    Point3F minPoint( 0.f, 0.f, 0.f );
    for ( VPathNodeIterator itr = pPath->mNodeList.begin(); itr != pPath->mNodeList.end(); itr++ )
    {
        // Fetch Nodes.
        VPathNode *srcNode = ( *itr );
        VPathNode *dstNode = ( itr == ( pPath->mNodeList.end() - 1 ) ) ? ( *( pPath->mNodeList.begin() ) ) : ( *( itr + 1 ) );

        // Project to Screen.
        Point3F srcNodeScreenPosition, dstNodeScreenPosition;
        project( srcNode->getWorldPosition(), &srcNodeScreenPosition );
        project( dstNode->getWorldPosition(), &dstNodeScreenPosition );

        // Skip?
        if ( srcNodeScreenPosition.z > 1.f && dstNodeScreenPosition.z > 1.f )
        {
            continue;
        }

        Point3F ptOut0, ptOut1;
        F32 ptOutDistance;
        if ( !Utility::FindNearestDistanceBetweenLines( pt0, pt1,
                                                        srcNode->getWorldPosition(), dstNode->getWorldPosition(),
                                                        &ptOut0, &ptOut1, &ptOutDistance ) )
        {
            continue;
        }

        if ( ptOutDistance < minDistance )
        {
            minDistance = ptOutDistance;
            minPoint = ptOut1;
            minNode = ( itr - pPath->mNodeList.begin() );
        }
    }

    // Distance too Large?
    if ( minDistance > 0.25f )
    {
        // Invalid.
        return false;
    }

    // Setup.
    pTransform.identity();
    pTransform.setPosition( minPoint );

    // Store Node.
    pNode = minNode;

    return true;
}

bool VPathEditor::getPointOnBezierPath( VPath *pPath, const Gui3DMouseEvent &pEvent, S32 &pNode, MatrixF &pTransform )
{
    S32 minNode = -1;
    F32 minInterp = 0.f;
    F32 minDistance = F32_MAX;
    Point3F minPoint( 0.f, 0.f, 0.f );
    for ( VPathNodeIterator itr = pPath->mNodeList.begin(); itr != pPath->mNodeList.end(); itr++ )
    {
        // Fetch Nodes.
        VPathNode *srcNode = ( *itr );
        VPathNode *dstNode = ( itr == ( pPath->mNodeList.end() - 1 ) ) ? ( *( pPath->mNodeList.begin() ) ) : ( *( itr + 1 ) );

        // Project to Screen.
        Point3F srcNodeScreenPosition, dstNodeScreenPosition;
        project( srcNode->getWorldPosition(), &srcNodeScreenPosition );
        project( dstNode->getWorldPosition(), &dstNodeScreenPosition );

        // Skip?
        if ( srcNodeScreenPosition.z > 1.f && dstNodeScreenPosition.z > 1.f )
        {
            continue;
        }

        // Positions.
        const Point3F &pt0 = srcNode->getWorldPosition();
        const Point3F &pt3 = dstNode->getWorldPosition();

        // Fetch Node Rotation Matrices.
        MatrixF mat0, mat1;
        srcNode->getWorldRotation().setMatrix( &mat0 );
        dstNode->getWorldRotation().setMatrix( &mat1 );

        // Determine Tangent Axis.
        Point3F pt1(  VPath::gBezierAxis * srcNode->getWeight() );
        Point3F pt2( -VPath::gBezierAxis * dstNode->getWeight() );

        // Rotate Axis.
        mat0.mulP( pt1 );
        mat1.mulP( pt2 );

        // Offset Points.
        pt1 += pt0;
        pt2 += pt3;

        for ( F32 t = 0.f, it = 1.f; t <= 1.f; t += 0.1f, it = ( 1.f - t ) )
        {
            // Calculate Position.
            Point3F pos = ( pt0 * it * it * it ) + ( 3 * pt1 * it * it * t ) + ( 3 * pt2 * it * t * t ) + ( pt3 * t * t * t );

            // Determine the Screen Position.
            Point3F screenPos;
            project( pos, &screenPos );
            // Behind?
            if ( screenPos.z > 1.f )
            {
                // Skip Point.
                continue;
            }

            // Determine the Distance.
            F32 screenDistance = Point2F( screenPos.x - pEvent.mousePoint.x, screenPos.y - pEvent.mousePoint.y ).lenSquared();
            // Min Distance?
            if ( screenDistance < minDistance )
            {
                // Store.
                minDistance = screenDistance;
                minInterp = t;
                minPoint = pos;
                minNode = ( itr - pPath->mNodeList.begin() );
            }
        }
    }

    // Distance too Large?
    if ( minDistance > 1000.f )
    {
        // Invalid.
        return false;
    }

    // Fetch Orientation.
    const VectorF &orientation = pPath->getPathOrientation( pPath->getNode( minNode ), 
                                                            pPath->getNode( ( minNode + 1 ) % pPath->getNodeCount() ),
                                                            minInterp, true );

    // Z-Axis.
    VectorF zVec = -orientation;
    zVec.normalize();

    // X-Axis.
    VectorF xVec = mCross( VPath::gBezierUp, zVec );
    xVec.normalize();

    // Y-Axis.
    VectorF yVec = mCross( zVec, xVec );
    yVec.normalize();

    // Setup Object Transform.
    pTransform.identity();
    pTransform.setColumn( 0,  xVec );
    pTransform.setColumn( 1, -zVec );
    pTransform.setColumn( 2,  yVec );
    // Set the Position.
    pTransform.setPosition( minPoint );

    // Store Node.
    pNode = minNode;

    return true;
}

void VPathEditor::addNode( const Gui3DMouseEvent &pEvent )
{
    VPath *path = mSelection.Path;
    if ( !path )
    {
        // Woops!
        return;
    }

    // Min Index.
    S32 nodeIndex = -1;
    MatrixF nodeTransform( true );
    if ( !getPointOnPath( path, pEvent, nodeIndex, nodeTransform ) )
    {
        // Can't Add.
        return;
    }

    // Invert Transform.
    MatrixF pathTransform = mSelection.Path->getTransform();
    pathTransform.setPosition( Point3F::Zero );
    pathTransform.inverse();

    Point3F nodePosition = ( nodeTransform.getPosition() - mSelection.Path->getPosition() );
    pathTransform.mulP( nodePosition );

    // Node Rotation.
    nodeTransform.mul( pathTransform );
    QuatF nodeRotation( nodeTransform );

    // Node Weights.
    F32 nodeWeight = 10.f;

    // Add New Node.
    VPathNode *node = path->addNode( nodePosition, nodeRotation, nodeWeight, ++nodeIndex );

    // Valid Node?
    if ( !node )
    {
        return;
    }

    // Update Size.
    path->updateContainer();

    // Calculate Path.
    path->calculatePath();

    UndoManager *historyManager = NULL;
    if ( !Sim::findObject( "EUndoManager", historyManager ) )
    {
        Con::errorf( "VPathEditor::addNode() - EUndoManager not found!" );
        return;           
    }

    // Create Undo Action.
    VPathEditorAddNodeAction *editAction = new VPathEditorAddNodeAction();

    // Store Editor.
    editAction->mEditor       = this;

    // Store Node Details.
    editAction->mPath         = path;
    editAction->mNodeIndex    = nodeIndex;

    editAction->mNodePosition = nodePosition;
    editAction->mNodeRotation = nodeRotation;
    editAction->mNodeWeight   = nodeWeight;

    // Add To Manager.
    historyManager->addAction( editAction );

    // Set World Editor Dirty.
    setWorldEditorDirty();
}

void VPathEditor::deleteNode( const S32 &pNodeIndex )
{
    VPath *path = mSelection.Path;
    if ( !path )
    {
        // Woops!
        return;
    }

    // Fetch Node Properites.
    VPathNode *node        = path->getNode( pNodeIndex );
    const Point3F position = node->getLocalPosition();
    const QuatF   rotation = node->getLocalRotation();
    const F32     weight   = node->getWeight();

    // Delete Node.
    path->deleteNode( pNodeIndex );
    
    // Update Path.
    path->updateContainer();

    // Calculate Path.
    path->calculatePath();

    // Selected Node?
    const S32 _nodeIndex = pNodeIndex;
    if ( pNodeIndex == mSelection.Node )
    {
        // Update Selection.
        updateSelection( mSelection.Path, -1 );
    }

    UndoManager *historyManager = NULL;
    if ( !Sim::findObject( "EUndoManager", historyManager ) )
    {
        Con::errorf( "VPathEditor::deleteNode() - EUndoManager not found!" );
        return;           
    }

    // Create Undo Action.
    VPathEditorDeleteNodeAction *editAction = new VPathEditorDeleteNodeAction();

    // Store Editor.
    editAction->mEditor       = this;

    // Store Node Details.
    editAction->mPath         = path;
    editAction->mNodeIndex    = _nodeIndex;

    editAction->mNodePosition = position;
    editAction->mNodeRotation = rotation;
    editAction->mNodeWeight   = weight;

    // Add To Manager.
    historyManager->addAction( editAction );

    // Set World Editor Dirty.
    setWorldEditorDirty();
}

void VPathEditor::setNodePosition( const S32 &pNodeIndex, const Point3F &pPosition )
{
    // Fetch Paths.
    VPath *serverPath = mSelection.Path;
    VPath *clientPath = getClientPath( serverPath );

    // Sanity!
    if ( !serverPath || !clientPath )
    {
        return;
    }

    // Change?
    if ( serverPath->getNodeLocalPosition( pNodeIndex ) == pPosition )
    {
        return;
    }

    // Set Position.
    serverPath->setNodePosition( pNodeIndex, pPosition );
    clientPath->setNodePosition( pNodeIndex, pPosition );

    // Update Selection.
    updateSelection();
    
    // Dirty.
    mIsDirty    = true;
    mNodeEdit.Dirty = true;

    // Arg Buffer.
    char buffer[3][32];
    dSprintf( buffer[0], sizeof( buffer[0] ), "%d", mSelection.Path->getId() );
    dSprintf( buffer[1], sizeof( buffer[1] ), "%d", pNodeIndex );
    dSprintf( buffer[2], sizeof( buffer[2] ), "%d", ( mSelection.Node == pNodeIndex ) );

    // Callback.
    Con::executef( this, "onUpdateNodePosition", buffer[0], buffer[1], buffer[2] );
}

void VPathEditor::setNodeRotation( const S32 &pNodeIndex, const QuatF &pRotation )
{
    // Fetch Paths.
    VPath *serverPath = mSelection.Path;
    VPath *clientPath = getClientPath( serverPath );

    // Sanity!
    if ( !serverPath || !clientPath )
    {
        return;
    }

    // Change?
    if ( serverPath->getNodeLocalRotation( pNodeIndex ) == pRotation )
    {
        return;
    }

    // Set Position.
    serverPath->setNodeRotation( pNodeIndex, pRotation );
    clientPath->setNodeRotation( pNodeIndex, pRotation );

    // Update Selection.
    updateSelection();
    
    // Dirty.
    mIsDirty    = true;
    mNodeEdit.Dirty = true;

    // Arg Buffer.
    char buffer[3][32];
    dSprintf( buffer[0], sizeof( buffer[0] ), "%d", mSelection.Path->getId() );
    dSprintf( buffer[1], sizeof( buffer[1] ), "%d", pNodeIndex );
    dSprintf( buffer[2], sizeof( buffer[2] ), "%d", ( mSelection.Node == pNodeIndex ) );

    // Callback.
    Con::executef( this, "onUpdateNodeRotation", buffer[0], buffer[1], buffer[2] );
}

void VPathEditor::setNodeWeight( const S32 &pNodeIndex, const F32 &pWeight )
{
    // Fetch Paths.
    VPath *serverPath = mSelection.Path;
    VPath *clientPath = getClientPath( serverPath );

    // Sanity!
    if ( !serverPath || !clientPath )
    {
        return;
    }

    // Change?
    if ( serverPath->getNodeWeight( pNodeIndex ) == pWeight )
    {
        return;
    }

    // Set Weight.
    serverPath->setNodeWeight( pNodeIndex, pWeight );
    clientPath->setNodeWeight( pNodeIndex, pWeight );

    // Update Selection.
    updateSelection();
    
    // Dirty.
    mIsDirty    = true;
    mNodeEdit.Dirty = true;

    // Arg Buffer.
    char buffer[3][32];
    dSprintf( buffer[0], sizeof( buffer[0] ), "%d", mSelection.Path->getId() );
    dSprintf( buffer[1], sizeof( buffer[1] ), "%d", pNodeIndex );
    dSprintf( buffer[2], sizeof( buffer[2] ), "%d", ( mSelection.Node == pNodeIndex ) );

    // Callback.
    Con::executef( this, "onUpdateNodeWeight", buffer[0], buffer[1], buffer[2] );
}

void VPathEditor::setNodeOrientationMode( const S32 &pNodeIndex, const VPathNode::eOrientationType &pType )
{
    // Fetch Paths.
    VPath *serverPath = mSelection.Path;
    VPath *clientPath = getClientPath( serverPath );

    // Sanity!
    if ( !serverPath || !clientPath )
    {
        return;
    }

    // Set Orientation Mode.
    serverPath->setNodeOrientationMode( pNodeIndex, pType );
    clientPath->setNodeOrientationMode( pNodeIndex, pType );
    
    // Dirty.
    mIsDirty    = true;
    mNodeEdit.Dirty = true;

    // Arg Buffer.
    char buffer[3][32];
    dSprintf( buffer[0], sizeof( buffer[0] ), "%d", mSelection.Path->getId() );
    dSprintf( buffer[1], sizeof( buffer[1] ), "%d", pNodeIndex );
    dSprintf( buffer[2], sizeof( buffer[2] ), "%d", ( mSelection.Node == pNodeIndex ) );

    // Callback.
    Con::executef( this, "onUpdateNodeOrientation", buffer[0], buffer[1], buffer[2] );
}

void VPathEditor::setNodeOrientationMode( const S32 &pNodeIndex, const VPathNode::eOrientationType &pType, const Point3F &pPoint )
{
    // Fetch Paths.
    VPath *serverPath = mSelection.Path;
    VPath *clientPath = getClientPath( serverPath );

    // Sanity!
    if ( !serverPath || !clientPath )
    {
        return;
    }

    // Set Orientation Mode.
    serverPath->setNodeOrientationMode( pNodeIndex, pType, pPoint );
    clientPath->setNodeOrientationMode( pNodeIndex, pType, pPoint );
    
    // Dirty.
    mIsDirty    = true;
    mNodeEdit.Dirty = true;

    // Arg Buffer.
    char buffer[3][32];
    dSprintf( buffer[0], sizeof( buffer[0] ), "%d", mSelection.Path->getId() );
    dSprintf( buffer[1], sizeof( buffer[1] ), "%d", pNodeIndex );
    dSprintf( buffer[2], sizeof( buffer[2] ), "%d", ( mSelection.Node == pNodeIndex ) );

    // Callback.
    Con::executef( this, "onUpdateNodeOrientation", buffer[0], buffer[1], buffer[2] );
}

void VPathEditor::pushPathEdit( void )
{
    // Clear Current Edit Dirty.
    mPathEdit.Dirty = false;

    if ( mSelection.Path != NULL )
    {
        // Store Node Details.
        mPathEdit.Transform = mSelection.Path->getTransform();
    }
}

void VPathEditor::popPathEdit( void )
{
    // Did Edit?
    if ( mPathEdit.Dirty && mSelection.Path != NULL )
    {
        UndoManager *historyManager = NULL;
        if ( !Sim::findObject( "EUndoManager", historyManager ) )
        {
            Con::errorf( "VPathEditor - EUndoManager not found!" );
            return;           
        }

        // Create Undo Action.
        VPathEditorEditPathAction *editAction = new VPathEditorEditPathAction( "Edit Path" );

        // Store Editor.
        editAction->mEditor   = this;

        // Store Path Details.
        editAction->mPath      = mSelection.Path;
        editAction->mTransform = mPathEdit.Transform;

        // Add To Manager.
        historyManager->addAction( editAction );

        // Clear Dirty.
        mPathEdit.Dirty = false;

        // Set World Editor Dirty.
        setWorldEditorDirty();
    }
}

void VPathEditor::pushNodeEdit( void )
{
    // Clear Current Edit Dirty.
    mNodeEdit.Dirty = false;

    if ( isValidSelection() )
    {
        // Fetch Node.
        VPathNode *node = mSelection.Path->getNode( mSelection.Node );

        // Store Node Details.
        mNodeEdit.Position = node->getLocalPosition();
        mNodeEdit.Rotation = node->getLocalRotation();
        mNodeEdit.Weight   = node->getWeight();
    }
}

void VPathEditor::popNodeEdit( void )
{
    // Did Edit?
    if ( mNodeEdit.Dirty && isValidSelection() )
    {
        UndoManager *historyManager = NULL;
        if ( !Sim::findObject( "EUndoManager", historyManager ) )
        {
            Con::errorf( "VPathEditor - EUndoManager not found!" );
            return;           
        }

        // Create Undo Action.
        VPathEditorEditNodeAction *editAction = new VPathEditorEditNodeAction( "Edit Node" );

        // Store Editor.
        editAction->mEditor       = this;

        // Store Node Details.
        editAction->mPath         = mSelection.Path;
        editAction->mNodeIndex    = mSelection.Node;

        editAction->mNodePosition = mNodeEdit.Position;
        editAction->mNodeRotation = mNodeEdit.Rotation;
        editAction->mNodeWeight   = mNodeEdit.Weight;

        editAction->mNodeOrientation = mSelection.Path->getNode( mSelection.Node )->getOrientationMode();

        // Add To Manager.
        historyManager->addAction( editAction );

        // Clear Dirty.
        mNodeEdit.Dirty = false;

        // Set World Editor Dirty.
        setWorldEditorDirty();
    }
}

void VPathEditor::setWorldEditorDirty( void )
{
    WorldEditor *worldEditor;
    if ( Sim::findObject( "EWorldEditor", worldEditor ) )
    {
        worldEditor->setDirty();
    }
}

//-----------------------------------------------------------------------------
//
// Render Methods.
//
//-----------------------------------------------------------------------------

void VPathEditor::setStateBlock( void )
{
    // Valid State Block?
    if ( !mStateBlock )
    {
        // Setup Definition.
        GFXStateBlockDesc def;
        def.blendDefined = true;
        def.blendEnable = true;
        def.blendSrc = GFXBlendSrcAlpha;
        def.blendDest = GFXBlendInvSrcAlpha;
        def.zDefined = true;
        def.cullDefined = false;

        // Create State Block.
        mStateBlock = GFX->createStateBlock( def );
    }

    // Set State Block.
    GFX->setStateBlock( mStateBlock );
}

void VPathEditor::renderScene( const RectI &pUpdateRect )
{
    // Setup State Block.
    setStateBlock();

    if ( isValidSelection() )
    {
        // Fetch Current Node.
        VPathNode *node = mSelection.Path->getNode( mSelection.Node );

        // Render Gizmo?
        if ( mEditMode == k_Gizmo && mGizmoProfile->mode != ScaleMode )
        {
            // Fetch Node Transform.
            MatrixF mat= node->getWorldTransform();

            // Move Gizmo.
            mGizmo->set( mat, node->getWorldPosition(), Point3F( 1.0f, 1.0f, 1.0f ) );

            // Render Gizmo.
            mGizmo->renderGizmo( mLastCameraQuery.cameraMatrix );
        }

        // Render Handles?
        if ( mSelection.Path->mPathType == VPath::k_PathBezier )
        {
            // Fetch Tangent Handles.
            const Point3F &pt0 = mSelection.TangentHandle[0];
            const Point3F &pt1 = mSelection.TangentHandle[1];

            // State Block.
            GFXStateBlockDesc desc;
            desc.setZReadWrite( true, true );
            desc.fillMode = GFXFillSolid;

            // Set Color.
            PrimBuild::color( gPathColorSel );

            // Render Line.
            PrimBuild::begin( GFXLineList, 2 );
                PrimBuild::vertex3fv( pt0 );
                PrimBuild::vertex3fv( pt1 );
            PrimBuild::end();

            // Render Handles.
            GFX->getDrawUtil()->drawSphere( desc, 0.1f, pt0, gPathColorSel );
            GFX->getDrawUtil()->drawSphere( desc, 0.1f, pt1, gPathColorSel );
        }

        // ToPoint Node?
        if ( node->getOrientationMode().Type == VPathNode::k_OrientationToPoint )
        {
            PrimBuild::color( gNodeLookAtPointColor );
            PrimBuild::begin( GFXLineStrip, 2 );

            PrimBuild::vertex3fv( node->getWorldPosition() );
            PrimBuild::vertex3fv( node->getOrientationMode().Point );

            PrimBuild::end();
        }
    }
    else if ( mSelection.Path && mEditMode == k_Gizmo )
    {
        switch ( mGizmoProfile->mode )
        {
            case MoveMode:
                {
                    // Fetch Path Transform.
                    const MatrixF &mat = mSelection.Path->getTransform();

                    // Fetch the Path's Box Center.
                    const Point3F &pos = mSelection.Path->getWorldBox().getCenter();

                    // Move Gizmo.
                    mGizmo->set( mat, pos, Point3F( 1.0f, 1.0f, 1.0f ) );

                    // Render Gizmo.
                    mGizmo->renderGizmo( mLastCameraQuery.cameraMatrix );

                } break;
        }
    }

    // Render Path Segments.
    renderPaths( k_RenderSegments );

    // Set Clip Rect.
    GFX->setClipRect( pUpdateRect ); 

    // Render Path Nodes.
    renderPaths( k_RenderNodes );

    if ( isValidSelection() )
    {
        // Fetch Current Node.
        VPathNode *node = mSelection.Path->getNode( mSelection.Node );

        // ToPoint Node?
        if ( node->getOrientationMode().Type == VPathNode::k_OrientationToPoint )
        {
            // Project to Screen.
            Point3F screenPosition;
            project( node->getOrientationMode().Point, &screenPosition );
            if ( screenPosition.z <= 1.0f )
            {
                // Determine the center & size of the node rectangle.
                Point2I nodeCenter = Point2I( screenPosition.x, screenPosition.y );
                Point2I nodeHalfSize = Point2I( 8, 8 );
                // Determine Render Rectangle.
                RectI nodeRect;
                nodeRect.point  = nodeCenter - nodeHalfSize;
                nodeRect.extent = ( 2 * nodeHalfSize );

                // Draw?
                if ( getBounds().overlaps( nodeRect ) )
                {
                    // Render the Point.
                    GFX->getDrawUtil()->drawRectFill( nodeRect, gNodeLookAtPointColor );
                }
            }
        }
    }
}

void VPathEditor::renderPaths( const RenderType &pRenderType )
{
    SimSet *objectSet = VPath::getServerSet();
    for ( SimSetIterator itr( objectSet ); *itr; ++itr )
    {
        VPath *path = dynamic_cast<VPath*>( *itr );
        if ( path )
        {
            // Render Path.
            renderPath( pRenderType, path, ( path == mSelection.Path ) ? gPathColorSel : gPathColor );
        }
    }
}

void VPathEditor::renderPath( const RenderType &pRenderType, VPath *pPath, const ColorI &pColor )
{
    if ( !pPath )
    {
        // Sanity!
        return;
    }

    switch ( pRenderType )
    {
        case k_RenderSegments :
            {
                switch ( pPath->mPathType )
                {
                    case VPath::k_PathLinear : 
                        {
                            renderLinearPath( pPath, pColor );

                        } break;

                    case VPath::k_PathBezier :
                        {
                            renderBezierPath( pPath, pColor );

                        } break;
                }

            } break;

        case k_RenderNodes :
            {
                // Fetch Draw Util.
                GFXDrawUtil *drawUtil = GFX->getDrawUtil();

                // Fetch Bounds.
                RectI bounds = getBounds();

                const Point2I nodeMinHalfSize( 8, 8 );
                for ( VPathNodeIterator itr = pPath->mNodeList.begin(); itr != pPath->mNodeList.end(); itr++ )
                {
                    // Fetch Node.
                    VPathNode *node = ( *itr );

                    // Project to Screen.
                    Point3F screenPosition;
                    project( node->getWorldPosition(), &screenPosition );
                    if ( screenPosition.z > 1.0f )
                    {
                        continue;
                    }

                    // Determine the node text information.
                    const char *nodeText = avar( "%d", ( itr - pPath->mNodeList.begin() ) );
                    const Point2I nodeTextHalfSize = Point2I( 0.5f * (F32)getControlProfile()->mFont->getStrWidth( nodeText ),
                                                              0.5f * (F32)getControlProfile()->mFont->getHeight() );

                    // Determine the center & size of the node rectangle.
                    Point2I nodeCenter = Point2I( screenPosition.x, screenPosition.y );
                    Point2I nodeHalfSize = Point2I( nodeTextHalfSize.x + 3, nodeTextHalfSize.y + 3 );
                    nodeHalfSize.setMax( nodeMinHalfSize );
                    // Determine Render Rectangle.
                    RectI nodeRect;
                    nodeRect.point  = nodeCenter - nodeHalfSize;
                    nodeRect.extent = ( 2 * nodeHalfSize );

                    // Draw?
                    if ( !bounds.overlaps( nodeRect ) )
                    {
                        continue;
                    }

                    // Render the Point.
                    drawUtil->drawRectFill( nodeRect, pColor );

                    // Draw the node index text.
                    drawUtil->setBitmapModulation( getControlProfile()->mFontColor );
                    drawUtil->drawText( getControlProfile()->mFont, nodeCenter - nodeTextHalfSize, nodeText );
                }

            } break;
    }
}

void VPathEditor::renderLinearPath( VPath *pPath, const ColorI &pColor )
{
    if ( pPath->mNodeList.size() < 2 )
    {
        // No Lines.
        return;
    }

    PrimBuild::color( pColor );
    PrimBuild::begin( GFXLineStrip, ( pPath->mNodeList.size() + 1 ) );

    for ( VPathNodeIterator itr = pPath->mNodeList.begin(); itr != pPath->mNodeList.end(); itr++ )
    {
        // Apply Vertex.
        PrimBuild::vertex3fv( ( *itr )->getWorldPosition() );
    }

    // Loop Back.
    PrimBuild::vertex3fv( pPath->mNodeList.front()->getWorldPosition() );

    PrimBuild::end();
}

void VPathEditor::renderBezierPath( VPath *pPath, const ColorI &pColor )
{
    if ( pPath->mNodeList.size() < 2 )
    {
        // No Lines.
        return;
    }

    PrimBuild::color( pColor );
    PrimBuild::begin( GFXLineStrip, U32( ( ( 1.01f / 0.01f ) + 1 ) * pPath->mNodeList.size() ) );

    for ( VPathNodeIterator itr = pPath->mNodeList.begin(); itr != pPath->mNodeList.end(); itr++ )
    {
        // Fetch Nodes.
        VPathNode *srcNode = ( *itr );
        VPathNode *dstNode = ( itr == ( pPath->mNodeList.end() - 1 ) ) ? ( *( pPath->mNodeList.begin() ) ) : ( *( itr + 1 ) );

        // Positions.
        const Point3F &pt0 = srcNode->getWorldPosition();
        const Point3F &pt3 = dstNode->getWorldPosition();

        // Fetch Node Rotation Matrices.
        MatrixF mat0, mat1;
        srcNode->getWorldRotation().setMatrix( &mat0 );
        dstNode->getWorldRotation().setMatrix( &mat1 );

        // Determine Tangent Axis.
        Point3F pt1(  VPath::gBezierAxis * srcNode->getWeight() );
        Point3F pt2( -VPath::gBezierAxis * dstNode->getWeight() );

        // Rotate Axis.
        mat0.mulP( pt1 );
        mat1.mulP( pt2 );

        // Offset Points.
        pt1 += pt0;
        pt2 += pt3;

        for ( F32 t = 0.f, it = 1.f; t <= 1.f; t += 0.01f, it = ( 1.f - t ) )
        {
            // Calculate Position.
            Point3F pos = ( pt0 * it * it * it ) + ( 3 * pt1 * it * it * t ) + ( 3 * pt2 * it * t * t ) + ( pt3 * t * t * t );
            // Apply Vertex.
            PrimBuild::vertex3fv( pos );
        }
    }

    PrimBuild::end();
}

//-----------------------------------------------------------------------------
//
// History Events
//
//-----------------------------------------------------------------------------

void VPathEditor::VPathEditorEditPathAction::undo( void )
{
    const MatrixF oldTransform = mTransform;
    const MatrixF newTransform = mPath->getTransform();

    // Apply Old Values.
    mEditor->setPathTransform( oldTransform );

    // The ol' Switcheroo.
    mTransform = newTransform;

    // Update Selection.
    mEditor->updateSelection();

    if ( mPath == mEditor->mSelection.Path )
    {
        // Arg Buffer.
        char buffer[32];
        dSprintf( buffer, sizeof( buffer ), "%d", mPath->getId() );

        // Callback.
        Con::executef( mEditor, "onUpdatePath", buffer );
    }

    // Set World Editor Dirty.
    mEditor->setWorldEditorDirty();
}

void VPathEditor::VPathEditorEditPathAction::redo( void )
{
    // Undo.
    undo();
}

void VPathEditor::VPathEditorEditNodeAction::undo( void )
{
    // Fetch Properties.
    const Point3F oldPosition = mNodePosition;
    const QuatF   oldRotation = mNodeRotation;
    const F32     oldWeight   = mNodeWeight;
    const VPathNode::sOrientation oldOrientation = mNodeOrientation;

    VPathNode *node           = mPath->getNode( mNodeIndex );
    const Point3F newPosition = node->getLocalPosition();
    const QuatF   newRotation = node->getLocalRotation();
    const F32     newWeight   = node->getWeight();
    const VPathNode::sOrientation newOrientation = node->getOrientationMode();

    // Apply Old Values.
    mPath->setNodePosition( mNodeIndex, oldPosition );
    mPath->setNodeRotation( mNodeIndex, oldRotation );
    mPath->setNodeWeight( mNodeIndex, oldWeight );

    switch( oldOrientation.Type )
    {
    case VPathNode::k_OrientationFree :
        {

            // Orient Free.
            mPath->setNodeOrientationMode( mNodeIndex, oldOrientation.Type );

        } break;

    case VPathNode::k_OrientationToPoint :
        {

            // Orient To Point.
            mPath->setNodeOrientationMode( mNodeIndex, oldOrientation.Type, oldOrientation.Point );

        } break;
    }

    // The ol' Switcheroo.
    mNodePosition    = newPosition;
    mNodeRotation    = newRotation;
    mNodeWeight      = newWeight;
    mNodeOrientation = newOrientation;

    // Update Selection.
    mEditor->updateSelection();

    if ( mPath == mEditor->mSelection.Path )
    {
        // Arg Buffer.
        char buffer[3][32];
        dSprintf( buffer[0], sizeof( buffer[0] ), "%d", mPath->getId() );
        dSprintf( buffer[1], sizeof( buffer[1] ), "%d", mNodeIndex );
        dSprintf( buffer[2], sizeof( buffer[2] ), "%d", ( mEditor->mSelection.Node == mNodeIndex ) );

        // Callback.
        Con::executef( mEditor, "onUpdateNode", buffer[0], buffer[1], buffer[2] );
    }

    // Set World Editor Dirty.
    mEditor->setWorldEditorDirty();
}

void VPathEditor::VPathEditorEditNodeAction::redo( void )
{
    // Undo.
    undo();
}

void VPathEditor::VPathEditorAddNodeAction::undo( void )
{
    // Selected Node?
    if ( mNodeIndex == mEditor->mSelection.Node )
    {
        // Update Selection.
        mEditor->updateSelection( mEditor->mSelection.Path, -1 );
    }

    // Delete Node.
    mPath->deleteNode( mNodeIndex );

    // Update Size.
    mPath->updateContainer();

    // Calculate Path.
    mPath->calculatePath();

    // Set World Editor Dirty.
    mEditor->setWorldEditorDirty();
}

void VPathEditor::VPathEditorAddNodeAction::redo( void )
{
    // Add Node.
    VPathNode *node = mPath->addNode( mNodePosition, mNodeRotation, mNodeWeight, mNodeIndex );

    // Valid Node?
    if ( node )
    {
        // Update Size.
        mPath->updateContainer();

        // Calculate Path.
        mPath->calculatePath();
    }

    // Set World Editor Dirty.
    mEditor->setWorldEditorDirty();
}

void VPathEditor::VPathEditorDeleteNodeAction::undo( void )
{
    // Add Node.
    VPathNode *node = mPath->addNode( mNodePosition, mNodeRotation, mNodeWeight, mNodeIndex );

    // Valid Node?
    if ( node )
    {
        // Update Size.
        mPath->updateContainer();

        // Calculate Path.
        mPath->calculatePath();
    }

    // Set World Editor Dirty.
    mEditor->setWorldEditorDirty();
}

void VPathEditor::VPathEditorDeleteNodeAction::redo( void )
{
    // Delete Node.
    mPath->deleteNode( mNodeIndex );

    // Update Size.
    mPath->updateContainer();

    // Calculate Path.
    mPath->calculatePath();

    // Set World Editor Dirty.
    mEditor->setWorldEditorDirty();
}

//-----------------------------------------------------------------------------
//
// Script Edit Methods
//
//-----------------------------------------------------------------------------

DefineEngineMethod( VPathEditor, setNodePosition, void, (Point3F position), (Point3F::Zero), "( pPosition )" )
{
    // Valid Selection?
    if ( !object->isValidSelection() )
    {
        Con::warnf( "VPathEditor::setNodePosition() - Invalid Node Selection." );
        return;
    }

    // Store.
    object->pushNodeEdit();

    // Apply Update.
    object->setNodePosition( object->mSelection.Node, position );

    // Create Undo Action.
    object->popNodeEdit();
}

DefineEngineMethod( VPathEditor, setNodeRotation, void, (AngAxisF aa), (AngAxisF( Point3F( 0, 0, 1 ), 0)), "( pRotation )" )
{
    // Valid Selection?
    if ( !object->isValidSelection() )
    {
        Con::warnf( "VPathEditor::setNodeRotation() - Invalid Node Selection." );
        return;
    }

    // Fetch Rotation.
    QuatF    rotation;

    // Set Rotation.
    rotation.set( aa );

    // Store.
    object->pushNodeEdit();

    // Apply Update.
    object->setNodeRotation( object->mSelection.Node, rotation );

    // Create Undo Action.
    object->popNodeEdit();
}

DefineEngineMethod( VPathEditor, setNodeWeight, void, (F32 weight), (1), "( pWeight )" )
{
    // Valid Selection?
    if ( !object->isValidSelection() )
    {
        Con::warnf( "VPathEditor::setNodeWeight() - Invalid Node Selection." );
        return;
    }

    // Store.
    object->pushNodeEdit();

    // Apply Update.
    object->setNodeWeight( object->mSelection.Node, weight);

    // Create Undo Action.
    object->popNodeEdit();
}

DefineEngineMethod( VPathEditor, setNodeOrientationMode, void, (String orientationType, Point3F lookAtPoint), ("", Point3F::One), "( string pOrientationType, [vector pPoint] )" )
{
    // Valid Selection?
    if ( !object->isValidSelection() )
    {
        Con::warnf( "VPathEditor::setNodeOrientationMode() - Invalid Node Selection." );
        return;
    }

    // Store.
    object->pushNodeEdit();

    // Orient?
    const VPathNode::eOrientationType type = VPathNode::getOrientationTypeEnum(orientationType);

    switch ( type )
    {
        case VPathNode::k_OrientationFree :
            {

                // Apply Mode.
                object->setNodeOrientationMode( object->mSelection.Node, type );

            } break;

        case VPathNode::k_OrientationToPoint:
            {
                // Apply Mode.
                object->setNodeOrientationMode( object->mSelection.Node, type, lookAtPoint );
            } break;
    }

    // Create Undo Action.
    object->popNodeEdit();
}

//-----------------------------------------------------------------------------
//
// Utility
//
//-----------------------------------------------------------------------------

bool Utility::FindNearestDistanceBetweenLines( const Point3F &pA0, const Point3F &pA1, const Point3F &pB0, const Point3F &pB1, Point3F *pOutA, Point3F *pOutB, F32 *pDist )
{
    const Point3F pA1A0 = ( pA1 - pA0 );
    if ( pA1A0.isZero() )
    {
        return false;
    }

    const Point3F pB1B0 = ( pB1 - pB0 );
    if ( pB1B0.isZero() )
    {
        return false;
    }

    const Point3F pA0B0 = ( pA0 - pB0 );

    const F32 &d1343 = pA0B0.x * pB1B0.x + pA0B0.y * pB1B0.y + pA0B0.z * pB1B0.z;
    const F32 &d4321 = pB1B0.x * pA1A0.x + pB1B0.y * pA1A0.y + pB1B0.z * pA1A0.z;
    const F32 &d1321 = pA0B0.x * pA1A0.x + pA0B0.y * pA1A0.y + pA0B0.z * pA1A0.z;
    const F32 &d4343 = pB1B0.x * pB1B0.x + pB1B0.y * pB1B0.y + pB1B0.z * pB1B0.z;
    const F32 &d2121 = pA1A0.x * pA1A0.x + pA1A0.y * pA1A0.y + pA1A0.z * pA1A0.z;

    const F32 &denom = d2121 * d4343 - d4321 * d4321;
    if ( mIsZero( denom ) )
    {
        return false;
    }

    const F32 &mua = ( d1343 * d4321 - d1321 * d4343 ) / denom;
    const F32 &mub = ( d1343 + d4321 * mua ) / d4343;

    *pOutA = pA0 + mua *pA1A0;
    *pOutB = pB0 + mub *pB1B0;

    // Store Distance.
    *pDist = ( ( *pOutA ) - ( *pOutB ) ).len();

    return true;
}

bool Utility::IntersectLineSegment( const Point3F &pA0, const Point3F &pA1, const Point3F &pB0, const Point3F &pB1, const bool pSnap, Point3F *pX )
{
    //
    // Finding the intersection with the following method:
    // We have line a going from P1 to P2:
    //    Pa = P1 + ua( P2 - P1 )
    // and line b going from P3 to P4:
    //    Pb = P3 + ub( P4 - P3 )
    //
    // Solving for Pa = Pb:
    //    x1 + ua( x2 - x1 ) = x3 + ub( x4 - x3 )
    //    y1 + ua( y2 - y1 ) = y3 + ub( y4 - y3 )
    //
    // Solving for ua and ub:
    //    ua = ( ( x4 - x3 )( y1 - y3 ) - ( y4 - y3 )( x1 - x3 ) ) / d
    //    ub = ( ( x2 - x1 )( y1 - y3 ) - ( y2 - y1 )( x1 - x3 ) ) / d
    //    denom = ( y4 - y3 )( x2 - x1 ) - ( x4 - x3 )( y2 - y1 )
    //
    // x = x1 + ua( x2 - x1 )
    // y = y1 + ua( y2 - y1 )
    //

    const F32 d = ( ( pB1.y - pB0.y ) * ( pA1.x - pA0.x ) ) - ( ( pB1.x - pB0.x ) * ( pA1.y - pA0.y ) );

    if ( d == 0.0f )
    {
        // Lines are parallel
        return false;
    }

    // Find the point of intersection
    const F32 uA = ( ( ( pB1.x - pB0.x ) * ( pA0.y - pB0.y ) ) - ( ( pB1.y - pB0.y ) * ( pA0.x - pB0.x ) ) ) / d;
    const F32 uB = ( ( ( pA1.x - pA0.x ) * ( pA0.y - pB0.y ) ) - ( ( pA1.y - pA0.y ) * ( pA0.x - pB0.x ) ) ) / d;

    if ( !pSnap
         && ( ( uA < 0.0f ) || ( uA > 1.0f )
           || ( uB < 0.0f ) || ( uB > 1.0f ) ) )
    {
        return false;
    }

    if ( pX )
    {
        if ( uA < 0.0f )
        {
            *pX = pA0;
        }
        else if ( uA > 1.f )
        {
            *pX = pA1;
        }
        else
        {
            // The path intersects the segment
            *pX = pA0 + uA * ( pA1 - pA0 );
        }
    }

    return true;
}

bool Utility::FindNearestPointOnLine( const Point3F &pSrcPosition, const Point3F &pA0, const Point3F &pA1, Point3F *pDstPosition )
{
    const Point3F up( 0.0f, 0.0f, 1.0f );
    
    Point3F dir = ( pA1 - pA0 );
    dir.normalize();

    Point3F normal = mCross( dir, up );
    normal.normalize();

    // Find the nearest intersection point between the point and the line

    const Point3F b0 = pSrcPosition + ( normal * 100000.0f );
    const Point3F b1 = pSrcPosition - ( normal * 100000.0f );

    return IntersectLineSegment( pA0, pA1, b0, b1, true, pDstPosition );
}

F32 Utility::GetPitch( const VectorF &pVec )
{
    F32 pitch;
    if ( mFabs( pVec.x ) > mFabs( pVec.y ) )
    {
        pitch = mAtan2( mFabs( pVec.z ), mFabs( pVec.x ) );
    }
    else
    {
        pitch = mAtan2( mFabs( pVec.z ), mFabs( pVec.y ) );
    }

    if ( pVec.z < 0.f )
    {
        pitch = -pitch;
    }

    return pitch;
}

F32 Utility::GetYaw( const VectorF &pVec )
{
    F32 yaw = mAtan2( pVec.x, pVec.y );
    if ( yaw < 0.f )
    {
        yaw += M_2PI_F;
    }

    return yaw;
}
#endif
