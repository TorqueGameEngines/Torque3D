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

#include "sfx/sfxFileStream.h"
#include "core/stream/fileStream.h"
#include "console/console.h"
#include "core/util/safeDelete.h"
#include "sfx/media/sfxSndStream.h"

SFXFileStream* SFXFileStream::create( String filename )
{
    SFXFileStream *sfxStream = NULL;

    Stream *stream = FileStream::createAndOpen(filename, Torque::FS::File::Read );
    if ( !stream )
        return NULL;

    // Note that the creation function swallows up the 
    // resource stream and will take care of deleting it.
    sfxStream = SFXSndStream::create( stream );
    if ( sfxStream )
        return sfxStream;

   return NULL;
}

bool SFXFileStream::exists( String filename )
{
      if( Torque::FS::IsFile(filename) )
         return true;
   return false;
}

SFXFileStream::SFXFileStream()
   :  mStream( NULL ),
      mOwnStream( false ),
      mFormat( 0, 0, 0 ),
      mSamples( 0 )
{
}

SFXFileStream::SFXFileStream( const SFXFileStream& cloneFrom )
{
   mStream = cloneFrom.mStream->clone();
   if( !mStream )
   {
      Con::errorf( "SFXFileStream::SFXFileStream() - Failed to clone source stream" );
      return;
   }

   mOwnStream  = true;
   mFormat     = cloneFrom.mFormat;
   mSamples    = cloneFrom.mSamples;
}


SFXFileStream::~SFXFileStream()
{
   // If the stream is still open, close it now.  _close()
   // should usually be called by the destructor of derived classes,
   // but it their constructor fails, these won't even run.
   
   if( mStream && mOwnStream )
      SAFE_DELETE( mStream );
}

bool SFXFileStream::open( Stream *stream, bool ownStream )
{
   AssertFatal( stream, "SFXFileStream::open() - Got null stream!" );   

   close();

   mStream = stream;
   mOwnStream = ownStream;

   if( _readHeader() )
   {
      reset(); // Make sure we're set to read sample data.
      return true;
   }
   else
      return false;
}

void SFXFileStream::close()
{
   if ( !mStream )
      return;

   // Let the overloaded class cleanup.
   _close();

   // We only close it if we own it.
   if ( mOwnStream )
      SAFE_DELETE( mStream );

   // Reset these to make it easier to detect bugs.
   mFormat.set( 0, 0, 0 );
   mSamples = 0;
}

bool SFXFileStream::isEOS() const
{
   if ( !mStream )
      return true;

   return mStream->getStatus() != Stream::Ok;
}
