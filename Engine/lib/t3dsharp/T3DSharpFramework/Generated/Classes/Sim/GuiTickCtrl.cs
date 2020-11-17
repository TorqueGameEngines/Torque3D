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
    /// <summary>Brief Description.</summary>
    /// <description>
    /// This Gui Control is designed to be subclassed to let people create controls which want to receive update ticks at a constant interval. This class was created to be the Parent class of a control which used a DynamicTexture along with a VectorField to create warping effects much like the ones found in visualization displays for iTunes or Winamp. Those displays are updated at the framerate frequency. This works fine for those effects, however for an application of the same type of effects for things like Gui transitions the framerate-driven update frequency is not desirable because it does not allow the developer to be able to have any idea of a consistent user-experience.
    /// 
    /// Enter the ITickable interface. This lets the Gui control, in this case, update the dynamic texture at a constant rate of once per tick, even though it gets rendered every frame, thus creating a framerate-independent update frequency so that the effects are at a consistent speed regardless of the specifics of the system the user is on. This means that the screen-transitions will occur in the same time on a machine getting 300fps in the Gui shell as a machine which gets 150fps in the Gui shell.
    /// </description>
    public unsafe class GuiTickCtrl : GuiControl {
        public GuiTickCtrl(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public GuiTickCtrl(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public GuiTickCtrl(string pName) 
            : this(pName, false) {
        }
        
        public GuiTickCtrl(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public GuiTickCtrl(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public GuiTickCtrl(SimObject pObj) 
            : base(pObj) {
        }
        
        public GuiTickCtrl(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct SetProcessTicks__Args
            {
                [MarshalAs(UnmanagedType.I1)]
                internal bool tick;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetProcessTicks(IntPtr _this, SetProcessTicks__Args args);
            private static _SetProcessTicks _SetProcessTicksFunc;
            internal static _SetProcessTicks SetProcessTicks() {
                if (_SetProcessTicksFunc == null) {
                    _SetProcessTicksFunc =
                        (_SetProcessTicks)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiTickCtrl_setProcessTicks"), typeof(_SetProcessTicks));
                }
                
                return _SetProcessTicksFunc;
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
                                "fnGuiTickCtrl_staticGetType"), typeof(_StaticGetType));
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
                                "fnGuiTickCtrl_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// ( [tick = true] ) - This will set this object to either be processing ticks or not
        /// </description>
        public void SetProcessTicks(bool tick = true) {
             InternalUnsafeMethods.SetProcessTicks__Args _args = new InternalUnsafeMethods.SetProcessTicks__Args() {
                tick = tick,
             };
             InternalUnsafeMethods.SetProcessTicks()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the GuiTickCtrl class.
        /// </description>
        /// <returns>The type info object for GuiTickCtrl</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }
    }
}