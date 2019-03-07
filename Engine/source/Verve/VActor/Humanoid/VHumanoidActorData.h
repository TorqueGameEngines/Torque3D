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
#ifndef _VT_VHUMANOIDACTORDATA_H_
#define _VT_VHUMANOIDACTORDATA_H_

#ifndef _VT_VACTORDATA_H_
#include "../VActorData.h"
#endif

//-----------------------------------------------------------------------------

struct VHumanoidActorData : public VActorData
{
private:

    typedef VActorData Parent;
    friend class VHumanoidActor;

public:

    enum eAnimationList
    {
        k_IdleAnimation           = Parent::k_NextAnimation +  0,

        k_WalkForwardAnimation    = Parent::k_NextAnimation +  1,
        k_WalkBackwardAnimation   = Parent::k_NextAnimation +  2,

        k_RunForwardAnimation     = Parent::k_NextAnimation +  3,
        k_RunBackwardAnimation    = Parent::k_NextAnimation +  4,

        k_SwimIdleAnimation       = Parent::k_NextAnimation +  5,
        k_SwimForwardAnimation    = Parent::k_NextAnimation +  6,
        k_SwimBackwardAnimation   = Parent::k_NextAnimation +  7,

        k_HeadHorizontalAnimation = Parent::k_NextAnimation +  8,
        k_HeadVerticalAnimation   = Parent::k_NextAnimation +  9,

        k_ArmsUpDownAnimation     = Parent::k_NextAnimation + 10,

        k_NextAnimation           = Parent::k_NextAnimation + 11,
    };

    enum ePhysicsStateList
    {
        k_OnGroundPhysics         = Parent::k_NextPhysicsState + 0,
        k_InAirPhysics            = Parent::k_NextPhysicsState + 1,
        k_InWaterPhysics          = Parent::k_NextPhysicsState + 2,

        k_NextPhysicsState        = Parent::k_NextPhysicsState + 3,
    };

public:

    VHumanoidActorData( void );

    virtual bool    preload( bool pServer, String &pErrorStr );

    DECLARE_CONOBJECT( VHumanoidActorData );
};

#endif // _VT_VHUMANOIDACTORDATA_H_