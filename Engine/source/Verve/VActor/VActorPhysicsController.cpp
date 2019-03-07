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
#include "VActorPhysicsController.h"

#include "VActor.h"
#include "VActorData.h"
#include "VActorPhysicsStates.h"

#include "Verve/VPath/VPath.h"

#include "collision/clippedPolyList.h"
#include "collision/earlyOutPolyList.h"
#include "collision/extrudedPolyList.h"
#include "core/stream/bitStream.h"
#include "environment/waterObject.h"

//-----------------------------------------------------------------------------

static const U32 sGroundCollisionMask = ( StaticObjectType | StaticShapeObjectType | TerrainObjectType );
static const U32 sMoveCollisionMask   = ( PlayerObjectType | VehicleObjectType );
static const U32 sCollisionMask       = ( sGroundCollisionMask | sMoveCollisionMask );

//-----------------------------------------------------------------------------

VActorPhysicsController::VActorPhysicsController( void ) :
        mObject( NULL ),
        mMountedPath( NULL ),
        mPhysicsState( 0 ),
        mControlState( k_NullControlState ),
        mMoveState( k_NullMove ),
        mVelocity( VectorF::Zero ),
        mGravity( 0.f, 0.f, -9.8f )
{
    // Void.
}

VActorPhysicsController::~VActorPhysicsController( void )
{
    // Clear Object.
    clearObject();
}




//-----------------------------------------------------------------------------
//
// Initialisation Methods.
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//
// VActorPhysicsController::initPhysicsController();
//
// Initialise the physics table and setup the interface between the Controller
// and the reference object.
//
//-----------------------------------------------------------------------------
bool VActorPhysicsController::initPhysicsController( VActor *pObject )
{
    // Valid Object?
    if ( !pObject )
    {
        // Assert & Quit.
        AssertFatal( false, "VActorPhysicsController::initPhysicsController() - Invalid Object Specified." );
        return false;
    }

    // Set Object.
    mObject = pObject;
    // Register for Actor Events.
    mObject->getEventSignal().notify( this, &VActorPhysicsController::onActorEvent );

    // Set Table's Reference.
    mPhysicsStateTable.setObject( pObject );

    // Init the Convex Box.
    mConvex.init( pObject );

    // Reset Interp.
    mInterpController.resetDelta( pObject->getTransform() );

    // Validate.
    return initPhysicsTable();
}

//-----------------------------------------------------------------------------
//
// VActorPhysicsController::initPhysicsTable();
//
// Register the available physics states which this controller may utilize.
//
//-----------------------------------------------------------------------------
bool VActorPhysicsController::initPhysicsTable( void )
{
    // Valid Object?
    if ( !isValidObject() )
    {
        // No, Quit Now.
        return false;
    }

    // Clear the Table.
    mPhysicsStateTable.clear();

    // Fetch Sequence List.
    VActorData::tPhysicsStateVector *stateList = getObjectDataBlock()->getPhysicsStateList();

    // Initialise the Physics States.
    for ( VActorData::tPhysicsStateVector::iterator itr = stateList->begin();
          itr != stateList->end();
          itr++ )
    {
        // Fetch Sequence Definition.
        const VActorData::sPhysicsState &physState = ( *itr );

        // Valid State?
        if ( physState.State )
        {
            // Register State.
            mPhysicsStateTable.registerState( physState.State, physState.Priority );
        }
    }

    // Sort the Table.
    mPhysicsStateTable.sort();

    // Valid.
    return true;
}




//-----------------------------------------------------------------------------
//
// Accessor Methods
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//
// VActorPhysicsController::isValidObject();
//
// Do we have a valid reference object?
//
//-----------------------------------------------------------------------------
bool VActorPhysicsController::isValidObject( void )
{
    return ( mObject && mObject->getDataBlock() );
}

//-----------------------------------------------------------------------------
//
// VActorPhysicsController::getObject();
//
// Return the reference object.
//
//-----------------------------------------------------------------------------
VActor *VActorPhysicsController::getObject( void )
{
    return mObject;
}

//-----------------------------------------------------------------------------
//
// VActorPhysicsController::getObjectDataBlock();
//
// Get the Actor Data for the reference object.
//
//-----------------------------------------------------------------------------
VActorData *VActorPhysicsController::getObjectDataBlock( void )
{
    // Valid Object?
    if ( !mObject )
    {
        // No.
        return NULL;
    }

    // Return DataBlock.
    return mObject->getDataBlock();
}

//-----------------------------------------------------------------------------
//
// VActorPhysicsController::clearObject();
//
// Clear the reference object. Note that this should *never* be called outside
// of the controller's destructor!
//
//-----------------------------------------------------------------------------
void VActorPhysicsController::clearObject( void )
{
    // Valid Object?
    if ( !mObject )
    {
        // No.
        return;
    }

    // Clear Notify.
    mObject->getEventSignal().remove( this, &VActorPhysicsController::onActorEvent );

    // Clear Object.
    mObject = NULL;

    // Clear Table.
    mPhysicsStateTable.setObject( NULL );
    mPhysicsStateTable.clear();
}

//-----------------------------------------------------------------------------
//
// VActorPhysicsController::getControlState();
//
// Get the current Control State.
//
//-----------------------------------------------------------------------------
const U32 VActorPhysicsController::getControlState( void )
{
    return mControlState;
}

//-----------------------------------------------------------------------------
//
// VActorPhysicsController::clearControlState( pControlState );
//
// Clear the Control State of a particular mask.
//
//-----------------------------------------------------------------------------
void VActorPhysicsController::clearControlState( const U32 &pControlState )
{
    mControlState &= ( ~pControlState );
}

//-----------------------------------------------------------------------------
//
// VActorPhysicsController::setControlState( pControlState );
//
// Set the Control State.
//
//-----------------------------------------------------------------------------
void VActorPhysicsController::setControlState( const U32 &pControlState )
{
    mControlState = pControlState;
}

//-----------------------------------------------------------------------------
//
// VActorPhysicsController::isMoving();
//
// Is the Actor currently Moving?
//
//-----------------------------------------------------------------------------
const bool VActorPhysicsController::isMoving( void )
{
    return ( !mIsZero( getVelocity().lenSquared() ) );
}

//-----------------------------------------------------------------------------
//
// VActorPhysicsController::isMoving( pMoveState );
//
// Is the Actor currently moving with the desired state?
//
//-----------------------------------------------------------------------------
const bool VActorPhysicsController::isMoving( const U32 &pMoveState )
{
    // Moving?
    return ( ( getMoveState() & pMoveState ) && isMoving() );
}

//-----------------------------------------------------------------------------
//
// VActorPhysicsController::getMoveState();
//
// Get the current Move State.
//
//-----------------------------------------------------------------------------
const U32 VActorPhysicsController::getMoveState( void )
{
    // Return Move State.
    return mMoveState;
}

//-----------------------------------------------------------------------------
//
// VActorPhysicsController::clearMoveState( pMoveState );
//
// Clear the Move State of a particular mask.
//
//-----------------------------------------------------------------------------
void VActorPhysicsController::clearMoveState( const U32 &pMoveState )
{
    // Set Move State.
    mMoveState &= ( ~pMoveState );
}

//-----------------------------------------------------------------------------
//
// VActorPhysicsController::setMoveState( pMoveState );
//
// Set the Move State.
//
//-----------------------------------------------------------------------------
void VActorPhysicsController::setMoveState( const U32 &pMoveState )
{
    // Set Move State.
    mMoveState = pMoveState;
}

//-----------------------------------------------------------------------------
//
// VActorPhysicsController::isPathing();
//
// Is the Actor Pathing?
//
//-----------------------------------------------------------------------------
const bool VActorPhysicsController::isPathing( void )
{
    // Valid Object?
    if ( !isValidObject() )
    {
        // No.
        return false;
    }

    return ( mMountedPath != NULL );
}

//-----------------------------------------------------------------------------
//
// VActorPhysicsController::getPathObject();
//
// Get the Path Object the Actor is mounted to.
//
//-----------------------------------------------------------------------------
VPath *VActorPhysicsController::getPathObject( void )
{
    // Valid Object?
    if ( !isValidObject() )
    {
        // No.
        return NULL;
    }

    return mMountedPath;
}

//-----------------------------------------------------------------------------
//
// VActorPhysicsController::isOnGround();
//
// Is the Actor On the Ground?
//
//-----------------------------------------------------------------------------
const bool VActorPhysicsController::isOnGround( void )
{
    // Valid Objects?
    if ( !isValidObject() )
    {
        // No.
        return false;
    }

    // On Ground?
    return ( mOnGround && mGroundObject && !isInWater() );
}

//-----------------------------------------------------------------------------
//
// VActorPhysicsController::isInAir();
//
// Is the Actor in the Air?
//
//-----------------------------------------------------------------------------
const bool VActorPhysicsController::isInAir( void )
{
    // Valid Objects?
    if ( !isValidObject() )
    {
        // No.
        return false;
    }

    // In Air?
    return ( !isOnGround() && !isInWater() );
}

//-----------------------------------------------------------------------------
//
// VActorPhysicsController::isInWater();
//
// Is the Actor in the Water?
//
//-----------------------------------------------------------------------------
const bool VActorPhysicsController::isInWater( void )
{
    // Valid Objects?
    if ( !isValidObject() || !getWaterObject() )
    {
        // No.
        return false;
    }

    // Submerged?
    return ( ( mObject->getWaterCoverage() + POINT_EPSILON ) >= mObject->getDataBlock()->getSumbergeCoverage() );
}

//-----------------------------------------------------------------------------
//
// VActorPhysicsController::getWaterObject();
//
// Get the current Water Object the Actor is in.
//
//-----------------------------------------------------------------------------
WaterObject *VActorPhysicsController::getWaterObject( void )
{
    // Valid Object?
    if ( !isValidObject() )
    {
        // No.
        return NULL;
    }

    return mObject->getCurrentWaterObject();
}

//-----------------------------------------------------------------------------
//
// VActorPhysicsController::getTransform();
//
// Get the Actor's Transform.
//
//-----------------------------------------------------------------------------
MatrixF VActorPhysicsController::getTransform( void )
{
    // Valid Object?
    if ( !isValidObject() )
    {
        // No.
        return MatrixF::Identity;
    }

    // Return Transform.
    return mObject->getTransform();
}

//-----------------------------------------------------------------------------
//
// VActorPhysicsController::setTransform( pTransform );
//
// Set the Actor's Transform.
//
//-----------------------------------------------------------------------------
void VActorPhysicsController::setTransform( const MatrixF &pTransform )
{
    // Valid Object?
    if ( !isValidObject() )
    {
        // No.
        return;
    }

    // Apply Transform.
    mObject->setTransform( pTransform );
}

//-----------------------------------------------------------------------------
//
// VActorPhysicsController::getPosition();
//
// Get the Actor's Position.
//
//-----------------------------------------------------------------------------
Point3F VActorPhysicsController::getPosition( void )
{
    // Valid Object?
    if ( !isValidObject() )
    {
        // No.
        return Point3F::Zero;
    }

    // Return Position.
    return mObject->getPosition();
}

//-----------------------------------------------------------------------------
//
// VActorPhysicsController::setPosition( pPosition );
//
// Set the Actor's Position.
//
//-----------------------------------------------------------------------------
void VActorPhysicsController::setPosition( const Point3F &pPosition )
{
    // Valid Object?
    if ( !isValidObject() )
    {
        // No.
        return;
    }

    // Apply Position.
    mObject->setPosition( pPosition );
}

//-----------------------------------------------------------------------------
//
// VActorPhysicsController::applyGravity( pElapsedTime );
//
// Apply gravity for the elapsed period.
//
//-----------------------------------------------------------------------------
void VActorPhysicsController::applyGravity( const F32 &pElapsedTime )
{
    // Get Velocity.
    VectorF velocity = getVelocity();
    // Add Tick Gravity.
    velocity += getGravity() * pElapsedTime;
    // Apply.
    setVelocity( velocity );
}

//-----------------------------------------------------------------------------
//
// VActorPhysicsController::getVelocity();
//
// Get the Actor's Velocity.
//
//-----------------------------------------------------------------------------
VectorF VActorPhysicsController::getVelocity( void )
{
    // Valid Object?
    if ( !isValidObject() )
    {
        // No.
        return VectorF::Zero;
    }

    // Return Velocity.
    return mVelocity;
}

//-----------------------------------------------------------------------------
//
// VActorPhysicsController::setVelocity( pVelocity );
//
// Set the Actor's Velocity.
//
//-----------------------------------------------------------------------------
void VActorPhysicsController::setVelocity( const VectorF &pVelocity )
{
    // Set Velocity.
    mVelocity = pVelocity;
}




//-----------------------------------------------------------------------------
//
// Physics Methods
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//
// VActorPhysicsController::update( pDelta, pMove );
//
// ...
//
//-----------------------------------------------------------------------------
void VActorPhysicsController::update( const F32 &pDelta, const Move *pMove )
{
    // Valid Objects?
    if ( !isValidObject() )
    {
        // No, Quit Now.
        return;
    }

    // Pre-tick Update.
    preTickUpdate( pDelta );

    // Integrate Tick Update.
    integrateTickUpdate( pDelta, pMove );

    // Post-tick Update.
    postTickUpdate( pDelta );
}

//-----------------------------------------------------------------------------
//
// VActorPhysicsController::preTickUpdate( pDelta );
//
// ...
//
//-----------------------------------------------------------------------------
void VActorPhysicsController::preTickUpdate( const F32 &pDelta )
{
    // Pop Delta.
    mInterpController.popDelta();

    switch( mControlState )
    {
    case k_PathControlState :
        {
            AssertFatal( isPathing(), "VActorPhysicsController::preTickUpdate() - Invalid Path State." );

            // Fetch Mount Velocity.
            const VectorF &mountVelocity = mMountedPath->getMountVelocity( mObject->getMountNode() );

            // Use X & Y Velocity.
            VectorF velocity = getVelocity();
            velocity.x = mountVelocity.x;
            velocity.y = mountVelocity.y;

            // Apply Updates.
            setVelocity( velocity );

        } break;
    }

    // Update Move State.
    updateMoveState();
}

//-----------------------------------------------------------------------------
//
// VActorPhysicsController::integrateTickUpdate( pDelta, pMove );
//
// ...
//
//-----------------------------------------------------------------------------
void VActorPhysicsController::integrateTickUpdate( const F32 &pDelta, const Move *pMove )
{
    // Update Collision Set.
    updateWorkingCollisionSet();
    // Ground Ground Status.
    updateGroundStatus();

    // Execute Physics Table.
    VActorPhysicsState *physState = dynamic_cast<VActorPhysicsState*>( mPhysicsStateTable.execute() );
    // Assert.
    AssertFatal( physState, "VActorPhysicsController::update() - Invalid Physics State in the Table." );

    // Process the State.
    physState->processTick( mObject, pDelta, pMove );

    // Process Collisions.
    processCollisions();
}

//-----------------------------------------------------------------------------
//
// VActorPhysicsController::postTickUpdate( pDelta );
//
// ...
//
//-----------------------------------------------------------------------------
void VActorPhysicsController::postTickUpdate( const F32 &pDelta )
{
    switch( mControlState )
    {
    case k_PathControlState :
        {
            AssertFatal( isPathing(), "VActorPhysicsController::postTickUpdate() - Invalid Path State." );

            // Fetch Mount Transform.
            MatrixF transform;
            mMountedPath->getMountTransform( mObject->getMountNode(), getTransform(), &transform );
            // Fetch Mount Position.
            const Point3F &mountPosition = transform.getPosition();

            // Update X & Y Position.
            Point3F position = getPosition();
            position.x = mountPosition.x;
            position.y = mountPosition.y;

            // In Water?
            bool underWater = false;
            if ( isInWater() )
            {
                // Fetch Body of Water.
                WaterObject *waterBody = getWaterObject();

                // Fetch Surface Position.
                const F32 &waterSurfacePosition = waterBody->getSurfaceHeight( Point2F( position.x, position.y ) );
                // Fetch Submersion Position.
                const F32 sumbersionPosition = waterSurfacePosition - ( mObject->getWorldBox().len_z() * mObject->getDataBlock()->getSumbergeCoverage() );

                // Choose a Z Value.
                // Note: This is done so that the Actor will either path under the
                //       water, or it will swim along the water's surface.
                position.z = getMin( mountPosition.z, sumbersionPosition );

                // Under Water?
                underWater = ( position.z < sumbersionPosition );
            }

            // Under Water?
            if ( !underWater )
            {
                // Fetch Y Column.
                VectorF forwardVector;
                transform.getColumn( 1, &forwardVector );

                // Determine Angle.
                const F32 &angle = -mAtan2( -forwardVector.x, forwardVector.y );

                // Reset Transform.
                transform.set( EulerF( 0.f, 0.f, angle ) );

                // In the air?
                if ( !isOnGround() )
                {
                    // Apply z-axis force.
                    position.z += ( getVelocity().z * pDelta );
                }
            }

            // Update Transform.
            transform.setPosition( position );

            // Apply Update.
            setTransform( transform );

        } break;

    default :
        {
            // Fetch Transform.
            MatrixF transform = getTransform();

            // Determine the Post-Tick Position.
            Point3F postTickPosition = getPosition() + ( getVelocity() * pDelta );
            // Set the Post Tick Position.
            transform.setPosition( postTickPosition );

            // Apply the Transform.
            setTransform( transform );

        } break;
    }

    // Push Delta.
    mInterpController.pushDelta( getTransform() );
}




//-----------------------------------------------------------------------------
//
// VActorPhysicsController::interpolateTick( pDelta );
//
// ...
//
//-----------------------------------------------------------------------------
void VActorPhysicsController::interpolateTick( const F32 &pDelta )
{
    // Fetch Interpolated Transform.
    const MatrixF transform = mInterpController.getTransform( pDelta );
    // Apply Render Transform.
    mObject->setRenderTransform( transform );
}




//-----------------------------------------------------------------------------
//
// VActorPhysicsController::updateWorkingCollisionSet();
//
// ...
//
//-----------------------------------------------------------------------------
void VActorPhysicsController::updateWorkingCollisionSet()
{
    // Contstruct Bounding Box.
    const Box3F boundingBox = mConvex.getBoundingBox( getTransform(), mObject->getScale() );

    // Determine Sweep Vector.
    const VectorF sweepVector = ( getVelocity() * TickSec );

    // Construct Swept Box.
    Box3F sweptBox = boundingBox;
    sweptBox.minExtents.setMin( boundingBox.minExtents + sweepVector );
    sweptBox.maxExtents.setMax( boundingBox.maxExtents + sweepVector );

    // Update Collision List.
    mObject->disableCollision();
        mConvex.updateWorkingList( sweptBox, sCollisionMask );
    mObject->enableCollision();
}




//-----------------------------------------------------------------------------
//
// VActorPhysicsController::updateMoveState();
//
// ...
//
//-----------------------------------------------------------------------------
void VActorPhysicsController::updateMoveState( void )
{
    switch( mControlState )
    {
    case k_PathControlState :
        {
            AssertFatal( isPathing(), "VActorPhysicsController::updateMoveState() - Invalid Path State." );

            // Update Move State.
            VPathObject *pathObject = mMountedPath->getPathObject( mObject );
            if ( !pathObject->isActive() )
            {
                // Idle.
                setMoveState( k_NullMove );
            }
            else
            {
                // Set Movement Direction.
                setMoveState( ( pathObject->isForward() ) ? k_ForwardMove : k_BackwardMove );
            }

        } break;

    default :
        {
            // Set Idle.
            setMoveState( k_NullMove );

        } break;
    }
}




//-----------------------------------------------------------------------------
//
// VActorPhysicsController::clearGroundStatus();
//
// ...
//
//-----------------------------------------------------------------------------
void VActorPhysicsController::clearGroundStatus( void )
{
    // Clear Grounding.
    mOnGround     = false;
    mGroundObject = NULL;
    mGroundNormal.zero();
}

//-----------------------------------------------------------------------------
//
// VActorPhysicsController::updateGroundStatus();
//
// ...
//
//-----------------------------------------------------------------------------
void VActorPhysicsController::updateGroundStatus( void )
{
    // Submerged?
    if ( isInWater() )
    {
        // Clear Ground Status.
        clearGroundStatus();
        return;
    }

    // Check for Grounding.
    SceneObject *groundObject;
    Point3F groundPoint;
    VectorF groundNormal;
    if ( !findGroundContact( groundObject, groundPoint, groundNormal ) )
    {
        // Clear Ground Status.
        clearGroundStatus();
        return;
    }

    // Tidy up the Contact Position.
    // Note: This basically "clamps" the Actor to the surface of the ground
    //       object.
    const Point3F objPosition = getPosition();
    setPosition( objPosition - Point3F( 0.f, 0.f, ( objPosition.z - groundPoint.z ) ) );

    // Clear Z-Axis Velocity.
    mVelocity.z = 0.f;

    // Store Details.
    mOnGround     = true;
    mGroundObject = groundObject;
    mGroundNormal = groundNormal;
}

//-----------------------------------------------------------------------------
//
// VActorPhysicsController::findGroundContact( pContactObject, pContactPoint, pContactNormal );
//
// ...
//
//-----------------------------------------------------------------------------
bool VActorPhysicsController::findGroundContact( SceneObject *&pContactObject, Point3F &pContactPoint, VectorF &pContactNormal )
{
    // Setup Collision List.
    static CollisionList sCollisionList;
    sCollisionList.clear();

    static Polyhedron       sBoxPolyhedron;
    static ExtrudedPolyList sExtrudedPolyList;

    // Fetch Max Step Height.
    const F32 stepHeight = mObject->getDataBlock()->getMaxStepHeight();

    // Determine Positions.
    const Point3F preTickPosition  = getPosition() + Point3F( 0.f, 0.f, stepHeight );
    const VectorF preTickVelocity  = getVelocity() + mGravity - VectorF( 0.f, 0.f, stepHeight / TickSec );
    const Point3F postTickPosition = preTickPosition + ( preTickVelocity * TickSec );
    const VectorF postTickVector   = postTickPosition - preTickPosition;

    // Construct Scaled Box.
    Box3F scaledBox = mObject->getObjBox();
    scaledBox.minExtents.convolve( mObject->getScale() );
    scaledBox.maxExtents.convolve( mObject->getScale() );

    // Setup Polyherdron.
    MatrixF collisionMatrix( true );
    collisionMatrix.setPosition( preTickPosition );
    sBoxPolyhedron.buildBox( collisionMatrix, scaledBox );

    // Setup Extruded Poly List.
    sExtrudedPolyList.extrude( sBoxPolyhedron, postTickVector );
    sExtrudedPolyList.setVelocity( preTickVelocity );
    sExtrudedPolyList.setCollisionList( &sCollisionList );

    // Construct World Convex Box & Adjust for Sweep.
    Box3F convexBox = scaledBox;
    getTransform().mul( convexBox );
    convexBox.minExtents += postTickVector;
    convexBox.maxExtents += postTickVector;

    // Build List of Contacts.
    CollisionWorkingList &rList = mConvex.getWorkingList();
    for ( CollisionWorkingList *pList = rList.wLink.mNext; pList != &rList; pList = pList->wLink.mNext )
    {
        Convex *convexShape = pList->mConvex;

        // Ground Object?
        if ( !( convexShape->getObject()->getTypeMask() & sGroundCollisionMask ) )
        {
            // No, Continue.
            continue;
        }

        // Overlap?
        const Box3F &collisionConvexBox = convexShape->getBoundingBox();
        if ( convexBox.isOverlapped( collisionConvexBox ) )
        {
            // Build Contact Information.
            convexShape->getPolyList( &sExtrudedPolyList );
        }
    }

    // Valid Collision?
    if ( sCollisionList.getCount() == 0 || sCollisionList.getTime() < 0.f || sCollisionList.getTime() > 1.f )
    {
        // No, Quit Now.
        return false;
    }

    // Use First Collision.
    Collision *collision = &sCollisionList[0];

    // More Collisions?
    if ( sCollisionList.getCount() > 1 )
    {
        // Check for Better Contacts.
        for ( Collision *cp = ( collision + 1 ); cp != ( collision + sCollisionList.getCount() ); cp++ )
        {
            if ( cp->faceDot > collision->faceDot )
            {
                // Use this One.
                collision = cp;
            }
        }
    }

    // Set Properties.
    pContactObject = collision->object;
    //pContactPoint  = collision->point;
    pContactPoint  = ( preTickPosition + ( preTickVelocity * TickSec * sCollisionList.getTime() ) );
    pContactNormal = collision->normal;

    // Valid Contact.
    return true;
}




//-----------------------------------------------------------------------------
//
// VActorPhysicsController::processCollisions();
//
// ...
//
//-----------------------------------------------------------------------------
void VActorPhysicsController::processCollisions( void )
{
    // Find & Resolve Collisions.
    Collision *collision;
    if ( findCollision( collision ) )
    {
        // Solve the Collision.
        solveCollision( collision );
    }
}

//-----------------------------------------------------------------------------
//
// VActorPhysicsController::findCollision( pCollision );
//
// ...
//
//-----------------------------------------------------------------------------
bool VActorPhysicsController::findCollision( Collision *&pCollision )
{
    // Setup Collision List.
    static CollisionList sCollisionList;
    sCollisionList.clear();

    static Polyhedron       sBoxPolyhedron;
    static ExtrudedPolyList sExtrudedPolyList;

    // Determine Positions.
    const Point3F preTickPosition  = getPosition();
    const VectorF preTickVelocity  = getVelocity();
    const Point3F postTickPosition = preTickPosition + ( preTickVelocity * TickSec );
    const VectorF postTickVector   = postTickPosition - preTickPosition;

    // Construct Scaled Box.
    Box3F scaledBox = mObject->getObjBox();
    scaledBox.minExtents.convolve( mObject->getScale() );
    scaledBox.maxExtents.convolve( mObject->getScale() );

    // Setup Polyherdron.
    MatrixF collisionMatrix( true );
    collisionMatrix.setPosition( preTickPosition );
    sBoxPolyhedron.buildBox( collisionMatrix, scaledBox );

    // Setup Extruded Poly List.
    sExtrudedPolyList.extrude( sBoxPolyhedron, postTickVector );
    sExtrudedPolyList.setVelocity( preTickVelocity );
    sExtrudedPolyList.setCollisionList( &sCollisionList );

    // Construct World Convex Box & Adjust for Sweep.
    Box3F convexBox = scaledBox;
    getTransform().mul( convexBox );
    convexBox.minExtents += postTickVector;
    convexBox.maxExtents += postTickVector;

    // Determine the Collision Mask.
    const U32 collisionMask = ( isInWater() ) ? ( sGroundCollisionMask | sMoveCollisionMask ) : sMoveCollisionMask;

    // Build List of Contacts.
    CollisionWorkingList &rList = mConvex.getWorkingList();
    for ( CollisionWorkingList *pList = rList.wLink.mNext; pList != &rList; pList = pList->wLink.mNext )
    {
        Convex *convexShape = pList->mConvex;

        // Valid Collision Target?
        if ( !( convexShape->getObject()->getTypeMask() & collisionMask ) )
        {
            // No, Continue.
            continue;
        }

        // Overlap?
        const Box3F &collisionConvexBox = convexShape->getBoundingBox();
        if ( convexBox.isOverlapped( collisionConvexBox ) )
        {
            // Build Contact Information.
            convexShape->getPolyList( &sExtrudedPolyList );
        }
    }

    // Valid Collision?
    if ( sCollisionList.getCount() == 0 || sCollisionList.getTime() > 1.f )
    {
        // No, Quit Now.
        return false;
    }

    // Use First Collision.
    Collision *collision = &sCollisionList[0];

    // More Collisions?
    if ( sCollisionList.getCount() > 1 )
    {
        // Check for Better Contacts.
        for ( Collision *cp = ( collision + 1 ); cp != ( collision + sCollisionList.getCount() ); cp++ )
        {
            if ( cp->faceDot > collision->faceDot )
            {
                // Use this One.
                collision = cp;
            }
        }
    }

    // Store Reference.
    pCollision = collision;

    // Valid Collision.
    return true;
}

//-----------------------------------------------------------------------------
//
// VActorPhysicsController::solveCollision( pCollision );
//
// ...
//
//-----------------------------------------------------------------------------
void VActorPhysicsController::solveCollision( Collision *pCollision )
{
    // Fetch Velocity.
    VectorF velocity = getVelocity();
    // Resolve Collision.
    velocity -= ( pCollision->normal * mDot( getVelocity(), pCollision->normal ) );

    // Pathing?
    if ( isPathing() )
    {
        // Clear X & Y Velocity Adjustments.
        // Note: This means that any collisions made during pathing will not
        //       be solved, unless they only affect Z position. It is up to the
        //       user to construct Paths which avoid obsticles!
        velocity.x = velocity.y = 0.f;
    }

    // Set Velocity.
    setVelocity( velocity );
}




//-----------------------------------------------------------------------------
//
// Update Methods
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//
// VActorPhysicsController::onActorEvent( pEvent );
//
// ...
//
//-----------------------------------------------------------------------------
void VActorPhysicsController::onActorEvent( const VActor::eEventType &pEvent )
{
    switch( pEvent )
    {
    case VActor::k_MountEvent :
        {
            // Set Control State.
            setControlState( k_PathControlState );

            // Store Path.
            mMountedPath = dynamic_cast<VPath*>( mObject->getObjectMount() );

        } break;

    case VActor::k_UnmountEvent :
        {
            // Clear Control State.
            clearControlState( k_PathControlState );

            // Clear Path.
            mMountedPath = NULL;
            // Clear X & Y Velocity.
            setVelocity( VectorF( 0.f, 0.f, mVelocity.z ) );

        } break;
    }
}

//-----------------------------------------------------------------------------
//
// VActorPhysicsController::packUpdate( pConnection, pMask, pStream );
//
// ...
//
//-----------------------------------------------------------------------------
U32 VActorPhysicsController::packUpdate( NetConnection *pConnection, U32 pMask, BitStream *pStream )
{
    // Return Mask.
    U32 retMask = 0;

    // Valid Object?
    if ( !pStream->writeFlag( isValidObject() ) )
    {
        return retMask;
    }

    // Write Move?
    const bool writeMove = ( pMask & VActor::MoveMask ) && !isPathing();
    if ( pStream->writeFlag( writeMove ) )
    {
        // Write Position.
        const Point3F &position = getPosition();
        pStream->write( position.x );
        pStream->write( position.y );
        pStream->write( position.z );
    }

    return retMask;
}

//-----------------------------------------------------------------------------
//
// VActorPhysicsController::unpackUpdate( pConnection, pStream );
//
// ...
//
//-----------------------------------------------------------------------------
void VActorPhysicsController::unpackUpdate( NetConnection *pConnection, BitStream *pStream )
{
    // Valid Object?
    if ( !pStream->readFlag() )
    {
        return;
    }

    // Read Move?
    if ( pStream->readFlag() )
    {
        // Read Position.
        Point3F position;
        pStream->read( &position.x );
        pStream->read( &position.y );
        pStream->read( &position.z );

        // Apply.
        setPosition( position );
    }
}