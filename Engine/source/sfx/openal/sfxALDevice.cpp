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

#include "AL/al.h"
#include "AL/alc.h"
#include "AL/efx.h"
#include "AL/alext.h"

#ifndef ALC_CONNECTED
#define ALC_CONNECTED 0x313
#endif

#ifndef ALC_DEVICE_CLOCK_SOFT
#define ALC_DEVICE_CLOCK_SOFT 0x1600
#endif

#ifndef ALC_DEVICE_LATENCY_SOFT
#define ALC_DEVICE_LATENCY_SOFT 0x1601
#endif

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#define FUNCTION_CAST(T, ptr) (union{void *p; T f;}){ptr}.f
#elif defined(__cplusplus)
#define FUNCTION_CAST(T, ptr) reinterpret_cast<T>(ptr)
#else
#define FUNCTION_CAST(T, ptr) (T)(ptr)
#endif

/* Effect object functions */
static LPALGENFILTERS alGenFilters{ nullptr };
static LPALDELETEFILTERS alDeleteFilters{ nullptr };
static LPALISFILTER alIsFilter{ nullptr };
static LPALFILTERF alFilterf{ nullptr };
static LPALFILTERFV alFilterfv{ nullptr };
static LPALFILTERI alFilteri{ nullptr };
static LPALFILTERIV alFilteriv{ nullptr };
static LPALGETFILTERF alGetFilterf{ nullptr };
static LPALGETFILTERFV alGetFilterfv{ nullptr };
static LPALGETFILTERI alGetFilteri{ nullptr };
static LPALGETFILTERIV alGetFilteriv{ nullptr };
static LPALGENEFFECTS alGenEffects{ nullptr };
static LPALDELETEEFFECTS alDeleteEffects{ nullptr };
static LPALISEFFECT alIsEffect{ nullptr };
static LPALEFFECTF alEffectf{ nullptr };
static LPALEFFECTFV alEffectfv{ nullptr };
static LPALEFFECTI alEffecti{ nullptr };
static LPALEFFECTIV alEffectiv{ nullptr };
static LPALGETEFFECTF alGetEffectf{ nullptr };
static LPALGETEFFECTFV alGetEffectfv{ nullptr };
static LPALGETEFFECTI alGetEffecti{ nullptr };
static LPALGETEFFECTIV alGetEffectiv{ nullptr };
static LPALGENAUXILIARYEFFECTSLOTS alGenAuxiliaryEffectSlots{ nullptr };
static LPALDELETEAUXILIARYEFFECTSLOTS alDeleteAuxiliaryEffectSlots{ nullptr };
static LPALISAUXILIARYEFFECTSLOT alIsAuxiliaryEffectSlot{ nullptr };
static LPALAUXILIARYEFFECTSLOTF alAuxiliaryEffectSlotf{ nullptr };
static LPALAUXILIARYEFFECTSLOTFV alAuxiliaryEffectSlotfv{ nullptr };
static LPALAUXILIARYEFFECTSLOTI alAuxiliaryEffectSloti{ nullptr };
static LPALAUXILIARYEFFECTSLOTIV alAuxiliaryEffectSlotiv{ nullptr };
static LPALGETAUXILIARYEFFECTSLOTF alGetAuxiliaryEffectSlotf{ nullptr };
static LPALGETAUXILIARYEFFECTSLOTFV alGetAuxiliaryEffectSlotfv{ nullptr };
static LPALGETAUXILIARYEFFECTSLOTI alGetAuxiliaryEffectSloti{ nullptr };
static LPALGETAUXILIARYEFFECTSLOTIV alGetAuxiliaryEffectSlotiv{ nullptr };
static LPALCGETSTRINGISOFT alcGetStringiSOFT{ nullptr };
static LPALCRESETDEVICESOFT alcResetDeviceSOFT{ nullptr };
static LPALCREOPENDEVICESOFT alcReopenDeviceSOFT{ nullptr };
static LPALCGETINTEGER64VSOFT alcGetInteger64vSOFT{ nullptr };

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
      const ALchar* extStr = alcGetString(device, ALC_EXTENSIONS);
      if (extStr)
      {
         Con::printf("| SFXALDevice - Supported ALC extensions:");

         // Copy to a modifiable string.
         char* extCopy = dStrdup(extStr);
         char* token = dStrtok(extCopy, " ");
         while (token)
         {
            Con::printf("| %s", token);
            token = dStrtok(NULL, " ");
         }

         dFree(extCopy);
      }

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
      mUserRolloffFactor(1.0f),
      mHasEFX(false),
      mEffect(0),
      mAuxSlot(0)
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

   // --- Capabilities ---
   if (alcIsExtensionPresent(mDevice, "ALC_EXT_EFX") == AL_TRUE)
      mCaps |= CAPS_Reverb | CAPS_Occlusion;
   if (alcIsExtensionPresent(mDevice, "ALC_SOFT_HRTF") == AL_TRUE)
      mCaps |= CAPS_HRTF;
   if (alIsExtensionPresent("AL_EXT_float32") == AL_TRUE)
      mCaps |= CAPS_Float32;
   if (alIsExtensionPresent("AL_EXT_MCFORMATS") == AL_TRUE)
      mCaps |= CAPS_MonoStereo;

   if (mCaps & CAPS_Reverb)
   {
#define LOAD_PROC(T, x)  ((x) = FUNCTION_CAST(T, alGetProcAddress(#x)))
      LOAD_PROC(LPALGENEFFECTS, alGenEffects);
      LOAD_PROC(LPALDELETEEFFECTS, alDeleteEffects);
      LOAD_PROC(LPALISEFFECT, alIsEffect);
      LOAD_PROC(LPALEFFECTI, alEffecti);
      LOAD_PROC(LPALEFFECTIV, alEffectiv);
      LOAD_PROC(LPALEFFECTF, alEffectf);
      LOAD_PROC(LPALEFFECTFV, alEffectfv);
      LOAD_PROC(LPALGETEFFECTI, alGetEffecti);
      LOAD_PROC(LPALGETEFFECTIV, alGetEffectiv);
      LOAD_PROC(LPALGETEFFECTF, alGetEffectf);
      LOAD_PROC(LPALGETEFFECTFV, alGetEffectfv);

      LOAD_PROC(LPALGENAUXILIARYEFFECTSLOTS, alGenAuxiliaryEffectSlots);
      LOAD_PROC(LPALDELETEAUXILIARYEFFECTSLOTS, alDeleteAuxiliaryEffectSlots);
      LOAD_PROC(LPALISAUXILIARYEFFECTSLOT, alIsAuxiliaryEffectSlot);
      LOAD_PROC(LPALAUXILIARYEFFECTSLOTI, alAuxiliaryEffectSloti);
      LOAD_PROC(LPALAUXILIARYEFFECTSLOTIV, alAuxiliaryEffectSlotiv);
      LOAD_PROC(LPALAUXILIARYEFFECTSLOTF, alAuxiliaryEffectSlotf);
      LOAD_PROC(LPALAUXILIARYEFFECTSLOTFV, alAuxiliaryEffectSlotfv);
      LOAD_PROC(LPALGETAUXILIARYEFFECTSLOTI, alGetAuxiliaryEffectSloti);
      LOAD_PROC(LPALGETAUXILIARYEFFECTSLOTIV, alGetAuxiliaryEffectSlotiv);
      LOAD_PROC(LPALGETAUXILIARYEFFECTSLOTF, alGetAuxiliaryEffectSlotf);
      LOAD_PROC(LPALGETAUXILIARYEFFECTSLOTFV, alGetAuxiliaryEffectSlotfv);
#undef LOAD_PROC

      // generate our auxiliary slot for the effects.
      alGenAuxiliaryEffectSlots(1, &mAuxSlot);
   }

   // --- Device frequency ---
   ALCint freq = 0;
   alcGetIntegerv(mDevice, ALC_FREQUENCY, 1, &freq);
   if (freq > 0)
      Con::setIntVariable("$pref::SFX::frequency", freq);
   else
      Con::setIntVariable("$pref::SFX::frequency", 44100); // default

   // --- Bitrate approximation ---
   U32 bitrate = (mCaps & CAPS_Float32) ? 32 : 16;
   Con::setIntVariable("$pref::SFX::bitrate", bitrate);

   printALInfo(mDevice);

   mMaxBuffers = getMaxSources();
   Con::setIntVariable("$pref::SFX::maxSoftwareBuffers", mMaxBuffers);
}

//-----------------------------------------------------------------------------

SFXALDevice::~SFXALDevice()
{
   _releaseAllResources();

   if (alIsEffect(mEffect))
   {
      alDeleteAuxiliaryEffectSlots(1, &mAuxSlot);
      alDeleteEffects(1, &mEffect);
   }

   ///cleanup of effects ends
   alcMakeContextCurrent( NULL );
	alcDestroyContext( mContext );
	alcCloseDevice( mDevice );
}

//-----------------------------------------------------------------------------

void SFXALDevice::enumerateProviders(Vector<SFXProvider*>& providerList)
{
   const ALCchar* devices;
   U32 index = providerList.size();
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

void SFXALDevice::setReverb(const SFXReverbProperties& r)
{
   if (!(mCaps & CAPS_Reverb))
      return;

   ALenum err;

   /* Clear error state. */
   alGetError();

   if (alIsEffect(mEffect))
      alDeleteEffects(1, &mEffect);

   /* Create the effect object and check if we can do EAX reverb. */
   alGenEffects(1, &mEffect);
   alEffecti(mEffect, AL_EFFECT_TYPE, AL_EFFECT_EAXREVERB);
   err = alGetError();

   // Map your engine's properties to EFX parameters.
   // Using EAX Reverb as an example:
   if (err == AL_NO_ERROR)
   {
      alEffectf(mEffect, AL_EAXREVERB_DENSITY, r.flDensity);
      alEffectf(mEffect, AL_EAXREVERB_DIFFUSION, r.flDiffusion);
      alEffectf(mEffect, AL_EAXREVERB_GAIN, r.flGain);
      alEffectf(mEffect, AL_EAXREVERB_GAINHF, r.flGainHF);
      alEffectf(mEffect, AL_EAXREVERB_GAINLF, r.flGainLF);
      alEffectf(mEffect, AL_EAXREVERB_DECAY_TIME, r.flDecayTime);
      alEffectf(mEffect, AL_EAXREVERB_DECAY_HFRATIO, r.flDecayHFRatio);
      alEffectf(mEffect, AL_EAXREVERB_DECAY_LFRATIO, r.flDecayLFRatio);

      alEffectf(mEffect, AL_EAXREVERB_REFLECTIONS_GAIN, r.flReflectionsGain);
      alEffectf(mEffect, AL_EAXREVERB_REFLECTIONS_DELAY, r.flReflectionsDelay);
      alEffectfv(mEffect, AL_EAXREVERB_REFLECTIONS_PAN, r.flReflectionsPan);

      alEffectf(mEffect, AL_EAXREVERB_LATE_REVERB_GAIN, r.flLateReverbGain);
      alEffectf(mEffect, AL_EAXREVERB_LATE_REVERB_DELAY, r.flLateReverbDelay);
      alEffectfv(mEffect, AL_EAXREVERB_LATE_REVERB_PAN, r.flLateReverbPan);

      alEffectf(mEffect, AL_EAXREVERB_ECHO_TIME, r.flEchoTime);
      alEffectf(mEffect, AL_EAXREVERB_ECHO_DEPTH, r.flEchoDepth);
      alEffectf(mEffect, AL_EAXREVERB_MODULATION_TIME, r.flModulationTime);
      alEffectf(mEffect, AL_EAXREVERB_MODULATION_DEPTH, r.flModulationDepth);

      alEffectf(mEffect, AL_EAXREVERB_AIR_ABSORPTION_GAINHF, r.flAirAbsorptionGainHF);
      alEffectf(mEffect, AL_EAXREVERB_HFREFERENCE, r.flHFReference);
      alEffectf(mEffect, AL_EAXREVERB_LFREFERENCE, r.flLFReference);
      alEffectf(mEffect, AL_EAXREVERB_ROOM_ROLLOFF_FACTOR, r.flRoomRolloffFactor);
      alEffecti(mEffect, AL_EAXREVERB_DECAY_HFLIMIT, r.iDecayHFLimit);
   }
   else
   {
      alEffecti(mEffect, AL_EFFECT_TYPE, AL_EFFECT_REVERB);

      alEffectf(mEffect, AL_REVERB_DENSITY, r.flDensity);
      alEffectf(mEffect, AL_REVERB_DIFFUSION, r.flDiffusion);
      alEffectf(mEffect, AL_REVERB_GAIN, r.flGain);
      alEffectf(mEffect, AL_REVERB_GAINHF, r.flGainHF);
      alEffectf(mEffect, AL_REVERB_DECAY_TIME, r.flDecayTime);
      alEffectf(mEffect, AL_REVERB_DECAY_HFRATIO, r.flDecayHFRatio);
      alEffectf(mEffect, AL_REVERB_REFLECTIONS_GAIN, r.flReflectionsGain);
      alEffectf(mEffect, AL_REVERB_REFLECTIONS_DELAY, r.flReflectionsDelay);
      alEffectf(mEffect, AL_REVERB_LATE_REVERB_GAIN, r.flLateReverbGain);
      alEffectf(mEffect, AL_REVERB_LATE_REVERB_DELAY, r.flLateReverbDelay);
      alEffectf(mEffect, AL_REVERB_AIR_ABSORPTION_GAINHF, r.flAirAbsorptionGainHF);
      alEffectf(mEffect, AL_REVERB_ROOM_ROLLOFF_FACTOR, r.flRoomRolloffFactor);
      alEffecti(mEffect, AL_REVERB_DECAY_HFLIMIT, r.iDecayHFLimit);
   }

   err = alGetError();
   if (err != AL_NO_ERROR)
   {
      if (alIsEffect(mEffect))
         alDeleteEffects(1, &mEffect);
   }
   else
   {
      // Bind updated effect to slot
      alAuxiliaryEffectSloti(mAuxSlot, AL_EFFECTSLOT_EFFECT, (ALint)mEffect);
   }
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

void SFXALDevice::setSpeedOfSound(F32 speedOfSound)
{
   alSpeedOfSound(speedOfSound);
}
