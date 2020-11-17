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
    /// <summary>A container that splits its area between two child controls.</summary>
    /// <description>
    /// A GuiSplitContainer can be used to dynamically subdivide an area between two child controls.  A splitter bar is placed between the two controls and allows to dynamically adjust the sizing ratio between the two sides.  Splitting can be either horizontal (subdividing top and bottom) or vertical (subdividing left and right) depending on #orientation.
    /// 
    /// By using #fixedPanel, one of the panels can be chosen to remain at a fixed size (#fixedSize).
    /// </description>
    /// <code>
    /// // Create a vertical splitter with a fixed-size left panel.
    /// %splitter = new GuiSplitContainer()
    /// {
    ///    orientation = "Vertical";
    ///    fixedPanel = "FirstPanel";
    ///    fixedSize = 100;
    /// 
    ///    new GuiScrollCtrl()
    ///    {
    ///       new GuiMLTextCtrl()
    ///       {
    ///          text = %longText;
    ///       };
    ///    };
    /// 
    ///    new GuiScrollCtrl()
    ///    {
    ///       new GuiMLTextCtrl()
    ///       {
    ///          text = %moreLongText;
    ///       };
    ///    };
    /// };
    /// </code>
    /// <remarks> The children placed inside GuiSplitContainers must be GuiContainers.
    /// 
    /// </remarks>
    public unsafe class GuiSplitContainer : GuiContainer {
        public GuiSplitContainer(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public GuiSplitContainer(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public GuiSplitContainer(string pName) 
            : this(pName, false) {
        }
        
        public GuiSplitContainer(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public GuiSplitContainer(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public GuiSplitContainer(SimObject pObj) 
            : base(pObj) {
        }
        
        public GuiSplitContainer(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct SetSplitPoint__Args
            {
                internal IntPtr splitPoint;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetSplitPoint(IntPtr _this, SetSplitPoint__Args args);
            private static _SetSplitPoint _SetSplitPointFunc;
            internal static _SetSplitPoint SetSplitPoint() {
                if (_SetSplitPointFunc == null) {
                    _SetSplitPointFunc =
                        (_SetSplitPoint)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiSplitContainer_setSplitPoint"), typeof(_SetSplitPoint));
                }
                
                return _SetSplitPointFunc;
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
                                "fnGuiSplitContainer_staticGetType"), typeof(_StaticGetType));
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
                                "fnGuiSplitContainer_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Set the position of the split handle.
        /// </description>
        public void SetSplitPoint(Point2I splitPoint) {
splitPoint.Alloc();             InternalUnsafeMethods.SetSplitPoint__Args _args = new InternalUnsafeMethods.SetSplitPoint__Args() {
                splitPoint = splitPoint.internalStructPtr,
             };
             InternalUnsafeMethods.SetSplitPoint()(ObjectPtr, _args);
splitPoint.Free();        }

        /// <description>
        /// Get the type info object for the GuiSplitContainer class.
        /// </description>
        /// <returns>The type info object for GuiSplitContainer</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Whether to split between top and bottom (horizontal) or between left and right (vertical).
        /// </description>
        /// </value>
        public GuiSplitOrientation Orientation {
            get => GenericMarshal.StringTo<GuiSplitOrientation>(GetFieldValue("orientation"));
            set => SetFieldValue("orientation", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Width of the splitter bar between the two sides.  Default is 2.
        /// </description>
        /// </value>
        public int SplitterSize {
            get => GenericMarshal.StringTo<int>(GetFieldValue("splitterSize"));
            set => SetFieldValue("splitterSize", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Point on control through which the splitter goes.
        /// 
        /// Changed relatively if size of control changes.
        /// </description>
        /// </value>
        public Point2I SplitPoint {
            get => GenericMarshal.StringTo<Point2I>(GetFieldValue("splitPoint"));
            set => SetFieldValue("splitPoint", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Which (if any) side of the splitter to keep at a fixed size.
        /// </description>
        /// </value>
        public GuiSplitFixedPanel FixedPanel {
            get => GenericMarshal.StringTo<GuiSplitFixedPanel>(GetFieldValue("fixedPanel"));
            set => SetFieldValue("fixedPanel", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Width of the fixed panel specified by #fixedPanel (if any).
        /// </description>
        /// </value>
        public int FixedSize {
            get => GenericMarshal.StringTo<int>(GetFieldValue("fixedSize"));
            set => SetFieldValue("fixedSize", GenericMarshal.ToString(value));
        }
    }
}