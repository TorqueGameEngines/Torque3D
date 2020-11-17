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
    /// <summary>Defines the properties of a PhysicsShape.</summary>
    /// <description>
    /// 
    /// </description>
    /// <see cref="PhysicsShape." />
    public unsafe class PhysicsShapeData : GameBaseData {
        public PhysicsShapeData(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public PhysicsShapeData(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public PhysicsShapeData(string pName) 
            : this(pName, false) {
        }
        
        public PhysicsShapeData(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public PhysicsShapeData(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public PhysicsShapeData(SimObject pObj) 
            : base(pObj) {
        }
        
        public PhysicsShapeData(IntPtr pObj) 
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
                                "fnPhysicsShapeData_staticGetType"), typeof(_StaticGetType));
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
                                "fnPhysicsShapeData_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the PhysicsShapeData class.
        /// </description>
        /// <returns>The type info object for PhysicsShapeData</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <summary>Path to the .DAE or .DTS file to use for this shape.</summary>
        /// <description>
        /// Compatable with Live-Asset Reloading.
        /// </description>
        /// </value>
        public string ShapeName {
            get => GenericMarshal.StringTo<string>(GetFieldValue("shapeName"));
            set => SetFieldValue("shapeName", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Name of a PhysicsDebrisData to spawn when this shape is destroyed (optional).</summary>
        /// </value>
        public PhysicsDebrisData Debris {
            get => GenericMarshal.StringTo<PhysicsDebrisData>(GetFieldValue("Debris"));
            set => SetFieldValue("Debris", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Name of an ExplosionData to spawn when this shape is destroyed (optional).</summary>
        /// </value>
        public ExplosionData Explosion {
            get => GenericMarshal.StringTo<ExplosionData>(GetFieldValue("Explosion"));
            set => SetFieldValue("Explosion", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Name of a PhysicsShapeData to spawn when this shape is destroyed (optional).</summary>
        /// </value>
        public PhysicsShapeData DestroyedShape {
            get => GenericMarshal.StringTo<PhysicsShapeData>(GetFieldValue("destroyedShape"));
            set => SetFieldValue("destroyedShape", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Value representing the mass of the shape.</summary>
        /// <description>
        /// A shape's mass influences the magnitude of any force exerted on it. For example, a PhysicsShape with a large mass requires a much larger force to move than the same shape with a smaller mass.
        /// </description>
        /// <remarks> A mass of zero will create a kinematic shape while anything greater will create a dynamic shape.</remarks>
        /// </value>
        public float Mass {
            get => GenericMarshal.StringTo<float>(GetFieldValue("mass"));
            set => SetFieldValue("mass", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Coefficient of kinetic %friction to be applied to the shape.</summary>
        /// <description>
        /// Kinetic %friction reduces the velocity of a moving object while it is in contact with a surface. A higher coefficient will result in a larger velocity reduction. A shape's friction should be lower than it's staticFriction, but larger than 0.
        /// </description>
        /// <remarks> This value is only applied while an object is in motion. For an object starting at rest, see PhysicsShape::staticFriction</remarks>
        /// </value>
        public float Friction {
            get => GenericMarshal.StringTo<float>(GetFieldValue("friction"));
            set => SetFieldValue("friction", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Coefficient of static %friction to be applied to the shape.</summary>
        /// <description>
        /// Static %friction determines the force needed to start moving an at-rest object in contact with a surface. If the force applied onto shape cannot overcome the force of static %friction, the shape will remain at rest. A larger coefficient will require a larger force to start motion. This value should be larger than zero and the physicsShape's friction.
        /// </description>
        /// <remarks> This value is only applied while an object is at rest. For an object in motion, see PhysicsShape::friction</remarks>
        /// </value>
        public float StaticFriction {
            get => GenericMarshal.StringTo<float>(GetFieldValue("staticFriction"));
            set => SetFieldValue("staticFriction", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Coeffecient of a bounce applied to the shape in response to a collision.</summary>
        /// <description>
        /// Restitution is a ratio of a shape's velocity before and after a collision. A value of 0 will zero out a shape's post-collision velocity, making it stop on contact. Larger values will remove less velocity after a collision, making it 'bounce' with a greater force. Normal %restitution values range between 0 and 1.0.
        /// </description>
        /// <remarks> Values near or equaling 1.0 are likely to cause undesirable results in the physics simulation. Because of this it is reccomended to avoid values close to 1.0</remarks>
        /// </value>
        public float Restitution {
            get => GenericMarshal.StringTo<float>(GetFieldValue("restitution"));
            set => SetFieldValue("restitution", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Value that reduces an object's linear velocity over time.</summary>
        /// <description>
        /// Larger values will cause velocity to decay quicker.
        /// </description>
        /// </value>
        public float LinearDamping {
            get => GenericMarshal.StringTo<float>(GetFieldValue("linearDamping"));
            set => SetFieldValue("linearDamping", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Value that reduces an object's rotational velocity over time.</summary>
        /// <description>
        /// Larger values will cause velocity to decay quicker.
        /// </description>
        /// </value>
        public float AngularDamping {
            get => GenericMarshal.StringTo<float>(GetFieldValue("angularDamping"));
            set => SetFieldValue("angularDamping", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Minimum linear velocity before the shape can be put to sleep.</summary>
        /// <description>
        /// This should be a positive value. Shapes put to sleep will not be simulated in order to save system resources.
        /// </description>
        /// <remarks> The shape must be dynamic.</remarks>
        /// </value>
        public float LinearSleepThreshold {
            get => GenericMarshal.StringTo<float>(GetFieldValue("linearSleepThreshold"));
            set => SetFieldValue("linearSleepThreshold", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Minimum rotational velocity before the shape can be put to sleep.</summary>
        /// <description>
        /// This should be a positive value. Shapes put to sleep will not be simulated in order to save system resources.
        /// </description>
        /// <remarks> The shape must be dynamic.</remarks>
        /// </value>
        public float AngularSleepThreshold {
            get => GenericMarshal.StringTo<float>(GetFieldValue("angularSleepThreshold"));
            set => SetFieldValue("angularSleepThreshold", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Scale to apply to linear and angular dampening while underwater.</summary>
        /// <description>
        /// Used with the waterViscosity of the
        /// </description>
        /// <see cref="angularDamping linearDamping" />
        /// </value>
        public float WaterDampingScale {
            get => GenericMarshal.StringTo<float>(GetFieldValue("waterDampingScale"));
            set => SetFieldValue("waterDampingScale", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>The density of the shape for calculating buoyant forces.</summary>
        /// <description>
        /// The result of the calculated buoyancy is relative to the density of the WaterObject the PhysicsShape is within.
        /// </description>
        /// <see cref="WaterObject::density" />
        /// </value>
        public float BuoyancyDensity {
            get => GenericMarshal.StringTo<float>(GetFieldValue("buoyancyDensity"));
            set => SetFieldValue("buoyancyDensity", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Controls whether this shape is simulated on the server, client, or both physics simulations.</summary>
        /// <description>
        /// 
        /// </description>
        /// </value>
        public PhysicsSimType SimType {
            get => GenericMarshal.StringTo<PhysicsSimType>(GetFieldValue("simType"));
            set => SetFieldValue("simType", GenericMarshal.ToString(value));
        }
    }
}