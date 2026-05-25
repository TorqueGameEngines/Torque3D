//-----------------------------------------------------------------------------
// Copyright (c) 2012 GarageGames, LLC
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
#ifndef _FEATUREMGR_H_
#define _FEATUREMGR_H_

#ifndef _TSINGLETON_H_
#include "core/util/tSingleton.h"
#endif 
#ifndef _TVECTOR_H_
#include "core/util/tVector.h"
#endif

#ifndef _UTIL_DELEGATE_H_
#include "core/util/delegate.h"
#endif

class FeatureType;
class ShaderFeature;

struct FeatureParamField
{
   StringTableEntry paramName;
   S32 offset;
   S32 type;
   U32 arraySize;
};

inline void addParam(Vector<FeatureParamField>& list,
                     const char* name,
                     S32 offset,
                     S32 consoleType,
                     U32 arraySize = 1)
{
   FeatureParamField f = { name, offset, consoleType, arraySize };
   list.push_back(f);
}

/// <summary>
/// Base class for all shader feature parameter structs.
/// </summary>
class FeatureParamsBase
{
public:
   virtual ~FeatureParamsBase() {}

   virtual const char* getOutputVar() const { return "default"; }
   // For debug or script reflection, you can override to serialize/print parameters
   virtual const char* getFeatureParamTypeName() const { return "FeatureParamsBase"; }
};

typedef Delegate<FeatureParamsBase* ()> CreateFeatureParams;

/// Metadata for a parameter struct type.
struct FeatureParamInfo
{
   const FeatureType* type;     // Matches feature
   const FeatureParamField* fields;
   U32 fieldCount;
   CreateFeatureParams createFn; // makes a new param struct
};

typedef Delegate<ShaderFeature* (FeatureParamsBase*)> CreateShaderFeatureDelegate;

/// <summary>
/// Used by the feature manager.
/// </summary>
/// <param name="type">The shader feature type.</param>
/// <param name="feature">The shader feature class.</param>
/// <param name="createFunc">The static create function for this feature.</param>
struct FeatureInfo
{
   const FeatureType *type;
   ShaderFeature *feature;
   CreateShaderFeatureDelegate createFunc;
};


///
class FeatureMgr
{
protected:

   bool mNeedsSort;

   typedef Vector<FeatureInfo> FeatureInfoVector;
   FeatureInfoVector mFeatures;

   typedef Vector<FeatureParamInfo> FeatureParamInfoVector;
   FeatureParamInfoVector mParamInfos;

   static S32 QSORT_CALLBACK _featureInfoCompare( const FeatureInfo *a, const FeatureInfo *b );

public:
   
   FeatureMgr();
   ~FeatureMgr();

   /// Returns the count of registered features.
   U32 getFeatureCount() const { return mFeatures.size(); }

   /// Returns the feature info at the index.
   const FeatureInfo& getAt( U32 index );

   /// 
   ShaderFeature* getByType( const FeatureType &type );

   /// <summary>
   /// Creates a shader feature of this type with the arguments provided.
   /// </summary>
   /// <param name="type">The shader feature type.</param>
   /// <param name="argStruct">The arguments for setting up this isntance of the shaderFeature.</param>
   /// <returns>An instance of the shader feature using its static createFunction taking in the
   /// argument struct.
   /// </returns>
   ShaderFeature* createFeature(const FeatureType& type, FeatureParamsBase* argStruct);

   void registerFeatureParams(const FeatureType& type, const FeatureParamField* fields, U32 fieldCount, CreateFeatureParams createFn);

   FeatureParamsBase* createFeatureParams(const FeatureType& type) const;

   void applyFeatureParams(const FeatureType& type, FeatureParamsBase* params, const Vector<String>& args) const;

   /// <summary>
   /// Allows other systems to add features.  index is 
   /// the enum in GFXMaterialFeatureData.
   /// </summary>
   /// <param name="type">The shader feature type.</param>
   /// <param name="feature">The shader feature (can be null if featureDelegate defined)</param>
   /// <param name="featureDelegate">The feature delegate create function.</param>
   void registerFeature(const FeatureType& type,
                        ShaderFeature* feature = NULL,
                        CreateShaderFeatureDelegate featureDelegate = NULL);

   // Unregister a feature.
   void unregisterFeature( const FeatureType &type );


   /// Removes all features.
   void unregisterAll();

   // For ManagedSingleton.
   static const char* getSingletonName() { return "FeatureMgr"; }   
};

// Helper for accessing the feature manager singleton.
#define FEATUREMGR ManagedSingleton<FeatureMgr>::instance()

#define REGISTER_FEATURE_PARAMS(TYPE, STRUCT_TYPE)                                \
   struct STRUCT_TYPE##_AutoRegister                                              \
   {                                                                              \
      STRUCT_TYPE##_AutoRegister()                                                \
      {                                                                           \
         Vector<FeatureParamField> fieldList;                                     \
         STRUCT_TYPE::persistedFields(fieldList);                                 \
         FEATUREMGR->registerFeatureParams(                                       \
            TYPE,                                                                 \
            fieldList.address(),                                                  \
            fieldList.size(),                                                     \
             Delegate<FeatureParamsBase*()>([]() -> FeatureParamsBase* { return new STRUCT_TYPE(); })\
         );                                                                       \
      }                                                                           \
   } STRUCT_TYPE##_AutoRegisterInstance;

#endif // FEATUREMGR
