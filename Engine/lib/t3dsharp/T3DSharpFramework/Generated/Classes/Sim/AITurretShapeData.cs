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
    /// <summary>Defines properties for an AITurretShape object.</summary>
    /// <description>
    /// 
    /// </description>
    /// <see cref="AITurretShape" />
    /// <see cref="TurretShapeData" />
    public unsafe class AITurretShapeData : TurretShapeData {
        public AITurretShapeData(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public AITurretShapeData(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public AITurretShapeData(string pName) 
            : this(pName, false) {
        }
        
        public AITurretShapeData(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public AITurretShapeData(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public AITurretShapeData(SimObject pObj) 
            : base(pObj) {
        }
        
        public AITurretShapeData(IntPtr pObj) 
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
                                "fnAITurretShapeData_staticGetType"), typeof(_StaticGetType));
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
                                "fnAITurretShapeData_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the AITurretShapeData class.
        /// </description>
        /// <returns>The type info object for AITurretShapeData</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <summary>Maximum number of degrees to scan left and right.</summary>
        /// <description>
        /// 
        /// </description>
        /// <remarks> Maximum scan heading is 90 degrees.
        /// </remarks>
        /// </value>
        public float MaxScanHeading {
            get => GenericMarshal.StringTo<float>(GetFieldValue("maxScanHeading"));
            set => SetFieldValue("maxScanHeading", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Maximum number of degrees to scan up and down.</summary>
        /// <description>
        /// 
        /// </description>
        /// <remarks> Maximum scan pitch is 90 degrees.
        /// </remarks>
        /// </value>
        public float MaxScanPitch {
            get => GenericMarshal.StringTo<float>(GetFieldValue("maxScanPitch"));
            set => SetFieldValue("maxScanPitch", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Maximum distance to scan.</summary>
        /// <description>
        /// When combined with maxScanHeading and maxScanPitch this forms a 3D scanning wedge used to initially locate a target.
        /// </description>
        /// </value>
        public float MaxScanDistance {
            get => GenericMarshal.StringTo<float>(GetFieldValue("maxScanDistance"));
            set => SetFieldValue("maxScanDistance", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>How often should we perform a full scan when looking for a target.</summary>
        /// <description>
        /// Expressed as the number of ticks between full scans, but no less than 1.
        /// </description>
        /// </value>
        public int ScanTickFrequency {
            get => GenericMarshal.StringTo<int>(GetFieldValue("scanTickFrequency"));
            set => SetFieldValue("scanTickFrequency", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Random amount that should be added to the scan tick frequency each scan period.</summary>
        /// <description>
        /// Expressed as the number of ticks to randomly add, but no less than zero.
        /// </description>
        /// </value>
        public int ScanTickFrequencyVariance {
            get => GenericMarshal.StringTo<int>(GetFieldValue("scanTickFrequencyVariance"));
            set => SetFieldValue("scanTickFrequencyVariance", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>How long after the turret has lost the target should it still track it.</summary>
        /// <description>
        /// Expressed in seconds.
        /// </description>
        /// </value>
        public float TrackLostTargetTime {
            get => GenericMarshal.StringTo<float>(GetFieldValue("trackLostTargetTime"));
            set => SetFieldValue("trackLostTargetTime", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Maximum distance that the weapon will fire upon a target.</summary>
        /// <description>
        /// 
        /// </description>
        /// </value>
        public float MaxWeaponRange {
            get => GenericMarshal.StringTo<float>(GetFieldValue("maxWeaponRange"));
            set => SetFieldValue("maxWeaponRange", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Velocity used to lead target.</summary>
        /// <description>
        /// If value <= 0, don't lead target.
        /// </description>
        /// </value>
        public float WeaponLeadVelocity {
            get => GenericMarshal.StringTo<float>(GetFieldValue("weaponLeadVelocity"));
            set => SetFieldValue("weaponLeadVelocity", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Name of this state.
        /// </description>
        /// </value>
        public DynamicFieldVector<string> StateName {
            get => new DynamicFieldVector<string>(
                    this, 
                    "stateName", 
                    31, 
                    val => GenericMarshal.StringTo<string>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Name of the state to transition to when the turret is at rest (static).
        /// </description>
        /// </value>
        public DynamicFieldVector<string> StateTransitionOnAtRest {
            get => new DynamicFieldVector<string>(
                    this, 
                    "stateTransitionOnAtRest", 
                    31, 
                    val => GenericMarshal.StringTo<string>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Name of the state to transition to when the turret is not at rest (not static).
        /// </description>
        /// </value>
        public DynamicFieldVector<string> StateTransitionOnNotAtRest {
            get => new DynamicFieldVector<string>(
                    this, 
                    "stateTransitionOnNotAtRest", 
                    31, 
                    val => GenericMarshal.StringTo<string>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Name of the state to transition to when the turret gains a target.
        /// </description>
        /// </value>
        public DynamicFieldVector<string> StateTransitionOnTarget {
            get => new DynamicFieldVector<string>(
                    this, 
                    "stateTransitionOnTarget", 
                    31, 
                    val => GenericMarshal.StringTo<string>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Name of the state to transition to when the turret loses a target.
        /// </description>
        /// </value>
        public DynamicFieldVector<string> StateTransitionOnNoTarget {
            get => new DynamicFieldVector<string>(
                    this, 
                    "stateTransitionOnNoTarget", 
                    31, 
                    val => GenericMarshal.StringTo<string>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Name of the state to transition to when the turret goes from deactivated to activated.
        /// </description>
        /// </value>
        public DynamicFieldVector<string> StateTransitionOnActivated {
            get => new DynamicFieldVector<string>(
                    this, 
                    "stateTransitionOnActivated", 
                    31, 
                    val => GenericMarshal.StringTo<string>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Name of the state to transition to when the turret goes from activated to deactivated
        /// </description>
        /// </value>
        public DynamicFieldVector<string> StateTransitionOnDeactivated {
            get => new DynamicFieldVector<string>(
                    this, 
                    "stateTransitionOnDeactivated", 
                    31, 
                    val => GenericMarshal.StringTo<string>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Name of the state to transition to when we have been in this state for stateTimeoutValue seconds.
        /// </description>
        /// </value>
        public DynamicFieldVector<string> StateTransitionOnTimeout {
            get => new DynamicFieldVector<string>(
                    this, 
                    "stateTransitionOnTimeout", 
                    31, 
                    val => GenericMarshal.StringTo<string>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Time in seconds to wait before transitioning to stateTransitionOnTimeout.
        /// </description>
        /// </value>
        public DynamicFieldVector<float> StateTimeoutValue {
            get => new DynamicFieldVector<float>(
                    this, 
                    "stateTimeoutValue", 
                    31, 
                    val => GenericMarshal.StringTo<float>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// If false, this state ignores stateTimeoutValue and transitions immediately if other transition conditions are met.
        /// </description>
        /// </value>
        public DynamicFieldVector<bool> StateWaitForTimeout {
            get => new DynamicFieldVector<bool>(
                    this, 
                    "stateWaitForTimeout", 
                    31, 
                    val => GenericMarshal.StringTo<bool>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// The first state with this set to true is the state entered by the client when it receives the 'fire' event.
        /// </description>
        /// </value>
        public DynamicFieldVector<bool> StateFire {
            get => new DynamicFieldVector<bool>(
                    this, 
                    "stateFire", 
                    31, 
                    val => GenericMarshal.StringTo<bool>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Indicates the turret should perform a continuous scan looking for targets.
        /// </description>
        /// </value>
        public DynamicFieldVector<bool> StateScan {
            get => new DynamicFieldVector<bool>(
                    this, 
                    "stateScan", 
                    31, 
                    val => GenericMarshal.StringTo<bool>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <summary>Direction of the animation to play in this state.</summary>
        /// <description>
        /// True is forward, false is backward.
        /// </description>
        /// </value>
        public DynamicFieldVector<bool> StateDirection {
            get => new DynamicFieldVector<bool>(
                    this, 
                    "stateDirection", 
                    31, 
                    val => GenericMarshal.StringTo<bool>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Name of the sequence to play on entry to this state.
        /// </description>
        /// </value>
        public DynamicFieldVector<string> StateSequence {
            get => new DynamicFieldVector<string>(
                    this, 
                    "stateSequence", 
                    31, 
                    val => GenericMarshal.StringTo<string>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// If true, the timeScale of the stateSequence animation will be adjusted such that the sequence plays for stateTimeoutValue seconds.
        /// </description>
        /// </value>
        public DynamicFieldVector<bool> StateScaleAnimation {
            get => new DynamicFieldVector<bool>(
                    this, 
                    "stateScaleAnimation", 
                    31, 
                    val => GenericMarshal.StringTo<bool>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <summary>Method to execute on entering this state.</summary>
        /// <description>
        /// Scoped to AITurretShapeData.
        /// </description>
        /// </value>
        public DynamicFieldVector<string> StateScript {
            get => new DynamicFieldVector<string>(
                    this, 
                    "stateScript", 
                    31, 
                    val => GenericMarshal.StringTo<string>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }
    }
}