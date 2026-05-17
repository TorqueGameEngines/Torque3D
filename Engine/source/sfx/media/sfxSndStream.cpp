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
#include "sfx/media/sfxSndStream.h"
#include "core/stream/fileStream.h"
#include "core/stream/stream.h"
#include "console/console.h"

#define MAX_BUFFER 4096

bool SFXSndStream::_readHeader()
{
   mCurPos = 0;
   mBytesRead = 0;

   dMemset(&sfinfo, 0, sizeof(SF_INFO));

   vio.get_filelen = sndFileLen;
   vio.seek = sndSeek;
   vio.read = sndRead;
   vio.write = sndWrite;
   vio.tell = sndTell;

   vio_data.length = 0;
   vio_data.offset = 0;
   vio_data.data = mStream;

   vio_data.sampleBlockAlign = 1;
   vio_data.byteBlockAlign = 0;

   if ((sndFile = sf_open_virtual(&vio, SFM_READ, &sfinfo, &vio_data)) == NULL)
   {
      Con::printf("SFXSndStream - _readHeader failed: %s", sf_strerror(sndFile));
      return false;
   }

   S32 bitsPerSample = 16;

   switch (sfinfo.format & SF_FORMAT_SUBMASK)
   {
   case SF_FORMAT_PCM_S8:
   case SF_FORMAT_PCM_U8:
      bitsPerSample = 8;
      mSampleType = Sample_Int8;  // Still decode using sf_readf_short()
      break;

   case SF_FORMAT_PCM_16:
      bitsPerSample = 16;
      mSampleType = Sample_Int16;
      break;

   case SF_FORMAT_PCM_24:
   case SF_FORMAT_PCM_32:
   case SF_FORMAT_FLOAT:
   case SF_FORMAT_DOUBLE:
   case SF_FORMAT_VORBIS:
   case SF_FORMAT_OPUS:
   case SF_FORMAT_ALAC_20:
   case SF_FORMAT_ALAC_24:
   case SF_FORMAT_ALAC_32:
   case 0x0080/*SF_FORMAT_MPEG_LAYER_I*/:
   case 0x0081/*SF_FORMAT_MPEG_LAYER_II*/:
   case 0x0082/*SF_FORMAT_MPEG_LAYER_III*/:
      bitsPerSample = 32;
      mSampleType = Sample_Float;
      break;

   case SF_FORMAT_IMA_ADPCM:
      bitsPerSample = 16;
      mSampleType = Sample_IMA4;
      break;

   case SF_FORMAT_MS_ADPCM:
      bitsPerSample = 16;
      mSampleType = Sample_MSADPCM;
      break;

   default:
      bitsPerSample = 16;
      mSampleType = Sample_Int16;
      break;
   }

   //------------------------------------------------------------
   // Block alignment logic for ADPCM formats
   //------------------------------------------------------------
   int byteBlockAlign = 0;
   int sampleBlockAlign = 1;

   if (mSampleType == Sample_IMA4 || mSampleType == Sample_MSADPCM)
   {
      SF_CHUNK_INFO inf = { "fmt ", 4, 0, NULL };
      SF_CHUNK_ITERATOR* iter = sf_get_chunk_iterator(sndFile, &inf);

      if (!iter || sf_get_chunk_size(iter, &inf) != SF_ERR_NO_ERROR || inf.datalen < 14)
         mSampleType = Sample_Int16;
      else
      {
         uint8_t* fmtbuf = (uint8_t*)malloc(inf.datalen);
         inf.data = fmtbuf;

         if (sf_get_chunk_data(iter, &inf) != SF_ERR_NO_ERROR)
            mSampleType = Sample_Int16;
         else
         {
            byteBlockAlign = fmtbuf[12] | (fmtbuf[13] << 8);
            int ch = sfinfo.channels;

            if (mSampleType == Sample_IMA4)
               sampleBlockAlign = (byteBlockAlign / ch - 4) / 4 * 8 + 1;
            else
               sampleBlockAlign = (byteBlockAlign / ch - 7) * 2 + 2;
         }
         dFree(fmtbuf);
      }
   }

   //------------------------------------------------------------
   // Commit alignment to class + VIO data
   //------------------------------------------------------------
   if (mSampleType == Sample_Int16)
   {
      sampleBlockAlign = 1;
      byteBlockAlign = sfinfo.channels * 2;
   }
   else if (mSampleType == Sample_Float)
   {
      sampleBlockAlign = 1;
      byteBlockAlign = sfinfo.channels * 4;
   }

   vio_data.sampleBlockAlign = sampleBlockAlign;
   vio_data.byteBlockAlign = byteBlockAlign;

   mSampleBlockAlign = sampleBlockAlign;
   mByteBlockAlign = byteBlockAlign;

   mFormat.set(sfinfo.channels, bitsPerSample * sfinfo.channels, sfinfo.samplerate, mSampleType);

   mSamples = sfinfo.frames;

   return true;
}

void SFXSndStream::_close()
{
   if (!sndFile)
      return;

   sf_close(sndFile);
   sndFile = NULL;
}

SFXSndStream* SFXSndStream::create(Stream* stream)
{
   SFXSndStream* sfxStream = new SFXSndStream();
   if (sfxStream->open(stream, true))
      return sfxStream;

   delete sfxStream;
   return NULL;
}

void SFXSndStream::reset()
{
   if (!sndFile)
      return;
   vio_data.offset = 0;
   sf_seek(sndFile, 0, SEEK_SET);
}

U32 SFXSndStream::read(U8* buffer, U32 length)
{
   if (!sndFile)
   {
      Con::errorf("SFXSndStream - read: Called on uninitialized or closed stream.");
      return 0;
   }

   if (!buffer)
   {
      Con::errorf("SFXSndStream - read: NULL buffer passed.");
      return 0;
   }

   const U32 bytesPerSample = mFormat.getBytesPerSample();
   if (bytesPerSample == 0)
   {
      Con::errorf("SFXSndStream - read: bytesPerSample is zero, format not initialized?");
      return 0;
   }

   U32 framesToRead = length / bytesPerSample;
   if (framesToRead == 0)
   {
      Con::errorf("SFXSndStream - read: length %d too small for bytesPerSample %d", length, bytesPerSample);
      return 0;
   }

   U32 framesRead = 0;

   switch (mSampleType)
   {
   case SFXSampleType::Sample_Int8: framesRead = sf_readf_int(sndFile, (int*)buffer, framesToRead);
      break;
   case SFXSampleType::Sample_Int16: framesRead = sf_readf_short(sndFile, (short*)buffer, framesToRead);
      break;
   case SFXSampleType::Sample_Float: framesRead = sf_readf_float(sndFile, (float*)buffer, framesToRead);
      break;
   case SFXSampleType::Sample_IMA4:
   case SFXSampleType::Sample_MSADPCM:
      framesRead = sf_read_raw(sndFile, buffer, framesToRead);
      break;
   default:
      break;
   }

   if (framesRead != framesToRead)
   {
      Con::errorf("SFXSndStream - read: %s", sf_strerror(sndFile));
   }

   sf_count_t currentFrame = sf_seek(sndFile, 0, SEEK_CUR);
   if (currentFrame >= sfinfo.frames - (sf_count_t)MAX_BUFFER)
   {
      sf_seek(sndFile, 0, SEEK_SET);
      vio_data.offset = 0;
   }


   return framesRead * mFormat.getBytesPerSample();
}

bool SFXSndStream::isEOS() const
{
   return (Parent::isEOS() || (mStream && vio_data.length == vio_data.offset));
}

U32 SFXSndStream::getPosition() const
{
   return vio_data.offset;
}

void SFXSndStream::setPosition(U32 offset)
{
   sf_seek(sndFile, offset / mFormat.getBytesPerSample(), SEEK_SET);
}

sf_count_t SFXSndStream::sndSeek(sf_count_t offset, int whence, void* user_data)
{
   VIO_DATA* vf = (VIO_DATA*)user_data;
   Stream* stream = reinterpret_cast<Stream*>(vf->data);

   switch (whence)
   {
   case SEEK_SET:
      vf->offset = offset;
      break;

   case SEEK_CUR:
      vf->offset = vf->offset + offset;
      break;

   case SEEK_END:
      vf->offset = vf->length - offset;
      break;
   default:
      break;
   };

   return stream->setPosition(vf->offset) ? 0 : -1;
}

sf_count_t SFXSndStream::sndRead(void* ptr, sf_count_t count, void* user_data)
{
   VIO_DATA* vf = (VIO_DATA*)user_data;
   Stream* stream = reinterpret_cast<Stream*>(vf->data);

   if (vf->offset + count > vf->length)
      count = vf->length - vf->offset;

   stream->read((U32)(count), ptr);
   vf->offset += count;

   return count;
}

sf_count_t SFXSndStream::sndWrite(const void* ptr, sf_count_t count, void* user_data)
{
   return sf_count_t();
}

sf_count_t SFXSndStream::sndTell(void* user_data)
{
   VIO_DATA* vf = (VIO_DATA*)user_data;
   return vf->offset;
}

sf_count_t SFXSndStream::sndFileLen(void* user_data)
{
   VIO_DATA* vf = (VIO_DATA*)user_data;
   Stream* stream = reinterpret_cast<Stream*>(vf->data);

   vf->length = stream->getStreamSize();

   return vf->length;
}
