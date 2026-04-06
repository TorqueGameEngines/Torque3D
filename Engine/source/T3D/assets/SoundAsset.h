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

   // asset Base load
   U32 load() override;

   void                    setSoundFile(StringTableEntry pSoundFile, U32 slot = 0);
   inline StringTableEntry getSoundFile(U32 slot = 0) { return mSoundFile[slot]; }
   inline StringTableEntry getRelativeSoundFile(U32 slot = 0) { return collapseAssetFilePath(mSoundFile[slot]); }

   SFXTrack* getSFXTrack() { load(); return mResolvedTrack; }
   SFXDescription* getSfxDescription() { return mResolvedDescription ? mResolvedDescription : &mProfileDesc; }
   bool isPlaylist() { return mIsPlaylist; }

   bool isLoop() { return mProfileDesc.mIsLooping; }
   bool is3D() { return mProfileDesc.mIs3D; }

   static StringTableEntry getAssetIdByFilename(StringTableEntry fileName);
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

DefineConsoleType(TypeSoundAssetPtr, SoundAsset)
DefineConsoleType(TypeSoundAssetId, String)

#define DECLARE_SOUNDASSET(className, name)                                                                                                                                   \
private:                                                                                                                                                                      \
   AssetPtr<SoundAsset> m##name##Asset;                                                                                                                                       \
   StringTableEntry     m##name##File  = StringTable->EmptyString();                                                                                                          \
public:                                                                                                                                                                       \
   void _set##name(StringTableEntry _in){                                                                                                                                     \
      if(m##name##Asset.getAssetId() == _in)                                                                                                                                  \
         return;                                                                                                                                                              \
      if(get##name##File() == _in)                                                                                                                                            \
         return;                                                                                                                                                              \
      if(_in == NULL || !String::compare(_in,StringTable->EmptyString()))                                                                                                     \
      {                                                                                                                                                                       \
         m##name##Asset = NULL;                                                                                                                                               \
         m##name##File = "";                                                                                                                                                  \
         return;                                                                                                                                                              \
      }                                                                                                                                                                       \
      if(!AssetDatabase.isDeclaredAsset(_in))                                                                                                                                 \
      {                                                                                                                                                                       \
         StringTableEntry soundAssetId = StringTable->EmptyString();                                                                                                          \
         AssetQuery query;                                                                                                                                                    \
         S32 foundAssetcount = AssetDatabase.findAssetLooseFile(&query, _in);                                                                                                 \
         if (foundAssetcount != 0)                                                                                                                                            \
         {                                                                                                                                                                    \
            soundAssetId = query.mAssetList[0];                                                                                                                               \
         }                                                                                                                                                                    \
         else if(Torque::FS::IsFile(_in))                                                                                                                                     \
         {                                                                                                                                                                    \
            soundAssetId = SoundAsset::getAssetIdByFilename(_in);                                                                                                             \
            if (soundAssetId == StringTable->EmptyString())                                                                                                                   \
            {                                                                                                                                                                 \
               SoundAsset* privateSound = new SoundAsset();                                                                                                                   \
               privateSound->setSoundFile(_in);                                                                                                                               \
               soundAssetId = AssetDatabase.addPrivateAsset(privateSound);                                                                                                    \
            }                                                                                                                                                                 \
         }                                                                                                                                                                    \
         else                                                                                                                                                                 \
         {                                                                                                                                                                    \
            Con::warnf("%s::%s: Could not find asset for: %s, there is no fallback for sound assets.", #className, #name, _in);                                               \
            soundAssetId = StringTable->EmptyString();                                                                                                                        \
         }                                                                                                                                                                    \
         m##name##Asset = soundAssetId;                                                                                                                                       \
         m##name##File = _in;                                                                                                                                                 \
      }                                                                                                                                                                       \
      else                                                                                                                                                                    \
      {                                                                                                                                                                       \
         m##name##Asset = _in;                                                                                                                                                \
         m##name##File = get##name##File();                                                                                                                                   \
      }                                                                                                                                                                       \
   };                                                                                                                                                                         \
                                                                                                                                                                              \
   inline StringTableEntry _get##name(void) const { return m##name##Asset.getAssetId(); }                                                                                     \
   AssetPtr<SoundAsset> get##name##Asset(void) { return m##name##Asset; }                                                                                                     \
   static bool _set##name##Data(void* obj, const char* index, const char* data) { static_cast<className*>(obj)->_set##name(_getStringTable()->insert(data)); return false;}   \
   StringTableEntry get##name##File(){ return m##name##Asset.notNull() ? m##name##Asset->getSoundFile() : ""; }                                                               \
   bool is##name##Valid() { return (get##name##File() != StringTable->EmptyString() && m##name##Asset && m##name##Asset->getStatus() == AssetBase::Ok); }                     \
   SFXDescription* get##name##Description()                                                                                                                                   \
   {                                                                                                                                                                          \
      if (m##name##Asset.notNull())                                                                                                                                           \
         return m##name##Asset->getSfxDescription();                                                                                                                          \
      return NULL;                                                                                                                                                            \
   }                                                                                                                                                                          \
   SimObjectPtr<SFXTrack> get##name##SFXTrack(){ return m##name##Asset.notNull() ? m##name##Asset->getSFXTrack() : NULL; }                                                    \
   SimObjectPtr<SFXTrack> get##name##Profile(){ return get##name##SFXTrack(); }

#define INITPERSISTFIELD_SOUNDASSET(name, consoleClass, docs)                                                                                                                 \
   addProtectedField(#name, TypeSoundFilename, Offset(m##name##File, consoleClass), _set##name##Data, &defaultProtectedGetFn, assetDoc(name, file docs.), AbstractClassRep::FIELD_HideInInspectors); \
   addProtectedField(assetText(name, Asset), TypeSoundAssetPtr, Offset(m##name##Asset, consoleClass), _set##name##Data, &defaultProtectedGetFn, assetDoc(name, asset docs.)); \
   addProtectedField(assetText(name, File), TypeSoundFilename, Offset(m##name##File, consoleClass), _set##name##Data, &defaultProtectedGetFn, assetDoc(name, file docs.), AbstractClassRep::FIELD_HideInInspectors);

//network send - datablock
#define PACKDATA_SOUNDASSET(name)\
   if (stream->writeFlag(m##name##Asset.notNull()))\
   {\
      stream->writeString(m##name##Asset.getAssetId());\
   }\
   else\
   {\
      if(stream->writeFlag(Sim::findObject(m##name##Name)))\
      {\
         SFXTrack* sndTrack = get##name##Profile();\
         stream->writeRangedU32(SimObjectId(sndTrack->getId()), DataBlockObjectIdFirst, DataBlockObjectIdLast);\
         sfxWrite(stream, sndTrack);\
      }\
      else\
      {\
         stream->writeString(m##name##Name);\
      }\
   }


//network recieve - datablock
#define UNPACKDATA_SOUNDASSET(name)\
   if (stream->readFlag())\
   {\
      m##name##AssetId = stream->readSTString();\
      _set##name(m##name##AssetId);\
   }\
   else\
   {\
      if(stream->readFlag())\
      {\
         String errorStr;\
         m##name##SFXId = stream->readRangedU32( DataBlockObjectIdFirst, DataBlockObjectIdLast );\
         sfxReadAndResolve(stream, &m##name##Profile, errorStr);\
         Con::errorf("%s", errorStr.c_str());\
      }\
      else\
      {\
         m##name##Name = stream->readSTString(); \
         _set##name(m##name##Name); \
      }\
   }

#pragma endregion

#pragma region Arrayed Asset Macros

#define INIT_SOUNDASSET_ARRAY(name, index) \
{\
   m##name##Name[index] = StringTable->EmptyString(); \
   m##name##AssetId[index] = StringTable->EmptyString(); \
   m##name##Asset[index] = NULL;\
   m##name[index] = NULL;\
   m##name##Profile[index] = NULL;\
   m##name##SFXId[index] = 0;\
}

#define DECLARE_SOUNDASSET_ARRAY(className,name,max)\
private:                                                                                                                                                                      \
   AssetPtr<SoundAsset> m##name##Asset[max];                                                                                                                                  \
   StringTableEntry     m##name##File[max] = {StringTable->EmptyString() };                                                                                                   \
public:                                                                                                                                                                       \
void _set##name(StringTableEntry _in, const U32& index){                                                                                                                      \
      if(m##name##Asset[index].getAssetId() == _in)                                                                                                                           \
         return;                                                                                                                                                              \
      if(get##name##File(index) == _in)                                                                                                                                       \
         return;                                                                                                                                                              \
      if(_in == NULL || !String::compare(_in,StringTable->EmptyString()))                                                                                                     \
      {                                                                                                                                                                       \
         m##name##Asset[index] = NULL;                                                                                                                                        \
         m##name##File[index] = "";                                                                                                                                           \
         return;                                                                                                                                                              \
      }                                                                                                                                                                       \
      if(!AssetDatabase.isDeclaredAsset(_in))                                                                                                                                 \
      {                                                                                                                                                                       \
         StringTableEntry soundAssetId = StringTable->EmptyString();                                                                                                          \
         AssetQuery query;                                                                                                                                                    \
         S32 foundAssetcount = AssetDatabase.findAssetLooseFile(&query, _in);                                                                                                 \
         if (foundAssetcount != 0)                                                                                                                                            \
         {                                                                                                                                                                    \
            soundAssetId = query.mAssetList[0];                                                                                                                               \
         }                                                                                                                                                                    \
         else if(Torque::FS::IsFile(_in))                                                                                                                                     \
         {                                                                                                                                                                    \
            soundAssetId = SoundAsset::getAssetIdByFilename(_in);                                                                                                             \
            if (soundAssetId == StringTable->EmptyString())                                                                                                                   \
            {                                                                                                                                                                 \
               SoundAsset* privateSound = new SoundAsset();                                                                                                                   \
               privateSound->setSoundFile(_in);                                                                                                                               \
               soundAssetId = AssetDatabase.addPrivateAsset(privateSound);                                                                                                    \
            }                                                                                                                                                                 \
         }                                                                                                                                                                    \
         else                                                                                                                                                                 \
         {                                                                                                                                                                    \
            Con::warnf("%s::%s: Could not find asset for: %s, there is no fallback for sound assets.", #className, #name, _in);                                               \
            soundAssetId = StringTable->EmptyString();                                                                                                                        \
         }                                                                                                                                                                    \
         m##name##Asset[index] = soundAssetId;                                                                                                                                \
         m##name##File[index] = _in;                                                                                                                                          \
      }                                                                                                                                                                       \
      else                                                                                                                                                                    \
      {                                                                                                                                                                       \
         m##name##Asset[index] = _in;                                                                                                                                         \
         m##name##File[index] = get##name##File(index);                                                                                                                       \
      }                                                                                                                                                                       \
   };                                                                                                                                                                         \
                                                                                                                                                                              \
   inline StringTableEntry _get##name(const U32& index) const { return m##name##Asset[index].getAssetId(); }                                                                  \
   AssetPtr<SoundAsset> get##name##Asset(const U32& index) { return m##name##Asset[index]; }                                                                                  \
   static bool _set##name##Data(void* obj, const char* index, const char* data) { static_cast<className*>(obj)->_set##name(_getStringTable()->insert(data), dAtoi(index)); return false; }   \
   StringTableEntry get##name##File(const U32& index) { return m##name##Asset[index].notNull() ? m##name##Asset[index]->getSoundFile() : ""; }                                \
   bool is##name##Valid(const U32& id) {return (get##name##File(id) != StringTable->EmptyString() && m##name##Asset[id] && m##name##Asset[id]->getStatus() == AssetBase::Ok); } \
   SFXDescription* get##name##Description(const U32& index)                                                                                                                   \
   {                                                                                                                                                                          \
      if (m##name##Asset[index].notNull())                                                                                                                                    \
         return m##name##Asset[index]->getSfxDescription();                                                                                                                   \
      return NULL;                                                                                                                                                            \
   }                                                                                                                                                                          \
   SimObjectPtr<SFXTrack> get##name##SFXTrack(const U32& index) { return m##name##Asset[index].notNull() ? m##name##Asset[index]->getSFXTrack() : NULL; }                     \
   SimObjectPtr<SFXTrack> get##name##Profile(const U32& index){ return get##name##SFXTrack(index); }


#define INITPERSISTFIELD_SOUNDASSET_ARRAY(name, arraySize, consoleClass, docs) \
   addProtectedField(#name, TypeSoundFilename, Offset(m##name##File, consoleClass), _set##name##Data, &defaultProtectedGetFn, arraySize, assetDoc(name, docs), AbstractClassRep::FIELD_HideInInspectors); \
   addProtectedField(assetText(name, Asset), TypeSoundAssetPtr, Offset(m##name##Asset, consoleClass), _set##name##Data, &defaultProtectedGetFn, arraySize, assetDoc(name, asset docs.));\
   addProtectedField(assetText(name, File), TypeSoundFilename, Offset(m##name##File, consoleClass), _set##name##Data, &defaultProtectedGetFn, arraySize, assetDoc(name, docs), AbstractClassRep::FIELD_HideInInspectors); \


#define LOAD_SOUNDASSET_ARRAY(name, index)\
if (m##name##AssetId[index] != StringTable->EmptyString())\
{\
   S32 assetState = SoundAsset::getAssetById(m##name##AssetId[index], &m##name##Asset[index]);\
   if (assetState == SoundAsset::Ok )\
   {\
      m##name##Name[index] = StringTable->EmptyString();\
   }\
   else Con::warnf("Warning: %s::LOAD_SOUNDASSET_ARRAY(%s[%i])-%s", mClassName, m##name##AssetId[index], index, ImageAsset::getAssetErrstrn(assetState).c_str());\
}

#define assetEnumNameConcat(x, suff) ([](const char* base) { \
         String result = String(base) + #suff; \
         char* ret = Con::getReturnBuffer(result.length() + 1); \
         dStrcpy(ret, result.c_str(), result.length() + 1); \
         return ret; \
      })(x)

#define INITPERSISTFIELD_SOUNDASSET_ENUMED(name, enumType, maxValue, consoleClass, docs) \
   for (U32 i = 0; i < maxValue; i++)\
   {\
      const enumType itter = static_cast<enumType>(i);\
      const char* enumString = castConsoleTypeToString(static_cast<enumType>(itter));\
      if (enumString && enumString[0])\
      {\
         addField(assetEnumNameConcat(enumString, Asset), TypeSoundAssetPtr, Offset(m##name##Asset[0], consoleClass) + sizeof(m##name##Asset[0])*i, assetText(name, asset reference.));\
         addField(assetEnumNameConcat(enumString, File), TypeSoundFilename, Offset(m##name##File[0], consoleClass) + sizeof(m##name##File[0])*i, assetText(name, docs), AbstractClassRep::FIELD_HideInInspectors); \
      }\
   }

#define PACKDATA_SOUNDASSET_ARRAY(name, index)\
   AssetDatabase.packDataAsset(stream, m##name##AssetId[index])

//network recieve - datablock
#define UNPACKDATA_SOUNDASSET_ARRAY(name, index)\
   m##name##AssetId[index] = AssetDatabase.unpackDataAsset(stream)

#pragma endregion
#endif // _ASSET_BASE_H_

