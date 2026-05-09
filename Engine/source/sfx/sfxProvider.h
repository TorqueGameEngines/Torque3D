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

#ifndef _SFXCOMMON_H_
#include "sfx/sfxCommon.h"
#endif

#ifndef _TVECTOR_H_
#include "core/util/tVector.h"
#endif

#ifndef _UTIL_DELEGATE_H_
#include "core/util/delegate.h"
#endif

class SFXDevice;

struct SFXProvider
{
public:
   typedef Delegate<SFXDevice* (U32 providerIndex)> CreateProviderInstanceDelegate;

   String            mName;
   bool              mHasHardware;
   SFXProviderType   mType;
   SFXDeviceType     mDeviceType;
   U32               mIndex;
   bool              mDefault;
   CreateProviderInstanceDelegate mCreateDeviceInstanceDelegate;

   const char*       getName() const { return mName; }

   SFXProvider()
   {
      mName = String::EmptyString;
      mHasHardware = false;
      mType = NullProvider;
      mIndex = 0;
      mDefault = false;
      mDeviceType = Output;
   }
};


#endif // _SFXPROVIDER_H_
