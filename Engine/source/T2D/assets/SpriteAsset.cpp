#include "T2D/assets/SpriteAsset.h"

#ifndef _ASSET_MANAGER_H_
#include "assets/assetManager.h"
#endif

#ifndef _CONSOLETYPES_H_
#include "console/consoleTypes.h"
#endif

#ifndef _MMATH_H_
#include "math/mMath.h"
#endif

#ifndef _TAML_
#include "persistence/taml/taml.h"
#endif

#ifndef _ASSET_PTR_H_
#include "assets/assetPtr.h"
#endif

#include "gfx/gfxStringEnumTranslate.h"

// Debug Profiling.
#include "platform/profiler.h"

//-----------------------------------------------------------------------------
static StringTableEntry customCellsNode   = StringTable->insert("CustomCells");
static StringTableEntry cellNodeName      = StringTable->insert("Cell");
static StringTableEntry cellRegionName    = StringTable->insert("RegionName");
static StringTableEntry cellOffsetName    = StringTable->insert("Offset");
static StringTableEntry cellOffsetXName   = StringTable->insert("OffsetX");
static StringTableEntry cellOffsetYName   = StringTable->insert("OffsetY");
static StringTableEntry cellWidthName     = StringTable->insert("Width");
static StringTableEntry cellHeightName    = StringTable->insert("Height");
static StringTableEntry cellNameEntryName = StringTable->insert("Name");
//-----------------------------------------------------------------------------

ConsoleType(assetIdString, TypeSpriteAssetPtr, String, ASSET_ID_FIELD_PREFIX)

ConsoleGetType(TypeSpriteAssetPtr)
{
   // Fetch asset Id.
   return *((StringTableEntry*)dptr);
}

ConsoleSetType(TypeSpriteAssetPtr)
{
   // Was a single argument specified?
   if (argc == 1)
   {
      // Yes, so fetch field value.
      const char* pFieldValue = argv[0];

      // Fetch asset Id.
      StringTableEntry* assetId = (StringTableEntry*)(dptr);

      // Update asset value.
      *assetId = StringTable->insert(pFieldValue);

      return;
   }

   // Warn.
   Con::warnf("(TypeSpriteAssetPtr) - Cannot set multiple args to a single asset.");
}

ConsoleType(assetIdString, TypeSpriteAssetId, String, ASSET_ID_FIELD_PREFIX)

ConsoleGetType(TypeSpriteAssetId)
{
   // Fetch asset Id.
   return *((const char**)(dptr));
}

ConsoleSetType(TypeSpriteAssetId)
{
   // Was a single argument specified?
   if (argc == 1)
   {
      // Yes, so fetch field value.
      const char* pFieldValue = argv[0];

      // Fetch asset Id.
      StringTableEntry* assetId = (StringTableEntry*)(dptr);

      // Update asset value.
      *assetId = StringTable->insert(pFieldValue);

      return;
   }

   // Warn.
   Con::warnf("(TypeSpriteAssetId) - Cannot set multiple args to a single asset.");
}

//-----------------------------------------------------------------------------

SpriteAsset::SpriteAsset() :
      AssetBase(),
      mSprite(nullptr),
      mCellRowOrder(true),
      mCellOffsetX(0),
      mCellOffsetY(0),
      mCellStrideX(0),
      mCellStrideY(0),
      mCellCountX(0),
      mCellCountY(0),
      mCellWidth(0),
      mCellHeight(0),
      mIsValidSprite(false)

{
   // Set Vector Associations.
   VECTOR_SET_ASSOCIATION(mFrames);
   VECTOR_SET_ASSOCIATION(mCustomFrames);
   mSpriteFileName = StringTable->EmptyString();
   mSpritePath = StringTable->EmptyString();
}

SpriteAsset::~SpriteAsset()
{
}

void SpriteAsset::initPersistFields()
{
   // Parent
   Parent::initPersistFields();

   addProtectedField("spriteFile", TypeAssetLooseFilePath, Offset(mSpriteFileName, SpriteAsset), &setSpriteFileName, &getSpriteFileName,
      "Path to the sprite.");

   addField("cellRowOrder",   TypeBool, Offset(mCellRowOrder, SpriteAsset), "");
   addField("cellOffsetX",    TypeS32, Offset(mCellOffsetX, SpriteAsset), "");
   addField("cellOffsetY",    TypeS32, Offset(mCellOffsetY, SpriteAsset), "");
   addField("cellStrideX",    TypeS32, Offset(mCellStrideX, SpriteAsset), "");
   addField("cellStrideY",    TypeS32, Offset(mCellStrideY, SpriteAsset), "");
   addField("cellCountX",     TypeS32, Offset(mCellCountX, SpriteAsset), "");
   addField("cellCountY",     TypeS32, Offset(mCellCountY, SpriteAsset), "");
   addField("cellWidth",      TypeS32, Offset(mCellWidth, SpriteAsset), "");
   addField("cellHeight",     TypeS32, Offset(mCellHeight, SpriteAsset), "");

}

void SpriteAsset::copyTo(SimObject* object)
{
   Parent::copyTo(object);
}

void SpriteAsset::loadSprite()
{
   if (mSpritePath)
   {
      if (!Torque::FS::IsFile(mSpritePath))
      {
         Con::errorf("SpriteAsset::initializeAsset: Attempted to load file %s but it was not valid!", mSpriteFileName);
         mLoadedState = BadFileReference;
         return;
      }

      mLoadedState = Ok;
      mIsValidSprite = true;
      mChangeSignal.trigger();
      return;
   }
   mLoadedState = BadFileReference;

   mIsValidSprite = false;

}

U32 SpriteAsset::getAssetByFilename(StringTableEntry fileName, AssetPtr<SpriteAsset>* spriteAsset)
{
   AssetQuery query;
   S32 foundAssetcount = AssetDatabase.findAssetLooseFile(&query, fileName);
   if (foundAssetcount == 0)
   {

      if (spriteAsset->isNull())
      {
         //Well that's bad, loading the fallback failed.
         Con::warnf("ImageAsset::getAssetByFilename - Finding of asset associated with file %s failed with no fallback asset", fileName);
         return AssetErrCode::Failed;
      }

      //handle noshape not being loaded itself
      if ((*spriteAsset)->mLoadedState == BadFileReference)
      {
         Con::warnf("ImageAsset::getAssetByFilename - Finding of associated with file %s failed, and fallback asset reported error of Bad File Reference.", fileName);
         return AssetErrCode::BadFileReference;
      }

      Con::warnf("ImageAsset::getAssetByFilename - Finding of associated with file %s failed, utilizing fallback asset", fileName);

      (*spriteAsset)->mLoadedState = AssetErrCode::UsingFallback;
      return AssetErrCode::UsingFallback;
   }
   else
   {
      //acquire and bind the asset, and return it out
      spriteAsset->setAssetId(query.mAssetList[0]);
      return (*spriteAsset)->mLoadedState;
   }
}

StringTableEntry SpriteAsset::getAssetIdByFilename(StringTableEntry fileName)
{
   if (fileName == StringTable->EmptyString())
      return StringTable->EmptyString();

   StringTableEntry spriteAssetId = StringTable->EmptyString();

   AssetQuery query;
   S32 foundAssetcount = AssetDatabase.findAssetLooseFile(&query, fileName);
   if (foundAssetcount != 0)
   {
      //acquire and bind the asset, and return it out
      spriteAssetId = query.mAssetList[0];
   }
   else
   {
      AssetPtr<SpriteAsset> spriteAsset = spriteAssetId;
      spriteAsset->mLoadedState = AssetErrCode::BadFileReference;
   }

   return spriteAssetId;
}

U32 SpriteAsset::getAssetById(StringTableEntry assetId, AssetPtr<SpriteAsset>* spriteAsset)
{
   (*spriteAsset) = assetId;

   if (spriteAsset->notNull())
   {
      return (*spriteAsset)->mLoadedState;
   }
   else
   {
      if (spriteAsset->isNull())
      {
         //Well that's bad, loading the fallback failed.
         Con::warnf("SpriteAsset::getAssetById - Finding of asset with id %s failed with no fallback asset", assetId);
         return AssetErrCode::Failed;
      }

      //handle noshape not being loaded itself
      if ((*spriteAsset)->mLoadedState == BadFileReference)
      {
         Con::warnf("SpriteAsset::getAssetById - Finding of asset with id %s failed, and fallback asset reported error of Bad File Reference.", assetId);
         return AssetErrCode::BadFileReference;
      }

      Con::warnf("SpriteAsset::getAssetById - Finding of asset with id %s failed, utilizing fallback asset", assetId);

      (*spriteAsset)->mLoadedState = AssetErrCode::UsingFallback;
      return AssetErrCode::UsingFallback;
   }
}

void SpriteAsset::initializeAsset()
{
   ResourceManager::get().getChangedSignal().notify(this, &SpriteAsset::_onResourceChanged);

   mSpritePath = getOwned() ? expandAssetFilePath(mSpriteFileName) : mSpritePath;

   loadSprite();

   calculateSprite();

}

void SpriteAsset::_onResourceChanged(const Torque::Path& path)
{
   if (path != Torque::Path(mSpritePath))
      return;

   refreshAsset();
}

void SpriteAsset::onAssetRefresh()
{
   mSpritePath = getOwned() ? expandAssetFilePath(mSpriteFileName) : mSpritePath;
   loadSprite();
   calculateSprite();

}

void SpriteAsset::setSpriteFileName(const char* pScriptFile)
{
   AssertFatal(pScriptFile != NULL, "Cannot use a null sprite file.");

   mSpriteFileName = StringTable->insert(pScriptFile);

   refreshAsset();

}

void SpriteAsset::addCustomFrame(const S32 cellOffX, const S32 cellOffY, const S32 cellWidth, const S32 cellHeight, const char* regionName)
{
   /// calculate texel scale.
   const F32 texWScale = 1.0f / (F32)mSprite->getWidth();
   const F32 texHScale = 1.0f / (F32)mSprite->getHeight();

   /// original bitmap dimension
   const U32 spriteWidth = mSprite->getBitmapWidth();
   const U32 spriteHeight = mSprite->getBitmapHeight();

   FrameArea frameArea(0, 0, spriteWidth, spriteHeight, texWScale, texHScale);

   if (regionName == NULL)
   {
      Con::warnf("SpriteAsset::addCustomFrame() - Cell name of '%s' is invalid or was not set.", regionName);

      U32 currentIndex = mCustomFrames.size();
      Con::warnf("- Setting to the next index in the frame list: '%i'", currentIndex);

      dSscanf(regionName, "%i", currentIndex);
   }

   if (cellOffX < 0 || cellOffY < 0 || cellOffX > spriteWidth || cellOffY > spriteHeight)
   {
      Con::warnf("SpriteAsset::addCustomFrame() - Cell offset of '(%d,%d)' is invalid or was not set.", cellOffX, cellOffY);
   }

   if (cellWidth <= 0 || cellWidth > spriteWidth)
   {
      Con::warnf("SpriteAsset::addCustomFrame() - Cell width of '%d' is invalid or was not set.", cellWidth);
   }

   if (cellHeight <= 0 || cellHeight > spriteHeight)
   {
      Con::warnf("SpriteAsset::addCustomFrame() - Cell height of '%d' is invalid or was not set.", cellHeight);
   }

   frameArea.setArea(cellOffX, cellOffY, cellWidth, cellHeight, texWScale, texHScale, regionName);
   mCustomFrames.push_back(frameArea);

}

void SpriteAsset::setCellRowOrder(const bool cellRowOrder)
{
   // Ignore no change.
   if (cellRowOrder == mCellRowOrder)
      return;

   // Update.
   mCellRowOrder = cellRowOrder;

   // Refresh the asset.
   refreshAsset();
}

void SpriteAsset::setCellOffsetX(const S32 cellOffsetX)
{
   // Ignore no change.
   if (cellOffsetX == mCellOffsetX)
      return;

   // Valid?
   if (cellOffsetX < 0)
   {
      // No, so warn.
      Con::warnf("Invalid CELL offset X '%d'.", cellOffsetX);
      return;
   }

   // Update.
   mCellOffsetX = cellOffsetX;

   // Refresh the asset.
   refreshAsset();
}

void SpriteAsset::setCellOffsetY(const S32 cellOffsetY)
{
   // Ignore no change.
   if (cellOffsetY == mCellOffsetY)
      return;

   // Valid?
   if (cellOffsetY < 0)
   {
      // No, so warn.
      Con::warnf("Invalid CELL offset Y '%d'.", cellOffsetY);
      return;
   }

   // Update.
   mCellOffsetY = cellOffsetY;

   // Refresh the asset.
   refreshAsset();
}


void SpriteAsset::setCellStrideX(const S32 cellStrideX)
{
   // Ignore no change.
   if (cellStrideX == mCellStrideX)
      return;

   // Valid?
   if (cellStrideX < 0)
   {
      // No, so warn.
      Con::warnf("Invalid CELL stride X '%d'.", cellStrideX);
      return;
   }

   // Update.
   mCellStrideX = cellStrideX;

   // Refresh the asset.
   refreshAsset();
}

void SpriteAsset::setCellStrideY(const S32 cellStrideY)
{
   // Ignore no change.
   if (cellStrideY == mCellStrideY)
      return;

   // Valid?
   if (cellStrideY < 0)
   {
      // No, so warn.
      Con::warnf("Invalid CELL stride Y '%d'.", cellStrideY);
      return;
   }

   // Update.
   mCellStrideY = cellStrideY;

   // Refresh the asset.
   refreshAsset();
}

void SpriteAsset::setCellCountX(const S32 cellCountX)
{
   // Ignore no change.
   if (cellCountX == mCellCountX)
      return;

   // Valid?
   if (cellCountX < 0)
   {
      // No, so warn.
      Con::warnf("Invalid CELL count X '%d'.", cellCountX);
      return;
   }

   // Update.
   mCellCountX = cellCountX;

   // Refresh the asset.
   refreshAsset();
}

void SpriteAsset::setCellCountY(const S32 cellCountY)
{
   // Ignore no change.
   if (cellCountY == mCellCountY)
      return;

   // Valid?
   if (cellCountY < 0)
   {
      // No, so warn.
      Con::warnf("Invalid CELL count Y '%d'.", cellCountY);
      return;
   }

   // Update.
   mCellCountY = cellCountY;

   // Refresh the asset.
   refreshAsset();
}

void SpriteAsset::setCellWidth(const S32 cellWidth)
{
   // Ignore no change.
   if (cellWidth == mCellWidth)
      return;

   // Valid?
   if (cellWidth < 0)
   {
      // No, so warn.
      Con::warnf("Invalid cell width %d.", cellWidth);
      return;
   }

   // Update.
   mCellWidth = cellWidth;

   // Refresh the asset.
   refreshAsset();
}

void SpriteAsset::setCellHeight(const S32 cellHeight)
{
   if (cellHeight == mCellHeight)
      return;

   if (cellHeight < 0)
   {
      Con::warnf("Invalid cell height %d.", cellHeight);
      return;
   }

   mCellHeight = cellHeight;

   refreshAsset();

}

const char* SpriteAsset::getSpriteInfo()
{
   Con::printf("get sprite info");
   if (mIsValidSprite)
   {
      static const U32 bufSize = 2048;
      char* returnBuffer = Con::getReturnBuffer(bufSize);
      dSprintf(returnBuffer, bufSize, "%s %d %d %d %d",
               GFXStringTextureFormat[mSprite.getFormat()],
               mSprite.getHeight(),
               mSprite.getWidth(),
               getFrameCount(),
               mCustomFrames.size());

      return returnBuffer;
   }

   return "";

}

void SpriteAsset::calculateSprite()
{
   /// Debug profile
   mFrames.clear();

   mSprite = TEXMGR->createTexture(mSpritePath, &GFXStaticTextureSRGBProfile);

   calculateImplicit();

}

void SpriteAsset::calculateImplicit()
{
   /// calculate texel scale.
   GFXTextureObject* texObj = mSprite;

   const F32 texWScale = 1.0f / ((F32)texObj->getWidth());
   const F32 texHScale = 1.0f / ((F32)texObj->getHeight());

   /// original bitmap dimension
   const U32 spriteWidth = texObj->getBitmapWidth();
   const U32 spriteHeight = texObj->getBitmapHeight();

   /// default frame.
   FrameArea frameArea(0, 0, spriteWidth, spriteHeight, texWScale, texHScale);
   mFrames.push_back(frameArea);

   /// we don't have cells get out.
   if (mCellCountX < 1 || mCellCountY < 1)
      return;

   if (mCellWidth < 1 || mCellWidth > spriteWidth)
   {
      Con::warnf("SpriteAsset::calculateSprite() - Invalid cell width of %d", mCellWidth);
      return;
   }

   if (mCellHeight < 1 || mCellHeight > spriteHeight)
   {
      Con::warnf("SpriteAsset::calculateSprite() - Invalid cell height of %d", mCellHeight);
      return;
   }

   // The Cell Offset X needs to be within the image.
   if (mCellOffsetX < 0 || mCellOffsetX >= spriteWidth)
   {
      // Warn.
      Con::warnf("SpriteAsset::calculateSprite() - Invalid Cell OffsetX of %d.", mCellOffsetX);
      return;
   }

   // The Cell Offset Y needs to be within the image.
   if (mCellOffsetY < 0 || mCellOffsetY >= spriteHeight)
   {
      // Warn.
      Con::warnf("SpriteAsset::calculateSprite() - Invalid Cell OffsetY of %d.", mCellOffsetY);
      return;
   }

   // Are we using Cell-StrideX?
   S32 cellStepX;
   if (mCellStrideX != 0)
   {
      // Yes, so set stepX to be StrideX.
      cellStepX = mCellStrideX;
   }
   else
   {
      // No, so set stepY to be Cell Width.
      cellStepX = mCellWidth;
   }

   // Are we using Cell-StrideY?
   S32 cellStepY;
   if (mCellStrideY != 0)
   {
      // Yes, so set stepY to be StrideY.
      cellStepY = mCellStrideY;
   }
   else
   {
      // No, so set stepY to be Cell Height.
      cellStepY = mCellHeight;
   }

   // Calculate Final Cell Position X.
   S32 cellFinalPositionX = mCellOffsetX + ((mCellCountX - ((cellStepX < 0) ? 1 : 0))*cellStepX);
   // Off Left?
   if (cellFinalPositionX < 0)
   {
      // Warn.
      Con::warnf("SpriteAsset::calculateImage() - Invalid Cell OffsetX(%d)/Width(%d)/CountX(%d); off image left-hand-side.", mCellOffsetX, mCellWidth, mCellCountX);
      return;
   }
   // Off Right?
   else if (cellFinalPositionX > spriteWidth)
   {
      // Warn.
      Con::warnf("SpriteAsset::calculateImage() - Invalid Cell OffsetX(%d)/Width(%d)/CountX(%d); off image right-hand-side.", mCellOffsetX, mCellWidth, mCellCountX);
      return;
   }

   // Calculate Final Cell Position Y.
   S32 cellFinalPositionY = mCellOffsetY + ((mCellCountY - ((cellStepY < 0) ? 1 : 0))*cellStepY);
   // Off Top?
   if (cellFinalPositionY < 0)
   {
      // Warn.
      Con::warnf("SpriteAsset::calculateImage() - Invalid Cell OffsetY(%d)/Height(%d)/CountY(%d); off image top-side.", mCellOffsetY, mCellHeight, mCellCountY);
      return;
   }
   // Off Bottom?
   else if (cellFinalPositionY > spriteHeight)
   {
      // Warn.
      Con::warnf("SpriteAsset::calculateImage() - Invalid Cell OffsetY(%d)/Height(%d)/CountY(%d); off image bottom-side.", mCellOffsetY, mCellHeight, mCellCountY);
      return;
   }

   // Clear default frame.
   mFrames.clear();

   // Cell Row Order?
   if (mCellRowOrder)
   {
      // Yes, so RowRow Order.
      for (S32 y = 0, cellPositionY = mCellOffsetY; y < mCellCountY; y++, cellPositionY += cellStepY)
      {
         for (S32 x = 0, cellPositionX = mCellOffsetX; x < mCellCountX; x++, cellPositionX += cellStepX)
         {
            // Set frame area.
            frameArea.setArea(cellPositionX, cellPositionY, mCellWidth, mCellHeight, texWScale, texHScale);

            // Store fame.
            mFrames.push_back(frameArea);
         }
      }

      return;
   }

   // No, so Column Order.
   for (S32 x = 0, cellPositionX = mCellOffsetX; x < mCellCountX; x++, cellPositionX += cellStepX)
   {
      for (S32 y = 0, cellPositionY = mCellOffsetY; y < mCellCountY; y++, cellPositionY += cellStepY)
      {
         // Set frame area.
         frameArea.setArea(cellPositionX, cellPositionY, mCellWidth, mCellHeight, texWScale, texHScale);

         // Store fame.
         mFrames.push_back(frameArea);
      }
   }

}


void SpriteAsset::onTamlCustomWrite(TamlCustomNodes & customNodes)
{
   Parent::onTamlCustomWrite(customNodes);

   if (mCustomFrames.size() > 0)
   {
      TamlCustomNode* pCustomCellNode = customNodes.addNode(customCellsNode);
      for (typeFrameAreaVector::iterator Itr = mCustomFrames.begin(); Itr != mCustomFrames.end(); ++Itr)
      {
         const FrameArea& frameArea = *Itr;

         TamlCustomNode* pCellNode = pCustomCellNode->addNode(cellNodeName);

         pCellNode->addField(cellRegionName,    frameArea.mPixelArea.mRegionName);
         pCellNode->addField(cellOffsetName,    frameArea.mPixelArea.mPixelOffset);
         pCellNode->addField(cellWidthName,     frameArea.mPixelArea.mPixelWidth);
         pCellNode->addField(cellHeightName ,   frameArea.mPixelArea.mPixelHeight);
      }
   }
   else
      return;

}

void SpriteAsset::onTamlCustomRead(TamlCustomNodes & customNodes)
{
   Parent::onTamlCustomRead(customNodes);

   const TamlCustomNode* pCustomCellNode = customNodes.findNode(customCellsNode);
   if (pCustomCellNode != NULL)
   {
      /// calculate texel scale.
      const F32 texWScale = 1.0f / (F32)mSprite->getWidth();
      const F32 texHScale = 1.0f / (F32)mSprite->getHeight();

      /// original bitmap dimension
      const U32 spriteWidth = mSprite->getBitmapWidth();
      const U32 spriteHeight = mSprite->getBitmapHeight();

      FrameArea frameArea(0, 0, spriteWidth, spriteHeight, texWScale, texHScale);

      mCustomFrames.clear();

      const TamlCustomNodeVector& cellNodes = pCustomCellNode->getChildren();

      for (TamlCustomNodeVector::const_iterator cellNodeItr = cellNodes.begin(); cellNodeItr != cellNodes.end(); ++cellNodeItr)
      {
         TamlCustomNode* pCellNode = *cellNodeItr;

         StringTableEntry nodeName = pCellNode->getNodeName();

         if (nodeName != cellNodeName)
         {
            Con::warnf("SpriteAsset::onTamlCustomRead() - Encountered an unknown custom name of '%s'.  Only '%s' is valid.", nodeName, cellNodeName);
            continue;
         }

         Point2I cellOffset(0, 0);
         S32 cellWidth = 0;
         S32 cellHeight = 0;
         const char* regionName = NULL;

         const TamlCustomFieldVector& fields = pCellNode->getFields();

         for (TamlCustomFieldVector::const_iterator fieldItr = fields.begin(); fieldItr != fields.end(); ++fieldItr)
         {
            const TamlCustomField* pField = *fieldItr;

            StringTableEntry fieldName = pField->getFieldName();

            if (fieldName == cellRegionName)
            {
               regionName = pField->getFieldValue();
            }
            else if (fieldName == cellOffsetName)
            {
               pField->getFieldValue(cellOffset);
            }
            else if (fieldName == cellOffsetXName)
            {
               pField->getFieldValue(cellOffset.x);
            }
            else if (fieldName == cellOffsetYName)
            {
               pField->getFieldValue(cellOffset.y);
            }
            else if (fieldName == cellWidthName)
            {
               pField->getFieldValue(cellWidth);
            }
            else if (fieldName == cellHeightName)
            {
               pField->getFieldValue(cellHeight);
            }
            else
            {
               Con::warnf("SpriteAsset::onTamlCustomRead() - Encountered an unknown custom field name of '%s'.", fieldName);
               continue;
            }
         }

         if (regionName == NULL)
         {
            Con::warnf("SpriteAsset::onTamlCustomRead() - Cell name of '%s' is invalid or was not set.", regionName);

            U32 currentIndex = mCustomFrames.size();
            Con::warnf("- Setting to the next index in the frame list: '%i'", currentIndex);

            dSscanf(regionName, "%i", currentIndex);
         }

         if (cellOffset.x < 0 || cellOffset.y < 0 || cellOffset.x > spriteWidth || cellOffset.y > spriteHeight)
         {
            Con::warnf("SpriteAsset::onTamlCustomRead() - Cell offset of '(%d,%d)' is invalid or was not set.", cellOffset.x, cellOffset.y);
            continue;
         }

         if (cellWidth <= 0 || cellWidth > spriteWidth)
         {
            Con::warnf("SpriteAsset::onTamlCustomRead() - Cell width of '%d' is invalid or was not set.", cellWidth);
            continue;
         }

         if (cellHeight <= 0 || cellHeight > spriteHeight)
         {
            Con::warnf("SpriteAsset::onTamlCustomRead() - Cell height of '%d' is invalid or was not set.", cellHeight);
            continue;
         }

         frameArea.setArea(cellOffset.x, cellOffset.y, cellWidth, cellHeight, texWScale, texHScale, regionName);
         mCustomFrames.push_back(frameArea);
         
      }

   }

}

static void WriteCustomTamlSchema(const AbstractClassRep* pClassRep, tinyxml2::XMLElement* pParentElement)
{
   AssertFatal(pClassRep != NULL, "SpriteAsset::WriteCustomTamlSchema() - ClassRep cannot be NULL.");
   AssertFatal(pParentElement != NULL, "SpriteAsset::WriteCustomTamlSchema() - Parent Element cannot be NULL.");

   char buffer[1024];

   tinyxml2::XMLDocument* doc = pParentElement->GetDocument();

   // Create ImageAsset node element.
   tinyxml2::XMLElement* pSpriteAssetNodeElement = doc->NewElement("xs:element");
   dSprintf(buffer, sizeof(buffer), "%s.%s", pClassRep->getClassName(), customCellsNode);
   pSpriteAssetNodeElement->SetAttribute("name", buffer);
   pSpriteAssetNodeElement->SetAttribute("minOccurs", 0);
   pSpriteAssetNodeElement->SetAttribute("maxOccurs", 1);
   pParentElement->LinkEndChild(pSpriteAssetNodeElement);

   // Create complex type.
   tinyxml2::XMLElement* pSpriteAssetNodeComplexTypeElement = doc->NewElement("xs:complexType");
   pSpriteAssetNodeElement->LinkEndChild(pSpriteAssetNodeComplexTypeElement);

   // Create choice element.
   tinyxml2::XMLElement* pSpriteAssetNodeChoiceElement = doc->NewElement("xs:choice");
   pSpriteAssetNodeChoiceElement->SetAttribute("minOccurs", 0);
   pSpriteAssetNodeChoiceElement->SetAttribute("maxOccurs", "unbounded");
   pSpriteAssetNodeComplexTypeElement->LinkEndChild(pSpriteAssetNodeChoiceElement);

   // Create ImageAsset element.
   tinyxml2::XMLElement* pSpriteAssetElement = doc->NewElement("xs:element");
   pSpriteAssetElement->SetAttribute("name", cellNodeName);
   pSpriteAssetElement->SetAttribute("minOccurs", 0);
   pSpriteAssetElement->SetAttribute("maxOccurs", 1);
   pSpriteAssetNodeChoiceElement->LinkEndChild(pSpriteAssetElement);

   // Create complex type Element.
   tinyxml2::XMLElement* pSpriteAssetComplexTypeElement = doc->NewElement("xs:complexType");
   pSpriteAssetElement->LinkEndChild(pSpriteAssetComplexTypeElement);

   // Create "RegionName" attribute.
   tinyxml2::XMLElement* pSpriteAssetRegionName = doc->NewElement("xs:attribute");
   pSpriteAssetRegionName->SetAttribute("name", cellRegionName);
   pSpriteAssetRegionName->SetAttribute("type", "xs:string");
   pSpriteAssetComplexTypeElement->LinkEndChild(pSpriteAssetRegionName);

   // Create "Offset" attribute.
   tinyxml2::XMLElement* pSpriteAssetOffset = doc->NewElement("xs:attribute");
   pSpriteAssetOffset->SetAttribute("name", cellOffsetName);
   pSpriteAssetOffset->SetAttribute("type", "Point2I_ConsoleType");
   pSpriteAssetComplexTypeElement->LinkEndChild(pSpriteAssetOffset);

   // Create "Width" attribute.
   tinyxml2::XMLElement* pSpriteAssetWidth = doc->NewElement("xs:attribute");
   pSpriteAssetWidth->SetAttribute("name", cellWidthName);
   pSpriteAssetWidth->SetAttribute("type", "xs:unsignedInt");
   pSpriteAssetComplexTypeElement->LinkEndChild(pSpriteAssetWidth);

   // Create "Height" attribute.
   tinyxml2::XMLElement* pSpriteAssetHeight = doc->NewElement("xs:attribute");
   pSpriteAssetHeight->SetAttribute("name", cellHeightName);
   pSpriteAssetHeight->SetAttribute("type", "xs:unsignedInt");
   pSpriteAssetComplexTypeElement->LinkEndChild(pSpriteAssetHeight);

}

IMPLEMENT_CONOBJECT_SCHEMA(SpriteAsset, WriteCustomTamlSchema);

DefineEngineMethod(SpriteAsset, getSpriteFileName, const char*, (), ,
   "Creates an instance of the given GameObject given the asset definition.\n"
   "@return The GameObject entity created from the asset.")
{
   return object->getSpriteFileName();
}

DefineEngineMethod(SpriteAsset, getSpriteInfo, const char*, (), ,
   "Creates an instance of the given GameObject given the asset definition.\n"
   "@return The GameObject entity created from the asset.")
{
   return object->getSpriteInfo();
}

DefineEngineMethod(SpriteAsset, getCellCountX, S32, (), ,
   "")
{
   return object->getCellCountX();
}

DefineEngineMethod(SpriteAsset, getCellCountY, S32, (), ,
   "")
{
   return object->getCellCountY();
}

DefineEngineMethod(SpriteAsset, getFrameCount, S32, (), ,
   "")
{
   return object->getFrameCount();
}


//-----------------------------------------------------------------------------
// GuiInspectorTypeSpriteAssetPtr
//-----------------------------------------------------------------------------

IMPLEMENT_CONOBJECT(GuiInspectorTypeSpriteAssetPtr);

ConsoleDocClass(GuiInspectorTypeSpriteAssetPtr,
   "@brief Inspector field for sprite asset\n\n"
   "Editor Use only.\n\n"
   "@internal");

void GuiInspectorTypeSpriteAssetPtr::consoleInit()
{
   Parent::consoleInit();

   ConsoleBaseType::getType(TypeSpriteAssetPtr)->setInspectorFieldType("GuiInspectorTypeSpriteAssetPtr");
}

GuiControl * GuiInspectorTypeSpriteAssetPtr::constructEditControl()
{
   GuiControl *retCtrl = Parent::constructEditControl();
   if(retCtrl == NULL)
      return retCtrl;

   // Change filespec
   char szBuffer[512];
   dSprintf(szBuffer, sizeof(szBuffer), "AssetBrowser.showDialog(\"SpriteAsset\", \"AssetBrowser.changeAsset\", %s, %s);",
      mInspector->getInspectObject()->getIdString(), mCaption);
   mBrowseButton->setField("Command", szBuffer);

   return retCtrl;

}

bool GuiInspectorTypeSpriteAssetPtr::updateRects()
{
   S32 dividerPos, dividerMargin;
   mInspector->getDivider(dividerPos, dividerMargin);
   Point2I fieldExtent = getExtent();
   Point2I fieldPos = getPosition();

   mCaptionRect.set(0, 0, fieldExtent.x - dividerPos - dividerMargin, fieldExtent.y);
   mEditCtrlRect.set(fieldExtent.x - dividerPos + dividerMargin, 1, dividerPos - dividerMargin - 34, fieldExtent.y);

   bool resized = mEdit->resize(mEditCtrlRect.point, mEditCtrlRect.extent);
   if (mBrowseButton != NULL)
   {
      mBrowseRect.set(fieldExtent.x - 32, 2, 14, fieldExtent.y - 4);
      resized |= mBrowseButton->resize(mBrowseRect.point, mBrowseRect.extent);
   }

   //if (mSpriteEdButton != NULL)
   //{
   //   RectI shapeEdRect(fieldExtent.x - 16, 2, 14, fieldExtent.y - 4);
   //   resized |= mSpriteEdButton->resize(shapeEdRect.point, shapeEdRect.extent);
   //}

   return resized;
}

IMPLEMENT_CONOBJECT(GuiInspectorTypeSpriteAssetId);

ConsoleDocClass(GuiInspectorTypeSpriteAssetId,
   "@brief Inspector field for sprite asset\n\n"
   "Editor Use only.\n\n"
   "@internal");

void GuiInspectorTypeSpriteAssetId::consoleInit()
{
   Parent::consoleInit();

   ConsoleBaseType::getType(TypeSpriteAssetId)->setInspectorFieldType("GuiInspectorTypeSpriteAssetId");
}
