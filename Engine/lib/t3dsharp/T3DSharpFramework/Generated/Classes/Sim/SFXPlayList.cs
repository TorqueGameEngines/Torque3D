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
    /// <summary>A datablock describing a playback pattern of sounds.</summary>
    /// <description>
    /// Playlists allow to define intricate playback patterns of invidual tracks and thus allow the sound system to be easily used for playing multiple sounds in single operations.
    /// 
    /// As playlists are %SFXTracks, they can thus be used anywhere in the engine where sound data can be assigned.
    /// 
    /// Each playlist can hold a maximum of 16 tracks.  Longer playlists may be constructed by cascading lists, i.e. by creating a playlist that references other playlists.
    /// 
    /// Processing of a single playlist slot progresses in a fixed set of steps that are invariably iterated through for each slot (except the slot is assigned a state and its state is deactivated; in this case, the controller will exit out of the slot directly):
    /// 
    /// <ol>
    /// <li><b>delayIn:</b><p>Waits a set amount of time before processing the slot. This is 0 by default and is determined by the #delayTimeIn (seconds to wait) and #delayTimeInVariance (bounds on randomization) properties.</p></li>
    /// <li><b>#transitionIn:</b><p>Decides what to do
    /// </description>
    /// <remarks> Be aware that time limits set on slot delays are soft limits.  The sound system updates sound sources in discrete (and equally system update frequency dependent) intervals which thus determines the granularity at which time-outs can be handled.
    /// 
    /// </remarks>
    /// <code>
    /// // Create a play list from two SFXProfiles.
    /// %playList = new SFXPlayList()
    /// {
    ///    // Use a looped description so the list playback will loop.
    ///    description = AudioMusicLoop2D;
    /// 
    ///    track[ 0 ] = Profile1;
    ///    track[ 1 ] = Profile2;
    /// };
    /// 
    /// // Play the list.
    /// sfxPlayOnce( %playList );
    /// </code>
    public unsafe class SFXPlayList : SFXTrack {
        public SFXPlayList(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public SFXPlayList(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public SFXPlayList(string pName) 
            : this(pName, false) {
        }
        
        public SFXPlayList(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public SFXPlayList(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public SFXPlayList(SimObject pObj) 
            : base(pObj) {
        }
        
        public SFXPlayList(IntPtr pObj) 
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
                                "fnSFXPlayList_staticGetType"), typeof(_StaticGetType));
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
                                "fnSFXPlayList_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the SFXPlayList class.
        /// </description>
        /// <returns>The type info object for SFXPlayList</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Slot playback order randomization pattern.
        /// By setting this field to something other than "NotRandom" to order in which slots of the playlist are processed can be changed from sequential to a random pattern.  This allows to to create more varied playback patterns.
        /// Defaults to "NotRandom".
        /// </description>
        /// </value>
        public SFXPlayListRandomMode Random {
            get => GenericMarshal.StringTo<SFXPlayListRandomMode>(GetFieldValue("random"));
            set => SetFieldValue("random", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Behavior when description has looping enabled.
        /// The loop mode determines whether the list will loop over a single slot or loop over all the entire list of slots being played.
        /// </description>
        /// <see cref="SFXDescription::isLooping" />
        /// </value>
        public SFXPlayListLoopMode LoopMode {
            get => GenericMarshal.StringTo<SFXPlayListLoopMode>(GetFieldValue("loopMode"));
            set => SetFieldValue("loopMode", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Number of slots to play.
        /// Up to a maximum of 16, this field determines the number of slots that are taken from the list for playback.  Only slots that have a valid #track assigned will be considered for this.
        /// </description>
        /// </value>
        public int NumSlotsToPlay {
            get => GenericMarshal.StringTo<int>(GetFieldValue("numSlotsToPlay"));
            set => SetFieldValue("numSlotsToPlay", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Track to play in this slot.
        /// This must be set for the slot to be considered for playback.  Other settings for a slot will not take effect except this field is set.
        /// </description>
        /// </value>
        public DynamicFieldVector<SFXTrack> Track {
            get => new DynamicFieldVector<SFXTrack>(
                    this, 
                    "track", 
                    12, 
                    val => GenericMarshal.StringTo<SFXTrack>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Behavior when an already playing sound is encountered on this slot from a previous cycle.
        /// Each slot can have an arbitrary number of sounds playing on it from previous cycles.  This field determines how SFXController will handle these sources.
        /// </description>
        /// </value>
        public DynamicFieldVector<SFXPlayListReplayMode> Replay {
            get => new DynamicFieldVector<SFXPlayListReplayMode>(
                    this, 
                    "replay", 
                    12, 
                    val => GenericMarshal.StringTo<SFXPlayListReplayMode>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Behavior when moving into this slot.
        /// After the delayIn time has expired (if any), this slot determines what the controller will do before actually playing the slot.
        /// </description>
        /// </value>
        public DynamicFieldVector<SFXPlayListTransitionMode> TransitionIn {
            get => new DynamicFieldVector<SFXPlayListTransitionMode>(
                    this, 
                    "transitionIn", 
                    12, 
                    val => GenericMarshal.StringTo<SFXPlayListTransitionMode>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Behavior when moving out of this slot.
        /// After the #detailTimeOut has expired (if any), this slot determines what the controller will do before moving on to the next slot.
        /// </description>
        /// </value>
        public DynamicFieldVector<SFXPlayListTransitionMode> TransitionOut {
            get => new DynamicFieldVector<SFXPlayListTransitionMode>(
                    this, 
                    "transitionOut", 
                    12, 
                    val => GenericMarshal.StringTo<SFXPlayListTransitionMode>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Seconds to wait after moving into slot before #transitionIn.
        /// </description>
        /// </value>
        public DynamicFieldVector<float> DelayTimeIn {
            get => new DynamicFieldVector<float>(
                    this, 
                    "delayTimeIn", 
                    12, 
                    val => GenericMarshal.StringTo<float>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Bounds on randomization of #delayTimeIn.
        /// </description>
        /// </value>
        public DynamicFieldVector<Point2F> DelayTimeInVariance {
            get => new DynamicFieldVector<Point2F>(
                    this, 
                    "delayTimeInVariance", 
                    12, 
                    val => GenericMarshal.StringTo<Point2F>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Seconds to wait before moving out of slot after #transitionOut.
        /// </description>
        /// </value>
        public DynamicFieldVector<float> DelayTimeOut {
            get => new DynamicFieldVector<float>(
                    this, 
                    "delayTimeOut", 
                    12, 
                    val => GenericMarshal.StringTo<float>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Bounds on randomization of #delayTimeOut.
        /// </description>
        /// </value>
        public DynamicFieldVector<Point2F> DelayTimeOutVariance {
            get => new DynamicFieldVector<Point2F>(
                    this, 
                    "delayTimeOutVariance", 
                    12, 
                    val => GenericMarshal.StringTo<Point2F>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Seconds to fade sound in (-1 to use the track's own fadeInTime.)
        /// </description>
        /// <see cref="SFXDescription::fadeTimeIn" />
        /// </value>
        public DynamicFieldVector<float> FadeTimeIn {
            get => new DynamicFieldVector<float>(
                    this, 
                    "fadeTimeIn", 
                    12, 
                    val => GenericMarshal.StringTo<float>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Bounds on randomization of #fadeInTime.
        /// </description>
        /// </value>
        public DynamicFieldVector<Point2F> FadeTimeInVariance {
            get => new DynamicFieldVector<Point2F>(
                    this, 
                    "fadeTimeInVariance", 
                    12, 
                    val => GenericMarshal.StringTo<Point2F>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Seconds to fade sound out (-1 to use the track's own fadeOutTime.)
        /// </description>
        /// <see cref="SFXDescription::fadeTimeOut" />
        /// </value>
        public DynamicFieldVector<float> FadeTimeOut {
            get => new DynamicFieldVector<float>(
                    this, 
                    "fadeTimeOut", 
                    12, 
                    val => GenericMarshal.StringTo<float>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Bounds on randomization of #fadeOutTime
        /// </description>
        /// </value>
        public DynamicFieldVector<Point2F> FadeTimeOutVariance {
            get => new DynamicFieldVector<Point2F>(
                    this, 
                    "fadeTimeOutVariance", 
                    12, 
                    val => GenericMarshal.StringTo<Point2F>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <see cref="SFXDescription::referenceDistance" />
        /// </value>
        public DynamicFieldVector<float> ReferenceDistance {
            get => new DynamicFieldVector<float>(
                    this, 
                    "referenceDistance", 
                    12, 
                    val => GenericMarshal.StringTo<float>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Bounds on randomization of #referenceDistance.
        /// </description>
        /// </value>
        public DynamicFieldVector<Point2F> ReferenceDistanceVariance {
            get => new DynamicFieldVector<Point2F>(
                    this, 
                    "referenceDistanceVariance", 
                    12, 
                    val => GenericMarshal.StringTo<Point2F>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <see cref="SFXDescription::maxDistance" />
        /// </value>
        public DynamicFieldVector<float> MaxDistance {
            get => new DynamicFieldVector<float>(
                    this, 
                    "maxDistance", 
                    12, 
                    val => GenericMarshal.StringTo<float>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Bounds on randomization of #maxDistance.
        /// </description>
        /// </value>
        public DynamicFieldVector<Point2F> MaxDistanceVariance {
            get => new DynamicFieldVector<Point2F>(
                    this, 
                    "maxDistanceVariance", 
                    12, 
                    val => GenericMarshal.StringTo<Point2F>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Scale factor to apply to volume of sounds played on this list slot.
        /// This value will scale the actual volume level set on the track assigned to the slot, i.e. a value of 0.5 will cause the track to play at half-volume.
        /// </description>
        /// </value>
        public DynamicFieldVector<float> VolumeScale {
            get => new DynamicFieldVector<float>(
                    this, 
                    "volumeScale", 
                    12, 
                    val => GenericMarshal.StringTo<float>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Bounds on randomization of #volumeScale.
        /// </description>
        /// </value>
        public DynamicFieldVector<Point2F> VolumeScaleVariance {
            get => new DynamicFieldVector<Point2F>(
                    this, 
                    "volumeScaleVariance", 
                    12, 
                    val => GenericMarshal.StringTo<Point2F>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Scale factor to apply to pitch of sounds played on this list slot.
        /// This value will scale the actual pitch set on the track assigned to the slot, i.e. a value of 0.5 will cause the track to play at half its assigned speed.
        /// </description>
        /// </value>
        public DynamicFieldVector<float> PitchScale {
            get => new DynamicFieldVector<float>(
                    this, 
                    "pitchScale", 
                    12, 
                    val => GenericMarshal.StringTo<float>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Bounds on randomization of #pitchScale.
        /// </description>
        /// </value>
        public DynamicFieldVector<Point2F> PitchScaleVariance {
            get => new DynamicFieldVector<Point2F>(
                    this, 
                    "pitchScaleVariance", 
                    12, 
                    val => GenericMarshal.StringTo<Point2F>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Number of times to loop this slot.
        /// </description>
        /// </value>
        public DynamicFieldVector<int> RepeatCount {
            get => new DynamicFieldVector<int>(
                    this, 
                    "repeatCount", 
                    12, 
                    val => GenericMarshal.StringTo<int>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// State that must be active for this slot to play.
        /// </description>
        /// </value>
        public DynamicFieldVector<SFXState> State {
            get => new DynamicFieldVector<SFXState>(
                    this, 
                    "state", 
                    12, 
                    val => GenericMarshal.StringTo<SFXState>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Behavior when assigned state is deactivated while slot is playing.
        /// </description>
        /// </value>
        public DynamicFieldVector<SFXPlayListStateMode> StateMode {
            get => new DynamicFieldVector<SFXPlayListStateMode>(
                    this, 
                    "stateMode", 
                    12, 
                    val => GenericMarshal.StringTo<SFXPlayListStateMode>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Enable/disable execution tracing for this playlist (local only).
        /// If this is true, SFXControllers attached to the list will automatically run in trace mode.
        /// </description>
        /// </value>
        public bool Trace {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("trace"));
            set => SetFieldValue("trace", GenericMarshal.ToString(value));
        }
    }
}