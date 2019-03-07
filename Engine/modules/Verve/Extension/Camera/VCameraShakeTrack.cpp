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
#include "Verve/Extension/Camera/VCameraShakeTrack.h"
#include "Verve/Extension/Camera/VCameraShakeEvent.h"

//-----------------------------------------------------------------------------
IMPLEMENT_CONOBJECT( VCameraShakeTrack );
//-----------------------------------------------------------------------------

VCameraShakeTrack::VCameraShakeTrack( void )
{
    setLabel( "CameraShakeTrack" );
}

//-----------------------------------------------------------------------------
//
// Camera Methods.
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// 
// VCameraShakeTrack::onCameraEvent( pEvent );
// 
// When the Camera changes, this method is called on both the outgoing and
// incoming Camera Groups.
// 
// For a full list of possible events, see the 'eCameraEventType' declaration
// in VCameraGroup.h.
// 
//-----------------------------------------------------------------------------
bool VCameraShakeTrack::onCameraEvent( const VCameraGroup::eCameraEventType &pEvent )
{
    // Parent Call.
    if ( !Parent::onCameraEvent( pEvent ) )
    {
        // Skip.
        return false;
    }

    // Enabled?
    if ( !isEnabled() )
    {
        // Continue Processing Events.
        return true;
    }

    switch( pEvent )
    {
        case VCameraGroup::k_EventActivate :
            {

                VCameraShakeEvent *event;
                if ( getCurrentEvent( event ) )
                {
                    // Re-Trigger Event.
                    event->onTrigger( getControllerTime(), 0 );
                }

            } break;

        case VCameraGroup::k_EventDeactivate :
            {

                // Stop Camera Shake.
                VTorque::stopCameraShake();

            } break;
    }

    return true;
}

//-----------------------------------------------------------------------------
//
// Controller Methods.
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// 
// VCameraShakeTrack::onControllerReset( pTime, pForward );
// 
// Stop all camera shake events.
// 
//-----------------------------------------------------------------------------
void VCameraShakeTrack::onControllerReset( const S32 &pTime, const bool &pForward )
{
    // Default Reset.
    Parent::onControllerReset( pTime, pForward );

    // Stop Camera Shake.
    VTorque::stopCameraShake();
}