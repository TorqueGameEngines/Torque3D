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
    /// 
    public unsafe class TurretShape : Item {
        public TurretShape(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public TurretShape(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public TurretShape(string pName) 
            : this(pName, false) {
        }
        
        public TurretShape(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public TurretShape(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public TurretShape(SimObject pObj) 
            : base(pObj) {
        }
        
        public TurretShape(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct DoRespawn__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _DoRespawn(IntPtr _this, DoRespawn__Args args);
            private static _DoRespawn _DoRespawnFunc;
            internal static _DoRespawn DoRespawn() {
                if (_DoRespawnFunc == null) {
                    _DoRespawnFunc =
                        (_DoRespawn)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTurretShape_doRespawn"), typeof(_DoRespawn));
                }
                
                return _DoRespawnFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetTurretEulerRotation__Args
            {
                internal IntPtr rot;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetTurretEulerRotation(IntPtr _this, SetTurretEulerRotation__Args args);
            private static _SetTurretEulerRotation _SetTurretEulerRotationFunc;
            internal static _SetTurretEulerRotation SetTurretEulerRotation() {
                if (_SetTurretEulerRotationFunc == null) {
                    _SetTurretEulerRotationFunc =
                        (_SetTurretEulerRotation)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTurretShape_setTurretEulerRotation"), typeof(_SetTurretEulerRotation));
                }
                
                return _SetTurretEulerRotationFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetTurretEulerRotation__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate Point3F.InternalStruct _GetTurretEulerRotation(IntPtr _this, GetTurretEulerRotation__Args args);
            private static _GetTurretEulerRotation _GetTurretEulerRotationFunc;
            internal static _GetTurretEulerRotation GetTurretEulerRotation() {
                if (_GetTurretEulerRotationFunc == null) {
                    _GetTurretEulerRotationFunc =
                        (_GetTurretEulerRotation)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTurretShape_getTurretEulerRotation"), typeof(_GetTurretEulerRotation));
                }
                
                return _GetTurretEulerRotationFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetState__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetState(IntPtr _this, GetState__Args args);
            private static _GetState _GetStateFunc;
            internal static _GetState GetState() {
                if (_GetStateFunc == null) {
                    _GetStateFunc =
                        (_GetState)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTurretShape_getState"), typeof(_GetState));
                }
                
                return _GetStateFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetAllowManualFire__Args
            {
                [MarshalAs(UnmanagedType.I1)]
                internal bool allow;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetAllowManualFire(IntPtr _this, SetAllowManualFire__Args args);
            private static _SetAllowManualFire _SetAllowManualFireFunc;
            internal static _SetAllowManualFire SetAllowManualFire() {
                if (_SetAllowManualFireFunc == null) {
                    _SetAllowManualFireFunc =
                        (_SetAllowManualFire)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTurretShape_setAllowManualFire"), typeof(_SetAllowManualFire));
                }
                
                return _SetAllowManualFireFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetAllowManualFire__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _GetAllowManualFire(IntPtr _this, GetAllowManualFire__Args args);
            private static _GetAllowManualFire _GetAllowManualFireFunc;
            internal static _GetAllowManualFire GetAllowManualFire() {
                if (_GetAllowManualFireFunc == null) {
                    _GetAllowManualFireFunc =
                        (_GetAllowManualFire)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTurretShape_getAllowManualFire"), typeof(_GetAllowManualFire));
                }
                
                return _GetAllowManualFireFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetAllowManualRotation__Args
            {
                [MarshalAs(UnmanagedType.I1)]
                internal bool allow;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetAllowManualRotation(IntPtr _this, SetAllowManualRotation__Args args);
            private static _SetAllowManualRotation _SetAllowManualRotationFunc;
            internal static _SetAllowManualRotation SetAllowManualRotation() {
                if (_SetAllowManualRotationFunc == null) {
                    _SetAllowManualRotationFunc =
                        (_SetAllowManualRotation)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTurretShape_setAllowManualRotation"), typeof(_SetAllowManualRotation));
                }
                
                return _SetAllowManualRotationFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetAllowManualRotation__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _GetAllowManualRotation(IntPtr _this, GetAllowManualRotation__Args args);
            private static _GetAllowManualRotation _GetAllowManualRotationFunc;
            internal static _GetAllowManualRotation GetAllowManualRotation() {
                if (_GetAllowManualRotationFunc == null) {
                    _GetAllowManualRotationFunc =
                        (_GetAllowManualRotation)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTurretShape_getAllowManualRotation"), typeof(_GetAllowManualRotation));
                }
                
                return _GetAllowManualRotationFunc;
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
                                "fnTurretShape_staticGetType"), typeof(_StaticGetType));
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
                                "fnTurretShape_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <summary>Does the turret respawn after it has been destroyed.</summary>
        /// <description>
        /// 
        /// </description>
        /// <returns>True if the turret respawns.</returns>
        public bool DoRespawn() {
             InternalUnsafeMethods.DoRespawn__Args _args = new InternalUnsafeMethods.DoRespawn__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.DoRespawn()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Set Euler rotation of this turret's heading and pitch nodes in degrees.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="rot">The rotation in degrees.  The pitch is the X component and the heading is the Z component.  The Y component is ignored.</param>
        public void SetTurretEulerRotation(Point3F rot) {
rot.Alloc();             InternalUnsafeMethods.SetTurretEulerRotation__Args _args = new InternalUnsafeMethods.SetTurretEulerRotation__Args() {
                rot = rot.internalStructPtr,
             };
             InternalUnsafeMethods.SetTurretEulerRotation()(ObjectPtr, _args);
rot.Free();        }

        /// <summary>Get Euler rotation of this turret's heading and pitch nodes.</summary>
        /// <description>
        /// 
        /// </description>
        /// <returns>the orientation of the turret's heading and pitch nodes in the form of rotations around the X, Y and Z axes in degrees.</returns>
        public Point3F GetTurretEulerRotation() {
             InternalUnsafeMethods.GetTurretEulerRotation__Args _args = new InternalUnsafeMethods.GetTurretEulerRotation__Args() {
             };
             Point3F.InternalStruct _engineResult = InternalUnsafeMethods.GetTurretEulerRotation()(ObjectPtr, _args);
             return new Point3F(_engineResult);
        }

        /// <summary>Get the name of the turret's current state.</summary>
        /// <description>
        /// The state is one of the following:
        /// 
        /// <ul><li>Dead - The TurretShape is destroyed.</li><li>Mounted - The TurretShape is mounted to an object such as a vehicle.</li><li>Ready - The TurretShape is free to move.  The usual state.</li></ul>
        /// </description>
        /// <returns>The current state; one of: "Dead", "Mounted", "Ready"</returns>
        public string GetState() {
             InternalUnsafeMethods.GetState__Args _args = new InternalUnsafeMethods.GetState__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetState()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <summary>Set if the turret is allowed to fire through moves.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="allow">If true then the turret may be fired through moves.</param>
        public void SetAllowManualFire(bool allow) {
             InternalUnsafeMethods.SetAllowManualFire__Args _args = new InternalUnsafeMethods.SetAllowManualFire__Args() {
                allow = allow,
             };
             InternalUnsafeMethods.SetAllowManualFire()(ObjectPtr, _args);
        }

        /// <summary>Get if the turret is allowed to fire through moves.</summary>
        /// <description>
        /// 
        /// </description>
        /// <returns>True if the turret is allowed to fire through moves.</returns>
        public bool GetAllowManualFire() {
             InternalUnsafeMethods.GetAllowManualFire__Args _args = new InternalUnsafeMethods.GetAllowManualFire__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.GetAllowManualFire()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Set if the turret is allowed to rotate through moves.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="allow">If true then the turret may be rotated through moves.</param>
        public void SetAllowManualRotation(bool allow) {
             InternalUnsafeMethods.SetAllowManualRotation__Args _args = new InternalUnsafeMethods.SetAllowManualRotation__Args() {
                allow = allow,
             };
             InternalUnsafeMethods.SetAllowManualRotation()(ObjectPtr, _args);
        }

        /// <summary>Get if the turret is allowed to rotate through moves.</summary>
        /// <description>
        /// 
        /// </description>
        /// <returns>True if the turret is allowed to rotate through moves.</returns>
        public bool GetAllowManualRotation() {
             InternalUnsafeMethods.GetAllowManualRotation__Args _args = new InternalUnsafeMethods.GetAllowManualRotation__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.GetAllowManualRotation()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Get the type info object for the TurretShape class.
        /// </description>
        /// <returns>The type info object for TurretShape</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <summary>Respawn the turret after it has been destroyed.</summary>
        /// <description>
        /// If true, the turret will respawn after it is destroyed.
        /// </description>
        /// </value>
        public bool Respawn {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("respawn"));
            set => SetFieldValue("respawn", GenericMarshal.ToString(value));
        }
    }
}