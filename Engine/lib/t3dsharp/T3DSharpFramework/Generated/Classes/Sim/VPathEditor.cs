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
    /// 
    public unsafe class VPathEditor : EditTSCtrl {
        public VPathEditor(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public VPathEditor(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public VPathEditor(string pName) 
            : this(pName, false) {
        }
        
        public VPathEditor(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public VPathEditor(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public VPathEditor(SimObject pObj) 
            : base(pObj) {
        }
        
        public VPathEditor(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct SetNodeOrientationMode__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string orientationType;
                internal IntPtr lookAtPoint;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetNodeOrientationMode(IntPtr _this, SetNodeOrientationMode__Args args);
            private static _SetNodeOrientationMode _SetNodeOrientationModeFunc;
            internal static _SetNodeOrientationMode SetNodeOrientationMode() {
                if (_SetNodeOrientationModeFunc == null) {
                    _SetNodeOrientationModeFunc =
                        (_SetNodeOrientationMode)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVPathEditor_setNodeOrientationMode"), typeof(_SetNodeOrientationMode));
                }
                
                return _SetNodeOrientationModeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetNodeWeight__Args
            {
                internal float weight;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetNodeWeight(IntPtr _this, SetNodeWeight__Args args);
            private static _SetNodeWeight _SetNodeWeightFunc;
            internal static _SetNodeWeight SetNodeWeight() {
                if (_SetNodeWeightFunc == null) {
                    _SetNodeWeightFunc =
                        (_SetNodeWeight)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVPathEditor_setNodeWeight"), typeof(_SetNodeWeight));
                }
                
                return _SetNodeWeightFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetNodeRotation__Args
            {
                internal IntPtr aa;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetNodeRotation(IntPtr _this, SetNodeRotation__Args args);
            private static _SetNodeRotation _SetNodeRotationFunc;
            internal static _SetNodeRotation SetNodeRotation() {
                if (_SetNodeRotationFunc == null) {
                    _SetNodeRotationFunc =
                        (_SetNodeRotation)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVPathEditor_setNodeRotation"), typeof(_SetNodeRotation));
                }
                
                return _SetNodeRotationFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetNodePosition__Args
            {
                internal IntPtr position;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetNodePosition(IntPtr _this, SetNodePosition__Args args);
            private static _SetNodePosition _SetNodePositionFunc;
            internal static _SetNodePosition SetNodePosition() {
                if (_SetNodePositionFunc == null) {
                    _SetNodePositionFunc =
                        (_SetNodePosition)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVPathEditor_setNodePosition"), typeof(_SetNodePosition));
                }
                
                return _SetNodePositionFunc;
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
                                "fnVPathEditor_deleteSelection"), typeof(_DeleteSelection));
                }
                
                return _DeleteSelectionFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetSelectedNode__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetSelectedNode(IntPtr _this, GetSelectedNode__Args args);
            private static _GetSelectedNode _GetSelectedNodeFunc;
            internal static _GetSelectedNode GetSelectedNode() {
                if (_GetSelectedNodeFunc == null) {
                    _GetSelectedNodeFunc =
                        (_GetSelectedNode)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVPathEditor_getSelectedNode"), typeof(_GetSelectedNode));
                }
                
                return _GetSelectedNodeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetSelectedPath__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetSelectedPath(IntPtr _this, GetSelectedPath__Args args);
            private static _GetSelectedPath _GetSelectedPathFunc;
            internal static _GetSelectedPath GetSelectedPath() {
                if (_GetSelectedPathFunc == null) {
                    _GetSelectedPathFunc =
                        (_GetSelectedPath)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVPathEditor_getSelectedPath"), typeof(_GetSelectedPath));
                }
                
                return _GetSelectedPathFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsValidSelection__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsValidSelection(IntPtr _this, IsValidSelection__Args args);
            private static _IsValidSelection _IsValidSelectionFunc;
            internal static _IsValidSelection IsValidSelection() {
                if (_IsValidSelectionFunc == null) {
                    _IsValidSelectionFunc =
                        (_IsValidSelection)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVPathEditor_isValidSelection"), typeof(_IsValidSelection));
                }
                
                return _IsValidSelectionFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetSelection__Args
            {
                internal IntPtr sceneObject;
                internal int nodeIndex;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetSelection(IntPtr _this, SetSelection__Args args);
            private static _SetSelection _SetSelectionFunc;
            internal static _SetSelection SetSelection() {
                if (_SetSelectionFunc == null) {
                    _SetSelectionFunc =
                        (_SetSelection)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVPathEditor_setSelection"), typeof(_SetSelection));
                }
                
                return _SetSelectionFunc;
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
                                "fnVPathEditor_clearSelection"), typeof(_ClearSelection));
                }
                
                return _ClearSelectionFunc;
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
                                "fnVPathEditor_staticGetType"), typeof(_StaticGetType));
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
                                "fnVPathEditor_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// ( string pOrientationType, [vector pPoint] )
        /// </description>
        public void SetNodeOrientationMode(string orientationType = "", Point3F lookAtPoint = null) {
lookAtPoint = lookAtPoint ?? new Point3F("1 1 1");
lookAtPoint.Alloc();             InternalUnsafeMethods.SetNodeOrientationMode__Args _args = new InternalUnsafeMethods.SetNodeOrientationMode__Args() {
                orientationType = orientationType,
                lookAtPoint = lookAtPoint.internalStructPtr,
             };
             InternalUnsafeMethods.SetNodeOrientationMode()(ObjectPtr, _args);
lookAtPoint.Free();        }

        /// <description>
        /// ( pWeight )
        /// </description>
        public void SetNodeWeight(float weight = 1f) {
             InternalUnsafeMethods.SetNodeWeight__Args _args = new InternalUnsafeMethods.SetNodeWeight__Args() {
                weight = weight,
             };
             InternalUnsafeMethods.SetNodeWeight()(ObjectPtr, _args);
        }

        /// <description>
        /// ( pRotation )
        /// </description>
        public void SetNodeRotation(AngAxisF aa = null) {
aa = aa ?? new AngAxisF("0 0 0 0");
aa.Alloc();             InternalUnsafeMethods.SetNodeRotation__Args _args = new InternalUnsafeMethods.SetNodeRotation__Args() {
                aa = aa.internalStructPtr,
             };
             InternalUnsafeMethods.SetNodeRotation()(ObjectPtr, _args);
aa.Free();        }

        /// <description>
        /// ( pPosition )
        /// </description>
        public void SetNodePosition(Point3F position = null) {
position = position ?? new Point3F("0 0 0");
position.Alloc();             InternalUnsafeMethods.SetNodePosition__Args _args = new InternalUnsafeMethods.SetNodePosition__Args() {
                position = position.internalStructPtr,
             };
             InternalUnsafeMethods.SetNodePosition()(ObjectPtr, _args);
position.Free();        }

        /// <description>
        /// ( void )
        /// </description>
        public void DeleteSelection() {
             InternalUnsafeMethods.DeleteSelection__Args _args = new InternalUnsafeMethods.DeleteSelection__Args() {
             };
             InternalUnsafeMethods.DeleteSelection()(ObjectPtr, _args);
        }

        /// <description>
        /// ( void )
        /// </description>
        public int GetSelectedNode() {
             InternalUnsafeMethods.GetSelectedNode__Args _args = new InternalUnsafeMethods.GetSelectedNode__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetSelectedNode()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// ( void )
        /// </description>
        public int GetSelectedPath() {
             InternalUnsafeMethods.GetSelectedPath__Args _args = new InternalUnsafeMethods.GetSelectedPath__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetSelectedPath()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// ( void )
        /// </description>
        public bool IsValidSelection() {
             InternalUnsafeMethods.IsValidSelection__Args _args = new InternalUnsafeMethods.IsValidSelection__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.IsValidSelection()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// ( pObject, [pNodeIndex] )
        /// </description>
        public void SetSelection(SceneObject sceneObject = null, int nodeIndex = -1) {
             InternalUnsafeMethods.SetSelection__Args _args = new InternalUnsafeMethods.SetSelection__Args() {
                sceneObject = sceneObject.ObjectPtr,
                nodeIndex = nodeIndex,
             };
             InternalUnsafeMethods.SetSelection()(ObjectPtr, _args);
        }

        /// <description>
        /// ( void )
        /// </description>
        public void ClearSelection() {
             InternalUnsafeMethods.ClearSelection__Args _args = new InternalUnsafeMethods.ClearSelection__Args() {
             };
             InternalUnsafeMethods.ClearSelection()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the VPathEditor class.
        /// </description>
        /// <returns>The type info object for VPathEditor</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// 
        /// </value>
        public bool IsDirty {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("isDirty"));
            set => SetFieldValue("isDirty", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public VPathEditorMode EditMode {
            get => GenericMarshal.StringTo<VPathEditorMode>(GetFieldValue("EditMode"));
            set => SetFieldValue("EditMode", GenericMarshal.ToString(value));
        }
    }
}