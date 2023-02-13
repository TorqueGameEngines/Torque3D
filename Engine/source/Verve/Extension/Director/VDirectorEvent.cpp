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
#include "Verve/Extension/Director/VDirectorEvent.h"

#include "console/consoleTypes.h"

//-----------------------------------------------------------------------------
IMPLEMENT_CONOBJECT( VDirectorEvent );
//-----------------------------------------------------------------------------

VDirectorEvent::VDirectorEvent( void ) : 
        mTarget( String::EmptyString )
{
    // Void.
}

void VDirectorEvent::initPersistFields()
{
   docsURL;
    Parent::initPersistFields();

    addField( "Target", TypeRealString, Offset( mTarget, VDirectorEvent ), "The name of the CameraGroup that will be activated upon triggering." );
}

//-----------------------------------------------------------------------------
//
// Controller Methods.
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// 
// VDirectorEvent::onTrigger( pTime, pDelta );
// 
// Cut the camera to the target group.
// 
//-----------------------------------------------------------------------------
void VDirectorEvent::onTrigger( const S32 &pTime, const S32 &pDelta )
{
    Parent::onTrigger( pTime, pDelta );

    // Fetch Controller.
    VController *controller = getController();

    // Valid Target?
    VCameraGroup *targetGroup = NULL;
    if ( !controller->getObject( mTarget, targetGroup ) )
    {
        Con::warnf( "VDirectorEvent::onTrigger() - Invalid Target Group specified." );
        return;
    }

    // Change Camera.
    targetGroup->setActive();
}
