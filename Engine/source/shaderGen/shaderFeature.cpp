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

#include "platform/platform.h"
#include "shaderGen/shaderFeature.h"

#include "shaderGen/langElement.h"
#include "shaderGen/shaderOp.h"


void ShaderFeature::addDependency( const ShaderDependency *dependsOn )
{
   for ( U32 i = 0; i < mDependencies.size(); i++ )
   {
      if ( *mDependencies[i] == *dependsOn )
         return;
   }

   mDependencies.push_back( dependsOn );
}

Var* ShaderFeature::getVertTexCoord(const String& name)
{
   Var* inTex = NULL;

   for (U32 i = 0; i < LangElement::elementList.size(); i++)
   {
      if (!String::compare((char*)LangElement::elementList[i]->name, name.c_str()))
      {
         inTex = dynamic_cast<Var*>(LangElement::elementList[i]);
         if (inTex)
         {
            // NOTE: This used to do this check...
            //
            // String::compare( (char*)inTex->structName, "IN" )
            //
            // ... to ensure that the var was from the input
            // vertex structure, but this kept some features
            // ( ie. imposter vert ) from decoding their own
            // coords for other features to use.
            //
            // If we run into issues with collisions between
            // IN vars and local vars we may need to revise.

            break;
         }
      }
   }

   return inTex;
}

LangElement* ShaderFeature::expandNormalMap(LangElement* sampleNormalOp, LangElement* normalDecl, LangElement* normalVar, const MaterialFeatureData& fd)
{
   MultiLine* meta = new MultiLine;
   const bool hasBc3 = fd.features.hasFeature(MFT_IsBC3nm, getProcessIndex());
   const bool hasBc5 = fd.features.hasFeature(MFT_IsBC5nm, getProcessIndex());

   if (hasBc3 || hasBc5)
   {
      if (fd.features[MFT_ImposterVert])
      {
         // The imposter system uses object space normals and
         // encodes them with the z axis in the alpha component.
         meta->addStatement(new GenOp("   @ = @( normalize( @.xyw * 2.0 - 1.0 ), 0.0 ); // Obj DXTnm\r\n", normalDecl, new TypeOp(GFXSCT_Float4), sampleNormalOp));
      }
      else if (hasBc3)
      {
         // BC3 Swizzle trick
         meta->addStatement(new GenOp("   @ = @( @.ag * 2.0 - 1.0, 0.0, 0.0 ); // DXTnm\r\n", normalDecl, new TypeOp(GFXSCT_Float4), sampleNormalOp));
         meta->addStatement(new GenOp("   @.z = sqrt( 1.0 - dot( @.xy, @.xy ) ); // DXTnm\r\n", normalVar, normalVar, normalVar));
      }
      else if (hasBc5)
      {
         // BC5
         meta->addStatement(new GenOp("   @ = @( @.gr * 2.0 - 1.0, 0.0, 0.0 ); // bc5nm\r\n", normalDecl, new TypeOp(GFXSCT_Float4), sampleNormalOp));
         meta->addStatement(new GenOp("   @.z = sqrt( 1.0 - dot( @.xy, @.xy ) ); // bc5nm\r\n", normalVar, normalVar, normalVar));
      }
   }
   else
   {
      meta->addStatement(new GenOp("   @ = @;\r\n", normalDecl, sampleNormalOp));
      meta->addStatement(new GenOp("   @.xyz = @.xyz * 2.0 - 1.0;\r\n", normalVar, normalVar));
   }

   return meta;
}

ShaderFeature::Resources ShaderFeature::getResources( const MaterialFeatureData &fd )
{
   Resources temp; 
   return temp; 
}

const char* ShaderFeature::getOutputTargetVarName( OutputTarget target ) const
{
   const char* targName = "col";

   switch(target)
   {
      case DefaultTarget:
         targName = "col";
         break;

      case RenderTarget1:
      targName = "col1";
         break;

      case RenderTarget2:
         targName = "col2";
         break;

      case RenderTarget3:
         targName = "col3";
         break;

      case RenderTarget4:
         targName = "col4";
         break;

      case RenderTarget5:
         targName = "col5";
         break;
   }

   return targName;
}

Var* ShaderFeature::findOrCreateLocal( const char *name, 
                                       const char *type, 
                                       MultiLine *multi )
{
   Var *outVar = (Var*)LangElement::find( name );
   if ( !outVar )
   {
      outVar = new Var;
      outVar->setType( type );
      outVar->setName( name );
      multi->addStatement( new GenOp( "   @;\r\n", new DecOp( outVar ) ) );
   }

   return outVar;
}

void ShaderFeature::setInstancingFormat(GFXVertexFormat *format)
{
   mInstancingFormat = format;
}
