#include "assetImporter.h"
#include "assetImporter_ScriptBinding.h"
#include "core/strings/findMatch.h"
#include "ImageAsset.h"
#include "ShapeAsset.h"
#include "SoundAsset.h"
#include "MaterialAsset.h"
#include "ShapeAnimationAsset.h"

#include "ts/collada/colladaUtils.h"
#include "ts/collada/colladaAppNode.h"
#include "ts/collada/colladaShapeLoader.h"

#include "ts/assimp/assimpShapeLoader.h"
#include "ts/tsShapeConstruct.h"
#include "core/resourceManager.h"

#include "materials/materialManager.h"

#include "console/persistenceManager.h"
#include "core/util/timeClass.h"

ConsoleDocClass(AssetImportConfig,
   "@brief Defines properties for an AssetImprotConfig object.\n"
   "@AssetImportConfig is a SimObject derived object intended to act as a container for all the necessary configuration data when running the Asset Importer.\n"
   "@It dictates if and how any given asset type will be processed when running an import action. This is because the Asset Importer utilizes a lot of informed logic\n"
   "@to try and automate as much of the import process as possible. In theory, you would run the import on a given file, and based on your config the importer will do\n"
   "@everything from importing the designated file, as well as finding and importing any associated files such as images or materials, and prepping the objects at time\n"
   "@of import to avoid as much manual post-processing as possible.\n\n"
   "@ingroup Assets\n"
);

IMPLEMENT_CONOBJECT(AssetImportConfig);

AssetImportConfig::AssetImportConfig() :
   DuplicateAutoResolution("AutoRename"),
   WarningsAsErrors(false),
   PreventImportWithErrors(true),
   AutomaticallyPromptMissingFiles(false),
   AddDirectoryPrefixToAssetName(false),
   ImportMesh(true),
   AlwaysAddShapeSuffix(false),
   AddedShapeSuffix("_shape"),
   UseManualShapeConfigRules(false),
   DoUpAxisOverride(false),
   UpAxisOverride("Z_AXIS"),
   DoScaleOverride(false),
   ScaleOverride(false),
   IgnoreNodeScale(false),
   AdjustCenter(false),
   AdjustFloor(false),
   CollapseSubmeshes(false),
   LODType("TrailingNumber"),
   AlwaysImportedNodes(""),
   AlwaysIgnoreNodes(""),
   AlwaysImportMeshes(""),
   AlwaysIgnoreMeshes(""),
   convertLeftHanded(false),
   calcTangentSpace(false),
   removeRedundantMats(false),
   genUVCoords(false),
   TransformUVs(false),
   flipUVCoords(false),
   findInstances(false),
   limitBoneWeights(false),
   JoinIdenticalVerts(false),
   reverseWindingOrder(false),
   invertNormals(false),
   ImportMaterials(true),
   AlwaysAddMaterialSuffix(true),
   AddedMaterialSuffix("_mat"),
   CreateORMConfig(true),
   UseDiffuseSuffixOnOriginImage(false),
   UseExistingMaterials(false),
   IgnoreMaterials(""),
   PopulateMaterialMaps(true),
   ImportAnimations(true),
   SeparateAnimations(false),
   SeparateAnimationPrefix(""),
   animTiming("FrameCount"),
   animFPS(false),
   AlwaysAddShapeAnimationSuffix(true),
   AddedShapeAnimationSuffix("_anim"),
   GenerateCollisions(false),
   GenCollisionType(""),
   CollisionMeshPrefix(""),
   GenerateLOSCollisions(false),
   GenLOSCollisionType(""),
   LOSCollisionMeshPrefix(""),
   importImages(true),
   AlwaysAddImageSuffix(true),
   AddedImageSuffix("_image"),
   ImageType("GUI"),
   DiffuseTypeSuffixes("_ALBEDO,_DIFFUSE,_ALB,_DIF,_COLOR,_COL,_A,_C,-ALBEDO,-DIFFUSE,-ALB,-DIF,-COLOR,-COL,-A,-C"),
   NormalTypeSuffixes("_NORMAL,_NORM,_N,-NORMAL,-NORM,-N"),
   MetalnessTypeSuffixes("_METAL,_MET,_METALNESS,_METALLIC,_M,-METAL,-MET,-METALNESS,-METALLIC,-M"),
   RoughnessTypeSuffixes("_ROUGH,_ROUGHNESS,_R,-ROUGH,-ROUGHNESS,-R"),
   SmoothnessTypeSuffixes("_SMOOTH,_SMOOTHNESS,_S,-SMOOTH,-SMOOTHNESS,-S"),
   AOTypeSuffixes("_AO,_AMBIENT,_AMBIENTOCCLUSION,-AO,-AMBIENT,-AMBIENTOCCLUSION"),
   PBRTypeSuffixes("_COMP,_COMPOSITE,_PBR,-COMP,-COMPOSITE,-PBR,_ORM,-ORM"),
   TextureFilteringMode("Bilinear"),
   UseMips(true),
   IsHDR(false),
   Scaling(false),
   ImagesCompressed(false),
   GenerateMaterialOnImport(true),
   importSounds(true),
   VolumeAdjust(false),
   PitchAdjust(false),
   SoundsCompressed(false),
   AlwaysAddSoundSuffix(false),
   AddedSoundSuffix("_sound")
{
}

AssetImportConfig::~AssetImportConfig()
{

}

bool AssetImportConfig::onAdd()
{
   if (!Parent::onAdd())
      return false;

   return true;
}

void AssetImportConfig::onRemove()
{
   Parent::onRemove();
}

/// Engine.
void AssetImportConfig::initPersistFields()
{
   docsURL;
   Parent::initPersistFields();

   addGroup("General");
      addField("DuplicateAutoResolution", TypeRealString, Offset(DuplicateAutoResolution, AssetImportConfig), "Duplicate Asset Auto-Resolution Action. Options are None, AutoPrune, AutoRename, FolderPrefix");
      addField("WarningsAsErrors", TypeBool, Offset(WarningsAsErrors, AssetImportConfig), "Indicates if warnings should be treated as errors");
      addField("PreventImportWithErrors", TypeBool, Offset(PreventImportWithErrors, AssetImportConfig), "Indicates if importing should be prevented from completing if any errors are detected at all");
      addField("AutomaticallyPromptMissingFiles", TypeBool, Offset(AutomaticallyPromptMissingFiles, AssetImportConfig), "Should the importer automatically prompt to find missing files if they are not detected automatically by the importer");
      addField("AddDirectoryPrefixToAssetName", TypeBool, Offset(AddDirectoryPrefixToAssetName, AssetImportConfig), "Should the importer add the folder name as a prefix to the assetName. Helps prevent name collisions.");   
   endGroup("General");

   addGroup("Meshes");
      addField("ImportMesh", TypeBool, Offset(ImportMesh, AssetImportConfig), "Indicates if this config supports importing meshes");
      addField("AlwaysAddShapeSuffix", TypeBool, Offset(AlwaysAddShapeSuffix, AssetImportConfig), "When importing a shape, this indicates if it should automatically add a standard suffix onto the name");
      addField("AddedShapeSuffix", TypeString, Offset(AddedShapeSuffix, AssetImportConfig), " If AlwaysAddShapeSuffix is on, this is the suffix to be added");
      addField("UseManualShapeConfigRules", TypeBool, Offset(UseManualShapeConfigRules, AssetImportConfig), "Indicates if this config should override the per-format sis files with the config's specific settings");
      addField("DoUpAxisOverride", TypeBool, Offset(DoUpAxisOverride, AssetImportConfig), "Indicates if the up axis in the model file should be overridden");
      addField("UpAxisOverride", TypeRealString, Offset(UpAxisOverride, AssetImportConfig), "If overriding, what axis should be used as up. Options are X_AXIS, Y_AXIS, Z_AXIS");
      addField("DoScaleOverride", TypeBool, Offset(DoScaleOverride, AssetImportConfig), "Indicates if the scale in the model file should be overridden");
      addField("ScaleOverride", TypeF32, Offset(ScaleOverride, AssetImportConfig), "If overriding, what scale should be used");
      addField("IgnoreNodeScale", TypeBool, Offset(IgnoreNodeScale, AssetImportConfig), "Indicates if scale of nodes should be ignored");
      addField("AdjustCenter", TypeBool, Offset(AdjustCenter, AssetImportConfig), "Indicates if the center of the model file should be automatically recentered");
      addField("AdjustFloor", TypeBool, Offset(AdjustFloor, AssetImportConfig), "Indicates if the floor height of the model file should be automatically zero'd");
      addField("CollapseSubmeshes", TypeBool, Offset(CollapseSubmeshes, AssetImportConfig), "Indicates if submeshes should be collapsed down into a single main mesh");
      addField("LODType", TypeRealString, Offset(LODType, AssetImportConfig), "Indicates what LOD mode the model file should utilize to process out LODs. Options are TrailingNumber, DetectDTS, SingleSize");
      addField("AlwaysImportedNodes", TypeRealString, Offset(AlwaysImportedNodes, AssetImportConfig), " A list of what nodes should be guaranteed to be imported if found in the model file. Separated by either , or ;");
      addField("AlwaysIgnoreNodes", TypeRealString, Offset(AlwaysIgnoreNodes, AssetImportConfig), "A list of what nodes should be guaranteed to not be imported if found in the model file. Separated by either , or ;");
      addField("AlwaysImportMeshes", TypeRealString, Offset(AlwaysImportMeshes, AssetImportConfig), "A list of what mesh objects should be guaranteed to be imported if found in the model file. Separated by either , or ;");
      addField("AlwaysIgnoreMeshes", TypeRealString, Offset(AlwaysIgnoreMeshes, AssetImportConfig), "A list of what mesh objects should be guaranteed to not be imported if found in the model file. Separated by either , or ;");
      addField("convertLeftHanded", TypeBool, Offset(convertLeftHanded, AssetImportConfig), "Flag to indicate the shape loader should convert to a left-handed coordinate system");
      addField("calcTangentSpace", TypeBool, Offset(calcTangentSpace, AssetImportConfig), "Should the shape loader calculate tangent space values");
      addField("removeRedundantMats", TypeBool, Offset(removeRedundantMats, AssetImportConfig), "Should the shape loader automatically prune redundant/duplicate materials");
      addField("genUVCoords", TypeBool, Offset(genUVCoords, AssetImportConfig), "Should the shape loader auto-generate UV Coordinates for the mesh.");
      addField("TransformUVs", TypeBool, Offset(TransformUVs, AssetImportConfig), "Should the UV coordinates be transformed");
      addField("flipUVCoords", TypeBool, Offset(flipUVCoords, AssetImportConfig), "Should the UV coordinates be flipped");
      addField("findInstances", TypeBool, Offset(findInstances, AssetImportConfig), "Should the shape loader automatically look for instanced submeshes in the model file");
      addField("limitBoneWeights", TypeBool, Offset(limitBoneWeights, AssetImportConfig), "Should the shape loader limit the bone weights");
      addField("JoinIdenticalVerts", TypeBool, Offset(JoinIdenticalVerts, AssetImportConfig), "Should the shape loader automatically merge identical/duplicate verts");
      addField("reverseWindingOrder", TypeBool, Offset(reverseWindingOrder, AssetImportConfig), "Should the shape loader reverse the winding order of the mesh's face indicies");
      addField("invertNormals", TypeBool, Offset(invertNormals, AssetImportConfig), "Should the normals on the model be inverted");
   endGroup("Meshes");

   addGroup("Materials");
      addField("ImportMaterials", TypeBool, Offset(ImportMaterials, AssetImportConfig), "Does this config allow for importing of materials");
      addField("AlwaysAddMaterialSuffix", TypeBool, Offset(AlwaysAddMaterialSuffix, AssetImportConfig), "When importing a material, this indicates if it should automatically add a standard suffix onto the name");
      addField("AddedMaterialSuffix", TypeString, Offset(AddedMaterialSuffix, AssetImportConfig), " If AlwaysAddMaterialSuffix is on, this is the suffix to be added");
      addField("CreateORMConfig", TypeBool, Offset(PreventImportWithErrors, AssetImportConfig), "When importing a material, should it automatically attempt to merge Roughness, AO and Metalness maps into a single, composited PBR Configuration map");
      addField("UseDiffuseSuffixOnOriginImage", TypeBool, Offset(UseDiffuseSuffixOnOriginImage, AssetImportConfig), "When generating a material off of an importing image, should the importer force appending a diffusemap suffix onto the end to avoid potential naming confusion.\n e.g. MyCoolStuff.png is imported, generating MyCoolStuff material asset and MyCoolStuff_Diffuse image asset");
      addField("UseExistingMaterials", TypeBool, Offset(UseExistingMaterials, AssetImportConfig), "Should the importer try and use existing material assets in the game directory if at all possible. (Not currently utilized)");
      addField("IgnoreMaterials", TypeRealString, Offset(IgnoreMaterials, AssetImportConfig), "A list of material names that should not be imported. Separated by either , or ;");
      addField("PopulateMaterialMaps", TypeBool, Offset(PopulateMaterialMaps, AssetImportConfig), "When processing a material asset, should the importer attempt to populate the various material maps on it by looking up common naming conventions for potentially relevent image files.\n e.g. If MyCoolStuff_Diffuse.png is imported, generating MyCoolStuff material, it would also find MyCoolStuff_Normal and MyCoolStuff_PBR images and map them to the normal and ORMConfig maps respectively automatically");
   endGroup("Materials");

   addGroup("Animation");
      addField("ImportAnimations", TypeBool, Offset(ImportAnimations, AssetImportConfig), "Does this config allow for importing Shape Animations");
      addField("SeparateAnimations", TypeBool, Offset(SeparateAnimations, AssetImportConfig), "When importing a shape file, should the animations within be separated out into unique files");
      addField("SeparateAnimationPrefix", TypeRealString, Offset(SeparateAnimationPrefix, AssetImportConfig), "If separating animations out from a source file, what prefix should be added to the names for grouping association");
      addField("animTiming", TypeRealString, Offset(animTiming, AssetImportConfig), "Defines the animation timing for the given animation sequence. Options are FrameTime, Seconds, Milliseconds");
      addField("animFPS", TypeBool, Offset(animFPS, AssetImportConfig), "The FPS of the animation sequence");
      addField("AlwaysAddShapeAnimationSuffix", TypeBool, Offset(AlwaysAddShapeAnimationSuffix, AssetImportConfig), "When importing a shape animation, this indicates if it should automatically add a standard suffix onto the name");
      addField("AddedShapeAnimationSuffix", TypeString, Offset(AddedShapeAnimationSuffix, AssetImportConfig), " If AlwaysAddShapeAnimationSuffix is on, this is the suffix to be added");
   endGroup("Animation");

   addGroup("Collision");
      addField("GenerateCollisions", TypeBool, Offset(GenerateCollisions, AssetImportConfig), "Does this configuration generate collision geometry when importing. (Not currently enabled)");
      addField("GenCollisionType", TypeRealString, Offset(GenCollisionType, AssetImportConfig), "What sort of collision geometry is generated. (Not currently enabled)");
      addField("CollisionMeshPrefix", TypeRealString, Offset(CollisionMeshPrefix, AssetImportConfig), "What prefix is added to the collision geometry generated. (Not currently enabled)");
      addField("GenerateLOSCollisions", TypeBool, Offset(GenerateLOSCollisions, AssetImportConfig), "Does this configuration generate Line of Sight collision geometry. (Not currently enabled)");
      addField("GenLOSCollisionType", TypeRealString, Offset(GenLOSCollisionType, AssetImportConfig), "What sort of Line of Sight collision geometry is generated. (Not currently enabled)");
      addField("LOSCollisionMeshPrefix", TypeRealString, Offset(LOSCollisionMeshPrefix, AssetImportConfig), "What prefix is added to the Line of Sight collision geometry generated. (Not currently enabled)");
   endGroup("Collision");

   addGroup("Images");
      addField("importImages", TypeBool, Offset(importImages, AssetImportConfig), "Does this configuration support importing images.");
      addField("AlwaysAddImageSuffix", TypeBool, Offset(AlwaysAddImageSuffix, AssetImportConfig), "When importing an image, this indicates if it should automatically add a standard suffix onto the name");
      addField("AddedImageSuffix", TypeString, Offset(AddedImageSuffix, AssetImportConfig), " If AlwaysAddImageSuffix is on, this is the suffix to be added");
      addField("ImageType", TypeRealString, Offset(ImageType, AssetImportConfig), "What is the default ImageType images are imported as. Options are: N/A, Diffuse, Normal, Metalness, Roughness, AO, ORMConfig, GUI, Cubemap");
      addField("DiffuseTypeSuffixes", TypeRealString, Offset(DiffuseTypeSuffixes, AssetImportConfig), "What type of suffixes are scanned to detect if an importing image is a diffuse map. \n e.g. _Albedo or _Color");
      addField("NormalTypeSuffixes", TypeRealString, Offset(NormalTypeSuffixes, AssetImportConfig), "What type of suffixes are scanned to detect if an importing image is a normal map. \n e.g. _Normal or _Norm");
      addField("MetalnessTypeSuffixes", TypeRealString, Offset(MetalnessTypeSuffixes, AssetImportConfig), "What type of suffixes are scanned to detect if an importing image is a metalness map. \n e.g. _Metalness or _Metal");
      addField("RoughnessTypeSuffixes", TypeRealString, Offset(RoughnessTypeSuffixes, AssetImportConfig), "What type of suffixes are scanned to detect if an importing image is a roughness map.\n e.g. _roughness or _rough");
      addField("SmoothnessTypeSuffixes", TypeRealString, Offset(SmoothnessTypeSuffixes, AssetImportConfig), "What type of suffixes are scanned to detect if an importing image is a smoothness map. \n e.g. _smoothness or _smooth");
      addField("AOTypeSuffixes", TypeRealString, Offset(AOTypeSuffixes, AssetImportConfig), "What type of suffixes are scanned to detect if an importing image is a ambient occlusion map. \n e.g. _ambient or _ao");
      addField("PBRTypeSuffixes", TypeRealString, Offset(PBRTypeSuffixes, AssetImportConfig), "What type of suffixes are scanned to detect if an importing image is a ORMConfig map.\n e.g. _Composite or _PBR");
      addField("TextureFilteringMode", TypeRealString, Offset(TextureFilteringMode, AssetImportConfig), "Indicates what filter mode images imported with this configuration utilizes. Options are Linear, Bilinear, Trilinear");
      addField("UseMips", TypeBool, Offset(UseMips, AssetImportConfig), "Indicates if images imported with this configuration utilize mipmaps");

      addField("IsHDR", TypeBool, Offset(IsHDR, AssetImportConfig), "Indicates if images imported with this configuration are in an HDR format");
      addField("Scaling", TypeF32, Offset(Scaling, AssetImportConfig), "Indicates what amount of scaling images imported with this configuration use");
      addField("ImagesCompressed", TypeBool, Offset(ImagesCompressed, AssetImportConfig), "Indicates if images imported with this configuration are compressed");
      addField("GenerateMaterialOnImport", TypeBool, Offset(GenerateMaterialOnImport, AssetImportConfig), "Indicates if images imported with this configuration generate a parent material for it as well");
   endGroup("Images");

   addGroup("Sounds");
      addField("importSounds", TypeBool, Offset(importSounds, AssetImportConfig), "Indicates if sounds are imported with this configuration");
      addField("VolumeAdjust", TypeF32, Offset(VolumeAdjust, AssetImportConfig), "Indicates what amount the volume is adjusted on sounds imported with this configuration");
      addField("PitchAdjust", TypeF32, Offset(PitchAdjust, AssetImportConfig), "Indicates what amount the pitch is adjusted on sounds imported with this configuration");
      addField("SoundsCompressed", TypeBool, Offset(SoundsCompressed, AssetImportConfig), "Indicates if sounds imported with this configuration are compressed");
   endGroup("Sounds");
}

void AssetImportConfig::loadImportConfig(Settings* configSettings, String configName)
{
   //General
   DuplicateAutoResolution = configSettings->value(String(configName + "/General/DuplicateAutoResolution").c_str());
   WarningsAsErrors = dAtob(configSettings->value(String(configName + "/General/WarningsAsErrors").c_str()));
   PreventImportWithErrors = dAtob(configSettings->value(String(configName + "/General/PreventImportWithErrors").c_str()));
   AutomaticallyPromptMissingFiles = dAtob(configSettings->value(String(configName + "/General/AutomaticallyPromptMissingFiles").c_str()));
   AddDirectoryPrefixToAssetName = dAtob(configSettings->value(String(configName + "/General/AddDirectoryPrefixToAssetName").c_str()));

   //Meshes
   ImportMesh = dAtob(configSettings->value(String(configName + "/Meshes/ImportMesh").c_str()));
   AlwaysAddShapeSuffix = dAtob(configSettings->value(String(configName + "/Meshes/AlwaysAddShapeSuffix").c_str()));
   AddedShapeSuffix = configSettings->value(String(configName + "/Meshes/AddedShapeSuffix").c_str());
   UseManualShapeConfigRules = dAtob(configSettings->value(String(configName + "/Meshes/UseManualShapeConfigRules").c_str()));
   DoUpAxisOverride = dAtob(configSettings->value(String(configName + "/Meshes/DoUpAxisOverride").c_str()));
   UpAxisOverride = configSettings->value(String(configName + "/Meshes/UpAxisOverride").c_str());
   DoScaleOverride = dAtob(configSettings->value(String(configName + "/Meshes/DoScaleOverride").c_str()));
   ScaleOverride = dAtof(configSettings->value(String(configName + "/Meshes/ScaleOverride").c_str()));
   IgnoreNodeScale = dAtob(configSettings->value(String(configName + "/Meshes/IgnoreNodeScale").c_str()));
   AdjustCenter = dAtob(configSettings->value(String(configName + "/Meshes/AdjustCenter").c_str()));
   AdjustFloor = dAtob(configSettings->value(String(configName + "/Meshes/AdjustFloor").c_str()));
   CollapseSubmeshes = dAtob(configSettings->value(String(configName + "/Meshes/CollapseSubmeshes").c_str()));
   LODType = configSettings->value(String(configName + "/Meshes/LODType").c_str());
   AlwaysImportedNodes = configSettings->value(String(configName + "/Meshes/AlwaysImportedNodes").c_str());
   AlwaysIgnoreNodes = configSettings->value(String(configName + "/Meshes/AlwaysIgnoreNodes").c_str());
   AlwaysImportMeshes = configSettings->value(String(configName + "/Meshes/AlwaysImportMeshes").c_str());
   AlwaysIgnoreMeshes = configSettings->value(String(configName + "/Meshes/AlwaysIgnoreMeshes").c_str());

   //Assimp/Collada
   convertLeftHanded = dAtob(configSettings->value(String(configName + "/Meshes/convertLeftHanded").c_str()));
   calcTangentSpace = dAtob(configSettings->value(String(configName + "/Meshes/calcTangentSpace").c_str()));
   removeRedundantMats = dAtob(configSettings->value(String(configName + "/Meshes/removeRedundantMats").c_str()));
   genUVCoords = dAtob(configSettings->value(String(configName + "/Meshes/genUVCoords").c_str()));
   TransformUVs = dAtob(configSettings->value(String(configName + "/Meshes/TransformUVs").c_str()));
   flipUVCoords = dAtob(configSettings->value(String(configName + "/Meshes/flipUVCoords").c_str()));
   findInstances = dAtob(configSettings->value(String(configName + "/Meshes/findInstances").c_str()));
   limitBoneWeights = dAtob(configSettings->value(String(configName + "/Meshes/limitBoneWeights").c_str()));
   JoinIdenticalVerts = dAtob(configSettings->value(String(configName + "/Meshes/JoinIdenticalVerts").c_str()));
   reverseWindingOrder = dAtob(configSettings->value(String(configName + "/Meshes/reverseWindingOrder").c_str()));
   invertNormals = dAtob(configSettings->value(String(configName + "/Meshes/invertNormals").c_str()));

   //Materials
   ImportMaterials = dAtob(configSettings->value(String(configName + "/Materials/ImportMaterials").c_str()));
   AlwaysAddMaterialSuffix = dAtob(configSettings->value(String(configName + "/Materials/AlwaysAddMaterialSuffix").c_str()));
   AddedMaterialSuffix = configSettings->value(String(configName + "/Materials/AddedMaterialSuffix").c_str());
   CreateORMConfig = dAtob(configSettings->value(String(configName + "/Materials/CreateORMConfig").c_str()));
   UseDiffuseSuffixOnOriginImage = dAtob(configSettings->value(String(configName + "/Materials/UseDiffuseSuffixOnOriginImage").c_str()));
   UseExistingMaterials = dAtob(configSettings->value(String(configName + "/Materials/UseExistingMaterials").c_str()));
   IgnoreMaterials = configSettings->value(String(configName + "/Materials/IgnoreMaterials").c_str());
   PopulateMaterialMaps = dAtob(configSettings->value(String(configName + "/Materials/PopulateMaterialMaps").c_str()));

   //Animations
   ImportAnimations = dAtob(configSettings->value(String(configName + "/Animations/ImportAnimations").c_str()));
   SeparateAnimations = dAtob(configSettings->value(String(configName + "/Animations/SeparateAnimations").c_str()));
   SeparateAnimationPrefix = configSettings->value(String(configName + "/Animations/SeparateAnimationPrefix").c_str());
   animTiming = configSettings->value(String(configName + "/Animations/animTiming").c_str());
   animFPS = dAtof(configSettings->value(String(configName + "/Animations/animFPS").c_str()));
   AlwaysAddShapeAnimationSuffix = dAtob(configSettings->value(String(configName + "/Animations/AlwaysAddShapeAnimationSuffix").c_str()));
   AddedShapeAnimationSuffix = configSettings->value(String(configName + "/Animations/AddedShapeAnimationSuffix").c_str());

   //Collisions
   GenerateCollisions = dAtob(configSettings->value(String(configName + "/Collision/GenerateCollisions").c_str()));
   GenCollisionType = configSettings->value(String(configName + "/Collision/GenCollisionType").c_str());
   CollisionMeshPrefix = configSettings->value(String(configName + "/Collision/CollisionMeshPrefix").c_str());
   GenerateLOSCollisions = dAtob(configSettings->value(String(configName + "/Collision/GenerateLOSCollisions").c_str()));
   GenLOSCollisionType = configSettings->value(String(configName + "/Collision/GenLOSCollisionType").c_str());
   LOSCollisionMeshPrefix = configSettings->value(String(configName + "/Collision/LOSCollisionMeshPrefix").c_str());

   //Images
   importImages = dAtob(configSettings->value(String(configName + "/Images/importImages").c_str()));
   AlwaysAddImageSuffix = dAtob(configSettings->value(String(configName + "/Images/AlwaysAddImageSuffix").c_str()));
   AddedImageSuffix = configSettings->value(String(configName + "/Images/AddedImageSuffix").c_str());
   ImageType = configSettings->value(String(configName + "/Images/ImageType").c_str());
   DiffuseTypeSuffixes = configSettings->value(String(configName + "/Images/DiffuseTypeSuffixes").c_str());
   NormalTypeSuffixes = configSettings->value(String(configName + "/Images/NormalTypeSuffixes").c_str());
   MetalnessTypeSuffixes = configSettings->value(String(configName + "/Images/MetalnessTypeSuffixes").c_str());
   RoughnessTypeSuffixes = configSettings->value(String(configName + "/Images/RoughnessTypeSuffixes").c_str());
   SmoothnessTypeSuffixes = configSettings->value(String(configName + "/Images/SmoothnessTypeSuffixes").c_str());
   AOTypeSuffixes = configSettings->value(String(configName + "/Images/AOTypeSuffixes").c_str());
   PBRTypeSuffixes = configSettings->value(String(configName + "/Images/PBRTypeSuffixes").c_str());
   TextureFilteringMode = configSettings->value(String(configName + "/Images/TextureFilteringMode").c_str());
   UseMips = dAtob(configSettings->value(String(configName + "/Images/UseMips").c_str()));
   IsHDR = dAtob(configSettings->value(String(configName + "/Images/IsHDR").c_str()));
   Scaling = dAtof(configSettings->value(String(configName + "/Images/Scaling").c_str()));
   ImagesCompressed = dAtob(configSettings->value(String(configName + "/Images/Compressed").c_str()));
   GenerateMaterialOnImport = dAtob(configSettings->value(String(configName + "/Images/GenerateMaterialOnImport").c_str()));

   //Sounds
   VolumeAdjust = dAtof(configSettings->value(String(configName + "/Sounds/VolumeAdjust").c_str()));
   PitchAdjust = dAtof(configSettings->value(String(configName + "/Sounds/PitchAdjust").c_str()));
   SoundsCompressed = dAtob(configSettings->value(String(configName + "/Sounds/Compressed").c_str()));
   AlwaysAddSoundSuffix = dAtob(configSettings->value(String(configName + "/Sounds/AlwaysAddSoundSuffix").c_str()));
   AddedSoundSuffix = configSettings->value(String(configName + "/Sounds/AddedSoundSuffix").c_str());
}

void AssetImportConfig::CopyTo(AssetImportConfig* target) const
{
   target->DuplicateAutoResolution = DuplicateAutoResolution;
   target->WarningsAsErrors = WarningsAsErrors;
   target->PreventImportWithErrors = PreventImportWithErrors;
   target->AutomaticallyPromptMissingFiles = AutomaticallyPromptMissingFiles;
   target->AddDirectoryPrefixToAssetName = AddDirectoryPrefixToAssetName;

   //Meshes
   target->ImportMesh = ImportMesh;
   target->AlwaysAddShapeSuffix = AlwaysAddShapeSuffix;
   target->AddedShapeSuffix = AddedShapeSuffix;
   target->UseManualShapeConfigRules = UseManualShapeConfigRules;
   target->DoUpAxisOverride = DoUpAxisOverride;
   target->UpAxisOverride = UpAxisOverride;
   target->DoScaleOverride = DoScaleOverride;
   target->ScaleOverride = ScaleOverride;
   target->IgnoreNodeScale = IgnoreNodeScale;
   target->AdjustCenter = AdjustCenter;
   target->AdjustFloor = AdjustFloor;
   target->CollapseSubmeshes = CollapseSubmeshes;
   target->LODType = LODType;
   target->AlwaysImportedNodes = AlwaysImportedNodes;
   target->AlwaysIgnoreNodes = AlwaysIgnoreNodes;
   target->AlwaysImportMeshes = AlwaysImportMeshes;
   target->AlwaysIgnoreMeshes = AlwaysIgnoreMeshes;

   //Assimp/Collada
   target->convertLeftHanded = convertLeftHanded;
   target->calcTangentSpace = calcTangentSpace;
   target->removeRedundantMats = removeRedundantMats;
   target->genUVCoords = genUVCoords;
   target->TransformUVs = TransformUVs;
   target->flipUVCoords = flipUVCoords;
   target->findInstances = findInstances;
   target->limitBoneWeights = limitBoneWeights;
   target->JoinIdenticalVerts = JoinIdenticalVerts;
   target->reverseWindingOrder = reverseWindingOrder;
   target->invertNormals = invertNormals;

   //Materials
   target->ImportMaterials = ImportMaterials;
   target->AlwaysAddMaterialSuffix = AlwaysAddMaterialSuffix;
   target->AddedMaterialSuffix = AddedMaterialSuffix;
   target->CreateORMConfig = CreateORMConfig;
   target->UseDiffuseSuffixOnOriginImage = UseDiffuseSuffixOnOriginImage;
   target->UseExistingMaterials = UseExistingMaterials;
   target->IgnoreMaterials = IgnoreMaterials;
   target->PopulateMaterialMaps = PopulateMaterialMaps;

   //Animations
   target->ImportAnimations = ImportAnimations;
   target->SeparateAnimations = SeparateAnimations;
   target->SeparateAnimationPrefix = SeparateAnimationPrefix;
   target->animTiming = animTiming;
   target->animFPS = animFPS;
   target->AlwaysAddShapeAnimationSuffix = AlwaysAddShapeAnimationSuffix;
   target->AddedShapeAnimationSuffix = AddedShapeAnimationSuffix;

   //Collisions
   target->GenerateCollisions = GenerateCollisions;
   target->GenCollisionType = GenCollisionType;
   target->CollisionMeshPrefix = CollisionMeshPrefix;
   target->GenerateLOSCollisions = GenerateLOSCollisions;
   target->GenLOSCollisionType = GenLOSCollisionType;
   target->LOSCollisionMeshPrefix = LOSCollisionMeshPrefix;

   //Images
   target->importImages = importImages;
   target->AlwaysAddImageSuffix = AlwaysAddImageSuffix;
   target->AddedImageSuffix = AddedImageSuffix;
   target->ImageType = ImageType;
   target->DiffuseTypeSuffixes = DiffuseTypeSuffixes;
   target->NormalTypeSuffixes = NormalTypeSuffixes;
   target->MetalnessTypeSuffixes = MetalnessTypeSuffixes;
   target->RoughnessTypeSuffixes = RoughnessTypeSuffixes;
   target->SmoothnessTypeSuffixes = SmoothnessTypeSuffixes;
   target->AOTypeSuffixes = AOTypeSuffixes;
   target->PBRTypeSuffixes = PBRTypeSuffixes;
   target->TextureFilteringMode = TextureFilteringMode;
   target->UseMips = UseMips;
   target->IsHDR = IsHDR;
   target->Scaling = Scaling;
   target->ImagesCompressed = ImagesCompressed;
   target->GenerateMaterialOnImport = GenerateMaterialOnImport;

   //Sounds
   target->VolumeAdjust = VolumeAdjust;
   target->PitchAdjust = PitchAdjust;
   target->SoundsCompressed = SoundsCompressed;
   target->AlwaysAddSoundSuffix = AlwaysAddSoundSuffix;
   target->AddedSoundSuffix = AddedSoundSuffix;
}

ConsoleDocClass(AssetImportObject,
   "@brief Defines properties for an AssetImportObject object.\n"
   "@AssetImportObject is a SimObject derived object intended to act as a stand-in for the to-be imported objects.\n"
   "@It contains important info such as dependencies, if it's been processed, any error/status issues and the originating file\n"
   "@or if it's been programmatically generated as part of the import process.\n\n"
   "@ingroup Assets\n"
);

IMPLEMENT_CONOBJECT(AssetImportObject);

AssetImportObject::AssetImportObject() :
   dirty(false),
   importStatus(AssetImportObject::NotProcessed),
   generatedAsset(false),
   parentAssetItem(nullptr),
   tamlFilePath(""),
   imageSuffixType(""),
   shapeInfo(nullptr),
   filePathString(StringTable->EmptyString())
{

}

AssetImportObject::~AssetImportObject()
{

}

bool AssetImportObject::onAdd()
{
   if (!Parent::onAdd())
      return false;

   return true;
}

void AssetImportObject::onRemove()
{
   Parent::onRemove();
}

void AssetImportObject::initPersistFields()
{
   docsURL;
   Parent::initPersistFields();

   addField("assetType", TypeRealString, Offset(assetType, AssetImportObject), "What type is the importing asset");
   addProtectedField("filePath", TypeFilename, Offset(filePathString, AssetImportObject), &_setFilePath, &defaultProtectedGetFn, "What is the source file path of the importing asset");
   addField("assetName", TypeRealString, Offset(assetName, AssetImportObject), "What is the asset's name");
   addField("cleanAssetName", TypeRealString, Offset(cleanAssetName, AssetImportObject), "What is the original, unmodified by processing, asset name");
   addField("status", TypeRealString, Offset(status, AssetImportObject), "What is the current status of this asset item in it's import process");
   addField("statusType", TypeRealString, Offset(statusType, AssetImportObject), "If there is a warning or error status, what type is the condition for this asset item");
   addField("statusInfo", TypeRealString, Offset(statusInfo, AssetImportObject), "What is the articulated information of the status of the asset. Contains the error or warning log data");

   addField("dirty", TypeBool, Offset(dirty, AssetImportObject), "Is the asset item currently flagged as dirty");
   addField("generatedAsset", TypeBool, Offset(generatedAsset, AssetImportObject), "Is this specific asset item generated as part of the import process of another item");

   addField("tamlFilePath", TypeRealString, Offset(tamlFilePath, AssetImportObject), "What is the ultimate asset taml file path for this import item");

   addField("imageType", TypeRealString, Offset(imageSuffixType, AssetImportObject), "Specific to ImageAsset type. What is the image asset's suffix type. Options are: Albedo, Normal, Roughness, AO, Metalness, ORMConfig");

   addField("shapeInfo", TYPEID< GuiTreeViewCtrl >(), Offset(shapeInfo, AssetImportObject), "Specific to ShapeAsset type. Processed information about the shape file. Contains numbers and lists of meshes, materials and animations");
}

bool AssetImportObject::_setFilePath(void* obj, const char* index, const char* data)
{
   AssetImportObject* importObj = static_cast<AssetImportObject*>(obj);
   importObj->setFilePath(StringTable->insert(data));

   return false;
}

void AssetImportObject::setFilePath(StringTableEntry pFilePath)
{
   filePathString = pFilePath;
   filePath = Torque::Path(pFilePath);
}

ConsoleDocClass(AssetImporter,
   "@brief Defines properties for an AssetImportObject object.\n"
   "@AssetImportObject is a SimObject derived object intended to act as a stand-in for the to-be imported objects.\n"
   "@It contains important info such as dependencies, if it's been processed, any error/status issues and the originating file\n"
   "@or if it's been programmatically generated as part of the import process.\n\n"
   "@ingroup Assets\n"
);

IMPLEMENT_CONOBJECT(AssetImporter);

AssetImporter::AssetImporter() :
   importIssues(false),
   isReimport(false),
   assetHeirarchyChanged(false),
   importLogBuffer(""),
   activeImportConfig(nullptr),
   mDumpLogs(true)
{
}

AssetImporter::~AssetImporter()
{
}

bool AssetImporter::onAdd()
{
   if (!Parent::onAdd())
      return false;

   return true;
}

void AssetImporter::onRemove()
{
   Parent::onRemove();
}

void AssetImporter::initPersistFields()
{
   docsURL;
   Parent::initPersistFields();

   addField("targetModuleId", TypeRealString, Offset(targetModuleId, AssetImporter), "The Id of the module the assets are to be imported into");
   addField("finalImportedAssetPath", TypeRealString, Offset(finalImportedAssetPath, AssetImporter), "The Id of the module the assets are to be imported into");
   addField("targetPath", TypeRealString, Offset(targetPath, AssetImporter), "The path any imported assets are placed in as their destination");
   addField("dumpLogs", TypeBool, Offset(mDumpLogs, AssetImporter), "Indicates if the importer always dumps its logs or not");
}

//
// Utility Functions
//

AssetImportObject* AssetImporter::addImportingFile(Torque::Path filePath)
{
   String assetType = getAssetTypeByFile(filePath);

   if (assetType.isEmpty())
   {
      dSprintf(importLogBuffer, sizeof(importLogBuffer), "Unable to import file %s because it is of an unrecognized/unsupported type.", filePath.getFullPath().c_str());
      activityLog.push_back(importLogBuffer);
      return nullptr;
   }

   AssetImportObject* newAssetItem = addImportingAsset(assetType, filePath, nullptr, "");

   originalImportingFiles.push_back(filePath);

   return newAssetItem;
}

void AssetImporter::addImportingAssetItem(AssetImportObject* assetItem, AssetImportObject* parentItem)
{
   if (assetItem == nullptr)
   {
      dSprintf(importLogBuffer, sizeof(importLogBuffer), "Cannot add a null AssetImportObject to import session!");
      activityLog.push_back(importLogBuffer);
      return;
   }

   if (parentItem != nullptr)
   {
      dSprintf(importLogBuffer, sizeof(importLogBuffer), "Added Child Importing Asset to %s", parentItem->assetName.c_str());
      activityLog.push_back(importLogBuffer);

      parentItem->childAssetItems.push_back(assetItem);
      assetItem->parentAssetItem = parentItem;
   }
   else
   {
      dSprintf(importLogBuffer, sizeof(importLogBuffer), "Added Importing Asset");
      activityLog.push_back(importLogBuffer);
      importingAssets.push_back(assetItem);
   }

   dSprintf(importLogBuffer, sizeof(importLogBuffer), "   Asset Info: Name: %s | Type: %s", assetItem->assetName.c_str(), assetItem->assetType.c_str());
   activityLog.push_back(importLogBuffer);

   if (!assetItem->filePath.isEmpty())
   {
      dSprintf(importLogBuffer, sizeof(importLogBuffer), "   File: %s", assetItem->filePath.getFullPath().c_str());
      activityLog.push_back(importLogBuffer);
   }
}

AssetImportObject* AssetImporter::addImportingAsset(String assetType, Torque::Path filePath, AssetImportObject* parentItem, String assetNameOverride)
{
   String assetName;
   String origionalName;

   //In some cases(usually generated assets on import, like materials) we'll want to specifically define the asset name instead of peeled from the filePath
   if (assetNameOverride.isNotEmpty())
      assetName = assetNameOverride;
   else
      assetName = filePath.getFileName();

   AssetImportObject* assetImportObj = new AssetImportObject();
   assetImportObj->registerObject();

   //sanitize
   String processedString = assetName;

   U32 start;
   U32 end;
   String firstNumber = String::GetFirstNumber(processedString, start, end);
   if (!firstNumber.isEmpty() && processedString.startsWith(firstNumber.c_str()))
      processedString = processedString.replace(firstNumber, "");

   processedString = processedString.replace(" ", "_");

   U32 len = processedString.length() + 1;
   char* sanitizedStr = Con::getReturnBuffer(len);
   dStrcpy(sanitizedStr, processedString.c_str(), len);

   U32 pos = dStrcspn(sanitizedStr, "-+*/%$&�=()[].?\\\"#,;!~<>|�^{}");
   while (pos < dStrlen(sanitizedStr))
   {
      dStrcpy(sanitizedStr + pos, sanitizedStr + pos + 1, len - pos);
      pos = dStrcspn(sanitizedStr, "-+*/%$&�=()[].?\\\"#,;!~<>|�^{}");
   }

   origionalName = assetName;

   //If we did, indeed, modify the name, update it now
   if (String(sanitizedStr) != assetName)
   {
      assetName = sanitizedStr;
   }

   assetImportObj->assetType = assetType;
   assetImportObj->filePath = filePath;
   assetImportObj->filePathString = StringTable->insert(filePath.getFullPath().c_str());
   assetImportObj->assetName = assetName;
   assetImportObj->cleanAssetName = origionalName;
   assetImportObj->moduleName = targetModuleId;
   assetImportObj->status = "";
   assetImportObj->statusType = "";
   assetImportObj->statusInfo = "";

   assetImportObj->dirty = false;
   assetImportObj->importStatus = AssetImportObject::NotProcessed;
   assetImportObj->generatedAsset = false;

   //If the config is marked to always set the directory prefix, do that now
   if (activeImportConfig->AddDirectoryPrefixToAssetName)
   {
      assetName = getFolderPrefixedName(assetImportObj);
      assetImportObj->assetName = assetName;
      assetImportObj->cleanAssetName = assetName;
   }

   if (parentItem != nullptr)
   {
      dSprintf(importLogBuffer, sizeof(importLogBuffer), "Added Child Importing Asset to %s", parentItem->assetName.c_str());
      activityLog.push_back(importLogBuffer);

      parentItem->childAssetItems.push_back(assetImportObj);
      assetImportObj->parentAssetItem = parentItem;
   }
   else
   {
      dSprintf(importLogBuffer, sizeof(importLogBuffer), "Added Importing Asset");
      activityLog.push_back(importLogBuffer);

      importingAssets.push_back(assetImportObj);
   }

   dSprintf(importLogBuffer, sizeof(importLogBuffer), "   Asset Info: Name: %s | Type: %s", assetImportObj->assetName.c_str(), assetImportObj->assetType.c_str());
   activityLog.push_back(importLogBuffer);

   if (!filePath.isEmpty())
   {
      dSprintf(importLogBuffer, sizeof(importLogBuffer), "   File: %s", filePath.getFullPath().c_str());
      activityLog.push_back(importLogBuffer);
   }

   return assetImportObj;
}

void AssetImporter::deleteImportingAsset(AssetImportObject* assetItem)
{
   assetItem->importStatus = AssetImportObject::Skipped;

   //log it
   dSprintf(importLogBuffer, sizeof(importLogBuffer), "Deleting Importing Asset %s and all it's child items", assetItem->assetName.c_str());
   activityLog.push_back(importLogBuffer);
}

AssetImportObject* AssetImporter::findImportingAssetByName(String assetName, AssetImportObject* assetItem)
{
   Vector<AssetImportObject*> itemList = importingAssets;
   if (assetItem != nullptr)
      itemList = assetItem->childAssetItems;

   for (U32 i = 0; i < itemList.size(); i++)
   {
      if (itemList[i]->cleanAssetName == assetName)
      {
         return itemList[i];
      }

      //If it wasn't a match, try recusing on the children(if any)
      AssetImportObject* retItem = findImportingAssetByName(assetName, itemList[i]);
      if (retItem != nullptr)
         return retItem;
   }

   return nullptr;
}

ModuleDefinition* AssetImporter::getModuleFromPath(Torque::Path filePath)
{
   // Use a relative path so modules on mounted file systems will be found.
   ModuleDefinition* moduleDef = ModuleDatabase.findModuleByFilePath(Platform::makeRelativePathName(filePath.getFullPath().c_str(), NULL));

   return moduleDef;
}

String AssetImporter::parseImageSuffixes(String assetName, String* suffixType)
{
   //Here, we loop over our different suffix lists progressively.
   //This lets us walk through a list of suffixes in the Import Config, such as DiffuseTypeSuffixes
   //And then iterate over the delinated list of items within it to look for a match.
   //If we don't find a match, we then increment our list switch index and scan through the next list.
   U32 suffixTypeIdx = 0;
   while (suffixTypeIdx < 6)
   {
      String suffixList;
      switch (suffixTypeIdx)
      {
         case 0:
            suffixList = activeImportConfig->DiffuseTypeSuffixes;
            suffixType->insert(0, "Albedo", 6);
            break;
         case 1:
            suffixList = activeImportConfig->NormalTypeSuffixes;
            suffixType->insert(0, "Normal", 6);
            break;
         case 2:
            suffixList = activeImportConfig->RoughnessTypeSuffixes;
            suffixType->insert(0, "Roughness", 9);
            break;
         case 3:
            suffixList = activeImportConfig->AOTypeSuffixes;
            suffixType->insert(0, "AO", 2);
            break;
         case 4:
            suffixList = activeImportConfig->MetalnessTypeSuffixes;
            suffixType->insert(0, "Metalness", 9);
            break;
         case 5:
            suffixList = activeImportConfig->PBRTypeSuffixes;
            suffixType->insert(0, "ORMConfig", 9);
            break;
         default:
            suffixList = "";
      }

      suffixTypeIdx++;

      U32 suffixCount = StringUnit::getUnitCount(suffixList, ",;\t");
      for (U32 i = 0; i < suffixCount; i++)
      {
         String suffix = StringUnit::getUnit(suffixList, i, ",;\t");
         String searchSuffix = String("*") + suffix;

         if (FindMatch::isMatch(searchSuffix.c_str(), assetName.c_str(), false))
         {
            //We have a match, so indicate as such
            S32 pos = assetName.length();
            pos -= searchSuffix.length();
            suffix = assetName.substr(pos+1);
            return suffix;
         }
      }
   }

   suffixType->clear();
   return "";
}

String AssetImporter::getAssetTypeByFile(Torque::Path filePath)
{
   String fileExt = String::ToLower(filePath.getExtension());
   String fileName = String::ToLower(filePath.getFileName());

   if (fileExt == String("dts") && fileName.endsWith("cached"))
      return "";

   if (fileExt == String("png") || fileExt == String("jpg") || fileExt == String("jpeg") || fileExt == String("dds"))
      return "ImageAsset";
   else if (fileExt == String("dae") || fileExt == String("fbx") || fileExt == String("blend") || fileExt == String("obj") || fileExt == String("dts") || fileExt == String("gltf") || fileExt == String("gltb"))
      return "ShapeAsset";
   else if (fileExt == String("dsq"))
      return "ShapeAnimationAsset";
   else if (fileExt == String("ogg") || fileExt == String("wav") || fileExt == String("mp3"))
      return "SoundAsset";
   else if (fileExt == String("zip"))
      return "Zip";
   else if (fileExt.isEmpty())
      return "Folder";

   return "";
}

String AssetImporter::getTrueFilename(const String& fileName)
{
   Torque::Path pth(fileName);
   String pattern = pth.getFullPath() + "*";

   static const String sSlash("/");

   Vector<String> findFilesResults;

   String sPattern(Torque::Path::CleanSeparators(pattern));
   if (sPattern.isEmpty())
   {
      Con::errorf("findFirstFile() requires a search pattern");
      return "";
   }

   char scriptFilenameBuffer[1024];

   if (!Con::expandScriptFilename(scriptFilenameBuffer, sizeof(scriptFilenameBuffer), sPattern.c_str()))
   {
      Con::errorf("findFirstFile() given initial directory cannot be expanded: '%s'", pattern.c_str());
      return "";
   }
   sPattern = String::ToString(scriptFilenameBuffer);

   String::SizeType slashPos = sPattern.find('/', 0, String::Right);
   //    if(slashPos == String::NPos)
   //    {
   //       Con::errorf("findFirstFile() missing search directory or expression: '%s'", sPattern.c_str());
   //       return -1;
   //    }

      // Build the initial search path
   Torque::Path givenPath(Torque::Path::CompressPath(sPattern));
   givenPath.setFileName("*");
   givenPath.setExtension("*");

   if (givenPath.getPath().length() > 0 && givenPath.getPath().find('*', 0, String::Right) == givenPath.getPath().length() - 1)
   {
      // Deal with legacy searches of the form '*/*.*'
      String suspectPath = givenPath.getPath();
      String::SizeType newLen = suspectPath.length() - 1;
      if (newLen > 0 && suspectPath.find('/', 0, String::Right) == suspectPath.length() - 2)
      {
         --newLen;
      }
      givenPath.setPath(suspectPath.substr(0, newLen));
   }

   Torque::FS::FileSystemRef fs = Torque::FS::GetFileSystem(givenPath);
   //Torque::Path path = fs->mapTo(givenPath);
   Torque::Path path = givenPath;

   // Make sure that we have a root so the correct file system can be determined when using zips
   if (givenPath.isRelative())
      path = Torque::Path::Join(Torque::FS::GetCwd(), '/', givenPath);

   path.setFileName(String::EmptyString);
   path.setExtension(String::EmptyString);
   if (!Torque::FS::IsDirectory(path))
   {
      Con::errorf("findFirstFile() invalid initial search directory: '%s'", path.getFullPath().c_str());
      return "";
   }

   // Build the search expression
   const String expression(slashPos != String::NPos ? sPattern.substr(slashPos + 1) : sPattern);
   if (expression.isEmpty())
   {
      Con::errorf("findFirstFile() requires a search expression: '%s'", sPattern.c_str());
      return "";
   }

   S32 results = Torque::FS::FindByPattern(path, expression, false, findFilesResults, false);
   if (givenPath.isRelative() && results > 0)
   {
      // Strip the CWD out of the returned paths
      // MakeRelativePath() returns incorrect results (it adds a leading ..) so doing this the dirty way
      const String cwd = Torque::FS::GetCwd().getFullPath();
      for (S32 i = 0; i < findFilesResults.size(); ++i)
      {
         String str = findFilesResults[i];
         if (str.compare(cwd, cwd.length(), String::NoCase) == 0)
            str = str.substr(cwd.length());
         findFilesResults[i] = str;
      }
   }

   for (U32 i = 0; i < findFilesResults.size(); i++)
   {
      if (!findFilesResults[i].compare(fileName, 0, String::NoCase|String::Left))
         return findFilesResults[i];
   }

   return "";
}

void AssetImporter::resetImportSession(bool hardClearSession)
{
   importingAssets.clear();
   activityLog.clear();

   if (hardClearSession)
   {
      originalImportingFiles.clear();
   }
   else
   {
      Vector<Torque::Path> tempImportingFiles = originalImportingFiles;
      originalImportingFiles.clear();

      for (U32 i = 0; i < tempImportingFiles.size(); i++)
      {
         addImportingFile(tempImportingFiles[i]);
      }
   }
}

S32 AssetImporter::getActivityLogLineCount()
{
   return activityLog.size();
}

String AssetImporter::getActivityLogLine(U32 line)
{
   if (line >= activityLog.size())
      return "";

   return activityLog[line];
}

void AssetImporter::dumpActivityLog()
{
   if (!mDumpLogs)
      return;

   FileObject logFile;

   //If there's nothing logged, don't bother
   if (activityLog.size() == 0)
      return;

   Torque::Time::DateTime curTime;
   Torque::Time::getCurrentDateTime(curTime);

   String logName = String("tools/logs/AssetImportLog_") + String::ToString(curTime.year + 1900) + "-" +
      String::ToString(curTime.month + 1) + "-" + String::ToString(curTime.day) + "_" +
      String::ToString(curTime.hour) + "-" + String::ToString(curTime.minute) + "-" + String::ToString(curTime.second)
      + "-" + String::ToString(curTime.microsecond) + ".log";

   if (logFile.openForWrite(logName.c_str()))
   {
      for (U32 i = 0; i < activityLog.size(); i++)
      {
         logFile.writeLine((const U8*)activityLog[i].c_str());
      }

      logFile.close();

      Con::warnf("Asset Import log file dumped to: %s", logName.c_str());
   }
   else
   {
      Con::errorf("Error: Failed to open log file for writing! Dumping log results to console!");
      for (U32 i = 0; i < activityLog.size(); i++)
      {
         Con::printf(activityLog[i].c_str());
      }
   }
}

S32 AssetImporter::getAssetItemCount()
{
   return importingAssets.size();
}

AssetImportObject* AssetImporter::getAssetItem(U32 index)
{
   if (index >= importingAssets.size())
      return nullptr;

   return importingAssets[index];
}

S32 AssetImporter::getAssetItemChildCount(AssetImportObject* assetItem)
{
   return assetItem->childAssetItems.size();
}

AssetImportObject* AssetImporter::getAssetItemChild(AssetImportObject* assetItem, U32 index)
{
   if (index >= assetItem->childAssetItems.size())
      return nullptr;

   return assetItem->childAssetItems[index];
}
//
// Processing
//
// Helper struct for counting nodes, meshes and polygons down through the scene
// hierarchy
struct SceneStats
{
   S32 numNodes;
   S32 numMeshes;
   S32 numPolygons;
   S32 numMaterials;
   S32 numLights;
   S32 numClips;

   SceneStats() : numNodes(0), numMeshes(0), numPolygons(0), numMaterials(0), numLights(0), numClips(0) { }
};

// Recurse through the <visual_scene> adding nodes and geometry to the GuiTreeView control
static void processNode(GuiTreeViewCtrl* tree, domNode* node, S32 parentID, SceneStats& stats)
{
   stats.numNodes++;
   S32 nodeID = tree->insertItem(parentID, _GetNameOrId(node), "node", "", 0, 0);

   // Update mesh and poly counts
   for (S32 i = 0; i < node->getContents().getCount(); i++)
   {
      domGeometry* geom = 0;
      const char* elemName = "";

      daeElement* child = node->getContents()[i];
      switch (child->getElementType())
      {
      case COLLADA_TYPE::INSTANCE_GEOMETRY:
      {
         domInstance_geometry* instgeom = daeSafeCast<domInstance_geometry>(child);
         if (instgeom)
         {
            geom = daeSafeCast<domGeometry>(instgeom->getUrl().getElement());
            elemName = _GetNameOrId(geom);
         }
         break;
      }

      case COLLADA_TYPE::INSTANCE_CONTROLLER:
      {
         domInstance_controller* instctrl = daeSafeCast<domInstance_controller>(child);
         if (instctrl)
         {
            domController* ctrl = daeSafeCast<domController>(instctrl->getUrl().getElement());
            elemName = _GetNameOrId(ctrl);
            if (ctrl && ctrl->getSkin())
               geom = daeSafeCast<domGeometry>(ctrl->getSkin()->getSource().getElement());
            else if (ctrl && ctrl->getMorph())
               geom = daeSafeCast<domGeometry>(ctrl->getMorph()->getSource().getElement());
         }
         break;
      }

      case COLLADA_TYPE::INSTANCE_LIGHT:
         stats.numLights++;
         tree->insertItem(nodeID, _GetNameOrId(node), "light", "", 0, 0);
         break;
      }

      if (geom && geom->getMesh())
      {
         const char* name = _GetNameOrId(node);
         if (dStrEqual(name, "null") || dStrEndsWith(name, "PIVOT"))
            name = _GetNameOrId(daeSafeCast<domNode>(node->getParent()));

         stats.numMeshes++;
         tree->insertItem(nodeID, name, "mesh", "", 0, 0);

         for (S32 j = 0; j < geom->getMesh()->getTriangles_array().getCount(); j++)
            stats.numPolygons += geom->getMesh()->getTriangles_array()[j]->getCount();
         for (S32 j = 0; j < geom->getMesh()->getTristrips_array().getCount(); j++)
            stats.numPolygons += geom->getMesh()->getTristrips_array()[j]->getCount();
         for (S32 j = 0; j < geom->getMesh()->getTrifans_array().getCount(); j++)
            stats.numPolygons += geom->getMesh()->getTrifans_array()[j]->getCount();
         for (S32 j = 0; j < geom->getMesh()->getPolygons_array().getCount(); j++)
            stats.numPolygons += geom->getMesh()->getPolygons_array()[j]->getCount();
         for (S32 j = 0; j < geom->getMesh()->getPolylist_array().getCount(); j++)
            stats.numPolygons += geom->getMesh()->getPolylist_array()[j]->getCount();
      }
   }

   // Recurse into child nodes
   for (S32 i = 0; i < node->getNode_array().getCount(); i++)
      processNode(tree, node->getNode_array()[i], nodeID, stats);

   for (S32 i = 0; i < node->getInstance_node_array().getCount(); i++)
   {
      domInstance_node* instnode = node->getInstance_node_array()[i];
      domNode* dNode = daeSafeCast<domNode>(instnode->getUrl().getElement());
      if (dNode)
         processNode(tree, dNode, nodeID, stats);
   }
}

static bool enumColladaForImport(const char* shapePath, GuiTreeViewCtrl* tree, bool loadCachedDts)
{
   // Check if a cached DTS is available => no need to import the collada file
   // if we can load the DTS instead
   Torque::Path path(shapePath);
   if (loadCachedDts && ColladaShapeLoader::canLoadCachedDTS(path))
      return false;

   // Check if this is a Sketchup file (.kmz) and if so, mount the zip filesystem
   // and get the path to the DAE file.
   String mountPoint;
   Torque::Path daePath;
   bool isSketchup = ColladaShapeLoader::checkAndMountSketchup(path, mountPoint, daePath);

   // Load the Collada file into memory
   domCOLLADA* root = ColladaShapeLoader::getDomCOLLADA(daePath);
   if (!root)
   {
      TSShapeLoader::updateProgress(TSShapeLoader::Load_Complete, "Load complete");
      return false;
   }

   if (isSketchup)
   {
      // Unmount the zip if we mounted it
      Torque::FS::Unmount(mountPoint);
   }

   // Initialize tree
   tree->removeItem(0);
   S32 nodesID = tree->insertItem(0, "Shape", "", "", 0, 0);
   S32 matsID = tree->insertItem(0, "Materials", "", "", 0, 0);
   S32 animsID = tree->insertItem(0, "Animations", "", "", 0, 0);

   SceneStats stats;

   // Query DOM for shape summary details
   for (S32 i = 0; i < root->getLibrary_visual_scenes_array().getCount(); i++)
   {
      const domLibrary_visual_scenes* libScenes = root->getLibrary_visual_scenes_array()[i];
      for (S32 j = 0; j < libScenes->getVisual_scene_array().getCount(); j++)
      {
         const domVisual_scene* visualScene = libScenes->getVisual_scene_array()[j];
         for (S32 k = 0; k < visualScene->getNode_array().getCount(); k++)
            processNode(tree, visualScene->getNode_array()[k], nodesID, stats);
      }
   }

   // Get material count
   for (S32 i = 0; i < root->getLibrary_materials_array().getCount(); i++)
   {
      const domLibrary_materials* libraryMats = root->getLibrary_materials_array()[i];
      stats.numMaterials += libraryMats->getMaterial_array().getCount();
      for (S32 j = 0; j < libraryMats->getMaterial_array().getCount(); j++)
      {
         domMaterial* mat = libraryMats->getMaterial_array()[j];
         tree->insertItem(matsID, _GetNameOrId(mat), "", "", 0, 0);
      }
   }

   // Get images count
   for (S32 i = 0; i < root->getLibrary_images_array().getCount(); i++)
   {
      const domLibrary_images* libraryImages = root->getLibrary_images_array()[i];

      for (S32 j = 0; j < libraryImages->getImage_array().getCount(); j++)
      {
         domImage* img = libraryImages->getImage_array()[j];

         String imageName = _GetNameOrId(img);

         S32 materialID = tree->findItemByName(imageName.c_str());

         if (materialID == 0)
         {
            bool materialFound = false;
            String matName = "";

            //If we don't have an immediate name match, we'll have to actually go look it up
            for (S32 e = 0; e < root->getLibrary_effects_array().getCount(); e++)
            {
               const domLibrary_effects* libraryEffects = root->getLibrary_effects_array()[e];

               for (S32 f = 0; f < libraryEffects->getEffect_array().getCount(); f++)
               {
                  domEffect* efct = libraryEffects->getEffect_array()[f];

                  String effectName = efct->getID();

                  for (S32 p = 0; p < efct->getFx_profile_abstract_array().getCount(); p++)
                  {
                     domProfile_COMMON* profile = daeSafeCast<domProfile_COMMON>(efct->getFx_profile_abstract_array()[p]);

                     for (S32 n = 0; n < profile->getNewparam_array().getCount(); n++)
                     {
                        domCommon_newparam_typeRef param = profile->getNewparam_array()[n];
                        String paramName = param->getSid();
                        if (paramName.endsWith("-surface"))
                        {
                           //ok it's surface data, parse out the name
                           String surfaceName = paramName.substr(0, paramName.length() - 8);
                           if (surfaceName == imageName)
                           {
                              //got a match!
                              matName = effectName;
                              if (matName.endsWith("-effect"))
                              {
                                 matName = matName.substr(0, matName.length() - 7);
                                 materialFound = true;
                                 break;
                              }
                           }
                        }
                     }

                     if (materialFound)
                        break;
                  }

                  if (materialFound)
                  {
                     materialID = tree->findItemByName(matName.c_str());
                  }

                  if (materialID != 0)
                     break;
               }
            }

            //if we STILL haven't found a match, then yes, we've failed
            if (materialID == 0)
               continue;
         }

         String imagePath = img->getInit_from()->getValue().str().c_str();
         if (imagePath.startsWith("/"))
            imagePath = imagePath.substr(1, imagePath.length() - 1);

         tree->setItemValue(materialID, StringTable->insert(imagePath.c_str()));
      }
   }

   // Get animation count
   for (S32 i = 0; i < root->getLibrary_animation_clips_array().getCount(); i++)
   {
      const domLibrary_animation_clips* libraryClips = root->getLibrary_animation_clips_array()[i];
      stats.numClips += libraryClips->getAnimation_clip_array().getCount();
      for (S32 j = 0; j < libraryClips->getAnimation_clip_array().getCount(); j++)
      {
         domAnimation_clip* clip = libraryClips->getAnimation_clip_array()[j];
         tree->insertItem(animsID, _GetNameOrId(clip), "animation", "", 0, 0);
      }
   }
   if (stats.numClips == 0)
   {
      // No clips => check if there are any animations (these will be added to a default clip)
      for (S32 i = 0; i < root->getLibrary_animations_array().getCount(); i++)
      {
         const domLibrary_animations* libraryAnims = root->getLibrary_animations_array()[i];
         if (libraryAnims->getAnimation_array().getCount())
         {
            stats.numClips = 1;
            tree->insertItem(animsID, "ambient", "animation", "", 0, 0);
            break;
         }
      }
   }

   // Extract the global scale and up_axis from the top level <asset> element,
   F32 unit = 1.0f;
   domUpAxisType upAxis = UPAXISTYPE_Z_UP;
   if (root->getAsset()) {
      if (root->getAsset()->getUnit())
         unit = root->getAsset()->getUnit()->getMeter();
      if (root->getAsset()->getUp_axis())
         upAxis = root->getAsset()->getUp_axis()->getValue();
   }

   TSShapeLoader::updateProgress(TSShapeLoader::Load_Complete, "Load complete");

   // Store shape information in the tree control
   tree->setDataField(StringTable->insert("_nodeCount"), 0, avar("%d", stats.numNodes));
   tree->setDataField(StringTable->insert("_meshCount"), 0, avar("%d", stats.numMeshes));
   tree->setDataField(StringTable->insert("_polygonCount"), 0, avar("%d", stats.numPolygons));
   tree->setDataField(StringTable->insert("_materialCount"), 0, avar("%d", stats.numMaterials));
   tree->setDataField(StringTable->insert("_lightCount"), 0, avar("%d", stats.numLights));
   tree->setDataField(StringTable->insert("_animCount"), 0, avar("%d", stats.numClips));
   tree->setDataField(StringTable->insert("_unit"), 0, avar("%g", unit));

   if (upAxis == UPAXISTYPE_X_UP)
      tree->setDataField(StringTable->insert("_upAxis"), 0, "X_AXIS");
   else if (upAxis == UPAXISTYPE_Y_UP)
      tree->setDataField(StringTable->insert("_upAxis"), 0, "Y_AXIS");
   else
      tree->setDataField(StringTable->insert("_upAxis"), 0, "Z_AXIS");

   char shapesStr[16];
   dSprintf(shapesStr, 16, "%i", stats.numMeshes);
   char materialsStr[16];
   dSprintf(materialsStr, 16, "%i", stats.numMaterials);
   char animationsStr[16];
   dSprintf(animationsStr, 16, "%i", stats.numClips);

   tree->setItemValue(nodesID, StringTable->insert(shapesStr));
   tree->setItemValue(matsID, StringTable->insert(materialsStr));
   tree->setItemValue(animsID, StringTable->insert(animationsStr));

   return true;
}

static bool enumDTSForImport(const char* shapePath, GuiTreeViewCtrl* tree)
{
   // Check if a cached DTS is available => no need to import the collada file
   // if we can load the DTS instead
   Torque::Path path(shapePath);
   Resource<TSShape> dtsShape = ResourceManager::get().load(shapePath);

   if (!dtsShape)
      return false;

   // Initialize tree
   tree->removeItem(0);
   S32 nodesID = tree->insertItem(0, "Shape", "", "", 0, 0);
   S32 matsID = tree->insertItem(0, "Materials", "", "", 0, 0);
   S32 animsID = tree->insertItem(0, "Animations", "", "", 0, 0);

   SceneStats stats;

   // Query DOM for shape summary details
   for (S32 i = 0; i < dtsShape->objects.size(); i++)
   {
      tree->insertItem(nodesID, dtsShape->names[dtsShape->objects[i].nameIndex], "", "", 0, 0);
      stats.numMeshes++;
   }

   // Get material count
   for (S32 i = 0; i < dtsShape->materialList->size(); i++)
   {
      S32 matId = tree->insertItem(matsID, dtsShape->materialList->getMaterialName(i).c_str(), "", "", 0, 0);
      stats.numMaterials++;

      GFXTextureObject* difTex = dtsShape->materialList->getDiffuseTexture(i);
      if (difTex)
      {
         tree->insertItem(matId, difTex->getPath().c_str(), "", "", 0, 0);
      }
   }

   // Get animation count
   for (S32 i = 0; i < dtsShape->sequences.size(); i++)
   {
      tree->insertItem(animsID, dtsShape->names[dtsShape->sequences[i].nameIndex], "animation", "", 0, 0);
      stats.numClips++;
   }

   /*if (stats.numClips == 0)
   {
      // No clips => check if there are any animations (these will be added to a default clip)
      for (S32 i = 0; i < root->getLibrary_animations_array().getCount(); i++)
      {
         const domLibrary_animations* libraryAnims = root->getLibrary_animations_array()[i];
         if (libraryAnims->getAnimation_array().getCount())
         {
            stats.numClips = 1;
            tree->insertItem(animsID, "ambient", "animation", "", 0, 0);
            break;
         }
      }
   }*/

   F32 unit = 1.0f;

   // Store shape information in the tree control
   tree->setDataField(StringTable->insert("_nodeCount"), 0, avar("%d", stats.numNodes));
   tree->setDataField(StringTable->insert("_meshCount"), 0, avar("%d", stats.numMeshes));
   tree->setDataField(StringTable->insert("_polygonCount"), 0, avar("%d", stats.numPolygons));
   tree->setDataField(StringTable->insert("_materialCount"), 0, avar("%d", stats.numMaterials));
   tree->setDataField(StringTable->insert("_lightCount"), 0, avar("%d", stats.numLights));
   tree->setDataField(StringTable->insert("_animCount"), 0, avar("%d", stats.numClips));
   tree->setDataField(StringTable->insert("_unit"), 0, avar("%g", unit));

   tree->setDataField(StringTable->insert("_upAxis"), 0, "Z_AXIS");

   char shapesStr[16];
   dSprintf(shapesStr, 16, "%i", stats.numMeshes);
   char materialsStr[16];
   dSprintf(materialsStr, 16, "%i", stats.numMaterials);
   char animationsStr[16];
   dSprintf(animationsStr, 16, "%i", stats.numClips);

   tree->setItemValue(nodesID, StringTable->insert(shapesStr));
   tree->setItemValue(matsID, StringTable->insert(materialsStr));
   tree->setItemValue(animsID, StringTable->insert(animationsStr));

   return true;
}

void AssetImportConfig::loadSISFile(Torque::Path filePath)
{
   String settingsFilePath = "Tools";
   Settings* editorSettings;
   //See if we can get our editor settings
   if (Sim::findObject("EditorSettings", editorSettings))
   {
      settingsFilePath = editorSettings->value("defaultSettingsPath", "Tools");
   }

   String fileExtension = filePath.getExtension();
   String settingsFile = settingsFilePath + "/" + fileExtension + ".sis";

   FileObject* fileObj = new FileObject();
   if (Torque::FS::IsFile(settingsFile))
   {
      if (!fileObj->readMemory(settingsFile.c_str()))
      {
         Con::errorf("AssetImporter::loadSISFile() - Error opening file to load settings: %s", settingsFile.c_str());
         fileObj->deleteObject();
         return;
      }
   }
   else
   {
      return;
   }

   String headerLine = (const char*)fileObj->readLine();
   if (headerLine.substr(0, 4).compare("SISV", 0U, String::NoCase) != 0)
      return; //not a sis file?

   while (!fileObj->isEOF())
   {
      const char* line = (const char*)fileObj->readLine();
      String key = StringUnit::getUnit(line, 0, "\t");
      String value = StringUnit::getUnit(line, 1, "\t");

      if (key.compare("DoUpAxisOverride", 0U, String::NoCase) == 0)
         DoUpAxisOverride = dAtob(value.c_str());
      else if (key.compare("UpAxisOverride", 0U, String::NoCase) == 0)
         UpAxisOverride = value.c_str();
      else if (key.compare("DoScaleOverride", 0U, String::NoCase) == 0)
         DoScaleOverride = dAtob(value.c_str());
      else if (key.compare("ScaleOverride", 0U, String::NoCase) == 0)
         ScaleOverride = dAtof(value.c_str());
      else if (key.compare("IgnoreNodeScale", 0U, String::NoCase) == 0)
         IgnoreNodeScale = dAtob(value.c_str());
      else if (key.compare("AdjustCenter", 0U, String::NoCase) == 0)
         AdjustCenter = dAtob(value.c_str());
      else if (key.compare("AdjustFloor", 0U, String::NoCase) == 0)
         AdjustFloor = dAtob(value.c_str());
      else if (key.compare("CollapseSubmeshes", 0U, String::NoCase) == 0)
         CollapseSubmeshes = dAtob(value.c_str());
      else if (key.compare("LODType", 0U, String::NoCase) == 0)
         LODType = value.c_str();
      else if (key.compare("AlwaysImportedNodes", 0U, String::NoCase) == 0)
         AlwaysImportedNodes = value.c_str();
      else if (key.compare("AlwaysIgnoreNodes", 0U, String::NoCase) == 0)
         AlwaysIgnoreNodes = value.c_str();
      else if (key.compare("AlwaysImportMeshes", 0U, String::NoCase) == 0)
         AlwaysImportMeshes = value.c_str();
      else if (key.compare("AlwaysIgnoreMeshes", 0U, String::NoCase) == 0)
         AlwaysIgnoreMeshes = value.c_str();
      else if (key.compare("convertLeftHanded", 0U, String::NoCase) == 0)
         convertLeftHanded = dAtob(value.c_str());
      else if (key.compare("calcTangentSpace", 0U, String::NoCase) == 0)
         calcTangentSpace = dAtob(value.c_str());
      else if (key.compare("removeRedundantMats", 0U, String::NoCase) == 0)
         removeRedundantMats = dAtob(value.c_str());
      else if (key.compare("genUVCoords", 0U, String::NoCase) == 0)
         genUVCoords = dAtob(value.c_str());
      else if (key.compare("TransformUVs", 0U, String::NoCase) == 0)
         TransformUVs = dAtob(value.c_str());
      else if (key.compare("flipUVCoords", 0U, String::NoCase) == 0)
         flipUVCoords = dAtob(value.c_str());
      else if (key.compare("findInstances", 0U, String::NoCase) == 0)
         findInstances = dAtob(value.c_str());
      else if (key.compare("limitBoneWeights", 0U, String::NoCase) == 0)
         limitBoneWeights = dAtob(value.c_str());
      else if (key.compare("JoinIdenticalVerts", 0U, String::NoCase) == 0)
         JoinIdenticalVerts = dAtob(value.c_str());
      else if (key.compare("reverseWindingOrder", 0U, String::NoCase) == 0)
         reverseWindingOrder = dAtob(value.c_str());
      else if (key.compare("invertNormals", 0U, String::NoCase) == 0)
         invertNormals = dAtob(value.c_str());
   }

   fileObj->close();
   fileObj->deleteObject();
}

void AssetImporter::processImportAssets(AssetImportObject* assetItem)
{
   Vector<AssetImportObject*> itemList = importingAssets;
   if (assetItem != nullptr)
      itemList = assetItem->childAssetItems;

   assetHeirarchyChanged = false;

   for (U32 i = 0; i < itemList.size(); i++)
   {
      AssetImportObject* item = itemList[i];
      if (item->importStatus != AssetImportObject::NotProcessed)
         continue;

      //Sanitize before modifying our asset name(suffix additions, etc)
      if (item->assetName != item->cleanAssetName)
         item->assetName = item->cleanAssetName;

		//process the asset items
		if (item->assetType == String("ImageAsset"))
		{
		   processImageAsset(item);
		}
		else if (item->assetType == String("ShapeAsset"))
		{
		   processShapeAsset(item);
		}
		else if (item->assetType == String("SoundAsset"))
		{
		   processSoundAsset(item);
		}
		else if (item->assetType == String("MaterialAsset"))
		{
		   processMaterialAsset(item);
		}
      else if (item->assetType == String("ShapeAnimationAsset"))
      {
         processShapeAnimationAsset(item);
      }
      else
      {
         String processCommand = "process";
         processCommand += item->assetType;
         if (isMethod(processCommand.c_str()))
            Con::executef(this, processCommand.c_str(), item);
      }

      //If we've already set our status in the processing phase, don't override that new status
      if(item->importStatus == AssetImportObject::NotProcessed)
         item->importStatus = AssetImportObject::Processed;

      //try recusing on the children(if any)
      processImportAssets(item);
   }

   //If our hierarchy changed, it's because we did so during processing
   //so we'll loop back through again until everything has been processed
   if (assetHeirarchyChanged)
      processImportAssets();
}

void AssetImporter::processImageAsset(AssetImportObject* assetItem)
{
   dSprintf(importLogBuffer, sizeof(importLogBuffer), "Preparing Image for Import: %s", assetItem->assetName.c_str());
   activityLog.push_back(importLogBuffer);

   if ((activeImportConfig->GenerateMaterialOnImport && assetItem->parentAssetItem == nullptr)/* || assetItem->parentAssetItem != nullptr*/)
   {
      //find our suffix match, if any
      String noSuffixName = assetItem->assetName;
      String suffixType;
      String suffix = parseImageSuffixes(assetItem->assetName, &suffixType);

      if (suffix.isNotEmpty())
      {
         assetItem->imageSuffixType = suffixType;
         S32 suffixPos =assetItem->assetName.find(suffix, 0, String::NoCase|String::Left);
         noSuffixName = assetItem->assetName.substr(0, suffixPos);
      }

      //We try to automatically populate materials under the naming convention: materialName: Rock, image maps: Rock_Albedo, Rock_Normal, etc

      AssetImportObject* materialAsset = findImportingAssetByName(noSuffixName);
      if (materialAsset != nullptr && materialAsset->assetType != String("MaterialAsset"))
      {
         //We may have a situation where an asset matches the no-suffix name, but it's not a material asset. Ignore this
         //asset item for now

         materialAsset = nullptr;
      }

      //If we didn't find a matching material asset in our current items, we'll make one now
      if (materialAsset == nullptr)
      {
         if (!assetItem->filePath.isEmpty())
         {
            materialAsset = addImportingAsset("MaterialAsset", assetItem->filePath, nullptr, noSuffixName);
         }
      }

      //Not that, one way or another, we have the generated material asset, lets move on to associating our image with it
      if (materialAsset != nullptr && materialAsset != assetItem->parentAssetItem)
      {
         if (assetItem->parentAssetItem != nullptr)
         {
            //If the image had an existing parent, it gets removed from that parent's child item list
            assetItem->parentAssetItem->childAssetItems.remove(assetItem);
         }
         else
         {
            //If it didn't have one, we're going to pull it from the importingAssets list
            importingAssets.remove(assetItem);
         }

         //Now we can add it to the correct material asset
         materialAsset->childAssetItems.push_back(assetItem);
         assetItem->parentAssetItem = materialAsset;

         assetHeirarchyChanged = true;
      }

      //Now to do some cleverness. If we're generating a material, we can parse like assets being imported(similar filenames) but different suffixes
      //If we find these, we'll just populate into the original's material

      //if we need to append the diffuse suffix and indeed didn't find a suffix on the name, do that here
      if (suffixType.isEmpty())
      {
         if (activeImportConfig->UseDiffuseSuffixOnOriginImage)
         {
            String diffuseToken = StringUnit::getUnit(activeImportConfig->DiffuseTypeSuffixes, 0, ",;\t");
            assetItem->assetName = assetItem->assetName + diffuseToken;
            //assetItem->cleanAssetName = assetItem->assetName;
         }
         else
         {
            //We need to ensure that our image asset doesn't match the same name as the material asset, so if we're not trying to force the diffuse suffix
            //we'll give it a generic one
            if ((materialAsset && materialAsset->assetName.compare(assetItem->assetName) == 0) || activeImportConfig->AlwaysAddImageSuffix)
            {
               assetItem->assetName = assetItem->assetName + activeImportConfig->AddedImageSuffix;
               //assetItem->cleanAssetName = assetItem->assetName;
            }
         }

         //Assume for abledo if it has no suffix matches
         assetItem->imageSuffixType = "Albedo";
      }
      else
      {

      }
   }
   else
   {
      //If we're processing an unaffiliated image without generating materials for it, we can check some other bits
      if (assetItem->parentAssetItem == nullptr)
      {
         if (assetItem->typeHint != String::EmptyString)
         {
            ImageAssetType type = ImageAsset::getImageTypeFromName(StringTable->insert(assetItem->typeHint.c_str()));

            if (type == ImageAssetType::GUI)
            {

            }
         }
      }
   }

   if(assetItem->assetName == assetItem->cleanAssetName && activeImportConfig->AlwaysAddImageSuffix)
   {
      if (!assetItem->assetName.endsWith(activeImportConfig->AddedImageSuffix.c_str()))
         assetItem->assetName = assetItem->assetName + activeImportConfig->AddedImageSuffix;
   }

   assetItem->importStatus = AssetImportObject::Processed;
}

void AssetImporter::processMaterialAsset(AssetImportObject* assetItem)
{
   dSprintf(importLogBuffer, sizeof(importLogBuffer), "Preparing Material for Import: %s", assetItem->assetName.c_str());
   activityLog.push_back(importLogBuffer);

   String filePath = assetItem->filePath.getFullPath();
   String fileName = assetItem->filePath.getFileName();
   String fileExt = assetItem->filePath.getExtension();
   const char* assetName = assetItem->assetName.c_str();

   assetItem->generatedAsset = true;

   if (activeImportConfig->IgnoreMaterials.isNotEmpty())
   {
      U32 ignoredMatNameCount = StringUnit::getUnitCount(activeImportConfig->IgnoreMaterials, ",;\t");
      for (U32 i = 0; i < ignoredMatNameCount; i++)
      {
         String ignoredName = StringUnit::getUnit(activeImportConfig->IgnoreMaterials, i, ",;\t");
         if (FindMatch::isMatch(ignoredName.c_str(), assetName, false))
         {
            assetItem->importStatus = AssetImportObject::Skipped;

            dSprintf(importLogBuffer, sizeof(importLogBuffer), "Material %s has been ignored due to it's name being listed in the IgnoreMaterials list in the Import Config.", assetItem->assetName.c_str());
            activityLog.push_back(importLogBuffer);
            return;
         }
      }
   }

   bool foundExistingMaterial = false;
   if (activeImportConfig->UseExistingMaterials)
   {
      //So if the material already exists, we should just use that. So first, let's find out if it already exists

      //check to see if the definition for this already exists
      StringTableEntry existingMatAsset = MaterialAsset::getAssetIdByMaterialName(StringTable->insert(assetName));

      if (existingMatAsset != StringTable->EmptyString() && existingMatAsset != StringTable->insert("Core_Rendering:NoMaterial"))
      {
         assetItem->importStatus = AssetImportObject::UseForDependencies;
         dSprintf(importLogBuffer, sizeof(importLogBuffer), "Material %s has been skipped because we already found an asset Id that uses that material definition. The found assetId is: %s", assetItem->assetName.c_str(), existingMatAsset);
         activityLog.push_back(importLogBuffer);
         return;
      }

      //If there was no existing assetId, then lets see if it already exists in a legacy file, like a materials.cs or materials.tscript
      //If it does, we'll just make our asset point to that instead of a new file
      Material* mat;
      Sim::findObject(assetName, mat);

      if (!mat)
         mat = MATMGR->getMaterialDefinitionByMapTo(assetName);

      if (!mat && assetItem->assetName != assetItem->cleanAssetName)
      {
         mat = MATMGR->getMaterialDefinitionByName(assetItem->cleanAssetName);

         if (!mat)
            mat = MATMGR->getMaterialDefinitionByMapTo(assetItem->cleanAssetName);
      }

      if(mat)
      {
         //We found a match, so just modify our asset item's info to point against it. This will create the asset definition, but otherwise leave the material definition as-is.
         assetItem->filePath = (Torque::Path)(mat->getFilename());
         foundExistingMaterial = true;
      }
   }

   if(!foundExistingMaterial)
   {
      if (activeImportConfig->AlwaysAddMaterialSuffix) //we only opt to force on the suffix if we're not obligating using the original material defs
      {
         if(!assetItem->assetName.endsWith(activeImportConfig->AddedMaterialSuffix.c_str()))
            assetItem->assetName += activeImportConfig->AddedMaterialSuffix;
      }

      if (activeImportConfig->PopulateMaterialMaps)
      {
         //If we're trying to populate the rest of our material maps, we need to go looking
         dSprintf(importLogBuffer, sizeof(importLogBuffer), "Attempting to Auto-Populate Material Maps");
         activityLog.push_back(importLogBuffer);

         AssetImportObject* matchedImageTypes[ImageAsset::ImageTypeCount] = { nullptr };

         String materialImageNoSuffix;

         for (U32 i = 0; i < assetItem->childAssetItems.size(); i++)
         {
            AssetImportObject* childAssetItem = assetItem->childAssetItems[i];

            if (childAssetItem->importStatus == AssetImportObject::Skipped || childAssetItem->assetType != String("ImageAsset"))
               continue;

            for (S32 t = 0; t < ImageAsset::ImageTypeCount; t++)
            {
               //If the imageType name and child asset image type match, check it off our list
               if (!dStricmp(ImageAsset::getImageTypeNameFromType((ImageAsset::ImageTypes)t), childAssetItem->imageSuffixType.c_str()))
               {
                  matchedImageTypes[t] = childAssetItem;

                  if (t == ImageAsset::ImageTypes::Albedo)
                  {
                     String sufType;
                     String suffix = parseImageSuffixes(childAssetItem->assetName, &sufType);

                     String imageAssetName = childAssetItem->assetName;

                     if (suffix.isEmpty())
                        materialImageNoSuffix = imageAssetName;
                     else
                        materialImageNoSuffix = imageAssetName.erase(imageAssetName.length() - suffix.length(), suffix.length());//cache this for later as we may need it for file association lookups
                  }
               }
            }
         }

         //Now that we've checked off any existingly matched image types, process through the unmatched to look for files that associate
         for (S32 t = 0; t < ImageAsset::ImageTypeCount; t++)
         {
            //This type wasn't found, so try and find a match based on suffix
            String suffixList;

            switch (t)
            {
            case ImageAsset::Albedo:
               suffixList = activeImportConfig->DiffuseTypeSuffixes;
               break;
            case ImageAsset::Normal:
               suffixList = activeImportConfig->NormalTypeSuffixes;
               break;
            case ImageAsset::ORMConfig:
               suffixList = activeImportConfig->PBRTypeSuffixes;
               break;
            case ImageAsset::Metalness:
               suffixList = activeImportConfig->MetalnessTypeSuffixes;
               break;
            case ImageAsset::AO:
               suffixList = activeImportConfig->AOTypeSuffixes;
               break;
            case ImageAsset::Roughness:
               suffixList = activeImportConfig->RoughnessTypeSuffixes;
               break;
               //TODO: Glow map lookup too
            }

            if (!matchedImageTypes[t])
            {
               U32 suffixCount = StringUnit::getUnitCount(suffixList.c_str(), ",;\t");
               for (U32 i = 0; i < suffixCount; i++)
               {
                  //First, try checking based on the material's assetName for our patternbase
                  String testPath = assetItem->filePath.getRootAndPath();
                  testPath += "/" + assetItem->cleanAssetName + StringUnit::getUnit(suffixList.c_str(), i, ",;\t");

                  String imagePath = AssetImporter::findImagePath(testPath);

                  if (imagePath.isNotEmpty())
                  {
                     //got a match!
                     AssetImportObject* newImageAssetObj = addImportingAsset("ImageAsset", imagePath, assetItem, "");

                     newImageAssetObj->imageSuffixType = ImageAsset::getImageTypeNameFromType((ImageAsset::ImageTypes)t);

                     matchedImageTypes[t] = newImageAssetObj;
                     break;
                  }
                  else
                  {
                     //Check to see if our target module has a matching assetId for this slot already
                     String testAssetId = targetModuleId + ":" + assetItem->cleanAssetName + StringUnit::getUnit(suffixList.c_str(), i, ",;\t");
                     bool localAssetFound = false;

                     if (AssetDatabase.isDeclaredAsset(testAssetId.c_str()))
                        localAssetFound = true;

                     if (localAssetFound == false)
                        //Didn't work, try checking the common default type suffix
                        testAssetId = targetModuleId + ":" + assetItem->cleanAssetName + StringUnit::getUnit(suffixList.c_str(), i, ",;\t") + activeImportConfig->AddedImageSuffix;

                     if (localAssetFound)
                     {
                        //got a match!
                        ImageAsset* foundImageAsset = AssetDatabase.acquireAsset<ImageAsset>(testAssetId.c_str());
                        imagePath = foundImageAsset->getImagePath();

                        AssetImportObject* newImageAssetObj = addImportingAsset("ImageAsset", imagePath, assetItem, "");

                        newImageAssetObj->imageSuffixType = ImageAsset::getImageTypeNameFromType((ImageAsset::ImageTypes)t);
                        newImageAssetObj->importStatus = AssetImportObject::UseForDependencies; //we aren't going to actually IMPORT an already imported asset,
                                                                                                //so mark it as dependency use only
                        matchedImageTypes[t] = newImageAssetObj;
                        break;
                     }

                     if (materialImageNoSuffix.isNotEmpty())
                     {
                        testPath = assetItem->filePath.getRootAndPath();
                        testPath += "/" + materialImageNoSuffix + StringUnit::getUnit(suffixList.c_str(), i, ",;\t");

                        imagePath = AssetImporter::findImagePath(testPath);

                        if (imagePath.isNotEmpty())
                        {
                           //got a match!
                           AssetImportObject* newImageAssetObj = addImportingAsset("ImageAsset", imagePath, assetItem, "");

                           newImageAssetObj->imageSuffixType = ImageAsset::getImageTypeNameFromType((ImageAsset::ImageTypes)t);

                           matchedImageTypes[t] = newImageAssetObj;
                           break;
                        }

                        //Check to see if our target module has a matching assetId for this slot already based on our trimmed mat name
                        testAssetId = targetModuleId + ":" + materialImageNoSuffix + StringUnit::getUnit(suffixList.c_str(), i, ",;\t");
                        bool localAssetFound = false;

                        if (AssetDatabase.isDeclaredAsset(testAssetId.c_str()))
                           localAssetFound = true;

                        if (localAssetFound == false)
                           //Didn't work, try checking the common default type suffix
                           testAssetId = targetModuleId + ":" + materialImageNoSuffix + StringUnit::getUnit(suffixList.c_str(), i, ",;\t") + activeImportConfig->AddedImageSuffix;

                        if (localAssetFound)
                        {
                           //got a match!
                           ImageAsset* foundImageAsset = AssetDatabase.acquireAsset<ImageAsset>(testAssetId.c_str());
                           imagePath = foundImageAsset->getImagePath();

                           AssetImportObject* newImageAssetObj = addImportingAsset("ImageAsset", imagePath, assetItem, "");

                           newImageAssetObj->imageSuffixType = ImageAsset::getImageTypeNameFromType((ImageAsset::ImageTypes)t);
                           newImageAssetObj->importStatus = AssetImportObject::UseForDependencies; //we aren't going to actually IMPORT an already imported asset,
                                                                                                   //so mark it as dependency use only
                           matchedImageTypes[t] = newImageAssetObj;
                           break;
                        }
                     }
                  }
               }

               //If we're the abledo slot and after all that we didn't find anything, it probably is a suffixless image
               if (t == ImageAsset::Albedo && matchedImageTypes[t] == nullptr)
               {
                  String testPath = assetItem->filePath.getRootAndPath() + "/" + assetItem->cleanAssetName;
                  String imagePath = AssetImporter::findImagePath(testPath);

                  if (imagePath.isNotEmpty())
                  {
                     //got a match!
                     AssetImportObject* newImageAssetObj = addImportingAsset("ImageAsset", imagePath, assetItem, "");

                     //In the event that the names match, we want to avoid duplications, so we'll go ahead and append a suffix onto our new image asset
                     if (newImageAssetObj->assetName == assetItem->assetName)
                     {
                        newImageAssetObj->assetName += StringUnit::getUnit(suffixList.c_str(), 0, ",;\t");
                        //newImageAssetObj->cleanAssetName = newImageAssetObj->assetName;
                     }

                     newImageAssetObj->imageSuffixType = ImageAsset::getImageTypeNameFromType(ImageAsset::ImageTypes::Albedo);

                     matchedImageTypes[t] = newImageAssetObj;
                  }
               }
            }
            else
            {
               //just a bit of cleanup and logical testing for matches
               //in the event we KNOW what the type is, but we don't have a suffix, such as a found image on a material lookup
               //that doesn't have a suffix, we assume it to be the albedo, so we'll just append the suffix to avoid collisions if
               //the name already matches our material name, similar to above logic
               if (matchedImageTypes[t]->assetName == assetItem->assetName)
               {
                  matchedImageTypes[t]->assetName += StringUnit::getUnit(suffixList.c_str(), 0, ",;\t");
                  //matchedImageTypes[t]->cleanAssetName = matchedImageTypes[t]->assetName;
               }
            }
         }
      }
   }
   
   assetItem->importStatus = AssetImportObject::Processed;
}

void AssetImporter::processShapeAsset(AssetImportObject* assetItem)
{
   dSprintf(importLogBuffer, sizeof(importLogBuffer), "Preparing Shape for Import: %s", assetItem->assetName.c_str());
   activityLog.push_back(importLogBuffer);

   String filePath = assetItem->filePath.getFullPath();
   String fileName = assetItem->filePath.getFileName();
   String fileExt = assetItem->filePath.getExtension();

   if (assetItem->shapeInfo == nullptr)
   {
      GuiTreeViewCtrl* shapeInfo = new GuiTreeViewCtrl();
      shapeInfo->registerObject();

      if (fileExt.compare("dae") == 0)
      {
         enumColladaForImport(filePath, shapeInfo, false);
      }
      else if (fileExt.compare("dts") == 0)
      {
         enumDTSForImport(filePath, shapeInfo);
      }
      else
      {
         // Check if a cached DTS is available => no need to import the source file
         // if we can load the DTS instead

         AssimpShapeLoader loader;
         loader.fillGuiTreeView(filePath.c_str(), shapeInfo);
      }

      assetItem->shapeInfo = shapeInfo;
   }

   if (activeImportConfig->AlwaysAddShapeSuffix)
   {
      if(!assetItem->assetName.endsWith(activeImportConfig->AddedShapeSuffix.c_str()))
         assetItem->assetName += activeImportConfig->AddedShapeSuffix;
   }

   S32 meshCount = dAtoi(assetItem->shapeInfo->getDataField(StringTable->insert("_meshCount"), nullptr));

   S32 animCount = dAtoi(assetItem->shapeInfo->getDataField(StringTable->insert("_animCount"), nullptr));

   S32 materialCount = dAtoi(assetItem->shapeInfo->getDataField(StringTable->insert("_materialCount"), nullptr));
   S32 matItem = assetItem->shapeInfo->findItemByName("Materials");

   dSprintf(importLogBuffer, sizeof(importLogBuffer), "   Shape Info: Mesh Count: %i | Material Count: %i | Anim Count: %i", meshCount, animCount, materialCount);
   activityLog.push_back(importLogBuffer);

   AssetImportConfig* cachedConfig = new AssetImportConfig();;
   cachedConfig->registerObject();
   activeImportConfig->CopyTo(cachedConfig);

   if (!activeImportConfig->UseManualShapeConfigRules)
   {
      //Try and load a sis file if it exists for this format
      activeImportConfig->loadSISFile(assetItem->filePath);
   }

   if (activeImportConfig->ImportMesh && meshCount > 0)
   {

   }

   if (activeImportConfig->ImportAnimations && animCount > 0)
   {
      //If we have animations but no meshes, then this is a pure animation file so we can swap the asset type here
      if (meshCount == 0)
      {
         assetItem->assetType = "ShapeAnimationAsset";
      }
   }

   if (activeImportConfig->ImportMaterials && materialCount > 0)
   {
      S32 materialId = assetItem->shapeInfo->getChildItem(matItem);
      processShapeMaterialInfo(assetItem, materialId);

      materialId = assetItem->shapeInfo->getNextSiblingItem(materialId);
      while (materialId != 0)
      {
         processShapeMaterialInfo(assetItem, materialId);
         materialId = assetItem->shapeInfo->getNextSiblingItem(materialId);
      }
   }

   //restore the cached version just in case we loaded a sis file
   cachedConfig->CopyTo(activeImportConfig);
   cachedConfig->deleteObject();

   assetItem->importStatus = AssetImportObject::Processed;
}

void AssetImporter::processShapeAnimationAsset(AssetImportObject* assetItem)
{
   dSprintf(importLogBuffer, sizeof(importLogBuffer), "Preparing Shape Animation for Import: %s", assetItem->assetName.c_str());
   activityLog.push_back(importLogBuffer);

   String filePath = assetItem->filePath.getFullPath();
   String fileName = assetItem->filePath.getFileName();
   String fileExt = assetItem->filePath.getExtension();

   if (assetItem->shapeInfo == nullptr)
   {
      GuiTreeViewCtrl* shapeInfo = new GuiTreeViewCtrl();
      shapeInfo->registerObject();

      if (fileExt.compare("dae") == 0)
      {
         enumColladaForImport(filePath, shapeInfo, false);
      }
      else if (fileExt.compare("dts") == 0 || fileExt.compare("dsq") == 0)
      {
         enumDTSForImport(filePath, shapeInfo);
      }
      else
      {
         // Check if a cached DTS is available => no need to import the source file
         // if we can load the DTS instead

         AssimpShapeLoader loader;
         loader.fillGuiTreeView(filePath.c_str(), shapeInfo);
      }

      assetItem->shapeInfo = shapeInfo;
   }

   if (activeImportConfig->AlwaysAddShapeAnimationSuffix)
   {
      if (!assetItem->assetName.endsWith(activeImportConfig->AddedShapeAnimationSuffix.c_str()))
         assetItem->assetName += activeImportConfig->AddedShapeAnimationSuffix;
   }

   S32 animCount = dAtoi(assetItem->shapeInfo->getDataField(StringTable->insert("_animCount"), nullptr));

   dSprintf(importLogBuffer, sizeof(importLogBuffer), "   Shape Animation Info: Anim Count: %i", animCount);
   activityLog.push_back(importLogBuffer);

   AssetImportConfig* cachedConfig = new AssetImportConfig();;
   cachedConfig->registerObject();
   activeImportConfig->CopyTo(cachedConfig);

   if (!activeImportConfig->UseManualShapeConfigRules)
   {
      //Try and load a sis file if it exists for this format
      activeImportConfig->loadSISFile(assetItem->filePath);
   }

   if (activeImportConfig->ImportAnimations && animCount > 0)
   {
      
   }

   //restore the cached version just in case we loaded a sis file
   cachedConfig->CopyTo(activeImportConfig);
   cachedConfig->deleteObject();

   assetItem->importStatus = AssetImportObject::Processed;
}

void AssetImporter::processShapeMaterialInfo(AssetImportObject* assetItem, S32 materialItemId)
{
   String matName = assetItem->shapeInfo->getItemText(materialItemId);
   String matAssetName = matName;

   if (matName == assetItem->assetName)
   {
      //So apparently we managed to name the material the same as the shape. So we'll tweak the name
      matAssetName += activeImportConfig->AddedMaterialSuffix;
   }

   //Do a check so we don't import materials that are on our ignore list
   if (activeImportConfig->IgnoreMaterials.isNotEmpty())
   {
      U32 ignoredMatNamesCount = StringUnit::getUnitCount(activeImportConfig->IgnoreMaterials, ",;\t");
      for (U32 i = 0; i < ignoredMatNamesCount; i++)
      {
         const char* ignoreMatName = StringUnit::getUnit(activeImportConfig->IgnoreMaterials, i, ",;\t");
         if (FindMatch::isMatch(ignoreMatName, matName.c_str(), false))
         {
            //If we have a match to one of our ignore names, just bail out here and skip the material wholesale
            return;
         }
      }
   }

   String materialItemValue = assetItem->shapeInfo->getItemValue(materialItemId);

   AssetImportObject* matAssetItem = nullptr;

   //If it happens to just be a color value instead of an image, we'll go ahead and skip doing any lookups
   //TODO: properly map the 'texture' color to the material that gets created
   if (materialItemValue.startsWith("Color:"))
   {
      matAssetItem = addImportingAsset("MaterialAsset", "", assetItem, matName);
   }
   else
   {
      Torque::Path filePath = materialItemValue;
      String fullFilePath = filePath.getFullPath().c_str();
      String shapePathBase = assetItem->filePath.getRootAndPath();

      if (fullFilePath.isNotEmpty())
      {
         if (!Torque::FS::IsFile(fullFilePath.c_str()))
         {
            //could be a stale path reference, such as if it was downloaded elsewhere. Trim to just the filename and see
            //if we can find it there
            
            //trim (not found) if needbe
            fullFilePath = fullFilePath.replace(" (Not Found)", "");
            fullFilePath = fullFilePath.replace(" (not found)", "");

            if(filePath.getPath().isEmpty())
               fullFilePath = shapePathBase + "/" + fullFilePath;
 
            if (Torque::FS::IsFile(fullFilePath.c_str()))
            {
               filePath = Torque::Path(fullFilePath);
            }
            else
            {
               //Hmm, didn't find it. It could be that the in-model filename could be different by virtue of
               //image extension. Some files have source content files like psd's, but the mesh was exported to use
               //a dds or png, etc
               Torque::Path testFilePath = fullFilePath;
               String imgFileName = AssetImporter::findImagePath(testFilePath.getPath() + "/" + testFilePath.getFileName());
               if (imgFileName.isNotEmpty())
                  filePath = imgFileName;
               else
                  filePath = Torque::Path(""); //no luck, so we just won't try importing in the image
            }
         }
 
         matAssetItem = addImportingAsset("MaterialAsset", shapePathBase + "/" + matName, assetItem, matName);

         if (!filePath.isEmpty())
         {
            AssetImportObject* imageAssetItem = addImportingAsset("ImageAsset", filePath, matAssetItem, "");

            String suffixType;
            String suffix = parseImageSuffixes(imageAssetItem->assetName, &suffixType);
            if (suffix.isNotEmpty())
            {
               imageAssetItem->imageSuffixType = suffixType;
            }
            else
            {
               //we'll assume it's albedo
               imageAssetItem->imageSuffixType = "Albedo";
            }
         }
      }
      else
      {
         matAssetItem = addImportingAsset("MaterialAsset", shapePathBase + "/" + matName, assetItem, matName);
      }
   }

   //In the event we modified the asset name(such as appending _Mat to avoid naming conflicts) update the name here
   //This preseves the 'clean asset name' which we can later use for lookups and the like as needed
   if (matAssetItem && matAssetName != matName)
      matAssetItem->assetName = matAssetName;
}

void AssetImporter::processSoundAsset(AssetImportObject* assetItem)
{
   dSprintf(importLogBuffer, sizeof(importLogBuffer), "Preparing Sound for Import: %s", assetItem->assetName.c_str());
   activityLog.push_back(importLogBuffer);

   if (activeImportConfig->AlwaysAddSoundSuffix)
   {
      if (!assetItem->assetName.endsWith(activeImportConfig->AddedSoundSuffix.c_str()))
         assetItem->assetName += activeImportConfig->AddedSoundSuffix;
   }

   assetItem->importStatus = AssetImportObject::Processed;
}

//
// Validation
//

bool AssetImporter::validateAssets()
{
   importIssues = false;

   resetAssetValidationStatus();

   for (U32 i = 0; i < importingAssets.size(); i++)
   {
      validateAsset(importingAssets[i]);
      resolveAssetItemIssues(importingAssets[i]);
   }

   return importIssues;
}

void AssetImporter::validateAsset(AssetImportObject* assetItem)
{
   if (assetItem->importStatus == AssetImportObject::Skipped || assetItem->importStatus == AssetImportObject::NotProcessed
      || assetItem->importStatus == AssetImportObject::UseForDependencies)
      return;

   //If this item's already been marked as being in error, don't bother with it. It knows what it did.
   //This avoids running collision checks on an item already known to have a collision, which could erroneously
   //mark the original, not-colliding item as colliding with this item, invaliding both
   if (assetItem->status == String("Error") || assetItem->statusType.isNotEmpty())
   {
      importIssues = true;
      return;
   }

   //Runm this item against our other importing assets and check for any collisions
   if (checkAssetForCollision(assetItem))
   {
      importIssues = true;
      return;
   }

   if (!isReimport)
   {
      AssetQuery aQuery;
      U32 numAssetsFound = AssetDatabase.findAllAssets(&aQuery);

      for (U32 i = 0; i < numAssetsFound; i++)
      {
         StringTableEntry assetId = aQuery.mAssetList[i];

         ModuleDefinition* moduleDef = AssetDatabase.getAssetModuleDefinition(assetId);

         if ((moduleDef == NULL) || moduleDef->getModuleId() != StringTable->insert(targetModuleId.c_str()))
            continue;

         StringTableEntry assetName = AssetDatabase.getAssetName(assetId);

         if (assetName == StringTable->insert(assetItem->assetName.c_str()))
         {
            assetItem->status = "Error";
            assetItem->statusType = "DuplicateAsset";
            assetItem->statusInfo = "Duplicate asset names found within the target module!\nAsset \"" + assetItem->assetName + "\" of type \"" + assetItem->assetType + "\" has a matching name.\nPlease rename it and try again!";

            //log it
            dSprintf(importLogBuffer, sizeof(importLogBuffer), "Error! Asset %s has an identically named asset in the target module.", assetItem->assetName.c_str());
            activityLog.push_back(importLogBuffer);
            break;
         }
      }
   }

   if (!assetItem->filePath.isEmpty() && !assetItem->generatedAsset && !Torque::FS::IsFile(assetItem->filePath.getFullPath().c_str()))
   {
      assetItem->status = "Error";
      assetItem->statusType = "MissingFile";
      assetItem->statusInfo = "Unable to find file to be imported with provided path: " + assetItem->filePath + "\n Please select a valid file.";

      //log it
      dSprintf(importLogBuffer, sizeof(importLogBuffer), "Error! Asset %s's file at %s was not found.", assetItem->assetName.c_str(), assetItem->filePath.getFullPath().c_str());
      activityLog.push_back(importLogBuffer);
   }

   if (assetItem->status == String("Warning"))
   {
      if (activeImportConfig->WarningsAsErrors)
      {
         assetItem->status = "Error";

         //log it
         dSprintf(importLogBuffer, sizeof(importLogBuffer), "Error! Import configuration has treated an import warning as an error.", assetItem->assetName.c_str());
         activityLog.push_back(importLogBuffer);
      }
   }

   if (assetItem->status == String("Error"))
      importIssues = true;

   for (U32 i = 0; i < assetItem->childAssetItems.size(); i++)
   {
      validateAsset(assetItem->childAssetItems[i]);
      resolveAssetItemIssues(assetItem->childAssetItems[i]);
   }

   return;
}

void AssetImporter::resetAssetValidationStatus(AssetImportObject* assetItem)
{
   Vector<AssetImportObject*> itemList = importingAssets;
   if (assetItem != nullptr)
      itemList = assetItem->childAssetItems;

   for (U32 i = 0; i < itemList.size(); i++)
   {
      if (itemList[i]->importStatus == AssetImportObject::Skipped)
         continue;

      itemList[i]->status = "";
      itemList[i]->statusType = "";
      itemList[i]->statusInfo = "";

      //If it wasn't a match, try recusing on the children(if any)
      resetAssetValidationStatus(itemList[i]);
   }
}

bool AssetImporter::checkAssetForCollision(AssetImportObject* assetItemToCheck, AssetImportObject* assetItem)
{
   bool results = false;

   Vector<AssetImportObject*> itemList = importingAssets;
   if (assetItem != nullptr)
      itemList = assetItem->childAssetItems;

   for (U32 i = 0; i < itemList.size(); i++)
   {
      AssetImportObject* importingAsset = itemList[i];

      if (importingAsset->importStatus == AssetImportObject::Skipped || importingAsset->importStatus == AssetImportObject::UseForDependencies)
         continue;

      if ((assetItemToCheck->assetName.compare(importingAsset->assetName) == 0) && (assetItemToCheck->getId() != importingAsset->getId()))
      {
         //we do have a collision, note the collsion and bail out
         assetItemToCheck->status = "Warning";
         assetItemToCheck->statusType = "DuplicateImportAsset";
         assetItemToCheck->statusInfo = "Duplicate asset names found with importing assets!\nAsset \"" + importingAsset->assetName + "\" of the type \"" + importingAsset->assetType + "\" and \"" +
                                          assetItemToCheck->assetName + "\" of the type \"" + assetItemToCheck->assetType + "\" have matching names.\nPlease rename one of them.";

            dSprintf(importLogBuffer, sizeof(importLogBuffer), "Warning! Asset %s, type %s has a naming collision with another importing asset: %s, type %s",
               assetItemToCheck->assetName.c_str(), assetItemToCheck->assetType.c_str(),
               importingAsset->assetName.c_str(), importingAsset->assetType.c_str());
            activityLog.push_back(importLogBuffer);

         return true;
      }

      //If it wasn't a match, try recusing on the children(if any)
      results = checkAssetForCollision(assetItemToCheck, importingAsset);
      if (results)
         return results;
   }

   return results;
}

void AssetImporter::resolveAssetItemIssues(AssetImportObject* assetItem)
{
   if(assetItem->importStatus == AssetImportObject::UseForDependencies)
   {
      //if we've already marked as only existing for dependency reasons, we'll just skip resolving any issues with it
      importIssues = false;
      return;
   }
   if (assetItem->statusType == String("DuplicateImportAsset") || assetItem->statusType == String("DuplicateAsset"))
   {
      String humanReadableReason = assetItem->statusType == String("DuplicateImportAsset") ? "Importing asset was duplicate of another importing asset" : "Importing asset was duplicate of an existing asset";

      //get the config value for duplicateAutoResolution
      if (activeImportConfig->DuplicateAutoResolution == String("AutoPrune"))
      {
         //delete the item
         if (assetItem->parentAssetItem == nullptr)
         {
            //if there's no parent, just delete
            deleteImportingAsset(assetItem);
         }
         else
         {
            //otherwise, we'll likely want to retain our dependency for our parent
            assetItem->importStatus = AssetImportObject::UseForDependencies;
         }

         //log it's deletion
         dSprintf(importLogBuffer, sizeof(importLogBuffer), "Asset %s was autopruned due to %s as part of the Import Configuration", assetItem->assetName.c_str(), humanReadableReason.c_str());
         activityLog.push_back(importLogBuffer);

         importIssues = false;
      }
      else if (activeImportConfig->DuplicateAutoResolution == String("AutoRename"))
      {
         //Set trailing number
         String renamedAssetName = assetItem->assetName;
         String renamedAssetId = assetItem->moduleName + ":" + renamedAssetName;

         String addedSuffix;

         if (assetItem->assetType == String("ShapeAsset"))
            addedSuffix = activeImportConfig->AddedShapeSuffix;
         else if (assetItem->assetType == String("MaterialAsset"))
            addedSuffix = activeImportConfig->AddedMaterialSuffix;
         else if (assetItem->assetType == String("ImageAsset"))
            addedSuffix = activeImportConfig->AddedImageSuffix;
         else if (assetItem->assetType == String("SoundAsset"))
            addedSuffix = activeImportConfig->AddedSoundSuffix;

         //do the suffix if it isn't already on it
         if (!renamedAssetName.endsWith(addedSuffix.c_str()))
         {
            renamedAssetName += addedSuffix;
            renamedAssetId = assetItem->moduleName + ":" + renamedAssetName;
            assetItem->assetName = renamedAssetName;
         }

         //if still conflicted
         //add the directory prefix
         if (AssetDatabase.isDeclaredAsset(renamedAssetId.c_str()))
         {
            renamedAssetName = getFolderPrefixedName(assetItem);
            renamedAssetId = assetItem->moduleName + ":" + renamedAssetName;
            assetItem->assetName = renamedAssetName;
         }

         bool appendedNumber = false;
         U32 uniqueNumber = 0;
         while (AssetDatabase.isDeclaredAsset(renamedAssetId.c_str()))
         {
            uniqueNumber++;
            renamedAssetId = assetItem->moduleName + ":" + renamedAssetName + String::ToString(uniqueNumber);
            appendedNumber = true;
         }

         if (appendedNumber)
         {
            renamedAssetName += String::ToString(uniqueNumber);
         }

         //Log it's renaming
         dSprintf(importLogBuffer, sizeof(importLogBuffer), "Asset %s was renamed due to %s as part of the Import Configuration", assetItem->assetName.c_str(), humanReadableReason.c_str());
         activityLog.push_back(importLogBuffer);

         dSprintf(importLogBuffer, sizeof(importLogBuffer), "Asset %s was renamed to %s", assetItem->assetName.c_str(), renamedAssetName.c_str());
         activityLog.push_back(importLogBuffer);

         assetItem->assetName = renamedAssetName;

         //Whatever status we had prior is no longer relevent, so reset the status
         resetAssetValidationStatus(assetItem);
         importIssues = false;
      }
      else if (activeImportConfig->DuplicateAutoResolution == String("UseExisting"))
      {

      }
      else if (activeImportConfig->DuplicateAutoResolution == String("FolderPrefix"))
      {
         String renamedAssetName = getFolderPrefixedName(assetItem);

         //Log it's renaming
         dSprintf(importLogBuffer, sizeof(importLogBuffer), "Asset %s was renamed due to %s as part of the Import Configuration", assetItem->assetName.c_str(), humanReadableReason.c_str());
         activityLog.push_back(importLogBuffer);

         dSprintf(importLogBuffer, sizeof(importLogBuffer), "Asset %s was renamed to %s", assetItem->assetName.c_str(), renamedAssetName.c_str());
         activityLog.push_back(importLogBuffer);

         assetItem->assetName = renamedAssetName;

         //Whatever status we had prior is no longer relevent, so reset the status
         resetAssetValidationStatus(assetItem);
         importIssues = false;
      }
   }
   else if (assetItem->statusType == String("MissingFile"))
   {
      //Trigger callback to look?
   }
}

void AssetImporter::resetImportConfig()
{
   //use a default import config
   if (activeImportConfig == nullptr)
   {
      activeImportConfig = new AssetImportConfig();
      activeImportConfig->registerObject();
   }

   Settings* editorSettings;
   //See if we can get our editor settings
   if (Sim::findObject("EditorSettings", editorSettings))
   {
      String defaultImportConfig = editorSettings->value("Assets/AssetImporDefaultConfig");

      //If we found it, grab the import configs
      Settings* importConfigs;
      if (Sim::findObject("AssetImportSettings", importConfigs))
      {
         dSprintf(importLogBuffer, sizeof(importLogBuffer), "Loading import config: %s!", defaultImportConfig.c_str());
         activityLog.push_back(importLogBuffer);

         //Now load the editor setting-deigned config!
         activeImportConfig->loadImportConfig(importConfigs, defaultImportConfig.c_str());
      }
   }
}

//
// Importing
//
StringTableEntry AssetImporter::autoImportFile(Torque::Path filePath, String typeHint)
{
   //Just in case we're reusing the same importer object from another import session, nuke any existing files
   resetImportSession(true);

   String assetType = getAssetTypeByFile(filePath);

   if (assetType == String("Folder") || assetType == String("Zip"))
   {
      dSprintf(importLogBuffer, sizeof(importLogBuffer), "Unable to import file %s because it is a folder or zip.", filePath.getFullPath().c_str());
      activityLog.push_back(importLogBuffer);

      dumpActivityLog();
      return StringTable->EmptyString();
   }

   if (assetType.isEmpty())
   {
      dSprintf(importLogBuffer, sizeof(importLogBuffer), "Unable to import file %s because it is of an unrecognized/unsupported type.", filePath.getFullPath().c_str());
      activityLog.push_back(importLogBuffer);

      dumpActivityLog();
      return StringTable->EmptyString();
   }

   //Find out if the filepath has an associated module to it. If we're importing in-place, it needs to be within a module's directory
   ModuleDefinition* targetModuleDef = AssetImporter::getModuleFromPath(filePath);

   if (targetModuleDef == nullptr)
   {
      dSprintf(importLogBuffer, sizeof(importLogBuffer), "Unable to import file %s because it is not in a valid module folder.", filePath.getFullPath().c_str());
      activityLog.push_back(importLogBuffer);

      dumpActivityLog();
      return StringTable->EmptyString();
   }
   else
   {
      targetModuleId = targetModuleDef->getModuleId();
   }

   //set our path
   targetPath = filePath.getPath();

   resetImportConfig();

   AssetImportObject* assetItem = addImportingAsset(assetType, filePath, nullptr, "");

   processImportAssets();

   bool hasIssues = validateAssets();

   if (hasIssues)
   {
      //log it
      dSprintf(importLogBuffer, sizeof(importLogBuffer), "Error! Import process has failed due to issues discovered during validation!");
      activityLog.push_back(importLogBuffer);
   }
   else
   {
      importAssets();

      acquireAssets();
   }

   dumpActivityLog();

   if (hasIssues ||
      assetItem->importStatus == AssetImportObject::Skipped ||
      assetItem->importStatus == AssetImportObject::UseForDependencies ||
      assetItem->importStatus == AssetImportObject::Error)
   {
      return StringTable->EmptyString();
   }
   else
   {
      String assetId = targetModuleId + ":" + assetItem->assetName;
      return StringTable->insert(assetId.c_str());
   }
}

void AssetImporter::importAssets(AssetImportObject* assetItem)
{
   ModuleDefinition* moduleDef = ModuleDatabase.findModule(targetModuleId.c_str(), 1);

   if (moduleDef == nullptr)
   {
      dSprintf(importLogBuffer, sizeof(importLogBuffer), "AssetImporter::importAssets - Unable to find moduleId %s", targetModuleId.c_str());
      activityLog.push_back(importLogBuffer);
      dumpActivityLog();
      return;
   }

   Vector<AssetImportObject*> itemList = importingAssets;
   if (assetItem != nullptr)
      itemList = assetItem->childAssetItems;

   for (U32 i = 0; i < itemList.size(); i++)
   {
      AssetImportObject* item = itemList[i];
      if (!item->canImport())
         continue;

      Torque::Path assetPath;
      if (item->assetType == String("ImageAsset"))
      {
         assetPath = importImageAsset(item);
      }
      else if (item->assetType == String("ShapeAsset"))
      {
         assetPath = importShapeAsset(item);
      }
      else if (item->assetType == String("SoundAsset"))
      {
         assetPath = importSoundAsset(item);
      }
      else if (item->assetType == String("MaterialAsset"))
      {
         assetPath = importMaterialAsset(item);
      }
      else if (item->assetType == String("ShapeAnimationAsset"))
      {
         assetPath = importShapeAnimationAsset(item);
      }
      else
      {
         finalImportedAssetPath = String::EmptyString;

         String processCommand = "import";
         processCommand += item->assetType;
         if (isMethod(processCommand.c_str()))
         {
            Con::executef(this, processCommand.c_str(), item);

            assetPath = finalImportedAssetPath;
         }
      }
      /*else if (importingAssets[i]->assetType == String("ShapeAnimationAsset"))
         assetPath = ShapeAnimationAsset::importAsset(importingAssets[i]);*/

      if (assetPath.isEmpty() && item->assetType != String("MaterialAsset"))
      {
         dSprintf(importLogBuffer, sizeof(importLogBuffer), "AssetImporter::importAssets - Import attempt of %s failed, so skipping asset.", item->assetName.c_str());
         activityLog.push_back(importLogBuffer);

         continue;
      }
      else
      {
         //If we got a valid filepath back from the import action, then we know we're good to go and we can go ahead and register the asset!
         if (!isReimport)
         {
            bool registerSuccess = AssetDatabase.addDeclaredAsset(moduleDef, assetPath.getFullPath().c_str());

            String assetIdStr = item->moduleName + ":" + item->assetName;
            StringTableEntry assetId = StringTable->insert(assetIdStr.c_str());

            if (!registerSuccess)
            {
               dSprintf(importLogBuffer, sizeof(importLogBuffer), "AssetImporter::importAssets - Failed to successfully register new asset at path %s to moduleId %s", assetPath.getFullPath().c_str(), targetModuleId.c_str());
               activityLog.push_back(importLogBuffer);
            }
            else
            {
               //Any special-case post-reg stuff here
               if (item->assetType == String("ShapeAsset") || item->assetType == String("ShapeAnimationAsset"))
               {
                  //forcefully update it's shape constructor
                  TSShapeConstructor* tss = TSShapeConstructor::findShapeConstructorByAssetId(assetId);

                  if(tss)
                     tss->setShapeAssetId(assetId);
               }
            }
         }
         else
         {
            String assetId = item->moduleName + ":" + item->assetName;
            bool refreshSuccess = AssetDatabase.refreshAsset(assetId.c_str());

            if (!refreshSuccess)
            {
               dSprintf(importLogBuffer, sizeof(importLogBuffer), "AssetImporter::importAssets - Failed to refresh reimporting asset %s.", item->assetName.c_str());
               activityLog.push_back(importLogBuffer);
            }
         }
      }

      //Mark us as successfully imported
      item->importStatus = AssetImportObject::Imported;

      //recurse if needed
      importAssets(item);
   }

   dumpActivityLog();
}

void AssetImporter::acquireAssets(AssetImportObject* assetItem)
{
   Vector<AssetImportObject*> itemList = importingAssets;
   if (assetItem != nullptr)
      itemList = assetItem->childAssetItems;

   for (U32 i = 0; i < itemList.size(); i++)
   {
      AssetImportObject* item = itemList[i];
      if (item->importStatus == AssetImportObject::Skipped ||
         item->importStatus == AssetImportObject::NotProcessed ||
         item->importStatus == AssetImportObject::Error)
         continue;

      //recurse if needed, we want to process child items first for dependency reasons
      acquireAssets(item);

      //Go ahead and force the asset to load now just to kick it for immediate use
      String assetId = item->moduleName + ":" + item->assetName;

      if (AssetDatabase.isDeclaredAsset(assetId))
      {
         AssetBase* assetDef = AssetDatabase.acquireAsset<AssetBase>(assetId);
         AssetDatabase.releaseAsset(assetId);
      }
   }
}

//
// Type-specific import logic
//

Torque::Path AssetImporter::importImageAsset(AssetImportObject* assetItem)
{
   dSprintf(importLogBuffer, sizeof(importLogBuffer), "Beginning importing of Image Asset: %s", assetItem->assetName.c_str());
   activityLog.push_back(importLogBuffer);

   ImageAsset* newAsset = new ImageAsset();
   newAsset->registerObject();

   StringTableEntry assetName = StringTable->insert(assetItem->assetName.c_str());

   String imageFileName = assetItem->filePath.getFileName() + "." + assetItem->filePath.getExtension();
   String assetPath = targetPath + "/" + imageFileName;
   String tamlPath = targetPath + "/" + assetName + ".asset.taml";
   String originalPath = assetItem->filePath.getFullPath().c_str();

   char qualifiedFromFile[2048];
   char qualifiedToFile[2048];

#ifndef TORQUE_SECURE_VFS
   Platform::makeFullPathName(originalPath.c_str(), qualifiedFromFile, sizeof(qualifiedFromFile));
   Platform::makeFullPathName(assetPath.c_str(), qualifiedToFile, sizeof(qualifiedToFile));
#else
   dStrcpy(qualifiedFromFile, originalPath.c_str(), sizeof(qualifiedFromFile));
   dStrcpy(qualifiedToFile, assetPath.c_str(), sizeof(qualifiedToFile));
#endif
   
   newAsset->setAssetName(assetName);
   newAsset->setImageFileName(imageFileName.c_str());

   //If it's not a re-import, check that the file isn't being in-place imported. If it isn't, store off the original
   //file path for reimporting support later
   if (!isReimport && String::compare(qualifiedFromFile, qualifiedToFile) && Torque::FS::IsFile(qualifiedFromFile))
   {
      newAsset->setDataField(StringTable->insert("originalFilePath"), nullptr, qualifiedFromFile);
   }

   if (assetItem->typeHint != String::EmptyString)
   {
      newAsset->setImageType(ImageAsset::getImageTypeFromName(StringTable->insert(assetItem->typeHint.c_str())));
   }
   else
   {
      ImageAsset::ImageTypes imageType = ImageAsset::getImageTypeFromName(assetItem->imageSuffixType.c_str());
      newAsset->setImageType(imageType);
   }

   Taml tamlWriter;
   bool importSuccessful = tamlWriter.write(newAsset, tamlPath.c_str());

   if (!importSuccessful)
   {
      dSprintf(importLogBuffer, sizeof(importLogBuffer), "Error! Unable to write asset taml file %s", tamlPath.c_str());
      activityLog.push_back(importLogBuffer);
      return "";
   }

   if (!isReimport)
   {
      bool isInPlace = !String::compare(qualifiedFromFile, qualifiedToFile);

      if (!isInPlace && !Torque::FS::CopyFile(qualifiedFromFile, qualifiedToFile, !isReimport))
      {
         dSprintf(importLogBuffer, sizeof(importLogBuffer), "Error! Unable to copy file %s", assetItem->filePath.getFullPath().c_str());
         activityLog.push_back(importLogBuffer);
         return "";
      }
   }

   return tamlPath;
}

Torque::Path AssetImporter::importMaterialAsset(AssetImportObject* assetItem)
{
   dSprintf(importLogBuffer, sizeof(importLogBuffer), "Beginning importing of Material Asset: %s", assetItem->assetName.c_str());
   activityLog.push_back(importLogBuffer);

   MaterialAsset* newAsset = new MaterialAsset();
   newAsset->registerObject();

   StringTableEntry assetName = StringTable->insert(assetItem->assetName.c_str());

   String tamlPath = targetPath + "/" + assetName + ".asset.taml";
   String originalPath = assetItem->filePath.getFullPath().c_str();

   char qualifiedFromFile[2048];

#ifndef TORQUE_SECURE_VFS
   Platform::makeFullPathName(originalPath.c_str(), qualifiedFromFile, sizeof(qualifiedFromFile));
#else
   dStrcpy(qualifiedFromFile, originalPath.c_str(), sizeof(qualifiedFromFile));
#endif

   newAsset->setAssetName(assetName);

   if (!isReimport && Torque::FS::IsFile(qualifiedFromFile))
   {
   newAsset->setDataField(StringTable->insert("originalFilePath"), nullptr, qualifiedFromFile);
   }

   newAsset->setDataField(StringTable->insert("materialDefinitionName"), nullptr, assetName);

   //iterate through and write out the material maps dependencies
   S32 dependencySlotId = 0;
   for (U32 i = 0; i < assetItem->childAssetItems.size(); i++)
   {
      AssetImportObject* childItem = assetItem->childAssetItems[i];

      if ((!childItem->canImport() && childItem->importStatus != AssetImportObject::UseForDependencies) || childItem->assetType.compare("ImageAsset") != 0)
         continue;

      char dependencyFieldName[64];
      dSprintf(dependencyFieldName, 64, "imageMap%i", dependencySlotId);

      char dependencyFieldDef[512];
      dSprintf(dependencyFieldDef, 512, "%s=%s:%s", ASSET_ID_SIGNATURE, targetModuleId.c_str(), childItem->assetName.c_str());

      newAsset->setDataField(StringTable->insert(dependencyFieldName), nullptr, dependencyFieldDef);

      dependencySlotId++;
   }

   //build the ORMConfig file if we're flagged to and have valid image maps
   if (activeImportConfig->CreateORMConfig)
   {
      AssetImportObject* ormMap = nullptr;
      AssetImportObject* roughnessMap = nullptr;
      AssetImportObject* metalnessMap = nullptr;
      AssetImportObject* aoMap = nullptr;

      //We need to find any/all respective image maps for the given channels
      for (U32 i = 0; i < assetItem->childAssetItems.size(); i++)
      {
         AssetImportObject* childItem = assetItem->childAssetItems[i];

         if (childItem->canImport() || childItem->assetType.compare("ImageAsset") != 0)
            continue;

         if (childItem->imageSuffixType.compare("ORMConfig") == 0)
            ormMap = childItem;
         else if(childItem->imageSuffixType.compare("Roughness") == 0)
            roughnessMap = childItem;
         else if (childItem->imageSuffixType.compare("Metalness") == 0)
            metalnessMap = childItem;
         else if (childItem->imageSuffixType.compare("AO") == 0)
            aoMap = childItem;
      }

      if (ormMap != nullptr && ormMap->generatedAsset)
      {
         if (roughnessMap != nullptr || metalnessMap != nullptr || aoMap != nullptr)
         {
            U32 channelKey[4] = { 0,1,2,3 };

            GFX->getTextureManager()->saveCompositeTexture(aoMap->filePath.getFullPath(), roughnessMap->filePath.getFullPath(), metalnessMap->filePath.getFullPath(), "",
               channelKey, ormMap->filePath.getFullPath(), &GFXTexturePersistentProfile);
         }
      }
   }

   //If we're not using existing materials, or the material in question doesn't actually already exist, spool it up
   if (!activeImportConfig->UseExistingMaterials || !Sim::findObject(assetName))
   {
      Material* newMat = new Material();
      newMat->registerObject(assetName);
      newMat->mMapTo = assetItem->cleanAssetName;

      bool hasRoughness = false;
      for (U32 i = 0; i < assetItem->childAssetItems.size(); i++)
      {
         AssetImportObject* childItem = assetItem->childAssetItems[i];

         if ((!childItem->canImport() && childItem->importStatus != AssetImportObject::UseForDependencies) || childItem->assetType.compare("ImageAsset") != 0)
            continue;

         ImageAsset::ImageTypes imageType = ImageAsset::getImageTypeFromName(childItem->imageSuffixType);

         String assetMapFillIn = targetModuleId + ":" + childItem->assetName;
         StringTableEntry assetMapFillInStr = StringTable->insert(assetMapFillIn.c_str());

         if (imageType == ImageAsset::ImageTypes::Albedo || childItem->imageSuffixType.isEmpty())
         {
            newMat->mDiffuseMapAssetId[0] = assetMapFillInStr;
         }
         else if (imageType == ImageAsset::ImageTypes::Normal)
         {
            newMat->mNormalMapAssetId[0] = assetMapFillInStr;
         }
         else if (imageType == ImageAsset::ImageTypes::ORMConfig)
         {
            newMat->mORMConfigMapAssetId[0] = assetMapFillInStr;
         }
         else if (imageType == ImageAsset::ImageTypes::Metalness)
         {
            newMat->mMetalMapAssetId[0] = assetMapFillInStr;
         }
         else if (imageType == ImageAsset::ImageTypes::AO)
         {
            newMat->mAOMapAssetId[0] = assetMapFillInStr;
         }
         else if (imageType == ImageAsset::ImageTypes::Roughness)
         {
            newMat->mRoughMapAssetId[0] = assetMapFillInStr;
            hasRoughness = true;
         }
      }

      if (hasRoughness)
      {
         newMat->mInvertRoughness[0] = true;
      }

      newAsset->addObject(newMat);
   }
   else 
   {
      dSprintf(importLogBuffer, sizeof(importLogBuffer), "Set to use an existing material, so avoiding writing a material definition to new asset definition for material: %s", assetName);
      activityLog.push_back(importLogBuffer);
      return "";
   }

   Taml tamlWriter;
   bool importSuccessful = tamlWriter.write(newAsset, tamlPath.c_str());

   if (!importSuccessful)
   {
      dSprintf(importLogBuffer, sizeof(importLogBuffer), "Error! Unable to write asset taml file %s", tamlPath.c_str());
      activityLog.push_back(importLogBuffer);
      return "";
   }

   return tamlPath;
}

Torque::Path AssetImporter::importShapeAsset(AssetImportObject* assetItem)
{
   dSprintf(importLogBuffer, sizeof(importLogBuffer), "Beginning importing of Shape Asset: %s", assetItem->assetName.c_str());
   activityLog.push_back(importLogBuffer);

   ShapeAsset* newAsset = new ShapeAsset();
   newAsset->registerObject();

   StringTableEntry assetName = StringTable->insert(assetItem->assetName.c_str());

   String shapeFileName = assetItem->filePath.getFileName() + "." + assetItem->filePath.getExtension();
   String constructorFileName = assetItem->filePath.getFileName() + "." TORQUE_SCRIPT_EXTENSION;
   String assetPath = targetPath + "/" + shapeFileName;
   String constructorPath = targetPath + "/" + constructorFileName;
   String tamlPath = targetPath + "/" + assetName + ".asset.taml";
   String originalPath = assetItem->filePath.getFullPath().c_str();
   String originalConstructorPath = assetItem->filePath.getPath() + "/" + constructorFileName;

   char qualifiedFromFile[2048];
   char qualifiedToFile[2048];
   char qualifiedFromCSFile[2048];
   char qualifiedToCSFile[2048];

#ifndef TORQUE_SECURE_VFS
   Platform::makeFullPathName(originalPath.c_str(), qualifiedFromFile, sizeof(qualifiedFromFile));
   Platform::makeFullPathName(assetPath.c_str(), qualifiedToFile, sizeof(qualifiedToFile));
   Platform::makeFullPathName(originalConstructorPath.c_str(), qualifiedFromCSFile, sizeof(qualifiedFromCSFile));
   Platform::makeFullPathName(constructorPath.c_str(), qualifiedToCSFile, sizeof(qualifiedToCSFile));
#else
   dStrcpy(qualifiedFromFile, originalPath.c_str(), sizeof(qualifiedFromFile));
   dStrcpy(qualifiedToFile, assetPath.c_str(), sizeof(qualifiedToFile));
   dStrcpy(qualifiedFromCSFile, originalConstructorPath.c_str(), sizeof(qualifiedFromCSFile));
   dStrcpy(qualifiedToCSFile, constructorPath.c_str(), sizeof(qualifiedToCSFile));
#endif

   newAsset->setAssetName(assetName);
   newAsset->setShapeFile(shapeFileName.c_str());
   newAsset->setShapeConstructorFile(constructorFileName.c_str());

   AssetImportConfig* cachedConfig = new AssetImportConfig();
   cachedConfig->registerObject();
   activeImportConfig->CopyTo(cachedConfig);

   if (!activeImportConfig->UseManualShapeConfigRules)
   {
      //Try and load a sis file if it exists for this format
      activeImportConfig->loadSISFile(assetItem->filePath);
   }

   //If it's not a re-import, check that the file isn't being in-place imported. If it isn't, store off the original
   //file path for reimporting support later
   if (!isReimport && String::compare(qualifiedFromFile, qualifiedToFile) && Torque::FS::IsFile(qualifiedFromFile))
   {
      newAsset->setDataField(StringTable->insert("originalFilePath"), nullptr, qualifiedFromFile);
   }

   //iterate through and write out the material maps dependencies
   S32 dependencySlotId = 0;
   for (U32 i = 0; i < assetItem->childAssetItems.size(); i++)
   {
      AssetImportObject* childItem = assetItem->childAssetItems[i];

      if (!childItem->canImport() && childItem->importStatus != AssetImportObject::UseForDependencies)
         continue;

      if (childItem->assetType.compare("MaterialAsset") == 0)
      {
         char dependencyFieldName[64];
         dSprintf(dependencyFieldName, 64, "materialSlot%i", dependencySlotId);

         char dependencyFieldDef[512];
         dSprintf(dependencyFieldDef, 512, "%s=%s:%s", ASSET_ID_SIGNATURE, targetModuleId.c_str(), childItem->assetName.c_str());
  
         newAsset->setDataField(StringTable->insert(dependencyFieldName), nullptr, dependencyFieldDef);

         dependencySlotId++;
      }
      else if (childItem->assetType.compare("ShapeAnimationAsset") == 0)
      {
         char dependencyFieldName[64];
         dSprintf(dependencyFieldName, 64, "animationSequence%i", dependencySlotId);

         char dependencyFieldDef[512];
         dSprintf(dependencyFieldDef, 512, "%s=%s:%s", ASSET_ID_SIGNATURE, targetModuleId.c_str(), childItem->assetName.c_str());

         newAsset->setDataField(StringTable->insert(dependencyFieldName), nullptr, dependencyFieldDef);

         dependencySlotId++;
      }
   }

   if (Con::getBoolVariable("$TSLastDetail::dumpImposters", false))
   {
      String imposterPath = assetItem->assetName + "_imposter.png";
      String normalsPath = assetItem->assetName + "_imposter_normals.png";

      newAsset->setDiffuseImposterFile(imposterPath.c_str());
      newAsset->setNormalImposterFile(normalsPath.c_str());
   }

   Taml tamlWriter;
   bool importSuccessful = tamlWriter.write(newAsset, tamlPath.c_str());

   if (!importSuccessful)
   {
      dSprintf(importLogBuffer, sizeof(importLogBuffer), "Error! Unable to write asset taml file %s", tamlPath.c_str());
      activityLog.push_back(importLogBuffer);
      return "";
   }

   bool makeNewConstructor = true;
   if (!isReimport)
   {
      bool isInPlace = !String::compare(qualifiedFromFile, qualifiedToFile);

      if (!isInPlace && !Torque::FS::CopyFile(qualifiedFromFile, qualifiedToFile, !isReimport))
      {
         dSprintf(importLogBuffer, sizeof(importLogBuffer), "Error! Unable to copy file %s", qualifiedFromFile);
         activityLog.push_back(importLogBuffer);
         return "";
      }

      if (!isInPlace)
      {
         if (Torque::FS::IsFile(qualifiedFromCSFile))
         {
            if (!Torque::FS::CopyFile(qualifiedFromCSFile, qualifiedToCSFile, !isReimport))
            {
               dSprintf(importLogBuffer, sizeof(importLogBuffer), "Error! Unable to copy file %s", qualifiedFromCSFile);
               activityLog.push_back(importLogBuffer);
            }
            else
            {
               //We successfully copied the original constructor file, so no extra work required
               makeNewConstructor = false;
               dSprintf(importLogBuffer, sizeof(importLogBuffer), "Successfully copied original TSShape Constructor file %s", qualifiedFromCSFile);
               activityLog.push_back(importLogBuffer);
            }
         }
      }
      else
      {
         //We're doing an in-place import, so double check we've already got a constructor file in the expected spot
         if (Torque::FS::IsFile(qualifiedFromCSFile))
         {
            //Yup, found it, we're good to go
            makeNewConstructor = false;
            dSprintf(importLogBuffer, sizeof(importLogBuffer), "Existing TSShape Constructor file %s found", qualifiedFromCSFile);
            activityLog.push_back(importLogBuffer);
         }
         else
         {
            //Didn't work, but it's possible it's using the old .cs extension when our extension variable is set to something else, so check that one as well just to be sure
            Torque::Path constrFilePath = qualifiedFromCSFile;
            constrFilePath.setExtension("cs");

            if (Torque::FS::IsFile(constrFilePath.getFullPath().c_str()))
            {
               //Yup, found it, we're good to go
               makeNewConstructor = false;
               dSprintf(importLogBuffer, sizeof(importLogBuffer), "Existing TSShape Constructor file %s found", constrFilePath.getFullPath().c_str());
               activityLog.push_back(importLogBuffer);
            }
         }
      }
   }

   if (makeNewConstructor)
   {
      dSprintf(importLogBuffer, sizeof(importLogBuffer), "Beginning creation of new TSShapeConstructor file: %s", qualifiedToCSFile);
      activityLog.push_back(importLogBuffer);

      //find/create shape constructor
      TSShapeConstructor* constructor = TSShapeConstructor::findShapeConstructorByFilename(Torque::Path(qualifiedToFile).getFullPath());
      if (constructor == nullptr)
      {
         String fullAssetName = assetItem->moduleName + ":" + assetItem->assetName;
         constructor = new TSShapeConstructor(StringTable->insert(fullAssetName.c_str()));

         String constructorName = assetItem->filePath.getFileName() + assetItem->filePath.getExtension().substr(0, 3);
         constructorName.replace(" ", "_");
         constructorName.replace("-", "_");
         constructorName.replace(".", "_");
         constructorName = Sim::getUniqueName(constructorName.c_str());
         constructor->registerObject(constructorName.c_str());
      }

      //now we write the import config logic into the constructor itself to ensure we load like we wanted it to
      String neverImportMats;

      if (activeImportConfig->IgnoreMaterials.isNotEmpty())
      {
         U32 ignoredMatNamesCount = StringUnit::getUnitCount(activeImportConfig->IgnoreMaterials, ",;\t");
         for (U32 i = 0; i < ignoredMatNamesCount; i++)
         {
            if (i == 0)
               neverImportMats = StringUnit::getUnit(activeImportConfig->IgnoreMaterials, i, ",;\t");
            else
               neverImportMats += String("\t") + StringUnit::getUnit(activeImportConfig->IgnoreMaterials, i, ",;\t");
         }
      }

      if (activeImportConfig->DoUpAxisOverride)
      {
         S32 upAxis = domUpAxisType::UPAXISTYPE_Z_UP;
         if (activeImportConfig->UpAxisOverride.compare("X_AXIS") == 0)
         {
            upAxis = domUpAxisType::UPAXISTYPE_X_UP;
         }
         else if (activeImportConfig->UpAxisOverride.compare("Y_AXIS") == 0)
         {
            upAxis = domUpAxisType::UPAXISTYPE_Y_UP;
         }
         else if (activeImportConfig->UpAxisOverride.compare("Z_AXIS") == 0)
         {
            upAxis = domUpAxisType::UPAXISTYPE_Z_UP;
         }
         constructor->mOptions.upAxis = (domUpAxisType)upAxis;
      }

      if (activeImportConfig->DoScaleOverride)
         constructor->mOptions.unit = activeImportConfig->ScaleOverride;
      else
         constructor->mOptions.unit = -1;

      enum eAnimTimingType
      {
         FrameCount = 0,
         Seconds = 1,
         Milliseconds = 1000
      };

      S32 lodType = ColladaUtils::ImportOptions::eLodType::TrailingNumber;
      if (activeImportConfig->LODType.compare("TrailingNumber") == 0)
         lodType = ColladaUtils::ImportOptions::eLodType::TrailingNumber;
      else if (activeImportConfig->LODType.compare("SingleSize") == 0)
         lodType = ColladaUtils::ImportOptions::eLodType::SingleSize;
      else if (activeImportConfig->LODType.compare("DetectDTS") == 0)
         lodType = ColladaUtils::ImportOptions::eLodType::DetectDTS;
      constructor->mOptions.lodType = (ColladaUtils::ImportOptions::eLodType)lodType;

      constructor->mOptions.singleDetailSize = activeImportConfig->convertLeftHanded;
      constructor->mOptions.alwaysImport = activeImportConfig->AlwaysImportedNodes;
      constructor->mOptions.neverImport = activeImportConfig->AlwaysIgnoreNodes;
      constructor->mOptions.alwaysImportMesh = activeImportConfig->AlwaysImportMeshes;
      constructor->mOptions.neverImportMesh = activeImportConfig->AlwaysIgnoreMeshes;
      constructor->mOptions.ignoreNodeScale = activeImportConfig->IgnoreNodeScale;
      constructor->mOptions.adjustCenter = activeImportConfig->AdjustCenter;
      constructor->mOptions.adjustFloor = activeImportConfig->AdjustFloor;

      constructor->mOptions.convertLeftHanded = activeImportConfig->convertLeftHanded;
      constructor->mOptions.calcTangentSpace = activeImportConfig->calcTangentSpace;
      constructor->mOptions.genUVCoords = activeImportConfig->genUVCoords;
      constructor->mOptions.flipUVCoords = activeImportConfig->flipUVCoords;
      constructor->mOptions.findInstances = activeImportConfig->findInstances;
      constructor->mOptions.limitBoneWeights = activeImportConfig->limitBoneWeights;
      constructor->mOptions.joinIdenticalVerts = activeImportConfig->JoinIdenticalVerts;
      constructor->mOptions.reverseWindingOrder = activeImportConfig->reverseWindingOrder;
      constructor->mOptions.invertNormals = activeImportConfig->invertNormals;
      constructor->mOptions.removeRedundantMats = activeImportConfig->removeRedundantMats;

      S32 animTimingType;
      if (activeImportConfig->animTiming.compare("FrameCount") == 0)
         animTimingType = ColladaUtils::ImportOptions::eAnimTimingType::FrameCount;
      else if (activeImportConfig->animTiming.compare("Seconds") == 0)
         animTimingType = ColladaUtils::ImportOptions::eAnimTimingType::Seconds;
      else// (activeImportConfig->animTiming.compare("Milliseconds") == 0)
         animTimingType = ColladaUtils::ImportOptions::eAnimTimingType::Milliseconds;

      constructor->mOptions.animTiming = (ColladaUtils::ImportOptions::eAnimTimingType)animTimingType;

      constructor->mOptions.animFPS = activeImportConfig->animFPS;

      constructor->mOptions.neverImportMat = neverImportMats;

      PersistenceManager* constructorPersist = new PersistenceManager();
      constructorPersist->registerObject();
      constructorPersist->setDirty(constructor, qualifiedToCSFile);

      if (!constructorPersist->saveDirtyObject(constructor))
      {
         dSprintf(importLogBuffer, sizeof(importLogBuffer), "Error! Failed to save shape constructor file to %s", constructorPath.c_str());
         activityLog.push_back(importLogBuffer);
      }
      else
      {
         dSprintf(importLogBuffer, sizeof(importLogBuffer), "Finished creating shape constructor file to %s", constructorPath.c_str());
         activityLog.push_back(importLogBuffer);
      }

      constructorPersist->destroySelf();
   }

   //restore the cached version just in case we loaded a sis file
   cachedConfig->CopyTo(activeImportConfig);
   cachedConfig->deleteObject();

   return tamlPath;
}

Torque::Path AssetImporter::importSoundAsset(AssetImportObject* assetItem)
{
   dSprintf(importLogBuffer, sizeof(importLogBuffer), "Beginning importing of Sound Asset: %s", assetItem->assetName.c_str());
   activityLog.push_back(importLogBuffer);

   SoundAsset* newAsset = new SoundAsset();
   newAsset->registerObject();

   StringTableEntry assetName = StringTable->insert(assetItem->assetName.c_str());

   String imageFileName = assetItem->filePath.getFileName() + "." + assetItem->filePath.getExtension();
   String assetPath = targetPath + "/" + imageFileName;
   String tamlPath = targetPath + "/" + assetName + ".asset.taml";
   String originalPath = assetItem->filePath.getFullPath().c_str();

   char qualifiedFromFile[2048];
   char qualifiedToFile[2048];

#ifndef TORQUE_SECURE_VFS
   Platform::makeFullPathName(originalPath.c_str(), qualifiedFromFile, sizeof(qualifiedFromFile));
   Platform::makeFullPathName(assetPath.c_str(), qualifiedToFile, sizeof(qualifiedToFile));
#else
   dStrcpy(qualifiedFromFile, originalPath.c_str(), sizeof(qualifiedFromFile));
   dStrcpy(qualifiedToFile, assetPath.c_str(), sizeof(qualifiedToFile));
#endif

   newAsset->setAssetName(assetName);
   newAsset->setSoundFile(imageFileName.c_str());

   //If it's not a re-import, check that the file isn't being in-place imported. If it isn't, store off the original
   //file path for reimporting support later
   if (!isReimport && String::compare(qualifiedFromFile, qualifiedToFile) && Torque::FS::IsFile(qualifiedFromFile))
   {
      newAsset->setDataField(StringTable->insert("originalFilePath"), nullptr, qualifiedFromFile);
   }

   Taml tamlWriter;
   bool importSuccessful = tamlWriter.write(newAsset, tamlPath.c_str());

   if (!importSuccessful)
   {
      dSprintf(importLogBuffer, sizeof(importLogBuffer), "Error! Unable to write asset taml file %s", tamlPath.c_str());
      activityLog.push_back(importLogBuffer);
      return "";
   }

   if (!isReimport)
   {
      bool isInPlace = !String::compare(qualifiedFromFile, qualifiedToFile);

      if (!isInPlace && !Torque::FS::CopyFile(qualifiedFromFile, qualifiedToFile, !isReimport))
      {
         dSprintf(importLogBuffer, sizeof(importLogBuffer), "Error! Unable to copy file %s", assetItem->filePath.getFullPath().c_str());
         activityLog.push_back(importLogBuffer);
         return "";
      }
   }

   return tamlPath;
}

Torque::Path AssetImporter::importShapeAnimationAsset(AssetImportObject* assetItem)
{
   dSprintf(importLogBuffer, sizeof(importLogBuffer), "Beginning importing of Shape Animation Asset: %s", assetItem->assetName.c_str());
   activityLog.push_back(importLogBuffer);

   ShapeAnimationAsset* newAsset = new ShapeAnimationAsset();
   newAsset->registerObject();

   StringTableEntry assetName = StringTable->insert(assetItem->assetName.c_str());

   String imageFileName = assetItem->filePath.getFileName() + "." + assetItem->filePath.getExtension();
   String assetPath = targetPath + "/" + imageFileName;
   String tamlPath = targetPath + "/" + assetName + ".asset.taml";
   String originalPath = assetItem->filePath.getFullPath().c_str();

   char qualifiedFromFile[2048];
   char qualifiedToFile[2048];

#ifndef TORQUE_SECURE_VFS
   Platform::makeFullPathName(originalPath.c_str(), qualifiedFromFile, sizeof(qualifiedFromFile));
   Platform::makeFullPathName(assetPath.c_str(), qualifiedToFile, sizeof(qualifiedToFile));
#else
   dStrcpy(qualifiedFromFile, originalPath.c_str(), sizeof(qualifiedFromFile));
   dStrcpy(qualifiedToFile, assetPath.c_str(), sizeof(qualifiedToFile));
#endif

   newAsset->setAssetName(assetName);
   newAsset->setAnimationFile(imageFileName.c_str());

   //If it's not a re-import, check that the file isn't being in-place imported. If it isn't, store off the original
   //file path for reimporting support later
   if (!isReimport && String::compare(qualifiedFromFile, qualifiedToFile) && Torque::FS::IsFile(qualifiedFromFile))
   {
      newAsset->setDataField(StringTable->insert("originalFilePath"), nullptr, qualifiedFromFile);
   }

   Taml tamlWriter;
   bool importSuccessful = tamlWriter.write(newAsset, tamlPath.c_str());

   if (!importSuccessful)
   {
      dSprintf(importLogBuffer, sizeof(importLogBuffer), "Error! Unable to write asset taml file %s", tamlPath.c_str());
      activityLog.push_back(importLogBuffer);
      return "";
   }

   if (!isReimport)
   {
      bool isInPlace = !String::compare(qualifiedFromFile, qualifiedToFile);

      if (!isInPlace && !Torque::FS::CopyFile(qualifiedFromFile, qualifiedToFile, !isReimport))
      {
         dSprintf(importLogBuffer, sizeof(importLogBuffer), "Error! Unable to copy file %s", assetItem->filePath.getFullPath().c_str());
         activityLog.push_back(importLogBuffer);
         return "";
      }
   }

   return tamlPath;
}
