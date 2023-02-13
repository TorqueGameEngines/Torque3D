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
#include "Verve/Extension/PostEffect/VPostEffectToggleTrack.h"
#include "Verve/Extension/PostEffect/VPostEffectToggleEvent.h"
#include "Verve/Extension/Camera/VCameraGroup.h"

#include "console/consoleTypes.h"

//-----------------------------------------------------------------------------
IMPLEMENT_CONOBJECT( VPostEffectToggleTrack );
//-----------------------------------------------------------------------------

VPostEffectToggleTrack::VPostEffectToggleTrack( void ) : 
        mPostEffect( NULL )
{
    setLabel( "PostEffectTrack" );
}

void VPostEffectToggleTrack::initPersistFields()
{
   docsURL;
    Parent::initPersistFields();

    addField( "PostEffect", TYPEID<VTorque::PostEffectType>(), Offset( mPostEffect, VPostEffectToggleTrack ), "The name of the PostEffect object to be triggered." );
}

//-----------------------------------------------------------------------------
//
// Camera Methods.
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// 
// VPostEffectToggleTrack::onCameraEvent( pEvent );
// 
// When the Camera changes, this method is called on both the outgoing and
// incoming Camera Groups.
// 
// For a full list of possible events, see the 'eCameraEventType' declaration
// in VCameraGroup.h.
// 
//-----------------------------------------------------------------------------
bool VPostEffectToggleTrack::onCameraEvent( const VCameraGroup::eCameraEventType &pEvent )
{
    // Parent Call.
    if ( !Parent::onCameraEvent( pEvent ) )
    {
        // Skip.
        return false;
    }

    // Enabled?
    if ( !isEnabled() || !mPostEffect.isValid() )
    {
        // Quit Now.
        return true;
    }

    switch( pEvent )
    {
        case VCameraGroup::k_EventActivate :
            {

                VPostEffectToggleEvent *event;
                if ( getPreviousEvent( event ) && event->mEventType == VSharedEnum::k_ActionTurnOn )
                {
                    // Toggle Post Effect On.
                    VTorque::setPostEffectOn( mPostEffect, true );
                }

            } break;

        case VCameraGroup::k_EventDeactivate :
            {

                // Turn Post Effect Off.
                VTorque::setPostEffectOn( mPostEffect, false );

            } break;
    }

    return true;
}
