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
    public unsafe class RibbonNode : GameBase {
        public RibbonNode(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public RibbonNode(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public RibbonNode(string pName) 
            : this(pName, false) {
        }
        
        public RibbonNode(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public RibbonNode(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public RibbonNode(SimObject pObj) 
            : base(pObj) {
        }
        
        public RibbonNode(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct SetActive__Args
            {
                [MarshalAs(UnmanagedType.I1)]
                internal bool active;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetActive(IntPtr _this, SetActive__Args args);
            private static _SetActive _SetActiveFunc;
            internal static _SetActive SetActive() {
                if (_SetActiveFunc == null) {
                    _SetActiveFunc =
                        (_SetActive)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnRibbonNode_setActive"), typeof(_SetActive));
                }
                
                return _SetActiveFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetRibbonDatablock__Args
            {
                internal IntPtr ribbonDatablock;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetRibbonDatablock(IntPtr _this, SetRibbonDatablock__Args args);
            private static _SetRibbonDatablock _SetRibbonDatablockFunc;
            internal static _SetRibbonDatablock SetRibbonDatablock() {
                if (_SetRibbonDatablockFunc == null) {
                    _SetRibbonDatablockFunc =
                        (_SetRibbonDatablock)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnRibbonNode_setRibbonDatablock"), typeof(_SetRibbonDatablock));
                }
                
                return _SetRibbonDatablockFunc;
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
                                "fnRibbonNode_staticGetType"), typeof(_StaticGetType));
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
                                "fnRibbonNode_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Turns the ribbon on or off.
        /// </description>
        /// <param name="active">New ribbon state</param>
        public void SetActive(bool active) {
             InternalUnsafeMethods.SetActive__Args _args = new InternalUnsafeMethods.SetActive__Args() {
                active = active,
             };
             InternalUnsafeMethods.SetActive()(ObjectPtr, _args);
        }

        /// <description>
        /// Assigns the datablock for this ribbon node.
        /// </description>
        /// <param name="ribbonDatablock">RibbonData datablock to assign</param>
        /// <code>
        /// // Assign a new emitter datablock
        /// %emitter.setRibbonDatablock( %ribbonDatablock );
        /// </code>
        public void SetRibbonDatablock(RibbonData ribbonDatablock = null) {
             InternalUnsafeMethods.SetRibbonDatablock__Args _args = new InternalUnsafeMethods.SetRibbonDatablock__Args() {
                ribbonDatablock = ribbonDatablock.ObjectPtr,
             };
             InternalUnsafeMethods.SetRibbonDatablock()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the RibbonNode class.
        /// </description>
        /// <returns>The type info object for RibbonNode</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Controls whether ribbon is emitted from this node.
        /// </description>
        /// </value>
        public bool Active {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("active"));
            set => SetFieldValue("active", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Datablock to use for the ribbon.
        /// </description>
        /// </value>
        public RibbonData Ribbon {
            get => GenericMarshal.StringTo<RibbonData>(GetFieldValue("Ribbon"));
            set => SetFieldValue("Ribbon", GenericMarshal.ToString(value));
        }
    }
}