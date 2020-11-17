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

    public static unsafe class GFXCardProfiler {

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct GetBestDepthFormat__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetBestDepthFormat(GetBestDepthFormat__Args args);
            private static _GetBestDepthFormat _GetBestDepthFormatFunc;
            internal static _GetBestDepthFormat GetBestDepthFormat() {
                if (_GetBestDepthFormatFunc == null) {
                    _GetBestDepthFormatFunc =
                        (_GetBestDepthFormat)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGFXCardProfilerAPI_getBestDepthFormat"), typeof(_GetBestDepthFormat));
                }
                
                return _GetBestDepthFormatFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct QueryProfile__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
                internal int defaultValue;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _QueryProfile(QueryProfile__Args args);
            private static _QueryProfile _QueryProfileFunc;
            internal static _QueryProfile QueryProfile() {
                if (_QueryProfileFunc == null) {
                    _QueryProfileFunc =
                        (_QueryProfile)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGFXCardProfilerAPI_queryProfile"), typeof(_QueryProfile));
                }
                
                return _QueryProfileFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetCapability__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
                internal int value;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetCapability(SetCapability__Args args);
            private static _SetCapability _SetCapabilityFunc;
            internal static _SetCapability SetCapability() {
                if (_SetCapabilityFunc == null) {
                    _SetCapabilityFunc =
                        (_SetCapability)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGFXCardProfilerAPI_setCapability"), typeof(_SetCapability));
                }
                
                return _SetCapabilityFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetVideoMemoryMB__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetVideoMemoryMB(GetVideoMemoryMB__Args args);
            private static _GetVideoMemoryMB _GetVideoMemoryMBFunc;
            internal static _GetVideoMemoryMB GetVideoMemoryMB() {
                if (_GetVideoMemoryMBFunc == null) {
                    _GetVideoMemoryMBFunc =
                        (_GetVideoMemoryMB)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGFXCardProfilerAPI_getVideoMemoryMB"), typeof(_GetVideoMemoryMB));
                }
                
                return _GetVideoMemoryMBFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetRenderer__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetRenderer(GetRenderer__Args args);
            private static _GetRenderer _GetRendererFunc;
            internal static _GetRenderer GetRenderer() {
                if (_GetRendererFunc == null) {
                    _GetRendererFunc =
                        (_GetRenderer)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGFXCardProfilerAPI_getRenderer"), typeof(_GetRenderer));
                }
                
                return _GetRendererFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetVendor__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetVendor(GetVendor__Args args);
            private static _GetVendor _GetVendorFunc;
            internal static _GetVendor GetVendor() {
                if (_GetVendorFunc == null) {
                    _GetVendorFunc =
                        (_GetVendor)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGFXCardProfilerAPI_getVendor"), typeof(_GetVendor));
                }
                
                return _GetVendorFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetCard__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetCard(GetCard__Args args);
            private static _GetCard _GetCardFunc;
            internal static _GetCard GetCard() {
                if (_GetCardFunc == null) {
                    _GetCardFunc =
                        (_GetCard)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGFXCardProfilerAPI_getCard"), typeof(_GetCard));
                }
                
                return _GetCardFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetVersion__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetVersion(GetVersion__Args args);
            private static _GetVersion _GetVersionFunc;
            internal static _GetVersion GetVersion() {
                if (_GetVersionFunc == null) {
                    _GetVersionFunc =
                        (_GetVersion)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGFXCardProfilerAPI_getVersion"), typeof(_GetVersion));
                }
                
                return _GetVersionFunc;
            }
        }
        #endregion

        /// <description>
        /// Returns the card name.
        /// </description>
        public static string GetBestDepthFormat() {
             InternalUnsafeMethods.GetBestDepthFormat__Args _args = new InternalUnsafeMethods.GetBestDepthFormat__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetBestDepthFormat()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Used to query the value of a specific card capability.
        /// </description>
        /// <param name="name">The name of the capability being queried.</param>
        /// <param name="defaultValue">The value to return if the capability is not defined.</param>
        public static int QueryProfile(string name, int defaultValue) {
             InternalUnsafeMethods.QueryProfile__Args _args = new InternalUnsafeMethods.QueryProfile__Args() {
                name = name,
                defaultValue = defaultValue,
             };
             int _engineResult = InternalUnsafeMethods.QueryProfile()(_args);
             return _engineResult;
        }

        /// <description>
        /// Used to set the value for a specific card capability.
        /// </description>
        /// <param name="name">The name of the capability being set.</param>
        /// <param name="value">The value to set for that capability.</param>
        public static void SetCapability(string name, int value) {
             InternalUnsafeMethods.SetCapability__Args _args = new InternalUnsafeMethods.SetCapability__Args() {
                name = name,
                value = value,
             };
             InternalUnsafeMethods.SetCapability()(_args);
        }

        /// <description>
        /// Returns the amount of video memory in megabytes.
        /// </description>
        public static int GetVideoMemoryMB() {
             InternalUnsafeMethods.GetVideoMemoryMB__Args _args = new InternalUnsafeMethods.GetVideoMemoryMB__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetVideoMemoryMB()(_args);
             return _engineResult;
        }

        /// <description>
        /// Returns the renderer name.  For example D3D11 or OpenGL.
        /// </description>
        public static string GetRenderer() {
             InternalUnsafeMethods.GetRenderer__Args _args = new InternalUnsafeMethods.GetRenderer__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetRenderer()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Returns the card vendor name.
        /// </description>
        public static string GetVendor() {
             InternalUnsafeMethods.GetVendor__Args _args = new InternalUnsafeMethods.GetVendor__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetVendor()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Returns the card name.
        /// </description>
        public static string GetCard() {
             InternalUnsafeMethods.GetCard__Args _args = new InternalUnsafeMethods.GetCard__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetCard()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Returns the driver version string.
        /// </description>
        public static string GetVersion() {
             InternalUnsafeMethods.GetVersion__Args _args = new InternalUnsafeMethods.GetVersion__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetVersion()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

    }
}