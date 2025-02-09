#include "sfx/sfxApi.h"

IMPLEMENT_SCOPE(SFXAPI, SFX, ,
   "Sound subystem.");

ImplementEnumType(SFXStatus,
   "Playback status of sound source.\n"
   "@ingroup SFX")
   { SFXStatusPlaying, "Playing",
         "The source is currently playing."
   },
   { SFXStatusStopped, "Stopped",
      "Playback of the source is stopped.  When transitioning to Playing state, playback will start at the beginning "
         "of the source." },
   { SFXStatusPaused, "Paused",
      "Playback of the source is paused.  Resuming playback will play from the current playback position." },
EndImplementEnumType;

ImplementEnumType(SFXDistanceModel,
   "Type of volume distance attenuation curve.\n"
   "The distance model determines the falloff curve applied to the volume of 3D sounds over distance.\n\n"
   "@ref SFXSource_volume\n\n"
   "@ref SFX_3d\n\n"
   "@ingroup SFX")
   { SFXDistanceModelLinear, "Linear",
         "Volume attenuates linearly from the references distance onwards to max distance where it reaches zero."
   },
   { SFXDistanceModelLogarithmic, "Logarithmic",
      "Volume attenuates logarithmically starting from the reference distance and halving every reference distance step from there on. "
      "Attenuation stops at max distance but volume won't reach zero." },
   { SFXDistanceModelExponent, "Exponential",
   "Volume attenuates exponentially starting from the reference distance and attenuating every reference distance step by the rolloff factor. "
   "Attenuation stops at max distance but volume won't reach zero." },
EndImplementEnumType;

ImplementEnumType(SFXChannel,
   "Channels are individual properties of sound sources that may be animated over time.\n\n"
   "@see SFXParameter\n\n"
   "@ref SFX_interactive\n\n"
   "@ingroup SFX")
   { SFXChannelVolume, "Volume",
         "Channel controls volume level of attached sound sources.\n"
         "@see SFXDescription::volume"
   },
   { SFXChannelPitch,              "Pitch",
      "Channel controls pitch of attached sound sources.\n"
      "@see SFXDescription::pitch" },
   { SFXChannelPriority,           "Priority",
      "Channel controls virtualizaton priority level of attached sound sources.\n"
      "@see SFXDescription::priority" },
   { SFXChannelPositionX,          "PositionX",
      "Channel controls X coordinate of 3D sound position of attached sources." },
   { SFXChannelPositionY,          "PositionY",
      "Channel controls Y coordinate of 3D sound position of attached sources." },
   { SFXChannelPositionZ,          "PositionZ",
      "Channel controls Z coordinate of 3D sound position of attached sources." },
   { SFXChannelRotationX,          "RotationX",
      "Channel controls X rotation (in degrees) of 3D sound orientation of attached sources." },
   { SFXChannelRotationY,          "RotationY",
      "Channel controls Y rotation (in degrees) of 3D sound orientation of attached sources." },
   { SFXChannelRotationZ,          "RotationZ",
      "Channel controls Z rotation (in degrees) of 3D sound orientation of attached sources." },
   { SFXChannelVelocityX,          "VelocityX",
      "Channel controls X coordinate of 3D sound velocity vector of attached sources." },
   { SFXChannelVelocityY,          "VelocityY",
      "Channel controls Y coordinate of 3D sound velocity vector of attached sources." },
   { SFXChannelVelocityZ,          "VelocityZ",
      "Channel controls Z coordinate of 3D sound velocity vector of attached sources." },
   { SFXChannelMinDistance,        "ReferenceDistance",
      "Channel controls reference distance of 3D sound of attached sources.\n"
      "@see SFXDescription::referenceDistance" },
   { SFXChannelMaxDistance,        "MaxDistance",
      "Channel controls max volume attenuation distance of 3D sound of attached sources.\n"
      "@see SFXDescription::maxDistance" },
   { SFXChannelConeInsideAngle,    "ConeInsideAngle",
      "Channel controls angle (in degrees) of 3D sound inner volume cone of attached sources.\n"
      "@see SFXDescription::coneInsideAngle" },
   { SFXChannelConeOutsideAngle,   "ConeOutsideAngle",
      "Channel controls angle (in degrees) of 3D sound outer volume cone of attached sources.\n"
      "@see SFXDescription::coneOutsideAngle" },
   { SFXChannelConeOutsideVolume,  "ConeOutsideVolume",
      "Channel controls volume outside of 3D sound outer cone of attached sources.\n"
      "@see SFXDescription::coneOutsideVolume" },
   { SFXChannelCursor,             "Cursor",
      "Channel controls playback cursor of attached sound sources.\n\n"
      "@note Be aware that different types of sound sources interpret play cursor positions differently "
         "or do not actually have play cursors (these sources will ignore the channel)." },
   { SFXChannelStatus,             "Status",
      "Channel controls playback status of attached sound sources.\n\n"
      "The channel's value is rounded down to the nearest integer and interpreted in the following way:\n"
      "- 1: Play\n"
      "- 2: Stop\n"
      "- 3: Pause\n\n" },
   { SFXChannelUser0,              "User0",
      "Channel available for custom use.  By default ignored by sources.\n\n"
      "@see SFXSource::onParameterValueChange" },
   { SFXChannelUser1,              "User1",
      "Channel available for custom use.  By default ignored by sources.\n\n"
      "@see SFXSource::onParameterValueChange" },
   { SFXChannelUser2,              "User2",
      "Channel available for custom use.  By default ignored by sources.\n\n"
      "@see SFXSource::onParameterValueChange" },
   { SFXChannelUser3,              "User3",
      "Channel available for custom use.  By default ignored by sources.\n\n"
      "@see SFXSource::onParameterValueChange" }
EndImplementEnumType;

ImplementEnumType(SFXProviderType,
   "The sfx provider.\n"
   "@ingroup SFX")
   { SFXProviderType::OpenAL,       "OpenAL",      "Openal Provider." },
   { SFXProviderType::DirectSound,  "DirectSound", "DirectSound Provider." },
   { SFXProviderType::XAudio,       "XAudio",      "XAudio Provider." },
   { SFXProviderType::NullProvider, "NullProvider","NullProvider Provider." }
EndImplementEnumType;
