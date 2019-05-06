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
#include "VHumanoidActorAnimationController.h"

//-----------------------------------------------------------------------------

VHumanoidActorAnimationController::VHumanoidActorAnimationController( void )
{
    // Void.
}

VHumanoidActorAnimationController::~VHumanoidActorAnimationController( void )
{
    // Void.
}

//-----------------------------------------------------------------------------

bool VHumanoidActorAnimationController::initArmAnimation( const U32 &pIndex, const F32 &pPosition, const F32 &pTimeScale )
{
    // Initialise Animation Ref.
    return initAnimation( mArmAnimation, pIndex, pPosition, pTimeScale );
}




//-----------------------------------------------------------------------------
//
// Animation Methods
//
//-----------------------------------------------------------------------------

void VHumanoidActorAnimationController::update( const F32 &pDelta )
{
    // Parent Call.
    VActorAnimationController::update( pDelta );

    // Update the Look Thread.
    if ( mArmAnimation.Thread )
    {
        // Set Position.
        getShapeInstance()->setPos( mArmAnimation.Thread, 0.5f );
    }
}