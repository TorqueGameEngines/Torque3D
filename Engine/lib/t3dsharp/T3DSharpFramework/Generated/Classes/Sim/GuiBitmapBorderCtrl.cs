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
    /// <summary>A control that renders a skinned border specified in its profile.</summary>
    /// <description>
    /// This control uses the bitmap specified in it's profile (GuiControlProfile::bitmapName).  It takes this image and breaks up aspects of it to skin the border of this control with.  It is also important to set GuiControlProfile::hasBitmapArray to true on the profile as well.
    /// 
    /// The bitmap referenced should be broken up into a 3 x 3 grid (using the top left color pixel as a border color between each of the images) in which it will map to the following places:
    /// 1 = Top Left Corner
    /// 2 = Top Right Corner
    /// 3 = Top Center
    /// 4 = Left Center
    /// 5 = Right Center
    /// 6 = Bottom Left Corner
    /// 7 = Bottom Center
    /// 8 = Bottom Right Corner
    /// 0 = Nothing
    /// 
    /// 1 2 3
    /// 4 5 0
    /// 6 7 8
    /// </description>
    /// <code>
    /// singleton GuiControlProfile (BorderGUIProfile)
    /// {
    ///    bitmap = "core/art/gui/images/borderArray";
    ///    hasBitmapArray = true;
    ///    opaque = false;
    /// };
    /// 
    /// new GuiBitmapBorderCtrl(BitmapBorderGUI)
    /// {
    ///    profile = "BorderGUIProfile";
    ///    position = "0 0";
    ///    extent = "400 40";
    ///    visible = "1";
    /// };
    /// </code>
    /// <see cref="GuiControlProfile::bitmapName" />
    /// <see cref="GuiControlProfile::hasBitmapArray" />
    public unsafe class GuiBitmapBorderCtrl : GuiControl {
        public GuiBitmapBorderCtrl(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public GuiBitmapBorderCtrl(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public GuiBitmapBorderCtrl(string pName) 
            : this(pName, false) {
        }
        
        public GuiBitmapBorderCtrl(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public GuiBitmapBorderCtrl(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public GuiBitmapBorderCtrl(SimObject pObj) 
            : base(pObj) {
        }
        
        public GuiBitmapBorderCtrl(IntPtr pObj) 
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
                                "fnGuiBitmapBorderCtrl_staticGetType"), typeof(_StaticGetType));
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
                                "fnGuiBitmapBorderCtrl_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the GuiBitmapBorderCtrl class.
        /// </description>
        /// <returns>The type info object for GuiBitmapBorderCtrl</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }
    }
}