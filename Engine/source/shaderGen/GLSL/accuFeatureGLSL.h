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

#ifndef _ACCUFEATUREGLSL_H_
#define _ACCUFEATUREGLSL_H_

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

/// Accu texture
class AccuTexFeatGLSL : public ShaderFeatureGLSL
{
public:

   //****************************************************************************
   // Accu Texture
   //****************************************************************************
   void processVert(  Vector<ShaderComponent*> &componentList, 
                              const MaterialFeatureData &fd ) override;

   void processPix(   Vector<ShaderComponent*> &componentList, 
                              const MaterialFeatureData &fd ) override;

   void getAccuVec( MultiLine *meta, LangElement *accuVec );

   Var* addOutAccuVec( Vector<ShaderComponent*> &componentList, MultiLine *meta );

   Material::BlendOp getBlendOp() override{ return Material::LerpAlpha; }

   Resources getResources( const MaterialFeatureData &fd ) override
   {
      Resources res; 
      res.numTex = 1;
      res.numTexReg = 1;
      return res;
   }

   void setTexData(   Material::StageData &stageDat,
                              const MaterialFeatureData &fd,
                              RenderPassData &passData,
                              U32 &texIndex ) override;

   String getName() override
   {
      return "Accu Texture";
   }
};

class AccuScaleFeature : public ShaderFeatureGLSL
{
public:
   void processPix( Vector<ShaderComponent*> &componentList, const MaterialFeatureData &fd ) override
   {
      // Find the constant value
      Var *accuScale = (Var *)( LangElement::find("accuScale") );
      if( accuScale == NULL )
      {
         accuScale = new Var;
         accuScale->setType( "float" );
         accuScale->setName( "accuScale" );
         accuScale->constSortPos = cspPotentialPrimitive;
         accuScale->uniform = true;
      }
   }

   String getName() override { return "Accu Scale"; }
};

class AccuDirectionFeature : public ShaderFeatureGLSL
{
public:
   void processPix( Vector<ShaderComponent*> &componentList, const MaterialFeatureData &fd ) override
   {
      // Find the constant value
      Var *accuDirection = (Var *)( LangElement::find("accuDirection") );
      if( accuDirection == NULL )
      {
         accuDirection = new Var;
         accuDirection->setType( "float" );
         accuDirection->setName( "accuDirection" );
         accuDirection->constSortPos = cspPotentialPrimitive;
         accuDirection->uniform = true;
      }
   }

   String getName() override { return "Accu Direction"; }
};

class AccuStrengthFeature : public ShaderFeatureGLSL
{
public:
   void processPix( Vector<ShaderComponent*> &componentList, const MaterialFeatureData &fd ) override
   {
      // Find the constant value
      Var *accuStrength = (Var *)( LangElement::find("accuStrength") );
      if( accuStrength == NULL )
      {
         accuStrength = new Var;
         accuStrength->setType( "float" );
         accuStrength->setName( "accuStrength" );
         accuStrength->constSortPos = cspPotentialPrimitive;
         accuStrength->uniform = true;
      }
   }

   String getName() override { return "Accu Strength"; }
};

class AccuCoverageFeature : public ShaderFeatureGLSL
{
public:
   void processPix( Vector<ShaderComponent*> &componentList, const MaterialFeatureData &fd ) override
   {
      // Find the constant value
      Var *accuCoverage = (Var *)( LangElement::find("accuCoverage") );
      if( accuCoverage == NULL )
      {
         accuCoverage = new Var;
         accuCoverage->setType( "float" );
         accuCoverage->setName( "accuCoverage" );
         accuCoverage->constSortPos = cspPotentialPrimitive;
         accuCoverage->uniform = true;
      }
   }

   String getName() override { return "Accu Coverage"; }
};


class AccuSpecularFeature : public ShaderFeatureGLSL
{
public:
   void processPix( Vector<ShaderComponent*> &componentList, const MaterialFeatureData &fd ) override
   {
      // Find the constant value
      Var *accuSpecular = (Var *)( LangElement::find("accuSpecular") );
      if( accuSpecular == NULL )
      {
         accuSpecular = new Var;
         accuSpecular->setType( "float" );
         accuSpecular->setName( "accuSpecular" );
         accuSpecular->constSortPos = cspPotentialPrimitive;
         accuSpecular->uniform = true;
      }
   }

   String getName() override { return "Accu Specular"; }
};

#endif