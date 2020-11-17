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
    /// <summary>Base debris class. Uses the DebrisData datablock for properties of individual debris objects.</summary>
    /// <description>
    /// Debris is typically made up of a shape and up to two particle emitters.  In most cases Debris objects are not created directly.  They are usually produced automatically by other means, such as through the Explosion class.  When an explosion goes off, its ExplosionData datablock determines what Debris to emit.
    /// </description>
    /// <code>
    /// datablock ExplosionData(GrenadeLauncherExplosion)
    /// {
    ///    // Assiging debris data
    ///    debris = GrenadeDebris;
    /// 
    ///    // Adjust how debris is ejected
    ///    debrisThetaMin = 10;
    ///    debrisThetaMax = 60;
    ///    debrisNum = 4;
    ///    debrisNumVariance = 2;
    ///    debrisVelocity = 25;
    ///    debrisVelocityVariance = 5;
    /// 
    ///    // Note: other ExplosionData properties are not listed for this example
    /// };
    /// </code>
    /// <remarks> Debris are client side only objects.
    /// </remarks>
    /// <see cref="DebrisData" />
    /// <see cref="ExplosionData" />
    /// <see cref="Explosion" />
    public unsafe class Debris : GameBase {
        public Debris(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public Debris(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public Debris(string pName) 
            : this(pName, false) {
        }
        
        public Debris(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public Debris(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public Debris(SimObject pObj) 
            : base(pObj) {
        }
        
        public Debris(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct Init__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string inputPosition;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string inputVelocity;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _Init(IntPtr _this, Init__Args args);
            private static _Init _InitFunc;
            internal static _Init Init() {
                if (_InitFunc == null) {
                    _InitFunc =
                        (_Init)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnDebris_init"), typeof(_Init));
                }
                
                return _InitFunc;
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
                                "fnDebris_staticGetType"), typeof(_StaticGetType));
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
                                "fnDebris_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <summary>Manually set this piece of debris at the given position with the given velocity.</summary>
        /// <description>
        /// Usually you do not manually create Debris objects as they are generated through other means, such as an Explosion.  This method exists when you do manually create a Debris object and want to have it start moving.
        /// </description>
        /// <param name="inputPosition">Position to place the debris.</param>
        /// <param name="inputVelocity">Velocity to move the debris after it has been placed.</param>
        /// <returns>Always returns true.</returns>
        /// <code>
        /// // Define the position
        /// %position = "1.0 1.0 1.0";
        /// 
        /// // Define the velocity
        /// %velocity = "1.0 0.0 0.0";
        /// 
        /// // Inform the debris object of its new position and velocity
        /// %debris.init(%position,%velocity);
        /// </code>
        public bool Init(string inputPosition = "1.0 1.0 1.0", string inputVelocity = "1.0 0.0 0.0") {
             InternalUnsafeMethods.Init__Args _args = new InternalUnsafeMethods.Init__Args() {
                inputPosition = inputPosition,
                inputVelocity = inputVelocity,
             };
             bool _engineResult = InternalUnsafeMethods.Init()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Get the type info object for the Debris class.
        /// </description>
        /// <returns>The type info object for Debris</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <summary>Length of time for this debris object to exist. When expired, the object will be deleted.</summary>
        /// <description>
        /// The initial lifetime value comes from the DebrisData datablock.
        /// </description>
        /// <see cref="DebrisData::lifetime" />
        /// <see cref="DebrisData::lifetimeVariance" />
        /// </value>
        public float Lifetime {
            get => GenericMarshal.StringTo<float>(GetFieldValue("lifetime"));
            set => SetFieldValue("lifetime", GenericMarshal.ToString(value));
        }
    }
}