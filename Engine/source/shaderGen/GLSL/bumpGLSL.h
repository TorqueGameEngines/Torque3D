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

#ifndef _BUMP_GLSL_H_
#define _BUMP_GLSL_H_

#ifndef _SHADERGEN_GLSL_SHADERFEATUREGLSL_H_
#include "shaderGen/GLSL/shaderFeatureGLSL.h"
#endif
#ifndef _LANG_ELEMENT_H_
#include "shaderGen/langElement.h"
#endif

struct RenderPassData;
class MultiLine;


/// The Bumpmap feature will read the normal map and
/// transform it by the inverse of the worldToTanget 
/// matrix.  This normal is then used by subsequent
/// shader features.
class BumpFeatGLSL : public ShaderFeatureGLSL
{
public:

   // ShaderFeatureGLSL
   void processVert( Vector<ShaderComponent*> &componentList,
                             const MaterialFeatureData &fd ) override;
   void processPix( Vector<ShaderComponent*> &componentList, 
                            const MaterialFeatureData &fd ) override;
   Material::BlendOp getBlendOp() override{ return Material::LerpAlpha; }  
   Resources getResources( const MaterialFeatureData &fd ) override;
   void setTexData( Material::StageData &stageDat,
                            const MaterialFeatureData &fd,
                            RenderPassData &passData,
                            U32 &texIndex ) override;
   String getName() override { return "Bumpmap"; }
};


/// This feature either generates the cheap yet effective offset
/// mapping style parallax or the much more expensive occlusion 
/// mapping technique based on the enabled feature flags.
class ParallaxFeatGLSL : public ShaderFeatureGLSL
{
protected:

   static Var* _getUniformVar(   const char *name, 
                                 const char *type, 
                                 ConstantSortPosition csp );

   ShaderIncludeDependency mIncludeDep;

public:

   ParallaxFeatGLSL();

   // ShaderFeatureGLSL
   void processVert(  Vector<ShaderComponent*> &componentList,
                              const MaterialFeatureData &fd ) override;
   void processPix(   Vector<ShaderComponent*> &componentList, 
                              const MaterialFeatureData &fd ) override;
   Resources getResources( const MaterialFeatureData &fd ) override;
   void setTexData(   Material::StageData &stageDat,
                              const MaterialFeatureData &fd,
                              RenderPassData &passData,
                              U32 &texIndex ) override;
   String getName() override { return "Parallax"; }
};


/// This feature is used to render normals to the 
/// diffuse target for imposter rendering.
class NormalsOutFeatGLSL : public ShaderFeatureGLSL
{
public:
	
   // ShaderFeatureGLSL
   void processVert(  Vector<ShaderComponent*> &componentList,
									 const MaterialFeatureData &fd ) override;
   void processPix( Vector<ShaderComponent*> &componentList, 
									const MaterialFeatureData &fd ) override;
   Material::BlendOp getBlendOp() override{ return Material::LerpAlpha; }  
   String getName() override { return "NormalsOut"; }
};

#endif // _BUMP_GLSL_H_