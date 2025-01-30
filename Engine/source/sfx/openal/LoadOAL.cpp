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

void AddDriver(const char* name, LIB_HANDLE dllHandle)
{
   openAlInterface* oal = new openAlInterface(name, dllHandle);

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

   if (loadok)
   {
      ALCint maj, min;
      oal->alcGetIntegerv(nullptr, ALC_MAJOR_VERSION, 1, &maj);
      oal->alcGetIntegerv(nullptr, ALC_MINOR_VERSION, 1, &min);
      if (oal->alcGetError(nullptr) == ALC_NO_ERROR)
      {
         oal->ALCVer = MakeALCVer(maj, min);
      }
      else
      {
         Con::warnf("Failed to query ALC version assuming 1.0");
         oal->ALCVer = MakeALCVer(1, 0);
      }
   }

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

   if (loadok)
   {
      if (oal->alcIsExtensionPresent(nullptr, "ALC_EXT_thread_local_context"))
      {
         LOAD_REQUIRED(oal, alcSetThreadContext);
         LOAD_REQUIRED(oal, alcGetThreadContext);
      }

      ALDriverList.push_back(oal);
   }
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

#elif __APPLE__

#ifdef TORQUE_DEBUG
   driverPaths.push_back("@rpath/libopenald.1.dylib");
   driverPaths.push_back("@rpath/libopenald.1.23.1.dylib");
#else
   driverPaths.push_back("@rpath/libopenal.1.dylib");
   driverPaths.push_back("@rpath/libopenal.1.23.1.dylib");
#endif

#endif
   
      const char* searchDirs[] = {
           "/usr/lib/",
           "/usr/local/lib/",
           "/Library/Audio/Plug-Ins/HAL/"
   };

   for (const char* sys_path : searchDirs)
   {
      DIR* dir = opendir(sys_path);
      if (!dir) continue;

      struct dirent* entry;
      while ((entry = readdir(dir)) != nullptr)
      {
         std::string fileName(entry->d_name);

#ifdef __linux__
         if (fileName.find("oal.so") != std::string::npos)
#elif __APPLE__
         if (fileName.find("openal.dylib") != std::string::npos)  // Fix for macOS
#endif
         {
            std::string fullPath = std::string(sys_path) + fileName;
            driverPaths.push_back(fullPath);
}
        }

      closedir(dir);
    }
#endif

   for(String driver : driverPaths)
   {
      LIB_HANDLE mod = LOAD_LIBRARY(driver);
      if (mod)
      {
         AddDriver(driver, mod);
      }
   }

}

