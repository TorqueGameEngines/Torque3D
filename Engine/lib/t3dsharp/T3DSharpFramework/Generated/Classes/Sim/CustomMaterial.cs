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
    /// <summary>Material object which provides more control over surface properties.</summary>
    /// <description>
    /// CustomMaterials allow the user to specify their own shaders via the ShaderData datablock. Because CustomMaterials are derived from Materials, they can hold a lot of the same properties. It is up to the user to code how these properties are used.
    /// </description>
    /// <code>
    /// singleton CustomMaterial( WaterBasicMat )
    /// {
    ///    sampler["reflectMap"] = "$reflectbuff";
    ///    sampler["refractBuff"] = "$backbuff";
    /// 
    ///    cubemap = NewLevelSkyCubemap;
    ///    shader = WaterBasicShader;
    ///    stateBlock = WaterBasicStateBlock;
    ///    version = 2.0;
    /// };
    /// </code>
    /// <see cref="Material, GFXStateBlockData, ShaderData" />
    public unsafe class CustomMaterial : Material {
        public CustomMaterial(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public CustomMaterial(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public CustomMaterial(string pName) 
            : this(pName, false) {
        }
        
        public CustomMaterial(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public CustomMaterial(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public CustomMaterial(SimObject pObj) 
            : base(pObj) {
        }
        
        public CustomMaterial(IntPtr pObj) 
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
                                "fnCustomMaterial_staticGetType"), typeof(_StaticGetType));
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
                                "fnCustomMaterial_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the CustomMaterial class.
        /// </description>
        /// <returns>The type info object for CustomMaterial</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <summary>Specifies pixel shader version for hardware.</summary>
        /// <description>
        /// Valid pixel shader versions include 2.0, 3.0, etc.
        /// </description>
        /// <remarks> All features aren't compatible with all pixel shader versions.</remarks>
        /// </value>
        public float Version {
            get => GenericMarshal.StringTo<float>(GetFieldValue("version"));
            set => SetFieldValue("version", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Alternate material for targeting lower end hardware.</summary>
        /// <description>
        /// If the CustomMaterial requires a higher pixel shader version than the one it's using, it's fallback Material will be processed instead. If the fallback material wasn't defined, Torque 3D will assert and attempt to use a very basic material in it's place.
        /// </description>
        /// </value>
        public Material Fallback {
            get => GenericMarshal.StringTo<Material>(GetFieldValue("fallback"));
            set => SetFieldValue("fallback", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Name of the ShaderData to use for this effect.</summary>
        /// <description>
        /// 
        /// </description>
        /// </value>
        public string Shader {
            get => GenericMarshal.StringTo<string>(GetFieldValue("shader"));
            set => SetFieldValue("shader", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Name of a GFXStateBlockData for this effect.</summary>
        /// <description>
        /// 
        /// </description>
        /// </value>
        public GFXStateBlockData StateBlock {
            get => GenericMarshal.StringTo<GFXStateBlockData>(GetFieldValue("stateBlock"));
            set => SetFieldValue("stateBlock", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>String identifier of this material's target texture.</summary>
        /// </value>
        public string Target {
            get => GenericMarshal.StringTo<string>(GetFieldValue("Target"));
            set => SetFieldValue("Target", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Determines if the material should recieve lights in Basic Lighting. Has no effect in Advanced Lighting.</summary>
        /// <description>
        /// 
        /// </description>
        /// </value>
        public bool ForwardLit {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("forwardLit"));
            set => SetFieldValue("forwardLit", GenericMarshal.ToString(value));
        }
    }
}