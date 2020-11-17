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
    /// <summary>Stores and controls the rendering and status information for a game level.</summary>
    /// <description>
    /// 
    /// </description>
    /// <code>
    /// new LevelInfo(theLevelInfo)
    /// {
    ///   visibleDistance = "1000";
    ///   fogColor = "0.6 0.6 0.7 1";
    ///   fogDensity = "0";
    ///   fogDensityOffset = "700";
    ///   fogAtmosphereHeight = "0";
    ///   canvasClearColor = "0 0 0 255";
    ///   canSaveDynamicFields = "1";
    ///   levelName = "Blank Room";
    ///   desc0 = "A blank room ready to be populated with Torque objects.";
    ///   Enabled = "1";
    /// };
    /// </code>
    public unsafe class LevelInfo : NetObject {
        public LevelInfo(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public LevelInfo(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public LevelInfo(string pName) 
            : this(pName, false) {
        }
        
        public LevelInfo(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public LevelInfo(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public LevelInfo(SimObject pObj) 
            : base(pObj) {
        }
        
        public LevelInfo(IntPtr pObj) 
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
                                "fnLevelInfo_staticGetType"), typeof(_StaticGetType));
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
                                "fnLevelInfo_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the LevelInfo class.
        /// </description>
        /// <returns>The type info object for LevelInfo</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Closest distance from the camera's position to render the world.
        /// </description>
        /// </value>
        public float NearClip {
            get => GenericMarshal.StringTo<float>(GetFieldValue("nearClip"));
            set => SetFieldValue("nearClip", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Furthest distance from the camera's position to render the world.
        /// </description>
        /// </value>
        public float VisibleDistance {
            get => GenericMarshal.StringTo<float>(GetFieldValue("visibleDistance"));
            set => SetFieldValue("visibleDistance", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Furthest distance from the camera's position to render players. Defaults to visibleDistance.
        /// </description>
        /// </value>
        public float VisibleGhostDistance {
            get => GenericMarshal.StringTo<float>(GetFieldValue("visibleGhostDistance"));
            set => SetFieldValue("visibleGhostDistance", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// NearPlane bias used when rendering Decal and DecalRoad. This should be tuned to the visibleDistance in your level.
        /// </description>
        /// </value>
        public float DecalBias {
            get => GenericMarshal.StringTo<float>(GetFieldValue("decalBias"));
            set => SetFieldValue("decalBias", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The default color for the scene fog.
        /// </description>
        /// </value>
        public LinearColorF FogColor {
            get => GenericMarshal.StringTo<LinearColorF>(GetFieldValue("fogColor"));
            set => SetFieldValue("fogColor", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The 0 to 1 density value for the exponential fog falloff.
        /// </description>
        /// </value>
        public float FogDensity {
            get => GenericMarshal.StringTo<float>(GetFieldValue("fogDensity"));
            set => SetFieldValue("fogDensity", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// An offset from the camera in meters for moving the start of the fog effect.
        /// </description>
        /// </value>
        public float FogDensityOffset {
            get => GenericMarshal.StringTo<float>(GetFieldValue("fogDensityOffset"));
            set => SetFieldValue("fogDensityOffset", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// A height in meters for altitude fog falloff.
        /// </description>
        /// </value>
        public float FogAtmosphereHeight {
            get => GenericMarshal.StringTo<float>(GetFieldValue("fogAtmosphereHeight"));
            set => SetFieldValue("fogAtmosphereHeight", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The color used to clear the background before the scene or any GUIs are rendered.
        /// </description>
        /// </value>
        public ColorI CanvasClearColor {
            get => GenericMarshal.StringTo<ColorI>(GetFieldValue("canvasClearColor"));
            set => SetFieldValue("canvasClearColor", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Number of seconds it takes to blend from one ambient light color to a different one.
        /// </description>
        /// </value>
        public float AmbientLightBlendPhase {
            get => GenericMarshal.StringTo<float>(GetFieldValue("ambientLightBlendPhase"));
            set => SetFieldValue("ambientLightBlendPhase", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Interpolation curve to use for blending from one ambient light color to a different one.
        /// </description>
        /// </value>
        public EaseF AmbientLightBlendCurve {
            get => GenericMarshal.StringTo<EaseF>(GetFieldValue("ambientLightBlendCurve"));
            set => SetFieldValue("ambientLightBlendCurve", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Accumulation texture.
        /// </description>
        /// </value>
        public string AccuTexture {
            get => GenericMarshal.StringTo<string>(GetFieldValue("AccuTexture"));
            set => SetFieldValue("AccuTexture", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The global ambient sound environment.
        /// </description>
        /// </value>
        public SFXAmbience SoundAmbience {
            get => GenericMarshal.StringTo<SFXAmbience>(GetFieldValue("soundAmbience"));
            set => SetFieldValue("soundAmbience", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The distance attenuation model to use.
        /// </description>
        /// </value>
        public SFXDistanceModel SoundDistanceModel {
            get => GenericMarshal.StringTo<SFXDistanceModel>(GetFieldValue("soundDistanceModel"));
            set => SetFieldValue("soundDistanceModel", GenericMarshal.ToString(value));
        }
    }
}