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

#ifndef _SFXPROVIDER_H_
#define _SFXPROVIDER_H_

#ifndef _TVECTOR_H_
   #include "core/util/tVector.h"
#endif

#ifndef _SFXENUMS_H_
#include "sfx/sfxEnums.h"
#endif

class SFXDevice;



struct SFXDeviceInfo
{
   String   name;
   bool     hasHardware = false;
   S32      maxSources = 0;
   U32      deviceIdx = 0;
   SFXDeviceType type;
};

typedef Vector<SFXDeviceInfo*> SFXDeviceInfoVector;

struct SFXProvider
{
      String mName;
      SFXDeviceInfoVector  mDeviceInfo;
      /// The case sensitive name of this provider.
      const String& getName() const { return mName; }
      SFXProviderType mType;

      /// This is called from SFXSystem to create a new device.  Must be implemented
      /// by all contrete provider classes.
      ///
      /// @param deviceName      The case sensitive name of the device or NULL to create the 
      //                         default device.
      /// @param useHardware     Toggles the use of hardware processing when available.
      /// @param maxSources      The maximum buffers for this device to use or -1 
      ///                        for the device to pick a reasonable default for that device.
      ///
      /// @return Returns the created device or NULL for failure.
      ///
      virtual SFXDevice* createDevice(const String& deviceName, bool useHardware, S32 maxSources) = 0;

      virtual ~SFXProvider();
};


#endif // _SFXPROVIDER_H_
