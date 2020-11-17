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
    /// 
    public unsafe class VEditorWindow : GuiCanvas {
        public VEditorWindow(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public VEditorWindow(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public VEditorWindow(string pName) 
            : this(pName, false) {
        }
        
        public VEditorWindow(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public VEditorWindow(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public VEditorWindow(SimObject pObj) 
            : base(pObj) {
        }
        
        public VEditorWindow(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct SetVideoMode__Args
            {
                internal int width;
                internal int height;
                [MarshalAs(UnmanagedType.I1)]
                internal bool fullscreen;
                internal int bitDepth;
                internal int refreshRate;
                internal int antiAliasLevel;
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
                                "fnVEditorWindow_setVideoMode"), typeof(_SetVideoMode));
                }
                
                return _SetVideoModeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ResetCursor__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ResetCursor(IntPtr _this, ResetCursor__Args args);
            private static _ResetCursor _ResetCursorFunc;
            internal static _ResetCursor ResetCursor() {
                if (_ResetCursorFunc == null) {
                    _ResetCursorFunc =
                        (_ResetCursor)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVEditorWindow_resetCursor"), typeof(_ResetCursor));
                }
                
                return _ResetCursorFunc;
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
                                "fnVEditorWindow_staticGetType"), typeof(_StaticGetType));
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
                                "fnVEditorWindow_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// (int width, int height, bool fullscreen, [int bitDepth], [int refreshRate])
        /// Change the video mode of this canvas. This method has the side effect of setting the $pref::Video::mode to the new values.
        /// 
        /// \param width The screen width to set.
        /// \param height The screen height to set.
        /// \param fullscreen Specify true to run fullscreen or false to run in a window
        /// \param bitDepth [optional] The desired bit-depth. Defaults to the current setting. This parameter is ignored if you are running in a window.
        /// \param refreshRate [optional] The desired refresh rate. Defaults to the current setting. This parameter is ignored if you are running in a window\param antialiasLevel [optional] The level of anti-aliasing to apply 0 = none
        /// </description>
        public void SetVideoMode(int width = 800, int height = 600, bool fullscreen = false, int bitDepth = 32, int refreshRate = 60, int antiAliasLevel = 0) {
             InternalUnsafeMethods.SetVideoMode__Args _args = new InternalUnsafeMethods.SetVideoMode__Args() {
                width = width,
                height = height,
                fullscreen = fullscreen,
                bitDepth = bitDepth,
                refreshRate = refreshRate,
                antiAliasLevel = antiAliasLevel,
             };
             InternalUnsafeMethods.SetVideoMode()(ObjectPtr, _args);
        }

        /// <description>
        /// ( )
        /// </description>
        public void ResetCursor() {
             InternalUnsafeMethods.ResetCursor__Args _args = new InternalUnsafeMethods.ResetCursor__Args() {
             };
             InternalUnsafeMethods.ResetCursor()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the VEditorWindow class.
        /// </description>
        /// <returns>The type info object for VEditorWindow</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }
    }
}