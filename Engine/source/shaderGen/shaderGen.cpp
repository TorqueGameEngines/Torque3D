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
#include "shaderGen/shaderGen.h"

#include "shaderGen/conditionerFeature.h"
#include "core/stream/fileStream.h"
#include "shaderGen/featureMgr.h"
#include "shaderGen/shaderOp.h"
#include "gfx/gfxDevice.h"
#include "core/memVolume.h"
#include "core/module.h"

#ifdef TORQUE_D3D11
#include "shaderGen/HLSL/customFeatureHLSL.h"
#endif
#ifdef TORQUE_OPENGL
#include "shaderGen/GLSL/customFeatureGLSL.h"
#endif

static const U32 gStageOrder[] =
{
   GFXShaderStage::VERTEX_SHADER,
   GFXShaderStage::HULL_SHADER,
   GFXShaderStage::DOMAIN_SHADER,
   GFXShaderStage::GEOMETRY_SHADER,
   GFXShaderStage::PIXEL_SHADER,
   GFXShaderStage::COMPUTE_SHADER
};

static const char* _getStagePostfix(GFXShaderStage stage)
{
   switch (stage)
   {
   case GFXShaderStage::VERTEX_SHADER:   return "_V";
   case GFXShaderStage::HULL_SHADER:     return "_H";
   case GFXShaderStage::DOMAIN_SHADER:   return "_D";
   case GFXShaderStage::GEOMETRY_SHADER: return "_G";
   case GFXShaderStage::PIXEL_SHADER:    return "_P";
   case GFXShaderStage::COMPUTE_SHADER:  return "_C";
   }

   return "_U"; // Unknown
}

MODULE_BEGIN( ShaderGen )

   MODULE_INIT_BEFORE( GFX )
   MODULE_SHUTDOWN_AFTER( GFX )

   MODULE_INIT
   {
      ManagedSingleton< ShaderGen >::createSingleton();
   }

   MODULE_SHUTDOWN
   {
      ManagedSingleton< ShaderGen >::deleteSingleton();
   }

MODULE_END;

String ShaderGen::smCommonShaderPath("shaders/common");

ShaderGen::ShaderGen()
{
   mInit = false;
   GFXDevice::getDeviceEventSignal().notify(this, &ShaderGen::_handleGFXEvent);
   mOutput = NULL;
}

ShaderGen::~ShaderGen()
{
   GFXDevice::getDeviceEventSignal().remove(this, &ShaderGen::_handleGFXEvent);
   _uninit();

   mFileCache.clear();
}

void ShaderGen::registerInitDelegate(GFXAdapterType adapterType, ShaderGenInitDelegate& initDelegate)
{
   mInitDelegates[(U32)adapterType] = initDelegate;
}

bool ShaderGen::_handleGFXEvent(GFXDevice::GFXDeviceEventType event)
{
   switch (event)
   {
   case GFXDevice::deInit :
      initShaderGen();
      break;
   case GFXDevice::deDestroy :
      {
         flushProceduralShaders();
      }
      break;
   default :
      break;
   }
   return true;
}

void ShaderGen::initShaderGen()
{
   if (mInit)
      return;

   const GFXAdapterType adapterType = GFX->getAdapterType();
   const bool isGl = adapterType == GFXAdapterType::OpenGL;

   if (!mInitDelegates[adapterType])
      return;

   smCommonShaderPath = String(Con::getVariable("$Core::CommonShaderPath", "shaders/common"));

   mInitDelegates[adapterType](this);
   mFeatureInitSignal.trigger( adapterType );
   mInit = true;

   String shaderPath = Con::getVariable( "$shaderGen::cachePath");
   if (!shaderPath.equal( "shadergen:" ) && !shaderPath.isEmpty() )
   {
      // this is necessary, especially under Windows with UAC enabled
      if (!Torque::FS::VerifyWriteAccess(shaderPath))
      {
         // we don't have write access so enable the virtualized memory store
         Con::warnf("ShaderGen: Write permission unavailable, switching to virtualized memory storage");
         shaderPath.clear();
      }

   }

   if ( shaderPath.equal( "shadergen:" ) || shaderPath.isEmpty() )
   {
      // If we didn't get a path then we're gonna cache the shaders to
      // a virtualized memory file system.
      mMemFS = new Torque::Mem::MemFileSystem( "shadergen:/" );
      Torque::FS::Mount( "shadergen", mMemFS );
   }
   else
      Torque::FS::Mount( "shadergen", shaderPath + "/" );

   // Delete the auto-generated conditioner include file.
   Torque::FS::Remove( "shadergen:/" + ConditionerFeature::ConditionerIncludeFileName );

   Vector<String> fileList;
   String pattern = "*.";
   pattern += isGl ? "glsl" : "hlsl";
   S32 numShaderFiles = Torque::FS::FindByPattern("shadergen:/", pattern, false, fileList);
   for (U32 i = 0; i < numShaderFiles; i++)
   {
      Torque::Path filePath = fileList[i];
      mFileCache[filePath.getFileName()] = true;
   }

   // build our type maps.
   LangElement::buildTypeMaps();
}

void ShaderGen::generateShader( const MaterialFeatureData& featureData,
                                ShaderData* shaderData,
                                const GFXVertexFormat *vertexFormat,
                                const char* cacheName,
                                Vector<GFXShaderMacro> &macros)
{
   PROFILE_SCOPE( ShaderGen_GenerateShader );

   mFeatureData = featureData;
   mVertexFormat = vertexFormat;
   mInstancingFormat.clear();

   _uninit();
   _init();

   const FeatureSet& features = mFeatureData.features;
   U32 stages = 0;

   // loop through and see which stages this featureset is expecting to make.
   for (U32 i = 0; i < features.getCount(); i++)
   {

      const FeatureType& type = features.getAt(i);
      ShaderFeature* feat = FEATUREMGR->getByType(type);
      stages |= feat->getShaderStages();

   }

   for (U32 s = 0; s < (sizeof(gStageOrder) / sizeof(U32)); s++)
   {
      U32 stage = gStageOrder[s];

      // skip unused stages
      if (!(stages & stage))
         continue;

      bool skipRegen = !Con::getBoolVariable("ShaderGen::GenNewShaders", true);
      GFXShaderStage curStage = (GFXShaderStage)stage;

      char fileName[256];
      const char* postfix = _getStagePostfix(curStage);
      String stageName;

      if (curStage & GFXShaderStage::VERTEX_SHADER)
         stageName += vertexFormat->getDescription();

      // build our filename.
      for (U32 i = 0; i < features.getCount(); i++)
      {
         const FeatureType& type = features.getAt(i);
         if (stage & FEATUREMGR->getByType(type)->getShaderStages())
         {
            stageName += type.getName();
         }
      }

      stageName = Torque::getStringHash64(stageName);
      stageName += postfix;

      FileCacheSet::iterator file = mFileCache.find(stageName);
      if (file != mFileCache.end())
      {
         // set the shaderdata file for this stage, shaderdata ptr needs to be passed in here.
         dSprintf(fileName, sizeof(fileName), "shadergen:/%s.%s", stageName.c_str(), mFileEnding.c_str());
         shaderData->setShaderStageFile(curStage, fileName);
         if (!(curStage & GFXShaderStage::VERTEX_SHADER))
         {
            continue;
         }

         skipRegen = true;
      }

      mFileCache[stageName] = true;

      dSprintf(fileName, sizeof(fileName), "shadergen:/%s.%s", stageName.c_str(), mFileEnding.c_str());

      shaderData->setShaderStageFile(curStage, fileName);

      mOutput = new MultiLine;
      FileStream* stream = new FileStream();
      if (!skipRegen)
      {
         if (!stream->open(fileName, Torque::FS::File::Write))
         {
            AssertFatal(false, "Failed to open Shader Stream");
            return;
         }
      }

      switch (curStage)
      {
      case VERTEX_SHADER:
         _processVertFeatures(macros, skipRegen);
         if (skipRegen)
            continue;
         _printVertShader(*stream);
         ((ShaderConnector*)mComponents[C_CONNECTOR])->reset();
         break;
      case PIXEL_SHADER:
         _processPixFeatures(macros, skipRegen);
         if (skipRegen)
            continue;
         _printPixShader(*stream);
         break;
      case GEOMETRY_SHADER:
         break;
      case DOMAIN_SHADER:
         break;
      case HULL_SHADER:
         break;
      case COMPUTE_SHADER:
         break;
      case ALL_STAGES:
         break;
      default:
         break;
      }

      delete stream;
      LangElement::deleteElements();

   }
}

void ShaderGen::_init()
{
   _createComponents();
}

void ShaderGen::_uninit()
{
   for( U32 i=0; i<mComponents.size(); i++ )
   {
      delete mComponents[i];
      mComponents[i] = NULL;
   }
   mComponents.setSize(0);

   LangElement::deleteElements();

   Var::reset();
}

void ShaderGen::_createComponents()
{
   ShaderComponent* vertComp = mComponentFactory->createVertexInputConnector( *mVertexFormat );
   mComponents.push_back(vertComp);

   ShaderComponent* vertPixelCon = mComponentFactory->createVertexPixelConnector();
   mComponents.push_back(vertPixelCon);

   ShaderComponent* vertParamDef = mComponentFactory->createVertexParamsDef();
   mComponents.push_back(vertParamDef);

   ShaderComponent* pixParamDef = mComponentFactory->createPixelParamsDef();
   mComponents.push_back(pixParamDef);
}

//----------------------------------------------------------------------------
// Process features
//----------------------------------------------------------------------------
void ShaderGen::_processVertFeatures( Vector<GFXShaderMacro> &macros, bool macrosOnly )
{
   const FeatureSet &features = mFeatureData.features;

   for( U32 i=0; i < features.getCount(); i++ )
   {
      S32 index;
      const FeatureType &type = features.getAt( i, &index );
      FeatureParamsBase* args = features.getArguments(i);
      ShaderFeature* feature = nullptr;
      if(args)
         feature = FEATUREMGR->createFeature(type, args);
      else
         feature = FEATUREMGR->getByType( type );

      if ( feature && (feature->getShaderStages() & GFXShaderStage::VERTEX_SHADER))
      {
         feature->setProcessIndex( index );

         feature->processVertMacros( macros, mFeatureData );

         feature->setInstancingFormat( &mInstancingFormat );

         feature->mVertexFormat = mVertexFormat;

         feature->processVert( mComponents, mFeatureData );

         if (macrosOnly)
            continue;

         String line;
         if ( index > -1 )
            line = String::ToString( "   // %s %d\r\n", feature->getName().c_str(), index );
         else
            line = String::ToString( "   // %s\r\n", feature->getName().c_str() );
         mOutput->addStatement( new GenOp( line ) );

         if ( feature->getOutput() )
            mOutput->addStatement( feature->getOutput() );

         feature->reset();
         mOutput->addStatement( new GenOp( "   \r\n" ) );
      }
   }

   ShaderConnector *connect = dynamic_cast<ShaderConnector *>( mComponents[C_CONNECTOR] );
   connect->sortVars();
}

void ShaderGen::_processPixFeatures( Vector<GFXShaderMacro> &macros, bool macrosOnly )
{
   const FeatureSet &features = mFeatureData.features;

   for( U32 i=0; i < features.getCount(); i++ )
   {
      S32 index;
      const FeatureType &type = features.getAt( i, &index );
      FeatureParamsBase* args = features.getArguments(i);
      ShaderFeature* feature = nullptr;
      if (args)
         feature = FEATUREMGR->createFeature(type, args);
      else
         feature = FEATUREMGR->getByType(type);
      if ( feature && (feature->getShaderStages() & GFXShaderStage::PIXEL_SHADER))
      {
         feature->setProcessIndex( index );

         feature->processPixMacros( macros, mFeatureData );

         if ( macrosOnly )
            continue;

         feature->setInstancingFormat( &mInstancingFormat );
         feature->processPix( mComponents, mFeatureData );

         String line;
         if ( index > -1 )
            line = String::ToString( "   // %s %d\r\n", feature->getName().c_str(), index );
         else
            line = String::ToString( "   // %s\r\n", feature->getName().c_str() );
         mOutput->addStatement( new GenOp( line ) );

         if ( feature->getOutput() )
            mOutput->addStatement( feature->getOutput() );

         feature->reset();
         mOutput->addStatement( new GenOp( "   \r\n" ) );
      }
   }

   ShaderConnector *connect = dynamic_cast<ShaderConnector *>( mComponents[C_CONNECTOR] );
   connect->sortVars();
}

void ShaderGen::_printFeatureList(Stream &stream)
{
   mPrinter->printLine(stream, "// Features:");

   const FeatureSet &features = mFeatureData.features;

   for( U32 i=0; i < features.getCount(); i++ )
   {
      S32 index;
      const FeatureType &type = features.getAt( i, &index );
      FeatureParamsBase* args = features.getArguments(i);
      ShaderFeature* feature = nullptr;
      if (args)
         feature = FEATUREMGR->createFeature(type, args);
      else
         feature = FEATUREMGR->getByType(type);
      if ( feature )
      {
         String line;
         if ( index > -1 )
            line = String::ToString( "// %s %d", feature->getName().c_str(), index );
         else
            line = String::ToString( "// %s", feature->getName().c_str() );

         mPrinter->printLine( stream, line );
      }
   }

   mPrinter->printLine(stream, "");
}

void ShaderGen::_printDependencies(Stream &stream, GFXShaderStage stage)
{
   Vector<const ShaderDependency *> dependencies;

   for( U32 i=0; i < FEATUREMGR->getFeatureCount(); i++ )
   {
      const FeatureInfo &info = FEATUREMGR->getAt( i );
      if ( mFeatureData.features.hasFeature( *info.type ) )
         dependencies.merge( info.feature->getDependencies() );
   }

   // Do a quick loop removing any duplicate dependancies.
   for( U32 i=0; i < dependencies.size(); )
   {
      bool dup = false;

      for( U32 j=0; j < dependencies.size(); j++ )
      {
         if (  j != i &&
               *dependencies[i] == *dependencies[j] )
         {
            dup = true;
            break;
         }
      }

      if ( dup )
         dependencies.erase( i );
      else
         i++;
   }

   // Print dependencies
   if( dependencies.size() > 0 )
   {
      mPrinter->printLine(stream, "// Dependencies:");

      for( S32 i = 0; i < dependencies.size(); i++ )
         dependencies[i]->print( stream, stage);

      mPrinter->printLine(stream, "");
   }
}

void ShaderGen::_printFeatures( Stream &stream )
{
   mOutput->print( stream );
}

void ShaderGen::_printVertShader( Stream &stream )
{
   mPrinter->printShaderHeader(stream);

   _printDependencies(stream, GFXShaderStage::VERTEX_SHADER); // TODO: Split into vert and pix dependencies?
   _printFeatureList(stream);

   // print out structures
   mComponents[C_VERT_STRUCT]->print( stream, true );
   mComponents[C_CONNECTOR]->print( stream, true );

   mPrinter->printMainComment(stream);

   mComponents[C_VERT_MAIN]->print( stream, true );
   mComponents[C_VERT_STRUCT]->printOnMain( stream, true );

   // print out the function
   _printFeatures( stream );

   mPrinter->printVertexShaderCloser(stream);
}

void ShaderGen::_printPixShader( Stream &stream )
{
   mPrinter->printShaderHeader(stream);

   _printDependencies(stream, GFXShaderStage::PIXEL_SHADER); // TODO: Split into vert and pix dependencies?
   _printFeatureList(stream);

   mComponents[C_CONNECTOR]->print( stream, false );

   mPrinter->printPixelShaderOutputStruct(stream, mFeatureData);
   mPrinter->printMainComment(stream);

   mComponents[C_PIX_MAIN]->print( stream, false );
   mComponents[C_CONNECTOR]->printOnMain( stream, false );

   // print out the function
   _printFeatures( stream );

   mPrinter->printPixelShaderCloser(stream);
}

GFXShader* ShaderGen::getShader(const MaterialFeatureData& featureData, const GFXVertexFormat* vertexFormat, const Vector<GFXShaderMacro>* macros, const Vector<String>& samplers)
{
   PROFILE_SCOPE(ShaderGen_GetShader);

   const FeatureSet& features = featureData.codify();

   // Build a description string from the features
   // and vertex format combination ( and macros ).
   String shaderDescription = vertexFormat->getDescription() + features.getDescription();

   String cacheKey = Torque::getStringHash64(shaderDescription);

   ShaderDataMap::iterator dat = mProcShaderData.find(cacheKey);
   if (dat != mProcShaderData.end())
   {
      Vector<GFXShaderMacro> shaderMacros;
      shaderMacros.push_back(GFXShaderMacro("TORQUE_SHADERGEN"));
      if (macros)
         shaderMacros.merge(*macros);

      // should we loop vertex shader features to build mInstancingFormat before sending it down to see old hob?
      return dat->value->getShader(shaderMacros);
   }

   ShaderData* shaderData = new ShaderData;

   shaderData->setPixVersion(GFX->getPixelShaderVersion());

   for (U32 samp = 0; samp < samplers.size(); samp++)
   {
      shaderData->setSamplerName(samplers[samp], samp);
   }

   Vector<GFXShaderMacro> shaderMacros;
   shaderMacros.push_back(GFXShaderMacro("TORQUE_SHADERGEN"));
   if (macros)
      shaderMacros.merge(*macros);

   generateShader(featureData, shaderData, vertexFormat, cacheKey, shaderMacros);

   shaderData->setInstancingFormat(&mInstancingFormat);
   shaderData->registerObject();

   mProcShaderData[cacheKey] = shaderData;
   return shaderData->getShader(shaderMacros);
}

void ShaderGen::flushProceduralShaders()
{
   for (auto data : mProcShaderData)
   {
      data.value->deleteObject();
   }

   mProcShaderData.clear();
}
