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
   VECTOR_SET_ASSOCIATION(mDrawCache);
   mPrimType = 0;
   mVertCount = 0;
   mOverrideState = false;
}

duDebugDrawTorque::~duDebugDrawTorque()
{
}

void duDebugDrawTorque::depthMask(bool state)
{
   if (mOverrideState)
      return;

   mDesc.setZReadWrite(state);
   if (!state)
   {
      mDesc.setCullMode(GFXCullNone);
      mDesc.setBlend(true);
   }
   else
   {
      mDesc.setCullMode(GFXCullCW);
      mDesc.setBlend(false);
   }
}

void duDebugDrawTorque::depthMask(bool state, bool isOverride)
{
   depthMask(state);
   mOverrideState = isOverride;
}

void duDebugDrawTorque::blend(bool blend)
{
   mDesc.setBlend(true);
}

void duDebugDrawTorque::texture(bool state)
{
   // need a checker texture?...... if(state is true) then set first slot to that texture.
}

unsigned int duDebugDrawTorque::areaToCol(unsigned int area)
{
   switch (area)
   {
      // Ground (1) : light blue
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

   mVertCount = 0;
   mPrimType = 0;

   switch (prim)
   {
   case DU_DRAW_POINTS: mPrimType = DU_DRAW_POINTS; break;
   case DU_DRAW_LINES:  mPrimType = DU_DRAW_LINES; break;
   case DU_DRAW_TRIS:   mPrimType = DU_DRAW_TRIS; break;
   case DU_DRAW_QUADS:  mPrimType = DU_DRAW_QUADS; break;
   }

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
   
   switch (mPrimType)
   {
   case DU_DRAW_POINTS:
   {
      const U32 totalPoints = mVertList.size();

      for (U32 p = 0; p < totalPoints;)
      {
         const U32 pointsThisBatch = getMin(maxVertsPerDraw, totalPoints - p);
         const U32 batchVerts = pointsThisBatch;
         Box3F box;
         box.minExtents.set(F32_MAX, F32_MAX, F32_MAX);
         box.maxExtents.set(-F32_MAX, -F32_MAX, -F32_MAX);

         GFXVertexBufferHandle<GFXVertexPCT> buffer;
         buffer.set(GFX, batchVerts, GFXBufferTypeStatic);
         GFXVertexPCT* verts = buffer.lock();

         for (U32 i = 0; i < pointsThisBatch; ++i)
         {
            verts[i] = mVertList[p + i];
            box.minExtents.setMin(verts[i].point);
            box.maxExtents.setMax(verts[i].point);
         }
         buffer.unlock();

         // --- Build index buffer
         GFXPrimitiveBufferHandle pb;
         pb.set(GFX, pointsThisBatch, pointsThisBatch, GFXBufferTypeStatic);
         U16* indices = nullptr;
         pb.lock(&indices);

         for (U32 i = 0; i < pointsThisBatch; ++i)
         {
            indices[i] = i;
         }

         pb.unlock();

         CachedDraw batch;
         batch.primType = GFXPointList;
         batch.buffer = buffer;
         batch.vertexCount = batchVerts;
         batch.primitiveBuffer = pb;
         batch.primitiveCount = pointsThisBatch;
         batch.state = mDesc;
         batch.bounds = box;

         mDrawCache.push_back(batch);

         p += pointsThisBatch;
      }
      break;
   }

   case DU_DRAW_LINES:
   {
      AssertFatal(mVertList.size() % 2 == 0, "DU_DRAW_LINES given invalid vertex count.");

      const U32 vertsPerLine = 2;
      const U32 totalLines = mVertList.size() / vertsPerLine;

      for (U32 l = 0; l < totalLines;)
      {
         const U32 linesThisBatch = getMin(maxVertsPerDraw / vertsPerLine, totalLines - l);
         const U32 batchVerts = linesThisBatch * vertsPerLine;
         Box3F box;
         box.minExtents.set(F32_MAX, F32_MAX, F32_MAX);
         box.maxExtents.set(-F32_MAX, -F32_MAX, -F32_MAX);

         GFXVertexBufferHandle<GFXVertexPCT> buffer;
         buffer.set(GFX, batchVerts, GFXBufferTypeStatic);
         GFXVertexPCT* verts = buffer.lock();

         for (U32 i = 0; i < linesThisBatch * vertsPerLine; ++i)
         {
            verts[i] = mVertList[l * vertsPerLine + i];
            box.minExtents.setMin(verts[i].point);
            box.maxExtents.setMax(verts[i].point);
         }
         buffer.unlock();

         // --- Build index buffer
         GFXPrimitiveBufferHandle pb;
         pb.set(GFX, linesThisBatch * 2, linesThisBatch, GFXBufferTypeStatic);
         U16* indices = nullptr;
         pb.lock(&indices);

         for (U32 i = 0; i < linesThisBatch; ++i)
         {
            indices[i * 2 + 0] = i * 2;
            indices[i * 2 + 1] = i * 2 + 1;
         }

         pb.unlock();

         CachedDraw batch;
         batch.primType = GFXLineList;
         batch.buffer = buffer;
         batch.vertexCount = batchVerts;
         batch.primitiveBuffer = pb;
         batch.primitiveCount = linesThisBatch;
         batch.state = mDesc;
         batch.bounds = box;

         mDrawCache.push_back(batch);

         l += linesThisBatch;
      }

      break;
   }

   case DU_DRAW_TRIS:
   {
      AssertFatal(mVertList.size() % 3 == 0, "DU_DRAW_TRIS given invalid vertex count.");

      const U32 vertsPerTri = 3;
      const U32 totalTris = mVertList.size() / vertsPerTri;

      for (U32 t = 0; t < totalTris;)
      {
         const U32 trisThisBatch = getMin(maxVertsPerDraw / vertsPerTri, totalTris - t);
         const U32 batchVerts = trisThisBatch * vertsPerTri;
         Box3F box;
         box.minExtents.set(F32_MAX, F32_MAX, F32_MAX);
         box.maxExtents.set(-F32_MAX, -F32_MAX, -F32_MAX);

         GFXVertexBufferHandle<GFXVertexPCT> buffer;
         buffer.set(GFX, batchVerts, GFXBufferTypeStatic);
         GFXVertexPCT* verts = buffer.lock();

         for (U32 i = 0; i < trisThisBatch * vertsPerTri; ++i)
         {
            verts[i] = mVertList[t * vertsPerTri + i];
            box.minExtents.setMin(verts[i].point);
            box.maxExtents.setMax(verts[i].point);
         }

         buffer.unlock();

         // --- Build index buffer
         GFXPrimitiveBufferHandle pb;
         pb.set(GFX, trisThisBatch*3, trisThisBatch, GFXBufferTypeStatic);
         U16* indices = nullptr;
         pb.lock(&indices);

         for (U32 i = 0; i < trisThisBatch; ++i)
         {
            indices[i * 3 + 0] = i * 3 + 0;
            indices[i * 3 + 1] = i * 3 + 1;
            indices[i * 3 + 2] = i * 3 + 2;
         }

         pb.unlock();

         CachedDraw batch;
         batch.primType = GFXTriangleList;
         batch.buffer = buffer;
         batch.vertexCount = batchVerts;
         batch.primitiveBuffer = pb;
         batch.primitiveCount = trisThisBatch;
         batch.state = mDesc;
         batch.bounds = box;

         mDrawCache.push_back(batch);

         t += trisThisBatch;
      }

      break;
   }

   case DU_DRAW_QUADS:
   {
      AssertFatal(mVertList.size() % 4 == 0, "DU_DRAW_QUADS given wrong number of vertices.");
      const U32 vertsPerQuad = 4;
      const U32 totalQuads = mVertList.size() / 4;

      for (U32 q = 0; q < totalQuads;)
      {
         const U32 quadsThisBatch = getMin(maxVertsPerDraw / vertsPerQuad, totalQuads - q);
         const U32 batchVerts = quadsThisBatch * vertsPerQuad;
         const U32 batchIndices = quadsThisBatch * 6;
         Box3F box;
         box.minExtents.set(F32_MAX, F32_MAX, F32_MAX);
         box.maxExtents.set(-F32_MAX, -F32_MAX, -F32_MAX);

         GFXVertexBufferHandle<GFXVertexPCT> buffer;
         buffer.set(GFX, batchVerts, GFXBufferTypeStatic);
         GFXVertexPCT* verts = buffer.lock();

         U32 outIdx = 0;
         for (U32 i = 0; i < quadsThisBatch; ++i)
         {
            const GFXVertexPCT& v0 = mVertList[(q + i) * 4 + 0];
            const GFXVertexPCT& v1 = mVertList[(q + i) * 4 + 1];
            const GFXVertexPCT& v2 = mVertList[(q + i) * 4 + 2];
            const GFXVertexPCT& v3 = mVertList[(q + i) * 4 + 3];

            verts[outIdx++] = v0;
            verts[outIdx++] = v1;
            verts[outIdx++] = v2;
            verts[outIdx++] = v3;
         }

         buffer.unlock();

         GFXPrimitiveBufferHandle pb;
         pb.set(GFX, batchIndices, quadsThisBatch*2, GFXBufferTypeStatic);
         U16* indices = nullptr;
         pb.lock(&indices);

         for (U32 i = 0; i < quadsThisBatch; ++i)
         {
            const U16 base = i * 4;
            indices[i * 6 + 0] = base + 0;
            indices[i * 6 + 1] = base + 1;
            indices[i * 6 + 2] = base + 2;
            indices[i * 6 + 3] = base + 0;
            indices[i * 6 + 4] = base + 2;
            indices[i * 6 + 5] = base + 3;
         }

         pb.unlock();

         CachedDraw batch;
         batch.primType = GFXTriangleList;
         batch.buffer = buffer;
         batch.vertexCount = batchVerts;
         batch.primitiveBuffer = pb;
         batch.primitiveCount = quadsThisBatch*2;
         batch.state = mDesc;

         mDrawCache.push_back(batch);

         q += quadsThisBatch;
      }
      break;
   }

   }

   mVertList.clear();
}

void duDebugDrawTorque::clearCache()
{
   mDrawCache.clear();
}

void duDebugDrawTorque::render(SceneRenderState* state)
{
   if (!state->isDiffusePass()) return;

   const Frustum& frustum = state->getCameraFrustum();

   for (U32 i = 0; i < mDrawCache.size(); ++i)
   {
      const CachedDraw& draw = mDrawCache[i];

      if (!frustum.getBounds().isOverlapped(draw.bounds))
         continue;

      GFX->setPrimitiveBuffer(draw.primitiveBuffer);
      GFX->setStateBlockByDesc(draw.state);
      GFX->setupGenericShaders(GFXDevice::GSColor);
      GFX->setVertexBuffer(draw.buffer);

      GFX->drawIndexedPrimitive(
         draw.primType,
         0,                      // start vertex
         0,                      // min vertex index
         draw.vertexCount,       // vertex count
         0,                      // start index
         draw.primitiveCount     // primitive count
      );
   }
}

void duDebugDrawTorque::immediateRender()
{
   for (U32 i = 0; i < mDrawCache.size(); ++i)
   {
      const CachedDraw& draw = mDrawCache[i];

      GFX->setPrimitiveBuffer(draw.primitiveBuffer);
      GFX->setStateBlockByDesc(draw.state);
      GFX->setupGenericShaders(GFXDevice::GSColor);
      GFX->setVertexBuffer(draw.buffer);

      GFX->drawIndexedPrimitive(
         draw.primType,
         0,                      // start vertex
         0,                      // min vertex index
         draw.vertexCount,       // vertex count
         0,                      // start index
         draw.primitiveCount     // primitive count
      );
   }
}

