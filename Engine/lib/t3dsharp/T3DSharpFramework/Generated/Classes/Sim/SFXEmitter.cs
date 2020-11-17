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
    /// <summary>An invisible 3D object that emits sound.</summary>
    /// <description>
    /// Sound emitters are used to place sounds in the level.  They are full 3D objects with their own position and orientation and when assigned 3D sounds, the transform and velocity of the sound emitter object will be applied to the 3D sound.
    /// 
    /// Sound emitters can be set up of in either of two ways:
    /// <ul>
    /// <li><p>By assigning an existing SFXTrack to the emitter's #track property.</p>
    /// <p>In this case the general sound setup (3D, streaming, looping, etc.) will be taken from #track.  However, the emitter's own properties will still override their corresponding properties in the #track's SFXDescription.</p></li>
    /// <li><p>By directly assigning a sound file to the emitter's #fileName property.</p>
    /// <p>In this case, the sound file will be set up for playback according to the properties defined on the emitter.</p>
    /// </ul>
    /// 
    /// Using #playOnAdd emitters can be configured to start playing immediately when they are added to the system (e.g. when the level objects are loaded from the mission file).
    /// </description>
    /// <remarks> A sound emitter need not necessarily emit a 3D sound.  Instead, sound emitters may also be used to play non-positional sounds.  For placing background audio to a level, however, it is usually easier to use LevelInfo::soundAmbience.
    /// 
    /// </remarks>
    public unsafe class SFXEmitter : SceneObject {
        public SFXEmitter(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public SFXEmitter(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public SFXEmitter(string pName) 
            : this(pName, false) {
        }
        
        public SFXEmitter(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public SFXEmitter(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public SFXEmitter(SimObject pObj) 
            : base(pObj) {
        }
        
        public SFXEmitter(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct GetSource__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate IntPtr _GetSource(IntPtr _this, GetSource__Args args);
            private static _GetSource _GetSourceFunc;
            internal static _GetSource GetSource() {
                if (_GetSourceFunc == null) {
                    _GetSourceFunc =
                        (_GetSource)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSFXEmitter_getSource"), typeof(_GetSource));
                }
                
                return _GetSourceFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Stop__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Stop(IntPtr _this, Stop__Args args);
            private static _Stop _StopFunc;
            internal static _Stop Stop() {
                if (_StopFunc == null) {
                    _StopFunc =
                        (_Stop)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSFXEmitter_stop"), typeof(_Stop));
                }
                
                return _StopFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Play__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Play(IntPtr _this, Play__Args args);
            private static _Play _PlayFunc;
            internal static _Play Play() {
                if (_PlayFunc == null) {
                    _PlayFunc =
                        (_Play)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSFXEmitter_play"), typeof(_Play));
                }
                
                return _PlayFunc;
            }

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
                                "fnSFXEmitter_staticGetType"), typeof(_StaticGetType));
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
                                "fnSFXEmitter_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the sound source object from the emitter.
        /// </description>
        /// <returns>The sound source used by the emitter or null.</returns>
        /// <remarks> This method will return null when called on the server-side SFXEmitter object.  Only client-side ghosts actually hold on to %SFXSources.
        /// 
        /// </remarks>
        public SFXSource GetSource() {
             InternalUnsafeMethods.GetSource__Args _args = new InternalUnsafeMethods.GetSource__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetSource()(ObjectPtr, _args);
             return new SFXSource(_engineResult);
        }

        /// <description>
        /// Manually stop playback of the emitter's sound.
        /// If this is called on the server-side object, the stop command will be related to all client-side ghosts.
        /// </description>
        public void Stop() {
             InternalUnsafeMethods.Stop__Args _args = new InternalUnsafeMethods.Stop__Args() {
             };
             InternalUnsafeMethods.Stop()(ObjectPtr, _args);
        }

        /// <description>
        /// Manually start playback of the emitter's sound.
        /// If this is called on the server-side object, the play command will be related to all client-side ghosts.
        /// </description>
        public void Play() {
             InternalUnsafeMethods.Play__Args _args = new InternalUnsafeMethods.Play__Args() {
             };
             InternalUnsafeMethods.Play()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the SFXEmitter class.
        /// </description>
        /// <returns>The type info object for SFXEmitter</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// The track which the emitter should play.
        /// </description>
        /// <remarks> If assigned, this field will take precedence over a #fileName that may also be assigned to the emitter.</remarks>
        /// </value>
        public SFXTrack Track {
            get => GenericMarshal.StringTo<SFXTrack>(GetFieldValue("track"));
            set => SetFieldValue("track", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The sound file to play.
        /// Use
        /// </description>
        /// </value>
        public string FileName {
            get => GenericMarshal.StringTo<string>(GetFieldValue("fileName"));
            set => SetFieldValue("fileName", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Whether playback of the emitter's sound should start as soon as the emitter object is added to the level.
        /// If this is true, the emitter will immediately start to play when the level is loaded.
        /// </description>
        /// </value>
        public bool PlayOnAdd {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("playOnAdd"));
            set => SetFieldValue("playOnAdd", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// If this is true, all fields except for #playOnAdd and #track are ignored on the emitter object.
        /// This is useful to prevent fields in the #track's description from being overridden by emitter fields.
        /// </description>
        /// </value>
        public bool UseTrackDescriptionOnly {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("useTrackDescriptionOnly"));
            set => SetFieldValue("useTrackDescriptionOnly", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Whether to play #fileName in an infinite loop.
        /// If a #track is assigned, the value of this field is ignored.
        /// </description>
        /// <see cref="SFXDescription::isLooping" />
        /// </value>
        public bool IsLooping {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("isLooping"));
            set => SetFieldValue("isLooping", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Whether to use streamed playback for #fileName.
        /// If a #track is assigned, the value of this field is ignored.
        /// </description>
        /// <see cref="SFXDescription::isStreaming" />
        /// </value>
        public bool IsStreaming {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("isStreaming"));
            set => SetFieldValue("isStreaming", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The SFXSource to which to assign the sound of this emitter as a child.
        /// </description>
        /// <remarks> This field is ignored if #useTrackDescriptionOnly is true.
        /// 
        /// </remarks>
        /// <see cref="SFXDescription::sourceGroup" />
        /// </value>
        public SFXSource SourceGroup {
            get => GenericMarshal.StringTo<SFXSource>(GetFieldValue("sourceGroup"));
            set => SetFieldValue("sourceGroup", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Volume level to apply to the sound.
        /// </description>
        /// <remarks> This field is ignored if #useTrackDescriptionOnly is true.
        /// 
        /// </remarks>
        /// <see cref="SFXDescription::volume" />
        /// </value>
        public float Volume {
            get => GenericMarshal.StringTo<float>(GetFieldValue("volume"));
            set => SetFieldValue("volume", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Pitch shift to apply to the sound.  Default is 1 = play at normal speed.
        /// </description>
        /// <remarks> This field is ignored if #useTrackDescriptionOnly is true.
        /// 
        /// </remarks>
        /// <see cref="SFXDescription::pitch" />
        /// </value>
        public float Pitch {
            get => GenericMarshal.StringTo<float>(GetFieldValue("pitch"));
            set => SetFieldValue("pitch", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Number of seconds to gradually fade in volume from zero when playback starts.
        /// </description>
        /// <remarks> This field is ignored if #useTrackDescriptionOnly is true.
        /// 
        /// </remarks>
        /// <see cref="SFXDescription::fadeInTime" />
        /// </value>
        public float FadeInTime {
            get => GenericMarshal.StringTo<float>(GetFieldValue("fadeInTime"));
            set => SetFieldValue("fadeInTime", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Number of seconds to gradually fade out volume down to zero when playback is stopped or paused.
        /// </description>
        /// <remarks> This field is ignored if #useTrackDescriptionOnly is true.
        /// 
        /// </remarks>
        /// <see cref="SFXDescription::fadeOutTime" />
        /// </value>
        public float FadeOutTime {
            get => GenericMarshal.StringTo<float>(GetFieldValue("fadeOutTime"));
            set => SetFieldValue("fadeOutTime", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Whether to play #fileName as a positional (3D) sound or not.
        /// If a #track is assigned, the value of this field is ignored.
        /// </description>
        /// <see cref="SFXDescription::is3D" />
        /// </value>
        public bool Is3D {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("is3D"));
            set => SetFieldValue("is3D", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Distance at which to start volume attenuation of the 3D sound.
        /// </description>
        /// <remarks> This field is ignored if #useTrackDescriptionOnly is true.
        /// 
        /// </remarks>
        /// <see cref="SFXDescription::referenceDistance" />
        /// </value>
        public float ReferenceDistance {
            get => GenericMarshal.StringTo<float>(GetFieldValue("referenceDistance"));
            set => SetFieldValue("referenceDistance", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Distance at which to stop volume attenuation of the 3D sound.
        /// </description>
        /// <remarks> This field is ignored if #useTrackDescriptionOnly is true.
        /// 
        /// </remarks>
        /// <see cref="SFXDescription::maxDistance" />
        /// </value>
        public float MaxDistance {
            get => GenericMarshal.StringTo<float>(GetFieldValue("maxDistance"));
            set => SetFieldValue("maxDistance", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Bounds on random offset to apply to initial 3D sound position.
        /// </description>
        /// <remarks> This field is ignored if #useTrackDescriptionOnly is true.
        /// 
        /// </remarks>
        /// <see cref="SFXDescription::scatterDistance" />
        /// </value>
        public Point3F ScatterDistance {
            get => GenericMarshal.StringTo<Point3F>(GetFieldValue("scatterDistance"));
            set => SetFieldValue("scatterDistance", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Angle of inner volume cone of 3D sound in degrees.
        /// </description>
        /// <remarks> This field is ignored if #useTrackDescriptionOnly is true.
        /// 
        /// </remarks>
        /// <see cref="SFXDescription::coneInsideAngle" />
        /// </value>
        public int ConeInsideAngle {
            get => GenericMarshal.StringTo<int>(GetFieldValue("coneInsideAngle"));
            set => SetFieldValue("coneInsideAngle", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Angle of outer volume cone of 3D sound in degrees
        /// </description>
        /// <remarks> This field is ignored if #useTrackDescriptionOnly is true.
        /// 
        /// </remarks>
        /// <see cref="SFXDescription::coneOutsideAngle" />
        /// </value>
        public int ConeOutsideAngle {
            get => GenericMarshal.StringTo<int>(GetFieldValue("coneOutsideAngle"));
            set => SetFieldValue("coneOutsideAngle", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Volume scale factor of outside of outer volume 3D sound cone.
        /// </description>
        /// <remarks> This field is ignored if #useTrackDescriptionOnly is true.
        /// 
        /// </remarks>
        /// <see cref="SFXDescription::coneOutsideVolume" />
        /// </value>
        public float ConeOutsideVolume {
            get => GenericMarshal.StringTo<float>(GetFieldValue("coneOutsideVolume"));
            set => SetFieldValue("coneOutsideVolume", GenericMarshal.ToString(value));
        }
    }
}