#pragma once

#include "assets/assetPtr.h"
#include "assets/assetManager.h"
#include "module/moduleManager.h"
#include "util/settings.h"
#include "gui/controls/guiTreeViewCtrl.h"

/// <summary>
/// AssetImportConfig is a SimObject derived object intended to act as a container for all the necessary configuration data when running the Asset Importer.
/// It dictates if and how any given asset type will be processed when running an import action. This is because the Asset Importer utilizes a lot of informed logic
/// to try and automate as much of the import process as possible. In theory, you would run the import on a given file, and based on your config the importer will do
/// everything from importing the designated file, as well as finding and importing any associated files such as images or materials, and prepping the objects at time
/// of import to avoid as much manual post-processing as possible.
/// </summary>
class AssetImportConfig : public SimObject
{
   typedef SimObject Parent;

   //General Settings
public:
   /// <summary>
   /// Duplicate Asset Auto-Resolution Action. Options are None, AutoPrune, AutoRename
   /// </summary>
   String DuplicateAutoResolution;

   /// <summary>
   /// Indicates if warnings should be treated as errors.
   /// </summary>
   bool WarningsAsErrors;

   /// <summary>
   /// Indicates if importing should be prevented from completing if any errors are detected at all
   /// </summary>
   bool PreventImportWithErrors;

   /// <summary>
   /// Should the importer automatically prompt to find missing files if they are not detected automatically by the importer
   /// </summary>
   bool AutomaticallyPromptMissingFiles;
   //

   /// <summary>
   /// Should the importer add the folder name as a prefix to the assetName. Helps prevent name collisions.
   /// </summary>
   bool AddDirectoryPrefixToAssetName;
   //
   //
   //Mesh Settings
   /// <summary>
   /// Indicates if this config supports importing meshes
   /// </summary>
   bool ImportMesh;

   /// <summary>
   /// When importing a shape, this indicates if it should automatically add a standard suffix onto the name
   /// </summary>
   bool AlwaysAddShapeSuffix;

   /// <summary>
   /// If AlwaysAddShapeSuffix is on, this is the suffix to be added
   /// </summary>
   String AddedShapeSuffix;

   /// <summary>
   /// Indicates if this config should override the per-format sis files with the config's specific settings
   /// </summary>
   bool UseManualShapeConfigRules;

   /// <summary>
   /// Indicates if the up axis in the model file should be overridden 
   /// </summary>
   bool DoUpAxisOverride;

   /// <summary>
   /// If overriding, what axis should be used as up. Options are X_AXIS, Y_AXIS, Z_AXIS
   /// </summary>
   String UpAxisOverride;

   /// <summary>
   /// Indicates if the scale in the model file should be overridden 
   /// </summary>
   bool DoScaleOverride;

   /// <summary>
   /// If overriding, what scale should be used
   /// </summary>
   F32 ScaleOverride;

   /// <summary>
   /// Indicates if scale of nodes should be ignored
   /// </summary>
   bool IgnoreNodeScale;

   /// <summary>
   /// Indicates if the center of the model file should be automatically recentered
   /// </summary>
   bool AdjustCenter;

   /// <summary>
   /// Indicates if the floor height of the model file should be automatically zero'd
   /// </summary>
   bool AdjustFloor;

   /// <summary>
   /// Indicates if submeshes should be collapsed down into a single main mesh
   /// </summary>
   bool CollapseSubmeshes;

   /// <summary>
   /// Indicates what LOD mode the model file should utilize to process out LODs. Options are TrailingNumber, DetectDTS, SingleSize
   /// </summary>
   String LODType;

   //ImportAssetConfigSettingsList.addNewConfigSetting("TrailingNumber", "Trailing Number", "float", "", "2", "", "Mesh");
   /// <summary>
   /// A list of what nodes should be guaranteed to be imported if found in the model file. Separated by either , or ;
   /// </summary>
   String AlwaysImportedNodes;

   /// <summary>
   /// A list of what nodes should be guaranteed to not be imported if found in the model file. Separated by either , or ;
   /// </summary>
   String AlwaysIgnoreNodes;

   /// <summary>
   /// A list of what mesh objects should be guaranteed to be imported if found in the model file. Separated by either , or ;
   /// </summary>
   String AlwaysImportMeshes;

   /// <summary>
   /// A list of what mesh objects should be guaranteed to not be imported if found in the model file. Separated by either , or ;
   /// </summary>
   String AlwaysIgnoreMeshes;

   //Assimp/Collada params
   /// <summary>
   /// Flag to indicate the shape loader should convert to a left-handed coordinate system
   /// </summary>
   bool convertLeftHanded;

   /// <summary>
   /// Should the shape loader calculate tangent space values
   /// </summary>
   bool calcTangentSpace;

   /// <summary>
   /// Should the shape loader automatically prune redundant/duplicate materials
   /// </summary>
   bool removeRedundantMats;

   /// <summary>
   /// Should the shape loader auto-generate UV Coordinates for the mesh.
   /// </summary>
   bool genUVCoords;

   /// <summary>
   /// Should the UV coordinates be transformed.
   /// </summary>
   bool TransformUVs;

   /// <summary>
   /// Should the UV coordinates be flipped
   /// </summary>
   bool flipUVCoords;

   /// <summary>
   /// Should the shape loader automatically look for instanced submeshes in the model file
   /// </summary>
   bool findInstances;

   /// <summary>
   /// Should the shape loader limit the bone weights
   /// </summary>
   bool limitBoneWeights;

   /// <summary>
   /// Should the shape loader automatically merge identical/duplicate verts
   /// </summary>
   bool JoinIdenticalVerts;

   /// <summary>
   /// Should the shape loader reverse the winding order of the mesh's face indicies
   /// </summary>
   bool reverseWindingOrder;

   /// <summary>
   /// Should the normals on the model be inverted
   /// </summary>
   bool invertNormals;
   //

   //
   //Materials
   /// <summary>
   /// Does this config allow for importing of materials
   /// </summary>
   bool ImportMaterials;

   /// <summary>
   /// When importing a material, should it automatically attempt to merge Roughness, AO and Metalness maps into a single, composited PBR Configuration map
   /// </summary>
   bool CreateORMConfig;

   /// <summary>
   /// When creating a material on import, this indicates if it should automatically add a standard suffix onto the name
   /// </summary>
   bool AlwaysAddMaterialSuffix;

   /// <summary>
   /// If AlwaysAddMaterialSuffix is on, this is the suffix to be added
   /// </summary>
   String AddedMaterialSuffix;

   /// <summary>
   /// When generating a material off of an importing image, should the importer force appending a diffusemap suffix onto the end to avoid potential naming confusion.
   /// e.g. MyCoolStuff.png is imported, generating MyCoolStuff material asset and MyCoolStuff_Diffuse image asset
   /// </summary>
   bool UseDiffuseSuffixOnOriginImage;

   /// <summary>
   /// Should the importer try and use existing material assets in the game directory if at all possible. (Not currently utilized)
   /// </summary>
   bool UseExistingMaterials;

   /// <summary>
   /// A list of material names that should not be imported. Separated by either , or ;
   /// </summary>
   String IgnoreMaterials;

   /// <summary>
   /// When processing a material asset, should the importer attempt to populate the various material maps on it by looking up common naming conventions for potentially relevent image files
   /// e.g. If MyCoolStuff_Diffuse.png is imported, generating MyCoolStuff material, it would also find MyCoolStuff_Normal and MyCoolStuff_PBR images and map them to the normal and ORMConfig maps respectively automatically
   /// </summary>
   bool PopulateMaterialMaps;

   //
   //Animations
   /// <summary>
   /// Does this config allow for importing Shape Animations
   /// </summary>
   bool ImportAnimations;

   /// <summary>
   /// When importing a shape file, should the animations within be separated out into unique files
   /// </summary>
   bool SeparateAnimations;

   /// <summary>
   /// If separating animations out from a source file, what prefix should be added to the names for grouping association
   /// </summary>
   String SeparateAnimationPrefix;

   /// <summary>
   /// Defines the animation timing for the given animation sequence. Options are FrameTime, Seconds, Milliseconds
   /// </summary>
   String animTiming;

   /// <summary>
   /// The FPS of the animation sequence
   /// </summary>
   F32 animFPS;

   /// <summary>
   /// When importing a shape animation, this indicates if it should automatically add a standard suffix onto the name
   /// </summary>
   bool AlwaysAddShapeAnimationSuffix;

   /// <summary>
   /// If AlwaysAddShapeAnimationSuffix is on, this is the suffix to be added
   /// </summary>
   String AddedShapeAnimationSuffix;

   //
   //Collision
   /// <summary>
   /// Does this configuration generate collision geometry when importing. (Not currently enabled)
   /// </summary>
   bool GenerateCollisions;

   /// <summary>
   /// What sort of collision geometry is generated. (Not currently enabled)
   /// </summary>
   String GenCollisionType;

   /// <summary>
   /// What prefix is added to the collision geometry generated. (Not currently enabled)
   /// </summary>
   String CollisionMeshPrefix;

   /// <summary>
   /// Does this configuration generate Line of Sight collision geometry. (Not currently enabled)
   /// </summary>
   bool  GenerateLOSCollisions;

   /// <summary>
   /// What sort of Line of Sight collision geometry is generated. (Not currently enabled)
   /// </summary>
   String GenLOSCollisionType;

   /// <summary>
   /// What prefix is added to the Line of Sight collision geometry generated. (Not currently enabled)
   /// </summary>
   String LOSCollisionMeshPrefix;

   //
   //Images
   /// <summary>
   /// Does this configuration support importing images.
   /// </summary>
   bool importImages;

   /// <summary>
   /// When importing an image, this indicates if it should automatically add a standard suffix onto the name
   /// </summary>
   bool AlwaysAddImageSuffix;

   /// <summary>
   /// If AlwaysAddImageSuffix is on, this is the suffix to be added
   /// </summary>
   String AddedImageSuffix;

   /// <summary>
   /// What is the default ImageType images are imported as. Options are: N/A, Diffuse, Normal, Metalness, Roughness, AO, ORMConfig, GUI, Cubemap
   /// </summary>
   String ImageType;

   /// <summary>
   /// What type of suffixes are scanned to detect if an importing image is a diffuse map.
   /// e.g. _Albedo or _Color
   /// </summary>
   String DiffuseTypeSuffixes;

   /// <summary>
   /// What type of suffixes are scanned to detect if an importing image is a normal map.
   /// e.g. _Normal or _Norm
   /// </summary>
   String NormalTypeSuffixes;

   /// <summary>
   /// What type of suffixes are scanned to detect if an importing image is a metalness map.
   /// e.g. _Metalness or _Metal
   /// </summary>
   String MetalnessTypeSuffixes;

   /// <summary>
   /// What type of suffixes are scanned to detect if an importing image is a roughness map.
   /// e.g. _roughness or _rough
   /// </summary>
   String RoughnessTypeSuffixes;

   /// <summary>
   /// What type of suffixes are scanned to detect if an importing image is a smoothness map.
   /// e.g. _smoothness or _smooth
   /// </summary>
   String SmoothnessTypeSuffixes;

   /// <summary>
   /// What type of suffixes are scanned to detect if an importing image is a ambient occlusion map.
   /// e.g. _ambient or _ao
   /// </summary>
   String AOTypeSuffixes;

   /// <summary>
   /// What type of suffixes are scanned to detect if an importing image is a ORMConfig map.
   /// e.g. _Composite or _PBR
   /// </summary>
   String PBRTypeSuffixes;

   /// <summary>
   /// Indicates what filter mode images imported with this configuration utilizes. Options are Linear, Bilinear, Trilinear
   /// </summary>
   String TextureFilteringMode;

   /// <summary>
   /// Indicates if images imported with this configuration utilize mipmaps
   /// </summary>
   bool UseMips;

   /// <summary>
   /// Indicates if images imported with this configuration are in an HDR format
   /// </summary>
   bool IsHDR;

   /// <summary>
   /// Indicates what amount of scaling images imported with this configuration use
   /// </summary>
   F32 Scaling;

   /// <summary>
   /// Indicates if images imported with this configuration are compressed
   /// </summary>
   bool ImagesCompressed;

   /// <summary>
   /// Indicates if images imported with this configuration generate a parent material for it as well
   /// </summary>
   bool GenerateMaterialOnImport;

   //
   //Sounds
   /// <summary>
   /// Indicates if sounds are imported with this configuration
   /// </summary>
   bool importSounds;

   /// <summary>
   /// Indicates what amount the volume is adjusted on sounds imported with this configuration
   /// </summary>
   F32 VolumeAdjust;

   /// <summary>
   /// Indicates what amount the pitch is adjusted on sounds imported with this configuration
   /// </summary>
   F32 PitchAdjust;

   /// <summary>
   /// Indicates if sounds imported with this configuration are compressed
   /// </summary>
   bool SoundsCompressed;

   /// When importing an image, this indicates if it should automatically add a standard suffix onto the name
   /// </summary>
   bool AlwaysAddSoundSuffix;

   /// <summary>
   /// If AlwaysAddSoundSuffix is on, this is the suffix to be added
   /// </summary>
   String AddedSoundSuffix;

public:
   AssetImportConfig();
   virtual ~AssetImportConfig();

   virtual bool onAdd();
   virtual void onRemove();

   /// Engine.
   static void initPersistFields();

   /// <summary>
   /// Loads a configuration from a Settings object
   /// @param configSettings, The Settings object to load from
   /// @param configName, The name of the configuration setting to load from the setting object
   /// </summary>
   void loadImportConfig(Settings* configSettings, String configName);

   void CopyTo(AssetImportConfig* target) const;

   /// Declare Console Object.
   DECLARE_CONOBJECT(AssetImportConfig);

   void loadSISFile(Torque::Path filePath);
};

/// <summary>
/// AssetImportConfig is a SimObject derived object that represents and holds information for an importing asset. They are generated and processed by the AssetImporter
/// </summary>
class AssetImportObject : public SimObject
{
   typedef SimObject Parent;

public:
   /// <summary>
   /// What type is the importing asset
   /// </summary>
   String assetType;

   /// <summary>
   /// What is the source file path of the importing asset
   /// </summary>
   Torque::Path filePath;

   /// <summary>
   /// What is the source file path of the importing asset in string form
   /// </summary>
   StringTableEntry filePathString;

   /// <summary>
   /// What is the asset's name
   /// </summary>
   String assetName;

   /// <summary>
   /// What is the original, unmodified by processing, asset name
   /// </summary>
   String cleanAssetName;

   /// <summary>
   /// What is the name of the module this asset will be importing into
   /// </summary>
   String moduleName;

   /// <summary>
   /// What is the current status of this asset item in it's import process
   /// </summary>
   String status;

   /// <summary>
   /// If there is a warning or error status, what type is the condition for this asset item
   /// </summary>
   String statusType;

   /// <summary>
   /// What is the articulated information of the status of the asset. Contains the error or warning log data.
   /// </summary>
   String statusInfo;

   /// <summary>
   /// Is the asset item currently flagged as dirty
   /// </summary>
   bool dirty;

   enum
   {
      NotProcessed=0,
      Processed,
      Skipped,
      UseForDependencies,
      Error,
      Imported
   };

   /// <summary>
   /// Is this asset item marked to be skipped. If it is, it's usually due to being marked as deleted
   /// </summary>
   U32 importStatus;

   /// <summary>
   /// Is this specific asset item generated as part of the import process of another item
   /// </summary>
   bool generatedAsset;

   /// <summary>
   /// What, if any, importing asset item is this item's parent
   /// </summary>
   AssetImportObject* parentAssetItem;

   /// <summary>
   /// What, if any, importing asset item are children of this item
   /// </summary>
   Vector< AssetImportObject*> childAssetItems;

   /// <summary>
   /// What is the ultimate asset taml file path for this import item
   /// </summary>
   String tamlFilePath;

   //
   /// <summary>
   /// Specific to ImageAsset type
   /// What is the image asset's suffix type. Options are: Albedo, Normal, Roughness, AO, Metalness, ORMConfig
   /// </summary>
   String imageSuffixType;

   //
   /// <summary>
   /// Specific to ShapeAsset type
   /// Processed information about the shape file. Contains numbers and lists of meshes, materials and animations
   /// </summary>
   GuiTreeViewCtrl* shapeInfo;

   //
   /// <summary>
   /// A string that can hold a hint string to help the auto-import ensure the correct asset subtype is assigned.
   /// e.g. "GUI" would inform an image asset being imported that it should be flagged as a GUI image type
   /// </summary>
   String typeHint;

public:
   AssetImportObject();
   virtual ~AssetImportObject();

   virtual bool onAdd();
   virtual void onRemove();

   /// Engine.
   static void initPersistFields();

   /// Declare Console Object.
   DECLARE_CONOBJECT(AssetImportObject);

   static bool _setFilePath(void* obj, const char* index, const char* data);

   void setFilePath(StringTableEntry pFilePath);

   bool operator == (const AssetImportObject& o) const
   {
      return o.getId() == this->getId();
   }

   bool canImport() {
      return (importStatus == AssetImportObject::Processed);
   }
};

/// <summary>
/// AssetImporter is a SimObject derived object that processed and imports files and turns them into assets if they are of valid types.
/// Utilizes an AssetImportConfig to inform the importing process's behavior.
/// </summary>
class AssetImporter : public SimObject
{
   typedef SimObject Parent;

   /// <summary>
   /// The import configuration that is currently being utilized
   /// </summary>
   AssetImportConfig* activeImportConfig;

   /// <summary>
   /// A log of all the actions that have been performed by the importer
   /// </summary>
   Vector<String> activityLog;

   /// <summary>
   /// A list of AssetImportObjects that are to be imported
   /// </summary>
   Vector<AssetImportObject*> importingAssets;

   /// <summary>
   /// A list of file paths that are to be imported. These are only used for resetting purposes;
   /// </summary>
   Vector<Torque::Path> originalImportingFiles;

   /// <summary>
   /// The Id of the module the assets are to be imported into
   /// </summary>
   String targetModuleId;

   /// <summary>
   /// The path any imported assets are placed in as their destination
   /// </summary>
   String targetPath;

   /// <summary>
   /// Are there any issues with any of the current import asset items
   /// </summary>
   bool importIssues;

   /// <summary>
   /// Is this import action a reimport of an existing asset
   /// </summary>
   bool isReimport;

   /// <summary>
   /// Has the heirarchy of asset import items changed due to processing
   /// </summary>
   bool assetHeirarchyChanged;

   /// <summary>
   /// A string used for writing into the importLog
   /// </summary>
   char importLogBuffer[1024];

   /// <summary>
   /// only used for passing up the result of an import action for a script-side handled type
   /// </summary>
   String finalImportedAssetPath;

   bool mDumpLogs;

public:
   AssetImporter();
   virtual ~AssetImporter();

   virtual bool onAdd();
   virtual void onRemove();

   /// Engine.
   static void initPersistFields();

   /// Declare Console Object.
   DECLARE_CONOBJECT(AssetImporter);

   /// <summary>
   /// Sets the target path for the assets being imported to be deposited into
   /// <para>@param pTargetPath, The filePath of the destination point assets are imported into</para>
   /// </summary>
   void setTargetPath(Torque::Path pTargetPath) { targetPath = pTargetPath; }

   /// <summary>
   /// Processes a file into an AssetImportObject and adds it to the session for importing
   /// <para>@param filePath, The filePath of the file to be imported in as an asset</para>
   /// <para>@return AssetImportObject that was created</para>
   /// </summary>
   AssetImportObject* addImportingFile(Torque::Path filePath);

   /// <summary>
   /// Adds an existing AssetImportObject to our import session. Generally this would be created in a script somewhere
   /// <para>@param assetItem, The asset item to be added to the import session</para>
   /// <para>@param parentItem (Optional), The asset item that will be the parent of the assetItem being added</para>
   /// </summary>
   void addImportingAssetItem(AssetImportObject* assetItem, AssetImportObject* parentItem);

   /// <summary>
   /// Adds an importing asset to the current session
   /// <para>@param assetType, Type of the asset being imported</para>
   /// <para>@param filePath, path of the file to be imported</para>
   /// <para>@param parentItem, AssetImportObject that the new item is a child of. null if no parent</para>
   /// <para>@param assetNameOverride, If not blank, will be the new item's assetName instead of being created off of the filePath</para>
   /// <para>@return AssetImportObject that was created</para>
   /// </summary>
   AssetImportObject* addImportingAsset(String assetType, Torque::Path filePath, AssetImportObject* parentItem, String assetNameOverride);

   /// <summary>
   /// Deletes the asset item from the import session. Affects the item's children as well
   /// <para>@param assetItem, asset item to be marked as deleted</para>
   /// </summary>
   void deleteImportingAsset(AssetImportObject* assetItem);

   /// <summary>
   /// Finds an asset item in the session if it exists, by name
   /// <para>@param assetName, Asset name to find</para>
   /// <para>@param assetItem, if null, will loop over and recurse the main import asset items, if a specific AssetImportObject is passed in, it will recurse it's children</para>
   /// <para>@return AssetImportObject that was found</para>
   /// </summary>
   AssetImportObject* findImportingAssetByName(String assetName, AssetImportObject* assetItem = nullptr);

   /// <summary>
   /// Finds the module associated with a given file path
   /// <para>@param filePath, File path to parse the the module from</para>
   /// <para>@return ModuleDefinition that was found</para>
   /// </summary>
   static ModuleDefinition* getModuleFromPath(Torque::Path filePath);

   /// <summary>
   /// Parses an asset's name to try and find if any of the import config's suffix lists match to it
   /// <para>@param assetName, Asset name to parse any image suffix out of</para>
   /// <para>@param suffixType, output, The suffix type that was matched to the asset name</para>
   /// <para>@return suffix that matched to the asset name</para>
   /// </summary>
   String parseImageSuffixes(String assetName, String* suffixType);

   /// <summary>
   /// Parses a file path to determine its asset type
   /// <para>@param filePath, File path to parse</para>
   /// <para>@return The asset type as a string</para>
   /// </summary>
   String getAssetTypeByFile(Torque::Path filePath);

   /// <summary>
   /// Resets the import session to a clean slate. This will clear all existing AssetImportObjects and the activity log
   /// and then re-process the original filePaths again.
   /// <para>@param hardClearSession, Defaults to false. If true, will also clear the original filePaths</para>
   /// </summary>
   void resetImportSession(bool hardClearSession = false);

   /// <summary>
   /// Get the number of lines in the activity log
   /// <para>@return Line count as S32</para>
   /// </summary>
   S32 getActivityLogLineCount();

   /// <summary>
   /// Gets the log line at a given index
   /// <para>@param line, line in the log to get</para>
   /// <para>@return The log line as a string</para>
   /// </summary>
   String getActivityLogLine(U32 line);

   /// <summary>
   /// Dumps the entire current activity log to the console.
   /// </summary>
   void dumpActivityLog();

   /// <summary>
   /// Gets the number of top-level asset items in the current import session(doesn't count children)
   /// <para>@return Number of children</para>
   /// </summary>
   S32 getAssetItemCount();

   /// <summary>
   /// Get the top-level asset item in the current import session at the requested index
   /// <para>@param index, The index of the item array to get</para>
   /// <para>@return The AssetImportObject at the index</para>
   /// </summary>
   AssetImportObject* getAssetItem(U32 index);

   /// <summary>
   /// Gets the number of child asset items of a given AssetImportObject
   /// <para>@param assetItem, The AssetImportObject to get the number of child items for</para>
   /// <para>@return Number of children</para>
   /// </summary>
   S32 getAssetItemChildCount(AssetImportObject* assetItem);

   /// <summary>
   /// Get the child asset item of a specific AssetImportObject at the requested index
   /// <para>@param assetItem, The AssetImportObject to get the number of child items for</para>
   /// <para>@param index, The index of the child item array to get</para>
   /// <para>@return The AssetImportObject at the index</para>
   /// </summary>
   AssetImportObject* getAssetItemChild(AssetImportObject* assetItem, U32 index);

   /// <summary>
   /// Process AssetImportObject's to prepare them for importing.
   /// <para>@param assetItem, If null, will loop over the top-level asset items list, if a specific item is provided, will process it's children</para>
   /// </summary>
   void processImportAssets(AssetImportObject* assetItem = nullptr);

   /// <summary>
   /// Process a specific AssetImportObject that is an ImageAsset type to prepare it for importing
   /// <para>@param assetItem, The AssetImportObject to process</para>
   /// </summary>
   void processImageAsset(AssetImportObject* assetItem);

   /// <summary>
   /// Process a specific AssetImportObject that is an MaterialAsset type to prepare it for importing
   /// <para>@param assetItem, The AssetImportObject to process</para>
   /// </summary>
   void processMaterialAsset(AssetImportObject* assetItem);

   /// <summary>
   /// Process a specific AssetImportObject that is an ShapeAnimationAsset type to prepare it for importing
   /// <para>@param assetItem, The AssetImportObject to process</para>
   /// </summary>
   void processShapeAsset(AssetImportObject* assetItem);

   /// <summary>
   /// Process a specific AssetImportObject that is an ShapeAsset type to prepare it for importing
   /// <para>@param assetItem, The AssetImportObject to process</para>
   /// </summary>
   void processShapeAnimationAsset(AssetImportObject* assetItem);

   /// <summary>
   /// Process a specific ShapeAsset AssetImportObject with a material id in order to parse and handle the materials listed in the shape file
   /// <para>@param assetItem, The AssetImportObject to process</para>
   /// <para>@param materialItemId, The materialItemId in the shapeInfo to process</para>
   /// </summary>
   void processShapeMaterialInfo(AssetImportObject* assetItem, S32 materialItemId);

   /// <summary>
   /// Process a specific AssetImportObject that is an SoundAsset type to prepare it for importing
   /// <para>@param assetItem, The AssetImportObject to process</para>
   /// </summary>
   void processSoundAsset(AssetImportObject* assetItem);

   /// <summary>
   /// Run through and validate assets for issues, such as name collisions
   /// </summary>
   bool validateAssets();

   /// <summary>
   /// Validate a specific asset item
   /// <para>@param assetItem, The AssetImportObject to validate</para>
   /// </summary>
   void validateAsset(AssetImportObject* assetItem);

   /// <summary>
   /// Reset the validation status of asset items
   /// <para>@param assetItem, If null, will loop over the top-level asset items list, if a specific item is provided, will reset it's children</para>
   /// </summary>
   void resetAssetValidationStatus(AssetImportObject* assetItem = nullptr);

   /// <summary>
   /// Checks asset items for any collisions in the current import session
   /// <para>@param assetItemToCheckFor, The asset to check for collisions with</para>
   /// <para>@param assetItem, if null, will loop over and recurse the main import asset items, if a specific AssetImportObject is passed in, it will recurse it's children</para>
   /// <para>@return If a collision was detected</para>
   /// </summary>
   bool checkAssetForCollision(AssetImportObject* assetItemToCheckFor, AssetImportObject* assetItem = nullptr);

   /// <summary>
   /// Attempts to automatically resolve import issues according to the import config settings
   /// <para>@param assetItem, The AssetImportObject to resolve</para>
   /// </summary>
   void resolveAssetItemIssues(AssetImportObject* assetItem);

   /// <summary>
   /// Runs the import process on a single file in-place. Intended primarily for autoimporting a loose file that's in the game directory.
   /// <para>@param filePath, The filePath of the file to be imported in as an asset</para>
   /// <para>@param typeHint, Optional. A string that provides a hint of the intended asset type. Such as an image being intended for GUI use.</para>
   /// <para>@return AssetId of the asset that was imported. If import failed, it will be empty.</para>
   /// </summary>
   StringTableEntry autoImportFile(Torque::Path filePath, String typeHint);

   /// <summary>
   /// Runs the import process in the current session
   /// <para>@param assetItem, if null, will loop over and recurse the main import asset items, if a specific AssetImportObject is passed in, it will recurse it's children</para>
   /// </summary>
   void importAssets(AssetImportObject* assetItem = nullptr);

   /// <summary>
   /// Runs the import processing on a specific ImageAsset item
   /// <para>@param assetItem, The asset item to import</para>
   /// <para>@return TAML File path of the new asset that was imported. If import failed, it will be empty.</para>
   /// </summary>
   Torque::Path importImageAsset(AssetImportObject* assetItem);

   /// <summary>
   /// Runs the import processing on a specific MaterialAsset item
   /// <para>@param assetItem, The asset item to import</para>
   /// <para>@return TAML File path of the new asset that was imported. If import failed, it will be empty.</para>
   /// </summary>
   Torque::Path importMaterialAsset(AssetImportObject* assetItem);

   /// <summary>
   /// Runs the import processing on a specific ShapeAsset item
   /// <para>@param assetItem, The asset item to import</para>
   /// <para>@return TAML File path of the new asset that was imported. If import failed, it will be empty.</para>
   /// </summary>
   Torque::Path importShapeAsset(AssetImportObject* assetItem);

   /// <summary>
   /// Runs the import processing on a specific SoundAsset item
   /// <para>@param assetItem, The asset item to import</para>
   /// <para>@return TAML File path of the new asset that was imported. If import failed, it will be empty.</para>
   /// </summary>
   Torque::Path importSoundAsset(AssetImportObject* assetItem);

   /// <summary>
   /// Runs the import processing on a specific ShapeAnimationAsset item
   /// <para>@param assetItem, The asset item to import</para>
   /// <para>@return TAML File path of the new asset that was imported. If import failed, it will be empty.</para>
   /// </summary>
   Torque::Path importShapeAnimationAsset(AssetImportObject* assetItem);

   /// <summary>
   /// Iterates over all the items in the current session and acquires them, which jumpstarts the loading/init'ng process on them, making the available for use immediately
   /// <para>@param assetItem, if null, will loop over and recurse the main import asset items, if a specific AssetImportObject is passed in, it will recurse it's children</para>
   /// </summary>
   void acquireAssets(AssetImportObject* assetItem = nullptr);

   //
   /// <summary>
   /// Gets the currently active import configuration
   /// <para>@return Current AssetImportConfig the importer is using</para>
   /// </summary>
   AssetImportConfig* getImportConfig() { return activeImportConfig; }

   void setImportConfig(AssetImportConfig* importConfig)
   {
      if (importConfig != nullptr)
      {
         dSprintf(importLogBuffer, sizeof(importLogBuffer), "Loading import config: %s!", importConfig->getName());
         activityLog.push_back(importLogBuffer);

         activeImportConfig = importConfig;
      }
   }

   /// <summary>
   /// Resets the active import config to whatever the default is. Either a clean slate if one isn't defined
   /// or loading one if defined via the editor config
   /// </summary>
   void resetImportConfig();

   //
   static String getTrueFilename(const String& fileName);

   //
   /// <summary>
   /// </summary>
   static inline String findImagePath(const String &testPath)
   {

      String imagePath;
      if (Platform::isFile(testPath + String(".jpg")))
         imagePath = testPath + String(".jpg");
      else if (Platform::isFile(testPath + String(".png")))
         imagePath = testPath + String(".png");
      else if (Platform::isFile(testPath + String(".dds")))
         imagePath = testPath + String(".dds");
      else if (Platform::isFile(testPath + String(".tif")))
         imagePath = testPath + String(".tif");

      if(imagePath.isNotEmpty())
         //This ensures case-correct for the filename
         imagePath = getTrueFilename(imagePath);

      return imagePath;
   }

   //
   void setTargetModuleId(const String& moduleId) { targetModuleId = moduleId; }
   const String& getTargetModuleId() { return targetModuleId; }

   String getFolderPrefixedName(AssetImportObject* assetItem)
   {
      String renamedAssetName = assetItem->assetName;
      S32 dirIndex = assetItem->filePath.getDirectoryCount() - 1;
      while (dirIndex > -1)
      {
         renamedAssetName = assetItem->assetName;
         String owningFolder = assetItem->filePath.getDirectory(dirIndex);

         renamedAssetName = owningFolder + "_" + renamedAssetName;

         if (AssetDatabase.isDeclaredAsset(renamedAssetName))
         {
            dirIndex--;
            continue;
         }

         break;
      }

      return renamedAssetName;
   }
};
