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
#ifndef _VT_VEDITORBUTTON_H_
#define _VT_VEDITORBUTTON_H_

#ifndef _GUIBITMAPBUTTON_H_
#include "gui/buttons/guiBitmapButtonCtrl.h"
#endif

class VEditorButton : public GuiBitmapButtonTextCtrl
{
    typedef GuiBitmapButtonTextCtrl Parent;

public:

    bool            mIsDraggable;

public:

    VEditorButton();

    static void     initPersistFields();

    void            onMouseDown( const GuiEvent &pEvent );
    void            onMouseUp( const GuiEvent &pEvent );
    void            onMouseDragged( const GuiEvent &pEvent );

    void            onRightMouseDown( const GuiEvent &pEvent );
    void            onRightMouseUp( const GuiEvent &pEvent );

    void            onMouseEnter( const GuiEvent &pEvent );
    void            onMouseLeave( const GuiEvent &pEvent );
    void            onMouseEvent( const char *pEventName, const GuiEvent &pEvent );

    void            onRender( Point2I offset, const RectI &updateRect );

public:

    DECLARE_CONOBJECT( VEditorButton );
};

#endif //_VT_VEDITORBUTTON_H_