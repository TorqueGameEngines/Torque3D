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
    /// <summary>Acts as the physical point in space in white a Splash is created from.</summary>
    /// <description>
    /// 
    /// </description>
    public unsafe class SplashData : GameBaseData {
        public SplashData(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public SplashData(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public SplashData(string pName) 
            : this(pName, false) {
        }
        
        public SplashData(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public SplashData(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public SplashData(SimObject pObj) 
            : base(pObj) {
        }
        
        public SplashData(IntPtr pObj) 
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
                                "fnSplashData_staticGetType"), typeof(_StaticGetType));
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
                                "fnSplashData_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the SplashData class.
        /// </description>
        /// <returns>The type info object for SplashData</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// SFXProfile effect to play.
        /// </description>
        /// </value>
        public SFXProfile SoundProfile {
            get => GenericMarshal.StringTo<SFXProfile>(GetFieldValue("soundProfile"));
            set => SetFieldValue("soundProfile", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The scale of this splashing effect, defined as the F32 points X, Y, Z.
        /// </description>
        /// </value>
        public Point3F Scale {
            get => GenericMarshal.StringTo<Point3F>(GetFieldValue("scale"));
            set => SetFieldValue("scale", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// List of particle emitters to create at the point of this Splash effect.
        /// </description>
        /// </value>
        public DynamicFieldVector<ParticleEmitterData> Emitter {
            get => new DynamicFieldVector<ParticleEmitterData>(
                    this, 
                    "emitter", 
                    3, 
                    val => GenericMarshal.StringTo<ParticleEmitterData>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Time to delay, in milliseconds, before actually starting this effect.
        /// </description>
        /// </value>
        public int DelayMS {
            get => GenericMarshal.StringTo<int>(GetFieldValue("delayMS"));
            set => SetFieldValue("delayMS", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Time variance for delayMS.
        /// </description>
        /// </value>
        public int DelayVariance {
            get => GenericMarshal.StringTo<int>(GetFieldValue("delayVariance"));
            set => SetFieldValue("delayVariance", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Lifetime for this effect, in milliseconds.
        /// </description>
        /// </value>
        public int LifetimeMS {
            get => GenericMarshal.StringTo<int>(GetFieldValue("lifetimeMS"));
            set => SetFieldValue("lifetimeMS", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Time variance for lifetimeMS.
        /// </description>
        /// </value>
        public int LifetimeVariance {
            get => GenericMarshal.StringTo<int>(GetFieldValue("lifetimeVariance"));
            set => SetFieldValue("lifetimeVariance", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Width for the X and Y coordinates to create this effect within.
        /// </description>
        /// </value>
        public float Width {
            get => GenericMarshal.StringTo<float>(GetFieldValue("width"));
            set => SetFieldValue("width", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Number of ejection points in the splash ring.
        /// </description>
        /// </value>
        public int NumSegments {
            get => GenericMarshal.StringTo<int>(GetFieldValue("numSegments"));
            set => SetFieldValue("numSegments", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Velocity for the splash effect to travel.
        /// </description>
        /// </value>
        public float Velocity {
            get => GenericMarshal.StringTo<float>(GetFieldValue("velocity"));
            set => SetFieldValue("velocity", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Height for the splash to reach.
        /// </description>
        /// </value>
        public float Height {
            get => GenericMarshal.StringTo<float>(GetFieldValue("height"));
            set => SetFieldValue("height", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Constant acceleration value to place upon the splash effect.
        /// </description>
        /// </value>
        public float Acceleration {
            get => GenericMarshal.StringTo<float>(GetFieldValue("acceleration"));
            set => SetFieldValue("acceleration", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Times to transition through the splash effect. Up to 4 allowed. Values are 0.0 - 1.0, and corrispond to the life of the particle where 0 is first created and 1 is end of lifespace.
        /// </description>
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
        /// <description>
        /// Color values to set the splash effect, rgba. Up to 4 allowed. Will transition through colors based on values set in the times value. Example: colors[0] = "0.6 1.0 1.0 0.5".
        /// </description>
        /// </value>
        public DynamicFieldVector<LinearColorF> Colors {
            get => new DynamicFieldVector<LinearColorF>(
                    this, 
                    "colors", 
                    4, 
                    val => GenericMarshal.StringTo<LinearColorF>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Imagemap file to use as the texture for the splash effect.
        /// </description>
        /// </value>
        public DynamicFieldVector<string> Texture {
            get => new DynamicFieldVector<string>(
                    this, 
                    "texture", 
                    2, 
                    val => GenericMarshal.StringTo<string>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Amount to wrap the texture around the splash ring, 0.0f - 1.0f.
        /// </description>
        /// </value>
        public float TexWrap {
            get => GenericMarshal.StringTo<float>(GetFieldValue("texWrap"));
            set => SetFieldValue("texWrap", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Factor in which to apply the texture to the splash ring, 0.0f - 1.0f.
        /// </description>
        /// </value>
        public float TexFactor {
            get => GenericMarshal.StringTo<float>(GetFieldValue("texFactor"));
            set => SetFieldValue("texFactor", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Frequency in which to emit splash rings.
        /// </description>
        /// </value>
        public float EjectionFreq {
            get => GenericMarshal.StringTo<float>(GetFieldValue("ejectionFreq"));
            set => SetFieldValue("ejectionFreq", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Rotational angle to create a splash ring.
        /// </description>
        /// </value>
        public float EjectionAngle {
            get => GenericMarshal.StringTo<float>(GetFieldValue("ejectionAngle"));
            set => SetFieldValue("ejectionAngle", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Lifetime, in milliseconds, for a splash ring.
        /// </description>
        /// </value>
        public float RingLifetime {
            get => GenericMarshal.StringTo<float>(GetFieldValue("ringLifetime"));
            set => SetFieldValue("ringLifetime", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Starting radius size of a splash ring.
        /// </description>
        /// </value>
        public float StartRadius {
            get => GenericMarshal.StringTo<float>(GetFieldValue("startRadius"));
            set => SetFieldValue("startRadius", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// ExplosionData object to create at the creation position of this splash effect.
        /// </description>
        /// </value>
        public ExplosionData Explosion {
            get => GenericMarshal.StringTo<ExplosionData>(GetFieldValue("Explosion"));
            set => SetFieldValue("Explosion", GenericMarshal.ToString(value));
        }
    }
}