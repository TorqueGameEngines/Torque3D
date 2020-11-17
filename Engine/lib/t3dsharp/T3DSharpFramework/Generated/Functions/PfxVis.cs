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

    public static unsafe class PfxVis {

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct OnWindowClosed__Args
            {
                internal IntPtr ctrl;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnWindowClosed(OnWindowClosed__Args args);
            private static _OnWindowClosed _OnWindowClosedFunc;
            internal static _OnWindowClosed OnWindowClosed() {
                if (_OnWindowClosedFunc == null) {
                    _OnWindowClosedFunc =
                        (_OnWindowClosed)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnPfxVis_onWindowClosed"), typeof(_OnWindowClosed));
                }
                
                return _OnWindowClosedFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Show__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Show(Show__Args args);
            private static _Show _ShowFunc;
            internal static _Show Show() {
                if (_ShowFunc == null) {
                    _ShowFunc =
                        (_Show)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnPfxVis_show"), typeof(_Show));
                }
                
                return _ShowFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Hide__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Hide(Hide__Args args);
            private static _Hide _HideFunc;
            internal static _Hide Hide() {
                if (_HideFunc == null) {
                    _HideFunc =
                        (_Hide)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnPfxVis_hide"), typeof(_Hide));
                }
                
                return _HideFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Open__Args
            {
                internal IntPtr pfx;
                [MarshalAs(UnmanagedType.I1)]
                internal bool clear;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Open(Open__Args args);
            private static _Open _OpenFunc;
            internal static _Open Open() {
                if (_OpenFunc == null) {
                    _OpenFunc =
                        (_Open)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnPfxVis_open"), typeof(_Open));
                }
                
                return _OpenFunc;
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
                                "fnPfxVis_clear"), typeof(_Clear));
                }
                
                return _ClearFunc;
            }
        }
        #endregion

        /// 
        public static void OnWindowClosed(GuiWindowCtrl ctrl) {
             InternalUnsafeMethods.OnWindowClosed__Args _args = new InternalUnsafeMethods.OnWindowClosed__Args() {
                ctrl = ctrl.ObjectPtr,
             };
             InternalUnsafeMethods.OnWindowClosed()(_args);
        }

        /// 
        public static void Show() {
             InternalUnsafeMethods.Show__Args _args = new InternalUnsafeMethods.Show__Args() {
             };
             InternalUnsafeMethods.Show()(_args);
        }

        /// 
        public static void Hide() {
             InternalUnsafeMethods.Hide__Args _args = new InternalUnsafeMethods.Hide__Args() {
             };
             InternalUnsafeMethods.Hide()(_args);
        }

        /// <description>
        /// ( PostEffect, [bool clear = false] )
        /// </description>
        public static void Open(PostEffect pfx, bool clear = false) {
             InternalUnsafeMethods.Open__Args _args = new InternalUnsafeMethods.Open__Args() {
                pfx = pfx.ObjectPtr,
                clear = clear,
             };
             InternalUnsafeMethods.Open()(_args);
        }

        /// 
        public static void Clear() {
             InternalUnsafeMethods.Clear__Args _args = new InternalUnsafeMethods.Clear__Args() {
             };
             InternalUnsafeMethods.Clear()(_args);
        }

    }
}