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
   for (U32 i = 0; i < SFXPlayList::NUM_SLOTS; i++)
   {
      mSoundFile[i] = StringTable->EmptyString();
      mSoundPath[i] = StringTable->EmptyString();
   }

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
   addArray("slots", SFXPlayList::NUM_SLOTS);
      addProtectedField("soundFile", TypeAssetLooseFilePath, Offset(mSoundFile, SoundAsset),
         &defaultProtectedSetFn, &defaultProtectedGetFn, "Path to the sound file.");

      addField("replay", TYPEID< SFXPlayList::EReplayMode >(), Offset(mPlaylist.mSlots.mReplayMode, SoundAsset), SFXPlayList::NUM_SLOTS,
         "Behavior when an already playing sound is encountered on this slot from a previous cycle.\n"
         "Each slot can have an arbitrary number of sounds playing on it from previous cycles.  This field determines "
         "how SFXController will handle these sources.");
      addField("transitionIn", TYPEID< SFXPlayList::ETransitionMode >(), Offset(mPlaylist.mSlots.mTransitionIn, SoundAsset), SFXPlayList::NUM_SLOTS,
         "Behavior when moving into this slot.\n"
         "After the delayIn time has expired (if any), this slot determines what the controller "
         "will do before actually playing the slot.");
      addField("transitionOut", TYPEID< SFXPlayList::ETransitionMode >(), Offset(mPlaylist.mSlots.mTransitionOut, SoundAsset), SFXPlayList::NUM_SLOTS,
         "Behavior when moving out of this slot.\n"
         "After the #detailTimeOut has expired (if any), this slot determines what the controller "
         "will do before moving on to the next slot.");
      addField("delayTimeIn", TypeF32, Offset(mPlaylist.mSlots.mDelayTimeIn.mValue, SoundAsset), SFXPlayList::NUM_SLOTS,
         "Seconds to wait after moving into slot before #transitionIn.");
      addField("delayTimeInVariance", TypePoint2F, Offset(mPlaylist.mSlots.mDelayTimeIn.mVariance, SoundAsset), SFXPlayList::NUM_SLOTS,
         "Bounds on randomization of #delayTimeIn.\n\n"
         "@ref SFXPlayList_randomization\n");
      addField("delayTimeOut", TypeF32, Offset(mPlaylist.mSlots.mDelayTimeOut.mValue, SoundAsset), SFXPlayList::NUM_SLOTS,
         "Seconds to wait before moving out of slot after #transitionOut.");
      addField("delayTimeOutVariance", TypePoint2F, Offset(mPlaylist.mSlots.mDelayTimeOut.mVariance, SoundAsset), SFXPlayList::NUM_SLOTS,
         "Bounds on randomization of #delayTimeOut.\n\n"
         "@ref SFXPlayList_randomization\n");
      addField("fadeTimeIn", TypeF32, Offset(mPlaylist.mSlots.mFadeTimeIn.mValue, SoundAsset), SFXPlayList::NUM_SLOTS,
         "Seconds to fade sound in (-1 to use the track's own fadeInTime.)\n"
         "@see SFXDescription::fadeTimeIn");
      addField("fadeTimeInVariance", TypePoint2F, Offset(mPlaylist.mSlots.mFadeTimeIn.mVariance, SoundAsset), SFXPlayList::NUM_SLOTS,
         "Bounds on randomization of #fadeInTime.\n\n"
         "@ref SFXPlayList_randomization\n");
      addField("fadeTimeOut", TypeF32, Offset(mPlaylist.mSlots.mFadeTimeOut.mValue, SoundAsset), SFXPlayList::NUM_SLOTS,
         "Seconds to fade sound out (-1 to use the track's own fadeOutTime.)\n"
         "@see SFXDescription::fadeTimeOut");
      addField("fadeTimeOutVariance", TypePoint2F, Offset(mPlaylist.mSlots.mFadeTimeOut.mVariance, SoundAsset), SFXPlayList::NUM_SLOTS,
         "Bounds on randomization of #fadeOutTime\n\n"
         "@ref SFXPlayList_randomization\n");
      addField("referenceDistance", TypeF32, Offset(mPlaylist.mSlots.mMinDistance.mValue, SoundAsset), SFXPlayList::NUM_SLOTS,
         "@c referenceDistance to set for 3D sounds in this slot (<1 to use @c referenceDistance of track's own description).\n"
         "@see SFXDescription::referenceDistance");
      addField("referenceDistanceVariance", TypePoint2F, Offset(mPlaylist.mSlots.mMinDistance.mVariance, SoundAsset), SFXPlayList::NUM_SLOTS,
         "Bounds on randomization of #referenceDistance.\n\n"
         "@ref SFXPlayList_randomization\n");
      addField("maxDistance", TypeF32, Offset(mPlaylist.mSlots.mMaxDistance.mValue, SoundAsset), SFXPlayList::NUM_SLOTS,
         "@c maxDistance to apply to 3D sounds in this slot (<1 to use @c maxDistance of track's own description).\n"
         "@see SFXDescription::maxDistance");
      addField("maxDistanceVariance", TypePoint2F, Offset(mPlaylist.mSlots.mMaxDistance.mVariance, SoundAsset), SFXPlayList::NUM_SLOTS,
         "Bounds on randomization of #maxDistance.\n\n"
         "@ref SFXPlayList_randomization\n");
      addField("volumeScale", TypeF32, Offset(mPlaylist.mSlots.mVolumeScale.mValue, SoundAsset), SFXPlayList::NUM_SLOTS,
         "Scale factor to apply to volume of sounds played on this list slot.\n"
         "This value will scale the actual volume level set on the track assigned to the slot, i.e. a value of 0.5 will "
         "cause the track to play at half-volume.");
      addField("volumeScaleVariance", TypePoint2F, Offset(mPlaylist.mSlots.mVolumeScale.mVariance, SoundAsset), SFXPlayList::NUM_SLOTS,
         "Bounds on randomization of #volumeScale.\n\n"
         "@ref SFXPlayList_randomization\n");
      addField("pitchScale", TypeF32, Offset(mPlaylist.mSlots.mPitchScale.mValue, SoundAsset), SFXPlayList::NUM_SLOTS,
         "Scale factor to apply to pitch of sounds played on this list slot.\n"
         "This value will scale the actual pitch set on the track assigned to the slot, i.e. a value of 0.5 will "
         "cause the track to play at half its assigned speed.");
      addField("pitchScaleVariance", TypePoint2F, Offset(mPlaylist.mSlots.mPitchScale.mVariance, SoundAsset), SFXPlayList::NUM_SLOTS,
         "Bounds on randomization of #pitchScale.\n\n"
         "@ref SFXPlayList_randomization\n");
      addField("repeatCount", TypeS32, Offset(mPlaylist.mSlots.mRepeatCount, SoundAsset), SFXPlayList::NUM_SLOTS,
         "Number of times to loop this slot.");
      addField("state", TypeSFXStateName, Offset(mPlaylist.mSlots.mState, SoundAsset), SFXPlayList::NUM_SLOTS,
         "State that must be active for this slot to play.\n\n"
         "@ref SFXPlayList_states");
      addField("stateMode", TYPEID< SFXPlayList::EStateMode >(), Offset(mPlaylist.mSlots.mStateMode, SoundAsset), SFXPlayList::NUM_SLOTS,
         "Behavior when assigned state is deactivated while slot is playing.\n\n"
         "@ref SFXPlayList_states");
   endArray("slots");

   addField("pitchAdjust", TypeF32, Offset(mProfileDesc.mPitch, SoundAsset), "Adjustment of the pitch value 1 is default.");
   addField("volumeAdjust", TypeF32, Offset(mProfileDesc.mVolume, SoundAsset), "Adjustment to the volume.");
   addField("is3D", TypeBool, Offset(mProfileDesc.mIs3D, SoundAsset), "Set this sound to 3D.");
   addField("isLooping", TypeBool, Offset(mProfileDesc.mIsLooping, SoundAsset), "Does this sound loop.");
   // if streaming, a default packet size should be chosen for all sounds.
   addField("isStreaming", TypeBool, Offset(mProfileDesc.mIsStreaming, SoundAsset), "Use streaming.");
   //....why?
   addField("useHardware", TypeBool, Offset(mProfileDesc.mUseHardware, SoundAsset), "Use hardware mixing for this sound.");
   addField("sourceGroup", TypeSFXSourceName, Offset(mProfileDesc.mSourceGroup, SoundAsset), "Group that sources playing with this description should be put into.");

   addGroup("Fading");
      addField("fadeInTime", TypeF32, Offset(mProfileDesc.mFadeInTime, SoundAsset), "Number of seconds to gradually fade in volume from zero when playback starts.");
      addField("fadeOutTime", TypeF32, Offset(mProfileDesc.mFadeOutTime, SoundAsset), "Number of seconds to gradually fade out volume down to zero when playback is stopped or paused.");
      addField("fadeInEase", TypeEaseF, Offset(mProfileDesc.mFadeInEase, SoundAsset), "Easing curve for fade-in transition.");
      addField("fadeOutEase", TypeEaseF, Offset(mProfileDesc.mFadeOutEase, SoundAsset), "Easing curve for fade-out transition.");
      addField("fadeLoops", TypeBool, Offset(mProfileDesc.mFadeLoops, SoundAsset), "Fade each cycle of a loop in and/or out; otherwise only fade-in first cycle.");
   endGroup("Fading");

   addGroup("3D");
      addField("minDistance", TypeF32, Offset(mProfileDesc.mMinDistance, SoundAsset), "Minimum distance for sound.");
      addField("maxDistance", TypeF32, Offset(mProfileDesc.mMaxDistance, SoundAsset), "Max distance for sound.");
      addField("coneInsideAngle", TypeS32, Offset(mProfileDesc.mConeInsideAngle, SoundAsset), "Cone inside angle.");
      addField("coneOutsideAngle", TypeS32, Offset(mProfileDesc.mConeOutsideAngle, SoundAsset), "Cone outside angle.");
      addField("coneOutsideVolume", TypeF32, Offset(mProfileDesc.mConeOutsideVolume, SoundAsset), "Cone outside volume.");
      addField("rolloffFactor", TypeF32, Offset(mProfileDesc.mRolloffFactor, SoundAsset), "Rolloff factor.");
      addField("scatterDistance", TypePoint3F, Offset(mProfileDesc.mScatterDistance, SoundAsset), "Randomization to the spacial position of the sound.");
   endGroup("3D");
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
   U32 slotCount = 0;
   for (U32 i = 0; i < SFXPlayList::NUM_SLOTS; i++)
   {
      if (i == 0 && mSoundFile[i] == StringTable->EmptyString())
         return;

      if (mSoundFile[i] == StringTable->EmptyString())
         break;

      mSoundPath[i] = getOwned() ? expandAssetFilePath(mSoundFile[i]) : mSoundPath[i];
      slotCount++;
   }

   loadSound(slotCount);
}

void SoundAsset::_onResourceChanged(const Torque::Path &path)
{
   /*U32 slotCount = 0;
   for (U32 i = 0; i < SFXPlayList::NUM_SLOTS; i++)
   {

      if (path != Torque::Path(mSoundPath[i]))
         return;
   }
   refreshAsset();

   loadSound();*/
}

void SoundAsset::onAssetRefresh(void)
{
   U32 slotCount = 0;
   for (U32 i = 0; i < SFXPlayList::NUM_SLOTS; i++)
   {
      if (i == 0 && mSoundFile[i] == StringTable->EmptyString())
         return;

      if (mSoundFile[i] == StringTable->EmptyString())
         break;

      mSoundPath[i] = getOwned() ? expandAssetFilePath(mSoundFile[i]) : mSoundPath[i];
      slotCount++;
   }

   loadSound(slotCount);
}

bool SoundAsset::loadSound(U32 numSlots)
{
   if (numSlots > 1)
   {
      for (U32 i = 0; i < numSlots; i++)
      {
         if (mSoundPath[i])
         {
            if (!Torque::FS::IsFile(mSoundPath[i]))
            {
               Con::errorf("SoundAsset::initializeAsset: Attempted to load file %s but it was not valid!", mSoundFile[i]);
               mLoadedState = BadFileReference;
               mSFXProfile[i].setDescription(NULL);
               mSFXProfile[i].setSoundFileName(StringTable->insert(StringTable->EmptyString()));
               mSFXProfile[i].setPreload(false);
               return false;
            }
            else
            {// = new SFXProfile(mProfileDesc, mSoundFile, mPreload);
               if (mProfileDesc.mSourceGroup == NULL)
                  mProfileDesc.mSourceGroup = dynamic_cast<SFXSource*>(Sim::findObject("AudioChannelMaster"));
               SFXProfile* trackProfile = new SFXProfile(&mProfileDesc, mSoundPath);
               trackProfile->setDescription(&mProfileDesc);
               trackProfile->setSoundFileName(mSoundPath[0]);
               trackProfile->setPreload(mPreload);

               mSFXProfile[i].setDescription(&mProfileDesc);
               mSFXProfile[i].setSoundFileName(mSoundPath[0]);
               mSFXProfile[i].setPreload(mPreload);

               mPlaylist.mSlots.mTrack[i] = trackProfile;
            }
         }
      }
   }
   else
   {
      if (mSoundPath[0])
      {
         if (!Torque::FS::IsFile(mSoundPath[0]))
         {
            Con::errorf("SoundAsset::initializeAsset: Attempted to load file %s but it was not valid!", mSoundFile[0]);
            mLoadedState = BadFileReference;
            mSFXProfile[0].setDescription(NULL);
            mSFXProfile[0].setSoundFileName(StringTable->insert(StringTable->EmptyString()));
            mSFXProfile[0].setPreload(false);
            return false;
         }
         else
         {// = new SFXProfile(mProfileDesc, mSoundFile, mPreload);
            if (mProfileDesc.mSourceGroup == NULL)
               mProfileDesc.mSourceGroup = dynamic_cast<SFXSource*>(Sim::findObject("AudioChannelMaster"));
            mSFXProfile[0].setDescription(&mProfileDesc);
            mSFXProfile[0].setSoundFileName(mSoundPath[0]);
            mSFXProfile[0].setPreload(mPreload);

            //give it a nudge to preload if required
            mSFXProfile[0].getBuffer();
         }

      }
   }
   mChangeSignal.trigger();
   mLoadedState = Ok;
   return true;
}

//void SoundAsset::setSoundFile(const char* pSoundFile)
//{
//   // Sanity!
//   AssertFatal(pSoundFile != NULL, "Cannot use a NULL sound file.");
//
//   // Fetch sound file.
//   pSoundFile = StringTable->insert(pSoundFile, true);
//
//   // Ignore no change,
//   if (pSoundFile == mSoundFile)
//      return;
//
//   // Update.
//   mSoundFile = getOwned() ? expandAssetFilePath(pSoundFile) : pSoundFile;
//
//   // Refresh the asset.
//   refreshAsset();
//}

StringTableEntry SoundAsset::getAssetIdByFileName(StringTableEntry fileName)
{
   if (fileName == StringTable->EmptyString())
      return StringTable->EmptyString();

   StringTableEntry soundAssetId = StringTable->EmptyString();

   AssetQuery query;
   U32 foundCount = AssetDatabase.findAssetType(&query, "SoundAsset");
   if (foundCount != 0)
   {
      for (U32 i = 0; i < foundCount && soundAssetId == StringTable->EmptyString(); i++)
      {
         SoundAsset* soundAsset = AssetDatabase.acquireAsset<SoundAsset>(query.mAssetList[i]);
         if (soundAsset)
         {
            if (soundAsset->getSoundPath() == fileName)
               soundAssetId = soundAsset->getAssetId();

            AssetDatabase.releaseAsset(query.mAssetList[i]);
         }
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
