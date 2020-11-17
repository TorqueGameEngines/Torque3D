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
    /// <summary>Defines the attributes of an Explosion: particleEmitters, debris, lighting and camera shake effects.</summary>
    /// <description>
    /// 
    /// </description>
    public unsafe class ExplosionData : GameBaseData {
        public ExplosionData(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public ExplosionData(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public ExplosionData(string pName) 
            : this(pName, false) {
        }
        
        public ExplosionData(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public ExplosionData(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public ExplosionData(SimObject pObj) 
            : base(pObj) {
        }
        
        public ExplosionData(IntPtr pObj) 
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
                                "fnExplosionData_staticGetType"), typeof(_StaticGetType));
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
                                "fnExplosionData_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the ExplosionData class.
        /// </description>
        /// <returns>The type info object for ExplosionData</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <summary>Optional DTS or DAE shape to place at the center of the explosion.</summary>
        /// <description>
        /// The <i>ambient</i> animation of this model will be played automatically at the start of the explosion.
        /// </description>
        /// </value>
        public string ExplosionShape {
            get => GenericMarshal.StringTo<string>(GetFieldValue("explosionShape"));
            set => SetFieldValue("explosionShape", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// "X Y Z" scale factor applied to the explosionShape model at the start of the explosion.
        /// </description>
        /// </value>
        public Point3F ExplosionScale {
            get => GenericMarshal.StringTo<Point3F>(GetFieldValue("explosionScale"));
            set => SetFieldValue("explosionScale", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Time scale at which to play the explosionShape <i>ambient</i> sequence.
        /// </description>
        /// </value>
        public float PlaySpeed {
            get => GenericMarshal.StringTo<float>(GetFieldValue("playSpeed"));
            set => SetFieldValue("playSpeed", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Non-looping sound effect that will be played at the start of the explosion.
        /// </description>
        /// </value>
        public SFXTrack SoundProfile {
            get => GenericMarshal.StringTo<SFXTrack>(GetFieldValue("soundProfile"));
            set => SetFieldValue("soundProfile", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Controls whether the visual effects of the explosion always face the camera.
        /// </description>
        /// </value>
        public bool FaceViewer {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("faceViewer"));
            set => SetFieldValue("faceViewer", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Emitter used to generate a cloud of particles at the start of the explosion.</summary>
        /// <description>
        /// Explosions can generate two different particle effects. The first is a single burst of particles at the start of the explosion emitted in a spherical cloud using particleEmitter.
        /// 
        /// The second effect spawns the list of ParticleEmitters given by the emitter[] field. These emitters generate particles in the normal way throughout the lifetime of the explosion.
        /// </description>
        /// </value>
        public ParticleEmitterData ParticleEmitter {
            get => GenericMarshal.StringTo<ParticleEmitterData>(GetFieldValue("ParticleEmitter"));
            set => SetFieldValue("ParticleEmitter", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Density of the particle cloud created at the start of the explosion.</summary>
        /// <description>
        /// 
        /// </description>
        /// <see cref="particleEmitter" />
        /// </value>
        public int ParticleDensity {
            get => GenericMarshal.StringTo<int>(GetFieldValue("particleDensity"));
            set => SetFieldValue("particleDensity", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Radial distance from the explosion center at which cloud particles are emitted.</summary>
        /// <description>
        /// 
        /// </description>
        /// <see cref="particleEmitter" />
        /// </value>
        public float ParticleRadius {
            get => GenericMarshal.StringTo<float>(GetFieldValue("particleRadius"));
            set => SetFieldValue("particleRadius", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>List of additional ParticleEmitterData objects to spawn with this explosion.</summary>
        /// <description>
        /// 
        /// </description>
        /// <see cref="particleEmitter" />
        /// </value>
        public DynamicFieldVector<ParticleEmitterData> Emitter {
            get => new DynamicFieldVector<ParticleEmitterData>(
                    this, 
                    "emitter", 
                    4, 
                    val => GenericMarshal.StringTo<ParticleEmitterData>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// List of DebrisData objects to spawn with this explosion.
        /// </description>
        /// </value>
        public DebrisData Debris {
            get => GenericMarshal.StringTo<DebrisData>(GetFieldValue("Debris"));
            set => SetFieldValue("Debris", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Minimum angle, from the horizontal plane, to eject debris from.
        /// </description>
        /// </value>
        public float DebrisThetaMin {
            get => GenericMarshal.StringTo<float>(GetFieldValue("debrisThetaMin"));
            set => SetFieldValue("debrisThetaMin", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Maximum angle, from the horizontal plane, to eject debris from.
        /// </description>
        /// </value>
        public float DebrisThetaMax {
            get => GenericMarshal.StringTo<float>(GetFieldValue("debrisThetaMax"));
            set => SetFieldValue("debrisThetaMax", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Minimum reference angle, from the vertical plane, to eject debris from.
        /// </description>
        /// </value>
        public float DebrisPhiMin {
            get => GenericMarshal.StringTo<float>(GetFieldValue("debrisPhiMin"));
            set => SetFieldValue("debrisPhiMin", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Maximum reference angle, from the vertical plane, to eject debris from.
        /// </description>
        /// </value>
        public float DebrisPhiMax {
            get => GenericMarshal.StringTo<float>(GetFieldValue("debrisPhiMax"));
            set => SetFieldValue("debrisPhiMax", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Number of debris objects to create.
        /// </description>
        /// </value>
        public int DebrisNum {
            get => GenericMarshal.StringTo<int>(GetFieldValue("debrisNum"));
            set => SetFieldValue("debrisNum", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Variance in the number of debris objects to create (must be from 0 - debrisNum).
        /// </description>
        /// </value>
        public int DebrisNumVariance {
            get => GenericMarshal.StringTo<int>(GetFieldValue("debrisNumVariance"));
            set => SetFieldValue("debrisNumVariance", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Velocity to toss debris at.
        /// </description>
        /// </value>
        public float DebrisVelocity {
            get => GenericMarshal.StringTo<float>(GetFieldValue("debrisVelocity"));
            set => SetFieldValue("debrisVelocity", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Variance in the debris initial velocity (must be >= 0).
        /// </description>
        /// </value>
        public float DebrisVelocityVariance {
            get => GenericMarshal.StringTo<float>(GetFieldValue("debrisVelocityVariance"));
            set => SetFieldValue("debrisVelocityVariance", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// List of additional ExplosionData objects to create at the start of the explosion.
        /// </description>
        /// </value>
        public DynamicFieldVector<ExplosionData> SubExplosion {
            get => new DynamicFieldVector<ExplosionData>(
                    this, 
                    "subExplosion", 
                    5, 
                    val => GenericMarshal.StringTo<ExplosionData>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Amount of time, in milliseconds, to delay the start of the explosion effect from the creation of the Explosion object.
        /// </description>
        /// </value>
        public int DelayMS {
            get => GenericMarshal.StringTo<int>(GetFieldValue("delayMS"));
            set => SetFieldValue("delayMS", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Variance, in milliseconds, of delayMS.
        /// </description>
        /// </value>
        public int DelayVariance {
            get => GenericMarshal.StringTo<int>(GetFieldValue("delayVariance"));
            set => SetFieldValue("delayVariance", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Lifetime, in milliseconds, of the Explosion object.</summary>
        /// <description>
        /// 
        /// </description>
        /// <remarks> If explosionShape is defined and contains an <i>ambient</i> animation, this field is ignored, and the playSpeed scaled duration of the animation is used instead.</remarks>
        /// </value>
        public int LifetimeMS {
            get => GenericMarshal.StringTo<int>(GetFieldValue("lifetimeMS"));
            set => SetFieldValue("lifetimeMS", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Variance, in milliseconds, of the lifetimeMS of the Explosion object.
        /// </description>
        /// </value>
        public int LifetimeVariance {
            get => GenericMarshal.StringTo<int>(GetFieldValue("lifetimeVariance"));
            set => SetFieldValue("lifetimeVariance", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Offset distance (in a random direction) of the center of the explosion from the Explosion object position.</summary>
        /// <description>
        /// Most often used to create some variance in position for subExplosion effects.
        /// </description>
        /// </value>
        public float Offset {
            get => GenericMarshal.StringTo<float>(GetFieldValue("offset"));
            set => SetFieldValue("offset", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Time keyframes used to scale the explosionShape model.</summary>
        /// <description>
        /// Values should be in increasing order from 0.0 - 1.0, and correspond to the life of the Explosion where 0 is the beginning and 1 is the end of the explosion lifetime.
        /// </description>
        /// <see cref="lifetimeMS" />
        /// </value>
        public DynamicFieldVector<float> Times {
            get => new DynamicFieldVector<float>(
                    this, 
                    "times", 
                    4, 
                    val => GenericMarshal.StringTo<float>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <summary>"X Y Z" size keyframes used to scale the explosionShape model.</summary>
        /// <description>
        /// The explosionShape (if defined) will be scaled using the times/sizes keyframes over the lifetime of the explosion.
        /// </description>
        /// <see cref="lifetimeMS" />
        /// </value>
        public DynamicFieldVector<Point3F> Sizes {
            get => new DynamicFieldVector<Point3F>(
                    this, 
                    "sizes", 
                    4, 
                    val => GenericMarshal.StringTo<Point3F>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Controls whether the camera shakes during this explosion.
        /// </description>
        /// </value>
        public bool ShakeCamera {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("ShakeCamera"));
            set => SetFieldValue("ShakeCamera", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Frequency of camera shaking, defined in the "X Y Z" axes.
        /// </description>
        /// </value>
        public Point3F CamShakeFreq {
            get => GenericMarshal.StringTo<Point3F>(GetFieldValue("camShakeFreq"));
            set => SetFieldValue("camShakeFreq", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Amplitude of camera shaking, defined in the "X Y Z" axes.</summary>
        /// <description>
        /// Set any value to 0 to disable shaking in that axis.
        /// </description>
        /// </value>
        public Point3F CamShakeAmp {
            get => GenericMarshal.StringTo<Point3F>(GetFieldValue("camShakeAmp"));
            set => SetFieldValue("camShakeAmp", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Duration (in seconds) to shake the camera.
        /// </description>
        /// </value>
        public float CamShakeDuration {
            get => GenericMarshal.StringTo<float>(GetFieldValue("camShakeDuration"));
            set => SetFieldValue("camShakeDuration", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Radial distance that a camera's position must be within relative to the center of the explosion to be shaken.
        /// </description>
        /// </value>
        public float CamShakeRadius {
            get => GenericMarshal.StringTo<float>(GetFieldValue("camShakeRadius"));
            set => SetFieldValue("camShakeRadius", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Falloff value for the camera shake.
        /// </description>
        /// </value>
        public float CamShakeFalloff {
            get => GenericMarshal.StringTo<float>(GetFieldValue("camShakeFalloff"));
            set => SetFieldValue("camShakeFalloff", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Initial radius of the PointLight created by this explosion.</summary>
        /// <description>
        /// Radius is linearly interpolated from lightStartRadius to lightEndRadius over the lifetime of the explosion.
        /// </description>
        /// <see cref="lifetimeMS" />
        /// </value>
        public float LightStartRadius {
            get => GenericMarshal.StringTo<float>(GetFieldValue("lightStartRadius"));
            set => SetFieldValue("lightStartRadius", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Final radius of the PointLight created by this explosion.</summary>
        /// <description>
        /// 
        /// </description>
        /// <see cref="lightStartRadius" />
        /// </value>
        public float LightEndRadius {
            get => GenericMarshal.StringTo<float>(GetFieldValue("lightEndRadius"));
            set => SetFieldValue("lightEndRadius", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Initial color of the PointLight created by this explosion.</summary>
        /// <description>
        /// Color is linearly interpolated from lightStartColor to lightEndColor over the lifetime of the explosion.
        /// </description>
        /// <see cref="lifetimeMS" />
        /// </value>
        public LinearColorF LightStartColor {
            get => GenericMarshal.StringTo<LinearColorF>(GetFieldValue("lightStartColor"));
            set => SetFieldValue("lightStartColor", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Final color of the PointLight created by this explosion.</summary>
        /// <description>
        /// 
        /// </description>
        /// <see cref="lightStartColor" />
        /// </value>
        public LinearColorF LightEndColor {
            get => GenericMarshal.StringTo<LinearColorF>(GetFieldValue("lightEndColor"));
            set => SetFieldValue("lightEndColor", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Initial brightness of the PointLight created by this explosion.</summary>
        /// <description>
        /// Brightness is linearly interpolated from lightStartBrightness to lightEndBrightness over the lifetime of the explosion.
        /// </description>
        /// <see cref="lifetimeMS" />
        /// </value>
        public float LightStartBrightness {
            get => GenericMarshal.StringTo<float>(GetFieldValue("lightStartBrightness"));
            set => SetFieldValue("lightStartBrightness", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Final brightness of the PointLight created by this explosion.</summary>
        /// <description>
        /// 
        /// </description>
        /// <see cref="lightStartBrightness" />
        /// </value>
        public float LightEndBrightness {
            get => GenericMarshal.StringTo<float>(GetFieldValue("lightEndBrightness"));
            set => SetFieldValue("lightEndBrightness", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Distance (in the explosion normal direction) of the PointLight position from the explosion center.
        /// </description>
        /// </value>
        public float LightNormalOffset {
            get => GenericMarshal.StringTo<float>(GetFieldValue("lightNormalOffset"));
            set => SetFieldValue("lightNormalOffset", GenericMarshal.ToString(value));
        }
    }
}