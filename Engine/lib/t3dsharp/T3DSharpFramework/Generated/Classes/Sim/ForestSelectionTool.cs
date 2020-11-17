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
    /// <summary>Specialized selection tool for picking individual trees in a forest.</summary>
    /// <description>
    /// Editor use only.
    /// </description>
    public unsafe class ForestSelectionTool : ForestTool {
        public ForestSelectionTool(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public ForestSelectionTool(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public ForestSelectionTool(string pName) 
            : this(pName, false) {
        }
        
        public ForestSelectionTool(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public ForestSelectionTool(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public ForestSelectionTool(SimObject pObj) 
            : base(pObj) {
        }
        
        public ForestSelectionTool(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct PasteSelection__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _PasteSelection(IntPtr _this, PasteSelection__Args args);
            private static _PasteSelection _PasteSelectionFunc;
            internal static _PasteSelection PasteSelection() {
                if (_PasteSelectionFunc == null) {
                    _PasteSelectionFunc =
                        (_PasteSelection)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnForestSelectionTool_pasteSelection"), typeof(_PasteSelection));
                }
                
                return _PasteSelectionFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct CopySelection__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _CopySelection(IntPtr _this, CopySelection__Args args);
            private static _CopySelection _CopySelectionFunc;
            internal static _CopySelection CopySelection() {
                if (_CopySelectionFunc == null) {
                    _CopySelectionFunc =
                        (_CopySelection)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnForestSelectionTool_copySelection"), typeof(_CopySelection));
                }
                
                return _CopySelectionFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct CutSelection__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _CutSelection(IntPtr _this, CutSelection__Args args);
            private static _CutSelection _CutSelectionFunc;
            internal static _CutSelection CutSelection() {
                if (_CutSelectionFunc == null) {
                    _CutSelectionFunc =
                        (_CutSelection)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnForestSelectionTool_cutSelection"), typeof(_CutSelection));
                }
                
                return _CutSelectionFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ClearSelection__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ClearSelection(IntPtr _this, ClearSelection__Args args);
            private static _ClearSelection _ClearSelectionFunc;
            internal static _ClearSelection ClearSelection() {
                if (_ClearSelectionFunc == null) {
                    _ClearSelectionFunc =
                        (_ClearSelection)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnForestSelectionTool_clearSelection"), typeof(_ClearSelection));
                }
                
                return _ClearSelectionFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct DeleteSelection__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _DeleteSelection(IntPtr _this, DeleteSelection__Args args);
            private static _DeleteSelection _DeleteSelectionFunc;
            internal static _DeleteSelection DeleteSelection() {
                if (_DeleteSelectionFunc == null) {
                    _DeleteSelectionFunc =
                        (_DeleteSelection)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnForestSelectionTool_deleteSelection"), typeof(_DeleteSelection));
                }
                
                return _DeleteSelectionFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetSelectionCount__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetSelectionCount(IntPtr _this, GetSelectionCount__Args args);
            private static _GetSelectionCount _GetSelectionCountFunc;
            internal static _GetSelectionCount GetSelectionCount() {
                if (_GetSelectionCountFunc == null) {
                    _GetSelectionCountFunc =
                        (_GetSelectionCount)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnForestSelectionTool_getSelectionCount"), typeof(_GetSelectionCount));
                }
                
                return _GetSelectionCountFunc;
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
                                "fnForestSelectionTool_staticGetType"), typeof(_StaticGetType));
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
                                "fnForestSelectionTool_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// 
        public void PasteSelection() {
             InternalUnsafeMethods.PasteSelection__Args _args = new InternalUnsafeMethods.PasteSelection__Args() {
             };
             InternalUnsafeMethods.PasteSelection()(ObjectPtr, _args);
        }

        /// 
        public void CopySelection() {
             InternalUnsafeMethods.CopySelection__Args _args = new InternalUnsafeMethods.CopySelection__Args() {
             };
             InternalUnsafeMethods.CopySelection()(ObjectPtr, _args);
        }

        /// 
        public void CutSelection() {
             InternalUnsafeMethods.CutSelection__Args _args = new InternalUnsafeMethods.CutSelection__Args() {
             };
             InternalUnsafeMethods.CutSelection()(ObjectPtr, _args);
        }

        /// 
        public void ClearSelection() {
             InternalUnsafeMethods.ClearSelection__Args _args = new InternalUnsafeMethods.ClearSelection__Args() {
             };
             InternalUnsafeMethods.ClearSelection()(ObjectPtr, _args);
        }

        /// 
        public void DeleteSelection() {
             InternalUnsafeMethods.DeleteSelection__Args _args = new InternalUnsafeMethods.DeleteSelection__Args() {
             };
             InternalUnsafeMethods.DeleteSelection()(ObjectPtr, _args);
        }

        /// 
        public int GetSelectionCount() {
             InternalUnsafeMethods.GetSelectionCount__Args _args = new InternalUnsafeMethods.GetSelectionCount__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetSelectionCount()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Get the type info object for the ForestSelectionTool class.
        /// </description>
        /// <returns>The type info object for ForestSelectionTool</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }
    }
}