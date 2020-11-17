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
    /// <summary>GUI tool that makes up the River Editor</summary>
    /// <description>
    /// Editor use only.
    /// </description>
    public unsafe class GuiRiverEditorCtrl : EditTSCtrl {
        public GuiRiverEditorCtrl(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public GuiRiverEditorCtrl(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public GuiRiverEditorCtrl(string pName) 
            : this(pName, false) {
        }
        
        public GuiRiverEditorCtrl(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public GuiRiverEditorCtrl(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public GuiRiverEditorCtrl(SimObject pObj) 
            : base(pObj) {
        }
        
        public GuiRiverEditorCtrl(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct Regenerate__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Regenerate(IntPtr _this, Regenerate__Args args);
            private static _Regenerate _RegenerateFunc;
            internal static _Regenerate Regenerate() {
                if (_RegenerateFunc == null) {
                    _RegenerateFunc =
                        (_Regenerate)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiRiverEditorCtrl_regenerate"), typeof(_Regenerate));
                }
                
                return _RegenerateFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetSelectedRiver__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetSelectedRiver(IntPtr _this, GetSelectedRiver__Args args);
            private static _GetSelectedRiver _GetSelectedRiverFunc;
            internal static _GetSelectedRiver GetSelectedRiver() {
                if (_GetSelectedRiverFunc == null) {
                    _GetSelectedRiverFunc =
                        (_GetSelectedRiver)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiRiverEditorCtrl_getSelectedRiver"), typeof(_GetSelectedRiver));
                }
                
                return _GetSelectedRiverFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetSelectedRiver__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string objName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetSelectedRiver(IntPtr _this, SetSelectedRiver__Args args);
            private static _SetSelectedRiver _SetSelectedRiverFunc;
            internal static _SetSelectedRiver SetSelectedRiver() {
                if (_SetSelectedRiverFunc == null) {
                    _SetSelectedRiverFunc =
                        (_SetSelectedRiver)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiRiverEditorCtrl_setSelectedRiver"), typeof(_SetSelectedRiver));
                }
                
                return _SetSelectedRiverFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetNodeNormal__Args
            {
                internal IntPtr normal;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetNodeNormal(IntPtr _this, SetNodeNormal__Args args);
            private static _SetNodeNormal _SetNodeNormalFunc;
            internal static _SetNodeNormal SetNodeNormal() {
                if (_SetNodeNormalFunc == null) {
                    _SetNodeNormalFunc =
                        (_SetNodeNormal)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiRiverEditorCtrl_setNodeNormal"), typeof(_SetNodeNormal));
                }
                
                return _SetNodeNormalFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetNodeNormal__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate Point3F.InternalStruct _GetNodeNormal(IntPtr _this, GetNodeNormal__Args args);
            private static _GetNodeNormal _GetNodeNormalFunc;
            internal static _GetNodeNormal GetNodeNormal() {
                if (_GetNodeNormalFunc == null) {
                    _GetNodeNormalFunc =
                        (_GetNodeNormal)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiRiverEditorCtrl_getNodeNormal"), typeof(_GetNodeNormal));
                }
                
                return _GetNodeNormalFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetNodePosition__Args
            {
                internal IntPtr pos;
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
                                "fnGuiRiverEditorCtrl_setNodePosition"), typeof(_SetNodePosition));
                }
                
                return _SetNodePositionFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetNodePosition__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate Point3F.InternalStruct _GetNodePosition(IntPtr _this, GetNodePosition__Args args);
            private static _GetNodePosition _GetNodePositionFunc;
            internal static _GetNodePosition GetNodePosition() {
                if (_GetNodePositionFunc == null) {
                    _GetNodePositionFunc =
                        (_GetNodePosition)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiRiverEditorCtrl_getNodePosition"), typeof(_GetNodePosition));
                }
                
                return _GetNodePositionFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetNodeDepth__Args
            {
                internal float depth;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetNodeDepth(IntPtr _this, SetNodeDepth__Args args);
            private static _SetNodeDepth _SetNodeDepthFunc;
            internal static _SetNodeDepth SetNodeDepth() {
                if (_SetNodeDepthFunc == null) {
                    _SetNodeDepthFunc =
                        (_SetNodeDepth)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiRiverEditorCtrl_setNodeDepth"), typeof(_SetNodeDepth));
                }
                
                return _SetNodeDepthFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetNodeDepth__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _GetNodeDepth(IntPtr _this, GetNodeDepth__Args args);
            private static _GetNodeDepth _GetNodeDepthFunc;
            internal static _GetNodeDepth GetNodeDepth() {
                if (_GetNodeDepthFunc == null) {
                    _GetNodeDepthFunc =
                        (_GetNodeDepth)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiRiverEditorCtrl_getNodeDepth"), typeof(_GetNodeDepth));
                }
                
                return _GetNodeDepthFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetNodeWidth__Args
            {
                internal float width;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetNodeWidth(IntPtr _this, SetNodeWidth__Args args);
            private static _SetNodeWidth _SetNodeWidthFunc;
            internal static _SetNodeWidth SetNodeWidth() {
                if (_SetNodeWidthFunc == null) {
                    _SetNodeWidthFunc =
                        (_SetNodeWidth)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiRiverEditorCtrl_setNodeWidth"), typeof(_SetNodeWidth));
                }
                
                return _SetNodeWidthFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetNodeWidth__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _GetNodeWidth(IntPtr _this, GetNodeWidth__Args args);
            private static _GetNodeWidth _GetNodeWidthFunc;
            internal static _GetNodeWidth GetNodeWidth() {
                if (_GetNodeWidthFunc == null) {
                    _GetNodeWidthFunc =
                        (_GetNodeWidth)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiRiverEditorCtrl_getNodeWidth"), typeof(_GetNodeWidth));
                }
                
                return _GetNodeWidthFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetMode__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string mode;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetMode(IntPtr _this, SetMode__Args args);
            private static _SetMode _SetModeFunc;
            internal static _SetMode SetMode() {
                if (_SetModeFunc == null) {
                    _SetModeFunc =
                        (_SetMode)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiRiverEditorCtrl_setMode"), typeof(_SetMode));
                }
                
                return _SetModeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetMode__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetMode(IntPtr _this, GetMode__Args args);
            private static _GetMode _GetModeFunc;
            internal static _GetMode GetMode() {
                if (_GetModeFunc == null) {
                    _GetModeFunc =
                        (_GetMode)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiRiverEditorCtrl_getMode"), typeof(_GetMode));
                }
                
                return _GetModeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct DeleteNode__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _DeleteNode(IntPtr _this, DeleteNode__Args args);
            private static _DeleteNode _DeleteNodeFunc;
            internal static _DeleteNode DeleteNode() {
                if (_DeleteNodeFunc == null) {
                    _DeleteNodeFunc =
                        (_DeleteNode)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiRiverEditorCtrl_deleteNode"), typeof(_DeleteNode));
                }
                
                return _DeleteNodeFunc;
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
                                "fnGuiRiverEditorCtrl_staticGetType"), typeof(_StaticGetType));
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
                                "fnGuiRiverEditorCtrl_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// 
        public void Regenerate() {
             InternalUnsafeMethods.Regenerate__Args _args = new InternalUnsafeMethods.Regenerate__Args() {
             };
             InternalUnsafeMethods.Regenerate()(ObjectPtr, _args);
        }

        /// 
        public int GetSelectedRiver() {
             InternalUnsafeMethods.GetSelectedRiver__Args _args = new InternalUnsafeMethods.GetSelectedRiver__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetSelectedRiver()(ObjectPtr, _args);
             return _engineResult;
        }

        /// 
        public void SetSelectedRiver(string objName = "") {
             InternalUnsafeMethods.SetSelectedRiver__Args _args = new InternalUnsafeMethods.SetSelectedRiver__Args() {
                objName = objName,
             };
             InternalUnsafeMethods.SetSelectedRiver()(ObjectPtr, _args);
        }

        /// 
        public void SetNodeNormal(Point3F normal) {
normal.Alloc();             InternalUnsafeMethods.SetNodeNormal__Args _args = new InternalUnsafeMethods.SetNodeNormal__Args() {
                normal = normal.internalStructPtr,
             };
             InternalUnsafeMethods.SetNodeNormal()(ObjectPtr, _args);
normal.Free();        }

        /// 
        public Point3F GetNodeNormal() {
             InternalUnsafeMethods.GetNodeNormal__Args _args = new InternalUnsafeMethods.GetNodeNormal__Args() {
             };
             Point3F.InternalStruct _engineResult = InternalUnsafeMethods.GetNodeNormal()(ObjectPtr, _args);
             return new Point3F(_engineResult);
        }

        /// 
        public void SetNodePosition(Point3F pos) {
pos.Alloc();             InternalUnsafeMethods.SetNodePosition__Args _args = new InternalUnsafeMethods.SetNodePosition__Args() {
                pos = pos.internalStructPtr,
             };
             InternalUnsafeMethods.SetNodePosition()(ObjectPtr, _args);
pos.Free();        }

        /// 
        public Point3F GetNodePosition() {
             InternalUnsafeMethods.GetNodePosition__Args _args = new InternalUnsafeMethods.GetNodePosition__Args() {
             };
             Point3F.InternalStruct _engineResult = InternalUnsafeMethods.GetNodePosition()(ObjectPtr, _args);
             return new Point3F(_engineResult);
        }

        /// 
        public void SetNodeDepth(float depth) {
             InternalUnsafeMethods.SetNodeDepth__Args _args = new InternalUnsafeMethods.SetNodeDepth__Args() {
                depth = depth,
             };
             InternalUnsafeMethods.SetNodeDepth()(ObjectPtr, _args);
        }

        /// 
        public float GetNodeDepth() {
             InternalUnsafeMethods.GetNodeDepth__Args _args = new InternalUnsafeMethods.GetNodeDepth__Args() {
             };
             float _engineResult = InternalUnsafeMethods.GetNodeDepth()(ObjectPtr, _args);
             return _engineResult;
        }

        /// 
        public void SetNodeWidth(float width) {
             InternalUnsafeMethods.SetNodeWidth__Args _args = new InternalUnsafeMethods.SetNodeWidth__Args() {
                width = width,
             };
             InternalUnsafeMethods.SetNodeWidth()(ObjectPtr, _args);
        }

        /// 
        public float GetNodeWidth() {
             InternalUnsafeMethods.GetNodeWidth__Args _args = new InternalUnsafeMethods.GetNodeWidth__Args() {
             };
             float _engineResult = InternalUnsafeMethods.GetNodeWidth()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// setMode( String mode )
        /// </description>
        public void SetMode(string mode) {
             InternalUnsafeMethods.SetMode__Args _args = new InternalUnsafeMethods.SetMode__Args() {
                mode = mode,
             };
             InternalUnsafeMethods.SetMode()(ObjectPtr, _args);
        }

        /// 
        public string GetMode() {
             InternalUnsafeMethods.GetMode__Args _args = new InternalUnsafeMethods.GetMode__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetMode()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// deleteNode()
        /// </description>
        public void DeleteNode() {
             InternalUnsafeMethods.DeleteNode__Args _args = new InternalUnsafeMethods.DeleteNode__Args() {
             };
             InternalUnsafeMethods.DeleteNode()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the GuiRiverEditorCtrl class.
        /// </description>
        /// <returns>The type info object for GuiRiverEditorCtrl</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// 
        /// </value>
        public float DefaultWidth {
            get => GenericMarshal.StringTo<float>(GetFieldValue("DefaultWidth"));
            set => SetFieldValue("DefaultWidth", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public float DefaultDepth {
            get => GenericMarshal.StringTo<float>(GetFieldValue("DefaultDepth"));
            set => SetFieldValue("DefaultDepth", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public Point3F DefaultNormal {
            get => GenericMarshal.StringTo<Point3F>(GetFieldValue("DefaultNormal"));
            set => SetFieldValue("DefaultNormal", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public ColorI HoverSplineColor {
            get => GenericMarshal.StringTo<ColorI>(GetFieldValue("HoverSplineColor"));
            set => SetFieldValue("HoverSplineColor", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public ColorI SelectedSplineColor {
            get => GenericMarshal.StringTo<ColorI>(GetFieldValue("SelectedSplineColor"));
            set => SetFieldValue("SelectedSplineColor", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public ColorI HoverNodeColor {
            get => GenericMarshal.StringTo<ColorI>(GetFieldValue("HoverNodeColor"));
            set => SetFieldValue("HoverNodeColor", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public bool IsDirty {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("isDirty"));
            set => SetFieldValue("isDirty", GenericMarshal.ToString(value));
        }
    }
}