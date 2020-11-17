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
    /// <summary>Draws the bitmap within a special button control.  Only a single bitmap is used and the</summary>
    /// <description>
    /// button will be drawn in a highlighted mode when the mouse hovers over it or when it
    /// has been clicked.
    /// </description>
    /// <code>
    /// new GuiIconButtonCtrl(TestIconButton)
    /// {
    ///  buttonMargin = "4 4";
    ///  iconBitmap = "art/gui/lagIcon.png";
    ///  iconLocation = "Center";
    ///  sizeIconToButton = "0";
    ///  makeIconSquare = "1";
    ///  textLocation = "Bottom";
    ///  textMargin = "-2";
    ///   autoSize = "0";
    ///   text = "Lag Icon";
    ///   textID = ""STR_LAG"";
    ///   buttonType = "PushButton";
    ///   profile = "GuiIconButtonProfile";
    /// };
    /// </code>
    /// <see cref="GuiControl" />
    /// <see cref="GuiButtonCtrl" />
    public unsafe class GuiIconButtonCtrl : GuiButtonCtrl {
        public GuiIconButtonCtrl(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public GuiIconButtonCtrl(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public GuiIconButtonCtrl(string pName) 
            : this(pName, false) {
        }
        
        public GuiIconButtonCtrl(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public GuiIconButtonCtrl(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public GuiIconButtonCtrl(SimObject pObj) 
            : base(pObj) {
        }
        
        public GuiIconButtonCtrl(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct SetBitmap__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string buttonFilename;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetBitmap(IntPtr _this, SetBitmap__Args args);
            private static _SetBitmap _SetBitmapFunc;
            internal static _SetBitmap SetBitmap() {
                if (_SetBitmapFunc == null) {
                    _SetBitmapFunc =
                        (_SetBitmap)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiIconButtonCtrl_setBitmap"), typeof(_SetBitmap));
                }
                
                return _SetBitmapFunc;
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
                                "fnGuiIconButtonCtrl_staticGetType"), typeof(_StaticGetType));
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
                                "fnGuiIconButtonCtrl_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <summary>Set the bitmap to use for the button portion of this control.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="buttonFilename">Filename for the image</param>
        /// <code>
        /// // Define the button filename
        /// %buttonFilename = "pearlButton";
        /// 
        /// // Inform the GuiIconButtonCtrl control to update its main button graphic to the defined bitmap
        /// %thisGuiIconButtonCtrl.setBitmap(%buttonFilename);
        /// </code>
        /// <see cref="GuiControl" />
        /// <see cref="GuiButtonCtrl" />
        public void SetBitmap(string buttonFilename) {
             InternalUnsafeMethods.SetBitmap__Args _args = new InternalUnsafeMethods.SetBitmap__Args() {
                buttonFilename = buttonFilename,
             };
             InternalUnsafeMethods.SetBitmap()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the GuiIconButtonCtrl class.
        /// </description>
        /// <returns>The type info object for GuiIconButtonCtrl</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Margin area around the button.
        /// </description>
        /// </value>
        public Point2I ButtonMargin {
            get => GenericMarshal.StringTo<Point2I>(GetFieldValue("buttonMargin"));
            set => SetFieldValue("buttonMargin", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Bitmap file for the icon to display on the button.
        /// </description>
        /// </value>
        public string IconBitmap {
            get => GenericMarshal.StringTo<string>(GetFieldValue("iconBitmap"));
            set => SetFieldValue("iconBitmap", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Where to place the icon on the control. Options are 0 (None), 1 (Left), 2 (Right), 3 (Center).
        /// </description>
        /// </value>
        public GuiIconButtonIconLocation IconLocation {
            get => GenericMarshal.StringTo<GuiIconButtonIconLocation>(GetFieldValue("iconLocation"));
            set => SetFieldValue("iconLocation", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// If true, the icon will be scaled to be the same size as the button.
        /// </description>
        /// </value>
        public bool SizeIconToButton {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("sizeIconToButton"));
            set => SetFieldValue("sizeIconToButton", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// If true, will make sure the icon is square.
        /// </description>
        /// </value>
        public bool MakeIconSquare {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("makeIconSquare"));
            set => SetFieldValue("makeIconSquare", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Where to place the text on the control.
        /// Options are 0 (None), 1 (Bottom), 2 (Right), 3 (Top), 4 (Left), 5 (Center).
        /// </description>
        /// </value>
        public GuiIconButtonTextLocation TextLocation {
            get => GenericMarshal.StringTo<GuiIconButtonTextLocation>(GetFieldValue("textLocation"));
            set => SetFieldValue("textLocation", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Margin between the icon and the text.
        /// </description>
        /// </value>
        public int TextMargin {
            get => GenericMarshal.StringTo<int>(GetFieldValue("textMargin"));
            set => SetFieldValue("textMargin", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// If true, the text and icon will be automatically sized to the size of the control.
        /// </description>
        /// </value>
        public bool AutoSize {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("autoSize"));
            set => SetFieldValue("autoSize", GenericMarshal.ToString(value));
        }
    }
}