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
#include "Verve/Core/VTrack.h"

#include "Verve/Extension/Script/VScriptEvent.h"

#include "console/consoleTypes.h"

//-----------------------------------------------------------------------------
IMPLEMENT_CONOBJECT( VScriptEvent );
//-----------------------------------------------------------------------------

// Implement the Command Type enum list.
ImplementEnumType( VScriptEventCommandType, "" )
    { VScriptEvent::k_TypeExpression, "EXPRESSION" },
    { VScriptEvent::k_TypeMethod,     "METHOD"     },
EndImplementEnumType;

//-----------------------------------------------------------------------------

VScriptEvent::VScriptEvent( void ) : 
        mCommandType( k_TypeMethod ),
        mCommand( String::EmptyString )
{
    setLabel( "ScriptEvent" );
}

void VScriptEvent::initPersistFields()
{
   docsURL;
    Parent::initPersistFields();

    addField( "CommandType", TYPEID<eCommandType>(), Offset( mCommandType, VScriptEvent ), "The type of command to be evaluated." );
    addField( "Command",     TypeRealString,         Offset( mCommand,     VScriptEvent ), "The command to be evaluated." );
}

//-----------------------------------------------------------------------------
//
// Callback Methods.
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// 
// VScriptEvet::onTrigger( pTime, pDelta );
// 
// Execute a method or evaluate a command.
// 
//-----------------------------------------------------------------------------
void VScriptEvent::onTrigger( const S32 &pTime, const S32 &pDelta )
{
    Parent::onTrigger( pTime, pDelta );

    switch ( mCommandType )
    {
        case k_TypeExpression :
            {

                // Evaluate Expression.
                Con::evaluate( mCommand, false, NULL );

            } break;

        case k_TypeMethod :
            {

                SimObject *object = getSceneObject();
                if ( object )
                {
                    // Execute Method.
                    Con::executef( object, mCommand.c_str() );
                }
                else
                {
                    // Execute Function.
                    Con::executef( mCommand.c_str());
                }

            } break;
    }
}
