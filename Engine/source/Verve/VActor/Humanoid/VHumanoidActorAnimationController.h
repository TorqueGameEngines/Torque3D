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
#ifndef _VT_VHUMANOIDACTORANIMATIONCONTROLLER_H_
#define _VT_VHUMANOIDACTORANIMATIONCONTROLLER_H_

#ifndef _VT_VACTORANIMATIONCONTROLLER_H_
#include "../VActorAnimationController.h"
#endif

//-----------------------------------------------------------------------------

class VActor;
class VActorStateTable;

//-----------------------------------------------------------------------------

class VHumanoidActorAnimationController : public VActorAnimationController
{
public:

    /*
    struct sHeadAnimation
    {
        S32           HSequence;
        TSThread     *HThread;
        Range         HRange;

        S32           VSequence;
        TSThread     *VThread;
        Range         VRange;

        S32           FaceSequence;
        TSThread     *FaceThread;

        sHeadAnimation( void ) :
            HSequence( -1 ),
            HThread( NULL ),
            HRange( 0.f, 1.f ),
            VSequence( -1 ),
            VThread( NULL ),
            VRange( 0.f, 1.f )
        {
            // Void.
        }
    };
    */

protected:

    //sHeadAnimation      mHeadAnimation;

    sAnimationRef    mHeadHAnimation;
    sAnimationRef    mHeadVAnimation;
    sAnimationRef    mArmAnimation;

public:

    VHumanoidActorAnimationController( void );
    virtual ~VHumanoidActorAnimationController( void );

    // Initialisation Methods.

    bool            initArmAnimation( const U32 &pIndex, const F32 &pPosition, const F32 &pTimeScale );

    // Animation Methods.

    void            update( const F32 &pDelta );
};

#endif // _VT_VACTORANIMATIONCONTROLLER_H_