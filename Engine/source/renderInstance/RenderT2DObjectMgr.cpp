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
#include "RenderT2DObjectMgr.h"
#include "console/consoleTypes.h"
#include "scene/sceneObject.h"
#include "materials/materialManager.h"
#include "scene/sceneRenderState.h"
#include "materials/sceneData.h"

IMPLEMENT_CONOBJECT(RenderT2DObjectMgr);

ConsoleDocClass(RenderT2DObjectMgr,
   "@brief A render bin just for rendering T2D objects.\n"
   "@ingroup RenderBin\n");

RenderT2DObjectMgr::RenderT2DObjectMgr()
   : RenderBinManager(RenderPassManager::RIT_T2DObject, 1.0f, 1.0f)
{
   mOverrideMat = NULL;
}

RenderT2DObjectMgr::RenderT2DObjectMgr(RenderInstType riType, F32 renderOrder, F32 processAddOrder)
   : RenderBinManager(riType, renderOrder, processAddOrder)
{
   mOverrideMat = NULL;
}

void RenderT2DObjectMgr::initPersistFields()
{
   Parent::initPersistFields();
}

void RenderT2DObjectMgr::setOverrideMaterial(BaseMatInstance* overrideMat)
{
   mOverrideMat = overrideMat;
}


void RenderT2DObjectMgr::render(SceneRenderState* state)
{
   PROFILE_SCOPE(RenderT2DObjectMgr_render);

   // Early out if nothing to draw.
   if (!mElementList.size())
      return;

   // Check if bin is disabled in advanced lighting.
   if (MATMGR->getDeferredEnabled() && mBasicOnly)
      return;

   SceneData sgData;

   sgData.init(state);

   for (U32 i = 0; i < mElementList.size(); i++)
   {
      T2DObjectRenderInst* ri = static_cast<T2DObjectRenderInst*>(mElementList[i].inst);

      dMemcpy(sgData.lights, ri->lights, sizeof(sgData.lights));

      if (ri->renderDelegate)
         ri->renderDelegate(ri, state, mOverrideMat);
   }
}
