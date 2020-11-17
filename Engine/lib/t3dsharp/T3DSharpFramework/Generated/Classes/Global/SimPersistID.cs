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

namespace T3DSharpFramework.Generated.Classes.Global {
    /// 
    public unsafe class SimPersistID : EngineObject, ISimPersistID {
        public SimPersistID(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public SimPersistID(ConsoleObjectBase pObj) 
            : base(pObj) {
        }
        
        public SimPersistID(IntPtr pObj) 
            : base(pObj) {
        }
		public string MarshalToString() {
			return GenericMarshal.ToString(GetUUID());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct GetObject__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate IntPtr _GetObject(IntPtr _this, GetObject__Args args);
            private static _GetObject _GetObjectFunc;
            internal static _GetObject GetObject() {
                if (_GetObjectFunc == null) {
                    _GetObjectFunc =
                        (_GetObject)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSimPersistID_getObject"), typeof(_GetObject));
                }
                
                return _GetObjectFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetUUID__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate UUID.InternalStruct _GetUUID(IntPtr _this, GetUUID__Args args);
            private static _GetUUID _GetUUIDFunc;
            internal static _GetUUID GetUUID() {
                if (_GetUUIDFunc == null) {
                    _GetUUIDFunc =
                        (_GetUUID)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSimPersistID_getUUID"), typeof(_GetUUID));
                }
                
                return _GetUUIDFunc;
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
                                "fnSimPersistID_staticGetType"), typeof(_StaticGetType));
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
                                "fnSimPersistID_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// 
        public SimObject GetObject() {
             InternalUnsafeMethods.GetObject__Args _args = new InternalUnsafeMethods.GetObject__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetObject()(ObjectPtr, _args);
             return new SimObject(_engineResult);
        }

        /// 
        public UUID GetUUID() {
             InternalUnsafeMethods.GetUUID__Args _args = new InternalUnsafeMethods.GetUUID__Args() {
             };
             UUID.InternalStruct _engineResult = InternalUnsafeMethods.GetUUID()(ObjectPtr, _args);
             return new UUID(_engineResult);
        }

        /// <description>
        /// Get the type info object for the SimPersistID class.
        /// </description>
        /// <returns>The type info object for SimPersistID</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }
    }
}