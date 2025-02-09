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
// Based on Openal-soft router code.

#include "sfx/openal/LoadOAL.h"
#include "console/console.h"

#if defined(TORQUE_OS_WIN)
#include <windows.h>
#else
#include <dirent.h>
#include <sys/types.h>
#endif

void AddDriver(const Torque::Path& name, LIB_HANDLE dllHandle)
{
   openAlInterface* oal = new openAlInterface(name.getFileName(), dllHandle);

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
   
#if defined(AL_ALEXT_PROTOTYPES)
   if (loadok)
   {
      if (oal->alcIsExtensionPresent(nullptr, "ALC_EXT_thread_local_context"))
      {
         LOAD_REQUIRED(oal, alcSetThreadContext);
         LOAD_REQUIRED(oal, alcGetThreadContext);
      }

      ALDriverList.push_back(oal);
   }
#else
   if (loadok)
   {
      ALDriverList.push_back(oal);
   }
#endif
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
   driverPaths.push_back("libopenald.so");
#else
   driverPaths.push_back("libopenal.so");
#endif

#elif __APPLE__

#ifdef TORQUE_DEBUG
   driverPaths.push_back("@rpath/libopenald.dylib");
#else
   driverPaths.push_back("@rpath/libopenal.dylib");
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
         String fileName = String::ToString(entry->d_name);

#ifdef __linux__
         if (fileName.endsWith("oal.so"))
#elif __APPLE__
         if (fileName.endsWith("openal.dylib"))  // Fix for macOS
#endif
         {
            String fullPath = String::ToString(sys_path) + fileName;
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

