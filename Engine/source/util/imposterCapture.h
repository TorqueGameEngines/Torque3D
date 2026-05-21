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

#ifndef _IMPOSTERCAPTURE_H_
#define _IMPOSTERCAPTURE_H_
#include "math/mathTypes.h"

#include "math/mPoint3.h"

#include "math/mMatrix.h"

#include "core/util/tVector.h"

#include "ts/tsRenderState.h"

#include "gfx/gfxTextureHandle.h"

class GBitmap;
class SceneRenderState;
class TSShapeInstance;
class GFXTextureTarget;
class RenderPassManager;
class RenderMeshMgr;


class ImposterCapture
{
   
protected:

   S32 mDl;
   S32 mDim;

   /// The bounding radius of the shape used to size the billboard.
   F32 mRadius;

   /// 
   Point3F mCenter;

   GBitmap *mBlackBmp;
   GBitmap *mWhiteBmp;

   GFXTexHandle mBlackTex;
   GFXTexHandle mWhiteTex;
   GFXTexHandle mNormalTex;
   GFXTexHandle mDepthBuffer;

   SceneRenderState *mState;
   TSShapeInstance *mShapeInstance;
   TSRenderState mRData;

   GFXTextureTarget *mRenderTarget;

   RenderPassManager *mRenderPass;
   RenderMeshMgr     *mMeshRenderBin;

   void _colorAverageFilter(  U32 dimensions, const U8 *inBmpBits, U8 *outBmpBits );
   void _renderToTexture( GFXTexHandle texHandle, GBitmap *outBitmap, const ColorI &color ); 

   void _separateAlpha( GBitmap *imposterOut );

   void _convertDXT5nm( GBitmap *imposterOut );

public:

   ImposterCapture();

   ~ImposterCapture();

   void begin( TSShapeInstance *shapeInst,
               S32 dl, 
               S32 dim,
               F32 radius,
               const Point3F &center );

   void capture(  const MatrixF &rotMatrix, 
                  GBitmap **imposterOut,
                  GBitmap **normalMapOut );

   void end();

};

#endif // _IMPOSTERCAPTURE_H_