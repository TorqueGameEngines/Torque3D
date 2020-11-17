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
    /// <summary>A datablock that specifies a Gui Controller effect.</summary>
    /// <description>
    /// A Gui Controller enables effect manipulation of pre-existing gui controls. With a Gui Controller effect, a regular gui control is located by name, made visible during the lifetime of the effect, and potentially repositioned by projecting 3D constraint positions into 2D screen space. In addition, when used with a progress-bar control, (GuiProgressCtrl, afxSpellCastBar, afxStatusBar), the progress-bar will continuously reflect the elapsed progress of the effect over its lifetime.
    /// </description>
    public unsafe class afxGuiControllerData : GameBaseData {
        public afxGuiControllerData(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public afxGuiControllerData(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public afxGuiControllerData(string pName) 
            : this(pName, false) {
        }
        
        public afxGuiControllerData(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public afxGuiControllerData(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public afxGuiControllerData(SimObject pObj) 
            : base(pObj) {
        }
        
        public afxGuiControllerData(IntPtr pObj) 
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
                                "fnafxGuiControllerData_staticGetType"), typeof(_StaticGetType));
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
                                "fnafxGuiControllerData_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the afxGuiControllerData class.
        /// </description>
        /// <returns>The type info object for afxGuiControllerData</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Specifies the name of an existing gui-control.
        /// </description>
        /// </value>
        public string ControlName {
            get => GenericMarshal.StringTo<string>(GetFieldValue("controlName"));
            set => SetFieldValue("controlName", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// When true, the gui-control will retain its initial position, otherwise the gui-control position will be continuously updated using a projection of the 3D constraint position into 2D screen coordinates.
        /// </description>
        /// </value>
        public bool PreservePosition {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("preservePosition"));
            set => SetFieldValue("preservePosition", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// If true, the effect will only be applied to a gui-control on the client that matches the controlling-client of the primary position constraint object.
        /// </description>
        /// </value>
        public bool ControllingClientOnly {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("controllingClientOnly"));
            set => SetFieldValue("controllingClientOnly", GenericMarshal.ToString(value));
        }
    }
}