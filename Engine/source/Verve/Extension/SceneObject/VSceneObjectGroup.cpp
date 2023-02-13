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
#include "Verve/Core/VController.h"

#include "console/consoleTypes.h"

//-----------------------------------------------------------------------------
IMPLEMENT_CONOBJECT( VSceneObjectGroup );
//-----------------------------------------------------------------------------

VSceneObjectGroup::VSceneObjectGroup( void ) : 
        mDataReference( String::EmptyString ),
        mSceneObject( NULL )
{
    setLabel( "SceneObjectGroup" );
};

void VSceneObjectGroup::initPersistFields()
{
   docsURL;
    Parent::initPersistFields();

    addField( "Reference", TypeRealString, Offset( mDataReference, VSceneObjectGroup ), "The name of the data field referencing the targeted object." );
}

//-----------------------------------------------------------------------------
//
// Reference Methods.
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// 
// VSceneObjectGroup::getObject();
// 
// Returns the group's object reference.
// 
//-----------------------------------------------------------------------------
VTorque::SceneObjectType *VSceneObjectGroup::getSceneObject( void )
{
#ifndef VT_EDITOR
    // Already Referenced?
    if ( mSceneObject )
    {
        // Return Object.
        return mSceneObject;
    }
#endif

    VController *controller = getController();
    if ( !controller )
    {
        // No Controller!
        return NULL;
    }

    String fieldValue;
    if ( controller->getDataValue( mDataReference, fieldValue ) )
    {
        // Store Object.
        mSceneObject = dynamic_cast<VTorque::SceneObjectType*>( Sim::findObject( fieldValue ) );
    }

    // Return.
    return mSceneObject;
}

#ifdef VT_EDITOR
//-----------------------------------------------------------------------------
//
// Debug Methods.
//
//-----------------------------------------------------------------------------

DefineEngineMethod( VSceneObjectGroup, getSceneObject, S32, (),, "( void ) - Get the object this group references.\n"
                                                             "@return Returns the SimObjectID for the object." )
{
    // Fetch Object.
    VTorque::SceneObjectType *objReference = object->getSceneObject();

    // Return.
    return ( objReference ) ? objReference->getId() : 0;
}
#endif
