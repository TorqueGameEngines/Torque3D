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
#include "Verve/Torque3D/VCameraShake.h"

#include "T3D/gameBase/gameConnection.h"
#include "core/stream/bitStream.h"

//-----------------------------------------------------------------------------
IMPLEMENT_CO_CLIENTEVENT_V1( VCameraShakeNetEvent );
//-----------------------------------------------------------------------------

// ShakeCamera( 1, 10, "1 0 0", "1 0 0" );
DefineEngineFunction( ShakeCamera, void, (F32 duration, F32 falloff, VectorF amplitude, VectorF frequency), (0,0,VectorF::Zero, VectorF::Zero), "( pDuration, pFalloff, pAmplitude, pFrequency )" )
{
    // Shake Camera.
    VTorque::startCameraShake( duration, falloff, amplitude, frequency );
}

void VTorque::startCameraShake( const F32 &pDuration, const F32 &pFalloff, const VectorF &pAmplitude, const VectorF &pFrequency )
{
#ifdef VT_EDITOR

    // Create FX Event
    CameraShake *camShake = new CameraShake();

    // Set Duration.
    camShake->setDuration( pDuration );

    // Set Falloff.
    camShake->setFalloff( pFalloff );

    // Set Amplitude.
    VectorF amp = pAmplitude;
    camShake->setAmplitude( amp );

    // Set Frequency.
    VectorF freq = pFrequency;
    camShake->setFrequency( freq );

    // Initialise.
    camShake->init();

    // Add to Manager.
    gCamFXMgr.addFX( camShake );

#else

    // Fetch Client Group.
    SimGroup* clientGroup = Sim::getClientGroup();

    for ( SimGroup::iterator itr = clientGroup->begin(); itr != clientGroup->end(); itr++ )
    {
        NetConnection *connection = static_cast<NetConnection*>( *itr );
        if ( connection )
        {
            // Create Event.
            VCameraShakeNetEvent *event = new VCameraShakeNetEvent();

            // Setup Event.
            event->mEventType |= ( VCameraShakeNetEvent::k_TypeClear | VCameraShakeNetEvent::k_TypeMake );
            event->mDuration   = pDuration;
            event->mFalloff    = pFalloff;
            event->mAmplitude  = pAmplitude;
            event->mFrequency  = pFrequency;

            // Post Event.
            connection->postNetEvent( event );
        }
    }

#endif
}

void VTorque::stopCameraShake( void )
{
#ifdef VT_EDITOR

    // Clear Manager.
    gCamFXMgr.clear();

#else

    // Fetch Client Group.
    SimGroup* clientGroup = Sim::getClientGroup();

    for ( SimGroup::iterator itr = clientGroup->begin(); itr != clientGroup->end(); itr++ )
    {
        NetConnection *connection = static_cast<NetConnection*>( *itr );
        if ( connection )
        {
            // Create Event.
            VCameraShakeNetEvent *event = new VCameraShakeNetEvent();

            // Setup Event.
            event->mEventType |= VCameraShakeNetEvent::k_TypeClear;

            // Post Event.
            connection->postNetEvent( event );
        }
    }

#endif
}

//-----------------------------------------------------------------------------

VCameraShakeNetEvent::VCameraShakeNetEvent( void ) : mEventType( 0 ),
                                                     mDuration( 0.f ),
                                                     mFalloff( 10.f ),
                                                     mAmplitude( Point3F::Zero ),
                                                     mFrequency( Point3F::Zero )
{
    // Void.
}

void VCameraShakeNetEvent::write( NetConnection *pConnection, BitStream *pStream )
{
    // Void.
}

void VCameraShakeNetEvent::pack( NetConnection *pConnection, BitStream *pStream )
{
    // Clear Manager?
    pStream->write( mEventType & k_TypeClear );

    // Make Event?
    if ( pStream->write( mEventType & k_TypeMake ) )
    {
        // Duration.
        pStream->write( mDuration );

        // Falloff.
        pStream->write( mFalloff );

        // Amplitude.
        pStream->write( mAmplitude.x );
        pStream->write( mAmplitude.y );
        pStream->write( mAmplitude.z );

        // Frequency.
        pStream->write( mFrequency.x );
        pStream->write( mFrequency.y );
        pStream->write( mFrequency.z );
    }
}

void VCameraShakeNetEvent::unpack( NetConnection *pConnection, BitStream *pStream )
{
    // Clear Manager?
    if ( pStream->readFlag() )
    {
        // Update State.
        mEventType |= k_TypeClear;
    }

    // Make Event?
    if ( pStream->readFlag() )
    {
        // Update State.
        mEventType |= k_TypeMake;

        // Duration.
        pStream->read( &mDuration );

        // Falloff.
        pStream->read( &mFalloff );

        // Amplitude.
        pStream->read( &mAmplitude.x );
        pStream->read( &mAmplitude.y );
        pStream->read( &mAmplitude.z );

        // Frequency.
        pStream->read( &mFrequency.x );
        pStream->read( &mFrequency.y );
        pStream->read( &mFrequency.z );
    }
}

void VCameraShakeNetEvent::process( NetConnection *pConnection )
{
    if ( mEventType & k_TypeClear )
    {
        // Clear Manager.
        gCamFXMgr.clear();
    }

    if ( mEventType & k_TypeMake )
    {
        // Create FX Event
        CameraShake *camShake = new CameraShake();

        // Set Duration.
        camShake->setDuration( mDuration );

        // Set Falloff.
        camShake->setFalloff( mFalloff );

        // Set Amplitude.
        camShake->setAmplitude( mAmplitude );

        // Set Frequency.
        camShake->setFrequency( mFrequency );

        // Initialise.
        camShake->init();

        // Add to Manager.
        gCamFXMgr.addFX( camShake );
    }
}
