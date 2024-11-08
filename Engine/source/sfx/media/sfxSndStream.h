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

#ifndef _SFXSNDSTREAM_H_
#define _SFXSNDSTREAM_H_

#ifndef _SFXFILESTREAM_H_
#  include "sfx/sfxFileStream.h"
#endif
#include "core/util/safeDelete.h"

#include <sndfile.h>

/// An SFXFileStream that loads sample data from a Vorbis file.
class SFXSndStream : public SFXFileStream,
   public IPositionable< U32 >
{
public:
   typedef SFXFileStream Parent;

protected:

   // setup our vio_data struct.
   typedef struct
   {
      sf_count_t offset, length;
      Stream* data;
   } VIO_DATA;

   /// Total number of bytes read from the stream so far.
   U32 mBytesRead;
   /// The current bitstream index.
   S32 mCurPos;

   SF_VIRTUAL_IO vio;
   SNDFILE* sndFile;
   VIO_DATA vio_data;
   SF_INFO sfinfo;

   // vio callbacks
   static sf_count_t sndSeek(sf_count_t offset, int whence, void* user_data);
   static sf_count_t sndRead(void *ptr, sf_count_t count, void* user_data);
   static sf_count_t sndWrite(const void* ptr, sf_count_t count, void* user_data);
   static sf_count_t sndTell(void* user_data);
   static sf_count_t sndFileLen(void* user_data);
   
   // SFXStream
   bool _readHeader() override;
   void _close() override;

public:

   ///
   static SFXSndStream* create(Stream* stream);

   // SFXStream
   void reset() override;
   U32 read(U8* buffer, U32 length) override;
   bool isEOS() const override;
   SFXStream* clone() const override
   {
      SFXSndStream* stream = new SFXSndStream(*this);
      if (!stream->sndFile)
         SAFE_DELETE(stream);
      return stream;
   }

   // IPositionable
   U32 getPosition() const override;
   void setPosition(U32 offset) override;
};

#endif
