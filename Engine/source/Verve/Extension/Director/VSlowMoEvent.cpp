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
#include "Verve/Core/VController.h"
#include "Verve/Extension/Director/VSlowMoEvent.h"

#include "console/consoleTypes.h"

//-----------------------------------------------------------------------------
IMPLEMENT_CONOBJECT( VSlowMoEvent );
//-----------------------------------------------------------------------------

VSlowMoEvent::VSlowMoEvent( void ) : 
        mTimeScale( 1.f ),
        mTimeScaleTickDelta( 0.f )
{
    setLabel( "SlowMoEvent" );
}

void VSlowMoEvent::initPersistFields()
{
   docsURL;
    Parent::initPersistFields();

    addField( "TimeScale", TypeF32, Offset( mTimeScale, VSlowMoEvent ), "The Time Scale to be applied to the Root Controller." );
}

//-----------------------------------------------------------------------------
//
// Controller Methods.
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// 
// VSlowMoEvent::onTrigger( pTime, pDelta );
// 
// 
// 
//-----------------------------------------------------------------------------
void VSlowMoEvent::onTrigger( const S32 &pTime, const S32 &pDelta )
{
    Parent::onTrigger( pTime, pDelta );

    VController *controller = getController();
    if ( !controller )
    {
        // Invalid Controller.
        return;
    }

    // Instant Update?
    if ( getDuration() == 0 )
    {
        // Apply & Return.
        controller->setTimeScale( mTimeScale );
        return;
    }

    // Determine the Number of Ticks.
    const F32 tickCount = ( ( F32 )getDuration() ) / TickMs;

    // Determine the Tick Delta.
    mTimeScaleTickDelta = ( mTimeScale - controller->getTimeScale() ) / tickCount;
}

//-----------------------------------------------------------------------------
// 
// VSlowMoEvent::onUpdate( pTime, pDelta );
// 
// 
// 
//-----------------------------------------------------------------------------
void VSlowMoEvent::onUpdate( const S32 &pTime, const S32 &pDelta )
{
    Parent::onUpdate( pTime, pDelta );

    VController *controller = getController();
    if ( !controller )
    {
        // Invalid Controller.
        return;
    }

    // Fetch Current Time Scale.
    const F32 timeScale = controller->getTimeScale();

    // Apply Update.
    controller->setTimeScale( timeScale + mTimeScaleTickDelta );
}

//-----------------------------------------------------------------------------
// 
// VSlowMoEvent::onComplete( pTime, pDelta );
// 
// 
// 
//-----------------------------------------------------------------------------
void VSlowMoEvent::onComplete( const S32 &pTime, const S32 &pDelta )
{
    Parent::onComplete( pTime, pDelta );

    VController *controller = getController();
    if ( !controller )
    {
        // Invalid Controller.
        return;
    }

    // Tidy Up.
    controller->setTimeScale( mTimeScale );
}
