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
#include "Verve/GUI/VFadeControl.h"

#include "console/consoleTypes.h"
#include "gfx/gfxDrawUtil.h"
#include "math/mMathFn.h"

//-----------------------------------------------------------------------------
IMPLEMENT_CONOBJECT( VFadeControl );
//-----------------------------------------------------------------------------

VFadeControl::VFadeControl( void ) : 
        mActive( false ),
        mFadeType( k_TypeInvalid ),
        mElapsedTime( 0 ),
        mDuration( 1000 ),
        mLastTime( 0 )
{
    // Void.
}

//-----------------------------------------------------------------------------
//
// Render Methods.
//
//-----------------------------------------------------------------------------

void VFadeControl::onRender( Point2I pOffset, const RectI &pUpdateRect )
{
    Parent::onRender( pOffset, pUpdateRect );

    if ( mFadeType == k_TypeInvalid )
    {
        // Invalid Fade State.
        return;
    }

    // Fetch Time.
    const U32 time  = Platform::getRealMilliseconds();
    // Fetch Delta.
    const U32 delta = ( time - mLastTime );
    // Store Time.
    mLastTime       = time;

    if ( mActive )
    {
        // Update Elapsed Time.
        mElapsedTime += delta;
    }

    F32 alpha = 1.f - mClampF( F32( mElapsedTime ) / F32( mDuration ), 0.f, 1.f );

    if ( mFadeType == k_TypeOut )
    {
        // Flip.
        alpha = 1.f - alpha;
    }

    if ( alpha > 0.f )
    {
        // Render.
        GFX->getDrawUtil()->drawRectFill( pOffset, pOffset + getExtent(), ColorI( 0, 0, 0, alpha * 255 ) );
    }

    if ( mElapsedTime >= mDuration )
    {
        // Stop.
        mActive = false;
    }
}

//-----------------------------------------------------------------------------
//
// Control Methods.
//
//-----------------------------------------------------------------------------

void VFadeControl::start( eFadeType pType, S32 pDuration )
{
    mActive      = true;

    mFadeType    = pType;

    mElapsedTime = 0;
    mDuration    = pDuration;

    mLastTime    = Platform::getRealMilliseconds();
}

void VFadeControl::pause( void )
{
    mActive = false;
}
