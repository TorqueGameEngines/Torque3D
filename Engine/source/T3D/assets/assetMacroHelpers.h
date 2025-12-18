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
#pragma once

//general class-injection hooks for asset support. not all cases are needed for every class/usage. 

//-----------------------------------------------------------------------------
/// INDIVIDUALIZED CLASS ENTRIES
//-----------------------------------------------------------------------------

//iniitalization
#define INIT_ASSET(name) \
   m##name##Name = StringTable->EmptyString(); \
   m##name##AssetId = StringTable->EmptyString(); \
   m##name##Asset = NULL;\
   m##name = NULL;

//load asset into memory by looking up the ID, spew a warning if anything goes wrong
#define LOAD_ASSET(name, assetClass)\
if (m##name##AssetId != StringTable->EmptyString())\
{\
   S32 assetState = assetClass::getAssetById(m##name##AssetId, &m##name##Asset);\
   if (assetState == assetClass::Ok )\
   {\
      m##name##Name = StringTable->EmptyString();\
   }\
   else Con::warnf("Warning: %s::LOAD_ASSET(%s)-%s", mClassName, m##name##AssetId, assetClass::getAssetErrstrn(assetState).c_str());\
}

// copy constructor 
#define CLONE_ASSET(name) \
   m##name##Name = other.m##name##Name;\
   m##name##AssetId = other.m##name##AssetId;\
   m##name##Asset = other.m##name##Asset;\
   m##name = other.m##name

// copy constructor refactor
#define CLONE_ASSET_REFACTOR(name) \
   m##name##Asset = other.m##name##Asset;\

//network send - datablock refactor
#define PACKDATA_ASSET_REFACTOR(name)\
AssetDatabase.packDataAsset(stream, m##name##Asset.getAssetId())

//network recieve - datablock
#define UNPACKDATA_ASSET_REFACTOR(name)\
m##name##Asset = AssetDatabase.unpackDataAsset(stream)

//network send - object-instance
#define PACK_ASSET_REFACTOR(netconn, name)\
AssetDatabase.packUpdateAsset(netconn, mask, stream, m##name##Asset.getAssetId())

//network recieve - object-instance
#define UNPACK_ASSET_REFACTOR(netconn, name)\
_set##name(AssetDatabase.unpackUpdateAsset(netconn, stream))

//network send - datablock
#define PACKDATA_ASSET_ARRAY_REFACTOR(name, max)\
for (U32 i = 0; i < max; i++)\
{\
   AssetDatabase.packDataAsset(stream, m##name##Asset[i].getAssetId());\
}

//network recieve - datablock
#define UNPACKDATA_ASSET_ARRAY_REFACTOR(name, max)\
for (U32 i = 0; i < max; i++)\
{\
   m##name##Asset[i] = AssetDatabase.unpackDataAsset(stream);\
}

//network send - object-instance
#define PACK_ASSET_ARRAY_REFACTOR(netconn, name, max)\
for (U32 i = 0; i < max; i++)\
{\
   AssetDatabase.packUpdateAsset(netconn, mask, stream, m##name##Asset[i].getAssetId());\
}

//network recieve - object-instance
#define UNPACK_ASSET_ARRAY_REFACTOR(netconn, name, max)\
for (U32 i = 0; i < max; i++)\
{\
   _set##name(AssetDatabase.unpackUpdateAsset(netconn, stream), i);\
}

#define DEF_ASSET_BINDS_REFACTOR(className,name)\
DefineEngineMethod(className, get##name, StringTableEntry, (), , "get name")\
{\
   return object->get##name##File(); \
}\
DefineEngineMethod(className, get##name##Asset, StringTableEntry, (), , assetText(name, asset reference))\
{\
   return object->_get##name(); \
}\
DefineEngineMethod(className, set##name, void, (const char* assetName), , assetText(name,assignment. first tries asset then flat file.))\
{\
   object->_set##name(StringTable->insert(assetName));\
}
// addProtectedField acessors
#define DECLARE_ASSET_SETGET(className, name)\
   static bool _set##name##Data(void* obj, const char* index, const char* data)\
   {\
      bool ret = false;\
      className* object = static_cast<className*>(obj);\
      ret = object->_set##name(StringTable->insert(data));\
      return ret;\
   }

// addProtectedField acessors for networked objects (sets a flag)
#define DECLARE_ASSET_NET_SETGET(className, name, bitmask)\
   static bool _set##name##Data(void* obj, const char* index, const char* data)\
   {\
      bool ret = false;\
      className* object = static_cast<className*>(obj);\
      ret = object->_set##name(StringTable->insert(data));\
      if(ret)\
         object->setMaskBits(bitmask);\
      return ret;\
   }

//network send - datablock
#define PACKDATA_ASSET(name)\
   if (stream->writeFlag(m##name##Asset.notNull()))\
   {\
      AssetDatabase.packDataAsset(stream, m##name##Asset.getAssetId());\
   }\
   else if(stream->writeFlag(m##name##Name != StringTable->EmptyString()))\
   {\
      stream->writeString(m##name##Name);\
   }\

//network recieve - datablock
#define UNPACKDATA_ASSET(name)\
   if (stream->readFlag())\
   {\
      m##name##AssetId = AssetDatabase.unpackDataAsset(stream);\
      _set##name(m##name##AssetId);\
   }\
   else if (stream->readFlag())\
   {\
      m##name##Name = stream->readSTString();\
      _set##name(m##name##Name);\
   }\
   else\
   {\
      _set##name(StringTable->EmptyString());\
   }\

//network send - object-instance
#define PACK_ASSET(netconn, name)\
   if (stream->writeFlag(m##name##Asset.notNull()))\
   {\
      AssetDatabase.packDataAsset(stream, m##name##Asset.getAssetId());\
   }\
   else if (stream->writeFlag(m##name##Name != StringTable->EmptyString()))\
   {\
      NetStringHandle nameStr = m##name##Name;\
      netconn->packNetStringHandleU(stream, nameStr);\
   }\

//network recieve - object-instance
#define UNPACK_ASSET(netconn, name)\
   if (stream->readFlag())\
   {\
      m##name##AssetId = AssetDatabase.unpackDataAsset(stream);\
      _set##name(m##name##AssetId);\
   }\
   else if (stream->readFlag())\
   {\
      _set##name(StringTable->insert(netconn->unpackNetStringHandleU(stream).getString()));\
   }\
   else\
   {\
      _set##name(StringTable->EmptyString()); \
   }\

//script methods for class.asset acces
//declare general get<entry>, get<entry>Asset and set<entry> methods
#define DEF_ASSET_BINDS(className,name)\
DefineEngineMethod(className, get##name, String, (), , "get name")\
{\
   return object->get##name(); \
}\
DefineEngineMethod(className, get##name##Asset, String, (), , assetText(name, asset reference))\
{\
   return object->m##name##AssetId; \
}\
DefineEngineMethod(className, set##name, bool, (const char* assetName), , assetText(name,assignment. first tries asset then flat file.))\
{\
   return object->_set##name(StringTable->insert(assetName));\
}

//-----------------------------------------------------------------------------
/// ARRAY CLASS ENTRIES
//-----------------------------------------------------------------------------

//iniitalization
#define INIT_ASSET_ARRAY(name, index) \
{\
   m##name##Name[index] = StringTable->EmptyString(); \
   m##name##AssetId[index] = StringTable->EmptyString(); \
   m##name##Asset[index] = NULL;\
   m##name[index] = NULL;\
}

//load asset into memory by looking up the ID, spew a warning if anything goes wrong
#define LOAD_ASSET_ARRAY(name, index, assetClass)\
if (m##name##AssetId[index] != StringTable->EmptyString())\
{\
   S32 assetState = assetClass::getAssetById(m##name##AssetId[index], &m##name##Asset[index]);\
   if (assetState == assetClass::Ok )\
   {\
      m##name##Name[index] = StringTable->EmptyString();\
   }\
   else Con::warnf("Warning: %s::LOAD_ASSET(%s[%d])-%s", mClassName, m##name##AssetId[index],index, assetClass::getAssetErrstrn(assetState).c_str());\
}

// copy constructor 
#define CLONE_ASSET_ARRAY(name, index) \
{\
   m##name##Name[index] = other.m##name##Name[index];\
   m##name##AssetId[index] = other.m##name##AssetId[index];\
   m##name##Asset[index] = other.m##name##Asset[index];\
   m##name[index] = other.m##name[index];\
}
// addProtectedField acessors
#define DECLARE_ASSET_ARRAY_SETGET(className, name)\
   static bool _set##name##Data(void* obj, const char* index, const char* data)\
   {\
      if(!index) return false;\
      U32 idx = dAtoi(index);\
      if (idx >= sm##name##Count)\
         return false;\
      bool ret = false;\
      className* object = static_cast<className*>(obj);\
      ret = object->_set##name(StringTable->insert(data), idx);\
      return ret;\
   }
// addProtectedField acessors for networked objects (sets a flag)
#define DECLARE_ASSET_ARRAY_NET_SETGET(className, name, bitmask)\
   static bool _set##name##Data(void* obj, const char* index, const char* data)\
   {\
      if (!index) return false;\
      U32 idx = dAtoi(index);\
      if (idx >= sm##name##Count)\
         return false;\
      bool ret = false;\
      className* object = static_cast<className*>(obj);\
      ret = object->_set##name(StringTable->insert(data), idx);\
      if(ret)\
         object->setMaskBits(bitmask);\
      return ret;\
   }
//network send - datablock
#define PACKDATA_ASSET_ARRAY(name, index)\
   AssetDatabase.packDataAsset(stream, m##name##Asset[index].getAssetId())

//network recieve - datablock
#define UNPACKDATA_ASSET_ARRAY(name, index)\
   m##name##Asset[index] = AssetDatabase.unpackDataAsset(stream)

//network send - object-instance
#define PACK_ASSET_ARRAY(netconn, name, index)\
AssetDatabase.packUpdateAsset(netconn, mask, stream, m##name##Asset[index].getAssetId());

//network recieve - object-instance
#define UNPACK_ASSET_ARRAY(netconn, name, index)\
_set##name(AssetDatabase.unpackUpdateAsset(netconn, stream), index);

//script methods for class.asset acces
//declare general get<entry>, get<entry>Asset and set<entry> methods
//signatures are:
//using DiffuseMap as an example
//material.getDiffuseMap(%layer); //returns the raw file referenced
//material.getDiffuseMapAsset(%layer); //returns the asset id
//material.setDiffuseMap(%texture, %layer); //tries to set the asset and failing that attempts a flat file reference
#define DEF_ASSET_ARRAY_BINDS(className,name)\
DefineEngineMethod(className, get##name, const char*, (S32 index), , "get name")\
{\
   return object->get##name(index); \
}\
DefineEngineMethod(className, get##name##Asset, const char*, (S32 index), , assetText(name, asset reference))\
{\
   if(index >= className::sm##name##Count || index < 0)\
      return "";\
   return object->m##name##AssetId[index]; \
}\
DefineEngineMethod(className, set##name, bool, (const char* assetName, S32 index), , assetText(name,assignment. first tries asset then flat file.))\
{\
    return object->_set##name(StringTable->insert(assetName), index);\
}

//-----------------------------------------------------------------------------
/// ARRAYS REFERENCED VIA ENUM CLASS ENTRIES
//-----------------------------------------------------------------------------
// 
// substite these in to see the enum strings and assigned values
//network send - object-instance
#define PACKDATA_ASSET_ARRAY_ENUMED(name, enumType, index )\
{\
   if (stream->writeFlag(m##name##Asset[index].notNull()))\
   {\
      stream->writeString(m##name##Asset[index].getAssetId());\
      const char* enumString = castConsoleTypeToString(static_cast<enumType>(index));\
      Con::printf("pack: %s = %s",enumString, m##name##AssetId[index]);\
   }\
   else if (stream->writeFlag(m##name##File[index] != StringTable->EmptyString()))\
   {\
      stream->writeString(m##name##File[index]);\
      const char* enumString = castConsoleTypeToString(static_cast<enumType>(index));\
      Con::printf("pack: %s = %s",enumString, m##name##File[index]);\
   }\
}
//network recieve - object-instance
#define UNPACKDATA_ASSET_ARRAY_ENUMED(name, enumType, index )\
{\
   if (stream->readFlag())\
   {\
      m##name##AssetId[index] = stream->readSTString();\
      _set##name(m##name##AssetId[index], index);\
      const char* enumString = castConsoleTypeToString(static_cast<enumType>(index));\
      Con::printf("unpack: %s = %s",enumString, m##name##AssetId[index]);\
   }\
   else if (stream->readFlag())\
   {\
      m##name##File[index] = stream->readSTString();\
      _set##name(m##name##File[index], index);\
      const char* enumString = castConsoleTypeToString(static_cast<enumType>(index));\
      Con::printf("unpack: %s = %s",enumString, m##name##AssetId[index]);\
   }\
   else\
   {\
      _set##name(StringTable->EmptyString(), index);\
   }\
}

