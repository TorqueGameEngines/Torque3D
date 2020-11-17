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
    /// <summary>Contains information for how specific particles should look and react including particle colors, particle imagemap, acceleration value for individual particles and spin information.</summary>
    /// <description>
    /// 
    /// </description>
    /// <code>
    /// datablock ParticleData( GLWaterExpSmoke )
    /// {
    ///    textureName = "art/shapes/particles/smoke";
    ///    dragCoefficient = 0.4;
    ///    gravityCoefficient = -0.25;
    ///    inheritedVelFactor = 0.025;
    ///    constantAcceleration = -1.1;
    ///    lifetimeMS = 1250;
    ///    lifetimeVarianceMS = 0;
    ///    useInvAlpha = false;
    ///    spinSpeed = 1;
    ///    spinRandomMin = -200.0;
    ///    spinRandomMax = 200.0;
    /// 
    ///    colors[0] = "0.1 0.1 1.0 1.0";
    ///    colors[1] = "0.4 0.4 1.0 1.0";
    ///    colors[2] = "0.4 0.4 1.0 0.0";
    /// 
    ///    sizes[0] = 2.0;
    ///    sizes[1] = 6.0;
    ///    sizes[2] = 2.0;
    /// 
    ///    times[0] = 0.0;
    ///    times[1] = 0.5;
    ///    times[2] = 1.0;
    /// };
    /// </code>
    /// <see cref="ParticleEmitter" />
    /// <see cref="ParticleEmitterData" />
    /// <see cref="ParticleEmitterNode" />
    public unsafe class ParticleData : SimDataBlock {
        public ParticleData(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public ParticleData(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public ParticleData(string pName) 
            : this(pName, false) {
        }
        
        public ParticleData(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public ParticleData(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public ParticleData(SimObject pObj) 
            : base(pObj) {
        }
        
        public ParticleData(IntPtr pObj) 
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
                                "fnParticleData_reload"), typeof(_Reload));
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
                                "fnParticleData_staticGetType"), typeof(_StaticGetType));
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
                                "fnParticleData_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Reloads this particle.
        /// </description>
        /// <code>
        /// // Get the editor's current particle
        /// %particle = PE_ParticleEditor.currParticle
        /// 
        /// // Change a particle value
        /// %particle.setFieldValue( %propertyField, %value );
        /// 
        /// // Reload it
        /// %particle.reload();
        /// </code>
        public void Reload() {
             InternalUnsafeMethods.Reload__Args _args = new InternalUnsafeMethods.Reload__Args() {
             };
             InternalUnsafeMethods.Reload()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the ParticleData class.
        /// </description>
        /// <returns>The type info object for ParticleData</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Particle physics drag amount.
        /// </description>
        /// </value>
        public float DragCoefficient {
            get => GenericMarshal.StringTo<float>(GetFieldValue("dragCoefficient"));
            set => SetFieldValue("dragCoefficient", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Strength of wind on the particles.
        /// </description>
        /// </value>
        public float WindCoefficient {
            get => GenericMarshal.StringTo<float>(GetFieldValue("windCoefficient"));
            set => SetFieldValue("windCoefficient", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Strength of gravity on the particles.
        /// </description>
        /// </value>
        public float GravityCoefficient {
            get => GenericMarshal.StringTo<float>(GetFieldValue("gravityCoefficient"));
            set => SetFieldValue("gravityCoefficient", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Amount of emitter velocity to add to particle initial velocity.
        /// </description>
        /// </value>
        public float InheritedVelFactor {
            get => GenericMarshal.StringTo<float>(GetFieldValue("inheritedVelFactor"));
            set => SetFieldValue("inheritedVelFactor", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Constant acceleration to apply to this particle.
        /// </description>
        /// </value>
        public float ConstantAcceleration {
            get => GenericMarshal.StringTo<float>(GetFieldValue("constantAcceleration"));
            set => SetFieldValue("constantAcceleration", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Time in milliseconds before this particle is destroyed.
        /// </description>
        /// </value>
        public int LifetimeMS {
            get => GenericMarshal.StringTo<int>(GetFieldValue("lifetimeMS"));
            set => SetFieldValue("lifetimeMS", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Variance in lifetime of particle, from 0 - lifetimeMS.
        /// </description>
        /// </value>
        public int LifetimeVarianceMS {
            get => GenericMarshal.StringTo<int>(GetFieldValue("lifetimeVarianceMS"));
            set => SetFieldValue("lifetimeVarianceMS", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Speed at which to spin the particle.
        /// </description>
        /// </value>
        public float SpinSpeed {
            get => GenericMarshal.StringTo<float>(GetFieldValue("spinSpeed"));
            set => SetFieldValue("spinSpeed", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Minimum allowed spin speed of this particle, between -1000 and spinRandomMax.
        /// </description>
        /// </value>
        public float SpinRandomMin {
            get => GenericMarshal.StringTo<float>(GetFieldValue("spinRandomMin"));
            set => SetFieldValue("spinRandomMin", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Maximum allowed spin speed of this particle, between spinRandomMin and 1000.
        /// </description>
        /// </value>
        public float SpinRandomMax {
            get => GenericMarshal.StringTo<float>(GetFieldValue("spinRandomMax"));
            set => SetFieldValue("spinRandomMax", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Controls how particles blend with the scene.</summary>
        /// <description>
        /// If true, particles blend like ParticleBlendStyle NORMAL, if false, blend like ParticleBlendStyle ADDITIVE.
        /// </description>
        /// <remarks> If ParticleEmitterData::blendStyle is set, it will override this value.</remarks>
        /// </value>
        public bool UseInvAlpha {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("useInvAlpha"));
            set => SetFieldValue("useInvAlpha", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// If true, allow the particle texture to be an animated sprite.
        /// </description>
        /// </value>
        public bool AnimateTexture {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("animateTexture"));
            set => SetFieldValue("animateTexture", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// If animateTexture is true, this defines the frames per second of the sprite animation.
        /// </description>
        /// </value>
        public int FramesPerSec {
            get => GenericMarshal.StringTo<int>(GetFieldValue("framesPerSec"));
            set => SetFieldValue("framesPerSec", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>4 element array defining the UV coords into textureName to use for this particle.</summary>
        /// <description>
        /// Coords should be set for the first tile only when using animTexTiling; coordinates for other tiles will be calculated automatically. "0 0" is top left and "1 1" is bottom right.
        /// </description>
        /// </value>
        public DynamicFieldVector<Point2F> TextureCoords {
            get => new DynamicFieldVector<Point2F>(
                    this, 
                    "textureCoords", 
                    4, 
                    val => GenericMarshal.StringTo<Point2F>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <summary>The number of frames, in rows and columns stored in textureName (when animateTexture is true).</summary>
        /// <description>
        /// A maximum of 256 frames can be stored in a single texture when using animTexTiling. Value should be "NumColumns NumRows", for example "4 4".
        /// </description>
        /// </value>
        public Point2I AnimTexTiling {
            get => GenericMarshal.StringTo<Point2I>(GetFieldValue("animTexTiling"));
            set => SetFieldValue("animTexTiling", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>A list of frames and/or frame ranges to use for particle animation if animateTexture is true.</summary>
        /// <description>
        /// Each frame token must be separated by whitespace. A frame token must be a positive integer frame number or a range of frame numbers separated with a '-'. The range separator, '-', cannot have any whitspace around it.
        /// 
        /// Ranges can be specified to move through the frames in reverse as well as forward (eg. 19-14). Frame numbers exceeding the number of tiles will wrap.
        /// </description>
        /// <code>
        /// animTexFrames = "0-16 20 19 18 17 31-21";
        /// </code>
        /// </value>
        public string AnimTexFrames {
            get => GenericMarshal.StringTo<string>(GetFieldValue("animTexFrames"));
            set => SetFieldValue("animTexFrames", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Texture file to use for this particle.
        /// </description>
        /// </value>
        public string TextureName {
            get => GenericMarshal.StringTo<string>(GetFieldValue("textureName"));
            set => SetFieldValue("textureName", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Texture file to use for this particle if animateTexture is true.</summary>
        /// <description>
        /// Deprecated. Use textureName instead.
        /// </description>
        /// </value>
        public string AnimTexName {
            get => GenericMarshal.StringTo<string>(GetFieldValue("animTexName"));
            set => SetFieldValue("animTexName", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Particle RGBA color keyframe values.</summary>
        /// <description>
        /// The particle color will linearly interpolate between the color/time keys over the lifetime of the particle.
        /// </description>
        /// </value>
        public DynamicFieldVector<LinearColorF> Colors {
            get => new DynamicFieldVector<LinearColorF>(
                    this, 
                    "colors", 
                    8, 
                    val => GenericMarshal.StringTo<LinearColorF>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <summary>Particle size keyframe values.</summary>
        /// <description>
        /// The particle size will linearly interpolate between the size/time keys over the lifetime of the particle.
        /// </description>
        /// </value>
        public DynamicFieldVector<float> Sizes {
            get => new DynamicFieldVector<float>(
                    this, 
                    "sizes", 
                    8, 
                    val => GenericMarshal.StringTo<float>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <summary>Time keys used with the colors and sizes keyframes.</summary>
        /// <description>
        /// Values are from 0.0 (particle creation) to 1.0 (end of lifespace).
        /// </description>
        /// </value>
        public DynamicFieldVector<float> Times {
            get => new DynamicFieldVector<float>(
                    this, 
                    "times", 
                    8, 
                    val => GenericMarshal.StringTo<float>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// 
        /// </value>
        public string TextureExtName {
            get => GenericMarshal.StringTo<string>(GetFieldValue("textureExtName"));
            set => SetFieldValue("textureExtName", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public bool ConstrainPos {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("constrainPos"));
            set => SetFieldValue("constrainPos", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public float Angle {
            get => GenericMarshal.StringTo<float>(GetFieldValue("angle"));
            set => SetFieldValue("angle", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public float AngleVariance {
            get => GenericMarshal.StringTo<float>(GetFieldValue("angleVariance"));
            set => SetFieldValue("angleVariance", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public float SizeBias {
            get => GenericMarshal.StringTo<float>(GetFieldValue("sizeBias"));
            set => SetFieldValue("sizeBias", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public float SpinBias {
            get => GenericMarshal.StringTo<float>(GetFieldValue("spinBias"));
            set => SetFieldValue("spinBias", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public bool RandomizeSpinDir {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("randomizeSpinDir"));
            set => SetFieldValue("randomizeSpinDir", GenericMarshal.ToString(value));
        }
    }
}