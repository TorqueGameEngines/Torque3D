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
#ifndef _VT_VACTORPHYSICSCONTROLLER_H_
#define _VT_VACTORPHYSICSCONTROLLER_H_

#ifndef _VT_TYPES_H_
#include "Types/VTypes.h"
#endif

#ifndef _VT_VACTORSTATETABLE_H_
#include "VActorStateTable.h"
#endif

#ifndef _VT_VACTOR_H_
#include "VActor.h"
#endif

#ifndef _VT_VINTERPCONTROLLER_H_
#include "VInterpController.h"
#endif

#ifndef _BOXCONVEX_H_
#include "collision/boxConvex.h"
#endif

//-----------------------------------------------------------------------------

class VPath;

//-----------------------------------------------------------------------------

class VActorPhysicsController
{
protected:

    SimObjectPtr<VActor>         mObject;
    SimObjectPtr<VPath>          mMountedPath;

    VActorStateTable             mPhysicsStateTable;

    VInterpController            mInterpController;

    U32                          mPhysicsState;
    U32                          mControlState;
    U32                          mMoveState;

    OrthoBoxConvex               mConvex;

    VectorF                      mGravity;
    VectorF                      mVelocity;

    bool                         mOnGround;
    SimObjectPtr<SceneObject>    mGroundObject;
    VectorF                      mGroundNormal;

public:

    VActorPhysicsController( void );
    virtual ~VActorPhysicsController( void );

    // Initialisation Methods.

    bool                     initPhysicsController( VActor *pObject );
    bool                     initPhysicsTable( void );

    // Accessor Methods.

    bool                     isValidObject( void );
    VActor                  *getObject( void );
    VActorData              *getObjectDataBlock( void );
    void                     clearObject( void );

    virtual const U32        getControlState( void );
    virtual void             clearControlState( const U32 &pControlState );
    virtual void             setControlState( const U32 &pControlState );

    virtual const bool       isMoving( void );
    virtual const bool       isMoving( const U32 &pMoveState );
    virtual const U32        getMoveState( void );
    virtual void             clearMoveState( const U32 &pMoveState );
    virtual void             setMoveState( const U32 &pMoveState );

    virtual const bool       isPathing( void );
    virtual VPath           *getPathObject( void );

    virtual const bool       isInWater( void );
    virtual WaterObject     *getWaterObject( void );

    virtual const bool       isOnGround( void );
    virtual const bool       isInAir( void );
    inline  SceneObject     *getGroundObject( void ) { return mGroundObject; };
    inline  const VectorF   &getGroundNormal( void ) { return mGroundNormal; };

    inline  const U32       &getPhysicsState( void ) { return mPhysicsState; };
    inline  void             setPhysicsState( const U32 &pState ) { mPhysicsState = pState; };

    virtual MatrixF          getTransform( void );
    virtual void             setTransform( const MatrixF &pTransform );

    virtual Point3F          getPosition( void );
    virtual void             setPosition( const Point3F &pPosition );

    inline  VectorF          getGravity( void ) { return mGravity; };
    inline  void             setGravity( VectorF &pGravity ) { mGravity = pGravity; };
    virtual void             applyGravity( const F32 &pElapsedTime );

    virtual VectorF          getVelocity( void );
    virtual void             setVelocity( const VectorF &pVelocity );

    // Physics Methods.

    void                     update( const F32 &pDelta, const Move *pMove );

    virtual void             preTickUpdate( const F32 &pDelta );
    virtual void             integrateTickUpdate( const F32 &pDelta, const Move *pMove );
    virtual void             postTickUpdate( const F32 &pDelta );

    void                     interpolateTick( const F32 &pDelta );

    void                     updateWorkingCollisionSet( void );

    void                     updateMoveState( void );

    void                     clearGroundStatus( void );
    void                     updateGroundStatus( void );
    bool                     findGroundContact( SceneObject *&pContactObject, Point3F &pContactPoint, VectorF &pContactNormal );

    void                     processCollisions( void );
    bool                     findCollision( Collision *&pCollision );
    void                     solveCollision( Collision *pCollision );

    // Updates Methods.

    void                     onActorEvent( const VActor::eEventType &pEvent );

    U32                      packUpdate( NetConnection *pConnection, U32 pMask, BitStream *pStream );
    void                     unpackUpdate( NetConnection *pConnection, BitStream *pStream );
};

#endif // _VT_VACTORANIMATIONCONTROLLER_H_