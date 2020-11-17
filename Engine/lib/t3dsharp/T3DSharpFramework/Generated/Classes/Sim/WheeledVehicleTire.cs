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
    /// <summary>Defines the properties of a WheeledVehicle tire.</summary>
    /// <description>
    /// Tires act as springs and generate lateral and longitudinal forces to move the vehicle. These distortion/spring forces are what convert wheel angular velocity into forces that act on the rigid body.
    /// </description>
    public unsafe class WheeledVehicleTire : SimDataBlock {
        public WheeledVehicleTire(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public WheeledVehicleTire(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public WheeledVehicleTire(string pName) 
            : this(pName, false) {
        }
        
        public WheeledVehicleTire(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public WheeledVehicleTire(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public WheeledVehicleTire(SimObject pObj) 
            : base(pObj) {
        }
        
        public WheeledVehicleTire(IntPtr pObj) 
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
                                "fnWheeledVehicleTire_staticGetType"), typeof(_StaticGetType));
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
                                "fnWheeledVehicleTire_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the WheeledVehicleTire class.
        /// </description>
        /// <returns>The type info object for WheeledVehicleTire</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// The path to the shape to use for the wheel.
        /// </description>
        /// </value>
        public string ShapeFile {
            get => GenericMarshal.StringTo<string>(GetFieldValue("shapeFile"));
            set => SetFieldValue("shapeFile", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The mass of the wheel.
        /// Currently unused.
        /// </description>
        /// </value>
        public float Mass {
            get => GenericMarshal.StringTo<float>(GetFieldValue("mass"));
            set => SetFieldValue("mass", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>The radius of the wheel.</summary>
        /// <description>
        /// The radius is determined from the bounding box of the shape provided in the shapefile field, and does not need to be specified in script. The tire should be built with its hub axis along the object's Y-axis.
        /// </description>
        /// </value>
        public float Radius {
            get => GenericMarshal.StringTo<float>(GetFieldValue("radius"));
            set => SetFieldValue("radius", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Tire friction when the wheel is not slipping (has traction).
        /// </description>
        /// </value>
        public float StaticFriction {
            get => GenericMarshal.StringTo<float>(GetFieldValue("staticFriction"));
            set => SetFieldValue("staticFriction", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Tire friction when the wheel is slipping (no traction).
        /// </description>
        /// </value>
        public float KineticFriction {
            get => GenericMarshal.StringTo<float>(GetFieldValue("kineticFriction"));
            set => SetFieldValue("kineticFriction", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Tire restitution.
        /// Currently unused.
        /// </description>
        /// </value>
        public float Restitution {
            get => GenericMarshal.StringTo<float>(GetFieldValue("restitution"));
            set => SetFieldValue("restitution", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Tire force perpendicular to the direction of movement.</summary>
        /// <description>
        /// Lateral force can in simple terms be considered left/right steering force. WheeledVehicles are acted upon by forces generated by their tires and the lateralForce measures the magnitude of the force exerted on the vehicle when the tires are deformed along the x-axis. With real wheeled vehicles, tires are constantly being deformed and it is the interplay of deformation forces which determines how a vehicle moves. In Torque's simulation of vehicle physics, tire deformation obviously can't be handled with absolute realism, but the interplay of a vehicle's velocity, its engine's torque and braking forces, and its wheels' friction, lateral deformation, lateralDamping, lateralRelaxation, longitudinal deformation, longitudinalDamping, and longitudinalRelaxation forces, along with its wheels' angular velocity are combined to create a robust real-time physical simulation.
        /// 
        /// For this field, the larger the value supplied for the lateralForce, the larger the effect steering maneuvers can have. In Torque tire forces are applied at a vehicle's wheel hubs.
        /// </description>
        /// </value>
        public float LateralForce {
            get => GenericMarshal.StringTo<float>(GetFieldValue("lateralForce"));
            set => SetFieldValue("lateralForce", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Damping force applied against lateral forces generated by the tire.
        /// </description>
        /// <see cref="lateralForce" />
        /// </value>
        public float LateralDamping {
            get => GenericMarshal.StringTo<float>(GetFieldValue("lateralDamping"));
            set => SetFieldValue("lateralDamping", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Relaxing force applied against lateral forces generated by the tire.</summary>
        /// <description>
        /// The lateralRelaxation force measures how strongly the tire effectively un-deforms.
        /// </description>
        /// <see cref="lateralForce" />
        /// </value>
        public float LateralRelaxation {
            get => GenericMarshal.StringTo<float>(GetFieldValue("lateralRelaxation"));
            set => SetFieldValue("lateralRelaxation", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Tire force in the direction of movement.</summary>
        /// <description>
        /// Longitudinal force can in simple terms be considered forward/backward movement force. WheeledVehicles are acted upon by forces generated by their tires and the longitudinalForce measures the magnitude of the force exerted on the vehicle when the tires are deformed along the y-axis.
        /// 
        /// For this field, the larger the value, the larger the effect acceleration/deceleration inputs have.
        /// </description>
        /// <see cref="lateralForce" />
        /// </value>
        public float LongitudinalForce {
            get => GenericMarshal.StringTo<float>(GetFieldValue("longitudinalForce"));
            set => SetFieldValue("longitudinalForce", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Damping force applied against longitudinal forces generated by the tire.
        /// </description>
        /// <see cref="longitudinalForce" />
        /// </value>
        public float LongitudinalDamping {
            get => GenericMarshal.StringTo<float>(GetFieldValue("longitudinalDamping"));
            set => SetFieldValue("longitudinalDamping", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Relaxing force applied against longitudinal forces generated by the tire.</summary>
        /// <description>
        /// The longitudinalRelaxation force measures how strongly the tire effectively un-deforms.
        /// </description>
        /// <see cref="longitudinalForce" />
        /// </value>
        public float LongitudinalRelaxation {
            get => GenericMarshal.StringTo<float>(GetFieldValue("longitudinalRelaxation"));
            set => SetFieldValue("longitudinalRelaxation", GenericMarshal.ToString(value));
        }
    }
}