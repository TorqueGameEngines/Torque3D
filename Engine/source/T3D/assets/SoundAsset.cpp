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

#ifndef _SFXPROFILE_H_
#include "sfx/sfxProfile.h"
#endif // !_SFXPROFILE_H_

// Debug Profiling.
#include "platform/profiler.h"
#include "sfx/sfxTypes.h"

#include "SoundAssetInspectors.h"
#include "console/typeValidators.h"

//-----------------------------------------------------------------------------

IMPLEMENT_CONOBJECT(SoundAsset);

IMPLEMENT_STRUCT(AssetPtr<SoundAsset>, AssetPtrSoundAsset, , "")
END_IMPLEMENT_STRUCT

ConsoleType(SoundAssetPtr, TypeSoundAssetPtr, AssetPtr<SoundAsset>, ASSET_ID_FIELD_PREFIX)

ConsoleGetType(TypeSoundAssetPtr)
{
   // Fetch asset Id.
   return (*((AssetPtr<SoundAsset>*)dptr)).getAssetId();
}

ConsoleSetType(TypeSoundAssetPtr)
{
   // Was a single argument specified?
   if (argc == 1)
   {
      // Yes, so fetch field value.
      const char* pFieldValue = argv[0];

      // Fetch asset pointer.
      AssetPtr<SoundAsset>* pAssetPtr = dynamic_cast<AssetPtr<SoundAsset>*>((AssetPtrBase*)(dptr));

      // Is the asset pointer the correct type?
      if (pAssetPtr == NULL)
      {
         Con::warnf("(TypeSoundAssetPtrRefactor) - Failed to set asset Id '%d'.", pFieldValue);
         return;
      }

      // Set asset.
      pAssetPtr->setAssetId(pFieldValue);

      return;
   }

   // Warn.
   Con::warnf("(TypeSoundAssetPtrRefactor) - Cannot set multiple args to a single asset.");
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

const String SoundAsset::mErrCodeStrings[] =
{
   "BadProfile",
   "BadDescription",
   "BadBufferData",
   "UnKnown"
};

//-----------------------------------------------------------------------------

SoundAsset::SoundAsset()
   : AssetBase()
{
   dMemset(mPlaylist.mSlots.mReplayMode, 0, sizeof(mPlaylist.mSlots.mReplayMode));
   dMemset(mPlaylist.mSlots.mTransitionIn, 0, sizeof(mPlaylist.mSlots.mTransitionIn));
   dMemset(mPlaylist.mSlots.mRepeatCount, 0, sizeof(mPlaylist.mSlots.mRepeatCount));
   dMemset(mPlaylist.mSlots.mState, 0, sizeof(mPlaylist.mSlots.mState));
   dMemset(mPlaylist.mSlots.mTrack, 0, sizeof(mPlaylist.mSlots.mTrack));
   dMemset(mPlaylist.mSlots.mStateMode, 0, sizeof(mPlaylist.mSlots.mStateMode));

   for (U32 i = 0; i < SFXPlayList::NUM_SLOTS; i++)
   {
      mSoundFile[i] = StringTable->EmptyString();
      mSoundResource[i] = NULL;

      mPlaylist.mSlots.mTransitionOut[i] = SFXPlayList::TRANSITION_Wait;
      mPlaylist.mSlots.mVolumeScale.mValue[i] = 1.f;
      mPlaylist.mSlots.mPitchScale.mValue[i] = 1.f;
      mPlaylist.mSlots.mFadeTimeIn.mValue[i] = -1.f;  // Don't touch by default.
      mPlaylist.mSlots.mFadeTimeOut.mValue[i] = -1.f;  // Don't touch by default.
      mPlaylist.mSlots.mMinDistance.mValue[i] = -1.f;  // Don't touch by default.
      mPlaylist.mSlots.mMaxDistance.mValue[i] = -1.f;  // Don't touch by default.

   }

   mSubtitleString = StringTable->EmptyString();

   mLoadedState = AssetErrCode::NotLoaded;
   mPreload = true;
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
   mProfileDesc.mFadeInTime = 0.0f;
   mProfileDesc.mFadeOutTime = 0.0f;
   mProfileDesc.mFadeLoops = false;
   mProfileDesc.mScatterDistance = Point3F(0.f, 0.f, 0.f);
   mProfileDesc.mStreamPacketSize = 8;
   mProfileDesc.mStreamReadAhead = 3;
   mProfileDesc.mPriority = 1.0f;
   mProfileDesc.mSourceGroup = NULL;
   mProfileDesc.mFadeInEase = EaseF();
   mProfileDesc.mSourceGroup = dynamic_cast<SFXSource*>(Sim::findObject("AudioChannelMaster"));

   dMemset(mProfileDesc.mParameters, 0, sizeof(mProfileDesc.mParameters));
   mIsPlaylist = false;

   mPlaylist.mNumSlotsToPlay = SFXPlayList::SFXPlaylistSettings::NUM_SLOTS;
   mPlaylist.mRandomMode = SFXPlayList::RANDOM_NotRandom;
   mPlaylist.mTrace = false;
   mPlaylist.mLoopMode = SFXPlayList::LOOP_All;
   mPlaylist.mActiveSlots = 1;

   mResolvedTrack = NULL;
   mResolvedDescription = NULL;

}

//-----------------------------------------------------------------------------

SoundAsset::~SoundAsset()
{

   if (mResolvedTrack)
   {
      if (mResolvedTrack->isProperlyAdded() && !mResolvedTrack->isDeleted())
         mResolvedTrack->deleteObject();
   }

   if (mResolvedDescription)
   {
      if (mResolvedDescription->isProperlyAdded() && !mResolvedDescription->isDeleted())
         mResolvedDescription->deleteObject();
   }
}

//-----------------------------------------------------------------------------
void SoundAsset::initPersistFields()
{
   docsURL;
   // Call parent.
   Parent::initPersistFields();
   GROUP("SoundSlots")
   { 
      ARRAY_BEGIN("slots", SFXPlayList::SFXPlaylistSettings::NUM_SLOTS)
         .showWhen(&slotVisible);

         ADD_FIELD("soundFile", TypeAssetLooseFilePath, Offset(mSoundFile, SoundAsset))
            .doc("Path to the sound file.")
            .onSet(&_setSoundFile);

         ADD_FIELD("replay", TYPEID< SFXPlayList::EReplayMode >(), Offset(mPlaylist.mSlots.mReplayMode, SoundAsset))
            .doc("Behavior when an already playing sound is encountered on this slot from a previous cycle.\n"
            "Each slot can have an arbitrary number of sounds playing on it from previous cycles.  This field determines "
            "how SFXController will handle these sources.");

         ADD_FIELD("transitionIn", TYPEID< SFXPlayList::ETransitionMode >(), Offset(mPlaylist.mSlots.mTransitionIn, SoundAsset)) 
            .doc("Behavior when moving into this slot.\n"
            "After the delayIn time has expired (if any), this slot determines what the controller "
            "will do before actually playing the slot.");
         ADD_FIELD("transitionOut", TYPEID< SFXPlayList::ETransitionMode >(), Offset(mPlaylist.mSlots.mTransitionOut, SoundAsset)) 
            .doc("Behavior when moving out of this slot.\n"
            "After the #detailTimeOut has expired (if any), this slot determines what the controller "
            "will do before moving on to the next slot.");
         ADD_FIELD("delayTimeIn", TypeRangedF32, Offset(mPlaylist.mSlots.mDelayTimeIn.mValue, SoundAsset)).validate(&CommonValidators::PositiveFloat) 
            .doc("Seconds to wait after moving into slot before #transitionIn.");
         ADD_FIELD("delayTimeInVariance", TypePoint2F, Offset(mPlaylist.mSlots.mDelayTimeIn.mVariance, SoundAsset)) 
            .doc("Bounds on randomization of #delayTimeIn.\n\n"
            "@ref SFXPlayList_randomization\n");
         ADD_FIELD("delayTimeOut", TypeRangedF32, Offset(mPlaylist.mSlots.mDelayTimeOut.mValue, SoundAsset)).validate(&CommonValidators::PositiveFloat) 
            .doc("Seconds to wait before moving out of slot after #transitionOut.");
         ADD_FIELD("delayTimeOutVariance", TypePoint2F, Offset(mPlaylist.mSlots.mDelayTimeOut.mVariance, SoundAsset)) 
            .doc("Bounds on randomization of #delayTimeOut.\n\n"
            "@ref SFXPlayList_randomization\n");
         ADD_FIELD("fadeTimeIn", TypeRangedF32, Offset(mPlaylist.mSlots.mFadeTimeIn.mValue, SoundAsset)).validate(&CommonValidators::PositiveFloat) 
            .doc("Seconds to fade sound in (-1 to use the track's own fadeInTime.)\n"
            "@see SFXDescription::fadeTimeIn");
         ADD_FIELD("fadeTimeInVariance", TypePoint2F, Offset(mPlaylist.mSlots.mFadeTimeIn.mVariance, SoundAsset)) 
            .doc("Bounds on randomization of #fadeInTime.\n\n"
            "@ref SFXPlayList_randomization\n");
         ADD_FIELD("fadeTimeOut", TypeRangedF32, Offset(mPlaylist.mSlots.mFadeTimeOut.mValue, SoundAsset)).validate(&CommonValidators::PositiveFloat) 
            .doc("Seconds to fade sound out (-1 to use the track's own fadeOutTime.)\n"
            "@see SFXDescription::fadeTimeOut");
         ADD_FIELD("fadeTimeOutVariance", TypePoint2F, Offset(mPlaylist.mSlots.mFadeTimeOut.mVariance, SoundAsset)) 
            .doc("Bounds on randomization of #fadeOutTime\n\n"
            "@ref SFXPlayList_randomization\n");
         ADD_FIELD("referenceDistance", TypeRangedF32, Offset(mPlaylist.mSlots.mMinDistance.mValue, SoundAsset)).validate(&CommonValidators::PositiveFloat) 
            .doc("@c referenceDistance to set for 3D sounds in this slot (<1 to use @c referenceDistance of track's own description).\n"
            "@see SFXDescription::referenceDistance");
         ADD_FIELD("referenceDistanceVariance", TypePoint2F, Offset(mPlaylist.mSlots.mMinDistance.mVariance, SoundAsset)) 
            .doc("Bounds on randomization of #referenceDistance.\n\n"
            "@ref SFXPlayList_randomization\n");
         ADD_FIELD("maxSlotDistance", TypeRangedF32, Offset(mPlaylist.mSlots.mMaxDistance.mValue, SoundAsset)).validate(&CommonValidators::PositiveFloat) 
            .doc("@c maxDistance to apply to 3D sounds in this slot (<1 to use @c maxDistance of track's own description).\n"
            "@see SFXDescription::maxDistance");
         ADD_FIELD("maxSlotDistanceVariance", TypePoint2F, Offset(mPlaylist.mSlots.mMaxDistance.mVariance, SoundAsset)) 
            .doc("Bounds on randomization of #maxDistance.\n\n"
            "@ref SFXPlayList_randomization\n");
         ADD_FIELD("volumeScale", TypeRangedF32, Offset(mPlaylist.mSlots.mVolumeScale.mValue, SoundAsset)).validate(&CommonValidators::PositiveFloat) 
            .doc("Scale factor to apply to volume of sounds played on this list slot.\n"
            "This value will scale the actual volume level set on the track assigned to the slot, i.e. a value of 0.5 will "
            "cause the track to play at half-volume.");
         ADD_FIELD("volumeScaleVariance", TypePoint2F, Offset(mPlaylist.mSlots.mVolumeScale.mVariance, SoundAsset)) 
            .doc("Bounds on randomization of #volumeScale.\n\n"
            "@ref SFXPlayList_randomization\n");
         ADD_FIELD("pitchScale", TypeRangedF32, Offset(mPlaylist.mSlots.mPitchScale.mValue, SoundAsset)).validate(&CommonValidators::PositiveFloat) 
            .doc("Scale factor to apply to pitch of sounds played on this list slot.\n"
            "This value will scale the actual pitch set on the track assigned to the slot, i.e. a value of 0.5 will "
            "cause the track to play at half its assigned speed.");
         ADD_FIELD("pitchScaleVariance", TypePoint2F, Offset(mPlaylist.mSlots.mPitchScale.mVariance, SoundAsset)) 
            .doc("Bounds on randomization of #pitchScale.\n\n"
            "@ref SFXPlayList_randomization\n");
         ADD_FIELD("repeatCount", TypeRangedS32, Offset(mPlaylist.mSlots.mRepeatCount, SoundAsset)).validate(&CommonValidators::PositiveInt) 
            .doc("Number of times to loop this slot.");
         ADD_FIELD("state", TypeSFXStateName, Offset(mPlaylist.mSlots.mState, SoundAsset)) 
            .doc("State that must be active for this slot to play.\n\n"
            "@ref SFXPlayList_states");
         ADD_FIELD("stateMode", TYPEID< SFXPlayList::EStateMode >(), Offset(mPlaylist.mSlots.mStateMode, SoundAsset)) 
            .doc("Behavior when assigned state is deactivated while slot is playing.\n\n"
            "@ref SFXPlayList_states");

      ARRAY_END("slots");
   }

   GROUP("General Profile")
   {
      ADD_FIELD("pitchAdjust", TypeRangedF32, Offset(mProfileDesc.mPitch, SoundAsset))
         .doc("Adjustment of the pitch value 1 is default.")
         .validate(&CommonValidators::PositiveFloat);

      ADD_FIELD("volumeAdjust", TypeRangedF32, Offset(mProfileDesc.mVolume, SoundAsset))
         .doc("Adjustment to the volume.")
         .validate(&CommonValidators::PositiveFloat);

      ADD_FIELD("is3D", TypeBool, Offset(mProfileDesc.mIs3D, SoundAsset)).doc("Set this sound to 3D.");
      ADD_FIELD("isLooping", TypeBool, Offset(mProfileDesc.mIsLooping, SoundAsset)).doc("Does this sound loop.");
      // if streaming, a default packet size should be chosen for all sounds.
      ADD_FIELD("isStreaming", TypeBool, Offset(mProfileDesc.mIsStreaming, SoundAsset)).doc("Use streaming.");
      //....why?
      ADD_FIELD("useHardware", TypeBool, Offset(mProfileDesc.mUseHardware, SoundAsset)).doc("Use hardware mixing for this sound.");
      ADD_FIELD("sourceGroup", TypeSFXSourceName, Offset(mProfileDesc.mSourceGroup, SoundAsset)).doc("Group that sources playing with this description should be put into.");
      ADD_FIELD("preload", TypeBool, Offset(mPreload, SoundAsset)).doc("Whether to preload sound data when the profile is added to system.");
   }

   GROUP("Fading")
   {
      ADD_FIELD("fadeInTime", TypeRangedF32, Offset(mProfileDesc.mFadeInTime, SoundAsset))
         .validate(&CommonValidators::PositiveFloat)
         .doc("Number of seconds to gradually fade in volume from zero when playback starts.");

      ADD_FIELD("fadeOutTime", TypeRangedF32, Offset(mProfileDesc.mFadeOutTime, SoundAsset))
         .validate(&CommonValidators::PositiveFloat)
         .doc("Number of seconds to gradually fade out volume down to zero when playback is stopped or paused.");

      ADD_FIELD("fadeInEase", TypeEaseF, Offset(mProfileDesc.mFadeInEase, SoundAsset)).doc("Easing curve for fade-in transition.");
      ADD_FIELD("fadeOutEase", TypeEaseF, Offset(mProfileDesc.mFadeOutEase, SoundAsset)).doc("Easing curve for fade-out transition.");
      ADD_FIELD("fadeLoops", TypeBool, Offset(mProfileDesc.mFadeLoops, SoundAsset)).doc("Fade each cycle of a loop in and/or out; otherwise only fade-in first cycle.");
   }

   GROUP("3D")
   {
      ADD_FIELD("minDistance", TypeRangedF32, Offset(mProfileDesc.mMinDistance, SoundAsset)).validate(&CommonValidators::PositiveFloat).doc("Minimum distance for sound.");
      ADD_FIELD("maxDistance", TypeRangedF32, Offset(mProfileDesc.mMaxDistance, SoundAsset)).validate(&CommonValidators::PositiveFloat).doc("Max distance for sound.");
      ADD_FIELD("coneInsideAngle", TypeRangedS32, Offset(mProfileDesc.mConeInsideAngle, SoundAsset)).validate(&CommonValidators::S32_PosDegreeRange).doc("Cone inside angle.");
      ADD_FIELD("coneOutsideAngle", TypeRangedS32, Offset(mProfileDesc.mConeOutsideAngle, SoundAsset)).validate(&CommonValidators::S32_PosDegreeRange).doc("Cone outside angle.");
      ADD_FIELD("coneOutsideVolume", TypeRangedF32, Offset(mProfileDesc.mConeOutsideVolume, SoundAsset)).validate(&CommonValidators::NormalizedFloat).doc("Cone outside volume.");
      ADD_FIELD("rolloffFactor", TypeRangedF32, Offset(mProfileDesc.mRolloffFactor, SoundAsset)).validate(&CommonValidators::NegDefaultF32).doc("Rolloff factor.");
      ADD_FIELD("scatterDistance", TypePoint3F, Offset(mProfileDesc.mScatterDistance, SoundAsset)).doc("Randomization to the spacial position of the sound.");
   }

   GROUP("Playlist settings")
   {
      ADD_FIELD("random", TYPEID< SFXPlayList::ERandomMode >(), Offset(mPlaylist.mRandomMode, SoundAsset)).doc("Slot playback order randomization pattern.");
      ADD_FIELD("loopMode", TYPEID< SFXPlayList::ELoopMode >(), Offset(mPlaylist.mLoopMode, SoundAsset)).doc("Behavior when description has looping enabled.");
      ADD_FIELD("numSlotsToPlay", TypeRangedS32, Offset(mPlaylist.mNumSlotsToPlay, SoundAsset)).validate(&playlistSlotRange).doc("Number of slots to play.");
      ADD_FIELD("trace", TypeBool, Offset(mPlaylist.mTrace, SoundAsset)).doc("Enable/disable execution tracing for this playlist (local only).");
   }
}

//------------------------------------------------------------------------------

void SoundAsset::onRemove()
{
   for (U32 i = 0; i < SFXPlayList::SFXPlaylistSettings::NUM_SLOTS; i++)
   {
      if (mSoundFile[i] == StringTable->EmptyString())
         break;

      Torque::FS::RemoveChangeNotification(mSoundFile[i], this, &SoundAsset::_onResourceChanged);
   }

   Parent::onRemove();
}

void SoundAsset::inspectPostApply()
{
   Parent::inspectPostApply();

   refreshAsset();
}

void SoundAsset::copyTo(SimObject* object)
{
   // Call to parent.
   Parent::copyTo(object);

}

void SoundAsset::initializeAsset(void)
{
   Parent::initializeAsset();

   for (U32 i = 0; i < SFXPlayList::SFXPlaylistSettings::NUM_SLOTS; i++)
   {
      if (i == 0 && mSoundFile[i] == StringTable->EmptyString())
         return;

      if (mSoundFile[i] == StringTable->EmptyString())
         break;

      mSoundFile[i] = expandAssetFilePath(mSoundFile[i]);
      if (getOwned())
         Torque::FS::AddChangeNotification(mSoundFile[i], this, &SoundAsset::_onResourceChanged);
   }

   populateSFXTrack();
}

void SoundAsset::_onResourceChanged(const Torque::Path& path)
{
   for (U32 i = 0; i < SFXPlayList::NUM_SLOTS; i++)
   {

      if (path != Torque::Path(mSoundFile[i]))
         return;
   }

   refreshAsset();
}

void SoundAsset::onAssetRefresh(void)
{
   if (!isProperlyAdded())
      return;

   Parent::onAssetRefresh();

   populateSFXTrack();
}

U32 SoundAsset::load()
{
   if (mLoadedState == AssetErrCode::Ok)
      return mLoadedState;

   if (!mResolvedTrack)
   {
      if (mIsPlaylist)
      {
         mResolvedTrack = buildPlaylist();
      }
      else
      {
         mResolvedTrack = buildProfile();
      }

      mResolvedTrack->registerObject(String::ToString("%s_profile_track", getAssetName()).c_str());
   }

   mLoadedState = Ok;
   return mLoadedState;
}

bool SoundAsset::slotVisible(void* object, const char* index)
{
   S32 idx = index ? dAtoi(index) : 0;
   if (idx == 0) return true;

   SoundAsset* sa = static_cast<SoundAsset*>(object);
   if (!sa)
      return false;

   return sa->mSoundFile[idx - 1] != NULL && sa->mSoundFile[idx - 1][0] != '\0';
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
      for (U32 i = 0; i < foundCount && soundAssetId == StringTable->EmptyString(); i++)
      {
         SoundAsset* soundAsset = AssetDatabase.acquireAsset<SoundAsset>(query.mAssetList[i]);
         if (soundAsset)
         {
            if (soundAsset->getSoundFile() == fileName)
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

U32 SoundAsset::getAssetByFilename(StringTableEntry fileName, AssetPtr<SoundAsset>* soundAsset)
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
         if (tSoundAsset && tSoundAsset->getSoundFile() == fileName)
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

void SoundAsset::buildDescription()
{
   if (!mResolvedDescription)
   {
      mResolvedDescription = new SFXDescription;
      // calls on add which should validate the description. but do it on mProfileDesc before applying values anyway.
      mResolvedDescription->registerObject(String::ToString("%s_profile_description", getAssetName()).c_str());
   }

   mProfileDesc.validate();

   mResolvedDescription->mPitch = mProfileDesc.mPitch;
   mResolvedDescription->mVolume = mProfileDesc.mVolume;
   mResolvedDescription->mIs3D = mProfileDesc.mIs3D;
   mResolvedDescription->mIsLooping = mProfileDesc.mIsLooping;
   mResolvedDescription->mIsStreaming = mProfileDesc.mIsStreaming;
   mResolvedDescription->mUseHardware = mProfileDesc.mUseHardware;
   mResolvedDescription->mMinDistance = mProfileDesc.mMinDistance;
   mResolvedDescription->mMaxDistance = mProfileDesc.mMaxDistance;
   mResolvedDescription->mConeInsideAngle = mProfileDesc.mConeInsideAngle;
   mResolvedDescription->mConeOutsideAngle = mProfileDesc.mConeOutsideAngle;
   mResolvedDescription->mConeOutsideVolume = mProfileDesc.mConeOutsideVolume;
   mResolvedDescription->mRolloffFactor = mProfileDesc.mRolloffFactor;
   mResolvedDescription->mFadeInTime = mProfileDesc.mFadeInTime;
   mResolvedDescription->mFadeOutTime = mProfileDesc.mFadeOutTime;
   mResolvedDescription->mFadeLoops = mProfileDesc.mFadeLoops;
   mResolvedDescription->mScatterDistance = mProfileDesc.mScatterDistance;
   mResolvedDescription->mStreamPacketSize = mProfileDesc.mStreamPacketSize;
   mResolvedDescription->mStreamReadAhead = mProfileDesc.mStreamReadAhead;
   mResolvedDescription->mPriority = mProfileDesc.mPriority;
   mResolvedDescription->mSourceGroup = mProfileDesc.mSourceGroup;
   mResolvedDescription->mFadeInEase = mProfileDesc.mFadeInEase;
   mResolvedDescription->mSourceGroup = mProfileDesc.mSourceGroup;
}

SFXProfile* SoundAsset::buildProfile()
{
   SFXProfile* profile = new SFXProfile(mResolvedDescription, mSoundFile[0], mPreload);
   mSoundResource[0] = profile->getResource();
   return profile;
}

//-----------------------------------------------------------------------------
//  BUILD PLAYLIST
//-----------------------------------------------------------------------------

SFXPlayList* SoundAsset::buildPlaylist()
{
   SFXPlayList* pl = new SFXPlayList();

   pl->mRandomMode = mPlaylist.mRandomMode;
   pl->mLoopMode = mPlaylist.mLoopMode;
   pl->mNumSlotsToPlay = mPlaylist.mNumSlotsToPlay;
   pl->mTrace = mPlaylist.mTrace;
   pl->mSlots = mPlaylist.mSlots;

   // Build child tracks for each valid slot
   for (U32 i = 0; i < SFXPlayList::SFXPlaylistSettings::NUM_SLOTS; ++i)
   {
      if (mSoundFile[i] == StringTable->EmptyString())
         continue;

      // Build child SFXProfile
      SFXProfile* child = new SFXProfile(mResolvedDescription, mSoundFile[i], mPreload);
      mSoundResource[i] = child->getResource();
      pl->mSlots.mTrack[i] = child;
   }

   return pl;
}

void SoundAsset::populateSFXTrack(void)
{
   U32 count = 0;
   for (U32 i = 0; i < SFXPlayList::SFXPlaylistSettings::NUM_SLOTS; ++i)
   {
      if (mSoundFile[i] != StringTable->EmptyString())
      {
         if (!Torque::FS::IsFile(mSoundFile[i]))
         {
            mLoadedState = AssetErrCode::BadFileReference;
            return;
         }

         ++count;
      }
   }

   mIsPlaylist = (count > 1);

   buildDescription();

   if (mResolvedTrack && mResolvedDescription)
   {
      if (SFX)
         SFX->notifyDescriptionChanged(mResolvedDescription);

      return;
   }

   mResolvedTrack = NULL;

   // reset loaded state.
   mLoadedState = AssetErrCode::NotLoaded;
}

void SoundAsset::setSoundFile(StringTableEntry pSoundFile, U32 slot)
{
   AssertFatal(pSoundFile != NULL, "Cannot use a NULL sound file.");

   pSoundFile = StringTable->insert(pSoundFile);

   if (pSoundFile == mSoundFile[slot])
      return;

   mSoundFile[slot] = getOwned() ? expandAssetFilePath(pSoundFile) : StringTable->insert(pSoundFile);;

   refreshAsset();
}

void SoundAsset::onTamlPreWrite(void)
{
   // Call parent.
   Parent::onTamlPreWrite();

   for (U32 i = 0; i < SFXPlayList::SFXPlaylistSettings::NUM_SLOTS; i++)
   {
      if (mSoundFile[i] == StringTable->EmptyString())
         break;

      mSoundFile[i] = collapseAssetFilePath(mSoundFile[i]);
   }
}

void SoundAsset::onTamlPostWrite(void)
{
   for (U32 i = 0; i < SFXPlayList::SFXPlaylistSettings::NUM_SLOTS; i++)
   {
      if (mSoundFile[i] == StringTable->EmptyString())
         break;

      mSoundFile[i] = expandAssetFilePath(mSoundFile[i]);
   }
}

void SoundAsset::onTamlCustomWrite(TamlCustomNodes& customNodes)
{
   // Debug Profiling.
   PROFILE_SCOPE(SoundAsset_OnTamlCustomWrite);

   // Call parent.
   Parent::onTamlCustomRead(customNodes);
}

void SoundAsset::onTamlCustomRead(const TamlCustomNodes& customNodes)
{
   // Debug Profiling.
   PROFILE_SCOPE(SoundAsset_OnTamlCustomRead);

   // Call parent.
   Parent::onTamlCustomRead(customNodes);
}

DefineEngineMethod(SoundAsset, getSoundPath, const char*, (), , "")
{
   return object->getSoundFile();
}

DefineEngineMethod(SoundAsset, playSound, S32, (Point3F position), (Point3F::Zero),
   "Plays the sound for this asset.\n"
   "@return (sound plays).\n")
{
   if (object->getSFXTrack())
   {
      MatrixF transform;
      transform.setPosition(position);
      SFXSource* source;
      if (position == Point3F::Zero && !object->is3D())
      {
         source = SFX->playOnce(object->getSFXTrack());
      }
      else
      {
         if (position == Point3F::Zero)
            transform = SFX->getListener().getTransform();
         source = SFX->playOnce(object->getSFXTrack(), &transform, NULL, -1);
      }

      if (source)
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

GuiControl* GuiInspectorTypeSoundAssetPtr::constructEditControl()
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
