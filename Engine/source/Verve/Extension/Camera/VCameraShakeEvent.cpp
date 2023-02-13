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
#include "Verve/Core/VGroup.h"
#include "Verve/Extension/Camera/VCameraGroup.h"
#include "Verve/Extension/Camera/VCameraShakeEvent.h"

#include "console/consoleTypes.h"

//-----------------------------------------------------------------------------
IMPLEMENT_CONOBJECT( VCameraShakeEvent );
//-----------------------------------------------------------------------------

VCameraShakeEvent::VCameraShakeEvent( void ) : 
        mAmplitude( Point3F::Zero ),
        mFalloff( 10.f ),
        mFrequency( Point3F::Zero )
{
    // Clear Label.
    setLabel( "CameraShakeEvent" );
}

void VCameraShakeEvent::initPersistFields()
{
   docsURL;
    Parent::initPersistFields();

    addField( "Amplitude", TypePoint3F, Offset( mAmplitude, VCameraShakeEvent ), "Amplitude of the Camera Shake event." );
    addField( "Falloff",   TypeF32,     Offset( mFalloff,   VCameraShakeEvent ), "Falloff of the Camera Shake event." );
    addField( "Frequency", TypePoint3F, Offset( mFrequency, VCameraShakeEvent ), "Frequency of the Camera Shake event." );
}

//-----------------------------------------------------------------------------
//
// Controller Methods.
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// 
// VCameraShakeEvent::onTrigger( pTime, pDelta );
// 
// Start shaking the camera. Also account for any offet in playtime, and
// timescale.
// 
//-----------------------------------------------------------------------------
void VCameraShakeEvent::onTrigger( const S32 &pTime, const S32 &pDelta )
{
    Parent::onTrigger( pTime, pDelta );

    // Fetch Group.
    VCameraGroup *group;
    if ( !getGroup( group ) || !group->isActive() )
    {
        // Inactive.
        return;
    }

    // Duration.
    //const F32 duration  = ( mDuration - mAbs( pTime - getStartTime() ) ) / ( 1000.f * mFabs( getControllerTimeScale() ) );
    const F32 duration  = ( mDuration - mAbs( pTime - getStartTime() ) ) / 1000.f;

    // Shake Camera.
    VTorque::startCameraShake( duration, mFalloff, mAmplitude, mFrequency );
}
