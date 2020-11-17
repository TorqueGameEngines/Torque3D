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
    /// <summary>Basic HUD clock. Displays the current simulation time offset from some base.</summary>
    /// <description>
    /// 
    /// </description>
    /// <code>
    /// new GuiClockHud(){
    /// 	fillColor = "0.0 1.0 0.0 1.0"; // Fills with a solid green color
    /// 	frameColor = "1.0 1.0 1.0 1.0"; // Solid white frame color
    /// 	textColor = "1.0 1.0 1.0 1.0"; // Solid white text Color
    /// 	showFill = "true";
    /// 	showFrame = "true";
    /// };
    /// </code>
    public unsafe class GuiClockHud : GuiControl {
        public GuiClockHud(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public GuiClockHud(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public GuiClockHud(string pName) 
            : this(pName, false) {
        }
        
        public GuiClockHud(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public GuiClockHud(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public GuiClockHud(SimObject pObj) 
            : base(pObj) {
        }
        
        public GuiClockHud(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct GetTime__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _GetTime(IntPtr _this, GetTime__Args args);
            private static _GetTime _GetTimeFunc;
            internal static _GetTime GetTime() {
                if (_GetTimeFunc == null) {
                    _GetTimeFunc =
                        (_GetTime)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiClockHud_getTime"), typeof(_GetTime));
                }
                
                return _GetTimeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetReverseTime__Args
            {
                internal float timeInSeconds;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetReverseTime(IntPtr _this, SetReverseTime__Args args);
            private static _SetReverseTime _SetReverseTimeFunc;
            internal static _SetReverseTime SetReverseTime() {
                if (_SetReverseTimeFunc == null) {
                    _SetReverseTimeFunc =
                        (_SetReverseTime)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiClockHud_setReverseTime"), typeof(_SetReverseTime));
                }
                
                return _SetReverseTimeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetTime__Args
            {
                internal float timeInSeconds;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetTime(IntPtr _this, SetTime__Args args);
            private static _SetTime _SetTimeFunc;
            internal static _SetTime SetTime() {
                if (_SetTimeFunc == null) {
                    _SetTimeFunc =
                        (_SetTime)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiClockHud_setTime"), typeof(_SetTime));
                }
                
                return _SetTimeFunc;
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
                                "fnGuiClockHud_staticGetType"), typeof(_StaticGetType));
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
                                "fnGuiClockHud_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Returns the current time, in seconds.
        /// </description>
        /// <returns>timeInseconds Current time, in seconds</returns>
        /// <code>
        /// // Get the current time from the GuiClockHud control
        /// %timeInSeconds = %guiClockHud.getTime();
        /// </code>
        public float GetTime() {
             InternalUnsafeMethods.GetTime__Args _args = new InternalUnsafeMethods.GetTime__Args() {
             };
             float _engineResult = InternalUnsafeMethods.GetTime()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Sets a time for a countdown clock.</summary>
        /// <description>
        /// Setting the time like this will cause the clock to count backwards from the specified time.
        /// </description>
        /// <param name="timeInSeconds">Time to set the clock, in seconds (IE: 00:02 would be 120)</param>
        /// <see cref="setTime" />
        public void SetReverseTime(float timeInSeconds = 60f) {
             InternalUnsafeMethods.SetReverseTime__Args _args = new InternalUnsafeMethods.SetReverseTime__Args() {
                timeInSeconds = timeInSeconds,
             };
             InternalUnsafeMethods.SetReverseTime()(ObjectPtr, _args);
        }

        /// <description>
        /// Sets the current base time for the clock.
        /// </description>
        /// <param name="timeInSeconds">Time to set the clock, in seconds (IE: 00:02 would be 120)</param>
        /// <code>
        /// // Define the time, in seconds
        /// %timeInSeconds = 120;
        /// 
        /// // Change the time on the GuiClockHud control
        /// %guiClockHud.setTime(%timeInSeconds);
        /// </code>
        public void SetTime(float timeInSeconds = 60f) {
             InternalUnsafeMethods.SetTime__Args _args = new InternalUnsafeMethods.SetTime__Args() {
                timeInSeconds = timeInSeconds,
             };
             InternalUnsafeMethods.SetTime()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the GuiClockHud class.
        /// </description>
        /// <returns>The type info object for GuiClockHud</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// If true, draws a background color behind the control.
        /// </description>
        /// </value>
        public bool ShowFill {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("showFill"));
            set => SetFieldValue("showFill", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// If true, draws a frame around the control.
        /// </description>
        /// </value>
        public bool ShowFrame {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("showFrame"));
            set => SetFieldValue("showFrame", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Standard color for the background of the control.
        /// </description>
        /// </value>
        public LinearColorF FillColor {
            get => GenericMarshal.StringTo<LinearColorF>(GetFieldValue("fillColor"));
            set => SetFieldValue("fillColor", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Color for the control's frame.
        /// </description>
        /// </value>
        public LinearColorF FrameColor {
            get => GenericMarshal.StringTo<LinearColorF>(GetFieldValue("frameColor"));
            set => SetFieldValue("frameColor", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Color for the text on this control.
        /// </description>
        /// </value>
        public LinearColorF TextColor {
            get => GenericMarshal.StringTo<LinearColorF>(GetFieldValue("textColor"));
            set => SetFieldValue("textColor", GenericMarshal.ToString(value));
        }
    }
}