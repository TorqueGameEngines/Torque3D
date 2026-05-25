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

DeclareFeatureType(SNF_VertexPosition);
DeclareFeatureType(SNF_DefaultTexCoord);
DeclareFeatureType(SNF_TextureFeature);
DeclareFeatureType(SNF_NormalMapFeature);

/// <summary>
/// This enum is so we can map to nodes in script.
/// </summary>
enum ShaderNodeFeature_enum
{
   eSNF_VertexPosition,
   eSNF_DefaultTexCoord,
   eSNF_TextureFeature,
   eSNF_NormalMapFeature,
};

DefineEnumType(ShaderNodeFeature_enum);

class ShaderFeatureNode : public ShaderFeature
{
public:

   ///
   Var* getObjTrans( Vector<ShaderComponent*>& componentList,
                     bool useInstancing,
                     MultiLine* meta);

   Var* getModelView(Vector<ShaderComponent*>& componentList,
                     bool useInstancing,
                     MultiLine* meta);

   Var* getWorldView(Vector<ShaderComponent*>& componentList, bool useInstancing, MultiLine* meta);

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

class NodeVertexPositionFeature : public ShaderFeatureNode
{
   void processVert(Vector<ShaderComponent*>& componentList,
      const MaterialFeatureData& fd) override;

   void processPix(Vector<ShaderComponent*>& componentList,
      const MaterialFeatureData& fd) override;

   String getName() override
   {
      return "NodeVertexPositionFeature";
   }
};

class DefaultTexcoordFeature : public ShaderFeatureNode
{
   void processVert(Vector<ShaderComponent*>& componentList,
      const MaterialFeatureData& fd) override;

   void processPix(Vector<ShaderComponent*>& componentList,
      const MaterialFeatureData& fd) override;

   String getName() override
   {
      return "DefaultTexCoord";
   }
};

//--------------------------------------------------------
// TEXTURE SAMPLER FEATURE
//--------------------------------------------------------

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

   /// <summary>
   /// Texture features output variable is samplerName + "_col"
   /// </summary>
   /// <returns>The output variable for a texture feature.</returns>
   const char* getOutputVar() const override { return samplerName + "_col"; }

   static void persistedFields(Vector<FeatureParamField>& fields)
   {
      addParam(fields, "sampler", Offset(samplerName, TextureFeatureParams), TypeString);
      addParam(fields, "samplerType", Offset(samplerType, TextureFeatureParams), TypeGFXShaderConstType);
      addParam(fields, "samplerState", Offset(samplerState, TextureFeatureParams), TYPEID<GFXSamplerStateData>());
      addParam(fields, "uvName", Offset(uvName, TextureFeatureParams), TypeString);
      addParam(fields, "useGather", Offset(useGather, TextureFeatureParams), TypeBool);
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

   ShaderFeature::Resources getResources(const MaterialFeatureData& fd) override;

   // create a static function on the feature class
   static ShaderFeature* createFunction(FeatureParamsBase* args)
   {
      TextureFeatureParams* params = static_cast<TextureFeatureParams*>(args);
      return new TextureFeature(params);
   }

   String getName() override
   {
      return "TextureSampler_" + params->samplerName + "_" + params->uvName;
   }
};

//--------------------------------------------------------
// NORMAL MAPPING FEATURE
//--------------------------------------------------------

/// <summary>
/// Parameters for the NormalMapFeature
/// </summary>
struct NormalMapFeatureParams : public FeatureParamsBase
{
   String inputName;    // name of the sampled normal texture (Var* from TextureFeature)
   F32 strength;        // normal strength multiplier
   bool flipX;
   bool flipY;

   NormalMapFeatureParams()
   {
      inputName = "normalSampler";
      strength = 1.0f;
      flipX = false;
      flipY = false;
   }

   const char* getFeatureParamTypeName() const override { return "NormalMapFeatureParams"; }

   /// <summary>
   /// Normal map feature writes the result into the input name
   /// </summary>
   /// <returns>The output variable for a normal map feature.</returns>
   const char* getOutputVar() const override { return inputName; }

   static void persistedFields(Vector<FeatureParamField>& fields)
   {
      addParam(fields, "input", Offset(inputName, NormalMapFeatureParams), TypeString);
      addParam(fields, "strength", Offset(strength, NormalMapFeatureParams), TypeF32);
      addParam(fields, "flipX", Offset(flipX, NormalMapFeatureParams), TypeBool);
      addParam(fields, "flipY", Offset(flipY, NormalMapFeatureParams), TypeBool);
   }
};

class NormalMapFeature : public ShaderFeatureNode
{
private:
   NormalMapFeatureParams* params;

public:
   NormalMapFeature() { params = new NormalMapFeatureParams(); }
   NormalMapFeature(NormalMapFeatureParams* p) { params = p; }

   void processPix(Vector<ShaderComponent*>& componentList, const MaterialFeatureData& fd) override;

   // normal map feature does not need any resources as these were created from the texture feature.

   static ShaderFeature* createFunction(FeatureParamsBase* args)
   {
      return new NormalMapFeature(static_cast<NormalMapFeatureParams*>(args));
   }

   String getName() override
   {
      return "NormalMap_" + params->inputName;
   }
};
