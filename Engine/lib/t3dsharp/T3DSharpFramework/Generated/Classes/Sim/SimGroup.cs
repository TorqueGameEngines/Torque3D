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
    /// <summary>A collection of SimObjects that are owned by the group.</summary>
    /// <description>
    /// A SimGroup is a stricter form of SimSet. SimObjects may only be a member of a single SimGroup at a time. The SimGroup will automatically enforce the single-group-membership rule (ie. adding an object to a SimGroup will cause it to be removed from its current SimGroup, if any).
    /// 
    /// Deleting a SimGroup will also delete all SimObjects in the SimGroup.
    /// </description>
    /// <code>
    /// // Create a SimGroup for particle emitters
    /// new SimGroup(Emitters)
    /// {
    ///    canSaveDynamicFields = "1";
    /// 
    ///    new ParticleEmitterNode(CrystalEmmiter) {
    ///       active = "1";
    ///       emitter = "dustEmitter";
    ///       velocity = "1";
    ///       dataBlock = "GenericSmokeEmitterNode";
    ///       position = "-61.6276 2.1142 4.45027";
    ///       rotation = "1 0 0 0";
    ///       scale = "1 1 1";
    ///       canSaveDynamicFields = "1";
    ///    };
    /// 
    ///    new ParticleEmitterNode(Steam1) {
    ///       active = "1";
    ///       emitter = "SlowSteamEmitter";
    ///       velocity = "1";
    ///       dataBlock = "GenericSmokeEmitterNode";
    ///       position = "-25.0458 1.55289 2.51308";
    ///       rotation = "1 0 0 0";
    ///       scale = "1 1 1";
    ///       canSaveDynamicFields = "1";
    ///    };
    /// };
    /// </code>
    public unsafe class SimGroup : SimSet {
        public SimGroup(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public SimGroup(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public SimGroup(string pName) 
            : this(pName, false) {
        }
        
        public SimGroup(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public SimGroup(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public SimGroup(SimObject pObj) 
            : base(pObj) {
        }
        
        public SimGroup(IntPtr pObj) 
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
                                "fnSimGroup_staticGetType"), typeof(_StaticGetType));
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
                                "fnSimGroup_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the SimGroup class.
        /// </description>
        /// <returns>The type info object for SimGroup</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }
    }
}