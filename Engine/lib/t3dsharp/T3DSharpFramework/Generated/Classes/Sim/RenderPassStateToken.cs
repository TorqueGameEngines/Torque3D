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
    /// <summary>Abstract base class for RenderFormatToken, used to manipulate what goes on in the render manager</summary>
    /// <description>
    /// You cannot actually instantiate RenderPassToken, only its child: RenderFormatToken. RenderFormatToken is an implementation which changes the format of the back buffer and/or the depth buffer.
    /// 
    /// The RenderPassStateBin manager changes the rendering state associated with a token it is declared with. In stock Torque 3D, a single example exists in the way of AL_FormatToken (found in renderManager.cs). In that script file, all the render managers are intialized, and a single RenderFormatToken is used. This implementation basically exists to ensure Advanced Lighting works with MSAA.
    /// </description>
    /// <see cref="RenderFormatToken" />
    /// <see cref="RenderPassStateBin" />
    /// <see cref="game/core/scripts/client/renderManager.cs" />
    public unsafe class RenderPassStateToken : SimObject {
        public RenderPassStateToken(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public RenderPassStateToken(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public RenderPassStateToken(string pName) 
            : this(pName, false) {
        }
        
        public RenderPassStateToken(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public RenderPassStateToken(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public RenderPassStateToken(SimObject pObj) 
            : base(pObj) {
        }
        
        public RenderPassStateToken(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct Toggle__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Toggle(IntPtr _this, Toggle__Args args);
            private static _Toggle _ToggleFunc;
            internal static _Toggle Toggle() {
                if (_ToggleFunc == null) {
                    _ToggleFunc =
                        (_Toggle)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnRenderPassStateToken_toggle"), typeof(_Toggle));
                }
                
                return _ToggleFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Disable__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Disable(IntPtr _this, Disable__Args args);
            private static _Disable _DisableFunc;
            internal static _Disable Disable() {
                if (_DisableFunc == null) {
                    _DisableFunc =
                        (_Disable)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnRenderPassStateToken_disable"), typeof(_Disable));
                }
                
                return _DisableFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Enable__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Enable(IntPtr _this, Enable__Args args);
            private static _Enable _EnableFunc;
            internal static _Enable Enable() {
                if (_EnableFunc == null) {
                    _EnableFunc =
                        (_Enable)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnRenderPassStateToken_enable"), typeof(_Enable));
                }
                
                return _EnableFunc;
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
                                "fnRenderPassStateToken_staticGetType"), typeof(_StaticGetType));
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
                                "fnRenderPassStateToken_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <summary>Toggles the token from enabled to disabled or vice versa.</summary>
        public void Toggle() {
             InternalUnsafeMethods.Toggle__Args _args = new InternalUnsafeMethods.Toggle__Args() {
             };
             InternalUnsafeMethods.Toggle()(ObjectPtr, _args);
        }

        /// <summary>Disables the token.</summary>
        public void Disable() {
             InternalUnsafeMethods.Disable__Args _args = new InternalUnsafeMethods.Disable__Args() {
             };
             InternalUnsafeMethods.Disable()(ObjectPtr, _args);
        }

        /// <summary>Enables the token.</summary>
        public void Enable() {
             InternalUnsafeMethods.Enable__Args _args = new InternalUnsafeMethods.Enable__Args() {
             };
             InternalUnsafeMethods.Enable()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the RenderPassStateToken class.
        /// </description>
        /// <returns>The type info object for RenderPassStateToken</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Enables or disables this token.
        /// </description>
        /// </value>
        public bool Enabled {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("Enabled"));
            set => SetFieldValue("Enabled", GenericMarshal.ToString(value));
        }
    }
}