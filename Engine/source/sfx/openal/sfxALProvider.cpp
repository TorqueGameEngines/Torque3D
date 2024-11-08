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
#include "sfx/openal/aldlist.h"
#include "sfx/openal/LoadOAL.h"

#include "core/strings/stringFunctions.h"
#include "console/console.h"
#include "core/module.h"


class SFXALProvider : public SFXProvider
{
public:

   SFXALProvider()
      : SFXProvider( "OpenAL" ) { dMemset(&mOpenAL,0,sizeof(mOpenAL)); mALDL = NULL; }
   virtual ~SFXALProvider();

protected:
   OPENALFNTABLE mOpenAL;
   ALDeviceList *mALDL;

   struct ALDeviceInfo : SFXDeviceInfo
   {
      
   };

   void init() override;

public:
   SFXDevice *createDevice( const String& deviceName, bool useHardware, S32 maxBuffers ) override;

};

MODULE_BEGIN( OpenAL )

   MODULE_INIT_BEFORE( SFX )
   MODULE_SHUTDOWN_AFTER( SFX )
   
   SFXALProvider* mProvider = NULL;
   
   MODULE_INIT
   {
      mProvider = new SFXALProvider;
   }
   
   MODULE_SHUTDOWN
   {
      delete mProvider;
   }

MODULE_END;

void SFXALProvider::init()
{
   if( LoadOAL10Library( NULL, &mOpenAL ) != AL_TRUE )
   {
      Con::printf( "SFXALProvider - OpenAL not available." );
      return;
   }
   mALDL = new ALDeviceList( mOpenAL );

   // Did we get any devices?
   if ( mALDL->GetNumDevices() < 1 )
   {
      Con::printf( "SFXALProvider - No valid devices found!" );
      return;
   }

   // Cool, loop through them, and caps em
   //const char *deviceFormat = "OpenAL v%d.%d %s";

   for( S32 i = 0; i < mALDL->GetNumDevices(); i++ )
   {
      ALDeviceInfo* info = new ALDeviceInfo;
      
      info->internalName = String( mALDL->GetInternalDeviceName( i ) );
      info->name = String( mALDL->GetDeviceName( i ) );

      mDeviceInfo.push_back( info );
   }

   regProvider( this );
}

SFXALProvider::~SFXALProvider()
{
   UnloadOAL10Library();

   if (mALDL)
	delete mALDL;
}

SFXDevice *SFXALProvider::createDevice( const String& deviceName, bool useHardware, S32 maxBuffers )
{
   ALDeviceInfo *info = dynamic_cast< ALDeviceInfo* >
      ( _findDeviceInfo( deviceName) );

   // Do we find one to create?
   if (info)
      return new SFXALDevice(this, mOpenAL, info->internalName, useHardware, maxBuffers);

   return NULL;
}
