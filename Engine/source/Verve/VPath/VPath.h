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
#ifndef _VT_VPATH_H_
#define _VT_VPATH_H_

#ifndef _SCENEOBJECT_H_
#include "scene/sceneObject.h"
#endif

#ifndef _VT_PATHNODE_H_
#include "VPathNode.h"
#endif

#ifndef _VT_PATHOBJECT_H_
#include "VPathObject.h"
#endif

//-----------------------------------------------------------------------------

typedef Vector<VPathNode*>             VPathNodeVector;
typedef VPathNodeVector::iterator      VPathNodeIterator;

typedef Vector<VPathObject*>           VPathObjectVector;
typedef VPathObjectVector::iterator    VPathObjectIterator;

//-----------------------------------------------------------------------------

class VPath : public SceneObject
{
    typedef SceneObject Parent;

    friend class VPathEditor;

public:

    // Static Members.

    static SimObjectPtr<SimSet>    gServerSet;

    static U32                     gMaxNodeTransmit;
    static U32                     gMaxNodeBits;
    static U32                     gMaxNodeCount;

    static U32                     gMaxObjectTransmit;
    static U32                     gMaxObjectBits;
    static U32                     gMaxObjectCount;

    static Point3F                 gBezierAxis;
    static Point3F                 gBezierUp;

    enum eMaskBits
    {
        InitialUpdateMask = Parent::NextFreeMask << 0,
        PathUpdateMask    = Parent::NextFreeMask << 1,
        NodeUpdateMask    = Parent::NextFreeMask << 2,
        ObjectUpdateMask  = Parent::NextFreeMask << 3,
        NextFreeMask      = Parent::NextFreeMask << 4,
    };

    enum ePathType
    {
       k_PathLinear,
       k_PathBezier,

       k_PathInvalid,

       k_PathTypeSize,
    };

private:

    U32                  mPathType;

    VPathNodeVector      mNodeList;

    VPathObjectVector    mObjectList;

public:

    VPath( void );
    ~VPath( void );

    bool                onAdd( void );
    void                onDeleteNotify( SimObject *pObject );
    void                onRemove( void );

    static void         initPersistFields();

    static SimSet      *getServerSet( void );

    // Editor Methods.

    bool                collideBox( const Point3F &pStart, const Point3F &pEnd, RayInfo* pInfo );

    // Update Methods.

    F32                 getUpdatePriority( CameraScopeQuery *pFocusObject, U32 pUpdateMask, S32 pUpdateSkips );

    void                updateContainer( void );
    void                updateNodeTransforms( void );

    void                setTransform( const MatrixF &pMatrix );
    void                setScale( const VectorF &pScale );

    void                setPathType( const ePathType &pType );
    static bool         setPathType( void *pObject, const char *pArray, const char *pData );

    // Mounting Methods.

    U32                 getAvailableMountIndex( void );
    bool                isMountIndex( const U32 &pIndex );

    void                mountObject( SceneObject *pObject, S32 pIndex, const MatrixF &pTransform = MatrixF::Identity );
    void                unmountObject( SceneObject *pObject );

    void                getMountTransform( S32 pIndex, const MatrixF &pInTransform, MatrixF *pTransform );
    void                getRenderMountTransform( F32 pDelta, S32 pIndex, const MatrixF &pInTransform, MatrixF *pTransform );

    VectorF             getMountVelocity( const U32 &pIndex );

    // Persistence Methods.

    void                readFields( void );
    void                writeFields( Stream &pStream, U32 pTabStop );

    U32                 packUpdate( NetConnection *pConnection, U32 pMask, BitStream *pStream );
    void                unpackUpdate( NetConnection *pConnection, BitStream *pStream );

    DECLARE_CONOBJECT( VPath );

public:

    // Node Methods.

    static VPathNode   *createNode( void );
    static void         deleteNode( VPathNode *pNode );

    void                clear( void );

    VPathNode          *getNode( const S32 &pNodeIndex );

    VPathNode          *addNode( const Point3F &pPosition, const QuatF &pRotation, const F32 &pWeight, const S32 &pLocation = -1 );
    VPathNode          *addNode( VPathNode *pNode, const S32 &pLocation = -1 );

    void                deleteNode( const S32 &pNodeIndex );
    void                removeNode( const S32 &pNodeIndex );

    S32                 normalizeNodeIndex( S32 &pNodeIndex );
    S32                 normalizeNodeIndex( const S32 &pNodeIndex );
    S32                 normalizeNodeIndex( S32 &pNodeIndex, const S32 &pNodeCount );

    // Object Methods.

    bool                isObjectAttached( SceneObject *pObject );
    VPathObject        *getPathObject( SceneObject *pObject );

    void                attachObject( SceneObject *pObject, const bool &pForward, const F32 &pSpeed, const bool &pRelative, const S32 &pStartNode, const S32 &pEndNode );
    void                attachObject( SceneObject *pObject, const bool &pForward, const F32 &pSpeed, const bool &pRelative, const S32 &pStartNode, const S32 &pEndNode, const VPathObject::eOrientationType &pOrientationMode );
    void                attachObject( SceneObject *pObject, const bool &pForward, const F32 &pSpeed, const bool &pRelative, const S32 &pStartNode, const S32 &pEndNode, const VPathObject::eOrientationType &pOrientationMode, void *pOrientationData );
    void                attachObject( VPathObject *pPathObject );
    void                onAttachObject( VPathObject *pPathObject );

    void                detachObject( SceneObject *pObject );
    void                detachObject( VPathObject *pPathObject );
    void                onDetachObject( VPathObject *pPathObject );

    void                processTick( const Move *pMove );
    void                advanceObject( VPathObject *pPathObject, const F32 &pDelta );

    void                updatePosition( VPathObject *pPathObject );
    void                updateOrientation( VPathObject *pPathObject );
    void                updateOrientation( VPathObject *pPathObject, const Point3F &pPathOrientation );

    // Path Methods.

    void                calculatePath( void );

    Point3F             getAdvancedPathPosition( VPathObject *pPathObject, const F32 &pTargetDistance, F32 &pInterpDelta );
    
    Point3F             getPathPosition( VPathNode *pSourceNode, VPathNode *pDestinationNode, const F32 &pTimeInterp, const bool &pForward );
    Point3F             getPathPosition( VPathNode *pSourceNode, VPathNode *pDestinationNode, const F32 &pTimeInterp, const bool &pForward, F32 &pPathInterp );
    VectorF             getPathOrientation( VPathNode *pSourceNode, VPathNode *pDestinationNode, const F32 &pTimeInterp, const bool &pForward );

    //
    // Linear Path Methods.

    void                calculateLinearPath( VPathNode *pNode, VPathNode *pNextNode );

    Point3F             getAdvancedLinearPathPosition( VPathObject *pPathObject, const F32 &pTargetDistance, F32 &pInterpDelta );

    Point3F             getLinearPathPosition( VPathNode *pSourceNode, VPathNode *pDestinationNode, const F32 &pInterp, const bool &pForward, F32 &pPathInterp );
    VectorF             getLinearPathOrientation( VPathNode *pSourceNode, VPathNode *pDestinationNode, const F32 &pInterp, const bool &pForward );

    //
    // Bezier Path Methods.

    void                calculateBezierPath( VPathNode *pNode, VPathNode *pNextNode );

    Point3F             getAdvancedBezierPathPosition( VPathObject *pPathObject, const F32 &pTargetDistance, F32 &pInterpDelta );

    Point3F             getBezierPathPosition( VPathNode *pSourceNode, VPathNode *pDestinationNode, const F32 &pInterp, const bool &pForward, F32 &pPathInterp );
    Point3F             getBezierPathPosition( VPathNode *pSourceNode, VPathNode *pDestinationNode, const F32 &pInterp, const Point3F &pReferencePosition, const F32 &pTargetDistance, const bool &pForward, const bool &pRelativeToReference, F32 &pPathInterpDelta );
    VectorF             getBezierPathOrientation( VPathNode *pSourceNode, VPathNode *pDestinationNode, const F32 &pInterp, const bool &pForward );

public:

    // Node Property Methods.

    S32                 getNodeCount( void );

    Point3F             getNodeLocalPosition( const S32 &pNodeIndex );
    Point3F             getNodeWorldPosition( const S32 &pNodeIndex );
    QuatF               getNodeLocalRotation( const S32 &pNodeIndex );
    QuatF               getNodeWorldRotation( const S32 &pNodeIndex );
    F32                 getNodeWeight( const S32 &pNodeIndex );
    F32                 getNodeLength( const S32 &pNodeIndex );

    void                setNodePosition( const S32 &pNodeIndex, const Point3F &pPosition );
    void                setNodeRotation( const S32 &pNodeIndex, const QuatF &pRotation );
    void                setNodeWeight( const S32 &pNodeIndex, const F32 &pWeight );

    void                setNodeOrientationMode( const S32 &pNodeIndex, const VPathNode::eOrientationType &pType );
    void                setNodeOrientationMode( const S32 &pNodeIndex, const VPathNode::eOrientationType &pType, const Point3F pPoint );

    // Path Object Property Methods.

    void                setPathObjectActive( SceneObject *pObject, const bool &pActive );
    void                setPathObjectInterp( SceneObject *pObject, const F32 &pTimeInterp );
    void                setPathObjectOffset( SceneObject *pObject, const Point3F &pOffset );
    void                setPathObjectSpeed( SceneObject *pObject, const F32 &pSpeed );
    void                setPathObjectOrientationMode( SceneObject *pObject, const VPathObject::eOrientationType &pType );
    void                setPathObjectOrientationMode( SceneObject *pObject, const VPathObject::eOrientationType &pType, SceneObject *pLookAtObject );
    void                setPathObjectOrientationMode( SceneObject *pObject, const VPathObject::eOrientationType &pType, const Point3F pPoint );
    void                setPathObjectForward( SceneObject *pObject, const bool &pForward );
    void                setPathObjectNode( SceneObject *pObject, const S32 &pNodeIndex );
    void                setPathObjectEndNode( SceneObject *pObject, const S32 &pNodeIndex );

    void                setPathObjectInterp( VPathObject *pPathObject, const F32 &pTimeInterp );
};

//-----------------------------------------------------------------------------

// Define Types.
typedef VPath::ePathType VPathType;

// Declare Enum Types.
DefineEnumType( VPathType );

//-----------------------------------------------------------------------------

#endif // _VT_VPATH_H_