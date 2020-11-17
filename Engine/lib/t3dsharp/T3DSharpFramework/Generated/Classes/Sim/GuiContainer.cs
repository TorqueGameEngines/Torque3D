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
    /// <summary>Brief Desc.</summary>
    /// <description>
    /// 
    /// </description>
    /// <code>
    /// // Comment:
    /// %okButton = new ClassObject()
    /// instantiation
    /// </code>
    public unsafe class GuiContainer : GuiControl {
        public GuiContainer(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public GuiContainer(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public GuiContainer(string pName) 
            : this(pName, false) {
        }
        
        public GuiContainer(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public GuiContainer(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public GuiContainer(SimObject pObj) 
            : base(pObj) {
        }
        
        public GuiContainer(IntPtr pObj) 
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
                                "fnGuiContainer_staticGetType"), typeof(_StaticGetType));
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
                                "fnGuiContainer_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the GuiContainer class.
        /// </description>
        /// <returns>The type info object for GuiContainer</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// 
        /// </value>
        public GuiDockingType Docking {
            get => GenericMarshal.StringTo<GuiDockingType>(GetFieldValue("docking"));
            set => SetFieldValue("docking", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public RectSpacingI Margin {
            get => GenericMarshal.StringTo<RectSpacingI>(GetFieldValue("margin"));
            set => SetFieldValue("margin", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public RectSpacingI Padding {
            get => GenericMarshal.StringTo<RectSpacingI>(GetFieldValue("padding"));
            set => SetFieldValue("padding", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public bool AnchorTop {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("anchorTop"));
            set => SetFieldValue("anchorTop", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public bool AnchorBottom {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("anchorBottom"));
            set => SetFieldValue("anchorBottom", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public bool AnchorLeft {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("anchorLeft"));
            set => SetFieldValue("anchorLeft", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public bool AnchorRight {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("anchorRight"));
            set => SetFieldValue("anchorRight", GenericMarshal.ToString(value));
        }
    }
}