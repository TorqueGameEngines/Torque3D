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
    /// <summary>Visual representation of color box used with the GuiColorPickerCtrl</summary>
    /// <description>
    /// Editor use only.
    /// </description>
    public unsafe class GuiGradientCtrl : GuiControl {
        public GuiGradientCtrl(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public GuiGradientCtrl(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public GuiGradientCtrl(string pName) 
            : this(pName, false) {
        }
        
        public GuiGradientCtrl(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public GuiGradientCtrl(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public GuiGradientCtrl(SimObject pObj) 
            : base(pObj) {
        }
        
        public GuiGradientCtrl(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct GetColor__Args
            {
                internal int idx;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate LinearColorF.InternalStruct _GetColor(IntPtr _this, GetColor__Args args);
            private static _GetColor _GetColorFunc;
            internal static _GetColor GetColor() {
                if (_GetColorFunc == null) {
                    _GetColorFunc =
                        (_GetColor)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiGradientCtrl_getColor"), typeof(_GetColor));
                }
                
                return _GetColorFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetColorCount__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetColorCount(IntPtr _this, GetColorCount__Args args);
            private static _GetColorCount _GetColorCountFunc;
            internal static _GetColorCount GetColorCount() {
                if (_GetColorCountFunc == null) {
                    _GetColorCountFunc =
                        (_GetColorCount)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiGradientCtrl_getColorCount"), typeof(_GetColorCount));
                }
                
                return _GetColorCountFunc;
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
                                "fnGuiGradientCtrl_staticGetType"), typeof(_StaticGetType));
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
                                "fnGuiGradientCtrl_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get color value
        /// </description>
        public LinearColorF GetColor(int idx) {
             InternalUnsafeMethods.GetColor__Args _args = new InternalUnsafeMethods.GetColor__Args() {
                idx = idx,
             };
             LinearColorF.InternalStruct _engineResult = InternalUnsafeMethods.GetColor()(ObjectPtr, _args);
             return new LinearColorF(_engineResult);
        }

        /// <description>
        /// Get color count
        /// </description>
        public int GetColorCount() {
             InternalUnsafeMethods.GetColorCount__Args _args = new InternalUnsafeMethods.GetColorCount__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetColorCount()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Get the type info object for the GuiGradientCtrl class.
        /// </description>
        /// <returns>The type info object for GuiGradientCtrl</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// 
        /// </value>
        public LinearColorF BaseColor {
            get => GenericMarshal.StringTo<LinearColorF>(GetFieldValue("baseColor"));
            set => SetFieldValue("baseColor", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public LinearColorF PickColor {
            get => GenericMarshal.StringTo<LinearColorF>(GetFieldValue("pickColor"));
            set => SetFieldValue("pickColor", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public GuiGradientPickMode DisplayMode {
            get => GenericMarshal.StringTo<GuiGradientPickMode>(GetFieldValue("displayMode"));
            set => SetFieldValue("displayMode", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public bool ActionOnMove {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("actionOnMove"));
            set => SetFieldValue("actionOnMove", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public bool ShowReticle {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("showReticle"));
            set => SetFieldValue("showReticle", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public int SwatchFactor {
            get => GenericMarshal.StringTo<int>(GetFieldValue("swatchFactor"));
            set => SetFieldValue("swatchFactor", GenericMarshal.ToString(value));
        }
    }
}