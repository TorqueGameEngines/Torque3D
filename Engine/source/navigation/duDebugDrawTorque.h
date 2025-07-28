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

#ifndef _DU_DEBUG_DRAW_TORQUE_H_
#define _DU_DEBUG_DRAW_TORQUE_H_

#ifndef _TVECTOR_H_
#include "core/util/tVector.h"
#endif
#include <DebugDraw.h>

#ifndef _GFXSTATEBLOCK_H_
#include "gfx/gfxStateBlock.h"
#endif

#ifndef _GFXVERTEXTYPES_H_
#include "gfx/gfxVertexTypes.h"
#endif

#ifndef _GFXVERTEXBUFFER_H_
#include "gfx/gfxVertexBuffer.h"
#endif

#ifndef _SCENERENDERSTATE_H_
#include "scene/sceneRenderState.h"
#endif

/**
* @class duDebugDrawTorque
*  @brief Implements the duDebugDraw interface in Torque.
*
* Every debug draw from recast goes through a process of begin, add vertex and then end
* just like our primbuilder class, but we need to catch these vertices
* and add them to a GFXVertexBuffer as recast supports GL_QUADS which is now
* deprecated.
*/
class duDebugDrawTorque : public duDebugDraw {
public:
   duDebugDrawTorque();
   ~duDebugDrawTorque();

   /// Enable/disable Z read.
   void depthMask(bool state) override;

   /// <summary>
   /// Enable/disable Z read and overrides any setting that will come from detour.
   /// </summary>
   /// <param name="state">Z read state.</param>
   /// <param name="isOverride">Set to true to override any future changes.</param>
   void depthMask(bool state, bool isOverride);

   void blend(bool blend);

   /// Begin drawing primitives.
   /// @param prim [in] primitive type to draw, one of rcDebugDrawPrimitives.
   /// @param size [in] size of a primitive, applies to point size and line width only.
   void begin(duDebugDrawPrimitives prim, float size = 1.0f) override;

   /// Submit a vertex
   /// @param pos [in] position of the verts.
   /// @param color [in] color of the verts.
   void vertex(const float* pos, unsigned int color) override;

   /// Submit a vertex
   /// @param x,y,z [in] position of the verts.
   /// @param color [in] color of the verts.
   void vertex(const float x, const float y, const float z, unsigned int color) override;

   /// Submit a vertex
   /// @param pos [in] position of the verts.
   /// @param color [in] color of the verts.
   /// @param uv [in] the uv coordinates.
   void vertex(const float* pos, unsigned int color, const float* uv) override;

   /// Submit a vertex
   /// @param x,y,z [in] position of the verts.
   /// @param color [in] color of the verts.
   /// @param u [in] the u coordinate.
   /// @param v [in] the v coordinate.
   void vertex(const float x, const float y, const float z, unsigned int color, const float u, const float v) override;

   /// Set a texture
   /// @param state, use a texture in this draw, usually a checker texture.
   void texture(bool state) override;

   /// <summary>
   /// Assigns a colour to an area type.
   /// </summary>
   /// <param name="area">The area type.</param>
   /// <returns>The colour in recast format for the area.</returns>
   unsigned int areaToCol(unsigned int area) override;

   /// End drawing primitives.
   void end() override;

   void clearCache();
   void render(SceneRenderState* state);
   void immediateRender();

private:

   struct CachedDraw {
      GFXPrimitiveType primType;
      GFXVertexBufferHandle<GFXVertexPCT> buffer;
      GFXPrimitiveBufferHandle primitiveBuffer;
      U32 vertexCount;
      U32 primitiveCount;
      GFXStateBlockDesc state;
      Box3F bounds;
   };

   Vector<CachedDraw> mDrawCache;

   GFXStateBlockDesc mDesc;
   Vector<GFXVertexPCT> mVertList;                    // Our vertex list for setting up vertexBuffer in the End function.
   GFXVertexBufferHandle<GFXVertexPCT> mVertexBuffer; // our vertex buffer for drawing.

   U32 mPrimType;
   U32 mVertCount;
   bool mOverrideState;

   void _vertex(const float x, const float y, const float z, unsigned int color);
};

#endif
