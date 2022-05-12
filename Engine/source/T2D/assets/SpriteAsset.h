#ifndef _SPRITE_ASSET_H_
#define _SPRITE_ASSET_H_

#ifndef _ASSET_BASE_H_
#include "assets/assetBase.h"
#endif

#ifndef _MMATH_H_
#include "math/mMath.h"
#endif

#ifndef _MMATH_UTILS_H_
#include "math/mathUtils.h"
#endif

#ifndef _ASSET_DEFINITION_H_
#include "assets/assetDefinition.h"
#endif

#ifndef _STRINGUNIT_H_
#include "string/stringUnit.h"
#endif

#ifndef _ASSET_FIELD_TYPES_H_
#include "assets/assetFieldTypes.h"
#endif
#ifndef _ASSET_PTR_H_
#include "assets/assetPtr.h"
#endif

#include "gui/editor/guiInspectorTypes.h"
#include "gfx/bitmap/gBitmap.h"
#include "gfx/gfxTextureHandle.h"

class SpriteAsset : public AssetBase
{
   typedef AssetBase Parent;

protected:

   StringTableEntry mSpriteFileName;
   StringTableEntry mSpritePath;

   typedef Signal<void()> SpriteAssetChanged;
   SpriteAssetChanged mChangeSignal;
   
   bool mIsValidSprite;

   Map<GFXTextureProfile, GFXTexHandle> mResourceMap;

public:

   /// Frame area.
   class FrameArea
   {
   public:
      /// Frame Pixel Area.
      class PixelArea
      {
      public:
         PixelArea() {}
         PixelArea(const S32 pixelFrameOffsetX, const S32 pixelFrameOffsetY, const U32 pixelFrameWidth, const U32 pixelFrameHeight)
         {
            setArea(pixelFrameOffsetX, pixelFrameOffsetY, pixelFrameWidth, pixelFrameHeight);
         }
         PixelArea(const S32 pixelFrameOffsetX, const S32 pixelFrameOffsetY, const U32 pixelFrameWidth, const U32 pixelFrameHeight, const char* regionName)
         {
            setArea(pixelFrameOffsetX, pixelFrameOffsetY, pixelFrameWidth, pixelFrameHeight, regionName);
         }
         inline void setArea(const S32 pixelFrameOffsetX, const S32 pixelFrameOffsetY, const U32 pixelFrameWidth, const U32 pixelFrameHeight)
         {
            mPixelOffset.set(pixelFrameOffsetX, pixelFrameOffsetY);
            mPixelWidth = pixelFrameWidth;
            mPixelHeight = pixelFrameHeight;

         };
         inline void setArea(const S32 pixelFrameOffsetX, const S32 pixelFrameOffsetY, const U32 pixelFrameWidth, const U32 pixelFrameHeight, const char* regionName)
         {
            mPixelOffset.set(pixelFrameOffsetX, pixelFrameOffsetY);
            mPixelWidth = pixelFrameWidth;
            mPixelHeight = pixelFrameHeight;
            mRegionName = StringTable->insert(regionName);

         };

         Point2I mPixelOffset;
         U32 mPixelWidth;
         U32 mPixelHeight;
         StringTableEntry mRegionName;
      };


      /// Frame Texel Area.
      class TexelArea
      {
      public:
         TexelArea() {}
         TexelArea(const Point2I& pixelOffset, const U32 pixelFrameWidth, const U32 pixelFrameHeight, const F32 texelWidthScale, const F32 texelHeightScale)
         {
            setArea(pixelOffset, pixelFrameWidth, pixelFrameHeight, texelWidthScale, texelHeightScale);
         }

         void setArea(const Point2I& pixelOffset, const U32 pixelFrameWidth, const U32 pixelFrameHeight, const F32 texelWidthScale, const F32 texelHeightScale)
         {
            mTexelLower.x = pixelOffset.x * texelWidthScale;
            mTexelLower.y = pixelOffset.y * texelHeightScale;
            mTexelWidth = pixelFrameWidth * texelWidthScale;
            mTexelHeight = pixelFrameHeight * texelHeightScale;
            mTexelUpper.x = mTexelLower.x + mTexelWidth;
            mTexelUpper.y = mTexelLower.y + mTexelHeight;

         }

         void setFlip(const bool flipX, const bool flipY)
         {
            if (flipX) T3D::swap(mTexelLower.x, mTexelUpper.x);
            if (flipY) T3D::swap(mTexelLower.y, mTexelUpper.y);
         }

         Point2F mTexelLower;
         Point2F mTexelUpper;
         F32 mTexelWidth;
         F32 mTexelHeight;
      };

   public:
      FrameArea(const S32 pixelFrameOffsetX, const S32 pixelFrameOffsetY, const U32 pixelFrameWidth, const U32 pixelFrameHeight, const F32 texelWidthScale, const F32 texelHeightScale)
      {
         setArea(pixelFrameOffsetX, pixelFrameOffsetY, pixelFrameWidth, pixelFrameHeight, texelWidthScale, texelHeightScale);
      }
      FrameArea(const S32 pixelFrameOffsetX, const S32 pixelFrameOffsetY, const U32 pixelFrameWidth, const U32 pixelFrameHeight, const F32 texelWidthScale, const F32 texelHeightScale, const char* regionName)
      {
         setArea(pixelFrameOffsetX, pixelFrameOffsetY, pixelFrameWidth, pixelFrameHeight, texelWidthScale, texelHeightScale, regionName);
      }
      FrameArea()
      {
         setArea(0, 0, 0, 0, 0.0f, 0.0f);
      }

      void setArea(const S32 pixelFrameOffsetX, const S32 pixelFrameOffsetY, const U32 pixelFrameWidth, const U32 pixelFrameHeight, const F32 texelWidthScale, const F32 texelHeightScale)
      {
         mPixelArea.setArea(pixelFrameOffsetX, pixelFrameOffsetY, pixelFrameWidth, pixelFrameHeight);
         mTexelArea.setArea(mPixelArea.mPixelOffset, pixelFrameWidth, pixelFrameHeight, texelWidthScale, texelHeightScale);
      }
      void setArea(const S32 pixelFrameOffsetX, const S32 pixelFrameOffsetY, const U32 pixelFrameWidth, const U32 pixelFrameHeight, const F32 texelWidthScale, const F32 texelHeightScale, const char* regionName)
      {
         mPixelArea.setArea(pixelFrameOffsetX, pixelFrameOffsetY, pixelFrameWidth, pixelFrameHeight, regionName);
         mTexelArea.setArea(mPixelArea.mPixelOffset, pixelFrameWidth, pixelFrameHeight, texelWidthScale, texelHeightScale);
      }

      PixelArea mPixelArea;
      TexelArea mTexelArea;
   };

private:

   typedef Vector<FrameArea> typeFrameAreaVector;

   bool           mCellRowOrder;
   S32            mCellOffsetX;
   S32            mCellOffsetY;
   S32            mCellStrideX;
   S32            mCellStrideY;
   S32            mCellWidth;
   S32            mCellHeight;
   S32            mCellCountX;
   S32            mCellCountY;
   GFXTexHandle   mSprite;

   typeFrameAreaVector         mFrames;
   typeFrameAreaVector         mCustomFrames;

   inline void clampFrame(U32& frame) const { const U32 totalFrames = getFrameCount(); if (frame >= totalFrames) frame = (totalFrames == 0 ? 0 : totalFrames - 1); };
   void calculateSprite();
   void calculateImplicit();

public:

   ///--------------------------------------------
   /// Very simple image asset for 2d Sprites
   /// TODO: Add custom defined frames
   /// and allow them to be named.
   /// TODO: add ability for multiple cell areas.
   ///--------------------------------------------

   SpriteAsset();
   virtual ~SpriteAsset();

   /// Engine.
   static void initPersistFields();
   virtual void copyTo(SimObject* object);

   /// Declare Console Object.
   DECLARE_CONOBJECT(SpriteAsset);

   /// getters and setters
   GFXTexHandle            getSprite() { return mSprite; }
   void                    setSpriteFileName(const char* pScriptFile);
   const char*             getSpriteInfo();
   inline StringTableEntry getSpriteFileName(void) const { return mSpriteFileName; };
   inline S32              getSpriteWidth(void) const { return mSprite.getWidth(); }
   inline S32              getSpriteHeight(void) const { return mSprite.getHeight(); }
   inline U32              getFrameCount(void) const { return (U32)mFrames.size(); };

   void                    addCustomFrame(const S32 cellOffX, const S32 cellOffY,
                                          const S32 cellWidth, const S32 cellHeight,
                                          const char* regionName);

   void                    setCellRowOrder(const bool cellRowOrder);
   inline bool             getCellRowOrder(void) const { return mCellRowOrder; }

   void                    setCellOffsetX(const S32 cellOffsetX);
   inline S32              getCellOffsetX(void) const { return mCellOffsetX; }

   void                    setCellOffsetY(const S32 cellOffsetY);
   inline S32              getCellOffsetY(void) const { return mCellOffsetY; }

   void                    setCellStrideX(const S32 cellStrideX);
   inline S32              getCellStrideX(void) const { return mCellStrideX; }

   void                    setCellStrideY(const S32 cellStrideY);
   inline S32              getCellStrideY(void) const { return mCellStrideY; }

   void                    setCellCountX(const S32 cellCountX);
   inline S32              getCellCountX(void) const { return mCellCountX; }

   void                    setCellCountY(const S32 cellCountY);
   inline S32              getCellCountY(void) const { return mCellCountY; }

   void                    setCellWidth(const S32 cellWidth);
   inline S32              getCellWidth(void) const { return mCellWidth; }

   void                    setCellHeight(const S32 cellheight);
   inline S32              getCellHeight(void) const { return mCellHeight; }

   inline const FrameArea& getSpriteFrameArea(U32 frame) const { clampFrame(frame); return mFrames[frame]; };

   bool isValid() { return mIsValidSprite; }

   /// Public asset accessor
   static U32 getAssetByFilename(StringTableEntry fileName, AssetPtr<SpriteAsset>* shapeAsset);
   static StringTableEntry getAssetIdByFilename(StringTableEntry fileName);
   static U32 getAssetById(StringTableEntry assetId, AssetPtr<SpriteAsset>* shapeAsset);
   static U32 getAssetById(String assetId, AssetPtr<SpriteAsset>* spriteAsset) { return getAssetById(assetId.c_str(), spriteAsset); };
   SpriteAssetChanged& getChangedSignal() { return mChangeSignal; }
   inline StringTableEntry getSpritePath(void) const { return mSpritePath; };

protected:
   virtual void initializeAsset(void);
   void _onResourceChanged(const Torque::Path& path);
   virtual void onAssetRefresh(void);

   static bool setSpriteFileName(void *obj, const char *index, const char *data) { static_cast<SpriteAsset*>(obj)->setSpriteFileName(data); return false; }
   static StringTableEntry getSpriteFileName(void* obj, StringTableEntry data) { return static_cast<SpriteAsset*>(obj)->getSpriteFileName(); }

   void loadSprite();

   virtual void onTamlCustomWrite(TamlCustomNodes& customNodes);
   virtual void onTamlCustomRead(TamlCustomNodes& customNodes);
};

DefineConsoleType(TypeSpriteAssetPtr, SpriteAsset)
DefineConsoleType(TypeSpriteAssetId, String)

class GuiInspectorTypeSpriteAssetPtr : public GuiInspectorTypeFileName
{
   typedef GuiInspectorTypeFileName Parent;

public:

   GuiBitmapButtonCtrl *mSpriteEdButton;
   DECLARE_CONOBJECT(GuiInspectorTypeSpriteAssetPtr);
   static void consoleInit();

   virtual GuiControl* constructEditControl();
   virtual bool updateRects();

};

class GuiInspectorTypeSpriteAssetId : public GuiInspectorTypeSpriteAssetPtr
{
   typedef GuiInspectorTypeSpriteAssetPtr Parent;
public:
   DECLARE_CONOBJECT(GuiInspectorTypeSpriteAssetId);
   static void consoleInit();
};

#pragma region Singular Asset Macros

#define DECLARE_SPRITEASSET(className, name, changeFunc, profile) public: \
   GFXTexHandle m##name = NULL;\
   StringTableEntry m##name##Name; \
   StringTableEntry m##name##AssetId;\
   AssetPtr<SpriteAsset>  m##name##Asset;\
   GFXTextureProfile* m##name##Profile = &profile;\
public: \
   const StringTableEntry get##name##File() const { return m##name##Name; }\
   void set##name##File(const FileName &_in) { m##name##Name = StringTable->insert(_in.c_str());}\
   const AssetPtr<SpriteAsset> & get##name##Asset() const { return m##name##Asset; }\
   void set##name##Asset(const AssetPtr<SpriteAsset> &_in) { m##name##Asset = _in;}\
   \
   bool _set##name(StringTableEntry _in)\
   {\
      if(m##name##AssetId != _in || m##name##Name != _in)\
      {\
         if (m##name##Asset.notNull())\
         {\
            m##name##Asset->getChangedSignal().remove(this, &className::changeFunc);\
         }\
         if (_in == NULL || _in == StringTable->EmptyString())\
         {\
            m##name##Name = StringTable->EmptyString();\
            m##name##AssetId = StringTable->EmptyString();\
            m##name##Asset = NULL;\
            m##name.free();\
            m##name = NULL;\
            return true;\
         }\
         else if(_in[0] == '$' || _in[0] == '#')\
         {\
            m##name##Name = _in;\
            m##name##AssetId = StringTable->EmptyString();\
            m##name##Asset = NULL;\
            m##name.free();\
            m##name = NULL;\
            return true;\
         }\
         \
         if (AssetDatabase.isDeclaredAsset(_in))\
         {\
            m##name##AssetId = _in;\
            \
            U32 assetState = SpriteAsset::getAssetById(m##name##AssetId, &m##name##Asset);\
            \
            if (SpriteAsset::Ok == assetState)\
            {\
               m##name##Name = StringTable->EmptyString();\
            }\
         }\
         else\
         {\
            StringTableEntry assetId = SpriteAsset::getAssetIdByFilename(_in);\
            if (assetId != StringTable->EmptyString())\
            {\
               m##name##AssetId = assetId;\
               if (SpriteAsset::getAssetById(m##name##AssetId, &m##name##Asset) == SpriteAsset::Ok)\
               {\
                  m##name##Name = StringTable->EmptyString();\
               }\
            }\
            else\
            {\
               m##name##Name = _in;\
               m##name##AssetId = StringTable->EmptyString();\
               m##name##Asset = NULL;\
            }\
         }\
      }\
      if (get##name() != StringTable->EmptyString() && m##name##Name != StringTable->insert("texhandle"))\
      {\
         if (m##name##Asset.notNull())\
         {\
            m##name##Asset->getChangedSignal().notify(this, &className::changeFunc);\
         }\
         \
         m##name.set(get##name(), m##name##Profile, avar("%s() - mTextureObject (line %d)", __FUNCTION__, __LINE__));\
      }\
      else\
      {\
         m##name.free();\
         m##name = NULL;\
      }\
      \
      if(get##name() == StringTable->EmptyString())\
         return true;\
      \
      if (m##name##Asset.notNull() && m##name##Asset->getStatus() != SpriteAsset::Ok)\
      {\
         Con::errorf("%s(%s)::_set%s() - sprite asset failure\"%s\" due to [%s]", macroText(className), getName(), macroText(name), _in, SpriteAsset::getAssetErrstrn(m##name##Asset->getStatus()).c_str());\
         return false; \
      }\
      else if (!m##name)\
      {\
         Con::errorf("%s(%s)::_set%s() - Couldn't load image \"%s\"", macroText(className), getName(), macroText(name), _in);\
         return false;\
      }\
      return true;\
   }\
   \
   const StringTableEntry get##name() const\
   {\
      if (m##name##Asset && (m##name##Asset->getSpriteFileName() != StringTable->EmptyString()))\
         return  Platform::makeRelativePathName(m##name##Asset->getSpritePath(), Platform::getMainDotCsDir());\
      else if (m##name##AssetId != StringTable->EmptyString())\
         return m##name##AssetId;\
      else if (m##name##Name != StringTable->EmptyString())\
         return StringTable->insert(Platform::makeRelativePathName(m##name##Name, Platform::getMainDotCsDir()));\
      else\
         return StringTable->EmptyString();\
   }\
   GFXTexHandle get##name##Resource() \
   {\
      return m##name;\
   }\
   bool name##Valid() {return (get##name() != StringTable->EmptyString() && m##name##Asset->getStatus() == AssetBase::Ok); }

#define INITPERSISTFIELD_SPRITEASSET(name, consoleClass, docs) \
   addProtectedField(#name, TypeImageFilename, Offset(m##name##Name, consoleClass), _set##name##Data, &defaultProtectedGetFn, assetDoc(name, docs), AbstractClassRep::FIELD_HideInInspectors); \
   addProtectedField(assetText(name, Asset), TypeSpriteAssetId, Offset(m##name##AssetId, consoleClass), _set##name##Data, &defaultProtectedGetFn, assetDoc(name, asset docs.));

#define LOAD_SPRITEASSET(name)\
if (m##name##AssetId != StringTable->EmptyString())\
{\
   S32 assetState = SpriteAsset::getAssetById(m##name##AssetId, &m##name##Asset);\
   if (assetState == SpriteAsset::Ok )\
   {\
      m##name##Name = StringTable->EmptyString();\
   }\
   else Con::warnf("Warning: %s::LOAD_SPRITEASSET(%s)-%s", mClassName, m##name##AssetId, SpriteAsset::getAssetErrstrn(assetState).c_str());\
}


#pragma endregion

#endif // !_SPRITE_ASSET_H_

