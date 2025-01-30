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

#include "sfx/openal/LoadOAL.h"
#include "console/console.h"

#if defined(TORQUE_OS_WIN)
#include <windows.h>
#else
#include <dirent.h>
#include <sys/types.h>
#endif

ALboolean LoadOAL10Library(char *szOALFullPathName, openAlInterface& lpOALFnTable)
{
	if (szOALFullPathName)
      lpOALFnTable.openaAlDll = LoadLibraryA(szOALFullPathName);
   else
   {
#ifdef TORQUE_DEBUG
      lpOALFnTable.openaAlDll = LoadLibraryA("openal32d.dll");
#else
      lpOALFnTable.openaAlDll = LoadLibraryA("openal32.dll");
#endif
   }
	if (!lpOALFnTable.openaAlDll)
		return AL_FALSE;

   bool loadok = true;

   LOAD_REQUIRED(lpOALFnTable, alcCreateContext);
   LOAD_REQUIRED(lpOALFnTable, alcMakeContextCurrent);
   LOAD_REQUIRED(lpOALFnTable, alcProcessContext);
   LOAD_REQUIRED(lpOALFnTable, alcSuspendContext);
   LOAD_REQUIRED(lpOALFnTable, alcDestroyContext);
   LOAD_REQUIRED(lpOALFnTable, alcGetCurrentContext);
   LOAD_REQUIRED(lpOALFnTable, alcGetContextsDevice);
   LOAD_REQUIRED(lpOALFnTable, alcOpenDevice);
   LOAD_REQUIRED(lpOALFnTable, alcCloseDevice);
   LOAD_REQUIRED(lpOALFnTable, alcGetError);
   LOAD_REQUIRED(lpOALFnTable, alcIsExtensionPresent);
   LOAD_REQUIRED(lpOALFnTable, alcGetProcAddress);
   LOAD_REQUIRED(lpOALFnTable, alcGetEnumValue);
   LOAD_REQUIRED(lpOALFnTable, alcGetString);
   LOAD_REQUIRED(lpOALFnTable, alcGetIntegerv);
   LOAD_REQUIRED(lpOALFnTable, alcCaptureOpenDevice);
   LOAD_REQUIRED(lpOALFnTable, alcCaptureCloseDevice);
   LOAD_REQUIRED(lpOALFnTable, alcCaptureStart);
   LOAD_REQUIRED(lpOALFnTable, alcCaptureStop);
   LOAD_REQUIRED(lpOALFnTable, alcCaptureSamples);

   LOAD_REQUIRED(lpOALFnTable, alEnable);
   LOAD_REQUIRED(lpOALFnTable, alDisable);
   LOAD_REQUIRED(lpOALFnTable, alIsEnabled);
   LOAD_REQUIRED(lpOALFnTable, alGetString);
   LOAD_REQUIRED(lpOALFnTable, alGetBooleanv);
   LOAD_REQUIRED(lpOALFnTable, alGetIntegerv);
   LOAD_REQUIRED(lpOALFnTable, alGetFloatv);
   LOAD_REQUIRED(lpOALFnTable, alGetDoublev);
   LOAD_REQUIRED(lpOALFnTable, alGetBoolean);
   LOAD_REQUIRED(lpOALFnTable, alGetInteger);
   LOAD_REQUIRED(lpOALFnTable, alGetFloat);
   LOAD_REQUIRED(lpOALFnTable, alGetDouble);
   LOAD_REQUIRED(lpOALFnTable, alGetError);
   LOAD_REQUIRED(lpOALFnTable, alIsExtensionPresent);
   LOAD_REQUIRED(lpOALFnTable, alGetProcAddress);
   LOAD_REQUIRED(lpOALFnTable, alGetEnumValue);
   LOAD_REQUIRED(lpOALFnTable, alListenerf);
   LOAD_REQUIRED(lpOALFnTable, alListener3f);
   LOAD_REQUIRED(lpOALFnTable, alListenerfv);
   LOAD_REQUIRED(lpOALFnTable, alListeneri);
   LOAD_REQUIRED(lpOALFnTable, alListener3i);
   LOAD_REQUIRED(lpOALFnTable, alListeneriv);
   LOAD_REQUIRED(lpOALFnTable, alGetListenerf);
   LOAD_REQUIRED(lpOALFnTable, alGetListener3f);
   LOAD_REQUIRED(lpOALFnTable, alGetListenerfv);
   LOAD_REQUIRED(lpOALFnTable, alGetListeneri);
   LOAD_REQUIRED(lpOALFnTable, alGetListener3i);
   LOAD_REQUIRED(lpOALFnTable, alGetListeneriv);
   LOAD_REQUIRED(lpOALFnTable, alGenSources);
   LOAD_REQUIRED(lpOALFnTable, alDeleteSources);
   LOAD_REQUIRED(lpOALFnTable, alIsSource);
   LOAD_REQUIRED(lpOALFnTable, alSourcef);
   LOAD_REQUIRED(lpOALFnTable, alSource3f);
   LOAD_REQUIRED(lpOALFnTable, alSourcefv);
   LOAD_REQUIRED(lpOALFnTable, alSourcei);
   LOAD_REQUIRED(lpOALFnTable, alSource3i);
   LOAD_REQUIRED(lpOALFnTable, alSourceiv);
   LOAD_REQUIRED(lpOALFnTable, alGetSourcef);
   LOAD_REQUIRED(lpOALFnTable, alGetSource3f);
   LOAD_REQUIRED(lpOALFnTable, alGetSourcefv);
   LOAD_REQUIRED(lpOALFnTable, alGetSourcei);
   LOAD_REQUIRED(lpOALFnTable, alGetSource3i);
   LOAD_REQUIRED(lpOALFnTable, alGetSourceiv);
   LOAD_REQUIRED(lpOALFnTable, alSourcePlayv);
   LOAD_REQUIRED(lpOALFnTable, alSourceStopv);
   LOAD_REQUIRED(lpOALFnTable, alSourceRewindv);
   LOAD_REQUIRED(lpOALFnTable, alSourcePausev);
   LOAD_REQUIRED(lpOALFnTable, alSourcePlay);
   LOAD_REQUIRED(lpOALFnTable, alSourceStop);
   LOAD_REQUIRED(lpOALFnTable, alSourceRewind);
   LOAD_REQUIRED(lpOALFnTable, alSourcePause);
   LOAD_REQUIRED(lpOALFnTable, alSourceQueueBuffers);
   LOAD_REQUIRED(lpOALFnTable, alSourceUnqueueBuffers);
   LOAD_REQUIRED(lpOALFnTable, alGenBuffers);
   LOAD_REQUIRED(lpOALFnTable, alDeleteBuffers);
   LOAD_REQUIRED(lpOALFnTable, alIsBuffer);
   LOAD_REQUIRED(lpOALFnTable, alBufferData);
   LOAD_REQUIRED(lpOALFnTable, alDopplerFactor);
   LOAD_REQUIRED(lpOALFnTable, alDopplerVelocity);
   LOAD_REQUIRED(lpOALFnTable, alSpeedOfSound);
   LOAD_REQUIRED(lpOALFnTable, alDistanceModel);

   if (loadok)
   {
      ALCint maj, min;
      lpOALFnTable.alcGetIntegerv(nullptr, ALC_MAJOR_VERSION, 1, &maj);
      lpOALFnTable.alcGetIntegerv(nullptr, ALC_MINOR_VERSION, 1, &min);
      if (lpOALFnTable.alcGetError(nullptr) == ALC_NO_ERROR)
      {
         lpOALFnTable.ALCVer = MakeALCVer(maj, min);
      }
      else
      {
         Con::warnf("Failed to query ALC version assuming 1.0");
         lpOALFnTable.ALCVer = MakeALCVer(1, 0);
      }
   }
   else
   {
      return AL_FALSE;
   }

   // these are optional.
   LOAD_REQUIRED(lpOALFnTable, alBufferf);
   LOAD_REQUIRED(lpOALFnTable, alBuffer3f);
   LOAD_REQUIRED(lpOALFnTable, alBufferfv);
   LOAD_REQUIRED(lpOALFnTable, alBufferi);
   LOAD_REQUIRED(lpOALFnTable, alBuffer3i);
   LOAD_REQUIRED(lpOALFnTable, alBufferiv);
   LOAD_REQUIRED(lpOALFnTable, alGetBufferf);
   LOAD_REQUIRED(lpOALFnTable, alGetBuffer3f);
   LOAD_REQUIRED(lpOALFnTable, alGetBufferfv);
   LOAD_REQUIRED(lpOALFnTable, alGetBufferi);
   LOAD_REQUIRED(lpOALFnTable, alGetBuffer3i);
   LOAD_REQUIRED(lpOALFnTable, alGetBufferiv);

   if (loadok)
   {
      if (lpOALFnTable.alcIsExtensionPresent(nullptr, "ALC_EXT_thread_local_context"))
      {
         LOAD_REQUIRED(lpOALFnTable, alcSetThreadContext);
         LOAD_REQUIRED(lpOALFnTable, alcGetThreadContext);
      }
   }

   if (!loadok)
   {
      return AL_FALSE;
   }

	return AL_TRUE;
}

void LoadDriverList()
{
   Vector<String> driverPaths;

   /// make sure our built dll is top of the list.
#if defined(TORQUE_OS_WIN)

#ifdef TORQUE_DEBUG
   driverPaths.push_back("openal32d.dll");
#else
   driverPaths.push_back("openal32.dll");
#endif

   char sys_path[MAX_PATH];
   if (GetSystemDirectoryA(sys_path, MAX_PATH))
   {
      String searchPath = String::ToString(sys_path) + "\\*oal.dll";

      WIN32_FIND_DATAA fdata;
      HANDLE srchHdl = FindFirstFileA(searchPath.c_str(), &fdata);
      if (srchHdl == INVALID_HANDLE_VALUE) return;

      do {
         String fullPath = String::ToString(sys_path) + "\\" + fdata.cFileName;
         driverPaths.push_back(fullPath);
      } while (FindNextFileA(srchHdl, &fdata));

      FindClose(srchHdl);
   }

#else  // Linux & macOS
   const char* sys_path = "/usr/lib/";

#ifdef __linux__

#ifdef TORQUE_DEBUG
   driverPaths.push_back("libopenald.so.1");
   driverPaths.push_back("libopenald.so");
#else
   driverPaths.push_back("libopenal.so.1");
   driverPaths.push_back("libopenal.so");
#endif

   const char* pattern = "*oal.so"

#elif __APPLE__

#ifdef TORQUE_DEBUG
   driverPaths.push_back("@rpath/libopenald.1.dylib");
   driverPaths.push_back("@rpath/libopenald.1.23.1.dylib");
#else
   driverPaths.push_back("@rpath/libopenal.1.dylib");
   driverPaths.push_back("@rpath/libopenal.1.23.1.dylib");
#endif

   const char* pattern = "*oal.dylib"

#endif

   char search[1024];
   dSprintf(search, sizeof(search), "%s", sys_path, pattern);

   DIR* dir = opendir(search);
   if (!dir) return;

   struct dirent* fEntry;
   while ((fEntry = readdir(dir)) != nullptr)
   {
      if ((fStat.st_mode & S_IFMT) == S_IFDIR)
         continue;

      char filename[BUFSIZ + 1];
      dSprintf(filename, sizeof(filename), "%s/%s", search, fEntry->d_name); // "construct" the file name
      String fullPath = String::ToString(filename);
      driverPaths.push_back(fullPath);
   }

   closedir(dir);
#endif
}

