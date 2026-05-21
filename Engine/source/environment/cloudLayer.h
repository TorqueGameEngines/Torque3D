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
#pragma once 
#pragma once 

#ifndef _CLOUDLAYER_H_
#define _CLOUDLAYER_H_
#include "scene/sceneObject.h"

#include "gfx/gfxTextureHandle.h"

#include "gfx/gfxVertexBuffer.h"

#include "gfx/gfxPrimitiveBuffer.h"

#include "materials/matInstance.h"

#include "T3D/assets/ImageAsset.h"

GFXDeclareVertexFormat( GFXCloudVertex )
{
   Point3F point;
   Point3F normal;
   Point3F binormal;
   Point3F tangent; 
   Point2F texCoord;
};

class CloudLayer : public SceneObject
{
   typedef SceneObject Parent;

   enum 
   { 
      CloudLayerMask    = Parent::NextFreeMask,      
      NextFreeMask      = Parent::NextFreeMask << 1,
   };  

   #define TEX_COUNT 3
public:

   CloudLayer();
   virtual ~CloudLayer() {}

   DECLARE_CONOBJECT( CloudLayer );
   DECLARE_CATEGORY("Environment \t Weather");

   // ConsoleObject
   bool onAdd() override;
   void onRemove() override;
   static void initPersistFields();
   void inspectPostApply() override;   

   // NetObject
   U32 packUpdate( NetConnection *conn, U32 mask, BitStream *stream ) override;
   void unpackUpdate( NetConnection *conn, BitStream *stream ) override;

   // SceneObject
   void prepRenderImage( SceneRenderState *state ) override;
   void renderObject( ObjectRenderInst *ri, SceneRenderState *state, BaseMatInstance *mi );

   void onImageChanged() {}

protected:

   void _initBuffers();

protected:

   static U32 smVertStride;
   static U32 smStrideMinusOne;
   static U32 smVertCount;
   static U32 smTriangleCount;

public:

   DECLARE_IMAGEASSET_NET(CloudLayer,Texture, GFXStaticTextureSRGBProfile, CloudLayerMask)

   GFXShaderRef mShader;

   GFXStateBlockRef mStateblock;

   GFXShaderConstBufferRef mShaderConsts;
   GFXShaderConstHandle *mModelViewProjSC; 
   GFXShaderConstHandle *mAmbientColorSC;
   GFXShaderConstHandle *mSunColorSC;
   GFXShaderConstHandle *mSunVecSC;
   GFXShaderConstHandle *mTexOffsetSC[3];
   GFXShaderConstHandle *mTexScaleSC;
   GFXShaderConstHandle *mBaseColorSC;    
   GFXShaderConstHandle *mCoverageSC;  
   GFXShaderConstHandle *mExposureSC;  
   GFXShaderConstHandle *mEyePosWorldSC;
   GFXShaderConstHandle *mNormalHeightMapSC;

   GFXVertexBufferHandle<GFXCloudVertex> mVB;
   GFXPrimitiveBufferHandle mPB;

   Point2F mTexOffset[3];
   U32 mLastTime;

   // Fields...

   F32 mTexScale[TEX_COUNT];
   Point2F mTexDirection[TEX_COUNT];
   F32 mTexSpeed[TEX_COUNT];   
   
   LinearColorF mBaseColor;
   F32 mExposure;
   F32 mCoverage;
   F32 mWindSpeed;   
   F32 mHeight;
};


#endif // _CLOUDLAYER_H_
