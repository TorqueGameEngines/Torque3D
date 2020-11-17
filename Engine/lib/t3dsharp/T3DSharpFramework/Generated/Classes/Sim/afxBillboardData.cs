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
    /// <summary>A datablock that specifies a Billboard effect.</summary>
    /// <description>
    /// A Billboard effect is a textured quadrangle which is always aligned to face towards the camera. It is much like a single static particle and is rendered in a similar fashion.
    /// </description>
    public unsafe class afxBillboardData : GameBaseData {
        public afxBillboardData(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public afxBillboardData(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public afxBillboardData(string pName) 
            : this(pName, false) {
        }
        
        public afxBillboardData(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public afxBillboardData(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public afxBillboardData(SimObject pObj) 
            : base(pObj) {
        }
        
        public afxBillboardData(IntPtr pObj) 
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
                                "fnafxBillboardData_staticGetType"), typeof(_StaticGetType));
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
                                "fnafxBillboardData_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the afxBillboardData class.
        /// </description>
        /// <returns>The type info object for afxBillboardData</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// The color assigned to the quadrangle geometry. The way it combines with the given texture varies according to the setting of the textureFunction field.
        /// </description>
        /// </value>
        public LinearColorF Color {
            get => GenericMarshal.StringTo<LinearColorF>(GetFieldValue("color"));
            set => SetFieldValue("color", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// An image to use as the billboard's texture.
        /// </description>
        /// </value>
        public string Texture {
            get => GenericMarshal.StringTo<string>(GetFieldValue("texture"));
            set => SetFieldValue("texture", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// A value-pair that specifies the horizontal and vertical dimensions of the billboard in scene units.
        /// </description>
        /// </value>
        public Point2F Dimensions {
            get => GenericMarshal.StringTo<Point2F>(GetFieldValue("dimensions"));
            set => SetFieldValue("dimensions", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// An array of four value-pairs that specify the UV texture coordinates for the four corners of the billboard's quadrangle.
        /// </description>
        /// </value>
        public DynamicFieldVector<Point2F> TextureCoords {
            get => new DynamicFieldVector<Point2F>(
                    this, 
                    "textureCoords", 
                    4, 
                    val => GenericMarshal.StringTo<Point2F>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Selects a common blend factor preset. When set to 'user', srcBlendFactor and dstBlendFactor can be used to set additional blend factor combinations.
        /// Possible values: normal, additive, subtractive, premultalpha, or user.
        /// </description>
        /// </value>
        public afxBillboard_BlendStyle BlendStyle {
            get => GenericMarshal.StringTo<afxBillboard_BlendStyle>(GetFieldValue("blendStyle"));
            set => SetFieldValue("blendStyle", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Specifies source blend factor when blendStyle is set to 'user'.
        /// Possible values: GFXBlendZero, GFXBlendOne, GFXBlendDestColor, GFXBlendInvDestColor, GFXBlendSrcAlpha, GFXBlendInvSrcAlpha, GFXBlendDestAlpha, GFXBlendInvDestAlpha, or GFXBlendSrcAlphaSat
        /// </description>
        /// </value>
        public GFXBlend SrcBlendFactor {
            get => GenericMarshal.StringTo<GFXBlend>(GetFieldValue("srcBlendFactor"));
            set => SetFieldValue("srcBlendFactor", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Specifies destination blend factor when blendStyle is set to 'user'.
        /// Possible values: GFXBlendZero, GFXBlendOne, GFXBlendSrcColor, GFXBlendInvSrcColor, GFXBlendSrcAlpha, GFXBlendInvSrcAlpha, GFXBlendDestAlpha, or GFXBlendInvDestAlpha
        /// </description>
        /// </value>
        public GFXBlend DstBlendFactor {
            get => GenericMarshal.StringTo<GFXBlend>(GetFieldValue("dstBlendFactor"));
            set => SetFieldValue("dstBlendFactor", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Selects a texture function that determines how the texture pixels are combined with the shaded color of the billboard's quadrangle geometry.
        /// Possible values: replace, modulate, or add.
        /// </description>
        /// </value>
        public afxBillboard_TexFuncType TextureFunction {
            get => GenericMarshal.StringTo<afxBillboard_TexFuncType>(GetFieldValue("textureFunction"));
            set => SetFieldValue("textureFunction", GenericMarshal.ToString(value));
        }
    }
}