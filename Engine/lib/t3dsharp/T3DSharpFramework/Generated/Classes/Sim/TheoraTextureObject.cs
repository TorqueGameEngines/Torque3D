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
    /// <summary>Definition of a named texture target playing a Theora video.</summary>
    /// <description>
    /// TheoraTextureObject defines a named texture target that may play back a Theora video.  This texture target can, for example, be used by materials to texture objects with videos.
    /// </description>
    /// <code>
    /// // The object that provides the video texture and controls its playback.
    /// singleton TheoraTextureObject( TheVideo )
    /// {
    ///    // Unique name for the texture target for referencing in materials.
    ///    texTargetName = "video";
    /// 
    ///    // Path to the video file.
    ///    theoraFile = "./MyVideo.ogv";
    /// };
    /// 
    /// // Material that uses the video texture.
    /// singleton Material( TheVideoMaterial )
    /// {
    ///    // This has to reference the named texture target defined by the
    ///    // TheoraTextureObject's 'texTargetName' property.  Prefix with '#' to
    ///    // identify as texture target reference.
    ///    diffuseMap[ 0 ] = "#video";
    /// };
    /// </code>
    public unsafe class TheoraTextureObject : SimObject {
        public TheoraTextureObject(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public TheoraTextureObject(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public TheoraTextureObject(string pName) 
            : this(pName, false) {
        }
        
        public TheoraTextureObject(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public TheoraTextureObject(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public TheoraTextureObject(SimObject pObj) 
            : base(pObj) {
        }
        
        public TheoraTextureObject(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
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
                                "fnTheoraTextureObject_pause"), typeof(_Pause));
                }
                
                return _PauseFunc;
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
                                "fnTheoraTextureObject_stop"), typeof(_Stop));
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
                                "fnTheoraTextureObject_play"), typeof(_Play));
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
                                "fnTheoraTextureObject_staticGetType"), typeof(_StaticGetType));
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
                                "fnTheoraTextureObject_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Pause playback of the video.
        /// </description>
        public void Pause() {
             InternalUnsafeMethods.Pause__Args _args = new InternalUnsafeMethods.Pause__Args() {
             };
             InternalUnsafeMethods.Pause()(ObjectPtr, _args);
        }

        /// <description>
        /// Stop playback of the video.
        /// </description>
        public void Stop() {
             InternalUnsafeMethods.Stop__Args _args = new InternalUnsafeMethods.Stop__Args() {
             };
             InternalUnsafeMethods.Stop()(ObjectPtr, _args);
        }

        /// <description>
        /// Start playback of the video.
        /// </description>
        public void Play() {
             InternalUnsafeMethods.Play__Args _args = new InternalUnsafeMethods.Play__Args() {
             };
             InternalUnsafeMethods.Play()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the TheoraTextureObject class.
        /// </description>
        /// <returns>The type info object for TheoraTextureObject</returns>
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
        /// Name of the texture target by which the texture can be referenced in materials.
        /// </description>
        /// </value>
        public string TexTargetName {
            get => GenericMarshal.StringTo<string>(GetFieldValue("texTargetName"));
            set => SetFieldValue("texTargetName", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Sound description to use for the video's audio channel.
        /// 
        /// If not set, will use a default one.
        /// </description>
        /// </value>
        public SFXDescription SFXDescription {
            get => GenericMarshal.StringTo<SFXDescription>(GetFieldValue("SFXDescription"));
            set => SetFieldValue("SFXDescription", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Should the video loop.
        /// </description>
        /// </value>
        public bool Loop {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("Loop"));
            set => SetFieldValue("Loop", GenericMarshal.ToString(value));
        }
    }
}