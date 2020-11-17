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
    /// <summary>Basic cross hair hud. Reacts to state of control object. Also displays health bar for named objects under the cross hair.</summary>
    /// <description>
    /// Uses the base bitmap control to render a bitmap, and decides whether to draw or not depending on the current control object and it's state. If there is ShapeBase object under the cross hair and it's named, then a small health bar is displayed.
    /// </description>
    /// <code>
    /// new GuiCrossHairHud(){
    /// 	damageFillColor = "1.0 0.0 0.0 1.0"; // Fills with a solid red color
    /// 	damageFrameColor = "1.0 1.0 1.0 1.0"; // Solid white frame color
    /// 	damageRect = "15 5";
    /// 	damageOffset = "0 -10";
    /// };
    /// </code>
    public unsafe class GuiCrossHairHud : GuiBitmapCtrl {
        public GuiCrossHairHud(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public GuiCrossHairHud(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public GuiCrossHairHud(string pName) 
            : this(pName, false) {
        }
        
        public GuiCrossHairHud(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public GuiCrossHairHud(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public GuiCrossHairHud(SimObject pObj) 
            : base(pObj) {
        }
        
        public GuiCrossHairHud(IntPtr pObj) 
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
                                "fnGuiCrossHairHud_staticGetType"), typeof(_StaticGetType));
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
                                "fnGuiCrossHairHud_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the GuiCrossHairHud class.
        /// </description>
        /// <returns>The type info object for GuiCrossHairHud</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// As the health bar depletes, this color will represent the health loss amount.
        /// </description>
        /// </value>
        public LinearColorF DamageFillColor {
            get => GenericMarshal.StringTo<LinearColorF>(GetFieldValue("damageFillColor"));
            set => SetFieldValue("damageFillColor", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Color for the health bar's frame.
        /// </description>
        /// </value>
        public LinearColorF DamageFrameColor {
            get => GenericMarshal.StringTo<LinearColorF>(GetFieldValue("damageFrameColor"));
            set => SetFieldValue("damageFrameColor", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Size for the health bar portion of the control.
        /// </description>
        /// </value>
        public Point2I DamageRect {
            get => GenericMarshal.StringTo<Point2I>(GetFieldValue("damageRect"));
            set => SetFieldValue("damageRect", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Offset for drawing the damage portion of the health control.
        /// </description>
        /// </value>
        public Point2I DamageOffset {
            get => GenericMarshal.StringTo<Point2I>(GetFieldValue("damageOffset"));
            set => SetFieldValue("damageOffset", GenericMarshal.ToString(value));
        }
    }
}