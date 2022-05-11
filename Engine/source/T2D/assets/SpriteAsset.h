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
   static bool getAssetById(StringTableEntry assetId, AssetPtr<SpriteAsset>* shapeAsset);

protected:
   virtual void initializeAsset(void);
   virtual void onAssetRefresh(void);

   static bool setSpriteFileName(void *obj, const char *index, const char *data) { static_cast<SpriteAsset*>(obj)->setSpriteFileName(data); return false; }
   static const char* getSpriteFileName(void* obj, const char* data) { return static_cast<SpriteAsset*>(obj)->getSpriteFileName(); }

   void loadSprite();

   virtual void onTamlCustomWrite(TamlCustomNodes& customNodes);
   virtual void onTamlCustomRead(TamlCustomNodes& customNodes);

   bool getAssetByFilename(StringTableEntry fileName, AssetPtr<SpriteAsset>* spriteAsset);
};

DefineConsoleType(TypeSpriteAssetPtr, S32)
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

#endif // !_SPRITE_ASSET_H_

