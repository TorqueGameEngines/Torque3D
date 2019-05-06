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
#ifndef _VT_VHUMANOIDACTOR_H_
#define _VT_VHUMANOIDACTOR_H_

#ifndef _VT_VACTOR_H_
#include "../VActor.h"
#endif

#ifndef _VT_VHUMANOIDACTORDATA_H_
#include "VHumanoidActorData.h"
#endif

#ifndef _VT_VHUMANOIDACTORANIMATIONCONTROLLER_H_
#include "VHumanoidActorAnimationController.h"
#endif

#ifndef _VT_VHUMANOIDACTORPHYSICSCONTROLLER_H_
#include "VHumanoidActorPhysicsController.h"
#endif

//-----------------------------------------------------------------------------

class VHumanoidActor : public VActor
{
    typedef VActor Parent;

protected:

    VHumanoidActorAnimationController   mAnimationController;
    VHumanoidActorPhysicsController     mPhysicsController;

public:

    VHumanoidActor( void );
    ~VHumanoidActor( void );

    // Initialisation Methods.

    bool            onNewDataBlock( GameBaseData *pDataBlock, bool pReload );

    // Update Methods.

    void            processTick( const Move *pMove );
    void            interpolateTick( F32 pDelta );
    void            advanceTime( F32 pDelta );

    U32             packUpdate( NetConnection *pConnection, U32 pMask, BitStream *pStream );
    void            unpackUpdate( NetConnection *pConnection, BitStream *pStream );

    // Animation Methods.

    bool                         initAnimationController( void );
    VActorAnimationController   *getAnimationController( void );

    // Physics Methods.

    bool                         initPhysicsController( void );
    VActorPhysicsController     *getPhysicsController( void );

    DECLARE_CONOBJECT( VHumanoidActor );
};

#endif // _VT_VHUMANOIDACTOR_H_