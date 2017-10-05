#ifndef _SHADERGEN_HLSL_SHADERFEATUREHLSL_H_
#include "shaderGen/HLSL/shaderFeatureHLSL.h"
#endif
#ifndef _LANG_ELEMENT_H_
#include "shaderGen/langElement.h"
#endif
#ifndef _GFXDEVICE_H_
#include "gfx/gfxDevice.h"
#endif
#ifndef _FEATUREMGR_H_
#include "shaderGen/featureMgr.h"
#endif
#ifndef _MATERIALFEATURETYPES_H_
#include "materials/materialFeatureTypes.h"
#endif
#ifndef _MATERIALFEATUREDATA_H_
#include "materials/materialFeatureData.h"
#endif

#ifndef CUSTOMSHADERFEATURE_H
#include "shaderGen/customShaderFeature.h"
#endif

class CustomShaderFeatureData;

class CustomFeatureHLSL : public ShaderFeatureHLSL
{
	friend class CustomShaderFeatureData;

public:
	CustomShaderFeatureData* mOwner;

protected:
	MultiLine *meta;

public:

	//****************************************************************************
	// Accu Texture
	//****************************************************************************
	virtual void processVert(Vector<ShaderComponent*> &componentList,
		const MaterialFeatureData &fd);

	virtual void processPix(Vector<ShaderComponent*> &componentList,
		const MaterialFeatureData &fd);

	virtual Material::BlendOp getBlendOp() { return Material::LerpAlpha; }

	virtual Resources getResources(const MaterialFeatureData &fd)
	{
		Resources res;
		res.numTex = 1;
		res.numTexReg = 1;
		return res;
	}

	virtual void setTexData(Material::StageData &stageDat,
		const MaterialFeatureData &fd,
		RenderPassData &passData,
		U32 &texIndex);

	virtual String getName()
	{
		return mOwner->getName();
	}

	void writeLine(String format, S32 argc, ConsoleValueRef *argv);
};