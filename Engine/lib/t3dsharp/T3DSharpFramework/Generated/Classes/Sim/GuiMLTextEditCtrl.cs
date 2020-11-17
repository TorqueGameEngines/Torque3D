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
    /// <summary>A text entry control that accepts the Gui Markup Language ('ML') tags and multiple lines.</summary>
    /// <description>
    /// 
    /// </description>
    /// <code>
    /// new GuiMLTextEditCtrl()
    /// 	{
    /// 		lineSpacing = "2";
    /// 		allowColorChars = "0";
    /// 		maxChars = "-1";
    /// 		deniedSound = "DeniedSoundProfile";
    /// 		text = "";
    /// 		escapeCommand = "onEscapeScriptFunction();";
    /// 	  //Properties not specific to this control have been omitted from this example.
    /// 	};
    /// </code>
    /// <see cref="GuiMLTextCtrl" />
    /// <see cref="GuiControl" />
    public unsafe class GuiMLTextEditCtrl : GuiMLTextCtrl {
        public GuiMLTextEditCtrl(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public GuiMLTextEditCtrl(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public GuiMLTextEditCtrl(string pName) 
            : this(pName, false) {
        }
        
        public GuiMLTextEditCtrl(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public GuiMLTextEditCtrl(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public GuiMLTextEditCtrl(SimObject pObj) 
            : base(pObj) {
        }
        
        public GuiMLTextEditCtrl(IntPtr pObj) 
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
                                "fnGuiMLTextEditCtrl_staticGetType"), typeof(_StaticGetType));
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
                                "fnGuiMLTextEditCtrl_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the GuiMLTextEditCtrl class.
        /// </description>
        /// <returns>The type info object for GuiMLTextEditCtrl</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Script function to run whenever the 'escape' key is pressed when this control is in focus.
        /// </description>
        /// </value>
        public string EscapeCommand {
            get => GenericMarshal.StringTo<string>(GetFieldValue("escapeCommand"));
            set => SetFieldValue("escapeCommand", GenericMarshal.ToString(value));
        }
    }
}