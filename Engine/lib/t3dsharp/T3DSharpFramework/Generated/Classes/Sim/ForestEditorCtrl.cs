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
    /// <summary>The actual Forest Editor control</summary>
    /// <description>
    /// Editor use only, should not be modified.
    /// </description>
    public unsafe class ForestEditorCtrl : EditTSCtrl {
        public ForestEditorCtrl(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public ForestEditorCtrl(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public ForestEditorCtrl(string pName) 
            : this(pName, false) {
        }
        
        public ForestEditorCtrl(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public ForestEditorCtrl(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public ForestEditorCtrl(SimObject pObj) 
            : base(pObj) {
        }
        
        public ForestEditorCtrl(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct SetActiveForest__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string obj;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetActiveForest(IntPtr _this, SetActiveForest__Args args);
            private static _SetActiveForest _SetActiveForestFunc;
            internal static _SetActiveForest SetActiveForest() {
                if (_SetActiveForestFunc == null) {
                    _SetActiveForestFunc =
                        (_SetActiveForest)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnForestEditorCtrl_setActiveForest"), typeof(_SetActiveForest));
                }
                
                return _SetActiveForestFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsDirty__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsDirty(IntPtr _this, IsDirty__Args args);
            private static _IsDirty _IsDirtyFunc;
            internal static _IsDirty IsDirty() {
                if (_IsDirtyFunc == null) {
                    _IsDirtyFunc =
                        (_IsDirty)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnForestEditorCtrl_isDirty"), typeof(_IsDirty));
                }
                
                return _IsDirtyFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct DeleteMeshSafe__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string obj;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _DeleteMeshSafe(IntPtr _this, DeleteMeshSafe__Args args);
            private static _DeleteMeshSafe _DeleteMeshSafeFunc;
            internal static _DeleteMeshSafe DeleteMeshSafe() {
                if (_DeleteMeshSafeFunc == null) {
                    _DeleteMeshSafeFunc =
                        (_DeleteMeshSafe)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnForestEditorCtrl_deleteMeshSafe"), typeof(_DeleteMeshSafe));
                }
                
                return _DeleteMeshSafeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetActiveTool__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetActiveTool(IntPtr _this, GetActiveTool__Args args);
            private static _GetActiveTool _GetActiveToolFunc;
            internal static _GetActiveTool GetActiveTool() {
                if (_GetActiveToolFunc == null) {
                    _GetActiveToolFunc =
                        (_GetActiveTool)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnForestEditorCtrl_getActiveTool"), typeof(_GetActiveTool));
                }
                
                return _GetActiveToolFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetActiveTool__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string toolName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetActiveTool(IntPtr _this, SetActiveTool__Args args);
            private static _SetActiveTool _SetActiveToolFunc;
            internal static _SetActiveTool SetActiveTool() {
                if (_SetActiveToolFunc == null) {
                    _SetActiveToolFunc =
                        (_SetActiveTool)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnForestEditorCtrl_setActiveTool"), typeof(_SetActiveTool));
                }
                
                return _SetActiveToolFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct UpdateActiveForest__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _UpdateActiveForest(IntPtr _this, UpdateActiveForest__Args args);
            private static _UpdateActiveForest _UpdateActiveForestFunc;
            internal static _UpdateActiveForest UpdateActiveForest() {
                if (_UpdateActiveForestFunc == null) {
                    _UpdateActiveForestFunc =
                        (_UpdateActiveForest)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnForestEditorCtrl_updateActiveForest"), typeof(_UpdateActiveForest));
                }
                
                return _UpdateActiveForestFunc;
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
                                "fnForestEditorCtrl_staticGetType"), typeof(_StaticGetType));
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
                                "fnForestEditorCtrl_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// ( Forest obj )
        /// </description>
        public void SetActiveForest(string obj) {
             InternalUnsafeMethods.SetActiveForest__Args _args = new InternalUnsafeMethods.SetActiveForest__Args() {
                obj = obj,
             };
             InternalUnsafeMethods.SetActiveForest()(ObjectPtr, _args);
        }

        /// 
        public bool IsDirty() {
             InternalUnsafeMethods.IsDirty__Args _args = new InternalUnsafeMethods.IsDirty__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.IsDirty()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// ( ForestItemData obj )
        /// </description>
        public void DeleteMeshSafe(string obj) {
             InternalUnsafeMethods.DeleteMeshSafe__Args _args = new InternalUnsafeMethods.DeleteMeshSafe__Args() {
                obj = obj,
             };
             InternalUnsafeMethods.DeleteMeshSafe()(ObjectPtr, _args);
        }

        /// <description>
        /// ()
        /// </description>
        public int GetActiveTool() {
             InternalUnsafeMethods.GetActiveTool__Args _args = new InternalUnsafeMethods.GetActiveTool__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetActiveTool()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// ( ForestTool tool )
        /// </description>
        public void SetActiveTool(string toolName) {
             InternalUnsafeMethods.SetActiveTool__Args _args = new InternalUnsafeMethods.SetActiveTool__Args() {
                toolName = toolName,
             };
             InternalUnsafeMethods.SetActiveTool()(ObjectPtr, _args);
        }

        /// <description>
        /// ()
        /// </description>
        public void UpdateActiveForest() {
             InternalUnsafeMethods.UpdateActiveForest__Args _args = new InternalUnsafeMethods.UpdateActiveForest__Args() {
             };
             InternalUnsafeMethods.UpdateActiveForest()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the ForestEditorCtrl class.
        /// </description>
        /// <returns>The type info object for ForestEditorCtrl</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }
    }
}