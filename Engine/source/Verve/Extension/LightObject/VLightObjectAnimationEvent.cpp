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
#include "Verve/Extension/LightObject/VLightObjectAnimationEvent.h"

#include "console/consoleTypes.h"

//-----------------------------------------------------------------------------
IMPLEMENT_CONOBJECT( VLightObjectAnimationEvent );
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

VLightObjectAnimationEvent::VLightObjectAnimationEvent( void ) : 
        mAnimationData( NULL )
{
    setLabel( "AnimationEvent" );
}

void VLightObjectAnimationEvent::initPersistFields()
{
   docsURL;
    Parent::initPersistFields();

    addField( "AnimationData", TYPEID<VTorque::LightAnimationDataType>(), Offset( mAnimationData, VLightObjectAnimationEvent ) );
}

//-----------------------------------------------------------------------------
//
// Callback Methods.
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// 
// VLightObjectAnimationEvent::onTrigger( pTime, pDelta );
// 
// When this Event is triggered the light object will begin to play the target
// animation.
// 
//-----------------------------------------------------------------------------
void VLightObjectAnimationEvent::onTrigger( const S32 &pTime, const S32 &pDelta )
{
    Parent::onTrigger( pTime, pDelta );

    // Fetch the Light Object.
    VTorque::LightObjectType *lightObject;
    if ( getSceneObject( lightObject ) )
    {
        // Play the Animation.
        VTorque::playAnimation( lightObject, mAnimationData );
    }
}

//-----------------------------------------------------------------------------
// 
// VLightObjectAnimationEvent::onComplete( pTime, pDelta );
// 
// The current animation played by the light object will be paused when this
// Event completes its updates.
// 
//-----------------------------------------------------------------------------
void VLightObjectAnimationEvent::onComplete( const S32 &pTime, const S32 &pDelta )
{
    Parent::onTrigger( pTime, pDelta );

    // Fetch the Light Object.
    VTorque::LightObjectType *lightObject;
    if ( getSceneObject( lightObject ) )
    {
        // Pause the Animation.
        VTorque::pauseAnimation( lightObject );
    }
}
