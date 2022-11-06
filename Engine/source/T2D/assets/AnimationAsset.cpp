#include "T2D/assets/AnimationAsset.h"
#include "T2D/assets/SpriteAsset.h"

// Debug Profiling.
#include "platform/profiler.h"

//------------------------------------------------------------------------------

IMPLEMENT_CONOBJECT(AnimationAsset);

//------------------------------------------------------------------------------

AnimationAsset::AnimationAsset()
   :  mAnimFPS(12),
      mAnimLoop(true),
      mRandomStart(false),
      mBounce(false),
      mSpriteAssetId(StringTable->EmptyString())
{
   VECTOR_SET_ASSOCIATION(mAnimFrames);
}

AnimationAsset::~AnimationAsset()
{
}

bool AnimationAsset::_setSpriteAsset(void * obj, const char * index, const char * data)
{
   AnimationAsset* aa = static_cast<AnimationAsset*>(obj);

   aa->mSpriteAssetId = StringTable->insert(data);

   return aa->setSpriteAsset(aa->mSpriteAssetId);

}

bool AnimationAsset::setSpriteAsset(const StringTableEntry spriteAssetId)
{
   if (!SpriteAsset::getAssetById(spriteAssetId, &mSpriteAsset))
   {
      Con::warnf("Error sprite asset id '%s' not found.", spriteAssetId);
      return false;
   }

   return true;
}

bool AnimationAsset::_setAnimationFrames(void * obj, const char * index, const char * data)
{
   AnimationAsset* aa = static_cast<AnimationAsset*>(obj);
   if (!aa->setAnimationFrames(data))
   {
      Con::warnf("Error frames not valid.");
      return false;
   }

   return true;
}

bool AnimationAsset::setAnimationFrames(const char * animFrames)
{
   mAnimFrames.clear();

   if (mSpriteAsset == NULL)
   {
      Con::warnf("AnimationAsset::setAnimationFrames() - cannot set frames without a sprite asset.");
      return false;
   }

   const U32 frameCount = StringUnit::getUnitCount(animFrames, " \t\n");

   for (U32 i = 0; i < frameCount; i++)
   {
      U32 frame = dAtoi(StringUnit::getUnit(animFrames, i, " \t\n"));

      if (frame >= mSpriteAsset->getFrameCount() || frame < 0)
      {
         Con::warnf("AnimationAsset::setAnimationFrames() frame %d out of range.", frame);
      }
      else
      {
         mAnimFrames.push_back(frame);
      }
   }

   return true;
}

bool AnimationAsset::getAssetById(StringTableEntry assetId, AssetPtr<AnimationAsset>* animAsset)
{
   (*animAsset) = assetId;

   if (!animAsset->isNull())
      return true;

   return false;
}

SpriteAsset::FrameArea AnimationAsset::getActiveFrameArea(U32 frame)
{
   return mSpriteAsset->getSpriteFrameArea(frame);
}

void AnimationAsset::initPersistFields()
{
   Parent::initPersistFields();

   addProtectedField("spriteAsset", TypeSpriteAssetId, Offset(mSpriteAssetId, AnimationAsset), &_setSpriteAsset, &defaultProtectedGetFn,
      "Add a sprite asset.");

   addProtectedField("animFrames", TypeS32Vector, Offset(mAnimFrames, AnimationAsset), &_setAnimationFrames, &defaultProtectedGetFn,
      "Set frames in this animation.");

   addField("animFPS", TypeS32, Offset(mAnimFPS, AnimationAsset),
      "Set animation time.");

   addField("animLoop", TypeBool, Offset(mAnimLoop, AnimationAsset),
      "Loop Animation.");

   addField("randStart", TypeBool, Offset(mRandomStart, AnimationAsset),
      "Start on a random frame.");

   addField("animBounce", TypeBool, Offset(mBounce, AnimationAsset),
      "When the animation gets to the end it plays backwards.");

}

void AnimationAsset::copyTo(SimObject* object)
{
   Parent::copyTo(object);
}

ConsoleType(assetIdString, TypeAnimationAssetPtr, String, ASSET_ID_FIELD_PREFIX)

ConsoleGetType(TypeAnimationAssetPtr)
{
   // Fetch asset Id.
   return *((StringTableEntry*)dptr);
}

ConsoleSetType(TypeAnimationAssetPtr)
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
   Con::warnf("(TypeAnimationAssetPtr) - Cannot set multiple args to a single asset.");
}

ConsoleType(assetIdString, TypeAnimationAssetId, String, ASSET_ID_FIELD_PREFIX)

ConsoleGetType(TypeAnimationAssetId)
{
   // Fetch asset Id.
   return *((const char**)(dptr));
}

ConsoleSetType(TypeAnimationAssetId)
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
   Con::warnf("(TypeAnimationAssetId) - Cannot set multiple args to a single asset.");
}

//-----------------------------------------------------------------------------
// GuiInspectorTypeAnimationAssetPtr
//-----------------------------------------------------------------------------

IMPLEMENT_CONOBJECT(GuiInspectorTypeAnimationAssetPtr);

ConsoleDocClass(GuiInspectorTypeAnimationAssetPtr,
   "@brief Inspector field for animation asset\n\n"
   "Editor Use only.\n\n"
   "@internal");

void GuiInspectorTypeAnimationAssetPtr::consoleInit()
{
   Parent::consoleInit();

   ConsoleBaseType::getType(TypeSpriteAssetPtr)->setInspectorFieldType("GuiInspectorTypeAnimationAssetPtr");
}

GuiControl * GuiInspectorTypeAnimationAssetPtr::constructEditControl()
{
   GuiControl *retCtrl = Parent::constructEditControl();
   if (retCtrl == NULL)
      return retCtrl;

   // Change filespec
   char szBuffer[512];
   dSprintf(szBuffer, sizeof(szBuffer), "AssetBrowser.showDialog(\"AnimationAsset\", \"AssetBrowser.changeAsset\", %s, %s);",
      mInspector->getInspectObject()->getIdString(), mCaption);
   mBrowseButton->setField("Command", szBuffer);

   return retCtrl;
}

bool GuiInspectorTypeAnimationAssetPtr::updateRects()
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

IMPLEMENT_CONOBJECT(GuiInspectorTypeAnimationAssetId);

ConsoleDocClass(GuiInspectorTypeAnimationAssetId,
   "@brief Inspector field for Animation asset\n\n"
   "Editor Use only.\n\n"
   "@internal");

void GuiInspectorTypeAnimationAssetId::consoleInit()
{
   Parent::consoleInit();

   ConsoleBaseType::getType(TypeSpriteAssetId)->setInspectorFieldType("GuiInspectorTypeAnimationAssetId");
}
