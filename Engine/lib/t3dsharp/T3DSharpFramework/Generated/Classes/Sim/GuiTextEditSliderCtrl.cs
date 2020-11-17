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
    /// <summary>GUI Control which displays a numerical value which can be increased or decreased using a pair of arrows.</summary>
    /// <description>
    /// 
    /// </description>
    /// <code>
    /// new GuiTextEditSliderCtrl()
    /// {
    ///    format = "%3.2f";
    ///    range = "-1e+03 1e+03";
    ///    increment = "0.1";
    ///    focusOnMouseWheel = "0";
    ///    //Properties not specific to this control have been omitted from this example.
    /// };
    /// </code>
    /// <see cref="GuiTextEditCtrl" />
    public unsafe class GuiTextEditSliderCtrl : GuiTextEditCtrl {
        public GuiTextEditSliderCtrl(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public GuiTextEditSliderCtrl(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public GuiTextEditSliderCtrl(string pName) 
            : this(pName, false) {
        }
        
        public GuiTextEditSliderCtrl(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public GuiTextEditSliderCtrl(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public GuiTextEditSliderCtrl(SimObject pObj) 
            : base(pObj) {
        }
        
        public GuiTextEditSliderCtrl(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
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
                                "fnGuiTextEditSliderCtrl_staticGetType"), typeof(_StaticGetType));
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
                                "fnGuiTextEditSliderCtrl_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the GuiTextEditSliderCtrl class.
        /// </description>
        /// <returns>The type info object for GuiTextEditSliderCtrl</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Character format type to place in the control.
        /// </description>
        /// </value>
        public string Format {
            get => GenericMarshal.StringTo<string>(GetFieldValue("Format"));
            set => SetFieldValue("Format", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Maximum vertical and horizontal range to allow in the control.
        /// </description>
        /// </value>
        public Point2F Range {
            get => GenericMarshal.StringTo<Point2F>(GetFieldValue("range"));
            set => SetFieldValue("range", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// How far to increment the slider on each step.
        /// </description>
        /// </value>
        public float Increment {
            get => GenericMarshal.StringTo<float>(GetFieldValue("increment"));
            set => SetFieldValue("increment", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// If true, the control will accept giving focus to the user when the mouse wheel is used.
        /// </description>
        /// </value>
        public bool FocusOnMouseWheel {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("focusOnMouseWheel"));
            set => SetFieldValue("focusOnMouseWheel", GenericMarshal.ToString(value));
        }
    }
}