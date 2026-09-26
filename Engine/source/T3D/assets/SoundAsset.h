#pragma once
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
#define SOUND_ASSET_H

#ifndef _ASSET_BASE_H_
#include "assets/assetBase.h"
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

#ifndef _BITSTREAM_H_
#include "core/stream/bitStream.h"
#endif

#ifndef _SFXRESOURCE_H_
#include "sfx/sfxResource.h"
#endif

#ifndef _SFXDESCRIPTION_H_
#include "sfx/sfxDescription.h"
#endif // !_SFXDESCRIPTION_H_


#ifndef _SFXTRACK_H_
#include "sfx/sfxTrack.h"
#endif

#ifndef _SFXPROFILE_H_
#include "sfx/sfxProfile.h"
#endif // !_SFXPROFILE_H_

#ifndef _RESOURCEMANAGER_H_
#include "core/resourceManager.h"
#endif

#ifndef _SFXPLAYLIST_H_
#include "sfx/sfxPlayList.h"
#endif

#ifndef _SFXTYPES_H_
#include "sfx/sfxTypes.h"
#endif

#include "assetMacroHelpers.h"
class SFXResource;
class SFXPlayList;

//-----------------------------------------------------------------------------
class SoundAsset : public AssetBase
{
   typedef AssetBase Parent;
   typedef AssetPtr<SoundAsset> ConcreteAssetPtr;

protected:

   //SFXPlayList::SlotData   mSlots;

   /*These will be needed in the refactor!
   Resource<SFXResource>   mSoundResource;


   // SFXDesctriptions, some off these will be removed
   F32                     mPitchAdjust;
   F32                     mVolumeAdjust;
   bool                    mIs3D;
   bool                    mLoop;
   bool                    mIsStreaming;
   bool                    mUseHardware;

   F32                     mMinDistance;
   F32                     mMaxDistance;
   U32                     mConeInsideAngle;
   U32                     mConeOutsideAngle;
   F32                     mConeOutsideVolume;
   F32                     mRolloffFactor;
   Point3F                 mScatterDistance;
   F32                     mPriority;
   */

public:
   enum SoundAssetErrCode
   {
      BadProfile = AssetErrCode::Extended,
      BadDescription,
      BadBufferData,
      Extended
   };

   static const String mErrCodeStrings[U32(SoundAssetErrCode::Extended) - U32(Parent::Extended) + 1];
   static U32 getAssetErrCode(ConcreteAssetPtr checkAsset) { if (checkAsset) return checkAsset->mLoadedState; else return 0; }

   static String getAssetErrstrn(U32 errCode)
   {
      if (errCode < Parent::Extended) return Parent::getAssetErrstrn(errCode);
      if (errCode > SoundAssetErrCode::Extended) return "undefined error";
      return mErrCodeStrings[errCode - Parent::Extended];
   };

private:
   StringTableEntry        mSoundFile[SFXPlayList::SFXPlaylistSettings::NUM_SLOTS];
   Resource<SFXResource>   mSoundResource[SFXPlayList::SFXPlaylistSettings::NUM_SLOTS];

   SFXDescription          mProfileDesc;

   SFXPlayList             mPlaylist;
   // subtitles
   StringTableEntry        mSubtitleString;
   bool                    mPreload;
   bool                    mIsPlaylist;
   SFXTrack* mResolvedTrack;
   SFXDescription* mResolvedDescription;

public:
   SoundAsset();
   virtual ~SoundAsset();

   /// Engine.
   static void initPersistFields();
   void onRemove() override;
   void inspectPostApply() override;
   void copyTo(SimObject* object) override;

   //SFXResource* getSound() { return mSoundResource; }
   Resource<SFXResource> getSoundResource(const U32 slotId = 0) { load(); return mSoundResource[slotId]; }

   /// Declare Console Object.
   DECLARE_CONOBJECT(SoundAsset);
   
   static bool slotVisible(void* object, const char* index);
   U32 load() override;
#ifdef TORQUE_TOOLS
   U32 getAssetMemoryUsage() const override;
#endif

   void                    setSoundFile(StringTableEntry pSoundFile, U32 slot = 0);
   inline StringTableEntry getSoundFile(U32 slot = 0) { return mSoundFile[slot]; }
   inline StringTableEntry getRelativeSoundFile(U32 slot = 0) { return collapseAssetFilePath(mSoundFile[slot]); }

   SFXTrack* getSFXTrack() { load(); return mResolvedTrack; }
   SFXDescription* getSfxDescription() { return mResolvedDescription ? mResolvedDescription : &mProfileDesc; }
   bool isPlaylist() { return mIsPlaylist; }

   bool isLoop() { return mProfileDesc.mIsLooping; }
   bool is3D() { return mProfileDesc.mIs3D; }

   static StringTableEntry getAssetIdByFileName(StringTableEntry fileName);
   static U32 getAssetById(StringTableEntry assetId, AssetPtr<SoundAsset>* materialAsset);
   static U32 getAssetByFilename(StringTableEntry fileName, AssetPtr<SoundAsset>* matAsset);

   void        buildDescription();
   SFXProfile* buildProfile();
   SFXPlayList* buildPlaylist();

   void populateSFXTrack(void);

protected:
   // Asset Base callback
   void  initializeAsset(void) override;
   void  _onResourceChanged(const Torque::Path& path);
   void  onAssetRefresh(void) override;

   /// Taml callbacks.
   void onTamlPreWrite(void) override;
   void onTamlPostWrite(void) override;
   void onTamlCustomWrite(TamlCustomNodes& customNodes) override;
   void onTamlCustomRead(const TamlCustomNodes& customNodes) override;

protected:
   static bool _setSoundFile(void* obj, const char* index, const char* data) { U32 idx = 0; if (index) idx = dAtoi(index); static_cast<SoundAsset*>(obj)->setSoundFile(data, idx); return false; }

};

DECLARE_STRUCT(AssetPtr<SoundAsset>)
DefineConsoleType(TypeSoundAssetPtr, SoundAsset)
DefineConsoleType(TypeSoundAssetId, String)
DECLARE_STRUCT(AssetRef<SoundAsset>)
DefineConsoleType(TypeSoundAssetRef, AssetRef<SoundAsset>)

#endif // _ASSET_BASE_H_

