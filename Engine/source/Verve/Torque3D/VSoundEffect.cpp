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
#include "Verve/Torque3D/VSoundEffect.h"

#include "T3D/gameBase/gameConnection.h"
#include "core/stream/bitStream.h"
#include "math/mathIO.h"
#include "sfx/sfxSystem.h"
#include "sfx/sfxDescription.h"

//-----------------------------------------------------------------------------
//
// Sound Methods.
//
//-----------------------------------------------------------------------------

bool VTorque::isSoundLooping( SoundEffectType *pSoundProfile )
{
    if ( !pSoundProfile )
    {
        // Sanity!
        return false;
    }

    // Return Looping.
    return pSoundProfile->getDescription()->mIsLooping;
}

S32 VTorque::getSoundDuration( SoundEffectType *pSoundProfile )
{
    if ( !pSoundProfile )
    {
        // Sanity!
        return 0;
    }

    // Return Duration.
    return pSoundProfile->getSoundDuration();
}

VTorque::SoundSourceType *VTorque::playSound( SoundEffectType *pSoundProfile, const U32 &pPosition, const F32 &pPitch )
{
    if ( !pSoundProfile )
    {
        // Sanity!
        return NULL;
    }

#ifdef VT_EDITOR

    // Play Sound.
    SFXSound *source = ( SFXSound* )SFX->playOnce( pSoundProfile );

    if ( source )
    {
        // Set Position.
        source->setPosition( pPosition );

        // Set Pitch.
        source->setPitch( pPitch );
    }

    // Return Source.
    return source;

#else

    // Fetch Client Group.
    SimGroup* clientGroup = Sim::getClientGroup();

    for ( SimGroup::iterator itr = clientGroup->begin(); itr != clientGroup->end(); itr++ )
    {
        NetConnection *connection = static_cast<NetConnection*>( *itr );
        if ( connection )
        {
            // Create Event.
            VSoundEffectNetEvent *event = new VSoundEffectNetEvent();

            // Setup Event.
            event->mProfile  = pSoundProfile;
            event->mPosition = pPosition;
            event->mPitch    = pPitch;
            event->mIs3D     = false;

            // Post Event.
            connection->postNetEvent( event );
        }
    }

    return NULL;

#endif
}

VTorque::SoundSourceType *VTorque::playSound( SoundEffectType *pSoundProfile, SceneObjectType *pObject, const U32 &pPosition, const F32 &pPitch )
{
    if ( !pSoundProfile )
    {
        // Sanity!
        return NULL;
    }

#ifdef VT_EDITOR

    // Fetch Reference Transform.
    const MatrixF &transform = pObject->getTransform();

    // Play Sound.
    SFXSound *source = ( SFXSound* )SFX->playOnce( pSoundProfile, &transform );

    if ( source )
    {
        // Set Position.
        source->setPosition( pPosition );

        // Set Pitch.
        source->setPitch( pPitch );
    }

    // Return Source.
    return source;

#else

    // Fetch Client Group.
    SimGroup* clientGroup = Sim::getClientGroup();

    for ( SimGroup::iterator itr = clientGroup->begin(); itr != clientGroup->end(); itr++ )
    {
        NetConnection *connection = static_cast<NetConnection*>( *itr );
        if ( connection )
        {
            // Create Event.
            VSoundEffectNetEvent *event = new VSoundEffectNetEvent();

            // Setup Event.
            event->mProfile   = pSoundProfile;
            event->mPosition  = pPosition;
            event->mPitch     = pPitch;
            event->mIs3D      = true;
            event->mTransform = pObject->getTransform();

            // Post Event.
            connection->postNetEvent( event );
        }
    }

    return NULL;

#endif
}

void VTorque::playSound( SoundSourceType *pSource )
{
    if ( !pSource )
    {
        // Sanity!
        return;
    }

    // Play.
    pSource->play();
}

void VTorque::pauseSound( SoundSourceType *pSource )
{
    if ( !pSource )
    {
        // Sanity!
        return;
    }

    // Pause.
    pSource->pause();
}

void VTorque::stopSound( SoundSourceType *pSource )
{
    if ( !pSource )
    {
        // Sanity!
        return;
    }

    // Stop.
    pSource->stop();
}

void VTorque::setSoundPosition( SoundSourceType *pSource, const U32 &pPosition )
{
    if ( !pSource )
    {
        // Sanity!
        return;
    }

    // Set Position.
    pSource->setPosition( pPosition );
}

void VTorque::setSoundPitch( SoundSourceType *pSource, const F32 &pPitch )
{
    if ( !pSource )
    {
        // Sanity!
        return;
    }

    // Set Pitch.
    pSource->setPitch( pPitch );
}

//-----------------------------------------------------------------------------
IMPLEMENT_CO_CLIENTEVENT_V1( VSoundEffectNetEvent );
//-----------------------------------------------------------------------------

VSoundEffectNetEvent::VSoundEffectNetEvent( void ) : mProfile( NULL ),
                                                     mPosition( 0.f ),
                                                     mPitch( 1.f ),
                                                     mIs3D( false ),
                                                     mTransform( MatrixF::Identity )
{
    // Void.
}

void VSoundEffectNetEvent::write( NetConnection *pConnection, BitStream *pStream )
{
    // Void.
}

void VSoundEffectNetEvent::pack( NetConnection *pConnection, BitStream *pStream )
{
    // Valid?
    if ( !pStream->writeFlag( mProfile != NULL ) )
    {
        return;
    }

    // Profile.
    pStream->writeInt( mProfile->getId() - DataBlockObjectIdFirst, DataBlockObjectIdBitSize );

    // Position.
    pStream->write( mPosition );

    // Pitch.
    pStream->write( mPitch );

    // 3D?
    if ( pStream->writeFlag( mIs3D ) )
    {
        // Rotation.
        SFXDescription* description = mProfile->getDescription();
        if ( pStream->writeFlag( description->mConeInsideAngle || description->mConeOutsideAngle ) ) 
        {
            // Entire Transform.
            pStream->writeAffineTransform( mTransform );
        }
        else
        {
            // Position.
            mathWrite( *pStream, mTransform.getColumn3F( 3 ) );
        }
    }
}

void VSoundEffectNetEvent::unpack( NetConnection *pConnection, BitStream *pStream )
{
    // Valid?
    if ( !pStream->readFlag() )
    {
        return;
    }

    // Profile.
    Sim::findObject( pStream->readInt( DataBlockObjectIdBitSize ) + DataBlockObjectIdFirst, mProfile );

    // Position.
    pStream->read( &mPosition );

    // Pitch.
    pStream->read( &mPitch );

    // 3D?
    if ( pStream->readFlag() )
    {
        // Yup!
        mIs3D = true;

        // Rotation?
        if ( pStream->readFlag() )
        {
            // Transform.
            pStream->readAffineTransform( &mTransform );
        }
        else
        {
            // Position.
            Point3F pos;
            mathRead( *pStream, &pos );
            mTransform.setColumn( 3, pos );
        }
    }
}

void VSoundEffectNetEvent::process( NetConnection *pConnection )
{
    // Valid?
    if ( !mProfile )
    {
        return;
    }

    SFXSound *source = NULL;
    if ( mIs3D )
    {
        // Play 3D Sound.
        source = ( SFXSound* )SFX->playOnce( mProfile, &mTransform );
    }
    else
    {
        // Play 2D Sound.
        source = ( SFXSound* )SFX->playOnce( mProfile );
    }

    if ( source )
    {
        // Set Position.
        source->setPosition( mPosition );

        // Set Pitch.
        source->setPitch( mPitch );
    }
}