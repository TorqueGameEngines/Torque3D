//-----------------------------------------------------------------------------
// Copyright (c) 2012 GarageGames, LLC
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

#include "sfx/openal/sfxALDevice.h"
#include "sfx/openal/sfxALBuffer.h"
#include "platform/async/asyncUpdate.h"

class SFXALRegisterProvider
{
public:
   SFXALRegisterProvider()
   {
      SFXSystem::getRegisterProviderSignal().notify(&SFXALDevice::enumerateProviders);
   }
};

static SFXALRegisterProvider pSFXALRegisterProvider;

SFXProvider::CreateProviderInstanceDelegate SFXALDevice::mCreateDeviceInstance(SFXALDevice::createInstance);

SFXDevice* SFXALDevice::createInstance(U32 providerIndex)
{
   SFXALDevice* dev = new SFXALDevice(providerIndex);
   return dev;
}


//----------------------------------------------------------------------------
// STATIC OPENAL FUNCTIONS
//----------------------------------------------------------------------------
void SFXALDevice::printALInfo(ALCdevice* device)
{
   ALCint major, minor;
   if (device)
   {
      const ALCchar* devname = NULL;
      Con::printBlankLine();

      if (alcIsExtensionPresent(device, "ALC_ENUMERATE_ALL_EXT") != AL_FALSE)
      {
         devname = alcGetString(device, ALC_ALL_DEVICES_SPECIFIER);
      }
      else
      {
         devname = alcGetString(device, ALC_DEVICE_SPECIFIER);
      }

      Con::printf("| Device info for: %s ", devname);
   }

   alcGetIntegerv(device, ALC_MAJOR_VERSION, 1, &major);
   alcGetIntegerv(device, ALC_MINOR_VERSION, 1, &minor);
   Con::printf("| OpenAL Version: %d.%d", major, minor);

   if (device)
   {
      Con::printf("%s", alcGetString(device, ALC_EXTENSIONS));

      U32 err = alcGetError(device);
      if (err != ALC_NO_ERROR)
         Con::errorf("SFXALDevice - Error Retrieving ALC Extensions: %s", alcGetString(device, err));
   }
  
}

S32 SFXALDevice::getMaxSources()
{
   alGetError();
   
   ALCint nummono;
   alcGetIntegerv(mDevice, ALC_MONO_SOURCES, 1, &nummono);
   
   if(nummono == 0)
      nummono = getMaxSourcesOld();
   
   return nummono;
}

S32 SFXALDevice::getMaxSourcesOld()
{
   ALuint uiSource[256] = {};
   S32 sourceCount = 0;
   
   // clear errors.
   alGetError();
   
   for(sourceCount = 0; sourceCount < 256; sourceCount++)
   {
      alGenSources(1,&uiSource[sourceCount]);
      if(alGetError() != AL_NO_ERROR)
         break;
   }
   
   alDeleteSources(sourceCount, uiSource);
   if(alGetError() != AL_NO_ERROR)
   {
      for(U32 i = 0; i < 256; i++)
      {
         alDeleteSources(1,&uiSource[i]);
      }
   }
   
   return sourceCount;
   
}

SFXALDevice::SFXALDevice(U32 providerIndex)
   :  mContext(NULL),
      mDevice(NULL),
      mDistanceModel(SFXDistanceModelLinear),
      mDistanceFactor(1.0f),
      mRolloffFactor(1.0f),
      mUserRolloffFactor(1.0f)
{
   SFXProvider* p = SFXSystem::getProvider(providerIndex);

   mDevice = alcOpenDevice(p->getName());

   U32 err = alcGetError(mDevice);
   if (err != ALC_NO_ERROR)
      Con::errorf("SFXALDevice - Device Initialization Error: %s", alcGetString(mDevice, err));

   if (mDevice)
   {
      mContext = alcCreateContext(mDevice, NULL);

      if (mContext)
         alcMakeContextCurrent(mContext);

      if( err != ALC_NO_ERROR )
         Con::errorf( "SFXALDevice - Context Initialization Error: %s", alcGetString( mDevice, err ) );
   }

   AssertFatal( mDevice != NULL && mContext != NULL, "Failed to create OpenAL device and/or context!" );

   // Start the update thread.
   // TODO AsyncPeriodicUpdateThread support for Linux/Mac
#ifdef TORQUE_OS_WIN
   if( !Con::getBoolVariable( "$_forceAllMainThread" ) )
   {
      SFXInternal::gUpdateThread = new AsyncPeriodicUpdateThread
         ( "OpenAL Update Thread", SFXInternal::gBufferUpdateList,
           Con::getIntVariable( "$pref::SFX::updateInterval", SFXInternal::DEFAULT_UPDATE_INTERVAL ) );
      SFXInternal::gUpdateThread->start();
   }
#endif

   // alcIsExtensionPresent(mDevice, "ALC_EXT_EFX")

   printALInfo(mDevice);

   mMaxBuffers = getMaxSources();
}

//-----------------------------------------------------------------------------

SFXALDevice::~SFXALDevice()
{
   _releaseAllResources();

   ///cleanup of effects ends
   alcMakeContextCurrent( NULL );
	alcDestroyContext( mContext );
	alcCloseDevice( mDevice );
}

//-----------------------------------------------------------------------------

void SFXALDevice::enumerateProviders(Vector<SFXProvider*>& providerList)
{
   const ALCchar* devices;
   U32 index = 0;
   const ALCchar* defaultDeviceName;

   if (alcIsExtensionPresent(NULL, "ALC_ENUMERATE_ALL_EXT") == AL_TRUE)
   {
      devices = alcGetString(NULL, ALC_ALL_DEVICES_SPECIFIER);
      defaultDeviceName = alcGetString(NULL, ALC_DEFAULT_ALL_DEVICES_SPECIFIER);
   }
   else
   {
      devices = alcGetString(NULL, ALC_DEVICE_SPECIFIER);
      defaultDeviceName = alcGetString(NULL, ALC_DEFAULT_DEVICE_SPECIFIER);
   }

   const ALCchar* currentDevice = devices;

   while (*currentDevice != '\0')
   {
      SFXProvider* toAdd = new SFXProvider;
      toAdd->mName = String::ToString(currentDevice);
      toAdd->mIndex = index;
      toAdd->mDeviceType = Output;
      toAdd->mType = OpenAL;
      toAdd->mCreateDeviceInstanceDelegate = mCreateDeviceInstance;

      if (String::compare(currentDevice, defaultDeviceName) == 0)
         toAdd->mDefault = true;

      currentDevice += dStrlen(currentDevice) + 1;
      index++;

      providerList.push_back(toAdd);
   }

}

SFXBuffer* SFXALDevice::createBuffer( const ThreadSafeRef< SFXStream >& stream, SFXDescription* description )
{
   AssertFatal( stream, "SFXALDevice::createBuffer() - Got null stream!" );
   AssertFatal( description, "SFXALDevice::createBuffer() - Got null description!" );

   SFXALBuffer* buffer = SFXALBuffer::create(   stream,
                                                description, 
                                                mUseHardware );
   if ( !buffer )
      return NULL;

   _addBuffer( buffer );
   return buffer;
}

//-----------------------------------------------------------------------------

SFXVoice* SFXALDevice::createVoice( bool is3D, SFXBuffer *buffer )
{
   // Don't bother going any further if we've 
   // exceeded the maximum voices.
   if ( mVoices.size() >= mMaxBuffers )
      return NULL;

   AssertFatal( buffer, "SFXALDevice::createVoice() - Got null buffer!" );

   SFXALBuffer* alBuffer = dynamic_cast<SFXALBuffer*>( buffer );
   AssertFatal( alBuffer, "SFXALDevice::createVoice() - Got bad buffer!" );

   SFXALVoice* voice = SFXALVoice::create( this, alBuffer );
   if ( !voice )
      return NULL;

   _addVoice( voice );
	return voice;
}

//-----------------------------------------------------------------------------

void SFXALDevice::setListener( U32 index, const SFXListenerProperties& listener )
{
   if( index != 0 )
      return;

   // Torque and OpenAL are both right handed 
   // systems, so no coordinate flipping is needed.

   const MatrixF &transform = listener.getTransform();
   Point3F pos, tupple[2];
   transform.getColumn( 3, &pos );
   transform.getColumn( 1, &tupple[0] );
   transform.getColumn( 2, &tupple[1] );

   const VectorF &velocity = listener.getVelocity();

   alListenerfv( AL_POSITION, pos );
   alListenerfv( AL_VELOCITY, velocity );
   alListenerfv( AL_ORIENTATION, (const F32 *)&tupple[0] );
}

//-----------------------------------------------------------------------------

void SFXALDevice::setDistanceModel( SFXDistanceModel model )
{
   switch( model )
   {
      case SFXDistanceModelLinear:
         alDistanceModel( AL_LINEAR_DISTANCE_CLAMPED );
         if( mRolloffFactor != 1.0f )
            _setRolloffFactor( 1.0f ); // No rolloff on linear.
         break;
         
      case SFXDistanceModelLogarithmic:
         alDistanceModel( AL_INVERSE_DISTANCE_CLAMPED );
         if( mUserRolloffFactor != mRolloffFactor )
            _setRolloffFactor( mUserRolloffFactor );
         break;
         /// create a case for our exponential distance model
      case SFXDistanceModelExponent:
         alDistanceModel(AL_EXPONENT_DISTANCE_CLAMPED);
         if (mUserRolloffFactor != mRolloffFactor)
            _setRolloffFactor(mUserRolloffFactor);
         break;

      default:
         AssertWarn( false, "SFXALDevice::setDistanceModel - distance model not implemented" );
   }
   
   mDistanceModel = model;
}

//-----------------------------------------------------------------------------

void SFXALDevice::setDopplerFactor( F32 factor )
{
   alDopplerFactor( factor );
}

//-----------------------------------------------------------------------------

void SFXALDevice::_setRolloffFactor( F32 factor )
{
   mRolloffFactor = factor;
   
   for( U32 i = 0, num = mVoices.size(); i < num; ++ i )
      alSourcef( ( ( SFXALVoice* ) mVoices[ i ] )->mSourceName, AL_ROLLOFF_FACTOR, factor );
}

//-----------------------------------------------------------------------------

void SFXALDevice::setRolloffFactor( F32 factor )
{
   if( mDistanceModel == SFXDistanceModelLinear && factor != 1.0f )
      Con::errorf( "SFXALDevice::setRolloffFactor - rolloff factor <> 1.0f ignored in linear distance model" );
   else
      _setRolloffFactor( factor );
      
   mUserRolloffFactor = factor;
}

