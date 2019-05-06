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
#include "VHumanoidPhysicsStates.h"
#include "VHumanoidActor.h"

#include "../VActorPhysicsController.h"

//-----------------------------------------------------------------------------
//
// Implement Physics States.
//
//-----------------------------------------------------------------------------

ImplementActorPhysicsState( HumanoidOnGround, VHumanoidActorData::k_OnGroundPhysics );
ImplementActorPhysicsState( HumanoidInAir,    VHumanoidActorData::k_InAirPhysics );
ImplementActorPhysicsState( HumanoidInWater,  VHumanoidActorData::k_InWaterPhysics );




//-----------------------------------------------------------------------------
//
// Execute Animation States.
//
//-----------------------------------------------------------------------------

ExecuteActorPhysicsState( HumanoidOnGround )
{
    // Fetch Controller.
    VActorPhysicsController *physicsController = pObject->getPhysicsController();

    // On the Ground?
    if ( !physicsController->isOnGround() )
    {
        // No.
        return false;
    }

    // On Ground.
    return true;
}

ProcessActorPhysicsState( HumanoidOnGround )
{
    // Void.
}

//-----------------------------------------------------------------------------

ExecuteActorPhysicsState( HumanoidInAir )
{
    // Fetch Controller.
    VActorPhysicsController *physicsController = pObject->getPhysicsController();

    // In the Air?
    if ( !physicsController->isInAir() )
    {
        // No.
        return false;
    }

    // In Air.
    return true;
}

ProcessActorPhysicsState( HumanoidInAir )
{
    // Apply Gravity for the Tick.
    pObject->getPhysicsController()->applyGravity( pElapsedTime );
}

//-----------------------------------------------------------------------------

ExecuteActorPhysicsState( HumanoidInWater )
{
    // Fetch Controller.
    VActorPhysicsController *physicsController = pObject->getPhysicsController();

    // Sumberged?
    if ( !physicsController->isInWater() )
    {
        // No.
        return false;
    }

    // Swimming
    return true;
}

ProcessActorPhysicsState( HumanoidInWater )
{
    // Void.
}