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
    /// <summary>A hovering vehicle.</summary>
    /// <description>
    /// A hover vehicle is a vehicle that maintains a specific distance between the vehicle and the ground at all times; unlike a flying vehicle which is free to ascend and descend at will.The model used for the HoverVehicle has the following requirements:
    /// <dl><dt>Collision mesh</dt><dd>A convex collision mesh at detail size -1.</dd><dt>JetNozzle0-1 nodes</dt><dd>Particle emitter nodes used when thrusting forward.</dd><dt>JetNozzle2-3 nodes</dt><dd>Particle emitter nodes used when thrusting downward.</dd><dt>JetNozzleX node</dt><dd>Particle emitter node used when thrusting backward.</dd><dt>activateBack animation</dt><dd>Non-cyclic animation sequence played when the vehicle begins thrusting forwards.</dd><dt>maintainBack animation</dt><dd>Cyclic animation sequence played after activateBack when the vehicle continues thrusting forwards.</dd></dl>
    /// </description>
    public unsafe class HoverVehicle : Vehicle {
        public HoverVehicle(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public HoverVehicle(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public HoverVehicle(string pName) 
            : this(pName, false) {
        }
        
        public HoverVehicle(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public HoverVehicle(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public HoverVehicle(SimObject pObj) 
            : base(pObj) {
        }
        
        public HoverVehicle(IntPtr pObj) 
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
                                "fnHoverVehicle_staticGetType"), typeof(_StaticGetType));
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
                                "fnHoverVehicle_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the HoverVehicle class.
        /// </description>
        /// <returns>The type info object for HoverVehicle</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }
    }
}