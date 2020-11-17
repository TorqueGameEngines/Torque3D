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
    /// <summary>A datablock baseclass for afxT3DPointLightData and afxT3DSpotLightData.</summary>
    /// <description>
    /// Not intended to be used directly, afxT3DLightBaseData exists to provide base member variables and generic functionality for the derived classes afxT3DPointLightData and afxT3DSpotLightData.
    /// </description>
    /// <see cref="afxT3DPointLightData" />
    /// <see cref="afxT3DSpotLightData" />
    /// <see cref="PointLight" />
    /// <see cref="SpotLight" />
    public unsafe class afxT3DLightBaseData : GameBaseData {
        public afxT3DLightBaseData(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public afxT3DLightBaseData(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public afxT3DLightBaseData(string pName) 
            : this(pName, false) {
        }
        
        public afxT3DLightBaseData(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public afxT3DLightBaseData(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public afxT3DLightBaseData(SimObject pObj) 
            : base(pObj) {
        }
        
        public afxT3DLightBaseData(IntPtr pObj) 
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
                                "fnafxT3DLightBaseData_staticGetType"), typeof(_StaticGetType));
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
                                "fnafxT3DLightBaseData_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the afxT3DLightBaseData class.
        /// </description>
        /// <returns>The type info object for afxT3DLightBaseData</returns>
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
        /// Enables/disables shadow casts by this light.
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
        /// Enables/disables a semi-transparent geometry to help visualize the light's range and placement.
        /// </description>
        /// </value>
        public bool LocalRenderViz {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("localRenderViz"));
            set => SetFieldValue("localRenderViz", GenericMarshal.ToString(value));
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
    }
}