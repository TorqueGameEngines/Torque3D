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
    /// <summary>A state block description for rendering.</summary>
    /// <description>
    /// This object is used with ShaderData in CustomMaterial and PostEffect to define the render state.
    /// </description>
    /// <code>
    /// singleton GFXStateBlockData( PFX_DOFDownSampleStateBlock )
    /// {
    ///    zDefined = true;
    ///    zEnable = false;
    ///    zWriteEnable = false;
    /// 
    ///    samplersDefined = true;
    ///    samplerStates[0] = SamplerClampLinear;
    ///    samplerStates[1] = SamplerClampPoint;
    /// 
    ///    // Copy the clamped linear sampler, but change
    ///    // the u coord to wrap for this special case.
    ///    samplerStates[2] = new GFXSamplerStateData( : SamplerClampLinear )
    ///    {
    ///       addressModeU = GFXAddressWrap;
    ///    };
    /// };
    /// </code>
    /// <remarks> The 'xxxxDefined' fields are used to know what groups of fields are modified when combining multiple state blocks in material processing.  You should take care to enable the right ones when setting values.
    /// </remarks>
    public unsafe class GFXStateBlockData : SimObject {
        public GFXStateBlockData(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public GFXStateBlockData(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public GFXStateBlockData(string pName) 
            : this(pName, false) {
        }
        
        public GFXStateBlockData(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public GFXStateBlockData(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public GFXStateBlockData(SimObject pObj) 
            : base(pObj) {
        }
        
        public GFXStateBlockData(IntPtr pObj) 
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
                                "fnGFXStateBlockData_staticGetType"), typeof(_StaticGetType));
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
                                "fnGFXStateBlockData_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the GFXStateBlockData class.
        /// </description>
        /// <returns>The type info object for GFXStateBlockData</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Set to true if the alpha blend state is not all defaults.
        /// </description>
        /// </value>
        public bool BlendDefined {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("blendDefined"));
            set => SetFieldValue("blendDefined", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Enables alpha blending.  The default is false.
        /// </description>
        /// </value>
        public bool BlendEnable {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("blendEnable"));
            set => SetFieldValue("blendEnable", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The source blend state.  The default is GFXBlendOne.
        /// </description>
        /// </value>
        public GFXBlend BlendSrc {
            get => GenericMarshal.StringTo<GFXBlend>(GetFieldValue("blendSrc"));
            set => SetFieldValue("blendSrc", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The destination blend state.  The default is GFXBlendZero.
        /// </description>
        /// </value>
        public GFXBlend BlendDest {
            get => GenericMarshal.StringTo<GFXBlend>(GetFieldValue("blendDest"));
            set => SetFieldValue("blendDest", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The arithmetic operation applied to alpha blending.  The default is GFXBlendOpAdd.
        /// </description>
        /// </value>
        public GFXBlendOp BlendOp {
            get => GenericMarshal.StringTo<GFXBlendOp>(GetFieldValue("blendOp"));
            set => SetFieldValue("blendOp", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Set to true if the seperate alpha blend state is not all defaults.
        /// </description>
        /// </value>
        public bool SeparateAlphaBlendDefined {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("separateAlphaBlendDefined"));
            set => SetFieldValue("separateAlphaBlendDefined", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Enables the separate blend mode for the alpha channel.  The default is false.
        /// </description>
        /// </value>
        public bool SeparateAlphaBlendEnable {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("separateAlphaBlendEnable"));
            set => SetFieldValue("separateAlphaBlendEnable", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The source blend state.  The default is GFXBlendOne.
        /// </description>
        /// </value>
        public GFXBlend SeparateAlphaBlendSrc {
            get => GenericMarshal.StringTo<GFXBlend>(GetFieldValue("separateAlphaBlendSrc"));
            set => SetFieldValue("separateAlphaBlendSrc", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The destination blend state.  The default is GFXBlendZero.
        /// </description>
        /// </value>
        public GFXBlend SeparateAlphaBlendDest {
            get => GenericMarshal.StringTo<GFXBlend>(GetFieldValue("separateAlphaBlendDest"));
            set => SetFieldValue("separateAlphaBlendDest", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The arithmetic operation applied to separate alpha blending.  The default is GFXBlendOpAdd.
        /// </description>
        /// </value>
        public GFXBlendOp SeparateAlphaBlendOp {
            get => GenericMarshal.StringTo<GFXBlendOp>(GetFieldValue("separateAlphaBlendOp"));
            set => SetFieldValue("separateAlphaBlendOp", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Set to true if the alpha test state is not all defaults.
        /// </description>
        /// </value>
        public bool AlphaDefined {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("alphaDefined"));
            set => SetFieldValue("alphaDefined", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Enables per-pixel alpha testing.  The default is false.
        /// </description>
        /// </value>
        public bool AlphaTestEnable {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("alphaTestEnable"));
            set => SetFieldValue("alphaTestEnable", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The test function used to accept or reject a pixel based on its alpha value.  The default is GFXCmpGreaterEqual.
        /// </description>
        /// </value>
        public GFXCmpFunc AlphaTestFunc {
            get => GenericMarshal.StringTo<GFXCmpFunc>(GetFieldValue("alphaTestFunc"));
            set => SetFieldValue("alphaTestFunc", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The reference alpha value against which pixels are tested.  The default is zero.
        /// </description>
        /// </value>
        public int AlphaTestRef {
            get => GenericMarshal.StringTo<int>(GetFieldValue("alphaTestRef"));
            set => SetFieldValue("alphaTestRef", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Set to true if the color write state is not all defaults.
        /// </description>
        /// </value>
        public bool ColorWriteDefined {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("colorWriteDefined"));
            set => SetFieldValue("colorWriteDefined", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Enables red channel writes.  The default is true.
        /// </description>
        /// </value>
        public bool ColorWriteRed {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("colorWriteRed"));
            set => SetFieldValue("colorWriteRed", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Enables blue channel writes.  The default is true.
        /// </description>
        /// </value>
        public bool ColorWriteBlue {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("colorWriteBlue"));
            set => SetFieldValue("colorWriteBlue", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Enables green channel writes.  The default is true.
        /// </description>
        /// </value>
        public bool ColorWriteGreen {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("colorWriteGreen"));
            set => SetFieldValue("colorWriteGreen", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Enables alpha channel writes.  The default is true.
        /// </description>
        /// </value>
        public bool ColorWriteAlpha {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("colorWriteAlpha"));
            set => SetFieldValue("colorWriteAlpha", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Set to true if the culling state is not all defaults.
        /// </description>
        /// </value>
        public bool CullDefined {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("cullDefined"));
            set => SetFieldValue("cullDefined", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Defines how back facing triangles are culled if at all.  The default is GFXCullCCW.
        /// </description>
        /// </value>
        public GFXCullMode CullMode {
            get => GenericMarshal.StringTo<GFXCullMode>(GetFieldValue("cullMode"));
            set => SetFieldValue("cullMode", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Set to true if the depth state is not all defaults.
        /// </description>
        /// </value>
        public bool ZDefined {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("zDefined"));
            set => SetFieldValue("zDefined", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Enables z-buffer reads.  The default is true.
        /// </description>
        /// </value>
        public bool ZEnable {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("zEnable"));
            set => SetFieldValue("zEnable", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Enables z-buffer writes.  The default is true.
        /// </description>
        /// </value>
        public bool ZWriteEnable {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("zWriteEnable"));
            set => SetFieldValue("zWriteEnable", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The depth comparision function which a pixel must pass to be written to the z-buffer.  The default is GFXCmpLessEqual.
        /// </description>
        /// </value>
        public GFXCmpFunc ZFunc {
            get => GenericMarshal.StringTo<GFXCmpFunc>(GetFieldValue("zFunc"));
            set => SetFieldValue("zFunc", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// A floating-point bias used when comparing depth values.  The default is zero.
        /// </description>
        /// </value>
        public float ZBias {
            get => GenericMarshal.StringTo<float>(GetFieldValue("zBias"));
            set => SetFieldValue("zBias", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// An additional floating-point bias based on the maximum depth slop of the triangle being rendered.  The default is zero.
        /// </description>
        /// </value>
        public float ZSlopeBias {
            get => GenericMarshal.StringTo<float>(GetFieldValue("zSlopeBias"));
            set => SetFieldValue("zSlopeBias", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Set to true if the stencil state is not all defaults.
        /// </description>
        /// </value>
        public bool StencilDefined {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("stencilDefined"));
            set => SetFieldValue("stencilDefined", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Enables stenciling.  The default is false.
        /// </description>
        /// </value>
        public bool StencilEnable {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("stencilEnable"));
            set => SetFieldValue("stencilEnable", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The stencil operation to perform if the stencil test fails.  The default is GFXStencilOpKeep.
        /// </description>
        /// </value>
        public GFXStencilOp StencilFailOp {
            get => GenericMarshal.StringTo<GFXStencilOp>(GetFieldValue("stencilFailOp"));
            set => SetFieldValue("stencilFailOp", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The stencil operation to perform if the stencil test passes and the depth test fails.  The default is GFXStencilOpKeep.
        /// </description>
        /// </value>
        public GFXStencilOp StencilZFailOp {
            get => GenericMarshal.StringTo<GFXStencilOp>(GetFieldValue("stencilZFailOp"));
            set => SetFieldValue("stencilZFailOp", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The stencil operation to perform if both the stencil and the depth tests pass.  The default is GFXStencilOpKeep.
        /// </description>
        /// </value>
        public GFXStencilOp StencilPassOp {
            get => GenericMarshal.StringTo<GFXStencilOp>(GetFieldValue("stencilPassOp"));
            set => SetFieldValue("stencilPassOp", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The comparison function to test the reference value to a stencil buffer entry.  The default is GFXCmpNever.
        /// </description>
        /// </value>
        public GFXCmpFunc StencilFunc {
            get => GenericMarshal.StringTo<GFXCmpFunc>(GetFieldValue("stencilFunc"));
            set => SetFieldValue("stencilFunc", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The reference value for the stencil test.  The default is zero.
        /// </description>
        /// </value>
        public int StencilRef {
            get => GenericMarshal.StringTo<int>(GetFieldValue("stencilRef"));
            set => SetFieldValue("stencilRef", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The mask applied to the reference value and each stencil buffer entry to determine the significant bits for the stencil test. The default is 0xFFFFFFFF.
        /// </description>
        /// </value>
        public int StencilMask {
            get => GenericMarshal.StringTo<int>(GetFieldValue("stencilMask"));
            set => SetFieldValue("stencilMask", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The write mask applied to values written into the stencil buffer. The default is 0xFFFFFFFF.
        /// </description>
        /// </value>
        public int StencilWriteMask {
            get => GenericMarshal.StringTo<int>(GetFieldValue("stencilWriteMask"));
            set => SetFieldValue("stencilWriteMask", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Enables fixed function lighting when rendering without a shader on geometry with vertex normals.  The default is false.
        /// </description>
        /// </value>
        public bool FfLighting {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("ffLighting"));
            set => SetFieldValue("ffLighting", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Enables fixed function vertex coloring when rendering without a shader.  The default is false.
        /// </description>
        /// </value>
        public bool VertexColorEnable {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("vertexColorEnable"));
            set => SetFieldValue("vertexColorEnable", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Set to true if the sampler states are not all defaults.
        /// </description>
        /// </value>
        public bool SamplersDefined {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("samplersDefined"));
            set => SetFieldValue("samplersDefined", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The array of texture sampler states.
        /// </description>
        /// <remarks> Not all graphics devices support 16 samplers.  In general all systems support 4 samplers with most modern cards doing 8.</remarks>
        /// </value>
        public DynamicFieldVector<GFXSamplerStateData> SamplerStates {
            get => new DynamicFieldVector<GFXSamplerStateData>(
                    this, 
                    "samplerStates", 
                    16, 
                    val => GenericMarshal.StringTo<GFXSamplerStateData>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// The color used for multiple-texture blending with the GFXTATFactor texture-blending argument or the GFXTOPBlendFactorAlpha texture-blending operation.  The default is opaque white (255, 255, 255, 255).
        /// </description>
        /// </value>
        public ColorI TextureFactor {
            get => GenericMarshal.StringTo<ColorI>(GetFieldValue("textureFactor"));
            set => SetFieldValue("textureFactor", GenericMarshal.ToString(value));
        }
    }
}