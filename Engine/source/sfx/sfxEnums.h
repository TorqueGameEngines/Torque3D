#pragma once
#ifndef _SFXENUMS_H_

enum SFXProviderType
{
   OpenAL,
   XAudio,
   DirectSound,
   NullProvider,
   SFXProviderType_Count
};

enum SFXDeviceType
{
   Output,
   Input
};

/// The sound playback state.
enum SFXStatus
{
   /// Initial state; no operation yet performed on sound.
   SFXStatusNull,

   /// Sound is playing.
   SFXStatusPlaying,

   /// Sound has been stopped.
   SFXStatusStopped,

   /// Sound is paused.
   SFXStatusPaused,

   /// Sound stream is starved and playback blocked.
   SFXStatusBlocked,

   /// Temporary state while transitioning to another state.  This is used when multiple
   /// threads concurrently maintain a status and need to perform a sequence of actions before
   /// being able to fully go from a previous to a new current state.  In this case, the
   /// transition state marks the status as being under update on another thread.
   ///
   /// @note Not all places that use SFXStatus actually use this state.
   SFXStatusTransition,
};

/// Animatable channels in the SFX system.
enum SFXChannel
{
   SFXChannelVolume,
   SFXChannelPitch,
   SFXChannelPriority,
   SFXChannelPositionX,
   SFXChannelPositionY,
   SFXChannelPositionZ,
   SFXChannelRotationX,
   SFXChannelRotationY,
   SFXChannelRotationZ,
   SFXChannelVelocityX,
   SFXChannelVelocityY,
   SFXChannelVelocityZ,
   SFXChannelMinDistance,
   SFXChannelMaxDistance,
   SFXChannelConeInsideAngle,
   SFXChannelConeOutsideAngle,
   SFXChannelConeOutsideVolume,
   SFXChannelCursor,
   SFXChannelStatus,
   SFXChannelUser0,
   SFXChannelUser1,
   SFXChannelUser2,
   SFXChannelUser3,

   /// Total number of animatable channels.
   SFX_NUM_CHANNELS
};

/// Rolloff curve used for distance volume attenuation of 3D sounds.
enum SFXDistanceModel
{
   SFXDistanceModelLinear,             ///< Volume decreases linearly from min to max where it reaches zero.
   SFXDistanceModelLogarithmic,        ///< Volume halves every min distance steps starting from min distance; attenuation stops at max distance.
   SFXDistanceModelExponent,           /// exponential falloff for distance attenuation.
};


#endif // !_SFXENUMS_H_
