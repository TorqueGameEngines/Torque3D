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
    /// <summary>Lighting object that radiates light in all directions.</summary>
    /// <description>
    /// PointLight is one of the two types of lighting objects that can be added to a Torque 3D level, the other being SpotLight. Unlike directional or conical light, the PointLight emits lighting in all directions. The attenuation is controlled by a single variable: LightObject::radius.
    /// </description>
    /// <code>
    /// // Declaration of a point light in script, or created by World Editor
    /// new PointLight(CrystalLight)
    /// {
    ///    radius = "10";
    ///    isEnabled = "1";
    ///    color = "1 0.905882 0 1";
    ///    brightness = "0.5";
    ///    castShadows = "1";
    ///    priority = "1";
    ///    animate = "1";
    ///    animationType = "SubtlePulseLightAnim";
    ///    animationPeriod = "3";
    ///    animationPhase = "3";
    ///    flareScale = "1";
    ///    attenuationRatio = "0 1 1";
    ///    shadowType = "DualParaboloidSinglePass";
    ///    texSize = "512";
    ///    overDarkFactor = "2000 1000 500 100";
    ///    shadowDistance = "400";
    ///    shadowSoftness = "0.15";
    ///    numSplits = "1";
    ///    logWeight = "0.91";
    ///    fadeStartDistance = "0";
    ///    lastSplitTerrainOnly = "0";
    ///    splitFadeDistances = "10 20 30 40";
    ///    representedInLightmap = "0";
    ///    shadowDarkenColor = "0 0 0 -1";
    ///    includeLightmappedGeometryInShadow = "1";
    ///    position = "-61.3866 1.69186 5.1464";
    ///    rotation = "1 0 0 0";
    /// };
    /// </code>
    /// <see cref="LightBase" />
    /// <see cref="SpotLight" />
    public unsafe class PointLight : LightBase {
        public PointLight(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public PointLight(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public PointLight(string pName) 
            : this(pName, false) {
        }
        
        public PointLight(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public PointLight(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public PointLight(SimObject pObj) 
            : base(pObj) {
        }
        
        public PointLight(IntPtr pObj) 
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
                                "fnPointLight_staticGetType"), typeof(_StaticGetType));
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
                                "fnPointLight_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the PointLight class.
        /// </description>
        /// <returns>The type info object for PointLight</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Controls the falloff of the light emission
        /// </description>
        /// </value>
        public float Radius {
            get => GenericMarshal.StringTo<float>(GetFieldValue("radius"));
            set => SetFieldValue("radius", GenericMarshal.ToString(value));
        }
    }
}