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
    /// <summary>The on-screen, in-game console. Calls getLog() to get the on-screen console entries, then renders them as needed.</summary>
    /// <description>
    /// 
    /// </description>
    /// <code>
    /// new GuiConsole()
    /// 		{
    /// 			//Properties not specific to this control have been omitted from this example.
    /// 		};
    /// </code>
    /// <see cref="GuiControl" />
    public unsafe class GuiConsole : GuiArrayCtrl {
        public GuiConsole(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public GuiConsole(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public GuiConsole(string pName) 
            : this(pName, false) {
        }
        
        public GuiConsole(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public GuiConsole(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public GuiConsole(SimObject pObj) 
            : base(pObj) {
        }
        
        public GuiConsole(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct Refresh__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Refresh(IntPtr _this, Refresh__Args args);
            private static _Refresh _RefreshFunc;
            internal static _Refresh Refresh() {
                if (_RefreshFunc == null) {
                    _RefreshFunc =
                        (_Refresh)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiConsole_refresh"), typeof(_Refresh));
                }
                
                return _RefreshFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ToggleNormalFilter__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ToggleNormalFilter(IntPtr _this, ToggleNormalFilter__Args args);
            private static _ToggleNormalFilter _ToggleNormalFilterFunc;
            internal static _ToggleNormalFilter ToggleNormalFilter() {
                if (_ToggleNormalFilterFunc == null) {
                    _ToggleNormalFilterFunc =
                        (_ToggleNormalFilter)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiConsole_toggleNormalFilter"), typeof(_ToggleNormalFilter));
                }
                
                return _ToggleNormalFilterFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ToggleWarnFilter__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ToggleWarnFilter(IntPtr _this, ToggleWarnFilter__Args args);
            private static _ToggleWarnFilter _ToggleWarnFilterFunc;
            internal static _ToggleWarnFilter ToggleWarnFilter() {
                if (_ToggleWarnFilterFunc == null) {
                    _ToggleWarnFilterFunc =
                        (_ToggleWarnFilter)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiConsole_toggleWarnFilter"), typeof(_ToggleWarnFilter));
                }
                
                return _ToggleWarnFilterFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ToggleErrorFilter__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ToggleErrorFilter(IntPtr _this, ToggleErrorFilter__Args args);
            private static _ToggleErrorFilter _ToggleErrorFilterFunc;
            internal static _ToggleErrorFilter ToggleErrorFilter() {
                if (_ToggleErrorFilterFunc == null) {
                    _ToggleErrorFilterFunc =
                        (_ToggleErrorFilter)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiConsole_toggleErrorFilter"), typeof(_ToggleErrorFilter));
                }
                
                return _ToggleErrorFilterFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetNormalFilter__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _GetNormalFilter(IntPtr _this, GetNormalFilter__Args args);
            private static _GetNormalFilter _GetNormalFilterFunc;
            internal static _GetNormalFilter GetNormalFilter() {
                if (_GetNormalFilterFunc == null) {
                    _GetNormalFilterFunc =
                        (_GetNormalFilter)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiConsole_getNormalFilter"), typeof(_GetNormalFilter));
                }
                
                return _GetNormalFilterFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetWarnFilter__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _GetWarnFilter(IntPtr _this, GetWarnFilter__Args args);
            private static _GetWarnFilter _GetWarnFilterFunc;
            internal static _GetWarnFilter GetWarnFilter() {
                if (_GetWarnFilterFunc == null) {
                    _GetWarnFilterFunc =
                        (_GetWarnFilter)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiConsole_getWarnFilter"), typeof(_GetWarnFilter));
                }
                
                return _GetWarnFilterFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetErrorFilter__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _GetErrorFilter(IntPtr _this, GetErrorFilter__Args args);
            private static _GetErrorFilter _GetErrorFilterFunc;
            internal static _GetErrorFilter GetErrorFilter() {
                if (_GetErrorFilterFunc == null) {
                    _GetErrorFilterFunc =
                        (_GetErrorFilter)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiConsole_getErrorFilter"), typeof(_GetErrorFilter));
                }
                
                return _GetErrorFilterFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetDisplayFilters__Args
            {
                [MarshalAs(UnmanagedType.I1)]
                internal bool errors;
                [MarshalAs(UnmanagedType.I1)]
                internal bool warns;
                [MarshalAs(UnmanagedType.I1)]
                internal bool normal;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetDisplayFilters(IntPtr _this, SetDisplayFilters__Args args);
            private static _SetDisplayFilters _SetDisplayFiltersFunc;
            internal static _SetDisplayFilters SetDisplayFilters() {
                if (_SetDisplayFiltersFunc == null) {
                    _SetDisplayFiltersFunc =
                        (_SetDisplayFilters)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiConsole_setDisplayFilters"), typeof(_SetDisplayFilters));
                }
                
                return _SetDisplayFiltersFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnNewMessage__Args
            {
                internal uint errorCount;
                internal uint warnCount;
                internal uint normalCount;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnNewMessage(IntPtr _this, OnNewMessage__Args args);
            private static _OnNewMessage _OnNewMessageFunc;
            internal static _OnNewMessage OnNewMessage() {
                if (_OnNewMessageFunc == null) {
                    _OnNewMessageFunc =
                        (_OnNewMessage)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbGuiConsole_onNewMessage"), typeof(_OnNewMessage));
                }
                
                return _OnNewMessageFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnMessageSelected__Args
            {
                internal int level;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string message;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnMessageSelected(IntPtr _this, OnMessageSelected__Args args);
            private static _OnMessageSelected _OnMessageSelectedFunc;
            internal static _OnMessageSelected OnMessageSelected() {
                if (_OnMessageSelectedFunc == null) {
                    _OnMessageSelectedFunc =
                        (_OnMessageSelected)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbGuiConsole_onMessageSelected"), typeof(_OnMessageSelected));
                }
                
                return _OnMessageSelectedFunc;
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
                                "fnGuiConsole_staticGetType"), typeof(_StaticGetType));
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
                                "fnGuiConsole_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Refreshes the displayed messages.
        /// </description>
        public void Refresh() {
             InternalUnsafeMethods.Refresh__Args _args = new InternalUnsafeMethods.Refresh__Args() {
             };
             InternalUnsafeMethods.Refresh()(ObjectPtr, _args);
        }

        /// <description>
        /// Toggles the normal messages filter.
        /// </description>
        public void ToggleNormalFilter() {
             InternalUnsafeMethods.ToggleNormalFilter__Args _args = new InternalUnsafeMethods.ToggleNormalFilter__Args() {
             };
             InternalUnsafeMethods.ToggleNormalFilter()(ObjectPtr, _args);
        }

        /// <description>
        /// Toggles the warning filter.
        /// </description>
        public void ToggleWarnFilter() {
             InternalUnsafeMethods.ToggleWarnFilter__Args _args = new InternalUnsafeMethods.ToggleWarnFilter__Args() {
             };
             InternalUnsafeMethods.ToggleWarnFilter()(ObjectPtr, _args);
        }

        /// <description>
        /// Toggles the error filter.
        /// </description>
        public void ToggleErrorFilter() {
             InternalUnsafeMethods.ToggleErrorFilter__Args _args = new InternalUnsafeMethods.ToggleErrorFilter__Args() {
             };
             InternalUnsafeMethods.ToggleErrorFilter()(ObjectPtr, _args);
        }

        /// <description>
        /// Returns if the normal message filter is on or not.
        /// </description>
        public bool GetNormalFilter() {
             InternalUnsafeMethods.GetNormalFilter__Args _args = new InternalUnsafeMethods.GetNormalFilter__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.GetNormalFilter()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Returns if the warning filter is on or not.
        /// </description>
        public bool GetWarnFilter() {
             InternalUnsafeMethods.GetWarnFilter__Args _args = new InternalUnsafeMethods.GetWarnFilter__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.GetWarnFilter()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Returns if the error filter is on or not.
        /// </description>
        public bool GetErrorFilter() {
             InternalUnsafeMethods.GetErrorFilter__Args _args = new InternalUnsafeMethods.GetErrorFilter__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.GetErrorFilter()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Sets the current display filters for the console gui. Allows you to indicate if it should display errors, warns and/or normal messages.
        /// </description>
        /// <param name="errors">If true, the console gui will display any error messages that were emitted.</param>
        /// <param name="warns">If true, the console gui will display any warning messages that were emitted.</param>
        /// <param name="normal">If true, the console gui will display any regular messages that were emitted.</param>
        public void SetDisplayFilters(bool errors = true, bool warns = true, bool normal = true) {
             InternalUnsafeMethods.SetDisplayFilters__Args _args = new InternalUnsafeMethods.SetDisplayFilters__Args() {
                errors = errors,
                warns = warns,
                normal = normal,
             };
             InternalUnsafeMethods.SetDisplayFilters()(ObjectPtr, _args);
        }

        /// <description>
        /// Called when a new message is logged.
        /// </description>
        /// <param name="errorCount">The number of error messages logged.</param>
        /// <param name="warnCount">The number of warning messages logged.</param>
        /// <param name="normalCount">The number of normal messages logged.</param>
        public virtual void OnNewMessage(uint errorCount, uint warnCount, uint normalCount) {
             InternalUnsafeMethods.OnNewMessage__Args _args = new InternalUnsafeMethods.OnNewMessage__Args() {
                errorCount = errorCount,
                warnCount = warnCount,
                normalCount = normalCount,
             };
             InternalUnsafeMethods.OnNewMessage()(ObjectPtr, _args);
        }

        /// <description>
        /// Called when a message in the log is clicked.
        /// </description>
        /// <param name="level">Diagnostic level of the message.</param>
        /// <param name="message">Message text.</param>
        public virtual void OnMessageSelected(LogLevel level, string message) {
             InternalUnsafeMethods.OnMessageSelected__Args _args = new InternalUnsafeMethods.OnMessageSelected__Args() {
                level = (int)level,
                message = message,
             };
             InternalUnsafeMethods.OnMessageSelected()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the GuiConsole class.
        /// </description>
        /// <returns>The type info object for GuiConsole</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }
    }
}