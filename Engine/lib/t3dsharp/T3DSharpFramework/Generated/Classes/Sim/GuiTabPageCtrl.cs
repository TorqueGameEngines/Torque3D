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
    /// <summary>A single page in a GuiTabBookCtrl.</summary>
    /// <description>
    /// 
    /// </description>
    /// <code>
    /// new GuiTabPageCtrl()
    /// {
    ///    fitBook = "1";
    ///    //Properties not specific to this control have been omitted from this example.
    /// };
    /// </code>
    public unsafe class GuiTabPageCtrl : GuiTextCtrl {
        public GuiTabPageCtrl(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public GuiTabPageCtrl(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public GuiTabPageCtrl(string pName) 
            : this(pName, false) {
        }
        
        public GuiTabPageCtrl(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public GuiTabPageCtrl(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public GuiTabPageCtrl(SimObject pObj) 
            : base(pObj) {
        }
        
        public GuiTabPageCtrl(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct Select__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Select(IntPtr _this, Select__Args args);
            private static _Select _SelectFunc;
            internal static _Select Select() {
                if (_SelectFunc == null) {
                    _SelectFunc =
                        (_Select)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiTabPageCtrl_select"), typeof(_Select));
                }
                
                return _SelectFunc;
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
                                "fnGuiTabPageCtrl_staticGetType"), typeof(_StaticGetType));
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
                                "fnGuiTabPageCtrl_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Select this page in its tab book.
        /// </description>
        public void Select() {
             InternalUnsafeMethods.Select__Args _args = new InternalUnsafeMethods.Select__Args() {
             };
             InternalUnsafeMethods.Select()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the GuiTabPageCtrl class.
        /// </description>
        /// <returns>The type info object for GuiTabPageCtrl</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Determines whether to resize this page when it is added to the tab book. If true, the page will be resized according to the tab book extents and <i>tabPosition</i> property.
        /// </description>
        /// </value>
        public bool FitBook {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("fitBook"));
            set => SetFieldValue("fitBook", GenericMarshal.ToString(value));
        }
    }
}