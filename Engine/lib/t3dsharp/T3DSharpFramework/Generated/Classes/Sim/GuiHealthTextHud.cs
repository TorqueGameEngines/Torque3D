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
    /// <summary>Shows the health or energy value of the current PlayerObjectType control object.</summary>
    /// <description>
    /// This gui can be configured to display either the health or energy value of the current Player Object. It can use an alternate display color if the health or drops below a set value. It can also be set to pulse if the health or energy drops below a set value. This control only works if a server connection exists and it's control object is a PlayerObjectType. If either of these requirements is false, the control is not rendered.
    /// </description>
    /// <code>
    /// new GuiHealthTextHud(){
    ///    fillColor = "0.0 0.0 0.0 0.5"; // Fills with a transparent black color
    ///    frameColor = "1.0 1.0 1.0 1.0"; // Solid white frame color
    ///    textColor = "0.0 1.0 0.0 1.0" // Solid green text color
    ///    warningColor = "1.0 0.0 0.0 1.0"; // Solid red color, used when damaged
    ///    showFill = "true";
    ///    showFrame = "true";
    ///    showTrueValue = "false";
    ///    showEnergy = "false";
    ///    warnThreshold = "50";
    ///    pulseThreshold = "25";
    ///    pulseRate = "500";
    ///    profile = "GuiBigTextProfile";
    /// };
    /// </code>
    public unsafe class GuiHealthTextHud : GuiControl {
        public GuiHealthTextHud(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public GuiHealthTextHud(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public GuiHealthTextHud(string pName) 
            : this(pName, false) {
        }
        
        public GuiHealthTextHud(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public GuiHealthTextHud(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public GuiHealthTextHud(SimObject pObj) 
            : base(pObj) {
        }
        
        public GuiHealthTextHud(IntPtr pObj) 
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
                                "fnGuiHealthTextHud_staticGetType"), typeof(_StaticGetType));
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
                                "fnGuiHealthTextHud_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the GuiHealthTextHud class.
        /// </description>
        /// <returns>The type info object for GuiHealthTextHud</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Color for the background of the control.
        /// </description>
        /// </value>
        public LinearColorF FillColor {
            get => GenericMarshal.StringTo<LinearColorF>(GetFieldValue("fillColor"));
            set => SetFieldValue("fillColor", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Color for the control's frame.
        /// </description>
        /// </value>
        public LinearColorF FrameColor {
            get => GenericMarshal.StringTo<LinearColorF>(GetFieldValue("frameColor"));
            set => SetFieldValue("frameColor", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Color for the text on this control.
        /// </description>
        /// </value>
        public LinearColorF TextColor {
            get => GenericMarshal.StringTo<LinearColorF>(GetFieldValue("textColor"));
            set => SetFieldValue("textColor", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Color for the text when health is low.
        /// </description>
        /// </value>
        public LinearColorF WarningColor {
            get => GenericMarshal.StringTo<LinearColorF>(GetFieldValue("warningColor"));
            set => SetFieldValue("warningColor", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// If true, draw the background.
        /// </description>
        /// </value>
        public bool ShowFill {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("showFill"));
            set => SetFieldValue("showFill", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// If true, draw the frame.
        /// </description>
        /// </value>
        public bool ShowFrame {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("showFrame"));
            set => SetFieldValue("showFrame", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// If true, we don't hardcode maxHealth to 100.
        /// </description>
        /// </value>
        public bool ShowTrueValue {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("showTrueValue"));
            set => SetFieldValue("showTrueValue", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// If true, display the energy value rather than the damage value.
        /// </description>
        /// </value>
        public bool ShowEnergy {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("showEnergy"));
            set => SetFieldValue("showEnergy", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The health level at which to use the warningColor.
        /// </description>
        /// </value>
        public float WarnThreshold {
            get => GenericMarshal.StringTo<float>(GetFieldValue("warnThreshold"));
            set => SetFieldValue("warnThreshold", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Health level at which to begin pulsing.
        /// </description>
        /// </value>
        public float PulseThreshold {
            get => GenericMarshal.StringTo<float>(GetFieldValue("pulseThreshold"));
            set => SetFieldValue("pulseThreshold", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Speed at which the control will pulse.
        /// </description>
        /// </value>
        public int PulseRate {
            get => GenericMarshal.StringTo<int>(GetFieldValue("pulseRate"));
            set => SetFieldValue("pulseRate", GenericMarshal.ToString(value));
        }
    }
}