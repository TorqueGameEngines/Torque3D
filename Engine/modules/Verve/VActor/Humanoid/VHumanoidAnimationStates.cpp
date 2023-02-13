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
#include "VHumanoidAnimationStates.h"
#include "VHumanoidActor.h"

#include "../VActorAnimationController.h"
#include "../VActorPhysicsController.h"

//-----------------------------------------------------------------------------
//
// Implement Animation States.
//
//-----------------------------------------------------------------------------

ImplementActorAnimationState( HumanoidIdle,         VHumanoidActorData::k_IdleAnimation );

ImplementActorAnimationState( HumanoidWalkForward,  VHumanoidActorData::k_WalkForwardAnimation );
ImplementActorAnimationState( HumanoidWalkBackward, VHumanoidActorData::k_WalkBackwardAnimation );

ImplementActorAnimationState( HumanoidRunForward,   VHumanoidActorData::k_RunForwardAnimation );
ImplementActorAnimationState( HumanoidRunBackward,  VHumanoidActorData::k_RunBackwardAnimation );

ImplementActorAnimationState( HumanoidSwimIdle,     VHumanoidActorData::k_SwimIdleAnimation );
ImplementActorAnimationState( HumanoidSwimForward,  VHumanoidActorData::k_SwimForwardAnimation );
ImplementActorAnimationState( HumanoidSwimBackward, VHumanoidActorData::k_SwimBackwardAnimation );




//-----------------------------------------------------------------------------
//
// Execute Animation States.
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//
// OnGround Animation States
//
//-----------------------------------------------------------------------------

ExecuteActorAnimationState( HumanoidIdle )
{
    // Always Enter.
    return true;
}

ExecuteActorAnimationState( HumanoidWalkForward )
{
    // Fetch Controller.
    VActorPhysicsController *physicsController = pObject->getPhysicsController();

    // On the Ground?
    if ( physicsController->getPhysicsState() != VHumanoidActorData::k_OnGroundPhysics )
    {
        // Can't Run Forward.
        return false;
    }

    // Fetch Velocity.
    const VectorF &velocity = physicsController->getVelocity();
    // Determine Move Speed.
    const F32 moveSpeed = mSqrt( velocity.x * velocity.x + velocity.y * velocity.y );

    // Moving Forward & Slow Enough?
    return ( ( physicsController->getMoveState() & k_ForwardMove ) &&
             ( moveSpeed < pObject->getDataBlock()->getRunSpeed() ) );
}

ExecuteActorAnimationState( HumanoidWalkBackward )
{
    // Fetch Controller.
    VActorPhysicsController *physicsController = pObject->getPhysicsController();

    // On the Ground?
    if ( physicsController->getPhysicsState() != VHumanoidActorData::k_OnGroundPhysics )
    {
        // Can't Run Backward.
        return false;
    }

    // Fetch Velocity.
    const VectorF &velocity = physicsController->getVelocity();
    // Determine Move Speed.
    const F32 moveSpeed = mSqrt( velocity.x * velocity.x + velocity.y * velocity.y );

    // Moving Backward?
    return ( ( physicsController->getMoveState() & k_BackwardMove ) &&
             ( moveSpeed < pObject->getDataBlock()->getRunSpeed() ) );
}

ExecuteActorAnimationState( HumanoidRunForward )
{
    // Fetch Controller.
    VActorPhysicsController *physicsController = pObject->getPhysicsController();

    // On the Ground?
    if ( physicsController->getPhysicsState() != VHumanoidActorData::k_OnGroundPhysics )
    {
        // Can't Run Forward.
        return false;
    }

    // Fetch Velocity.
    const VectorF &velocity = physicsController->getVelocity();
    // Determine Move Speed.
    const F32 moveSpeed = mSqrt( velocity.x * velocity.x + velocity.y * velocity.y );

    // Moving Forward?
    return ( ( physicsController->getMoveState() & k_ForwardMove ) &&
             ( moveSpeed >= pObject->getDataBlock()->getRunSpeed() ) );
}

ExecuteActorAnimationState( HumanoidRunBackward )
{
    // Fetch Controller.
    VActorPhysicsController *physicsController = pObject->getPhysicsController();

    // On the Ground?
    if ( physicsController->getPhysicsState() != VHumanoidActorData::k_OnGroundPhysics )
    {
        // Can't Run Backward.
        return false;
    }

    // Fetch Velocity.
    const VectorF &velocity = physicsController->getVelocity();
    // Determine Move Speed.
    const F32 moveSpeed = mSqrt( velocity.x * velocity.x + velocity.y * velocity.y );

    // Moving Backward?
    return ( ( physicsController->getMoveState() & k_BackwardMove ) &&
             ( moveSpeed >= pObject->getDataBlock()->getRunSpeed() ) );
}




//-----------------------------------------------------------------------------
//
// InWater Animation States
//
//-----------------------------------------------------------------------------

ExecuteActorAnimationState( HumanoidSwimIdle )
{
    // Fetch Controller.
    VActorPhysicsController *physicsController = pObject->getPhysicsController();

    // In the Water?
    if ( physicsController->getPhysicsState() != VHumanoidActorData::k_InWaterPhysics )
    {
        // Can't Swim.
        return false;
    }

    // Idle?
    return ( physicsController->getMoveState() & k_NullMove );
}

ExecuteActorAnimationState( HumanoidSwimForward )
{
    // Fetch Controller.
    VActorPhysicsController *physicsController = pObject->getPhysicsController();

    // In the Water?
    if ( physicsController->getPhysicsState() != VHumanoidActorData::k_InWaterPhysics )
    {
        // Can't Swim.
        return false;
    }

    // Moving Around?
    return ( physicsController->getMoveState() & ( k_ForwardMove |
                                                   k_UpMove |
                                                   k_DownMove ) );
}

ExecuteActorAnimationState( HumanoidSwimBackward )
{
    // Fetch Controller.
    VActorPhysicsController *physicsController = pObject->getPhysicsController();

    // In the Water?
    if ( physicsController->getPhysicsState() != VHumanoidActorData::k_InWaterPhysics )
    {
        // Can't Swim.
        return false;
    }

    // Moving Backward?
    return ( physicsController->getMoveState() & k_BackwardMove );
}