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
    /// <summary>An emitter for lightning bolts.</summary>
    /// <description>
    /// Lightning strike events are created on the server and transmitted to all clients to render the bolt. The strike may be followed by a random thunder sound. Player or Vehicle objects within the Lightning strike range can be hit and damaged by bolts.
    /// </description>
    /// <see cref="LightningData" />
    public unsafe class Lightning : GameBase {
        public Lightning(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public Lightning(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public Lightning(string pName) 
            : this(pName, false) {
        }
        
        public Lightning(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public Lightning(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public Lightning(SimObject pObj) 
            : base(pObj) {
        }
        
        public Lightning(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct StrikeObject__Args
            {
                internal IntPtr pSB;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _StrikeObject(IntPtr _this, StrikeObject__Args args);
            private static _StrikeObject _StrikeObjectFunc;
            internal static _StrikeObject StrikeObject() {
                if (_StrikeObjectFunc == null) {
                    _StrikeObjectFunc =
                        (_StrikeObject)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnLightning_strikeObject"), typeof(_StrikeObject));
                }
                
                return _StrikeObjectFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct StrikeRandomPoint__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _StrikeRandomPoint(IntPtr _this, StrikeRandomPoint__Args args);
            private static _StrikeRandomPoint _StrikeRandomPointFunc;
            internal static _StrikeRandomPoint StrikeRandomPoint() {
                if (_StrikeRandomPointFunc == null) {
                    _StrikeRandomPointFunc =
                        (_StrikeRandomPoint)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnLightning_strikeRandomPoint"), typeof(_StrikeRandomPoint));
                }
                
                return _StrikeRandomPointFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct WarningFlashes__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _WarningFlashes(IntPtr _this, WarningFlashes__Args args);
            private static _WarningFlashes _WarningFlashesFunc;
            internal static _WarningFlashes WarningFlashes() {
                if (_WarningFlashesFunc == null) {
                    _WarningFlashesFunc =
                        (_WarningFlashes)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnLightning_warningFlashes"), typeof(_WarningFlashes));
                }
                
                return _WarningFlashesFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ApplyDamage__Args
            {
                internal IntPtr hitPosition;
                internal IntPtr hitNormal;
                internal IntPtr hitObject;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ApplyDamage(IntPtr _this, ApplyDamage__Args args);
            private static _ApplyDamage _ApplyDamageFunc;
            internal static _ApplyDamage ApplyDamage() {
                if (_ApplyDamageFunc == null) {
                    _ApplyDamageFunc =
                        (_ApplyDamage)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbLightning_applyDamage"), typeof(_ApplyDamage));
                }
                
                return _ApplyDamageFunc;
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
                                "fnLightning_staticGetType"), typeof(_StaticGetType));
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
                                "fnLightning_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Creates a LightningStrikeEvent which strikes a specific object.
        /// </description>
        /// <remarks> This method is currently unimplemented.
        /// </remarks>
        public void StrikeObject(ShapeBase pSB = null) {
             InternalUnsafeMethods.StrikeObject__Args _args = new InternalUnsafeMethods.StrikeObject__Args() {
                pSB = pSB.ObjectPtr,
             };
             InternalUnsafeMethods.StrikeObject()(ObjectPtr, _args);
        }

        /// <description>
        /// Creates a LightningStrikeEvent which attempts to strike and damage a random object in range of the Lightning object.
        /// </description>
        /// <code>
        /// // Generate a damaging lightning strike effect on all clients
        /// %lightning.strikeRandomPoint();
        /// </code>
        public void StrikeRandomPoint() {
             InternalUnsafeMethods.StrikeRandomPoint__Args _args = new InternalUnsafeMethods.StrikeRandomPoint__Args() {
             };
             InternalUnsafeMethods.StrikeRandomPoint()(ObjectPtr, _args);
        }

        /// <summary>Creates a LightningStrikeEvent that triggers harmless lightning bolts on all clients.</summary>
        /// <description>
        /// No objects will be damaged by these bolts.
        /// </description>
        /// <code>
        /// // Generate a harmless lightning strike effect on all clients
        /// %lightning.warningFlashes();
        /// </code>
        public void WarningFlashes() {
             InternalUnsafeMethods.WarningFlashes__Args _args = new InternalUnsafeMethods.WarningFlashes__Args() {
             };
             InternalUnsafeMethods.WarningFlashes()(ObjectPtr, _args);
        }

        /// <description>
        /// Informs an object that it was hit by a lightning bolt and needs to take damage.
        /// </description>
        /// <param name="hitPosition">World position hit by the lightning bolt.</param>
        /// <param name="hitNormal">Surface normal at<paramref name="" /> hitPosition.
        /// </param>
        /// <param name="hitObject">Player or Vehicle object that was hit.</param>
        /// <code>
        /// function Lightning::applyDamage( %this, %hitPosition, %hitNormal, %hitObject )
        /// {
        ///    // apply damage to the player
        ///    %hitObject.applyDamage( 25 );
        /// }
        /// </code>
        public virtual void ApplyDamage(Point3F hitPosition, Point3F hitNormal, SceneObject hitObject) {
hitPosition.Alloc();hitNormal.Alloc();             InternalUnsafeMethods.ApplyDamage__Args _args = new InternalUnsafeMethods.ApplyDamage__Args() {
                hitPosition = hitPosition.internalStructPtr,
                hitNormal = hitNormal.internalStructPtr,
                hitObject = hitObject.ObjectPtr,
             };
             InternalUnsafeMethods.ApplyDamage()(ObjectPtr, _args);
hitPosition.Free();hitNormal.Free();        }

        /// <description>
        /// Get the type info object for the Lightning class.
        /// </description>
        /// <returns>The type info object for Lightning</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <summary>Number of lightning strikes to perform per minute.</summary>
        /// <description>
        /// Automatically invokes strikeRandomPoint() at regular intervals.
        /// </description>
        /// </value>
        public int StrikesPerMinute {
            get => GenericMarshal.StringTo<int>(GetFieldValue("strikesPerMinute"));
            set => SetFieldValue("strikesPerMinute", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Width of a lightning bolt.
        /// </description>
        /// </value>
        public float StrikeWidth {
            get => GenericMarshal.StringTo<float>(GetFieldValue("strikeWidth"));
            set => SetFieldValue("strikeWidth", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Horizontal size (XY plane) of the search box used to find and damage Player or Vehicle objects within range of the strike.</summary>
        /// <description>
        /// Only the object at highest altitude with a clear line of sight to the bolt will be hit.
        /// </description>
        /// </value>
        public float StrikeRadius {
            get => GenericMarshal.StringTo<float>(GetFieldValue("strikeRadius"));
            set => SetFieldValue("strikeRadius", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Color to blend the strike texture with.
        /// </description>
        /// </value>
        public LinearColorF Color {
            get => GenericMarshal.StringTo<LinearColorF>(GetFieldValue("color"));
            set => SetFieldValue("color", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Color to blend the strike texture with when the bolt is fading away.</summary>
        /// <description>
        /// Bolts fade away automatically shortly after the strike occurs.
        /// </description>
        /// </value>
        public LinearColorF FadeColor {
            get => GenericMarshal.StringTo<LinearColorF>(GetFieldValue("fadeColor"));
            set => SetFieldValue("fadeColor", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Percentage chance (0-1) that a given lightning bolt will hit something.
        /// </description>
        /// </value>
        public float ChanceToHitTarget {
            get => GenericMarshal.StringTo<float>(GetFieldValue("chanceToHitTarget"));
            set => SetFieldValue("chanceToHitTarget", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Radial distance from the center of the Lightning object for the start point of the bolt.</summary>
        /// <description>
        /// The actual start point will be a random point within this radius.
        /// </description>
        /// </value>
        public float BoltStartRadius {
            get => GenericMarshal.StringTo<float>(GetFieldValue("boltStartRadius"));
            set => SetFieldValue("boltStartRadius", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Controls whether lightning bolts are affected by fog when they are rendered.
        /// </description>
        /// </value>
        public bool UseFog {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("useFog"));
            set => SetFieldValue("useFog", GenericMarshal.ToString(value));
        }
    }
}