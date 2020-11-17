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
    /// <summary>Unimplemented GUI control meant to interact with Toolbox.</summary>
    /// <description>
    /// For Torque 3D editors only, soon to be deprecated
    /// </description>
    public unsafe class GuiToolboxButtonCtrl : GuiButtonCtrl {
        public GuiToolboxButtonCtrl(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public GuiToolboxButtonCtrl(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public GuiToolboxButtonCtrl(string pName) 
            : this(pName, false) {
        }
        
        public GuiToolboxButtonCtrl(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public GuiToolboxButtonCtrl(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public GuiToolboxButtonCtrl(SimObject pObj) 
            : base(pObj) {
        }
        
        public GuiToolboxButtonCtrl(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct SetHoverBitmap__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetHoverBitmap(IntPtr _this, SetHoverBitmap__Args args);
            private static _SetHoverBitmap _SetHoverBitmapFunc;
            internal static _SetHoverBitmap SetHoverBitmap() {
                if (_SetHoverBitmapFunc == null) {
                    _SetHoverBitmapFunc =
                        (_SetHoverBitmap)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiToolboxButtonCtrl_setHoverBitmap"), typeof(_SetHoverBitmap));
                }
                
                return _SetHoverBitmapFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetLoweredBitmap__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetLoweredBitmap(IntPtr _this, SetLoweredBitmap__Args args);
            private static _SetLoweredBitmap _SetLoweredBitmapFunc;
            internal static _SetLoweredBitmap SetLoweredBitmap() {
                if (_SetLoweredBitmapFunc == null) {
                    _SetLoweredBitmapFunc =
                        (_SetLoweredBitmap)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiToolboxButtonCtrl_setLoweredBitmap"), typeof(_SetLoweredBitmap));
                }
                
                return _SetLoweredBitmapFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetNormalBitmap__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetNormalBitmap(IntPtr _this, SetNormalBitmap__Args args);
            private static _SetNormalBitmap _SetNormalBitmapFunc;
            internal static _SetNormalBitmap SetNormalBitmap() {
                if (_SetNormalBitmapFunc == null) {
                    _SetNormalBitmapFunc =
                        (_SetNormalBitmap)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiToolboxButtonCtrl_setNormalBitmap"), typeof(_SetNormalBitmap));
                }
                
                return _SetNormalBitmapFunc;
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
                                "fnGuiToolboxButtonCtrl_staticGetType"), typeof(_StaticGetType));
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
                                "fnGuiToolboxButtonCtrl_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// ( filepath name ) sets the bitmap that shows when the button is disabled
        /// </description>
        public void SetHoverBitmap(string name) {
             InternalUnsafeMethods.SetHoverBitmap__Args _args = new InternalUnsafeMethods.SetHoverBitmap__Args() {
                name = name,
             };
             InternalUnsafeMethods.SetHoverBitmap()(ObjectPtr, _args);
        }

        /// <description>
        /// ( filepath name ) sets the bitmap that shows when the button is disabled
        /// </description>
        public void SetLoweredBitmap(string name) {
             InternalUnsafeMethods.SetLoweredBitmap__Args _args = new InternalUnsafeMethods.SetLoweredBitmap__Args() {
                name = name,
             };
             InternalUnsafeMethods.SetLoweredBitmap()(ObjectPtr, _args);
        }

        /// <description>
        /// ( filepath name ) sets the bitmap that shows when the button is active
        /// </description>
        public void SetNormalBitmap(string name) {
             InternalUnsafeMethods.SetNormalBitmap__Args _args = new InternalUnsafeMethods.SetNormalBitmap__Args() {
                name = name,
             };
             InternalUnsafeMethods.SetNormalBitmap()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the GuiToolboxButtonCtrl class.
        /// </description>
        /// <returns>The type info object for GuiToolboxButtonCtrl</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// 
        /// </value>
        public string NormalBitmap {
            get => GenericMarshal.StringTo<string>(GetFieldValue("normalBitmap"));
            set => SetFieldValue("normalBitmap", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public string LoweredBitmap {
            get => GenericMarshal.StringTo<string>(GetFieldValue("loweredBitmap"));
            set => SetFieldValue("loweredBitmap", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public string HoverBitmap {
            get => GenericMarshal.StringTo<string>(GetFieldValue("hoverBitmap"));
            set => SetFieldValue("hoverBitmap", GenericMarshal.ToString(value));
        }
    }
}