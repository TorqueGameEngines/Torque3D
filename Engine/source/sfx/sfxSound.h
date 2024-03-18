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

#ifndef _SFXSOUND_H_
#define _SFXSOUND_H_

#ifndef _SFXSOURCE_H_
   #include "sfx/sfxSource.h"
#endif
#ifndef _SFXVOICE_H_
   #include "sfx/sfxVoice.h"
#endif
#ifndef _SIMBASE_H_
   #include "console/simBase.h"
#endif
#ifndef _MPOINT3_H_
   #include "math/mPoint3.h"
#endif
#ifndef _MMATRIX_H_
   #include "math/mMatrix.h"
#endif
#ifndef _TSTREAM_H_
   #include "core/stream/tStream.h"
#endif
#ifndef _SFXPROFILE_H_
   #include "sfx/sfxProfile.h"
#endif


class SFXBuffer;
class SFXDevice;



/// A scriptable controller playing a specific single sound file.
class SFXSound : public SFXSource,
                 public IPositionable< U32 >
{
      friend class SFXSystem;

      typedef SFXSource Parent;
   
   protected:

      /// Used by SFXSystem to create sources.
      static SFXSound* _create( SFXDevice* device, SFXProfile* profile );
      static SFXSound* _create( SFXDevice* device, const ThreadSafeRef< SFXStream >& stream, SFXDescription* description );

      /// Internal constructor used for sources.
      SFXSound( SFXProfile* profile, SFXDescription* description );
      
      /// The device specific voice which is used during
      /// playback.  By making it a SafePtr it will NULL
      /// automatically when the device is deleted.
      StrongWeakRefPtr< SFXVoice > mVoice;

      /// The reference counted device specific buffer used by 
      /// the voice for playback.
      StrongWeakRefPtr< SFXBuffer > mBuffer;

      /// The duration of the sound cached from the buffer in
      /// _initBuffer() used for managing virtual sources.
      U32 mDuration;

      ///Used for setPosition (time in miliseconds)
      U32 mSetPositionValue;

      /// Create a new voice for this source.
      bool _allocVoice( SFXDevice* device );

      /// Release the voice if the source has one.
      bool _releaseVoice();
      
      ///
      void _setBuffer( SFXBuffer* buffer );
      
      /// Reload the sound buffer.  Temporarily goes to virtualized playback when necessary.
      void _reloadBuffer();

      ///
      void _onProfileChanged( SFXProfile* profile )
      {
         if( profile == mTrack )
            _reloadBuffer();
      }
      
      // SFXSource.
      void _play() override;
      void _pause() override;
      void _stop() override;
      void _updateStatus() override;
      void _onParameterEvent( SFXParameter* parameter, SFXParameterEvent event ) override;
      void _updateVolume( const MatrixF& listener ) override;
      void _updatePitch() override;
      void _updatePriority() override;
      void _setMinMaxDistance( F32 min, F32 max ) override;
      void _setCone( F32 innerAngle, F32 outerAngle, F32 outerVolume ) override;

   public:

      DECLARE_CONOBJECT( SFXSound );

      /// The default constructor is *only* here to satisfy the
      /// construction needs of IMPLEMENT_CONOBJECT.  It does not
      /// create a valid source!
      explicit SFXSound();

      /// This is normally called from the system to 
      /// detect if this source has been assigned a
      /// voice for playback.
      bool hasVoice() const { return mVoice != NULL; }

      /// Return the current playback position in milliseconds.
      /// @note For looping sources, this returns the position in the current cycle.
      U32 getPosition() const override;

      /// Set the current playback position in milliseconds.
      void setPosition( U32 ms ) override;

      /// Returns the source's total playback time in milliseconds.
      U32 getDuration() const { return mDuration; }

      /// Return true if the sound stream tied to the source is currently in a buffer underrun situation.
      bool isBlocked() const { return ( mVoice && mVoice->getStatus() == SFXStatusBlocked ); }
      
      /// Returns true if this is a continuously streaming source.
      bool isStreaming() const { return mDescription ? mDescription->mIsStreaming : false; }

      /// Returns true if the source's associated data is ready for playback.
      bool isReady() const;

      /// Return the SFXProfile datablock attached to this sound.
      SFXProfile* getProfile() const;

      /// Used to sort sources by attenuated volume and channel priority.
      static S32 QSORT_CALLBACK qsortCompare( const void* item1, const void* item2 );

      // SFXSource.
      void setTransform( const MatrixF& transform ) override;
      void setVelocity( const VectorF& velocity ) override;
      bool isVirtualized() const override;
      F32 getElapsedPlayTimeCurrentCycle() const override;
      F32 getTotalPlayTime() const override;

      // SimObject.
      void onRemove() override;
      void onDeleteNotify( SimObject* object ) override;
};

#endif // !_SFXSOUND_H_
