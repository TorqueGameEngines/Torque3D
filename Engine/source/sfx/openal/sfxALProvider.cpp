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

#include "platform/platform.h"

#include "sfx/sfxProvider.h"
#include "sfx/openal/sfxALDevice.h"
#include "sfx/openal/sfxALProvider.h"
#include "sfx/openal/LoadOAL.h"

#include "core/strings/stringFunctions.h"
#include "console/console.h"
#include "core/module.h"
#include "sfx/SFXInit.h"


class SFXALRegisterProvider
{
public:
   SFXALRegisterProvider()
   {
      SFXInit::getRegisterProviderSignal().notify(&SFXALProvider::enumerateDriversAndDevices);
   }
};

static SFXALRegisterProvider pSFXALRegisterProvider;

SFXALProvider::~SFXALProvider()
{
}

void SFXALProvider::enumerateDriversAndDevices(Vector<SFXProvider*> &providerList)
{
   LoadDriverList();

   if (ALDriverList.size() < 1)
   {
      Con::printf("SFXALProvider - No valid openal drivers.");
      return;
   }

   SFXALProvider* alProvider = new SFXALProvider();
   alProvider->mType = SFXProviderType::OpenAL;
   alProvider->mName = "OpenAL";

   U32 driverIdx = 0;
   U32 deviceIdx = 0;
   for (openAlInterface* alDriver : ALDriverList)
   {
      if (alDriver->alcIsExtensionPresent(NULL, "ALC_ENUMERATION_EXT") == AL_TRUE)
      {
         char* devices, *defaultDeviceName;
         if (alDriver->alcIsExtensionPresent(NULL, "ALC_ENUMERATE_ALL_EXT") == AL_TRUE) {
            devices = (char*)alDriver->alcGetString(NULL, ALC_ALL_DEVICES_SPECIFIER);
            defaultDeviceName = (char*)alDriver->alcGetString(NULL, ALC_DEFAULT_ALL_DEVICES_SPECIFIER);
         }
         else {
            devices = (char*)alDriver->alcGetString(NULL, ALC_DEVICE_SPECIFIER);
            defaultDeviceName = (char*)alDriver->alcGetString(NULL, ALC_DEFAULT_DEVICE_SPECIFIER);
         }

         // add default device first so it is top of the list.
         if (defaultDeviceName != NULL)
         {
            // make sure we can create it
            ALCdevice* device = alDriver->alcOpenDevice(defaultDeviceName);
            if (device)
            {
               ALCcontext* ctx = alDriver->alcCreateContext(device, nullptr);
               if (ctx)
               {
                  ALDeviceInfo* devInfo = new ALDeviceInfo;
                  devInfo->driverIdx = driverIdx;
                  devInfo->deviceIdx = deviceIdx;
                  devInfo->name = String(defaultDeviceName);
                  devInfo->type = SFXDeviceType::Output;
                  // only true for default driver
                  devInfo->defaultDevice = driverIdx == 0 ? true : false;

                  alProvider->mDeviceInfo.push_back(devInfo);
                  deviceIdx++;
                  alDriver->alcMakeContextCurrent(nullptr);
                  alDriver->alcDestroyContext(ctx);
               }

               alDriver->alcCloseDevice(device);
            }
         }

         const char* ptr = devices;
         while (*ptr != 0)
         {
            bool found = false;
            for (SFXDeviceInfo* dev : alProvider->mDeviceInfo)
            {
               if (String::compare(dev->name.c_str(), ptr) == 0)
               {
                  ptr += dev->name.length() + 1;
                  found = true;
                  break;
               }
            }

            if (found)
               continue;

            ALCdevice* device = alDriver->alcOpenDevice(ptr);
            if (device)
            {
               ALCcontext* ctx = alDriver->alcCreateContext(device, nullptr);
               if (ctx)
               {
                  alDriver->alcMakeContextCurrent(ctx);

                  ALDeviceInfo* devInfo = new ALDeviceInfo;
                  devInfo->driverIdx = driverIdx;
                  devInfo->deviceIdx = deviceIdx;
                  devInfo->name = String(ptr);
                  devInfo->type = SFXDeviceType::Output;

                  alProvider->mDeviceInfo.push_back(devInfo);
                  deviceIdx++;
                  ptr += devInfo->name.length() + 1;

                  alDriver->alcMakeContextCurrent(nullptr);
                  alDriver->alcDestroyContext(ctx);
               }

               alDriver->alcCloseDevice(device);
            }
         }

         if (alDriver->alcIsExtensionPresent(NULL, "ALC_EXT_CAPTURE") == AL_FALSE)
            continue;

         devices = (char*)alcGetString(NULL, ALC_CAPTURE_DEVICE_SPECIFIER);
         ptr = devices;
         while (*ptr != 0)
         {
            bool found = false;
            for (SFXDeviceInfo* dev : alProvider->mDeviceInfo)
            {
               if (String::compare(dev->name.c_str(), ptr) == 0)
               {
                  ptr += dev->name.length() + 1;
                  found = true;
                  break;
               }
            }

            if (found)
               continue;

            ALCdevice* device = alDriver->alcCaptureOpenDevice(ptr, 22040, AL_FORMAT_MONO8, 22040 * 2);
            if (device)
            {
               ALDeviceInfo* devInfo = new ALDeviceInfo;
               devInfo->driverIdx = driverIdx;
               devInfo->deviceIdx = deviceIdx;
               devInfo->name = String(ptr);
               devInfo->type = SFXDeviceType::Input;

               alProvider->mDeviceInfo.push_back(devInfo);
               deviceIdx++;
               ptr += devInfo->name.length() + 1;

               alDriver->alcCaptureCloseDevice(device);
            }
         }
      }

      driverIdx++;
   }

   Con::printf("Devices Found for %s:", alProvider->mName.c_str());
   for (SFXDeviceInfo* info : alProvider->mDeviceInfo)
   {
      Con::printf("[%s] %s %s", info->type == SFXDeviceType::Output ? "Output Device" : "Input Device",
         info->name.c_str(),
         info->defaultDevice ? "(Default Device)" : "");
   }

   providerList.push_back(alProvider);
}

SFXDevice* SFXALProvider::createDevice(const String& deviceName, bool useHardware, S32 maxSources)
{
   return NULL;
}
