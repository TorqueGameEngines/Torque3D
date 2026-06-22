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
#include "ts/assimp/assimpAppMesh.h"
#include "ts/assimp/assimpAppMaterial.h"
#include "ts/assimp/assimpAppSequence.h"

#include "core/util/tVector.h"
#include "core/strings/findMatch.h"
#include "core/strings/stringUnit.h"
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

#if !defined(TORQUE_DISABLE_MEMORY_MANAGER)
#ifdef new
#undef new
#endif
#endif
// assimp include files.
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/types.h>
#include <assimp/config.h>
#include <assimp/Exporter.hpp>
#include <exception>

#if !defined(TORQUE_DISABLE_MEMORY_MANAGER)
#  define _new new(__FILE__, __LINE__)
#  define new  _new
#endif

static bool sReadAssimp(const Torque::Path& path, TSShape*& shape);

static struct _privateRegisterAssimp
{
   _privateRegisterAssimp()
   {
      TSShape::ShapeRegistration reg;

      Assimp::Importer importer;
      for (U32 i = 0; i < importer.GetImporterCount(); i++)
      {
         const aiImporterDesc* desc = importer.GetImporterInfo(i);

         String extensions(desc->mFileExtensions);

         Vector<String> tokens;
         extensions.split(" ", tokens);
         for (U32 t = 0; t < tokens.size(); ++t)
         {
            const String& ext = tokens[t];
            if (ext.isEmpty() ||
               ext.equal("dae", String::NoCase) || // filter out collada importer formats (for now).
               ext.equal("zae", String::NoCase) ||
               ext.equal("xml", String::NoCase)
               )
               continue;

            reg.extensions.push_back({
                String(desc->mName), // convert from const char*
                ext
               });
         }

      }

      Assimp::Exporter exporter;

      for (U32 i = 0; i < exporter.GetExportFormatCount(); ++i)
      {
         const aiExportFormatDesc* desc = exporter.GetExportFormatDescription(i);
         String ext(desc->fileExtension);

         if (ext.isEmpty() ||
            ext.equal("dae", String::NoCase) || // filter out collada importer formats (for now).
            ext.equal("zae", String::NoCase) ||
            ext.equal("xml", String::NoCase)
            )
            continue;

         reg.export_extensions.push_back({
             String(desc->description),
             ext
            });
      }

      reg.readFunc = sReadAssimp;
      reg.writeFunc = NULL;

      TSShape::sRegisterFormat(reg);
   }
} sStaticRegisterAssimp;


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
}

void applyTransformation(aiNode* node, const aiMatrix4x4& transform) {
   node->mTransformation = transform * node->mTransformation; // Apply transformation to the node
}

void scaleScene(const aiScene* scene, F32 scaleFactor) {
   aiMatrix4x4 scaleMatrix;
   scaleMatrix = aiMatrix4x4::Scaling(aiVector3D(scaleFactor, scaleFactor, scaleFactor), scaleMatrix);
   applyTransformation(scene->mRootNode, scaleMatrix);
}

void debugSceneMetaData(const aiScene* scene) {
   if (!scene->mMetaData) {
      Con::printf("[ASSIMP] No metadata available.");
      return;
   }

   for (U32 i = 0; i < scene->mMetaData->mNumProperties; ++i) {
      const char* key = scene->mMetaData->mKeys[i].C_Str();
      aiMetadataType type = scene->mMetaData->mValues[i].mType;
      Con::printf("[ASSIMP] Metadata key: %s", key);

      switch (type) {
      case AI_BOOL:
         Con::printf("  Value: %d (bool)", *(bool*)scene->mMetaData->mValues[i].mData);
         break;
      case AI_INT32:
         Con::printf("  Value: %d (int)", *(S32*)scene->mMetaData->mValues[i].mData);
         break;
      case AI_UINT64:
         Con::printf("  Value: %llu (uint64)", *(U64*)scene->mMetaData->mValues[i].mData);
         break;
      case AI_FLOAT:
         Con::printf("  Value: %f (float)", *(F32*)scene->mMetaData->mValues[i].mData);
         break;
      case AI_DOUBLE:
         Con::printf("  Value: %f (double)", *(F64*)scene->mMetaData->mValues[i].mData);
         break;
      case AI_AISTRING:
         Con::printf("  Value: %s (string)", ((aiString*)scene->mMetaData->mValues[i].mData)->C_Str());
         break;
      case AI_AIVECTOR3D:
      {
         aiVector3D* vec = (aiVector3D*)scene->mMetaData->mValues[i].mData;
         Con::printf("  Value: (%f, %f, %f) (vector3d)", vec->x, vec->y, vec->z);
      }
      break;
      default:
         Con::printf("  Unknown metadata type.");
      }
   }
}

void AssimpShapeLoader::enumerateScene()
{
   TSShapeLoader::updateProgress(TSShapeLoader::Load_ReadFile, "Reading File");
   Con::printf("[ASSIMP] Attempting to load file: %s", shapePath.getFullPath().c_str());

   const ColladaUtils::ImportOptions& opts = ColladaUtils::getOptions();

   // Define post-processing steps
   unsigned flags =
      aiProcess_Triangulate |
      aiProcess_JoinIdenticalVertices |
      aiProcess_ValidateDataStructure |
      aiProcess_ConvertToLeftHanded & ~aiProcess_MakeLeftHanded;

   if (opts.convertLeftHanded)   flags |= aiProcess_MakeLeftHanded;
   if (opts.reverseWindingOrder) flags |= aiProcess_FlipWindingOrder;
   if (opts.genUVCoords)         flags |= aiProcess_GenUVCoords;
   if (opts.transformUVCoords)   flags |= aiProcess_TransformUVCoords;
   if (opts.limitBoneWeights)    flags |= aiProcess_LimitBoneWeights;
   if (opts.calcTangentSpace)    flags |= aiProcess_CalcTangentSpace;
   if (opts.findInstances)       flags |= aiProcess_FindInstances;
   if (opts.removeRedundantMats) flags |= aiProcess_RemoveRedundantMaterials;
   if (opts.joinIdenticalVerts)  flags |= aiProcess_JoinIdenticalVertices;
   if (opts.invertNormals)       flags |= aiProcess_FixInfacingNormals;
   if (opts.flipUVCoords)        flags |= aiProcess_FlipUVs;


   if (Con::getBoolVariable("$Assimp::OptimizeMeshes", false)) {
      flags |= aiProcess_OptimizeMeshes | aiProcess_OptimizeGraph;
   }
   if (Con::getBoolVariable("$Assimp::SplitLargeMeshes", false)) {
      flags |= aiProcess_SplitLargeMeshes;
   }


   struct aiLogStream shapeLog = aiGetPredefinedLogStream(aiDefaultLogStream_STDOUT, NULL);
   shapeLog.callback = assimpLogCallback;
   shapeLog.user = 0;
   aiAttachLogStream(&shapeLog);
#ifdef TORQUE_DEBUG
   aiEnableVerboseLogging(true);
#endif

   // Read the file
   mScene = mImporter.ReadFile(shapePath.getFullPath().c_str(), flags);

   if (!mScene || !mScene->mRootNode) {
      Con::errorf("[ASSIMP] ERROR: Could not load file: %s", shapePath.getFullPath().c_str());
      Con::errorf("[ASSIMP] Importer error: %s", mImporter.GetErrorString());
      TSShapeLoader::updateProgress(TSShapeLoader::Load_Complete, "Import failed");
      return;
   }

   Con::printf("[ASSIMP] Mesh Count: %d", mScene->mNumMeshes);
   Con::printf("[ASSIMP] Material Count: %d", mScene->mNumMaterials);

#ifdef TORQUE_DEBUG
   debugSceneMetaData(mScene);
#endif

   // Handle scaling
   configureImportUnits();

   if (mScene->mMetaData) {
      aiString fmt;
      if (mScene->mMetaData->Get("SourceAsset_Format", fmt)) {
         if (dStrstr(fmt.C_Str(), "FBX") != NULL) {
            // FBX is always centimeters. Convert to meters.
            ColladaUtils::getOptions().formatScaleFactor = 0.0100f;
            Con::printf("[ASSIMP] FBX detected: applying 0.01 scale (cm -> m).");
         }
      }
   }

   getRootAxisTransform();

   for (U32 i = 0; i < mScene->mNumTextures; ++i) {
      extractTexture(i, mScene->mTextures[i]);
   }

   // Load all materials
   AssimpAppMaterial::sDefaultMatNumber = 0;
   AssimpAppMesh::sMaterialRemap.setSize(mScene->mNumMaterials);
   for (U32 i = 0; i < mScene->mNumMaterials; ++i)
   {
      if (FindMatch::isMatchMultipleExprs(ColladaUtils::getOptions().neverImportMat,
         mScene->mMaterials[i]->GetName().C_Str(), false))
      {
         AssimpAppMesh::sMaterialRemap[i] = TSDrawPrimitive::NoMaterial; // TSDrawPrimitive::NoMaterial
         continue;
      }
      AssimpAppMesh::sMaterialRemap[i] = AppMesh::appMaterials.size();
      AppMesh::appMaterials.push_back(new AssimpAppMaterial(mScene->mMaterials[i]));
   }

   // Setup LOD checks
   detectDetails();

   aiNode* root = mScene->mRootNode;
   for (S32 iNode = 0; iNode < root->mNumChildren; iNode++)
   {
      aiNode* child = root->mChildren[iNode];
      AssimpAppNode* node = new AssimpAppNode(mScene, child);
      if (!processNode(node)) {
         delete node;
      }
   }

   if (!boundsNode) {
      aiNode* reqNode = new aiNode("bounds");
      reqNode->mTransformation = aiMatrix4x4();
      AssimpAppNode* appBoundsNode = new AssimpAppNode(mScene, reqNode);
      if (!processNode(appBoundsNode)) {
         delete appBoundsNode;
      }
   }

   // Process animations if available
   processAnimations();

   // Clean up log stream
   aiDetachLogStream(&shapeLog);
}

void AssimpShapeLoader::configureImportUnits() {
   auto& opts = ColladaUtils::getOptions();

   // Configure unit scaling
   if (opts.unit > 0.0f)
      return;


   // Try metadata for some formats
   if (mScene->mMetaData)
   {
      F64 unitScaleFactor = 1.0;
      if (!getMetaDouble("UnitScaleFactor", unitScaleFactor)) {
         F32 floatVal;
         S32 intVal;
         if (getMetaFloat("UnitScaleFactor", floatVal)) {
            unitScaleFactor = static_cast<F64>(floatVal);
         }
         else if (getMetaInt("UnitScaleFactor", intVal)) {
            unitScaleFactor = static_cast<F64>(intVal);
         }
      }

      opts.formatScaleFactor = unitScaleFactor;

      unitScaleFactor = 1.0;
      if (!getMetaDouble("OriginalUnitScaleFactor", unitScaleFactor)) {
         F32 floatVal;
         S32 intVal;
         if (getMetaFloat("OriginalUnitScaleFactor", floatVal)) {
            unitScaleFactor = static_cast<F64>(floatVal);
         }
         else if (getMetaInt("OriginalUnitScaleFactor", intVal)) {
            unitScaleFactor = static_cast<F64>(intVal);
         }
      }

      opts.unit = unitScaleFactor;

      // FBX may use another property name
      U32 unit = 0;
      if (mScene->mMetaData->Get("Unit", unit))
      {
         opts.unit = (F32)unit;
      }

      F32 fps;
      if(getMetaFloat("CustomFrameRate", fps))
         opts.animFPS = fps;
   }
}

void AssimpShapeLoader::getRootAxisTransform()
{
   int upAxis = 1, upSign = 1;
   int frontAxis = 2, frontSign = -1;
   int coordAxis = 0, coordSign = 1;

   aiMetadata* meta = mScene->mMetaData;
   if (meta)
   {
      meta->Get("UpAxis", upAxis);
      meta->Get("UpAxisSign", upSign);
      meta->Get("FrontAxis", frontAxis);
      meta->Get("FrontAxisSign", frontSign);
      meta->Get("CoordAxis", coordAxis);
      meta->Get("CoordAxisSign", coordSign);
   }

   if (ColladaUtils::getOptions().upAxis != UPAXISTYPE_COUNT)
   {
      switch (ColladaUtils::getOptions().upAxis)
      {
      case UPAXISTYPE_X_UP: upAxis = 0; break;
      case UPAXISTYPE_Y_UP: upAxis = 1; break;
      case UPAXISTYPE_Z_UP: upAxis = 2; break;
      default: break;
      }
   }

   domUpAxisType canonicalAxis;
   switch (upAxis)
   {
   case 0: canonicalAxis = UPAXISTYPE_X_UP; break;
   case 1: canonicalAxis = UPAXISTYPE_Y_UP; break;
   case 2: canonicalAxis = UPAXISTYPE_Z_UP; break;
   default: canonicalAxis = UPAXISTYPE_Y_UP; break;
   }

   ColladaUtils::getOptions().upAxis = canonicalAxis;
   MatrixF rot(true);

   // Build source basis
   auto axisToVector = [](int axis, int sign) -> Point3F
   {
      Point3F v(0, 0, 0);
      v[axis] = (F32)sign;
      return v;
   };

   Point3F forward = axisToVector(frontAxis, -frontSign);
   Point3F up = axisToVector(upAxis, upSign);
   Point3F right = mCross(forward, up);

   // Recompute forward
   forward = mCross(up, right);

   // Normalize (defensive, though they should already be unit)
   right.normalize();
   forward.normalize();
   up.normalize();

   MatrixF srcBasis(true);
   srcBasis.setColumn(0, right);
   srcBasis.setColumn(1, forward);
   srcBasis.setColumn(2, up);

   // Convert to Torque space
   rot = srcBasis;
   rot.inverse();

   ColladaUtils::getOptions().axisCorrectionMat = rot;
}

void AssimpShapeLoader::processAnimations()
{
   if (mScene->mNumAnimations == 0)
      return;

   // First pass: check whether this is an export with multiple actions.
   // tested on Blender -> FBX only, gltf doesnt work.
   bool hasMultipleActions = false;
   if(mScene->mNumAnimations > 1)
      hasMultipleActions = true;

   if (!hasMultipleActions)
   {
      F64 srcTPS = mScene->mAnimations[0]->mTicksPerSecond;
      F64 srcDur = mScene->mAnimations[0]->mDuration;

      ColladaUtils::ImportOptions& opts = ColladaUtils::getOptions();
      if (srcTPS <= 0.0 && srcDur < 100.0)
         opts.animTiming = ColladaUtils::ImportOptions::Seconds;
      else if (srcTPS >= 999.0 && srcTPS <= 1001.0)
         opts.animTiming = ColladaUtils::ImportOptions::Milliseconds;
      else
         opts.animTiming = ColladaUtils::ImportOptions::FrameCount;

      F64 targetTPS = (srcTPS > 0.0) ? srcTPS : ColladaUtils::getOptions().animFPS;

      // Original single-timeline path (no '|' in any animation name).
      // Concatenate all channels into one ambient sequence, exactly as before.
      aiAnimation* ambientSeq = new aiAnimation();
      ambientSeq->mName = "ambient";

      Vector<aiNodeAnim*> ambientChannels;
      F32 maxKeyTime = 0.0f;

      for (U32 i = 0; i < mScene->mNumAnimations; ++i)
      {
         aiAnimation* anim = mScene->mAnimations[i];
         for (U32 j = 0; j < anim->mNumChannels; j++)
         {
            aiNodeAnim* nodeAnim = anim->mChannels[j];
            for (U32 k = 0; k < nodeAnim->mNumPositionKeys; k++)
               maxKeyTime = getMax(maxKeyTime, (F32)nodeAnim->mPositionKeys[k].mTime);
            for (U32 k = 0; k < nodeAnim->mNumRotationKeys; k++)
               maxKeyTime = getMax(maxKeyTime, (F32)nodeAnim->mRotationKeys[k].mTime);
            for (U32 k = 0; k < nodeAnim->mNumScalingKeys; k++)
               maxKeyTime = getMax(maxKeyTime, (F32)nodeAnim->mScalingKeys[k].mTime);
            ambientChannels.push_back(nodeAnim);
         }
      }

      ambientSeq->mNumChannels = ambientChannels.size();
      ambientSeq->mChannels = ambientChannels.address();
      ambientSeq->mDuration = maxKeyTime;
      ambientSeq->mTicksPerSecond = targetTPS;

      appSequences.push_back(new AssimpAppSequence(ambientSeq));
      return;
   }

   // Calculate the timing used for this import.
   {
      F64 srcTPS = mScene->mAnimations[0]->mTicksPerSecond;
      F64 srcDur = mScene->mAnimations[0]->mDuration;

      ColladaUtils::ImportOptions& opts = ColladaUtils::getOptions();
      if (srcTPS <= 0.0 && srcDur < 100.0)
         opts.animTiming = ColladaUtils::ImportOptions::Seconds;
      else if (srcTPS >= 999.0 && srcTPS <= 1001.0)
         opts.animTiming = ColladaUtils::ImportOptions::Milliseconds;
      else
         opts.animTiming = ColladaUtils::ImportOptions::FrameCount;

      Con::printf("[ASSIMP] Animation timing: %s (mTicksPerSecond=%.1f)",
         opts.animTiming == ColladaUtils::ImportOptions::Seconds ? "Seconds" :
         opts.animTiming == ColladaUtils::ImportOptions::Milliseconds ? "Milliseconds" : "FrameCount",
         (F32)srcTPS);
   }

   // Seperated action path.
   // Data structures (kept as parallel vectors to avoid STL map dependency):
   //    actionNames[i]     - unique action name (after '|')
   //    actionDurations[i] - duration (ticks) of that action
   //    actionChannels[i]  - correctly-matched channels for that action
   //    actionNodesSeen[i] - node names already added (deduplication guard)
   Vector<String>               actionNames;
   Vector<F64>                  actionDurations;
   Vector< Vector<aiNodeAnim*> > actionChannels;
   Vector< Vector<String> >     actionNodesSeen;

   F64 ticksPerSecond = mScene->mAnimations[0]->mTicksPerSecond;
   if (ticksPerSecond <= 0.0) ticksPerSecond = 30.0;

   // GLTF stores times in seconds (mTicksPerSecond==0, mDuration < 100).
   // FBX stores frame-count ticks (mTicksPerSecond > 0, mDuration in hundreds).
   // Detect and rescale to ticks so both formats produce the same units downstream.
   F64 srcTPS = mScene->mAnimations[0]->mTicksPerSecond;
   F64 srcDur = mScene->mAnimations[0]->mDuration;
   bool timesInSeconds = (srcTPS <= 0.0 && srcDur < 100.0);
   F32  timeScale = timesInSeconds ? (F32)ticksPerSecond : 1.0f;

   if (timesInSeconds)
   {
      // Rescale all key timestamps in every animation channel in-place
      for (U32 i = 0; i < mScene->mNumAnimations; ++i)
      {
         aiAnimation* anim = mScene->mAnimations[i];
         anim->mDuration *= timeScale;
         for (U32 j = 0; j < anim->mNumChannels; ++j)
         {
            aiNodeAnim* ch = anim->mChannels[j];
            for (U32 k = 0; k < ch->mNumPositionKeys; ++k) ch->mPositionKeys[k].mTime *= timeScale;
            for (U32 k = 0; k < ch->mNumRotationKeys; ++k) ch->mRotationKeys[k].mTime *= timeScale;
            for (U32 k = 0; k < ch->mNumScalingKeys; ++k) ch->mScalingKeys[k].mTime *= timeScale;
         }
      }
   }

   for (U32 i = 0; i < mScene->mNumAnimations; ++i)
   {
      aiAnimation* anim = mScene->mAnimations[i];
      const char* fullName = anim->mName.C_Str();
      const char* pipe = dStrchr(fullName, '|');

      // Extract "NodePrefix" and "ActionName" from "NodePrefix|ActionName"
      String nodePrefix = pipe ? String(fullName, (U32)(pipe - fullName)) : String("");
      String actionName = pipe ? String(pipe + 1) : String(fullName);

      // Find or create the action slot
      S32 slot = -1;
      for (S32 k = 0; k < (S32)actionNames.size(); ++k)
      {
         if (actionNames[k] == actionName) { slot = k; break; }
      }
      if (slot == -1)
      {
         slot = (S32)actionNames.size();
         actionNames.push_back(actionName);
         actionDurations.push_back(0.0);
         actionChannels.push_back(Vector<aiNodeAnim*>());
         actionNodesSeen.push_back(Vector<String>());
      }

      // Track maximum duration for this action
      if (anim->mDuration > actionDurations[slot])
         actionDurations[slot] = anim->mDuration;

      // Accept channels whose node name matches the prefix
      for (U32 j = 0; j < anim->mNumChannels; ++j)
      {
         aiNodeAnim* chan = anim->mChannels[j];
         String chanNode = chan->mNodeName.C_Str();

         if (!nodePrefix.isEmpty() && nodePrefix != chanNode)
            continue;

         // Deduplicate: first channel for a given node in this action wins
         bool alreadyAdded = false;
         for (U32 n = 0; n < actionNodesSeen[slot].size(); ++n)
         {
            if (actionNodesSeen[slot][n] == chanNode) { alreadyAdded = true; break; }
         }
         if (!alreadyAdded)
         {
            actionChannels[slot].push_back(chan);
            actionNodesSeen[slot].push_back(chanNode);
         }
      }
   }

   // -----------------------------------------------------------------------
   // AMBIENT and NAMED SEQUENCES both use own-action-only channels.
   // -----------------------------------------------------------------------
   {
      // AMBIENT: use ONLY each node's own canonical action channel.
      Vector<aiNodeAnim*> ownChans;
      F64 ambientDuration = 0.0;

      for (U32 i = 0; i < actionNames.size(); ++i)
      {
         String      ownerName;
         aiNodeAnim* ownerChan = nullptr;

         for (U32 j = 0; j < actionChannels[i].size(); ++j)
         {
            const String& nodeName = actionNodesSeen[i][j];
            U32 nodeLen = nodeName.length();
            // Exact owner match: action name = nodeName + "Action" [+ optional suffix].
            const char* actionStr = actionNames[i].c_str();
            if (dStrnicmp(actionStr, nodeName.c_str(), nodeLen) == 0
               && dStrnicmp(actionStr + nodeLen, "Action", 6) == 0
               && nodeLen > ownerName.length())
            {
               ownerName = nodeName;
               ownerChan = actionChannels[i][j];
            }
         }

         if (ownerChan)
         {
            ownChans.push_back(ownerChan);
            ambientDuration = getMax(ambientDuration, actionDurations[i]);
            Con::printf("[ASSIMP] Ambient channel: node=%-25s action=%s  duration=%.1f ticks",
               ownerName.c_str(), actionNames[i].c_str(), (F32)actionDurations[i]);
         }
      }

      aiAnimation* ambientAnim = new aiAnimation();
      ambientAnim->mName = aiString("ambient");
      ambientAnim->mTicksPerSecond = ticksPerSecond;
      ambientAnim->mDuration = ambientDuration;
      ambientAnim->mNumChannels = ownChans.size();
      ambientAnim->mChannels = new aiNodeAnim * [ownChans.size()];
      for (U32 i = 0; i < ownChans.size(); ++i)
         ambientAnim->mChannels[i] = ownChans[i];

      Con::printf("[ASSIMP] Ambient: %d own-action channels, duration=%.1f ticks (%.2f sec)",
         ambientAnim->mNumChannels, (F32)ambientDuration, (F32)(ambientDuration / ticksPerSecond));

      appSequences.push_back(new AssimpAppSequence(ambientAnim));
   }

   // -----------------------------------------------------------------------
   // NAMED SEQUENCES: one sequence per unique action, containing ONLY the
   // owning node's channel. 
   // -----------------------------------------------------------------------
   for (U32 i = 0; i < actionNames.size(); ++i)
   {
      if (actionChannels[i].empty())
         continue;

      // Identify the owning node by exact nodeName+"Action" match (same logic as ambient)
      String      ownerName;
      aiNodeAnim* ownerChan = nullptr;
      for (U32 j = 0; j < actionChannels[i].size(); ++j)
      {
         const String& nodeName = actionNodesSeen[i][j];
         U32 nodeLen = nodeName.length();
         const char* actionStr = actionNames[i].c_str();
         if (dStrnicmp(actionStr, nodeName.c_str(), nodeLen) == 0
            && dStrnicmp(actionStr + nodeLen, "Action", 6) == 0
            && nodeLen > ownerName.length())
         {
            ownerName = nodeName;
            ownerChan = actionChannels[i][j];
         }
      }

      if (!ownerChan)
         continue;

      aiAnimation* seq = new aiAnimation();
      seq->mName = aiString(actionNames[i].c_str());
      seq->mTicksPerSecond = ticksPerSecond;
      seq->mDuration = actionDurations[i];
      seq->mNumChannels = 1;
      seq->mChannels = new aiNodeAnim * [1];
      seq->mChannels[0] = ownerChan;

      Con::printf("[ASSIMP] Sequence '%s': owner=%s  duration=%.1f ticks",
         actionNames[i].c_str(), ownerName.c_str(), (F32)actionDurations[i]);

      appSequences.push_back(new AssimpAppSequence(seq));
   }
}

void AssimpShapeLoader::computeBounds(Box3F& bounds)
{
   TSShapeLoader::computeBounds(bounds);

   // Check if the model origin needs adjusting
   bool adjustCenter = ColladaUtils::getOptions().adjustCenter;
   bool adjustFloor = ColladaUtils::getOptions().adjustFloor;
   if (bounds.isValidBox() && (adjustCenter || adjustFloor))
   {
      // Compute shape offset
      Point3F shapeOffset = Point3F::Zero;
      if (adjustCenter)
      {
         bounds.getCenter(&shapeOffset);
         shapeOffset = -shapeOffset;
      }
      if (adjustFloor)
         shapeOffset.z = -bounds.minExtents.z;

      // Adjust bounds
      bounds.minExtents += shapeOffset;
      bounds.maxExtents += shapeOffset;

      // Now adjust all positions for root level nodes (nodes with no parent)
      for (S32 iNode = 0; iNode < shape->nodes.size(); iNode++)
      {
         if (!appNodes[iNode]->isParentRoot())
            continue;

         // Adjust default translation
         shape->defaultTranslations[iNode] += shapeOffset;

         // Adjust animated translations
         for (S32 iSeq = 0; iSeq < shape->sequences.size(); iSeq++)
         {
            const TSShape::Sequence& seq = shape->sequences[iSeq];
            if (seq.translationMatters.test(iNode))
            {
               for (S32 iFrame = 0; iFrame < seq.numKeyframes; iFrame++)
               {
                  S32 index = seq.baseTranslation + seq.translationMatters.count(iNode) * seq.numKeyframes + iFrame;
                  shape->nodeTranslations[index] += shapeOffset;
               }
            }
         }
      }
   }
}

bool AssimpShapeLoader::fillGuiTreeView(const char* sourceShapePath, GuiTreeViewCtrl* tree)
{
   Assimp::Importer importer;
   Torque::Path path(sourceShapePath);
   String cleanFile = AppMaterial::cleanString(path.getFileName());

   // Attempt to import with Assimp.
   const aiScene* shapeScene = importer.ReadFile(path.getFullPath().c_str(), (aiProcessPreset_TargetRealtime_Quality | aiProcess_CalcTangentSpace)
      & ~aiProcess_RemoveRedundantMaterials & ~aiProcess_GenSmoothNormals);

   if (!shapeScene)
   {
      Con::printf("AssimpShapeLoader::fillGuiTreeView - Assimp Error: %s", importer.GetErrorString());
      return false;
   }
   mScene = shapeScene;

   // Initialize tree
   tree->removeItem(0);
   S32 meshItem = tree->insertItem(0, "Meshes", String::ToString("%i", shapeScene->mNumMeshes));
   S32 matItem = tree->insertItem(0, "Materials", String::ToString("%i", shapeScene->mNumMaterials));
   S32 animItem = tree->insertItem(0, "Animations", String::ToString("%i", shapeScene->mNumAnimations));
   //S32 lightsItem = tree->insertItem(0, "Lights", String::ToString("%i", shapeScene->mNumLights));
   //S32 texturesItem = tree->insertItem(0, "Textures", String::ToString("%i", shapeScene->mNumTextures));

   //Details!
   U32 numPolys = 0;
   U32 numVerts = 0;
   for (U32 i = 0; i < shapeScene->mNumMeshes; i++)
   {
      tree->insertItem(meshItem, String::ToString("%s", shapeScene->mMeshes[i]->mName.C_Str()));
      numPolys += shapeScene->mMeshes[i]->mNumFaces;
      numVerts += shapeScene->mMeshes[i]->mNumVertices;
   }

   U32 defaultMatNumber = 0;
   for (U32 i = 0; i < shapeScene->mNumMaterials; i++)
   {
      aiMaterial* aiMat = shapeScene->mMaterials[i];

      aiString matName;
      aiMat->Get(AI_MATKEY_NAME, matName);
      String name = matName.C_Str();
      if (name.isEmpty())
      {
         name = AppMaterial::cleanString(path.getFileName());
         name += "_defMat";
         name += String::ToString("%d", defaultMatNumber);
         defaultMatNumber++;
      }

      aiString texPath;
      aiMat->GetTexture(aiTextureType::aiTextureType_DIFFUSE, 0, &texPath);
      String texName = texPath.C_Str();
      if (texName.isEmpty())
      {
         aiColor3D read_color(1.f, 1.f, 1.f);
         if (AI_SUCCESS == aiMat->Get(AI_MATKEY_COLOR_DIFFUSE, read_color))
            texName = String::ToString("Color: %0.3f %0.3f %0.3f", (F32)read_color.r, (F32)read_color.g, (F32)read_color.b); //formatted as words for easy parsing
         else
            texName = "No Texture";
      }
      else
         texName = AssimpAppMaterial::cleanTextureName(texName, cleanFile, sourceShapePath, true);

      tree->insertItem(matItem, String::ToString("%s", name.c_str()), String::ToString("%s", texName.c_str()));
   }

   if (shapeScene->mNumAnimations == 0)
   {
      tree->insertItem(animItem, "ambient", "animation", "", 0, 0);
   }
   else
   {
      for (U32 i = 0; i < shapeScene->mNumAnimations; i++)
      {
         tree->insertItem(animItem, shapeScene->mAnimations[i]->mName.C_Str(), "animation", "", 0, 0);
      }
   }

   U32 numNodes = 0;
   if (shapeScene->mRootNode)
   {
      S32 nodesItem = tree->insertItem(0, "Nodes", "");
      addNodeToTree(nodesItem, shapeScene->mRootNode, tree, numNodes);
      tree->setItemValue(nodesItem, String::ToString("%i", numNodes));
   }

   U32 numMetaTags = shapeScene->mMetaData ? shapeScene->mMetaData->mNumProperties : 0;
   if (numMetaTags)
      addMetaDataToTree(shapeScene->mMetaData, tree);

   F64 unit;
   if (!getMetaDouble("UnitScaleFactor", unit))
      unit = 1.0f;

   S32 upAxis;
   if (!getMetaInt("UpAxis", upAxis))
      upAxis = UPAXISTYPE_Z_UP;

   /*for (U32 i = 0; i < shapeScene->mNumLights; i++)
   {
      treeObj->insertItem(lightsItem, String::ToString("%s", shapeScene->mLights[i]->mType));
   }*/

   // Store shape information in the tree control
   tree->setDataField(StringTable->insert("_nodeCount"), 0, avar("%d", numNodes));
   tree->setDataField(StringTable->insert("_meshCount"), 0, avar("%d", shapeScene->mNumMeshes));
   tree->setDataField(StringTable->insert("_polygonCount"), 0, avar("%d", numPolys));
   tree->setDataField(StringTable->insert("_materialCount"), 0, avar("%d", shapeScene->mNumMaterials));
   tree->setDataField(StringTable->insert("_lightCount"), 0, avar("%d", shapeScene->mNumLights));
   tree->setDataField(StringTable->insert("_animCount"), 0, avar("%d", shapeScene->mNumAnimations));
   tree->setDataField(StringTable->insert("_textureCount"), 0, avar("%d", shapeScene->mNumTextures));
   tree->setDataField(StringTable->insert("_vertCount"), 0, avar("%d", numVerts));
   tree->setDataField(StringTable->insert("_metaTagCount"), 0, avar("%d", numMetaTags));
   tree->setDataField(StringTable->insert("_unit"), 0, avar("%g", (F32)unit));

   if (upAxis == UPAXISTYPE_X_UP)
      tree->setDataField(StringTable->insert("_upAxis"), 0, "X_AXIS");
   else if (upAxis == UPAXISTYPE_Y_UP)
      tree->setDataField(StringTable->insert("_upAxis"), 0, "Y_AXIS");
   else
      tree->setDataField(StringTable->insert("_upAxis"), 0, "Z_AXIS");

   return true;
}

/// Check if an up-to-date cached DTS is available for this file
bool AssimpShapeLoader::canLoadCachedDTS(const Torque::Path& path)
{
   // Generate the cached filename
   Torque::Path cachedPath(path);
   cachedPath.setExtension("cached.dts");

   // Check if a cached DTS newer than this file is available
   FileTime cachedModifyTime;
   if (Platform::getFileTimes(cachedPath.getFullPath(), NULL, &cachedModifyTime))
   {
      bool forceLoad = Con::getBoolVariable("$assimp::forceLoad", false);

      FileTime daeModifyTime;
      if (!Platform::getFileTimes(path.getFullPath(), NULL, &daeModifyTime) ||
         (!forceLoad && (Platform::compareFileTimes(cachedModifyTime, daeModifyTime) >= 0)))
      {
         // Original file not found, or cached DTS is newer
         return true;
      }
   }
   return false;
}

void AssimpShapeLoader::assimpLogCallback(const char* message, char* user)
{
   Con::printf("[Assimp log message] %s", StringUnit::getUnit(message, 0, "\n"));
}

bool AssimpShapeLoader::ignoreNode(const String& name)
{
   // Do not add AssimpFbx dummy nodes to the TSShape. See: Assimp::FBX::ImportSettings::preservePivots
   // https://github.com/assimp/assimp/blob/master/code/FBXImportSettings.h#L116-L135
   if (name.find("_$AssimpFbx$_") != String::NPos)
      return true;

   if (FindMatch::isMatchMultipleExprs(ColladaUtils::getOptions().alwaysImport, name, false))
      return false;

   return FindMatch::isMatchMultipleExprs(ColladaUtils::getOptions().neverImport, name, false);
}

bool AssimpShapeLoader::ignoreMesh(const String& name)
{
   if (FindMatch::isMatchMultipleExprs(ColladaUtils::getOptions().alwaysImportMesh, name, false))
      return false;
   else
      return FindMatch::isMatchMultipleExprs(ColladaUtils::getOptions().neverImportMesh, name, false);
}

void AssimpShapeLoader::detectDetails()
{
   // Set LOD option
   bool singleDetail = true;
   switch (ColladaUtils::getOptions().lodType)
   {
   case ColladaUtils::ImportOptions::DetectDTS:
      // Check for a baseXX->startXX hierarchy at the top-level, if we find
      // one, use trailing numbers for LOD, otherwise use a single size
      for (S32 iNode = 0; singleDetail && (iNode < mScene->mRootNode->mNumChildren); iNode++) {
         aiNode* node = mScene->mRootNode->mChildren[iNode];
         if (node && dStrStartsWith(node->mName.C_Str(), "base")) {
            for (S32 iChild = 0; iChild < node->mNumChildren; iChild++) {
               aiNode* child = node->mChildren[iChild];
               if (child && dStrStartsWith(child->mName.C_Str(), "start")) {
                  singleDetail = false;
                  break;
               }
            }
         }
      }
      break;

   case ColladaUtils::ImportOptions::SingleSize:
      singleDetail = true;
      break;

   case ColladaUtils::ImportOptions::TrailingNumber:
      singleDetail = false;
      break;

   default:
      break;
   }

   AssimpAppMesh::fixDetailSize(singleDetail, ColladaUtils::getOptions().singleDetailSize);
}

void AssimpShapeLoader::extractTexture(U32 index, aiTexture* pTex)
{  // Cache an embedded texture to disk
   updateProgress(Load_EnumerateScene, "Extracting Textures...", mScene->mNumTextures, index);
   Con::printf("[Assimp] Extracting Texture %s, W: %d, H: %d, %d of %d, format hint: (%s)", pTex->mFilename.C_Str(),
      pTex->mWidth, pTex->mHeight, index, mScene->mNumTextures, pTex->achFormatHint);

   // Create the texture filename
   String cleanFile = AppMaterial::cleanString(TSShapeLoader::getShapePath().getFileName());
   String texName = String::ToString("%s_cachedTex%d", cleanFile.c_str(), index);
   Torque::Path texPath = shapePath;
   texPath.setFileName(texName);

   if (pTex->mHeight == 0)
   {  // Compressed format, write the data directly to disc
      texPath.setExtension(pTex->achFormatHint);
      FileStream* outputStream;
      if ((outputStream = FileStream::createAndOpen(texPath.getFullPath(), Torque::FS::File::Write, FileStream::AsyncMode::Background)) != NULL)
      {
         outputStream->setPosition(0);
         outputStream->write(pTex->mWidth, pTex->pcData);
         outputStream->close();
         delete outputStream;
      }
   }
   else
   {  // Embedded pixel data, fill a bitmap and save it.
      GFXTexHandle shapeTex;
      shapeTex.set(pTex->mWidth, pTex->mHeight, GFXFormatR8G8B8A8_SRGB, &GFXDynamicTextureSRGBProfile,
         String::ToString("AssimpShapeLoader (%s:%i)", __FILE__, __LINE__), 1, 0);
      GFXLockedRect* rect = shapeTex.lock();

      for (U32 y = 0; y < pTex->mHeight; ++y)
      {
         for (U32 x = 0; x < pTex->mWidth; ++x)
         {
            U32 targetIndex = (y * rect->pitch) + (x * 4);
            U32 sourceIndex = ((y * pTex->mWidth) + x) * 4;
            rect->bits[targetIndex] = pTex->pcData[sourceIndex].r;
            rect->bits[targetIndex + 1] = pTex->pcData[sourceIndex].g;
            rect->bits[targetIndex + 2] = pTex->pcData[sourceIndex].b;
            rect->bits[targetIndex + 3] = pTex->pcData[sourceIndex].a;
         }
      }
      shapeTex.unlock();

      texPath.setExtension("png");
      shapeTex->dumpToDisk("PNG", texPath.getFullPath());
   }
}

void AssimpShapeLoader::addNodeToTree(S32 parentItem, aiNode* node, GuiTreeViewCtrl* tree, U32& nodeCount)
{
   // Add this node
   S32 nodeItem = parentItem;
   String nodeName = node->mName.C_Str();
   if (!ignoreNode(nodeName))
   {
      if (nodeName.isEmpty())
         nodeName = "null";
      nodeItem = tree->insertItem(parentItem, nodeName.c_str(), String::ToString("%i", node->mNumChildren));
      nodeCount++;
   }

   // Add any child nodes
   for (U32 n = 0; n < node->mNumChildren; ++n)
      addNodeToTree(nodeItem, node->mChildren[n], tree, nodeCount);
}

void AssimpShapeLoader::addMetaDataToTree(const aiMetadata* metaData, GuiTreeViewCtrl* tree)
{
   S32 metaItem = tree->insertItem(0, "MetaData", String::ToString("%i", metaData->mNumProperties));

   aiString valString;
   aiVector3D valVec;

   for (U32 n = 0; n < metaData->mNumProperties; ++n)
   {
      String keyStr = metaData->mKeys[n].C_Str();
      keyStr += ": ";
      switch (metaData->mValues[n].mType)
      {
      case AI_BOOL:
         keyStr += ((bool)metaData->mValues[n].mData) ? "true" : "false";
         break;
      case AI_INT32:
         keyStr += String::ToString(*((S32*)(metaData->mValues[n].mData)));
         break;
      case AI_UINT64:
         keyStr += String::ToString("%I64u", *((U64*)metaData->mValues[n].mData));
         break;
      case AI_FLOAT:
         keyStr += String::ToString(*((F32*)metaData->mValues[n].mData));
         break;
      case AI_DOUBLE:
         keyStr += String::ToString(*((F64*)metaData->mValues[n].mData));
         break;
      case AI_AISTRING:
         metaData->Get<aiString>(metaData->mKeys[n], valString);
         keyStr += valString.C_Str();
         break;
      case AI_AIVECTOR3D:
         metaData->Get<aiVector3D>(metaData->mKeys[n], valVec);
         keyStr += String::ToString("%f, %f, %f", valVec.x, valVec.y, valVec.z);
         break;
      default:
         break;
      }

      tree->insertItem(metaItem, keyStr.c_str(), String::ToString("%i", n));
   }
}

bool AssimpShapeLoader::getMetabool(const char* key, bool& boolVal)
{
   if (!mScene || !mScene->mMetaData)
      return false;

   String keyStr = key;
   for (U32 n = 0; n < mScene->mMetaData->mNumProperties; ++n)
   {
      if (keyStr.equal(mScene->mMetaData->mKeys[n].C_Str(), String::NoCase))
      {
         if (mScene->mMetaData->mValues[n].mType == AI_BOOL)
         {
            boolVal = (bool)mScene->mMetaData->mValues[n].mData;
            return true;
         }
      }
   }
   return false;
}

bool AssimpShapeLoader::getMetaInt(const char* key, S32& intVal)
{
   if (!mScene || !mScene->mMetaData)
      return false;

   String keyStr = key;
   for (U32 n = 0; n < mScene->mMetaData->mNumProperties; ++n)
   {
      if (keyStr.equal(mScene->mMetaData->mKeys[n].C_Str(), String::NoCase))
      {
         if (mScene->mMetaData->mValues[n].mType == AI_INT32)
         {
            intVal = *((S32*)(mScene->mMetaData->mValues[n].mData));
            return true;
         }
      }
   }
   return false;
}

bool AssimpShapeLoader::getMetaFloat(const char* key, F32& floatVal)
{
   if (!mScene || !mScene->mMetaData)
      return false;

   String keyStr = key;
   for (U32 n = 0; n < mScene->mMetaData->mNumProperties; ++n)
   {
      if (keyStr.equal(mScene->mMetaData->mKeys[n].C_Str(), String::NoCase))
      {
         if (mScene->mMetaData->mValues[n].mType == AI_FLOAT)
         {
            floatVal = *((F32*)mScene->mMetaData->mValues[n].mData);
            return true;
         }
      }
   }
   return false;
}

bool AssimpShapeLoader::getMetaDouble(const char* key, F64& doubleVal)
{
   if (!mScene || !mScene->mMetaData)
      return false;

   String keyStr = key;
   for (U32 n = 0; n < mScene->mMetaData->mNumProperties; ++n)
   {
      if (keyStr.equal(mScene->mMetaData->mKeys[n].C_Str(), String::NoCase))
      {
         if (mScene->mMetaData->mValues[n].mType == AI_DOUBLE)
         {
            doubleVal = *((F64*)mScene->mMetaData->mValues[n].mData);
            return true;
         }
      }
   }
   return false;
}

bool AssimpShapeLoader::getMetaString(const char* key, String& stringVal)
{
   if (!mScene || !mScene->mMetaData)
      return false;

   String keyStr = key;
   for (U32 n = 0; n < mScene->mMetaData->mNumProperties; ++n)
   {
      if (keyStr.equal(mScene->mMetaData->mKeys[n].C_Str(), String::NoCase))
      {
         if (mScene->mMetaData->mValues[n].mType == AI_AISTRING)
         {
            aiString valString;
            mScene->mMetaData->Get<aiString>(mScene->mMetaData->mKeys[n], valString);
            stringVal = valString.C_Str();
            return true;
         }
      }
   }
   return false;
}
//-----------------------------------------------------------------------------
/// This function is invoked by the resource manager based on file extension.
static bool sReadAssimp(const Torque::Path& path, TSShape*& res_shape)
{
   if (!Torque::FS::IsFile(path))
   {
      // File does not exist, bail.
      return false;
   }

   // Allow TSShapeConstructor object to override properties
   ColladaUtils::getOptions().reset();
   TSShapeConstructor* tscon = TSShapeConstructor::findShapeConstructorByFilename(path.getFullPath());
   bool autoDetectUpAxis = true;
   if (tscon)
   {
      ColladaUtils::getOptions() = tscon->mOptions;
      autoDetectUpAxis = (tscon->mOptions.upAxis == UPAXISTYPE_COUNT);
   }

   AssimpShapeLoader loader;
   TSShape* tss = loader.generateShape(path);

   // override default options with the ones provided by the assimp import.
   if (tscon && autoDetectUpAxis)
      tscon->mOptions = ColladaUtils::getOptions();
   if (tss)
   {
      TSShapeLoader::updateProgress(TSShapeLoader::Load_Complete, "Import complete");

      bool realMesh = false;
      for (U32 i = 0; i < tss->meshes.size(); ++i)
      {
         if (tss->meshes[i] && tss->meshes[i]->getMeshType() != TSMesh::NullMeshType)
         {
            realMesh = true;
            break;
         }
      }


      if (realMesh)
         Con::printf("[ASSIMP] Shape created successfully.");
      else
         Con::printf("[ASSIMP] Animation created successfully.");

      Torque::Path cachedPath(path);
      // Cache the model to a DTS file for faster loading next time.
      cachedPath.setExtension("cached.dts");
      // Cache the model to a DTS file for faster loading next time.
      FileStream dtsStream;
      if (dtsStream.open(cachedPath.getFullPath(), Torque::FS::File::Write))
      {
         Con::printf("Writing cached shape to %s", cachedPath.getFullPath().c_str());
         tss->write(&dtsStream);
      }

      // only save dsq if we have a real mesh to pair with it.
      if (tss->sequences.size() > 0 && realMesh)
      {
         Torque::Path dsqPath(cachedPath);
         dsqPath.setExtension("dsq");
         FileStream animOutStream;

         for (S32 i = 0; i < tss->sequences.size(); i++)
         {
            const String& seqName = tss->getName(tss->sequences[i].nameIndex);
            Con::printf("Writing DSQ Animation File for sequence '%s'", seqName.c_str());

            dsqPath.setFileName(cachedPath.getFileName() + "_" + seqName);
            if (animOutStream.open(dsqPath.getFullPath(), Torque::FS::File::Write))
            {
               tss->exportSequence(&animOutStream, tss->sequences[i], false);
               animOutStream.close();
            }
         }
      }
   }
   loader.releaseImport();
   res_shape = tss;
   return true;
}

DefineEngineFunction(GetShapeInfo, bool, (const char* shapePath, const char* ctrl, bool loadCachedDts), ("", "", true),
   "(string shapePath, GuiTreeViewCtrl ctrl) Collect scene information from "
   "a shape file and store it in a GuiTreeView control. This function is "
   "used by the assimp import gui to show a preview of the scene contents "
   "prior to import, and is probably not much use for anything else.\n"
   "@param shapePath shape filename\n"
   "@param ctrl GuiTreeView control to add elements to\n"
   "@return true if successful, false otherwise\n"
   "@ingroup Editors\n"
   "@internal")
{
   GuiTreeViewCtrl* tree;
   if (!Sim::findObject(ctrl, tree))
   {
      Con::errorf("enumColladaScene::Could not find GuiTreeViewCtrl '%s'", ctrl);
      return false;
   }

   // Check if a cached DTS is available => no need to import the source file
   // if we can load the DTS instead
   Torque::Path path(shapePath);
   if (loadCachedDts && AssimpShapeLoader::canLoadCachedDTS(path))
      return false;

   AssimpShapeLoader loader;
   return loader.fillGuiTreeView(shapePath, tree);
}
