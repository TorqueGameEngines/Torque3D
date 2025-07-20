//-----------------------------------------------------------------------------
// Copyright (c) 2013 GarageGames, LLC
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

#include "torqueRecast.h"
#include "duDebugDrawTorque.h"

#include "gfx/gfxDevice.h"
#include "gfx/primBuilder.h"
#include "gfx/gfxStateBlock.h"

/// @class duDebugDrawTorque
/// This class uses the primitive builder (gfx/primBuild.h) to render navmeshes
/// and other Recast data. To facilitate the primbuilder's requirement to know
/// the number of vertices to render beforehand, this class stores all vertices
/// in a buffer of its own, then passes on that known-size buffer.
/// This means that you only need to call the duDebugDraw functions when your
/// data changes. At other times, you can cache the duDebugDrawTorque object
/// and call its render() method, which actually renders its buffered data.

duDebugDrawTorque::duDebugDrawTorque()
{
   VECTOR_SET_ASSOCIATION(mVertList);
   mPrimType = 0;
   mQuadsMode = false;
   mVertCount = 0;
   dMemset(&mStore, 0, sizeof(mStore));
}

duDebugDrawTorque::~duDebugDrawTorque()
{
}

void duDebugDrawTorque::depthMask(bool state)
{
   mDesc.setZReadWrite(state, state);
}

void duDebugDrawTorque::texture(bool state)
{
   // need a checker texture?...... if(state is true) then set first slot to that texture.
}

unsigned int duDebugDrawTorque::areaToCol(unsigned int area)
{
   switch (area)
   {
      // Ground (0) : light blue
   case GroundArea: return duRGBA(0, 192, 255, 255);
      // Water : blue
   case WaterArea: return duRGBA(0, 0, 255, 255);
      // Road : brown
   case OffMeshArea: return duRGBA(50, 20, 12, 255);
      // Unexpected : red
   default: return duRGBA(255, 0, 0, 255);
   }
}

/// Begin drawing primitives.
/// @param prim [in] primitive type to draw, one of rcDebugDrawPrimitives.
/// @param size [in] size of a primitive, applies to point size and line width only.
void duDebugDrawTorque::begin(duDebugDrawPrimitives prim, float size)
{
   if (!mVertList.empty())
      mVertList.clear();

   mQuadsMode = false;
   mVertCount = 0;
   mPrimType = 0;

   switch (prim)
   {
   case DU_DRAW_POINTS: mPrimType = GFXPointList; break;
   case DU_DRAW_LINES:  mPrimType = GFXLineList; break;
   case DU_DRAW_TRIS:   mPrimType = GFXTriangleList; break;
   case DU_DRAW_QUADS:  mPrimType = GFXTriangleList; mQuadsMode = true; break;
   }

   mDesc.setCullMode(GFXCullNone);
   mDesc.setBlend(true);
}

/// Submit a vertex
/// @param pos [in] position of the verts.
/// @param color [in] color of the verts.
void duDebugDrawTorque::vertex(const float* pos, unsigned int color)
{
   vertex(pos[0], pos[1], pos[2], color);
}

/// Submit a vertex
/// @param x,y,z [in] position of the verts.
/// @param color [in] color of the verts.
void duDebugDrawTorque::vertex(const float x, const float y, const float z, unsigned int color)
{
   _vertex(x, -z, y, color);
}

/// Submit a vertex
/// @param pos [in] position of the verts.
/// @param color [in] color of the verts.
void duDebugDrawTorque::vertex(const float* pos, unsigned int color, const float* uv)
{
   vertex(pos[0], pos[1], pos[2], color);
}

/// Submit a vertex
/// @param x,y,z [in] position of the verts.
/// @param color [in] color of the verts.
void duDebugDrawTorque::vertex(const float x, const float y, const float z, unsigned int color, const float u, const float v)
{
   vertex(x, y, z, color);
}

/// Push a vertex onto the buffer.
void duDebugDrawTorque::_vertex(const float x, const float y, const float z, unsigned int color)
{
   GFXVertexPCT vert;
   vert.point.set(x, y, z);

   U8 r, g, b, a;
   // Convert color integer to components.
   rcCol(color, r, g, b, a);

   vert.color.set(r, g, b, a);

   mVertList.push_back(vert);
}

/// End drawing primitives.
void duDebugDrawTorque::end()
{
   if (mVertList.empty())
      return;

   const U32 maxVertsPerDraw = GFX_MAX_DYNAMIC_VERTS;

   U32 totalVerts = mVertList.size();
   U32 stride = 1;
   U32 stripStart = 0;

   switch (mPrimType)
   {
   case GFXLineList:     stride = 2; break;
   case GFXTriangleList: stride = 3; break;
   case GFXLineStrip:    stripStart = 1; stride = 1; break;
   case GFXTriangleStrip:stripStart = 2; stride = 1; break;
   default:              stride = 1; break;
   }

   GFX->setPrimitiveBuffer(NULL);
   GFX->setStateBlockByDesc(mDesc);
   GFX->setupGenericShaders(GFXDevice::GSColor);

   for (U32 i = 0; i < totalVerts; i += maxVertsPerDraw)
   {
      U32 batchSize = getMin(maxVertsPerDraw, totalVerts - i);

      mVertexBuffer.set(GFX, batchSize, GFXBufferTypeDynamic);
      GFXVertexPCT* verts = mVertexBuffer.lock();

      if (verts)
         dMemcpy(verts, &mVertList[i], sizeof(GFXVertexPCT) * batchSize);
      mVertexBuffer.unlock();

      GFX->setVertexBuffer(mVertexBuffer);

      U32 numPrims = (batchSize / stride) - stripStart;
      GFX->drawPrimitive((GFXPrimitiveType)mPrimType, 0, numPrims);
   }

   mVertList.clear();
}

