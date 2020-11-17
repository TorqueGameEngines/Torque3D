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
    /// <summary>Playback controller for a sound source.</summary>
    /// <description>
    /// All sound playback is driven by SFXSources.  Each such source represents an independent playback controller that directly or indirectly affects sound output.
    /// 
    /// While this class itself is instantiable, such an instance will not by itself emit any sound.  This is the responsibility of its subclasses.  Note, however, that none of these subclasses must be instantiated directly but must instead be instantiated indirectly through the SFX interface.
    /// </description>
    /// <see cref="sfxPlayOnce" />
    /// <see cref="sfxDeleteWhenStopped" />
    /// <remarks> Be aware that the property values used to scale child property values are the </remarks>
    /// <see cref="SFXDescription::sourceGroup" />
    /// <see cref="SFXDescription::volume" />
    /// <see cref="SFXDescription::is3d" />
    /// <see cref="SFXDescription::fadeInTime" />
    /// <see cref="SFXDescription::fadeOutTime" />
    /// <see cref="SFXDescription::fadeInEase" />
    /// <see cref="SFXDescription::fadeOutEase" />
    /// <see cref="SFXDescription::fadeLoops" />
    /// <see cref="SFXDescription::coneInsideAngle" />
    /// <see cref="SFXDescription::coneOutsideAngle" />
    /// <see cref="SFXDescription::coneOutsideVolume" />
    /// <see cref="sfxGetDopplerFactor" />
    /// <see cref="sfxSetDopplerFactor" />
    /// <see cref="SFXAmbience::dopplerFactor" />
    public unsafe class SFXSource : SimGroup {
        public SFXSource(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public SFXSource(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public SFXSource(string pName) 
            : this(pName, false) {
        }
        
        public SFXSource(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public SFXSource(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public SFXSource(SimObject pObj) 
            : base(pObj) {
        }
        
        public SFXSource(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct AddMarker__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
                internal float pos;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _AddMarker(IntPtr _this, AddMarker__Args args);
            private static _AddMarker _AddMarkerFunc;
            internal static _AddMarker AddMarker() {
                if (_AddMarkerFunc == null) {
                    _AddMarkerFunc =
                        (_AddMarker)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSFXSource_addMarker"), typeof(_AddMarker));
                }
                
                return _AddMarkerFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetParameter__Args
            {
                internal int index;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate IntPtr _GetParameter(IntPtr _this, GetParameter__Args args);
            private static _GetParameter _GetParameterFunc;
            internal static _GetParameter GetParameter() {
                if (_GetParameterFunc == null) {
                    _GetParameterFunc =
                        (_GetParameter)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSFXSource_getParameter"), typeof(_GetParameter));
                }
                
                return _GetParameterFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct RemoveParameter__Args
            {
                internal IntPtr parameter;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _RemoveParameter(IntPtr _this, RemoveParameter__Args args);
            private static _RemoveParameter _RemoveParameterFunc;
            internal static _RemoveParameter RemoveParameter() {
                if (_RemoveParameterFunc == null) {
                    _RemoveParameterFunc =
                        (_RemoveParameter)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSFXSource_removeParameter"), typeof(_RemoveParameter));
                }
                
                return _RemoveParameterFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct AddParameter__Args
            {
                internal IntPtr parameter;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _AddParameter(IntPtr _this, AddParameter__Args args);
            private static _AddParameter _AddParameterFunc;
            internal static _AddParameter AddParameter() {
                if (_AddParameterFunc == null) {
                    _AddParameterFunc =
                        (_AddParameter)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSFXSource_addParameter"), typeof(_AddParameter));
                }
                
                return _AddParameterFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetParameterCount__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetParameterCount(IntPtr _this, GetParameterCount__Args args);
            private static _GetParameterCount _GetParameterCountFunc;
            internal static _GetParameterCount GetParameterCount() {
                if (_GetParameterCountFunc == null) {
                    _GetParameterCountFunc =
                        (_GetParameterCount)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSFXSource_getParameterCount"), typeof(_GetParameterCount));
                }
                
                return _GetParameterCountFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetCone__Args
            {
                internal float innerAngle;
                internal float outerAngle;
                internal float outsideVolume;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetCone(IntPtr _this, SetCone__Args args);
            private static _SetCone _SetConeFunc;
            internal static _SetCone SetCone() {
                if (_SetConeFunc == null) {
                    _SetConeFunc =
                        (_SetCone)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSFXSource_setCone"), typeof(_SetCone));
                }
                
                return _SetConeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetTransform__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string position;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string direction;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetTransform(IntPtr _this, SetTransform__Args args);
            private static _SetTransform _SetTransformFunc;
            internal static _SetTransform SetTransform() {
                if (_SetTransformFunc == null) {
                    _SetTransformFunc =
                        (_SetTransform)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSFXSource_setTransform"), typeof(_SetTransform));
                }
                
                return _SetTransformFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetPitch__Args
            {
                internal float pitch;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetPitch(IntPtr _this, SetPitch__Args args);
            private static _SetPitch _SetPitchFunc;
            internal static _SetPitch SetPitch() {
                if (_SetPitchFunc == null) {
                    _SetPitchFunc =
                        (_SetPitch)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSFXSource_setPitch"), typeof(_SetPitch));
                }
                
                return _SetPitchFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetPitch__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _GetPitch(IntPtr _this, GetPitch__Args args);
            private static _GetPitch _GetPitchFunc;
            internal static _GetPitch GetPitch() {
                if (_GetPitchFunc == null) {
                    _GetPitchFunc =
                        (_GetPitch)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSFXSource_getPitch"), typeof(_GetPitch));
                }
                
                return _GetPitchFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetFadeTimes__Args
            {
                internal float fadeInTime;
                internal float fadeOutTime;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetFadeTimes(IntPtr _this, SetFadeTimes__Args args);
            private static _SetFadeTimes _SetFadeTimesFunc;
            internal static _SetFadeTimes SetFadeTimes() {
                if (_SetFadeTimesFunc == null) {
                    _SetFadeTimesFunc =
                        (_SetFadeTimes)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSFXSource_setFadeTimes"), typeof(_SetFadeTimes));
                }
                
                return _SetFadeTimesFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetFadeOutTime__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _GetFadeOutTime(IntPtr _this, GetFadeOutTime__Args args);
            private static _GetFadeOutTime _GetFadeOutTimeFunc;
            internal static _GetFadeOutTime GetFadeOutTime() {
                if (_GetFadeOutTimeFunc == null) {
                    _GetFadeOutTimeFunc =
                        (_GetFadeOutTime)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSFXSource_getFadeOutTime"), typeof(_GetFadeOutTime));
                }
                
                return _GetFadeOutTimeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetFadeInTime__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _GetFadeInTime(IntPtr _this, GetFadeInTime__Args args);
            private static _GetFadeInTime _GetFadeInTimeFunc;
            internal static _GetFadeInTime GetFadeInTime() {
                if (_GetFadeInTimeFunc == null) {
                    _GetFadeInTimeFunc =
                        (_GetFadeInTime)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSFXSource_getFadeInTime"), typeof(_GetFadeInTime));
                }
                
                return _GetFadeInTimeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetAttenuatedVolume__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _GetAttenuatedVolume(IntPtr _this, GetAttenuatedVolume__Args args);
            private static _GetAttenuatedVolume _GetAttenuatedVolumeFunc;
            internal static _GetAttenuatedVolume GetAttenuatedVolume() {
                if (_GetAttenuatedVolumeFunc == null) {
                    _GetAttenuatedVolumeFunc =
                        (_GetAttenuatedVolume)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSFXSource_getAttenuatedVolume"), typeof(_GetAttenuatedVolume));
                }
                
                return _GetAttenuatedVolumeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetVolume__Args
            {
                internal float volume;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetVolume(IntPtr _this, SetVolume__Args args);
            private static _SetVolume _SetVolumeFunc;
            internal static _SetVolume SetVolume() {
                if (_SetVolumeFunc == null) {
                    _SetVolumeFunc =
                        (_SetVolume)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSFXSource_setVolume"), typeof(_SetVolume));
                }
                
                return _SetVolumeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetVolume__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _GetVolume(IntPtr _this, GetVolume__Args args);
            private static _GetVolume _GetVolumeFunc;
            internal static _GetVolume GetVolume() {
                if (_GetVolumeFunc == null) {
                    _GetVolumeFunc =
                        (_GetVolume)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSFXSource_getVolume"), typeof(_GetVolume));
                }
                
                return _GetVolumeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetStatus__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetStatus(IntPtr _this, GetStatus__Args args);
            private static _GetStatus _GetStatusFunc;
            internal static _GetStatus GetStatus() {
                if (_GetStatusFunc == null) {
                    _GetStatusFunc =
                        (_GetStatus)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSFXSource_getStatus"), typeof(_GetStatus));
                }
                
                return _GetStatusFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsStopped__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsStopped(IntPtr _this, IsStopped__Args args);
            private static _IsStopped _IsStoppedFunc;
            internal static _IsStopped IsStopped() {
                if (_IsStoppedFunc == null) {
                    _IsStoppedFunc =
                        (_IsStopped)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSFXSource_isStopped"), typeof(_IsStopped));
                }
                
                return _IsStoppedFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsPaused__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsPaused(IntPtr _this, IsPaused__Args args);
            private static _IsPaused _IsPausedFunc;
            internal static _IsPaused IsPaused() {
                if (_IsPausedFunc == null) {
                    _IsPausedFunc =
                        (_IsPaused)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSFXSource_isPaused"), typeof(_IsPaused));
                }
                
                return _IsPausedFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsPlaying__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsPlaying(IntPtr _this, IsPlaying__Args args);
            private static _IsPlaying _IsPlayingFunc;
            internal static _IsPlaying IsPlaying() {
                if (_IsPlayingFunc == null) {
                    _IsPlayingFunc =
                        (_IsPlaying)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSFXSource_isPlaying"), typeof(_IsPlaying));
                }
                
                return _IsPlayingFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Pause__Args
            {
                internal float fadeOutTime;
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
                                "fnSFXSource_pause"), typeof(_Pause));
                }
                
                return _PauseFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Stop__Args
            {
                internal float fadeOutTime;
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
                                "fnSFXSource_stop"), typeof(_Stop));
                }
                
                return _StopFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Play__Args
            {
                internal float fadeInTime;
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
                                "fnSFXSource_play"), typeof(_Play));
                }
                
                return _PlayFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnParameterValueChange__Args
            {
                internal IntPtr parameter;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnParameterValueChange(IntPtr _this, OnParameterValueChange__Args args);
            private static _OnParameterValueChange _OnParameterValueChangeFunc;
            internal static _OnParameterValueChange OnParameterValueChange() {
                if (_OnParameterValueChangeFunc == null) {
                    _OnParameterValueChangeFunc =
                        (_OnParameterValueChange)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbSFXSource_onParameterValueChange"), typeof(_OnParameterValueChange));
                }
                
                return _OnParameterValueChangeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnStatusChange__Args
            {
                internal int newStatus;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnStatusChange(IntPtr _this, OnStatusChange__Args args);
            private static _OnStatusChange _OnStatusChangeFunc;
            internal static _OnStatusChange OnStatusChange() {
                if (_OnStatusChangeFunc == null) {
                    _OnStatusChangeFunc =
                        (_OnStatusChange)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbSFXSource_onStatusChange"), typeof(_OnStatusChange));
                }
                
                return _OnStatusChangeFunc;
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
                                "fnSFXSource_staticGetType"), typeof(_StaticGetType));
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
                                "fnSFXSource_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Add a notification marker called<paramref name="" /> name at 
        /// </description>
        /// <param name="name">Symbolic name for the marker that will be passed to the onMarkerPassed() callback.</param>
        /// <param name="pos">Playback position in seconds when the notification should trigger.  Note that this is a soft limit and there may be a delay between the play cursor actually passing the position and the callback being triggered.</param>
        /// <remarks> For looped sounds, the marker will trigger on each iteration.
        /// 
        /// </remarks>
        /// <code>
        /// // Create a new source.
        /// $source = sfxCreateSource( AudioMusicLoop2D, "art/sound/backgroundMusic" );
        /// 
        /// // Assign a class to the source.
        /// $source.class = "BackgroundMusic";
        /// 
        /// // Add a playback marker at one minute into playback.
        /// $source.addMarker( "first", 60 );
        /// 
        /// // Define the callback function.  This function will be called when the playback position passes the one minute mark.
        /// function BackgroundMusic::onMarkerPassed( %this, %markerName )
        /// {
        ///    if( %markerName $= "first" )
        ///       echo( "Playback has passed the 60 seconds mark." );
        /// }
        /// 
        /// // Play the sound.
        /// $source.play();
        /// </code>
        public void AddMarker(string name, float pos) {
             InternalUnsafeMethods.AddMarker__Args _args = new InternalUnsafeMethods.AddMarker__Args() {
                name = name,
                pos = pos,
             };
             InternalUnsafeMethods.AddMarker()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the parameter at the given index.
        /// </description>
        /// <param name="index">Index of the parameter to fetch.  Must be 0<=index<=getParameterCount().</param>
        /// <returns>The parameter at the given<paramref name="" /> index or null if </returns>
        /// <code>
        /// // Print the name ofo each parameter attached to %source.
        /// %numParams = %source.getParameterCount();
        /// for( %i = 0; %i < %numParams; %i ++ )
        ///    echo( %source.getParameter( %i ).getParameterName() );
        /// </code>
        /// <see cref="getParameterCount" />
        public SFXParameter GetParameter(int index) {
             InternalUnsafeMethods.GetParameter__Args _args = new InternalUnsafeMethods.GetParameter__Args() {
                index = index,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetParameter()(ObjectPtr, _args);
             return new SFXParameter(_engineResult);
        }

        /// <description>
        /// Detach<paramref name="" /> parameter from the source.
        /// 
        /// Once detached, the source will no longer react to value changes of the given 
        /// </description>
        /// <param name="parameter">The parameter to detach from the source.</param>
        public void RemoveParameter(SFXParameter parameter) {
             InternalUnsafeMethods.RemoveParameter__Args _args = new InternalUnsafeMethods.RemoveParameter__Args() {
                parameter = parameter.ObjectPtr,
             };
             InternalUnsafeMethods.RemoveParameter()(ObjectPtr, _args);
        }

        /// <description>
        /// Attach<paramref name="" /> parameter to the source,
        /// 
        /// Once attached, the source will react to value changes of the given 
        /// </description>
        /// <param name="parameter">The parameter to attach to the source.</param>
        public void AddParameter(SFXParameter parameter) {
             InternalUnsafeMethods.AddParameter__Args _args = new InternalUnsafeMethods.AddParameter__Args() {
                parameter = parameter.ObjectPtr,
             };
             InternalUnsafeMethods.AddParameter()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the number of SFXParameters that are attached to the source.
        /// </description>
        /// <returns>The number of parameters attached to the source.</returns>
        /// <code>
        /// // Print the name ofo each parameter attached to %source.
        /// %numParams = %source.getParameterCount();
        /// for( %i = 0; %i < %numParams; %i ++ )
        ///    echo( %source.getParameter( %i ).getParameterName() );
        /// </code>
        /// <see cref="getParameter" />
        /// <see cref="addParameter" />
        public int GetParameterCount() {
             InternalUnsafeMethods.GetParameterCount__Args _args = new InternalUnsafeMethods.GetParameterCount__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetParameterCount()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Set up the 3D volume cone for the source.
        /// </description>
        /// <param name="innerAngle">Angle of the inner sound cone in degrees (</param>
        /// <param name="outerAngle">Angle of the outer sound cone in degrees (</param>
        /// <param name="outsideVolume">Volume scale factor outside of outer cone (</param>
        /// <remarks> This method has no effect on the source if the source is not 3D.
        /// 
        /// </remarks>
        public void SetCone(float innerAngle, float outerAngle, float outsideVolume) {
             InternalUnsafeMethods.SetCone__Args _args = new InternalUnsafeMethods.SetCone__Args() {
                innerAngle = innerAngle,
                outerAngle = outerAngle,
                outsideVolume = outsideVolume,
             };
             InternalUnsafeMethods.SetCone()(ObjectPtr, _args);
        }

        /// <description>
        /// ( vector position [, vector direction ] ) Set the position and orientation of a 3D sound source.
        /// </description>
        public void SetTransform(string position, string direction = "") {
             InternalUnsafeMethods.SetTransform__Args _args = new InternalUnsafeMethods.SetTransform__Args() {
                position = position,
                direction = direction,
             };
             InternalUnsafeMethods.SetTransform()(ObjectPtr, _args);
        }

        /// <description>
        /// Set the pitch scale of the source.
        /// Pitch determines the playback speed of the source (default: 1).
        /// </description>
        /// <param name="pitch">The new pitch scale factor.</param>
        /// <see cref="getPitch" />
        /// <see cref="SFXDescription::pitch" />
        public void SetPitch(float pitch) {
             InternalUnsafeMethods.SetPitch__Args _args = new InternalUnsafeMethods.SetPitch__Args() {
                pitch = pitch,
             };
             InternalUnsafeMethods.SetPitch()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the pitch scale of the source.
        /// Pitch determines the playback speed of the source (default: 1).
        /// </description>
        /// <returns>The current pitch scale factor of the source.</returns>
        /// <see cref="setPitch" />
        /// <see cref="SFXDescription::pitch" />
        public float GetPitch() {
             InternalUnsafeMethods.GetPitch__Args _args = new InternalUnsafeMethods.GetPitch__Args() {
             };
             float _engineResult = InternalUnsafeMethods.GetPitch()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Set the fade time parameters of the source.
        /// </description>
        /// <param name="fadeInTime">The new fade-in time in seconds.</param>
        /// <param name="fadeOutTime">The new fade-out time in seconds.</param>
        /// <see cref="SFXDescription::fadeInTime" />
        /// <see cref="SFXDescription::fadeOutTime" />
        public void SetFadeTimes(float fadeInTime, float fadeOutTime) {
             InternalUnsafeMethods.SetFadeTimes__Args _args = new InternalUnsafeMethods.SetFadeTimes__Args() {
                fadeInTime = fadeInTime,
                fadeOutTime = fadeOutTime,
             };
             InternalUnsafeMethods.SetFadeTimes()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the fade-out time set on the source.
        /// This will initially be SFXDescription::fadeOutTime.
        /// </description>
        /// <returns>The fade-out time set on the source in seconds.</returns>
        /// <see cref="SFXDescription::fadeOutTime" />
        public float GetFadeOutTime() {
             InternalUnsafeMethods.GetFadeOutTime__Args _args = new InternalUnsafeMethods.GetFadeOutTime__Args() {
             };
             float _engineResult = InternalUnsafeMethods.GetFadeOutTime()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Get the fade-in time set on the source.
        /// This will initially be SFXDescription::fadeInTime.
        /// </description>
        /// <returns>The fade-in time set on the source in seconds.</returns>
        /// <see cref="SFXDescription::fadeInTime" />
        public float GetFadeInTime() {
             InternalUnsafeMethods.GetFadeInTime__Args _args = new InternalUnsafeMethods.GetFadeInTime__Args() {
             };
             float _engineResult = InternalUnsafeMethods.GetFadeInTime()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Get the final effective volume level of the source.
        /// 
        /// This method returns the volume level as it is after source group volume modulation, fades, and distance-based volume attenuation have been applied to the base volume level.
        /// </description>
        /// <returns>The effective volume of the source.</returns>
        public float GetAttenuatedVolume() {
             InternalUnsafeMethods.GetAttenuatedVolume__Args _args = new InternalUnsafeMethods.GetAttenuatedVolume__Args() {
             };
             float _engineResult = InternalUnsafeMethods.GetAttenuatedVolume()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Set the base volume level for the source.
        /// This volume will be the starting point for source group volume modulation, fades, and distance-based volume attenuation.
        /// </description>
        /// <param name="volume">The new base volume level for the source.  Must be 0>=volume<=1.</param>
        /// <see cref="getVolume" />
        public void SetVolume(float volume) {
             InternalUnsafeMethods.SetVolume__Args _args = new InternalUnsafeMethods.SetVolume__Args() {
                volume = volume,
             };
             InternalUnsafeMethods.SetVolume()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the current base volume level of the source.
        /// This is not the final effective volume that the source is playing at but rather the starting volume level before source group modulation, fades, or distance-based volume attenuation are applied.
        /// </description>
        /// <returns>The current base volume level.</returns>
        /// <see cref="setVolume" />
        /// <see cref="SFXDescription::volume" />
        public float GetVolume() {
             InternalUnsafeMethods.GetVolume__Args _args = new InternalUnsafeMethods.GetVolume__Args() {
             };
             float _engineResult = InternalUnsafeMethods.GetVolume()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Get the current playback status.
        /// </description>
        /// <returns>Te current playback status</returns>
        public SFXStatus GetStatus() {
             InternalUnsafeMethods.GetStatus__Args _args = new InternalUnsafeMethods.GetStatus__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetStatus()(ObjectPtr, _args);
             return (SFXStatus)_engineResult;
        }

        /// <description>
        /// Test whether the source is currently stopped.
        /// </description>
        /// <returns>True if the source is in stopped state, false otherwise.</returns>
        /// <see cref="stop" />
        /// <see cref="getStatus" />
        /// <see cref="SFXStatus" />
        public bool IsStopped() {
             InternalUnsafeMethods.IsStopped__Args _args = new InternalUnsafeMethods.IsStopped__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.IsStopped()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Test whether the source is currently paused.
        /// </description>
        /// <returns>True if the source is in paused state, false otherwise.</returns>
        /// <see cref="pause" />
        /// <see cref="getStatus" />
        /// <see cref="SFXStatus" />
        public bool IsPaused() {
             InternalUnsafeMethods.IsPaused__Args _args = new InternalUnsafeMethods.IsPaused__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.IsPaused()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Test whether the source is currently playing.
        /// </description>
        /// <returns>True if the source is in playing state, false otherwise.</returns>
        /// <see cref="play" />
        /// <see cref="getStatus" />
        /// <see cref="SFXStatus" />
        public bool IsPlaying() {
             InternalUnsafeMethods.IsPlaying__Args _args = new InternalUnsafeMethods.IsPlaying__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.IsPlaying()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Pause playback of the source.
        /// </description>
        /// <param name="fadeOutTime">Seconds for the sound to fade down to zero volume.  If -1, the SFXDescription::fadeOutTime set in the source's associated description is used.  Pass 0 to disable a fade-out effect that may be configured on the description.
        /// Be aware that if a fade-out effect is used, the source will not immediately to paused state but will rather remain in playing state until the fade-out time has expired..</param>
        public void Pause(float fadeOutTime = -1f) {
             InternalUnsafeMethods.Pause__Args _args = new InternalUnsafeMethods.Pause__Args() {
                fadeOutTime = fadeOutTime,
             };
             InternalUnsafeMethods.Pause()(ObjectPtr, _args);
        }

        /// <description>
        /// Stop playback of the source.
        /// </description>
        /// <param name="fadeOutTime">Seconds for the sound to fade down to zero volume.  If -1, the SFXDescription::fadeOutTime set in the source's associated description is used.  Pass 0 to disable a fade-out effect that may be configured on the description.
        /// Be aware that if a fade-out effect is used, the source will not immediately transtion to stopped state but will rather remain in playing state until the fade-out time has expired.</param>
        public void Stop(float fadeOutTime = -1f) {
             InternalUnsafeMethods.Stop__Args _args = new InternalUnsafeMethods.Stop__Args() {
                fadeOutTime = fadeOutTime,
             };
             InternalUnsafeMethods.Stop()(ObjectPtr, _args);
        }

        /// <description>
        /// Start playback of the source.
        /// If the sound data for the source has not yet been fully loaded, there will be a delay after calling play and playback will start after the data has become available.
        /// </description>
        /// <param name="fadeInTime">Seconds for the sound to reach full volume.  If -1, the SFXDescription::fadeInTime set in the source's associated description is used.  Pass 0 to disable a fade-in effect that may be configured on the description.</param>
        public void Play(float fadeInTime = -1f) {
             InternalUnsafeMethods.Play__Args _args = new InternalUnsafeMethods.Play__Args() {
                fadeInTime = fadeInTime,
             };
             InternalUnsafeMethods.Play()(ObjectPtr, _args);
        }

        /// <description>
        /// Called when a parameter attached to the source changes value.
        /// This callback will be triggered before the value change has actually been applied to the source.
        /// </description>
        /// <param name="parameter">The parameter that has changed value.</param>
        /// <remarks> This is also triggered when the parameter is first attached to the source.</remarks>
        public virtual void OnParameterValueChange(SFXParameter parameter) {
             InternalUnsafeMethods.OnParameterValueChange__Args _args = new InternalUnsafeMethods.OnParameterValueChange__Args() {
                parameter = parameter.ObjectPtr,
             };
             InternalUnsafeMethods.OnParameterValueChange()(ObjectPtr, _args);
        }

        /// <description>
        /// Called when the playback status of the source changes.
        /// </description>
        /// <param name="newStatus">The new playback status.</param>
        public virtual void OnStatusChange(SFXStatus newStatus) {
             InternalUnsafeMethods.OnStatusChange__Args _args = new InternalUnsafeMethods.OnStatusChange__Args() {
                newStatus = (int)newStatus,
             };
             InternalUnsafeMethods.OnStatusChange()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the SFXSource class.
        /// </description>
        /// <returns>The type info object for SFXSource</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// The playback configuration that determines the initial sound properties and setup.
        /// Any SFXSource must have an associated SFXDescription.
        /// </description>
        /// </value>
        public SFXDescription Description {
            get => GenericMarshal.StringTo<SFXDescription>(GetFieldValue("description"));
            set => SetFieldValue("description", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Name of function to call when the status of the source changes.
        /// 
        /// The source that had its status changed is passed as the first argument to the function and the new status of the source is passed as the second argument.
        /// </description>
        /// </value>
        public string StatusCallback {
            get => GenericMarshal.StringTo<string>(GetFieldValue("statusCallback"));
            set => SetFieldValue("statusCallback", GenericMarshal.ToString(value));
        }
    }
}