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
    /// <summary>An example scene object which renders a mesh.</summary>
    /// <description>
    /// This class implements a basic SceneObject that can exist in the world at a 3D position and render itself. There are several valid ways to render an object in Torque. This class implements the preferred rendering method which is to submit a MeshRenderInst along with a Material, vertex buffer, primitive buffer, and transform and allow the RenderMeshMgr handle the actual setup and rendering for you.
    ///
    /// See the C++ code for implementation details.
    /// </description>
    public unsafe class ReflectionProbe : SceneObject {
        public ReflectionProbe(bool pRegister = false)
            : base(pRegister) {
        }

        public ReflectionProbe(string pName, bool pRegister)
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }

        public ReflectionProbe(string pName)
            : this(pName, false) {
        }

        public ReflectionProbe(string pName, string pParent, bool pRegister = false)
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }

        public ReflectionProbe(string pName, SimObject pParent, bool pRegister = false)
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }

        public ReflectionProbe(SimObject pObj)
            : base(pObj) {
        }

        public ReflectionProbe(IntPtr pObj)
            : base(pObj) {
        }

		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct Bake__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Bake(IntPtr _this, Bake__Args args);
            private static _Bake _BakeFunc;
            internal static _Bake Bake() {
                if (_BakeFunc == null) {
                    _BakeFunc =
                        (_Bake)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnReflectionProbe_Bake"), typeof(_Bake));
                }

                return _BakeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct PostApply__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _PostApply(IntPtr _this, PostApply__Args args);
            private static _PostApply _PostApplyFunc;
            internal static _PostApply PostApply() {
                if (_PostApplyFunc == null) {
                    _PostApplyFunc =
                        (_PostApply)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnReflectionProbe_postApply"), typeof(_PostApply));
                }

                return _PostApplyFunc;
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
                                "fnReflectionProbe_staticGetType"), typeof(_StaticGetType));
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
                                "fnReflectionProbe_create"), typeof(_Create));
                }

                return _CreateFunc;
            }
        }
        #endregion

        /// <summary>returns true if control object is inside the fog</summary>
        /// <description>
        /// .
        /// </description>
        public void Bake() {
             InternalUnsafeMethods.Bake__Args _args = new InternalUnsafeMethods.Bake__Args() {
             };
             InternalUnsafeMethods.Bake()(ObjectPtr, _args);
        }

        /// <description>
        /// A utility method for forcing a network update.
        /// </description>
        public void PostApply() {
             InternalUnsafeMethods.PostApply__Args _args = new InternalUnsafeMethods.PostApply__Args() {
             };
             InternalUnsafeMethods.PostApply()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the ReflectionProbe class.
        /// </description>
        /// <returns>The type info object for ReflectionProbe</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Regenerate Voxel Grid
        /// </description>
        /// </value>
        public bool Enabled {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("Enabled"));
            set => SetFieldValue("Enabled", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The name of the material used to render the mesh.
        /// </description>
        /// </value>
        public float Radius {
            get => GenericMarshal.StringTo<float>(GetFieldValue("radius"));
            set => SetFieldValue("radius", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Toggle Edit Pos Offset Mode
        /// </description>
        /// </value>
        public bool EditPosOffset {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("EditPosOffset"));
            set => SetFieldValue("EditPosOffset", GenericMarshal.ToString(value));
        }


        /// <value>
        ///
        /// </value>
        public Point3F RefOffset {
            get => GenericMarshal.StringTo<Point3F>(GetFieldValue("refOffset"));
            set => SetFieldValue("refOffset", GenericMarshal.ToString(value));
        }


        /// <value>
        ///
        /// </value>
        public Point3F RefScale {
            get => GenericMarshal.StringTo<Point3F>(GetFieldValue("refScale"));
            set => SetFieldValue("refScale", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The type of mesh data to use for collision queries.
        /// </description>
        /// </value>
        public ReflectionModeEnum ReflectionMode {
            get => GenericMarshal.StringTo<ReflectionModeEnum>(GetFieldValue("ReflectionMode"));
            set => SetFieldValue("ReflectionMode", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Cubemap used instead of reflection texture if fullReflect is off.
        /// </description>
        /// </value>
        public string StaticCubemap {
            get => GenericMarshal.StringTo<string>(GetFieldValue("StaticCubemap"));
            set => SetFieldValue("StaticCubemap", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// How often the dynamic cubemap is refreshed in milliseconds. Only works when the ReflectionMode is set to DynamicCubemap.
        /// </description>
        /// </value>
        public int DynamicReflectionRefreshMS {
            get => GenericMarshal.StringTo<int>(GetFieldValue("DynamicReflectionRefreshMS"));
            set => SetFieldValue("DynamicReflectionRefreshMS", GenericMarshal.ToString(value));
        }
    }
}
