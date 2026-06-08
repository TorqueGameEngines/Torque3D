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

#define SFX_LOAD_AL_PROC(T, x) \
   (x) = FUNCTION_CAST(T, alGetProcAddress(#x)); \
   if (!(x)) Con::warnf("SFXALDevice - Failed to load " #x);

#define SFX_LOAD_ALC_PROC(T, x) \
   (x) = FUNCTION_CAST(T, alcGetProcAddress(mDevice, #x)); \
   if (!(x)) Con::warnf("SFXALDevice - Failed to load " #x);

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

void SFXALDevice::_initExtensions()
{
   // Device-level soft extensions — must be loaded before context creation
   if (alcIsExtensionPresent(mDevice, "ALC_SOFT_reopen_device"))
   {
      SFX_LOAD_ALC_PROC(LPALCREOPENDEVICESOFT, alcReopenDeviceSOFT);
      SFX_LOAD_ALC_PROC(LPALCRESETDEVICESOFT, alcResetDeviceSOFT);
      if (alcReopenDeviceSOFT && alcResetDeviceSOFT)
      {
         mHasSoftReopen = true;
         mCaps |= CAPS_HotReconnect;
      }
   }

   if (alcIsExtensionPresent(mDevice, "ALC_SOFT_HRTF"))
   {
      SFX_LOAD_ALC_PROC(LPALCGETSTRINGISOFT, alcGetStringiSOFT);
      if (alcGetStringiSOFT)
      {
         mHasSoftHRTF = true;
         mCaps |= CAPS_HRTF;
      }
   }

   if (alcIsExtensionPresent(mDevice, "ALC_SOFT_device_clock"))
   {
      SFX_LOAD_ALC_PROC(LPALCGETINTEGER64VSOFT, alcGetInteger64vSOFT);
      if (alcGetInteger64vSOFT)
         mCaps |= CAPS_DeviceClock;
   }

   if (alcIsExtensionPresent(mDevice, "ALC_EXT_disconnect"))
      mCaps |= CAPS_DisconnectDetect;

   // Context-level AL extensions — loaded after context is current
   if (alIsExtensionPresent("AL_EXT_float32"))
      mCaps |= CAPS_Float32;
   if (alIsExtensionPresent("AL_EXT_MCFORMATS"))
      mCaps |= CAPS_MonoStereo;
   if (alIsExtensionPresent("AL_SOFT_source_spatialize"))
      mCaps |= CAPS_SourceSpatialize;
}

void SFXALDevice::_initEFX()
{
   if (alcIsExtensionPresent(mDevice, "ALC_EXT_EFX") != AL_TRUE)
      return;

   // Load all EFX procs
   SFX_LOAD_AL_PROC(LPALGENEFFECTS, alGenEffects);
   SFX_LOAD_AL_PROC(LPALDELETEEFFECTS, alDeleteEffects);
   SFX_LOAD_AL_PROC(LPALISEFFECT, alIsEffect);
   SFX_LOAD_AL_PROC(LPALEFFECTI, alEffecti);
   SFX_LOAD_AL_PROC(LPALEFFECTIV, alEffectiv);
   SFX_LOAD_AL_PROC(LPALEFFECTF, alEffectf);
   SFX_LOAD_AL_PROC(LPALEFFECTFV, alEffectfv);
   SFX_LOAD_AL_PROC(LPALGETEFFECTI, alGetEffecti);
   SFX_LOAD_AL_PROC(LPALGETEFFECTIV, alGetEffectiv);
   SFX_LOAD_AL_PROC(LPALGETEFFECTF, alGetEffectf);
   SFX_LOAD_AL_PROC(LPALGETEFFECTFV, alGetEffectfv);
   SFX_LOAD_AL_PROC(LPALGENAUXILIARYEFFECTSLOTS, alGenAuxiliaryEffectSlots);
   SFX_LOAD_AL_PROC(LPALDELETEAUXILIARYEFFECTSLOTS, alDeleteAuxiliaryEffectSlots);
   SFX_LOAD_AL_PROC(LPALISAUXILIARYEFFECTSLOT, alIsAuxiliaryEffectSlot);
   SFX_LOAD_AL_PROC(LPALAUXILIARYEFFECTSLOTI, alAuxiliaryEffectSloti);
   SFX_LOAD_AL_PROC(LPALAUXILIARYEFFECTSLOTIV, alAuxiliaryEffectSlotiv);
   SFX_LOAD_AL_PROC(LPALAUXILIARYEFFECTSLOTF, alAuxiliaryEffectSlotf);
   SFX_LOAD_AL_PROC(LPALAUXILIARYEFFECTSLOTFV, alAuxiliaryEffectSlotfv);
   SFX_LOAD_AL_PROC(LPALGETAUXILIARYEFFECTSLOTI, alGetAuxiliaryEffectSloti);
   SFX_LOAD_AL_PROC(LPALGETAUXILIARYEFFECTSLOTIV, alGetAuxiliaryEffectSlotiv);
   SFX_LOAD_AL_PROC(LPALGETAUXILIARYEFFECTSLOTF, alGetAuxiliaryEffectSlotf);
   SFX_LOAD_AL_PROC(LPALGETAUXILIARYEFFECTSLOTFV, alGetAuxiliaryEffectSlotfv);
   SFX_LOAD_AL_PROC(LPALGENFILTERS, alGenFilters);
   SFX_LOAD_AL_PROC(LPALDELETEFILTERS, alDeleteFilters);
   SFX_LOAD_AL_PROC(LPALISFILTER, alIsFilter);
   SFX_LOAD_AL_PROC(LPALFILTERI, alFilteri);
   SFX_LOAD_AL_PROC(LPALFILTERIV, alFilteriv);
   SFX_LOAD_AL_PROC(LPALFILTERF, alFilterf);
   SFX_LOAD_AL_PROC(LPALFILTERFV, alFilterfv);
   SFX_LOAD_AL_PROC(LPALGETFILTERI, alGetFilteri);
   SFX_LOAD_AL_PROC(LPALGETFILTERIV, alGetFilteriv);
   SFX_LOAD_AL_PROC(LPALGETFILTERF, alGetFilterf);
   SFX_LOAD_AL_PROC(LPALGETFILTERFV, alGetFilterfv);

   // Verify the minimum set we can't live without
   if (!alGenEffects || !alDeleteEffects ||
      !alGenAuxiliaryEffectSlots || !alDeleteAuxiliaryEffectSlots ||
      !alAuxiliaryEffectSloti)
   {
      Con::warnf("SFXALDevice - EFX proc loading incomplete, disabling reverb");
      return;
   }

   mCaps |= CAPS_Reverb | CAPS_Occlusion;

   // Filters require their own procs
   if (alGenFilters && alDeleteFilters && alFilteri && alFilterf)
      mCaps |= CAPS_SourceFilters;

   // Probe individual effect type support and slot count
   _probeEFXEffectCaps();
}

void SFXALDevice::_probeEFXEffectCaps()
{
   // Probe which effect types this driver actually supports
   // by attempting to set each type on a temporary effect object.
   // Some drivers report ALC_EXT_EFX but don't implement all types.

   struct EffectProbe { ALenum alType; U32 cap; const char* name; };
   static const EffectProbe probes[] =
   {
      { AL_EFFECT_EAXREVERB,  CAPS_Reverb | CAPS_EXTReverb, "EAX Reverb"  },
      { AL_EFFECT_REVERB,     CAPS_Reverb,        "EAXReverb"  },
      { AL_EFFECT_EQUALIZER,  CAPS_EFX_EQ,        "Equalizer"  },
      { AL_EFFECT_COMPRESSOR, CAPS_EFX_Compressor,"Compressor" },
      { AL_EFFECT_ECHO,       CAPS_EFX_Echo,      "Echo"       },
      { AL_EFFECT_CHORUS,     CAPS_EFX_Chorus,    "Chorus"     },
      { AL_EFFECT_DISTORTION, CAPS_EFX_Distortion,"Distortion" },
      { AL_EFFECT_FLANGER,    CAPS_EFX_Flanger,   "Flanger"    },
   };

   ALuint testEffect = 0;
   alGenEffects(1, &testEffect);

   for (const EffectProbe& probe : probes)
   {
      alGetError();
      alEffecti(testEffect, AL_EFFECT_TYPE, probe.alType);
      if (alGetError() == AL_NO_ERROR)
         mCaps |= probe.cap;
   }

   alDeleteEffects(1, &testEffect);
   alGetError();

   // Probe aux slot count
   Vector<ALuint> slots;
   alGetError();
   while (slots.size() < 64)
   {
      ALuint slot = 0;
      alGenAuxiliaryEffectSlots(1, &slot);
      if (alGetError() != AL_NO_ERROR)
         break;
      slots.push_back(slot);
   }

   Con::setIntVariable("$pref::SFX::maxEffectSlots", (S32)slots.size());

   ALCint sends = 0;
   alcGetIntegerv(mDevice, ALC_MAX_AUXILIARY_SENDS, 1, &sends);
   Con::setIntVariable("$pref::SFX::maxSendsPerSource", (S32)sends);

   for (ALuint slot : slots)
      alDeleteAuxiliaryEffectSlots(1, &slot);
   alGetError();

   // Allocate the device-level global reverb slot
   alGenAuxiliaryEffectSlots(1, &mAuxSlot);
   if (alGetError() != AL_NO_ERROR)
   {
      Con::warnf("SFXALDevice - Failed to create primary EFX slot");
      mCaps &= ~(CAPS_Reverb | CAPS_Occlusion);
      mAuxSlot = 0;
   }
}

//----------------------------------------------------------------------------
// STATIC OPENAL FUNCTIONS
//----------------------------------------------------------------------------
void SFXALDevice::printALInfo(ALCdevice* device)
{
   if (!device)
      return;

   Con::printBlankLine();
   Con::printf("SFX Device Info:");
   Con::printf("|------------------------------------------------");

   // --- Device name ---
   const ALCchar* devname = alcIsExtensionPresent(device, "ALC_ENUMERATE_ALL_EXT")
      ? alcGetString(device, ALC_ALL_DEVICES_SPECIFIER)
      : alcGetString(device, ALC_DEVICE_SPECIFIER);
   Con::printf("| Device:       %s", devname);

   // --- OpenAL version ---
   ALCint major, minor;
   alcGetIntegerv(device, ALC_MAJOR_VERSION, 1, &major);
   alcGetIntegerv(device, ALC_MINOR_VERSION, 1, &minor);
   Con::printf("| OpenAL:       %d.%d", major, minor);

   // --- Audio format ---
   ALCint freq = 0;
   alcGetIntegerv(device, ALC_FREQUENCY, 1, &freq);
   Con::printf("| Sample Rate:  %d Hz", freq > 0 ? freq : 44100);
   Con::printf("| Bit Depth:    %d-bit", (mCaps & CAPS_Float32) ? 32 : 16);
   Con::printf("| Max Voices:   %d", mMaxBuffers);

   Con::printf("|------------------------------------------------");
   Con::printf("| Capabilities:");

   // --- Hot reconnect ---
   Con::printf("|   Hot Reconnect:     %s", (mCaps & CAPS_HotReconnect) ? "Yes" : "No");
   Con::printf("|   Disconnect Detect: %s", (mCaps & CAPS_DisconnectDetect) ? "Yes" : "No");
   Con::printf("|   Device Clock:      %s", (mCaps & CAPS_DeviceClock) ? "Yes" : "No");
   Con::printf("|   Multi-Listener:    %s", (mCaps & CAPS_MultiListener) ? "Yes" : "No");
   Con::printf("|   Float32 Playback:  %s", (mCaps & CAPS_Float32) ? "Yes" : "No");
   Con::printf("|   Multi-Channel:     %s", (mCaps & CAPS_MonoStereo) ? "Yes" : "No");
   Con::printf("|   Spatialize:        %s", (mCaps & CAPS_SourceSpatialize) ? "Yes" : "No");

   // --- HRTF ---
   Con::printf("|   HRTF:              %s", (mCaps & CAPS_HRTF) ? "Yes" : "No");
   if (mCaps & CAPS_HRTF)
   {
      ALCint hrtfStatus = 0;
      alcGetIntegerv(device, ALC_HRTF_STATUS_SOFT, 1, &hrtfStatus);

      const char* statusStr = "Unknown";
      switch (hrtfStatus)
      {
      case ALC_HRTF_DISABLED_SOFT:          statusStr = "Disabled";              break;
      case ALC_HRTF_ENABLED_SOFT:           statusStr = "Enabled";               break;
      case ALC_HRTF_DENIED_SOFT:            statusStr = "Denied by device";      break;
      case ALC_HRTF_REQUIRED_SOFT:          statusStr = "Required by device";    break;
      case ALC_HRTF_HEADPHONES_DETECTED_SOFT: statusStr = "Headphones detected"; break;
      case ALC_HRTF_UNSUPPORTED_FORMAT_SOFT:  statusStr = "Unsupported format";  break;
      }
      Con::printf("|     Status:  %s", statusStr);

      ALCint profileCount = 0;
      alcGetIntegerv(device, ALC_NUM_HRTF_SPECIFIERS_SOFT, 1, &profileCount);
      Con::printf("|     Profiles: %d", profileCount);

      if (alcGetStringiSOFT && profileCount > 0)
         for (ALCint i = 0; i < profileCount; i++)
            Con::printf("|       [%d] %s", i,
               alcGetStringiSOFT(device, ALC_HRTF_SPECIFIER_SOFT, i));

      bool use_hrtf = Con::getBoolVariable("$pref::SFX::useHRTF");
      if (use_hrtf && (mCaps & CAPS_HotReconnect))
      {
         ALCint attr[5];
         ALCint index = Con::getIntVariable("$pref::SFX::hrtfProfile");
         ALCint i;

         i = 0;
         attr[i++] = ALC_HRTF_SOFT;
         attr[i++] = ALC_TRUE;
         // load the default device hrtf.
         if (index >= 0 && index < profileCount)
         {
            attr[i++] = ALC_HRTF_ID_SOFT;
            attr[i++] = index;
         }
         attr[i] = 0;

         if (!alcResetDeviceSOFT(mDevice, attr))
         {
            Con::printf("Failed to reset device: %s", alcGetString(mDevice, alcGetError(mDevice)));
         }
      }
   }

   // --- EFX ---
   Con::printf("|   EFX Reverb:        %s", (mCaps & CAPS_Reverb) ? "Yes" : "No");
   if (mCaps & CAPS_Reverb)
   {
      Con::printf("|     EQ:          %s", (mCaps & CAPS_EFX_EQ) ? "Yes" : "No");
      Con::printf("|     Compressor:  %s", (mCaps & CAPS_EFX_Compressor) ? "Yes" : "No");
      Con::printf("|     Echo:        %s", (mCaps & CAPS_EFX_Echo) ? "Yes" : "No");
      Con::printf("|     Chorus:      %s", (mCaps & CAPS_EFX_Chorus) ? "Yes" : "No");
      Con::printf("|     Distortion:  %s", (mCaps & CAPS_EFX_Distortion) ? "Yes" : "No");
      Con::printf("|     Flanger:     %s", (mCaps & CAPS_EFX_Flanger) ? "Yes" : "No");
      Con::printf("|     Filters:     %s", (mCaps & CAPS_SourceFilters) ? "Yes" : "No");

      Con::printf("|     Effect Slots: %d",
         Con::getIntVariable("$pref::SFX::maxEffectSlots"));
      Con::printf("|     Sends/Source: %d",
         Con::getIntVariable("$pref::SFX::maxSendsPerSource"));
   }

   Con::printf("|------------------------------------------------");

   // --- Full extension list last so it doesn't bury the important info ---
   const ALchar* extStr = alcGetString(device, ALC_EXTENSIONS);
   if (extStr)
   {
      Con::printf("| ALC Extensions:");
      char* extCopy = dStrdup(extStr);
      char* token = dStrtok(extCopy, " ");
      while (token)
      {
         Con::printf("|   %s", token);
         token = dStrtok(NULL, " ");
      }
      dFree(extCopy);
   }

   Con::printf("|------------------------------------------------");
   Con::printBlankLine();

   U32 err = alcGetError(device);
   if (err != ALC_NO_ERROR)
      Con::errorf("SFXALDevice - ALC error after info query: %s",
         alcGetString(device, err));
  
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
      mHasSoftReopen(false),
      mHasSoftHRTF(false),
      mEffect(0),
      mAuxSlot(0)
{
   SFXProvider* p = SFXSystem::getProvider(providerIndex);

   mDevice = alcOpenDevice(p->getName());
   if (!mDevice)
   {
      Con::errorf("SFXALDevice - Failed to open '%s'", p->getName());
      return;
   }

   // Extensions that must be loaded before context creation
   _initExtensions();

   mContext = alcCreateContext(mDevice, NULL);
   if (!mContext)
   {
      Con::errorf("SFXALDevice - Failed to create context (error %d)",
         alcGetError(mDevice));
      alcCloseDevice(mDevice);
      mDevice = NULL;
      return;
   }

   alcMakeContextCurrent(mContext);

#ifdef TORQUE_OS_WIN

   if (!Con::getBoolVariable("$_forceAllMainThread"))
   {
      SFXInternal::gUpdateThread = new AsyncPeriodicUpdateThread(
         "OpenAL Update Thread", SFXInternal::gBufferUpdateList,
         Con::getIntVariable("$pref::SFX::updateInterval",
            SFXInternal::DEFAULT_UPDATE_INTERVAL));
      SFXInternal::gUpdateThread->start();
   }
#endif

   // Context is current — load context-level extensions and EFX
   _initExtensions();  // second pass picks up AL_* extensions now context is current
   _initEFX();

   // Read back what the device actually settled on
   ALCint freq = 0;
   alcGetIntegerv(mDevice, ALC_FREQUENCY, 1, &freq);
   Con::setIntVariable("$pref::SFX::frequency", freq > 0 ? freq : 44100);
   Con::setIntVariable("$pref::SFX::bitrate", (mCaps & CAPS_Float32) ? 32 : 16);

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

   /* Clear error state. */
   alGetError();

   if (alIsEffect(mEffect))
      alDeleteEffects(1, &mEffect);

   /* Create the effect object and check if we can do EAX reverb. */
   alGenEffects(1, &mEffect);

   // Map your engine's properties to EFX parameters.
   // Using EAX Reverb as an example:
   if (mCaps & CAPS_EXTReverb)
   {
      // Full EAX parameter set — panning vectors, LF params, modulation etc.
      alEffecti(mEffect, AL_EFFECT_TYPE, AL_EFFECT_EAXREVERB);
      if (alGetError() == AL_NO_ERROR)
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
   }
   else
   {
      // Standard reverb — subset of EAX, no panning/LF/modulation params
      alEffecti(mEffect, AL_EFFECT_TYPE, AL_EFFECT_REVERB);
      if (alGetError() == AL_NO_ERROR)
      {
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
   }

   if (alGetError() == AL_NO_ERROR)
      alAuxiliaryEffectSloti(mAuxSlot, AL_EFFECTSLOT_EFFECT, (ALint)mEffect);
   else
   {
      Con::warnf("SFXALDevice::setReverb - failed applying reverb parameters");
      if (alIsEffect(mEffect))
         alDeleteEffects(1, &mEffect);
      mEffect = 0;
   }
}

//-----------------------------------------------------------------------------

void SFXALDevice::setDopplerFactor( F32 factor )
{
   alDopplerFactor( factor );
}

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

bool SFXALDevice::isDeviceConnected()
{
   if (!mDevice)
      return false;

   // ALC_CONNECTED is a standard-ish extension, check it first
   if (alcIsExtensionPresent(mDevice, "ALC_EXT_disconnect") == AL_TRUE)
   {
      ALCint connected = ALC_FALSE;
      alcGetIntegerv(mDevice, ALC_CONNECTED, 1, &connected);

      if (connected == ALC_FALSE)
      {
         //SFXSystem::removeProvider(mDevice->getProvider());
      }

      return (connected == ALC_TRUE);
   }

   // If the extension isn't available, assume connected
   return true;
}

bool SFXALDevice::reconnectDevice(U32 providerIndex)
{
   if (!mDevice || !mContext)
   {
      Con::errorf("SFXALDevice::reconnectDevice - no active device/context to reconnect");
      return false;
   }

   SFXProvider* p = SFXSystem::getProvider(providerIndex);

   // If no new name given, reuse the current device name (i.e. reconnect same device)
   if (!p->getName() || p->getName()[0] == '\0')
   {
      Con::errorf("SFXALDevice::reconnectDevice - unsupported provider given.");
      return false;
   }

   Con::printf("SFXALDevice::reconnectDevice - reconnecting to '%s'", p->getName());

   // Fast path: use ALC_SOFT_reopen_device to swap device without losing context.
   // All sources/buffers remain valid, playback resumes automatically.
   if (mHasSoftReopen && alcReopenDeviceSOFT)
   {
      // Build attribute list matching current device settings
      ALCint attribs[] =
      {
         ALC_FREQUENCY,    smDeviceFrequency,
         ALC_MONO_SOURCES, mMaxBuffers,
         0
      };

      if (alcReopenDeviceSOFT(mDevice, p->getName(), attribs) == ALC_TRUE)
      {
         Con::printf("SFXALDevice::reconnectDevice - soft reopen succeeded");
         return true;
      }

      Con::warnf("SFXALDevice::reconnectDevice - soft reopen failed (error %d), "
         "falling back to full recreate", alcGetError(mDevice));
   }

   // Slow path: destroy context and reopen device from scratch.
   // SFXSystem::createDevice will handle transitioning sounds to virtual playback.
   Con::printf("SFXALDevice::reconnectDevice - performing full device recreate");

   alcMakeContextCurrent(NULL);
   alcDestroyContext(mContext);
   mContext = NULL;
   alcCloseDevice(mDevice);
   mDevice = NULL;
   return false;
}
