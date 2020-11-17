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
    /// <summary>Displays the speed of the current Vehicle based control object.</summary>
    /// <description>
    /// This control only works if a server connection exists, and its control object is a Vehicle derived class. If either of these requirements is false, the control is not rendered.<br>The control renders the speedometer needle as a colored quad, rotated to indicate the Vehicle speed as determined by the <i>minAngle</i>, <i>maxAngle</i>, and <i>maxSpeed</i> properties. This control is normally placed on top of a GuiBitmapCtrl representing the speedometer dial.
    /// </description>
    /// <code>
    /// new GuiSpeedometerHud()
    /// {
    ///    maxSpeed = "100";
    ///    minAngle = "215";
    ///    maxAngle = "0";
    ///    color = "1 0.3 0.3 1";
    ///    center = "130 123";
    ///    length = "100";
    ///    width = "2";
    ///    tail = "0";
    ///    //Properties not specific to this control have been omitted from this example.
    /// };
    /// </code>
    public unsafe class GuiSpeedometerHud : GuiBitmapCtrl {
        public GuiSpeedometerHud(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public GuiSpeedometerHud(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public GuiSpeedometerHud(string pName) 
            : this(pName, false) {
        }
        
        public GuiSpeedometerHud(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public GuiSpeedometerHud(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public GuiSpeedometerHud(SimObject pObj) 
            : base(pObj) {
        }
        
        public GuiSpeedometerHud(IntPtr pObj) 
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
                                "fnGuiSpeedometerHud_staticGetType"), typeof(_StaticGetType));
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
                                "fnGuiSpeedometerHud_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the GuiSpeedometerHud class.
        /// </description>
        /// <returns>The type info object for GuiSpeedometerHud</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Maximum Vehicle speed (in Torque units per second) to represent on the speedo (Vehicle speeds greater than this are clamped to maxSpeed).
        /// </description>
        /// </value>
        public float MaxSpeed {
            get => GenericMarshal.StringTo<float>(GetFieldValue("maxSpeed"));
            set => SetFieldValue("maxSpeed", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Angle (in radians) of the needle when the Vehicle speed is 0. An angle of 0 points right, 90 points up etc).
        /// </description>
        /// </value>
        public float MinAngle {
            get => GenericMarshal.StringTo<float>(GetFieldValue("minAngle"));
            set => SetFieldValue("minAngle", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Angle (in radians) of the needle when the Vehicle speed is >= maxSpeed. An angle of 0 points right, 90 points up etc).
        /// </description>
        /// </value>
        public float MaxAngle {
            get => GenericMarshal.StringTo<float>(GetFieldValue("maxAngle"));
            set => SetFieldValue("maxAngle", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Center of the needle, offset from the GuiSpeedometerHud control top left corner
        /// </description>
        /// </value>
        public Point2F Center {
            get => GenericMarshal.StringTo<Point2F>(GetFieldValue("center"));
            set => SetFieldValue("center", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Length of the needle from center to end
        /// </description>
        /// </value>
        public float Length {
            get => GenericMarshal.StringTo<float>(GetFieldValue("length"));
            set => SetFieldValue("length", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Width of the needle
        /// </description>
        /// </value>
        public float Width {
            get => GenericMarshal.StringTo<float>(GetFieldValue("width"));
            set => SetFieldValue("width", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Length of the needle from center to tail
        /// </description>
        /// </value>
        public float Tail {
            get => GenericMarshal.StringTo<float>(GetFieldValue("tail"));
            set => SetFieldValue("tail", GenericMarshal.ToString(value));
        }
    }
}