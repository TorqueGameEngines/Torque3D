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
    /// <summary>3D view control used specifically by Torque 3D's editors.</summary>
    /// <description>
    /// For Torque 3D editors only, not for actual game development
    /// </description>
    public unsafe class EditTSCtrl : GuiTSCtrl {
        public EditTSCtrl(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public EditTSCtrl(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public EditTSCtrl(string pName) 
            : this(pName, false) {
        }
        
        public EditTSCtrl(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public EditTSCtrl(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public EditTSCtrl(SimObject pObj) 
            : base(pObj) {
        }
        
        public EditTSCtrl(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct IsMiddleMouseDown__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsMiddleMouseDown(IntPtr _this, IsMiddleMouseDown__Args args);
            private static _IsMiddleMouseDown _IsMiddleMouseDownFunc;
            internal static _IsMiddleMouseDown IsMiddleMouseDown() {
                if (_IsMiddleMouseDownFunc == null) {
                    _IsMiddleMouseDownFunc =
                        (_IsMiddleMouseDown)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnEditTSCtrl_isMiddleMouseDown"), typeof(_IsMiddleMouseDown));
                }
                
                return _IsMiddleMouseDownFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetGizmo__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetGizmo(IntPtr _this, GetGizmo__Args args);
            private static _GetGizmo _GetGizmoFunc;
            internal static _GetGizmo GetGizmo() {
                if (_GetGizmoFunc == null) {
                    _GetGizmoFunc =
                        (_GetGizmo)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnEditTSCtrl_getGizmo"), typeof(_GetGizmo));
                }
                
                return _GetGizmoFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct RenderLine__Args
            {
                internal IntPtr start;
                internal IntPtr end;
                internal float lineWidth;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _RenderLine(IntPtr _this, RenderLine__Args args);
            private static _RenderLine _RenderLineFunc;
            internal static _RenderLine RenderLine() {
                if (_RenderLineFunc == null) {
                    _RenderLineFunc =
                        (_RenderLine)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnEditTSCtrl_renderLine"), typeof(_RenderLine));
                }
                
                return _RenderLineFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct RenderTriangle__Args
            {
                internal IntPtr a;
                internal IntPtr b;
                internal IntPtr c;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _RenderTriangle(IntPtr _this, RenderTriangle__Args args);
            private static _RenderTriangle _RenderTriangleFunc;
            internal static _RenderTriangle RenderTriangle() {
                if (_RenderTriangleFunc == null) {
                    _RenderTriangleFunc =
                        (_RenderTriangle)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnEditTSCtrl_renderTriangle"), typeof(_RenderTriangle));
                }
                
                return _RenderTriangleFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct RenderCircle__Args
            {
                internal IntPtr pos;
                internal IntPtr normal;
                internal float radius;
                internal int segments;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _RenderCircle(IntPtr _this, RenderCircle__Args args);
            private static _RenderCircle _RenderCircleFunc;
            internal static _RenderCircle RenderCircle() {
                if (_RenderCircleFunc == null) {
                    _RenderCircleFunc =
                        (_RenderCircle)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnEditTSCtrl_renderCircle"), typeof(_RenderCircle));
                }
                
                return _RenderCircleFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct RenderSphere__Args
            {
                internal IntPtr pos;
                internal float radius;
                internal int sphereLevel;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _RenderSphere(IntPtr _this, RenderSphere__Args args);
            private static _RenderSphere _RenderSphereFunc;
            internal static _RenderSphere RenderSphere() {
                if (_RenderSphereFunc == null) {
                    _RenderSphereFunc =
                        (_RenderSphere)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnEditTSCtrl_renderSphere"), typeof(_RenderSphere));
                }
                
                return _RenderSphereFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct RenderBox__Args
            {
                internal IntPtr pos;
                internal IntPtr size;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _RenderBox(IntPtr _this, RenderBox__Args args);
            private static _RenderBox _RenderBoxFunc;
            internal static _RenderBox RenderBox() {
                if (_RenderBoxFunc == null) {
                    _RenderBoxFunc =
                        (_RenderBox)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnEditTSCtrl_renderBox"), typeof(_RenderBox));
                }
                
                return _RenderBoxFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetOrthoFOV__Args
            {
                internal float fov;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetOrthoFOV(IntPtr _this, SetOrthoFOV__Args args);
            private static _SetOrthoFOV _SetOrthoFOVFunc;
            internal static _SetOrthoFOV SetOrthoFOV() {
                if (_SetOrthoFOVFunc == null) {
                    _SetOrthoFOVFunc =
                        (_SetOrthoFOV)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnEditTSCtrl_setOrthoFOV"), typeof(_SetOrthoFOV));
                }
                
                return _SetOrthoFOVFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetOrthoFOV__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _GetOrthoFOV(IntPtr _this, GetOrthoFOV__Args args);
            private static _GetOrthoFOV _GetOrthoFOVFunc;
            internal static _GetOrthoFOV GetOrthoFOV() {
                if (_GetOrthoFOVFunc == null) {
                    _GetOrthoFOVFunc =
                        (_GetOrthoFOV)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnEditTSCtrl_getOrthoFOV"), typeof(_GetOrthoFOV));
                }
                
                return _GetOrthoFOVFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetDisplayType__Args
            {
                internal int displayType;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetDisplayType(IntPtr _this, SetDisplayType__Args args);
            private static _SetDisplayType _SetDisplayTypeFunc;
            internal static _SetDisplayType SetDisplayType() {
                if (_SetDisplayTypeFunc == null) {
                    _SetDisplayTypeFunc =
                        (_SetDisplayType)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnEditTSCtrl_setDisplayType"), typeof(_SetDisplayType));
                }
                
                return _SetDisplayTypeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetDisplayType__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetDisplayType(IntPtr _this, GetDisplayType__Args args);
            private static _GetDisplayType _GetDisplayTypeFunc;
            internal static _GetDisplayType GetDisplayType() {
                if (_GetDisplayTypeFunc == null) {
                    _GetDisplayTypeFunc =
                        (_GetDisplayType)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnEditTSCtrl_getDisplayType"), typeof(_GetDisplayType));
                }
                
                return _GetDisplayTypeFunc;
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
                                "fnEditTSCtrl_staticGetType"), typeof(_StaticGetType));
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
                                "fnEditTSCtrl_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// 
        public bool IsMiddleMouseDown() {
             InternalUnsafeMethods.IsMiddleMouseDown__Args _args = new InternalUnsafeMethods.IsMiddleMouseDown__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.IsMiddleMouseDown()(ObjectPtr, _args);
             return _engineResult;
        }

        /// 
        public int GetGizmo() {
             InternalUnsafeMethods.GetGizmo__Args _args = new InternalUnsafeMethods.GetGizmo__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetGizmo()(ObjectPtr, _args);
             return _engineResult;
        }

        /// 
        public void RenderLine(Point3F start, Point3F end, float lineWidth = 0f) {
start.Alloc();end.Alloc();             InternalUnsafeMethods.RenderLine__Args _args = new InternalUnsafeMethods.RenderLine__Args() {
                start = start.internalStructPtr,
                end = end.internalStructPtr,
                lineWidth = lineWidth,
             };
             InternalUnsafeMethods.RenderLine()(ObjectPtr, _args);
start.Free();end.Free();        }

        /// 
        public void RenderTriangle(Point3F a, Point3F b, Point3F c) {
a.Alloc();b.Alloc();c.Alloc();             InternalUnsafeMethods.RenderTriangle__Args _args = new InternalUnsafeMethods.RenderTriangle__Args() {
                a = a.internalStructPtr,
                b = b.internalStructPtr,
                c = c.internalStructPtr,
             };
             InternalUnsafeMethods.RenderTriangle()(ObjectPtr, _args);
a.Free();b.Free();c.Free();        }

        /// 
        public void RenderCircle(Point3F pos, Point3F normal, float radius, int segments = 0) {
pos.Alloc();normal.Alloc();             InternalUnsafeMethods.RenderCircle__Args _args = new InternalUnsafeMethods.RenderCircle__Args() {
                pos = pos.internalStructPtr,
                normal = normal.internalStructPtr,
                radius = radius,
                segments = segments,
             };
             InternalUnsafeMethods.RenderCircle()(ObjectPtr, _args);
pos.Free();normal.Free();        }

        /// 
        public void RenderSphere(Point3F pos, float radius, int sphereLevel = 0) {
pos.Alloc();             InternalUnsafeMethods.RenderSphere__Args _args = new InternalUnsafeMethods.RenderSphere__Args() {
                pos = pos.internalStructPtr,
                radius = radius,
                sphereLevel = sphereLevel,
             };
             InternalUnsafeMethods.RenderSphere()(ObjectPtr, _args);
pos.Free();        }

        /// 
        public void RenderBox(Point3F pos, Point3F size) {
pos.Alloc();size.Alloc();             InternalUnsafeMethods.RenderBox__Args _args = new InternalUnsafeMethods.RenderBox__Args() {
                pos = pos.internalStructPtr,
                size = size.internalStructPtr,
             };
             InternalUnsafeMethods.RenderBox()(ObjectPtr, _args);
pos.Free();size.Free();        }

        /// <description>
        /// Set the FOV for to use for orthographic views.
        /// </description>
        public void SetOrthoFOV(float fov) {
             InternalUnsafeMethods.SetOrthoFOV__Args _args = new InternalUnsafeMethods.SetOrthoFOV__Args() {
                fov = fov,
             };
             InternalUnsafeMethods.SetOrthoFOV()(ObjectPtr, _args);
        }

        /// <description>
        /// Return the FOV for orthographic views.
        /// </description>
        public float GetOrthoFOV() {
             InternalUnsafeMethods.GetOrthoFOV__Args _args = new InternalUnsafeMethods.GetOrthoFOV__Args() {
             };
             float _engineResult = InternalUnsafeMethods.GetOrthoFOV()(ObjectPtr, _args);
             return _engineResult;
        }

        /// 
        public void SetDisplayType(int displayType) {
             InternalUnsafeMethods.SetDisplayType__Args _args = new InternalUnsafeMethods.SetDisplayType__Args() {
                displayType = displayType,
             };
             InternalUnsafeMethods.SetDisplayType()(ObjectPtr, _args);
        }

        /// 
        public int GetDisplayType() {
             InternalUnsafeMethods.GetDisplayType__Args _args = new InternalUnsafeMethods.GetDisplayType__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetDisplayType()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Get the type info object for the EditTSCtrl class.
        /// </description>
        /// <returns>The type info object for EditTSCtrl</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// 
        /// </value>
        public float GridSize {
            get => GenericMarshal.StringTo<float>(GetFieldValue("gridSize"));
            set => SetFieldValue("gridSize", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public ColorI GridColor {
            get => GenericMarshal.StringTo<ColorI>(GetFieldValue("gridColor"));
            set => SetFieldValue("gridColor", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public ColorI GridOriginColor {
            get => GenericMarshal.StringTo<ColorI>(GetFieldValue("gridOriginColor"));
            set => SetFieldValue("gridOriginColor", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public ColorI GridMinorTickColor {
            get => GenericMarshal.StringTo<ColorI>(GetFieldValue("gridMinorTickColor"));
            set => SetFieldValue("gridMinorTickColor", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Whether to render the grid in orthographic axial projections.
        /// </description>
        /// </value>
        public bool RenderOrthoGrid {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("renderOrthoGrid"));
            set => SetFieldValue("renderOrthoGrid", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Grid patch pixel size below which to switch to coarser grid resolutions.
        /// </description>
        /// </value>
        public float RenderOrthoGridPixelBias {
            get => GenericMarshal.StringTo<float>(GetFieldValue("renderOrthoGridPixelBias"));
            set => SetFieldValue("renderOrthoGridPixelBias", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public bool RenderMissionArea {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("renderMissionArea"));
            set => SetFieldValue("renderMissionArea", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public ColorI MissionAreaFillColor {
            get => GenericMarshal.StringTo<ColorI>(GetFieldValue("missionAreaFillColor"));
            set => SetFieldValue("missionAreaFillColor", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public ColorI MissionAreaFrameColor {
            get => GenericMarshal.StringTo<ColorI>(GetFieldValue("missionAreaFrameColor"));
            set => SetFieldValue("missionAreaFrameColor", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// How high above and below the terrain to render the mission area bounds.
        /// </description>
        /// </value>
        public float MissionAreaHeightAdjust {
            get => GenericMarshal.StringTo<float>(GetFieldValue("missionAreaHeightAdjust"));
            set => SetFieldValue("missionAreaHeightAdjust", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public bool AllowBorderMove {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("allowBorderMove"));
            set => SetFieldValue("allowBorderMove", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public int BorderMovePixelSize {
            get => GenericMarshal.StringTo<int>(GetFieldValue("borderMovePixelSize"));
            set => SetFieldValue("borderMovePixelSize", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public float BorderMoveSpeed {
            get => GenericMarshal.StringTo<float>(GetFieldValue("borderMoveSpeed"));
            set => SetFieldValue("borderMoveSpeed", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public ColorI ConsoleFrameColor {
            get => GenericMarshal.StringTo<ColorI>(GetFieldValue("consoleFrameColor"));
            set => SetFieldValue("consoleFrameColor", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public ColorI ConsoleFillColor {
            get => GenericMarshal.StringTo<ColorI>(GetFieldValue("consoleFillColor"));
            set => SetFieldValue("consoleFillColor", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public int ConsoleSphereLevel {
            get => GenericMarshal.StringTo<int>(GetFieldValue("consoleSphereLevel"));
            set => SetFieldValue("consoleSphereLevel", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public int ConsoleCircleSegments {
            get => GenericMarshal.StringTo<int>(GetFieldValue("consoleCircleSegments"));
            set => SetFieldValue("consoleCircleSegments", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public int ConsoleLineWidth {
            get => GenericMarshal.StringTo<int>(GetFieldValue("consoleLineWidth"));
            set => SetFieldValue("consoleLineWidth", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public GizmoProfile GizmoProfile {
            get => GenericMarshal.StringTo<GizmoProfile>(GetFieldValue("GizmoProfile"));
            set => SetFieldValue("GizmoProfile", GenericMarshal.ToString(value));
        }
    }
}