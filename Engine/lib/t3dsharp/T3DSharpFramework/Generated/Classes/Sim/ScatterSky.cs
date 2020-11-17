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
    /// <summary>Represents both the sun and sky for scenes with a dynamic time of day.</summary>
    /// <description>
    /// %ScatterSky renders as a dome shaped mesh which is camera relative and always overhead. It is intended to be part of the background of your scene and renders before all other objects types.
    /// 
    /// %ScatterSky is designed for outdoor scenes which need to transition fluidly between radically different times of day. It will respond to time changes originating from a TimeOfDay object or the elevation field can be directly adjusted.
    /// 
    /// During day, %ScatterSky uses atmosphereic sunlight scattering aproximations to generate a sky gradient and sun corona. It also calculates the fog color, ambient color, and sun color, which are used for scene lighting. This is user controlled by fields within the ScatterSky group.
    /// 
    /// During night, %ScatterSky supports can transition to a night sky cubemap and moon sprite. The user can control this and night time colors used for scene lighting with fields within the Night group.
    /// 
    /// A scene with a ScatterSky should not have any other sky or sun objects as it already fulfills both roles.
    /// 
    /// %ScatterSky is intended to be used with CloudLayer and TimeOfDay as part of a scene with dynamic lighting. Having a %ScatterSky without a changing time of day would unnecessarily give up artistic control compared and fillrate compared to a SkyBox + Sun setup.
    /// </description>
    public unsafe class ScatterSky : SceneObject {
        public ScatterSky(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public ScatterSky(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public ScatterSky(string pName) 
            : this(pName, false) {
        }
        
        public ScatterSky(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public ScatterSky(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public ScatterSky(SimObject pObj) 
            : base(pObj) {
        }
        
        public ScatterSky(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct ApplyChanges__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ApplyChanges(IntPtr _this, ApplyChanges__Args args);
            private static _ApplyChanges _ApplyChangesFunc;
            internal static _ApplyChanges ApplyChanges() {
                if (_ApplyChangesFunc == null) {
                    _ApplyChangesFunc =
                        (_ApplyChanges)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnScatterSky_applyChanges"), typeof(_ApplyChanges));
                }
                
                return _ApplyChangesFunc;
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
                                "fnScatterSky_staticGetType"), typeof(_StaticGetType));
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
                                "fnScatterSky_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Apply a full network update of all fields to all clients.
        /// </description>
        public void ApplyChanges() {
             InternalUnsafeMethods.ApplyChanges__Args _args = new InternalUnsafeMethods.ApplyChanges__Args() {
             };
             InternalUnsafeMethods.ApplyChanges()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the ScatterSky class.
        /// </description>
        /// <returns>The type info object for ScatterSky</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Global brightness and intensity applied to the sky and objects in the level.
        /// </description>
        /// </value>
        public float SkyBrightness {
            get => GenericMarshal.StringTo<float>(GetFieldValue("skyBrightness"));
            set => SetFieldValue("skyBrightness", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Affects the size of the sun's disk.
        /// </description>
        /// </value>
        public float SunSize {
            get => GenericMarshal.StringTo<float>(GetFieldValue("sunSize"));
            set => SetFieldValue("sunSize", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Controls how much the alpha component of colorize brigthens the sky. Setting to 0 returns default behavior.
        /// </description>
        /// </value>
        public float ColorizeAmount {
            get => GenericMarshal.StringTo<float>(GetFieldValue("colorizeAmount"));
            set => SetFieldValue("colorizeAmount", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Tints the sky the color specified, the alpha controls the brigthness. The brightness is multipled by the value of colorizeAmt.
        /// </description>
        /// </value>
        public LinearColorF Colorize {
            get => GenericMarshal.StringTo<LinearColorF>(GetFieldValue("colorize"));
            set => SetFieldValue("colorize", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Controls how blue the atmosphere is during the day.
        /// </description>
        /// </value>
        public float RayleighScattering {
            get => GenericMarshal.StringTo<float>(GetFieldValue("rayleighScattering"));
            set => SetFieldValue("rayleighScattering", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Modulates the directional color of sunlight.
        /// </description>
        /// </value>
        public LinearColorF SunScale {
            get => GenericMarshal.StringTo<LinearColorF>(GetFieldValue("sunScale"));
            set => SetFieldValue("sunScale", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Modulates the ambient color of sunlight.
        /// </description>
        /// </value>
        public LinearColorF AmbientScale {
            get => GenericMarshal.StringTo<LinearColorF>(GetFieldValue("ambientScale"));
            set => SetFieldValue("ambientScale", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Modulates the fog color. Note that this overrides the LevelInfo.fogColor property, so you should not use LevelInfo.fogColor if the level contains a ScatterSky object.
        /// </description>
        /// </value>
        public LinearColorF FogScale {
            get => GenericMarshal.StringTo<LinearColorF>(GetFieldValue("fogScale"));
            set => SetFieldValue("fogScale", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Controls the contrast of the sky and sun during daytime.
        /// </description>
        /// </value>
        public float Exposure {
            get => GenericMarshal.StringTo<float>(GetFieldValue("exposure"));
            set => SetFieldValue("exposure", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Offsets the scatterSky to avoid canvas rendering. Use 5000 or greater for the initial adjustment
        /// </description>
        /// </value>
        public float ZOffset {
            get => GenericMarshal.StringTo<float>(GetFieldValue("zOffset"));
            set => SetFieldValue("zOffset", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The horizontal angle of the sun measured clockwise from the positive Y world axis. This field is networked.
        /// </description>
        /// </value>
        public float Azimuth {
            get => GenericMarshal.StringTo<float>(GetFieldValue("azimuth"));
            set => SetFieldValue("azimuth", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The elevation angle of the sun above or below the horizon. This field is networked.
        /// </description>
        /// </value>
        public float Elevation {
            get => GenericMarshal.StringTo<float>(GetFieldValue("elevation"));
            set => SetFieldValue("elevation", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The horizontal angle of the moon measured clockwise from the positive Y world axis. This is not animated by time or networked.
        /// </description>
        /// </value>
        public float MoonAzimuth {
            get => GenericMarshal.StringTo<float>(GetFieldValue("moonAzimuth"));
            set => SetFieldValue("moonAzimuth", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The elevation angle of the moon above or below the horizon. This is not animated by time or networked.
        /// </description>
        /// </value>
        public float MoonElevation {
            get => GenericMarshal.StringTo<float>(GetFieldValue("moonElevation"));
            set => SetFieldValue("moonElevation", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Enables/disables shadows cast by objects due to ScatterSky light.
        /// </description>
        /// </value>
        public bool CastShadows {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("castShadows"));
            set => SetFieldValue("castShadows", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// static shadow refresh rate (milliseconds)
        /// </description>
        /// </value>
        public int StaticRefreshFreq {
            get => GenericMarshal.StringTo<int>(GetFieldValue("staticRefreshFreq"));
            set => SetFieldValue("staticRefreshFreq", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// dynamic shadow refresh rate (milliseconds)
        /// </description>
        /// </value>
        public int DynamicRefreshFreq {
            get => GenericMarshal.StringTo<int>(GetFieldValue("dynamicRefreshFreq"));
            set => SetFieldValue("dynamicRefreshFreq", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The brightness of the ScatterSky's light object.
        /// </description>
        /// </value>
        public float Brightness {
            get => GenericMarshal.StringTo<float>(GetFieldValue("brightness"));
            set => SetFieldValue("brightness", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Datablock for the flare produced by the ScatterSky.
        /// </description>
        /// </value>
        public LightFlareData FlareType {
            get => GenericMarshal.StringTo<LightFlareData>(GetFieldValue("flareType"));
            set => SetFieldValue("flareType", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Changes the size and intensity of the flare.
        /// </description>
        /// </value>
        public float FlareScale {
            get => GenericMarshal.StringTo<float>(GetFieldValue("flareScale"));
            set => SetFieldValue("flareScale", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The ambient color during night. Also used for the sky color if useNightCubemap is false.
        /// </description>
        /// </value>
        public LinearColorF NightColor {
            get => GenericMarshal.StringTo<LinearColorF>(GetFieldValue("nightColor"));
            set => SetFieldValue("nightColor", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The fog color during night.
        /// </description>
        /// </value>
        public LinearColorF NightFogColor {
            get => GenericMarshal.StringTo<LinearColorF>(GetFieldValue("nightFogColor"));
            set => SetFieldValue("nightFogColor", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Enable or disable rendering of the moon sprite during night.
        /// </description>
        /// </value>
        public bool MoonEnabled {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("moonEnabled"));
            set => SetFieldValue("moonEnabled", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Material for the moon sprite.
        /// </description>
        /// </value>
        public string MoonMat {
            get => GenericMarshal.StringTo<string>(GetFieldValue("moonMat"));
            set => SetFieldValue("moonMat", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Controls size the moon sprite renders, specified as a fractional amount of the screen height.
        /// </description>
        /// </value>
        public float MoonScale {
            get => GenericMarshal.StringTo<float>(GetFieldValue("moonScale"));
            set => SetFieldValue("moonScale", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Color of light cast by the directional light during night.
        /// </description>
        /// </value>
        public LinearColorF MoonLightColor {
            get => GenericMarshal.StringTo<LinearColorF>(GetFieldValue("moonLightColor"));
            set => SetFieldValue("moonLightColor", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Transition to the nightCubemap during night. If false we use nightColor.
        /// </description>
        /// </value>
        public bool UseNightCubemap {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("useNightCubemap"));
            set => SetFieldValue("useNightCubemap", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Cubemap visible during night.
        /// </description>
        /// </value>
        public string NightCubemap {
            get => GenericMarshal.StringTo<string>(GetFieldValue("nightCubemap"));
            set => SetFieldValue("nightCubemap", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The proportions of constant, linear, and quadratic attenuation to use for the falloff for point and spot lights.
        /// </description>
        /// </value>
        public Point3F AttenuationRatio {
            get => GenericMarshal.StringTo<Point3F>(GetFieldValue("attenuationRatio"));
            set => SetFieldValue("attenuationRatio", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The type of shadow to use on this light.
        /// </description>
        /// </value>
        public ShadowType ShadowType {
            get => GenericMarshal.StringTo<ShadowType>(GetFieldValue("shadowType"));
            set => SetFieldValue("shadowType", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// A custom pattern texture which is projected from the light.
        /// </description>
        /// </value>
        public string Cookie {
            get => GenericMarshal.StringTo<string>(GetFieldValue("cookie"));
            set => SetFieldValue("cookie", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The texture size of the shadow map.
        /// </description>
        /// </value>
        public int TexSize {
            get => GenericMarshal.StringTo<int>(GetFieldValue("texSize"));
            set => SetFieldValue("texSize", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The ESM shadow darkening factor
        /// </description>
        /// </value>
        public Point4F OverDarkFactor {
            get => GenericMarshal.StringTo<Point4F>(GetFieldValue("overDarkFactor"));
            set => SetFieldValue("overDarkFactor", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The distance from the camera to extend the PSSM shadow.
        /// </description>
        /// </value>
        public float ShadowDistance {
            get => GenericMarshal.StringTo<float>(GetFieldValue("shadowDistance"));
            set => SetFieldValue("shadowDistance", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public float ShadowSoftness {
            get => GenericMarshal.StringTo<float>(GetFieldValue("shadowSoftness"));
            set => SetFieldValue("shadowSoftness", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The logrithmic PSSM split distance factor.
        /// </description>
        /// </value>
        public int NumSplits {
            get => GenericMarshal.StringTo<int>(GetFieldValue("numSplits"));
            set => SetFieldValue("numSplits", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The logrithmic PSSM split distance factor.
        /// </description>
        /// </value>
        public float LogWeight {
            get => GenericMarshal.StringTo<float>(GetFieldValue("logWeight"));
            set => SetFieldValue("logWeight", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Start fading shadows out at this distance.  0 = auto calculate this distance.
        /// </description>
        /// </value>
        public float FadeStartDistance {
            get => GenericMarshal.StringTo<float>(GetFieldValue("fadeStartDistance"));
            set => SetFieldValue("fadeStartDistance", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// This toggles only terrain being rendered to the last split of a PSSM shadow map.
        /// </description>
        /// </value>
        public bool LastSplitTerrainOnly {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("lastSplitTerrainOnly"));
            set => SetFieldValue("lastSplitTerrainOnly", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// This light is represented in lightmaps (static light, default: false)
        /// </description>
        /// </value>
        public bool RepresentedInLightmap {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("representedInLightmap"));
            set => SetFieldValue("representedInLightmap", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The color that should be used to multiply-blend dynamic shadows onto lightmapped geometry (ignored if 'representedInLightmap' is false)
        /// </description>
        /// </value>
        public LinearColorF ShadowDarkenColor {
            get => GenericMarshal.StringTo<LinearColorF>(GetFieldValue("shadowDarkenColor"));
            set => SetFieldValue("shadowDarkenColor", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// This light should render lightmapped geometry during its shadow-map update (ignored if 'representedInLightmap' is false)
        /// </description>
        /// </value>
        public bool IncludeLightmappedGeometryInShadow {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("includeLightmappedGeometryInShadow"));
            set => SetFieldValue("includeLightmappedGeometryInShadow", GenericMarshal.ToString(value));
        }
    }
}