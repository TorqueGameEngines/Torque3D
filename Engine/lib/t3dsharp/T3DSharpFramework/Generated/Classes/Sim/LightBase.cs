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
    /// <summary>This is the base class for light objects.</summary>
    /// <description>
    /// It is *NOT* intended to be used directly in script, but exists to provide the base member variables and generic functionality. You should be using the derived classes PointLight and SpotLight, which can be declared in TorqueScript or added from the World Editor.
    /// 
    /// For this class, we only add basic lighting options that all lighting systems would use. The specific lighting system options are injected at runtime by the lighting system itself.
    /// </description>
    /// <see cref="PointLight" />
    /// <see cref="SpotLight" />
    public unsafe class LightBase : SceneObject {
        public LightBase(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public LightBase(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public LightBase(string pName) 
            : this(pName, false) {
        }
        
        public LightBase(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public LightBase(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public LightBase(SimObject pObj) 
            : base(pObj) {
        }
        
        public LightBase(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct PauseAnimation__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _PauseAnimation(IntPtr _this, PauseAnimation__Args args);
            private static _PauseAnimation _PauseAnimationFunc;
            internal static _PauseAnimation PauseAnimation() {
                if (_PauseAnimationFunc == null) {
                    _PauseAnimationFunc =
                        (_PauseAnimation)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnLightBase_pauseAnimation"), typeof(_PauseAnimation));
                }
                
                return _PauseAnimationFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct PlayAnimation__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string anim;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _PlayAnimation(IntPtr _this, PlayAnimation__Args args);
            private static _PlayAnimation _PlayAnimationFunc;
            internal static _PlayAnimation PlayAnimation() {
                if (_PlayAnimationFunc == null) {
                    _PlayAnimationFunc =
                        (_PlayAnimation)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnLightBase_playAnimation"), typeof(_PlayAnimation));
                }
                
                return _PlayAnimationFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetLightEnabled__Args
            {
                [MarshalAs(UnmanagedType.I1)]
                internal bool state;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetLightEnabled(IntPtr _this, SetLightEnabled__Args args);
            private static _SetLightEnabled _SetLightEnabledFunc;
            internal static _SetLightEnabled SetLightEnabled() {
                if (_SetLightEnabledFunc == null) {
                    _SetLightEnabledFunc =
                        (_SetLightEnabled)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnLightBase_setLightEnabled"), typeof(_SetLightEnabled));
                }
                
                return _SetLightEnabledFunc;
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
                                "fnLightBase_staticGetType"), typeof(_StaticGetType));
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
                                "fnLightBase_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Stops the light animation.
        /// </description>
        public void PauseAnimation() {
             InternalUnsafeMethods.PauseAnimation__Args _args = new InternalUnsafeMethods.PauseAnimation__Args() {
             };
             InternalUnsafeMethods.PauseAnimation()(ObjectPtr, _args);
        }

        /// <description>
        /// ( [LightAnimData anim] )	Plays a light animation on the light.  If no LightAnimData is passed the existing one is played.
        /// </description>
        public void PlayAnimation(string anim = "") {
             InternalUnsafeMethods.PlayAnimation__Args _args = new InternalUnsafeMethods.PlayAnimation__Args() {
                anim = anim,
             };
             InternalUnsafeMethods.PlayAnimation()(ObjectPtr, _args);
        }

        /// <summary>Toggles the light on and off</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="state">Turns the light on (true) or off (false)</param>
        /// <code>
        /// // Disable the light
        /// CrystalLight.setLightEnabled(false);
        /// 
        /// // Renable the light
        /// CrystalLight.setLightEnabled(true);
        /// </code>
        public void SetLightEnabled(bool state) {
             InternalUnsafeMethods.SetLightEnabled__Args _args = new InternalUnsafeMethods.SetLightEnabled__Args() {
                state = state,
             };
             InternalUnsafeMethods.SetLightEnabled()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the LightBase class.
        /// </description>
        /// <returns>The type info object for LightBase</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Enables/Disables the object rendering and functionality in the scene.
        /// </description>
        /// </value>
        public bool IsEnabled {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("isEnabled"));
            set => SetFieldValue("isEnabled", GenericMarshal.ToString(value));
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
        /// Enables/disabled shadow casts by this light.
        /// </description>
        /// </value>
        public bool CastShadows {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("castShadows"));
            set => SetFieldValue("castShadows", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Used for sorting of lights by the light manager. Priority determines if a light has a stronger effect than, those with a lower value
        /// </description>
        /// </value>
        public float Priority {
            get => GenericMarshal.StringTo<float>(GetFieldValue("priority"));
            set => SetFieldValue("priority", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Toggles animation for the light on and off
        /// </description>
        /// </value>
        public bool Animate {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("animate"));
            set => SetFieldValue("animate", GenericMarshal.ToString(value));
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
        /// The length of time in seconds for a single playback of the light animation (must be > 0)
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