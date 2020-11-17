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
    /// <summary>Defines the properties of a WheeledVehicle.</summary>
    /// <description>
    /// 
    /// </description>
    public unsafe class WheeledVehicleData : VehicleData {
        public WheeledVehicleData(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public WheeledVehicleData(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public WheeledVehicleData(string pName) 
            : this(pName, false) {
        }
        
        public WheeledVehicleData(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public WheeledVehicleData(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public WheeledVehicleData(SimObject pObj) 
            : base(pObj) {
        }
        
        public WheeledVehicleData(IntPtr pObj) 
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
                                "fnWheeledVehicleData_staticGetType"), typeof(_StaticGetType));
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
                                "fnWheeledVehicleData_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the WheeledVehicleData class.
        /// </description>
        /// <returns>The type info object for WheeledVehicleData</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Looping sound played when the vehicle is jetting.
        /// </description>
        /// </value>
        public SFXTrack JetSound {
            get => GenericMarshal.StringTo<SFXTrack>(GetFieldValue("jetSound"));
            set => SetFieldValue("jetSound", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Looping engine sound.</summary>
        /// <description>
        /// The pitch is dynamically adjusted based on the current engine RPM
        /// </description>
        /// </value>
        public SFXTrack EngineSound {
            get => GenericMarshal.StringTo<SFXTrack>(GetFieldValue("engineSound"));
            set => SetFieldValue("engineSound", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Looping sound played while any of the wheels is slipping.</summary>
        /// <description>
        /// The volume is dynamically adjusted based on how much the wheels are slipping.
        /// </description>
        /// </value>
        public SFXTrack SquealSound {
            get => GenericMarshal.StringTo<SFXTrack>(GetFieldValue("squealSound"));
            set => SetFieldValue("squealSound", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Sound played when the wheels impact the ground.
        /// Currently unused.
        /// </description>
        /// </value>
        public SFXTrack WheelImpactSound {
            get => GenericMarshal.StringTo<SFXTrack>(GetFieldValue("WheelImpactSound"));
            set => SetFieldValue("WheelImpactSound", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// ParticleEmitterData datablock used to generate particles from each wheel when the vehicle is moving and the wheel is in contact with the ground.
        /// </description>
        /// </value>
        public ParticleEmitterData TireEmitter {
            get => GenericMarshal.StringTo<ParticleEmitterData>(GetFieldValue("tireEmitter"));
            set => SetFieldValue("tireEmitter", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Maximum linear velocity of each wheel.</summary>
        /// <description>
        /// This caps the maximum speed of the vehicle.
        /// </description>
        /// </value>
        public float MaxWheelSpeed {
            get => GenericMarshal.StringTo<float>(GetFieldValue("maxWheelSpeed"));
            set => SetFieldValue("maxWheelSpeed", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Torque available from the engine at 100% throttle.</summary>
        /// <description>
        /// This controls vehicle acceleration. ie. how fast it will reach maximum speed.
        /// </description>
        /// </value>
        public float EngineTorque {
            get => GenericMarshal.StringTo<float>(GetFieldValue("engineTorque"));
            set => SetFieldValue("engineTorque", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Braking torque applied by the engine when the throttle and brake are both 0.</summary>
        /// <description>
        /// This controls how quickly the vehicle will coast to a stop.
        /// </description>
        /// </value>
        public float EngineBrake {
            get => GenericMarshal.StringTo<float>(GetFieldValue("engineBrake"));
            set => SetFieldValue("engineBrake", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Torque applied when braking.</summary>
        /// <description>
        /// This controls how fast the vehicle will stop when the brakes are applied.
        /// </description>
        /// </value>
        public float BrakeTorque {
            get => GenericMarshal.StringTo<float>(GetFieldValue("brakeTorque"));
            set => SetFieldValue("brakeTorque", GenericMarshal.ToString(value));
        }
    }
}