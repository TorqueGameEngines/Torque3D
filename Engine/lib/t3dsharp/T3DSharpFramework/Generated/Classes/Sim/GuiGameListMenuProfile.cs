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
    /// <summary>A GuiControlProfile with additional fields specific to GuiGameListMenuCtrl.</summary>
    /// <description>
    /// 
    /// </description>
    /// <code>
    /// new GuiGameListMenuProfile()
    /// {
    ///    hitAreaUpperLeft = "10 2";
    ///    hitAreaLowerRight = "190 18";
    ///    iconOffset = "10 2";
    ///    rowSize = "200 20";
    ///    columnSplit = "100";
    ///    rightPad = "4";
    ///    //Properties not specific to this control have been omitted from this example.
    /// };
    /// </code>
    public unsafe class GuiGameListMenuProfile : GuiControlProfile {
        public GuiGameListMenuProfile(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public GuiGameListMenuProfile(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public GuiGameListMenuProfile(string pName) 
            : this(pName, false) {
        }
        
        public GuiGameListMenuProfile(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public GuiGameListMenuProfile(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public GuiGameListMenuProfile(SimObject pObj) 
            : base(pObj) {
        }
        
        public GuiGameListMenuProfile(IntPtr pObj) 
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
                                "fnGuiGameListMenuProfile_staticGetType"), typeof(_StaticGetType));
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
                                "fnGuiGameListMenuProfile_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the GuiGameListMenuProfile class.
        /// </description>
        /// <returns>The type info object for GuiGameListMenuProfile</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Position of the upper left corner of the row hit area (relative to row's top left corner)
        /// </description>
        /// </value>
        public Point2I HitAreaUpperLeft {
            get => GenericMarshal.StringTo<Point2I>(GetFieldValue("hitAreaUpperLeft"));
            set => SetFieldValue("hitAreaUpperLeft", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Position of the lower right corner of the row hit area (relative to row's top left corner)
        /// </description>
        /// </value>
        public Point2I HitAreaLowerRight {
            get => GenericMarshal.StringTo<Point2I>(GetFieldValue("hitAreaLowerRight"));
            set => SetFieldValue("hitAreaLowerRight", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Offset from the row's top left corner at which to render the row icon
        /// </description>
        /// </value>
        public Point2I IconOffset {
            get => GenericMarshal.StringTo<Point2I>(GetFieldValue("iconOffset"));
            set => SetFieldValue("iconOffset", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The base size ("width height") of a row
        /// </description>
        /// </value>
        public Point2I RowSize {
            get => GenericMarshal.StringTo<Point2I>(GetFieldValue("rowSize"));
            set => SetFieldValue("rowSize", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Padding between the leftmost edge of the control, and the row's left arrow.
        /// </description>
        /// </value>
        public int ColumnSplit {
            get => GenericMarshal.StringTo<int>(GetFieldValue("columnSplit"));
            set => SetFieldValue("columnSplit", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Padding between the rightmost edge of the control and the row's right arrow.
        /// </description>
        /// </value>
        public int RightPad {
            get => GenericMarshal.StringTo<int>(GetFieldValue("rightPad"));
            set => SetFieldValue("rightPad", GenericMarshal.ToString(value));
        }
    }
}