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
#include "Verve/Extension/Camera/VCameraTrack.h"

//-----------------------------------------------------------------------------
IMPLEMENT_CONOBJECT( VCameraTrack );
//-----------------------------------------------------------------------------

VCameraTrack::VCameraTrack( void )
{
    setLabel( "CameraTrack" );
}

//-----------------------------------------------------------------------------
//
// Tree Methods.
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// 
// VCameraTrack::onAttach();
// 
// This callback subscribes this object to the Camera Group's event signal.
// 
//-----------------------------------------------------------------------------
void VCameraTrack::onAttach( void )
{
    Parent::onAttach();

    // Valid Controller & Group?
    VCameraGroup *group;
    if ( getController() && getGroup( group ) )
    {
        // Add Event Notification.
        group->getCameraEventSignal().notify( this, &VCameraTrack::onCameraEvent );
    }
}

//-----------------------------------------------------------------------------
// 
// VCameraTrack::onAttach();
// 
// This callback removes this object from the Camera Group's event signal
// notification list.
// 
//-----------------------------------------------------------------------------
void VCameraTrack::onDetach( void )
{
    // Valid Controller & Group?
    VCameraGroup *group;
    if ( getController() && getGroup( group ) )
    {
        // Clear Event Notification.
        group->getCameraEventSignal().remove( this, &VCameraTrack::onCameraEvent );
    }

    Parent::onDetach();
}

//-----------------------------------------------------------------------------
//
// Camera Methods.
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// 
// VCameraTrack::onCameraEvent( pEvent );
// 
// When the Camera changes, this method is called on both the outgoing and
// incomming Camera Groups.
// 
// For a full list of possible events, see the 'eCameraEventType' declaration
// in VCameraGroup.h.
// 
//-----------------------------------------------------------------------------
bool VCameraTrack::onCameraEvent( const VCameraGroup::eCameraEventType &pEvent )
{
    if ( !getController() )
    {
        AssertFatal( false, "VCameraTrack::onControllerEvent() - Invalid Controller." );
        return false;
    }

    // Ok.
    return true;
}