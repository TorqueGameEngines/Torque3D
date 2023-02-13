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

#include "T3D/lighting/sphereEnvironmentProbe.h"
#include "math/mathIO.h"
#include "scene/sceneRenderState.h"
#include "console/consoleTypes.h"
#include "core/stream/bitStream.h"
#include "materials/baseMatInstance.h"
#include "console/engineAPI.h"
#include "gfx/gfxDrawUtil.h"
#include "gfx/gfxDebugEvent.h"
#include "gfx/gfxTransformSaver.h"
#include "math/mathUtils.h"
#include "gfx/bitmap/gBitmap.h"
#include "core/stream/fileStream.h"
#include "core/fileObject.h"
#include "core/resourceManager.h"
#include "console/simPersistID.h"
#include "T3D/gameFunctions.h"
#include "postFx/postEffect.h"
#include "renderInstance/renderProbeMgr.h"
#include "renderInstance/renderProbeMgr.h"

#include "math/util/sphereMesh.h"
#include "materials/materialManager.h"
#include "math/util/matrixSet.h"
#include "gfx/bitmap/cubemapSaver.h"

#include "materials/materialFeatureTypes.h"

#include "materials/shaderData.h"
#include "gfx/gfxTextureManager.h"

#include "gfx/bitmap/imageUtils.h"

#include "T3D/lighting/IBLUtilities.h"

extern bool gEditingMission;
extern ColorI gCanvasClearColor;

IMPLEMENT_CO_NETOBJECT_V1(SphereEnvironmentProbe);

ConsoleDocClass(SphereEnvironmentProbe,
   "@brief An example scene object which renders a mesh.\n\n"
   "This class implements a basic SceneObject that can exist in the world at a "
   "3D position and render itself. There are several valid ways to render an "
   "object in Torque. This class implements the preferred rendering method which "
   "is to submit a MeshRenderInst along with a Material, vertex buffer, "
   "primitive buffer, and transform and allow the RenderMeshMgr handle the "
   "actual setup and rendering for you.\n\n"
   "See the C++ code for implementation details.\n\n"
   "@ingroup Examples\n");

//-----------------------------------------------------------------------------
// Object setup and teardown
//-----------------------------------------------------------------------------
SphereEnvironmentProbe::SphereEnvironmentProbe() : ReflectionProbe()
{
   mCaptureMask = REFLECTION_PROBE_CAPTURE_TYPEMASK;
   mProbeShapeType = ProbeInfo::Sphere;
}

SphereEnvironmentProbe::~SphereEnvironmentProbe()
{
}

//-----------------------------------------------------------------------------
// Object Editing
//-----------------------------------------------------------------------------
void SphereEnvironmentProbe::initPersistFields()
{
   docsURL;
   // SceneObject already handles exposing the transform
   Parent::initPersistFields();

   removeField("scale");
}

void SphereEnvironmentProbe::inspectPostApply()
{
   Parent::inspectPostApply();

   mDirty = true;

   // Flag the network mask to send the updates
   // to the client object
   setMaskBits(-1);
}

bool SphereEnvironmentProbe::onAdd()
{
   if (!Parent::onAdd())
      return false;

   return true;
}

void SphereEnvironmentProbe::onRemove()
{
   Parent::onRemove();
}

U32 SphereEnvironmentProbe::packUpdate(NetConnection *conn, U32 mask, BitStream *stream)
{
   // Allow the Parent to get a crack at writing its info
   U32 retMask = Parent::packUpdate(conn, mask, stream);

   return retMask;
}

void SphereEnvironmentProbe::unpackUpdate(NetConnection *conn, BitStream *stream)
{
   // Let the Parent read any info it sent
   Parent::unpackUpdate(conn, stream);

   if (mDirty)
   {
      updateProbeParams();
   }
}

//-----------------------------------------------------------------------------
// Object Rendering
//-----------------------------------------------------------------------------

void SphereEnvironmentProbe::updateProbeParams()
{
   mProbeShapeType = ProbeInfo::Sphere;
   Parent::updateProbeParams();
}

void SphereEnvironmentProbe::setPreviewMatParameters(SceneRenderState* renderState, BaseMatInstance* mat)
{
   Parent::setPreviewMatParameters(renderState, mat);
}
