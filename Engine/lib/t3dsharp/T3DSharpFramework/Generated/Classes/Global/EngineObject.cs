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
    /// <description>
    /// Abstract base class for all objects exposed through the engine API.
    /// </description>
    public unsafe class EngineObject : ConsoleObjectBase {
        public EngineObject(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public EngineObject(ConsoleObjectBase pObj) 
            : base(pObj) {
        }
        
        public EngineObject(IntPtr pObj) 
            : base(pObj) {
        }

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct SetUserData__Args
            {
                internal IntPtr ptr;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetUserData(IntPtr _this, SetUserData__Args args);
            private static _SetUserData _SetUserDataFunc;
            internal static _SetUserData SetUserData() {
                if (_SetUserDataFunc == null) {
                    _SetUserDataFunc =
                        (_SetUserData)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnEngineObject_setUserData"), typeof(_SetUserData));
                }
                
                return _SetUserDataFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetUserData__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate IntPtr _GetUserData(IntPtr _this, GetUserData__Args args);
            private static _GetUserData _GetUserDataFunc;
            internal static _GetUserData GetUserData() {
                if (_GetUserDataFunc == null) {
                    _GetUserDataFunc =
                        (_GetUserData)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnEngineObject_getUserData"), typeof(_GetUserData));
                }
                
                return _GetUserDataFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Release__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Release(IntPtr _this, Release__Args args);
            private static _Release _ReleaseFunc;
            internal static _Release Release() {
                if (_ReleaseFunc == null) {
                    _ReleaseFunc =
                        (_Release)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnEngineObject_release"), typeof(_Release));
                }
                
                return _ReleaseFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct AddRef__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _AddRef(IntPtr _this, AddRef__Args args);
            private static _AddRef _AddRefFunc;
            internal static _AddRef AddRef() {
                if (_AddRefFunc == null) {
                    _AddRefFunc =
                        (_AddRef)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnEngineObject_addRef"), typeof(_AddRef));
                }
                
                return _AddRefFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetType__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate IntPtr _GetType(IntPtr _this, GetType__Args args);
            private static _GetType _GetTypeFunc;
            internal static _GetType GetType() {
                if (_GetTypeFunc == null) {
                    _GetTypeFunc =
                        (_GetType)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnEngineObject_getType"), typeof(_GetType));
                }
                
                return _GetTypeFunc;
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
                                "fnEngineObject_staticGetType"), typeof(_StaticGetType));
                }
                
                return _StaticGetTypeFunc;
            }
        }
        #endregion

        /// <description>
        /// Install an opaque pointer on the object that the control layer can use to associate data with the object.
        /// </description>
        /// <param name="ptr">A pointer.</param>
        public void SetUserData(IntPtr ptr) {
             InternalUnsafeMethods.SetUserData__Args _args = new InternalUnsafeMethods.SetUserData__Args() {
                ptr = ptr,
             };
             InternalUnsafeMethods.SetUserData()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the opaque user data pointer installed on the object.
        /// </description>
        /// <returns>The user data pointer previously installed on the object; NULL by default.</returns>
        public IntPtr GetUserData() {
             InternalUnsafeMethods.GetUserData__Args _args = new InternalUnsafeMethods.GetUserData__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetUserData()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Decrease the reference count of the given object.  If the count drops to zero, the object will be deleted.
        /// </description>
        /// <param name="object">An object.</param>
        public void Release() {
             InternalUnsafeMethods.Release__Args _args = new InternalUnsafeMethods.Release__Args() {
             };
             InternalUnsafeMethods.Release()(ObjectPtr, _args);
        }

        /// <description>
        /// Increase the reference count of the given object.
        /// </description>
        /// <param name="object">An object.</param>
        public void AddRef() {
             InternalUnsafeMethods.AddRef__Args _args = new InternalUnsafeMethods.AddRef__Args() {
             };
             InternalUnsafeMethods.AddRef()(ObjectPtr, _args);
        }

        /// <description>
        /// Return the type descriptor for the type the object is an instance of.
        /// </description>
        /// <returns>The type descriptor for the object's dynamic type.</returns>
        public EngineTypeInfo GetType() {
             InternalUnsafeMethods.GetType__Args _args = new InternalUnsafeMethods.GetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetType()(ObjectPtr, _args);
             return new EngineTypeInfo(_engineResult);
        }

        /// <description>
        /// Get the type info object for the EngineObject class.
        /// </description>
        /// <returns>The type info object for EngineObject</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }
    }
}