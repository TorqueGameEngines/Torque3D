//-----------------------------------------------------------------------------
// Copyright (c) 2012 GarageGames, LLC
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//-----------------------------------------------------------------------------

/*
   Resource stream -> Buffer
   Buffer -> Collada DOM
   Collada DOM -> TSShapeLoader
   TSShapeLoader installed into TSShape
*/

//-----------------------------------------------------------------------------

#include "platform/platform.h"

#include "ts/assimp/assimpShapeLoader.h"
#include "ts/assimp/assimpAppNode.h"
#include "ts/assimp/assimpAppMaterial.h"
#include "ts/assimp/assimpAppSequence.h"

#include "core/util/tVector.h"
#include "core/strings/findMatch.h"
#include "core/stream/fileStream.h"
#include "core/fileObject.h"
#include "ts/tsShape.h"
#include "ts/tsShapeInstance.h"
#include "materials/materialManager.h"
#include "console/persistenceManager.h"
#include "ts/tsShapeConstruct.h"
#include "core/util/zip/zipVolume.h"
#include "gfx/bitmap/gBitmap.h"
#include "gui/controls/guiTreeViewCtrl.h"

// assimp include files. 
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/types.h>
#include <assimp/config.h>
#include <exception>

#include <assimp/Importer.hpp>

MODULE_BEGIN( AssimpShapeLoader )
   MODULE_INIT_AFTER( ShapeLoader )
   MODULE_INIT
   {
      TSShapeLoader::addFormat("DirectX X", "x");
      TSShapeLoader::addFormat("Autodesk FBX", "fbx");
      TSShapeLoader::addFormat("Blender 3D", "blend" );
      TSShapeLoader::addFormat("3ds Max 3DS", "3ds");
      TSShapeLoader::addFormat("3ds Max ASE", "ase");
      TSShapeLoader::addFormat("Wavefront Object", "obj");
      TSShapeLoader::addFormat("Industry Foundation Classes (IFC/Step)", "ifc");
      TSShapeLoader::addFormat("Stanford Polygon Library", "ply");
      TSShapeLoader::addFormat("AutoCAD DXF", "dxf");
      TSShapeLoader::addFormat("LightWave", "lwo");
      TSShapeLoader::addFormat("LightWave Scene", "lws");
      TSShapeLoader::addFormat("Modo", "lxo");
      TSShapeLoader::addFormat("Stereolithography", "stl");
      TSShapeLoader::addFormat("AC3D", "ac");
      TSShapeLoader::addFormat("Milkshape 3D", "ms3d");
      TSShapeLoader::addFormat("TrueSpace COB", "cob");
      TSShapeLoader::addFormat("TrueSpace SCN", "scn");
      TSShapeLoader::addFormat("Ogre XML", "xml");
      TSShapeLoader::addFormat("Irrlicht Mesh", "irrmesh");
      TSShapeLoader::addFormat("Irrlicht Scene", "irr");
      TSShapeLoader::addFormat("Quake I", "mdl" );
      TSShapeLoader::addFormat("Quake II", "md2" );
      TSShapeLoader::addFormat("Quake III Mesh", "md3");
      TSShapeLoader::addFormat("Quake III Map/BSP", "pk3");
      TSShapeLoader::addFormat("Return to Castle Wolfenstein", "mdc");
      TSShapeLoader::addFormat("Doom 3", "md5" );
      TSShapeLoader::addFormat("Valve SMD", "smd");
      TSShapeLoader::addFormat("Valve VTA", "vta");
      TSShapeLoader::addFormat("Starcraft II M3", "m3");
      TSShapeLoader::addFormat("Unreal", "3d");
      TSShapeLoader::addFormat("BlitzBasic 3D", "b3d" );
      TSShapeLoader::addFormat("Quick3D Q3D", "q3d");
      TSShapeLoader::addFormat("Quick3D Q3S", "q3s");
      TSShapeLoader::addFormat("Neutral File Format", "nff");
      TSShapeLoader::addFormat("Object File Format", "off");
      TSShapeLoader::addFormat("PovRAY Raw", "raw");
      TSShapeLoader::addFormat("Terragen Terrain", "ter");
      TSShapeLoader::addFormat("3D GameStudio (3DGS)", "mdl");
      TSShapeLoader::addFormat("3D GameStudio (3DGS) Terrain", "hmp");
      TSShapeLoader::addFormat("Izware Nendo", "ndo");
      TSShapeLoader::addFormat("gltf", "gltf");
      TSShapeLoader::addFormat("gltf binary", "glb");
   }
MODULE_END;

//-----------------------------------------------------------------------------

AssimpShapeLoader::AssimpShapeLoader() 
{
   mScene = NULL;
}

AssimpShapeLoader::~AssimpShapeLoader()
{

}

void AssimpShapeLoader::releaseImport()
{
   aiReleaseImport(mScene);
}

void AssimpShapeLoader::enumerateScene()
{
   TSShapeLoader::updateProgress(TSShapeLoader::Load_ReadFile, "Reading File");
   Con::printf("[ASSIMP] Attempting to load file: %s", shapePath.getFullPath().c_str());

   // Post-Processing
   unsigned int ppsteps = 
       Con::getBoolVariable("$Assimp::ConvertToLeftHanded", false) ? aiProcess_ConvertToLeftHanded : 0 |
       Con::getBoolVariable("$Assimp::CalcTangentSpace", false) ? aiProcess_CalcTangentSpace : 0 |
       Con::getBoolVariable("$Assimp::JoinIdenticalVertices", false) ? aiProcess_JoinIdenticalVertices : 0 |
       Con::getBoolVariable("$Assimp::ValidateDataStructure", false) ? aiProcess_ValidateDataStructure : 0 |
       Con::getBoolVariable("$Assimp::ImproveCacheLocality", false) ? aiProcess_ImproveCacheLocality : 0 |
       Con::getBoolVariable("$Assimp::RemoveRedundantMaterials", false) ? aiProcess_RemoveRedundantMaterials : 0 |
       Con::getBoolVariable("$Assimp::FindDegenerates", false) ? aiProcess_FindDegenerates : 0 |
       Con::getBoolVariable("$Assimp::FindInvalidData", false) ? aiProcess_FindInvalidData : 0 |
       Con::getBoolVariable("$Assimp::GenUVCoords", false) ? aiProcess_GenUVCoords : 0 |
       Con::getBoolVariable("$Assimp::TransformUVCoords", false) ? aiProcess_TransformUVCoords : 0 |
       Con::getBoolVariable("$Assimp::FindInstances", false) ? aiProcess_FindInstances : 0 |
       Con::getBoolVariable("$Assimp::LimitBoneWeights", false) ? aiProcess_LimitBoneWeights : 0 |
       Con::getBoolVariable("$Assimp::OptimizeMeshes", false) ? aiProcess_OptimizeMeshes | aiProcess_OptimizeGraph : 0 |
       0;

   if(Con::getBoolVariable("$Assimp::FlipUVs", true))
      ppsteps |= aiProcess_FlipUVs;

   if(Con::getBoolVariable("$Assimp::Triangulate", true))
      ppsteps |= aiProcess_Triangulate;

   if (Con::getBoolVariable("$Assimp::OptimizeMeshes", false))
      ppsteps |= aiProcess_OptimizeMeshes | aiProcess_OptimizeGraph;

   if (Con::getBoolVariable("$Assimp::SplitLargeMeshes", false))
      ppsteps |= aiProcess_SplitLargeMeshes;

   //aiProcess_SortByPType              | // make 'clean' meshes which consist of a single typ of primitives

   aiPropertyStore* props = aiCreatePropertyStore();

   aiSetImportPropertyInteger(props,   AI_CONFIG_IMPORT_TER_MAKE_UVS,         1);
   aiSetImportPropertyInteger(props,   AI_CONFIG_PP_SBP_REMOVE,               (aiProcessPreset_TargetRealtime_Quality 
                                                                                    | aiProcess_FlipWindingOrder | aiProcess_FlipUVs 
                                                                                    | aiProcess_CalcTangentSpace
                                                                                    | aiProcess_FixInfacingNormals) 
                                                                                       & ~aiProcess_RemoveRedundantMaterials);
   aiSetImportPropertyInteger(props,   AI_CONFIG_GLOB_MEASURE_TIME,           1);
   aiSetImportPropertyFloat(props,     AI_CONFIG_PP_GSN_MAX_SMOOTHING_ANGLE,  80.f);
   //aiSetImportPropertyInteger(props,AI_CONFIG_PP_PTV_KEEP_HIERARCHY,1);

   //Assimp::Importer importer;

   // Attempt to import with Assimp.
   //mScene = importer.ReadFile(shapePath.getFullPath().c_str(), (aiProcessPreset_TargetRealtime_Quality | aiProcess_FlipWindingOrder | aiProcess_FlipUVs | aiProcess_CalcTangentSpace)
   //   & ~aiProcess_RemoveRedundantMaterials);

   mScene = (aiScene*)aiImportFileExWithProperties(shapePath.getFullPath().c_str(), ppsteps, NULL, props);

   aiReleasePropertyStore(props);

   if ( mScene )
   {
      Con::printf("[ASSIMP] Mesh Count: %d", mScene->mNumMeshes);
      Con::printf("[ASSIMP] Material Count: %d", mScene->mNumMaterials);

      // Load all the materials.
      for ( U32 i = 0; i < mScene->mNumMaterials; i++ )
         AppMesh::appMaterials.push_back(new AssimpAppMaterial(mScene->mMaterials[i]));

      // Define the root node, and process down the chain.
      AssimpAppNode* node = new AssimpAppNode(mScene, mScene->mRootNode, 0);
      
      if (!processNode(node))
         delete node;

      // Check for animations and process those.
      processAnimations();
   } 
   else 
   {
      TSShapeLoader::updateProgress(TSShapeLoader::Load_Complete, "Import failed");
      Con::printf("[ASSIMP] Import Error: %s", aiGetErrorString());
   }
}

void AssimpShapeLoader::processAnimations()
{
   for(U32 n = 0; n < mScene->mNumAnimations; ++n)
   {
      Con::printf("[ASSIMP] Animation Found: %s", mScene->mAnimations[n]->mName.C_Str());

      AssimpAppSequence* newAssimpSeq = new AssimpAppSequence(mScene->mAnimations[n]);
      appSequences.push_back(newAssimpSeq);
   }
}

void AssimpShapeLoader::updateMaterialsScript(const Torque::Path &path)
{
   Torque::Path scriptPath(path);
   scriptPath.setFileName("materials");
   scriptPath.setExtension("cs");

   // First see what materials we need to update
   PersistenceManager persistMgr;
   for ( U32 iMat = 0; iMat < AppMesh::appMaterials.size(); iMat++ )
   {
      AssimpAppMaterial *mat = dynamic_cast<AssimpAppMaterial*>( AppMesh::appMaterials[iMat] );
      if ( mat )
      {
         Material *mappedMat;
         if ( Sim::findObject( MATMGR->getMapEntry( mat->getName() ), mappedMat ) )
         {
            // Only update existing materials if forced to
            if ( ColladaUtils::getOptions().forceUpdateMaterials )
               persistMgr.setDirty( mappedMat );
         }
         else
         {
            // Create a new material definition
            persistMgr.setDirty( mat->createMaterial( scriptPath ), scriptPath.getFullPath() );
         }
      }
   }

   if ( persistMgr.getDirtyList().empty() )
      return;

   persistMgr.saveDirty();
}

/// Check if an up-to-date cached DTS is available for this DAE file
bool AssimpShapeLoader::canLoadCachedDTS(const Torque::Path& path)
{
   return false;

   // Generate the cached filename
   Torque::Path cachedPath(path);
   cachedPath.setExtension("cached.dts");

   // Check if a cached DTS newer than this file is available
   FileTime cachedModifyTime;
   if (Platform::getFileTimes(cachedPath.getFullPath(), NULL, &cachedModifyTime))
   {
      bool forceLoadDAE = Con::getBoolVariable("$assimp::forceLoad", false);

      FileTime daeModifyTime;
      if (!Platform::getFileTimes(path.getFullPath(), NULL, &daeModifyTime) ||
         (!forceLoadDAE && (Platform::compareFileTimes(cachedModifyTime, daeModifyTime) >= 0) ))
      {
         // DAE not found, or cached DTS is newer
         return true;
      }
   }

   return false;
}

bool AssimpShapeLoader::ignoreNode(const String& name)
{
   // Do not add AssimpFbx dummy nodes to the TSShape. See: Assimp::FBX::ImportSettings::preservePivots
   // https://github.com/assimp/assimp/blob/master/code/FBXImportSettings.h#L116-L135
   if (name.find("_$AssimpFbx$_") != String::NPos)
      return true;
   return false;
}

//-----------------------------------------------------------------------------
/// This function is invoked by the resource manager based on file extension.
TSShape* assimpLoadShape(const Torque::Path &path)
{
   // TODO: add .cached.dts generation.
   // Generate the cached filename
   Torque::Path cachedPath(path);
   cachedPath.setExtension("cached.dts");

   // Check if an up-to-date cached DTS version of this file exists, and
   // if so, use that instead.
   if (AssimpShapeLoader::canLoadCachedDTS(path))
   {
      FileStream cachedStream;
      cachedStream.open(cachedPath.getFullPath(), Torque::FS::File::Read);
      if (cachedStream.getStatus() == Stream::Ok)
      {
         TSShape *shape = new TSShape;
         bool readSuccess = shape->read(&cachedStream);
         cachedStream.close();

         if (readSuccess)
         {
         #ifdef TORQUE_DEBUG
            Con::printf("Loaded cached shape from %s", cachedPath.getFullPath().c_str());
         #endif
            return shape;
         }
         else
            delete shape;
      }

      Con::warnf("Failed to load cached shape from %s", cachedPath.getFullPath().c_str());
   }

   if (!Torque::FS::IsFile(path))
   {
      // File does not exist, bail.
      return NULL;
   }

   AssimpShapeLoader loader;
   TSShape* tss = loader.generateShape(path);
   if (tss)
   {
      TSShapeLoader::updateProgress(TSShapeLoader::Load_Complete, "Import complete");
      Con::printf("[ASSIMP] Shape created successfully.");

      // Cache the model to a DTS file for faster loading next time.
      FileStream dtsStream;
      if (dtsStream.open(cachedPath.getFullPath(), Torque::FS::File::Write))
      {
         Con::printf("Writing cached shape to %s", cachedPath.getFullPath().c_str());
         tss->write(&dtsStream);
      }

      loader.updateMaterialsScript(path);
   }
   loader.releaseImport();
   return tss;
}

DefineEngineFunction(GetShapeInfo, GuiTreeViewCtrl*, (String filePath), ,
   "Returns a list of supported shape formats in filter form.\n"
   "Example output: DSQ Files|*.dsq|COLLADA Files|*.dae|")
{
   Assimp::Importer importer;

   GuiTreeViewCtrl* treeObj = new GuiTreeViewCtrl();
   treeObj->registerObject();

   Torque::Path path = Torque::Path(filePath);

   // Attempt to import with Assimp.
   const aiScene* shapeScene = importer.ReadFile(path.getFullPath().c_str(), (aiProcessPreset_TargetRealtime_Quality | aiProcess_CalcTangentSpace)
      & ~aiProcess_RemoveRedundantMaterials & ~aiProcess_GenSmoothNormals);

   //Populate info
   S32 meshItem = treeObj->insertItem(0, "Shape", String::ToString("%i", shapeScene->mNumMeshes));
   S32 matItem = treeObj->insertItem(0, "Materials", String::ToString("%i", shapeScene->mNumMaterials));
   S32 animItem = treeObj->insertItem(0, "Animations", String::ToString("%i", shapeScene->mNumAnimations));
   S32 lightsItem = treeObj->insertItem(0, "Lights", String::ToString("%i", shapeScene->mNumLights));
   S32 texturesItem = treeObj->insertItem(0, "Textures", String::ToString("%i", shapeScene->mNumTextures));
   //S32 meshItem = ->insertItem(0, "Cameras", String::ToString("%s", shapeScene->mNumCameras));

   //Details!
   for (U32 i = 0; i < shapeScene->mNumMeshes; i++)
   {
      treeObj->insertItem(meshItem, String::ToString("%s", shapeScene->mMeshes[i]->mName));
   }

   for (U32 i = 0; i < shapeScene->mNumMaterials; i++)
   {
      aiMaterial* aiMat = shapeScene->mMaterials[i];

      aiString matName;
      aiMat->Get(AI_MATKEY_NAME, matName);

      aiString texPath;
      aiMat->GetTexture(aiTextureType::aiTextureType_DIFFUSE, 0, &texPath);

      treeObj->insertItem(matItem, String::ToString("%s", matName.C_Str()), String::ToString("%s", texPath.C_Str()));
   }

   for (U32 i = 0; i < shapeScene->mNumAnimations; i++)
   {
      treeObj->insertItem(animItem, String::ToString("%s", shapeScene->mAnimations[i]->mName.C_Str()));
   }

   /*for (U32 i = 0; i < shapeScene->mNumLights; i++)
   {
      treeObj->insertItem(lightsItem, String::ToString("%s", shapeScene->mLights[i]->mType));
   }*/

   return treeObj;
}