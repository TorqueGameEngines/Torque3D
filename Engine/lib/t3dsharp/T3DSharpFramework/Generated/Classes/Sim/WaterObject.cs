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
    /// <summary>Abstract base class for representing a body of water.</summary>
    /// <description>
    /// %WaterObject is abstract and may not be created. It defines functionality shared by its derived classes.
    /// 
    /// %WaterObject exposes many fields for controlling it visual quality.
    /// 
    /// %WaterObject surface rendering has the following general features:
    /// 	- Waves represented by vertex undulation and user paramaters.
    /// 	- Ripples represented by a normal map and user parameters.
    /// 	- Refraction of underwater objects.
    /// 	- Dynamic planar reflection or static cubemap reflection.
    /// 	- Paramable water fog and color shift.
    /// 
    /// It will, however, look significantly different depending on the LightingManager that is active. With Basic Lighting, we do not have a deferred texture to lookup per-pixel depth and therefore cannot use our rendering techniques that depend on it.
    /// 
    /// In particular, the following field groups are not used under Basic Lighting:
    /// 	- Underwater Fogging 
    /// 	- Misc 
    /// 	- Distortion 
    /// 	- And foam related fields under the %WaterObject group.
    /// 
    /// %WaterObject also defines several fields for gameplay use and objects that support buoyancy.
    /// </description>
    public unsafe class WaterObject : SceneObject {
        public WaterObject(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public WaterObject(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public WaterObject(string pName) 
            : this(pName, false) {
        }
        
        public WaterObject(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public WaterObject(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public WaterObject(SimObject pObj) 
            : base(pObj) {
        }
        
        public WaterObject(IntPtr pObj) 
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
                                "fnWaterObject_staticGetType"), typeof(_StaticGetType));
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
                                "fnWaterObject_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the WaterObject class.
        /// </description>
        /// <returns>The type info object for WaterObject</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Affects buoyancy of an object, thus affecting the Z velocity of a player (jumping, falling, etc.
        /// </description>
        /// </value>
        public float Density {
            get => GenericMarshal.StringTo<float>(GetFieldValue("density"));
            set => SetFieldValue("density", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Affects drag force applied to an object submerged in this container.
        /// </description>
        /// </value>
        public float Viscosity {
            get => GenericMarshal.StringTo<float>(GetFieldValue("viscosity"));
            set => SetFieldValue("viscosity", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Liquid type of WaterBlock, such as water, ocean, lava Currently only Water is defined and used.
        /// </description>
        /// </value>
        public string LiquidType {
            get => GenericMarshal.StringTo<string>(GetFieldValue("liquidType"));
            set => SetFieldValue("liquidType", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Changes color of water fog.
        /// </description>
        /// </value>
        public ColorI BaseColor {
            get => GenericMarshal.StringTo<ColorI>(GetFieldValue("baseColor"));
            set => SetFieldValue("baseColor", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Extent of fresnel affecting reflection fogging.
        /// </description>
        /// </value>
        public float FresnelBias {
            get => GenericMarshal.StringTo<float>(GetFieldValue("fresnelBias"));
            set => SetFieldValue("fresnelBias", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Measures intensity of affect on reflection based on fogging.
        /// </description>
        /// </value>
        public float FresnelPower {
            get => GenericMarshal.StringTo<float>(GetFieldValue("fresnelPower"));
            set => SetFieldValue("fresnelPower", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Power used for specularity on the water surface ( sun only ).
        /// </description>
        /// </value>
        public float SpecularPower {
            get => GenericMarshal.StringTo<float>(GetFieldValue("specularPower"));
            set => SetFieldValue("specularPower", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Color used for specularity on the water surface ( sun only ).
        /// </description>
        /// </value>
        public LinearColorF SpecularColor {
            get => GenericMarshal.StringTo<LinearColorF>(GetFieldValue("specularColor"));
            set => SetFieldValue("specularColor", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// When true the water colors don't react to changes to environment lighting.
        /// </description>
        /// </value>
        public bool Emissive {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("emissive"));
            set => SetFieldValue("emissive", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Direction waves flow toward shores.
        /// </description>
        /// </value>
        public DynamicFieldVector<Point2F> WaveDir {
            get => new DynamicFieldVector<Point2F>(
                    this, 
                    "waveDir", 
                    3, 
                    val => GenericMarshal.StringTo<Point2F>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Speed of water undulation.
        /// </description>
        /// </value>
        public DynamicFieldVector<float> WaveSpeed {
            get => new DynamicFieldVector<float>(
                    this, 
                    "waveSpeed", 
                    3, 
                    val => GenericMarshal.StringTo<float>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Height of water undulation.
        /// </description>
        /// </value>
        public DynamicFieldVector<float> WaveMagnitude {
            get => new DynamicFieldVector<float>(
                    this, 
                    "waveMagnitude", 
                    3, 
                    val => GenericMarshal.StringTo<float>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Master variable affecting entire body of water's undulation
        /// </description>
        /// </value>
        public float OverallWaveMagnitude {
            get => GenericMarshal.StringTo<float>(GetFieldValue("overallWaveMagnitude"));
            set => SetFieldValue("overallWaveMagnitude", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Normal map used to simulate small surface ripples
        /// </description>
        /// </value>
        public string RippleTex {
            get => GenericMarshal.StringTo<string>(GetFieldValue("rippleTex"));
            set => SetFieldValue("rippleTex", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Modifies the direction of ripples on the surface.
        /// </description>
        /// </value>
        public DynamicFieldVector<Point2F> RippleDir {
            get => new DynamicFieldVector<Point2F>(
                    this, 
                    "rippleDir", 
                    3, 
                    val => GenericMarshal.StringTo<Point2F>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Modifies speed of surface ripples.
        /// </description>
        /// </value>
        public DynamicFieldVector<float> RippleSpeed {
            get => new DynamicFieldVector<float>(
                    this, 
                    "rippleSpeed", 
                    3, 
                    val => GenericMarshal.StringTo<float>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Intensifies the affect of the normal map applied to the surface.
        /// </description>
        /// </value>
        public DynamicFieldVector<Point2F> RippleTexScale {
            get => new DynamicFieldVector<Point2F>(
                    this, 
                    "rippleTexScale", 
                    3, 
                    val => GenericMarshal.StringTo<Point2F>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Intensifies the vertext modification of the surface.
        /// </description>
        /// </value>
        public DynamicFieldVector<float> RippleMagnitude {
            get => new DynamicFieldVector<float>(
                    this, 
                    "rippleMagnitude", 
                    3, 
                    val => GenericMarshal.StringTo<float>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Master variable affecting entire surface
        /// </description>
        /// </value>
        public float OverallRippleMagnitude {
            get => GenericMarshal.StringTo<float>(GetFieldValue("overallRippleMagnitude"));
            set => SetFieldValue("overallRippleMagnitude", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Diffuse texture for foam in shallow water (advanced lighting only)
        /// </description>
        /// </value>
        public string FoamTex {
            get => GenericMarshal.StringTo<string>(GetFieldValue("foamTex"));
            set => SetFieldValue("foamTex", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public DynamicFieldVector<Point2F> FoamDir {
            get => new DynamicFieldVector<Point2F>(
                    this, 
                    "foamDir", 
                    2, 
                    val => GenericMarshal.StringTo<Point2F>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// 
        /// </value>
        public DynamicFieldVector<float> FoamSpeed {
            get => new DynamicFieldVector<float>(
                    this, 
                    "foamSpeed", 
                    2, 
                    val => GenericMarshal.StringTo<float>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// applied to the surface.
        /// </description>
        /// </value>
        public DynamicFieldVector<Point2F> FoamTexScale {
            get => new DynamicFieldVector<Point2F>(
                    this, 
                    "foamTexScale", 
                    2, 
                    val => GenericMarshal.StringTo<Point2F>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// 
        /// </value>
        public DynamicFieldVector<float> FoamOpacity {
            get => new DynamicFieldVector<float>(
                    this, 
                    "foamOpacity", 
                    2, 
                    val => GenericMarshal.StringTo<float>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// 
        /// </value>
        public float OverallFoamOpacity {
            get => GenericMarshal.StringTo<float>(GetFieldValue("overallFoamOpacity"));
            set => SetFieldValue("overallFoamOpacity", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public float FoamMaxDepth {
            get => GenericMarshal.StringTo<float>(GetFieldValue("foamMaxDepth"));
            set => SetFieldValue("foamMaxDepth", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public float FoamAmbientLerp {
            get => GenericMarshal.StringTo<float>(GetFieldValue("foamAmbientLerp"));
            set => SetFieldValue("foamAmbientLerp", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public float FoamRippleInfluence {
            get => GenericMarshal.StringTo<float>(GetFieldValue("foamRippleInfluence"));
            set => SetFieldValue("foamRippleInfluence", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Cubemap used instead of reflection texture if fullReflect is off.
        /// </description>
        /// </value>
        public string Cubemap {
            get => GenericMarshal.StringTo<string>(GetFieldValue("cubemap"));
            set => SetFieldValue("cubemap", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Enables dynamic reflection rendering.
        /// </description>
        /// </value>
        public bool FullReflect {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("fullReflect"));
            set => SetFieldValue("fullReflect", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Overall scalar to the reflectivity of the water surface.
        /// </description>
        /// </value>
        public float Reflectivity {
            get => GenericMarshal.StringTo<float>(GetFieldValue("reflectivity"));
            set => SetFieldValue("reflectivity", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Affects the sort order of reflected objects.
        /// </description>
        /// </value>
        public float ReflectPriority {
            get => GenericMarshal.StringTo<float>(GetFieldValue("reflectPriority"));
            set => SetFieldValue("reflectPriority", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Affects the sort time of reflected objects.
        /// </description>
        /// </value>
        public int ReflectMaxRateMs {
            get => GenericMarshal.StringTo<int>(GetFieldValue("reflectMaxRateMs"));
            set => SetFieldValue("reflectMaxRateMs", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// scale up or down the detail level for objects rendered in a reflection
        /// </description>
        /// </value>
        public float ReflectDetailAdjust {
            get => GenericMarshal.StringTo<float>(GetFieldValue("reflectDetailAdjust"));
            set => SetFieldValue("reflectDetailAdjust", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// always use z up as the reflection normal
        /// </description>
        /// </value>
        public bool ReflectNormalUp {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("reflectNormalUp"));
            set => SetFieldValue("reflectNormalUp", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// turn off reflection rendering when occluded (delayed).
        /// </description>
        /// </value>
        public bool UseOcclusionQuery {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("useOcclusionQuery"));
            set => SetFieldValue("useOcclusionQuery", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The texture size used for reflections (square)
        /// </description>
        /// </value>
        public int ReflectTexSize {
            get => GenericMarshal.StringTo<int>(GetFieldValue("reflectTexSize"));
            set => SetFieldValue("reflectTexSize", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Intensity of underwater fogging.
        /// </description>
        /// </value>
        public float WaterFogDensity {
            get => GenericMarshal.StringTo<float>(GetFieldValue("waterFogDensity"));
            set => SetFieldValue("waterFogDensity", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Delta, or limit, applied to waterFogDensity.
        /// </description>
        /// </value>
        public float WaterFogDensityOffset {
            get => GenericMarshal.StringTo<float>(GetFieldValue("waterFogDensityOffset"));
            set => SetFieldValue("waterFogDensityOffset", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The depth in world units at which full darkening will be received, giving a wet look to objects underwater.
        /// </description>
        /// </value>
        public float WetDepth {
            get => GenericMarshal.StringTo<float>(GetFieldValue("wetDepth"));
            set => SetFieldValue("wetDepth", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The refract color intensity scaled at wetDepth.
        /// </description>
        /// </value>
        public float WetDarkening {
            get => GenericMarshal.StringTo<float>(GetFieldValue("wetDarkening"));
            set => SetFieldValue("wetDarkening", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// 1D texture defining the base water color by depth
        /// </description>
        /// </value>
        public string DepthGradientTex {
            get => GenericMarshal.StringTo<string>(GetFieldValue("depthGradientTex"));
            set => SetFieldValue("depthGradientTex", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Depth in world units, the max range of the color gradient texture.
        /// </description>
        /// </value>
        public float DepthGradientMax {
            get => GenericMarshal.StringTo<float>(GetFieldValue("depthGradientMax"));
            set => SetFieldValue("depthGradientMax", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Determines start of distortion effect where water surface intersects the camera near plane.
        /// </description>
        /// </value>
        public float DistortStartDist {
            get => GenericMarshal.StringTo<float>(GetFieldValue("distortStartDist"));
            set => SetFieldValue("distortStartDist", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Max distance that distortion algorithm is performed. The lower, the more distorted the effect.
        /// </description>
        /// </value>
        public float DistortEndDist {
            get => GenericMarshal.StringTo<float>(GetFieldValue("distortEndDist"));
            set => SetFieldValue("distortEndDist", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Determines the scaling down of distortion in shallow water.
        /// </description>
        /// </value>
        public float DistortFullDepth {
            get => GenericMarshal.StringTo<float>(GetFieldValue("distortFullDepth"));
            set => SetFieldValue("distortFullDepth", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Relative opacity or transparency of the water surface.
        /// </description>
        /// </value>
        public float Clarity {
            get => GenericMarshal.StringTo<float>(GetFieldValue("clarity"));
            set => SetFieldValue("clarity", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Changes the color shading of objects beneath the water surface.
        /// </description>
        /// </value>
        public ColorI UnderwaterColor {
            get => GenericMarshal.StringTo<ColorI>(GetFieldValue("underwaterColor"));
            set => SetFieldValue("underwaterColor", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Ambient sound environment when listener is submerged.
        /// </description>
        /// </value>
        public SFXAmbience SoundAmbience {
            get => GenericMarshal.StringTo<SFXAmbience>(GetFieldValue("soundAmbience"));
            set => SetFieldValue("soundAmbience", GenericMarshal.ToString(value));
        }
    }
}