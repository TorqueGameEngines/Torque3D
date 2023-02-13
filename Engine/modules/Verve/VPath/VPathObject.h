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
#ifndef _VT_VPATHOBJECT_H_
#define _VT_VPATHOBJECT_H_

#ifndef _GAMEBASE_H_
#include "T3D/gameBase/gameBase.h"
#endif

#ifndef _VNETSTATE_H_
#include "VNetState.h"
#endif

#ifndef _MOVEMANAGER_H_
#include "T3D/gameBase/moveManager.h"
#endif

//-----------------------------------------------------------------------------

class VPath;
class NetConnection;

struct VPathObject
{
public:

    enum eState
    {
        k_StateUpdateObject   = BIT( 0 ),
        k_StateUpdateMount    = BIT( 1 ),
        k_StateUpdatePosition = BIT( 2 ),
        k_StateUpdateState    = BIT( 3 ),

        k_StateAttach         = BIT( 4 ),
        k_StateDetach         = BIT( 5 ),

        k_StateUpdate         = ( k_StateUpdateObject | k_StateUpdateMount | k_StateUpdatePosition | k_StateUpdateState ),

        k_StateInit           = ( k_StateAttach | k_StateUpdate ),
    };

    enum eOrientationType
    {
        k_OrientationFree,
        k_OrientationInterpolate,

        k_OrientationToPath,
        k_OrientationToObject,
        k_OrientationToPoint,

        k_OrientationTypeSize,
    };

    struct sOrientation
    {
        eOrientationType    Type;

        // k_OrientationToObject
        SceneObject        *Object;
        // k_OrientationToPoint
        Point3F             Point;
    };

    struct sDelta
    {
        Point3F    Position[2];
        VectorF    Orientation[2];
    };

protected:

    bool            mActive;

    U32             mLastTime;
    F32             mLastDelta;

    SceneObject    *mObject;

    VNetState       mNetState;
    sDelta          mDelta;

    F32             mTimeInterp;
    F32             mPathInterp;
    Point3F         mPosition;
    Point3F         mOffset;
    sOrientation    mOrientationMode;
    VectorF         mOrientation;
    bool            mForward;
    F32             mSpeed;

    S32             mSourceNode;
    S32             mDestinationNode;

    S32             mStartNode;
    S32             mEndNode;

public:

    VPathObject( void );
    ~VPathObject( void );

    // Network Methods.

    U32             packUpdate( NetConnection *pConnection, BitStream *pStream );
    void            unpackUpdate( NetConnection *pConnection, BitStream *pStream );

    //-------------------------------------------------------------------------
    //
    // Gets
    //
    //-------------------------------------------------------------------------

    inline const bool           &isActive( void )           { return mActive;          };
    
    inline SceneObject          *getObject( void )          { return mObject;          };

    inline const F32            &getTimeInterp( void )      { return mTimeInterp;      };
    inline const F32            &getPathInterp( void )      { return mPathInterp;      };
    inline const Point3F        &getPosition( void )        { return mPosition;        };
    inline const Point3F        &getOffset( void )          { return mOffset;          };
    inline const VectorF        &getOrientation( void )     { return mOrientation;     };
    inline const sOrientation   &getOrientationMode( void ) { return mOrientationMode; };

    inline const bool           &isForward( void )          { return mForward;         };
    inline const F32            &getSpeed( void )           { return mSpeed;           };

    inline const S32            &getSourceNode( void )      { return mSourceNode;      };
    inline const S32            &getDestinationNode( void ) { return mDestinationNode; };
    inline const S32            &getStartNode( void )       { return mStartNode;       };
    inline const S32            &getEndNode( void )         { return mEndNode;         };

    Point3F                      getWorldPosition( void );
    Point3F                      getRenderWorldPosition( const F32 &pDelta );

    MatrixF                      getTransform( void );
    MatrixF                      getRenderTransform( const F32 &pDelta );

    inline F32 getTimeDelta( const bool &pUpdate = true )
    {
        if ( !pUpdate )
        {
            return mLastDelta;
        }

        // Calculate Delta.
        const S32 time  = Sim::getCurrentTime();
        const F32 delta = ( time - mLastTime ) / 1000.f;

        // Store Time.
        mLastTime  = time;
        mLastDelta = delta;

        // Return Delta.
        return delta;
    };

    inline void resetTime( void )
    {
        mLastTime = Sim::getCurrentTime();
    };

    //-------------------------------------------------------------------------
    //
    // Sets
    //
    //-------------------------------------------------------------------------

    void            setActive( const bool &pActive );

    void            setObject( SceneObject *pObject );

    void            setTimeInterp( const F32 &pInterp );
    void            setPathInterp( const F32 &pInterp );
    void            setPosition( const Point3F &pPosition );
    void            setOffset( const Point3F &pOffset );
    void            setOrientation( const VectorF &pOrientation );
    void            setOrientationMode( const eOrientationType &pType );
    void            setOrientationMode( const eOrientationType &pType, SceneObject *pObject );
    void            setOrientationMode( const eOrientationType &pType, const Point3F &pPoint );

    void            setForward( const bool &pForward );
    void            setSpeed( const F32 &pSpeed );

    void            setNode( const S32 &pSourceNodeIndex, const S32 &pDestinationNodeIndex );
    void            setStartNode( const S32 &pNodeIndex );
    void            setEndNode( const S32 &pNodeIndex );

    // Delta Methods.

    void            resetDelta( void );
    void            resetDelta( const Point3F &pPosition, const VectorF &pOrientation );

    void            popDelta( void );
    void            pushDelta( const Point3F &pPosition, const VectorF &pOrientation );

    Point3F         getPositionDelta( const F32 &pInterp );
    VectorF         getOrientationDelta( const F32 &pInterp );

    // Net State Methods.

    inline VNetStateInfo   *getState( NetConnection *pConnection )        { return mNetState.getState( pConnection );     };

    inline void             setMaskBits( const U32 &pMask )               { mNetState.setMaskBits( pMask );               };
    inline void             clearMaskBits( const U32 &pMask )             { mNetState.clearMaskBits( pMask );             };

    inline bool             isConnection( NetConnection *pConnection )    { return mNetState.isConnection( pConnection ); };
    inline void             addConnection( NetConnection *pConnection )   { mNetState.addConnection( pConnection );       };
    inline void             clearConnection( NetConnection *pConnection ) { mNetState.clearConnection( pConnection );     };

    // Enum Methods.

    static eOrientationType    getOrientationTypeEnum( const char *pLabel );
    static StringTableEntry    getOrientationTypeLabel( const eOrientationType &pType );
};

//-----------------------------------------------------------------------------

// Define Types.
typedef VPathObject::eOrientationType VPathObjectOrientationType;

// Declare Enum Types.
DefineEnumType( VPathObjectOrientationType );

//-----------------------------------------------------------------------------

#endif // _VT_VPATHOBJECT_H_