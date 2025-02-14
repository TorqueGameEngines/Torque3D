#pragma once
#ifndef _SFXALPROVIDER_H_
#define _SFXALPROVIDER_H_


#ifndef _SFXDEVICE_H_
#  include "sfx/sfxDevice.h"
#endif

#ifndef _SFXPROVIDER_H_
#  include "sfx/sfxProvider.h"
#endif

struct SFXALProvider : public SFXProvider
{
   typedef Delegate<SFXDevice* (U32 driverIndex)> CreateALDevice;
   static void enumerateDriversAndDevices(Vector<SFXProvider*>& providerList);

   struct ALDeviceInfo : SFXDeviceInfo
   {
      U32 driverIdx = 0;
   };

   SFXDevice* createDevice(const String& deviceName, bool useHardware, S32 maxSources) override;

   virtual ~SFXALProvider();
};


#endif // !_SFXALPROVIDER_H_
