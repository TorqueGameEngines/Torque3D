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
    /// <summary>An emitter to replicate fxFoliageItem objects across an area.</summary>
    /// <description>
    /// 
    /// </description>
    public unsafe class fxFoliageReplicator : SceneObject {
        public fxFoliageReplicator(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public fxFoliageReplicator(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public fxFoliageReplicator(string pName) 
            : this(pName, false) {
        }
        
        public fxFoliageReplicator(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public fxFoliageReplicator(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public fxFoliageReplicator(SimObject pObj) 
            : base(pObj) {
        }
        
        public fxFoliageReplicator(IntPtr pObj) 
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
                                "fnfxFoliageReplicator_staticGetType"), typeof(_StaticGetType));
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
                                "fnfxFoliageReplicator_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the fxFoliageReplicator class.
        /// </description>
        /// <returns>The type info object for fxFoliageReplicator</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Culling bins are drawn when set to true.
        /// </description>
        /// </value>
        public bool UseDebugInfo {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("UseDebugInfo"));
            set => SetFieldValue("UseDebugInfo", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Height multiplier for drawn culling bins.
        /// </description>
        /// </value>
        public float DebugBoxHeight {
            get => GenericMarshal.StringTo<float>(GetFieldValue("DebugBoxHeight"));
            set => SetFieldValue("DebugBoxHeight", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Foliage is hidden when set to true.
        /// </description>
        /// </value>
        public bool HideFoliage {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("HideFoliage"));
            set => SetFieldValue("HideFoliage", GenericMarshal.ToString(value));
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
        /// Random seed for foliage placement.
        /// </description>
        /// </value>
        public int Seed {
            get => GenericMarshal.StringTo<int>(GetFieldValue("seed"));
            set => SetFieldValue("seed", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Image file for the foliage texture.
        /// </description>
        /// </value>
        public string FoliageFile {
            get => GenericMarshal.StringTo<string>(GetFieldValue("FoliageFile"));
            set => SetFieldValue("FoliageFile", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Maximum foliage instance count.
        /// </description>
        /// </value>
        public int FoliageCount {
            get => GenericMarshal.StringTo<int>(GetFieldValue("FoliageCount"));
            set => SetFieldValue("FoliageCount", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Number of times to try placing a foliage instance before giving up.
        /// </description>
        /// </value>
        public int FoliageRetries {
            get => GenericMarshal.StringTo<int>(GetFieldValue("FoliageRetries"));
            set => SetFieldValue("FoliageRetries", GenericMarshal.ToString(value));
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
        /// Minimum width of foliage billboards
        /// </description>
        /// </value>
        public float MinWidth {
            get => GenericMarshal.StringTo<float>(GetFieldValue("MinWidth"));
            set => SetFieldValue("MinWidth", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Maximum width of foliage billboards
        /// </description>
        /// </value>
        public float MaxWidth {
            get => GenericMarshal.StringTo<float>(GetFieldValue("MaxWidth"));
            set => SetFieldValue("MaxWidth", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Minimum height of foliage billboards
        /// </description>
        /// </value>
        public float MinHeight {
            get => GenericMarshal.StringTo<float>(GetFieldValue("MinHeight"));
            set => SetFieldValue("MinHeight", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Maximum height of foliage billboards
        /// </description>
        /// </value>
        public float MaxHeight {
            get => GenericMarshal.StringTo<float>(GetFieldValue("MaxHeight"));
            set => SetFieldValue("MaxHeight", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Maintain aspect ratio of image if true. This option ignores MaxWidth.
        /// </description>
        /// </value>
        public bool FixAspectRatio {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("FixAspectRatio"));
            set => SetFieldValue("FixAspectRatio", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Use only MaxWidth and MaxHeight for billboard size. Ignores MinWidth and MinHeight.
        /// </description>
        /// </value>
        public bool FixSizeToMax {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("FixSizeToMax"));
            set => SetFieldValue("FixSizeToMax", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Offset billboards by this amount vertically.
        /// </description>
        /// </value>
        public float OffsetZ {
            get => GenericMarshal.StringTo<float>(GetFieldValue("OffsetZ"));
            set => SetFieldValue("OffsetZ", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Randomly flip billboards left-to-right.
        /// </description>
        /// </value>
        public bool RandomFlip {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("RandomFlip"));
            set => SetFieldValue("RandomFlip", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Use camera facing billboards ( including the z axis ).
        /// </description>
        /// </value>
        public bool UseTrueBillboards {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("useTrueBillboards"));
            set => SetFieldValue("useTrueBillboards", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Use culling bins when enabled.
        /// </description>
        /// </value>
        public bool UseCulling {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("UseCulling"));
            set => SetFieldValue("UseCulling", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Minimum size of culling bins.  Must be >= 8 and <= OuterRadius.
        /// </description>
        /// </value>
        public int CullResolution {
            get => GenericMarshal.StringTo<int>(GetFieldValue("CullResolution"));
            set => SetFieldValue("CullResolution", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Maximum distance from camera where foliage appears.
        /// </description>
        /// </value>
        public float ViewDistance {
            get => GenericMarshal.StringTo<float>(GetFieldValue("ViewDistance"));
            set => SetFieldValue("ViewDistance", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Minimum distance from camera where foliage appears.
        /// </description>
        /// </value>
        public float ViewClosest {
            get => GenericMarshal.StringTo<float>(GetFieldValue("ViewClosest"));
            set => SetFieldValue("ViewClosest", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Region beyond ViewDistance where foliage fades in/out.
        /// </description>
        /// </value>
        public float FadeInRegion {
            get => GenericMarshal.StringTo<float>(GetFieldValue("FadeInRegion"));
            set => SetFieldValue("FadeInRegion", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Region before ViewClosest where foliage fades in/out.
        /// </description>
        /// </value>
        public float FadeOutRegion {
            get => GenericMarshal.StringTo<float>(GetFieldValue("FadeOutRegion"));
            set => SetFieldValue("FadeOutRegion", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Minimum alpha value allowed on foliage instances.
        /// </description>
        /// </value>
        public float AlphaCutoff {
            get => GenericMarshal.StringTo<float>(GetFieldValue("AlphaCutoff"));
            set => SetFieldValue("AlphaCutoff", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Alpha of the foliage at ground level. 0 = transparent, 1 = opaque.
        /// </description>
        /// </value>
        public float GroundAlpha {
            get => GenericMarshal.StringTo<float>(GetFieldValue("GroundAlpha"));
            set => SetFieldValue("GroundAlpha", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Foliage should sway randomly when true.
        /// </description>
        /// </value>
        public bool SwayOn {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("SwayOn"));
            set => SetFieldValue("SwayOn", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Foliage instances should sway together when true and SwayOn is enabled.
        /// </description>
        /// </value>
        public bool SwaySync {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("SwaySync"));
            set => SetFieldValue("SwaySync", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Left-to-right sway magnitude.
        /// </description>
        /// </value>
        public float SwayMagSide {
            get => GenericMarshal.StringTo<float>(GetFieldValue("SwayMagSide"));
            set => SetFieldValue("SwayMagSide", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Front-to-back sway magnitude.
        /// </description>
        /// </value>
        public float SwayMagFront {
            get => GenericMarshal.StringTo<float>(GetFieldValue("SwayMagFront"));
            set => SetFieldValue("SwayMagFront", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Minumum sway cycle time in seconds.
        /// </description>
        /// </value>
        public float MinSwayTime {
            get => GenericMarshal.StringTo<float>(GetFieldValue("MinSwayTime"));
            set => SetFieldValue("MinSwayTime", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Maximum sway cycle time in seconds.
        /// </description>
        /// </value>
        public float MaxSwayTime {
            get => GenericMarshal.StringTo<float>(GetFieldValue("MaxSwayTime"));
            set => SetFieldValue("MaxSwayTime", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Foliage should be illuminated with changing lights when true.
        /// </description>
        /// </value>
        public bool LightOn {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("LightOn"));
            set => SetFieldValue("LightOn", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Foliage instances have the same lighting when set and LightOn is set.
        /// </description>
        /// </value>
        public bool LightSync {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("LightSync"));
            set => SetFieldValue("LightSync", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Minimum luminance for foliage instances.
        /// </description>
        /// </value>
        public float MinLuminance {
            get => GenericMarshal.StringTo<float>(GetFieldValue("MinLuminance"));
            set => SetFieldValue("MinLuminance", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Maximum luminance for foliage instances.
        /// </description>
        /// </value>
        public float MaxLuminance {
            get => GenericMarshal.StringTo<float>(GetFieldValue("MaxLuminance"));
            set => SetFieldValue("MaxLuminance", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Time before foliage illumination cycle repeats.
        /// </description>
        /// </value>
        public float LightTime {
            get => GenericMarshal.StringTo<float>(GetFieldValue("lightTime"));
            set => SetFieldValue("lightTime", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Foliage will be placed on terrain when set.
        /// </description>
        /// </value>
        public bool AllowOnTerrain {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("AllowOnTerrain"));
            set => SetFieldValue("AllowOnTerrain", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Foliage will be placed on Static shapes when set.
        /// </description>
        /// </value>
        public bool AllowOnStatics {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("AllowOnStatics"));
            set => SetFieldValue("AllowOnStatics", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Foliage will be placed on/under water when set.
        /// </description>
        /// </value>
        public bool AllowOnWater {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("AllowOnWater"));
            set => SetFieldValue("AllowOnWater", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Foliage will be placed on water when set. Requires AllowOnWater.
        /// </description>
        /// </value>
        public bool AllowWaterSurface {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("AllowWaterSurface"));
            set => SetFieldValue("AllowWaterSurface", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Maximum surface angle allowed for foliage instances.
        /// </description>
        /// </value>
        public int AllowedTerrainSlope {
            get => GenericMarshal.StringTo<int>(GetFieldValue("AllowedTerrainSlope"));
            set => SetFieldValue("AllowedTerrainSlope", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Multiplier controling amount foliage is modulated by sun's ambient.
        /// </description>
        /// </value>
        public float AmbientModulationBias {
            get => GenericMarshal.StringTo<float>(GetFieldValue("AmbientModulationBias"));
            set => SetFieldValue("AmbientModulationBias", GenericMarshal.ToString(value));
        }
    }
}