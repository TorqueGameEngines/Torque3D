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
    /// <summary>Stores properties for an individual projectile type.</summary>
    /// <description>
    /// 
    /// </description>
    /// <code>
    /// datablock ProjectileData(GrenadeLauncherProjectile)
    /// {
    ///  projectileShapeName = "art/shapes/weapons/SwarmGun/rocket.dts";
    /// directDamage = 30;
    /// radiusDamage = 30;
    /// damageRadius = 5;
    /// areaImpulse = 2000;
    /// explosion = GrenadeLauncherExplosion;
    /// waterExplosion = GrenadeLauncherWaterExplosion;
    /// decal = ScorchRXDecal;
    /// splash = GrenadeSplash;
    /// particleEmitter = GrenadeProjSmokeTrailEmitter;
    /// particleWaterEmitter = GrenadeTrailWaterEmitter;
    /// muzzleVelocity = 30;
    /// velInheritFactor = 0.3;
    /// armingDelay = 2000;
    /// lifetime = 10000;
    /// fadeDelay = 4500;
    /// bounceElasticity = 0.4;
    /// bounceFriction = 0.3;
    /// isBallistic = true;
    /// gravityMod = 0.9;
    /// lightDesc = GrenadeLauncherLightDesc;
    /// damageType = "GrenadeDamage";
    /// };
    /// </code>
    public unsafe class ProjectileData : GameBaseData {
        public ProjectileData(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public ProjectileData(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public ProjectileData(string pName) 
            : this(pName, false) {
        }
        
        public ProjectileData(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public ProjectileData(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public ProjectileData(SimObject pObj) 
            : base(pObj) {
        }
        
        public ProjectileData(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct OnCollision__Args
            {
                internal IntPtr proj;
                internal IntPtr col;
                internal float fade;
                internal IntPtr pos;
                internal IntPtr normal;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnCollision(IntPtr _this, OnCollision__Args args);
            private static _OnCollision _OnCollisionFunc;
            internal static _OnCollision OnCollision() {
                if (_OnCollisionFunc == null) {
                    _OnCollisionFunc =
                        (_OnCollision)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbProjectileData_onCollision"), typeof(_OnCollision));
                }
                
                return _OnCollisionFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnExplode__Args
            {
                internal IntPtr proj;
                internal IntPtr pos;
                internal float fade;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnExplode(IntPtr _this, OnExplode__Args args);
            private static _OnExplode _OnExplodeFunc;
            internal static _OnExplode OnExplode() {
                if (_OnExplodeFunc == null) {
                    _OnExplodeFunc =
                        (_OnExplode)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbProjectileData_onExplode"), typeof(_OnExplode));
                }
                
                return _OnExplodeFunc;
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
                                "fnProjectileData_staticGetType"), typeof(_StaticGetType));
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
                                "fnProjectileData_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <summary>Called when a projectile collides with another object.</summary>
        /// <description>
        /// This function is only called on server objects.
        /// </description>
        /// <param name="proj">The projectile colliding with SceneObject col.</param>
        /// <param name="col">The SceneObject hit by the projectile.</param>
        /// <param name="fade">The current fadeValue of the projectile, affects its visibility.</param>
        /// <param name="pos">The position of the collision.</param>
        /// <param name="normal">The normal of the collision.</param>
        /// <see cref="Projectile" />
        public virtual void OnCollision(Projectile proj, SceneObject col, float fade, Point3F pos, Point3F normal) {
pos.Alloc();normal.Alloc();             InternalUnsafeMethods.OnCollision__Args _args = new InternalUnsafeMethods.OnCollision__Args() {
                proj = proj.ObjectPtr,
                col = col.ObjectPtr,
                fade = fade,
                pos = pos.internalStructPtr,
                normal = normal.internalStructPtr,
             };
             InternalUnsafeMethods.OnCollision()(ObjectPtr, _args);
pos.Free();normal.Free();        }

        /// <summary>Called when a projectile explodes.</summary>
        /// <description>
        /// This function is only called on server objects.
        /// </description>
        /// <param name="proj">The exploding projectile.</param>
        /// <param name="pos">The position of the explosion.</param>
        /// <param name="fade">The current fadeValue of the projectile, affects its visibility.</param>
        /// <see cref="Projectile" />
        public virtual void OnExplode(Projectile proj, Point3F pos, float fade) {
pos.Alloc();             InternalUnsafeMethods.OnExplode__Args _args = new InternalUnsafeMethods.OnExplode__Args() {
                proj = proj.ObjectPtr,
                pos = pos.internalStructPtr,
                fade = fade,
             };
             InternalUnsafeMethods.OnExplode()(ObjectPtr, _args);
pos.Free();        }

        /// <description>
        /// Get the type info object for the ProjectileData class.
        /// </description>
        /// <returns>The type info object for ProjectileData</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <summary>Particle emitter datablock used to generate particles while the projectile is outside of water.</summary>
        /// <description>
        /// 
        /// </description>
        /// <remarks> If datablocks are defined for both particleEmitter and particleWaterEmitter, both effects will play as the projectile enters or leaves water.
        /// 
        /// </remarks>
        /// <see cref="particleWaterEmitter" />
        /// </value>
        public ParticleEmitterData ParticleEmitter {
            get => GenericMarshal.StringTo<ParticleEmitterData>(GetFieldValue("ParticleEmitter"));
            set => SetFieldValue("ParticleEmitter", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Particle emitter datablock used to generate particles while the projectile is submerged in water.</summary>
        /// <description>
        /// 
        /// </description>
        /// <remarks> If datablocks are defined for both particleWaterEmitter and particleEmitter , both effects will play as the projectile enters or leaves water.
        /// 
        /// </remarks>
        /// <see cref="particleEmitter" />
        /// </value>
        public ParticleEmitterData ParticleWaterEmitter {
            get => GenericMarshal.StringTo<ParticleEmitterData>(GetFieldValue("particleWaterEmitter"));
            set => SetFieldValue("particleWaterEmitter", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>File path to the model of the projectile.</summary>
        /// <description>
        /// 
        /// </description>
        /// </value>
        public string ProjectileShapeName {
            get => GenericMarshal.StringTo<string>(GetFieldValue("projectileShapeName"));
            set => SetFieldValue("projectileShapeName", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Scale to apply to the projectile's size.</summary>
        /// <description>
        /// 
        /// </description>
        /// <remarks> This is applied after SceneObject::scale
        /// </remarks>
        /// </value>
        public Point3F Scale {
            get => GenericMarshal.StringTo<Point3F>(GetFieldValue("scale"));
            set => SetFieldValue("scale", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>SFXTrack datablock used to play sounds while in flight.</summary>
        /// <description>
        /// 
        /// </description>
        /// </value>
        public SFXTrack Sound {
            get => GenericMarshal.StringTo<SFXTrack>(GetFieldValue("sound"));
            set => SetFieldValue("sound", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Explosion datablock used when the projectile explodes outside of water.</summary>
        /// <description>
        /// 
        /// </description>
        /// </value>
        public ExplosionData Explosion {
            get => GenericMarshal.StringTo<ExplosionData>(GetFieldValue("Explosion"));
            set => SetFieldValue("Explosion", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Explosion datablock used when the projectile explodes underwater.</summary>
        /// <description>
        /// 
        /// </description>
        /// </value>
        public ExplosionData WaterExplosion {
            get => GenericMarshal.StringTo<ExplosionData>(GetFieldValue("waterExplosion"));
            set => SetFieldValue("waterExplosion", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Splash datablock used to create splash effects as the projectile enters or leaves water</summary>
        /// <description>
        /// 
        /// </description>
        /// </value>
        public SplashData Splash {
            get => GenericMarshal.StringTo<SplashData>(GetFieldValue("Splash"));
            set => SetFieldValue("Splash", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Decal datablock used for decals placed at projectile explosion points.</summary>
        /// <description>
        /// 
        /// </description>
        /// </value>
        public DecalData Decal {
            get => GenericMarshal.StringTo<DecalData>(GetFieldValue("decal"));
            set => SetFieldValue("decal", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>LightDescription datablock used for lights attached to the projectile.</summary>
        /// <description>
        /// 
        /// </description>
        /// </value>
        public LightDescription LightDesc {
            get => GenericMarshal.StringTo<LightDescription>(GetFieldValue("lightDesc"));
            set => SetFieldValue("lightDesc", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Detetmines if the projectile should be affected by gravity and whether or not it bounces before exploding.</summary>
        /// <description>
        /// 
        /// </description>
        /// </value>
        public bool IsBallistic {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("isBallistic"));
            set => SetFieldValue("isBallistic", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Amount of velocity the projectile recieves from the source that created it.</summary>
        /// <description>
        /// Use an amount between 0 and 1 for the best effect. This value is never modified by the engine.
        /// </description>
        /// <remarks> This value by default is not transmitted between the server and the client.</remarks>
        /// </value>
        public float VelInheritFactor {
            get => GenericMarshal.StringTo<float>(GetFieldValue("velInheritFactor"));
            set => SetFieldValue("velInheritFactor", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Amount of velocity the projectile recieves from the "muzzle" of the gun.</summary>
        /// <description>
        /// Used with velInheritFactor to determine the initial velocity of the projectile. This value is never modified by the engine.
        /// </description>
        /// <remarks> This value by default is not transmitted between the server and the client.
        /// 
        /// </remarks>
        /// <see cref="velInheritFactor" />
        /// </value>
        public float MuzzleVelocity {
            get => GenericMarshal.StringTo<float>(GetFieldValue("muzzleVelocity"));
            set => SetFieldValue("muzzleVelocity", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public float ImpactForce {
            get => GenericMarshal.StringTo<float>(GetFieldValue("impactForce"));
            set => SetFieldValue("impactForce", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Amount of time, in milliseconds, before the projectile is removed from the simulation.</summary>
        /// <description>
        /// Used with fadeDelay to determine the transparency of the projectile at a given time. A projectile may exist up to a maximum of 131040ms (or 4095 ticks) as defined by Projectile::MaxLivingTicks in the source code.
        /// </description>
        /// <see cref="fadeDelay" />
        /// </value>
        public int Lifetime {
            get => GenericMarshal.StringTo<int>(GetFieldValue("lifetime"));
            set => SetFieldValue("lifetime", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Amount of time, in milliseconds, before the projectile will cause damage or explode on impact.</summary>
        /// <description>
        /// This value must be equal to or less than the projectile's lifetime.
        /// </description>
        /// <see cref="lifetime" />
        /// </value>
        public int ArmingDelay {
            get => GenericMarshal.StringTo<int>(GetFieldValue("armingDelay"));
            set => SetFieldValue("armingDelay", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Amount of time, in milliseconds, before the projectile begins to fade out.</summary>
        /// <description>
        /// This value must be smaller than the projectile's lifetime to have an affect.
        /// </description>
        /// </value>
        public int FadeDelay {
            get => GenericMarshal.StringTo<int>(GetFieldValue("fadeDelay"));
            set => SetFieldValue("fadeDelay", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Influences post-bounce velocity of a projectile that does not explode on contact.</summary>
        /// <description>
        /// Scales the velocity from a bounce after friction is taken into account. A value of 1.0 will leave it's velocity unchanged while values greater than 1.0 will increase it.
        /// </description>
        /// </value>
        public float BounceElasticity {
            get => GenericMarshal.StringTo<float>(GetFieldValue("bounceElasticity"));
            set => SetFieldValue("bounceElasticity", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Factor to reduce post-bounce velocity of a projectile that does not explode on contact.</summary>
        /// <description>
        /// Reduces bounce velocity by this factor and a multiple of the tangent to impact. Used to simulate surface friction.
        /// </description>
        /// </value>
        public float BounceFriction {
            get => GenericMarshal.StringTo<float>(GetFieldValue("bounceFriction"));
            set => SetFieldValue("bounceFriction", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Scales the influence of gravity on the projectile.</summary>
        /// <description>
        /// The larger this value is, the more that gravity will affect the projectile. A value of 1.0 will assume "normal" influence upon it.
        /// The magnitude of gravity is assumed to be 9.81 m/s/s
        /// </description>
        /// <remarks> ProjectileData::isBallistic must be true for this to have any affect.</remarks>
        /// </value>
        public float GravityMod {
            get => GenericMarshal.StringTo<float>(GetFieldValue("gravityMod"));
            set => SetFieldValue("gravityMod", GenericMarshal.ToString(value));
        }
    }
}