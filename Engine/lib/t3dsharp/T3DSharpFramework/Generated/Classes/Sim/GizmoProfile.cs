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
    /// <summary>This class contains behavior and rendering properties used by the Gizmo class</summary>
    /// <description>
    /// Not intended for game development, for editors or internal use only.
    /// </description>
    public unsafe class GizmoProfile : SimObject {
        public GizmoProfile(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public GizmoProfile(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public GizmoProfile(string pName) 
            : this(pName, false) {
        }
        
        public GizmoProfile(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public GizmoProfile(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public GizmoProfile(SimObject pObj) 
            : base(pObj) {
        }
        
        public GizmoProfile(IntPtr pObj) 
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
                                "fnGizmoProfile_staticGetType"), typeof(_StaticGetType));
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
                                "fnGizmoProfile_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the GizmoProfile class.
        /// </description>
        /// <returns>The type info object for GizmoProfile</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// 
        /// </value>
        public GizmoAlignment Alignment {
            get => GenericMarshal.StringTo<GizmoAlignment>(GetFieldValue("alignment"));
            set => SetFieldValue("alignment", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public GizmoMode Mode {
            get => GenericMarshal.StringTo<GizmoMode>(GetFieldValue("mode"));
            set => SetFieldValue("mode", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public bool SnapToGrid {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("snapToGrid"));
            set => SetFieldValue("snapToGrid", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public bool AllowSnapRotations {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("allowSnapRotations"));
            set => SetFieldValue("allowSnapRotations", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public float RotationSnap {
            get => GenericMarshal.StringTo<float>(GetFieldValue("rotationSnap"));
            set => SetFieldValue("rotationSnap", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public bool AllowSnapScale {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("allowSnapScale"));
            set => SetFieldValue("allowSnapScale", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public float ScaleSnap {
            get => GenericMarshal.StringTo<float>(GetFieldValue("scaleSnap"));
            set => SetFieldValue("scaleSnap", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public bool ForceSnapRotations {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("forceSnapRotations"));
            set => SetFieldValue("forceSnapRotations", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public bool RenderWhenUsed {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("renderWhenUsed"));
            set => SetFieldValue("renderWhenUsed", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public bool RenderInfoText {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("renderInfoText"));
            set => SetFieldValue("renderInfoText", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public bool RenderPlane {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("renderPlane"));
            set => SetFieldValue("renderPlane", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public bool RenderPlaneHashes {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("renderPlaneHashes"));
            set => SetFieldValue("renderPlaneHashes", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public bool RenderSolid {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("renderSolid"));
            set => SetFieldValue("renderSolid", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public bool RenderMoveGrid {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("renderMoveGrid"));
            set => SetFieldValue("renderMoveGrid", GenericMarshal.ToString(value));
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
        public float PlaneDim {
            get => GenericMarshal.StringTo<float>(GetFieldValue("planeDim"));
            set => SetFieldValue("planeDim", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public Point3F GridSize {
            get => GenericMarshal.StringTo<Point3F>(GetFieldValue("gridSize"));
            set => SetFieldValue("gridSize", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public int ScreenLength {
            get => GenericMarshal.StringTo<int>(GetFieldValue("screenLength"));
            set => SetFieldValue("screenLength", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public float RotateScalar {
            get => GenericMarshal.StringTo<float>(GetFieldValue("rotateScalar"));
            set => SetFieldValue("rotateScalar", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public float ScaleScalar {
            get => GenericMarshal.StringTo<float>(GetFieldValue("scaleScalar"));
            set => SetFieldValue("scaleScalar", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public int Flags {
            get => GenericMarshal.StringTo<int>(GetFieldValue("flags"));
            set => SetFieldValue("flags", GenericMarshal.ToString(value));
        }
    }
}