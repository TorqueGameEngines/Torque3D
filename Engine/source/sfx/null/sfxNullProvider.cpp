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

#include "sfx/sfxProvider.h"
#include "sfx/null/sfxNullDevice.h"
#include "core/strings/stringFunctions.h"
#include "core/module.h"
#include "sfx/SFXInit.h"

struct SFXNullProvider : public SFXProvider
{
   SFXDevice* createDevice( const String& deviceName, bool useHardware, S32 maxSources ) override;
   static void enumerateDriversAndDevices(Vector<SFXProvider*>& providerList);
};

class SFXNullRegisterProvider
{
public:
   SFXNullRegisterProvider()
   {
      SFXInit::getRegisterProviderSignal().notify(&SFXNullProvider::enumerateDriversAndDevices);
   }
};

static SFXNullRegisterProvider pSFXNULLRegisterProvider;

void SFXNullProvider::enumerateDriversAndDevices(Vector<SFXProvider*>& providerList)
{
   SFXNullProvider* nullPro = new SFXNullProvider();
   nullPro->mType = SFXProviderType::NullProvider;

   SFXDeviceInfo* info = new SFXDeviceInfo;
   info->name = "SFX Null Device";
   info->hasHardware = false;
   info->maxSources = 8;
   info->type = SFXDeviceType::Output;

   nullPro->mDeviceInfo.push_back( info );

   providerList.push_back(nullPro);
}

SFXDevice* SFXNullProvider::createDevice( const String& deviceName, bool useHardware, S32 maxSources )
{
   SFXDeviceInfo* info = mDeviceInfo[0];

   // Do we find one to create?
   if ( info )
      return new SFXNullDevice( this, info->name, useHardware, maxSources );

   return NULL;
}
