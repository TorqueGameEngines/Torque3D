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
    /// <summary>A global light affecting your entire scene and optionally renders a corona effect.</summary>
    /// <description>
    /// Sun is both the directional and ambient light for your entire scene.
    /// </description>
    public unsafe class Sun : SceneObject {
        public Sun(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public Sun(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public Sun(string pName) 
            : this(pName, false) {
        }
        
        public Sun(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public Sun(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public Sun(SimObject pObj) 
            : base(pObj) {
        }
        
        public Sun(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct Animate__Args
            {
                internal float duration;
                internal float startAzimuth;
                internal float endAzimuth;
                internal float startElevation;
                internal float endElevation;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Animate(IntPtr _this, Animate__Args args);
            private static _Animate _AnimateFunc;
            internal static _Animate Animate() {
                if (_AnimateFunc == null) {
                    _AnimateFunc =
                        (_Animate)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSun_animate"), typeof(_Animate));
                }
                
                return _AnimateFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Apply__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Apply(IntPtr _this, Apply__Args args);
            private static _Apply _ApplyFunc;
            internal static _Apply Apply() {
                if (_ApplyFunc == null) {
                    _ApplyFunc =
                        (_Apply)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSun_apply"), typeof(_Apply));
                }
                
                return _ApplyFunc;
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
                                "fnSun_staticGetType"), typeof(_StaticGetType));
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
                                "fnSun_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// animate( F32 duration, F32 startAzimuth, F32 endAzimuth, F32 startElevation, F32 endElevation )
        /// </description>
        public void Animate(float duration, float startAzimuth, float endAzimuth, float startElevation, float endElevation) {
             InternalUnsafeMethods.Animate__Args _args = new InternalUnsafeMethods.Animate__Args() {
                duration = duration,
                startAzimuth = startAzimuth,
                endAzimuth = endAzimuth,
                startElevation = startElevation,
                endElevation = endElevation,
             };
             InternalUnsafeMethods.Animate()(ObjectPtr, _args);
        }

        /// 
        public void Apply() {
             InternalUnsafeMethods.Apply__Args _args = new InternalUnsafeMethods.Apply__Args() {
             };
             InternalUnsafeMethods.Apply()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the Sun class.
        /// </description>
        /// <returns>The type info object for Sun</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// The horizontal angle of the sun measured clockwise from the positive Y world axis.
        /// </description>
        /// </value>
        public float Azimuth {
            get => GenericMarshal.StringTo<float>(GetFieldValue("azimuth"));
            set => SetFieldValue("azimuth", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The elevation angle of the sun above or below the horizon.
        /// </description>
        /// </value>
        public float Elevation {
            get => GenericMarshal.StringTo<float>(GetFieldValue("elevation"));
            set => SetFieldValue("elevation", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Color shading applied to surfaces in direct contact with light source.
        /// </description>
        /// </value>
        public LinearColorF Color {
            get => GenericMarshal.StringTo<LinearColorF>(GetFieldValue("color"));
            set => SetFieldValue("color", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Color shading applied to surfaces not in direct contact with light source, such as in the shadows or interiors.
        /// </description>
        /// </value>
        public LinearColorF Ambient {
            get => GenericMarshal.StringTo<LinearColorF>(GetFieldValue("ambient"));
            set => SetFieldValue("ambient", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Adjust the Sun's global contrast/intensity
        /// </description>
        /// </value>
        public float Brightness {
            get => GenericMarshal.StringTo<float>(GetFieldValue("brightness"));
            set => SetFieldValue("brightness", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Enables/disables shadows cast by objects due to Sun light
        /// </description>
        /// </value>
        public bool CastShadows {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("castShadows"));
            set => SetFieldValue("castShadows", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Enable or disable rendering of the corona sprite.
        /// </description>
        /// </value>
        public bool CoronaEnabled {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("coronaEnabled"));
            set => SetFieldValue("coronaEnabled", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Texture for the corona sprite.
        /// </description>
        /// </value>
        public string CoronaMaterial {
            get => GenericMarshal.StringTo<string>(GetFieldValue("coronaMaterial"));
            set => SetFieldValue("coronaMaterial", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Controls size the corona sprite renders, specified as a fractional amount of the screen height.
        /// </description>
        /// </value>
        public float CoronaScale {
            get => GenericMarshal.StringTo<float>(GetFieldValue("coronaScale"));
            set => SetFieldValue("coronaScale", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Modulates the corona sprite color ( if coronaUseLightColor is false ).
        /// </description>
        /// </value>
        public LinearColorF CoronaTint {
            get => GenericMarshal.StringTo<LinearColorF>(GetFieldValue("coronaTint"));
            set => SetFieldValue("coronaTint", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Modulate the corona sprite color by the color of the light ( overrides coronaTint ).
        /// </description>
        /// </value>
        public bool CoronaUseLightColor {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("coronaUseLightColor"));
            set => SetFieldValue("coronaUseLightColor", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Datablock for the flare produced by the Sun
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