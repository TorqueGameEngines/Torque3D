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
    /// <summary>A control which adds several reactions to other GUIs via callbacks.</summary>
    /// <description>
    /// GuiScriptNotifyCtrl does not exist to render anything. When parented or made a child of other controls, you can toggle flags on or off to make use of its specialized callbacks. Normally these callbacks are used as utility functions by the GUI Editor, or other container classes. However, for very fancy GUI work where controls interact with each other constantly, this is a handy utility to make use of.
    /// </description>
    /// <code>
    /// // Common member fields left out for sake of example
    /// new GuiScriptNotifyCtrl()
    /// {
    /// 	onChildAdded = "0";
    /// 	onChildRemoved = "0";
    /// 	onChildResized = "0";
    /// 	onParentResized = "0";
    /// };
    /// </code>
    public unsafe class GuiScriptNotifyCtrl : GuiControl {
        public GuiScriptNotifyCtrl(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public GuiScriptNotifyCtrl(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public GuiScriptNotifyCtrl(string pName) 
            : this(pName, false) {
        }
        
        public GuiScriptNotifyCtrl(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public GuiScriptNotifyCtrl(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public GuiScriptNotifyCtrl(SimObject pObj) 
            : base(pObj) {
        }
        
        public GuiScriptNotifyCtrl(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct OnGainFirstResponder__Args
            {
                internal uint ID;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnGainFirstResponder(IntPtr _this, OnGainFirstResponder__Args args);
            private static _OnGainFirstResponder _OnGainFirstResponderFunc;
            internal static _OnGainFirstResponder OnGainFirstResponder() {
                if (_OnGainFirstResponderFunc == null) {
                    _OnGainFirstResponderFunc =
                        (_OnGainFirstResponder)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbGuiScriptNotifyCtrl_onGainFirstResponder"), typeof(_OnGainFirstResponder));
                }
                
                return _OnGainFirstResponderFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnLoseFirstResponder__Args
            {
                internal uint ID;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnLoseFirstResponder(IntPtr _this, OnLoseFirstResponder__Args args);
            private static _OnLoseFirstResponder _OnLoseFirstResponderFunc;
            internal static _OnLoseFirstResponder OnLoseFirstResponder() {
                if (_OnLoseFirstResponderFunc == null) {
                    _OnLoseFirstResponderFunc =
                        (_OnLoseFirstResponder)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbGuiScriptNotifyCtrl_onLoseFirstResponder"), typeof(_OnLoseFirstResponder));
                }
                
                return _OnLoseFirstResponderFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnParentResized__Args
            {
                internal uint ID;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnParentResized(IntPtr _this, OnParentResized__Args args);
            private static _OnParentResized _OnParentResizedFunc;
            internal static _OnParentResized OnParentResized() {
                if (_OnParentResizedFunc == null) {
                    _OnParentResizedFunc =
                        (_OnParentResized)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbGuiScriptNotifyCtrl_onParentResized"), typeof(_OnParentResized));
                }
                
                return _OnParentResizedFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnChildResized__Args
            {
                internal uint ID;
                internal uint childID;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnChildResized(IntPtr _this, OnChildResized__Args args);
            private static _OnChildResized _OnChildResizedFunc;
            internal static _OnChildResized OnChildResized() {
                if (_OnChildResizedFunc == null) {
                    _OnChildResizedFunc =
                        (_OnChildResized)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbGuiScriptNotifyCtrl_onChildResized"), typeof(_OnChildResized));
                }
                
                return _OnChildResizedFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnChildRemoved__Args
            {
                internal uint ID;
                internal uint childID;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnChildRemoved(IntPtr _this, OnChildRemoved__Args args);
            private static _OnChildRemoved _OnChildRemovedFunc;
            internal static _OnChildRemoved OnChildRemoved() {
                if (_OnChildRemovedFunc == null) {
                    _OnChildRemovedFunc =
                        (_OnChildRemoved)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbGuiScriptNotifyCtrl_onChildRemoved"), typeof(_OnChildRemoved));
                }
                
                return _OnChildRemovedFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnChildAdded__Args
            {
                internal uint ID;
                internal uint childID;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnChildAdded(IntPtr _this, OnChildAdded__Args args);
            private static _OnChildAdded _OnChildAddedFunc;
            internal static _OnChildAdded OnChildAdded() {
                if (_OnChildAddedFunc == null) {
                    _OnChildAddedFunc =
                        (_OnChildAdded)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbGuiScriptNotifyCtrl_onChildAdded"), typeof(_OnChildAdded));
                }
                
                return _OnChildAddedFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnResize__Args
            {
                internal uint ID;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnResize(IntPtr _this, OnResize__Args args);
            private static _OnResize _OnResizeFunc;
            internal static _OnResize OnResize() {
                if (_OnResizeFunc == null) {
                    _OnResizeFunc =
                        (_OnResize)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbGuiScriptNotifyCtrl_onResize"), typeof(_OnResize));
                }
                
                return _OnResizeFunc;
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
                                "fnGuiScriptNotifyCtrl_staticGetType"), typeof(_StaticGetType));
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
                                "fnGuiScriptNotifyCtrl_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Called when this GUI gains focus.
        /// </description>
        /// <param name="ID">Unique object ID assigned when created (%this in script).</param>
        public virtual void OnGainFirstResponder(uint ID) {
             InternalUnsafeMethods.OnGainFirstResponder__Args _args = new InternalUnsafeMethods.OnGainFirstResponder__Args() {
                ID = ID,
             };
             InternalUnsafeMethods.OnGainFirstResponder()(ObjectPtr, _args);
        }

        /// <description>
        /// Called when this GUI loses focus.
        /// </description>
        /// <param name="ID">Unique object ID assigned when created (%this in script).</param>
        public virtual void OnLoseFirstResponder(uint ID) {
             InternalUnsafeMethods.OnLoseFirstResponder__Args _args = new InternalUnsafeMethods.OnLoseFirstResponder__Args() {
                ID = ID,
             };
             InternalUnsafeMethods.OnLoseFirstResponder()(ObjectPtr, _args);
        }

        /// <description>
        /// Called when this GUI's parent is resized.
        /// </description>
        /// <param name="ID">Unique object ID assigned when created (%this in script).</param>
        public virtual void OnParentResized(uint ID) {
             InternalUnsafeMethods.OnParentResized__Args _args = new InternalUnsafeMethods.OnParentResized__Args() {
                ID = ID,
             };
             InternalUnsafeMethods.OnParentResized()(ObjectPtr, _args);
        }

        /// <description>
        /// Called when a child is of this GUI is being resized.
        /// </description>
        /// <param name="ID">Unique object ID assigned when created (%this in script).</param>
        /// <param name="childID">Unique object ID of child being resized.</param>
        public virtual void OnChildResized(uint ID, uint childID) {
             InternalUnsafeMethods.OnChildResized__Args _args = new InternalUnsafeMethods.OnChildResized__Args() {
                ID = ID,
                childID = childID,
             };
             InternalUnsafeMethods.OnChildResized()(ObjectPtr, _args);
        }

        /// <description>
        /// Called when a child is removed from this GUI.
        /// </description>
        /// <param name="ID">Unique object ID assigned when created (%this in script).</param>
        /// <param name="childID">Unique object ID of child being removed.</param>
        public virtual void OnChildRemoved(uint ID, uint childID) {
             InternalUnsafeMethods.OnChildRemoved__Args _args = new InternalUnsafeMethods.OnChildRemoved__Args() {
                ID = ID,
                childID = childID,
             };
             InternalUnsafeMethods.OnChildRemoved()(ObjectPtr, _args);
        }

        /// <description>
        /// Called when a child is added to this GUI.
        /// </description>
        /// <param name="ID">Unique object ID assigned when created (%this in script).</param>
        /// <param name="childID">Unique object ID of child being added.</param>
        public virtual void OnChildAdded(uint ID, uint childID) {
             InternalUnsafeMethods.OnChildAdded__Args _args = new InternalUnsafeMethods.OnChildAdded__Args() {
                ID = ID,
                childID = childID,
             };
             InternalUnsafeMethods.OnChildAdded()(ObjectPtr, _args);
        }

        /// <description>
        /// Called when this GUI is resized.
        /// </description>
        /// <param name="ID">Unique object ID assigned when created (%this in script).</param>
        public virtual void OnResize(uint ID) {
             InternalUnsafeMethods.OnResize__Args _args = new InternalUnsafeMethods.OnResize__Args() {
                ID = ID,
             };
             InternalUnsafeMethods.OnResize()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the GuiScriptNotifyCtrl class.
        /// </description>
        /// <returns>The type info object for GuiScriptNotifyCtrl</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Enables/disables onChildAdded callback
        /// </description>
        /// </value>
        public bool NotifyOnChildAdded {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("notifyOnChildAdded"));
            set => SetFieldValue("notifyOnChildAdded", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Enables/disables onChildRemoved callback
        /// </description>
        /// </value>
        public bool NotifyOnChildRemoved {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("notifyOnChildRemoved"));
            set => SetFieldValue("notifyOnChildRemoved", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Enables/disables onChildResized callback
        /// </description>
        /// </value>
        public bool NotifyOnChildResized {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("notifyOnChildResized"));
            set => SetFieldValue("notifyOnChildResized", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Enables/disables onParentResized callback
        /// </description>
        /// </value>
        public bool NotifyOnParentResized {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("notifyOnParentResized"));
            set => SetFieldValue("notifyOnParentResized", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Enables/disables onResize callback
        /// </description>
        /// </value>
        public bool NotifyOnResize {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("notifyOnResize"));
            set => SetFieldValue("notifyOnResize", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Enables/disables onLoseFirstResponder callback
        /// </description>
        /// </value>
        public bool NotifyOnLoseFirstResponder {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("notifyOnLoseFirstResponder"));
            set => SetFieldValue("notifyOnLoseFirstResponder", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Enables/disables onGainFirstResponder callback
        /// </description>
        /// </value>
        public bool NotifyOnGainFirstResponder {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("notifyOnGainFirstResponder"));
            set => SetFieldValue("notifyOnGainFirstResponder", GenericMarshal.ToString(value));
        }
    }
}