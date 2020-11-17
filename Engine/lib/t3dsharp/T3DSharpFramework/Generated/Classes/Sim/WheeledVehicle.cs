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
    /// <summary>A wheeled vehicle.</summary>
    /// <description>
    /// 
    /// </description>
    public unsafe class WheeledVehicle : Vehicle {
        public WheeledVehicle(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public WheeledVehicle(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public WheeledVehicle(string pName) 
            : this(pName, false) {
        }
        
        public WheeledVehicle(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public WheeledVehicle(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public WheeledVehicle(SimObject pObj) 
            : base(pObj) {
        }
        
        public WheeledVehicle(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct GetWheelCount__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetWheelCount(IntPtr _this, GetWheelCount__Args args);
            private static _GetWheelCount _GetWheelCountFunc;
            internal static _GetWheelCount GetWheelCount() {
                if (_GetWheelCountFunc == null) {
                    _GetWheelCountFunc =
                        (_GetWheelCount)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnWheeledVehicle_getWheelCount"), typeof(_GetWheelCount));
                }
                
                return _GetWheelCountFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetWheelSpring__Args
            {
                internal int wheel;
                internal IntPtr spring;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _SetWheelSpring(IntPtr _this, SetWheelSpring__Args args);
            private static _SetWheelSpring _SetWheelSpringFunc;
            internal static _SetWheelSpring SetWheelSpring() {
                if (_SetWheelSpringFunc == null) {
                    _SetWheelSpringFunc =
                        (_SetWheelSpring)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnWheeledVehicle_setWheelSpring"), typeof(_SetWheelSpring));
                }
                
                return _SetWheelSpringFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetWheelTire__Args
            {
                internal int wheel;
                internal IntPtr tire;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _SetWheelTire(IntPtr _this, SetWheelTire__Args args);
            private static _SetWheelTire _SetWheelTireFunc;
            internal static _SetWheelTire SetWheelTire() {
                if (_SetWheelTireFunc == null) {
                    _SetWheelTireFunc =
                        (_SetWheelTire)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnWheeledVehicle_setWheelTire"), typeof(_SetWheelTire));
                }
                
                return _SetWheelTireFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetWheelPowered__Args
            {
                internal int wheel;
                [MarshalAs(UnmanagedType.I1)]
                internal bool powered;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _SetWheelPowered(IntPtr _this, SetWheelPowered__Args args);
            private static _SetWheelPowered _SetWheelPoweredFunc;
            internal static _SetWheelPowered SetWheelPowered() {
                if (_SetWheelPoweredFunc == null) {
                    _SetWheelPoweredFunc =
                        (_SetWheelPowered)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnWheeledVehicle_setWheelPowered"), typeof(_SetWheelPowered));
                }
                
                return _SetWheelPoweredFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetWheelSteering__Args
            {
                internal int wheel;
                internal float steering;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _SetWheelSteering(IntPtr _this, SetWheelSteering__Args args);
            private static _SetWheelSteering _SetWheelSteeringFunc;
            internal static _SetWheelSteering SetWheelSteering() {
                if (_SetWheelSteeringFunc == null) {
                    _SetWheelSteeringFunc =
                        (_SetWheelSteering)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnWheeledVehicle_setWheelSteering"), typeof(_SetWheelSteering));
                }
                
                return _SetWheelSteeringFunc;
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
                                "fnWheeledVehicle_staticGetType"), typeof(_StaticGetType));
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
                                "fnWheeledVehicle_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <summary>Get the number of wheels on this vehicle.</summary>
        /// <description>
        /// 
        /// </description>
        /// <returns>the number of wheels (equal to the number of hub nodes defined in the model)</returns>
        public int GetWheelCount() {
             InternalUnsafeMethods.GetWheelCount__Args _args = new InternalUnsafeMethods.GetWheelCount__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetWheelCount()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Set the WheeledVehicleSpring datablock for this wheel.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="wheel">index of the wheel to set (hub node #)</param>
        /// <param name="spring">WheeledVehicleSpring datablock</param>
        /// <returns>true if successful, false if failed</returns>
        /// <code>
        /// %obj.setWheelSpring( 0, FrontSpring );
        /// </code>
        public bool SetWheelSpring(int wheel, WheeledVehicleSpring spring) {
             InternalUnsafeMethods.SetWheelSpring__Args _args = new InternalUnsafeMethods.SetWheelSpring__Args() {
                wheel = wheel,
                spring = spring.ObjectPtr,
             };
             bool _engineResult = InternalUnsafeMethods.SetWheelSpring()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Set the WheeledVehicleTire datablock for this wheel.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="wheel">index of the wheel to set (hub node #)</param>
        /// <param name="tire">WheeledVehicleTire datablock</param>
        /// <returns>true if successful, false if failed</returns>
        /// <code>
        /// %obj.setWheelTire( 0, FrontTire );
        /// </code>
        public bool SetWheelTire(int wheel, WheeledVehicleTire tire) {
             InternalUnsafeMethods.SetWheelTire__Args _args = new InternalUnsafeMethods.SetWheelTire__Args() {
                wheel = wheel,
                tire = tire.ObjectPtr,
             };
             bool _engineResult = InternalUnsafeMethods.SetWheelTire()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Set whether the wheel is powered (has torque applied from the engine).</summary>
        /// <description>
        /// A rear wheel drive car for example would set the front wheels to false, and the rear wheels to true.
        /// </description>
        /// <param name="wheel">index of the wheel to set (hub node #)</param>
        /// <param name="powered">flag indicating whether to power the wheel or not</param>
        /// <returns>true if successful, false if failed</returns>
        public bool SetWheelPowered(int wheel, bool powered) {
             InternalUnsafeMethods.SetWheelPowered__Args _args = new InternalUnsafeMethods.SetWheelPowered__Args() {
                wheel = wheel,
                powered = powered,
             };
             bool _engineResult = InternalUnsafeMethods.SetWheelPowered()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Set how much the wheel is affected by steering.</summary>
        /// <description>
        /// The steering factor controls how much the wheel is rotated by the vehicle steering. For example, most cars would have their front wheels set to 1.0, and their rear wheels set to 0 since only the front wheels should turn.
        /// 
        /// Negative values will turn the wheel in the opposite direction to the steering angle.
        /// </description>
        /// <param name="wheel">index of the wheel to set (hub node #)</param>
        /// <param name="steering">steering factor from -1 (full inverse) to 1 (full)</param>
        /// <returns>true if successful, false if failed</returns>
        public bool SetWheelSteering(int wheel, float steering) {
             InternalUnsafeMethods.SetWheelSteering__Args _args = new InternalUnsafeMethods.SetWheelSteering__Args() {
                wheel = wheel,
                steering = steering,
             };
             bool _engineResult = InternalUnsafeMethods.SetWheelSteering()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Get the type info object for the WheeledVehicle class.
        /// </description>
        /// <returns>The type info object for WheeledVehicle</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }
    }
}