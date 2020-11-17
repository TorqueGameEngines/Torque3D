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
    /// <summary>A helper datablock used by classes (such as shapebase) that submit lights to the scene but do not use actual "LightBase" objects.</summary>
    /// <description>
    /// This datablock stores the properties of that light as fields that can be initialized from script.
    /// </description>
    /// <code>
    /// // Declare a light description to be used on a rocket launcher projectile
    /// datablock LightDescription(RocketLauncherLightDesc)
    /// {
    ///    range = 4.0;
    ///    color = "1 1 0";
    ///    brightness = 5.0;
    ///    animationType = PulseLightAnim;
    ///    animationPeriod = 0.25;
    /// };
    /// 
    /// // Declare a ProjectileDatablock which uses the light description
    /// datablock ProjectileData(RocketLauncherProjectile)
    /// {
    ///    lightDesc = RocketLauncherLightDesc;
    /// 
    ///    projectileShapeName = "art/shapes/weapons/SwarmGun/rocket.dts";
    /// 
    ///    directDamage = 30;
    ///    radiusDamage = 30;
    ///    damageRadius = 5;
    ///    areaImpulse = 2500;
    /// 
    ///    // ... remaining ProjectileData fields not listed for this example
    /// };
    /// </code>
    /// <see cref="LightBase" />
    public unsafe class LightDescription : SimDataBlock {
        public LightDescription(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public LightDescription(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public LightDescription(string pName) 
            : this(pName, false) {
        }
        
        public LightDescription(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public LightDescription(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public LightDescription(SimObject pObj) 
            : base(pObj) {
        }
        
        public LightDescription(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
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
                                "fnLightDescription_apply"), typeof(_Apply));
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
                                "fnLightDescription_staticGetType"), typeof(_StaticGetType));
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
                                "fnLightDescription_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <summary>Force an inspectPostApply call for the benefit of tweaking via the console</summary>
        /// <description>
        /// Normally this functionality is only exposed to objects via the World Editor, once changes have been made. Exposing apply to script allows you to make changes to it on the fly without the World Editor.
        /// </description>
        /// <remarks> This is intended for debugging and tweaking, not for game play
        /// 
        /// </remarks>
        /// <code>
        /// // Change a property of the light description
        /// RocketLauncherLightDesc.brightness = 10;
        /// 
        /// // Make it so
        /// RocketLauncherLightDesc.apply();
        /// </code>
        public void Apply() {
             InternalUnsafeMethods.Apply__Args _args = new InternalUnsafeMethods.Apply__Args() {
             };
             InternalUnsafeMethods.Apply()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the LightDescription class.
        /// </description>
        /// <returns>The type info object for LightDescription</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Changes the base color hue of the light.
        /// </description>
        /// </value>
        public LinearColorF Color {
            get => GenericMarshal.StringTo<LinearColorF>(GetFieldValue("color"));
            set => SetFieldValue("color", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Adjusts the lights power, 0 being off completely.
        /// </description>
        /// </value>
        public float Brightness {
            get => GenericMarshal.StringTo<float>(GetFieldValue("brightness"));
            set => SetFieldValue("brightness", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Controls the size (radius) of the light
        /// </description>
        /// </value>
        public float Range {
            get => GenericMarshal.StringTo<float>(GetFieldValue("range"));
            set => SetFieldValue("range", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Enables/disabled shadow casts by this light.
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
        /// Datablock containing light animation information (LightAnimData)
        /// </description>
        /// </value>
        public LightAnimData AnimationType {
            get => GenericMarshal.StringTo<LightAnimData>(GetFieldValue("animationType"));
            set => SetFieldValue("animationType", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The length of time in seconds for a single playback of the light animation
        /// </description>
        /// </value>
        public float AnimationPeriod {
            get => GenericMarshal.StringTo<float>(GetFieldValue("animationPeriod"));
            set => SetFieldValue("animationPeriod", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The phase used to offset the animation start time to vary the animation of nearby lights.
        /// </description>
        /// </value>
        public float AnimationPhase {
            get => GenericMarshal.StringTo<float>(GetFieldValue("animationPhase"));
            set => SetFieldValue("animationPhase", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Datablock containing light flare information (LightFlareData)
        /// </description>
        /// </value>
        public LightFlareData FlareType {
            get => GenericMarshal.StringTo<LightFlareData>(GetFieldValue("flareType"));
            set => SetFieldValue("flareType", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Globally scales all features of the light flare
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