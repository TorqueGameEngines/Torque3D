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
#ifndef _VT_VPATHEDITOR_H_
#define _VT_VPATHEDITOR_H_

#include "torqueConfig.h"
#ifdef TORQUE_TOOLS
#ifndef _EDITTSCTRL_H_
#include "gui/worldEditor/editTSCtrl.h"
#endif

#ifndef _VT_VPATH_H_
#include "VPath.h"
#endif

#ifndef _UNDO_H_
#include "util/undo.h"
#endif

//-----------------------------------------------------------------------------

class VPathEditor : public EditTSCtrl
{
    typedef EditTSCtrl Parent;

public:

    enum RenderType
    {
        k_RenderSegments,
        k_RenderNodes,
    };

    enum EditMode
    {
        k_Gizmo,
        k_AddNode,
        k_DeleteNode
    };

    struct Selection
    {
        Selection( void ) :
                Path( NULL ),
                Node( -1 )
        {
            TangentHandle[0].zero();
            TangentHandle[1].zero();
        };

        VPath     *Path;
        S32        Node;
        Point3F    TangentHandle[2];
    };

    struct PathEditAction
    {
        PathEditAction( void ) :
                Dirty( false ),
                Transform( true )
        {
            // Void.
        };

        bool        Dirty;
        MatrixF     Transform;
    };

    struct NodeEditAction
    {
        NodeEditAction( void ) :
                Dirty( false ),
                Position( 0.f, 0.f, 0.f ),
                Rotation( 0.f, 0.f, 0.f, 0.f ),
                Weight( 0.f )
        {
            // Void.
        };

        bool        Dirty;
        Point3F     Position;
        QuatF       Rotation;
        F32         Weight;
    };

    bool                mIsDirty;
    EditMode            mEditMode;

    Selection           mSelection;
    PathEditAction      mPathEdit;
    NodeEditAction      mNodeEdit;

    bool                mEditWeight;
    S32                 mEditWeightHandle;

    GFXStateBlockRef    mStateBlock;

public:

    VPathEditor( void );

    virtual bool    onAdd( void );
    virtual bool    onWake( void );

    static  void    initPersistFields();

    // Gui Events.

    virtual void    on3DMouseDown( const Gui3DMouseEvent &pEvent );
    virtual void    on3DMouseUp( const Gui3DMouseEvent &pEvent );
    virtual void    on3DMouseMove( const Gui3DMouseEvent &pEvent );
    virtual void    on3DMouseDragged( const Gui3DMouseEvent &pEvent );

    // Render Methods.

    virtual void    setStateBlock( void );
    virtual void    renderScene( const RectI &pUpdateRect );
    void            renderPaths( const RenderType &pRenderType );

    void            renderPath( const RenderType &pRenderType, VPath *pPath, const ColorI &pColor );
    void            renderLinearPath( VPath *pPath, const ColorI &pColor );
    void            renderBezierPath( VPath *pPath, const ColorI &pColor );

    DECLARE_CONOBJECT( VPathEditor );

public:

    // Reference Methods.

    VPath          *getClientPath( VPath *pPath );

    // Selection Methods.

    inline bool     isValidSelection( void ) { return ( mSelection.Path != NULL && mSelection.Node != -1 ); };

    bool            updateSelection( const Gui3DMouseEvent &pEvent );
    void            updateSelection( VPath *pPathObject, const S32 &pNodeIndex );
    void            updateSelection( void );

    // Weight Editing.

    bool            isEditingWeight( const Gui3DMouseEvent &pEvent );
    inline bool     isEditingWeight( void ) { return mEditWeight; };

    void            updateWeight( const Gui3DMouseEvent &pEvent );

    // Path Editor.

    bool            getPointOnPath( VPath *pPath, const Gui3DMouseEvent &pEvent, S32 &pNode, MatrixF &pTransform );
    bool            getPointOnLinearPath( VPath *pPath, const Gui3DMouseEvent &pEvent, S32 &pNode, MatrixF &pTransform );
    bool            getPointOnBezierPath( VPath *pPath, const Gui3DMouseEvent &pEvent, S32 &pNode, MatrixF &pTransform );

    void            setPathPosition( const Point3F &pPosition );
    void            setPathRotation( const QuatF &pRotation );
    void            setPathTransform( const MatrixF &pTransform );
    void            setPathScale( const VectorF &pScale );

    // Node Editing.

    void            addNode( const Gui3DMouseEvent &pEvent );
    void            deleteNode( const S32 &pNodeIndex );

    void            setNodePosition( const S32 &pNodeIndex, const Point3F &pPosition );
    void            setNodeRotation( const S32 &pNodeIndex, const QuatF &pRotation );
    void            setNodeWeight( const S32 &pNodeIndex, const F32 &pWeight );
    void            setNodeOrientationMode( const S32 &pNodeIndex, const VPathNode::eOrientationType &pType );
    void            setNodeOrientationMode( const S32 &pNodeIndex, const VPathNode::eOrientationType &pType, const Point3F &pPoint );

    void            pushPathEdit( void );
    void            popPathEdit( void );

    void            pushNodeEdit( void );
    void            popNodeEdit( void );

    void            setWorldEditorDirty( void );

private:

    class VPathEditorEditPathAction : public UndoAction
    {
    public:

        VPathEditorEditPathAction( const UTF8 *pName = "" ) :
                UndoAction( pName ), mEditor(NULL), mPath(NULL)
        {
            // Void.
        };

        VPathEditor               *mEditor;

        VPath                     *mPath;
        MatrixF                    mTransform;

        virtual void    undo( void );
        virtual void    redo( void );
    };

    class VPathEditorEditNodeAction : public UndoAction
    {
    public:

        VPathEditorEditNodeAction( const UTF8 *pName = "" ) :
                UndoAction( pName ), mEditor(NULL), mPath(NULL), mNodeIndex(0), mNodeWeight(0.0f)
        {
            // Void.
           mNodeOrientation.Type = VPathNode::k_OrientationFree;
           mNodeOrientation.Point = Point3F(0.0f, 0.0f, 0.0f);
        };

        VPathEditor               *mEditor;

        VPath                     *mPath;
        S32                        mNodeIndex;

        Point3F                    mNodePosition;
        QuatF                      mNodeRotation;
        F32                        mNodeWeight;

        VPathNode::sOrientation    mNodeOrientation;

        virtual void    undo( void );
        virtual void    redo( void );
    };

    class VPathEditorAddNodeAction : public VPathEditorEditNodeAction
    {
    public:

        VPathEditorAddNodeAction( const UTF8 *pName = "" ) :
                VPathEditorEditNodeAction( "Add Node" )
        {
            // Void.
        };

        virtual void    undo( void );
        virtual void    redo( void );
    };

    class VPathEditorDeleteNodeAction : public VPathEditorEditNodeAction
    {
    public:

        VPathEditorDeleteNodeAction( const UTF8 *pName = "" ) :
                VPathEditorEditNodeAction( "Delete Node" )
        {
            // Void.
        };

        virtual void    undo( void );
        virtual void    redo( void );
    };
};

//-----------------------------------------------------------------------------

// Define Types.
typedef VPathEditor::EditMode VPathEditorMode;

// Declare Enum Types.
DefineEnumType( VPathEditorMode );

//-----------------------------------------------------------------------------

namespace Utility
{
    bool            FindNearestDistanceBetweenLines( const Point3F &pA0, const Point3F &pA1, const Point3F &pB0, const Point3F &pB1, Point3F *pOutA, Point3F *pOutB, F32 *pDist );

    bool            IntersectLineSegment( const Point3F &pA0, const Point3F &pA1, const Point3F &pB0, const Point3F &pB1, const bool pSnap, Point3F *pX );
    bool            FindNearestPointOnLine( const Point3F &pSrcPosition, const Point3F &pA0, const Point3F &pA1, Point3F *pDstPosition );

    F32             GetPitch( const VectorF &pVec );
    F32             GetYaw( const VectorF &pVec );
};

//-----------------------------------------------------------------------------
#endif
#endif // _VT_VPATHEDITOR_H_
