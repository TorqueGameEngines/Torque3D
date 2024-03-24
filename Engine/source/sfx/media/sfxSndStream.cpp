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

   vio.get_filelen   = sndFileLen;
   vio.seek          = sndSeek;
   vio.read          = sndRead;
   vio.write         = sndWrite;
   vio.tell          = sndTell;

   vio_data.length = 0;
   vio_data.offset = 0;
   vio_data.data = mStream;

   if ((sndFile = sf_open_virtual(&vio, SFM_READ, &sfinfo, &vio_data)) == NULL)
   {
      Con::printf("SFXSndStream - _readHeader failed: %s", sf_strerror(sndFile));
      return false;
   }

   S32 bitsPerSample = 0;
   switch ((sfinfo.format & SF_FORMAT_SUBMASK))
   {
   case SF_FORMAT_PCM_S8:
   case SF_FORMAT_PCM_U8:
      bitsPerSample = 8;
      break;
   case SF_FORMAT_PCM_16:
   case SF_FORMAT_VORBIS:
      bitsPerSample = 16;
      break;
   case SF_FORMAT_PCM_24:
      bitsPerSample = 24;
      break;
   case SF_FORMAT_PCM_32:
   case SF_FORMAT_FLOAT:
      bitsPerSample = 32;
      break;
   default:
      // missed, set it to 16 anyway.
      bitsPerSample = 16;
      break;
   }

   mFormat.set(sfinfo.channels, bitsPerSample * sfinfo.channels, sfinfo.samplerate);

   mSamples = sfinfo.frames;

   return true;
}

void SFXSndStream::_close()
{
   if (!sndFile)
      return;

   sf_close(sndFile);
}

SFXSndStream* SFXSndStream::create(Stream* stream)
{
   SFXSndStream* sfxStream = new SFXSndStream();
   if (sfxStream->open(stream, true))
      return sfxStream;

   delete sfxStream;
   return nullptr;
}

void SFXSndStream::reset()
{
   vio_data.offset = 0;
}

U32 SFXSndStream::read(U8* buffer, U32 length)
{
   U32 framesRead = 0;

   framesRead = sf_readf_short(sndFile, (short*)buffer, sfinfo.frames);
   if (framesRead != sfinfo.frames)
   {
      Con::errorf("SFXSndStream - read: %s", sf_strerror(sndFile));
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

