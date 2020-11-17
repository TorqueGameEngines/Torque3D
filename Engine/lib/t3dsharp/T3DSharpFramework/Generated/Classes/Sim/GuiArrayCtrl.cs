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
    /// <summary>Abstract base class for controls that store and display multiple elements in a single view.</summary>
    /// <description>
    /// You cannot actually instantiate this class. Instead you can use its childre:
    /// 
    /// - GuiConsole
    /// - GuiTextListCtrl
    /// - GuiTreeViewCtrl
    /// - DbgFileView
    /// - CreatorTree
    /// This base class is primarily used by other internal classes or those dedicated to editors.
    /// </description>
    public unsafe class GuiArrayCtrl : GuiControl {
        public GuiArrayCtrl(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public GuiArrayCtrl(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public GuiArrayCtrl(string pName) 
            : this(pName, false) {
        }
        
        public GuiArrayCtrl(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public GuiArrayCtrl(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public GuiArrayCtrl(SimObject pObj) 
            : base(pObj) {
        }
        
        public GuiArrayCtrl(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct OnCellHighlighted__Args
            {
                internal IntPtr cell;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnCellHighlighted(IntPtr _this, OnCellHighlighted__Args args);
            private static _OnCellHighlighted _OnCellHighlightedFunc;
            internal static _OnCellHighlighted OnCellHighlighted() {
                if (_OnCellHighlightedFunc == null) {
                    _OnCellHighlightedFunc =
                        (_OnCellHighlighted)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbGuiArrayCtrl_onCellHighlighted"), typeof(_OnCellHighlighted));
                }
                
                return _OnCellHighlightedFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnCellSelected__Args
            {
                internal IntPtr cell;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnCellSelected(IntPtr _this, OnCellSelected__Args args);
            private static _OnCellSelected _OnCellSelectedFunc;
            internal static _OnCellSelected OnCellSelected() {
                if (_OnCellSelectedFunc == null) {
                    _OnCellSelectedFunc =
                        (_OnCellSelected)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbGuiArrayCtrl_onCellSelected"), typeof(_OnCellSelected));
                }
                
                return _OnCellSelectedFunc;
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
                                "fnGuiArrayCtrl_staticGetType"), typeof(_StaticGetType));
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
                                "fnGuiArrayCtrl_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Call when a cell in the array is highlighted (moused over).
        /// </description>
        /// <param name="">@cell Coordinates of the cell</param>
        public virtual void OnCellHighlighted(Point2I cell) {
cell.Alloc();             InternalUnsafeMethods.OnCellHighlighted__Args _args = new InternalUnsafeMethods.OnCellHighlighted__Args() {
                cell = cell.internalStructPtr,
             };
             InternalUnsafeMethods.OnCellHighlighted()(ObjectPtr, _args);
cell.Free();        }

        /// <description>
        /// Call when a cell in the array is selected (clicked).
        /// </description>
        /// <param name="">@cell Coordinates of the cell</param>
        public virtual void OnCellSelected(Point2I cell) {
cell.Alloc();             InternalUnsafeMethods.OnCellSelected__Args _args = new InternalUnsafeMethods.OnCellSelected__Args() {
                cell = cell.internalStructPtr,
             };
             InternalUnsafeMethods.OnCellSelected()(ObjectPtr, _args);
cell.Free();        }

        /// <description>
        /// Get the type info object for the GuiArrayCtrl class.
        /// </description>
        /// <returns>The type info object for GuiArrayCtrl</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }
    }
}