//-----------------------------------------------------------------------------
// Copyright (c) 2013 GarageGames, LLC
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

#ifndef SOUND_ASSET_H
#include "SoundAsset.h"
#endif

#ifndef _ASSET_MANAGER_H_
#include "assets/assetManager.h"
#endif

#ifndef _CONSOLETYPES_H_
#include "console/consoleTypes.h"
#endif

#ifndef _TAML_
#include "persistence/taml/taml.h"
#endif

#ifndef _ASSET_PTR_H_
#include "assets/assetPtr.h"
#endif

#ifndef _SFXSOURCE_H_
#include "sfx/sfxSource.h"
#endif

// Debug Profiling.
#include "platform/profiler.h"
#include "sfx/sfxTypes.h"

#include "SoundAssetInspectors.h"

//-----------------------------------------------------------------------------

IMPLEMENT_CONOBJECT(SoundAsset);

ConsoleType(SoundAssetPtr, TypeSoundAssetPtr, const char*, ASSET_ID_FIELD_PREFIX)

//-----------------------------------------------------------------------------

ConsoleGetType(TypeSoundAssetPtr)
{
   // Fetch asset Id.
   return *((const char**)(dptr));
}

//-----------------------------------------------------------------------------

ConsoleSetType(TypeSoundAssetPtr)
{
   // Was a single argument specified?
   if (argc == 1)
   {
      // Yes, so fetch field value.
      *((const char**)dptr) = StringTable->insert(argv[0]);

      return;
   }

   // Warn.
   Con::warnf("(TypeSoundAssetPtr) - Cannot set multiple args to a single asset.");
}

//-----------------------------------------------------------------------------

ConsoleType(assetIdString, TypeSoundAssetId, const char*, ASSET_ID_FIELD_PREFIX)

ConsoleGetType(TypeSoundAssetId)
{
   // Fetch asset Id.
   return *((const char**)(dptr));
}

ConsoleSetType(TypeSoundAssetId)
{
   // Was a single argument specified?
   if (argc == 1)
   {
      // Yes, so fetch field value.
      *((const char**)dptr) = StringTable->insert(argv[0]);

      return;
   }

   // Warn.
   Con::warnf("(TypeAssetId) - Cannot set multiple args to a single asset.");
}

//-----------------------------------------------------------------------------

SoundAsset::SoundAsset()
   : AssetBase()
{
   mSoundFile = StringTable->EmptyString();
   mSoundPath = StringTable->EmptyString();
   mSubtitleString = StringTable->EmptyString();

   mLoadedState = AssetErrCode::NotLoaded;
   mPreload = false;
   // SFX description inits
   // reverb is useless here, reverb is inacted on listener.
   mProfileDesc.mPitch = 1;
   mProfileDesc.mVolume = 1;
   mProfileDesc.mIs3D = false;
   mProfileDesc.mIsLooping = false;
   mProfileDesc.mIsStreaming = false;
   mProfileDesc.mUseHardware = false;
   mProfileDesc.mMinDistance = 1;
   mProfileDesc.mMaxDistance = 100;
   mProfileDesc.mConeInsideAngle = 360;
   mProfileDesc.mConeOutsideAngle = 360;
   mProfileDesc.mConeOutsideVolume = 1;
   mProfileDesc.mRolloffFactor = -1.0f;
   mProfileDesc.mScatterDistance = Point3F(0.f, 0.f, 0.f);
   mProfileDesc.mPriority = 1.0f;
   mProfileDesc.mSourceGroup = NULL;

}

//-----------------------------------------------------------------------------

SoundAsset::~SoundAsset()
{
}

//-----------------------------------------------------------------------------

void SoundAsset::initPersistFields()
{
   docsURL;
   // Call parent.
   Parent::initPersistFields();

   addProtectedField("soundFile", TypeAssetLooseFilePath, Offset(mSoundFile, SoundAsset),
      &setSoundFile, &getSoundFile, "Path to the sound file.");

   addField("pitchAdjust", TypeF32, Offset(mProfileDesc.mPitch, SoundAsset), "Adjustment of the pitch value 1 is default.");
   addField("volumeAdjust", TypeF32, Offset(mProfileDesc.mVolume, SoundAsset), "Adjustment to the volume.");
   addField("is3D", TypeBool, Offset(mProfileDesc.mIs3D, SoundAsset), "Set this sound to 3D.");
   addField("isLooping", TypeBool, Offset(mProfileDesc.mIsLooping, SoundAsset), "Does this sound loop.");
   // if streaming, a default packet size should be chosen for all sounds.
   addField("isStreaming", TypeBool, Offset(mProfileDesc.mIsStreaming, SoundAsset), "Use streaming.");
   //....why?
   addField("useHardware", TypeBool, Offset(mProfileDesc.mUseHardware, SoundAsset), "Use hardware mixing for this sound.");
   addField("minDistance", TypeF32, Offset(mProfileDesc.mMinDistance, SoundAsset), "Minimum distance for sound.");
   // more like it.
   addField("maxDistance", TypeF32, Offset(mProfileDesc.mMaxDistance, SoundAsset), "Max distance for sound.");
   addField("coneInsideAngle", TypeS32, Offset(mProfileDesc.mConeInsideAngle, SoundAsset), "Cone inside angle.");
   addField("coneOutsideAngle", TypeS32, Offset(mProfileDesc.mConeOutsideAngle, SoundAsset), "Cone outside angle.");
   addField("coneOutsideVolume", TypeF32, Offset(mProfileDesc.mConeOutsideVolume, SoundAsset), "Cone outside volume.");
   addField("rolloffFactor", TypeF32, Offset(mProfileDesc.mRolloffFactor, SoundAsset), "Rolloff factor.");
   addField("scatterDistance", TypePoint3F, Offset(mProfileDesc.mScatterDistance, SoundAsset), "Randomization to the spacial position of the sound.");
   addField("sourceGroup", TypeSFXSourceName, Offset(mProfileDesc.mSourceGroup, SoundAsset), "Group that sources playing with this description should be put into.");

}

//------------------------------------------------------------------------------

void SoundAsset::copyTo(SimObject* object)
{
   // Call to parent.
   Parent::copyTo(object);
}

void SoundAsset::initializeAsset(void)
{
   Parent::initializeAsset();

   if (mSoundFile == StringTable->EmptyString())
      return;

   mSoundPath = getOwned() ? expandAssetFilePath(mSoundFile) : mSoundPath;
   loadSound();
}

void SoundAsset::_onResourceChanged(const Torque::Path &path)
{
   if (path != Torque::Path(mSoundPath))
      return;

   refreshAsset();

   loadSound();
}

void SoundAsset::onAssetRefresh(void)
{
   if (mSoundFile == StringTable->EmptyString())
      return;

   //Update
   mSoundPath = getOwned() ? expandAssetFilePath(mSoundFile) : mSoundPath;
   loadSound();
}

bool SoundAsset::loadSound()
{
   if (mSoundPath)
   {
      if (!Torque::FS::IsFile(mSoundPath))
      {
         Con::errorf("SoundAsset::initializeAsset: Attempted to load file %s but it was not valid!", mSoundFile);
         mLoadedState = BadFileReference;
         mSFXProfile.setDescription(NULL);
         mSFXProfile.setSoundFileName(StringTable->insert(StringTable->EmptyString()));
         mSFXProfile.setPreload(false);
         return false;
      }
      else
      {// = new SFXProfile(mProfileDesc, mSoundFile, mPreload);
         if (mProfileDesc.mSourceGroup == NULL)
            mProfileDesc.mSourceGroup = dynamic_cast<SFXSource*>(Sim::findObject("AudioChannelMaster"));
         mSFXProfile.setDescription(&mProfileDesc);
         mSFXProfile.setSoundFileName(mSoundPath);
         mSFXProfile.setPreload(mPreload);

         //give it a nudge to preload if required
         mSFXProfile.getBuffer();
      }

   }
   mChangeSignal.trigger();
   mLoadedState = Ok;
   return true;
}

void SoundAsset::setSoundFile(const char* pSoundFile)
{
   // Sanity!
   AssertFatal(pSoundFile != NULL, "Cannot use a NULL sound file.");

   // Fetch sound file.
   pSoundFile = StringTable->insert(pSoundFile, true);

   // Ignore no change,
   if (pSoundFile == mSoundFile)
      return;

   // Update.
   mSoundFile = getOwned() ? expandAssetFilePath(pSoundFile) : pSoundFile;

   // Refresh the asset.
   refreshAsset();
}

StringTableEntry SoundAsset::getAssetIdByFileName(StringTableEntry fileName)
{
   if (fileName == StringTable->EmptyString())
      return StringTable->EmptyString();

   StringTableEntry soundAssetId = StringTable->EmptyString();

   AssetQuery query;
   U32 foundCount = AssetDatabase.findAssetType(&query, "SoundAsset");
   if (foundCount != 0)
   {
      for (U32 i = 0; i < foundCount; i++)
      {
         SoundAsset* soundAsset = AssetDatabase.acquireAsset<SoundAsset>(query.mAssetList[i]);
         if (soundAsset && soundAsset->getSoundPath() == fileName)
         {
            soundAssetId = soundAsset->getAssetId();
            AssetDatabase.releaseAsset(query.mAssetList[i]);
            break;
         }
         AssetDatabase.releaseAsset(query.mAssetList[i]);
      }
   }

   return soundAssetId;
}

U32 SoundAsset::getAssetById(StringTableEntry assetId, AssetPtr<SoundAsset>* soundAsset)
{
   (*soundAsset) = assetId;

   if (soundAsset->notNull())
   {
      return (*soundAsset)->mLoadedState;
   }
   else
   {
      //Well that's bad, loading the fallback failed.
      Con::warnf("SoundAsset::getAssetById - Finding of asset with id %s failed with no fallback asset", assetId);
      return AssetErrCode::Failed;
   }
}

U32 SoundAsset::getAssetByFileName(StringTableEntry fileName, AssetPtr<SoundAsset>* soundAsset)
{
   AssetQuery query;
   U32 foundAssetcount = AssetDatabase.findAssetType(&query, "SoundAsset");
   if (foundAssetcount == 0)
   {
      //Well that's bad, loading the fallback failed.
      Con::warnf("MaterialAsset::getAssetByMaterialName - Finding of asset associated with filename %s failed with no fallback asset", fileName);
      return AssetErrCode::Failed;
   }
   else
   {
      for (U32 i = 0; i < foundAssetcount; i++)
      {
         SoundAsset* tSoundAsset = AssetDatabase.acquireAsset<SoundAsset>(query.mAssetList[i]);
         if (tSoundAsset && tSoundAsset->getSoundPath() == fileName)
         {
            soundAsset->setAssetId(query.mAssetList[i]);
            AssetDatabase.releaseAsset(query.mAssetList[i]);
            return (*soundAsset)->mLoadedState;
         }
         AssetDatabase.releaseAsset(query.mAssetList[i]); //cleanup if that's not the one we needed
      }
   }

   //No good match
   return AssetErrCode::Failed;
}

DefineEngineMethod(SoundAsset, getSoundPath, const char*, (), , "")
{
   return object->getSoundPath();
}

DefineEngineMethod(SoundAsset, playSound, S32, (Point3F position), (Point3F::Zero),
   "Plays the sound for this asset.\n"
   "@return (sound plays).\n")
{
   if (object->getSfxProfile())
   {
      MatrixF transform;
      transform.setPosition(position);
      SFXSource* source = SFX->playOnce(object->getSfxProfile(), &transform, NULL, -1);
      if(source)
         return source->getId();
      else
         return 0;
   }
   else
      return 0;
}

#ifdef TORQUE_TOOLS
DefineEngineStaticMethod(SoundAsset, getAssetIdByFilename, const char*, (const char* filePath), (""),
   "Queries the Asset Database to see if any asset exists that is associated with the provided file path.\n"
   "@return The AssetId of the associated asset, if any.")
{
   return SoundAsset::getAssetIdByFileName(StringTable->insert(filePath));
}
IMPLEMENT_CONOBJECT(GuiInspectorTypeSoundAssetPtr);

ConsoleDocClass(GuiInspectorTypeSoundAssetPtr,
   "@brief Inspector field type for Sounds\n\n"
   "Editor use only.\n\n"
   "@internal"
);

void GuiInspectorTypeSoundAssetPtr::consoleInit()
{
   Parent::consoleInit();

   ConsoleBaseType::getType(TypeSoundAssetPtr)->setInspectorFieldType("GuiInspectorTypeSoundAssetPtr");
}

GuiControl * GuiInspectorTypeSoundAssetPtr::constructEditControl()
{
   // Create base filename edit controls
   GuiControl* retCtrl = Parent::constructEditControl();
   if (retCtrl == NULL)
      return retCtrl;

   // Change filespec
   char szBuffer[512];
   dSprintf(szBuffer, sizeof(szBuffer), "AssetBrowser.showDialog(\"SoundAsset\", \"AssetBrowser.changeAsset\", %s, \"\");",
      getIdString());
   mBrowseButton->setField("Command", szBuffer);

   setDataField(StringTable->insert("targetObject"), NULL, mInspector->getInspectObject()->getIdString());

   // Create "Open in Editor" button
   mEditButton = new GuiBitmapButtonCtrl();

   dSprintf(szBuffer, sizeof(szBuffer), "AssetBrowser.editAsset(%d.getText());", retCtrl->getId());
   mEditButton->setField("Command", szBuffer);

   char bitmapName[512] = "ToolsModule:SFXEmitter_image";
   mEditButton->setBitmap(StringTable->insert(bitmapName));

   mEditButton->setDataField(StringTable->insert("Profile"), NULL, "GuiButtonProfile");
   mEditButton->setDataField(StringTable->insert("tooltipprofile"), NULL, "GuiToolTipProfile");
   mEditButton->setDataField(StringTable->insert("hovertime"), NULL, "1000");
   mEditButton->setDataField(StringTable->insert("tooltip"), NULL, "Test play this sound");

   mEditButton->registerObject();
   addObject(mEditButton);

   return retCtrl;
}

bool GuiInspectorTypeSoundAssetPtr::updateRects()
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

   if (mEditButton != NULL)
   {
      RectI shapeEdRect(fieldExtent.x - 16, 2, 14, fieldExtent.y - 4);
      resized |= mEditButton->resize(shapeEdRect.point, shapeEdRect.extent);
   }

   return resized;
}

IMPLEMENT_CONOBJECT(GuiInspectorTypeSoundAssetId);

ConsoleDocClass(GuiInspectorTypeSoundAssetId,
   "@brief Inspector field type for Sounds\n\n"
   "Editor use only.\n\n"
   "@internal"
);

void GuiInspectorTypeSoundAssetId::consoleInit()
{
   Parent::consoleInit();

   ConsoleBaseType::getType(TypeSoundAssetId)->setInspectorFieldType("GuiInspectorTypeSoundAssetId");
}
#endif
