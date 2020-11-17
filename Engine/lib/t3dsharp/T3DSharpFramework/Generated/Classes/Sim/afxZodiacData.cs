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
    /// <summary>A datablock that specifies a decal-like Zodiac effect.</summary>
    /// <description>
    /// Zodiacs are special-purpose decal textures, often circular, that are always projected vertically onto the ground. Parameters control dynamic rotation and scale as well as texture, color, and blending style.
    /// 
    /// Zodiacs render on objects of type TerrainBlock, InteriorInstance, GroundPlane, MeshRoad, and TSStatic. They are very effective as spellcasting lighting rings, explosion shockwaves, scorched earth decals, and selection indicators.
    /// </description>
    public unsafe class afxZodiacData : GameBaseData {
        public afxZodiacData(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public afxZodiacData(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public afxZodiacData(string pName) 
            : this(pName, false) {
        }
        
        public afxZodiacData(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public afxZodiacData(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public afxZodiacData(SimObject pObj) 
            : base(pObj) {
        }
        
        public afxZodiacData(IntPtr pObj) 
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
                                "fnafxZodiacData_staticGetType"), typeof(_StaticGetType));
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
                                "fnafxZodiacData_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the afxZodiacData class.
        /// </description>
        /// <returns>The type info object for afxZodiacData</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// An image to use as the zodiac's texture.
        /// </description>
        /// </value>
        public string Texture {
            get => GenericMarshal.StringTo<string>(GetFieldValue("texture"));
            set => SetFieldValue("texture", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The zodiac's radius in scene units.
        /// </description>
        /// </value>
        public float Radius {
            get => GenericMarshal.StringTo<float>(GetFieldValue("radius"));
            set => SetFieldValue("radius", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// For interior zodiacs only, verticalRange specifies distances above and below the zodiac's position. If both values are 0.0, the radius is used.
        /// </description>
        /// </value>
        public Point2F VerticalRange {
            get => GenericMarshal.StringTo<Point2F>(GetFieldValue("verticalRange"));
            set => SetFieldValue("verticalRange", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Specifies if the zodiac's verticalRange should scale according to changes in the radius. When a zodiacs is used as an expanding shockwave, this value should be set to false, otherwise the zodiac can expand to cover an entire interior.
        /// </description>
        /// </value>
        public bool ScaleVerticalRange {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("scaleVerticalRange"));
            set => SetFieldValue("scaleVerticalRange", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The starting angle in degrees of the zodiac's rotation.
        /// </description>
        /// </value>
        public float StartAngle {
            get => GenericMarshal.StringTo<float>(GetFieldValue("startAngle"));
            set => SetFieldValue("startAngle", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The rate of rotation in degrees-per-second. Zodiacs with a positive rotationRate rotate clockwise, while those with negative values turn counter-clockwise.
        /// </description>
        /// </value>
        public float RotationRate {
            get => GenericMarshal.StringTo<float>(GetFieldValue("rotationRate"));
            set => SetFieldValue("rotationRate", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// A duration of time in seconds over which the zodiac grows from a zero size to its full size as specified by the radius.
        /// </description>
        /// </value>
        public float GrowInTime {
            get => GenericMarshal.StringTo<float>(GetFieldValue("growInTime"));
            set => SetFieldValue("growInTime", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// A duration of time in seconds over which the zodiac shrinks from full size to invisible.
        /// </description>
        /// </value>
        public float ShrinkOutTime {
            get => GenericMarshal.StringTo<float>(GetFieldValue("shrinkOutTime"));
            set => SetFieldValue("shrinkOutTime", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// A rate in meters-per-second at which the zodiac grows in size. A negative value will shrink the zodiac.
        /// </description>
        /// </value>
        public float GrowthRate {
            get => GenericMarshal.StringTo<float>(GetFieldValue("growthRate"));
            set => SetFieldValue("growthRate", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// A color value for the zodiac.
        /// </description>
        /// </value>
        public LinearColorF Color {
            get => GenericMarshal.StringTo<LinearColorF>(GetFieldValue("color"));
            set => SetFieldValue("color", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// A blending style for the zodiac. Possible values: normal, additive, or subtractive.
        /// </description>
        /// </value>
        public afxZodiac_BlendType Blend {
            get => GenericMarshal.StringTo<afxZodiac_BlendType>(GetFieldValue("blend"));
            set => SetFieldValue("blend", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Specifies if the zodiac should be rendered on terrain or terrain-like surfaces.
        /// </description>
        /// </value>
        public bool ShowOnTerrain {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("showOnTerrain"));
            set => SetFieldValue("showOnTerrain", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Specifies if the zodiac should be rendered on interior or interior-like surfaces.
        /// </description>
        /// </value>
        public bool ShowOnInteriors {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("showOnInteriors"));
            set => SetFieldValue("showOnInteriors", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Specifies if the zodiac should be rendered on the reflection rendering pass of the object it will be projected onto.
        /// </description>
        /// </value>
        public bool ShowInReflections {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("showInReflections"));
            set => SetFieldValue("showInReflections", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Specifies if the zodiac should be rendered on the non-reflection rendering pass of the object it will be projected onto.
        /// </description>
        /// </value>
        public bool ShowInNonReflections {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("showInNonReflections"));
            set => SetFieldValue("showInNonReflections", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Specifies if the zodiac's rotation should be defined by its constrained transformation.
        /// </description>
        /// </value>
        public bool TrackOrientConstraint {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("trackOrientConstraint"));
            set => SetFieldValue("trackOrientConstraint", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Specifies if interior zodiacs should be rendered exclusively on perfectly horizontal interior surfaces.
        /// </description>
        /// </value>
        public bool InteriorHorizontalOnly {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("interiorHorizontalOnly"));
            set => SetFieldValue("interiorHorizontalOnly", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Specifies if interior zodiacs should not be rendered on perfectly vertical interior surfaces.
        /// </description>
        /// </value>
        public bool InteriorIgnoreVertical {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("interiorIgnoreVertical"));
            set => SetFieldValue("interiorIgnoreVertical", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Specifies if interior zodiacs should not be rendered on interior surface which are backfacing to the zodiac's center.
        /// </description>
        /// </value>
        public bool InteriorIgnoreBackfaces {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("interiorIgnoreBackfaces"));
            set => SetFieldValue("interiorIgnoreBackfaces", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public bool InteriorIgnoreOpaque {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("interiorIgnoreOpaque"));
            set => SetFieldValue("interiorIgnoreOpaque", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public bool InteriorIgnoreTransparent {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("interiorIgnoreTransparent"));
            set => SetFieldValue("interiorIgnoreTransparent", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The altitude at which zodiac becomes invisible as the result of fading out or becoming too small.
        /// </description>
        /// </value>
        public float AltitudeMax {
            get => GenericMarshal.StringTo<float>(GetFieldValue("altitudeMax"));
            set => SetFieldValue("altitudeMax", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The altitude at which zodiac begins to fade and/or shrink.
        /// </description>
        /// </value>
        public float AltitudeFalloff {
            get => GenericMarshal.StringTo<float>(GetFieldValue("altitudeFalloff"));
            set => SetFieldValue("altitudeFalloff", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// When true, zodiac becomes smaller as altitude increases.
        /// </description>
        /// </value>
        public bool AltitudeShrinks {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("altitudeShrinks"));
            set => SetFieldValue("altitudeShrinks", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// When true, zodiac fades out as altitude increases.
        /// </description>
        /// </value>
        public bool AltitudeFades {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("altitudeFades"));
            set => SetFieldValue("altitudeFades", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The distance from camera at which the zodiac becomes invisible as the result of fading out.
        /// </description>
        /// </value>
        public float DistanceMax {
            get => GenericMarshal.StringTo<float>(GetFieldValue("distanceMax"));
            set => SetFieldValue("distanceMax", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The distance from camera at which the zodiac begins to fade out.
        /// </description>
        /// </value>
        public float DistanceFalloff {
            get => GenericMarshal.StringTo<float>(GetFieldValue("distanceFalloff"));
            set => SetFieldValue("distanceFalloff", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// When true, gradientRange will be used to determine on which polygons the zodiac will render.
        /// </description>
        /// </value>
        public bool UseGradientRange {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("useGradientRange"));
            set => SetFieldValue("useGradientRange", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// When true, a gradientRange specified on an InteriorInstance or TSStatic will be used instead of the zodiac's gradientRange.
        /// </description>
        /// </value>
        public bool PreferDestinationGradients {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("preferDestinationGradients"));
            set => SetFieldValue("preferDestinationGradients", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Zodiac will render on polygons with gradients within the range specified by gradientRange. 0 for floor polys, 90 for wall polys, 180 for ceiling polys.
        /// </description>
        /// </value>
        public Point2F GradientRange {
            get => GenericMarshal.StringTo<Point2F>(GetFieldValue("gradientRange"));
            set => SetFieldValue("gradientRange", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// When true, the zodiac will render on polygons with gradients outside of the range specified by gradientRange.
        /// </description>
        /// </value>
        public bool InvertGradientRange {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("invertGradientRange"));
            set => SetFieldValue("invertGradientRange", GenericMarshal.ToString(value));
        }
    }
}