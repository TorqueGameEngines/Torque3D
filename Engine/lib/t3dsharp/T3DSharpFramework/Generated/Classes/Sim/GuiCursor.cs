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
    /// <summary>Acts as a skin for the cursor, where each GuiCursor object can have its own look and click-zone.</summary>
    /// <description>
    /// GuiCursors act as skins for the cursor in the game, where each individual GuiCursor can have its own defined imagemap,
    /// click zone and render offset. This allows a game to easily support a wide range of cursors. The active cursor can de changed
    /// for each Canvas using %canvasObj.setCursor(GuiCursor);.
    /// </description>
    /// <code>
    /// new GuiCursor(DefaultCursor)
    /// {
    /// 	hotSpot = "1 1";
    /// 	renderOffset = "0 0";
    /// 	bitmapName = "~/art/gui/images/defaultCursor";
    /// };
    /// </code>
    /// <see cref="GuiCanvas" />
    public unsafe class GuiCursor : SimObject {
        public GuiCursor(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public GuiCursor(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public GuiCursor(string pName) 
            : this(pName, false) {
        }
        
        public GuiCursor(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public GuiCursor(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public GuiCursor(SimObject pObj) 
            : base(pObj) {
        }
        
        public GuiCursor(IntPtr pObj) 
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
                                "fnGuiCursor_staticGetType"), typeof(_StaticGetType));
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
                                "fnGuiCursor_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the GuiCursor class.
        /// </description>
        /// <returns>The type info object for GuiCursor</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// The location of the cursor's hot spot (which pixel carries the click).
        /// </description>
        /// </value>
        public Point2I HotSpot {
            get => GenericMarshal.StringTo<Point2I>(GetFieldValue("hotSpot"));
            set => SetFieldValue("hotSpot", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Offset of the bitmap, where 0 signifies left edge of the bitmap, 1, the right. Similarly for the Y-component.
        /// </description>
        /// </value>
        public Point2F RenderOffset {
            get => GenericMarshal.StringTo<Point2F>(GetFieldValue("renderOffset"));
            set => SetFieldValue("renderOffset", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// File name of the bitmap for the cursor.
        /// </description>
        /// </value>
        public string BitmapName {
            get => GenericMarshal.StringTo<string>(GetFieldValue("bitmapName"));
            set => SetFieldValue("bitmapName", GenericMarshal.ToString(value));
        }
    }
}