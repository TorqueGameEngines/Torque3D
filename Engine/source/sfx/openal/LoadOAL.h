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

#ifndef _LOADOAL_H_
#define _LOADOAL_H_

#ifndef _PLATFORM_H_
#  include "platform/platform.h"
#endif

#if defined(TORQUE_OS_MAC)
#undef AL_ALEXT_PROTOTYPES
#  include <OpenAL/al.h>
#  include <OpenAL/alc.h>
#elif defined(TORQUE_OS_LINUX)
#  include <AL/al.h>
#  include <AL/alc.h>
#  include <AL/alext.h>
#  include <AL/efx.h>
#  include <AL/efx-presets.h>
#else
#  include <al/al.h>
#  include <al/alc.h>
#  include <AL/alext.h>
#  include <AL/efx-presets.h>
#endif

#ifndef ALAPIENTRY
#define ALAPIENTRY
#endif

#ifndef ALCAPIENTRY
#define ALCAPIENTRY
#endif

// Open AL Function table definition

#ifndef _OPENALFNTABLE
#define _OPENALFNTABLE

// AL 1.0 did not define the ALchar and ALCchar types, so define them here
// if they don't exist

#ifndef ALchar
#define ALchar char
#endif

#ifndef ALCchar
#define ALCchar char
#endif

typedef struct
{
	LPALENABLE                 alEnable;
	LPALDISABLE                alDisable;
	LPALISENABLED              alIsEnabled;
	LPALGETBOOLEAN             alGetBoolean;
	LPALGETINTEGER             alGetInteger;
	LPALGETFLOAT               alGetFloat;
	LPALGETDOUBLE              alGetDouble;
	LPALGETBOOLEANV				alGetBooleanv;
	LPALGETINTEGERV				alGetIntegerv;
	LPALGETFLOATV              alGetFloatv;
	LPALGETDOUBLEV             alGetDoublev;
	LPALGETSTRING              alGetString;
	LPALGETERROR               alGetError;
	LPALISEXTENSIONPRESENT		alIsExtensionPresent;
	LPALGETPROCADDRESS			alGetProcAddress;
	LPALGETENUMVALUE           alGetEnumValue;
	LPALLISTENERI              alListeneri;
	LPALLISTENERF				   alListenerf;
	LPALLISTENER3F				   alListener3f;
	LPALLISTENERFV				   alListenerfv;
	LPALGETLISTENERI			   alGetListeneri;
	LPALGETLISTENERF			   alGetListenerf;
	LPALGETLISTENER3F			   alGetListener3f;
	LPALGETLISTENERFV			   alGetListenerfv;
	LPALGENSOURCES				   alGenSources;
	LPALDELETESOURCES			   alDeleteSources;
	LPALISSOURCE				   alIsSource;
	LPALSOURCEI					   alSourcei;
	LPALSOURCEF					   alSourcef;
   LPALSOURCE3I				   alSource3i;
	LPALSOURCE3F				   alSource3f;
	LPALSOURCEFV				   alSourcefv;
	LPALGETSOURCEI				   alGetSourcei;
	LPALGETSOURCEF				   alGetSourcef;
	LPALGETSOURCEFV				alGetSourcefv;
	LPALSOURCEPLAYV				alSourcePlayv;
	LPALSOURCESTOPV				alSourceStopv;
	LPALSOURCEPLAY				   alSourcePlay;
	LPALSOURCEPAUSE				alSourcePause;
	LPALSOURCESTOP				   alSourceStop;
   LPALSOURCEREWIND           alSourceRewind;
	LPALGENBUFFERS				   alGenBuffers;
	LPALDELETEBUFFERS			   alDeleteBuffers;
	LPALISBUFFER				   alIsBuffer;
	LPALBUFFERDATA				   alBufferData;
	LPALGETBUFFERI				   alGetBufferi;
	LPALGETBUFFERF				   alGetBufferf;
	LPALSOURCEQUEUEBUFFERS		alSourceQueueBuffers;
	LPALSOURCEUNQUEUEBUFFERS	alSourceUnqueueBuffers;
	LPALDISTANCEMODEL			   alDistanceModel;
	LPALDOPPLERFACTOR			   alDopplerFactor;
	LPALDOPPLERVELOCITY			alDopplerVelocity;
	LPALCGETSTRING				   alcGetString;
	LPALCGETINTEGERV			   alcGetIntegerv;
	LPALCOPENDEVICE				alcOpenDevice;
	LPALCCLOSEDEVICE			   alcCloseDevice;
	LPALCCREATECONTEXT			alcCreateContext;
	LPALCMAKECONTEXTCURRENT		alcMakeContextCurrent;
	LPALCPROCESSCONTEXT			alcProcessContext;
	LPALCGETCURRENTCONTEXT		alcGetCurrentContext;
	LPALCGETCONTEXTSDEVICE		alcGetContextsDevice;
	LPALCSUSPENDCONTEXT			alcSuspendContext;
	LPALCDESTROYCONTEXT			alcDestroyContext;
	LPALCGETERROR				   alcGetError;
	LPALCISEXTENSIONPRESENT		alcIsExtensionPresent;
	LPALCGETPROCADDRESS			alcGetProcAddress;
	LPALCGETENUMVALUE			   alcGetEnumValue;
    
#if defined(AL_ALEXT_PROTOTYPES)
   LPALGENEFFECTS				   alGenEffects;
   LPALDELETEEFFECTS			   alDeleteEffects;
   LPALISEFFECT				   alIsEffect;
   LPALEFFECTI					   alEffecti;
   LPALEFFECTIV				   alEffectiv;
   LPALEFFECTF					   alEffectf;
   LPALEFFECTFV				   alEffectfv;
   LPALGETEFFECTI 				alGetEffecti;
   LPALGETEFFECTIV				alGetEffectiv;
   LPALGETEFFECTF				   alGetEffectf;
   LPALGETEFFECTFV				alGetEffectfv;
   LPALRELEASEALEFFECTS		   alReleaseEffects;
   LPALGENAUXILIARYEFFECTSLOTS			alGenAuxiliaryEffectSlots;
   LPALDELETEAUXILIARYEFFECTSLOTS		alDeleteAuxiliaryEffectSlots;
   LPALISAUXILIARYEFFECTSLOT				alIsAuxiliaryEffectSlot;
   LPALAUXILIARYEFFECTSLOTI				alAuxiliaryEffectSloti;
   LPALAUXILIARYEFFECTSLOTIV				alAuxiliaryEffectSlotiv;
   LPALAUXILIARYEFFECTSLOTF				alAuxiliaryEffectSlotf;
   LPALAUXILIARYEFFECTSLOTFV				alAuxiliaryEffectSlotfv;
   LPALGETAUXILIARYEFFECTSLOTI			alGetAuxiliaryEffectSloti;
   LPALGETAUXILIARYEFFECTSLOTIV			alGetAuxiliaryEffectSlotiv;
   LPALGETAUXILIARYEFFECTSLOTF			alGetAuxiliaryEffectSlotf;
   LPALGETAUXILIARYEFFECTSLOTFV			alGetAuxiliaryEffectSlotfv;
   LPALGENFILTERS         alGenFilters;
   LPALDELETEFILTERS      alDeleteFilters;
   LPALFILTERI            alFilteri;
   LPALCGETSTRINGISOFT alcGetStringiSOFT;
#endif

} OPENALFNTABLE, *LPOPENALFNTABLE;
#endif

ALboolean LoadOAL10Library(char *szOALFullPathName, LPOPENALFNTABLE lpOALFnTable);
ALvoid UnloadOAL10Library();

#endif // _LOADOAL_H_
