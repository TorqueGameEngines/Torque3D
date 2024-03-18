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

#ifndef _SFXALDEVICE_H_
#define _SFXALDEVICE_H_

class SFXProvider;

#ifndef _SFXDEVICE_H_
#  include "sfx/sfxDevice.h"
#endif

#ifndef _SFXPROVIDER_H_
#  include "sfx/sfxProvider.h"
#endif

#ifndef _SFXALBUFFER_H_
#  include "sfx/openal/sfxALBuffer.h"
#endif

#ifndef _SFXALVOICE_H_
#  include "sfx/openal/sfxALVoice.h"
#endif

#ifndef _OPENALFNTABLE
#  include "sfx/openal/LoadOAL.h"
#endif


class SFXALDevice : public SFXDevice
{
   public:

      typedef SFXDevice Parent;
      friend class SFXALVoice; // mDistanceFactor, mRolloffFactor

      void printALInfo(ALCdevice* device);
      void printHRTFInfo(ALCdevice* device);
      void getEFXInfo(ALCdevice* device);
      S32 getMaxSources();
   
      // Compatibility with pre openal 1.2
      S32 getMaxSourcesOld();

      SFXALDevice(   SFXProvider *provider,
                     const OPENALFNTABLE &openal, 
                     String name, 
                     bool useHardware, 
                     S32 maxBuffers );

      virtual ~SFXALDevice();

   protected:

      OPENALFNTABLE mOpenAL;

      ALCcontext *mContext;

      ALCdevice *mDevice;
      
      SFXDistanceModel mDistanceModel;
      F32 mDistanceFactor;
      F32 mRolloffFactor;
      F32 mUserRolloffFactor;
      
      void _setRolloffFactor( F32 factor );

   public:

      // SFXDevice.
      SFXBuffer* createBuffer( const ThreadSafeRef< SFXStream >& stream, SFXDescription* description ) override;
      SFXVoice* createVoice( bool is3D, SFXBuffer *buffer ) override;
      void setListener( U32 index, const SFXListenerProperties& listener ) override;
      void setDistanceModel( SFXDistanceModel model ) override;
      void setDopplerFactor( F32 factor ) override;
      void setRolloffFactor( F32 factor ) override;
#if defined(AL_ALEXT_PROTOTYPES)
      //function for openAL to open slots
      virtual void openSlots();
      //slots
      ALuint	effectSlot[4] = { 0 };
      ALuint	effect[2] = { 0 };
      ALuint   uLoop;
      //get values from sfxreverbproperties and pass it to openal device
      virtual void setReverb(const SFXReverbProperties& reverb);
#endif
      void resetReverb() override {}
};

#endif // _SFXALDEVICE_H_
