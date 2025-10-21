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

//#define LOAD_PROC(x) x = reinterpret_cast<decltype(x)>(reinterpret_cast<void*>( alcGetProcAddress(mDevice, #x)))
//
//      if (alcIsExtensionPresent(mDevice, "ALC_EXT_EFX"))
//      {
//         LOAD_PROC(alGenFilters);
//         LOAD_PROC(alDeleteFilters);
//         LOAD_PROC(alIsFilter);
//         LOAD_PROC(alFilterf);
//         LOAD_PROC(alFilterfv);
//         LOAD_PROC(alFilteri);
//         LOAD_PROC(alFilteriv);
//         LOAD_PROC(alGetFilterf);
//         LOAD_PROC(alGetFilterfv);
//         LOAD_PROC(alGetFilteri);
//         LOAD_PROC(alGetFilteriv);
//         LOAD_PROC(alGenEffects);
//         LOAD_PROC(alDeleteEffects);
//         LOAD_PROC(alIsEffect);
//         LOAD_PROC(alEffectf);
//         LOAD_PROC(alEffectfv);
//         LOAD_PROC(alEffecti);
//         LOAD_PROC(alEffectiv);
//         LOAD_PROC(alGetEffectf);
//         LOAD_PROC(alGetEffectfv);
//         LOAD_PROC(alGetEffecti);
//         LOAD_PROC(alGetEffectiv);
//         LOAD_PROC(alGenAuxiliaryEffectSlots);
//         LOAD_PROC(alDeleteAuxiliaryEffectSlots);
//         LOAD_PROC(alIsAuxiliaryEffectSlot);
//         LOAD_PROC(alAuxiliaryEffectSlotf);
//         LOAD_PROC(alAuxiliaryEffectSlotfv);
//         LOAD_PROC(alAuxiliaryEffectSloti);
//         LOAD_PROC(alAuxiliaryEffectSlotiv);
//         LOAD_PROC(alGetAuxiliaryEffectSlotf);
//         LOAD_PROC(alGetAuxiliaryEffectSlotfv);
//         LOAD_PROC(alGetAuxiliaryEffectSloti);
//         LOAD_PROC(alGetAuxiliaryEffectSlotiv);
//      }

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

#if defined(AL_ALEXT_PROTOTYPES)
   dMemset(effectSlot, 0, sizeof(effectSlot));
   dMemset(effect, 0, sizeof(effect));
   uLoop = 0;
#endif

   printALInfo(mDevice);

   mMaxBuffers = getMaxSources();
}

//-----------------------------------------------------------------------------

//SFXALDevice::SFXALDevice(  SFXProvider *provider, 
//                           const OPENALFNTABLE &openal, 
//                           String name, 
//                           bool useHardware, 
//                           S32 maxBuffers )
//   :  Parent( name, provider, useHardware, maxBuffers ),
//      mOpenAL( openal ), 
//      mContext( NULL ),
//      mDevice( NULL ),
//      mDistanceModel(SFXDistanceModelLinear),
//      mDistanceFactor(1.0f),
//      mRolloffFactor( 1.0f ),
//      mUserRolloffFactor(1.0f)
//{
//   mMaxBuffers = getMax( maxBuffers, 8 );
//
//   // TODO: The OpenAL device doesn't set the primary buffer
//   // $pref::SFX::frequency or $pref::SFX::bitrate!
//   //check auxiliary device sends 4 and add them to the device
//   ALint attribs[4] = { 0 };
//#if defined(AL_ALEXT_PROTOTYPES)
//   ALCint iSends = 0;
//   attribs[0] = ALC_MAX_AUXILIARY_SENDS;
//#endif
//   attribs[1] = 4;
//
//   mDevice = alcOpenDevice( name );
//   U32 err = alcGetError(mDevice);
//   if (err != ALC_NO_ERROR)
//      Con::errorf("SFXALDevice - Device Initialization Error: %s", alcGetString(mDevice, err));
//
//   if( mDevice ) 
//   {
//      mContext = alcCreateContext( mDevice, attribs );
//
//      if( mContext ) 
//         alcMakeContextCurrent( mContext );
//
//#define LOAD_PROC(x) x = reinterpret_cast<decltype(x)>(reinterpret_cast<void*>( alcGetProcAddress(mDevice, #x)))
//
//      if (alcIsExtensionPresent(mDevice, "ALC_EXT_EFX"))
//      {
//         LOAD_PROC(alGenFilters);
//         LOAD_PROC(alDeleteFilters);
//         LOAD_PROC(alIsFilter);
//         LOAD_PROC(alFilterf);
//         LOAD_PROC(alFilterfv);
//         LOAD_PROC(alFilteri);
//         LOAD_PROC(alFilteriv);
//         LOAD_PROC(alGetFilterf);
//         LOAD_PROC(alGetFilterfv);
//         LOAD_PROC(alGetFilteri);
//         LOAD_PROC(alGetFilteriv);
//         LOAD_PROC(alGenEffects);
//         LOAD_PROC(alDeleteEffects);
//         LOAD_PROC(alIsEffect);
//         LOAD_PROC(alEffectf);
//         LOAD_PROC(alEffectfv);
//         LOAD_PROC(alEffecti);
//         LOAD_PROC(alEffectiv);
//         LOAD_PROC(alGetEffectf);
//         LOAD_PROC(alGetEffectfv);
//         LOAD_PROC(alGetEffecti);
//         LOAD_PROC(alGetEffectiv);
//         LOAD_PROC(alGenAuxiliaryEffectSlots);
//         LOAD_PROC(alDeleteAuxiliaryEffectSlots);
//         LOAD_PROC(alIsAuxiliaryEffectSlot);
//         LOAD_PROC(alAuxiliaryEffectSlotf);
//         LOAD_PROC(alAuxiliaryEffectSlotfv);
//         LOAD_PROC(alAuxiliaryEffectSloti);
//         LOAD_PROC(alAuxiliaryEffectSlotiv);
//         LOAD_PROC(alGetAuxiliaryEffectSlotf);
//         LOAD_PROC(alGetAuxiliaryEffectSlotfv);
//         LOAD_PROC(alGetAuxiliaryEffectSloti);
//         LOAD_PROC(alGetAuxiliaryEffectSlotiv);
//      }
//#undef LOAD_PROC
//
//#if defined(AL_ALEXT_PROTOTYPES)
//       alcGetIntegerv(mDevice, ALC_MAX_AUXILIARY_SENDS, 1, &iSends);
//#endif
//       err = alcGetError( mDevice );
//      
//      if( err != ALC_NO_ERROR )
//         Con::errorf( "SFXALDevice - Context Initialization Error: %s", alcGetString( mDevice, err ) );
//   }
//
//   AssertFatal( mDevice != NULL && mContext != NULL, "Failed to create OpenAL device and/or context!" );
//
//   // Start the update thread.
//   // TODO AsyncPeriodicUpdateThread support for Linux/Mac
//#ifdef TORQUE_OS_WIN
//   if( !Con::getBoolVariable( "$_forceAllMainThread" ) )
//   {
//      SFXInternal::gUpdateThread = new AsyncPeriodicUpdateThread
//         ( "OpenAL Update Thread", SFXInternal::gBufferUpdateList,
//           Con::getIntVariable( "$pref::SFX::updateInterval", SFXInternal::DEFAULT_UPDATE_INTERVAL ) );
//      SFXInternal::gUpdateThread->start();
//   }
//#endif
//
//#if defined(AL_ALEXT_PROTOTYPES)
//   dMemset(effectSlot, 0, sizeof(effectSlot));
//   dMemset(effect, 0, sizeof(effect));
//   uLoop = 0;
//#endif
//
//   printALInfo(mDevice);
//   
//
//   mMaxBuffers = getMaxSources();
//
//   // this should be max sources.
//   Con::printf("| Max Sources: %d", mMaxBuffers);
//
//}

//-----------------------------------------------------------------------------

SFXALDevice::~SFXALDevice()
{
   _releaseAllResources();
   ///cleanup our effects
#if defined(AL_ALEXT_PROTOTYPES)
   alDeleteAuxiliaryEffectSlots(4, effectSlot);
   alDeleteEffects(2, effect);
#endif
   ///cleanup of effects ends
   alcMakeContextCurrent( NULL );
	alcDestroyContext( mContext );
	alcCloseDevice( mDevice );
}

//-----------------------------------------------------------------------------

void SFXALDevice::enumerateProviders(Vector<SFXProvider*>& providerList)
{
   ALCdevice* device;
   ALCcontext* context;

   const ALCchar* devices;
   U32 index = 0;
   const ALCchar* defaultDeviceName;
   const ALCchar* actualDeviceName;

   /*device = alcOpenDevice(NULL);

   if (!device)
   {
      Con::errorf("Failed to open OpenAL Audio Device");
      return;
   }

   context = alcCreateContext(device, NULL);
   alcMakeContextCurrent(context);*/

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
   ///Pass a unit size to openal, 1.0 assumes 1 meter to 1 game unit.
   ///Crucial for air absorbtion calculations.
#if defined(AL_ALEXT_PROTOTYPES)
   alListenerf(AL_METERS_PER_UNIT, 1.0f);
#endif
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

#if defined(AL_ALEXT_PROTOTYPES)
void SFXALDevice::openSlots()
{
   for (uLoop = 0; uLoop < 4; uLoop++)
   {
      alGenAuxiliaryEffectSlots(1, &effectSlot[uLoop]);
   }

   for (uLoop = 0; uLoop < 2; uLoop++)
   {
      alGenEffects(1, &effect[uLoop]);
   }
   ///debug string output so we know our slots are open
   Platform::outputDebugString("Slots Open");
}

///create reverb effect
void SFXALDevice::setReverb(const SFXReverbProperties& reverb)
{
   ///output a debug string so we know each time the reverb changes
   Platform::outputDebugString("Updated");

   ///load an efxeaxreverb default and add our values from
   ///sfxreverbproperties to it
   EFXEAXREVERBPROPERTIES prop = EFX_REVERB_PRESET_GENERIC;

   prop.flDensity = reverb.flDensity;
   prop.flDiffusion = reverb.flDiffusion;
   prop.flGain = reverb.flGain;
   prop.flGainHF = reverb.flGainHF;
   prop.flGainLF = reverb.flGainLF;
   prop.flDecayTime = reverb.flDecayTime;
   prop.flDecayHFRatio = reverb.flDecayHFRatio;
   prop.flDecayLFRatio = reverb.flDecayLFRatio;
   prop.flReflectionsGain = reverb.flReflectionsGain;
   prop.flReflectionsDelay = reverb.flReflectionsDelay;
   prop.flLateReverbGain = reverb.flLateReverbGain;
   prop.flLateReverbDelay = reverb.flLateReverbDelay;
   prop.flEchoTime = reverb.flEchoTime;
   prop.flEchoDepth = reverb.flEchoDepth;
   prop.flModulationTime = reverb.flModulationTime;
   prop.flModulationDepth = reverb.flModulationDepth;
   prop.flAirAbsorptionGainHF = reverb.flAirAbsorptionGainHF;
   prop.flHFReference = reverb.flHFReference;
   prop.flLFReference = reverb.flLFReference;
   prop.flRoomRolloffFactor = reverb.flRoomRolloffFactor;
   prop.iDecayHFLimit = reverb.iDecayHFLimit;

   if (alGetEnumValue("AL_EFFECT_EAXREVERB") != 0)
   {

      /// EAX Reverb is available. Set the EAX effect type

      alEffecti(effect[0], AL_EFFECT_TYPE, AL_EFFECT_EAXREVERB);

      ///add our values to the setup of the reverb

      alEffectf(effect[0], AL_EAXREVERB_DENSITY, prop.flDensity);
      alEffectf(effect[0], AL_EAXREVERB_DIFFUSION, prop.flDiffusion);
      alEffectf(effect[0], AL_EAXREVERB_GAIN, prop.flGain);
      alEffectf(effect[0], AL_EAXREVERB_GAINHF, prop.flGainHF);
      alEffectf(effect[0], AL_EAXREVERB_GAINLF, prop.flGainLF);
      alEffectf(effect[0], AL_EAXREVERB_DECAY_TIME, prop.flDecayTime);
      alEffectf(effect[0], AL_EAXREVERB_DECAY_HFRATIO, prop.flDecayHFRatio);
      alEffectf(effect[0], AL_EAXREVERB_DECAY_LFRATIO, prop.flDecayLFRatio);
      alEffectf(effect[0], AL_EAXREVERB_REFLECTIONS_GAIN, prop.flReflectionsGain);
      alEffectf(effect[0], AL_EAXREVERB_REFLECTIONS_DELAY, prop.flReflectionsDelay);
      alEffectf(effect[0], AL_EAXREVERB_LATE_REVERB_GAIN, prop.flLateReverbGain);
      alEffectf(effect[0], AL_EAXREVERB_LATE_REVERB_DELAY, prop.flLateReverbDelay);
      alEffectf(effect[0], AL_EAXREVERB_ECHO_TIME, prop.flEchoTime);
      alEffectf(effect[0], AL_EAXREVERB_ECHO_DEPTH, prop.flEchoDepth);
      alEffectf(effect[0], AL_EAXREVERB_MODULATION_TIME, prop.flModulationTime);
      alEffectf(effect[0], AL_EAXREVERB_MODULATION_DEPTH, prop.flModulationDepth);
      alEffectf(effect[0], AL_EAXREVERB_AIR_ABSORPTION_GAINHF, prop.flAirAbsorptionGainHF);
      alEffectf(effect[0], AL_EAXREVERB_HFREFERENCE, prop.flHFReference);
      alEffectf(effect[0], AL_EAXREVERB_LFREFERENCE, prop.flLFReference);
      alEffectf(effect[0], AL_EAXREVERB_ROOM_ROLLOFF_FACTOR, prop.flRoomRolloffFactor);
      alEffecti(effect[0], AL_EAXREVERB_DECAY_HFLIMIT, prop.iDecayHFLimit);
      alAuxiliaryEffectSloti(1, AL_EFFECTSLOT_EFFECT, effect[0]);
      Platform::outputDebugString("eax reverb properties set");

   }
   else
   {

      /// No EAX Reverb. Set the standard reverb effect
      alEffecti(effect[0], AL_EFFECT_TYPE, AL_EFFECT_REVERB);

      alEffectf(effect[0], AL_REVERB_DENSITY, prop.flDensity);
      alEffectf(effect[0], AL_REVERB_DIFFUSION, prop.flDiffusion);
      alEffectf(effect[0], AL_REVERB_GAIN, prop.flGain);
      alEffectf(effect[0], AL_REVERB_GAINHF, prop.flGainHF);
      alEffectf(effect[0], AL_REVERB_DECAY_TIME, prop.flDecayTime);
      alEffectf(effect[0], AL_REVERB_DECAY_HFRATIO, prop.flDecayHFRatio);
      alEffectf(effect[0], AL_REVERB_REFLECTIONS_GAIN, prop.flReflectionsGain);
      alEffectf(effect[0], AL_REVERB_REFLECTIONS_DELAY, prop.flReflectionsDelay);
      alEffectf(effect[0], AL_REVERB_LATE_REVERB_GAIN, prop.flLateReverbGain);
      alEffectf(effect[0], AL_REVERB_LATE_REVERB_DELAY, prop.flLateReverbDelay);
      alEffectf(effect[0], AL_REVERB_AIR_ABSORPTION_GAINHF, prop.flAirAbsorptionGainHF);
      alEffectf(effect[0], AL_REVERB_ROOM_ROLLOFF_FACTOR, prop.flRoomRolloffFactor);
      alEffecti(effect[0], AL_REVERB_DECAY_HFLIMIT, prop.iDecayHFLimit);
      alAuxiliaryEffectSloti(1, AL_EFFECTSLOT_EFFECT, effect[0]);

   }

}
#endif
