#pragma once
#include "shaderGen/HLSL/shaderFeatureHLSL.h"

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
class DebugVizHLSL : public ShaderFeatureHLSL
{
protected:

   ShaderIncludeDependency mTorqueDep;

public:

   DebugVizHLSL();

   void processPix(Vector<ShaderComponent*>& componentList,
      const MaterialFeatureData& fd) override;

   String getName() override { return "Debug Viz"; }
};
