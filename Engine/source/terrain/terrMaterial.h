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

#ifndef _TERRMATERIAL_H_
#define _TERRMATERIAL_H_

#ifndef _SIMBASE_H_
#include "console/simBase.h"
#endif

#include "T3D/assets/ImageAsset.h"

/// The TerrainMaterial class orginizes the material settings 
/// for a single terrain material layer.
class TerrainMaterial : public SimObject
{
   typedef SimObject Parent;

protected:

   ///
  //FileName mDiffuseMap;

   //AssetPtr<ImageAsset> mDiffuseAsset;

   //DECLARE_IMAGEASSET(TerrainMaterial, DiffuseMap, GFXStaticTextureSRGBProfile);
public: \
   GFXTexHandle mDiffuseMap = NULL; \
   FileName mDiffuseMapFilename = String::EmptyString; \
   StringTableEntry mDiffuseMapAssetId = StringTable->EmptyString();\
   AssetPtr<ImageAsset>  mDiffuseMapAsset = NULL;\
   GFXTextureProfile* mDiffuseMapProfile = &GFXStaticTextureSRGBProfile;\
public: \
   const StringTableEntry getDiffuseMapFile() const { return StringTable->insert(mDiffuseMapFilename.c_str()); }\
   void setDiffuseMapFile(const FileName &_in) { mDiffuseMapFilename = _in;}\
   const AssetPtr<ImageAsset> & getDiffuseMapAsset() const { return mDiffuseMapAsset; }\
   void setDiffuseMapAsset(const AssetPtr<ImageAsset> &_in) { mDiffuseMapAsset = _in;}\
   \
   bool _setDiffuseMap(StringTableEntry _in)\
   {\
      if (_in == StringTable->EmptyString())\
      {\
         mDiffuseMapFilename = String::EmptyString;\
         mDiffuseMapAssetId = StringTable->EmptyString();\
         mDiffuseMapAsset = NULL;\
         mDiffuseMap.free();\
         mDiffuseMap = NULL;\
         return true;\
      }\
      \
      if (AssetDatabase.isDeclaredAsset(_in))\
      {\
         mDiffuseMapAssetId = _in;\
         \
         U32 assetState = ImageAsset::getAssetById(mDiffuseMapAssetId, &mDiffuseMapAsset);\
         \
         if (ImageAsset::Ok == assetState)\
         {\
            mDiffuseMapFilename = String::EmptyString;\
         }\
         else\
         {\
            mDiffuseMapFilename = _in;\
            mDiffuseMapAsset = NULL;\
         }\
      }\
      else\
      {\
         Torque::Path imagePath = _in;\
         if (imagePath.getExtension() == String::EmptyString)\
         {\
            if (Platform::isFile(imagePath.getFullPath() + ".png"))\
               imagePath.setExtension("png");\
            else if (Platform::isFile(imagePath.getFullPath() + ".dds"))\
               imagePath.setExtension("dds");\
            else if (Platform::isFile(imagePath.getFullPath() + ".jpg"))\
               imagePath.setExtension("jpg");\
         }\
         if (ImageAsset::getAssetByFilename(imagePath.getFullPath(), &mDiffuseMapAsset))\
         {\
            mDiffuseMapAssetId = mDiffuseMapAsset.getAssetId();\
            \
            if (ImageAsset::Ok == mDiffuseMapAsset->getStatus())\
            {\
               mDiffuseMapFilename = String::EmptyString;\
            }\
         }\
         else\
         {\
            mDiffuseMapFilename = _in;\
            mDiffuseMapAssetId = StringTable->EmptyString();\
            mDiffuseMapAsset = NULL;\
         }\
      }\
      if (getDiffuseMap() != StringTable->EmptyString() && !mDiffuseMapFilename.equal("texhandle", String::NoCase))\
      {\
         mDiffuseMap.set(getDiffuseMap(), mDiffuseMapProfile, avar("%s() - mTextureObject (line %d)", __FUNCTION__, __LINE__));\
         return true;\
      }\
      return false;\
   }\
   \
   const StringTableEntry getDiffuseMap() const\
   {\
      if (mDiffuseMapAsset && (mDiffuseMapAsset->getImageFileName() != StringTable->EmptyString()))\
         return  Platform::makeRelativePathName(mDiffuseMapAsset->getImagePath(), Platform::getMainDotCsDir());\
      else if (mDiffuseMapFilename.isNotEmpty())\
         return StringTable->insert(Platform::makeRelativePathName(mDiffuseMapFilename.c_str(), Platform::getMainDotCsDir()));\
      else\
         return StringTable->EmptyString();\
   }\
   GFXTexHandle getDiffuseMapResource() \
   {\
      return mDiffuseMap;\
   }

   DECLARE_IMAGEASSET_SETGET(TerrainMaterial, DiffuseMap);

   /// The size of the diffuse base map in meters 
   /// used to generate its texture coordinates.
   F32 mDiffuseSize;

   ///
   DECLARE_IMAGEASSET(TerrainMaterial, NormalMap, GFXNormalMapProfile);
   DECLARE_IMAGEASSET_SETGET(TerrainMaterial, NormalMap);

   ///
   DECLARE_IMAGEASSET(TerrainMaterial, DetailMap, GFXStaticTextureProfile);
   DECLARE_IMAGEASSET_SETGET(TerrainMaterial, DetailMap);
   
   /// The size of the detail map in meters used
   /// to generate the texture coordinates for the
   /// detail and normal maps.
   F32 mDetailSize;

   /// 
   F32 mDetailStrength;

   /// 
   F32 mDetailDistance;

   ///
   DECLARE_IMAGEASSET(TerrainMaterial, ORMConfigMap, GFXStaticTextureProfile);
   DECLARE_IMAGEASSET_SETGET(TerrainMaterial, ORMConfigMap);

   bool mIsSRGB;
   bool mInvertRoughness;

   /// Normally the detail is projected on to the xy 
   /// coordinates of the terrain.  If this flag is true
   /// then this detail is projected along the xz and yz
   /// planes.
   bool mSideProjection;

   DECLARE_IMAGEASSET(TerrainMaterial, MacroMap, GFXStaticTextureProfile);
   DECLARE_IMAGEASSET_SETGET(TerrainMaterial, MacroMap);
   F32 mMacroSize;
   F32 mMacroStrength;
   F32 mMacroDistance;

   ///
   F32 mParallaxScale;

   /// Depth for blending the textures using the new
   /// blending method. Higher numbers = larger blend
   /// radius.
   F32 mBlendDepth;

   F32 mBlendContrast;

public:

   TerrainMaterial();
   virtual ~TerrainMaterial();

   bool onAdd();
   static void initPersistFields();

   DECLARE_CONOBJECT( TerrainMaterial );

   /// This method locates the TerrainMaterial if it exists, tries 
   /// to create a new one if a valid texture path was passed, or
   /// returns a debug material if all else fails.
   static TerrainMaterial* findOrCreate( const char *nameOrPath );

   /// Returns the default warning terrain material used when
   /// a material is not found or defined.
   static TerrainMaterial* getWarningMaterial();

   F32 getDiffuseSize() const { return mDiffuseSize; }

   F32 getDetailSize() const { return mDetailSize; }

   F32 getDetailStrength() const { return mDetailStrength; }

   F32 getDetailDistance() const { return mDetailDistance; }

   F32 getMacroSize() const { return mMacroSize; }

   F32 getMacroDistance() const { return mMacroDistance; }

   F32 getMacroStrength() const { return mMacroStrength; }

   bool useSideProjection() const { return mSideProjection; }

   F32 getParallaxScale() const { return mParallaxScale; }

   F32 getBlendDepth() const { return mBlendDepth; }

   F32 getBlendContrast() const { return mBlendContrast; }

   bool getIsSRGB() const { return mIsSRGB; }

   bool getInvertRoughness() const { return mInvertRoughness; }

};

#endif // _TERRMATERIAL_H_
