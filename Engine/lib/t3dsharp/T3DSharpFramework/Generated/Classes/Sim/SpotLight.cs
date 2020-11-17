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
    /// <summary>Lighting object which emits conical light in a direction.</summary>
    /// <description>
    /// SpotLight is one of the two types of lighting objects that can be added to a Torque 3D level, the other being PointLight. Unlike directional or point lights, the SpotLights emits lighting in a specific direction within a cone. The distance of the cone is controlled by the SpotLight::range variable.
    /// </description>
    /// <code>
    /// // Declaration of a point light in script, or created by World Editor
    /// new SpotLight(SampleSpotLight)
    /// {
    ///    range = "10";
    ///    innerAngle = "40";
    ///    outerAngle = "45";
    ///    isEnabled = "1";
    ///    color = "1 1 1 1";
    ///    brightness = "1";
    ///    castShadows = "0";
    ///    priority = "1";
    ///    animate = "1";
    ///    animationPeriod = "1";
    ///    animationPhase = "1";
    ///    flareType = "LightFlareExample0";
    ///    flareScale = "1";
    ///    attenuationRatio = "0 1 1";
    ///    shadowType = "Spot";
    ///    texSize = "512";
    ///    overDarkFactor = "2000 1000 500 100";
    ///    shadowDistance = "400";
    ///    shadowSoftness = "0.15";
    ///    numSplits = "1";
    ///    logWeight = "0.91";
    ///    fadeStartDistance = "0";
    ///    lastSplitTerrainOnly = "0";
    ///    representedInLightmap = "0";
    ///    shadowDarkenColor = "0 0 0 -1";
    ///    includeLightmappedGeometryInShadow = "0";
    ///    position = "-29.4362 -5.86289 5.58602";
    ///    rotation = "1 0 0 0";
    /// };
    /// </code>
    /// <see cref="LightBase" />
    /// <see cref="PointLight" />
    public unsafe class SpotLight : LightBase {
        public SpotLight(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public SpotLight(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public SpotLight(string pName) 
            : this(pName, false) {
        }
        
        public SpotLight(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public SpotLight(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public SpotLight(SimObject pObj) 
            : base(pObj) {
        }
        
        public SpotLight(IntPtr pObj) 
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
                                "fnSpotLight_staticGetType"), typeof(_StaticGetType));
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
                                "fnSpotLight_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the SpotLight class.
        /// </description>
        /// <returns>The type info object for SpotLight</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// 
        /// </value>
        public float Range {
            get => GenericMarshal.StringTo<float>(GetFieldValue("range"));
            set => SetFieldValue("range", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public float InnerAngle {
            get => GenericMarshal.StringTo<float>(GetFieldValue("innerAngle"));
            set => SetFieldValue("innerAngle", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public float OuterAngle {
            get => GenericMarshal.StringTo<float>(GetFieldValue("outerAngle"));
            set => SetFieldValue("outerAngle", GenericMarshal.ToString(value));
        }
    }
}