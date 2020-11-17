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
    /// <summary>Used to overlaps a 'hot region' where you want to catch inputs with and have specific events occur based on individual callbacks.</summary>
    /// <description>
    /// Mouse event callbacks supported by this control are: onMouseUp, onMouseDown, onMouseMove, onMouseDragged, onMouseEnter, onMouseLeave,
    /// onRightMouseDown, onRightMouseUp and onRightMouseDragged.
    /// </description>
    /// <code>
    /// new GuiMouseEventCtrl()
    /// {
    /// 	lockMouse = "0";
    /// 	//Properties not specific to this control have been omitted from this example.
    /// };
    /// </code>
    /// <see cref="GuiControl" />
    public unsafe class GuiMouseEventCtrl : GuiControl {
        public GuiMouseEventCtrl(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public GuiMouseEventCtrl(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public GuiMouseEventCtrl(string pName) 
            : this(pName, false) {
        }
        
        public GuiMouseEventCtrl(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public GuiMouseEventCtrl(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public GuiMouseEventCtrl(SimObject pObj) 
            : base(pObj) {
        }
        
        public GuiMouseEventCtrl(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct OnRightMouseDragged__Args
            {
                internal int modifier;
                internal IntPtr mousePoint;
                internal int mouseClickCount;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnRightMouseDragged(IntPtr _this, OnRightMouseDragged__Args args);
            private static _OnRightMouseDragged _OnRightMouseDraggedFunc;
            internal static _OnRightMouseDragged OnRightMouseDragged() {
                if (_OnRightMouseDraggedFunc == null) {
                    _OnRightMouseDraggedFunc =
                        (_OnRightMouseDragged)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbGuiMouseEventCtrl_onRightMouseDragged"), typeof(_OnRightMouseDragged));
                }
                
                return _OnRightMouseDraggedFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnRightMouseUp__Args
            {
                internal int modifier;
                internal IntPtr mousePoint;
                internal int mouseClickCount;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnRightMouseUp(IntPtr _this, OnRightMouseUp__Args args);
            private static _OnRightMouseUp _OnRightMouseUpFunc;
            internal static _OnRightMouseUp OnRightMouseUp() {
                if (_OnRightMouseUpFunc == null) {
                    _OnRightMouseUpFunc =
                        (_OnRightMouseUp)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbGuiMouseEventCtrl_onRightMouseUp"), typeof(_OnRightMouseUp));
                }
                
                return _OnRightMouseUpFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnRightMouseDown__Args
            {
                internal int modifier;
                internal IntPtr mousePoint;
                internal int mouseClickCount;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnRightMouseDown(IntPtr _this, OnRightMouseDown__Args args);
            private static _OnRightMouseDown _OnRightMouseDownFunc;
            internal static _OnRightMouseDown OnRightMouseDown() {
                if (_OnRightMouseDownFunc == null) {
                    _OnRightMouseDownFunc =
                        (_OnRightMouseDown)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbGuiMouseEventCtrl_onRightMouseDown"), typeof(_OnRightMouseDown));
                }
                
                return _OnRightMouseDownFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnMouseLeave__Args
            {
                internal int modifier;
                internal IntPtr mousePoint;
                internal int mouseClickCount;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnMouseLeave(IntPtr _this, OnMouseLeave__Args args);
            private static _OnMouseLeave _OnMouseLeaveFunc;
            internal static _OnMouseLeave OnMouseLeave() {
                if (_OnMouseLeaveFunc == null) {
                    _OnMouseLeaveFunc =
                        (_OnMouseLeave)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbGuiMouseEventCtrl_onMouseLeave"), typeof(_OnMouseLeave));
                }
                
                return _OnMouseLeaveFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnMouseEnter__Args
            {
                internal int modifier;
                internal IntPtr mousePoint;
                internal int mouseClickCount;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnMouseEnter(IntPtr _this, OnMouseEnter__Args args);
            private static _OnMouseEnter _OnMouseEnterFunc;
            internal static _OnMouseEnter OnMouseEnter() {
                if (_OnMouseEnterFunc == null) {
                    _OnMouseEnterFunc =
                        (_OnMouseEnter)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbGuiMouseEventCtrl_onMouseEnter"), typeof(_OnMouseEnter));
                }
                
                return _OnMouseEnterFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnMouseDragged__Args
            {
                internal int modifier;
                internal IntPtr mousePoint;
                internal int mouseClickCount;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnMouseDragged(IntPtr _this, OnMouseDragged__Args args);
            private static _OnMouseDragged _OnMouseDraggedFunc;
            internal static _OnMouseDragged OnMouseDragged() {
                if (_OnMouseDraggedFunc == null) {
                    _OnMouseDraggedFunc =
                        (_OnMouseDragged)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbGuiMouseEventCtrl_onMouseDragged"), typeof(_OnMouseDragged));
                }
                
                return _OnMouseDraggedFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnMouseMove__Args
            {
                internal int modifier;
                internal IntPtr mousePoint;
                internal int mouseClickCount;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnMouseMove(IntPtr _this, OnMouseMove__Args args);
            private static _OnMouseMove _OnMouseMoveFunc;
            internal static _OnMouseMove OnMouseMove() {
                if (_OnMouseMoveFunc == null) {
                    _OnMouseMoveFunc =
                        (_OnMouseMove)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbGuiMouseEventCtrl_onMouseMove"), typeof(_OnMouseMove));
                }
                
                return _OnMouseMoveFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnMouseUp__Args
            {
                internal int modifier;
                internal IntPtr mousePoint;
                internal int mouseClickCount;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnMouseUp(IntPtr _this, OnMouseUp__Args args);
            private static _OnMouseUp _OnMouseUpFunc;
            internal static _OnMouseUp OnMouseUp() {
                if (_OnMouseUpFunc == null) {
                    _OnMouseUpFunc =
                        (_OnMouseUp)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbGuiMouseEventCtrl_onMouseUp"), typeof(_OnMouseUp));
                }
                
                return _OnMouseUpFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnMouseDown__Args
            {
                internal int modifier;
                internal IntPtr mousePoint;
                internal int mouseClickCount;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnMouseDown(IntPtr _this, OnMouseDown__Args args);
            private static _OnMouseDown _OnMouseDownFunc;
            internal static _OnMouseDown OnMouseDown() {
                if (_OnMouseDownFunc == null) {
                    _OnMouseDownFunc =
                        (_OnMouseDown)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbGuiMouseEventCtrl_onMouseDown"), typeof(_OnMouseDown));
                }
                
                return _OnMouseDownFunc;
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
                                "fnGuiMouseEventCtrl_staticGetType"), typeof(_StaticGetType));
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
                                "fnGuiMouseEventCtrl_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <summary>Callback that occurs whenever the mouse is dragged in this control while the right mouse button is pressed.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="modifier">Key that was pressed during this callback. Values are:
        /// 
        /// $EventModifier::RSHIFT
        /// 
        /// $EventModifier::SHIFT
        /// 
        /// $EventModifier::LCTRL
        /// 
        /// $EventModifier::RCTRL
        /// 
        /// $EventModifier::CTRL
        /// 
        /// $EventModifier::CTRL
        /// 
        /// $EventModifier::RALT
        /// 
        /// $EventModifier::ALT</param>
        /// <param name="mousePoint">X/Y location of the mouse point</param>
        /// <param name="mouseClickCount">How many mouse clicks have occured for this event</param>
        /// <code>
        /// // Right mouse button was dragged in this control, causing the callback
        /// GuiMouseEventCtrl::onRightMouseDragged(%this,%modifier,%mousePoint,%mouseClickCount)
        /// {
        /// 	// Code to call when a mouse event occurs.
        /// }
        /// </code>
        /// <see cref="GuiControl" />
        public virtual void OnRightMouseDragged(int modifier, Point2I mousePoint, int mouseClickCount) {
mousePoint.Alloc();             InternalUnsafeMethods.OnRightMouseDragged__Args _args = new InternalUnsafeMethods.OnRightMouseDragged__Args() {
                modifier = modifier,
                mousePoint = mousePoint.internalStructPtr,
                mouseClickCount = mouseClickCount,
             };
             InternalUnsafeMethods.OnRightMouseDragged()(ObjectPtr, _args);
mousePoint.Free();        }

        /// <summary>Callback that occurs whenever the right mouse button is released while in this control.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="modifier">Key that was pressed during this callback. Values are:
        /// 
        /// $EventModifier::RSHIFT
        /// 
        /// $EventModifier::SHIFT
        /// 
        /// $EventModifier::LCTRL
        /// 
        /// $EventModifier::RCTRL
        /// 
        /// $EventModifier::CTRL
        /// 
        /// $EventModifier::CTRL
        /// 
        /// $EventModifier::RALT
        /// 
        /// $EventModifier::ALT</param>
        /// <param name="mousePoint">X/Y location of the mouse point</param>
        /// <param name="mouseClickCount">How many mouse clicks have occured for this event</param>
        /// <code>
        /// // Right mouse button was released in this control, causing the callback
        /// GuiMouseEventCtrl::onRightMouseUp(%this,%modifier,%mousePoint,%mouseClickCount)
        /// {
        /// 	// Code to call when a mouse event occurs.
        /// }
        /// </code>
        /// <see cref="GuiControl" />
        public virtual void OnRightMouseUp(int modifier, Point2I mousePoint, int mouseClickCount) {
mousePoint.Alloc();             InternalUnsafeMethods.OnRightMouseUp__Args _args = new InternalUnsafeMethods.OnRightMouseUp__Args() {
                modifier = modifier,
                mousePoint = mousePoint.internalStructPtr,
                mouseClickCount = mouseClickCount,
             };
             InternalUnsafeMethods.OnRightMouseUp()(ObjectPtr, _args);
mousePoint.Free();        }

        /// <summary>Callback that occurs whenever the right mouse button is pressed while in this control.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="modifier">Key that was pressed during this callback. Values are:
        /// 
        /// $EventModifier::RSHIFT
        /// 
        /// $EventModifier::SHIFT
        /// 
        /// $EventModifier::LCTRL
        /// 
        /// $EventModifier::RCTRL
        /// 
        /// $EventModifier::CTRL
        /// 
        /// $EventModifier::CTRL
        /// 
        /// $EventModifier::RALT
        /// 
        /// $EventModifier::ALT</param>
        /// <param name="mousePoint">X/Y location of the mouse point</param>
        /// <param name="mouseClickCount">How many mouse clicks have occured for this event</param>
        /// <code>
        /// // Right mouse button was pressed in this control, causing the callback
        /// GuiMouseEventCtrl::onRightMouseDown(%this,%modifier,%mousePoint,%mouseClickCount)
        /// {
        /// 	// Code to call when a mouse event occurs.
        /// }
        /// </code>
        /// <see cref="GuiControl" />
        public virtual void OnRightMouseDown(int modifier, Point2I mousePoint, int mouseClickCount) {
mousePoint.Alloc();             InternalUnsafeMethods.OnRightMouseDown__Args _args = new InternalUnsafeMethods.OnRightMouseDown__Args() {
                modifier = modifier,
                mousePoint = mousePoint.internalStructPtr,
                mouseClickCount = mouseClickCount,
             };
             InternalUnsafeMethods.OnRightMouseDown()(ObjectPtr, _args);
mousePoint.Free();        }

        /// <summary>Callback that occurs whenever the mouse leaves this control.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="modifier">Key that was pressed during this callback. Values are:
        /// 
        /// $EventModifier::RSHIFT
        /// 
        /// $EventModifier::SHIFT
        /// 
        /// $EventModifier::LCTRL
        /// 
        /// $EventModifier::RCTRL
        /// 
        /// $EventModifier::CTRL
        /// 
        /// $EventModifier::CTRL
        /// 
        /// $EventModifier::RALT
        /// 
        /// $EventModifier::ALT</param>
        /// <param name="mousePoint">X/Y location of the mouse point</param>
        /// <param name="mouseClickCount">How many mouse clicks have occured for this event</param>
        /// <code>
        /// // Mouse left this control, causing the callback
        /// GuiMouseEventCtrl::onMouseLeave(%this,%modifier,%mousePoint,%mouseClickCount)
        /// {
        /// 	// Code to call when a mouse event occurs.
        /// }
        /// </code>
        /// <see cref="GuiControl" />
        public virtual void OnMouseLeave(int modifier, Point2I mousePoint, int mouseClickCount) {
mousePoint.Alloc();             InternalUnsafeMethods.OnMouseLeave__Args _args = new InternalUnsafeMethods.OnMouseLeave__Args() {
                modifier = modifier,
                mousePoint = mousePoint.internalStructPtr,
                mouseClickCount = mouseClickCount,
             };
             InternalUnsafeMethods.OnMouseLeave()(ObjectPtr, _args);
mousePoint.Free();        }

        /// <summary>Callback that occurs whenever the mouse enters this control.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="modifier">Key that was pressed during this callback. Values are:
        /// 
        /// $EventModifier::RSHIFT
        /// 
        /// $EventModifier::SHIFT
        /// 
        /// $EventModifier::LCTRL
        /// 
        /// $EventModifier::RCTRL
        /// 
        /// $EventModifier::CTRL
        /// 
        /// $EventModifier::CTRL
        /// 
        /// $EventModifier::RALT
        /// 
        /// $EventModifier::ALT</param>
        /// <param name="mousePoint">X/Y location of the mouse point</param>
        /// <param name="mouseClickCount">How many mouse clicks have occured for this event</param>
        /// <code>
        /// // Mouse entered this control, causing the callback
        /// GuiMouseEventCtrl::onMouseEnter(%this,%modifier,%mousePoint,%mouseClickCount)
        /// {
        /// 	// Code to call when a mouse event occurs.
        /// }
        /// </code>
        /// <see cref="GuiControl" />
        public virtual void OnMouseEnter(int modifier, Point2I mousePoint, int mouseClickCount) {
mousePoint.Alloc();             InternalUnsafeMethods.OnMouseEnter__Args _args = new InternalUnsafeMethods.OnMouseEnter__Args() {
                modifier = modifier,
                mousePoint = mousePoint.internalStructPtr,
                mouseClickCount = mouseClickCount,
             };
             InternalUnsafeMethods.OnMouseEnter()(ObjectPtr, _args);
mousePoint.Free();        }

        /// <summary>Callback that occurs whenever the mouse is dragged while in this control.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="modifier">Key that was pressed during this callback. Values are:
        /// 
        /// $EventModifier::RSHIFT
        /// 
        /// $EventModifier::SHIFT
        /// 
        /// $EventModifier::LCTRL
        /// 
        /// $EventModifier::RCTRL
        /// 
        /// $EventModifier::CTRL
        /// 
        /// $EventModifier::CTRL
        /// 
        /// $EventModifier::RALT
        /// 
        /// $EventModifier::ALT</param>
        /// <param name="mousePoint">X/Y location of the mouse point</param>
        /// <param name="mouseClickCount">How many mouse clicks have occured for this event</param>
        /// <code>
        /// // Mouse was dragged in this control, causing the callback
        /// GuiMouseEventCtrl::onMouseDragged(%this,%modifier,%mousePoint,%mouseClickCount)
        /// {
        /// 	// Code to call when a mouse event occurs.
        /// }
        /// </code>
        /// <see cref="GuiControl" />
        public virtual void OnMouseDragged(int modifier, Point2I mousePoint, int mouseClickCount) {
mousePoint.Alloc();             InternalUnsafeMethods.OnMouseDragged__Args _args = new InternalUnsafeMethods.OnMouseDragged__Args() {
                modifier = modifier,
                mousePoint = mousePoint.internalStructPtr,
                mouseClickCount = mouseClickCount,
             };
             InternalUnsafeMethods.OnMouseDragged()(ObjectPtr, _args);
mousePoint.Free();        }

        /// <summary>Callback that occurs whenever the mouse is moved (without dragging) while in this control.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="modifier">Key that was pressed during this callback. Values are:
        /// 
        /// $EventModifier::RSHIFT
        /// 
        /// $EventModifier::SHIFT
        /// 
        /// $EventModifier::LCTRL
        /// 
        /// $EventModifier::RCTRL
        /// 
        /// $EventModifier::CTRL
        /// 
        /// $EventModifier::CTRL
        /// 
        /// $EventModifier::RALT
        /// 
        /// $EventModifier::ALT</param>
        /// <param name="mousePoint">X/Y location of the mouse point</param>
        /// <param name="mouseClickCount">How many mouse clicks have occured for this event</param>
        /// <code>
        /// // Mouse was moved in this control, causing the callback
        /// GuiMouseEventCtrl::onMouseMove(%this,%modifier,%mousePoint,%mouseClickCount)
        /// {
        /// 	// Code to call when a mouse event occurs.
        /// }
        /// </code>
        /// <see cref="GuiControl" />
        public virtual void OnMouseMove(int modifier, Point2I mousePoint, int mouseClickCount) {
mousePoint.Alloc();             InternalUnsafeMethods.OnMouseMove__Args _args = new InternalUnsafeMethods.OnMouseMove__Args() {
                modifier = modifier,
                mousePoint = mousePoint.internalStructPtr,
                mouseClickCount = mouseClickCount,
             };
             InternalUnsafeMethods.OnMouseMove()(ObjectPtr, _args);
mousePoint.Free();        }

        /// <summary>Callback that occurs whenever the mouse is released while in this control.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="modifier">Key that was pressed during this callback. Values are:
        /// 
        /// $EventModifier::RSHIFT
        /// 
        /// $EventModifier::SHIFT
        /// 
        /// $EventModifier::LCTRL
        /// 
        /// $EventModifier::RCTRL
        /// 
        /// $EventModifier::CTRL
        /// 
        /// $EventModifier::CTRL
        /// 
        /// $EventModifier::RALT
        /// 
        /// $EventModifier::ALT</param>
        /// <param name="mousePoint">X/Y location of the mouse point</param>
        /// <param name="mouseClickCount">How many mouse clicks have occured for this event</param>
        /// <code>
        /// // Mouse was released in this control, causing the callback
        /// GuiMouseEventCtrl::onMouseUp(%this,%modifier,%mousePoint,%mouseClickCount)
        /// {
        /// 	// Code to call when a mouse event occurs.
        /// }
        /// </code>
        /// <see cref="GuiControl" />
        public virtual void OnMouseUp(int modifier, Point2I mousePoint, int mouseClickCount) {
mousePoint.Alloc();             InternalUnsafeMethods.OnMouseUp__Args _args = new InternalUnsafeMethods.OnMouseUp__Args() {
                modifier = modifier,
                mousePoint = mousePoint.internalStructPtr,
                mouseClickCount = mouseClickCount,
             };
             InternalUnsafeMethods.OnMouseUp()(ObjectPtr, _args);
mousePoint.Free();        }

        /// <summary>Callback that occurs whenever the mouse is pressed down while in this control.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="modifier">Key that was pressed during this callback. Values are:
        /// 
        /// $EventModifier::RSHIFT
        /// 
        /// $EventModifier::SHIFT
        /// 
        /// $EventModifier::LCTRL
        /// 
        /// $EventModifier::RCTRL
        /// 
        /// $EventModifier::CTRL
        /// 
        /// $EventModifier::CTRL
        /// 
        /// $EventModifier::RALT
        /// 
        /// $EventModifier::ALT</param>
        /// <param name="mousePoint">X/Y location of the mouse point</param>
        /// <param name="mouseClickCount">How many mouse clicks have occured for this event</param>
        /// <code>
        /// // Mouse was pressed down in this control, causing the callback
        /// GuiMouseEventCtrl::onMouseDown(%this,%modifier,%mousePoint,%mouseClickCount)
        /// {
        /// 	// Code to call when a mouse event occurs.
        /// }
        /// </code>
        /// <see cref="GuiControl" />
        public virtual void OnMouseDown(int modifier, Point2I mousePoint, int mouseClickCount) {
mousePoint.Alloc();             InternalUnsafeMethods.OnMouseDown__Args _args = new InternalUnsafeMethods.OnMouseDown__Args() {
                modifier = modifier,
                mousePoint = mousePoint.internalStructPtr,
                mouseClickCount = mouseClickCount,
             };
             InternalUnsafeMethods.OnMouseDown()(ObjectPtr, _args);
mousePoint.Free();        }

        /// <description>
        /// Get the type info object for the GuiMouseEventCtrl class.
        /// </description>
        /// <returns>The type info object for GuiMouseEventCtrl</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Whether the control should lock the mouse between up and down button events.
        /// </description>
        /// </value>
        public bool LockMouse {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("lockMouse"));
            set => SetFieldValue("lockMouse", GenericMarshal.ToString(value));
        }
    }
}