#pragma once

#ifndef _SHADERGEN_GLSL_SHADERFEATUREGLSL_H_
#include "shaderGen/GLSL/shaderFeatureGLSL.h"
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

/// This should be the final feature on most pixel shaders which
/// encodes the color for the current HDR target format.
/// @see HDRPostFx
/// @see LightManager
/// @see torque.hlsl
class DebugVizGLSL : public ShaderFeatureGLSL
{
protected:

   ShaderIncludeDependency mTorqueDep;

public:

   DebugVizGLSL();

   virtual void processPix(Vector<ShaderComponent*>& componentList,
      const MaterialFeatureData& fd);

   virtual String getName() { return "Debug Viz"; }
};
