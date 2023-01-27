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
#include "Verve/GUI/VTimeLineControl.h"
#include "console/consoleTypes.h"
#include "gfx/gfxDrawUtil.h"
#include "gui/core/guiCanvas.h"

//-----------------------------------------------------------------------------

const S32 gUnitsPerSec = 200;

//-----------------------------------------------------------------------------
IMPLEMENT_CONOBJECT( VTimeLineControl );
//-----------------------------------------------------------------------------

VTimeLineControl::VTimeLineControl( void ) :
        mIsController( true ),
        mController( NULL ),
        mDurationOffset( 50 )
{
    mSelection.Active    = false;
    mSelection.StartTime = 0;
    mSelection.EndTime   = 0;
}

void VTimeLineControl::initPersistFields()
{
   docsURL;
    Parent::initPersistFields();

    addField( "IsController",   TypeBool,              Offset( mIsController,   VTimeLineControl ) );
    addField( "Controller",     TYPEID<VController>(), Offset( mController,     VTimeLineControl ) );
    addField( "DurationOffset", TypeS32,               Offset( mDurationOffset, VTimeLineControl ) );
}

//-----------------------------------------------------------------------------
//
// Mouse Methods.
//
//-----------------------------------------------------------------------------

void VTimeLineControl::onMouseDown( const GuiEvent &pEvent )
{
    Parent::onMouseDown( pEvent );

    if ( !mIsController || !mController || mController->isPlaying() )
    {
        return;
    }

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

    // Calculate Time.
    const Point2I hitPoint = globalToLocalCoord( pEvent.mousePoint );
    const S32     time     = mClamp( toTime( hitPoint.x ), 0, mController->getDuration() );

    // Selection?
    if (  pEvent.modifier & SI_SHIFT )
    {
        if ( !mSelection.Active )
        {
            // Selection Active.
            mSelection.Active    = true;
            mSelection.StartTime = mController->getTime();
            mSelection.EndTime   = time;
        }
        else
        {
            // Update Selection.
            mSelection.EndTime = time;
        }

        // Callback.
        Con::executef( this, "onSelectionUpdate" );
    }
    else
    {
        if ( mSelection.Active )
        {
            // Selection Invalid.
            mSelection.Active = false;

            // Callback.
            Con::executef( this, "onSelectionUpdate" );
        }
    }

    // Set First Responder.
    setFirstResponder();

    if ( pEvent.modifier & SI_CTRL )
    {
        // Set Time, No Reset.
        mController->setTime( time );
    }
    else
    {
        // Reset.
        mController->reset( time );
    }
}

void VTimeLineControl::onMouseUp( const GuiEvent &pEvent )
{
    if ( isMouseLocked() )
    {
        // Unlock.
        mouseUnlock();
    }

    if ( mIsController && mController && !mController->isPlaying() )
    {
        // Stop without Reset.
        mController->stop( false );
    }
}

void VTimeLineControl::onMouseDragged( const GuiEvent &pEvent )
{
    Parent::onMouseDragged( pEvent );

    if ( !mIsController || !mController || mController->isPlaying() )
    {
        return;
    }

    // Calculate Time.
    const Point2I hitPoint = globalToLocalCoord( pEvent.mousePoint );
    const S32     time     = mClamp( toTime( hitPoint.x ), 0, mController->getDuration() );

    if (  pEvent.modifier & SI_SHIFT )
    {
        if ( mSelection.Active )
        {
            // Update Selection.
            mSelection.EndTime = time;

            // Callback.
            Con::executef( this, "onSelectionUpdate" );
        }
    }
    else
    {
        if ( mSelection.Active )
        {
            // Selection Invalid.
            mSelection.Active = false;

            // Callback.
            Con::executef( this, "onSelectionUpdate" );
        }
    }

    if ( pEvent.modifier & SI_CTRL )
    {
        // Set Time, No Reset.
        mController->setTime( time );
    }
    else if ( !mSelection.Active )
    {
        // Reset.
        mController->reset( time );
    }
}

void VTimeLineControl::onRightMouseDown( const GuiEvent &pEvent )
{
    Parent::onRightMouseDown( pEvent );

    if ( !mIsController || !mController || mController->isPlaying() )
    {
        return;
    }

    // Calculate Time.
    const Point2I hitPoint = globalToLocalCoord( pEvent.mousePoint );
    const S32     time     = mClamp( toTime( hitPoint.x ), 0, mController->getDuration() );

    // Set First Responder.
    setFirstResponder();

    if ( mSelection.Active )
    {
        const S32 minTime = getMin( mSelection.StartTime, mSelection.EndTime );
        const S32 maxTime = getMax( mSelection.StartTime, mSelection.EndTime );
        if ( time >= minTime && time <= maxTime )
        {
            // Callback.
            onMouseEvent( "onSelectionRightClick", pEvent );

            // Don't Update Time.
            return;
        }
        else
        {
            if ( mSelection.Active )
            {
                // Selection Invalid.
                mSelection.Active = false;

                // Callback.
                Con::executef( this, "onSelectionUpdate" );
            }
        }
    }

    // Reset.
    mController->reset( time );
}

void VTimeLineControl::onMouseEvent( const char *pEventName, const GuiEvent &pEvent )
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
//
// Render Methods.
//
//-----------------------------------------------------------------------------

void VTimeLineControl::onPreRender( void )
{
    setUpdate();
}

void VTimeLineControl::onRender( Point2I offset, const RectI &updateRect )
{
    if ( !mController )
    {
        // Default Render.
        Parent::onRender( offset, updateRect );

        // Quit.
        return;
    }

    // Render Properties.
    const S32 tickOffset        = toPoint( 0 );
    const S32 timeLineWidth     = toPoint( mController->getDuration() ) - tickOffset;
    const F32 tickStep          = 0.5f;
    const S32 tickInterval      = ( mIsController ) ? getWidth() : timeLineWidth;
    const S32 tickIntervalCount = ( S32 )mFloor( tickInterval / ( gUnitsPerSec * tickStep ) ) + 1;

    // Tick Render Proeprties.
    const Point2I tickExtent( 0, getHeight() - 1 );

    // Text Render Properties.
    const Point2I textExtent( gUnitsPerSec, mProfile->mFontSize );
    const Point2I textOffset( 4, -mProfile->mFontSize );

    // Render Border.
    GFX->getDrawUtil()->drawRectFill( RectI( offset + Point2I( tickOffset + 1, 1 ), Point2I( timeLineWidth - 1, getHeight() - 1 ) ), mProfile->mFillColorHL );
    
    // Font Color.
    GFX->getDrawUtil()->setBitmapModulation( mProfile->mFontColor );

    for ( S32 i = 0; i < tickIntervalCount; i++ )
    {
        // Tick Position.
        const Point2I tickPosition = offset + Point2I( tickOffset + i * ( gUnitsPerSec * tickStep ), 0 );

        // Line Color.
        const ColorI lineColor = ( ( i % 2 ) ) ? mProfile->mBorderColorHL : mProfile->mBorderColor;

        // Draw Line.
        GFX->getDrawUtil()->drawLine( tickPosition, tickPosition + tickExtent, lineColor );

        if ( mIsController )
        {
            // Render Times.
            renderJustifiedText( tickPosition + tickExtent + textOffset, textExtent, avar( "%.2f", ( F32 )( i * tickStep ) ) );
        }
    }

    // Render Children
    renderChildControls( offset, updateRect );

    if ( mSelection.Active )
    {
        // Selection Width.
        const S32 selectionWidth = mCeil( mAbs( toPoint( mSelection.EndTime ) - toPoint( mSelection.StartTime ) ) );
        
        // Selection Position.
        const S32 selectionPositionX = toPoint( getMin( mSelection.StartTime, mSelection.EndTime ) );

        // Selection Properties.
        const Point2I selectionExtent( selectionWidth, getHeight() );
        const Point2I selectionPosition = offset + Point2I( selectionPositionX, 0 );

        // Render Time Cue.
        GFX->getDrawUtil()->drawRectFill( RectI( selectionPosition, selectionExtent ), ColorI( 0, 0, 0, 128 ) );

        if ( mIsController )
        {
            // Buffer.
            char buffer[2][128];
            dSprintf( buffer[0], 128, "%.2f", ( F32 )( mSelection.StartTime / 1000.f ) );
            dSprintf( buffer[1], 128, "%.2f", ( F32 )( mSelection.EndTime / 1000.f ) );

            if ( mSelection.StartTime < mSelection.EndTime )
            {
                // Fetch Width.
                const S32 textWidth = mProfile->mFont->getStrWidth( buffer[0] );

                // Text Position.
                const Point2I startText = Point2I( getMax( ( S32 )( selectionPosition.x - ( textWidth + 2 ) ), updateRect.point.x + 4 ), selectionPosition.y + 2 );
                const Point2I endText   = Point2I( getMin( ( S32 )( selectionPosition.x + selectionWidth + 4 ), updateRect.point.x + updateRect.extent.x - ( textWidth + 2 ) ), selectionPosition.y + 2 );

                // Render Time Text.
                renderJustifiedText( startText, textExtent, buffer[0] );
                renderJustifiedText( endText, textExtent, buffer[1] );
            }
            else
            {
                // Fetch Width.
                const S32 textWidth = mProfile->mFont->getStrWidth( buffer[1] );

                // Text Position.
                const Point2I startText = Point2I( getMax( ( S32 )( selectionPosition.x - ( textWidth + 2 ) ), updateRect.point.x + 4 ), selectionPosition.y + 2 );
                const Point2I endText   = Point2I( getMin( ( S32 )( selectionPosition.x + selectionWidth + 4 ), updateRect.point.x + updateRect.extent.x - ( textWidth + 2 ) ), selectionPosition.y + 2 );

                // Render Time Text.
                renderJustifiedText( startText, textExtent, buffer[1] );
                renderJustifiedText( endText, textExtent, buffer[0] );
            }
        }
    }

    if ( mController && !mSelection.Active )
    {
        // Time Cue Properties.
        const Point2I timeCueExtent( ( mIsController ) ? 4 : 2, getHeight() );
        const Point2I timeCuePosition = offset + Point2I( toPoint( mController->getTime() ) - ( timeCueExtent.x / 2 ), 0 );

        // Render Time Cue.
        GFX->getDrawUtil()->drawRectFill( RectI( timeCuePosition, timeCueExtent ), ColorI( 0,0,0,128 ) );

        if ( mIsController )
        {
            // Buffer.
            char buffer[128];
            dSprintf( buffer, 128, "%.2f", ( F32 )( mController->getTime() / 1000.f ) );

            // Fetch Width.
            const S32 textWidth = mProfile->mFont->getStrWidth( buffer );

            // Text Position.
            const Point2I textPosition( getMin( getMax( timeCuePosition.x + 6, updateRect.point.x + 4 ), updateRect.point.x + updateRect.extent.x - ( textWidth + 2 ) ), timeCuePosition.y + 2 );

            // Render Time Text.
            renderJustifiedText( textPosition, textExtent, buffer );
        }
    }
}

//-----------------------------------------------------------------------------
//
// Console Methods.
//
//-----------------------------------------------------------------------------

DefineEngineMethod( VTimeLineControl, toPoint, S32, (S32 time), (0), "( pTime )" )
{
    return object->toPoint(time);
}

S32 VTimeLineControl::toTime( const S32 &pPoint )
{
    return ( ( S32 )( 1000.f * ( F32 )pPoint / gUnitsPerSec ) - mDurationOffset );
}

DefineEngineMethod( VTimeLineControl, toTime, S32, (S32 point), (0), "( pPoint )" )
{
    return object->toTime(point);
}

S32 VTimeLineControl::toPoint( const S32 &pTime )
{
    return ( S32 )( gUnitsPerSec * ( ( F32 )( pTime + mDurationOffset ) / 1000.f ) );
}

DefineEngineMethod( VTimeLineControl, getSelection, const char *, (),, "( )" )
{
    const S32 minTime = getMin( object->mSelection.StartTime, object->mSelection.EndTime );
    const S32 maxTime = getMax( object->mSelection.StartTime, object->mSelection.EndTime );

    // Fetch Return Buffer.
    char *retBuffer = Con::getReturnBuffer( 256 );

    // Write.
    dSprintf( retBuffer, 256, "%d %d %d", object->mSelection.Active, minTime, maxTime - minTime );

    // Return.
    return retBuffer;
}

DefineEngineMethod( VTimeLineControl, setSelection, void, (bool active, S32 time, S32 duration), (true, -1, 1), "( pActive, [pTime, pDuration] )" )
{
    object->mSelection.Active = active;
    if (time != -1)
    {
        object->mSelection.StartTime = time;
        object->mSelection.EndTime   = object->mSelection.StartTime + duration;
    }
}

DefineEngineMethod( VTimeLineControl, updateDuration, void, (),, "( )" )
{
    object->updateDuration();
}

void VTimeLineControl::updateDuration( void )
{
    if ( !mController )
    {
        // No Controller.
        return;
    }

    // Add 500ms.
    const S32 length = toPoint( mController->getDuration() + 500 );

    // Set Min Extent.
    setMinExtent( Point2I( length, getHeight() ) );

    if ( getWidth() < length )
    {
        // Conform to Min Extent.
        setExtent( length, getHeight() );
    }
}
