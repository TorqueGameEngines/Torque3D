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
#include "VHumanoidActorData.h"
#include "VHumanoidAnimationStates.h"
#include "VHumanoidPhysicsStates.h"

//-----------------------------------------------------------------------------
// Animation Table.
//-----------------------------------------------------------------------------

static VActorData::sAnimationSequence animSequenceLookup[] =
    {
        // State Based Animations.
        { VHumanoidActorData::k_IdleAnimation,           "root",     0.0f, ActorAnimationStateInstance( HumanoidIdle )         },

        { VHumanoidActorData::k_WalkForwardAnimation,    "walk",     0.1f, ActorAnimationStateInstance( HumanoidWalkForward )  },
        { VHumanoidActorData::k_WalkBackwardAnimation,   "walkback", 0.1f, ActorAnimationStateInstance( HumanoidWalkBackward ) },

        { VHumanoidActorData::k_RunForwardAnimation,     "run",      0.1f, ActorAnimationStateInstance( HumanoidRunForward )   },
        { VHumanoidActorData::k_RunBackwardAnimation,    "runback",  0.1f, ActorAnimationStateInstance( HumanoidRunBackward )  },

        { VHumanoidActorData::k_SwimIdleAnimation,       "swimroot", 1.0f, ActorAnimationStateInstance( HumanoidSwimIdle )     },
        { VHumanoidActorData::k_SwimForwardAnimation,    "swim",     1.0f, ActorAnimationStateInstance( HumanoidSwimForward )  },
        { VHumanoidActorData::k_SwimBackwardAnimation,   "swimback", 1.0f, ActorAnimationStateInstance( HumanoidSwimBackward ) },

        // Support Animations.
        { VHumanoidActorData::k_HeadHorizontalAnimation, "headside" },
        { VHumanoidActorData::k_HeadVerticalAnimation,   "head"     },

        { VHumanoidActorData::k_ArmsUpDownAnimation,     "look"     },
    };

//-----------------------------------------------------------------------------
// Physics Table.
//-----------------------------------------------------------------------------

static VActorData::sPhysicsState physStateLookup[] =
    {
        { VHumanoidActorData::k_OnGroundPhysics, 0.f, ActorPhysicsStateInstance( HumanoidOnGround ) },
        { VHumanoidActorData::k_InAirPhysics,    0.f, ActorPhysicsStateInstance( HumanoidInAir )    },
        { VHumanoidActorData::k_InWaterPhysics,  0.f, ActorPhysicsStateInstance( HumanoidInWater )  },
    };

//-----------------------------------------------------------------------------
IMPLEMENT_CO_DATABLOCK_V1( VHumanoidActorData );
//-----------------------------------------------------------------------------

VHumanoidActorData::VHumanoidActorData( void )
{
    // Void.
};

bool VHumanoidActorData::preload( bool pServer, String &pErrorStr )
{
    if ( !Parent::preload( pServer, pErrorStr ) )
    {
        return false;
    }

    // Initialise Animation List.
    if ( !initAnimationSequenceList( sizeof( animSequenceLookup ) /  sizeof( VActorData::sAnimationSequence ), &animSequenceLookup[0] ) )
    {
        Con::errorf( "VHumanoidActorData::preload() - Failed to Initialise Actor Animations." );
        return false;
    }

    // Initialise Physics State List.
    if ( !initPhysicsStateList( sizeof( physStateLookup ) /  sizeof( VActorData::sPhysicsState ), &physStateLookup[0] ) )
    {
        Con::errorf( "VHumanoidActorData::preload() - Failed to Initialise Actor Physics States." );
        return false;
    }

    // Valid Load.
    return true;
}