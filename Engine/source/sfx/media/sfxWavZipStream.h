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

#ifndef _SFXWAVZIPSTREAM_H_
#define _SFXWAVZIPSTREAM_H_

#ifndef _SFXFILESTREAM_H_
   #include "sfx/sfxFileStream.h"
#endif
#include "core/util/safeDelete.h"


/// An SFXFileStream that loads sample data from a WAV file.
class SFXWavZipStream : public SFXFileStream,
                     public IPositionable< U32 >
{
   public:

      typedef SFXFileStream Parent;

private:
   struct WavZipDecompressed {
      U32 fileSize = 0;
      U32 currentPosition = 0;
      U8* data = NULL;

      ~WavZipDecompressed() { SAFE_DELETE_ARRAY(data); }
   };

   WavZipDecompressed mDecompressedBuffer;

protected:

      /// The file position of the start of
      /// the PCM data for fast reset().
      U32 mDataStart;

      virtual U32 readFromBuffer(U32 bytes, void* outBuffer);

      // SFXFileStream
      virtual bool _readHeader();
      virtual void _close();

   public:

      ///
      static SFXWavZipStream* create( Stream *stream );

      ///
	   SFXWavZipStream();

      ///
      SFXWavZipStream( const SFXWavZipStream& cloneFrom );

      /// Destructor.
      virtual ~SFXWavZipStream();

      // SFXStream
      virtual void reset();
      virtual U32 read( U8 *buffer, U32 length );
      virtual SFXStream* clone() const
      {
         SFXWavZipStream* stream = new SFXWavZipStream( *this );
         if( !stream->mStream )
            SAFE_DELETE( stream );
         return stream;
      }

      // IPositionable
      virtual U32 getPosition() const;
      virtual void setPosition( U32 offset );
};

#endif  // _SFXWAVZIPSTREAM_H_
