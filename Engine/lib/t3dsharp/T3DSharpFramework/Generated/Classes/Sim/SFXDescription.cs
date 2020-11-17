using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using T3DSharpFramework.Engine;
using T3DSharpFramework.Engine.Util;
using T3DSharpFramework.Generated.Classes.Global;
using T3DSharpFramework.Generated.Classes.Reflection;
using T3DSharpFramework.Generated.Classes.Sim;
using T3DSharpFramework.Generated.Classes.Sim.Net;
using T3DSharpFramework.Generated.Enums.Global;
using T3DSharpFramework.Generated.Enums.Reflection;
using T3DSharpFramework.Generated.Structs.Global;
using T3DSharpFramework.Generated.Structs.Gui;
using T3DSharpFramework.Generated.Structs.Math;
using T3DSharpFramework.Interop;

namespace T3DSharpFramework.Generated.Classes.Sim {
    /// <summary>A description for how a sound should be played.</summary>
    /// <description>
    /// SFXDescriptions are used by the sound system to collect all parameters needed to set up a given sound for playback.  This includes information like its volume level, its pitch shift, etc. as well as more complex information like its fade behavior, 3D properties, and per-sound reverb properties.
    /// 
    /// Any sound playback will require a valid SFXDescription.
    /// 
    /// As datablocks, SFXDescriptions can be set up as either networked datablocks or non-networked datablocks, though it generally makes sense to keep all descriptions non-networked since they will be used exclusively by clients.
    /// </description>
    /// <code>
    /// // A description for a 3D sound with a reasonable default range setting.
    /// // The description is set up to assign sounds to the AudioChannelEffects source group
    /// // (defined in the core scripts).  An alternative means to achieve this is to use the
    /// // AudioEffects description as a copy source (": AudioEffects").
    /// 
    /// singleton SFXDescription( Audio3DSound )
    /// {
    ///   sourceGroup       = AudioChannelEffects;
    ///   is3D              = true;
    ///   referenceDistance = 20.0;
    ///   maxDistance       = 100.0;
    /// };
    /// </code>
    public unsafe class SFXDescription : SimDataBlock {
        public SFXDescription(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public SFXDescription(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public SFXDescription(string pName) 
            : this(pName, false) {
        }
        
        public SFXDescription(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public SFXDescription(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public SFXDescription(SimObject pObj) 
            : base(pObj) {
        }
        
        public SFXDescription(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct StaticGetType__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate IntPtr _StaticGetType(StaticGetType__Args args);
            private static _StaticGetType _StaticGetTypeFunc;
            internal static _StaticGetType StaticGetType() {
                if (_StaticGetTypeFunc == null) {
                    _StaticGetTypeFunc =
                        (_StaticGetType)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSFXDescription_staticGetType"), typeof(_StaticGetType));
                }
                
                return _StaticGetTypeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Create__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate IntPtr _Create(Create__Args args);
            private static _Create _CreateFunc;
            internal static _Create Create() {
                if (_CreateFunc == null) {
                    _CreateFunc =
                        (_Create)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSFXDescription_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the SFXDescription class.
        /// </description>
        /// <returns>The type info object for SFXDescription</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Group that sources playing with this description should be put into.
        /// 
        /// When a sound source is allocated, it will be made a child of the source group that is listed in its 
        /// description.  This group will then modulate several properties of the sound as it is played.
        /// 
        /// For example, one use of groups is to segregate sounds so that volume levels of different sound groups such as interface audio and game audio can be controlled independently.
        /// </description>
        /// </value>
        public SFXSource SourceGroup {
            get => GenericMarshal.StringTo<SFXSource>(GetFieldValue("sourceGroup"));
            set => SetFieldValue("sourceGroup", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Base volume level for the sound.
        /// 
        /// This will be the starting point for volume attenuation on the sound.  The final effective volume of a sound will be dependent on a number of parameters.
        /// 
        /// Must be between 0 (mute) and 1 (full volume).  Default is 1.
        /// </description>
        /// </value>
        public float Volume {
            get => GenericMarshal.StringTo<float>(GetFieldValue("volume"));
            set => SetFieldValue("volume", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Pitch shift to apply to playback.
        /// 
        /// The pitch assigned to a sound determines the speed at which it is played back.  A pitch shift of 1 plays the sound at its default speed.  A greater shift factor speeds up playback and a smaller shift factor slows it down.
        /// 
        /// Must be >0.  Default is 1.
        /// </description>
        /// </value>
        public float Pitch {
            get => GenericMarshal.StringTo<float>(GetFieldValue("pitch"));
            set => SetFieldValue("pitch", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// If true, the sound will be played in an endless loop.
        /// 
        /// Default is false.
        /// </description>
        /// </value>
        public bool IsLooping {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("isLooping"));
            set => SetFieldValue("isLooping", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Priority level for virtualization of sounds (1 = base level).
        /// When there are more concurrently active sounds than supported by the audio mixer, some of the sounds need to be culled.  Which sounds are culled first depends primarily on total audibility of individual sounds. However, the priority of invidual sounds may be decreased or decreased through this field.
        /// </description>
        /// </value>
        public float Priority {
            get => GenericMarshal.StringTo<float>(GetFieldValue("priority"));
            set => SetFieldValue("priority", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Whether the sound is allowed to be mixed in hardware.
        /// If true, the sound system will try to allocate the voice for the sound directly on the sound hardware for mixing by the hardware mixer.  Be aware that a hardware mixer may not provide all features available to sounds mixed in software.
        /// </description>
        /// <remarks> This flag currently only takes effect when using FMOD.
        /// 
        /// </remarks>
        /// <remarks> Generally, it is preferable to let sounds be mixed in software.
        /// 
        /// </remarks>
        /// </value>
        public bool UseHardware {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("useHardware"));
            set => SetFieldValue("useHardware", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Names of the parameters to which sources using this description will automatically be linked.
        /// 
        /// Individual parameters are identified by their #internalName.
        /// </description>
        /// </value>
        public DynamicFieldVector<string> Parameters {
            get => new DynamicFieldVector<string>(
                    this, 
                    "parameters", 
                    8, 
                    val => GenericMarshal.StringTo<string>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Number of seconds to gradually fade in volume from zero when playback starts.
        /// Must be >= 0.
        /// </description>
        /// </value>
        public float FadeInTime {
            get => GenericMarshal.StringTo<float>(GetFieldValue("fadeInTime"));
            set => SetFieldValue("fadeInTime", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Number of seconds to gradually fade out volume down to zero when playback is stopped or paused.
        /// Must be >=0.
        /// </description>
        /// </value>
        public float FadeOutTime {
            get => GenericMarshal.StringTo<float>(GetFieldValue("fadeOutTime"));
            set => SetFieldValue("fadeOutTime", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Easing curve for fade-in transition.
        /// Volume fade-ins will interpolate volume along this curve.
        /// </description>
        /// </value>
        public EaseF FadeInEase {
            get => GenericMarshal.StringTo<EaseF>(GetFieldValue("fadeInEase"));
            set => SetFieldValue("fadeInEase", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Easing curve for fade-out transition.
        /// Volume fade-outs will interpolate volume along this curve.
        /// </description>
        /// </value>
        public EaseF FadeOutEase {
            get => GenericMarshal.StringTo<EaseF>(GetFieldValue("fadeOutEase"));
            set => SetFieldValue("fadeOutEase", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Fade each cycle of a loop in and/or out; otherwise only fade-in first cycle.
        /// By default, volume fading is applied to the beginning and end of the playback range, i.e. a fade-in segment is placed at the beginning of the sound and a fade-out segment is paced at the end of a sound.  However, when looping playback, this may be undesirable as each iteration of the sound will then have a fade-in and fade-out effect.
        /// 
        /// To set up looping sounds such that a fade-in is applied only when the sound is first started (or playback resumed) and a fade-out is only applied when the sound is explicitly paused or stopped, set this field to true.
        /// 
        /// Default is false.
        /// </description>
        /// </value>
        public bool FadeLoops {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("fadeLoops"));
            set => SetFieldValue("fadeLoops", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// If true, sounds played with this description will have a position and orientation in space.
        /// Unlike a non-positional sound, a 3D sound will have its volume attenuated depending on the distance to the listener in space.  The farther the sound moves away from the listener, the less audible it will be.
        /// 
        /// Non-positional sounds, in contrast, will remain at their original volume regardless of where the listener is.
        /// </description>
        /// <remarks> Whether a sound is positional or non-positional cannot be changed once the sound was created so this field determines up front which is the case for a given sound.
        /// 
        /// </remarks>
        /// </value>
        public bool Is3D {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("is3D"));
            set => SetFieldValue("is3D", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Distance at which volume attenuation begins.
        /// Up to this distance, the sound retains its base volume.
        /// 
        /// In the linear distance model, the volume will linearly from this distance onwards up to maxDistance where it reaches zero.
        /// 
        /// In the logarithmic distance model, the reference distance determine how fast the sound volume decreases with distance.  Each referenceDistance steps (scaled by the rolloff factor), the volume halves.
        /// 
        /// A rule of thumb is that for sounds that require you to be close to hear them in the real world, set the reference distance to small values whereas for sounds that are widely audible set it to larger values.
        /// 
        /// Only applies to 3D sounds.
        /// </description>
        /// <see cref="LevelInfo::soundDistanceModel" />
        /// </value>
        public float ReferenceDistance {
            get => GenericMarshal.StringTo<float>(GetFieldValue("referenceDistance"));
            set => SetFieldValue("referenceDistance", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The distance at which attenuation stops.
        /// In the linear distance model, the attenuated volume will be zero at this distance.
        /// 
        /// In the logarithmic model, attenuation will simply stop at this distance and the sound will keep its attenuated volume from there on out.  As such, it primarily functions as a cutoff factor to exponential distance attentuation to limit the number of voices relevant to updates.
        /// 
        /// Only applies to 3D sounds.
        /// </description>
        /// <see cref="LevelInfo::soundDistanceModel" />
        /// </value>
        public float MaxDistance {
            get => GenericMarshal.StringTo<float>(GetFieldValue("maxDistance"));
            set => SetFieldValue("maxDistance", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Bounds on random displacement of 3D sound positions.
        /// When a 3D sound is created and given its initial position in space, this field is used to determine the amount of randomization applied to the actual position given to the sound system.
        /// 
        /// The randomization uses the following scheme:
        /// </description>
        /// </value>
        public Point3F ScatterDistance {
            get => GenericMarshal.StringTo<Point3F>(GetFieldValue("scatterDistance"));
            set => SetFieldValue("scatterDistance", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Inner sound cone angle in degrees.
        /// This value determines the angle of the inner volume cone that protrudes out in the direction of a sound.  Within this cone, the sound source retains full volume that is unaffected by sound cone settings (though still affected by distance attenuation.)
        /// 
        /// Valid values are from 0 to 360. Must be less than coneOutsideAngle. Default is 360. Only for 3D sounds.
        /// </description>
        /// </value>
        public int ConeInsideAngle {
            get => GenericMarshal.StringTo<int>(GetFieldValue("coneInsideAngle"));
            set => SetFieldValue("coneInsideAngle", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Outer sound cone angle in degrees.
        /// This value determines the angle of the outer volume cone that protrudes out in the direction of a sound and surrounds the inner volume cone.  Within this cone, volume will linearly interpolate from the outer cone hull inwards to the inner coner hull starting with the base volume scaled by coneOutsideVolume and ramping up/down to the full base volume.
        /// 
        /// Valid values are from 0 to 360.  Must be >= coneInsideAngle.  Default is 360.  Only for 3D sounds.
        /// </description>
        /// </value>
        public int ConeOutsideAngle {
            get => GenericMarshal.StringTo<int>(GetFieldValue("coneOutsideAngle"));
            set => SetFieldValue("coneOutsideAngle", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Determines the volume scale factor applied the a source's base volume level outside of the outer cone.
        /// In the outer cone, starting from outside the inner cone, the scale factor smoothly interpolates from 1.0 (within the inner cone) to this value.  At the moment, the allowed range is 0.0 (silence) to 1.0 (no attenuation) as amplification is only supported on XAudio2 but not on the other devices.
        /// 
        /// Only for 3D sound.
        /// </description>
        /// </value>
        public float ConeOutsideVolume {
            get => GenericMarshal.StringTo<float>(GetFieldValue("coneOutsideVolume"));
            set => SetFieldValue("coneOutsideVolume", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Scale factor to apply to logarithmic distance attenuation curve.  If -1, the global rolloff setting is used.
        /// </description>
        /// <remarks> Per-sound rolloff is only supported on OpenAL and FMOD at the moment.  With other divices, the global rolloff setting is used for all sounds.
        /// </remarks>
        /// <see cref="LevelInfo::soundDistanceModel" />
        /// </value>
        public float RolloffFactor {
            get => GenericMarshal.StringTo<float>(GetFieldValue("rolloffFactor"));
            set => SetFieldValue("rolloffFactor", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// If true, incrementally stream sounds; otherwise sounds are loaded in full.
        /// </description>
        /// </value>
        public bool IsStreaming {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("isStreaming"));
            set => SetFieldValue("isStreaming", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Number of seconds of sample data per single streaming packet.
        /// This field allows to fine-tune streaming for individual sounds.  The streaming system processes streamed sounds in batches called packets.  Each packet will contain a set amount of sample data determined by this field.  The greater its value, the more sample data each packet contains, the more work is done per packet.
        /// </description>
        /// <remarks> This field only takes effect when Torque's own sound system performs the streaming. When FMOD is used, this field is ignored and streaming is performed by FMOD.
        /// 
        /// </remarks>
        /// </value>
        public int StreamPacketSize {
            get => GenericMarshal.StringTo<int>(GetFieldValue("streamPacketSize"));
            set => SetFieldValue("streamPacketSize", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Number of sample packets to read and buffer in advance.
        /// This field determines the number of packets that the streaming system will try to keep buffered in advance.  As such it determines the number of packets that can be consumed by the sound device before the playback queue is running dry.  Greater values thus allow for more lag in the streaming pipeline.
        /// </description>
        /// <remarks> This field only takes effect when Torque's own sound system performs the streaming. When FMOD is used, this field is ignored and streaming is performed by FMOD.
        /// 
        /// </remarks>
        /// </value>
        public int StreamReadAhead {
            get => GenericMarshal.StringTo<int>(GetFieldValue("streamReadAhead"));
            set => SetFieldValue("streamReadAhead", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// If true, use the reverb properties defined here on sounds.
        /// By default, sounds will be assigned a generic reverb profile.  By setting this flag to true, a custom reverb setup can be defined using the "Reverb" properties that will then be assigned to sounds playing with the description.
        /// </description>
        /// </value>
        public bool UseCustomReverb {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("useCustomReverb"));
            set => SetFieldValue("useCustomReverb", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Density of reverb environment.
        /// </description>
        /// </value>
        public float ReverbDensity {
            get => GenericMarshal.StringTo<float>(GetFieldValue("reverbDensity"));
            set => SetFieldValue("reverbDensity", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Environment diffusion.
        /// </description>
        /// </value>
        public float ReverbDiffusion {
            get => GenericMarshal.StringTo<float>(GetFieldValue("reverbDiffusion"));
            set => SetFieldValue("reverbDiffusion", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Reverb Gain Level.
        /// </description>
        /// </value>
        public float ReverbGain {
            get => GenericMarshal.StringTo<float>(GetFieldValue("reverbGain"));
            set => SetFieldValue("reverbGain", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Reverb Gain to high frequencies
        /// </description>
        /// </value>
        public float ReverbGainHF {
            get => GenericMarshal.StringTo<float>(GetFieldValue("reverbGainHF"));
            set => SetFieldValue("reverbGainHF", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Reverb Gain to high frequencies
        /// </description>
        /// </value>
        public float ReverbGainLF {
            get => GenericMarshal.StringTo<float>(GetFieldValue("reverbGainLF"));
            set => SetFieldValue("reverbGainLF", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Decay time for the reverb.
        /// </description>
        /// </value>
        public float ReverbDecayTime {
            get => GenericMarshal.StringTo<float>(GetFieldValue("reverbDecayTime"));
            set => SetFieldValue("reverbDecayTime", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// High frequency decay time ratio.
        /// </description>
        /// </value>
        public float ReverbDecayHFRatio {
            get => GenericMarshal.StringTo<float>(GetFieldValue("reverbDecayHFRatio"));
            set => SetFieldValue("reverbDecayHFRatio", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// High frequency decay time ratio.
        /// </description>
        /// </value>
        public float ReverbDecayLFRatio {
            get => GenericMarshal.StringTo<float>(GetFieldValue("reverbDecayLFRatio"));
            set => SetFieldValue("reverbDecayLFRatio", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Reflection Gain.
        /// </description>
        /// </value>
        public float ReflectionsGain {
            get => GenericMarshal.StringTo<float>(GetFieldValue("reflectionsGain"));
            set => SetFieldValue("reflectionsGain", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// How long to delay reflections.
        /// </description>
        /// </value>
        public float ReflectionDelay {
            get => GenericMarshal.StringTo<float>(GetFieldValue("reflectionDelay"));
            set => SetFieldValue("reflectionDelay", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Late reverb gain amount.
        /// </description>
        /// </value>
        public float LateReverbGain {
            get => GenericMarshal.StringTo<float>(GetFieldValue("lateReverbGain"));
            set => SetFieldValue("lateReverbGain", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Late reverb delay time.
        /// </description>
        /// </value>
        public float LateReverbDelay {
            get => GenericMarshal.StringTo<float>(GetFieldValue("lateReverbDelay"));
            set => SetFieldValue("lateReverbDelay", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Reverb echo time.
        /// </description>
        /// </value>
        public float ReverbEchoTime {
            get => GenericMarshal.StringTo<float>(GetFieldValue("reverbEchoTime"));
            set => SetFieldValue("reverbEchoTime", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Reverb echo depth.
        /// </description>
        /// </value>
        public float ReverbEchoDepth {
            get => GenericMarshal.StringTo<float>(GetFieldValue("reverbEchoDepth"));
            set => SetFieldValue("reverbEchoDepth", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Reverb Modulation time.
        /// </description>
        /// </value>
        public float ReverbModTime {
            get => GenericMarshal.StringTo<float>(GetFieldValue("reverbModTime"));
            set => SetFieldValue("reverbModTime", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Reverb Modulation Depth.
        /// </description>
        /// </value>
        public float ReverbModDepth {
            get => GenericMarshal.StringTo<float>(GetFieldValue("reverbModDepth"));
            set => SetFieldValue("reverbModDepth", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// High Frequency air absorbtion
        /// </description>
        /// </value>
        public float AirAbsorbtionGainHF {
            get => GenericMarshal.StringTo<float>(GetFieldValue("airAbsorbtionGainHF"));
            set => SetFieldValue("airAbsorbtionGainHF", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Reverb High Frequency Reference.
        /// </description>
        /// </value>
        public float ReverbHFRef {
            get => GenericMarshal.StringTo<float>(GetFieldValue("reverbHFRef"));
            set => SetFieldValue("reverbHFRef", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Reverb Low Frequency Reference.
        /// </description>
        /// </value>
        public float ReverbLFRef {
            get => GenericMarshal.StringTo<float>(GetFieldValue("reverbLFRef"));
            set => SetFieldValue("reverbLFRef", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Rolloff factor for reverb.
        /// </description>
        /// </value>
        public float RoomRolloffFactor {
            get => GenericMarshal.StringTo<float>(GetFieldValue("roomRolloffFactor"));
            set => SetFieldValue("roomRolloffFactor", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// High Frequency decay limit.
        /// </description>
        /// </value>
        public int DecayHFLimit {
            get => GenericMarshal.StringTo<int>(GetFieldValue("decayHFLimit"));
            set => SetFieldValue("decayHFLimit", GenericMarshal.ToString(value));
        }
    }
}