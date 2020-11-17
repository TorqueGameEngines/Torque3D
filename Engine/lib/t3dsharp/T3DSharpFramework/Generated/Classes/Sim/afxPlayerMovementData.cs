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
    /// <summary>A datablock that specifies a Player Movement effect.</summary>
    /// <description>
    /// Player Movement effects are used to directly alter the speed and/or movement direction of Player objects. The Player Movement effect is similar to the Player Puppet effect, but where puppet effects totally take over a Player's transformation using the AFX constraint system, Player Movement effects 'steer' the player using the same mechanisms that allow Player control from mouse and keyboard input. Another difference is that Player Movement effects only influence the server instance of a Player. Puppet effects can influence both the Player's server instance and its client ghosts.
    /// </description>
    public unsafe class afxPlayerMovementData : GameBaseData {
        public afxPlayerMovementData(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public afxPlayerMovementData(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public afxPlayerMovementData(string pName) 
            : this(pName, false) {
        }
        
        public afxPlayerMovementData(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public afxPlayerMovementData(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public afxPlayerMovementData(SimObject pObj) 
            : base(pObj) {
        }
        
        public afxPlayerMovementData(IntPtr pObj) 
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
                                "fnafxPlayerMovementData_staticGetType"), typeof(_StaticGetType));
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
                                "fnafxPlayerMovementData_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the afxPlayerMovementData class.
        /// </description>
        /// <returns>The type info object for afxPlayerMovementData</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// A floating-point multiplier that scales the constraint Player's movement speed.
        /// </description>
        /// </value>
        public float SpeedBias {
            get => GenericMarshal.StringTo<float>(GetFieldValue("speedBias"));
            set => SetFieldValue("speedBias", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public Point3F Movement {
            get => GenericMarshal.StringTo<Point3F>(GetFieldValue("movement"));
            set => SetFieldValue("movement", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Possible values: add, multiply, or replace.
        /// </description>
        /// </value>
        public afxPlayerMovement_OpType MovementOp {
            get => GenericMarshal.StringTo<afxPlayerMovement_OpType>(GetFieldValue("movementOp"));
            set => SetFieldValue("movementOp", GenericMarshal.ToString(value));
        }
    }
}