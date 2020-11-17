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
    /// <summary>Text entry element of a GuiConsole.</summary>
    /// <description>
    /// 
    /// </description>
    /// <code>
    /// new GuiConsoleEditCtrl(ConsoleEntry)
    /// {
    ///    profile = "ConsoleTextEditProfile";
    ///    horizSizing = "width";
    ///    vertSizing = "top";
    ///    position = "0 462";
    ///    extent = "640 18";
    ///    minExtent = "8 8";
    ///    visible = "1";
    ///    altCommand = "ConsoleEntry::eval();";
    ///    helpTag = "0";
    ///    maxLength = "255";
    ///    historySize = "40";
    ///    password = "0";
    ///    tabComplete = "0";
    ///    sinkAllKeyEvents = "1";
    ///    useSiblingScroller = "1";
    /// };
    /// </code>
    public unsafe class GuiConsoleEditCtrl : GuiTextEditCtrl {
        public GuiConsoleEditCtrl(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public GuiConsoleEditCtrl(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public GuiConsoleEditCtrl(string pName) 
            : this(pName, false) {
        }
        
        public GuiConsoleEditCtrl(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public GuiConsoleEditCtrl(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public GuiConsoleEditCtrl(SimObject pObj) 
            : base(pObj) {
        }
        
        public GuiConsoleEditCtrl(IntPtr pObj) 
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
                                "fnGuiConsoleEditCtrl_staticGetType"), typeof(_StaticGetType));
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
                                "fnGuiConsoleEditCtrl_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the GuiConsoleEditCtrl class.
        /// </description>
        /// <returns>The type info object for GuiConsoleEditCtrl</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// 
        /// </value>
        public bool UseSiblingScroller {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("useSiblingScroller"));
            set => SetFieldValue("useSiblingScroller", GenericMarshal.ToString(value));
        }
    }
}