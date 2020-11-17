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
    /// 
    public unsafe class SoundAsset : AssetBase {
        public SoundAsset(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public SoundAsset(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public SoundAsset(string pName) 
            : this(pName, false) {
        }
        
        public SoundAsset(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public SoundAsset(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public SoundAsset(SimObject pObj) 
            : base(pObj) {
        }
        
        public SoundAsset(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct GetSoundPath__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetSoundPath(IntPtr _this, GetSoundPath__Args args);
            private static _GetSoundPath _GetSoundPathFunc;
            internal static _GetSoundPath GetSoundPath() {
                if (_GetSoundPathFunc == null) {
                    _GetSoundPathFunc =
                        (_GetSoundPath)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSoundAsset_getSoundPath"), typeof(_GetSoundPath));
                }
                
                return _GetSoundPathFunc;
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
                                "fnSoundAsset_staticGetType"), typeof(_StaticGetType));
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
                                "fnSoundAsset_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// 
        public string GetSoundPath() {
             InternalUnsafeMethods.GetSoundPath__Args _args = new InternalUnsafeMethods.GetSoundPath__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetSoundPath()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Get the type info object for the SoundAsset class.
        /// </description>
        /// <returns>The type info object for SoundAsset</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Path to the sound file.
        /// </description>
        /// </value>
        public string SoundFile {
            get => GenericMarshal.StringTo<string>(GetFieldValue("soundFile"));
            set => SetFieldValue("soundFile", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Adjustment of the pitch value
        /// </description>
        /// </value>
        public float PitchAdjust {
            get => GenericMarshal.StringTo<float>(GetFieldValue("PitchAdjust"));
            set => SetFieldValue("PitchAdjust", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Adjustment to the volume.
        /// </description>
        /// </value>
        public float VolumeAdjust {
            get => GenericMarshal.StringTo<float>(GetFieldValue("VolumeAdjust"));
            set => SetFieldValue("VolumeAdjust", GenericMarshal.ToString(value));
        }
    }
}