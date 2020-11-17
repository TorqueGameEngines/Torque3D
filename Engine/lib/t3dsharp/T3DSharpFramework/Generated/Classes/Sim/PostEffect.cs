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
    /// <summary>A fullscreen shader effect.</summary>
    /// <description>
    /// 
    /// </description>
    public unsafe class PostEffect : SimGroup {
        public PostEffect(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public PostEffect(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public PostEffect(string pName) 
            : this(pName, false) {
        }
        
        public PostEffect(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public PostEffect(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public PostEffect(SimObject pObj) 
            : base(pObj) {
        }
        
        public PostEffect(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct ClearShaderMacros__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ClearShaderMacros(IntPtr _this, ClearShaderMacros__Args args);
            private static _ClearShaderMacros _ClearShaderMacrosFunc;
            internal static _ClearShaderMacros ClearShaderMacros() {
                if (_ClearShaderMacrosFunc == null) {
                    _ClearShaderMacrosFunc =
                        (_ClearShaderMacros)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnPostEffect_clearShaderMacros"), typeof(_ClearShaderMacros));
                }
                
                return _ClearShaderMacrosFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct RemoveShaderMacro__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string key;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _RemoveShaderMacro(IntPtr _this, RemoveShaderMacro__Args args);
            private static _RemoveShaderMacro _RemoveShaderMacroFunc;
            internal static _RemoveShaderMacro RemoveShaderMacro() {
                if (_RemoveShaderMacroFunc == null) {
                    _RemoveShaderMacroFunc =
                        (_RemoveShaderMacro)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnPostEffect_removeShaderMacro"), typeof(_RemoveShaderMacro));
                }
                
                return _RemoveShaderMacroFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetShaderMacro__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string key;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string value;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetShaderMacro(IntPtr _this, SetShaderMacro__Args args);
            private static _SetShaderMacro _SetShaderMacroFunc;
            internal static _SetShaderMacro SetShaderMacro() {
                if (_SetShaderMacroFunc == null) {
                    _SetShaderMacroFunc =
                        (_SetShaderMacro)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnPostEffect_setShaderMacro"), typeof(_SetShaderMacro));
                }
                
                return _SetShaderMacroFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct DumpShaderDisassembly__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _DumpShaderDisassembly(IntPtr _this, DumpShaderDisassembly__Args args);
            private static _DumpShaderDisassembly _DumpShaderDisassemblyFunc;
            internal static _DumpShaderDisassembly DumpShaderDisassembly() {
                if (_DumpShaderDisassemblyFunc == null) {
                    _DumpShaderDisassemblyFunc =
                        (_DumpShaderDisassembly)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnPostEffect_dumpShaderDisassembly"), typeof(_DumpShaderDisassembly));
                }
                
                return _DumpShaderDisassemblyFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetAspectRatio__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _GetAspectRatio(IntPtr _this, GetAspectRatio__Args args);
            private static _GetAspectRatio _GetAspectRatioFunc;
            internal static _GetAspectRatio GetAspectRatio() {
                if (_GetAspectRatioFunc == null) {
                    _GetAspectRatioFunc =
                        (_GetAspectRatio)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnPostEffect_getAspectRatio"), typeof(_GetAspectRatio));
                }
                
                return _GetAspectRatioFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetShaderConst__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string value;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetShaderConst(IntPtr _this, SetShaderConst__Args args);
            private static _SetShaderConst _SetShaderConstFunc;
            internal static _SetShaderConst SetShaderConst() {
                if (_SetShaderConstFunc == null) {
                    _SetShaderConstFunc =
                        (_SetShaderConst)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnPostEffect_setShaderConst"), typeof(_SetShaderConst));
                }
                
                return _SetShaderConstFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetTexture__Args
            {
                internal int index;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string filePath;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetTexture(IntPtr _this, SetTexture__Args args);
            private static _SetTexture _SetTextureFunc;
            internal static _SetTexture SetTexture() {
                if (_SetTextureFunc == null) {
                    _SetTextureFunc =
                        (_SetTexture)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnPostEffect_setTexture"), typeof(_SetTexture));
                }
                
                return _SetTextureFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsEnabled__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsEnabled(IntPtr _this, IsEnabled__Args args);
            private static _IsEnabled _IsEnabledFunc;
            internal static _IsEnabled IsEnabled() {
                if (_IsEnabledFunc == null) {
                    _IsEnabledFunc =
                        (_IsEnabled)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnPostEffect_isEnabled"), typeof(_IsEnabled));
                }
                
                return _IsEnabledFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Toggle__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _Toggle(IntPtr _this, Toggle__Args args);
            private static _Toggle _ToggleFunc;
            internal static _Toggle Toggle() {
                if (_ToggleFunc == null) {
                    _ToggleFunc =
                        (_Toggle)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnPostEffect_toggle"), typeof(_Toggle));
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
                                "fnPostEffect_disable"), typeof(_Disable));
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
                                "fnPostEffect_enable"), typeof(_Enable));
                }
                
                return _EnableFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Reload__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Reload(IntPtr _this, Reload__Args args);
            private static _Reload _ReloadFunc;
            internal static _Reload Reload() {
                if (_ReloadFunc == null) {
                    _ReloadFunc =
                        (_Reload)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnPostEffect_reload"), typeof(_Reload));
                }
                
                return _ReloadFunc;
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
                                "fnPostEffect_staticGetType"), typeof(_StaticGetType));
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
                                "fnPostEffect_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnDisabled__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnDisabled(IntPtr _this, OnDisabled__Args args);
            private static _OnDisabled _OnDisabledFunc;
            internal static _OnDisabled OnDisabled() {
                if (_OnDisabledFunc == null) {
                    _OnDisabledFunc =
                        (_OnDisabled)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbPostEffect_onDisabled"), typeof(_OnDisabled));
                }
                
                return _OnDisabledFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnEnabled__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _OnEnabled(IntPtr _this, OnEnabled__Args args);
            private static _OnEnabled _OnEnabledFunc;
            internal static _OnEnabled OnEnabled() {
                if (_OnEnabledFunc == null) {
                    _OnEnabledFunc =
                        (_OnEnabled)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbPostEffect_onEnabled"), typeof(_OnEnabled));
                }
                
                return _OnEnabledFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetShaderConsts__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetShaderConsts(IntPtr _this, SetShaderConsts__Args args);
            private static _SetShaderConsts _SetShaderConstsFunc;
            internal static _SetShaderConsts SetShaderConsts() {
                if (_SetShaderConstsFunc == null) {
                    _SetShaderConstsFunc =
                        (_SetShaderConsts)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbPostEffect_setShaderConsts"), typeof(_SetShaderConsts));
                }
                
                return _SetShaderConstsFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct PreProcess__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _PreProcess(IntPtr _this, PreProcess__Args args);
            private static _PreProcess _PreProcessFunc;
            internal static _PreProcess PreProcess() {
                if (_PreProcessFunc == null) {
                    _PreProcessFunc =
                        (_PreProcess)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbPostEffect_preProcess"), typeof(_PreProcess));
                }
                
                return _PreProcessFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnAdd__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnAdd(IntPtr _this, OnAdd__Args args);
            private static _OnAdd _OnAddFunc;
            internal static _OnAdd OnAdd() {
                if (_OnAddFunc == null) {
                    _OnAddFunc =
                        (_OnAdd)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbPostEffect_onAdd"), typeof(_OnAdd));
                }
                
                return _OnAddFunc;
            }
        }
        #endregion

        /// <description>
        /// Remove all shader macros.
        /// </description>
        public void ClearShaderMacros() {
             InternalUnsafeMethods.ClearShaderMacros__Args _args = new InternalUnsafeMethods.ClearShaderMacros__Args() {
             };
             InternalUnsafeMethods.ClearShaderMacros()(ObjectPtr, _args);
        }

        /// <description>
        /// Remove a shader macro. This will usually be called within the preProcess callback.
        /// </description>
        /// <param name="key">Macro to remove.</param>
        public void RemoveShaderMacro(string key) {
             InternalUnsafeMethods.RemoveShaderMacro__Args _args = new InternalUnsafeMethods.RemoveShaderMacro__Args() {
                key = key,
             };
             InternalUnsafeMethods.RemoveShaderMacro()(ObjectPtr, _args);
        }

        /// <description>
        /// Adds a macro to the effect's shader or sets an existing one's value. This will usually be called within the onAdd or preProcess callback.
        /// </description>
        /// <param name="key">lval of the macro.</param>
        /// <param name="value">rval of the macro, or may be empty.</param>
        /// <code>
        /// function MyPfx::onAdd( %this )
        /// {
        ///    %this.setShaderMacro( "NUM_SAMPLES", "10" );
        ///    %this.setShaderMacro( "HIGH_QUALITY_MODE" );
        ///    
        ///    // In the shader looks like... 
        ///    // #define NUM_SAMPLES 10
        ///    // #define HIGH_QUALITY_MODE
        /// }
        /// </code>
        public void SetShaderMacro(string key, string value = "") {
             InternalUnsafeMethods.SetShaderMacro__Args _args = new InternalUnsafeMethods.SetShaderMacro__Args() {
                key = key,
                value = value,
             };
             InternalUnsafeMethods.SetShaderMacro()(ObjectPtr, _args);
        }

        /// <description>
        /// Dumps this PostEffect shader's disassembly to a temporary text file.
        /// </description>
        /// <returns>Full path to the dumped file or an empty string if failed.</returns>
        public string DumpShaderDisassembly() {
             InternalUnsafeMethods.DumpShaderDisassembly__Args _args = new InternalUnsafeMethods.DumpShaderDisassembly__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.DumpShaderDisassembly()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <returns>Width over height of the backbuffer.</returns>
        public float GetAspectRatio() {
             InternalUnsafeMethods.GetAspectRatio__Args _args = new InternalUnsafeMethods.GetAspectRatio__Args() {
             };
             float _engineResult = InternalUnsafeMethods.GetAspectRatio()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Sets the value of a uniform defined in the shader. This will usually be called within the setShaderConsts callback. Array type constants are not supported.
        /// </description>
        /// <param name="name">Name of the constanst, prefixed with '$'.</param>
        /// <param name="value">Value to set, space seperate values with more than one element.</param>
        /// <code>
        /// function MyPfx::setShaderConsts( %this )
        /// {
        ///    // example float4 uniform
        ///    %this.setShaderConst( "$colorMod", "1.0 0.9 1.0 1.0" );
        ///    // example float1 uniform
        ///    %this.setShaderConst( "$strength", "3.0" );
        ///    // example integer uniform
        ///    %this.setShaderConst( "$loops", "5" );}
        /// </code>
        public void SetShaderConst(string name, string value) {
             InternalUnsafeMethods.SetShaderConst__Args _args = new InternalUnsafeMethods.SetShaderConst__Args() {
                name = name,
                value = value,
             };
             InternalUnsafeMethods.SetShaderConst()(ObjectPtr, _args);
        }

        /// <description>
        /// This is used to set the texture file and load the texture on a running effect. If the texture file is not different from the current file nothing is changed.  If the texture cannot be found a null texture is assigned.
        /// </description>
        /// <param name="index">The texture stage index.</param>
        /// <param name="filePath">The file name of the texture to set.</param>
        public void SetTexture(int index, string filePath) {
             InternalUnsafeMethods.SetTexture__Args _args = new InternalUnsafeMethods.SetTexture__Args() {
                index = index,
                filePath = filePath,
             };
             InternalUnsafeMethods.SetTexture()(ObjectPtr, _args);
        }

        /// <returns>True if the effect is enabled.</returns>
        public bool IsEnabled() {
             InternalUnsafeMethods.IsEnabled__Args _args = new InternalUnsafeMethods.IsEnabled__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.IsEnabled()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Toggles the effect between enabled / disabled.
        /// </description>
        /// <returns>True if effect is enabled.</returns>
        public bool Toggle() {
             InternalUnsafeMethods.Toggle__Args _args = new InternalUnsafeMethods.Toggle__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.Toggle()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Disables the effect.
        /// </description>
        public void Disable() {
             InternalUnsafeMethods.Disable__Args _args = new InternalUnsafeMethods.Disable__Args() {
             };
             InternalUnsafeMethods.Disable()(ObjectPtr, _args);
        }

        /// <description>
        /// Enables the effect.
        /// </description>
        public void Enable() {
             InternalUnsafeMethods.Enable__Args _args = new InternalUnsafeMethods.Enable__Args() {
             };
             InternalUnsafeMethods.Enable()(ObjectPtr, _args);
        }

        /// <description>
        /// Reloads the effect shader and textures.
        /// </description>
        public void Reload() {
             InternalUnsafeMethods.Reload__Args _args = new InternalUnsafeMethods.Reload__Args() {
             };
             InternalUnsafeMethods.Reload()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the PostEffect class.
        /// </description>
        /// <returns>The type info object for PostEffect</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }

        /// <description>
        /// Called when this effect becomes disabled.
        /// </description>
        public virtual void OnDisabled() {
             InternalUnsafeMethods.OnDisabled__Args _args = new InternalUnsafeMethods.OnDisabled__Args() {
             };
             InternalUnsafeMethods.OnDisabled()(ObjectPtr, _args);
        }

        /// <description>
        /// Called when this effect becomes enabled. If the user returns false from this callback the effect will not be enabled.
        /// </description>
        /// <returns>True to allow this effect to be enabled.</returns>
        public virtual bool OnEnabled() {
             InternalUnsafeMethods.OnEnabled__Args _args = new InternalUnsafeMethods.OnEnabled__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.OnEnabled()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Called immediate before processing this effect. This is the user's chance to set the value of shader uniforms (constants).
        /// </description>
        /// <see cref="setShaderConst" />
        public virtual void SetShaderConsts() {
             InternalUnsafeMethods.SetShaderConsts__Args _args = new InternalUnsafeMethods.SetShaderConsts__Args() {
             };
             InternalUnsafeMethods.SetShaderConsts()(ObjectPtr, _args);
        }

        /// <description>
        /// Called when an effect is processed but before textures are bound. This allows the user to change texture related paramaters or macros at runtime.
        /// </description>
        /// <code>
        /// function SSAOPostFx::preProcess( %this )
        /// {
        ///    if ( $SSAOPostFx::quality !$= %this.quality )
        ///    {
        ///       %this.quality = mClamp( mRound( $SSAOPostFx::quality ), 0, 2 );
        ///       
        ///       %this.setShaderMacro( "QUALITY", %this.quality );
        ///    }
        ///    %this.targetScale = $SSAOPostFx::targetScale;
        /// }
        /// </code>
        /// <see cref="setShaderConst" />
        /// <see cref="setShaderMacro" />
        public virtual void PreProcess() {
             InternalUnsafeMethods.PreProcess__Args _args = new InternalUnsafeMethods.PreProcess__Args() {
             };
             InternalUnsafeMethods.PreProcess()(ObjectPtr, _args);
        }

        /// <description>
        /// Called when this object is first created and registered.
        /// </description>
        public virtual void OnAdd() {
             InternalUnsafeMethods.OnAdd__Args _args = new InternalUnsafeMethods.OnAdd__Args() {
             };
             InternalUnsafeMethods.OnAdd()(ObjectPtr, _args);
        }


        /// <value>
        /// <description>
        /// Name of a GFXShaderData for this effect.
        /// </description>
        /// </value>
        public string Shader {
            get => GenericMarshal.StringTo<string>(GetFieldValue("shader"));
            set => SetFieldValue("shader", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Name of a GFXStateBlockData for this effect.
        /// </description>
        /// </value>
        public GFXStateBlockData StateBlock {
            get => GenericMarshal.StringTo<GFXStateBlockData>(GetFieldValue("stateBlock"));
            set => SetFieldValue("stateBlock", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// String identifier of this effect's target texture.
        /// </description>
        /// <see cref="PFXTextureIdentifiers" />
        /// </value>
        public string Target {
            get => GenericMarshal.StringTo<string>(GetFieldValue("Target"));
            set => SetFieldValue("Target", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Optional string identifier for this effect's target depth/stencil texture.
        /// </description>
        /// <see cref="PFXTextureIdentifiers" />
        /// </value>
        public string TargetDepthStencil {
            get => GenericMarshal.StringTo<string>(GetFieldValue("targetDepthStencil"));
            set => SetFieldValue("targetDepthStencil", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// If targetSize is zero this is used to set a relative size from the current target.
        /// </description>
        /// </value>
        public Point2F TargetScale {
            get => GenericMarshal.StringTo<Point2F>(GetFieldValue("targetScale"));
            set => SetFieldValue("targetScale", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// If non-zero this is used as the absolute target size.
        /// </description>
        /// </value>
        public Point2I TargetSize {
            get => GenericMarshal.StringTo<Point2I>(GetFieldValue("targetSize"));
            set => SetFieldValue("targetSize", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Format of the target texture, not applicable if writing to the backbuffer.
        /// </description>
        /// </value>
        public GFXFormat TargetFormat {
            get => GenericMarshal.StringTo<GFXFormat>(GetFieldValue("targetFormat"));
            set => SetFieldValue("targetFormat", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Color to which the target texture is cleared before rendering.
        /// </description>
        /// </value>
        public LinearColorF TargetClearColor {
            get => GenericMarshal.StringTo<LinearColorF>(GetFieldValue("targetClearColor"));
            set => SetFieldValue("targetClearColor", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Describes when the target texture should be cleared.
        /// </description>
        /// </value>
        public PFXTargetClear TargetClear {
            get => GenericMarshal.StringTo<PFXTargetClear>(GetFieldValue("targetClear"));
            set => SetFieldValue("targetClear", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Specifies how the viewport should be set up for a target texture.
        /// </description>
        /// </value>
        public PFXTargetViewport TargetViewport {
            get => GenericMarshal.StringTo<PFXTargetViewport>(GetFieldValue("targetViewport"));
            set => SetFieldValue("targetViewport", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Input textures to this effect ( samplers ).
        /// </description>
        /// <see cref="PFXTextureIdentifiers" />
        /// </value>
        public DynamicFieldVector<string> Texture {
            get => new DynamicFieldVector<string>(
                    this, 
                    "texture", 
                    8, 
                    val => GenericMarshal.StringTo<string>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Set input texture to be sRGB
        /// </description>
        /// </value>
        public DynamicFieldVector<bool> TextureSRGB {
            get => new DynamicFieldVector<bool>(
                    this, 
                    "textureSRGB", 
                    8, 
                    val => GenericMarshal.StringTo<bool>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// When to process this effect during the frame.
        /// </description>
        /// </value>
        public PFXRenderTime RenderTime {
            get => GenericMarshal.StringTo<PFXRenderTime>(GetFieldValue("renderTime"));
            set => SetFieldValue("renderTime", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Name of a renderBin, used if renderTime is PFXBeforeBin or PFXAfterBin.
        /// </description>
        /// </value>
        public string RenderBin {
            get => GenericMarshal.StringTo<string>(GetFieldValue("renderBin"));
            set => SetFieldValue("renderBin", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// PostEffects are processed in DESCENDING order of renderPriority if more than one has the same renderBin/Time.
        /// </description>
        /// </value>
        public float RenderPriority {
            get => GenericMarshal.StringTo<float>(GetFieldValue("renderPriority"));
            set => SetFieldValue("renderPriority", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Is this effect processed during reflection render passes.
        /// </description>
        /// </value>
        public bool AllowReflectPass {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("allowReflectPass"));
            set => SetFieldValue("allowReflectPass", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Is the effect on.
        /// </description>
        /// </value>
        public bool Enabled {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("Enabled"));
            set => SetFieldValue("Enabled", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Allows you to turn on a PostEffect for only a single frame.
        /// </description>
        /// </value>
        public bool OnThisFrame {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("onThisFrame"));
            set => SetFieldValue("onThisFrame", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Allows you to turn on a PostEffect for only a single frame.
        /// </description>
        /// </value>
        public bool OneFrameOnly {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("oneFrameOnly"));
            set => SetFieldValue("oneFrameOnly", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Skip processing of this PostEffect and its children even if its parent is enabled. Parent and sibling PostEffects in the chain are still processed.
        /// </description>
        /// </value>
        public bool Skip {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("skip"));
            set => SetFieldValue("skip", GenericMarshal.ToString(value));
        }
    }
}