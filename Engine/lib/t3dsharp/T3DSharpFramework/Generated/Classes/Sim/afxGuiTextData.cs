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
    /// <summary>A datablock that specifies a Gui Text effect.</summary>
    /// <description>
    /// A Gui Text effect, with the help of an existing afxGuiTextHud, can be used to display 2D text effects on the Gui Canvas. Essentially, using Gui Text effects with an afxGuiTextHud is like using the stock GuiShapeNameHud, but with the ability to make additional text elements come and go as effects constrained to the projection of 3D positions onto the 2D screen.
    /// </description>
    public unsafe class afxGuiTextData : GameBaseData {
        public afxGuiTextData(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public afxGuiTextData(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public afxGuiTextData(string pName) 
            : this(pName, false) {
        }
        
        public afxGuiTextData(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public afxGuiTextData(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public afxGuiTextData(SimObject pObj) 
            : base(pObj) {
        }
        
        public afxGuiTextData(IntPtr pObj) 
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
                                "fnafxGuiTextData_staticGetType"), typeof(_StaticGetType));
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
                                "fnafxGuiTextData_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the afxGuiTextData class.
        /// </description>
        /// <returns>The type info object for afxGuiTextData</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// The literal text to display on the afxGuiTextHud. The center of the text will be placed at the projection of the 3D constraint position into 2D screen space.
        /// If the text field is set to the special string, '#shapeName', the shape name of the primary position constraint object will be used. (This is only meaningful if the constraint source is a ShapeBase-derived object.)
        /// </description>
        /// </value>
        public string Text {
            get => GenericMarshal.StringTo<string>(GetFieldValue("text"));
            set => SetFieldValue("text", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// A color value for the text label.
        /// </description>
        /// </value>
        public LinearColorF Color {
            get => GenericMarshal.StringTo<LinearColorF>(GetFieldValue("color"));
            set => SetFieldValue("color", GenericMarshal.ToString(value));
        }
    }
}