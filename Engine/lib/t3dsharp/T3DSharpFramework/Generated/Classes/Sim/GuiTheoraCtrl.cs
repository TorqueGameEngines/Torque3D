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
    /// <summary>A control to playing Theora videos.</summary>
    /// <description>
    /// This control can be used to play videos in the Theora video format.  The videos may include audio in Vorbis format.  The codecs for both formats are integrated with the engine and no codecs must be present on the user's machine.
    /// </description>
    /// <code>
    /// %video = new GuiTheoraCtrl()
    /// {
    ///    theoraFile = "videos/intro.ogv";
    ///    playOnWake = false;
    ///    stopOnSleep = true;
    /// }
    /// 
    /// Canvas.setContent( %video );
    /// %video.play();
    /// </code>
    /// <see href="http://www.theora.org" />
    public unsafe class GuiTheoraCtrl : GuiControl {
        public GuiTheoraCtrl(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public GuiTheoraCtrl(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public GuiTheoraCtrl(string pName) 
            : this(pName, false) {
        }
        
        public GuiTheoraCtrl(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public GuiTheoraCtrl(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public GuiTheoraCtrl(SimObject pObj) 
            : base(pObj) {
        }
        
        public GuiTheoraCtrl(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct IsPlaybackDone__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsPlaybackDone(IntPtr _this, IsPlaybackDone__Args args);
            private static _IsPlaybackDone _IsPlaybackDoneFunc;
            internal static _IsPlaybackDone IsPlaybackDone() {
                if (_IsPlaybackDoneFunc == null) {
                    _IsPlaybackDoneFunc =
                        (_IsPlaybackDone)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiTheoraCtrl_isPlaybackDone"), typeof(_IsPlaybackDone));
                }
                
                return _IsPlaybackDoneFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetCurrentTime__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _GetCurrentTime(IntPtr _this, GetCurrentTime__Args args);
            private static _GetCurrentTime _GetCurrentTimeFunc;
            internal static _GetCurrentTime GetCurrentTime() {
                if (_GetCurrentTimeFunc == null) {
                    _GetCurrentTimeFunc =
                        (_GetCurrentTime)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiTheoraCtrl_getCurrentTime"), typeof(_GetCurrentTime));
                }
                
                return _GetCurrentTimeFunc;
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
                                "fnGuiTheoraCtrl_stop"), typeof(_Stop));
                }
                
                return _StopFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Pause__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Pause(IntPtr _this, Pause__Args args);
            private static _Pause _PauseFunc;
            internal static _Pause Pause() {
                if (_PauseFunc == null) {
                    _PauseFunc =
                        (_Pause)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiTheoraCtrl_pause"), typeof(_Pause));
                }
                
                return _PauseFunc;
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
                                "fnGuiTheoraCtrl_play"), typeof(_Play));
                }
                
                return _PlayFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetFile__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string filename;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetFile(IntPtr _this, SetFile__Args args);
            private static _SetFile _SetFileFunc;
            internal static _SetFile SetFile() {
                if (_SetFileFunc == null) {
                    _SetFileFunc =
                        (_SetFile)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiTheoraCtrl_setFile"), typeof(_SetFile));
                }
                
                return _SetFileFunc;
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
                                "fnGuiTheoraCtrl_staticGetType"), typeof(_StaticGetType));
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
                                "fnGuiTheoraCtrl_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Test whether the video has finished playing.
        /// </description>
        /// <returns>True if the video has finished playing, false otherwise.</returns>
        public bool IsPlaybackDone() {
             InternalUnsafeMethods.IsPlaybackDone__Args _args = new InternalUnsafeMethods.IsPlaybackDone__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.IsPlaybackDone()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Get the current playback time.
        /// </description>
        /// <returns>The elapsed playback time in seconds.</returns>
        public float GetCurrentTime() {
             InternalUnsafeMethods.GetCurrentTime__Args _args = new InternalUnsafeMethods.GetCurrentTime__Args() {
             };
             float _engineResult = InternalUnsafeMethods.GetCurrentTime()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Stop playback of the video.  The next call to play() will then start playback from the beginning of the video.
        /// 
        /// While stopped, the control renders empty with just the background color.
        /// </description>
        public void Stop() {
             InternalUnsafeMethods.Stop__Args _args = new InternalUnsafeMethods.Stop__Args() {
             };
             InternalUnsafeMethods.Stop()(ObjectPtr, _args);
        }

        /// <description>
        /// Pause playback of the video.  If the video is not currently playing, the call is ignored.
        /// 
        /// While stopped, the control displays the last frame.
        /// </description>
        public void Pause() {
             InternalUnsafeMethods.Pause__Args _args = new InternalUnsafeMethods.Pause__Args() {
             };
             InternalUnsafeMethods.Pause()(ObjectPtr, _args);
        }

        /// <description>
        /// Start playing the video.  If the video is already playing, the call is ignored.
        /// </description>
        public void Play() {
             InternalUnsafeMethods.Play__Args _args = new InternalUnsafeMethods.Play__Args() {
             };
             InternalUnsafeMethods.Play()(ObjectPtr, _args);
        }

        /// <description>
        /// Set the video file to play.  If a video is already playing, playback is stopped and the new video file is loaded.
        /// </description>
        /// <param name="filename">The video file to load.</param>
        public void SetFile(string filename) {
             InternalUnsafeMethods.SetFile__Args _args = new InternalUnsafeMethods.SetFile__Args() {
                filename = filename,
             };
             InternalUnsafeMethods.SetFile()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the GuiTheoraCtrl class.
        /// </description>
        /// <returns>The type info object for GuiTheoraCtrl</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Theora video file to play.
        /// </description>
        /// </value>
        public string TheoraFile {
            get => GenericMarshal.StringTo<string>(GetFieldValue("theoraFile"));
            set => SetFieldValue("theoraFile", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Fill color when video is not playing.
        /// </description>
        /// </value>
        public ColorI BackgroundColor {
            get => GenericMarshal.StringTo<ColorI>(GetFieldValue("backgroundColor"));
            set => SetFieldValue("backgroundColor", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Whether to start playing video when control is woken up.
        /// </description>
        /// </value>
        public bool PlayOnWake {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("playOnWake"));
            set => SetFieldValue("playOnWake", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Loop playback.
        /// </description>
        /// </value>
        public bool Loop {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("Loop"));
            set => SetFieldValue("Loop", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Whether to stop video when control is set to sleep.
        /// 
        /// If this is not set to true, the video will be paused when the control is put to sleep.  This is because there is no support for seeking in the video stream in the player backend and letting the time source used to synchronize video (either audio or a raw timer) get far ahead of frame decoding will cause possibly very long delays when the control is woken up again.
        /// </description>
        /// </value>
        public bool StopOnSleep {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("stopOnSleep"));
            set => SetFieldValue("stopOnSleep", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Whether to automatically match control extents to the video size.
        /// </description>
        /// </value>
        public bool MatchVideoSize {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("matchVideoSize"));
            set => SetFieldValue("matchVideoSize", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// If true, displays an overlay on top of the video with useful debugging information.
        /// </description>
        /// </value>
        public bool RenderDebugInfo {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("renderDebugInfo"));
            set => SetFieldValue("renderDebugInfo", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The routine to use for Y'CbCr to RGB conversion.
        /// </description>
        /// </value>
        public GuiTheoraTranscoder Transcoder {
            get => GenericMarshal.StringTo<GuiTheoraTranscoder>(GetFieldValue("transcoder"));
            set => SetFieldValue("transcoder", GenericMarshal.ToString(value));
        }
    }
}