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
    /// <summary>Defines a precipitation based storm (rain, snow, etc).</summary>
    /// <description>
    /// The Precipitation effect works by creating many 'drops' within a fixed size box. This box can be configured to move around with the camera (to simulate level-wide precipitation), or to remain in a fixed position (to simulate localized precipitation). When #followCam is true, the box containing the droplets can be thought of as centered on the camera then pushed slightly forward in the direction the camera is facing so most of the box is in front of the camera (allowing more drops to be visible on screen at once).
    /// 
    /// The effect can also be configured to create a small 'splash' whenever a drop hits another world object.
    /// </description>
    /// <code>
    /// // The following is added to a level file (.mis) by the World Editor
    /// new Precipitation( TheRain )
    /// {
    ///    dropSize = "0.5";
    ///    splashSize = "0.5";
    ///    splashMS = "250";
    ///    animateSplashes = "1";
    ///    dropAnimateMS = "0";
    ///    fadeDist = "0";
    ///    fadeDistEnd = "0";
    ///    useTrueBillboards = "0";
    ///    useLighting = "0";
    ///    glowIntensity = "0 0 0 0";
    ///    reflect = "0";
    ///    rotateWithCamVel = "1";
    ///    doCollision = "1";
    ///    hitPlayers = "0";
    ///    hitVehicles = "0";
    ///    followCam = "1";
    ///    useWind = "0";
    ///    minSpeed = "1.5";
    ///    maxSpeed = "2";
    ///    minMass = "0.75";
    ///    maxMass = "0.85";
    ///    useTurbulence = "0";
    ///    maxTurbulence = "0.1";
    ///    turbulenceSpeed = "0.2";
    ///    numDrops = "1024";
    ///    boxWidth = "200";
    ///    boxHeight = "100";
    ///    dataBlock = "HeavyRain";
    /// };
    /// </code>
    /// <see cref="PrecipitationData" />
    public unsafe class Precipitation : GameBase {
        public Precipitation(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public Precipitation(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public Precipitation(string pName) 
            : this(pName, false) {
        }
        
        public Precipitation(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public Precipitation(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public Precipitation(SimObject pObj) 
            : base(pObj) {
        }
        
        public Precipitation(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct SetTurbulence__Args
            {
                internal float max;
                internal float speed;
                internal float seconds;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetTurbulence(IntPtr _this, SetTurbulence__Args args);
            private static _SetTurbulence _SetTurbulenceFunc;
            internal static _SetTurbulence SetTurbulence() {
                if (_SetTurbulenceFunc == null) {
                    _SetTurbulenceFunc =
                        (_SetTurbulence)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnPrecipitation_setTurbulence"), typeof(_SetTurbulence));
                }
                
                return _SetTurbulenceFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ModifyStorm__Args
            {
                internal float percentage;
                internal float seconds;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ModifyStorm(IntPtr _this, ModifyStorm__Args args);
            private static _ModifyStorm _ModifyStormFunc;
            internal static _ModifyStorm ModifyStorm() {
                if (_ModifyStormFunc == null) {
                    _ModifyStormFunc =
                        (_ModifyStorm)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnPrecipitation_modifyStorm"), typeof(_ModifyStorm));
                }
                
                return _ModifyStormFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetPercentage__Args
            {
                internal float percentage;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetPercentage(IntPtr _this, SetPercentage__Args args);
            private static _SetPercentage _SetPercentageFunc;
            internal static _SetPercentage SetPercentage() {
                if (_SetPercentageFunc == null) {
                    _SetPercentageFunc =
                        (_SetPercentage)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnPrecipitation_setPercentage"), typeof(_SetPercentage));
                }
                
                return _SetPercentageFunc;
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
                                "fnPrecipitation_staticGetType"), typeof(_StaticGetType));
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
                                "fnPrecipitation_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Smoothly change the turbulence parameters over a period of time.
        /// </description>
        /// <param name="max">New #maxTurbulence value. Set to 0 to disable turbulence.</param>
        /// <param name="speed">New #turbulenceSpeed value.</param>
        /// <param name="seconds">Length of time (in seconds) over which to interpolate the turbulence settings. Set to 0 to change instantly.</param>
        /// <code>
        /// %turbulence = 0.5;     // Set the new turbulence value. Set to 0 to disable turbulence.
        /// %speed = 5.0;          // The new speed of the turbulance effect.
        /// %seconds = 5.0;        // The length of time over which to make the change.
        /// %precipitation.setTurbulence( %turbulence, %speed, %seconds );
        /// </code>
        public void SetTurbulence(float max = 1f, float speed = 5f, float seconds = 5f) {
             InternalUnsafeMethods.SetTurbulence__Args _args = new InternalUnsafeMethods.SetTurbulence__Args() {
                max = max,
                speed = speed,
                seconds = seconds,
             };
             InternalUnsafeMethods.SetTurbulence()(ObjectPtr, _args);
        }

        /// <description>
        /// Smoothly change the maximum number of drops in the effect (from current value to #numDrops *<paramref name="" /> percentage).
        /// This method can be used to simulate a storm building or fading in intensity as the number of drops in the Precipitation box changes.
        /// 
        /// </description>
        /// <param name="percentage">New maximum number of drops value (as a percentage of #numDrops). Valid range is 0-1.</param>
        /// <param name="seconds">Length of time (in seconds) over which to increase the drops percentage value. Set to 0 to change instantly.</param>
        /// <code>
        /// %percentage = 0.5;  // The percentage, from 0 to 1, of the maximum drops to display
        /// %seconds = 5.0;     // The length of time over which to make the change.
        /// %precipitation.modifyStorm( %percentage, %seconds );
        /// </code>
        public void ModifyStorm(float percentage = 1f, float seconds = 5f) {
             InternalUnsafeMethods.ModifyStorm__Args _args = new InternalUnsafeMethods.ModifyStorm__Args() {
                percentage = percentage,
                seconds = seconds,
             };
             InternalUnsafeMethods.ModifyStorm()(ObjectPtr, _args);
        }

        /// <description>
        /// Sets the maximum number of drops in the effect, as a percentage of #numDrops.
        /// The change occurs instantly (use modifyStorm() to change the number of drops over a period of time.
        /// </description>
        /// <param name="percentage">New maximum number of drops value (as a percentage of #numDrops). Valid range is 0-1.</param>
        /// <code>
        /// %percentage = 0.5;  // The percentage, from 0 to 1, of the maximum drops to display
        /// %precipitation.setPercentage( %percentage );
        /// </code>
        /// <see cref="modifyStorm" />
        public void SetPercentage(float percentage = 1f) {
             InternalUnsafeMethods.SetPercentage__Args _args = new InternalUnsafeMethods.SetPercentage__Args() {
                percentage = percentage,
             };
             InternalUnsafeMethods.SetPercentage()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the Precipitation class.
        /// </description>
        /// <returns>The type info object for Precipitation</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <summary>Maximum number of drops allowed to exist in the precipitation box at any one time.</summary>
        /// <description>
        /// The actual number of drops in the effect depends on the current percentage, which can change over time using modifyStorm().
        /// </description>
        /// </value>
        public int NumDrops {
            get => GenericMarshal.StringTo<int>(GetFieldValue("numDrops"));
            set => SetFieldValue("numDrops", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Width and depth (horizontal dimensions) of the precipitation box.
        /// </description>
        /// </value>
        public float BoxWidth {
            get => GenericMarshal.StringTo<float>(GetFieldValue("boxWidth"));
            set => SetFieldValue("boxWidth", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Height (vertical dimension) of the precipitation box.
        /// </description>
        /// </value>
        public float BoxHeight {
            get => GenericMarshal.StringTo<float>(GetFieldValue("boxHeight"));
            set => SetFieldValue("boxHeight", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Size of each drop of precipitation. This will scale the texture.
        /// </description>
        /// </value>
        public float DropSize {
            get => GenericMarshal.StringTo<float>(GetFieldValue("dropSize"));
            set => SetFieldValue("dropSize", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Size of each splash animation when a drop collides with another surface.
        /// </description>
        /// </value>
        public float SplashSize {
            get => GenericMarshal.StringTo<float>(GetFieldValue("splashSize"));
            set => SetFieldValue("splashSize", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Lifetime of splashes in milliseconds.
        /// </description>
        /// </value>
        public int SplashMS {
            get => GenericMarshal.StringTo<int>(GetFieldValue("splashMS"));
            set => SetFieldValue("splashMS", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Set to true to enable splash animations when drops collide with other surfaces.
        /// </description>
        /// </value>
        public bool AnimateSplashes {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("animateSplashes"));
            set => SetFieldValue("animateSplashes", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Length (in milliseconds) to display each drop frame.</summary>
        /// <description>
        /// If #dropAnimateMS <= 0, drops select a single random frame at creation that does not change throughout the drop's lifetime. If #dropAnimateMS > 0, each drop cycles through the the available frames in the drop texture at the given rate.
        /// </description>
        /// </value>
        public int DropAnimateMS {
            get => GenericMarshal.StringTo<int>(GetFieldValue("dropAnimateMS"));
            set => SetFieldValue("dropAnimateMS", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The distance at which drops begin to fade out.
        /// </description>
        /// </value>
        public float FadeDist {
            get => GenericMarshal.StringTo<float>(GetFieldValue("fadeDist"));
            set => SetFieldValue("fadeDist", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The distance at which drops are completely faded out.
        /// </description>
        /// </value>
        public float FadeDistEnd {
            get => GenericMarshal.StringTo<float>(GetFieldValue("fadeDistEnd"));
            set => SetFieldValue("fadeDistEnd", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Set to true to make drops true (non axis-aligned) billboards.
        /// </description>
        /// </value>
        public bool UseTrueBillboards {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("useTrueBillboards"));
            set => SetFieldValue("useTrueBillboards", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Set to true to enable shading of the drops and splashes by the sun color.
        /// </description>
        /// </value>
        public bool UseLighting {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("useLighting"));
            set => SetFieldValue("useLighting", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Set to 0 to disable the glow or or use it to control the intensity of each channel.
        /// </description>
        /// </value>
        public LinearColorF GlowIntensity {
            get => GenericMarshal.StringTo<LinearColorF>(GetFieldValue("glowIntensity"));
            set => SetFieldValue("glowIntensity", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>This enables precipitation rendering during reflection passes.</summary>
        /// <description>
        /// 
        /// </description>
        /// <remarks> This is expensive.</remarks>
        /// </value>
        public bool Reflect {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("reflect"));
            set => SetFieldValue("reflect", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Set to true to include the camera velocity when calculating drop rotation speed.
        /// </description>
        /// </value>
        public bool RotateWithCamVel {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("rotateWithCamVel"));
            set => SetFieldValue("rotateWithCamVel", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Allow drops to collide with world objects.</summary>
        /// <description>
        /// If #animateSplashes is true, drops that collide with another object will produce a simple splash animation.
        /// </description>
        /// <remarks> This can be expensive as each drop will perform a raycast when it is created to determine where it will hit.</remarks>
        /// </value>
        public bool DoCollision {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("doCollision"));
            set => SetFieldValue("doCollision", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Allow drops to collide with Player objects; only valid if #doCollision is true.
        /// </description>
        /// </value>
        public bool HitPlayers {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("hitPlayers"));
            set => SetFieldValue("hitPlayers", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Allow drops to collide with Vehicle objects; only valid if #doCollision is true.
        /// </description>
        /// </value>
        public bool HitVehicles {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("hitVehicles"));
            set => SetFieldValue("hitVehicles", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Controls whether the Precipitation system follows the camera or remains where it is first placed in the scene.</summary>
        /// <description>
        /// Set to true to make it seem like it is raining everywhere in the level (ie. the Player will always be in the rain). Set to false to have a single area affected by rain (ie. the Player can move in and out of the rainy area).
        /// </description>
        /// </value>
        public bool FollowCam {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("followCam"));
            set => SetFieldValue("followCam", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Controls whether drops are affected by wind.
        /// </description>
        /// <see cref="ForestWindEmitter" />
        /// </value>
        public bool UseWind {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("useWind"));
            set => SetFieldValue("useWind", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Minimum speed at which a drop will fall.</summary>
        /// <description>
        /// On creation, the drop will be assigned a random speed between #minSpeed and #maxSpeed.
        /// </description>
        /// </value>
        public float MinSpeed {
            get => GenericMarshal.StringTo<float>(GetFieldValue("minSpeed"));
            set => SetFieldValue("minSpeed", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Maximum speed at which a drop will fall.</summary>
        /// <description>
        /// On creation, the drop will be assigned a random speed between #minSpeed and #maxSpeed.
        /// </description>
        /// </value>
        public float MaxSpeed {
            get => GenericMarshal.StringTo<float>(GetFieldValue("maxSpeed"));
            set => SetFieldValue("maxSpeed", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Minimum mass of a drop.</summary>
        /// <description>
        /// Drop mass determines how strongly the drop is affected by wind and turbulence. On creation, the drop will be assigned a random speed between #minMass and #minMass.
        /// </description>
        /// </value>
        public float MinMass {
            get => GenericMarshal.StringTo<float>(GetFieldValue("minMass"));
            set => SetFieldValue("minMass", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Maximum mass of a drop.</summary>
        /// <description>
        /// Drop mass determines how strongly the drop is affected by wind and turbulence. On creation, the drop will be assigned a random speed between #minMass and #minMass.
        /// </description>
        /// </value>
        public float MaxMass {
            get => GenericMarshal.StringTo<float>(GetFieldValue("maxMass"));
            set => SetFieldValue("maxMass", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Check to enable turbulence. This causes precipitation drops to spiral while falling.
        /// </description>
        /// </value>
        public bool UseTurbulence {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("useTurbulence"));
            set => SetFieldValue("useTurbulence", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Radius at which precipitation drops spiral when turbulence is enabled.
        /// </description>
        /// </value>
        public float MaxTurbulence {
            get => GenericMarshal.StringTo<float>(GetFieldValue("maxTurbulence"));
            set => SetFieldValue("maxTurbulence", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Speed at which precipitation drops spiral when turbulence is enabled.
        /// </description>
        /// </value>
        public float TurbulenceSpeed {
            get => GenericMarshal.StringTo<float>(GetFieldValue("turbulenceSpeed"));
            set => SetFieldValue("turbulenceSpeed", GenericMarshal.ToString(value));
        }
    }
}