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
    /// <summary>A SimSet that can be safely persisted.</summary>
    /// <description>
    /// Uses SimPersistIDs to reference objects in the set while persisted on disk.  This allows the set to resolve its references no matter whether they are loaded before or after the set is created.
    /// 
    /// Not intended for game development, for editors or internal use only.
    /// </description>
    public unsafe class SimPersistSet : SimSet {
        public SimPersistSet(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public SimPersistSet(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public SimPersistSet(string pName) 
            : this(pName, false) {
        }
        
        public SimPersistSet(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public SimPersistSet(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public SimPersistSet(SimObject pObj) 
            : base(pObj) {
        }
        
        public SimPersistSet(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct ResolvePersistentIds__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ResolvePersistentIds(IntPtr _this, ResolvePersistentIds__Args args);
            private static _ResolvePersistentIds _ResolvePersistentIdsFunc;
            internal static _ResolvePersistentIds ResolvePersistentIds() {
                if (_ResolvePersistentIdsFunc == null) {
                    _ResolvePersistentIdsFunc =
                        (_ResolvePersistentIds)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSimPersistSet_resolvePersistentIds"), typeof(_ResolvePersistentIds));
                }
                
                return _ResolvePersistentIdsFunc;
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
                                "fnSimPersistSet_staticGetType"), typeof(_StaticGetType));
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
                                "fnSimPersistSet_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// () - Try to bind unresolved persistent IDs in the set.
        /// </description>
        public void ResolvePersistentIds() {
             InternalUnsafeMethods.ResolvePersistentIds__Args _args = new InternalUnsafeMethods.ResolvePersistentIds__Args() {
             };
             InternalUnsafeMethods.ResolvePersistentIds()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the SimPersistSet class.
        /// </description>
        /// <returns>The type info object for SimPersistSet</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }
    }
}