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
#include "gfx/sim/cubemapData.h"

#include "core/stream/bitStream.h"
#include "console/consoleTypes.h"
#include "gfx/gfxCubemap.h"
#include "gfx/gfxDevice.h"
#include "gfx/gfxTextureManager.h"
#include "gfx/gfxTransformSaver.h"
#include "gfx/gfxDebugEvent.h"
#include "gfx/gfxAPI.h"
#include "scene/sceneManager.h"
#include "console/engineAPI.h"
#include "math/mathUtils.h"
#include "gfx/bitmap/cubemapSaver.h"

IMPLEMENT_CONOBJECT( CubemapData );

CubemapData::CubemapData()
{
   mCubemap = NULL;
}

CubemapData::~CubemapData()
{
   if (mCubeMapAssetRef.notNull())
   {
      mCubeMapAssetRef.assetPtr.clear();
   }

   if (mCubemap)
   {
      mCubemap.free();
   }
}

ConsoleDocClass( CubemapData, 
   "@brief Used to create static or dynamic cubemaps.\n\n"
   "This object is used with Material, WaterObject, and other objects for cubemap reflections.\n\n"
   "A simple declaration of a static cubemap:\n"
   "@tsexample\n"
   "singleton CubemapData( SkyboxCubemap )\n"
   "{\n"
   "   cubeFace[0] = \"./skybox_1\";\n"
   "   cubeFace[1] = \"./skybox_2\";\n"
   "   cubeFace[2] = \"./skybox_3\";\n"
   "   cubeFace[3] = \"./skybox_4\";\n"
   "   cubeFace[4] = \"./skybox_5\";\n"
   "   cubeFace[5] = \"./skybox_6\";\n"
   "};\n"
   "@endtsexample\n"
   "@note The dynamic cubemap functionality in CubemapData has been depreciated in favor of ReflectorDesc.\n"
   "@see ReflectorDesc\n"
   "@ingroup GFX\n" );

void CubemapData::initPersistFields()
{
   docsURL;
   ADD_FIELD("cubeMapFaceAsset", TypeImageAssetRef, Offset(mCubeMapFaceAssetRef, CubemapData))
      .elements(6)
      .doc("@brief The 6 cubemap face textures for a static cubemap.\n\n"
      "They are in the following order:\n"
      "  - cubeFace[0] is -X\n"
      "  - cubeFace[1] is +X\n"
      "  - cubeFace[2] is -Z\n"
      "  - cubeFace[3] is +Z\n"
      "  - cubeFace[4] is -Y\n"
      "  - cubeFace[5] is +Y\n");

   ADD_FIELD("cubeMapAsset", TypeImageAssetRef, Offset(mCubeMapAssetRef, CubemapData))
      .doc("@brief Cubemap dds Image Asset.\n\n");
}

bool CubemapData::onAdd()
{
   if( !Parent::onAdd() )
      return false;

   // Do NOT call this here as it forces every single cubemap defined to load its images, immediately, without mercy
   // createMap();

   return true;
}

void CubemapData::createMap()
{
   if( !mCubemap )
   {
       bool initSuccess = true;
       //check mCubeMapFile first
       if (mCubeMapAssetRef.notNull())
       {
          mCubemap = mCubeMapAssetRef.assetPtr->getTexture(&GFXCubemapStaticTextureProfile);
          return;
       }
       else
       {
          for (U32 i = 0; i < 6; i++)
          {
             if (mCubeMapFaceAssetRef[i].notNull())
             {
                if (!getCubeMapFace(i))
                {
                   Con::errorf("CubemapData::createMap - Failed to load texture '%s'", mCubeMapFaceAssetRef[i].assetPtr->getImageFile());
                   initSuccess = false;
                }
                else
                {
                   mCubeMapFaceTex[i] = getCubeMapFace(i);
                }
             }
          }
       }

       if( initSuccess )
       {
          if (mCubeMapFaceAssetRef[0].isNull())
             return;

          mCubemap.set(mCubeMapFaceTex->getWidth(), mCubeMapFaceTex->getHeight(), mCubeMapFaceTex->getFormat(), &GFXCubemapStaticTextureProfile, "CubemapData-InitTexture", mCubeMapFaceTex->getPointer()->getMipLevels());
          for (U32 i = 0; i < 6; i++)
          {
             mCubemap->updateTextureSlot(mCubeMapFaceTex[i],0, i);
          }
       }
   }
}

void CubemapData::updateFaces()
{
	bool initSuccess = true;

   //check mCubeMapFile first
   if (mCubeMapAssetRef.notNull())
   {
      mCubemap = mCubeMapAssetRef.assetPtr->getTexture(&GFXCubemapStaticTextureProfile);
      return;
   }
   else
   {
      for (U32 i = 0; i < 6; i++)
      {
         if (mCubeMapFaceAssetRef[i].notNull())
         {
            if (!getCubeMapFace(i))
            {
               Con::errorf("CubemapData::createMap - Failed to load texture '%s'", mCubeMapFaceAssetRef[i].assetPtr->getImageFile());
               initSuccess = false;
            }
            else
            {
               mCubeMapFaceTex[i] = getCubeMapFace(i);
            }
         }
      }
   }

	if( initSuccess )
	{
		mCubemap = NULL;
      if (mCubeMapFaceAssetRef[0].isNull())
         return;

      mCubemap.set(mCubeMapFaceTex->getWidth(), mCubeMapFaceTex->getHeight(), GFXFormatR16G16B16A16F, &GFXCubemapStaticTextureProfile, "CubemapData-InitTexture", mCubeMapFaceTex->getFormat());
      for (U32 i = 0; i < 6; i++)
      {
         mCubemap->updateTextureSlot(mCubeMapFaceTex[i], 0, i);
      }
	}
}

void CubemapData::setCubemapFile(FileName newCubemapFile)
{
   StringTableEntry _in = StringTable->insert(newCubemapFile.c_str());

   if (_in == StringTable->EmptyString())
   {
      mCubeMapAssetRef = StringTable->EmptyString();
      return;
   }

   if (AssetDatabase.isDeclaredAsset(_in))
   {
      mCubeMapAssetRef = _in;
   }
   else
   {
      AssetQuery query;
      S32 foundAssetcount = AssetDatabase.findAssetLooseFile(&query, _in);
      if (foundAssetcount != 0)
      {
         mCubeMapAssetRef = query.mAssetList[0];
      }
      else
      {
         mCubeMapAssetRef.assetId = _in;
         mCubeMapAssetRef.assetPtr = ImageAsset::getNamedTargetAssetPtr(_in);                                                                                                                                                                \
      }
   }
}

void CubemapData::setCubeFaceFile(U32 index, FileName newFaceFile)
{
   if (index >= 6)
      return;

   StringTableEntry _in = StringTable->insert(newFaceFile.c_str());

   if (_in == StringTable->EmptyString())
   {
      mCubeMapFaceAssetRef[index] = StringTable->EmptyString();
      return;
   }

   if (AssetDatabase.isDeclaredAsset(_in))
   {
      mCubeMapFaceAssetRef[index] = _in;
   }
   else
   {
      AssetQuery query;
      S32 foundAssetcount = AssetDatabase.findAssetLooseFile(&query, _in);
      if (foundAssetcount != 0)
      {
         mCubeMapFaceAssetRef[index] = query.mAssetList[0];
      }
      else
      {
         mCubeMapFaceAssetRef[index].assetId = _in;
         mCubeMapFaceAssetRef[index].assetPtr = ImageAsset::getNamedTargetAssetPtr(_in);                                                                                                                                                                \
      }
   }
}

void CubemapData::setCubeFaceTexture(U32 index, GFXTexHandle newFaceTexture)
{
   if (index >= 6)
      return;

   mCubeMapFaceTex[index] = newFaceTexture;
}

DefineEngineMethod( CubemapData, updateFaces, void, (),,
   "Update the assigned cubemaps faces." )
{
	object->updateFaces();
}

DefineEngineMethod( CubemapData, getFilename, const char*, (),,
   "Returns the script filename of where the CubemapData object was "
   "defined.  This is used by the material editor." )
{
   return object->getFilename();
}

DefineEngineMethod(CubemapData, save, void, (const char* filename, const GFXFormat format), ("", GFXFormatBC1),
	"Returns the script filename of where the CubemapData object was "
	"defined.  This is used by the material editor.")
{
   if (dStrEqual(filename, ""))
      filename = object->getName();

   //add dds extension if needed
   String finalName = String(filename);
   if(!finalName.endsWith(".dds") || !finalName.endsWith(".DDS"))
      finalName += String(".dds");

   CubemapSaver::save(object->mCubemap, finalName, format);
}
