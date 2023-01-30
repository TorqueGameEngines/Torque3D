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
#include "Verve/Extension/Director/VSceneJumpEvent.h"
#include "Verve/Extension/Director/VDirectorGroup.h"
#include "Verve/Extension/Director/VDirectorTrack.h"
#include "Verve/Extension/Director/VDirectorEvent.h"

#include "console/consoleTypes.h"

//-----------------------------------------------------------------------------
IMPLEMENT_CONOBJECT( VSceneJumpEvent );
//-----------------------------------------------------------------------------

VSceneJumpEvent::VSceneJumpEvent( void ) :
        mTarget( String::EmptyString )
{
    setLabel( "SceneJumpEvent" );
}

void VSceneJumpEvent::initPersistFields()
{
   docsURL;
    Parent::initPersistFields();

    addField( "Target", TypeRealString, Offset( mTarget, VSceneJumpEvent ), "The name of the Scene that the controller will jump to upon triggering." );
}

//-----------------------------------------------------------------------------
//
// Controller Methods.
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// 
// VSceneJumpEvent::onTrigger( pTime, pDelta );
// 
// Tell the controller to jump to a new scene.
// 
//-----------------------------------------------------------------------------
void VSceneJumpEvent::onTrigger( const S32 &pTime, const S32 &pDelta )
{
    Parent::onTrigger( pTime, pDelta );

    VDirectorTrack *track = getController()->getDirectorTrack();
    if ( !track )
    {
        // Invalid Track.
        return;
    }

    // Get Event.
    VDirectorEvent *event;
    if ( !track->getObject( mTarget, event ) )
    {
        // Can't Jump.
        return;
    }

    // Go To Scene.
    getController()->jump( VController::k_JumpTime, event->getTriggerTime() );
}
