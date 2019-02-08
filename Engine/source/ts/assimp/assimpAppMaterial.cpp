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

#include "platform/platform.h"
#include "ts/loader/appSequence.h"
#include "ts/assimp/assimpAppMaterial.h"
#include "ts/assimp/assimpAppMesh.h"
#include "materials/materialManager.h"
#include "ts/tsMaterialList.h"

// assimp include files. 
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/types.h>

String AppMaterial::cleanString(const String& str)
{
   String cleanStr(str);

   // Replace invalid characters with underscores
   const String badChars(" -,.+=*/");
   for (String::SizeType i = 0; i < badChars.length(); i++)
      cleanStr.replace(badChars[i], '_');

   // Prefix with an underscore if string starts with a number
   if ((cleanStr[0] >= '0') && (cleanStr[0] <= '9'))
      cleanStr.insert(0, '_');

   return cleanStr;
}

AssimpAppMaterial::AssimpAppMaterial(const char* matName)
{
   name = matName;
   diffuseColor = LinearColorF::ONE;
   specularColor = LinearColorF::ONE;
   specularPower = 0.8f;
   doubleSided = false;

   // Set some defaults
   flags |= TSMaterialList::S_Wrap;
   flags |= TSMaterialList::T_Wrap;
}

AssimpAppMaterial::AssimpAppMaterial(const struct aiMaterial* mtl)
{
   aiString matName;
   mtl->Get(AI_MATKEY_NAME, matName);
   name = matName.C_Str();
   if ( name.isEmpty() )
      name = "defaultMaterial";
   Con::printf("[ASSIMP] Loaded Material: %s", matName.C_Str());
   
   // Opacity
   F32 opacity = 0.0f;
   mtl->Get(AI_MATKEY_OPACITY, opacity);

   // Diffuse color
   aiColor3D diff_color (0.f, 0.f, 0.f);
   mtl->Get(AI_MATKEY_COLOR_DIFFUSE, diff_color);
   diffuseColor = LinearColorF(diff_color.r, diff_color.g, diff_color.b, opacity);

   // Spec Color color
   aiColor3D spec_color (0.f, 0.f, 0.f);
   mtl->Get(AI_MATKEY_COLOR_DIFFUSE, spec_color );
   specularColor = LinearColorF(spec_color.r, spec_color.g, spec_color.b, 1.0f);

   // Specular Power
   mtl->Get(AI_MATKEY_SHININESS_STRENGTH, specularPower);

   // Double-Sided
   S32 dbl_sided = 0;
   mtl->Get(AI_MATKEY_TWOSIDED, dbl_sided);
   doubleSided = (dbl_sided != 0);

   // Set some defaults
   flags |= TSMaterialList::S_Wrap;
   flags |= TSMaterialList::T_Wrap;
}

Material* AssimpAppMaterial::createMaterial(const Torque::Path& path) const
{
   // The filename and material name are used as TorqueScript identifiers, so
   // clean them up first
   String cleanFile = cleanString(TSShapeLoader::getShapePath().getFileName());
   String cleanName = cleanString(getName());

   // Prefix the material name with the filename (if not done already by TSShapeConstructor prefix)
   //if (!cleanName.startsWith(cleanFile))
   //   cleanName = cleanFile + "_" + cleanName;

   // Determine the blend operation for this material
   Material::BlendOp blendOp = (flags & TSMaterialList::Translucent) ? Material::LerpAlpha : Material::None;
   if (flags & TSMaterialList::Additive)
      blendOp = Material::Add;
   else if (flags & TSMaterialList::Subtractive)
      blendOp = Material::Sub;

   // Create the Material definition
   const String oldScriptFile = Con::getVariable("$Con::File");
   Con::setVariable("$Con::File", path.getFullPath());   // modify current script path so texture lookups are correct
   Material *newMat = MATMGR->allocateAndRegister( cleanName, getName() );
   Con::setVariable("$Con::File", oldScriptFile);        // restore script path

   newMat->mDiffuseMapFilename[0] = "";
   newMat->mNormalMapFilename[0] = "";
   newMat->mSpecularMapFilename[0] = "";

   newMat->mDiffuse[0] = diffuseColor;
   //newMat->mSpecular[0] = specularColor;
   //newMat->mSpecularPower[0] = specularPower;

   newMat->mDoubleSided = doubleSided;
   newMat->mTranslucent = (bool)(flags & TSMaterialList::Translucent);
   newMat->mTranslucentBlendOp = blendOp;

   return newMat;
}