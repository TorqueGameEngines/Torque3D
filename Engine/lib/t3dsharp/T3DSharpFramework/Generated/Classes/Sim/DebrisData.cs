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
    /// <summary>Stores properties for an individual debris type.</summary>
    /// <description>
    /// DebrisData defines the base properties for a Debris object.  Typically you'll want a Debris object to consist of a shape and possibly up to two particle emitters.  The DebrisData datablock provides the definition for these items, along with physical properties and how a Debris object will react to other game objects, such as water and terrain.
    /// </description>
    /// <code>
    /// datablock DebrisData(GrenadeDebris)
    /// {
    ///    shapeFile = "art/shapes/weapons/ramrifle/debris.dts";
    ///    emitters[0] = GrenadeDebrisFireEmitter;
    ///    elasticity = 0.4;
    ///    friction = 0.25;
    ///    numBounces = 3;
    ///    bounceVariance = 1;
    ///    explodeOnMaxBounce = false;
    ///    staticOnMaxBounce = false;
    ///    snapOnMaxBounce = false;
    ///    minSpinSpeed = 200;
    ///    maxSpinSpeed = 600;
    ///    lifetime = 4;
    ///    lifetimeVariance = 1.5;
    ///    velocity = 15;
    ///    velocityVariance = 5;
    ///    fade = true;
    ///    useRadiusMass = true;
    ///    baseRadius = 0.3;
    ///    gravModifier = 1.0;
    ///    terminalVelocity = 20;
    ///    ignoreWater = false;
    /// };
    /// </code>
    /// <see cref="Debris" />
    public unsafe class DebrisData : GameBaseData {
        public DebrisData(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public DebrisData(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public DebrisData(string pName) 
            : this(pName, false) {
        }
        
        public DebrisData(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public DebrisData(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public DebrisData(SimObject pObj) 
            : base(pObj) {
        }
        
        public DebrisData(IntPtr pObj) 
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
                                "fnDebrisData_staticGetType"), typeof(_StaticGetType));
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
                                "fnDebrisData_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the DebrisData class.
        /// </description>
        /// <returns>The type info object for DebrisData</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <summary>Texture imagemap to use for this debris object.</summary>
        /// <description>
        /// Not used any more.
        /// </description>
        /// </value>
        public string Texture {
            get => GenericMarshal.StringTo<string>(GetFieldValue("texture"));
            set => SetFieldValue("texture", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Object model to use for this debris object.</summary>
        /// <description>
        /// This shape is optional.  You could have Debris made up of only particles.
        /// </description>
        /// </value>
        public string ShapeFile {
            get => GenericMarshal.StringTo<string>(GetFieldValue("shapeFile"));
            set => SetFieldValue("shapeFile", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>List of particle emitters to spawn along with this debris object.</summary>
        /// <description>
        /// These are optional.  You could have Debris made up of only a shape.
        /// </description>
        /// </value>
        public DynamicFieldVector<ParticleEmitterData> Emitters {
            get => new DynamicFieldVector<ParticleEmitterData>(
                    this, 
                    "emitters", 
                    2, 
                    val => GenericMarshal.StringTo<ParticleEmitterData>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <summary>ExplosionData to spawn along with this debris object.</summary>
        /// <description>
        /// This is optional as not all Debris explode.
        /// </description>
        /// </value>
        public ExplosionData Explosion {
            get => GenericMarshal.StringTo<ExplosionData>(GetFieldValue("Explosion"));
            set => SetFieldValue("Explosion", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>A floating-point value specifying how 'bouncy' this object is.</summary>
        /// <description>
        /// Must be in the range of -10 to 10.
        /// </description>
        /// </value>
        public float Elasticity {
            get => GenericMarshal.StringTo<float>(GetFieldValue("elasticity"));
            set => SetFieldValue("elasticity", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>A floating-point value specifying how much velocity is lost to impact and sliding friction.</summary>
        /// <description>
        /// Must be in the range of -10 to 10.
        /// </description>
        /// </value>
        public float Friction {
            get => GenericMarshal.StringTo<float>(GetFieldValue("friction"));
            set => SetFieldValue("friction", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>How many times to allow this debris object to bounce until it either explodes, becomes static or snaps (defined in explodeOnMaxBounce, staticOnMaxBounce, snapOnMaxBounce).</summary>
        /// <description>
        /// Must be within the range of 0 to 10000.
        /// </description>
        /// <see cref="bounceVariance" />
        /// </value>
        public int NumBounces {
            get => GenericMarshal.StringTo<int>(GetFieldValue("numBounces"));
            set => SetFieldValue("numBounces", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Allowed variance in the value of numBounces.</summary>
        /// <description>
        /// Must be less than numBounces.
        /// </description>
        /// <see cref="numBounces" />
        /// </value>
        public int BounceVariance {
            get => GenericMarshal.StringTo<int>(GetFieldValue("bounceVariance"));
            set => SetFieldValue("bounceVariance", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Minimum speed that this debris object will rotate.</summary>
        /// <description>
        /// Must be in the range of -10000 to 1000, and must be less than maxSpinSpeed.
        /// </description>
        /// <see cref="maxSpinSpeed" />
        /// </value>
        public float MinSpinSpeed {
            get => GenericMarshal.StringTo<float>(GetFieldValue("minSpinSpeed"));
            set => SetFieldValue("minSpinSpeed", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Maximum speed that this debris object will rotate.</summary>
        /// <description>
        /// Must be in the range of -10000 to 10000.
        /// </description>
        /// <see cref="minSpinSpeed" />
        /// </value>
        public float MaxSpinSpeed {
            get => GenericMarshal.StringTo<float>(GetFieldValue("maxSpinSpeed"));
            set => SetFieldValue("maxSpinSpeed", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// How much gravity affects debris.
        /// </description>
        /// </value>
        public float GravModifier {
            get => GenericMarshal.StringTo<float>(GetFieldValue("gravModifier"));
            set => SetFieldValue("gravModifier", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Max velocity magnitude.
        /// </description>
        /// </value>
        public float TerminalVelocity {
            get => GenericMarshal.StringTo<float>(GetFieldValue("terminalVelocity"));
            set => SetFieldValue("terminalVelocity", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Speed at which this debris object will move.</summary>
        /// <description>
        /// 
        /// </description>
        /// <see cref="velocityVariance" />
        /// </value>
        public float Velocity {
            get => GenericMarshal.StringTo<float>(GetFieldValue("velocity"));
            set => SetFieldValue("velocity", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Allowed variance in the value of velocity</summary>
        /// <description>
        /// Must be less than velocity.
        /// </description>
        /// <see cref="velocity" />
        /// </value>
        public float VelocityVariance {
            get => GenericMarshal.StringTo<float>(GetFieldValue("velocityVariance"));
            set => SetFieldValue("velocityVariance", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Amount of time until this debris object is destroyed.</summary>
        /// <description>
        /// Must be in the range of 0 to 1000.
        /// </description>
        /// <see cref="lifetimeVariance" />
        /// </value>
        public float Lifetime {
            get => GenericMarshal.StringTo<float>(GetFieldValue("lifetime"));
            set => SetFieldValue("lifetime", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Allowed variance in the value of lifetime.</summary>
        /// <description>
        /// Must be less than lifetime.
        /// </description>
        /// <see cref="lifetime" />
        /// </value>
        public float LifetimeVariance {
            get => GenericMarshal.StringTo<float>(GetFieldValue("lifetimeVariance"));
            set => SetFieldValue("lifetimeVariance", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Use mass calculations based on radius.</summary>
        /// <description>
        /// Allows for the adjustment of elasticity and friction based on the Debris size.
        /// </description>
        /// <see cref="baseRadius" />
        /// </value>
        public bool UseRadiusMass {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("useRadiusMass"));
            set => SetFieldValue("useRadiusMass", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Radius at which the standard elasticity and friction apply.</summary>
        /// <description>
        /// Only used when useRaduisMass is true.
        /// </description>
        /// <see cref="useRadiusMass." />
        /// </value>
        public float BaseRadius {
            get => GenericMarshal.StringTo<float>(GetFieldValue("baseRadius"));
            set => SetFieldValue("baseRadius", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>If true, this debris object will explode after it has bounced max times.</summary>
        /// <description>
        /// Be sure to provide an ExplosionData datablock for this to take effect.
        /// </description>
        /// <see cref="explosion" />
        /// </value>
        public bool ExplodeOnMaxBounce {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("explodeOnMaxBounce"));
            set => SetFieldValue("explodeOnMaxBounce", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// If true, this debris object becomes static after it has bounced max times.
        /// </description>
        /// </value>
        public bool StaticOnMaxBounce {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("staticOnMaxBounce"));
            set => SetFieldValue("staticOnMaxBounce", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// If true, this debris object will snap into a resting position on the last bounce.
        /// </description>
        /// </value>
        public bool SnapOnMaxBounce {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("snapOnMaxBounce"));
            set => SetFieldValue("snapOnMaxBounce", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>If true, this debris object will fade out when destroyed.</summary>
        /// <description>
        /// This fade occurs over the last second of the Debris' lifetime.
        /// </description>
        /// </value>
        public bool Fade {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("fade"));
            set => SetFieldValue("fade", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// If true, this debris object will not collide with water, acting as if the water is not there.
        /// </description>
        /// </value>
        public bool IgnoreWater {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("ignoreWater"));
            set => SetFieldValue("ignoreWater", GenericMarshal.ToString(value));
        }
    }
}