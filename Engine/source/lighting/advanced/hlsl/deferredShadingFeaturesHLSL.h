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

#ifndef _DEFERREDSHADINGHLSL_H_
#define _DEFERREDSHADINGHLSL_H_

#include "shaderGen/HLSL/shaderFeatureHLSL.h"
#include "shaderGen/HLSL/bumpHLSL.h"

class DeferredOrmMapHLSL : public ShaderFeatureHLSL
{
public:
   String getName() override { return "Deferred Shading: PBR Config Map"; }

   U32 getOutputTargets(const MaterialFeatureData& fd) const override;

   void processPix( Vector<ShaderComponent*> &componentList, 
      const MaterialFeatureData &fd ) override;
   
   Resources getResources( const MaterialFeatureData &fd ) override;

   // Sets textures and texture flags for current pass
   void setTexData( Material::StageData &stageDat,
                            const MaterialFeatureData &fd,
                            RenderPassData &passData,
                            U32 &texIndex ) override;
   
   void processVert( Vector<ShaderComponent*> &componentList,
                             const MaterialFeatureData &fd ) override;
};

class MatInfoFlagsHLSL : public ShaderFeatureHLSL
{
public:
   String getName() override { return "Deferred Shading: Mat Info Flags"; }

   void processPix( Vector<ShaderComponent*> &componentList, 
      const MaterialFeatureData &fd ) override;

   U32 getOutputTargets(const MaterialFeatureData& fd) const override;
};

class ORMConfigVarsHLSL : public ShaderFeatureHLSL
{
public:
   String getName() override { return "Deferred Shading: PBR Config Explicit Numbers"; }

   U32 getOutputTargets(const MaterialFeatureData& fd) const override;

   void processPix( Vector<ShaderComponent*> &componentList, 
      const MaterialFeatureData &fd ) override;
};

class GlowMapHLSL : public ShaderFeatureHLSL
{
public:
   String getName() override { return "Glow Map"; }

   void processPix(Vector<ShaderComponent*> &componentList,
      const MaterialFeatureData &fd) override;

   U32 getOutputTargets(const MaterialFeatureData& fd) const override;

   Resources getResources(const MaterialFeatureData& fd) override;

   // Sets textures and texture flags for current pass
   void setTexData(Material::StageData& stageDat,
      const MaterialFeatureData& fd,
      RenderPassData& passData,
      U32& texIndex) override;
};

#endif
