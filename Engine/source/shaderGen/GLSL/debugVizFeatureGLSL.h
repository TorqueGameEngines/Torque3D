#pragma once
#include "shaderGen/GLSL/shaderFeatureGLSL.h"

#include "shaderGen/langElement.h"

#include "gfx/gfxDevice.h"

#include "shaderGen/featureMgr.h"

#include "materials/materialFeatureTypes.h"

#include "materials/materialFeatureData.h"

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

   void processPix(Vector<ShaderComponent*>& componentList,
      const MaterialFeatureData& fd) override;

   String getName() override { return "Debug Viz"; }
};
