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
    /// <summary>Defines properties for a TurretShape object.</summary>
    /// <description>
    /// 
    /// </description>
    /// <see cref="TurretShape" />
    /// <see cref="TurretShapeData" />
    public unsafe class TurretShapeData : ItemData {
        public TurretShapeData(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public TurretShapeData(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public TurretShapeData(string pName) 
            : this(pName, false) {
        }
        
        public TurretShapeData(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public TurretShapeData(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public TurretShapeData(SimObject pObj) 
            : base(pObj) {
        }
        
        public TurretShapeData(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct OnStickyCollision__Args
            {
                internal IntPtr obj;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnStickyCollision(IntPtr _this, OnStickyCollision__Args args);
            private static _OnStickyCollision _OnStickyCollisionFunc;
            internal static _OnStickyCollision OnStickyCollision() {
                if (_OnStickyCollisionFunc == null) {
                    _OnStickyCollisionFunc =
                        (_OnStickyCollision)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbTurretShapeData_onStickyCollision"), typeof(_OnStickyCollision));
                }
                
                return _OnStickyCollisionFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnUnmountObject__Args
            {
                internal IntPtr turret;
                internal IntPtr obj;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnUnmountObject(IntPtr _this, OnUnmountObject__Args args);
            private static _OnUnmountObject _OnUnmountObjectFunc;
            internal static _OnUnmountObject OnUnmountObject() {
                if (_OnUnmountObjectFunc == null) {
                    _OnUnmountObjectFunc =
                        (_OnUnmountObject)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbTurretShapeData_onUnmountObject"), typeof(_OnUnmountObject));
                }
                
                return _OnUnmountObjectFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnMountObject__Args
            {
                internal IntPtr turret;
                internal IntPtr obj;
                internal int node;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnMountObject(IntPtr _this, OnMountObject__Args args);
            private static _OnMountObject _OnMountObjectFunc;
            internal static _OnMountObject OnMountObject() {
                if (_OnMountObjectFunc == null) {
                    _OnMountObjectFunc =
                        (_OnMountObject)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbTurretShapeData_onMountObject"), typeof(_OnMountObject));
                }
                
                return _OnMountObjectFunc;
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
                                "fnTurretShapeData_staticGetType"), typeof(_StaticGetType));
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
                                "fnTurretShapeData_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <summary>Informs the TurretData object that it is now sticking to another object.</summary>
        /// <description>
        /// This callback is only called if the TurretData::sticky property for this Turret is true.
        /// </description>
        /// <param name="obj">The Turret object that is colliding.</param>
        /// <remarks> Server side only.
        /// </remarks>
        /// <see cref="TurretShape, TurretData" />
        public virtual void OnStickyCollision(TurretShape obj) {
             InternalUnsafeMethods.OnStickyCollision__Args _args = new InternalUnsafeMethods.OnStickyCollision__Args() {
                obj = obj.ObjectPtr,
             };
             InternalUnsafeMethods.OnStickyCollision()(ObjectPtr, _args);
        }

        /// <summary>Informs the TurretShapeData object that a player is unmounting it.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="turret">The TurretShape object.</param>
        /// <param name="obj">The player that is unmounting.</param>
        /// <remarks> Server side only.
        /// </remarks>
        public virtual void OnUnmountObject(SceneObject turret, SceneObject obj) {
             InternalUnsafeMethods.OnUnmountObject__Args _args = new InternalUnsafeMethods.OnUnmountObject__Args() {
                turret = turret.ObjectPtr,
                obj = obj.ObjectPtr,
             };
             InternalUnsafeMethods.OnUnmountObject()(ObjectPtr, _args);
        }

        /// <summary>Informs the TurretShapeData object that a player is mounting it.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="turret">The TurretShape object.</param>
        /// <param name="obj">The player that is mounting.</param>
        /// <param name="node">The node the player is mounting to.</param>
        /// <remarks> Server side only.
        /// </remarks>
        public virtual void OnMountObject(SceneObject turret, SceneObject obj, int node) {
             InternalUnsafeMethods.OnMountObject__Args _args = new InternalUnsafeMethods.OnMountObject__Args() {
                turret = turret.ObjectPtr,
                obj = obj.ObjectPtr,
                node = node,
             };
             InternalUnsafeMethods.OnMountObject()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the TurretShapeData class.
        /// </description>
        /// <returns>The type info object for TurretShapeData</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <summary>Should the turret allow only z rotations.</summary>
        /// <description>
        /// True indicates that the turret may only be rotated on its z axis, just like the Item class.  This keeps the turret always upright regardless of the surface it lands on.
        /// </description>
        /// </value>
        public bool ZRotOnly {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("zRotOnly"));
            set => SetFieldValue("zRotOnly", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Set how the mounted weapons are linked and triggered.</summary>
        /// <description>
        /// <ul><li>FireTogether: All weapons fire under trigger 0.</li><li>GroupedFire: Weapon mounts 0,2 fire under trigger 0, mounts 1,3 fire under trigger 1.</li><li>IndividualFire: Each weapon mount fires under its own trigger 0-3.</li></ul>
        /// </description>
        /// <see cref="TurretShapeFireLinkType" />
        /// </value>
        public TurretShapeFireLinkType WeaponLinkType {
            get => GenericMarshal.StringTo<TurretShapeFireLinkType>(GetFieldValue("weaponLinkType"));
            set => SetFieldValue("weaponLinkType", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Does the turret's mounted weapon(s) start in a loaded state.</summary>
        /// <description>
        /// True indicates that all mounted weapons start in a loaded state.
        /// </description>
        /// <see cref="ShapeBase::setImageLoaded()" />
        /// </value>
        public bool StartLoaded {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("startLoaded"));
            set => SetFieldValue("startLoaded", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Vertical (Z axis) height of the camera above the turret.
        /// </description>
        /// </value>
        public float CameraOffset {
            get => GenericMarshal.StringTo<float>(GetFieldValue("cameraOffset"));
            set => SetFieldValue("cameraOffset", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Maximum number of degrees to rotate from center.</summary>
        /// <description>
        /// A value of 180 or more degrees indicates the turret may rotate completely around.
        /// </description>
        /// </value>
        public float MaxHeading {
            get => GenericMarshal.StringTo<float>(GetFieldValue("maxHeading"));
            set => SetFieldValue("maxHeading", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Minimum number of degrees to rotate down from straight ahead.</summary>
        /// <description>
        /// 
        /// </description>
        /// </value>
        public float MinPitch {
            get => GenericMarshal.StringTo<float>(GetFieldValue("minPitch"));
            set => SetFieldValue("minPitch", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Maximum number of degrees to rotate up from straight ahead.</summary>
        /// <description>
        /// 
        /// </description>
        /// </value>
        public float MaxPitch {
            get => GenericMarshal.StringTo<float>(GetFieldValue("maxPitch"));
            set => SetFieldValue("maxPitch", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Degrees per second rotation.</summary>
        /// <description>
        /// A value of 0 means no rotation is allowed.  A value less than 0 means the rotation is instantaneous.
        /// </description>
        /// </value>
        public float HeadingRate {
            get => GenericMarshal.StringTo<float>(GetFieldValue("headingRate"));
            set => SetFieldValue("headingRate", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Degrees per second rotation.</summary>
        /// <description>
        /// A value of 0 means no rotation is allowed.  A value less than 0 means the rotation is instantaneous.
        /// </description>
        /// </value>
        public float PitchRate {
            get => GenericMarshal.StringTo<float>(GetFieldValue("pitchRate"));
            set => SetFieldValue("pitchRate", GenericMarshal.ToString(value));
        }
    }
}