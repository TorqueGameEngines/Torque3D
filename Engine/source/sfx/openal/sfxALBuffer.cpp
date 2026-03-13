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

#include "sfx/openal/sfxALBuffer.h"
#include "sfx/openal/sfxALVoice.h"
#include "sfx/openal/sfxALDevice.h"
#include "sfx/sfxDescription.h"
#include "console/console.h"


//#define DEBUG_SPEW


SFXALBuffer* SFXALBuffer::create(   const ThreadSafeRef< SFXStream >& stream,
                                    SFXDescription* description,
                                    bool useHardware )
{
   if( !_sfxFormatToALFormat( stream->getFormat() ) )
   {
      Con::errorf( "SFXALBuffer::create() - SFXFormat not supported by OpenAL" );
      return NULL;
   }

   SFXALBuffer *buffer = new SFXALBuffer( stream,
                                          description,
                                          useHardware );

   return buffer;
}

SFXALBuffer::SFXALBuffer(  const ThreadSafeRef< SFXStream >& stream,
                           SFXDescription* description,
                           bool useHardware )
   :  Parent( stream, description ),
      mIs3d( description->mIs3D ),
      mUseHardware( useHardware )
{
   // Set up device buffers.

   if( !isStreaming() )
      alGenBuffers( 1, &mALBuffer );
}

SFXALBuffer::~SFXALBuffer()
{
   if( _getUniqueVoice() )
      _getUniqueVoice()->stop();

   // Release buffers.
   if ( alIsBuffer( mALBuffer ))
      alDeleteBuffers( 1, &mALBuffer );

   while( mFreeBuffers.size() )
   {
      ALuint buffer = mFreeBuffers.last();
      alDeleteBuffers( 1, &buffer );
      mFreeBuffers.pop_back();
   }
}

void SFXALBuffer::write( SFXInternal::SFXStreamPacket* const* packets, U32 num )
{
   using namespace SFXInternal;
   
   if( !num )
      return;
   
   // If this is not a streaming buffer, just load the data into our single
   // static buffer.
   
   if( !isStreaming() )
   {
      SFXStreamPacket* packet = packets[ num - 1 ];
      
      ALenum alFormat = _sfxFormatToALFormat( getFormat() );
      AssertFatal( alFormat != 0, "SFXALBuffer::write() - format unsupported" );
      
      alBufferData( mALBuffer, alFormat,
         packet->data, packet->mSizeActual, getFormat().getSamplesPerSecond() );
         
      destructSingle( packet );
      return;
   }

   MutexHandle mutex;
   mutex.lock( &_getUniqueVoice()->mMutex, true );

   // Unqueue processed packets.

   ALuint source = _getUniqueVoice()->mSourceName;
   ALint numProcessed;
   alGetSourcei( source, AL_BUFFERS_PROCESSED, &numProcessed );
   
   for( U32 i = 0; i < numProcessed; ++ i )
   {
      // Unqueue the buffer.
      
      ALuint buffer;
      alSourceUnqueueBuffers( source, 1, &buffer );
      
      // Update the sample offset on the voice.
      
      ALint size;
      alGetBufferi( buffer, AL_SIZE, &size );
      _getUniqueVoice()->mSampleOffset += size / getFormat().getBytesPerSample();
      
      // Push the buffer onto the freelist.
      
      mFreeBuffers.push_back( buffer );
   }

   // Queue buffers.

   for( U32 i = 0; i < num; ++ i )
   {
      SFXStreamPacket* packet = packets[ i ];
      
      // Allocate a buffer.
      
      ALuint buffer;
      if( mFreeBuffers.size() )
      {
         buffer = mFreeBuffers.last();
         mFreeBuffers.pop_back();
      }
      else
         alGenBuffers( 1, &buffer );
         
      // Upload the data.
      
      ALenum alFormat = _sfxFormatToALFormat( getFormat() );
      AssertFatal( alFormat != 0, "SFXALBuffer::write() - format unsupported" );
      AssertFatal( alIsBuffer( buffer ), "SFXALBuffer::write() - buffer invalid" );
      
      alBufferData( buffer, alFormat,
         packet->data, packet->mSizeActual, getFormat().getSamplesPerSecond() );
      
      destructSingle( packet );
      
      // Queue the buffer.
      
      alSourceQueueBuffers( source, 1, &buffer );
   }
}

void SFXALBuffer::_flush()
{
   AssertFatal( isStreaming(), "SFXALBuffer::_flush() - not a streaming buffer" );
   AssertFatal( SFXInternal::isSFXThread(), "SFXALBuffer::_flush() - not on SFX thread" );

   #ifdef DEBUG_SPEW
   Platform::outputDebugString( "[SFXALBuffer] Flushing buffer" );
   #endif

   _getUniqueVoice()->_stop();

   MutexHandle mutex;
   mutex.lock( &_getUniqueVoice()->mMutex, true );

   ALuint source = _getUniqueVoice()->mSourceName;

   ALint numQueued;
   alGetSourcei( source, AL_BUFFERS_QUEUED, &numQueued );

   for( U32 i = 0; i < numQueued; ++ i )
   {
      ALuint buffer;
      alSourceUnqueueBuffers( source, 1, &buffer );
      mFreeBuffers.push_back( buffer );
   }

   _getUniqueVoice()->mSampleOffset = 0;
   
   //RD: disabling hack for now; rewritten queueing should be able to cope
   #if 0 //def TORQUE_OS_MAC
   
   //WORKAROUND: Ugly hack on Mac.  Apparently there's a bug in the OpenAL implementation
   // that will cause AL_BUFFERS_PROCESSED to not be reset as it should be causing write()
   // to fail.  Brute-force this and just re-create the source.  Let's pray that nobody
   // issues any concurrent state changes on the voice resulting in us losing state here.
   
   ALuint newSource;
   alGenSources( 1, &newSource );
   
   #define COPY_F( name ) \
   { \
      F32 val; \
      alGetSourcef( source, name, &val ); \
      alSourcef( source, name, val ); \
   }
   
   #define COPY_FV( name ) \
   { \
      VectorF val; \
      alGetSourcefv( source, name, val ); \
      alSourcefv( source, name, val ); \
   }
   
   COPY_F( AL_REFERENCE_DISTANCE );
   COPY_F( AL_MAX_DISTANCE );
   COPY_F( AL_GAIN );
   COPY_F( AL_PITCH );
   COPY_F( AL_CONE_INNER_ANGLE );
   COPY_F( AL_CONE_OUTER_ANGLE );
   COPY_F( AL_CONE_OUTER_GAIN );
   
   COPY_FV( AL_VELOCITY );
   COPY_FV( AL_POSITION );
   COPY_FV( AL_DIRECTION );
   
   _getUniqueVoice()->mSourceName = newSource;
   alDeleteSources( 1, &source );

   #endif
}
