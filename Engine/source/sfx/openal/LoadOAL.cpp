/*
 * Copyright (c) 2006, Creative Labs Inc.
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided
 * that the following conditions are met:
 * 
 *     * Redistributions of source code must retain the above copyright notice, this list of conditions and
 * 	     the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright notice, this list of conditions
 * 	     and the following disclaimer in the documentation and/or other materials provided with the distribution.
 *     * Neither the name of Creative Labs Inc. nor the names of its contributors may be used to endorse or
 * 	     promote products derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
 // Based on Openal-soft router code.

#include "sfx/openal/LoadOAL.h"
#include "console/console.h"

#if defined(TORQUE_OS_WIN)
#include <windows.h>
#else
#include <dirent.h>
#include <sys/types.h>
#endif

LIB_HANDLE openaAlDll = NULL;

#define LOAD_REQUIRED(table, x)                                                             \
     table->x = reinterpret_cast<decltype(table->x)>(reinterpret_cast<void*>(               \
        GET_PROC_ADDRESS(openaAlDll, #x)));                                                 \
    if(!table->x)                                                                           \
    {                                                                                       \
        Con::warnf("Failed to find entry point :%s\n", #x);                                 \
        loadok = false;                                                                     \
    }  


ALboolean LoadOAL10Library(char *szOALFullPathName, LPOPENALFNTABLE oal)
{
	if (!oal)
		return AL_FALSE;

   if (szOALFullPathName)
      openaAlDll = LOAD_LIBRARY(szOALFullPathName);
   else
   {
#if defined(TORQUE_OS_WIN)
      openaAlDll = LOAD_LIBRARY("openal32.dll");
#elif defined(__linux__)
      openaAlDll = LOAD_LIBRARY("libopenal.so");
#eilf defined(__APPLE__)
   openaAlDll = LOAD_LIBRARY("@rpath/libopenal.1.24.3.dylib");
#endif
   }

   if (!openaAlDll)
      return AL_FALSE;

   bool loadok = true;

   LOAD_REQUIRED(oal, alcCreateContext);
   LOAD_REQUIRED(oal, alcMakeContextCurrent);
   LOAD_REQUIRED(oal, alcProcessContext);
   LOAD_REQUIRED(oal, alcSuspendContext);
   LOAD_REQUIRED(oal, alcDestroyContext);
   LOAD_REQUIRED(oal, alcGetCurrentContext);
   LOAD_REQUIRED(oal, alcGetContextsDevice);
   LOAD_REQUIRED(oal, alcOpenDevice);
   LOAD_REQUIRED(oal, alcCloseDevice);
   LOAD_REQUIRED(oal, alcGetError);
   LOAD_REQUIRED(oal, alcIsExtensionPresent);
   LOAD_REQUIRED(oal, alcGetProcAddress);
   LOAD_REQUIRED(oal, alcGetEnumValue);
   LOAD_REQUIRED(oal, alcGetString);
   LOAD_REQUIRED(oal, alcGetIntegerv);
   LOAD_REQUIRED(oal, alcCaptureOpenDevice);
   LOAD_REQUIRED(oal, alcCaptureCloseDevice);
   LOAD_REQUIRED(oal, alcCaptureStart);
   LOAD_REQUIRED(oal, alcCaptureStop);
   LOAD_REQUIRED(oal, alcCaptureSamples);

   LOAD_REQUIRED(oal, alEnable);
   LOAD_REQUIRED(oal, alDisable);
   LOAD_REQUIRED(oal, alIsEnabled);
   LOAD_REQUIRED(oal, alGetString);
   LOAD_REQUIRED(oal, alGetBooleanv);
   LOAD_REQUIRED(oal, alGetIntegerv);
   LOAD_REQUIRED(oal, alGetFloatv);
   LOAD_REQUIRED(oal, alGetDoublev);
   LOAD_REQUIRED(oal, alGetBoolean);
   LOAD_REQUIRED(oal, alGetInteger);
   LOAD_REQUIRED(oal, alGetFloat);
   LOAD_REQUIRED(oal, alGetDouble);
   LOAD_REQUIRED(oal, alGetError);
   LOAD_REQUIRED(oal, alIsExtensionPresent);
   LOAD_REQUIRED(oal, alGetProcAddress);
   LOAD_REQUIRED(oal, alGetEnumValue);
   LOAD_REQUIRED(oal, alListenerf);
   LOAD_REQUIRED(oal, alListener3f);
   LOAD_REQUIRED(oal, alListenerfv);
   LOAD_REQUIRED(oal, alListeneri);
   LOAD_REQUIRED(oal, alListener3i);
   LOAD_REQUIRED(oal, alListeneriv);
   LOAD_REQUIRED(oal, alGetListenerf);
   LOAD_REQUIRED(oal, alGetListener3f);
   LOAD_REQUIRED(oal, alGetListenerfv);
   LOAD_REQUIRED(oal, alGetListeneri);
   LOAD_REQUIRED(oal, alGetListener3i);
   LOAD_REQUIRED(oal, alGetListeneriv);
   LOAD_REQUIRED(oal, alGenSources);
   LOAD_REQUIRED(oal, alDeleteSources);
   LOAD_REQUIRED(oal, alIsSource);
   LOAD_REQUIRED(oal, alSourcef);
   LOAD_REQUIRED(oal, alSource3f);
   LOAD_REQUIRED(oal, alSourcefv);
   LOAD_REQUIRED(oal, alSourcei);
   LOAD_REQUIRED(oal, alSource3i);
   LOAD_REQUIRED(oal, alSourceiv);
   LOAD_REQUIRED(oal, alGetSourcef);
   LOAD_REQUIRED(oal, alGetSource3f);
   LOAD_REQUIRED(oal, alGetSourcefv);
   LOAD_REQUIRED(oal, alGetSourcei);
   LOAD_REQUIRED(oal, alGetSource3i);
   LOAD_REQUIRED(oal, alGetSourceiv);
   LOAD_REQUIRED(oal, alSourcePlayv);
   LOAD_REQUIRED(oal, alSourceStopv);
   LOAD_REQUIRED(oal, alSourceRewindv);
   LOAD_REQUIRED(oal, alSourcePausev);
   LOAD_REQUIRED(oal, alSourcePlay);
   LOAD_REQUIRED(oal, alSourceStop);
   LOAD_REQUIRED(oal, alSourceRewind);
   LOAD_REQUIRED(oal, alSourcePause);
   LOAD_REQUIRED(oal, alSourceQueueBuffers);
   LOAD_REQUIRED(oal, alSourceUnqueueBuffers);
   LOAD_REQUIRED(oal, alGenBuffers);
   LOAD_REQUIRED(oal, alDeleteBuffers);
   LOAD_REQUIRED(oal, alIsBuffer);
   LOAD_REQUIRED(oal, alBufferData);
   LOAD_REQUIRED(oal, alDopplerFactor);
   LOAD_REQUIRED(oal, alDopplerVelocity);
   LOAD_REQUIRED(oal, alSpeedOfSound);
   LOAD_REQUIRED(oal, alDistanceModel);

   // these are optional.
   LOAD_REQUIRED(oal, alBufferf);
   LOAD_REQUIRED(oal, alBuffer3f);
   LOAD_REQUIRED(oal, alBufferfv);
   LOAD_REQUIRED(oal, alBufferi);
   LOAD_REQUIRED(oal, alBuffer3i);
   LOAD_REQUIRED(oal, alBufferiv);
   LOAD_REQUIRED(oal, alGetBufferf);
   LOAD_REQUIRED(oal, alGetBuffer3f);
   LOAD_REQUIRED(oal, alGetBufferfv);
   LOAD_REQUIRED(oal, alGetBufferi);
   LOAD_REQUIRED(oal, alGetBuffer3i);
   LOAD_REQUIRED(oal, alGetBufferiv);

   return AL_TRUE;
}

ALvoid UnloadOAL10Library()
{
	// Unload the dll
   if (openaAlDll)
      CLOSE_LIBRARY(openaAlDll);
}
