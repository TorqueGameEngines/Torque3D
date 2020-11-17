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
    /// <summary>Defines the properties of a FlyingVehicle.</summary>
    /// <description>
    /// 
    /// </description>
    public unsafe class FlyingVehicleData : VehicleData {
        public FlyingVehicleData(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public FlyingVehicleData(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public FlyingVehicleData(string pName) 
            : this(pName, false) {
        }
        
        public FlyingVehicleData(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public FlyingVehicleData(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public FlyingVehicleData(SimObject pObj) 
            : base(pObj) {
        }
        
        public FlyingVehicleData(IntPtr pObj) 
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
                                "fnFlyingVehicleData_staticGetType"), typeof(_StaticGetType));
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
                                "fnFlyingVehicleData_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the FlyingVehicleData class.
        /// </description>
        /// <returns>The type info object for FlyingVehicleData</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Looping sound to play while the vehicle is jetting.
        /// </description>
        /// </value>
        public SFXProfile JetSound {
            get => GenericMarshal.StringTo<SFXProfile>(GetFieldValue("jetSound"));
            set => SetFieldValue("jetSound", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Looping engine sound.
        /// </description>
        /// </value>
        public SFXProfile EngineSound {
            get => GenericMarshal.StringTo<SFXProfile>(GetFieldValue("engineSound"));
            set => SetFieldValue("engineSound", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Maximum X and Y (horizontal plane) maneuvering force.</summary>
        /// <description>
        /// The actual force applied depends on the current thrust.
        /// </description>
        /// </value>
        public float ManeuveringForce {
            get => GenericMarshal.StringTo<float>(GetFieldValue("maneuveringForce"));
            set => SetFieldValue("maneuveringForce", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Damping force in the opposite direction to sideways velocity.</summary>
        /// <description>
        /// Provides "bite" into the wind for climbing/diving and turning).
        /// </description>
        /// </value>
        public float HorizontalSurfaceForce {
            get => GenericMarshal.StringTo<float>(GetFieldValue("horizontalSurfaceForce"));
            set => SetFieldValue("horizontalSurfaceForce", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Damping force in the opposite direction to vertical velocity.</summary>
        /// <description>
        /// Controls side slip; lower numbers give more slide.
        /// </description>
        /// </value>
        public float VerticalSurfaceForce {
            get => GenericMarshal.StringTo<float>(GetFieldValue("verticalSurfaceForce"));
            set => SetFieldValue("verticalSurfaceForce", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Multiplier applied to the jetForce (defined in VehicleData) when thrusting vertically.
        /// </description>
        /// </value>
        public float VertThrustMultiple {
            get => GenericMarshal.StringTo<float>(GetFieldValue("vertThrustMultiple"));
            set => SetFieldValue("vertThrustMultiple", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Maximum X and Z (sideways and vertical) steering force.</summary>
        /// <description>
        /// The actual force applied depends on the current steering input.
        /// </description>
        /// </value>
        public float SteeringForce {
            get => GenericMarshal.StringTo<float>(GetFieldValue("steeringForce"));
            set => SetFieldValue("steeringForce", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Roll force induced by sideways steering input value (controls how much the vehicle rolls when turning).
        /// </description>
        /// </value>
        public float SteeringRollForce {
            get => GenericMarshal.StringTo<float>(GetFieldValue("steeringRollForce"));
            set => SetFieldValue("steeringRollForce", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Damping torque against rolling maneuvers (rotation about the y-axis), proportional to linear velocity.</summary>
        /// <description>
        /// Acts to adjust roll to a stable position over time as the vehicle moves.
        /// </description>
        /// </value>
        public float RollForce {
            get => GenericMarshal.StringTo<float>(GetFieldValue("rollForce"));
            set => SetFieldValue("rollForce", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Rotational drag factor (slows vehicle rotation speed in all axes).
        /// </description>
        /// </value>
        public float RotationalDrag {
            get => GenericMarshal.StringTo<float>(GetFieldValue("rotationalDrag"));
            set => SetFieldValue("rotationalDrag", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Maximum speed for automatic vehicle control assistance - vehicles travelling at speeds above this value do not get control assitance.
        /// </description>
        /// </value>
        public float MaxAutoSpeed {
            get => GenericMarshal.StringTo<float>(GetFieldValue("maxAutoSpeed"));
            set => SetFieldValue("maxAutoSpeed", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Scale factor applied to steering input if speed is less than maxAutoSpeed to.improve handling at very low speeds.</summary>
        /// <description>
        /// Smaller values make steering less sensitive.
        /// </description>
        /// </value>
        public float AutoInputDamping {
            get => GenericMarshal.StringTo<float>(GetFieldValue("autoInputDamping"));
            set => SetFieldValue("autoInputDamping", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Corrective force applied to slow the vehicle when moving at less than maxAutoSpeed.</summary>
        /// <description>
        /// The force is inversely proportional to vehicle speed.
        /// </description>
        /// </value>
        public float AutoLinearForce {
            get => GenericMarshal.StringTo<float>(GetFieldValue("autoLinearForce"));
            set => SetFieldValue("autoLinearForce", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Corrective torque applied to level out the vehicle when moving at less than maxAutoSpeed.</summary>
        /// <description>
        /// The torque is inversely proportional to vehicle speed.
        /// </description>
        /// </value>
        public float AutoAngularForce {
            get => GenericMarshal.StringTo<float>(GetFieldValue("autoAngularForce"));
            set => SetFieldValue("autoAngularForce", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The vehicle's height off the ground when at rest.
        /// </description>
        /// </value>
        public float HoverHeight {
            get => GenericMarshal.StringTo<float>(GetFieldValue("hoverHeight"));
            set => SetFieldValue("hoverHeight", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>The vehicle's height off the ground when useCreateHeight is active.</summary>
        /// <description>
        /// This can help avoid problems with spawning the vehicle.
        /// </description>
        /// </value>
        public float CreateHoverHeight {
            get => GenericMarshal.StringTo<float>(GetFieldValue("createHoverHeight"));
            set => SetFieldValue("createHoverHeight", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Emitter to generate particles for forward jet thrust.</summary>
        /// <description>
        /// Forward jet thrust particles are emitted from model nodes JetNozzle0 and JetNozzle1.
        /// </description>
        /// </value>
        public ParticleEmitterData ForwardJetEmitter {
            get => GenericMarshal.StringTo<ParticleEmitterData>(GetFieldValue("forwardJetEmitter"));
            set => SetFieldValue("forwardJetEmitter", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Emitter to generate particles for backward jet thrust.</summary>
        /// <description>
        /// Backward jet thrust particles are emitted from model nodes JetNozzleX and JetNozzleY.
        /// </description>
        /// </value>
        public ParticleEmitterData BackwardJetEmitter {
            get => GenericMarshal.StringTo<ParticleEmitterData>(GetFieldValue("backwardJetEmitter"));
            set => SetFieldValue("backwardJetEmitter", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Emitter to generate particles for downward jet thrust.</summary>
        /// <description>
        /// Downward jet thrust particles are emitted from model nodes JetNozzle2 and JetNozzle3.
        /// </description>
        /// </value>
        public ParticleEmitterData DownJetEmitter {
            get => GenericMarshal.StringTo<ParticleEmitterData>(GetFieldValue("downJetEmitter"));
            set => SetFieldValue("downJetEmitter", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Emitter to generate contrail particles from model nodes contrail0 - contrail3.
        /// </description>
        /// </value>
        public ParticleEmitterData TrailEmitter {
            get => GenericMarshal.StringTo<ParticleEmitterData>(GetFieldValue("trailEmitter"));
            set => SetFieldValue("trailEmitter", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Minimum speed at which to start generating contrail particles.
        /// </description>
        /// </value>
        public float MinTrailSpeed {
            get => GenericMarshal.StringTo<float>(GetFieldValue("minTrailSpeed"));
            set => SetFieldValue("minTrailSpeed", GenericMarshal.ToString(value));
        }
    }
}