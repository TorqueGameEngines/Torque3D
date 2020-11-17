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
    public unsafe class AITurretShape : TurretShape {
        public AITurretShape(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public AITurretShape(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public AITurretShape(string pName) 
            : this(pName, false) {
        }
        
        public AITurretShape(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public AITurretShape(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public AITurretShape(SimObject pObj) 
            : base(pObj) {
        }
        
        public AITurretShape(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct RecenterTurret__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _RecenterTurret(IntPtr _this, RecenterTurret__Args args);
            private static _RecenterTurret _RecenterTurretFunc;
            internal static _RecenterTurret RecenterTurret() {
                if (_RecenterTurretFunc == null) {
                    _RecenterTurretFunc =
                        (_RecenterTurret)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAITurretShape_recenterTurret"), typeof(_RecenterTurret));
                }
                
                return _RecenterTurretFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetGunSlotFiring__Args
            {
                internal int slot;
                [MarshalAs(UnmanagedType.I1)]
                internal bool fire;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetGunSlotFiring(IntPtr _this, SetGunSlotFiring__Args args);
            private static _SetGunSlotFiring _SetGunSlotFiringFunc;
            internal static _SetGunSlotFiring SetGunSlotFiring() {
                if (_SetGunSlotFiringFunc == null) {
                    _SetGunSlotFiringFunc =
                        (_SetGunSlotFiring)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAITurretShape_setGunSlotFiring"), typeof(_SetGunSlotFiring));
                }
                
                return _SetGunSlotFiringFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetAllGunsFiring__Args
            {
                [MarshalAs(UnmanagedType.I1)]
                internal bool fire;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetAllGunsFiring(IntPtr _this, SetAllGunsFiring__Args args);
            private static _SetAllGunsFiring _SetAllGunsFiringFunc;
            internal static _SetAllGunsFiring SetAllGunsFiring() {
                if (_SetAllGunsFiringFunc == null) {
                    _SetAllGunsFiringFunc =
                        (_SetAllGunsFiring)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAITurretShape_setAllGunsFiring"), typeof(_SetAllGunsFiring));
                }
                
                return _SetAllGunsFiringFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetWeaponLeadVelocity__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _GetWeaponLeadVelocity(IntPtr _this, GetWeaponLeadVelocity__Args args);
            private static _GetWeaponLeadVelocity _GetWeaponLeadVelocityFunc;
            internal static _GetWeaponLeadVelocity GetWeaponLeadVelocity() {
                if (_GetWeaponLeadVelocityFunc == null) {
                    _GetWeaponLeadVelocityFunc =
                        (_GetWeaponLeadVelocity)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAITurretShape_getWeaponLeadVelocity"), typeof(_GetWeaponLeadVelocity));
                }
                
                return _GetWeaponLeadVelocityFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetWeaponLeadVelocity__Args
            {
                internal float velocity;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetWeaponLeadVelocity(IntPtr _this, SetWeaponLeadVelocity__Args args);
            private static _SetWeaponLeadVelocity _SetWeaponLeadVelocityFunc;
            internal static _SetWeaponLeadVelocity SetWeaponLeadVelocity() {
                if (_SetWeaponLeadVelocityFunc == null) {
                    _SetWeaponLeadVelocityFunc =
                        (_SetWeaponLeadVelocity)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAITurretShape_setWeaponLeadVelocity"), typeof(_SetWeaponLeadVelocity));
                }
                
                return _SetWeaponLeadVelocityFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ResetTarget__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ResetTarget(IntPtr _this, ResetTarget__Args args);
            private static _ResetTarget _ResetTargetFunc;
            internal static _ResetTarget ResetTarget() {
                if (_ResetTargetFunc == null) {
                    _ResetTargetFunc =
                        (_ResetTarget)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAITurretShape_resetTarget"), typeof(_ResetTarget));
                }
                
                return _ResetTargetFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetTarget__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate IntPtr _GetTarget(IntPtr _this, GetTarget__Args args);
            private static _GetTarget _GetTargetFunc;
            internal static _GetTarget GetTarget() {
                if (_GetTargetFunc == null) {
                    _GetTargetFunc =
                        (_GetTarget)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAITurretShape_getTarget"), typeof(_GetTarget));
                }
                
                return _GetTargetFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct HasTarget__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _HasTarget(IntPtr _this, HasTarget__Args args);
            private static _HasTarget _HasTargetFunc;
            internal static _HasTarget HasTarget() {
                if (_HasTargetFunc == null) {
                    _HasTargetFunc =
                        (_HasTarget)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAITurretShape_hasTarget"), typeof(_HasTarget));
                }
                
                return _HasTargetFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct StopTrackingTarget__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _StopTrackingTarget(IntPtr _this, StopTrackingTarget__Args args);
            private static _StopTrackingTarget _StopTrackingTargetFunc;
            internal static _StopTrackingTarget StopTrackingTarget() {
                if (_StopTrackingTargetFunc == null) {
                    _StopTrackingTargetFunc =
                        (_StopTrackingTarget)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAITurretShape_stopTrackingTarget"), typeof(_StopTrackingTarget));
                }
                
                return _StopTrackingTargetFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct StartTrackingTarget__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _StartTrackingTarget(IntPtr _this, StartTrackingTarget__Args args);
            private static _StartTrackingTarget _StartTrackingTargetFunc;
            internal static _StartTrackingTarget StartTrackingTarget() {
                if (_StartTrackingTargetFunc == null) {
                    _StartTrackingTargetFunc =
                        (_StartTrackingTarget)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAITurretShape_startTrackingTarget"), typeof(_StartTrackingTarget));
                }
                
                return _StartTrackingTargetFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct StopScanForTargets__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _StopScanForTargets(IntPtr _this, StopScanForTargets__Args args);
            private static _StopScanForTargets _StopScanForTargetsFunc;
            internal static _StopScanForTargets StopScanForTargets() {
                if (_StopScanForTargetsFunc == null) {
                    _StopScanForTargetsFunc =
                        (_StopScanForTargets)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAITurretShape_stopScanForTargets"), typeof(_StopScanForTargets));
                }
                
                return _StopScanForTargetsFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct StartScanForTargets__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _StartScanForTargets(IntPtr _this, StartScanForTargets__Args args);
            private static _StartScanForTargets _StartScanForTargetsFunc;
            internal static _StartScanForTargets StartScanForTargets() {
                if (_StartScanForTargetsFunc == null) {
                    _StartScanForTargetsFunc =
                        (_StartScanForTargets)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAITurretShape_startScanForTargets"), typeof(_StartScanForTargets));
                }
                
                return _StartScanForTargetsFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct DeactivateTurret__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _DeactivateTurret(IntPtr _this, DeactivateTurret__Args args);
            private static _DeactivateTurret _DeactivateTurretFunc;
            internal static _DeactivateTurret DeactivateTurret() {
                if (_DeactivateTurretFunc == null) {
                    _DeactivateTurretFunc =
                        (_DeactivateTurret)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAITurretShape_deactivateTurret"), typeof(_DeactivateTurret));
                }
                
                return _DeactivateTurretFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ActivateTurret__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ActivateTurret(IntPtr _this, ActivateTurret__Args args);
            private static _ActivateTurret _ActivateTurretFunc;
            internal static _ActivateTurret ActivateTurret() {
                if (_ActivateTurretFunc == null) {
                    _ActivateTurretFunc =
                        (_ActivateTurret)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAITurretShape_activateTurret"), typeof(_ActivateTurret));
                }
                
                return _ActivateTurretFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetTurretState__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string newState;
                [MarshalAs(UnmanagedType.I1)]
                internal bool force;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetTurretState(IntPtr _this, SetTurretState__Args args);
            private static _SetTurretState _SetTurretStateFunc;
            internal static _SetTurretState SetTurretState() {
                if (_SetTurretStateFunc == null) {
                    _SetTurretStateFunc =
                        (_SetTurretState)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAITurretShape_setTurretState"), typeof(_SetTurretState));
                }
                
                return _SetTurretStateFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetIgnoreListObject__Args
            {
                internal int index;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate IntPtr _GetIgnoreListObject(IntPtr _this, GetIgnoreListObject__Args args);
            private static _GetIgnoreListObject _GetIgnoreListObjectFunc;
            internal static _GetIgnoreListObject GetIgnoreListObject() {
                if (_GetIgnoreListObjectFunc == null) {
                    _GetIgnoreListObjectFunc =
                        (_GetIgnoreListObject)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAITurretShape_getIgnoreListObject"), typeof(_GetIgnoreListObject));
                }
                
                return _GetIgnoreListObjectFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IgnoreListCount__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _IgnoreListCount(IntPtr _this, IgnoreListCount__Args args);
            private static _IgnoreListCount _IgnoreListCountFunc;
            internal static _IgnoreListCount IgnoreListCount() {
                if (_IgnoreListCountFunc == null) {
                    _IgnoreListCountFunc =
                        (_IgnoreListCount)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAITurretShape_ignoreListCount"), typeof(_IgnoreListCount));
                }
                
                return _IgnoreListCountFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ClearIgnoreList__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ClearIgnoreList(IntPtr _this, ClearIgnoreList__Args args);
            private static _ClearIgnoreList _ClearIgnoreListFunc;
            internal static _ClearIgnoreList ClearIgnoreList() {
                if (_ClearIgnoreListFunc == null) {
                    _ClearIgnoreListFunc =
                        (_ClearIgnoreList)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAITurretShape_clearIgnoreList"), typeof(_ClearIgnoreList));
                }
                
                return _ClearIgnoreListFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct RemoveFromIgnoreList__Args
            {
                internal IntPtr obj;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _RemoveFromIgnoreList(IntPtr _this, RemoveFromIgnoreList__Args args);
            private static _RemoveFromIgnoreList _RemoveFromIgnoreListFunc;
            internal static _RemoveFromIgnoreList RemoveFromIgnoreList() {
                if (_RemoveFromIgnoreListFunc == null) {
                    _RemoveFromIgnoreListFunc =
                        (_RemoveFromIgnoreList)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAITurretShape_removeFromIgnoreList"), typeof(_RemoveFromIgnoreList));
                }
                
                return _RemoveFromIgnoreListFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct AddToIgnoreList__Args
            {
                internal IntPtr obj;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _AddToIgnoreList(IntPtr _this, AddToIgnoreList__Args args);
            private static _AddToIgnoreList _AddToIgnoreListFunc;
            internal static _AddToIgnoreList AddToIgnoreList() {
                if (_AddToIgnoreListFunc == null) {
                    _AddToIgnoreListFunc =
                        (_AddToIgnoreList)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAITurretShape_addToIgnoreList"), typeof(_AddToIgnoreList));
                }
                
                return _AddToIgnoreListFunc;
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
                                "fnAITurretShape_staticGetType"), typeof(_StaticGetType));
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
                                "fnAITurretShape_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <summary>Recenter the turret's weapon.</summary>
        /// <description>
        /// 
        /// </description>
        public void RecenterTurret() {
             InternalUnsafeMethods.RecenterTurret__Args _args = new InternalUnsafeMethods.RecenterTurret__Args() {
             };
             InternalUnsafeMethods.RecenterTurret()(ObjectPtr, _args);
        }

        /// <summary>Set the firing state of the given gun slot.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="slot">The gun to modify.  Valid range is 0-3 that corresponds to the weapon mount point.</param>
        /// <param name="fire">Set to true to activate the gun.  False to deactivate it.</param>
        public void SetGunSlotFiring(int slot, bool fire) {
             InternalUnsafeMethods.SetGunSlotFiring__Args _args = new InternalUnsafeMethods.SetGunSlotFiring__Args() {
                slot = slot,
                fire = fire,
             };
             InternalUnsafeMethods.SetGunSlotFiring()(ObjectPtr, _args);
        }

        /// <summary>Set the firing state of the turret's guns.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="fire">Set to true to activate all guns.  False to deactivate them.</param>
        public void SetAllGunsFiring(bool fire) {
             InternalUnsafeMethods.SetAllGunsFiring__Args _args = new InternalUnsafeMethods.SetAllGunsFiring__Args() {
                fire = fire,
             };
             InternalUnsafeMethods.SetAllGunsFiring()(ObjectPtr, _args);
        }

        /// <summary>Get the turret's defined projectile velocity that helps with target leading.</summary>
        /// <description>
        /// 
        /// </description>
        /// <returns>The defined weapon projectile speed, or 0 if leading is disabled.</returns>
        public float GetWeaponLeadVelocity() {
             InternalUnsafeMethods.GetWeaponLeadVelocity__Args _args = new InternalUnsafeMethods.GetWeaponLeadVelocity__Args() {
             };
             float _engineResult = InternalUnsafeMethods.GetWeaponLeadVelocity()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Set the turret's projectile velocity to help lead the target.</summary>
        /// <description>
        /// This value normally comes from AITurretShapeData::weaponLeadVelocity but this method allows you to override the datablock value.  This can be useful if the turret changes ammunition, uses a different weapon than the default, is damaged, etc.
        /// </description>
        /// <remarks> Setting this to 0 will disable target leading.
        /// </remarks>
        public void SetWeaponLeadVelocity(float velocity) {
             InternalUnsafeMethods.SetWeaponLeadVelocity__Args _args = new InternalUnsafeMethods.SetWeaponLeadVelocity__Args() {
                velocity = velocity,
             };
             InternalUnsafeMethods.SetWeaponLeadVelocity()(ObjectPtr, _args);
        }

        /// <summary>Resets the turret's target tracking.</summary>
        /// <description>
        /// Only resets the internal target tracking.  Does not modify the turret's facing.
        /// </description>
        public void ResetTarget() {
             InternalUnsafeMethods.ResetTarget__Args _args = new InternalUnsafeMethods.ResetTarget__Args() {
             };
             InternalUnsafeMethods.ResetTarget()(ObjectPtr, _args);
        }

        /// <summary>Get the turret's current target.</summary>
        /// <description>
        /// 
        /// </description>
        /// <returns>The object that is the target's current target, or 0 if no target.</returns>
        public SimObject GetTarget() {
             InternalUnsafeMethods.GetTarget__Args _args = new InternalUnsafeMethods.GetTarget__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetTarget()(ObjectPtr, _args);
             return new SimObject(_engineResult);
        }

        /// <summary>Indicates if the turret has a target.</summary>
        /// <description>
        /// 
        /// </description>
        /// <returns>True if the turret has a target.</returns>
        public bool HasTarget() {
             InternalUnsafeMethods.HasTarget__Args _args = new InternalUnsafeMethods.HasTarget__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.HasTarget()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Stop the turret from tracking the current target.</summary>
        /// <description>
        /// 
        /// </description>
        public void StopTrackingTarget() {
             InternalUnsafeMethods.StopTrackingTarget__Args _args = new InternalUnsafeMethods.StopTrackingTarget__Args() {
             };
             InternalUnsafeMethods.StopTrackingTarget()(ObjectPtr, _args);
        }

        /// <summary>Have the turret track the current target.</summary>
        /// <description>
        /// 
        /// </description>
        public void StartTrackingTarget() {
             InternalUnsafeMethods.StartTrackingTarget__Args _args = new InternalUnsafeMethods.StartTrackingTarget__Args() {
             };
             InternalUnsafeMethods.StartTrackingTarget()(ObjectPtr, _args);
        }

        /// <summary>Stop scanning for targets.</summary>
        /// <description>
        /// 
        /// </description>
        /// <remarks> Only impacts the scanning for new targets.  Does not effect a turret's current target lock.
        /// </remarks>
        public void StopScanForTargets() {
             InternalUnsafeMethods.StopScanForTargets__Args _args = new InternalUnsafeMethods.StopScanForTargets__Args() {
             };
             InternalUnsafeMethods.StopScanForTargets()(ObjectPtr, _args);
        }

        /// <summary>Begin scanning for a target.</summary>
        /// <description>
        /// 
        /// </description>
        public void StartScanForTargets() {
             InternalUnsafeMethods.StartScanForTargets__Args _args = new InternalUnsafeMethods.StartScanForTargets__Args() {
             };
             InternalUnsafeMethods.StartScanForTargets()(ObjectPtr, _args);
        }

        /// <summary>Deactivate a turret from an active state.</summary>
        /// <description>
        /// 
        /// </description>
        public void DeactivateTurret() {
             InternalUnsafeMethods.DeactivateTurret__Args _args = new InternalUnsafeMethods.DeactivateTurret__Args() {
             };
             InternalUnsafeMethods.DeactivateTurret()(ObjectPtr, _args);
        }

        /// <summary>Activate a turret from a deactive state.</summary>
        /// <description>
        /// 
        /// </description>
        public void ActivateTurret() {
             InternalUnsafeMethods.ActivateTurret__Args _args = new InternalUnsafeMethods.ActivateTurret__Args() {
             };
             InternalUnsafeMethods.ActivateTurret()(ObjectPtr, _args);
        }

        /// <summary>Set the turret's current state.</summary>
        /// <description>
        /// Normally the turret's state comes from updating the state machine but this method allows you to override this and jump to the requested state immediately.
        /// </description>
        /// <param name="newState">The name of the new state.</param>
        /// <param name="force">Is true then force the full processing of the new state even if it is the same as the current state.  If false then only the time out value is reset and the state's script method is called, if any.</param>
        public void SetTurretState(string newState, bool force = false) {
             InternalUnsafeMethods.SetTurretState__Args _args = new InternalUnsafeMethods.SetTurretState__Args() {
                newState = newState,
                force = force,
             };
             InternalUnsafeMethods.SetTurretState()(ObjectPtr, _args);
        }

        /// <summary>Returns the object in the ignore list at index.</summary>
        /// <description>
        /// All objects in this list will be ignored by the turret's targeting.
        /// </description>
        /// <param name="index">The index of the object in the ignore list being retrieved.</param>
        public SimObject GetIgnoreListObject(int index) {
             InternalUnsafeMethods.GetIgnoreListObject__Args _args = new InternalUnsafeMethods.GetIgnoreListObject__Args() {
                index = index,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetIgnoreListObject()(ObjectPtr, _args);
             return new SimObject(_engineResult);
        }

        /// <summary>Returns the number of objects in the turrets ignore list.</summary>
        /// <description>
        /// All objects in this list will be ignored by the turret's targeting.
        /// </description>
        public int IgnoreListCount() {
             InternalUnsafeMethods.IgnoreListCount__Args _args = new InternalUnsafeMethods.IgnoreListCount__Args() {
             };
             int _engineResult = InternalUnsafeMethods.IgnoreListCount()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Removes all objects from the turret's ignore list.</summary>
        /// <description>
        /// All objects in this list will be ignored by the turret's targeting.
        /// </description>
        public void ClearIgnoreList() {
             InternalUnsafeMethods.ClearIgnoreList__Args _args = new InternalUnsafeMethods.ClearIgnoreList__Args() {
             };
             InternalUnsafeMethods.ClearIgnoreList()(ObjectPtr, _args);
        }

        /// <summary>Removes object from the turret's ignore list.</summary>
        /// <description>
        /// All objects in this list will be ignored by the turret's targeting.
        /// </description>
        /// <param name="obj">The ShapeBase object to once again allow for targeting.</param>
        public void RemoveFromIgnoreList(ShapeBase obj) {
             InternalUnsafeMethods.RemoveFromIgnoreList__Args _args = new InternalUnsafeMethods.RemoveFromIgnoreList__Args() {
                obj = obj.ObjectPtr,
             };
             InternalUnsafeMethods.RemoveFromIgnoreList()(ObjectPtr, _args);
        }

        /// <summary>Adds object to the turret's ignore list.</summary>
        /// <description>
        /// All objects in this list will be ignored by the turret's targeting.
        /// </description>
        /// <param name="obj">The ShapeBase object to ignore.</param>
        public void AddToIgnoreList(ShapeBase obj) {
             InternalUnsafeMethods.AddToIgnoreList__Args _args = new InternalUnsafeMethods.AddToIgnoreList__Args() {
                obj = obj.ObjectPtr,
             };
             InternalUnsafeMethods.AddToIgnoreList()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the AITurretShape class.
        /// </description>
        /// <returns>The type info object for AITurretShape</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }
    }
}