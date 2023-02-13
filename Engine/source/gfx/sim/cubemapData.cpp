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

   for (U32 i = 0; i < 6; i++)
   {
      INIT_IMAGEASSET_ARRAY(CubeMapFace, GFXStaticTextureSRGBProfile, i);
   }

   INIT_ASSET(CubeMap);
}

CubemapData::~CubemapData()
{
   mCubemap = NULL;
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
   addProtectedField( "cubeFace", TypeStringFilename, Offset(mCubeMapFaceName, CubemapData), _setCubeMapFaceData, defaultProtectedGetFn, 6,
      "@brief The 6 cubemap face textures for a static cubemap.\n\n"
      "They are in the following order:\n"
      "  - cubeFace[0] is -X\n"
      "  - cubeFace[1] is +X\n"
      "  - cubeFace[2] is -Z\n"
      "  - cubeFace[3] is +Z\n"
      "  - cubeFace[4] is -Y\n"
      "  - cubeFace[5] is +Y\n", AbstractClassRep::FIELD_HideInInspectors );

   INITPERSISTFIELD_IMAGEASSET_ARRAY(CubeMapFace, 6, CubemapData, "@brief The 6 cubemap face textures for a static cubemap.\n\n"
      "They are in the following order:\n"
      "  - cubeFace[0] is -X\n"
      "  - cubeFace[1] is +X\n"
      "  - cubeFace[2] is -Z\n"
      "  - cubeFace[3] is +Z\n"
      "  - cubeFace[4] is -Y\n"
      "  - cubeFace[5] is +Y\n");

   INITPERSISTFIELD_IMAGEASSET(CubeMap, CubemapData, "@brief Cubemap dds Image Asset.\n\n");
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
       if (getCubeMap() != StringTable->EmptyString())
       {
          mCubemap = TEXMGR->createCubemap(getCubeMap());
          return;
       }
       else
       {
          for (U32 i = 0; i < 6; i++)
          {
             if (!_setCubeMapFace(getCubeMapFace(i), i))
             {
                Con::errorf("CubemapData::createMap - Failed to load texture '%s'", getCubeMapFace(i));
                initSuccess = false;
             }
          }
       }

       if( initSuccess )
       {
           mCubemap = GFX->createCubemap();
           if (!mCubeMapFace || mCubeMapFace->isNull())
              return;
           mCubemap->initStatic(mCubeMapFace);
       }
   }
}

void CubemapData::updateFaces()
{
	bool initSuccess = true;

	for( U32 i=0; i<6; i++ )
   {
      //check mCubeMapFile first
      if (getCubeMap() != StringTable->EmptyString())
      {
         mCubemap = TEXMGR->createCubemap(getCubeMap());
         return;
      }
      else
      {
         if (!_setCubeMapFace(getCubeMapFace(i), i))
         {
            Con::errorf("CubemapData::createMap - Failed to load texture '%s'", getCubeMapFace(i));
            initSuccess = false;
         }
      }
   }

	if( initSuccess )
	{
		mCubemap = NULL;
		mCubemap = GFX->createCubemap();

		mCubemap->initStatic( mCubeMapFace );
	}
}

void CubemapData::setCubemapFile(FileName newCubemapFile)
{
   mCubeMapName = newCubemapFile;
}

void CubemapData::setCubeFaceFile(U32 index, FileName newFaceFile)
{
   if (index >= 6)
      return;

   mCubeMapFaceName[index] = newFaceFile;
}

void CubemapData::setCubeFaceTexture(U32 index, GFXTexHandle newFaceTexture)
{
   if (index >= 6)
      return;

   mCubeMapFace[index] = newFaceTexture;
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
