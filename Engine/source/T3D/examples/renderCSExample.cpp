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

#include "T3D/examples/renderCSExample.h"

#include "math/mathIO.h"
#include "scene/sceneRenderState.h"
#include "core/stream/bitStream.h"
#include "materials/sceneData.h"
#include "gfx/gfxDebugEvent.h"
#include "gfx/gfxTransformSaver.h"
#include "materials/shaderData.h"
#include "renderInstance/renderPassManager.h"


IMPLEMENT_CO_NETOBJECT_V1(RenderCSExample);

ConsoleDocClass(RenderCSExample,
   "@brief An example scene object which renders using a callback.\n\n"
   "This class implements a basic SceneObject that can exist in the world at a "
   "3D position and render itself. Note that RenderObjectExample handles its own "
   "rendering by submitting itself as an ObjectRenderInst (see "
   "renderInstance\renderPassmanager.h) along with a delegate for its render() "
   "function. However, the preffered rendering method in the engine is to submit "
   "a MeshRenderInst along with a Material, vertex buffer, primitive buffer, and "
   "transform and allow the RenderMeshMgr handle the actual rendering. You can "
   "see this implemented in RenderMeshExample.\n\n"
   "See the C++ code for implementation details.\n\n"
   "@ingroup Examples\n");

GFX_ImplementTextureProfile(CSTargetTextureProfile,
                           GFXTextureProfile::DiffuseMap,
                           GFXTextureProfile::AllowUav |
                           GFXTextureProfile::Pooled,
                           GFXTextureProfile::NONE);

//-----------------------------------------------------------------------------
// Object setup and teardown
//-----------------------------------------------------------------------------
RenderCSExample::RenderCSExample()
{
   // Flag this object so that it will always
   // be sent across the network to clients
   mNetFlags.set(Ghostable | ScopeAlways);

   // Set it as a "static" object
   mTypeMask |= StaticObjectType | StaticShapeObjectType;

   mComputeTarget = NULL;
   mConstShaderTest = NULL;
}

RenderCSExample::~RenderCSExample()
{
}

//-----------------------------------------------------------------------------
// Object Editing
//-----------------------------------------------------------------------------
void RenderCSExample::initPersistFields()
{
   docsURL;
   // SceneObject already handles exposing the transform

   Parent::initPersistFields();
}

bool RenderCSExample::onAdd()
{
   if (!Parent::onAdd())
      return false;

   // Set up a 1x1x1 bounding box
   mObjBox.set(Point3F(-0.5f, -0.5f, -0.5f),
      Point3F(0.5f, 0.5f, 0.5f));

   resetWorldBox();

   // Add this object to the scene
   addToScene();

   if (isClientObject())
   {
      // Find ShaderData
      ShaderData* shaderData;
      mShader = Sim::findObject("ComputeTextureShader", shaderData) ? shaderData->getShader() : NULL;
      if (!mShader)
      {
         Con::errorf("RenderCSExample::onAdd - could not find ComputeTextureShader");
         return false;
      }

      mShaderConsts = mShader->allocConstBuffer();
      mModelViewSC = mShader->getShaderConstHandle("$modelview");

      mCompShader = Sim::findObject("ComputeTestShader", shaderData) ? shaderData->getShader() : NULL;
      if (!mCompShader)
      {
         Con::errorf("RenderCSExample::onAdd - could not find ComputeTestShader");
         return false;
      }

      mCompShaderConsts = mCompShader->allocConstBuffer();


   }

   return true;
}

void RenderCSExample::onRemove()
{
   // Remove this object from the scene
   removeFromScene();

   Parent::onRemove();
}

void RenderCSExample::setTransform(const MatrixF& mat)
{
   // Let SceneObject handle all of the matrix manipulation
   Parent::setTransform(mat);

   // Dirty our network mask so that the new transform gets
   // transmitted to the client object
   setMaskBits(TransformMask);
}

U32 RenderCSExample::packUpdate(NetConnection* conn, U32 mask, BitStream* stream)
{
   // Allow the Parent to get a crack at writing its info
   U32 retMask = Parent::packUpdate(conn, mask, stream);

   // Write our transform information
   if (stream->writeFlag(mask & TransformMask))
   {
      mathWrite(*stream, getTransform());
      mathWrite(*stream, getScale());
   }

   return retMask;
}

void RenderCSExample::unpackUpdate(NetConnection* conn, BitStream* stream)
{
   // Let the Parent read any info it sent
   Parent::unpackUpdate(conn, stream);

   if (stream->readFlag())  // TransformMask
   {
      mathRead(*stream, &mObjToWorld);
      mathRead(*stream, &mObjScale);

      setTransform(mObjToWorld);
   }
}

//-----------------------------------------------------------------------------
// Object Rendering
//-----------------------------------------------------------------------------
void RenderCSExample::createGeometry()
{
   // Fill the vertex buffer
   VertexType* pVert = NULL;

   mVertexBuffer.set(GFX, 36, GFXBufferTypeStatic);
   pVert = mVertexBuffer.lock();

   Point3F halfSize = getObjBox().getExtents() * 0.5f;

   // We don't bother sharing
   // vertices here, in order to
   // avoid using a primitive buffer.
   pVert[0].point.set(-1, -1, 1);
   pVert[1].point.set(1, -1, 1);
   pVert[2].point.set(1, -1, -1);

   pVert[0].texCoord.set(0, 0);
   pVert[1].texCoord.set(1.0f, 0);
   pVert[2].texCoord.set(1.0f, 1.0f);

   pVert[3].point.set(-1, -1, 1);
   pVert[4].point.set(1, -1, -1);
   pVert[5].point.set(-1, -1, -1);

   pVert[3].texCoord.set(0, 0);
   pVert[4].texCoord.set(1.0f, 1.0f);
   pVert[5].texCoord.set(0, 1.0f);

   pVert[6].point.set(1, -1, 1);
   pVert[7].point.set(1, 1, 1);
   pVert[8].point.set(1, 1, -1);

   pVert[6].texCoord.set(0, 0);
   pVert[7].texCoord.set(1.0f, 0);
   pVert[8].texCoord.set(1.0f, 1.0f);

   pVert[9].point.set(1, -1, 1);
   pVert[10].point.set(1, 1, -1);
   pVert[11].point.set(1, -1, -1);

   pVert[9].texCoord.set(0, 0);
   pVert[10].texCoord.set(1.0f, 1.0f);
   pVert[11].texCoord.set(0, 1.0f);

   pVert[12].point.set(-1, 1, 1);
   pVert[13].point.set(-1, -1, 1);
   pVert[14].point.set(-1, -1, -1);

   pVert[12].texCoord.set(0, 0);
   pVert[13].texCoord.set(1.0f, 0);
   pVert[14].texCoord.set(1.0f, 1.0f);

   pVert[15].point.set(-1, 1, 1);
   pVert[16].point.set(-1, -1, -1);
   pVert[17].point.set(-1, 1, -1);

   pVert[15].texCoord.set(0, 0);
   pVert[16].texCoord.set(1.0f, 1.0f);
   pVert[17].texCoord.set(1.0f, 0);

   pVert[18].point.set(1, 1, 1);
   pVert[19].point.set(-1, 1, 1);
   pVert[20].point.set(-1, 1, -1);

   pVert[18].texCoord.set(0, 0);
   pVert[19].texCoord.set(1.0f, 0);
   pVert[20].texCoord.set(1.0f, 1.0f);

   pVert[21].point.set(1, 1, 1);
   pVert[22].point.set(-1, 1, -1);
   pVert[23].point.set(1, 1, -1);

   pVert[21].texCoord.set(0, 0);
   pVert[22].texCoord.set(1.0f, 1.0f);
   pVert[23].texCoord.set(0, 1.0f);

   pVert[24].point.set(-1, -1, 1);
   pVert[25].point.set(-1, 1, 1);
   pVert[26].point.set(1, 1, 1);

   pVert[24].texCoord.set(0, 0);
   pVert[25].texCoord.set(1.0f, 0);
   pVert[26].texCoord.set(1.0f, 1.0f);

   pVert[27].point.set(-1, -1, 1);
   pVert[28].point.set(1, 1, 1);
   pVert[29].point.set(1, -1, 1);

   pVert[27].texCoord.set(0, 0);
   pVert[28].texCoord.set(1.0f, 1.0f);
   pVert[29].texCoord.set(0, 1.0f);

   pVert[30].point.set(1, 1, -1);
   pVert[31].point.set(-1, 1, -1);
   pVert[32].point.set(-1, -1, -1);

   pVert[30].texCoord.set(1.0f, 1.0f);
   pVert[31].texCoord.set(1.0f, 0);
   pVert[32].texCoord.set(0, 0);

   pVert[33].point.set(1, -1, -1);
   pVert[34].point.set(1, 1, -1);
   pVert[35].point.set(-1, -1, -1);

   pVert[33].texCoord.set(0, 1.0f);
   pVert[34].texCoord.set(1.0f, 1.0f);
   pVert[35].texCoord.set(0, 0);

   mVertexBuffer.unlock();

   // Set up our normal and reflection StateBlocks
   GFXStateBlockDesc desc;
   // deferredBuffer sampler
   desc.samplersDefined = true;
   desc.samplers[0].addressModeU = GFXAddressWrap;
   desc.samplers[0].addressModeV = GFXAddressWrap;
   desc.samplers[0].addressModeW = GFXAddressWrap;
   desc.samplers[0].magFilter = GFXTextureFilterLinear;
   desc.samplers[0].minFilter = GFXTextureFilterLinear;
   desc.samplers[0].mipFilter = GFXTextureFilterLinear;
   // The normal StateBlock only needs a default StateBlock
   mNormalSB = GFX->createStateBlock(desc);

   // The reflection needs its culling reversed
   desc.cullDefined = true;
   desc.cullMode = GFXCullCW;
   mReflectSB = GFX->createStateBlock(desc);
}

void RenderCSExample::prepRenderImage(SceneRenderState* state)
{
   // Do a little prep work if needed
   if (mVertexBuffer.isNull())
      createGeometry();

   // Allocate an ObjectRenderInst so that we can submit it to the RenderPassManager
   ObjectRenderInst* ri = state->getRenderPass()->allocInst<ObjectRenderInst>();

   // Now bind our rendering function so that it will get called
   ri->renderDelegate.bind(this, &RenderCSExample::render);

   // Set our RenderInst as a standard object render
   ri->type = RenderPassManager::RIT_Object;

   // Set our sorting keys to a default value
   ri->defaultKey = 0;
   ri->defaultKey2 = 0;

   // Submit our RenderInst to the RenderPassManager
   state->getRenderPass()->addInst(ri);
}

GFXTextureObject* RenderCSExample::_getTestTexture(U32 width, U32 height)
{
   GFXTexHandle testTexture(width, height, GFXFormatB8G8R8A8, &CSTargetTextureProfile, "RenderCSExample::_getTestTexture");
   return testTexture;
}

void RenderCSExample::render(ObjectRenderInst* ri, SceneRenderState* state, BaseMatInstance* overrideMat)
{
   if (overrideMat)
      return;

   if (mVertexBuffer.isNull())
      return;

   PROFILE_SCOPE(RenderObjectExample_Render);

   // Set up a GFX debug event (this helps with debugging rendering events in external tools)
   GFXDEBUGEVENT_SCOPE(RenderObjectExample_Render, ColorI::RED);

   // GFXTransformSaver is a handy helper class that restores
   // the current GFX matrices to their original values when
   // it goes out of scope at the end of the function
   GFXTransformSaver saver;

   if (mComputeTarget == NULL)
   {
      mComputeTarget = _getTestTexture(256, 256);

      GFX->clearTextureStateImmediate(0);
      GFX->setShader(mCompShader);
      GFX->setTexture(0, mComputeTarget);
      GFX->dispatchCompute(256 / 32, 256 / 32, 1);
      GFX->clearTextureStateImmediate(0);
   }

   // Calculate our object to world transform matrix
   MatrixF objectToWorld = getRenderTransform();
   objectToWorld.scale(getScale());

   // Apply our object transform
   GFX->multWorld(objectToWorld);

   MatrixF xform = GFX->getProjectionMatrix();
   xform *= GFX->getViewMatrix();
   xform *= GFX->getWorldMatrix();

   mShaderConsts->setSafe(mModelViewSC, xform);
   
   // Set the vertex buffer
   GFX->setVertexBuffer(mVertexBuffer);

   // Set up the "generic" shaders
   // These handle rendering on GFX layers that don't support
   // fixed function. Otherwise they disable shaders.
   GFX->setShader(mShader);
   //GFX->setupGenericShaders(GFXDevice::GSTexture);
   GFX->setShaderConstBuffer(mShaderConsts);
   GFX->setTexture(0, mComputeTarget);

   // Deal with reflect pass otherwise
   // set the normal StateBlock
   if (state->isReflectPass())
      GFX->setStateBlock(mReflectSB);
   else
      GFX->setStateBlock(mNormalSB);

   // Draw our triangles
   GFX->drawPrimitive(GFXTriangleList, 0, 12);
}
