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

#ifndef _TERRFEATUREGLSL_H_
#define _TERRFEATUREGLSL_H_

#ifndef _SHADERGEN_GLSL_SHADERFEATUREGLSL_H_
#include "shaderGen/GLSL/shaderFeatureGLSL.h"
#endif
#ifndef _LANG_ELEMENT_H_
#include "shaderGen/langElement.h"
#endif


/// A shared base class for terrain features which
/// includes some helper functions.
class TerrainFeatGLSL : public ShaderFeatureGLSL
{
protected:
   ShaderIncludeDependency mTorqueDep;
   
public:
   TerrainFeatGLSL();
   Var* _getInDetailCoord(Vector<ShaderComponent*> &componentList );
   
   Var* _getInMacroCoord(Vector<ShaderComponent*> &componentList );

   Var* _getDetailMapSampler();
   Var* _getMacroMapSampler();
   Var* _getNormalMapSampler();
   Var* _getOrmMapSampler();

   static Var* _getUniformVar( const char *name, const char *type, ConstantSortPosition csp );
   
   Var* _getDetailIdStrengthParallax();
   Var* _getMacroIdStrengthParallax();
      
};


class TerrainBaseMapFeatGLSL : public TerrainFeatGLSL
{
public:

   void processVert( Vector<ShaderComponent*> &componentList,
                             const MaterialFeatureData &fd ) override;

   void processPix( Vector<ShaderComponent*> &componentList, 
                            const MaterialFeatureData &fd ) override;
          
   Resources getResources( const MaterialFeatureData &fd ) override;

   String getName() override { return "Terrain Base Texture"; }

   U32 getOutputTargets( const MaterialFeatureData &fd ) const override;
};


class TerrainDetailMapFeatGLSL : public TerrainFeatGLSL
{
protected:

   ShaderIncludeDependency mTorqueDep;
   ShaderIncludeDependency mTerrainDep;

public:

   TerrainDetailMapFeatGLSL();

   void processVert(  Vector<ShaderComponent*> &componentList,
                              const MaterialFeatureData &fd ) override;

   void processPix(   Vector<ShaderComponent*> &componentList, 
                              const MaterialFeatureData &fd ) override;

   Resources getResources( const MaterialFeatureData &fd ) override;

   String getName() override { return "Terrain Detail Texture"; }

   U32 getOutputTargets( const MaterialFeatureData &fd ) const override;
};


class TerrainMacroMapFeatGLSL : public TerrainFeatGLSL
{
protected:

   ShaderIncludeDependency mTorqueDep;
   ShaderIncludeDependency mTerrainDep;

public:

   TerrainMacroMapFeatGLSL();

   void processVert(  Vector<ShaderComponent*> &componentList,
                              const MaterialFeatureData &fd ) override;

   void processPix(   Vector<ShaderComponent*> &componentList, 
                              const MaterialFeatureData &fd ) override;

   Resources getResources( const MaterialFeatureData &fd ) override;

   String getName() override { return "Terrain Macro Texture"; }

   U32 getOutputTargets( const MaterialFeatureData &fd ) const override;
};


class TerrainNormalMapFeatGLSL : public TerrainFeatGLSL
{
public:

   void processVert(  Vector<ShaderComponent*> &componentList,
                            const MaterialFeatureData &fd ) override;
   
   void processPix(   Vector<ShaderComponent*> &componentList, 
                           const MaterialFeatureData &fd ) override;
   
   Resources getResources( const MaterialFeatureData &fd ) override;
   
   String getName() override { return "Terrain Normal Texture"; }
};

class TerrainLightMapFeatGLSL : public TerrainFeatGLSL
{
public:

   void processPix( Vector<ShaderComponent*> &componentList, 
                            const MaterialFeatureData &fd ) override;
          
   Resources getResources( const MaterialFeatureData &fd ) override;

   String getName() override { return "Terrain Lightmap Texture"; }
};

class TerrainORMMapFeatGLSL : public TerrainFeatGLSL
{
public:

	void processVert(Vector<ShaderComponent*> &componentList,
		const MaterialFeatureData &fd) override;

	void processPix(Vector<ShaderComponent*> &componentList,
		const MaterialFeatureData &fd) override;

	Resources getResources(const MaterialFeatureData &fd) override;

	U32 getOutputTargets(const MaterialFeatureData &fd) const override;
	String getName() override { return "Composite Matinfo map"; }
};

class TerrainBlankInfoMapFeatGLSL : public ShaderFeatureGLSL
{
public:

   void processPix(Vector<ShaderComponent*> &componentList,
      const MaterialFeatureData &fd) override;

   String getName() override { return "Blank Matinfo map"; }
};

class TerrainHeightMapBlendGLSL : public TerrainFeatGLSL
{
public:

   void processVert(Vector<ShaderComponent*>& componentList,
      const MaterialFeatureData& fd) override;

   void processPix(Vector<ShaderComponent*>& componentList,
      const MaterialFeatureData& fd) override;

   String getName() override { return "Terrain Heightmap Blend"; }
};

#endif // _TERRFEATUREGLSL_H_
