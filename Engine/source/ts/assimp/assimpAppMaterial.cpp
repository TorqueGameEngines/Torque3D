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
//#define TORQUE_PBR_MATERIALS

#include "platform/platform.h"
#include "ts/loader/appSequence.h"
#include "ts/assimp/assimpAppMaterial.h"
#include "ts/assimp/assimpAppMesh.h"
#include "materials/materialManager.h"
#include "ts/tsMaterialList.h"
#include "core/stream/fileStream.h"

// assimp include files. 
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/types.h>

U32 AssimpAppMaterial::sDefaultMatNumber = 0;

String AppMaterial::cleanString(const String& str)
{
   String cleanStr(str);

   // Replace invalid characters with underscores
   const String badChars(" -,.+=*/[]%$~;:");
   for (String::SizeType i = 0; i < badChars.length(); i++)
      cleanStr.replace(badChars[i], '_');

   // Prefix with an underscore if string starts with a number
   if ((cleanStr[0] >= '0') && (cleanStr[0] <= '9'))
      cleanStr.insert(0, '_');

   return cleanStr;
}

AssimpAppMaterial::AssimpAppMaterial(const char* matName)
{
   name = ColladaUtils::getOptions().matNamePrefix;
   name += matName;

   // Set some defaults
   flags |= TSMaterialList::S_Wrap;
   flags |= TSMaterialList::T_Wrap;
}

AssimpAppMaterial::AssimpAppMaterial(aiMaterial* mtl) :
   mAIMat(mtl)
{
   aiString matName;
   mtl->Get(AI_MATKEY_NAME, matName);
   name = matName.C_Str();
   if (name.isEmpty())
   {
      name = cleanString(TSShapeLoader::getShapePath().getFileName());
      name += "_defMat";
      name += String::ToString("%d", sDefaultMatNumber);
      sDefaultMatNumber++;
   }
   name = ColladaUtils::getOptions().matNamePrefix + name;
   Con::printf("[ASSIMP] Loading Material: %s", name.c_str());
#ifdef TORQUE_DEBUG
   enumerateMaterialProperties(mtl);
#endif
}

Material* AssimpAppMaterial::createMaterial(const Torque::Path& path) const
{
   // The filename and material name are used as TorqueScript identifiers, so
   // clean them up first
   String cleanFile = cleanString(TSShapeLoader::getShapePath().getFileName());
   String cleanName = cleanString(getName());

   // Create the Material definition
   const String oldScriptFile = Con::getVariable("$Con::File");
   Con::setVariable("$Con::File", path.getFullPath());   // modify current script path so texture lookups are correct
   Material *newMat = MATMGR->allocateAndRegister(cleanName, getName());
   Con::setVariable("$Con::File", oldScriptFile);        // restore script path

   initMaterial(path, newMat);

   return newMat;
}

void AssimpAppMaterial::initMaterial(const Torque::Path& path, Material* mat) const
{
   String cleanFile = cleanString(TSShapeLoader::getShapePath().getFileName());
   String cleanName = cleanString(getName());

   // Determine the blend mode and transparency for this material
   Material::BlendOp blendOp = Material::None;
   bool translucent = false;
   float opacity = 1.0f;
   if (AI_SUCCESS == mAIMat->Get(AI_MATKEY_OPACITY, opacity))
   {
      if (opacity != 1.0f)
      {
         translucent = true;
         int blendInt;
         blendOp = Material::LerpAlpha;
         if (AI_SUCCESS == mAIMat->Get(AI_MATKEY_BLEND_FUNC, blendInt))
         {
            if (blendInt == aiBlendMode_Additive)
               blendOp = Material::Add;
         }
      }
   }
   else
   {  // No opacity key, see if it's defined as a gltf property
      aiString opacityMode;
      if (AI_SUCCESS == mAIMat->Get("$mat.gltf.alphaMode", 0, 0, opacityMode))
      {
         if (dStrcmp("MASK", opacityMode.C_Str()) == 0)
         {
            translucent = true;
            blendOp = Material::None;

            float cutoff;
            if (AI_SUCCESS == mAIMat->Get("$mat.gltf.alphaCutoff", 0, 0, cutoff))
            {
               mat->mAlphaRef = (U32)(cutoff * 255);  // alpha ref 0-255
               mat->mAlphaTest = true;
            }
         }
         else if (dStrcmp("BLEND", opacityMode.C_Str()) == 0)
         {
            translucent = true;
            blendOp = Material::LerpAlpha;
            mat->mAlphaTest = false;
         }
         else
         {  // OPAQUE
            translucent = false;
            blendOp = Material::LerpAlpha; // Make default so it doesn't get written to materials.cs
         }
      }
   }
   mat->mTranslucent = translucent;
   mat->mTranslucentBlendOp = blendOp;

   // Assign color values.
   LinearColorF diffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
   aiColor3D read_color(1.f, 1.f, 1.f);
   if (AI_SUCCESS == mAIMat->Get(AI_MATKEY_COLOR_DIFFUSE, read_color))
      diffuseColor.set(read_color.r, read_color.g, read_color.b, opacity);
   mat->mDiffuse[0] = diffuseColor;

   aiString texName;
   String torquePath;
   if (AI_SUCCESS == mAIMat->Get(AI_MATKEY_TEXTURE(aiTextureType_DIFFUSE, 0), texName))
   {
      torquePath = texName.C_Str();
      if (!torquePath.isEmpty())
         mat->mDiffuseMapFilename[0] = cleanTextureName(torquePath, cleanFile, path, false);
   }

   if (AI_SUCCESS == mAIMat->Get(AI_MATKEY_TEXTURE(aiTextureType_NORMALS, 0), texName))
   {
      torquePath = texName.C_Str();
      if (!torquePath.isEmpty())
         mat->mNormalMapFilename[0] = cleanTextureName(torquePath, cleanFile, path, false);
   }

#ifdef TORQUE_PBR_MATERIALS
   float floatVal;
   if (AI_SUCCESS == mAIMat->Get("$mat.gltf.pbrMetallicRoughness.roughnessFactor", 0, 0, floatVal))
   {  // The shape has pbr material definitions
      String aoName, rmName; // occlusion and roughness/metalness maps
      if (AI_SUCCESS == mAIMat->Get(AI_MATKEY_TEXTURE(aiTextureType_LIGHTMAP, 0), texName))
         aoName = texName.C_Str();
      if (AI_SUCCESS == mAIMat->Get(AI_MATKEY_TEXTURE(aiTextureType_UNKNOWN, 0), texName))
         rmName = texName.C_Str();

      mat->mIsSRGb[0] = true;
      if (aoName.isNotEmpty() || rmName.isNotEmpty())
      {  // If we have either map, fill all three slots
         if (rmName.isNotEmpty())
         {
            mat->mRoughMapFilename[0] = cleanTextureName(rmName, cleanFile, path, false); // Roughness
            mat->mSmoothnessChan[0] = 1.0f;
            mat->mInvertSmoothness = (floatVal == 1.0f);
            mat->mMetalMapFilename[0] = cleanTextureName(rmName, cleanFile, path, false); // Metallic
            mat->mMetalChan[0] = 2.0f;
         }
         if (aoName.isNotEmpty())
         {
            mat->mAOMapFilename[0] = cleanTextureName(aoName, cleanFile, path, false); // occlusion
            mat->mAOChan[0] = 0.0f;
         }
         else
         {
            mat->mAOMapFilename[0] = cleanTextureName(rmName, cleanFile, path, false); // occlusion
            mat->mAOChan[0] = 0.0f;
         }
      }
   }
#else
   if (AI_SUCCESS == mAIMat->Get(AI_MATKEY_TEXTURE(aiTextureType_SPECULAR, 0), texName))
   {
      torquePath = texName.C_Str();
      if (!torquePath.isEmpty())
         mat->mSpecularMapFilename[0] = cleanTextureName(torquePath, cleanFile, path, false);
   }

   LinearColorF specularColor(1.0f, 1.0f, 1.0f, 1.0f);
   if (AI_SUCCESS == mAIMat->Get(AI_MATKEY_COLOR_SPECULAR, read_color))
      specularColor.set(read_color.r, read_color.g, read_color.b, opacity);
   mat->mSpecular[0] = specularColor;

   // Specular Power
   F32 specularPower = 1.0f;
   if (AI_SUCCESS == mAIMat->Get(AI_MATKEY_SHININESS_STRENGTH, specularPower))
      mat->mSpecularPower[0] = specularPower;

   // Specular
   F32 specularStrength = 0.0f;
   if (AI_SUCCESS == mAIMat->Get(AI_MATKEY_SHININESS, specularStrength))
      mat->mSpecularStrength[0] = specularStrength;
#endif

   // Double-Sided
   bool doubleSided = false;
   S32 dbl_sided = 0;
   if (AI_SUCCESS == mAIMat->Get(AI_MATKEY_TWOSIDED, dbl_sided))
      doubleSided = (dbl_sided != 0);
   mat->mDoubleSided = doubleSided;
}

String AssimpAppMaterial::cleanTextureName(String& texName, String& shapeName, const Torque::Path& path, bool nameOnly /*= false*/)
{
   Torque::Path foundPath;
   String cleanStr;

   if (texName[0] == '*')
   {  // It's an embedded texture reference. Make the cached name and return
      cleanStr = shapeName;
      cleanStr += "_cachedTex";
      cleanStr += texName.substr(1);
      return cleanStr;
   }

   // See if the file exists
   bool fileFound = false;
   String testPath = path.getPath();
   testPath += '/';
   testPath += texName;
   testPath.replace('\\', '/');
   fileFound = Torque::FS::IsFile(testPath);

   cleanStr = texName;
   cleanStr.replace('\\', '/');
   if (fileFound)
   {
      if (cleanStr.equal(texName))
         return cleanStr;
      foundPath = testPath;
   }
   else
   {
      // See if the file is in a sub-directory of the shape
      Vector<String> foundFiles;
      Torque::Path inPath(cleanStr);
      String mainDotCsDir = Platform::getMainDotCsDir();
      mainDotCsDir += "/";
      S32 results = Torque::FS::FindByPattern(Torque::Path(mainDotCsDir + path.getPath() + "/"), inPath.getFullFileName(), true, foundFiles);
      if (results == 0 || foundFiles.size() == 0) // Not under shape directory, try the full tree
         results = Torque::FS::FindByPattern(Torque::Path(mainDotCsDir), inPath.getFullFileName(), true, foundFiles);

      if (results > 0 && foundFiles.size() > 0)
      {
         fileFound = true;
         foundPath = foundFiles[0];
      }
   }

   if (fileFound)
   {
      if (nameOnly)
         cleanStr = foundPath.getFullFileName();
      else
      {  // Unless the file is in the same directory as the materials.cs (covered above)
         // we need to set the full path from the root directory. If we use "subdirectory/file.ext",
         // the material manager won't find the image file, but it will be found the next time the
         // material is loaded from file. If we use "./subdirectory/file.ext", the image will be found
         // now, but not the next time it's loaded from file...
         S32 rootLength = dStrlen(Platform::getMainDotCsDir());
         cleanStr = foundPath.getFullPathWithoutRoot().substr(rootLength-1);
      }
   }
   else if (nameOnly)
      cleanStr += " (Not Found)";
 
   return cleanStr;
}

#ifdef TORQUE_DEBUG
void AssimpAppMaterial::enumerateMaterialProperties(aiMaterial* mtl)
{
   for (U32 i = 0; i < mtl->mNumProperties; ++i)
   {
      aiMaterialProperty* matProp = mtl->mProperties[i];
      String outText;
      if (matProp)
      {
         outText = String::ToString(" Key: %s, Index: %d, Semantic: ", matProp->mKey.C_Str(), matProp->mIndex);
         switch (matProp->mSemantic)
         {
         case aiTextureType_NONE:
            outText += "aiTextureType_NONE";
            break;
         case aiTextureType_DIFFUSE:
            outText += "aiTextureType_DIFFUSE";
            break;
         case aiTextureType_SPECULAR:
            outText += "aiTextureType_SPECULAR";
            break;
         case aiTextureType_AMBIENT:
            outText += "aiTextureType_AMBIENT";
            break;
         case aiTextureType_EMISSIVE:
            outText += "aiTextureType_EMISSIVE";
            break;
         case aiTextureType_HEIGHT:
            outText += "aiTextureType_HEIGHT";
            break;
         case aiTextureType_NORMALS:
            outText += "aiTextureType_NORMALS";
            break;
         case aiTextureType_SHININESS:
            outText += "aiTextureType_SHININESS";
            break;
         case aiTextureType_OPACITY:
            outText += "aiTextureType_OPACITY";
            break;
         case aiTextureType_DISPLACEMENT:
            outText += "aiTextureType_DISPLACEMENT";
            break;
         case aiTextureType_LIGHTMAP:
            outText += "aiTextureType_LIGHTMAP";
            break;
         case aiTextureType_REFLECTION:
            outText += "aiTextureType_REFLECTION";
            break;
         default:
            outText += "aiTextureType_UNKNOWN";
            break;
         }

         aiString stringProp;
         F32* floatProp;
         double* doubleProp;
         S32* intProp;

         switch (matProp->mType)
         {
         case aiPTI_Float:
            floatProp = (F32*)matProp->mData;
            for (U32 j = 0; j < matProp->mDataLength / sizeof(F32); ++j)
               outText += String::ToString(", %0.4f", floatProp[j]);
            break;
         case aiPTI_Double:
            doubleProp = (double*)matProp->mData;
            for (U32 j = 0; j < matProp->mDataLength / sizeof(double); ++j)
               outText += String::ToString(", %0.4lf", doubleProp[j]);
            break;
         case aiPTI_String:
            aiGetMaterialString(mtl, matProp->mKey.C_Str(), matProp->mSemantic, matProp->mIndex, &stringProp);
            outText += String::ToString(", %s", stringProp.C_Str());
            break;
         case aiPTI_Integer:
            intProp = (S32*)matProp->mData;
            for (U32 j = 0; j < matProp->mDataLength / sizeof(S32); ++j)
               outText += String::ToString(", %d", intProp[j]);
            break;
         case aiPTI_Buffer:
            outText += ", aiPTI_Buffer format data";
            break;
         default:
            outText += ", Unknown data type";
         }

         Con::printf("%s", outText.c_str());
      }
   }
}
#endif