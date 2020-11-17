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
    /// <summary>Defines particle emission properties such as ejection angle, period and velocity for a ParticleEmitter.</summary>
    /// <description>
    /// 
    /// </description>
    /// <code>
    /// datablock ParticleEmitterData( GrenadeExpDustEmitter )
    /// {
    ///    ejectionPeriodMS = 1;
    ///    periodVarianceMS = 0;
    ///    ejectionVelocity = 15;
    ///    velocityVariance = 0.0;
    ///    ejectionOffset = 0.0;
    ///    thetaMin = 85;
    ///    thetaMax = 85;
    ///    phiReferenceVel = 0;
    ///    phiVariance = 360;
    ///    overrideAdvance = false;
    ///    lifetimeMS = 200;
    ///    particles = "GrenadeExpDust";
    /// };
    /// </code>
    /// <see cref="ParticleEmitter" />
    /// <see cref="ParticleData" />
    /// <see cref="ParticleEmitterNode" />
    public unsafe class ParticleEmitterData : GameBaseData {
        public ParticleEmitterData(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public ParticleEmitterData(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public ParticleEmitterData(string pName) 
            : this(pName, false) {
        }
        
        public ParticleEmitterData(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public ParticleEmitterData(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public ParticleEmitterData(SimObject pObj) 
            : base(pObj) {
        }
        
        public ParticleEmitterData(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct Reload__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Reload(IntPtr _this, Reload__Args args);
            private static _Reload _ReloadFunc;
            internal static _Reload Reload() {
                if (_ReloadFunc == null) {
                    _ReloadFunc =
                        (_Reload)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnParticleEmitterData_reload"), typeof(_Reload));
                }
                
                return _ReloadFunc;
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
                                "fnParticleEmitterData_staticGetType"), typeof(_StaticGetType));
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
                                "fnParticleEmitterData_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Reloads the ParticleData datablocks and other fields used by this emitter.
        /// </description>
        /// <code>
        /// // Get the editor's current particle emitter
        /// %emitter = PE_EmitterEditor.currEmitter
        /// 
        /// // Change a field value
        /// %emitter.setFieldValue( %propertyField, %value );
        /// 
        /// // Reload this emitter
        /// %emitter.reload();
        /// </code>
        public void Reload() {
             InternalUnsafeMethods.Reload__Args _args = new InternalUnsafeMethods.Reload__Args() {
             };
             InternalUnsafeMethods.Reload()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the ParticleEmitterData class.
        /// </description>
        /// <returns>The type info object for ParticleEmitterData</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Time (in milliseconds) between each particle ejection.
        /// </description>
        /// </value>
        public int EjectionPeriodMS {
            get => GenericMarshal.StringTo<int>(GetFieldValue("ejectionPeriodMS"));
            set => SetFieldValue("ejectionPeriodMS", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Variance in ejection period, from 1 - ejectionPeriodMS.
        /// </description>
        /// </value>
        public int PeriodVarianceMS {
            get => GenericMarshal.StringTo<int>(GetFieldValue("periodVarianceMS"));
            set => SetFieldValue("periodVarianceMS", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Particle ejection velocity.
        /// </description>
        /// </value>
        public float EjectionVelocity {
            get => GenericMarshal.StringTo<float>(GetFieldValue("ejectionVelocity"));
            set => SetFieldValue("ejectionVelocity", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Variance for ejection velocity, from 0 - ejectionVelocity.
        /// </description>
        /// </value>
        public float VelocityVariance {
            get => GenericMarshal.StringTo<float>(GetFieldValue("velocityVariance"));
            set => SetFieldValue("velocityVariance", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Distance along ejection Z axis from which to eject particles.
        /// </description>
        /// </value>
        public float EjectionOffset {
            get => GenericMarshal.StringTo<float>(GetFieldValue("ejectionOffset"));
            set => SetFieldValue("ejectionOffset", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Distance Padding along ejection Z axis from which to eject particles.
        /// </description>
        /// </value>
        public float EjectionOffsetVariance {
            get => GenericMarshal.StringTo<float>(GetFieldValue("ejectionOffsetVariance"));
            set => SetFieldValue("ejectionOffsetVariance", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Minimum angle, from the horizontal plane, to eject from.
        /// </description>
        /// </value>
        public float ThetaMin {
            get => GenericMarshal.StringTo<float>(GetFieldValue("thetaMin"));
            set => SetFieldValue("thetaMin", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Maximum angle, from the horizontal plane, to eject particles from.
        /// </description>
        /// </value>
        public float ThetaMax {
            get => GenericMarshal.StringTo<float>(GetFieldValue("thetaMax"));
            set => SetFieldValue("thetaMax", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Reference angle, from the vertical plane, to eject particles from.
        /// </description>
        /// </value>
        public float PhiReferenceVel {
            get => GenericMarshal.StringTo<float>(GetFieldValue("phiReferenceVel"));
            set => SetFieldValue("phiReferenceVel", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Variance from the reference angle, from 0 - 360.
        /// </description>
        /// </value>
        public float PhiVariance {
            get => GenericMarshal.StringTo<float>(GetFieldValue("phiVariance"));
            set => SetFieldValue("phiVariance", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// For soft particles, the distance (in meters) where particles will be faded based on the difference in depth between the particle and the scene geometry.
        /// </description>
        /// </value>
        public float SoftnessDistance {
            get => GenericMarshal.StringTo<float>(GetFieldValue("softnessDistance"));
            set => SetFieldValue("softnessDistance", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Used to generate the final particle color by controlling interpolation between the particle color and the particle color multiplied by the ambient light color.
        /// </description>
        /// </value>
        public float AmbientFactor {
            get => GenericMarshal.StringTo<float>(GetFieldValue("ambientFactor"));
            set => SetFieldValue("ambientFactor", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// If false, particles emitted in the same frame have their positions adjusted. If true, adjustment is skipped and particles will clump together.
        /// </description>
        /// </value>
        public bool OverrideAdvance {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("overrideAdvance"));
            set => SetFieldValue("overrideAdvance", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// If true, Particles will always face the camera.
        /// </description>
        /// </value>
        public bool OrientParticles {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("orientParticles"));
            set => SetFieldValue("orientParticles", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// If true, particles will be oriented to face in the direction they are moving.
        /// </description>
        /// </value>
        public bool OrientOnVelocity {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("orientOnVelocity"));
            set => SetFieldValue("orientOnVelocity", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>List of space or TAB delimited ParticleData datablock names.</summary>
        /// <description>
        /// A random one of these datablocks is selected each time a particle is emitted.
        /// </description>
        /// </value>
        public string Particles {
            get => GenericMarshal.StringTo<string>(GetFieldValue("particles"));
            set => SetFieldValue("particles", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Lifetime of emitted particles (in milliseconds).
        /// </description>
        /// </value>
        public int LifetimeMS {
            get => GenericMarshal.StringTo<int>(GetFieldValue("lifetimeMS"));
            set => SetFieldValue("lifetimeMS", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Variance in particle lifetime from 0 - lifetimeMS.
        /// </description>
        /// </value>
        public int LifetimeVarianceMS {
            get => GenericMarshal.StringTo<int>(GetFieldValue("lifetimeVarianceMS"));
            set => SetFieldValue("lifetimeVarianceMS", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>If true, use emitter specified sizes instead of datablock sizes.</summary>
        /// <description>
        /// Useful for Debris particle emitters that control the particle size.
        /// </description>
        /// </value>
        public bool UseEmitterSizes {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("useEmitterSizes"));
            set => SetFieldValue("useEmitterSizes", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>If true, use emitter specified colors instead of datablock colors.</summary>
        /// <description>
        /// Useful for ShapeBase dust and WheeledVehicle wheel particle emitters that use the current material to control particle color.
        /// </description>
        /// </value>
        public bool UseEmitterColors {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("useEmitterColors"));
            set => SetFieldValue("useEmitterColors", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// String value that controls how emitted particles blend with the scene.
        /// </description>
        /// </value>
        public ParticleBlendStyle BlendStyle {
            get => GenericMarshal.StringTo<ParticleBlendStyle>(GetFieldValue("blendStyle"));
            set => SetFieldValue("blendStyle", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// If true, particles are sorted furthest to nearest.
        /// </description>
        /// </value>
        public bool SortParticles {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("sortParticles"));
            set => SetFieldValue("sortParticles", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>If true, reverses the normal draw order of particles.</summary>
        /// <description>
        /// Particles are normally drawn from newest to oldest, or in Z order (furthest first) if sortParticles is true. Setting this field to true will reverse that order: oldest first, or nearest first if sortParticles is true.
        /// </description>
        /// </value>
        public bool ReverseOrder {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("reverseOrder"));
            set => SetFieldValue("reverseOrder", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Optional texture to override ParticleData::textureName.
        /// </description>
        /// </value>
        public string TextureName {
            get => GenericMarshal.StringTo<string>(GetFieldValue("textureName"));
            set => SetFieldValue("textureName", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// If true, particles always face along the axis defined by alignDirection.
        /// </description>
        /// </value>
        public bool AlignParticles {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("alignParticles"));
            set => SetFieldValue("alignParticles", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The direction aligned particles should face, only valid if alignParticles is true.
        /// </description>
        /// </value>
        public Point3F AlignDirection {
            get => GenericMarshal.StringTo<Point3F>(GetFieldValue("alignDirection"));
            set => SetFieldValue("alignDirection", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// This particle system should not use the mixed-resolution renderer. If your particle system has large amounts of overdraw, consider disabling this option.
        /// </description>
        /// </value>
        public bool HighResOnly {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("highResOnly"));
            set => SetFieldValue("highResOnly", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Controls whether particles are rendered onto reflective surfaces like water.
        /// </description>
        /// </value>
        public bool RenderReflection {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("renderReflection"));
            set => SetFieldValue("renderReflection", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// If true, the particles are rendered to the glow buffer as well.
        /// </description>
        /// </value>
        public bool Glow {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("glow"));
            set => SetFieldValue("glow", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public bool EjectionInvert {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("ejectionInvert"));
            set => SetFieldValue("ejectionInvert", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public bool FadeColor {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("fadeColor"));
            set => SetFieldValue("fadeColor", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public bool FadeAlpha {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("fadeAlpha"));
            set => SetFieldValue("fadeAlpha", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public bool FadeSize {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("fadeSize"));
            set => SetFieldValue("fadeSize", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public bool UseEmitterTransform {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("useEmitterTransform"));
            set => SetFieldValue("useEmitterTransform", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public afxParticlePoolData PoolData {
            get => GenericMarshal.StringTo<afxParticlePoolData>(GetFieldValue("poolData"));
            set => SetFieldValue("poolData", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public int PoolIndex {
            get => GenericMarshal.StringTo<int>(GetFieldValue("poolIndex"));
            set => SetFieldValue("poolIndex", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public bool PoolDepthFade {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("poolDepthFade"));
            set => SetFieldValue("poolDepthFade", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public bool PoolRadialFade {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("poolRadialFade"));
            set => SetFieldValue("poolRadialFade", GenericMarshal.ToString(value));
        }
    }
}