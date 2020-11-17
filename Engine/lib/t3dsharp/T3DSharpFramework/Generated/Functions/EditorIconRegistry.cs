using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using T3DSharpFramework.Generated.Classes.Global;
using T3DSharpFramework.Generated.Classes.Net;
using T3DSharpFramework.Generated.Classes.Sim;
using T3DSharpFramework.Generated.Classes.Sim.Net;
using T3DSharpFramework.Generated.Enums.Global;
using T3DSharpFramework.Generated.Structs.Global;
using T3DSharpFramework.Generated.Structs.Gui;
using T3DSharpFramework.Generated.Structs.Math;
using T3DSharpFramework.Interop;

namespace T3DSharpFramework.Generated.Functions {

    public static unsafe class EditorIconRegistry {

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct FindIconBySimObject__Args
            {
                internal IntPtr obj;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _FindIconBySimObject(FindIconBySimObject__Args args);
            private static _FindIconBySimObject _FindIconBySimObjectFunc;
            internal static _FindIconBySimObject FindIconBySimObject() {
                if (_FindIconBySimObjectFunc == null) {
                    _FindIconBySimObjectFunc =
                        (_FindIconBySimObject)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnEditorIconRegistry_findIconBySimObject"), typeof(_FindIconBySimObject));
                }
                
                return _FindIconBySimObjectFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct FindIconByClassName__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string className;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _FindIconByClassName(FindIconByClassName__Args args);
            private static _FindIconByClassName _FindIconByClassNameFunc;
            internal static _FindIconByClassName FindIconByClassName() {
                if (_FindIconByClassNameFunc == null) {
                    _FindIconByClassNameFunc =
                        (_FindIconByClassName)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnEditorIconRegistry_findIconByClassName"), typeof(_FindIconByClassName));
                }
                
                return _FindIconByClassNameFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Clear__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Clear(Clear__Args args);
            private static _Clear _ClearFunc;
            internal static _Clear Clear() {
                if (_ClearFunc == null) {
                    _ClearFunc =
                        (_Clear)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnEditorIconRegistry_clear"), typeof(_Clear));
                }
                
                return _ClearFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct LoadFromPath__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string imagePath;
                [MarshalAs(UnmanagedType.I1)]
                internal bool overwrite;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _LoadFromPath(LoadFromPath__Args args);
            private static _LoadFromPath _LoadFromPathFunc;
            internal static _LoadFromPath LoadFromPath() {
                if (_LoadFromPathFunc == null) {
                    _LoadFromPathFunc =
                        (_LoadFromPath)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnEditorIconRegistry_loadFromPath"), typeof(_LoadFromPath));
                }
                
                return _LoadFromPathFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Add__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string className;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string imageFile;
                [MarshalAs(UnmanagedType.I1)]
                internal bool overwrite;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Add(Add__Args args);
            private static _Add _AddFunc;
            internal static _Add Add() {
                if (_AddFunc == null) {
                    _AddFunc =
                        (_Add)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnEditorIconRegistry_add"), typeof(_Add));
                }
                
                return _AddFunc;
            }
        }
        #endregion

        /// <description>
        /// Returns the file path to the icon file if found.
        /// </description>
        public static string FindIconBySimObject(SimObject obj) {
             InternalUnsafeMethods.FindIconBySimObject__Args _args = new InternalUnsafeMethods.FindIconBySimObject__Args() {
                obj = obj.ObjectPtr,
             };
             IntPtr _engineResult = InternalUnsafeMethods.FindIconBySimObject()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <summary>Returns the file path to the icon file if found.</summary>
        public static string FindIconByClassName(string className) {
             InternalUnsafeMethods.FindIconByClassName__Args _args = new InternalUnsafeMethods.FindIconByClassName__Args() {
                className = className,
             };
             IntPtr _engineResult = InternalUnsafeMethods.FindIconByClassName()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// 
        public static void Clear() {
             InternalUnsafeMethods.Clear__Args _args = new InternalUnsafeMethods.Clear__Args() {
             };
             InternalUnsafeMethods.Clear()(_args);
        }

        /// 
        public static void LoadFromPath(string imagePath, bool overwrite = true) {
             InternalUnsafeMethods.LoadFromPath__Args _args = new InternalUnsafeMethods.LoadFromPath__Args() {
                imagePath = imagePath,
                overwrite = overwrite,
             };
             InternalUnsafeMethods.LoadFromPath()(_args);
        }

        /// 
        public static void Add(string className, string imageFile, bool overwrite = true) {
             InternalUnsafeMethods.Add__Args _args = new InternalUnsafeMethods.Add__Args() {
                className = className,
                imageFile = imageFile,
                overwrite = overwrite,
             };
             InternalUnsafeMethods.Add()(_args);
        }

    }
}