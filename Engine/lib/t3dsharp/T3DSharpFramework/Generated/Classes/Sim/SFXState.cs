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
    /// <summary>A boolean switch used to modify playlist behavior.</summary>
    /// <description>
    /// Sound system states are used to allow playlist controllers to make decisions based on global state.  This is useful, for example, to couple audio playback to gameplay state.  Certain states may, for example, represent different locations that the listener can be in, like underwater, in open space, or indoors.  Other states could represent moods of the current gameplay situation, like, for example, an aggressive mood during combat.
    /// 
    /// By activating and deactivating sound states according to gameplay state, a set of concurrently running playlists may react and adapt to changes in the game.
    /// </description>
    /// <code>
    /// // State indicating that the listener is submerged.
    /// singleton SFXState( AudioLocationUnderwater )
    /// {
    ///    parentGroup = AudioLocation;
    ///    // AudioStateExclusive is a class defined in the core scripts that will automatically
    ///    // ensure for a state to deactivate all the sibling SFXStates in its parentGroup when it
    ///    // is activated.
    ///    className = "AudioStateExclusive";
    /// };
    /// 
    /// // State suitable e.g. for combat.
    /// singleton SFXState( AudioMoodAggressive )
    /// {
    ///    parentGroup = AudioMood;
    ///    className = "AudioStateExclusive";
    /// };
    /// </code>
    /// <see cref="SFXPlayList" />
    /// <see cref="SFXController" />
    /// <see cref="SFXPlayList::state" />
    /// <see cref="SFXPlayList::stateMode" />
    public unsafe class SFXState : SimDataBlock {
        public SFXState(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public SFXState(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public SFXState(string pName) 
            : this(pName, false) {
        }
        
        public SFXState(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public SFXState(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public SFXState(SimObject pObj) 
            : base(pObj) {
        }
        
        public SFXState(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
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
                                "fnSFXState_enable"), typeof(_Enable));
                }
                
                return _EnableFunc;
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
                                "fnSFXState_disable"), typeof(_Disable));
                }
                
                return _DisableFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsDisabled__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsDisabled(IntPtr _this, IsDisabled__Args args);
            private static _IsDisabled _IsDisabledFunc;
            internal static _IsDisabled IsDisabled() {
                if (_IsDisabledFunc == null) {
                    _IsDisabledFunc =
                        (_IsDisabled)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSFXState_isDisabled"), typeof(_IsDisabled));
                }
                
                return _IsDisabledFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Deactivate__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Deactivate(IntPtr _this, Deactivate__Args args);
            private static _Deactivate _DeactivateFunc;
            internal static _Deactivate Deactivate() {
                if (_DeactivateFunc == null) {
                    _DeactivateFunc =
                        (_Deactivate)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSFXState_deactivate"), typeof(_Deactivate));
                }
                
                return _DeactivateFunc;
            }

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
                                "fnSFXState_activate"), typeof(_Activate));
                }
                
                return _ActivateFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsActive__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsActive(IntPtr _this, IsActive__Args args);
            private static _IsActive _IsActiveFunc;
            internal static _IsActive IsActive() {
                if (_IsActiveFunc == null) {
                    _IsActiveFunc =
                        (_IsActive)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSFXState_isActive"), typeof(_IsActive));
                }
                
                return _IsActiveFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnDeactivate__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnDeactivate(IntPtr _this, OnDeactivate__Args args);
            private static _OnDeactivate _OnDeactivateFunc;
            internal static _OnDeactivate OnDeactivate() {
                if (_OnDeactivateFunc == null) {
                    _OnDeactivateFunc =
                        (_OnDeactivate)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbSFXState_onDeactivate"), typeof(_OnDeactivate));
                }
                
                return _OnDeactivateFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnActivate__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnActivate(IntPtr _this, OnActivate__Args args);
            private static _OnActivate _OnActivateFunc;
            internal static _OnActivate OnActivate() {
                if (_OnActivateFunc == null) {
                    _OnActivateFunc =
                        (_OnActivate)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbSFXState_onActivate"), typeof(_OnActivate));
                }
                
                return _OnActivateFunc;
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
                                "fnSFXState_staticGetType"), typeof(_StaticGetType));
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
                                "fnSFXState_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Decrease the disabling count of the state.
        /// If the disabling count reaches zero while the activation count is still non-zero, the state will be reactivated again.
        /// </description>
        /// <see cref="isDisabled" />
        public void Enable() {
             InternalUnsafeMethods.Enable__Args _args = new InternalUnsafeMethods.Enable__Args() {
             };
             InternalUnsafeMethods.Enable()(ObjectPtr, _args);
        }

        /// <description>
        /// Increase the disabling count of the state.
        /// If the state is currently active, it will be deactivated.
        /// </description>
        /// <see cref="isDisabled" />
        public void Disable() {
             InternalUnsafeMethods.Disable__Args _args = new InternalUnsafeMethods.Disable__Args() {
             };
             InternalUnsafeMethods.Disable()(ObjectPtr, _args);
        }

        /// <description>
        /// Test whether the state is currently disabled.
        /// This is true when the disabling count of the state is non-zero.
        /// </description>
        /// <returns>True if the state is disabled.</returns>
        /// <see cref="disable" />
        public bool IsDisabled() {
             InternalUnsafeMethods.IsDisabled__Args _args = new InternalUnsafeMethods.IsDisabled__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.IsDisabled()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Decrease the activation count on the state.
        /// If the count reaches zero and the state was not disabled, the state will be deactivated.
        /// </description>
        /// <see cref="isActive" />
        /// <see cref="activate" />
        public void Deactivate() {
             InternalUnsafeMethods.Deactivate__Args _args = new InternalUnsafeMethods.Deactivate__Args() {
             };
             InternalUnsafeMethods.Deactivate()(ObjectPtr, _args);
        }

        /// <description>
        /// Increase the activation count on the state.
        /// If the state isn't already active and it is not disabled, the state will be activated.
        /// </description>
        /// <see cref="isActive" />
        /// <see cref="deactivate" />
        public void Activate() {
             InternalUnsafeMethods.Activate__Args _args = new InternalUnsafeMethods.Activate__Args() {
             };
             InternalUnsafeMethods.Activate()(ObjectPtr, _args);
        }

        /// <description>
        /// Test whether the state is currently active.
        /// This is true when the activation count is >0 and the disabling count is =0.
        /// </description>
        /// <returns>True if the state is currently active.</returns>
        /// <see cref="activate" />
        public bool IsActive() {
             InternalUnsafeMethods.IsActive__Args _args = new InternalUnsafeMethods.IsActive__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.IsActive()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// called when the state goes from active to deactive.
        /// </description>
        public virtual void OnDeactivate() {
             InternalUnsafeMethods.OnDeactivate__Args _args = new InternalUnsafeMethods.OnDeactivate__Args() {
             };
             InternalUnsafeMethods.OnDeactivate()(ObjectPtr, _args);
        }

        /// <description>
        /// Called when the state goes from inactive to active.
        /// </description>
        public virtual void OnActivate() {
             InternalUnsafeMethods.OnActivate__Args _args = new InternalUnsafeMethods.OnActivate__Args() {
             };
             InternalUnsafeMethods.OnActivate()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the SFXState class.
        /// </description>
        /// <returns>The type info object for SFXState</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// States that will automatically be activated when this state is activated.
        /// </description>
        /// </value>
        public DynamicFieldVector<SFXState> IncludedStates {
            get => new DynamicFieldVector<SFXState>(
                    this, 
                    "includedStates", 
                    4, 
                    val => GenericMarshal.StringTo<SFXState>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// States that will automatically be disabled when this state is activated.
        /// </description>
        /// </value>
        public DynamicFieldVector<SFXState> ExcludedStates {
            get => new DynamicFieldVector<SFXState>(
                    this, 
                    "excludedStates", 
                    4, 
                    val => GenericMarshal.StringTo<SFXState>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }
    }
}