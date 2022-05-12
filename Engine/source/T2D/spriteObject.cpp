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

IMPLEMENT_CO_NETOBJECT_V1(SpriteObject);

ConsoleDocClass(SpriteObject,
   "@brief Base object for all T2D objects.\n\n"
   "@ingroup Torque2D\n");

SpriteObject::SpriteObject()
{
   mFrame = 0;
   INIT_ASSET(Sprite);
   // Flag this object so that it will always
   // be sent across the network to clients
   mNetFlags.set(Ghostable | ScopeAlways);

   // Set it as a "torque2d" object
   mTypeMask = Torque2DObjectType;
}

SpriteObject::~SpriteObject()
{
}

//-----------------------------------------------------------------------------

void SpriteObject::initPersistFields()
{
   INITPERSISTFIELD_SPRITEASSET(Sprite, SpriteObject, "A sprite asset to use for this sprite object.");

   addField("SpriteFrame", TypeS32, Offset(mFrame, SpriteObject),"Set frame for this sprite to render.");

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
   }

   return true;
}

void SpriteObject::onRemove()
{
   // Remove this object from the scene
   removeFromScene();

   Parent::onRemove();
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
   stream->write(mFrame);

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
   stream->read(&mFrame);

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

   if (mVertexBuffer.isNull()) {
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

      pVert[0].texCoord.set(texLowerX, texLowerY);
      pVert[1].texCoord.set(texUpperX, texLowerY);
      pVert[2].texCoord.set(texLowerX, texUpperY);
      pVert[3].texCoord.set(texUpperX, texUpperY);
      
      mVertexBuffer.unlock();

      GFXStateBlockDesc desc;

      mNormalSB = GFX->createStateBlock(desc);

   }

   // Allocate an ObjectRenderInst so that we can submit it to the RenderPassManager
   ObjectRenderInst* ri = state->getRenderPass()->allocInst<ObjectRenderInst>();

   // Now bind our rendering function so that it will get called
   ri->renderDelegate.bind(this, &SpriteObject::render);

   // Set our RenderInst as a standard object render
   ri->type = RenderPassManager::RIT_Object;

   // Set our sorting keys to a default value
   ri->defaultKey = 0;
   ri->defaultKey2 = 0;

   // Submit our RenderInst to the RenderPassManager
   state->getRenderPass()->addInst(ri);
}

void SpriteObject::render(ObjectRenderInst* ri, SceneRenderState* state, BaseMatInstance* overrideMat)
{
   if (overrideMat)
      return;

   if (mVertexBuffer.isNull())
      return;

   PROFILE_SCOPE(SpriteObject_Render);

   // Set up a GFX debug event (this helps with debugging rendering events in external tools)
   GFXDEBUGEVENT_SCOPE(SpriteObject_Render, ColorI::RED);

   // GFXTransformSaver is a handy helper class that restores
   // the current GFX matrices to their original values when
   // it goes out of scope at the end of the function
   GFXTransformSaver saver;

   // Calculate our object to world transform matrix
   MatrixF objectToWorld = getRenderTransform();
   objectToWorld.scale(getScale());

   // Apply our object transform
   GFX->multWorld(objectToWorld);

   GFX->setStateBlock(mNormalSB);


   GFX->setTexture(0, mSprite);
   // Set up the "generic" shaders
   // These handle rendering on GFX layers that don't support
   // fixed function. Otherwise they disable shaders.
   GFX->setupGenericShaders(GFXDevice::GSTexture);

   // Set the vertex buffer
   GFX->setVertexBuffer(mVertexBuffer);

   // Draw our 2 triangles
   GFX->drawPrimitive(GFXTriangleStrip, 0, 2);
}
