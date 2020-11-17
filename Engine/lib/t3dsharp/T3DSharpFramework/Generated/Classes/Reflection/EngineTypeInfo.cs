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

namespace T3DSharpFramework.Generated.Classes.Reflection {
    /// <description>
    /// Information about an engine type.
    /// </description>
    public unsafe class EngineTypeInfo : EngineExportScope {
        public EngineTypeInfo(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public EngineTypeInfo(ConsoleObjectBase pObj) 
            : base(pObj) {
        }
        
        public EngineTypeInfo(IntPtr pObj) 
            : base(pObj) {
        }

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct GetSuperType__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate IntPtr _GetSuperType(IntPtr _this, GetSuperType__Args args);
            private static _GetSuperType _GetSuperTypeFunc;
            internal static _GetSuperType GetSuperType() {
                if (_GetSuperTypeFunc == null) {
                    _GetSuperTypeFunc =
                        (_GetSuperType)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnEngineTypeInfo_getSuperType"), typeof(_GetSuperType));
                }
                
                return _GetSuperTypeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetTypeKind__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetTypeKind(IntPtr _this, GetTypeKind__Args args);
            private static _GetTypeKind _GetTypeKindFunc;
            internal static _GetTypeKind GetTypeKind() {
                if (_GetTypeKindFunc == null) {
                    _GetTypeKindFunc =
                        (_GetTypeKind)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnEngineTypeInfo_getTypeKind"), typeof(_GetTypeKind));
                }
                
                return _GetTypeKindFunc;
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
                                "fnEngineTypeInfo_staticGetType"), typeof(_StaticGetType));
                }
                
                return _StaticGetTypeFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type that this type subtypes from.
        /// </description>
        /// <returns>The supertype info instance or NULL.</returns>
        public EngineTypeInfo GetSuperType() {
             InternalUnsafeMethods.GetSuperType__Args _args = new InternalUnsafeMethods.GetSuperType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetSuperType()(ObjectPtr, _args);
             return new EngineTypeInfo(_engineResult);
        }

        /// <description>
        /// Get the kind of the type.
        /// </description>
        /// <returns>The type kind.</returns>
        public EngineTypeKind GetTypeKind() {
             InternalUnsafeMethods.GetTypeKind__Args _args = new InternalUnsafeMethods.GetTypeKind__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetTypeKind()(ObjectPtr, _args);
             return (EngineTypeKind)_engineResult;
        }

        /// <description>
        /// Get the type info object for the EngineTypeInfo class.
        /// </description>
        /// <returns>The type info object for EngineTypeInfo</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Kind of type.
        /// </description>
        /// </value>
        public EngineTypeKind TypeKind => GetTypeKind();


        /// <value>
        /// <description>
        /// Type that this type subtypes from.
        /// </description>
        /// </value>
        public EngineTypeInfo SuperType => GetSuperType();
    }
}