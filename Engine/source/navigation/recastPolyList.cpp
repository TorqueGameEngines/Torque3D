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

#include "recastPolyList.h"
#include "platform/platform.h"

#include "gfx/gfxDevice.h"
#include "gfx/primBuilder.h"
#include "gfx/gfxStateBlock.h"

RecastPolyList::RecastPolyList() : mChunkyMesh(0)
{
   nverts = 0;
   verts = NULL;
   vertcap = 0;

   nnormals = 0;
   normals = NULL;
   normalcap = 0;

   ntris = 0;
   tris = NULL;
   tricap = 0;
   vidx = 0;
}

RecastPolyList::~RecastPolyList()
{
   clear();
}

rcChunkyTriMesh* RecastPolyList::getChunkyMesh()
{
   if (!mChunkyMesh)
   {
      mChunkyMesh = new rcChunkyTriMesh;
      if (!mChunkyMesh)
      {
         Con::errorf("Build tile navigation: out of memory");
         return NULL;
      }

      if (!rcCreateChunkyTriMesh(getVerts(), getTris(), getTriCount(), 256, mChunkyMesh))
      {
         Con::errorf("Build tile navigation: out of memory");
         return NULL;
      }

   }

   return mChunkyMesh;
}

void RecastPolyList::clear()
{
   nverts = 0;
   delete[] verts;
   verts = NULL;
   vertcap = 0;

   nnormals = 0;
   delete[] normals;
   normals = NULL;
   normalcap = 0;

   ntris = 0;
   delete[] tris;
   tris = NULL;
   tricap = 0;
}

bool RecastPolyList::isEmpty() const
{
   return getTriCount() == 0;
}

U32 RecastPolyList::addPoint(const Point3F &p)
{
   // If we've reached the vertex cap, double the array size.
   if(nverts == vertcap)
   {
      // vertcap starts at 64, otherwise it doubles.
      if(vertcap == 0) vertcap = 16;
      else vertcap *= 2;
      // Allocate new vertex storage.
      F32 *newverts = new F32[vertcap*3];

      dMemcpy(newverts, verts, nverts*3 * sizeof(F32));
      dFree(verts);
      verts = newverts;
   }
   Point3F v = p;
   v.convolve(mScale);
   mMatrix.mulP(v);
   // Insert the new vertex.
   verts[nverts*3] = v.x;
   verts[nverts*3+1] = v.z;
   verts[nverts*3+2] = -v.y;
   // Return nverts before incrementing it.
   return nverts++;
}

U32 RecastPolyList::addPlane(const PlaneF &plane)
{
   planes.increment();
   mPlaneTransformer.transform(plane, planes.last());
   return planes.size() - 1;
}

void RecastPolyList::begin(BaseMatInstance *material, U32 surfaceKey)
{
   vidx = 0;
   // If we've reached the tri cap, grow the array.
   if(ntris == tricap)
   {
      if(tricap == 0) tricap = 16;
      else tricap *= 2;
      // Allocate new vertex storage.
      S32 *newtris = new S32[tricap*3];

      dMemcpy(newtris, tris, ntris*3 * sizeof(S32));
      dFree(tris);
      tris = newtris;
   }
}

void RecastPolyList::plane(U32 v1, U32 v2, U32 v3)
{
}

void RecastPolyList::plane(const PlaneF& p)
{
}

void RecastPolyList::plane(const U32 index)
{
}

void RecastPolyList::vertex(U32 vi)
{
   if(vidx == 3)
      return;
   tris[ntris*3+2-vidx] = vi;
   vidx++;
}

void RecastPolyList::end()
{
   // Fetch current triangle indices
   const U32 i0 = tris[ntris * 3 + 0];
   const U32 i1 = tris[ntris * 3 + 1];
   const U32 i2 = tris[ntris * 3 + 2];

   // Rebuild vertices
   Point3F v0(verts[i0 * 3 + 0], verts[i0 * 3 + 1], verts[i0 * 3 + 2]);
   Point3F v1(verts[i1 * 3 + 0], verts[i1 * 3 + 1], verts[i1 * 3 + 2]);
   Point3F v2(verts[i2 * 3 + 0], verts[i2 * 3 + 1], verts[i2 * 3 + 2]);

   // Compute normal
   Point3F edge1 = v1 - v0;
   Point3F edge2 = v2 - v0;
   Point3F normal = mCross(edge1, edge2);
   normal.normalizeSafe();

   // Allocate/resize normal buffer if needed
   if (nnormals == normalcap)
   {
      normalcap = (normalcap == 0) ? 16 : normalcap * 2;
      F32* newNormals = new F32[normalcap * 3];
      if (normals)
         dMemcpy(newNormals, normals, nnormals * 3 * sizeof(F32));
      delete[] normals;
      normals = newNormals;
   }

   // Store normal
   normals[nnormals * 3 + 0] = normal.x;
   normals[nnormals * 3 + 1] = normal.y;
   normals[nnormals * 3 + 2] = normal.z;

   nnormals++;
   ntris++;
}

U32 RecastPolyList::getVertCount() const
{
   return nverts;
}

const F32 *RecastPolyList::getVerts() const
{
   return verts;
}

const F32* RecastPolyList::getNormals() const
{
   return normals;
}

U32 RecastPolyList::getTriCount() const
{
   return ntris;
}

const S32 *RecastPolyList::getTris() const
{
   return tris;
}

void RecastPolyList::renderWire() const
{
   GFXStateBlockDesc desc;
   desc.setCullMode(GFXCullNone);
   desc.setZReadWrite(false, false);
   //desc.setBlend(true);
   GFXStateBlockRef sb = GFX->createStateBlock(desc);
   GFX->setStateBlock(sb);

   PrimBuild::color3i(255, 0, 255);

   for(U32 t = 0; t < getTriCount(); t++)
   {
      PrimBuild::begin(GFXLineStrip, 4);

      PrimBuild::vertex3f(verts[tris[t*3]*3],   -verts[tris[t*3]*3+2],   verts[tris[t*3]*3+1]);
      PrimBuild::vertex3f(verts[tris[t*3+1]*3], -verts[tris[t*3+1]*3+2], verts[tris[t*3+1]*3+1]);
      PrimBuild::vertex3f(verts[tris[t*3+2]*3], -verts[tris[t*3+2]*3+2], verts[tris[t*3+2]*3+1]);
      PrimBuild::vertex3f(verts[tris[t*3]*3],   -verts[tris[t*3]*3+2],   verts[tris[t*3]*3+1]);

      PrimBuild::end();
   }
}
