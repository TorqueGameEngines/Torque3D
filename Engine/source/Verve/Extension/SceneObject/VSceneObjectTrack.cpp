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
#include "Verve/Extension/SceneObject/VSceneObjectGroup.h"
#include "Verve/Extension/SceneObject/VSceneObjectTrack.h"

//-----------------------------------------------------------------------------
IMPLEMENT_CONOBJECT( VSceneObjectTrack );
//-----------------------------------------------------------------------------

VSceneObjectTrack::VSceneObjectTrack( void )
{
    setLabel( "SceneObjectTrack" );
}

//-----------------------------------------------------------------------------
//
// Reference Methods.
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// 
// VSceneObjectTrack::getSceneObject();
// 
// Returns the parent group's object reference.
// 
//-----------------------------------------------------------------------------
VTorque::SceneObjectType *VSceneObjectTrack::getSceneObject( void )
{
    VSceneObjectGroup *group;
    if ( !getGroup( group ) )
    {
        // No Group!
        return NULL;
    }

    // Return Object.
    return group->getSceneObject();
}

#ifdef VT_EDITOR
//-----------------------------------------------------------------------------
//
// Debug Methods.
//
//-----------------------------------------------------------------------------

DefineEngineMethod( VSceneObjectTrack, getSceneObject, S32, (),, "( void ) - Get the object this group references.\n"
                                                             "@return Returns the SimObjectID for the object." )
{
    // Fetch Object.
    VTorque::SceneObjectType *objReference = object->getSceneObject();

    // Return.
    return ( objReference ) ? objReference->getId() : 0;
}
#endif
