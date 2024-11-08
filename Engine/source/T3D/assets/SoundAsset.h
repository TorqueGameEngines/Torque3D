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
   StringTableEntry        mSoundFile[SFXPlayList::SFXPlaylistSettings::NUM_SLOTS];
   StringTableEntry        mSoundPath[SFXPlayList::SFXPlaylistSettings::NUM_SLOTS];
   SFXProfile              mSFXProfile[SFXPlayList::SFXPlaylistSettings::NUM_SLOTS];

   SFXDescription          mProfileDesc;
   SFXPlayList             mPlaylist;
   // subtitles
   StringTableEntry        mSubtitleString;
   bool                    mPreload;
   bool                    mIsPlaylist;
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

   typedef Signal<void()> SoundAssetChanged;
   SoundAssetChanged mChangeSignal;

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
   SoundAsset();
   virtual ~SoundAsset();

   /// Engine.
   static void initPersistFields();
   void copyTo(SimObject* object) override;

   //SFXResource* getSound() { return mSoundResource; }
   Resource<SFXResource> getSoundResource(const U32 slotId = 0) { load(); return mSFXProfile[slotId].getResource(); }

   /// Declare Console Object.
   DECLARE_CONOBJECT(SoundAsset);

   static bool _setSoundFile(void* object, const char* index, const char* data);
   U32 load() override;
   inline StringTableEntry getSoundPath(const U32 slotId = 0) const { return mSoundPath[slotId]; };
   SFXProfile* getSfxProfile(const U32 slotId = 0) { return &mSFXProfile[slotId]; }
   SFXPlayList* getSfxPlaylist() { return &mPlaylist; }
   SFXTrack* getSFXTrack() { load(); return mIsPlaylist ? dynamic_cast<SFXTrack*>(&mPlaylist) : dynamic_cast<SFXTrack*>(&mSFXProfile[0]); }
   SFXDescription* getSfxDescription() { return &mProfileDesc; }
   bool isPlaylist(){ return mIsPlaylist; }

   bool isLoop() { return mProfileDesc.mIsLooping; }
   bool is3D() { return mProfileDesc.mIs3D; }

   static StringTableEntry getAssetIdByFileName(StringTableEntry fileName);
   static U32 getAssetById(StringTableEntry assetId, AssetPtr<SoundAsset>* materialAsset);
   static U32 getAssetByFileName(StringTableEntry fileName, AssetPtr<SoundAsset>* matAsset);

protected:
   void            initializeAsset(void) override;
   void _onResourceChanged(const Torque::Path & path);
   void            onAssetRefresh(void) override;
};

DefineConsoleType(TypeSoundAssetPtr, SoundAsset)
DefineConsoleType(TypeSoundAssetId, String)

#pragma region Singular Asset Macros

//Singular assets
/// <Summary>
/// Declares a sound asset
/// This establishes the assetId, asset and legacy filepath fields, along with supplemental getter and setter functions
/// </Summary>
#define DECLARE_SOUNDASSET(className, name) public: \
   Resource<SFXResource> m##name;\
   StringTableEntry m##name##Name; \
   StringTableEntry m##name##AssetId;\
   AssetPtr<SoundAsset> m##name##Asset = NULL;\
   SFXTrack* m##name##Profile = NULL;\
   SFXDescription* m##name##Desc = NULL;\
   SimObjectId m##name##SFXId = 0;\
public: \
   const StringTableEntry get##name##File() const { return m##name##Name; }\
   void set##name##File(const FileName &_in) { m##name##Name = StringTable->insert(_in.c_str());}\
   const AssetPtr<SoundAsset> & get##name##Asset() const { return m##name##Asset; }\
   void set##name##Asset(const AssetPtr<SoundAsset> &_in) { m##name##Asset = _in;}\
   \
   bool _set##name(StringTableEntry _in)\
   {\
      if(m##name##AssetId != _in || m##name##Name != _in)\
      {\
         if (_in == NULL || _in == StringTable->EmptyString())\
         {\
            m##name##Name = StringTable->EmptyString();\
            m##name##AssetId = StringTable->EmptyString();\
            m##name##Asset = NULL;\
            m##name = NULL;\
            return true;\
         }\
         \
         if (AssetDatabase.isDeclaredAsset(_in))\
         {\
            m##name##AssetId = _in;\
            \
            U32 assetState = SoundAsset::getAssetById(m##name##AssetId, &m##name##Asset);\
            \
            if (SoundAsset::Ok == assetState)\
            {\
               m##name##Name = StringTable->EmptyString();\
            }\
         }\
         else\
         {\
            StringTableEntry assetId = SoundAsset::getAssetIdByFileName(_in);\
            if (assetId != StringTable->EmptyString())\
            {\
               m##name##AssetId = assetId;\
               if(SoundAsset::getAssetById(m##name##AssetId, &m##name##Asset) == SoundAsset::Ok)\
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
      if (get##name() != StringTable->EmptyString() && m##name##Asset.notNull())\
      {\
         m##name = m##name##Asset->getSoundResource();\
      }\
      else\
      {\
         m##name = NULL;\
      }\
      if(get##name() == StringTable->EmptyString())\
         return true;\
      \
      if(get##name() == StringTable->EmptyString())\
         return true;\
      if (m##name##Asset.notNull() && m##name##Asset->getStatus() != SoundAsset::Ok)\
      {\
         Con::errorf("%s(%s)::_set%s() - sound asset failure\"%s\" due to [%s]", macroText(className), getName(), macroText(name), _in, SoundAsset::getAssetErrstrn(m##name##Asset->getStatus()).c_str());\
         return false; \
      }\
      else if (!m##name && (m##name##Name != StringTable->EmptyString() && !Sim::findObject(m##name##Name)))\
      {\
         Con::errorf("%s(%s)::_set%s() - Couldn't load sound \"%s\"", macroText(className), getName(), macroText(name), _in);\
         return false;\
      }\
      return true;\
   }\
   \
   const StringTableEntry get##name() const\
   {\
      if (m##name##Asset && (m##name##Asset->getSoundPath() != StringTable->EmptyString()))\
         return m##name##Asset->getSoundPath();\
      else if (m##name##AssetId != StringTable->EmptyString())\
         return m##name##AssetId;\
      else if (m##name##Name != StringTable->EmptyString())\
         return StringTable->insert(m##name##Name);\
      else\
         return StringTable->EmptyString();\
   }\
   Resource<SFXResource> get##name##Resource() \
   {\
      return m##name;\
   }\
   SFXTrack* get##name##Profile()\
   {\
      if (get##name() != StringTable->EmptyString() && m##name##Asset.notNull()){\
            m##name##Profile = m##name##Asset->getSFXTrack(); \
            return m##name##Profile;\
      }\
      return NULL;\
   }\
   SFXDescription* get##name##Description()\
   {\
      if (get##name() != StringTable->EmptyString() && m##name##Asset.notNull()){\
         m##name##Desc = m##name##Asset->getSfxDescription();\
         return m##name##Desc;}\
      return NULL;\
   }\
   bool is##name##Valid() { return (get##name() != StringTable->EmptyString() && m##name##Asset && m##name##Asset->getStatus() == AssetBase::Ok); }

#ifdef TORQUE_SHOW_LEGACY_FILE_FIELDS

#define INITPERSISTFIELD_SOUNDASSET(name, consoleClass, docs) \
   addProtectedField(assetText(name, File), TypeSoundFilename, Offset(m##name##Name, consoleClass), _set##name##Data, & defaultProtectedGetFn, assetText(name, docs)); \
   addProtectedField(assetText(name, Asset), TypeSoundAssetId, Offset(m##name##AssetId, consoleClass), _set##name##Data, & defaultProtectedGetFn, assetText(name, asset reference.));

#else

#define INITPERSISTFIELD_SOUNDASSET(name, consoleClass, docs) \
   addProtectedField(assetText(name, File), TypeSoundFilename, Offset(m##name##Name, consoleClass), _set##name##Data, & defaultProtectedGetFn, assetText(name, docs), AbstractClassRep::FIELD_HideInInspectors); \
   addProtectedField(assetText(name, Asset), TypeSoundAssetId, Offset(m##name##AssetId, consoleClass), _set##name##Data, & defaultProtectedGetFn, assetText(name, asset reference.));

#endif // TORQUE_SHOW_LEGACY_FILE_FIELDS

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

#define DECLARE_SOUNDASSET_ARRAY(className,name,max) public: \
   static const U32 sm##name##Count = max;\
   Resource<SFXResource> m##name[max];\
   StringTableEntry m##name##Name[max]; \
   StringTableEntry m##name##AssetId[max];\
   AssetPtr<SoundAsset> m##name##Asset[max];\
   SFXTrack* m##name##Profile[max];\
   SimObjectId m##name##SFXId[max];\
public: \
   const StringTableEntry get##name##File(const U32& index) const { return m##name##Name[index]; }\
   void set##name##File(const FileName &_in, const U32& index) { m##name##Name[index] = StringTable->insert(_in.c_str());}\
   const AssetPtr<SoundAsset> & get##name##Asset(const U32& index) const { return m##name##Asset[index]; }\
   void set##name##Asset(const AssetPtr<SoundAsset> &_in, const U32& index) { m##name##Asset[index] = _in;}\
   \
   bool _set##name(StringTableEntry _in, const U32& index)\
   {\
      if(m##name##AssetId[index] != _in || m##name##Name[index] != _in)\
      {\
         if(index >= sm##name##Count || index < 0) \
               return false;\
         if (_in == NULL || _in == StringTable->EmptyString())\
         {\
            m##name##Name[index] = StringTable->EmptyString();\
            m##name##AssetId[index] = StringTable->EmptyString();\
            m##name##Asset[index] = NULL;\
            m##name[index] = NULL;\
            return true;\
         }\
         else if(_in[0] == '$' || _in[0] == '#')\
         {\
            m##name##Name[index] = _in;\
            m##name##AssetId[index] = StringTable->EmptyString();\
            m##name##Asset[index] = NULL;\
            m##name[index] = NULL;\
            return true;\
         }\
         \
         if (AssetDatabase.isDeclaredAsset(_in))\
         {\
            m##name##AssetId[index] = _in;\
            \
            U32 assetState = SoundAsset::getAssetById(m##name##AssetId[index], &m##name##Asset[index]);\
            \
            if (SoundAsset::Ok == assetState)\
            {\
               m##name##Name[index] = StringTable->EmptyString();\
            }\
         }\
         else\
         {\
            StringTableEntry assetId = SoundAsset::getAssetIdByFileName(_in);\
            if (assetId != StringTable->EmptyString())\
            {\
               m##name##AssetId[index] = assetId;\
               if(SoundAsset::getAssetById(m##name##AssetId[index], &m##name##Asset[index]) == SoundAsset::Ok)\
               {\
                  m##name##Name[index] = StringTable->EmptyString();\
               }\
            }\
            else\
            {\
               m##name##Name[index] = _in;\
               m##name##AssetId[index] = StringTable->EmptyString();\
               m##name##Asset[index] = NULL;\
            }\
         }\
      }\
      if (get##name(index) != StringTable->EmptyString() && m##name##Asset[index].notNull())\
      {\
         m##name[index] = m##name##Asset[index]->getSoundResource();\
      }\
      else\
      {\
         m##name[index] = NULL;\
      }\
      if(get##name(index) == StringTable->EmptyString())\
         return true;\
      \
      if (m##name##Asset[index].notNull() && m##name##Asset[index]->getStatus() != SoundAsset::Ok)\
      {\
         Con::errorf("%s(%s)::_set%s(%i) - sound asset failure\"%s\" due to [%s]", macroText(className), getName(), macroText(name),index, _in, SoundAsset::getAssetErrstrn(m##name##Asset[index]->getStatus()).c_str());\
         return false; \
      }\
      else if (!m##name[index] && (m##name##Name[index] != StringTable->EmptyString() && !Sim::findObject(m##name##Name[index])))\
      {\
         Con::errorf("%s(%s)::_set%s(%i) - Couldn't load sound \"%s\"", macroText(className), getName(), macroText(name),index, _in);\
         return false;\
      }\
      return true;\
   }\
   \
   const StringTableEntry get##name(const U32& index) const\
   {\
      if (m##name##Asset[index] && (m##name##Asset[index]->getSoundPath() != StringTable->EmptyString()))\
         return m##name##Asset[index]->getSoundPath();\
      else if (m##name##AssetId[index] != StringTable->EmptyString())\
         return m##name##AssetId[index];\
      else if (m##name##Name[index] != StringTable->EmptyString())\
         return StringTable->insert(m##name##Name[index]);\
      else\
         return StringTable->EmptyString();\
   }\
   Resource<SFXResource> get##name##Resource(const U32& id) \
   {\
      if(id >= sm##name##Count || id < 0)\
         return ResourceManager::get().load( "" );\
      return m##name[id];\
   }\
   SFXTrack* get##name##Profile(const U32& id)\
   {\
         if (m##name##Asset[id].notNull())\
            return  m##name##Asset[id]->getSFXTrack(); \
      return NULL;\
   }\
   bool is##name##Valid(const U32& id) {return (get##name(id) != StringTable->EmptyString() && m##name##Asset[id] && m##name##Asset[id]->getStatus() == AssetBase::Ok); }


#ifdef TORQUE_SHOW_LEGACY_FILE_FIELDS

#define INITPERSISTFIELD_IMAGEASSET_ARRAY(name, arraySize, consoleClass, docs) \
   addProtectedField(#name, TypeSoundFilename, Offset(m##name##Name, consoleClass), _set##name##Data, &defaultProtectedGetFn, arraySize, assetDoc(name, docs)); \
   addProtectedField(assetText(name, Asset), TypeImageAssetId, Offset(m##name##AssetId, consoleClass), _set##name##Data, &defaultProtectedGetFn, arraySize, assetDoc(name, asset docs.));

#else

#define INITPERSISTFIELD_SOUNDASSET_ARRAY(name, arraySize, consoleClass, docs) \
   addProtectedField(#name, TypeSoundFilename, Offset(m##name##Name, consoleClass), _set##name##Data, &defaultProtectedGetFn, arraySize, assetDoc(name, docs), AbstractClassRep::FIELD_HideInInspectors); \
   addProtectedField(assetText(name, Asset), TypeSoundAssetId, Offset(m##name##AssetId, consoleClass), _set##name##Data, &defaultProtectedGetFn, arraySize, assetDoc(name, asset docs.));

#endif

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

#define assetEnumNameConcat(x,suff)(new std::string( x + std::string(#suff)))->c_str()

#define INITPERSISTFIELD_SOUNDASSET_ENUMED(name, enumType, maxValue, consoleClass, docs) \
   for (U32 i = 0; i < maxValue; i++)\
   {\
      const enumType itter = static_cast<enumType>(i);\
      const char* enumString = castConsoleTypeToString(static_cast<enumType>(itter));\
      if (enumString && enumString[0])\
      {\
         addField(assetEnumNameConcat(enumString, File), TypeSoundFilename, Offset(m##name##Name[0], consoleClass) + sizeof(m##name##Name[0])*i, assetText(name, docs), AbstractClassRep::FIELD_HideInInspectors); \
         addField(assetEnumNameConcat(enumString, Asset), TypeSoundAssetId, Offset(m##name##AssetId[0], consoleClass) + sizeof(m##name##AssetId[0])*i, assetText(name, asset reference.));\
      }\
   }

#define PACKDATA_SOUNDASSET_ARRAY(name, index)\
   if (stream->writeFlag(AssetDatabase.isDeclaredAsset(m##name##AssetId[index])))\
   {\
      stream->writeString(m##name##AssetId[index]);\
   }\
   else\
   {\
      if(stream->writeFlag(Sim::findObject(m##name##Name[index])))\
      {\
         SFXTrack* sndTrack = get##name##Profile(index);\
         if(stream->writeFlag(sndTrack != nullptr))\
         {\
            stream->writeRangedU32(SimObjectId(sndTrack->getId()), DataBlockObjectIdFirst, DataBlockObjectIdLast);\
            sfxWrite(stream, sndTrack);\
         }\
      }\
      else\
      {\
         stream->writeString(m##name##Name[index]);\
      }\
   }
      

//network recieve - datablock
#define UNPACKDATA_SOUNDASSET_ARRAY(name, index)\
   if (stream->readFlag())\
   {\
      m##name##AssetId[index] = stream->readSTString();\
      _set##name(m##name##AssetId[index], index);\
   }\
   else\
   {\
      if(stream->readFlag())\
      {\
         String errorStr;\
         if(stream->readFlag())\
         {\
            m##name##SFXId[index] = stream->readRangedU32( DataBlockObjectIdFirst, DataBlockObjectIdLast );\
            sfxReadAndResolve(stream, &m##name##Profile[index], errorStr);\
         }\
      }\
      else\
      {\
         m##name##Name[index] = stream->readSTString(); \
         _set##name(m##name##Name[index], index); \
      }\
   }
#pragma endregion

#endif // _ASSET_BASE_H_

