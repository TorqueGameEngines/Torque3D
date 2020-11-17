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
    /// <summary>GUI Control which displays a horizontal bar with individual drop-down menu items. Each menu item may also have submenu items.</summary>
    /// <description>
    /// 
    /// </description>
    /// <code>
    /// new GuiMenuBar(newMenuBar)
    /// {
    ///   Padding = "0";
    ///   //Properties not specific to this control have been omitted from this example.
    /// };
    /// 
    /// // Add a menu to the menu bar
    /// newMenuBar.addMenu(0,"New Menu");
    /// 
    /// // Add a menu item to the New Menu
    /// newMenuBar.addMenuItem(0,"New Menu Item",0,"n",-1);
    /// 
    /// // Add a submenu item to the New Menu Item
    /// newMenuBar.addSubmenuItem(0,1,"New Submenu Item",0,"s",-1);
    /// </code>
    /// <see cref="GuiTickCtrl" />
    public unsafe class GuiMenuBar : GuiTickCtrl {
        public GuiMenuBar(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public GuiMenuBar(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public GuiMenuBar(string pName) 
            : this(pName, false) {
        }
        
        public GuiMenuBar(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public GuiMenuBar(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public GuiMenuBar(SimObject pObj) 
            : base(pObj) {
        }
        
        public GuiMenuBar(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct FindMenu__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string barTitle;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _FindMenu(IntPtr _this, FindMenu__Args args);
            private static _FindMenu _FindMenuFunc;
            internal static _FindMenu FindMenu() {
                if (_FindMenuFunc == null) {
                    _FindMenuFunc =
                        (_FindMenu)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiMenuBar_findMenu"), typeof(_FindMenu));
                }
                
                return _FindMenuFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Insert__Args
            {
                internal IntPtr pObject;
                internal int pos;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Insert(IntPtr _this, Insert__Args args);
            private static _Insert _InsertFunc;
            internal static _Insert Insert() {
                if (_InsertFunc == null) {
                    _InsertFunc =
                        (_Insert)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiMenuBar_insert"), typeof(_Insert));
                }
                
                return _InsertFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetMenu__Args
            {
                internal int index;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetMenu(IntPtr _this, GetMenu__Args args);
            private static _GetMenu _GetMenuFunc;
            internal static _GetMenu GetMenu() {
                if (_GetMenuFunc == null) {
                    _GetMenuFunc =
                        (_GetMenu)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiMenuBar_getMenu"), typeof(_GetMenu));
                }
                
                return _GetMenuFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetMenuCount__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetMenuCount(IntPtr _this, GetMenuCount__Args args);
            private static _GetMenuCount _GetMenuCountFunc;
            internal static _GetMenuCount GetMenuCount() {
                if (_GetMenuCountFunc == null) {
                    _GetMenuCountFunc =
                        (_GetMenuCount)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiMenuBar_getMenuCount"), typeof(_GetMenuCount));
                }
                
                return _GetMenuCountFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct RemoveFromCanvas__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _RemoveFromCanvas(IntPtr _this, RemoveFromCanvas__Args args);
            private static _RemoveFromCanvas _RemoveFromCanvasFunc;
            internal static _RemoveFromCanvas RemoveFromCanvas() {
                if (_RemoveFromCanvasFunc == null) {
                    _RemoveFromCanvasFunc =
                        (_RemoveFromCanvas)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiMenuBar_removeFromCanvas"), typeof(_RemoveFromCanvas));
                }
                
                return _RemoveFromCanvasFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct AttachToCanvas__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string canvas;
                internal int pos;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _AttachToCanvas(IntPtr _this, AttachToCanvas__Args args);
            private static _AttachToCanvas _AttachToCanvasFunc;
            internal static _AttachToCanvas AttachToCanvas() {
                if (_AttachToCanvasFunc == null) {
                    _AttachToCanvasFunc =
                        (_AttachToCanvas)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiMenuBar_attachToCanvas"), typeof(_AttachToCanvas));
                }
                
                return _AttachToCanvasFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnMenuItemSelect__Args
            {
                internal int menuId;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string menuText;
                internal int menuItemId;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string menuItemText;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnMenuItemSelect(IntPtr _this, OnMenuItemSelect__Args args);
            private static _OnMenuItemSelect _OnMenuItemSelectFunc;
            internal static _OnMenuItemSelect OnMenuItemSelect() {
                if (_OnMenuItemSelectFunc == null) {
                    _OnMenuItemSelectFunc =
                        (_OnMenuItemSelect)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbGuiMenuBar_onMenuItemSelect"), typeof(_OnMenuItemSelect));
                }
                
                return _OnMenuItemSelectFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnMenuSelect__Args
            {
                internal int menuId;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string menuText;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnMenuSelect(IntPtr _this, OnMenuSelect__Args args);
            private static _OnMenuSelect _OnMenuSelectFunc;
            internal static _OnMenuSelect OnMenuSelect() {
                if (_OnMenuSelectFunc == null) {
                    _OnMenuSelectFunc =
                        (_OnMenuSelect)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbGuiMenuBar_onMenuSelect"), typeof(_OnMenuSelect));
                }
                
                return _OnMenuSelectFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnMouseInMenu__Args
            {
                [MarshalAs(UnmanagedType.I1)]
                internal bool isInMenu;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnMouseInMenu(IntPtr _this, OnMouseInMenu__Args args);
            private static _OnMouseInMenu _OnMouseInMenuFunc;
            internal static _OnMouseInMenu OnMouseInMenu() {
                if (_OnMouseInMenuFunc == null) {
                    _OnMouseInMenuFunc =
                        (_OnMouseInMenu)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbGuiMenuBar_onMouseInMenu"), typeof(_OnMouseInMenu));
                }
                
                return _OnMouseInMenuFunc;
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
                                "fnGuiMenuBar_staticGetType"), typeof(_StaticGetType));
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
                                "fnGuiMenuBar_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// (barTitle)
        /// </description>
        public int FindMenu(string barTitle = "") {
             InternalUnsafeMethods.FindMenu__Args _args = new InternalUnsafeMethods.FindMenu__Args() {
                barTitle = barTitle,
             };
             int _engineResult = InternalUnsafeMethods.FindMenu()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// (object, pos) insert object at position
        /// </description>
        public void Insert(SimObject pObject = null, int pos = -1) {
             InternalUnsafeMethods.Insert__Args _args = new InternalUnsafeMethods.Insert__Args() {
                pObject = pObject.ObjectPtr,
                pos = pos,
             };
             InternalUnsafeMethods.Insert()(ObjectPtr, _args);
        }

        /// <description>
        /// (Index)
        /// </description>
        public int GetMenu(int index = 0) {
             InternalUnsafeMethods.GetMenu__Args _args = new InternalUnsafeMethods.GetMenu__Args() {
                index = index,
             };
             int _engineResult = InternalUnsafeMethods.GetMenu()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// ()
        /// </description>
        public int GetMenuCount() {
             InternalUnsafeMethods.GetMenuCount__Args _args = new InternalUnsafeMethods.GetMenuCount__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetMenuCount()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// ()
        /// </description>
        public void RemoveFromCanvas() {
             InternalUnsafeMethods.RemoveFromCanvas__Args _args = new InternalUnsafeMethods.RemoveFromCanvas__Args() {
             };
             InternalUnsafeMethods.RemoveFromCanvas()(ObjectPtr, _args);
        }

        /// <description>
        /// (GuiCanvas, pos)
        /// </description>
        public void AttachToCanvas(string canvas, int pos) {
             InternalUnsafeMethods.AttachToCanvas__Args _args = new InternalUnsafeMethods.AttachToCanvas__Args() {
                canvas = canvas,
                pos = pos,
             };
             InternalUnsafeMethods.AttachToCanvas()(ObjectPtr, _args);
        }

        /// <summary>Called whenever an item in a menu is selected.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="menuId">Index id of the menu which contains the selected menu item</param>
        /// <param name="menuText">Text of the menu which contains the selected menu item</param>
        /// <param name="menuItemId">Index id of the selected menu item</param>
        /// <param name="menuItemText">Text of the selected menu item</param>
        /// <code>
        /// // A menu item has been selected, causing the callback to occur.
        /// GuiMenuBar::onMenuItemSelect(%this,%menuId,%menuText,%menuItemId,%menuItemText)
        /// {
        ///   // Code to run when the callback occurs
        /// }
        /// </code>
        /// <see cref="GuiTickCtrl" />
        public virtual void OnMenuItemSelect(int menuId, string menuText, int menuItemId, string menuItemText) {
             InternalUnsafeMethods.OnMenuItemSelect__Args _args = new InternalUnsafeMethods.OnMenuItemSelect__Args() {
                menuId = menuId,
                menuText = menuText,
                menuItemId = menuItemId,
                menuItemText = menuItemText,
             };
             InternalUnsafeMethods.OnMenuItemSelect()(ObjectPtr, _args);
        }

        /// <summary>Called whenever a menu is selected.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="menuId">Index id of the clicked menu</param>
        /// <param name="menuText">Text of the clicked menu</param>
        /// <code>
        /// // A menu has been selected, causing the callback to occur.
        /// GuiMenuBar::onMenuSelect(%this,%menuId,%menuText)
        /// {
        ///   // Code to run when the callback occurs
        /// }
        /// </code>
        /// <see cref="GuiTickCtrl" />
        public virtual void OnMenuSelect(int menuId, string menuText) {
             InternalUnsafeMethods.OnMenuSelect__Args _args = new InternalUnsafeMethods.OnMenuSelect__Args() {
                menuId = menuId,
                menuText = menuText,
             };
             InternalUnsafeMethods.OnMenuSelect()(ObjectPtr, _args);
        }

        /// <summary>Called whenever the mouse enters, or persists is in the menu.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="isInMenu">True if the mouse has entered the menu, otherwise is false.</param>
        /// <remarks> To receive this callback, call setProcessTicks(true) on the menu bar.
        /// </remarks>
        /// <code>
        /// // Mouse enters or persists within the menu, causing the callback to occur.
        /// GuiMenuBar::onMouseInMenu(%this,%hasLeftMenu)
        /// {
        ///   // Code to run when the callback occurs
        /// }
        /// </code>
        /// <see cref="GuiTickCtrl" />
        public virtual void OnMouseInMenu(bool isInMenu) {
             InternalUnsafeMethods.OnMouseInMenu__Args _args = new InternalUnsafeMethods.OnMouseInMenu__Args() {
                isInMenu = isInMenu,
             };
             InternalUnsafeMethods.OnMouseInMenu()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the GuiMenuBar class.
        /// </description>
        /// <returns>The type info object for GuiMenuBar</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Extra padding to add to the bounds of the control.
        /// </description>
        /// </value>
        public int Padding {
            get => GenericMarshal.StringTo<int>(GetFieldValue("padding"));
            set => SetFieldValue("padding", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Sets the height of the menubar when attached to the canvas.
        /// </description>
        /// </value>
        public int MenubarHeight {
            get => GenericMarshal.StringTo<int>(GetFieldValue("menubarHeight"));
            set => SetFieldValue("menubarHeight", GenericMarshal.ToString(value));
        }
    }
}