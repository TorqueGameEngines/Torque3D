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

#include "sfx/media/sfxWavZipStream.h"
#include "core/stream/stream.h"
#include "core/strings/stringFunctions.h"


/// WAV File-header
struct WAVFileHdr
{
   U8  id[4];
   U32 size;
   U8  type[4];
};

//// WAV Fmt-header
struct WAVFmtHdr
{
   U16 format;
   U16 channels;
   U32 samplesPerSec;
   U32 bytesPerSec;
   U16 blockAlign;
   U16 bitsPerSample;
};

/// WAV FmtEx-header
struct WAVFmtExHdr
{
   U16 size;
   U16 samplesPerBlock;
};

/// WAV Smpl-header
struct WAVSmplHdr
{
   U32 manufacturer;
   U32 product;
   U32 samplePeriod;
   U32 note;
   U32 fineTune;
   U32 SMPTEFormat;
   U32 SMPTEOffest;
   U32 loops;
   U32 samplerData;

   struct
   {
      U32 identifier;
      U32 type;
      U32 start;
      U32 end;
      U32 fraction;
      U32 count;
   } loop[1];
};

/// WAV Chunk-header
struct WAVChunkHdr
{
   U8  id[4];
   U32 size;
};


SFXWavZipStream* SFXWavZipStream::create( Stream *stream )
{
   SFXWavZipStream *sfxStream = new SFXWavZipStream();
   if ( sfxStream->open( stream, true ) )
      return sfxStream;

   delete sfxStream;
   return NULL;
}

SFXWavZipStream::SFXWavZipStream()
   :mDataStart(U32_MAX)
{
}

SFXWavZipStream::SFXWavZipStream( const SFXWavZipStream& cloneFrom )
   : Parent( cloneFrom ),
     mDataStart( cloneFrom.mDataStart )
{
}

SFXWavZipStream::~SFXWavZipStream()
{
   // We must call close from our own destructor
   // and not the base class... as it causes a
   // pure virtual runtime assertion.
   close();
}

void SFXWavZipStream::_close()
{
   mDataStart = U32_MAX;
}

U32 SFXWavZipStream::readFromBuffer(U32 bytes, void* outBuffer)
{
   if (bytes > (mDecompressedBuffer.fileSize - mDecompressedBuffer.currentPosition))
      bytes = mDecompressedBuffer.fileSize - mDecompressedBuffer.currentPosition;

   memcpy(outBuffer, &mDecompressedBuffer.data[mDecompressedBuffer.currentPosition], bytes);
   mDecompressedBuffer.currentPosition += bytes;

   return bytes;
}

bool SFXWavZipStream::_readHeader()
{
   // Fill buffer with decompressed data.
   if (mDecompressedBuffer.data == NULL)
   {
      mDecompressedBuffer.fileSize = mStream->getStreamSize();
      mDecompressedBuffer.currentPosition = 0;
      mDecompressedBuffer.data = new U8[mDecompressedBuffer.fileSize];
      if (!mDecompressedBuffer.data)
         return false;
      if (!mStream->read(mDecompressedBuffer.fileSize, mDecompressedBuffer.data))
         return false;
   }


   // We read the wav chunks to gather than header info
   // and find the start and end position of the data chunk. 
   mDataStart = U32_MAX;

   WAVFileHdr fileHdr;
   readFromBuffer( 4, &fileHdr.id[0] );
   readFromBuffer(sizeof(fileHdr.size), &fileHdr.size );
   readFromBuffer( 4, &fileHdr.type[0] );

   fileHdr.size=((fileHdr.size+1)&~1)-4;

   WAVChunkHdr chunkHdr;
   readFromBuffer( 4, &chunkHdr.id[0] );
   readFromBuffer(sizeof(chunkHdr.size), &chunkHdr.size);

   // Unread chunk data rounded up to nearest WORD.
   S32 chunkRemaining = chunkHdr.size + ( chunkHdr.size & 1 );

   WAVFmtHdr   fmtHdr;
   WAVFmtExHdr fmtExHdr;
   WAVSmplHdr  smplHdr;

   dMemset(&fmtHdr, 0, sizeof(fmtHdr));

   while ((fileHdr.size!=0) && (mDecompressedBuffer.currentPosition < mDecompressedBuffer.fileSize))
   {
      // WAV format header chunk.
      if ( !dStrncmp( (const char*)chunkHdr.id, "fmt ", 4 ) )
      {
         readFromBuffer(sizeof(fmtHdr.format), &fmtHdr.format);
         readFromBuffer(sizeof(fmtHdr.channels), &fmtHdr.channels);
         readFromBuffer(sizeof(fmtHdr.samplesPerSec), &fmtHdr.samplesPerSec);
         readFromBuffer(sizeof(fmtHdr.bytesPerSec), &fmtHdr.bytesPerSec);
         readFromBuffer(sizeof(fmtHdr.blockAlign), &fmtHdr.blockAlign);
         readFromBuffer(sizeof(fmtHdr.bitsPerSample), &fmtHdr.bitsPerSample);

         if ( fmtHdr.format == 0x0001 )
         {
            mFormat.set( fmtHdr.channels, fmtHdr.bitsPerSample * fmtHdr.channels, fmtHdr.samplesPerSec );
            chunkRemaining -= sizeof( WAVFmtHdr );
         }
         else
         {
            readFromBuffer(sizeof(WAVFmtExHdr), &fmtExHdr);
            chunkRemaining -= sizeof(WAVFmtExHdr);
         }
      }

      // WAV data chunk
      else if (!dStrncmp((const char*)chunkHdr.id,"data",4))
      {
         // TODO: Handle these other formats in a more graceful manner!

         if (fmtHdr.format==0x0001)
         {
            mDataStart = mDecompressedBuffer.currentPosition;
            mDecompressedBuffer.currentPosition = mDataStart + chunkHdr.size ;
            chunkRemaining -= chunkHdr.size;
            mSamples = chunkHdr.size / mFormat.getBytesPerSample();
         }
         else if (fmtHdr.format==0x0011)
         {
            //IMA ADPCM
         }
         else if (fmtHdr.format==0x0055)
         {
            //MP3 WAVE
         }
      }

      // WAV sample header
      else if (!dStrncmp((const char*)chunkHdr.id,"smpl",4))
      {
         // this struct read is NOT endian safe but it is ok because
         // we are only testing the loops field against ZERO
         readFromBuffer(sizeof(WAVSmplHdr), &smplHdr);

         // This has never been hooked up and its usefulness is
         // dubious.  Do we really want the audio file overriding
         // the SFXDescription setting?    
         //mLooping = ( smplHdr.loops ? true : false );

         chunkRemaining -= sizeof(WAVSmplHdr);
      }

      // either we have unread chunk data or we found an unknown chunk type
      // loop and read up to 1K bytes at a time until we have
      // read to the end of this chunk
      AssertFatal(chunkRemaining >= 0, "AudioBuffer::readWAV: remaining chunk data should never be less than zero.");
      if ( chunkRemaining > 0 )
      {
         mDecompressedBuffer.currentPosition = mDecompressedBuffer.currentPosition + chunkRemaining;
         chunkRemaining = 0;
      }

      fileHdr.size-=(((chunkHdr.size+1)&~1)+8);

      // read next chunk header...
      readFromBuffer(4, &chunkHdr.id[0]);
      readFromBuffer(sizeof(chunkHdr.size), &chunkHdr.size);
      // unread chunk data rounded up to nearest WORD
      chunkRemaining = chunkHdr.size + (chunkHdr.size&1);
   }

   return ( mDataStart != -1 );
}

void SFXWavZipStream::reset()
{
   AssertFatal(mDecompressedBuffer.data, "SFXWavZipStream::reset() - Stream is null!" );
   AssertFatal( mDataStart != -1, "SFXWavZipStream::seek() - Data start offset is invalid!" );
   mDecompressedBuffer.currentPosition = mDataStart;
}

U32 SFXWavZipStream::getPosition() const
{
   AssertFatal(mDecompressedBuffer.data, "SFXWavZipStream::getPosition() - Stream is null!" );
   return (mDecompressedBuffer.currentPosition - mDataStart);
}

void SFXWavZipStream::setPosition( U32 offset )
{
   AssertFatal(mDecompressedBuffer.data, "SFXWavZipStream::setPosition() - Stream is null!" );

   offset -= offset % mFormat.getBytesPerSample();
   const U32 dataLength = mSamples * mFormat.getBytesPerSample();
   if( offset > dataLength )
      offset = dataLength;

   AssertFatal( mDataStart != -1, "SFXWavZipStream::getPosition() - Data start offset is invalid!" );

   U32 byte = mDataStart + offset;

   mDecompressedBuffer.currentPosition = byte;
}

U32 SFXWavZipStream::read( U8 *buffer, U32 bytes )
{
   AssertFatal( mStream, "SFXWavZipStream::seek() - Stream is null!" );

   // Read in even sample chunks.  
   bytes -= bytes % mFormat.getBytesPerSample();

   const U32 numBytesRead = readFromBuffer( bytes, buffer );
      
   // TODO: Is it *just* 16 bit samples that needs to 
   // be flipped?  What about 32 bit samples?
   #ifdef TORQUE_BIG_ENDIAN

      // We need to endian-flip 16-bit data.
      if ( getFormat().getBytesPerChannel() == 2 ) 
      {
         U16 *ds = (U16*)buffer;
         U16 *de = (U16*)(buffer+bytes);
         while (ds<de)
         {
            *ds = convertLEndianToHost(*ds);
            ds++;
         }
      }

   #endif

   return numBytesRead;
}
