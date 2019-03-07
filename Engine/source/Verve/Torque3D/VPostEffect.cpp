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
#include "Verve/VerveConfig.h"
#include "Verve/Torque3D/VPostEffect.h"

#include "T3D/gameBase/gameConnection.h"
#include "core/stream/bitStream.h"

//-----------------------------------------------------------------------------
//
// Post Effect Methods.
//
//-----------------------------------------------------------------------------

bool VTorque::isPostEffectEnabled( PostEffectType *pPostEffect )
{
    if ( !pPostEffect )
    {
        // Sanity!
        return false;
    }

    return pPostEffect->isEnabled();
}

void VTorque::setPostEffectOn( PostEffectType *pPostEffect, const bool &pStatus )
{
    if ( !pPostEffect )
    {
        // Sanity!
        return;
    }

#ifdef VT_EDITOR

    if ( pStatus )
    {
        // Enable Effect.
        pPostEffect->enable();
    }
    else
    {
        // Disable Effect.
        pPostEffect->disable();
    }

#else

    // Fetch Name.
    StringTableEntry name = pPostEffect->getName();
    if ( !name || name == StringTable->insert( "" ) )
    {
        Con::warnf( "VTorque::setPostEffectOn() - Invalid Object Name." );
        return;
    }

    // Fetch Client Group.
    SimGroup* clientGroup = Sim::getClientGroup();

    for ( SimGroup::iterator itr = clientGroup->begin(); itr != clientGroup->end(); itr++ )
    {
        NetConnection *connection = static_cast<NetConnection*>( *itr );
        if ( connection )
        {
            // Create Event.
            VPostEffectNetEvent *event = new VPostEffectNetEvent();

            // Setup Event.
            event->mPostEffect = name;
            event->mEnabled    = pStatus;

            // Post Event.
            connection->postNetEvent( event );
        }
    }

#endif
}

//-----------------------------------------------------------------------------
IMPLEMENT_CO_CLIENTEVENT_V1( VPostEffectNetEvent );
//-----------------------------------------------------------------------------

VPostEffectNetEvent::VPostEffectNetEvent( void ) : mPostEffect( StringTable->insert( "" ) ),
                                                   mEnabled( false )
{
    // Void.
}

void VPostEffectNetEvent::write( NetConnection *pConnection, BitStream *pStream )
{
    // Void.
}

void VPostEffectNetEvent::pack( NetConnection *pConnection, BitStream *pStream )
{
    // Object Name.
    pStream->writeString( mPostEffect );

    // Status.
    pStream->writeFlag( mEnabled );
}

void VPostEffectNetEvent::unpack( NetConnection *pConnection, BitStream *pStream )
{
    // Object Name.
    mPostEffect = pStream->readSTString();

    // Status.
    mEnabled = pStream->readFlag();
}

void VPostEffectNetEvent::process( NetConnection *pConnection )
{
    PostEffect *postEffect;
    if ( !Sim::findObject( mPostEffect, postEffect ) )
    {
        Con::warnf( "VPostEffectNetEvent::process() - Unable to find PostEffect Object '%s'", mPostEffect );
        return;
    }

    if ( mEnabled )
    {
        // Enable Effect.
        postEffect->enable();
    }
    else
    {
        // Disable Effect.
        postEffect->disable();
    }
}