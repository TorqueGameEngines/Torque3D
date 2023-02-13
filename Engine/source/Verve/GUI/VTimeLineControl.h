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
#ifndef _VT_VTIMELINECONTROL_H_
#define _VT_VTIMELINECONTROL_H_

#ifndef _GUICONTROL_H_
#include "gui/core/guiControl.h"
#endif

#ifndef _VT_VCONTROLLER_H_
#include "Verve/Core/VController.h"
#endif

//-----------------------------------------------------------------------------

class VTimeLineControl : public GuiControl
{
    typedef GuiControl Parent;

public:

    struct sSelection
    {
        bool   Active;
        S32    StartTime;
        S32    EndTime;
    };

    bool            mIsController;
    VController    *mController;

    S32             mDurationOffset;

    sSelection      mSelection;
    
public:

    VTimeLineControl( void );

    static void     initPersistFields();

    // Mouse.

    virtual void    onMouseDown( const GuiEvent &pEvent );
    virtual void    onMouseUp( const GuiEvent &pEvent );
    virtual void    onMouseDragged( const GuiEvent &pEvent );

    virtual void    onRightMouseDown( const GuiEvent &pEvent );

    void            onMouseEvent( const char *pEventName, const GuiEvent &pEvent );

    // Rendering.

    void            onPreRender( void );
    void            onRender( Point2I offset, const RectI &updateRect );

    // Console Declaration.

    DECLARE_CONOBJECT( VTimeLineControl );

public:

    S32             toTime( const S32 &pPoint );
    S32             toPoint( const S32 &pTime );

    void            updateDuration( void );
};

//-----------------------------------------------------------------------------

#endif // _VT_VTIMELINECONTROL_H_