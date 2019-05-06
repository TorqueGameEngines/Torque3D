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
#ifndef _VT_VFADECONTROL_H_
#define _VT_VFADECONTROL_H_

#ifndef _GUICONTROL_H_
#include "gui/core/guiControl.h"
#endif

//-----------------------------------------------------------------------------

class VFadeControl : public GuiControl
{
    typedef GuiControl Parent;

public:

    enum eFadeType
    {
        k_TypeIn,
        k_TypeOut,

        k_TypeInvalid,
    };

    bool            mActive;
    eFadeType       mFadeType;

    S32             mElapsedTime;
    S32             mDuration;
    S32             mLastTime;
    
public:

    VFadeControl( void );

    // Render Methods.

    virtual void    onRender( Point2I pOffset, const RectI &pUpdateRect );

    // Console Declaration.

    DECLARE_CONOBJECT( VFadeControl );

public:

    void            start( eFadeType pType, S32 pDuration );
    void            pause( void );
};

//-----------------------------------------------------------------------------

#endif // _VT_VFADECONTROL_H_