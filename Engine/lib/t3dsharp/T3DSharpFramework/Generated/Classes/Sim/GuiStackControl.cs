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
    /// <summary>A container that stacks its children horizontally or vertically.</summary>
    /// <description>
    /// This container maintains a horizontal or vertical stack of GUI controls. If one is added, deleted, or resized, then the stack is resized to fit. The order of the stack is determined by the internal order of the children (ie. the order of addition).<br>
    /// </description>
    /// <code>
    /// new GuiStackControl()
    /// {
    ///    stackingType = "Dynamic";
    ///    horizStacking = "Left to Right";
    ///    vertStacking = "Top to Bottom";
    ///    padding = "4";
    ///    dynamicSize = "1";
    ///    dynamicNonStackExtent = "0";
    ///    dynamicPos = "0";
    ///    changeChildSizeToFit = "1";
    ///    changeChildPosition = "1";
    ///    //Properties not specific to this control have been omitted from this example.
    /// };
    /// </code>
    public unsafe class GuiStackControl : GuiControl {
        public GuiStackControl(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public GuiStackControl(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public GuiStackControl(string pName) 
            : this(pName, false) {
        }
        
        public GuiStackControl(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public GuiStackControl(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public GuiStackControl(SimObject pObj) 
            : base(pObj) {
        }
        
        public GuiStackControl(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct UpdateStack__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _UpdateStack(IntPtr _this, UpdateStack__Args args);
            private static _UpdateStack _UpdateStackFunc;
            internal static _UpdateStack UpdateStack() {
                if (_UpdateStackFunc == null) {
                    _UpdateStackFunc =
                        (_UpdateStack)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiStackControl_updateStack"), typeof(_UpdateStack));
                }
                
                return _UpdateStackFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Freeze__Args
            {
                [MarshalAs(UnmanagedType.I1)]
                internal bool freeze;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Freeze(IntPtr _this, Freeze__Args args);
            private static _Freeze _FreezeFunc;
            internal static _Freeze Freeze() {
                if (_FreezeFunc == null) {
                    _FreezeFunc =
                        (_Freeze)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiStackControl_freeze"), typeof(_Freeze));
                }
                
                return _FreezeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsFrozen__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsFrozen(IntPtr _this, IsFrozen__Args args);
            private static _IsFrozen _IsFrozenFunc;
            internal static _IsFrozen IsFrozen() {
                if (_IsFrozenFunc == null) {
                    _IsFrozenFunc =
                        (_IsFrozen)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiStackControl_isFrozen"), typeof(_IsFrozen));
                }
                
                return _IsFrozenFunc;
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
                                "fnGuiStackControl_staticGetType"), typeof(_StaticGetType));
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
                                "fnGuiStackControl_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Restack the child controls.
        /// </description>
        public void UpdateStack() {
             InternalUnsafeMethods.UpdateStack__Args _args = new InternalUnsafeMethods.UpdateStack__Args() {
             };
             InternalUnsafeMethods.UpdateStack()(ObjectPtr, _args);
        }

        /// <description>
        /// Prevents control from restacking - useful when adding or removing child controls
        /// </description>
        /// <param name="freeze">True to freeze the control, false to unfreeze it</param>
        /// <code>
        /// %stackCtrl.freeze(true);
        /// // add controls to stack
        /// %stackCtrl.freeze(false);
        /// </code>
        public void Freeze(bool freeze) {
             InternalUnsafeMethods.Freeze__Args _args = new InternalUnsafeMethods.Freeze__Args() {
                freeze = freeze,
             };
             InternalUnsafeMethods.Freeze()(ObjectPtr, _args);
        }

        /// <description>
        /// Return whether or not this control is frozen
        /// </description>
        public bool IsFrozen() {
             InternalUnsafeMethods.IsFrozen__Args _args = new InternalUnsafeMethods.IsFrozen__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.IsFrozen()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Get the type info object for the GuiStackControl class.
        /// </description>
        /// <returns>The type info object for GuiStackControl</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Determines the method used to position the child controls.
        /// </description>
        /// </value>
        public GuiStackingType StackingType {
            get => GenericMarshal.StringTo<GuiStackingType>(GetFieldValue("stackingType"));
            set => SetFieldValue("stackingType", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Controls the type of horizontal stacking to use (<i>Left to Right</i> or <i>Right to Left</i>)
        /// </description>
        /// </value>
        public GuiHorizontalStackingType HorizStacking {
            get => GenericMarshal.StringTo<GuiHorizontalStackingType>(GetFieldValue("horizStacking"));
            set => SetFieldValue("horizStacking", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Controls the type of vertical stacking to use (<i>Top to Bottom</i> or <i>Bottom to Top</i>)
        /// </description>
        /// </value>
        public GuiVerticalStackingType VertStacking {
            get => GenericMarshal.StringTo<GuiVerticalStackingType>(GetFieldValue("vertStacking"));
            set => SetFieldValue("vertStacking", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Distance (in pixels) between stacked child controls.
        /// </description>
        /// </value>
        public int Padding {
            get => GenericMarshal.StringTo<int>(GetFieldValue("padding"));
            set => SetFieldValue("padding", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Determines whether to resize the stack control along the stack axis (change width for horizontal stacking, change height for vertical stacking).
        /// 
        /// If true, the stack width/height will be resized to the sum of the child control widths/heights. If false, the stack will not be resized.
        /// </description>
        /// </value>
        public bool DynamicSize {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("dynamicSize"));
            set => SetFieldValue("dynamicSize", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Determines whether to resize the stack control along the non-stack axis (change height for horizontal stacking, change width for vertical stacking). No effect if dynamicSize is false.
        /// 
        /// If true, the stack will be resized to the maximum of the child control widths/heights. If false, the stack will not be resized.
        /// </description>
        /// </value>
        public bool DynamicNonStackExtent {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("dynamicNonStackExtent"));
            set => SetFieldValue("dynamicNonStackExtent", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Determines whether to reposition the stack along the stack axis when it is auto-resized. No effect if dynamicSize is false.
        /// 
        /// If true, the stack will grow left for horizontal stacking, and grow up for vertical stacking.
        /// If false, the stack will grow right for horizontal stacking, and grow down for vertical stacking.
        /// </description>
        /// </value>
        public bool DynamicPos {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("dynamicPos"));
            set => SetFieldValue("dynamicPos", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Determines whether to resize child controls.
        /// 
        /// If true, horizontally stacked children keep their width, but have their height set to the stack control height. Vertically stacked children keep their height, but have their width set to the stack control width. If false, child controls are not resized.
        /// </description>
        /// </value>
        public bool ChangeChildSizeToFit {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("changeChildSizeToFit"));
            set => SetFieldValue("changeChildSizeToFit", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Determines whether to reposition child controls.
        /// 
        /// If true, horizontally stacked children are aligned along the top edge of the stack control. Vertically stacked children are aligned along the left edge of the stack control. If false, horizontally stacked children retain their Y position, and vertically stacked children retain their X position.
        /// </description>
        /// </value>
        public bool ChangeChildPosition {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("changeChildPosition"));
            set => SetFieldValue("changeChildPosition", GenericMarshal.ToString(value));
        }
    }
}