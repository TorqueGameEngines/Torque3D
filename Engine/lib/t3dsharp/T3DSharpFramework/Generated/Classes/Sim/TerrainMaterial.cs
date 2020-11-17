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
    /// <summary>The TerrainMaterial class orginizes the material settings for a single terrain material layer.</summary>
    /// <description>
    /// 
    /// </description>
    /// <remarks> You should not be creating TerrainMaterials by hand in code. All TerrainMaterials should be created in the editors, as intended by the system.
    /// 
    /// </remarks>
    /// <code>
    /// // Created by the Terrain Painter tool in the World Editor
    /// new TerrainMaterial()
    /// {
    /// 	internalName = "grass1";
    /// 	diffuseMap = "art/terrains/Test/grass1";
    /// 	detailMap = "art/terrains/Test/grass1_d";
    /// 	detailSize = "10";
    /// 	isManaged = "1";
    /// 	detailBrightness = "1";
    /// 	Enabled = "1";
    /// 	diffuseSize = "200";
    /// };
    /// </code>
    /// <see cref="Materials" />
    public unsafe class TerrainMaterial : SimObject {
        public TerrainMaterial(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public TerrainMaterial(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public TerrainMaterial(string pName) 
            : this(pName, false) {
        }
        
        public TerrainMaterial(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public TerrainMaterial(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public TerrainMaterial(SimObject pObj) 
            : base(pObj) {
        }
        
        public TerrainMaterial(IntPtr pObj) 
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
                                "fnTerrainMaterial_staticGetType"), typeof(_StaticGetType));
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
                                "fnTerrainMaterial_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the TerrainMaterial class.
        /// </description>
        /// <returns>The type info object for TerrainMaterial</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// ,yrđ
        /// </description>
        /// </value>
        public string DiffuseMap {
            get => GenericMarshal.StringTo<string>(GetFieldValue("DiffuseMap"));
            set => SetFieldValue("DiffuseMap", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// ,yrđ
        /// </description>
        /// </value>
        public string DiffuseMapAsset {
            get => GenericMarshal.StringTo<string>(GetFieldValue("DiffuseMapAsset"));
            set => SetFieldValue("DiffuseMapAsset", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Used to scale the diffuse map to the material square
        /// </description>
        /// </value>
        public float DiffuseSize {
            get => GenericMarshal.StringTo<float>(GetFieldValue("diffuseSize"));
            set => SetFieldValue("diffuseSize", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Bump map for the material
        /// </description>
        /// </value>
        public string NormalMap {
            get => GenericMarshal.StringTo<string>(GetFieldValue("normalMap"));
            set => SetFieldValue("normalMap", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Detail map for the material
        /// </description>
        /// </value>
        public string DetailMap {
            get => GenericMarshal.StringTo<string>(GetFieldValue("detailMap"));
            set => SetFieldValue("detailMap", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Used to scale the detail map to the material square
        /// </description>
        /// </value>
        public float DetailSize {
            get => GenericMarshal.StringTo<float>(GetFieldValue("detailSize"));
            set => SetFieldValue("detailSize", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Exponentially sharpens or lightens the detail map rendering on the material
        /// </description>
        /// </value>
        public float DetailStrength {
            get => GenericMarshal.StringTo<float>(GetFieldValue("detailStrength"));
            set => SetFieldValue("detailStrength", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Changes how far camera can see the detail map rendering on the material
        /// </description>
        /// </value>
        public float DetailDistance {
            get => GenericMarshal.StringTo<float>(GetFieldValue("detailDistance"));
            set => SetFieldValue("detailDistance", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Makes that terrain material project along the sides of steep slopes instead of projected downwards
        /// </description>
        /// </value>
        public bool UseSideProjection {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("useSideProjection"));
            set => SetFieldValue("useSideProjection", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Macro map for the material
        /// </description>
        /// </value>
        public string MacroMap {
            get => GenericMarshal.StringTo<string>(GetFieldValue("macroMap"));
            set => SetFieldValue("macroMap", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Used to scale the Macro map to the material square
        /// </description>
        /// </value>
        public float MacroSize {
            get => GenericMarshal.StringTo<float>(GetFieldValue("macroSize"));
            set => SetFieldValue("macroSize", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Exponentially sharpens or lightens the Macro map rendering on the material
        /// </description>
        /// </value>
        public float MacroStrength {
            get => GenericMarshal.StringTo<float>(GetFieldValue("macroStrength"));
            set => SetFieldValue("macroStrength", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Changes how far camera can see the Macro map rendering on the material
        /// </description>
        /// </value>
        public float MacroDistance {
            get => GenericMarshal.StringTo<float>(GetFieldValue("macroDistance"));
            set => SetFieldValue("macroDistance", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Used to scale the height from the normal map to give some self occlusion effect (aka parallax) to the terrain material
        /// </description>
        /// </value>
        public float ParallaxScale {
            get => GenericMarshal.StringTo<float>(GetFieldValue("parallaxScale"));
            set => SetFieldValue("parallaxScale", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Composite map for the PBR Configuration of the material
        /// </description>
        /// </value>
        public string PbrConfigMap {
            get => GenericMarshal.StringTo<string>(GetFieldValue("pbrConfigMap"));
            set => SetFieldValue("pbrConfigMap", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Is the PBR Config map's image in sRGB format?
        /// </description>
        /// </value>
        public bool IsSRGB {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("isSRGB"));
            set => SetFieldValue("isSRGB", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Should the smoothness channel of the PBR Config map be inverted?
        /// </description>
        /// </value>
        public bool InvertSmoothness {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("invertSmoothness"));
            set => SetFieldValue("invertSmoothness", GenericMarshal.ToString(value));
        }
    }
}