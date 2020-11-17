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
    /// <summary>Encapsulates a single sound file for playback by the sound system.</summary>
    /// <description>
    /// SFXProfile combines a sound description (SFXDescription) with a sound file such that it can be played by the sound system.  To be able to play a sound file, the sound system will always require a profile for it to be created.  However, several of the SFX functions (sfxPlayOnce(), sfxCreateSource()) perform this creation internally for convenience using temporary profile objects.
    /// 
    /// Sound files can be in either OGG or WAV format.  However, extended format support is available when using FMOD. See
    /// </description>
    /// <remarks> Sounds using streamed playback (SFXDescription::isStreaming) cannot be preloaded and will thus ignore the #preload flag.
    /// 
    /// </remarks>
    /// <code>
    /// datablock SFXProfile( Shore01Snd )
    /// {
    ///    fileName     = "art/sound/Lakeshore_mono_01";
    ///    description  = Shore01Looping3d;
    ///    preload      = true;
    /// };
    /// </code>
    public unsafe class SFXProfile : SFXTrack {
        public SFXProfile(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public SFXProfile(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public SFXProfile(string pName) 
            : this(pName, false) {
        }
        
        public SFXProfile(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public SFXProfile(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public SFXProfile(SimObject pObj) 
            : base(pObj) {
        }
        
        public SFXProfile(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct GetSoundDuration__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _GetSoundDuration(IntPtr _this, GetSoundDuration__Args args);
            private static _GetSoundDuration _GetSoundDurationFunc;
            internal static _GetSoundDuration GetSoundDuration() {
                if (_GetSoundDurationFunc == null) {
                    _GetSoundDurationFunc =
                        (_GetSoundDuration)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSFXProfile_getSoundDuration"), typeof(_GetSoundDuration));
                }
                
                return _GetSoundDurationFunc;
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
                                "fnSFXProfile_staticGetType"), typeof(_StaticGetType));
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
                                "fnSFXProfile_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Return the length of the sound data in seconds.
        /// </description>
        /// <returns>The length of the sound data in seconds or 0 if the sound referenced by the profile could not be found.</returns>
        public float GetSoundDuration() {
             InternalUnsafeMethods.GetSoundDuration__Args _args = new InternalUnsafeMethods.GetSoundDuration__Args() {
             };
             float _engineResult = InternalUnsafeMethods.GetSoundDuration()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Get the type info object for the SFXProfile class.
        /// </description>
        /// <returns>The type info object for SFXProfile</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// %Path to the sound file.
        /// If the extension is left out, it will be inferred by the sound system.  This allows to easily switch the sound format without having to go through the profiles and change the filenames there, too.
        /// </description>
        /// </value>
        public string FileName {
            get => GenericMarshal.StringTo<string>(GetFieldValue("fileName"));
            set => SetFieldValue("fileName", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Whether to preload sound data when the profile is added to system.
        /// </description>
        /// <remarks> This flag is ignored by streamed sounds.
        /// 
        /// </remarks>
        /// </value>
        public bool Preload {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("preload"));
            set => SetFieldValue("preload", GenericMarshal.ToString(value));
        }
    }
}