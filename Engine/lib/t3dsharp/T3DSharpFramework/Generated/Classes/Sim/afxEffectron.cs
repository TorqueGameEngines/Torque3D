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
    /// <summary>A basic effects choreographer.</summary>
    /// <description>
    /// 
    /// </description>
    public unsafe class afxEffectron : afxChoreographer {
        public afxEffectron(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public afxEffectron(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public afxEffectron(string pName) 
            : this(pName, false) {
        }
        
        public afxEffectron(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public afxEffectron(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public afxEffectron(SimObject pObj) 
            : base(pObj) {
        }
        
        public afxEffectron(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct Activate__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Activate(IntPtr _this, Activate__Args args);
            private static _Activate _ActivateFunc;
            internal static _Activate Activate() {
                if (_ActivateFunc == null) {
                    _ActivateFunc =
                        (_Activate)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnafxEffectron_activate"), typeof(_Activate));
                }
                
                return _ActivateFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Interrupt__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Interrupt(IntPtr _this, Interrupt__Args args);
            private static _Interrupt _InterruptFunc;
            internal static _Interrupt Interrupt() {
                if (_InterruptFunc == null) {
                    _InterruptFunc =
                        (_Interrupt)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnafxEffectron_interrupt"), typeof(_Interrupt));
                }
                
                return _InterruptFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetTimeFactor__Args
            {
                internal float factor;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetTimeFactor(IntPtr _this, SetTimeFactor__Args args);
            private static _SetTimeFactor _SetTimeFactorFunc;
            internal static _SetTimeFactor SetTimeFactor() {
                if (_SetTimeFactorFunc == null) {
                    _SetTimeFactorFunc =
                        (_SetTimeFactor)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnafxEffectron_setTimeFactor"), typeof(_SetTimeFactor));
                }
                
                return _SetTimeFactorFunc;
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
                                "fnafxEffectron_staticGetType"), typeof(_StaticGetType));
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
                                "fnafxEffectron_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Activates an effectron that was started with postponeActivation=true.
        /// </description>
        public void Activate() {
             InternalUnsafeMethods.Activate__Args _args = new InternalUnsafeMethods.Activate__Args() {
             };
             InternalUnsafeMethods.Activate()(ObjectPtr, _args);
        }

        /// <description>
        /// Interrupts and deletes a running effectron.
        /// </description>
        public void Interrupt() {
             InternalUnsafeMethods.Interrupt__Args _args = new InternalUnsafeMethods.Interrupt__Args() {
             };
             InternalUnsafeMethods.Interrupt()(ObjectPtr, _args);
        }

        /// <description>
        /// Sets the time-factor for the effectron.
        /// </description>
        public void SetTimeFactor(float factor) {
             InternalUnsafeMethods.SetTimeFactor__Args _args = new InternalUnsafeMethods.SetTimeFactor__Args() {
                factor = factor,
             };
             InternalUnsafeMethods.SetTimeFactor()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the afxEffectron class.
        /// </description>
        /// <returns>The type info object for afxEffectron</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }
    }
}