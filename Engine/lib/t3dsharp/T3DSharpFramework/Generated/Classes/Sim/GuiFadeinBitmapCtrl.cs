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
    /// <summary>A GUI control which renders a black square over a bitmap image. The black square will fade out, then fade back in after a determined time.</summary>
    /// <description>
    /// This control is especially useful for transitions and splash screens.
    /// </description>
    /// <code>
    /// new GuiFadeinBitmapCtrl()
    /// 	{
    /// 		fadeinTime = "1000";
    /// 		waitTime = "2000";
    /// 		fadeoutTime = "1000";
    /// 		done = "1";
    /// 		// Additional GUI properties that are not specific to GuiFadeinBitmapCtrl have been omitted from this example.
    /// 	};
    /// </code>
    /// <see cref="GuiBitmapCtrl" />
    public unsafe class GuiFadeinBitmapCtrl : GuiBitmapCtrl {
        public GuiFadeinBitmapCtrl(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public GuiFadeinBitmapCtrl(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public GuiFadeinBitmapCtrl(string pName) 
            : this(pName, false) {
        }
        
        public GuiFadeinBitmapCtrl(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public GuiFadeinBitmapCtrl(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public GuiFadeinBitmapCtrl(SimObject pObj) 
            : base(pObj) {
        }
        
        public GuiFadeinBitmapCtrl(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct OnDone__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnDone(IntPtr _this, OnDone__Args args);
            private static _OnDone _OnDoneFunc;
            internal static _OnDone OnDone() {
                if (_OnDoneFunc == null) {
                    _OnDoneFunc =
                        (_OnDone)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbGuiFadeinBitmapCtrl_onDone"), typeof(_OnDone));
                }
                
                return _OnDoneFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Click__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Click(IntPtr _this, Click__Args args);
            private static _Click _ClickFunc;
            internal static _Click Click() {
                if (_ClickFunc == null) {
                    _ClickFunc =
                        (_Click)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbGuiFadeinBitmapCtrl_click"), typeof(_Click));
                }
                
                return _ClickFunc;
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
                                "fnGuiFadeinBitmapCtrl_staticGetType"), typeof(_StaticGetType));
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
                                "fnGuiFadeinBitmapCtrl_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <summary>Informs the script level that this object has completed is fade cycle.</summary>
        /// <description>
        /// 
        /// </description>
        /// <code>
        /// GuiFadeInBitmapCtrl::onDone(%this)
        /// 	{
        /// 		// Code to run when the fade cycle completes
        /// 	}
        /// </code>
        /// <see cref="GuiCore" />
        public virtual void OnDone() {
             InternalUnsafeMethods.OnDone__Args _args = new InternalUnsafeMethods.OnDone__Args() {
             };
             InternalUnsafeMethods.OnDone()(ObjectPtr, _args);
        }

        /// <summary>Informs the script level that this object received a Click event from the cursor or keyboard.</summary>
        /// <description>
        /// 
        /// </description>
        /// <code>
        /// GuiFadeInBitmapCtrl::click(%this)
        /// 	{
        /// 		// Code to run when click occurs
        /// 	}
        /// </code>
        /// <see cref="GuiCore" />
        public virtual void Click() {
             InternalUnsafeMethods.Click__Args _args = new InternalUnsafeMethods.Click__Args() {
             };
             InternalUnsafeMethods.Click()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the GuiFadeinBitmapCtrl class.
        /// </description>
        /// <returns>The type info object for GuiFadeinBitmapCtrl</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Color to fade in from and fade out to.
        /// </description>
        /// </value>
        public LinearColorF FadeColor {
            get => GenericMarshal.StringTo<LinearColorF>(GetFieldValue("fadeColor"));
            set => SetFieldValue("fadeColor", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Milliseconds for the bitmap to fade in.
        /// </description>
        /// </value>
        public int FadeInTime {
            get => GenericMarshal.StringTo<int>(GetFieldValue("fadeInTime"));
            set => SetFieldValue("fadeInTime", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Milliseconds to wait after fading in before fading out the bitmap.
        /// </description>
        /// </value>
        public int WaitTime {
            get => GenericMarshal.StringTo<int>(GetFieldValue("waitTime"));
            set => SetFieldValue("waitTime", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Milliseconds for the bitmap to fade out.
        /// </description>
        /// </value>
        public int FadeOutTime {
            get => GenericMarshal.StringTo<int>(GetFieldValue("fadeOutTime"));
            set => SetFieldValue("fadeOutTime", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Easing curve for fade-in.
        /// </description>
        /// </value>
        public EaseF FadeInEase {
            get => GenericMarshal.StringTo<EaseF>(GetFieldValue("fadeInEase"));
            set => SetFieldValue("fadeInEase", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Easing curve for fade-out.
        /// </description>
        /// </value>
        public EaseF FadeOutEase {
            get => GenericMarshal.StringTo<EaseF>(GetFieldValue("fadeOutEase"));
            set => SetFieldValue("fadeOutEase", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Whether the fade cycle has finished running.
        /// </description>
        /// </value>
        public bool Done {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("done"));
            set => SetFieldValue("done", GenericMarshal.ToString(value));
        }
    }
}