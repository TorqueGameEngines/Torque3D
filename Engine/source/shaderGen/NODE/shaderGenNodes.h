#pragma once

#ifndef _SHADERFEATURE_H_
#include "shaderGen/shaderFeature.h"
#endif

#ifndef _FEATUREMGR_H_
#include "shaderGen/featureMgr.h"
#endif

#ifndef _FEATURETYPE_H_
#include "shaderGen/featureType.h"
#endif

#ifndef __GFXSTATEBLOCKDATA_H_
#include "gfx/sim/gfxStateBlockData.h"
#endif

#ifndef _GFXAPI_H_
#include "gfx/gfxAPI.h"
#endif

DeclareFeatureType(SNF_DefaultTexCoord);
DeclareFeatureType(SNF_TextureFeature);

/// <summary>
/// This enum is so we can map to nodes in script.
/// </summary>
enum ShaderNodeFeature_enum
{
   eSNF_DefaultTexCoord,
   eSNF_TextureFeature,
};

DefineEnumType(ShaderNodeFeature_enum);

class ShaderFeatureNode : public ShaderFeature
{
public:
   void setupTextureSample(const String& samplerName,
                           GFXShaderConstType samplerType,
                           Vector<ShaderComponent*>& componentList,
                           MultiLine* meta,
                           LangElement* texCoord,
                           LangElement* compareValue,
                           bool useGather);

   Var* getOutTexCoord( const char* name,
                        GFXShaderConstType type,
                        bool useTexAnim,
                        MultiLine* meta,
                        Vector<ShaderComponent*>& componentList);

   LangElement* setupTexSpaceMat(Vector<ShaderComponent*>& componentList, Var** texSpaceMat) override;

   LangElement* assignColor(LangElement* elem, Material::BlendOp blend, LangElement* lerpElem = NULL, ShaderFeature::OutputTarget outputTarget = ShaderFeature::DefaultTarget) override;
};

/// <summary>
/// Parameters for the TextureFeature
/// </summary>
struct TextureFeatureParams : public FeatureParamsBase
{
   String samplerName;
   GFXShaderConstType samplerType;
   GFXSamplerStateData samplerState;
   String uvName;
   bool useGather;

   TextureFeatureParams()
   {
      samplerName = "defaultSampler";
      samplerType = GFXSCT_Sampler;
      uvName = "texCoord";
      useGather = false;

   }

   const char* getFeatureParamTypeName() const override { return "TextureFeatureParams"; }

   static void persistedFields(Vector<FeatureParamField>& fields)
   {
      addParam(fields, "sampler", Offset(samplerName, TextureFeatureParams), TypeString);
      addParam(fields, "samplerType", Offset(samplerType, TextureFeatureParams), TypeGFXShaderConstType);
      addParam(fields, "samplerState", Offset(samplerState, TextureFeatureParams), TYPEID<GFXSamplerStateData>());
      addParam(fields, "uvName", Offset(uvName, TextureFeatureParams), TypeString);
      addParam(fields, "useGather", Offset(useGather, TextureFeatureParams), TypeBool);
   }
};

REGISTER_FEATURE_PARAMS(SNF_TextureFeature, TextureFeatureParams)

class DefaultTexcoordFeature : public ShaderFeatureNode
{
   void processVert(Vector<ShaderComponent*>& componentList,
      const MaterialFeatureData& fd) override;

   void processPix(Vector<ShaderComponent*>& componentList,
      const MaterialFeatureData& fd) override;

   String getName() override
   {
      return "Default TexCoord";
   }
};

class TextureFeature : public ShaderFeatureNode
{
private:
   /// Parameters that this feature can use to change the shadergen output.
   TextureFeatureParams* params;
public:
   /// default constructor
   TextureFeature()
   {
      params = new TextureFeatureParams();
   }
   /// Constructor that takes params as an argument
   TextureFeature(TextureFeatureParams* inParams)
   {
      params = inParams;
   }

   void processPix(Vector<ShaderComponent*>& componentList,
      const MaterialFeatureData& fd) override;

   ShaderFeature::Resources getResources(const MaterialFeatureData& fd);

   // create a static function on the feature class
   static ShaderFeature* createFunction(FeatureParamsBase* args)
   {
      TextureFeatureParams* params = static_cast<TextureFeatureParams*>(args);
      return new TextureFeature(params);
   }

   String getName() override
   {
      return "Texture Sampler";
   }
};
