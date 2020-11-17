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
    /// <summary>A canvas on which rendering occurs.</summary>
    /// <description>
    /// 
    /// </description>
    /// <see cref="GuiControlProfile" />
    /// <see cref="GuiControl" />
    public unsafe class GuiCanvas : GuiControl {
        public GuiCanvas(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public GuiCanvas(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public GuiCanvas(string pName) 
            : this(pName, false) {
        }
        
        public GuiCanvas(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public GuiCanvas(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public GuiCanvas(SimObject pObj) 
            : base(pObj) {
        }
        
        public GuiCanvas(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct ResetVideoMode__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ResetVideoMode(IntPtr _this, ResetVideoMode__Args args);
            private static _ResetVideoMode _ResetVideoModeFunc;
            internal static _ResetVideoMode ResetVideoMode() {
                if (_ResetVideoModeFunc == null) {
                    _ResetVideoModeFunc =
                        (_ResetVideoMode)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiCanvas_resetVideoMode"), typeof(_ResetVideoMode));
                }
                
                return _ResetVideoModeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct CursorNudge__Args
            {
                internal float x;
                internal float y;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _CursorNudge(IntPtr _this, CursorNudge__Args args);
            private static _CursorNudge _CursorNudgeFunc;
            internal static _CursorNudge CursorNudge() {
                if (_CursorNudgeFunc == null) {
                    _CursorNudgeFunc =
                        (_CursorNudge)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiCanvas_cursorNudge"), typeof(_CursorNudge));
                }
                
                return _CursorNudgeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct CursorClick__Args
            {
                internal int buttonId;
                [MarshalAs(UnmanagedType.I1)]
                internal bool isDown;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _CursorClick(IntPtr _this, CursorClick__Args args);
            private static _CursorClick _CursorClickFunc;
            internal static _CursorClick CursorClick() {
                if (_CursorClickFunc == null) {
                    _CursorClickFunc =
                        (_CursorClick)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiCanvas_cursorClick"), typeof(_CursorClick));
                }
                
                return _CursorClickFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct HideWindow__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _HideWindow(IntPtr _this, HideWindow__Args args);
            private static _HideWindow _HideWindowFunc;
            internal static _HideWindow HideWindow() {
                if (_HideWindowFunc == null) {
                    _HideWindowFunc =
                        (_HideWindow)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiCanvas_hideWindow"), typeof(_HideWindow));
                }
                
                return _HideWindowFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ShowWindow__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ShowWindow(IntPtr _this, ShowWindow__Args args);
            private static _ShowWindow _ShowWindowFunc;
            internal static _ShowWindow ShowWindow() {
                if (_ShowWindowFunc == null) {
                    _ShowWindowFunc =
                        (_ShowWindow)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiCanvas_showWindow"), typeof(_ShowWindow));
                }
                
                return _ShowWindowFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetVideoMode__Args
            {
                internal uint width;
                internal uint height;
                [MarshalAs(UnmanagedType.I1)]
                internal bool fullscreen;
                internal uint bitDepth;
                internal uint refreshRate;
                internal uint antialiasLevel;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetVideoMode(IntPtr _this, SetVideoMode__Args args);
            private static _SetVideoMode _SetVideoModeFunc;
            internal static _SetVideoMode SetVideoMode() {
                if (_SetVideoModeFunc == null) {
                    _SetVideoModeFunc =
                        (_SetVideoMode)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiCanvas_setVideoMode"), typeof(_SetVideoMode));
                }
                
                return _SetVideoModeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetMenuBar__Args
            {
                internal IntPtr menu;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetMenuBar(IntPtr _this, SetMenuBar__Args args);
            private static _SetMenuBar _SetMenuBarFunc;
            internal static _SetMenuBar SetMenuBar() {
                if (_SetMenuBarFunc == null) {
                    _SetMenuBarFunc =
                        (_SetMenuBar)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiCanvas_setMenuBar"), typeof(_SetMenuBar));
                }
                
                return _SetMenuBarFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetFocus__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetFocus(IntPtr _this, SetFocus__Args args);
            private static _SetFocus _SetFocusFunc;
            internal static _SetFocus SetFocus() {
                if (_SetFocusFunc == null) {
                    _SetFocusFunc =
                        (_SetFocus)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiCanvas_setFocus"), typeof(_SetFocus));
                }
                
                return _SetFocusFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct RestoreWindow__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _RestoreWindow(IntPtr _this, RestoreWindow__Args args);
            private static _RestoreWindow _RestoreWindowFunc;
            internal static _RestoreWindow RestoreWindow() {
                if (_RestoreWindowFunc == null) {
                    _RestoreWindowFunc =
                        (_RestoreWindow)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiCanvas_restoreWindow"), typeof(_RestoreWindow));
                }
                
                return _RestoreWindowFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct MaximizeWindow__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _MaximizeWindow(IntPtr _this, MaximizeWindow__Args args);
            private static _MaximizeWindow _MaximizeWindowFunc;
            internal static _MaximizeWindow MaximizeWindow() {
                if (_MaximizeWindowFunc == null) {
                    _MaximizeWindowFunc =
                        (_MaximizeWindow)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiCanvas_maximizeWindow"), typeof(_MaximizeWindow));
                }
                
                return _MaximizeWindowFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsMaximized__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsMaximized(IntPtr _this, IsMaximized__Args args);
            private static _IsMaximized _IsMaximizedFunc;
            internal static _IsMaximized IsMaximized() {
                if (_IsMaximizedFunc == null) {
                    _IsMaximizedFunc =
                        (_IsMaximized)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiCanvas_isMaximized"), typeof(_IsMaximized));
                }
                
                return _IsMaximizedFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsMinimized__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsMinimized(IntPtr _this, IsMinimized__Args args);
            private static _IsMinimized _IsMinimizedFunc;
            internal static _IsMinimized IsMinimized() {
                if (_IsMinimizedFunc == null) {
                    _IsMinimizedFunc =
                        (_IsMinimized)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiCanvas_isMinimized"), typeof(_IsMinimized));
                }
                
                return _IsMinimizedFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct MinimizeWindow__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _MinimizeWindow(IntPtr _this, MinimizeWindow__Args args);
            private static _MinimizeWindow _MinimizeWindowFunc;
            internal static _MinimizeWindow MinimizeWindow() {
                if (_MinimizeWindowFunc == null) {
                    _MinimizeWindowFunc =
                        (_MinimizeWindow)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiCanvas_minimizeWindow"), typeof(_MinimizeWindow));
                }
                
                return _MinimizeWindowFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsFullscreen__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsFullscreen(IntPtr _this, IsFullscreen__Args args);
            private static _IsFullscreen _IsFullscreenFunc;
            internal static _IsFullscreen IsFullscreen() {
                if (_IsFullscreenFunc == null) {
                    _IsFullscreenFunc =
                        (_IsFullscreen)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiCanvas_isFullscreen"), typeof(_IsFullscreen));
                }
                
                return _IsFullscreenFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetWindowPosition__Args
            {
                internal IntPtr position;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetWindowPosition(IntPtr _this, SetWindowPosition__Args args);
            private static _SetWindowPosition _SetWindowPositionFunc;
            internal static _SetWindowPosition SetWindowPosition() {
                if (_SetWindowPositionFunc == null) {
                    _SetWindowPositionFunc =
                        (_SetWindowPosition)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiCanvas_setWindowPosition"), typeof(_SetWindowPosition));
                }
                
                return _SetWindowPositionFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetWindowPosition__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate Point2I.InternalStruct _GetWindowPosition(IntPtr _this, GetWindowPosition__Args args);
            private static _GetWindowPosition _GetWindowPositionFunc;
            internal static _GetWindowPosition GetWindowPosition() {
                if (_GetWindowPositionFunc == null) {
                    _GetWindowPositionFunc =
                        (_GetWindowPosition)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiCanvas_getWindowPosition"), typeof(_GetWindowPosition));
                }
                
                return _GetWindowPositionFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ScreenToClient__Args
            {
                internal IntPtr coordinate;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate Point2I.InternalStruct _ScreenToClient(IntPtr _this, ScreenToClient__Args args);
            private static _ScreenToClient _ScreenToClientFunc;
            internal static _ScreenToClient ScreenToClient() {
                if (_ScreenToClientFunc == null) {
                    _ScreenToClientFunc =
                        (_ScreenToClient)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiCanvas_screenToClient"), typeof(_ScreenToClient));
                }
                
                return _ScreenToClientFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ClientToScreen__Args
            {
                internal IntPtr coordinate;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate Point2I.InternalStruct _ClientToScreen(IntPtr _this, ClientToScreen__Args args);
            private static _ClientToScreen _ClientToScreenFunc;
            internal static _ClientToScreen ClientToScreen() {
                if (_ClientToScreenFunc == null) {
                    _ClientToScreenFunc =
                        (_ClientToScreen)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiCanvas_clientToScreen"), typeof(_ClientToScreen));
                }
                
                return _ClientToScreenFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ToggleFullscreen__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ToggleFullscreen(IntPtr _this, ToggleFullscreen__Args args);
            private static _ToggleFullscreen _ToggleFullscreenFunc;
            internal static _ToggleFullscreen ToggleFullscreen() {
                if (_ToggleFullscreenFunc == null) {
                    _ToggleFullscreenFunc =
                        (_ToggleFullscreen)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiCanvas_toggleFullscreen"), typeof(_ToggleFullscreen));
                }
                
                return _ToggleFullscreenFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetMode__Args
            {
                internal int modeId;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetMode(IntPtr _this, GetMode__Args args);
            private static _GetMode _GetModeFunc;
            internal static _GetMode GetMode() {
                if (_GetModeFunc == null) {
                    _GetModeFunc =
                        (_GetMode)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiCanvas_getMode"), typeof(_GetMode));
                }
                
                return _GetModeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetModeCount__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetModeCount(IntPtr _this, GetModeCount__Args args);
            private static _GetModeCount _GetModeCountFunc;
            internal static _GetModeCount GetModeCount() {
                if (_GetModeCountFunc == null) {
                    _GetModeCountFunc =
                        (_GetModeCount)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiCanvas_getModeCount"), typeof(_GetModeCount));
                }
                
                return _GetModeCountFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetVideoMode__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetVideoMode(IntPtr _this, GetVideoMode__Args args);
            private static _GetVideoMode _GetVideoModeFunc;
            internal static _GetVideoMode GetVideoMode() {
                if (_GetVideoModeFunc == null) {
                    _GetVideoModeFunc =
                        (_GetVideoMode)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiCanvas_getVideoMode"), typeof(_GetVideoMode));
                }
                
                return _GetVideoModeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetMonitorDesktopMode__Args
            {
                internal int monitorIndex;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetMonitorDesktopMode(IntPtr _this, GetMonitorDesktopMode__Args args);
            private static _GetMonitorDesktopMode _GetMonitorDesktopModeFunc;
            internal static _GetMonitorDesktopMode GetMonitorDesktopMode() {
                if (_GetMonitorDesktopModeFunc == null) {
                    _GetMonitorDesktopModeFunc =
                        (_GetMonitorDesktopMode)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiCanvas_getMonitorDesktopMode"), typeof(_GetMonitorDesktopMode));
                }
                
                return _GetMonitorDesktopModeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetMonitorMode__Args
            {
                internal int monitorIndex;
                internal int modeIndex;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetMonitorMode(IntPtr _this, GetMonitorMode__Args args);
            private static _GetMonitorMode _GetMonitorModeFunc;
            internal static _GetMonitorMode GetMonitorMode() {
                if (_GetMonitorModeFunc == null) {
                    _GetMonitorModeFunc =
                        (_GetMonitorMode)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiCanvas_getMonitorMode"), typeof(_GetMonitorMode));
                }
                
                return _GetMonitorModeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetMonitorModeCount__Args
            {
                internal int monitorIndex;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetMonitorModeCount(IntPtr _this, GetMonitorModeCount__Args args);
            private static _GetMonitorModeCount _GetMonitorModeCountFunc;
            internal static _GetMonitorModeCount GetMonitorModeCount() {
                if (_GetMonitorModeCountFunc == null) {
                    _GetMonitorModeCountFunc =
                        (_GetMonitorModeCount)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiCanvas_getMonitorModeCount"), typeof(_GetMonitorModeCount));
                }
                
                return _GetMonitorModeCountFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetMonitorUsableRect__Args
            {
                internal int index;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate RectI.InternalStruct _GetMonitorUsableRect(IntPtr _this, GetMonitorUsableRect__Args args);
            private static _GetMonitorUsableRect _GetMonitorUsableRectFunc;
            internal static _GetMonitorUsableRect GetMonitorUsableRect() {
                if (_GetMonitorUsableRectFunc == null) {
                    _GetMonitorUsableRectFunc =
                        (_GetMonitorUsableRect)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiCanvas_getMonitorUsableRect"), typeof(_GetMonitorUsableRect));
                }
                
                return _GetMonitorUsableRectFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetMonitorRect__Args
            {
                internal int index;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate RectI.InternalStruct _GetMonitorRect(IntPtr _this, GetMonitorRect__Args args);
            private static _GetMonitorRect _GetMonitorRectFunc;
            internal static _GetMonitorRect GetMonitorRect() {
                if (_GetMonitorRectFunc == null) {
                    _GetMonitorRectFunc =
                        (_GetMonitorRect)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiCanvas_getMonitorRect"), typeof(_GetMonitorRect));
                }
                
                return _GetMonitorRectFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetMonitorName__Args
            {
                internal int index;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetMonitorName(IntPtr _this, GetMonitorName__Args args);
            private static _GetMonitorName _GetMonitorNameFunc;
            internal static _GetMonitorName GetMonitorName() {
                if (_GetMonitorNameFunc == null) {
                    _GetMonitorNameFunc =
                        (_GetMonitorName)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiCanvas_getMonitorName"), typeof(_GetMonitorName));
                }
                
                return _GetMonitorNameFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetMonitorCount__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetMonitorCount(IntPtr _this, GetMonitorCount__Args args);
            private static _GetMonitorCount _GetMonitorCountFunc;
            internal static _GetMonitorCount GetMonitorCount() {
                if (_GetMonitorCountFunc == null) {
                    _GetMonitorCountFunc =
                        (_GetMonitorCount)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiCanvas_getMonitorCount"), typeof(_GetMonitorCount));
                }
                
                return _GetMonitorCountFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct FindFirstMatchingMonitor__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _FindFirstMatchingMonitor(IntPtr _this, FindFirstMatchingMonitor__Args args);
            private static _FindFirstMatchingMonitor _FindFirstMatchingMonitorFunc;
            internal static _FindFirstMatchingMonitor FindFirstMatchingMonitor() {
                if (_FindFirstMatchingMonitorFunc == null) {
                    _FindFirstMatchingMonitorFunc =
                        (_FindFirstMatchingMonitor)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiCanvas_findFirstMatchingMonitor"), typeof(_FindFirstMatchingMonitor));
                }
                
                return _FindFirstMatchingMonitorFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetWindowTitle__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string newTitle;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetWindowTitle(IntPtr _this, SetWindowTitle__Args args);
            private static _SetWindowTitle _SetWindowTitleFunc;
            internal static _SetWindowTitle SetWindowTitle() {
                if (_SetWindowTitleFunc == null) {
                    _SetWindowTitleFunc =
                        (_SetWindowTitle)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiCanvas_setWindowTitle"), typeof(_SetWindowTitle));
                }
                
                return _SetWindowTitleFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetExtent__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate Point2I.InternalStruct _GetExtent(IntPtr _this, GetExtent__Args args);
            private static _GetExtent _GetExtentFunc;
            internal static _GetExtent GetExtent() {
                if (_GetExtentFunc == null) {
                    _GetExtentFunc =
                        (_GetExtent)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiCanvas_getExtent"), typeof(_GetExtent));
                }
                
                return _GetExtentFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetMouseControl__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetMouseControl(IntPtr _this, GetMouseControl__Args args);
            private static _GetMouseControl _GetMouseControlFunc;
            internal static _GetMouseControl GetMouseControl() {
                if (_GetMouseControlFunc == null) {
                    _GetMouseControlFunc =
                        (_GetMouseControl)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiCanvas_getMouseControl"), typeof(_GetMouseControl));
                }
                
                return _GetMouseControlFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetCursorPos__Args
            {
                internal IntPtr pos;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetCursorPos(IntPtr _this, SetCursorPos__Args args);
            private static _SetCursorPos _SetCursorPosFunc;
            internal static _SetCursorPos SetCursorPos() {
                if (_SetCursorPosFunc == null) {
                    _SetCursorPosFunc =
                        (_SetCursorPos)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiCanvas_setCursorPos"), typeof(_SetCursorPos));
                }
                
                return _SetCursorPosFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetCursorPos__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate Point2I.InternalStruct _GetCursorPos(IntPtr _this, GetCursorPos__Args args);
            private static _GetCursorPos _GetCursorPosFunc;
            internal static _GetCursorPos GetCursorPos() {
                if (_GetCursorPosFunc == null) {
                    _GetCursorPosFunc =
                        (_GetCursorPos)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiCanvas_getCursorPos"), typeof(_GetCursorPos));
                }
                
                return _GetCursorPosFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Reset__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Reset(IntPtr _this, Reset__Args args);
            private static _Reset _ResetFunc;
            internal static _Reset Reset() {
                if (_ResetFunc == null) {
                    _ResetFunc =
                        (_Reset)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiCanvas_reset"), typeof(_Reset));
                }
                
                return _ResetFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Repaint__Args
            {
                internal int elapsedMS;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Repaint(IntPtr _this, Repaint__Args args);
            private static _Repaint _RepaintFunc;
            internal static _Repaint Repaint() {
                if (_RepaintFunc == null) {
                    _RepaintFunc =
                        (_Repaint)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiCanvas_repaint"), typeof(_Repaint));
                }
                
                return _RepaintFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsCursorShown__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsCursorShown(IntPtr _this, IsCursorShown__Args args);
            private static _IsCursorShown _IsCursorShownFunc;
            internal static _IsCursorShown IsCursorShown() {
                if (_IsCursorShownFunc == null) {
                    _IsCursorShownFunc =
                        (_IsCursorShown)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiCanvas_isCursorShown"), typeof(_IsCursorShown));
                }
                
                return _IsCursorShownFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsCursorOn__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsCursorOn(IntPtr _this, IsCursorOn__Args args);
            private static _IsCursorOn _IsCursorOnFunc;
            internal static _IsCursorOn IsCursorOn() {
                if (_IsCursorOnFunc == null) {
                    _IsCursorOnFunc =
                        (_IsCursorOn)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiCanvas_isCursorOn"), typeof(_IsCursorOn));
                }
                
                return _IsCursorOnFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct HideCursor__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _HideCursor(IntPtr _this, HideCursor__Args args);
            private static _HideCursor _HideCursorFunc;
            internal static _HideCursor HideCursor() {
                if (_HideCursorFunc == null) {
                    _HideCursorFunc =
                        (_HideCursor)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiCanvas_hideCursor"), typeof(_HideCursor));
                }
                
                return _HideCursorFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ShowCursor__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ShowCursor(IntPtr _this, ShowCursor__Args args);
            private static _ShowCursor _ShowCursorFunc;
            internal static _ShowCursor ShowCursor() {
                if (_ShowCursorFunc == null) {
                    _ShowCursorFunc =
                        (_ShowCursor)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiCanvas_showCursor"), typeof(_ShowCursor));
                }
                
                return _ShowCursorFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct RenderFront__Args
            {
                [MarshalAs(UnmanagedType.I1)]
                internal bool enable;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _RenderFront(IntPtr _this, RenderFront__Args args);
            private static _RenderFront _RenderFrontFunc;
            internal static _RenderFront RenderFront() {
                if (_RenderFrontFunc == null) {
                    _RenderFrontFunc =
                        (_RenderFront)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiCanvas_renderFront"), typeof(_RenderFront));
                }
                
                return _RenderFrontFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetCursor__Args
            {
                internal IntPtr cursor;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetCursor(IntPtr _this, SetCursor__Args args);
            private static _SetCursor _SetCursorFunc;
            internal static _SetCursor SetCursor() {
                if (_SetCursorFunc == null) {
                    _SetCursorFunc =
                        (_SetCursor)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiCanvas_setCursor"), typeof(_SetCursor));
                }
                
                return _SetCursorFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct CursorOff__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _CursorOff(IntPtr _this, CursorOff__Args args);
            private static _CursorOff _CursorOffFunc;
            internal static _CursorOff CursorOff() {
                if (_CursorOffFunc == null) {
                    _CursorOffFunc =
                        (_CursorOff)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiCanvas_cursorOff"), typeof(_CursorOff));
                }
                
                return _CursorOffFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct CursorOn__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _CursorOn(IntPtr _this, CursorOn__Args args);
            private static _CursorOn _CursorOnFunc;
            internal static _CursorOn CursorOn() {
                if (_CursorOnFunc == null) {
                    _CursorOnFunc =
                        (_CursorOn)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiCanvas_cursorOn"), typeof(_CursorOn));
                }
                
                return _CursorOnFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct PopLayer__Args
            {
                internal int layer;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _PopLayer(IntPtr _this, PopLayer__Args args);
            private static _PopLayer _PopLayerFunc;
            internal static _PopLayer PopLayer() {
                if (_PopLayerFunc == null) {
                    _PopLayerFunc =
                        (_PopLayer)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiCanvas_popLayer"), typeof(_PopLayer));
                }
                
                return _PopLayerFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct PopDialog__Args
            {
                internal IntPtr gui;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _PopDialog(IntPtr _this, PopDialog__Args args);
            private static _PopDialog _PopDialogFunc;
            internal static _PopDialog PopDialog() {
                if (_PopDialogFunc == null) {
                    _PopDialogFunc =
                        (_PopDialog)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiCanvas_popDialog"), typeof(_PopDialog));
                }
                
                return _PopDialogFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct PushDialog__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string ctrlName;
                internal int layer;
                [MarshalAs(UnmanagedType.I1)]
                internal bool center;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _PushDialog(IntPtr _this, PushDialog__Args args);
            private static _PushDialog _PushDialogFunc;
            internal static _PushDialog PushDialog() {
                if (_PushDialogFunc == null) {
                    _PushDialogFunc =
                        (_PushDialog)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiCanvas_pushDialog"), typeof(_PushDialog));
                }
                
                return _PushDialogFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetContent__Args
            {
                internal IntPtr ctrl;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetContent(IntPtr _this, SetContent__Args args);
            private static _SetContent _SetContentFunc;
            internal static _SetContent SetContent() {
                if (_SetContentFunc == null) {
                    _SetContentFunc =
                        (_SetContent)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiCanvas_setContent"), typeof(_SetContent));
                }
                
                return _SetContentFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetContent__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetContent(IntPtr _this, GetContent__Args args);
            private static _GetContent _GetContentFunc;
            internal static _GetContent GetContent() {
                if (_GetContentFunc == null) {
                    _GetContentFunc =
                        (_GetContent)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiCanvas_getContent"), typeof(_GetContent));
                }
                
                return _GetContentFunc;
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
                                "fnGuiCanvas_staticGetType"), typeof(_StaticGetType));
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
                                "fnGuiCanvas_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// 
        public void ResetVideoMode() {
             InternalUnsafeMethods.ResetVideoMode__Args _args = new InternalUnsafeMethods.ResetVideoMode__Args() {
             };
             InternalUnsafeMethods.ResetVideoMode()(ObjectPtr, _args);
        }

        /// 
        public void CursorNudge(float x, float y) {
             InternalUnsafeMethods.CursorNudge__Args _args = new InternalUnsafeMethods.CursorNudge__Args() {
                x = x,
                y = y,
             };
             InternalUnsafeMethods.CursorNudge()(ObjectPtr, _args);
        }

        /// 
        public void CursorClick(int buttonId, bool isDown) {
             InternalUnsafeMethods.CursorClick__Args _args = new InternalUnsafeMethods.CursorClick__Args() {
                buttonId = buttonId,
                isDown = isDown,
             };
             InternalUnsafeMethods.CursorClick()(ObjectPtr, _args);
        }

        /// 
        public void HideWindow() {
             InternalUnsafeMethods.HideWindow__Args _args = new InternalUnsafeMethods.HideWindow__Args() {
             };
             InternalUnsafeMethods.HideWindow()(ObjectPtr, _args);
        }

        /// 
        public void ShowWindow() {
             InternalUnsafeMethods.ShowWindow__Args _args = new InternalUnsafeMethods.ShowWindow__Args() {
             };
             InternalUnsafeMethods.ShowWindow()(ObjectPtr, _args);
        }

        /// <description>
        /// (int width, int height, bool fullscreen, [int bitDepth], [int refreshRate], [int antialiasLevel] )
        /// Change the video mode of this canvas. This method has the side effect of setting the $pref::Video::mode to the new values.
        /// 
        /// \param width The screen width to set.
        /// \param height The screen height to set.
        /// \param fullscreen Specify true to run fullscreen or false to run in a window
        /// \param bitDepth [optional] The desired bit-depth. Defaults to the current setting. This parameter is ignored if you are running in a window.
        /// \param refreshRate [optional] The desired refresh rate. Defaults to the current setting. This parameter is ignored if you are running in a window\param antialiasLevel [optional] The level of anti-aliasing to apply 0 = none
        /// </description>
        public void SetVideoMode(uint width, uint height, bool fullscreen = false, uint bitDepth = 0, uint refreshRate = 0, uint antialiasLevel = 0) {
             InternalUnsafeMethods.SetVideoMode__Args _args = new InternalUnsafeMethods.SetVideoMode__Args() {
                width = width,
                height = height,
                fullscreen = fullscreen,
                bitDepth = bitDepth,
                refreshRate = refreshRate,
                antialiasLevel = antialiasLevel,
             };
             InternalUnsafeMethods.SetVideoMode()(ObjectPtr, _args);
        }

        /// <description>
        /// Translate a coordinate from canvas window-space to screen-space.
        /// </description>
        /// <param name="coordinate">The coordinate in window-space.</param>
        /// <returns>The given coordinate translated to screen-space.</returns>
        public void SetMenuBar(GuiControl menu) {
             InternalUnsafeMethods.SetMenuBar__Args _args = new InternalUnsafeMethods.SetMenuBar__Args() {
                menu = menu.ObjectPtr,
             };
             InternalUnsafeMethods.SetMenuBar()(ObjectPtr, _args);
        }

        /// <description>
        /// () - Claim OS input focus for this canvas' window.
        /// </description>
        public void SetFocus() {
             InternalUnsafeMethods.SetFocus__Args _args = new InternalUnsafeMethods.SetFocus__Args() {
             };
             InternalUnsafeMethods.SetFocus()(ObjectPtr, _args);
        }

        /// <description>
        /// () - restore this canvas' window.
        /// </description>
        public void RestoreWindow() {
             InternalUnsafeMethods.RestoreWindow__Args _args = new InternalUnsafeMethods.RestoreWindow__Args() {
             };
             InternalUnsafeMethods.RestoreWindow()(ObjectPtr, _args);
        }

        /// <description>
        /// () - maximize this canvas' window.
        /// </description>
        public void MaximizeWindow() {
             InternalUnsafeMethods.MaximizeWindow__Args _args = new InternalUnsafeMethods.MaximizeWindow__Args() {
             };
             InternalUnsafeMethods.MaximizeWindow()(ObjectPtr, _args);
        }

        /// <description>
        /// ()
        /// </description>
        public bool IsMaximized() {
             InternalUnsafeMethods.IsMaximized__Args _args = new InternalUnsafeMethods.IsMaximized__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.IsMaximized()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// ()
        /// </description>
        public bool IsMinimized() {
             InternalUnsafeMethods.IsMinimized__Args _args = new InternalUnsafeMethods.IsMinimized__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.IsMinimized()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// () - minimize this canvas' window.
        /// </description>
        public void MinimizeWindow() {
             InternalUnsafeMethods.MinimizeWindow__Args _args = new InternalUnsafeMethods.MinimizeWindow__Args() {
             };
             InternalUnsafeMethods.MinimizeWindow()(ObjectPtr, _args);
        }

        /// <description>
        /// () - Is this canvas currently fullscreen?
        /// </description>
        public bool IsFullscreen() {
             InternalUnsafeMethods.IsFullscreen__Args _args = new InternalUnsafeMethods.IsFullscreen__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.IsFullscreen()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Set the position of the platform window associated with the canvas.
        /// </description>
        /// <param name="position">The new position of the window in screen-space.</param>
        public void SetWindowPosition(Point2I position) {
position.Alloc();             InternalUnsafeMethods.SetWindowPosition__Args _args = new InternalUnsafeMethods.SetWindowPosition__Args() {
                position = position.internalStructPtr,
             };
             InternalUnsafeMethods.SetWindowPosition()(ObjectPtr, _args);
position.Free();        }

        /// <description>
        /// Get the current position of the platform window associated with the canvas.
        /// </description>
        /// <returns>The window position of the canvas in screen-space.</returns>
        public Point2I GetWindowPosition() {
             InternalUnsafeMethods.GetWindowPosition__Args _args = new InternalUnsafeMethods.GetWindowPosition__Args() {
             };
             Point2I.InternalStruct _engineResult = InternalUnsafeMethods.GetWindowPosition()(ObjectPtr, _args);
             return new Point2I(_engineResult);
        }

        /// <description>
        /// Translate a coordinate from screen-space to canvas window-space.
        /// </description>
        /// <param name="coordinate">The coordinate in screen-space.</param>
        /// <returns>The given coordinate translated to window-space.</returns>
        public Point2I ScreenToClient(Point2I coordinate) {
coordinate.Alloc();             InternalUnsafeMethods.ScreenToClient__Args _args = new InternalUnsafeMethods.ScreenToClient__Args() {
                coordinate = coordinate.internalStructPtr,
             };
             Point2I.InternalStruct _engineResult = InternalUnsafeMethods.ScreenToClient()(ObjectPtr, _args);
coordinate.Free();             return new Point2I(_engineResult);
        }

        /// <description>
        /// Translate a coordinate from canvas window-space to screen-space.
        /// </description>
        /// <param name="coordinate">The coordinate in window-space.</param>
        /// <returns>The given coordinate translated to screen-space.</returns>
        public Point2I ClientToScreen(Point2I coordinate) {
coordinate.Alloc();             InternalUnsafeMethods.ClientToScreen__Args _args = new InternalUnsafeMethods.ClientToScreen__Args() {
                coordinate = coordinate.internalStructPtr,
             };
             Point2I.InternalStruct _engineResult = InternalUnsafeMethods.ClientToScreen()(ObjectPtr, _args);
coordinate.Free();             return new Point2I(_engineResult);
        }

        /// <summary>toggle canvas from fullscreen to windowed mode or back.</summary>
        /// <description>
        /// 
        /// </description>
        /// <code>
        /// // If we are in windowed mode, the following will put is in fullscreen
        /// Canvas.toggleFullscreen();
        /// </code>
        public void ToggleFullscreen() {
             InternalUnsafeMethods.ToggleFullscreen__Args _args = new InternalUnsafeMethods.ToggleFullscreen__Args() {
             };
             InternalUnsafeMethods.ToggleFullscreen()(ObjectPtr, _args);
        }

        /// <summary>Gets information on the specified mode of this device.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="modeId">Index of the mode to get data from.</param>
        /// <returns>A video mode string given an adapter and mode index.</returns>
        /// <see cref="GuiCanvas::getVideoMode()" />
        public string GetMode(int modeId) {
             InternalUnsafeMethods.GetMode__Args _args = new InternalUnsafeMethods.GetMode__Args() {
                modeId = modeId,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetMode()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <summary>Gets the number of modes available on this device.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="param">Description</param>
        /// <code>
        /// %modeCount = Canvas.getModeCount()
        /// </code>
        /// <returns>The number of video modes supported by the device</returns>
        public int GetModeCount() {
             InternalUnsafeMethods.GetModeCount__Args _args = new InternalUnsafeMethods.GetModeCount__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetModeCount()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Gets the current screen mode as a string.</summary>
        /// <description>
        /// The return string will contain 5 values (width, height, fullscreen, bitdepth, refreshRate). You will need to parse out each one for individual use.
        /// </description>
        /// <code>
        /// %screenWidth = getWord(Canvas.getVideoMode(), 0);
        /// %screenHeight = getWord(Canvas.getVideoMode(), 1);
        /// %isFullscreen = getWord(Canvas.getVideoMode(), 2);
        /// %bitdepth = getWord(Canvas.getVideoMode(), 3);
        /// %refreshRate = getWord(Canvas.getVideoMode(), 4);
        /// </code>
        /// <returns>String formatted with screen width, screen height, screen mode, bit depth, and refresh rate.</returns>
        public string GetVideoMode() {
             InternalUnsafeMethods.GetVideoMode__Args _args = new InternalUnsafeMethods.GetVideoMode__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetVideoMode()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Gets the current desktop mode for the selected monitor.
        /// </description>
        public string GetMonitorDesktopMode(int monitorIndex = 0) {
             InternalUnsafeMethods.GetMonitorDesktopMode__Args _args = new InternalUnsafeMethods.GetMonitorDesktopMode__Args() {
                monitorIndex = monitorIndex,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetMonitorDesktopMode()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Gets a video mode string from the selected monitor.
        /// </description>
        public string GetMonitorMode(int monitorIndex, int modeIndex = 0) {
             InternalUnsafeMethods.GetMonitorMode__Args _args = new InternalUnsafeMethods.GetMonitorMode__Args() {
                monitorIndex = monitorIndex,
                modeIndex = modeIndex,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetMonitorMode()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Gets the number of video modes available on the selected monitor.
        /// </description>
        public int GetMonitorModeCount(int monitorIndex = 0) {
             InternalUnsafeMethods.GetMonitorModeCount__Args _args = new InternalUnsafeMethods.GetMonitorModeCount__Args() {
                monitorIndex = monitorIndex,
             };
             int _engineResult = InternalUnsafeMethods.GetMonitorModeCount()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Use this function to get the usable desktop area represented by a display, with the primary display located at 0,0.</summary>
        /// <description>
        /// This is the same area as Canvas.getMonitorRect() reports, but with portions reserved by the system removed. For example, on Apple Mac OS X, this subtracts the area occupied by the menu bar and dock.
        /// Setting a window to be fullscreen generally bypasses these unusable areas, so these are good guidelines for the maximum space available to a non - fullscreen window.
        /// </description>
        /// <param name="index">The monitor index.</param>
        /// <returns>The rectangular region of the requested monitor.</returns>
        public RectI GetMonitorUsableRect(int index) {
             InternalUnsafeMethods.GetMonitorUsableRect__Args _args = new InternalUnsafeMethods.GetMonitorUsableRect__Args() {
                index = index,
             };
             RectI.InternalStruct _engineResult = InternalUnsafeMethods.GetMonitorUsableRect()(ObjectPtr, _args);
             return new RectI(_engineResult);
        }

        /// <summary>Gets the region of the requested monitor.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="index">The monitor index.</param>
        /// <returns>The rectangular region of the requested monitor.</returns>
        public RectI GetMonitorRect(int index) {
             InternalUnsafeMethods.GetMonitorRect__Args _args = new InternalUnsafeMethods.GetMonitorRect__Args() {
                index = index,
             };
             RectI.InternalStruct _engineResult = InternalUnsafeMethods.GetMonitorRect()(ObjectPtr, _args);
             return new RectI(_engineResult);
        }

        /// <summary>Gets the name of the requested monitor.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="index">The monitor index.</param>
        /// <returns>The name of the requested monitor.</returns>
        public string GetMonitorName(int index) {
             InternalUnsafeMethods.GetMonitorName__Args _args = new InternalUnsafeMethods.GetMonitorName__Args() {
                index = index,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetMonitorName()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <summary>Gets the number of monitors attached to the system.</summary>
        /// <description>
        /// 
        /// </description>
        /// <returns>The number of monitors attached to the system, including the default monoitor.</returns>
        public int GetMonitorCount() {
             InternalUnsafeMethods.GetMonitorCount__Args _args = new InternalUnsafeMethods.GetMonitorCount__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetMonitorCount()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Find the first monitor index that matches the given name.</summary>
        /// <description>
        /// The actual match algorithm depends on the implementation.
        /// </description>
        /// <param name="name">The name to search for.</param>
        /// <returns>The number of monitors attached to the system, including the default monoitor.</returns>
        public int FindFirstMatchingMonitor(string name) {
             InternalUnsafeMethods.FindFirstMatchingMonitor__Args _args = new InternalUnsafeMethods.FindFirstMatchingMonitor__Args() {
                name = name,
             };
             int _engineResult = InternalUnsafeMethods.FindFirstMatchingMonitor()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Change the title of the OS window.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="newTitle">String containing the new name</param>
        /// <code>
        /// Canvas.setWindowTitle("Documentation Rocks!");
        /// </code>
        public void SetWindowTitle(string newTitle) {
             InternalUnsafeMethods.SetWindowTitle__Args _args = new InternalUnsafeMethods.SetWindowTitle__Args() {
                newTitle = newTitle,
             };
             InternalUnsafeMethods.SetWindowTitle()(ObjectPtr, _args);
        }

        /// <summary>Returns the dimensions of the canvas</summary>
        /// <description>
        /// 
        /// </description>
        /// <code>
        /// %extent = Canvas.getExtent();
        /// </code>
        /// <returns>Width and height of canvas. Formatted as numerical values in a single string "# #"</returns>
        public Point2I GetExtent() {
             InternalUnsafeMethods.GetExtent__Args _args = new InternalUnsafeMethods.GetExtent__Args() {
             };
             Point2I.InternalStruct _engineResult = InternalUnsafeMethods.GetExtent()(ObjectPtr, _args);
             return new Point2I(_engineResult);
        }

        /// <summary>Gets the gui control under the mouse.</summary>
        /// <description>
        /// 
        /// </description>
        /// <code>
        /// %underMouse = Canvas.getMouseControl();
        /// </code>
        /// <returns>ID of the gui control, if one was found. NULL otherwise</returns>
        public int GetMouseControl() {
             InternalUnsafeMethods.GetMouseControl__Args _args = new InternalUnsafeMethods.GetMouseControl__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetMouseControl()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// (Point2I pos)
        /// </description>
        public void SetCursorPos(Point2I pos) {
pos.Alloc();             InternalUnsafeMethods.SetCursorPos__Args _args = new InternalUnsafeMethods.SetCursorPos__Args() {
                pos = pos.internalStructPtr,
             };
             InternalUnsafeMethods.SetCursorPos()(ObjectPtr, _args);
pos.Free();        }

        /// <summary>Get the current position of the cursor in screen-space. Note that this position might be outside the Torque window. If you want to get the position within the Canvas, call screenToClient on the result.</summary>
        /// <description>
        /// 
        /// </description>
        /// <see cref="Canvas::screenToClient()" />
        /// <param name="param">Description</param>
        /// <code>
        /// %cursorPos = Canvas.getCursorPos();
        /// </code>
        /// <returns>Screen coordinates of mouse cursor, in format "X Y"</returns>
        public Point2I GetCursorPos() {
             InternalUnsafeMethods.GetCursorPos__Args _args = new InternalUnsafeMethods.GetCursorPos__Args() {
             };
             Point2I.InternalStruct _engineResult = InternalUnsafeMethods.GetCursorPos()(ObjectPtr, _args);
             return new Point2I(_engineResult);
        }

        /// <summary>Reset the update regions for the canvas.</summary>
        /// <description>
        /// 
        /// </description>
        public void Reset() {
             InternalUnsafeMethods.Reset__Args _args = new InternalUnsafeMethods.Reset__Args() {
             };
             InternalUnsafeMethods.Reset()(ObjectPtr, _args);
        }

        /// <summary>Force canvas to redraw.</summary>
        /// <description>
        /// If the elapsed time is greater than the time since the last paint then the repaint will be skipped.
        /// </description>
        /// <param name="elapsedMS">The optional elapsed time in milliseconds.</param>
        public void Repaint(int elapsedMS = 0) {
             InternalUnsafeMethods.Repaint__Args _args = new InternalUnsafeMethods.Repaint__Args() {
                elapsedMS = elapsedMS,
             };
             InternalUnsafeMethods.Repaint()(ObjectPtr, _args);
        }

        /// <summary>Determines if mouse cursor is rendering.</summary>
        /// <description>
        /// 
        /// </description>
        /// <code>
        /// // Is cursor rendering?
        /// if(Canvas.isCursorShown())
        ///   echo("Canvas cursor is rendering");
        /// </code>
        /// <returns>Returns true if the cursor is rendering.</returns>
        public bool IsCursorShown() {
             InternalUnsafeMethods.IsCursorShown__Args _args = new InternalUnsafeMethods.IsCursorShown__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.IsCursorShown()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Determines if mouse cursor is enabled.</summary>
        /// <description>
        /// 
        /// </description>
        /// <code>
        /// // Is cursor on?
        /// if(Canvas.isCursorOn())
        ///   echo("Canvas cursor is on");
        /// </code>
        /// <returns>Returns true if the cursor is on.</returns>
        public bool IsCursorOn() {
             InternalUnsafeMethods.IsCursorOn__Args _args = new InternalUnsafeMethods.IsCursorOn__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.IsCursorOn()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Disable rendering of the cursor.</summary>
        /// <description>
        /// 
        /// </description>
        public void HideCursor() {
             InternalUnsafeMethods.HideCursor__Args _args = new InternalUnsafeMethods.HideCursor__Args() {
             };
             InternalUnsafeMethods.HideCursor()(ObjectPtr, _args);
        }

        /// <summary>Enable rendering of the cursor.</summary>
        /// <description>
        /// 
        /// </description>
        public void ShowCursor() {
             InternalUnsafeMethods.ShowCursor__Args _args = new InternalUnsafeMethods.ShowCursor__Args() {
             };
             InternalUnsafeMethods.ShowCursor()(ObjectPtr, _args);
        }

        /// <summary>This turns on/off front-buffer rendering.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="enable">True if all rendering should be done to the front buffer</param>
        public void RenderFront(bool enable) {
             InternalUnsafeMethods.RenderFront__Args _args = new InternalUnsafeMethods.RenderFront__Args() {
                enable = enable,
             };
             InternalUnsafeMethods.RenderFront()(ObjectPtr, _args);
        }

        /// <summary>Sets the cursor for the canvas.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="cursor">Name of the GuiCursor to use</param>
        public void SetCursor(GuiCursor cursor) {
             InternalUnsafeMethods.SetCursor__Args _args = new InternalUnsafeMethods.SetCursor__Args() {
                cursor = cursor.ObjectPtr,
             };
             InternalUnsafeMethods.SetCursor()(ObjectPtr, _args);
        }

        /// <summary>Turns on the mouse off.</summary>
        /// <description>
        /// 
        /// </description>
        public void CursorOff() {
             InternalUnsafeMethods.CursorOff__Args _args = new InternalUnsafeMethods.CursorOff__Args() {
             };
             InternalUnsafeMethods.CursorOff()(ObjectPtr, _args);
        }

        /// <summary>Turns on the mouse cursor.</summary>
        /// <description>
        /// 
        /// </description>
        public void CursorOn() {
             InternalUnsafeMethods.CursorOn__Args _args = new InternalUnsafeMethods.CursorOn__Args() {
             };
             InternalUnsafeMethods.CursorOn()(ObjectPtr, _args);
        }

        /// <description>
        /// (int layer)
        /// </description>
        public void PopLayer(int layer = 0) {
             InternalUnsafeMethods.PopLayer__Args _args = new InternalUnsafeMethods.PopLayer__Args() {
                layer = layer,
             };
             InternalUnsafeMethods.PopLayer()(ObjectPtr, _args);
        }

        /// <description>
        /// (GuiControl ctrl=NULL)
        /// </description>
        public void PopDialog(GuiControl gui = null) {
             InternalUnsafeMethods.PopDialog__Args _args = new InternalUnsafeMethods.PopDialog__Args() {
                gui = gui.ObjectPtr,
             };
             InternalUnsafeMethods.PopDialog()(ObjectPtr, _args);
        }

        /// <description>
        /// (GuiControl ctrl, int layer=0, bool center=false)
        /// </description>
        public void PushDialog(string ctrlName, int layer = 0, bool center = false) {
             InternalUnsafeMethods.PushDialog__Args _args = new InternalUnsafeMethods.PushDialog__Args() {
                ctrlName = ctrlName,
                layer = layer,
                center = center,
             };
             InternalUnsafeMethods.PushDialog()(ObjectPtr, _args);
        }

        /// <summary>Set the content of the canvas to a specified control.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="ctrl">ID or name of GuiControl to set content to</param>
        public void SetContent(GuiControl ctrl) {
             InternalUnsafeMethods.SetContent__Args _args = new InternalUnsafeMethods.SetContent__Args() {
                ctrl = ctrl.ObjectPtr,
             };
             InternalUnsafeMethods.SetContent()(ObjectPtr, _args);
        }

        /// <summary>Get the GuiControl which is being used as the content.</summary>
        /// <description>
        /// 
        /// </description>
        /// <returns>ID of current content control</returns>
        public int GetContent() {
             InternalUnsafeMethods.GetContent__Args _args = new InternalUnsafeMethods.GetContent__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetContent()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Get the type info object for the GuiCanvas class.
        /// </description>
        /// <returns>The type info object for GuiCanvas</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Deal with mouse buttons, even if the cursor is hidden.
        /// </description>
        /// </value>
        public bool AlwaysHandleMouseButtons {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("alwaysHandleMouseButtons"));
            set => SetFieldValue("alwaysHandleMouseButtons", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The number of GFX fences to use.
        /// </description>
        /// </value>
        public int NumFences {
            get => GenericMarshal.StringTo<int>(GetFieldValue("numFences"));
            set => SetFieldValue("numFences", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Controls if the canvas window is rendered or not.
        /// </description>
        /// </value>
        public bool DisplayWindow {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("displayWindow"));
            set => SetFieldValue("displayWindow", GenericMarshal.ToString(value));
        }
    }
}