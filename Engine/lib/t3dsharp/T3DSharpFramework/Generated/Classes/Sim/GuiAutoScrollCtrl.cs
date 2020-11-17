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
    /// <summary>A container that scrolls its child control up over time.</summary>
    /// <description>
    /// This container can be used to scroll a single child control in either of the four directions.
    /// </description>
    /// <code>
    /// // Create a GuiAutoScrollCtrl that scrolls a long text of credits.
    /// new GuiAutoScrollCtrl( CreditsScroller )
    /// {
    ///    position = "0 0";
    ///    extent = Canvas.extent.x SPC Canvas.extent.y;
    /// 
    ///    scrollDirection = "Up"; // Scroll upwards.
    ///    startDelay = 4; // Wait 4 seconds before starting to scroll.
    ///    isLooping = false; // Don't loop the credits.
    ///    scrollOutOfSight = true; // Scroll up fully.
    /// 
    ///    new GuiMLTextCtrl()
    ///    {
    ///       text = $CREDITS;
    ///    };
    /// };
    /// 
    /// function CreditsScroller::onComplete( %this )
    /// {
    ///    // Switch back to main menu after credits have rolled.
    ///    Canvas.setContent( MainMenu );
    /// }
    /// 
    /// // Start rolling credits.
    /// Canvas.setContent( CreditsScroller );
    /// </code>
    /// <remarks> Only the first child will be scrolled.
    /// 
    /// </remarks>
    public unsafe class GuiAutoScrollCtrl : GuiTickCtrl {
        public GuiAutoScrollCtrl(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public GuiAutoScrollCtrl(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public GuiAutoScrollCtrl(string pName) 
            : this(pName, false) {
        }
        
        public GuiAutoScrollCtrl(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public GuiAutoScrollCtrl(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public GuiAutoScrollCtrl(SimObject pObj) 
            : base(pObj) {
        }
        
        public GuiAutoScrollCtrl(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct Reset__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Reset(IntPtr _this, Reset__Args args);
            private static _Reset _ResetFunc;
            internal static _Reset Reset() {
                if (_ResetFunc == null) {
                    _ResetFunc =
                        (_Reset)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiAutoScrollCtrl_reset"), typeof(_Reset));
                }
                
                return _ResetFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnReset__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnReset(IntPtr _this, OnReset__Args args);
            private static _OnReset _OnResetFunc;
            internal static _OnReset OnReset() {
                if (_OnResetFunc == null) {
                    _OnResetFunc =
                        (_OnReset)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbGuiAutoScrollCtrl_onReset"), typeof(_OnReset));
                }
                
                return _OnResetFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnComplete__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnComplete(IntPtr _this, OnComplete__Args args);
            private static _OnComplete _OnCompleteFunc;
            internal static _OnComplete OnComplete() {
                if (_OnCompleteFunc == null) {
                    _OnCompleteFunc =
                        (_OnComplete)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbGuiAutoScrollCtrl_onComplete"), typeof(_OnComplete));
                }
                
                return _OnCompleteFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnStart__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnStart(IntPtr _this, OnStart__Args args);
            private static _OnStart _OnStartFunc;
            internal static _OnStart OnStart() {
                if (_OnStartFunc == null) {
                    _OnStartFunc =
                        (_OnStart)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbGuiAutoScrollCtrl_onStart"), typeof(_OnStart));
                }
                
                return _OnStartFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnTick__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnTick(IntPtr _this, OnTick__Args args);
            private static _OnTick _OnTickFunc;
            internal static _OnTick OnTick() {
                if (_OnTickFunc == null) {
                    _OnTickFunc =
                        (_OnTick)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbGuiAutoScrollCtrl_onTick"), typeof(_OnTick));
                }
                
                return _OnTickFunc;
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
                                "fnGuiAutoScrollCtrl_staticGetType"), typeof(_StaticGetType));
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
                                "fnGuiAutoScrollCtrl_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Reset scrolling.
        /// </description>
        public void Reset() {
             InternalUnsafeMethods.Reset__Args _args = new InternalUnsafeMethods.Reset__Args() {
             };
             InternalUnsafeMethods.Reset()(ObjectPtr, _args);
        }

        /// <description>
        /// Called when the child control is reset to its initial position and the cycle starts again.
        /// </description>
        public virtual void OnReset() {
             InternalUnsafeMethods.OnReset__Args _args = new InternalUnsafeMethods.OnReset__Args() {
             };
             InternalUnsafeMethods.OnReset()(ObjectPtr, _args);
        }

        /// <description>
        /// Called when the child control has been scrolled in entirety.
        /// </description>
        public virtual void OnComplete() {
             InternalUnsafeMethods.OnComplete__Args _args = new InternalUnsafeMethods.OnComplete__Args() {
             };
             InternalUnsafeMethods.OnComplete()(ObjectPtr, _args);
        }

        /// <description>
        /// Called when the control starts to scroll.
        /// </description>
        public virtual void OnStart() {
             InternalUnsafeMethods.OnStart__Args _args = new InternalUnsafeMethods.OnStart__Args() {
             };
             InternalUnsafeMethods.OnStart()(ObjectPtr, _args);
        }

        /// <description>
        /// Called every 32ms on the control.
        /// </description>
        public virtual void OnTick() {
             InternalUnsafeMethods.OnTick__Args _args = new InternalUnsafeMethods.OnTick__Args() {
             };
             InternalUnsafeMethods.OnTick()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the GuiAutoScrollCtrl class.
        /// </description>
        /// <returns>The type info object for GuiAutoScrollCtrl</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Direction in which the child control is moved.
        /// </description>
        /// </value>
        public GuiAutoScrollDirection ScrollDirection {
            get => GenericMarshal.StringTo<GuiAutoScrollDirection>(GetFieldValue("scrollDirection"));
            set => SetFieldValue("scrollDirection", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Seconds to wait before starting to scroll.
        /// </description>
        /// </value>
        public float StartDelay {
            get => GenericMarshal.StringTo<float>(GetFieldValue("startDelay"));
            set => SetFieldValue("startDelay", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Seconds to wait after scrolling completes before resetting and starting over.
        /// </description>
        /// <remarks> Only takes effect if #isLooping is true.</remarks>
        /// </value>
        public float ResetDelay {
            get => GenericMarshal.StringTo<float>(GetFieldValue("resetDelay"));
            set => SetFieldValue("resetDelay", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Padding to put around child control (in pixels).
        /// </description>
        /// </value>
        public int ChildBorder {
            get => GenericMarshal.StringTo<int>(GetFieldValue("childBorder"));
            set => SetFieldValue("childBorder", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Scrolling speed in pixels per second.
        /// </description>
        /// </value>
        public float ScrollSpeed {
            get => GenericMarshal.StringTo<float>(GetFieldValue("scrollSpeed"));
            set => SetFieldValue("scrollSpeed", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// If true, the scrolling will reset to the beginning once completing a cycle.
        /// </description>
        /// </value>
        public bool IsLooping {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("isLooping"));
            set => SetFieldValue("isLooping", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// If true, the child control will be completely scrolled out of sight; otherwise it will only scroll until the other end becomes visible.
        /// </description>
        /// </value>
        public bool ScrollOutOfSight {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("scrollOutOfSight"));
            set => SetFieldValue("scrollOutOfSight", GenericMarshal.ToString(value));
        }
    }
}