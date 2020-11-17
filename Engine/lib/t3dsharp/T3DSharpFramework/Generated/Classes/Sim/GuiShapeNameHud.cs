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
    /// <summary>Displays name and damage of ShapeBase objects in its bounds. Must be a child of a GuiTSCtrl and a server connection must be present.</summary>
    /// <description>
    /// This control displays the name and damage value of all named ShapeBase objects on the client. The name and damage of objects within the control's display area are overlayed above the object.
    /// 
    /// This GUI control must be a child of a TSControl, and a server connection and control object must be present. This is a stand-alone control and relies only on the standard base GuiControl.
    /// </description>
    /// <code>
    /// new GuiShapeNameHud(){
    /// 	fillColor = "0.0 1.0 0.0 1.0"; // Fills with a solid green color
    /// 	frameColor = "1.0 1.0 1.0 1.0"; // Solid white frame color
    /// 	textColor = "1.0 1.0 1.0 1.0"; // Solid white text Color
    /// 	showFill = "true";
    /// 	showFrame = "true";
    /// 	labelFillColor = "0.0 1.0 0.0 1.0"; // Fills with a solid green color
    /// 	labelFrameColor = "1.0 1.0 1.0 1.0"; // Solid white frame color
    /// 	showLabelFill = "true";
    /// 	showLabelFrame = "true";
    /// 	verticalOffset = "0.15";
    /// 	distanceFade = "15.0";
    /// };
    /// </code>
    public unsafe class GuiShapeNameHud : GuiControl {
        public GuiShapeNameHud(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public GuiShapeNameHud(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public GuiShapeNameHud(string pName) 
            : this(pName, false) {
        }
        
        public GuiShapeNameHud(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public GuiShapeNameHud(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public GuiShapeNameHud(SimObject pObj) 
            : base(pObj) {
        }
        
        public GuiShapeNameHud(IntPtr pObj) 
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
                                "fnGuiShapeNameHud_staticGetType"), typeof(_StaticGetType));
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
                                "fnGuiShapeNameHud_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the GuiShapeNameHud class.
        /// </description>
        /// <returns>The type info object for GuiShapeNameHud</returns>
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
        /// Color for the text on this control.
        /// </description>
        /// </value>
        public LinearColorF TextColor {
            get => GenericMarshal.StringTo<LinearColorF>(GetFieldValue("textColor"));
            set => SetFieldValue("textColor", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Color for the background of each shape name label.
        /// </description>
        /// </value>
        public LinearColorF LabelFillColor {
            get => GenericMarshal.StringTo<LinearColorF>(GetFieldValue("labelFillColor"));
            set => SetFieldValue("labelFillColor", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Color for the frames around each shape name label.
        /// </description>
        /// </value>
        public LinearColorF LabelFrameColor {
            get => GenericMarshal.StringTo<LinearColorF>(GetFieldValue("labelFrameColor"));
            set => SetFieldValue("labelFrameColor", GenericMarshal.ToString(value));
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
        /// If true, we draw a background for each shape name label.
        /// </description>
        /// </value>
        public bool ShowLabelFill {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("showLabelFill"));
            set => SetFieldValue("showLabelFill", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// If true, we draw a frame around each shape name label.
        /// </description>
        /// </value>
        public bool ShowLabelFrame {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("showLabelFrame"));
            set => SetFieldValue("showLabelFrame", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The padding (in pixels) between the label text and the frame.
        /// </description>
        /// </value>
        public Point2I LabelPadding {
            get => GenericMarshal.StringTo<Point2I>(GetFieldValue("labelPadding"));
            set => SetFieldValue("labelPadding", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Amount to vertically offset the control in relation to the ShapeBase object in focus.
        /// </description>
        /// </value>
        public float VerticalOffset {
            get => GenericMarshal.StringTo<float>(GetFieldValue("verticalOffset"));
            set => SetFieldValue("verticalOffset", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Visibility distance (how far the player must be from the ShapeBase object in focus) for this control to render.
        /// </description>
        /// </value>
        public float DistanceFade {
            get => GenericMarshal.StringTo<float>(GetFieldValue("distanceFade"));
            set => SetFieldValue("distanceFade", GenericMarshal.ToString(value));
        }
    }
}