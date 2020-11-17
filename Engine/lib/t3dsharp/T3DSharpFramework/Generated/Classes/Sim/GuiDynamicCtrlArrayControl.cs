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
    /// <summary>A container that arranges children into a grid.</summary>
    /// <description>
    /// This container maintains a 2D grid of GUI controls. If one is added, deleted, or resized, then the grid is updated. The insertion order into the grid is determined by the internal order of the children (ie. the order of addition).<br>Children are added to the grid by row or column until they fill the assocated GuiDynamicCtrlArrayControl extent (width or height). For example, a GuiDynamicCtrlArrayControl with 15 children, and <i>fillRowFirst</i> set to true may be arranged as follows:
    /// 
    /// <pre>
    /// 1  2  3  4  5  6
    /// 7  8  9  10 11 12
    /// 13 14 15
    /// </pre>
    /// If <i>dynamicSize</i> were set to true in this case, the GuiDynamicCtrlArrayControl height would be calculated to fit the 3 rows of child controls.
    /// </description>
    /// <code>
    /// new GuiDynamicCtrlArrayControl()
    /// {
    ///    colSize = "128";
    ///    rowSize = "18";
    ///    colSpacing = "2";
    ///    rowSpacing = "2";
    ///    frozen = "0";
    ///    autoCellSize = "1";
    ///    fillRowFirst = "1";
    ///    dynamicSize = "1";
    ///    padding = "0 0 0 0";
    ///    //Properties not specific to this control have been omitted from this example.
    /// };
    /// </code>
    public unsafe class GuiDynamicCtrlArrayControl : GuiControl {
        public GuiDynamicCtrlArrayControl(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public GuiDynamicCtrlArrayControl(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public GuiDynamicCtrlArrayControl(string pName) 
            : this(pName, false) {
        }
        
        public GuiDynamicCtrlArrayControl(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public GuiDynamicCtrlArrayControl(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public GuiDynamicCtrlArrayControl(SimObject pObj) 
            : base(pObj) {
        }
        
        public GuiDynamicCtrlArrayControl(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct Refresh__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Refresh(IntPtr _this, Refresh__Args args);
            private static _Refresh _RefreshFunc;
            internal static _Refresh Refresh() {
                if (_RefreshFunc == null) {
                    _RefreshFunc =
                        (_Refresh)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiDynamicCtrlArrayControl_refresh"), typeof(_Refresh));
                }
                
                return _RefreshFunc;
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
                                "fnGuiDynamicCtrlArrayControl_staticGetType"), typeof(_StaticGetType));
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
                                "fnGuiDynamicCtrlArrayControl_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Recalculates the position and size of this control and all its children.
        /// </description>
        public void Refresh() {
             InternalUnsafeMethods.Refresh__Args _args = new InternalUnsafeMethods.Refresh__Args() {
             };
             InternalUnsafeMethods.Refresh()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the GuiDynamicCtrlArrayControl class.
        /// </description>
        /// <returns>The type info object for GuiDynamicCtrlArrayControl</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Number of columns the child controls have been arranged into. This value is calculated automatically when children are added, removed or resized; writing it directly has no effect.
        /// </description>
        /// </value>
        public int ColCount {
            get => GenericMarshal.StringTo<int>(GetFieldValue("colCount"));
            set => SetFieldValue("colCount", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Width of each column. If <i>autoCellSize</i> is set, this will be calculated automatically from the widest child control
        /// </description>
        /// </value>
        public int ColSize {
            get => GenericMarshal.StringTo<int>(GetFieldValue("colSize"));
            set => SetFieldValue("colSize", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Number of rows the child controls have been arranged into. This value is calculated automatically when children are added, removed or resized; writing it directly has no effect.
        /// </description>
        /// </value>
        public int RowCount {
            get => GenericMarshal.StringTo<int>(GetFieldValue("rowCount"));
            set => SetFieldValue("rowCount", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Height of each row. If <i>autoCellSize</i> is set, this will be calculated automatically from the tallest child control
        /// </description>
        /// </value>
        public int RowSize {
            get => GenericMarshal.StringTo<int>(GetFieldValue("rowSize"));
            set => SetFieldValue("rowSize", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Spacing between rows
        /// </description>
        /// </value>
        public int RowSpacing {
            get => GenericMarshal.StringTo<int>(GetFieldValue("rowSpacing"));
            set => SetFieldValue("rowSpacing", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Spacing between columns
        /// </description>
        /// </value>
        public int ColSpacing {
            get => GenericMarshal.StringTo<int>(GetFieldValue("colSpacing"));
            set => SetFieldValue("colSpacing", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// When true, the array will not update when new children are added or in response to child resize events. This is useful to prevent unnecessary resizing when adding, removing or resizing a number of child controls.
        /// </description>
        /// </value>
        public bool Frozen {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("frozen"));
            set => SetFieldValue("frozen", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// When true, the cell size is set to the widest/tallest child control.
        /// </description>
        /// </value>
        public bool AutoCellSize {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("autoCellSize"));
            set => SetFieldValue("autoCellSize", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Controls whether rows or columns are filled first.
        /// 
        /// If true, controls are added to the grid left-to-right (to fill a row); then rows are added top-to-bottom as shown below:
        /// <pre>1 2 3 4
        /// 5 6 7 8</pre>
        /// If false, controls are added to the grid top-to-bottom (to fill a column); then columns are added left-to-right as shown below:
        /// <pre>1 3 5 7
        /// 2 4 6 8</pre>
        /// </description>
        /// </value>
        public bool FillRowFirst {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("fillRowFirst"));
            set => SetFieldValue("fillRowFirst", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// If true, the width or height of this control will be automatically calculated based on the number of child controls (width if <i>fillRowFirst</i> is false, height if <i>fillRowFirst</i> is true).
        /// </description>
        /// </value>
        public bool DynamicSize {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("dynamicSize"));
            set => SetFieldValue("dynamicSize", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Padding around the top, bottom, left, and right of this control. This reduces the area available for child controls.
        /// </description>
        /// </value>
        public RectSpacingI Padding {
            get => GenericMarshal.StringTo<RectSpacingI>(GetFieldValue("padding"));
            set => SetFieldValue("padding", GenericMarshal.ToString(value));
        }
    }
}