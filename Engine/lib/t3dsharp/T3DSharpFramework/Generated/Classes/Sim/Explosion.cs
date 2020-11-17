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
    /// <summary>The emitter for an explosion effect, with properties defined by a ExplosionData object.</summary>
    /// <description>
    /// 
    /// </description>
    /// <code>
    /// datablock ExplosionData( GrenadeSubExplosion )
    /// {
    ///    offset = 0.25;
    ///    emitter[0] = GrenadeExpSparkEmitter;
    /// 
    ///    lightStartRadius = 4.0;
    ///    lightEndRadius = 0.0;
    ///    lightStartColor = "0.9 0.7 0.7";
    ///    lightEndColor = "0.9 0.7 0.7";
    ///    lightStartBrightness = 2.0;
    ///    lightEndBrightness = 0.0;
    /// };
    /// 
    /// datablock ExplosionData( GrenadeLauncherExplosion )
    /// {
    ///    soundProfile = GrenadeLauncherExplosionSound;
    ///    lifeTimeMS = 400; // Quick flash, short burn, and moderate dispersal
    /// 
    ///    // Volume particles
    ///    particleEmitter = GrenadeExpFireEmitter;
    ///    particleDensity = 75;
    ///    particleRadius = 2.25;
    /// 
    ///    // Point emission
    ///    emitter[0] = GrenadeExpDustEmitter;
    ///    emitter[1] = GrenadeExpSparksEmitter;
    ///    emitter[2] = GrenadeExpSmokeEmitter;
    /// 
    ///    // Sub explosion objects
    ///    subExplosion[0] = GrenadeSubExplosion;
    /// 
    ///    // Camera Shaking
    ///    shakeCamera = true;
    ///    camShakeFreq = "10.0 11.0 9.0";
    ///    camShakeAmp = "15.0 15.0 15.0";
    ///    camShakeDuration = 1.5;
    ///    camShakeRadius = 20;
    /// 
    ///    // Exploding debris
    ///    debris = GrenadeDebris;
    ///    debrisThetaMin = 10;
    ///    debrisThetaMax = 60;
    ///    debrisNum = 4;
    ///    debrisNumVariance = 2;
    ///    debrisVelocity = 25;
    ///    debrisVelocityVariance = 5;
    /// 
    ///    lightStartRadius = 4.0;
    ///    lightEndRadius = 0.0;
    ///    lightStartColor = "1.0 1.0 1.0";
    ///    lightEndColor = "1.0 1.0 1.0";
    ///    lightStartBrightness = 4.0;
    ///    lightEndBrightness = 0.0;
    ///    lightNormalOffset = 2.0;
    /// };
    /// 
    /// function ServerPlayExplosion(%position, %datablock)
    /// {
    ///    // Play the given explosion on every client.
    ///    // The explosion will be transmitted as an event, not attached to any object.
    ///    for(%idx = 0; %idx < ClientGroup.getCount(); %idx++)
    ///    {
    ///       %client = ClientGroup.getObject(%idx);
    ///       commandToClient(%client, 'PlayExplosion', %position, %datablock.getId());
    ///    }
    /// }
    /// 
    /// function clientCmdPlayExplosion(%position, %effectDataBlock)
    /// {
    ///    // Play an explosion sent by the server. Make sure this function is defined
    ///    // on the client.
    ///    if (isObject(%effectDataBlock))
    ///    {
    ///       new Explosion()
    ///       {
    ///          position = %position;
    ///          dataBlock = %effectDataBlock;
    ///       };
    ///    }
    /// }
    /// 
    /// // schedule an explosion
    /// schedule(1000, 0, ServerPlayExplosion, "0 0 0", GrenadeLauncherExplosion);
    /// </code>
    public unsafe class Explosion : GameBase {
        public Explosion(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public Explosion(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public Explosion(string pName) 
            : this(pName, false) {
        }
        
        public Explosion(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public Explosion(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public Explosion(SimObject pObj) 
            : base(pObj) {
        }
        
        public Explosion(IntPtr pObj) 
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
                                "fnExplosion_staticGetType"), typeof(_StaticGetType));
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
                                "fnExplosion_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the Explosion class.
        /// </description>
        /// <returns>The type info object for Explosion</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Initial starting Normal.
        /// </description>
        /// </value>
        public Point3F InitialNormal {
            get => GenericMarshal.StringTo<Point3F>(GetFieldValue("initialNormal"));
            set => SetFieldValue("initialNormal", GenericMarshal.ToString(value));
        }
    }
}