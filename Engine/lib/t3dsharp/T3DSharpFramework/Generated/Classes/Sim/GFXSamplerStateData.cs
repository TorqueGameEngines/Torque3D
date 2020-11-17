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
    /// <summary>A sampler state used by GFXStateBlockData.</summary>
    /// <description>
    /// The samplers define how a texture will be sampled when used from the shader or fixed function device
    /// </description>
    /// <code>
    /// singleton GFXSamplerStateData(SamplerClampLinear)
    /// {
    ///    textureColorOp = GFXTOPModulate;
    ///    addressModeU = GFXAddressClamp;
    ///    addressModeV = GFXAddressClamp;
    ///    addressModeW = GFXAddressClamp;
    ///    magFilter = GFXTextureFilterLinear;
    ///    minFilter = GFXTextureFilterLinear;
    ///    mipFilter = GFXTextureFilterLinear;
    /// };
    /// </code>
    /// <see cref="GFXStateBlockData" />
    public unsafe class GFXSamplerStateData : SimObject {
        public GFXSamplerStateData(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public GFXSamplerStateData(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public GFXSamplerStateData(string pName) 
            : this(pName, false) {
        }
        
        public GFXSamplerStateData(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public GFXSamplerStateData(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public GFXSamplerStateData(SimObject pObj) 
            : base(pObj) {
        }
        
        public GFXSamplerStateData(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
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
                                "fnGFXSamplerStateData_staticGetType"), typeof(_StaticGetType));
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
                                "fnGFXSamplerStateData_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the GFXSamplerStateData class.
        /// </description>
        /// <returns>The type info object for GFXSamplerStateData</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// The texture color blending operation.  The default value is GFXTOPDisable which disables the sampler.
        /// </description>
        /// </value>
        public GFXTextureOp TextureColorOp {
            get => GenericMarshal.StringTo<GFXTextureOp>(GetFieldValue("textureColorOp"));
            set => SetFieldValue("textureColorOp", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The first color argument for the texture stage.  The default value is GFXTACurrent.
        /// </description>
        /// </value>
        public GFXTextureArgument ColorArg1 {
            get => GenericMarshal.StringTo<GFXTextureArgument>(GetFieldValue("colorArg1"));
            set => SetFieldValue("colorArg1", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The second color argument for the texture stage.  The default value is GFXTATexture.
        /// </description>
        /// </value>
        public GFXTextureArgument ColorArg2 {
            get => GenericMarshal.StringTo<GFXTextureArgument>(GetFieldValue("colorArg2"));
            set => SetFieldValue("colorArg2", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The third color argument for triadic operations (multiply, add, and linearly interpolate).  The default value is GFXTACurrent.
        /// </description>
        /// </value>
        public GFXTextureArgument ColorArg3 {
            get => GenericMarshal.StringTo<GFXTextureArgument>(GetFieldValue("colorArg3"));
            set => SetFieldValue("colorArg3", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The texture alpha blending operation.  The default value is GFXTOPModulate.
        /// </description>
        /// </value>
        public GFXTextureOp AlphaOp {
            get => GenericMarshal.StringTo<GFXTextureOp>(GetFieldValue("alphaOp"));
            set => SetFieldValue("alphaOp", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The first alpha argument for the texture stage.  The default value is GFXTATexture.
        /// </description>
        /// </value>
        public GFXTextureArgument AlphaArg1 {
            get => GenericMarshal.StringTo<GFXTextureArgument>(GetFieldValue("alphaArg1"));
            set => SetFieldValue("alphaArg1", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The second alpha argument for the texture stage.  The default value is GFXTADiffuse.
        /// </description>
        /// </value>
        public GFXTextureArgument AlphaArg2 {
            get => GenericMarshal.StringTo<GFXTextureArgument>(GetFieldValue("alphaArg2"));
            set => SetFieldValue("alphaArg2", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The third alpha channel selector operand for triadic operations (multiply, add, and linearly interpolate).  The default value is GFXTACurrent.
        /// </description>
        /// </value>
        public GFXTextureArgument AlphaArg3 {
            get => GenericMarshal.StringTo<GFXTextureArgument>(GetFieldValue("alphaArg3"));
            set => SetFieldValue("alphaArg3", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The texture address mode for the u coordinate.  The default is GFXAddressWrap.
        /// </description>
        /// </value>
        public GFXTextureAddressMode AddressModeU {
            get => GenericMarshal.StringTo<GFXTextureAddressMode>(GetFieldValue("addressModeU"));
            set => SetFieldValue("addressModeU", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The texture address mode for the v coordinate.  The default is GFXAddressWrap.
        /// </description>
        /// </value>
        public GFXTextureAddressMode AddressModeV {
            get => GenericMarshal.StringTo<GFXTextureAddressMode>(GetFieldValue("addressModeV"));
            set => SetFieldValue("addressModeV", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The texture address mode for the w coordinate.  The default is GFXAddressWrap.
        /// </description>
        /// </value>
        public GFXTextureAddressMode AddressModeW {
            get => GenericMarshal.StringTo<GFXTextureAddressMode>(GetFieldValue("addressModeW"));
            set => SetFieldValue("addressModeW", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The texture magnification filter.  The default is GFXTextureFilterLinear.
        /// </description>
        /// </value>
        public GFXTextureFilterType MagFilter {
            get => GenericMarshal.StringTo<GFXTextureFilterType>(GetFieldValue("magFilter"));
            set => SetFieldValue("magFilter", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The texture minification filter.  The default is GFXTextureFilterLinear.
        /// </description>
        /// </value>
        public GFXTextureFilterType MinFilter {
            get => GenericMarshal.StringTo<GFXTextureFilterType>(GetFieldValue("minFilter"));
            set => SetFieldValue("minFilter", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The texture mipmap filter used during minification.  The default is GFXTextureFilterLinear.
        /// </description>
        /// </value>
        public GFXTextureFilterType MipFilter {
            get => GenericMarshal.StringTo<GFXTextureFilterType>(GetFieldValue("mipFilter"));
            set => SetFieldValue("mipFilter", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The mipmap level of detail bias.  The default value is zero.
        /// </description>
        /// </value>
        public float MipLODBias {
            get => GenericMarshal.StringTo<float>(GetFieldValue("mipLODBias"));
            set => SetFieldValue("mipLODBias", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The maximum texture anisotropy.  The default value is 1.
        /// </description>
        /// </value>
        public int MaxAnisotropy {
            get => GenericMarshal.StringTo<int>(GetFieldValue("maxAnisotropy"));
            set => SetFieldValue("maxAnisotropy", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Sets the texture transform state.  The default is GFXTTFFDisable.
        /// </description>
        /// </value>
        public GFXTextureTransformFlags TextureTransform {
            get => GenericMarshal.StringTo<GFXTextureTransformFlags>(GetFieldValue("textureTransform"));
            set => SetFieldValue("textureTransform", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The selection of the destination register for the result of this stage.  The default is GFXTACurrent.
        /// </description>
        /// </value>
        public GFXTextureArgument ResultArg {
            get => GenericMarshal.StringTo<GFXTextureArgument>(GetFieldValue("resultArg"));
            set => SetFieldValue("resultArg", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Compares sampled data against existing sampled data.  The default is GFXCmpNever.
        /// </description>
        /// </value>
        public GFXCmpFunc SamplerFunc {
            get => GenericMarshal.StringTo<GFXCmpFunc>(GetFieldValue("samplerFunc"));
            set => SetFieldValue("samplerFunc", GenericMarshal.ToString(value));
        }
    }
}