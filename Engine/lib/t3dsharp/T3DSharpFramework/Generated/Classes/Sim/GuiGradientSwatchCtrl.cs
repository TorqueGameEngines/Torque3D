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
    /// <summary>Swatch selector that appears inside the GuiGradientCtrl object. These objects are automatically created by GuiGradientCtrl.</summary>
    /// <description>
    /// Currently only appears to be editor specific
    /// </description>
    /// <see cref="GuiSwatchButtonCtrl" />
    /// <see cref="GuiGradientCtrl" />
    public unsafe class GuiGradientSwatchCtrl : GuiSwatchButtonCtrl {
        public GuiGradientSwatchCtrl(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public GuiGradientSwatchCtrl(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public GuiGradientSwatchCtrl(string pName) 
            : this(pName, false) {
        }
        
        public GuiGradientSwatchCtrl(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public GuiGradientSwatchCtrl(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public GuiGradientSwatchCtrl(SimObject pObj) 
            : base(pObj) {
        }
        
        public GuiGradientSwatchCtrl(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct OnDoubleClick__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnDoubleClick(IntPtr _this, OnDoubleClick__Args args);
            private static _OnDoubleClick _OnDoubleClickFunc;
            internal static _OnDoubleClick OnDoubleClick() {
                if (_OnDoubleClickFunc == null) {
                    _OnDoubleClickFunc =
                        (_OnDoubleClick)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbGuiGradientSwatchCtrl_onDoubleClick"), typeof(_OnDoubleClick));
                }
                
                return _OnDoubleClickFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnMouseDown__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnMouseDown(IntPtr _this, OnMouseDown__Args args);
            private static _OnMouseDown _OnMouseDownFunc;
            internal static _OnMouseDown OnMouseDown() {
                if (_OnMouseDownFunc == null) {
                    _OnMouseDownFunc =
                        (_OnMouseDown)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbGuiGradientSwatchCtrl_onMouseDown"), typeof(_OnMouseDown));
                }
                
                return _OnMouseDownFunc;
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
                                "fnGuiGradientSwatchCtrl_staticGetType"), typeof(_StaticGetType));
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
                                "fnGuiGradientSwatchCtrl_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <summary>Called whenever the left mouse button performs a double click while in this control.</summary>
        /// <description>
        /// 
        /// </description>
        /// <code>
        /// // The left mouse button has performed a double click on the control, causing the callback to occur.
        /// GuiGradientSwatchCtrl::onDoubleClick(%this)
        /// 	{
        /// 		// Code to run when the callback occurs
        /// 	}
        /// </code>
        /// <see cref="GuiControl" />
        /// <see cref="GuiSwatchButtonCtrl" />
        public virtual void OnDoubleClick() {
             InternalUnsafeMethods.OnDoubleClick__Args _args = new InternalUnsafeMethods.OnDoubleClick__Args() {
             };
             InternalUnsafeMethods.OnDoubleClick()(ObjectPtr, _args);
        }

        /// <summary>Called whenever the left mouse button has entered the down state while in this control.</summary>
        /// <description>
        /// 
        /// </description>
        /// <code>
        /// // The left mouse button is down on the control, causing the callback to occur.
        /// GuiGradientSwatchCtrl::onMouseDown(%this)
        /// 	{
        /// 		// Code to run when the callback occurs
        /// 	}
        /// </code>
        /// <see cref="GuiControl" />
        /// <see cref="GuiSwatchButtonCtrl" />
        public virtual void OnMouseDown() {
             InternalUnsafeMethods.OnMouseDown__Args _args = new InternalUnsafeMethods.OnMouseDown__Args() {
             };
             InternalUnsafeMethods.OnMouseDown()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the GuiGradientSwatchCtrl class.
        /// </description>
        /// <returns>The type info object for GuiGradientSwatchCtrl</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }
    }
}