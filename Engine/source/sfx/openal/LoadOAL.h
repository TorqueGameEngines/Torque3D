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
#include "platform/platform.h"
#endif

#ifndef _TVECTOR_H_
#include "core/util/tVector.h"
#endif

#ifndef _PATH_H_
#include "core/util/path.h"
#endif

// Since openal is deprecated and we pack the lib into the mac bundle, all
// platforms now support all of these.
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alext.h>
#include <AL/efx.h>
#include <AL/efx-presets.h>

#ifndef _OPENALFNTABLE
#define _OPENALFNTABLE

#if defined(TORQUE_OS_WIN)
#include <windows.h>
#define LIB_HANDLE HINSTANCE
#define LOAD_LIBRARY(path) LoadLibraryA(path)
#define GET_PROC_ADDRESS(lib, name) GetProcAddress(lib, name)
#define CLOSE_LIBRARY(lib) FreeLibrary(lib)
#define LIB_EXTENSION L".dll"
#else
#include <dlfcn.h>
#define LIB_HANDLE void*
#define LOAD_LIBRARY(path) dlopen(path, RTLD_LAZY)
#define GET_PROC_ADDRESS(lib, name) dlsym(lib, name)
#define CLOSE_LIBRARY(lib) dlclose(lib)
#ifdef __APPLE__
#define LIB_EXTENSION ".dylib"
#else
#define LIB_EXTENSION ".so"
#endif
#endif

constexpr auto MakeALCVer(int major, int minor) noexcept -> int {
   return (major << 8) | minor;
}

#ifndef ALAPIENTRY
#define ALAPIENTRY
#endif

#ifndef ALCAPIENTRY
#define ALCAPIENTRY
#endif

// AL 1.0 did not define the ALchar and ALCchar types, so define them here
// if they don't exist

#ifndef ALchar
#define ALchar char
#endif

#ifndef ALCchar
#define ALCchar char
#endif

struct OPENALFNTABLE
{
   LPALCCREATECONTEXT alcCreateContext{ nullptr };
   LPALCMAKECONTEXTCURRENT alcMakeContextCurrent{ nullptr };
   LPALCPROCESSCONTEXT alcProcessContext{ nullptr };
   LPALCSUSPENDCONTEXT alcSuspendContext{ nullptr };
   LPALCDESTROYCONTEXT alcDestroyContext{ nullptr };
   LPALCGETCURRENTCONTEXT alcGetCurrentContext{ nullptr };
   LPALCGETCONTEXTSDEVICE alcGetContextsDevice{ nullptr };
   LPALCOPENDEVICE alcOpenDevice{ nullptr };
   LPALCCLOSEDEVICE alcCloseDevice{ nullptr };
   LPALCGETERROR alcGetError{ nullptr };
   LPALCISEXTENSIONPRESENT alcIsExtensionPresent{ nullptr };
   LPALCGETPROCADDRESS alcGetProcAddress{ nullptr };
   LPALCGETENUMVALUE alcGetEnumValue{ nullptr };
   LPALCGETSTRING alcGetString{ nullptr };
   LPALCGETINTEGERV alcGetIntegerv{ nullptr };
   LPALCCAPTUREOPENDEVICE alcCaptureOpenDevice{ nullptr };
   LPALCCAPTURECLOSEDEVICE alcCaptureCloseDevice{ nullptr };
   LPALCCAPTURESTART alcCaptureStart{ nullptr };
   LPALCCAPTURESTOP alcCaptureStop{ nullptr };
   LPALCCAPTURESAMPLES alcCaptureSamples{ nullptr };

   PFNALCSETTHREADCONTEXTPROC alcSetThreadContext{ nullptr };
   PFNALCGETTHREADCONTEXTPROC alcGetThreadContext{ nullptr };

   LPALENABLE alEnable{ nullptr };
   LPALDISABLE alDisable{ nullptr };
   LPALISENABLED alIsEnabled{ nullptr };
   LPALGETSTRING alGetString{ nullptr };
   LPALGETBOOLEANV alGetBooleanv{ nullptr };
   LPALGETINTEGERV alGetIntegerv{ nullptr };
   LPALGETFLOATV alGetFloatv{ nullptr };
   LPALGETDOUBLEV alGetDoublev{ nullptr };
   LPALGETBOOLEAN alGetBoolean{ nullptr };
   LPALGETINTEGER alGetInteger{ nullptr };
   LPALGETFLOAT alGetFloat{ nullptr };
   LPALGETDOUBLE alGetDouble{ nullptr };
   LPALGETERROR alGetError{ nullptr };
   LPALISEXTENSIONPRESENT alIsExtensionPresent{ nullptr };
   LPALGETPROCADDRESS alGetProcAddress{ nullptr };
   LPALGETENUMVALUE alGetEnumValue{ nullptr };
   LPALLISTENERF alListenerf{ nullptr };
   LPALLISTENER3F alListener3f{ nullptr };
   LPALLISTENERFV alListenerfv{ nullptr };
   LPALLISTENERI alListeneri{ nullptr };
   LPALLISTENER3I alListener3i{ nullptr };
   LPALLISTENERIV alListeneriv{ nullptr };
   LPALGETLISTENERF alGetListenerf{ nullptr };
   LPALGETLISTENER3F alGetListener3f{ nullptr };
   LPALGETLISTENERFV alGetListenerfv{ nullptr };
   LPALGETLISTENERI alGetListeneri{ nullptr };
   LPALGETLISTENER3I alGetListener3i{ nullptr };
   LPALGETLISTENERIV alGetListeneriv{ nullptr };
   LPALGENSOURCES alGenSources{ nullptr };
   LPALDELETESOURCES alDeleteSources{ nullptr };
   LPALISSOURCE alIsSource{ nullptr };
   LPALSOURCEF alSourcef{ nullptr };
   LPALSOURCE3F alSource3f{ nullptr };
   LPALSOURCEFV alSourcefv{ nullptr };
   LPALSOURCEI alSourcei{ nullptr };
   LPALSOURCE3I alSource3i{ nullptr };
   LPALSOURCEIV alSourceiv{ nullptr };
   LPALGETSOURCEF alGetSourcef{ nullptr };
   LPALGETSOURCE3F alGetSource3f{ nullptr };
   LPALGETSOURCEFV alGetSourcefv{ nullptr };
   LPALGETSOURCEI alGetSourcei{ nullptr };
   LPALGETSOURCE3I alGetSource3i{ nullptr };
   LPALGETSOURCEIV alGetSourceiv{ nullptr };
   LPALSOURCEPLAYV alSourcePlayv{ nullptr };
   LPALSOURCESTOPV alSourceStopv{ nullptr };
   LPALSOURCEREWINDV alSourceRewindv{ nullptr };
   LPALSOURCEPAUSEV alSourcePausev{ nullptr };
   LPALSOURCEPLAY alSourcePlay{ nullptr };
   LPALSOURCESTOP alSourceStop{ nullptr };
   LPALSOURCEREWIND alSourceRewind{ nullptr };
   LPALSOURCEPAUSE alSourcePause{ nullptr };
   LPALSOURCEQUEUEBUFFERS alSourceQueueBuffers{ nullptr };
   LPALSOURCEUNQUEUEBUFFERS alSourceUnqueueBuffers{ nullptr };
   LPALGENBUFFERS alGenBuffers{ nullptr };
   LPALDELETEBUFFERS alDeleteBuffers{ nullptr };
   LPALISBUFFER alIsBuffer{ nullptr };
   LPALBUFFERF alBufferf{ nullptr };
   LPALBUFFER3F alBuffer3f{ nullptr };
   LPALBUFFERFV alBufferfv{ nullptr };
   LPALBUFFERI alBufferi{ nullptr };
   LPALBUFFER3I alBuffer3i{ nullptr };
   LPALBUFFERIV alBufferiv{ nullptr };
   LPALGETBUFFERF alGetBufferf{ nullptr };
   LPALGETBUFFER3F alGetBuffer3f{ nullptr };
   LPALGETBUFFERFV alGetBufferfv{ nullptr };
   LPALGETBUFFERI alGetBufferi{ nullptr };
   LPALGETBUFFER3I alGetBuffer3i{ nullptr };
   LPALGETBUFFERIV alGetBufferiv{ nullptr };
   LPALBUFFERDATA alBufferData{ nullptr };
   LPALDOPPLERFACTOR alDopplerFactor{ nullptr };
   LPALDOPPLERVELOCITY alDopplerVelocity{ nullptr };
   LPALSPEEDOFSOUND alSpeedOfSound{ nullptr };
   LPALDISTANCEMODEL alDistanceModel{ nullptr };

   /* Functions to load after first context creation. */
   LPALGENFILTERS alGenFilters{ nullptr };
   LPALDELETEFILTERS alDeleteFilters{ nullptr };
   LPALISFILTER alIsFilter{ nullptr };
   LPALFILTERF alFilterf{ nullptr };
   LPALFILTERFV alFilterfv{ nullptr };
   LPALFILTERI alFilteri{ nullptr };
   LPALFILTERIV alFilteriv{ nullptr };
   LPALGETFILTERF alGetFilterf{ nullptr };
   LPALGETFILTERFV alGetFilterfv{ nullptr };
   LPALGETFILTERI alGetFilteri{ nullptr };
   LPALGETFILTERIV alGetFilteriv{ nullptr };
   LPALGENEFFECTS alGenEffects{ nullptr };
   LPALDELETEEFFECTS alDeleteEffects{ nullptr };
   LPALISEFFECT alIsEffect{ nullptr };
   LPALEFFECTF alEffectf{ nullptr };
   LPALEFFECTFV alEffectfv{ nullptr };
   LPALEFFECTI alEffecti{ nullptr };
   LPALEFFECTIV alEffectiv{ nullptr };
   LPALGETEFFECTF alGetEffectf{ nullptr };
   LPALGETEFFECTFV alGetEffectfv{ nullptr };
   LPALGETEFFECTI alGetEffecti{ nullptr };
   LPALGETEFFECTIV alGetEffectiv{ nullptr };
   LPALGENAUXILIARYEFFECTSLOTS alGenAuxiliaryEffectSlots{ nullptr };
   LPALDELETEAUXILIARYEFFECTSLOTS alDeleteAuxiliaryEffectSlots{ nullptr };
   LPALISAUXILIARYEFFECTSLOT alIsAuxiliaryEffectSlot{ nullptr };
   LPALAUXILIARYEFFECTSLOTF alAuxiliaryEffectSlotf{ nullptr };
   LPALAUXILIARYEFFECTSLOTFV alAuxiliaryEffectSlotfv{ nullptr };
   LPALAUXILIARYEFFECTSLOTI alAuxiliaryEffectSloti{ nullptr };
   LPALAUXILIARYEFFECTSLOTIV alAuxiliaryEffectSlotiv{ nullptr };
   LPALGETAUXILIARYEFFECTSLOTF alGetAuxiliaryEffectSlotf{ nullptr };
   LPALGETAUXILIARYEFFECTSLOTFV alGetAuxiliaryEffectSlotfv{ nullptr };
   LPALGETAUXILIARYEFFECTSLOTI alGetAuxiliaryEffectSloti{ nullptr };
   LPALGETAUXILIARYEFFECTSLOTIV alGetAuxiliaryEffectSlotiv{ nullptr };

};

using LPOPENALFNTABLE = OPENALFNTABLE*;

#endif

ALboolean LoadOAL10Library(char* szOALFullPathName, LPOPENALFNTABLE lpOALFnTable);
ALvoid UnloadOAL10Library();

#endif // _LOADOAL_H_
