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
#include "Verve/Extension/Director/VDirectorTrack.h"

#include "math/mMathFn.h"

//-----------------------------------------------------------------------------
IMPLEMENT_CONOBJECT( VDirectorTrack );
//-----------------------------------------------------------------------------

VDirectorTrack::VDirectorTrack( void )
{
    setLabel( "DirectorTrack" );
}

#ifdef VT_EDITOR
//-----------------------------------------------------------------------------
//
// Debug Methods.
//
//-----------------------------------------------------------------------------

ConsoleMethod( VDirectorTrack, updateTrack, void, 2, 2, "( void ) - Update the Track.\n"
                                                        "@return No return value."  )
{
    for ( ITreeNode *node = object->mChildNode; node != NULL; node = node->mSiblingNextNode )
    {
        VEvent *currEvent = ( VEvent* )node;
        VEvent *nextEvent = ( VEvent* )node->mSiblingNextNode;

        if ( !nextEvent )
        {
            // Update Duration.
            currEvent->setDuration( object->getControllerDuration() - currEvent->getTriggerTime() );
        }
        else
        {
            // Update Duration.
            currEvent->setDuration( mAbs( nextEvent->getTriggerTime() - currEvent->getTriggerTime() ) );
        }
    }
}
#endif