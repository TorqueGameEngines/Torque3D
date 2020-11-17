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
    /// <summary>A datablock that specifies a Player Puppet effect.</summary>
    /// <description>
    /// Player Puppet effects are defined using the afxPlayerPuppetData datablock and are used to control the movement of Player objects with the AFX constraint system. The Player Puppet effect is similar to the Player Movement effect, but where movement effects 'steer' the player using the same mechanisms that allow Player control from mouse and keyboard input, Player Puppet effects totally take over a Player's transformation using the AFX constraint system.
    /// 
    /// Player Puppet can be configured to directly move a Player's client ghosts as well as its server instance. When doing this, it is important to keep the general motion of the Player object and its ghosts somewhat consistent. Otherwise, obvious discontinuities in the motion will result when the Player Puppet ends and control is restored to the server Player.
    /// </description>
    public unsafe class afxPlayerPuppetData : GameBaseData {
        public afxPlayerPuppetData(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public afxPlayerPuppetData(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public afxPlayerPuppetData(string pName) 
            : this(pName, false) {
        }
        
        public afxPlayerPuppetData(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public afxPlayerPuppetData(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public afxPlayerPuppetData(SimObject pObj) 
            : base(pObj) {
        }
        
        public afxPlayerPuppetData(IntPtr pObj) 
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
                                "fnafxPlayerPuppetData_staticGetType"), typeof(_StaticGetType));
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
                                "fnafxPlayerPuppetData_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the afxPlayerPuppetData class.
        /// </description>
        /// <returns>The type info object for afxPlayerPuppetData</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// ...
        /// </description>
        /// </value>
        public string ObjectSpec {
            get => GenericMarshal.StringTo<string>(GetFieldValue("objectSpec"));
            set => SetFieldValue("objectSpec", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// ...
        /// </description>
        /// </value>
        public sbyte Networking {
            get => GenericMarshal.StringTo<sbyte>(GetFieldValue("networking"));
            set => SetFieldValue("networking", GenericMarshal.ToString(value));
        }
    }
}