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

#ifndef _SPRITEOBJECT_H_
#define _SPRITEOBJECT_H_

#ifndef _SCENEOBJECT_H_
#include "scene/sceneObject.h"
#endif

#ifndef _GFXSTATEBLOCK_H_
#include "gfx/gfxStateBlock.h"
#endif

#ifndef _GFXVERTEXBUFFER_H_
#include "gfx/gfxVertexBuffer.h"
#endif

#ifndef _GFXPRIMITIVEBUFFER_H_
#include "gfx/gfxPrimitiveBuffer.h"
#endif

#ifndef _SPRITE_ASSET_H_
#include "T2D/assets/SpriteAsset.h"
#endif

class BaseMatInstance;
struct T2DObjectRenderInst;

class SpriteObject : public SceneObject
{
   typedef SceneObject Parent;

   enum MaskBits
   {
      TransformMask =      Parent::NextFreeMask << 0,
      FrameUpdateMask =    Parent::NextFreeMask << 1,
      LayerUpdateMask =    Parent::NextFreeMask << 2,
      ColorUpdateMask =    Parent::NextFreeMask << 3,
      NextFreeMask =       Parent::NextFreeMask << 4
   };

   typedef GFXVertexPCT VertexType;

   S32 mFrame;
   S32 mLayerMask;
   bool mFrameDirty;
   ColorI mColorOverlay;
   // The handles for our StateBlocks
   GFXStateBlockRef mNormalSB;
   // The GFX vertex and primitive buffers
   GFXVertexBufferHandle< VertexType > mVertexBuffer;

   // shader stuffs
   GFXShaderRef mShader;
   GFXShaderConstBufferRef mShaderConsts;
   GFXShaderConstHandle* mTimeSC;
   GFXShaderConstHandle* mModelViewProjSC;
   GFXShaderConstHandle* mTexScaleSC;
   GFXShaderConstHandle* mTexDirectionSC;
   GFXShaderConstHandle* mTexOffsetSC;
   GFXShaderConstHandle* mDiffuseMapSC;
   GFXShaderConstHandle* mNormalMapSC;

   // lighting shader data
   GFXShaderConstHandle* mWorldPosSC;
   GFXShaderConstHandle* mEyePosSC;
   GFXShaderConstHandle* mAmbientColorSC;
   GFXShaderConstHandle* mLightPositionSC;
   GFXShaderConstHandle* mLightColorSC;
   GFXShaderConstHandle* mLightConfigDataSC;

public:
   DECLARE_SPRITEASSET(SpriteObject, Sprite, onChangeSprite, GFXStaticTextureSRGBProfile);
   DECLARE_ASSET_SETGET(SpriteObject, Sprite);
   SpriteObject();
   virtual ~SpriteObject();

   DECLARE_CONOBJECT(SpriteObject);

   static void initPersistFields();
   virtual void inspectPostApply();

   bool onAdd();
   void onRemove();

   void setTransform(const MatrixF& mat);

   U32 packUpdate(NetConnection* conn, U32 mask, BitStream* stream);
   void unpackUpdate(NetConnection* conn, BitStream* stream);

   void prepRenderImage(SceneRenderState* state);
   void render(T2DObjectRenderInst* ri, SceneRenderState* state, BaseMatInstance* overrideMat);

   S32 getLayerMask() { return mLayerMask; }

   void onChangeSprite() {}

};

#endif
