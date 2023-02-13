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
#include "Verve/GUI/VEditorButton.h"
#include "console/consoleTypes.h"
#include "gfx/gfxDrawUtil.h"
#include "gui/core/guiCanvas.h"
#include "gui/core/guiDefaultControlRender.h"

//-----------------------------------------------------------------------------
IMPLEMENT_CONOBJECT( VEditorButton );
//-----------------------------------------------------------------------------

VEditorButton::VEditorButton( void ) :
        mIsDraggable( false )
{
    // Void.
}

void VEditorButton::initPersistFields()
{
   docsURL;
    Parent::initPersistFields();

    addField( "IsDraggable", TypeBool, Offset( mIsDraggable, VEditorButton ) );
}

//-----------------------------------------------------------------------------

void VEditorButton::onMouseDown( const GuiEvent &pEvent )
{
    if ( !mActive )
    {
        return;
    }

    Parent::onMouseDown( pEvent );

    onMouseEvent( "onMouseDown", pEvent );
}

void VEditorButton::onMouseUp( const GuiEvent &pEvent )
{
    if ( !mActive )
    {
        return;
    }

    Parent::onMouseUp( pEvent );

    if ( mIsDraggable && isMouseLocked() )
    {
        // Unlock.
        mouseUnlock();
    }

    onMouseEvent( "onMouseUp", pEvent );
}

void VEditorButton::onMouseDragged( const GuiEvent &pEvent )
{
    if ( !mActive || !mIsDraggable )
    {
        return;
    }

    Parent::onMouseDragged( pEvent );

    if ( !isMouseLocked() )
    {
        GuiCanvas *canvas = getRoot();
        if ( canvas->getMouseLockedControl() )
        {
            GuiEvent event;
            canvas->getMouseLockedControl()->onMouseLeave( event );
            canvas->mouseUnlock( canvas->getMouseLockedControl() );
        }

        // Lock.
        mouseLock();
    }

    onMouseEvent( "onMouseDragged", pEvent );
}

void VEditorButton::onRightMouseDown( const GuiEvent &pEvent )
{
    if ( !mActive )
    {
        return;
    }

    Parent::onRightMouseDown( pEvent );

    onMouseEvent( "onRightMouseDown", pEvent );
}

void VEditorButton::onRightMouseUp( const GuiEvent &pEvent )
{
    if ( !mActive )
    {
        return;
    }

    Parent::onRightMouseUp( pEvent );

    onMouseEvent( "onRightMouseUp", pEvent );
}

void VEditorButton::onMouseEnter( const GuiEvent &pEvent )
{
    if ( !mActive )
    {
        return;
    }

    Parent::onMouseEnter( pEvent );

    onMouseEvent( "onMouseEnter", pEvent );
}

void VEditorButton::onMouseLeave( const GuiEvent &pEvent )
{
    if ( !mActive )
    {
        return;
    }

    Parent::onMouseLeave( pEvent );

    onMouseEvent( "onMouseLeave", pEvent );
}

void VEditorButton::onMouseEvent( const char *pEventName, const GuiEvent &pEvent )
{
    // Argument Buffers.
    char argBuffer[3][32];

    // Format Event-Position Buffer.
    dSprintf( argBuffer[0], 32, "%d %d", pEvent.mousePoint.x, pEvent.mousePoint.y );

    // Format Event-Modifier Buffer.
    dSprintf( argBuffer[1], 32, "%d", pEvent.modifier );

    // Format Mouse-Click Count Buffer.
    dSprintf( argBuffer[2], 32, "%d", pEvent.mouseClickCount );

    // Call Scripts.
    Con::executef( this, pEventName, argBuffer[0], argBuffer[1], argBuffer[2] );
}

//-----------------------------------------------------------------------------

void VEditorButton::onRender( Point2I offset, const RectI& updateRect )
{
    // Fetch Texture.
    GFXTexHandle texture = getTextureForCurrentState();

    // Valid?
    if ( texture )
    {
        GFX->getDrawUtil()->clearBitmapModulation();
        GFX->getDrawUtil()->drawBitmapStretch( texture, RectI( offset, getExtent() ) );
    }
    else
    {
        if ( mProfile->mBorder != 0 )
        {
            RectI boundsRect( offset, getExtent() );

            if ( mDepressed || mStateOn || mHighlighted )
            {
                renderFilledBorder( boundsRect, mProfile->mBorderColorHL, mProfile->mFillColorHL );
            }
            else
            {
                renderFilledBorder( boundsRect, mProfile->mBorderColor, mProfile->mFillColor );
            }
        }
    }

    // Render Text.
    GFX->getDrawUtil()->setBitmapModulation( mProfile->mFontColor );
    renderJustifiedText( offset + mProfile->mTextOffset, getExtent(), mButtonText );

    renderChildControls( offset, updateRect);
}

//-----------------------------------------------------------------------------
//
// Console Methods.
//
//-----------------------------------------------------------------------------

DefineEngineMethod( VEditorButton, getState, bool, (), , "()" )
{
    return object->getStateOn();
}
