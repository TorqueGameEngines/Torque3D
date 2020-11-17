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
    /// <summary>A flying vehicle.</summary>
    /// <description>
    /// 
    /// </description>
    public unsafe class FlyingVehicle : Vehicle {
        public FlyingVehicle(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public FlyingVehicle(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public FlyingVehicle(string pName) 
            : this(pName, false) {
        }
        
        public FlyingVehicle(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public FlyingVehicle(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public FlyingVehicle(SimObject pObj) 
            : base(pObj) {
        }
        
        public FlyingVehicle(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct UseCreateHeight__Args
            {
                [MarshalAs(UnmanagedType.I1)]
                internal bool enabled;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _UseCreateHeight(IntPtr _this, UseCreateHeight__Args args);
            private static _UseCreateHeight _UseCreateHeightFunc;
            internal static _UseCreateHeight UseCreateHeight() {
                if (_UseCreateHeightFunc == null) {
                    _UseCreateHeightFunc =
                        (_UseCreateHeight)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnFlyingVehicle_useCreateHeight"), typeof(_UseCreateHeight));
                }
                
                return _UseCreateHeightFunc;
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
                                "fnFlyingVehicle_staticGetType"), typeof(_StaticGetType));
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
                                "fnFlyingVehicle_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <summary>Set whether the vehicle should temporarily use the createHoverHeight specified in the datablock.</summary>
        /// <description>
        /// This can help avoid problems with spawning.
        /// </description>
        /// <param name="enabled">true to use the datablock createHoverHeight, false otherwise</param>
        public void UseCreateHeight(bool enabled) {
             InternalUnsafeMethods.UseCreateHeight__Args _args = new InternalUnsafeMethods.UseCreateHeight__Args() {
                enabled = enabled,
             };
             InternalUnsafeMethods.UseCreateHeight()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the FlyingVehicle class.
        /// </description>
        /// <returns>The type info object for FlyingVehicle</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }
    }
}