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
    /// <summary>A button that is used to represent color; often used in correlation with a color picker.</summary>
    /// <description>
    /// A swatch button is a push button that uses its color field to designate the color drawn over an image, on top of a button.
    /// 
    /// The color itself is a float value stored inside the GuiSwatchButtonCtrl::color field. The texture path that represents
    /// the image underlying the color is stored inside the GuiSwatchButtonCtrl::gridBitmap field.
    /// The default value assigned toGuiSwatchButtonCtrl::color is "1 1 1 1"( White ). The default/fallback image assigned to 
    /// GuiSwatchButtonCtrl::gridBitmap is "tools/gui/images/transp_grid".
    /// </description>
    /// <code>
    /// // Create a GuiSwatchButtonCtrl that calls randomFunction with its current color when clicked
    /// %swatchButton = new GuiSwatchButtonCtrl()
    /// {
    ///    profile = "GuiInspectorSwatchButtonProfile";
    ///    command = "randomFunction( $ThisControl.color );";
    /// };
    /// </code>
    public unsafe class GuiSwatchButtonCtrl : GuiButtonBaseCtrl {
        public GuiSwatchButtonCtrl(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public GuiSwatchButtonCtrl(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public GuiSwatchButtonCtrl(string pName) 
            : this(pName, false) {
        }
        
        public GuiSwatchButtonCtrl(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public GuiSwatchButtonCtrl(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public GuiSwatchButtonCtrl(SimObject pObj) 
            : base(pObj) {
        }
        
        public GuiSwatchButtonCtrl(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct SetColor__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string newColor;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetColor(IntPtr _this, SetColor__Args args);
            private static _SetColor _SetColorFunc;
            internal static _SetColor SetColor() {
                if (_SetColorFunc == null) {
                    _SetColorFunc =
                        (_SetColor)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiSwatchButtonCtrl_setColor"), typeof(_SetColor));
                }
                
                return _SetColorFunc;
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
                                "fnGuiSwatchButtonCtrl_staticGetType"), typeof(_StaticGetType));
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
                                "fnGuiSwatchButtonCtrl_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Set the color of the swatch control.
        /// </description>
        /// <param name="newColor">The new color string given to the swatch control in float format "r g b a".</param>
        /// <remarks> It's also important to note that when setColor is called causes
        /// the control's altCommand field to be executed.</remarks>
        public void SetColor(string newColor) {
             InternalUnsafeMethods.SetColor__Args _args = new InternalUnsafeMethods.SetColor__Args() {
                newColor = newColor,
             };
             InternalUnsafeMethods.SetColor()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the GuiSwatchButtonCtrl class.
        /// </description>
        /// <returns>The type info object for GuiSwatchButtonCtrl</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// The foreground color of GuiSwatchButtonCtrl
        /// </description>
        /// </value>
        public LinearColorF Color {
            get => GenericMarshal.StringTo<LinearColorF>(GetFieldValue("color"));
            set => SetFieldValue("color", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The bitmap used for the transparent grid
        /// </description>
        /// </value>
        public string GridBitmap {
            get => GenericMarshal.StringTo<string>(GetFieldValue("gridBitmap"));
            set => SetFieldValue("gridBitmap", GenericMarshal.ToString(value));
        }
    }
}