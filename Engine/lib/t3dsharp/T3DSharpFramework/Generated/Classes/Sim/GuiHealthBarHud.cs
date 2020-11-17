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
    /// <summary>A basic health bar. Shows the damage value of the current PlayerObjectType control object.</summary>
    /// <description>
    /// This gui displays the damage value of the current PlayerObjectType control object. The gui can be set to pulse if the health value drops below a set value. This control only works if a server connection exists and it's control object is a PlayerObjectType. If either of these requirements is false, the control is not rendered.
    /// </description>
    /// <code>
    /// new GuiHealthBarHud(){
    /// 	fillColor = "0.0 1.0 0.0 1.0"; // Fills with a solid green color
    /// 	frameColor = "1.0 1.0 1.0 1.0"; // Solid white frame color
    /// 	damageFillColor = "1.0 0.0 0.0 1.0"; // Fills with a solid red color
    /// 	pulseRate = "500";
    /// 	pulseThreshold = "0.25";
    /// 	showFill = "true";
    /// 	showFrame = "true";
    /// 	displayEnergy = "false";
    /// };
    /// </code>
    public unsafe class GuiHealthBarHud : GuiControl {
        public GuiHealthBarHud(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public GuiHealthBarHud(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public GuiHealthBarHud(string pName) 
            : this(pName, false) {
        }
        
        public GuiHealthBarHud(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public GuiHealthBarHud(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public GuiHealthBarHud(SimObject pObj) 
            : base(pObj) {
        }
        
        public GuiHealthBarHud(IntPtr pObj) 
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
                                "fnGuiHealthBarHud_staticGetType"), typeof(_StaticGetType));
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
                                "fnGuiHealthBarHud_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the GuiHealthBarHud class.
        /// </description>
        /// <returns>The type info object for GuiHealthBarHud</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Standard color for the background of the control.
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
        /// As the health bar depletes, this color will represent the health loss amount.
        /// </description>
        /// </value>
        public LinearColorF DamageFillColor {
            get => GenericMarshal.StringTo<LinearColorF>(GetFieldValue("damageFillColor"));
            set => SetFieldValue("damageFillColor", GenericMarshal.ToString(value));
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


        /// <value>
        /// <description>
        /// Health level the control must be under before the control will pulse.
        /// </description>
        /// </value>
        public float PulseThreshold {
            get => GenericMarshal.StringTo<float>(GetFieldValue("pulseThreshold"));
            set => SetFieldValue("pulseThreshold", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// If true, we draw the background color of the control.
        /// </description>
        /// </value>
        public bool ShowFill {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("showFill"));
            set => SetFieldValue("showFill", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// If true, we draw the frame of the control.
        /// </description>
        /// </value>
        public bool ShowFrame {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("showFrame"));
            set => SetFieldValue("showFrame", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// If true, display the energy value rather than the damage value.
        /// </description>
        /// </value>
        public bool DisplayEnergy {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("displayEnergy"));
            set => SetFieldValue("displayEnergy", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// If true, will fill bar in opposite direction.
        /// </description>
        /// </value>
        public bool Flip {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("flip"));
            set => SetFieldValue("flip", GenericMarshal.ToString(value));
        }
    }
}