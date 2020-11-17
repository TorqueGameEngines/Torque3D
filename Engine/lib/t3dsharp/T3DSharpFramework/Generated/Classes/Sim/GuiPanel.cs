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
    /// <summary>The GuiPanel panel is a container that when opaque will draw a left to right gradient using its profile fill and fill highlight colors.</summary>
    /// <description>
    /// 
    /// </description>
    /// <code>
    /// // Mandatory GuiDefaultProfile
    /// // Contains the fill color information required by a GuiPanel
    /// // Some values left out for sake of this example
    /// new GuiControlProfile (GuiDefaultProfile)
    /// {
    /// 	// fill color
    /// 	opaque = false;
    /// 	fillColor = "242 241 240";
    /// 	fillColorHL ="228 228 235";
    /// 	fillColorSEL = "98 100 137";
    /// 	fillColorNA = "255 255 255 ";
    /// };
    /// 
    /// new GuiPanel(TestPanel)
    /// {
    /// 	position = "45 33";
    /// 	extent = "342 379";
    /// 	minExtent = "16 16";
    /// 	horizSizing = "right";
    /// 	vertSizing = "bottom";
    /// 	profile = "GuiDefaultProfile"; // Color fill info is in this profile
    /// 	isContainer = "1";
    /// };
    /// </code>
    /// <see cref="GuiControlProfile" />
    public unsafe class GuiPanel : GuiContainer {
        public GuiPanel(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public GuiPanel(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public GuiPanel(string pName) 
            : this(pName, false) {
        }
        
        public GuiPanel(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public GuiPanel(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public GuiPanel(SimObject pObj) 
            : base(pObj) {
        }
        
        public GuiPanel(IntPtr pObj) 
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
                                "fnGuiPanel_staticGetType"), typeof(_StaticGetType));
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
                                "fnGuiPanel_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the GuiPanel class.
        /// </description>
        /// <returns>The type info object for GuiPanel</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }
    }
}