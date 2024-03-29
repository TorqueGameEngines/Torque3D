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

#ifndef _SFXNULLDEVICE_H_
#define _SFXNULLDEVICE_H_

class SFXProvider;

#ifndef _SFXDEVICE_H_
   #include "sfx/sfxDevice.h"
#endif
#ifndef _SFXPROVIDER_H_
   #include "sfx/sfxProvider.h"
#endif
#ifndef _SFXNULLBUFFER_H_
   #include "sfx/null/sfxNullBuffer.h"
#endif
#ifndef _SFXNULLVOICE_H_
   #include "sfx/null/sfxNullVoice.h"
#endif


class SFXNullDevice : public SFXDevice
{
   typedef SFXDevice Parent;

   public:

      SFXNullDevice( SFXProvider* provider, 
                     String name, 
                     bool useHardware, 
                     S32 maxBuffers );

      virtual ~SFXNullDevice();

   public:

      // SFXDevice.
       SFXBuffer* createBuffer( const ThreadSafeRef< SFXStream >& stream, SFXDescription* description ) override;
      SFXVoice* createVoice( bool is3D, SFXBuffer *buffer ) override;
      void update() override;
};

#endif // _SFXNULLDEVICE_H_