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
    /// <summary>An emitter for objects to replicate across an area.</summary>
    /// <description>
    /// 
    /// </description>
    public unsafe class fxShapeReplicator : SceneObject {
        public fxShapeReplicator(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public fxShapeReplicator(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public fxShapeReplicator(string pName) 
            : this(pName, false) {
        }
        
        public fxShapeReplicator(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public fxShapeReplicator(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public fxShapeReplicator(SimObject pObj) 
            : base(pObj) {
        }
        
        public fxShapeReplicator(IntPtr pObj) 
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
                                "fnfxShapeReplicator_staticGetType"), typeof(_StaticGetType));
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
                                "fnfxShapeReplicator_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the fxShapeReplicator class.
        /// </description>
        /// <returns>The type info object for fxShapeReplicator</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Replicated shapes are hidden when set to true.
        /// </description>
        /// </value>
        public bool HideReplications {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("HideReplications"));
            set => SetFieldValue("HideReplications", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Draw placement rings when set to true.
        /// </description>
        /// </value>
        public bool ShowPlacementArea {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("ShowPlacementArea"));
            set => SetFieldValue("ShowPlacementArea", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Height of the placement ring in world units.
        /// </description>
        /// </value>
        public int PlacementAreaHeight {
            get => GenericMarshal.StringTo<int>(GetFieldValue("PlacementAreaHeight"));
            set => SetFieldValue("PlacementAreaHeight", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Color of the placement ring.
        /// </description>
        /// </value>
        public LinearColorF PlacementColour {
            get => GenericMarshal.StringTo<LinearColorF>(GetFieldValue("PlacementColour"));
            set => SetFieldValue("PlacementColour", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Filename of shape to replicate.
        /// </description>
        /// </value>
        public string ShapeFile {
            get => GenericMarshal.StringTo<string>(GetFieldValue("shapeFile"));
            set => SetFieldValue("shapeFile", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Random seed for shape placement.
        /// </description>
        /// </value>
        public int Seed {
            get => GenericMarshal.StringTo<int>(GetFieldValue("seed"));
            set => SetFieldValue("seed", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Maximum shape instance count.
        /// </description>
        /// </value>
        public int ShapeCount {
            get => GenericMarshal.StringTo<int>(GetFieldValue("ShapeCount"));
            set => SetFieldValue("ShapeCount", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Number of times to try placing a shape instance before giving up.
        /// </description>
        /// </value>
        public int ShapeRetries {
            get => GenericMarshal.StringTo<int>(GetFieldValue("ShapeRetries"));
            set => SetFieldValue("ShapeRetries", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Placement area inner radius on the X axis
        /// </description>
        /// </value>
        public int InnerRadiusX {
            get => GenericMarshal.StringTo<int>(GetFieldValue("InnerRadiusX"));
            set => SetFieldValue("InnerRadiusX", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Placement area inner radius on the Y axis
        /// </description>
        /// </value>
        public int InnerRadiusY {
            get => GenericMarshal.StringTo<int>(GetFieldValue("InnerRadiusY"));
            set => SetFieldValue("InnerRadiusY", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Placement area outer radius on the X axis
        /// </description>
        /// </value>
        public int OuterRadiusX {
            get => GenericMarshal.StringTo<int>(GetFieldValue("OuterRadiusX"));
            set => SetFieldValue("OuterRadiusX", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Placement area outer radius on the Y axis
        /// </description>
        /// </value>
        public int OuterRadiusY {
            get => GenericMarshal.StringTo<int>(GetFieldValue("OuterRadiusY"));
            set => SetFieldValue("OuterRadiusY", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Shapes will be placed on terrain when set.
        /// </description>
        /// </value>
        public bool AllowOnTerrain {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("AllowOnTerrain"));
            set => SetFieldValue("AllowOnTerrain", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Shapes will be placed on Static shapes when set.
        /// </description>
        /// </value>
        public bool AllowOnStatics {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("AllowOnStatics"));
            set => SetFieldValue("AllowOnStatics", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Shapes will be placed on/under water when set.
        /// </description>
        /// </value>
        public bool AllowOnWater {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("AllowOnWater"));
            set => SetFieldValue("AllowOnWater", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Shapes will be placed on water when set. Requires AllowOnWater.
        /// </description>
        /// </value>
        public bool AllowWaterSurface {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("AllowWaterSurface"));
            set => SetFieldValue("AllowWaterSurface", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Align shapes to surface normal when set.
        /// </description>
        /// </value>
        public bool AlignToTerrain {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("AlignToTerrain"));
            set => SetFieldValue("AlignToTerrain", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Allow physics interactions with shapes.
        /// </description>
        /// </value>
        public bool Interactions {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("Interactions"));
            set => SetFieldValue("Interactions", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Maximum surface angle allowed for shape instances.
        /// </description>
        /// </value>
        public int AllowedTerrainSlope {
            get => GenericMarshal.StringTo<int>(GetFieldValue("AllowedTerrainSlope"));
            set => SetFieldValue("AllowedTerrainSlope", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Surface normals will be multiplied by these values when AlignToTerrain is enabled.
        /// </description>
        /// </value>
        public Point3F TerrainAlignment {
            get => GenericMarshal.StringTo<Point3F>(GetFieldValue("TerrainAlignment"));
            set => SetFieldValue("TerrainAlignment", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Minimum shape scale.
        /// </description>
        /// </value>
        public Point3F ShapeScaleMin {
            get => GenericMarshal.StringTo<Point3F>(GetFieldValue("ShapeScaleMin"));
            set => SetFieldValue("ShapeScaleMin", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Maximum shape scale.
        /// </description>
        /// </value>
        public Point3F ShapeScaleMax {
            get => GenericMarshal.StringTo<Point3F>(GetFieldValue("ShapeScaleMax"));
            set => SetFieldValue("ShapeScaleMax", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Minimum shape rotation angles.
        /// </description>
        /// </value>
        public Point3F ShapeRotateMin {
            get => GenericMarshal.StringTo<Point3F>(GetFieldValue("ShapeRotateMin"));
            set => SetFieldValue("ShapeRotateMin", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Maximum shape rotation angles.
        /// </description>
        /// </value>
        public Point3F ShapeRotateMax {
            get => GenericMarshal.StringTo<Point3F>(GetFieldValue("ShapeRotateMax"));
            set => SetFieldValue("ShapeRotateMax", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Offset shapes by this amount vertically.
        /// </description>
        /// </value>
        public int OffsetZ {
            get => GenericMarshal.StringTo<int>(GetFieldValue("OffsetZ"));
            set => SetFieldValue("OffsetZ", GenericMarshal.ToString(value));
        }
    }
}