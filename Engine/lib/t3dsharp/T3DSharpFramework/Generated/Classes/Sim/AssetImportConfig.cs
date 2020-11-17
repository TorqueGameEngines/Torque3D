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
    /// <summary>Defines properties for an AssetImprotConfig object.</summary>
    /// <description>
    /// 
    /// </description>
    public unsafe class AssetImportConfig : SimObject {
        public AssetImportConfig(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public AssetImportConfig(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public AssetImportConfig(string pName) 
            : this(pName, false) {
        }
        
        public AssetImportConfig(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public AssetImportConfig(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public AssetImportConfig(SimObject pObj) 
            : base(pObj) {
        }
        
        public AssetImportConfig(IntPtr pObj) 
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
                                "fnAssetImportConfig_staticGetType"), typeof(_StaticGetType));
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
                                "fnAssetImportConfig_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct LoadImportConfig__Args
            {
                internal IntPtr configSettings;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string configName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _LoadImportConfig(IntPtr _this, LoadImportConfig__Args args);
            private static _LoadImportConfig _LoadImportConfigFunc;
            internal static _LoadImportConfig LoadImportConfig() {
                if (_LoadImportConfigFunc == null) {
                    _LoadImportConfigFunc =
                        (_LoadImportConfig)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetImportConfig_loadImportConfig"), typeof(_LoadImportConfig));
                }
                
                return _LoadImportConfigFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the AssetImportConfig class.
        /// </description>
        /// <returns>The type info object for AssetImportConfig</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }

        /// <description>
        /// Creates a new script asset using the targetFilePath.
        /// </description>
        /// <returns>The bool result of calling exec</returns>
        public void LoadImportConfig(Settings configSettings = null, string configName = "") {
             InternalUnsafeMethods.LoadImportConfig__Args _args = new InternalUnsafeMethods.LoadImportConfig__Args() {
                configSettings = configSettings.ObjectPtr,
                configName = configName,
             };
             InternalUnsafeMethods.LoadImportConfig()(ObjectPtr, _args);
        }


        /// <value>
        /// <description>
        /// Duplicate Asset Auto-Resolution Action. Options are None, AutoPrune, AutoRename
        /// </description>
        /// </value>
        public string DuplicatAutoResolution {
            get => GenericMarshal.StringTo<string>(GetFieldValue("DuplicatAutoResolution"));
            set => SetFieldValue("DuplicatAutoResolution", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Indicates if warnings should be treated as errors
        /// </description>
        /// </value>
        public bool WarningsAsErrors {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("WarningsAsErrors"));
            set => SetFieldValue("WarningsAsErrors", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Indicates if importing should be prevented from completing if any errors are detected at all
        /// </description>
        /// </value>
        public bool PreventImportWithErrors {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("PreventImportWithErrors"));
            set => SetFieldValue("PreventImportWithErrors", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Should the importer automatically prompt to find missing files if they are not detected automatically by the importer
        /// </description>
        /// </value>
        public bool AutomaticallyPromptMissingFiles {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("AutomaticallyPromptMissingFiles"));
            set => SetFieldValue("AutomaticallyPromptMissingFiles", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Indicates if this config supports importing meshes
        /// </description>
        /// </value>
        public bool ImportMesh {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("ImportMesh"));
            set => SetFieldValue("ImportMesh", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Indicates if this config should override the per-format sis files with the config's specific settings
        /// </description>
        /// </value>
        public bool UseManualShapeConfigRules {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("UseManualShapeConfigRules"));
            set => SetFieldValue("UseManualShapeConfigRules", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Indicates if the up axis in the model file should be overridden
        /// </description>
        /// </value>
        public bool DoUpAxisOverride {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("DoUpAxisOverride"));
            set => SetFieldValue("DoUpAxisOverride", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// If overriding, what axis should be used as up. Options are X_AXIS, Y_AXIS, Z_AXIS
        /// </description>
        /// </value>
        public string UpAxisOverride {
            get => GenericMarshal.StringTo<string>(GetFieldValue("UpAxisOverride"));
            set => SetFieldValue("UpAxisOverride", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Indicates if the scale in the model file should be overridden
        /// </description>
        /// </value>
        public bool DoScaleOverride {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("DoScaleOverride"));
            set => SetFieldValue("DoScaleOverride", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// If overriding, what scale should be used
        /// </description>
        /// </value>
        public float ScaleOverride {
            get => GenericMarshal.StringTo<float>(GetFieldValue("ScaleOverride"));
            set => SetFieldValue("ScaleOverride", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Indicates if scale of nodes should be ignored
        /// </description>
        /// </value>
        public bool IgnoreNodeScale {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("IgnoreNodeScale"));
            set => SetFieldValue("IgnoreNodeScale", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Indicates if the center of the model file should be automatically recentered
        /// </description>
        /// </value>
        public bool AdjustCenter {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("AdjustCenter"));
            set => SetFieldValue("AdjustCenter", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Indicates if the floor height of the model file should be automatically zero'd
        /// </description>
        /// </value>
        public bool AdjustFloor {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("AdjustFloor"));
            set => SetFieldValue("AdjustFloor", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Indicates if submeshes should be collapsed down into a single main mesh
        /// </description>
        /// </value>
        public bool CollapseSubmeshes {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("CollapseSubmeshes"));
            set => SetFieldValue("CollapseSubmeshes", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Indicates what LOD mode the model file should utilize to process out LODs. Options are TrailingNumber, DetectDTS, SingleSize
        /// </description>
        /// </value>
        public string LODType {
            get => GenericMarshal.StringTo<string>(GetFieldValue("LODType"));
            set => SetFieldValue("LODType", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// A list of what nodes should be guaranteed to be imported if found in the model file. Separated by either , or ;
        /// </description>
        /// </value>
        public string ImportedNodes {
            get => GenericMarshal.StringTo<string>(GetFieldValue("ImportedNodes"));
            set => SetFieldValue("ImportedNodes", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// A list of what nodes should be guaranteed to not be imported if found in the model file. Separated by either , or ;
        /// </description>
        /// </value>
        public string IgnoreNodes {
            get => GenericMarshal.StringTo<string>(GetFieldValue("IgnoreNodes"));
            set => SetFieldValue("IgnoreNodes", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// A list of what mesh objects should be guaranteed to be imported if found in the model file. Separated by either , or ;
        /// </description>
        /// </value>
        public string ImportMeshes {
            get => GenericMarshal.StringTo<string>(GetFieldValue("ImportMeshes"));
            set => SetFieldValue("ImportMeshes", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// A list of what mesh objects should be guaranteed to not be imported if found in the model file. Separated by either , or ;
        /// </description>
        /// </value>
        public string IgnoreMeshes {
            get => GenericMarshal.StringTo<string>(GetFieldValue("IgnoreMeshes"));
            set => SetFieldValue("IgnoreMeshes", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Flag to indicate the shape loader should convert to a left-handed coordinate system
        /// </description>
        /// </value>
        public bool ConvertLeftHanded {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("convertLeftHanded"));
            set => SetFieldValue("convertLeftHanded", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Should the shape loader calculate tangent space values
        /// </description>
        /// </value>
        public bool CalcTangentSpace {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("calcTangentSpace"));
            set => SetFieldValue("calcTangentSpace", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Should the shape loader automatically prune redundant/duplicate materials
        /// </description>
        /// </value>
        public bool RemoveRedundantMats {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("removeRedundantMats"));
            set => SetFieldValue("removeRedundantMats", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Should the shape loader auto-generate UV Coordinates for the mesh.
        /// </description>
        /// </value>
        public bool GenUVCoords {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("genUVCoords"));
            set => SetFieldValue("genUVCoords", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Should the UV coordinates be transformed
        /// </description>
        /// </value>
        public bool TransformUVs {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("TransformUVs"));
            set => SetFieldValue("TransformUVs", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Should the UV coordinates be flipped
        /// </description>
        /// </value>
        public bool FlipUVCoords {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("flipUVCoords"));
            set => SetFieldValue("flipUVCoords", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Should the shape loader automatically look for instanced submeshes in the model file
        /// </description>
        /// </value>
        public bool FindInstances {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("findInstances"));
            set => SetFieldValue("findInstances", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Should the shape loader limit the bone weights
        /// </description>
        /// </value>
        public bool LimitBoneWeights {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("limitBoneWeights"));
            set => SetFieldValue("limitBoneWeights", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Should the shape loader automatically merge identical/duplicate verts
        /// </description>
        /// </value>
        public bool JoinIdenticalVerts {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("JoinIdenticalVerts"));
            set => SetFieldValue("JoinIdenticalVerts", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Should the shape loader reverse the winding order of the mesh's face indicies
        /// </description>
        /// </value>
        public bool ReverseWindingOrder {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("reverseWindingOrder"));
            set => SetFieldValue("reverseWindingOrder", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Should the normals on the model be inverted
        /// </description>
        /// </value>
        public bool InvertNormals {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("invertNormals"));
            set => SetFieldValue("invertNormals", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Does this config allow for importing of materials
        /// </description>
        /// </value>
        public bool ImportMaterials {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("ImportMaterials"));
            set => SetFieldValue("ImportMaterials", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// When importing a material, should it automatically attempt to merge Roughness, AO and Metalness maps into a single, composited PBR Configuration map
        /// </description>
        /// </value>
        public bool CreatePBRConfig {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("CreatePBRConfig"));
            set => SetFieldValue("CreatePBRConfig", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// When generating a material off of an importing image, should the importer force appending a diffusemap suffix onto the end to avoid potential naming confusion.
        ///  e.g. MyCoolStuff.png is imported, generating MyCoolStuff material asset and MyCoolStuff_Diffuse image asset
        /// </description>
        /// </value>
        public bool UseDiffuseSuffixOnOriginImage {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("UseDiffuseSuffixOnOriginImage"));
            set => SetFieldValue("UseDiffuseSuffixOnOriginImage", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Should the importer try and use existing material assets in the game directory if at all possible. (Not currently utilized)
        /// </description>
        /// </value>
        public bool UseExistingMaterials {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("UseExistingMaterials"));
            set => SetFieldValue("UseExistingMaterials", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// A list of material names that should not be imported. Separated by either , or ;
        /// </description>
        /// </value>
        public string IgnoreMaterials {
            get => GenericMarshal.StringTo<string>(GetFieldValue("IgnoreMaterials"));
            set => SetFieldValue("IgnoreMaterials", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// When processing a material asset, should the importer attempt to populate the various material maps on it by looking up common naming conventions for potentially relevent image files.
        ///  e.g. If MyCoolStuff_Diffuse.png is imported, generating MyCoolStuff material, it would also find MyCoolStuff_Normal and MyCoolStuff_PBR images and map them to the normal and PBRConfig maps respectively automatically
        /// </description>
        /// </value>
        public bool PopulateMaterialMaps {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("PopulateMaterialMaps"));
            set => SetFieldValue("PopulateMaterialMaps", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Does this config allow for importing Shape Animations
        /// </description>
        /// </value>
        public bool ImportAnimations {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("ImportAnimations"));
            set => SetFieldValue("ImportAnimations", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// When importing a shape file, should the animations within be separated out into unique files
        /// </description>
        /// </value>
        public bool SeparateAnimations {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("SeparateAnimations"));
            set => SetFieldValue("SeparateAnimations", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// If separating animations out from a source file, what prefix should be added to the names for grouping association
        /// </description>
        /// </value>
        public string SeparateAnimationPrefix {
            get => GenericMarshal.StringTo<string>(GetFieldValue("SeparateAnimationPrefix"));
            set => SetFieldValue("SeparateAnimationPrefix", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Defines the animation timing for the given animation sequence. Options are FrameTime, Seconds, Milliseconds
        /// </description>
        /// </value>
        public string AnimTiming {
            get => GenericMarshal.StringTo<string>(GetFieldValue("animTiming"));
            set => SetFieldValue("animTiming", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The FPS of the animation sequence
        /// </description>
        /// </value>
        public bool AnimFPS {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("animFPS"));
            set => SetFieldValue("animFPS", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Does this configuration generate collision geometry when importing. (Not currently enabled)
        /// </description>
        /// </value>
        public bool GenerateCollisions {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("GenerateCollisions"));
            set => SetFieldValue("GenerateCollisions", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// What sort of collision geometry is generated. (Not currently enabled)
        /// </description>
        /// </value>
        public string GenCollisionType {
            get => GenericMarshal.StringTo<string>(GetFieldValue("GenCollisionType"));
            set => SetFieldValue("GenCollisionType", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// What prefix is added to the collision geometry generated. (Not currently enabled)
        /// </description>
        /// </value>
        public string CollisionMeshPrefix {
            get => GenericMarshal.StringTo<string>(GetFieldValue("CollisionMeshPrefix"));
            set => SetFieldValue("CollisionMeshPrefix", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Does this configuration generate Line of Sight collision geometry. (Not currently enabled)
        /// </description>
        /// </value>
        public bool GenerateLOSCollisions {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("GenerateLOSCollisions"));
            set => SetFieldValue("GenerateLOSCollisions", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// What sort of Line of Sight collision geometry is generated. (Not currently enabled)
        /// </description>
        /// </value>
        public string GenLOSCollisionType {
            get => GenericMarshal.StringTo<string>(GetFieldValue("GenLOSCollisionType"));
            set => SetFieldValue("GenLOSCollisionType", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// What prefix is added to the Line of Sight collision geometry generated. (Not currently enabled)
        /// </description>
        /// </value>
        public string LOSCollisionMeshPrefix {
            get => GenericMarshal.StringTo<string>(GetFieldValue("LOSCollisionMeshPrefix"));
            set => SetFieldValue("LOSCollisionMeshPrefix", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Does this configuration support importing images.
        /// </description>
        /// </value>
        public bool ImportImages {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("importImages"));
            set => SetFieldValue("importImages", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// What is the default ImageType images are imported as. Options are: N/A, Diffuse, Normal, Metalness, Roughness, AO, PBRConfig, GUI, Cubemap
        /// </description>
        /// </value>
        public string ImageType {
            get => GenericMarshal.StringTo<string>(GetFieldValue("imageType"));
            set => SetFieldValue("imageType", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// What type of suffixes are scanned to detect if an importing image is a diffuse map. 
        ///  e.g. _Albedo or _Color
        /// </description>
        /// </value>
        public string DiffuseTypeSuffixes {
            get => GenericMarshal.StringTo<string>(GetFieldValue("DiffuseTypeSuffixes"));
            set => SetFieldValue("DiffuseTypeSuffixes", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// What type of suffixes are scanned to detect if an importing image is a normal map. 
        ///  e.g. _Normal or _Norm
        /// </description>
        /// </value>
        public string NormalTypeSuffixes {
            get => GenericMarshal.StringTo<string>(GetFieldValue("NormalTypeSuffixes"));
            set => SetFieldValue("NormalTypeSuffixes", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// What type of suffixes are scanned to detect if an importing image is a metalness map. 
        ///  e.g. _Metalness or _Metal
        /// </description>
        /// </value>
        public string MetalnessTypeSuffixes {
            get => GenericMarshal.StringTo<string>(GetFieldValue("MetalnessTypeSuffixes"));
            set => SetFieldValue("MetalnessTypeSuffixes", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// What type of suffixes are scanned to detect if an importing image is a roughness map.
        ///  e.g. _roughness or _rough
        /// </description>
        /// </value>
        public string RoughnessTypeSuffixes {
            get => GenericMarshal.StringTo<string>(GetFieldValue("RoughnessTypeSuffixes"));
            set => SetFieldValue("RoughnessTypeSuffixes", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// What type of suffixes are scanned to detect if an importing image is a smoothness map. 
        ///  e.g. _smoothness or _smooth
        /// </description>
        /// </value>
        public string SmoothnessTypeSuffixes {
            get => GenericMarshal.StringTo<string>(GetFieldValue("SmoothnessTypeSuffixes"));
            set => SetFieldValue("SmoothnessTypeSuffixes", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// What type of suffixes are scanned to detect if an importing image is a ambient occlusion map. 
        ///  e.g. _ambient or _ao
        /// </description>
        /// </value>
        public string AOTypeSuffixes {
            get => GenericMarshal.StringTo<string>(GetFieldValue("AOTypeSuffixes"));
            set => SetFieldValue("AOTypeSuffixes", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// What type of suffixes are scanned to detect if an importing image is a PBRConfig map.
        ///  e.g. _Composite or _PBR
        /// </description>
        /// </value>
        public string PBRTypeSuffixes {
            get => GenericMarshal.StringTo<string>(GetFieldValue("PBRTypeSuffixes"));
            set => SetFieldValue("PBRTypeSuffixes", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Indicates what filter mode images imported with this configuration utilizes. Options are Linear, Bilinear, Trilinear
        /// </description>
        /// </value>
        public string TextureFilteringMode {
            get => GenericMarshal.StringTo<string>(GetFieldValue("TextureFilteringMode"));
            set => SetFieldValue("TextureFilteringMode", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Indicates if images imported with this configuration utilize mipmaps
        /// </description>
        /// </value>
        public bool UseMips {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("UseMips"));
            set => SetFieldValue("UseMips", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Indicates if images imported with this configuration are in an HDR format
        /// </description>
        /// </value>
        public bool IsHDR {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("IsHDR"));
            set => SetFieldValue("IsHDR", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Indicates what amount of scaling images imported with this configuration use
        /// </description>
        /// </value>
        public float Scaling {
            get => GenericMarshal.StringTo<float>(GetFieldValue("Scaling"));
            set => SetFieldValue("Scaling", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Indicates if images imported with this configuration are compressed
        /// </description>
        /// </value>
        public bool ImagesCompressed {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("ImagesCompressed"));
            set => SetFieldValue("ImagesCompressed", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Indicates if images imported with this configuration generate a parent material for it as well
        /// </description>
        /// </value>
        public bool GenerateMaterialOnImport {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("GenerateMaterialOnImport"));
            set => SetFieldValue("GenerateMaterialOnImport", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Indicates if sounds are imported with this configuration
        /// </description>
        /// </value>
        public bool ImportSounds {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("importSounds"));
            set => SetFieldValue("importSounds", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Indicates what amount the volume is adjusted on sounds imported with this configuration
        /// </description>
        /// </value>
        public float VolumeAdjust {
            get => GenericMarshal.StringTo<float>(GetFieldValue("VolumeAdjust"));
            set => SetFieldValue("VolumeAdjust", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Indicates what amount the pitch is adjusted on sounds imported with this configuration
        /// </description>
        /// </value>
        public float PitchAdjust {
            get => GenericMarshal.StringTo<float>(GetFieldValue("PitchAdjust"));
            set => SetFieldValue("PitchAdjust", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Indicates if sounds imported with this configuration are compressed
        /// </description>
        /// </value>
        public bool SoundsCompressed {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("SoundsCompressed"));
            set => SetFieldValue("SoundsCompressed", GenericMarshal.ToString(value));
        }
    }
}