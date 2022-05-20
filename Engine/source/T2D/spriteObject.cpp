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

#include "T2D/spriteObject.h"

#include "math/mathIO.h"
#include "scene/sceneRenderState.h"
#include "core/stream/bitStream.h"
#include "materials/sceneData.h"
#include "gfx/gfxDebugEvent.h"
#include "gfx/gfxTransformSaver.h"
#include "renderInstance/renderPassManager.h"
#include "materials/shaderData.h"

IMPLEMENT_CO_NETOBJECT_V1(SpriteObject);

ConsoleDocClass(SpriteObject,
   "@brief Base object for all T2D objects.\n\n"
   "@ingroup Torque2D\n");

SpriteObject::SpriteObject()
{
   mFrame = 0;
   mLayerMask = 0;
   mColorOverlay = ColorI::WHITE;
   INIT_ASSET(Sprite);
   // Flag this object so that it will always
   // be sent across the network to clients
   mNetFlags.set(Ghostable | ScopeAlways);

   // Set it as a "torque2d" object
   mTypeMask = Torque2DObjectType;
   mFrameDirty = true;

   // shader consts
   mTimeSC = NULL;
   mModelViewProjSC = NULL;
   mTexScaleSC = NULL;
   mTexDirectionSC = NULL;
   mTexOffsetSC = NULL;
   mDiffuseMapSC = NULL;
   mNormalMapSC = NULL;

   mEyePosSC = NULL;
   mWorldPosSC = NULL;
   mAmbientColorSC = NULL;
   mLightColorSC = NULL;
   mLightPositionSC = NULL;
   mLightConfigDataSC = NULL;

}

SpriteObject::~SpriteObject()
{
}

//-----------------------------------------------------------------------------

void SpriteObject::initPersistFields()
{
   addGroup("Sprite Object");
      INITPERSISTFIELD_SPRITEASSET(Sprite, SpriteObject, "A sprite asset to use for this sprite object.");
      addField("SpriteFrame", TypeS32, Offset(mFrame, SpriteObject),"Set frame for this sprite to render.");
      addField("SpriteLayer", TypeS32, Offset(mLayerMask, SpriteObject),"Set layer for this sprite to render on.");
      addField("SpriteColor", TypeColorI, Offset(mColorOverlay, SpriteObject), "Set a color overlay for this sprite object.");
   endGroup("Sprite Object");
   // SceneObject already handles exposing the transform
   Parent::initPersistFields();
}

//-----------------------------------------------------------------------------

bool SpriteObject::onAdd()
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
      _setSprite(getSprite());

      // Find ShaderData
      ShaderData* shaderData;
      mShader = Sim::findObject("SpriteObjectShader", shaderData) ? shaderData->getShader() : NULL;
      if (!mShader)
      {
         Con::errorf("SpriteObject::onAdd - could not find SpriteObjectShader");
         return false;
      }

      // Create ShaderConstBuffer and Handles
      mShaderConsts = mShader->allocConstBuffer();
      mModelViewProjSC = mShader->getShaderConstHandle("$modelView");
      mTimeSC = mShader->getShaderConstHandle("$accumTime");
      mTexScaleSC = mShader->getShaderConstHandle("$texScale");
      mTexDirectionSC = mShader->getShaderConstHandle("$texDirection");
      mTexOffsetSC = mShader->getShaderConstHandle("$texOffset");
      mDiffuseMapSC = mShader->getShaderConstHandle("$diffuseMap");
      mNormalMapSC = mShader->getShaderConstHandle("$normalMap");

      mWorldPosSC = mShader->getShaderConstHandle("$worldPos");
      mEyePosSC = mShader->getShaderConstHandle("$eyePos");
      mAmbientColorSC = mShader->getShaderConstHandle("$ambientColor");
      mLightPositionSC = mShader->getShaderConstHandle("$inLightPos");
      mLightColorSC = mShader->getShaderConstHandle("$inLightColor");
      mLightConfigDataSC = mShader->getShaderConstHandle("$inLightConfigData");

   }

   return true;
}

void SpriteObject::onRemove()
{
   // Remove this object from the scene
   removeFromScene();

   Parent::onRemove();
}

void SpriteObject::inspectPostApply()
{

   Parent::inspectPostApply();

   setMaskBits(LayerUpdateMask | FrameUpdateMask | ColorUpdateMask);
}


//-----------------------------------------------------------------------------

void SpriteObject::setTransform(const MatrixF& mat)
{
   // Let SceneObject handle all of the matrix manipulation
   Parent::setTransform(mat);

   // Dirty our network mask so that the new transform gets
   // transmitted to the client object
   setMaskBits(TransformMask);
}

//-----------------------------------------------------------------------------

U32 SpriteObject::packUpdate(NetConnection* conn, U32 mask, BitStream* stream)
{
   // Allow the Parent to get a crack at writing its info
   U32 retMask = Parent::packUpdate(conn, mask, stream);

   PACK_ASSET(conn, Sprite);
   if (stream->writeFlag(mask & FrameUpdateMask))
   {
      stream->write(mFrame);
   }

   if (stream->writeFlag(mask & LayerUpdateMask))
   {
      stream->write(mLayerMask);
   }

   if (stream->writeFlag(mask & ColorUpdateMask))
   {
      stream->write(mColorOverlay);
   }

   // Write our transform information
   if (stream->writeFlag(mask & TransformMask))
   {
      mathWrite(*stream, getTransform());
      mathWrite(*stream, getScale());
   }

   return retMask;
}

void SpriteObject::unpackUpdate(NetConnection* conn, BitStream* stream)
{
   // Let the Parent read any info it sent
   Parent::unpackUpdate(conn, stream);

   UNPACK_ASSET(conn, Sprite);
   if (stream->readFlag()) // update frame flag
   {
      stream->read(&mFrame);
      mFrameDirty = true;
   }

   if (stream->readFlag()) // layer update mask
   {
      stream->read(&mLayerMask);
   }

   if (stream->readFlag()) // color update mask
   {
      stream->read(&mColorOverlay);
   }

   if (stream->readFlag())  // TransformMask
   {
      mathRead(*stream, &mObjToWorld);
      mathRead(*stream, &mObjScale);

      setTransform(mObjToWorld);
   }

   if (isProperlyAdded())
   {
      _setSprite(getSprite());
   }
}

//-----------------------------------------------------------------------------
// Rendering

void SpriteObject::prepRenderImage(SceneRenderState* state)
{

   SpriteAsset::FrameArea::TexelArea texelArea;
   if(mSpriteAsset.notNull())
      texelArea = mSpriteAsset->getSpriteFrameArea(mFrame).mTexelArea;

   const F32 texLowerX = texelArea.mTexelLower.x;
   const F32 texLowerY = texelArea.mTexelLower.y;
   const F32 texUpperX = texelArea.mTexelUpper.x;
   const F32 texUpperY = texelArea.mTexelUpper.y;

   if (mVertexBuffer.isNull() || mFrameDirty) {
      // Fill the vertex buffer
      VertexType *pVert = NULL;

      mVertexBuffer.set(GFX, 4, GFXBufferTypeStatic);
      pVert = mVertexBuffer.lock();

      F32 width = getObjBox().len_x() * 0.5f;
      F32 height = getObjBox().len_y() * 0.5f;

      pVert[0].point.set(-width, height, 0.0f);
      pVert[1].point.set(width, height, 0.0f);
      pVert[2].point.set(-width,  -height, 0.0f);
      pVert[3].point.set(width,   -height, 0.0f);

      pVert[0].color.set(mColorOverlay);
      pVert[1].color.set(mColorOverlay);
      pVert[2].color.set(mColorOverlay);
      pVert[3].color.set(mColorOverlay);

      pVert[0].texCoord.set(texLowerX, texLowerY);
      pVert[1].texCoord.set(texUpperX, texLowerY);
      pVert[2].texCoord.set(texLowerX, texUpperY);
      pVert[3].texCoord.set(texUpperX, texUpperY);
      
      mVertexBuffer.unlock();

      GFXStateBlockDesc desc;

      mNormalSB = GFX->createStateBlock(desc);
      mFrameDirty = false;

   }

   // Allocate an ObjectRenderInst so that we can submit it to the RenderPassManager
   T2DObjectRenderInst* ri = state->getRenderPass()->allocInst<T2DObjectRenderInst>();

   // Now bind our rendering function so that it will get called
   ri->renderDelegate.bind(this, &SpriteObject::render);

   // Set our RenderInst as a standard object render
   ri->type = RenderPassManager::RIT_T2DObject;

   // Set our sorting keys to a default value
   ri->defaultKey = getLayerMask();
   ri->defaultKey2 = 0;

   LightQuery query;
   query.init(getWorldSphere());
   query.getLights(ri->lights, 4);

   // Submit our RenderInst to the RenderPassManager
   state->getRenderPass()->addInst(ri);
}

void SpriteObject::render(T2DObjectRenderInst* ri, SceneRenderState* state, BaseMatInstance* overrideMat)
{
   if (overrideMat)
      return;

   if (mVertexBuffer.isNull())
      return;

   PROFILE_SCOPE(SpriteObject_Render);

   // Set up a GFX debug event (this helps with debugging rendering events in external tools)
   GFXDEBUGEVENT_SCOPE(SpriteObject_Render, ColorI::RED);

   //new setup
   const U32 MAX_FORWARD_LIGHTS = 4;

   static AlignedArray<Point4F> lightPositions(MAX_FORWARD_LIGHTS, sizeof(Point4F));
   static AlignedArray<Point4F> lightColors(MAX_FORWARD_LIGHTS, sizeof(Point4F));
   static AlignedArray<Point4F> lightConfigData(MAX_FORWARD_LIGHTS, sizeof(Point4F)); //type, brightness, range, invSqrRange : rgba

   dMemset(lightPositions.getBuffer(), 0, lightPositions.getBufferSize());
   dMemset(lightColors.getBuffer(), 0, lightColors.getBufferSize());
   dMemset(lightConfigData.getBuffer(), 0, lightConfigData.getBufferSize());

   // Gather the data for the first 4 lights.
   const LightInfo* light;
   for (U32 i = 0; i < MAX_FORWARD_LIGHTS; i++)
   {
      light = ri->lights[i];
      if (!light)
         break;

      // The light positions and spot directions are 
      // in SoA order to make optimal use of the GPU.
      const Point3F& lightPos = light->getPosition();
      lightPositions[i].x = lightPos.x;
      lightPositions[i].y = lightPos.y;
      lightPositions[i].z = lightPos.z;
      lightPositions[i].w = 0;

      lightColors[i] = Point4F(light->getColor());

      lightConfigData[i].x = 0;
      lightConfigData[i].y = light->getBrightness();

      F32 range = light->getRange().x;
      lightConfigData[i].z = range;
      lightConfigData[i].w = 1.0f / (range * range);
   }

   // GFXTransformSaver is a handy helper class that restores
   // the current GFX matrices to their original values when
   // it goes out of scope at the end of the function
   GFXTransformSaver saver;

   // Calculate our object to world transform matrix
   MatrixF objectToWorld = getRenderTransform();
   objectToWorld.scale(getScale());

   // Apply our object transform
   GFX->multWorld(objectToWorld);

   GFX->setShader(mShader);
   GFX->setShaderConstBuffer(mShaderConsts);
   GFX->setStateBlock(mNormalSB);

   MatrixF xform(GFX->getProjectionMatrix());
   xform *= GFX->getViewMatrix();
   xform *= GFX->getWorldMatrix();

   if (mAmbientColorSC->isValid() && state)
   {
      const LinearColorF& sunlight = state->getAmbientLightColor();
      Point4F ambientColor(sunlight.red, sunlight.green, sunlight.blue, sunlight.alpha);

      mShaderConsts->set(mAmbientColorSC, ambientColor);
   }

   const Point3F& eyePosWorld = state->getCameraPosition();

   if (mEyePosSC->isValid())
   {
      MatrixF tempMat(getRenderTransform());
      tempMat.inverse();
      Point3F eyepos;
      tempMat.mulP(eyePosWorld, &eyepos);
      mShaderConsts->set(mEyePosSC, eyepos);
   }

   mShaderConsts->setSafe(mWorldPosSC, getRenderTransform().getPosition());

   mShaderConsts->setSafe(mModelViewProjSC, xform);
   mShaderConsts->setSafe(mTimeSC, (F32)Sim::getCurrentTime() / 1000.0f);

   mShaderConsts->setSafe(mLightPositionSC, lightPositions);
   mShaderConsts->setSafe(mLightColorSC, lightColors);
   mShaderConsts->setSafe(mLightConfigDataSC, lightConfigData);
   // Set the texture to the sprite.
   GFX->setTexture(mDiffuseMapSC->getSamplerRegister(), mSprite);
   if (!mSpriteNormal.isNull())
      GFX->setTexture(mNormalMapSC->getSamplerRegister(), mSpriteAsset->getSpriteNormal());

   // Set the vertex buffer
   GFX->setVertexBuffer(mVertexBuffer);

   // Draw our 2 triangles
   GFX->drawPrimitive(GFXTriangleStrip, 0, 2);
}
