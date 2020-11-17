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
    /// <summary>A datablock that specifies an Audio Bank effect.</summary>
    /// <description>
    /// afxAudioBank is very similar to the stock Torque SFXProfile datablock but it allows specification of up to 32 different sound files. The sound that actually plays is determined by the playIndex field.
    /// 
    /// afxAudioBank is most useful when used in combination with field substitutions, whereby a substitution statement assigned to playIndex selects a different sound (perhaps randomly) each time the effect is used.
    /// </description>
    public unsafe class afxAudioBank : SimDataBlock {
        public afxAudioBank(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public afxAudioBank(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public afxAudioBank(string pName) 
            : this(pName, false) {
        }
        
        public afxAudioBank(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public afxAudioBank(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public afxAudioBank(SimObject pObj) 
            : base(pObj) {
        }
        
        public afxAudioBank(IntPtr pObj) 
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
                                "fnafxAudioBank_staticGetType"), typeof(_StaticGetType));
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
                                "fnafxAudioBank_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the afxAudioBank class.
        /// </description>
        /// <returns>The type info object for afxAudioBank</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// A filesystem path to the folder containing the sound files specified by the filenames[] field. All sound files used in a single AudioBank must be located in the same folder.
        /// </description>
        /// </value>
        public string Path {
            get => GenericMarshal.StringTo<string>(GetFieldValue("Path"));
            set => SetFieldValue("Path", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Up to 32 names of sound files found in the path folder. The sound that is actually played by an Audio Bank effect is determined by the playIndex field.
        /// </description>
        /// </value>
        public DynamicFieldVector<string> Filenames {
            get => new DynamicFieldVector<string>(
                    this, 
                    "filenames", 
                    32, 
                    val => GenericMarshal.StringTo<string>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// SFXDescription datablock to use with this set of sounds.
        /// </description>
        /// </value>
        public SFXDescription Description {
            get => GenericMarshal.StringTo<SFXDescription>(GetFieldValue("description"));
            set => SetFieldValue("description", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// If set to true, file is pre-loaded, otherwise it is loaded on-demand.
        /// </description>
        /// </value>
        public bool Preload {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("preload"));
            set => SetFieldValue("preload", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// An array index that selects a sound to play from the filenames[] field. Values outside of the range of assigned filename[] entries will not play any sound.
        /// </description>
        /// </value>
        public int PlayIndex {
            get => GenericMarshal.StringTo<int>(GetFieldValue("playIndex"));
            set => SetFieldValue("playIndex", GenericMarshal.ToString(value));
        }
    }
}