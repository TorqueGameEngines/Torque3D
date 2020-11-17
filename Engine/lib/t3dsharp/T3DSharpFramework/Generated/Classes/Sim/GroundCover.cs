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
    /// <summary>Covers the ground in a field of objects (IE: Grass, Flowers, etc).</summary>
    public unsafe class GroundCover : SceneObject {
        public GroundCover(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public GroundCover(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public GroundCover(string pName) 
            : this(pName, false) {
        }
        
        public GroundCover(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public GroundCover(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public GroundCover(SimObject pObj) 
            : base(pObj) {
        }
        
        public GroundCover(IntPtr pObj) 
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
                                "fnGroundCover_staticGetType"), typeof(_StaticGetType));
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
                                "fnGroundCover_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the GroundCover class.
        /// </description>
        /// <returns>The type info object for GroundCover</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Material used by all GroundCover segments.
        /// </description>
        /// </value>
        public string Material {
            get => GenericMarshal.StringTo<string>(GetFieldValue("Material"));
            set => SetFieldValue("Material", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Outer generation radius from the current camera position.
        /// </description>
        /// </value>
        public float Radius {
            get => GenericMarshal.StringTo<float>(GetFieldValue("radius"));
            set => SetFieldValue("radius", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// This is less than or equal to radius and defines when fading of cover elements begins.
        /// </description>
        /// </value>
        public float DissolveRadius {
            get => GenericMarshal.StringTo<float>(GetFieldValue("dissolveRadius"));
            set => SetFieldValue("dissolveRadius", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Scales the various culling radii when rendering a reflection. Typically for water.
        /// </description>
        /// </value>
        public float ReflectScale {
            get => GenericMarshal.StringTo<float>(GetFieldValue("reflectScale"));
            set => SetFieldValue("reflectScale", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The number of cells per axis in the grid.
        /// </description>
        /// </value>
        public int GridSize {
            get => GenericMarshal.StringTo<int>(GetFieldValue("gridSize"));
            set => SetFieldValue("gridSize", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Offset along the Z axis to render the ground cover.
        /// </description>
        /// </value>
        public float ZOffset {
            get => GenericMarshal.StringTo<float>(GetFieldValue("zOffset"));
            set => SetFieldValue("zOffset", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// This RNG seed is saved and sent to clients for generating the same cover.
        /// </description>
        /// </value>
        public int Seed {
            get => GenericMarshal.StringTo<int>(GetFieldValue("seed"));
            set => SetFieldValue("seed", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The maximum amount of cover elements to include in the grid at any one time.
        /// </description>
        /// </value>
        public int MaxElements {
            get => GenericMarshal.StringTo<int>(GetFieldValue("maxElements"));
            set => SetFieldValue("maxElements", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The maximum amout of degrees the billboard will tilt down to match the camera.
        /// </description>
        /// </value>
        public float MaxBillboardTiltAngle {
            get => GenericMarshal.StringTo<float>(GetFieldValue("maxBillboardTiltAngle"));
            set => SetFieldValue("maxBillboardTiltAngle", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// This is the distance at which DTS elements are  completely culled out.
        /// </description>
        /// </value>
        public float ShapeCullRadius {
            get => GenericMarshal.StringTo<float>(GetFieldValue("shapeCullRadius"));
            set => SetFieldValue("shapeCullRadius", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Whether DTS elements should cast shadows or not.
        /// </description>
        /// </value>
        public bool ShapesCastShadows {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("shapesCastShadows"));
            set => SetFieldValue("shapesCastShadows", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Subset material UV coordinates for this cover billboard.
        /// </description>
        /// </value>
        public DynamicFieldVector<RectF> BillboardUVs {
            get => new DynamicFieldVector<RectF>(
                    this, 
                    "billboardUVs", 
                    8, 
                    val => GenericMarshal.StringTo<RectF>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// The cover shape filename. [Optional]
        /// </description>
        /// </value>
        public DynamicFieldVector<string> ShapeFilename {
            get => new DynamicFieldVector<string>(
                    this, 
                    "shapeFilename", 
                    8, 
                    val => GenericMarshal.StringTo<string>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Terrain material name to limit coverage to, or blank to not limit.
        /// </description>
        /// </value>
        public DynamicFieldVector<string> Layer {
            get => new DynamicFieldVector<string>(
                    this, 
                    "layer", 
                    8, 
                    val => GenericMarshal.StringTo<string>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Indicates that the terrain material index given in 'layer' is an exclusion mask.
        /// </description>
        /// </value>
        public DynamicFieldVector<bool> InvertLayer {
            get => new DynamicFieldVector<bool>(
                    this, 
                    "invertLayer", 
                    8, 
                    val => GenericMarshal.StringTo<bool>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// The probability of one cover type verses another (relative to all cover types).
        /// </description>
        /// </value>
        public DynamicFieldVector<float> Probability {
            get => new DynamicFieldVector<float>(
                    this, 
                    "probability", 
                    8, 
                    val => GenericMarshal.StringTo<float>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// The minimum random size for each cover type.
        /// </description>
        /// </value>
        public DynamicFieldVector<float> SizeMin {
            get => new DynamicFieldVector<float>(
                    this, 
                    "sizeMin", 
                    8, 
                    val => GenericMarshal.StringTo<float>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// The maximum random size of this cover type.
        /// </description>
        /// </value>
        public DynamicFieldVector<float> SizeMax {
            get => new DynamicFieldVector<float>(
                    this, 
                    "sizeMax", 
                    8, 
                    val => GenericMarshal.StringTo<float>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// An exponent used to bias between the minimum and maximum random sizes.
        /// </description>
        /// </value>
        public DynamicFieldVector<float> SizeExponent {
            get => new DynamicFieldVector<float>(
                    this, 
                    "sizeExponent", 
                    8, 
                    val => GenericMarshal.StringTo<float>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// The wind effect scale.
        /// </description>
        /// </value>
        public DynamicFieldVector<float> WindScale {
            get => new DynamicFieldVector<float>(
                    this, 
                    "windScale", 
                    8, 
                    val => GenericMarshal.StringTo<float>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// The minimum slope angle in degrees for placement.
        /// </description>
        /// </value>
        public DynamicFieldVector<float> MinSlope {
            get => new DynamicFieldVector<float>(
                    this, 
                    "minSlope", 
                    8, 
                    val => GenericMarshal.StringTo<float>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// The maximum slope angle in degrees for placement.
        /// </description>
        /// </value>
        public DynamicFieldVector<float> MaxSlope {
            get => new DynamicFieldVector<float>(
                    this, 
                    "maxSlope", 
                    8, 
                    val => GenericMarshal.StringTo<float>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Use the terrain's slope for angle
        /// </description>
        /// </value>
        public DynamicFieldVector<bool> ConformToNormal {
            get => new DynamicFieldVector<bool>(
                    this, 
                    "conformToNormal", 
                    8, 
                    val => GenericMarshal.StringTo<bool>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// minumum amount of rotation along the X axis to add
        /// </description>
        /// </value>
        public DynamicFieldVector<float> MinRotX {
            get => new DynamicFieldVector<float>(
                    this, 
                    "minRotX", 
                    8, 
                    val => GenericMarshal.StringTo<float>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// maximum amount of rotation along the X axis to add
        /// </description>
        /// </value>
        public DynamicFieldVector<float> MaxRotX {
            get => new DynamicFieldVector<float>(
                    this, 
                    "maxRotX", 
                    8, 
                    val => GenericMarshal.StringTo<float>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// minumum amount of rotation along the Y axis to add
        /// </description>
        /// </value>
        public DynamicFieldVector<float> MinRotY {
            get => new DynamicFieldVector<float>(
                    this, 
                    "minRotY", 
                    8, 
                    val => GenericMarshal.StringTo<float>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// maximum amount of rotation along the Y axis to add
        /// </description>
        /// </value>
        public DynamicFieldVector<float> MaxRotY {
            get => new DynamicFieldVector<float>(
                    this, 
                    "maxRotY", 
                    8, 
                    val => GenericMarshal.StringTo<float>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// The minimum world space elevation for placement.
        /// </description>
        /// </value>
        public DynamicFieldVector<float> MinElevation {
            get => new DynamicFieldVector<float>(
                    this, 
                    "minElevation", 
                    8, 
                    val => GenericMarshal.StringTo<float>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// The maximum world space elevation for placement.
        /// </description>
        /// </value>
        public DynamicFieldVector<float> MaxElevation {
            get => new DynamicFieldVector<float>(
                    this, 
                    "maxElevation", 
                    8, 
                    val => GenericMarshal.StringTo<float>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// The minimum amount of elements in a clump.
        /// </description>
        /// </value>
        public DynamicFieldVector<int> MinClumpCount {
            get => new DynamicFieldVector<int>(
                    this, 
                    "minClumpCount", 
                    8, 
                    val => GenericMarshal.StringTo<int>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// The maximum amount of elements in a clump.
        /// </description>
        /// </value>
        public DynamicFieldVector<int> MaxClumpCount {
            get => new DynamicFieldVector<int>(
                    this, 
                    "maxClumpCount", 
                    8, 
                    val => GenericMarshal.StringTo<int>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// An exponent used to bias between the minimum and maximum clump counts for a particular clump.
        /// </description>
        /// </value>
        public DynamicFieldVector<float> ClumpExponent {
            get => new DynamicFieldVector<float>(
                    this, 
                    "clumpExponent", 
                    8, 
                    val => GenericMarshal.StringTo<float>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// The maximum clump radius.
        /// </description>
        /// </value>
        public DynamicFieldVector<float> ClumpRadius {
            get => new DynamicFieldVector<float>(
                    this, 
                    "clumpRadius", 
                    8, 
                    val => GenericMarshal.StringTo<float>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// The direction of the wind.
        /// </description>
        /// </value>
        public Point2F WindDirection {
            get => GenericMarshal.StringTo<Point2F>(GetFieldValue("windDirection"));
            set => SetFieldValue("windDirection", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The length in meters between peaks in the wind gust.
        /// </description>
        /// </value>
        public float WindGustLength {
            get => GenericMarshal.StringTo<float>(GetFieldValue("windGustLength"));
            set => SetFieldValue("windGustLength", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Controls how often the wind gust peaks per second.
        /// </description>
        /// </value>
        public float WindGustFrequency {
            get => GenericMarshal.StringTo<float>(GetFieldValue("windGustFrequency"));
            set => SetFieldValue("windGustFrequency", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The maximum distance in meters that the peak wind  gust will displace an element.
        /// </description>
        /// </value>
        public float WindGustStrength {
            get => GenericMarshal.StringTo<float>(GetFieldValue("windGustStrength"));
            set => SetFieldValue("windGustStrength", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Controls the overall rapidity of the wind turbulence.
        /// </description>
        /// </value>
        public float WindTurbulenceFrequency {
            get => GenericMarshal.StringTo<float>(GetFieldValue("windTurbulenceFrequency"));
            set => SetFieldValue("windTurbulenceFrequency", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The maximum distance in meters that the turbulence can displace a ground cover element.
        /// </description>
        /// </value>
        public float WindTurbulenceStrength {
            get => GenericMarshal.StringTo<float>(GetFieldValue("windTurbulenceStrength"));
            set => SetFieldValue("windTurbulenceStrength", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Debug parameter for locking the culling frustum which will freeze the cover generation.
        /// </description>
        /// </value>
        public bool LockFrustum {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("lockFrustum"));
            set => SetFieldValue("lockFrustum", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Debug parameter for displaying the grid cells.
        /// </description>
        /// </value>
        public bool RenderCells {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("renderCells"));
            set => SetFieldValue("renderCells", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Debug parameter for turning off billboard rendering.
        /// </description>
        /// </value>
        public bool NoBillboards {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("noBillboards"));
            set => SetFieldValue("noBillboards", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Debug parameter for turning off shape rendering.
        /// </description>
        /// </value>
        public bool NoShapes {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("noShapes"));
            set => SetFieldValue("noShapes", GenericMarshal.ToString(value));
        }
    }
}