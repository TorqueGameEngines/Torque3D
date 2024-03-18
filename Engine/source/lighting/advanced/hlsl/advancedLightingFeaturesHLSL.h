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

#ifndef _DEFERREDFEATURESHLSL_H_
#define _DEFERREDFEATURESHLSL_H_

#include "shaderGen/HLSL/shaderFeatureHLSL.h"
#include "shaderGen/HLSL/bumpHLSL.h"

class ConditionerMethodDependency;


/// Lights the pixel by sampling from the light deferred 
/// buffer.  It will fall back to forward lighting 
/// functionality for non-deferred rendered surfaces.
///
/// Also note that this feature is only used in the
/// forward rendering pass.  It is not used during the
/// deferred step.
///
class DeferredRTLightingFeatHLSL : public RTLightingFeatHLSL
{
   typedef RTLightingFeatHLSL Parent;

protected:

   /// @see DeferredRTLightingFeatHLSL::processPix()
   U32 mLastTexIndex;

public:

   void processVert( Vector<ShaderComponent*> &componentList,
                              const MaterialFeatureData &fd ) override;

   void processPix(   Vector<ShaderComponent*> &componentList, 
                              const MaterialFeatureData &fd ) override;

   void processPixMacros(   Vector<GFXShaderMacro> &macros, 
                                    const MaterialFeatureData &fd ) override;

   Material::BlendOp getBlendOp() override{ return Material::None; }

   Resources getResources( const MaterialFeatureData &fd ) override;

   void setTexData(   Material::StageData &stageDat,
                              const MaterialFeatureData &fd,
                              RenderPassData &passData,
                              U32 &texIndex ) override;

   String getName() override
   {
      return "Deferred RT Lighting";
   }
};


/// This is used during the 
class DeferredBumpFeatHLSL : public BumpFeatHLSL
{
   typedef BumpFeatHLSL Parent;

public:
   void processVert(  Vector<ShaderComponent*> &componentList,
                              const MaterialFeatureData &fd ) override;

   void processPix(   Vector<ShaderComponent*> &componentList, 
                              const MaterialFeatureData &fd ) override;

   Material::BlendOp getBlendOp() override { return Material::LerpAlpha; }

   Resources getResources( const MaterialFeatureData &fd ) override;

   void setTexData(   Material::StageData &stageDat,
                              const MaterialFeatureData &fd,
                              RenderPassData &passData,
                              U32 &texIndex ) override;

   String getName() override
   {
      return "Bumpmap [Deferred]";
   }
};


///
class DeferredMinnaertHLSL : public ShaderFeatureHLSL
{
   typedef ShaderFeatureHLSL Parent;
   
public:
   void processPix(   Vector<ShaderComponent*> &componentList, 
                              const MaterialFeatureData &fd ) override;
   void processVert(  Vector<ShaderComponent*> &componentList,
                              const MaterialFeatureData &fd ) override;

   void processPixMacros(   Vector<GFXShaderMacro> &macros, 
                                    const MaterialFeatureData &fd ) override;

   Resources getResources( const MaterialFeatureData &fd ) override;

   void setTexData(   Material::StageData &stageDat,
                              const MaterialFeatureData &fd,
                              RenderPassData &passData,
                              U32 &texIndex ) override;

   String getName() override
   {
      return "Minnaert Shading [Deferred]";
   }
};


///
class DeferredSubSurfaceHLSL : public ShaderFeatureHLSL
{
   typedef ShaderFeatureHLSL Parent;

public:
   void processPix(   Vector<ShaderComponent*> &componentList, 
                              const MaterialFeatureData &fd ) override;

   String getName() override
   {
      return "Sub-Surface Approximation [Deferred]";
   }
};

#endif // _DEFERREDFEATURESHLSL_H_
