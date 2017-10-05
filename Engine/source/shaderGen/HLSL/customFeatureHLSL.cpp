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

#include "customFeatureHLSL.h"
#include "shaderGen/shaderFeature.h"
#include "shaderGen/shaderOp.h"
#include "shaderGen/featureMgr.h"
//#include "materials/materialFeatureTypes.h"
//#include "gfx/gfxDevice.h"
//#include "materials/processedMaterial.h"

//****************************************************************************
// Accu Texture
//****************************************************************************
void CustomFeatureHLSL::processVert(Vector<ShaderComponent*> &componentList,
	const MaterialFeatureData &fd)
{
	/*MultiLine *meta = new MultiLine;
	getOutTexCoord(   "texCoord",
	"float2",
	false,
	meta,
	componentList );

	getOutObjToTangentSpace( componentList, meta, fd );

	output = meta;*/

	if (mOwner->isMethod("processVertHLSL"))
		Con::executef(mOwner, "processVertHLSL");
}

void CustomFeatureHLSL::processPix(Vector<ShaderComponent*> &componentList,
	const MaterialFeatureData &fd)
{
	meta = new MultiLine;
	
	/*MultiLine *meta = new MultiLine;

	output = meta;

	// OUT.col
	Var *color = (Var*) LangElement::find( "col1" );
	if (!color)
	{
	output = new GenOp("   //NULL COLOR!");
	return;
	}

	// accu map
	Var *accuMap = new Var;
	accuMap->setType("SamplerState");

	accuMap->setName( "accuMap" );
	accuMap->uniform = true;
	accuMap->sampler = true;
	accuMap->constNum = Var::getTexUnitNum();     // used as texture unit num here

	// accuColor var
	Var *accuColor = new Var;
	accuColor->setType( "float4" );
	accuColor->setName( "accuColor" );
	LangElement *colorAccuDecl = new DecOp( accuColor );

	// plc (placement)
	Var *accuPlc = new Var;
	accuPlc->setType( "float4" );
	accuPlc->setName( "plc" );
	LangElement *plcAccu = new DecOp( accuPlc );

	// accu constants
	Var *accuScale = (Var*)LangElement::find( "accuScale" );
	if ( !accuScale )
	{
	accuScale = new Var;
	accuScale->setType( "float" );
	accuScale->setName( "accuScale" );
	accuScale->uniform = true;
	accuScale->sampler = false;
	accuScale->constSortPos = cspPotentialPrimitive;
	}
	Var *accuDirection = (Var*)LangElement::find( "accuDirection" );
	if ( !accuDirection )
	{
	accuDirection = new Var;
	accuDirection->setType( "float" );
	accuDirection->setName( "accuDirection" );
	accuDirection->uniform = true;
	accuDirection->sampler = false;
	accuDirection->constSortPos = cspPotentialPrimitive;
	}
	Var *accuStrength = (Var*)LangElement::find( "accuStrength" );
	if ( !accuStrength )
	{
	accuStrength = new Var;
	accuStrength->setType( "float" );
	accuStrength->setName( "accuStrength" );
	accuStrength->uniform = true;
	accuStrength->sampler = false;
	accuStrength->constSortPos = cspPotentialPrimitive;
	}
	Var *accuCoverage = (Var*)LangElement::find( "accuCoverage" );
	if ( !accuCoverage )
	{
	accuCoverage = new Var;
	accuCoverage->setType( "float" );
	accuCoverage->setName( "accuCoverage" );
	accuCoverage->uniform = true;
	accuCoverage->sampler = false;
	accuCoverage->constSortPos = cspPotentialPrimitive;
	}
	Var *accuSpecular = (Var*)LangElement::find( "accuSpecular" );
	if ( !accuSpecular )
	{
	accuSpecular = new Var;
	accuSpecular->setType( "float" );
	accuSpecular->setName( "accuSpecular" );
	accuSpecular->uniform = true;
	accuSpecular->sampler = false;
	accuSpecular->constSortPos = cspPotentialPrimitive;
	}

	Var *inTex = getInTexCoord( "texCoord", "float2", componentList );
	Var *accuVec = getInTexCoord( "accuVec", "float3", componentList );
	Var *bumpNorm = (Var *)LangElement::find( "bumpSample" );
	if( bumpNorm == NULL )
	{
	bumpNorm = (Var *)LangElement::find( "bumpNormal" );
	if (!bumpNorm)
	return;
	}

	// get the accu pixel color

	Var *accuMapTex = new Var;
	accuMapTex->setType("Texture2D");
	accuMapTex->setName("accuMapTex");
	accuMapTex->uniform = true;
	accuMapTex->texture = true;
	accuMapTex->constNum = accuMap->constNum;
	meta->addStatement(new GenOp("   @ = @.Sample(@, @ * @);\r\n", colorAccuDecl, accuMapTex, accuMap, inTex, accuScale));

	// scale up normals
	meta->addStatement( new GenOp( "   @.xyz = @.xyz * 2.0 - 0.5;\r\n", bumpNorm, bumpNorm ) );

	// assign direction
	meta->addStatement( new GenOp( "   @.z *= @*2.0;\r\n", accuVec, accuDirection ) );

	// saturate based on strength
	meta->addStatement( new GenOp( "   @ = saturate( dot( @.xyz, @.xyz * pow(@, 5) ) );\r\n", plcAccu, bumpNorm, accuVec, accuStrength ) );

	// add coverage
	meta->addStatement( new GenOp( "   @.a += (2 * pow(@/2, 5)) - 0.5;\r\n", accuPlc, accuCoverage ) );

	// clamp to a sensible value
	meta->addStatement( new GenOp( "   @.a = clamp(@.a, 0, 1);\r\n", accuPlc, accuPlc ) );

	// light
	Var *lightColor = (Var*) LangElement::find( "d_lightcolor" );
	if(lightColor != NULL)
	meta->addStatement( new GenOp( "   @ *= float4(@, 1.0);\r\n\r\n", accuColor, lightColor ) );

	// lerp with current pixel - use the accu alpha as well
	meta->addStatement( new GenOp( "   @ = lerp( @, @, @.a * @.a);\r\n", color, color, accuColor, accuPlc, accuColor ) );

	// the result should always be opaque
	meta->addStatement( new GenOp( "   @.a = 1.0;\r\n", color ) );*/
	if (mOwner->isMethod("processPixelHLSL"))
		Con::executef(mOwner, "processPixelHLSL");

	output = meta;
}

void CustomFeatureHLSL::setTexData(Material::StageData &stageDat,
	const MaterialFeatureData &fd,
	RenderPassData &passData,
	U32 &texIndex)
{
	//GFXTextureObject *tex = stageDat.getTex( MFT_AccuMap );
	//if ( tex )
	//{
	//passData.mSamplerNames[ texIndex ] = "AccuMap";
	//passData.mTexType[ texIndex++ ] = Material::AccuMap;
	//}

	if (mOwner->isMethod("setTextureData"))
		Con::executef(mOwner, "setTextureData");
}

void CustomFeatureHLSL::writeLine(String format, S32 argc, ConsoleValueRef *argv)
{
	//do the var/arg fetching here
	meta->addStatement(new GenOp(format + "\n"/*, colorAccuDecl, accuMapTex, accuMap, inTex, accuScale*/));
}