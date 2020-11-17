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
    /// <summary>Defines a particular magic-missile type. (Use with afxMagicSpellData.)</summary>
    /// <description>
    /// 
    /// </description>
    /// <code>
    /// datablock afxMagicMissileData(Fireball_MM)
    /// {
    ///   muzzleVelocity = 50;
    ///   velInheritFactor = 0;
    ///   lifetime = 20000;
    ///   isBallistic = true;
    ///   ballisticCoefficient = 0.85;
    ///   gravityMod = 0.05;
    ///   isGuided = true;
    ///   precision = 30;
    ///   trackDelay = 7;
    ///   launchOffset = "0 0 43.7965";
    ///   launchOnServerSignal = true;
    /// };
    /// </code>
    public unsafe class afxMagicMissileData : GameBaseData {
        public afxMagicMissileData(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public afxMagicMissileData(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public afxMagicMissileData(string pName) 
            : this(pName, false) {
        }
        
        public afxMagicMissileData(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public afxMagicMissileData(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public afxMagicMissileData(SimObject pObj) 
            : base(pObj) {
        }
        
        public afxMagicMissileData(IntPtr pObj) 
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
                                "fnafxMagicMissileData_staticGetType"), typeof(_StaticGetType));
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
                                "fnafxMagicMissileData_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the afxMagicMissileData class.
        /// </description>
        /// <returns>The type info object for afxMagicMissileData</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// 
        /// </value>
        public ParticleEmitterData ParticleEmitter {
            get => GenericMarshal.StringTo<ParticleEmitterData>(GetFieldValue("ParticleEmitter"));
            set => SetFieldValue("ParticleEmitter", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public ParticleEmitterData ParticleWaterEmitter {
            get => GenericMarshal.StringTo<ParticleEmitterData>(GetFieldValue("particleWaterEmitter"));
            set => SetFieldValue("particleWaterEmitter", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public string ProjectileShapeName {
            get => GenericMarshal.StringTo<string>(GetFieldValue("projectileShapeName"));
            set => SetFieldValue("projectileShapeName", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public Point3F Scale {
            get => GenericMarshal.StringTo<Point3F>(GetFieldValue("scale"));
            set => SetFieldValue("scale", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public SFXTrack Sound {
            get => GenericMarshal.StringTo<SFXTrack>(GetFieldValue("sound"));
            set => SetFieldValue("sound", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public SplashData Splash {
            get => GenericMarshal.StringTo<SplashData>(GetFieldValue("Splash"));
            set => SetFieldValue("Splash", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public LightDescription LightDesc {
            get => GenericMarshal.StringTo<LightDescription>(GetFieldValue("lightDesc"));
            set => SetFieldValue("lightDesc", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public bool IsBallistic {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("isBallistic"));
            set => SetFieldValue("isBallistic", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public float MuzzleVelocity {
            get => GenericMarshal.StringTo<float>(GetFieldValue("muzzleVelocity"));
            set => SetFieldValue("muzzleVelocity", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public int Lifetime {
            get => GenericMarshal.StringTo<int>(GetFieldValue("lifetime"));
            set => SetFieldValue("lifetime", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public float GravityMod {
            get => GenericMarshal.StringTo<float>(GetFieldValue("gravityMod"));
            set => SetFieldValue("gravityMod", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public string MissileShapeName {
            get => GenericMarshal.StringTo<string>(GetFieldValue("missileShapeName"));
            set => SetFieldValue("missileShapeName", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public Point3F MissileShapeScale {
            get => GenericMarshal.StringTo<Point3F>(GetFieldValue("missileShapeScale"));
            set => SetFieldValue("missileShapeScale", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public Point3F StartingVelocityVector {
            get => GenericMarshal.StringTo<Point3F>(GetFieldValue("startingVelocityVector"));
            set => SetFieldValue("startingVelocityVector", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public bool IsGuided {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("isGuided"));
            set => SetFieldValue("isGuided", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public float Precision {
            get => GenericMarshal.StringTo<float>(GetFieldValue("precision"));
            set => SetFieldValue("precision", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public int TrackDelay {
            get => GenericMarshal.StringTo<int>(GetFieldValue("trackDelay"));
            set => SetFieldValue("trackDelay", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public float BallisticCoefficient {
            get => GenericMarshal.StringTo<float>(GetFieldValue("ballisticCoefficient"));
            set => SetFieldValue("ballisticCoefficient", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public int CollisionMask {
            get => GenericMarshal.StringTo<int>(GetFieldValue("collisionMask"));
            set => SetFieldValue("collisionMask", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public bool FollowTerrain {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("followTerrain"));
            set => SetFieldValue("followTerrain", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public float FollowTerrainHeight {
            get => GenericMarshal.StringTo<float>(GetFieldValue("followTerrainHeight"));
            set => SetFieldValue("followTerrainHeight", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public float FollowTerrainAdjustRate {
            get => GenericMarshal.StringTo<float>(GetFieldValue("followTerrainAdjustRate"));
            set => SetFieldValue("followTerrainAdjustRate", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public int FollowTerrainAdjustDelay {
            get => GenericMarshal.StringTo<int>(GetFieldValue("followTerrainAdjustDelay"));
            set => SetFieldValue("followTerrainAdjustDelay", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public float Acceleration {
            get => GenericMarshal.StringTo<float>(GetFieldValue("acceleration"));
            set => SetFieldValue("acceleration", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public int AccelDelay {
            get => GenericMarshal.StringTo<int>(GetFieldValue("accelDelay"));
            set => SetFieldValue("accelDelay", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public int AccelLifetime {
            get => GenericMarshal.StringTo<int>(GetFieldValue("accelLifetime"));
            set => SetFieldValue("accelLifetime", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public string LaunchNode {
            get => GenericMarshal.StringTo<string>(GetFieldValue("launchNode"));
            set => SetFieldValue("launchNode", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public Point3F LaunchOffset {
            get => GenericMarshal.StringTo<Point3F>(GetFieldValue("launchOffset"));
            set => SetFieldValue("launchOffset", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public Point3F LaunchOffsetServer {
            get => GenericMarshal.StringTo<Point3F>(GetFieldValue("launchOffsetServer"));
            set => SetFieldValue("launchOffsetServer", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public Point3F LaunchOffsetClient {
            get => GenericMarshal.StringTo<Point3F>(GetFieldValue("launchOffsetClient"));
            set => SetFieldValue("launchOffsetClient", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public Point3F LaunchNodeOffset {
            get => GenericMarshal.StringTo<Point3F>(GetFieldValue("launchNodeOffset"));
            set => SetFieldValue("launchNodeOffset", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public float LaunchAimPitch {
            get => GenericMarshal.StringTo<float>(GetFieldValue("launchAimPitch"));
            set => SetFieldValue("launchAimPitch", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public float LaunchAimPan {
            get => GenericMarshal.StringTo<float>(GetFieldValue("launchAimPan"));
            set => SetFieldValue("launchAimPan", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public string LaunchConstraintServer {
            get => GenericMarshal.StringTo<string>(GetFieldValue("launchConstraintServer"));
            set => SetFieldValue("launchConstraintServer", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public string LaunchConstraintClient {
            get => GenericMarshal.StringTo<string>(GetFieldValue("launchConstraintClient"));
            set => SetFieldValue("launchConstraintClient", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public bool EchoLaunchOffset {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("echoLaunchOffset"));
            set => SetFieldValue("echoLaunchOffset", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public FloatVector WiggleMagnitudes {
            get => GenericMarshal.StringTo<FloatVector>(GetFieldValue("wiggleMagnitudes"));
            set => SetFieldValue("wiggleMagnitudes", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public FloatVector WiggleSpeeds {
            get => GenericMarshal.StringTo<FloatVector>(GetFieldValue("wiggleSpeeds"));
            set => SetFieldValue("wiggleSpeeds", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public string WiggleAxis {
            get => GenericMarshal.StringTo<string>(GetFieldValue("wiggleAxis"));
            set => SetFieldValue("wiggleAxis", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public float HoverAltitude {
            get => GenericMarshal.StringTo<float>(GetFieldValue("hoverAltitude"));
            set => SetFieldValue("hoverAltitude", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public float HoverAttackDistance {
            get => GenericMarshal.StringTo<float>(GetFieldValue("hoverAttackDistance"));
            set => SetFieldValue("hoverAttackDistance", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public float HoverAttackGradient {
            get => GenericMarshal.StringTo<float>(GetFieldValue("hoverAttackGradient"));
            set => SetFieldValue("hoverAttackGradient", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public int Hovertime {
            get => GenericMarshal.StringTo<int>(GetFieldValue("hovertime"));
            set => SetFieldValue("hovertime", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public bool ReverseTargeting {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("reverseTargeting"));
            set => SetFieldValue("reverseTargeting", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public int CasterSafetyTime {
            get => GenericMarshal.StringTo<int>(GetFieldValue("casterSafetyTime"));
            set => SetFieldValue("casterSafetyTime", GenericMarshal.ToString(value));
        }
    }
}