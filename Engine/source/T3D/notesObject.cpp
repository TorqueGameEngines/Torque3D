#include "T3D/notesObject.h"

#include "math/mathIO.h"
#include "scene/sceneRenderState.h"
#include "core/stream/bitStream.h"
#include "materials/sceneData.h"
#include "gfx/gfxDebugEvent.h"
#include "gfx/gfxTransformSaver.h"
#include "renderInstance/renderPassManager.h"
#include "math/mathUtils.h"
#include "gfx/gfxDrawUtil.h"

IMPLEMENT_CO_NETOBJECT_V1(NotesObject);

extern bool gEditingMission;

//-----------------------------------------------------------------------------
// Object setup and teardown
//-----------------------------------------------------------------------------
NotesObject::NotesObject()
{
   // Flag this object so that it will always
   // be sent across the network to clients
   mNetFlags.set(Ghostable | ScopeAlways);

   // Set it as a "static" object
   mTypeMask |= StaticObjectType | StaticShapeObjectType;

   mShowArrow = true;
   mArrowLength = 5;
   mArrowRadius = 0.25;
}

NotesObject::~NotesObject()
{
}

//-----------------------------------------------------------------------------
// Object Editing
//-----------------------------------------------------------------------------
void NotesObject::initPersistFields()
{
   docsURL;
   Parent::initPersistFields();

   addField("Note", TypeCommand, Offset(mNote, NotesObject), "");

   addField("showArrow", TypeBool, Offset(mShowArrow, NotesObject), "");

   addField("arrowColor", TypeColorF, Offset(mArrowColor, NotesObject), "");
}

void NotesObject::inspectPostApply()
{
   // Apply any transformations set in the editor
   Parent::inspectPostApply();

   if (isServerObject())
   {
      setMaskBits(-1);
   }
}

bool NotesObject::onAdd()
{
   if (!Parent::onAdd())
      return false;

   // Set up a 1x1x1 bounding box
   mObjBox.set(Point3F(-0.5f, -0.5f, -0.5f),
      Point3F(0.5f, 0.5f, 0.5f));

   resetWorldBox();

   // Add this object to the scene
   addToScene();

   return true;
}

void NotesObject::onRemove()
{
   // Remove this object from the scene
   removeFromScene();

   Parent::onRemove();
}

void NotesObject::setTransform(const MatrixF& mat)
{
   // Let SceneObject handle all of the matrix manipulation
   Parent::setTransform(mat);

   // Dirty our network mask so that the new transform gets
   // transmitted to the client object
   setMaskBits(TransformMask);
}

U32 NotesObject::packUpdate(NetConnection* conn, U32 mask, BitStream* stream)
{
   // Allow the Parent to get a crack at writing its info
   U32 retMask = Parent::packUpdate(conn, mask, stream);

   // Write our transform information
   //if (stream->writeFlag(mask & TransformMask))
   {
      mathWrite(*stream, getTransform());
      mathWrite(*stream, getScale());
      stream->write(mShowArrow);

      stream->write(mArrowColor);
   }

   return retMask;
}

void NotesObject::unpackUpdate(NetConnection* conn, BitStream* stream)
{
   // Let the Parent read any info it sent
   Parent::unpackUpdate(conn, stream);

   //if (stream->readFlag())  // TransformMask
   {
      mathRead(*stream, &mObjToWorld);
      mathRead(*stream, &mObjScale);

      setTransform(mObjToWorld);

      stream->read(&mShowArrow);
      stream->read(&mArrowColor);
   }
}

void NotesObject::prepRenderImage(SceneRenderState* state)
{
   if (!gEditingMission)
      return;

   ObjectRenderInst* ri = state->getRenderPass()->allocInst<ObjectRenderInst>();
   ri->renderDelegate.bind(this, &NotesObject::_render);
   ri->type = RenderPassManager::RIT_Editor;
   state->getRenderPass()->addInst(ri);
}

void NotesObject::_render(ObjectRenderInst* ri, SceneRenderState* state, BaseMatInstance* overrideMat)
{
   if (showArrow())
   {
      GFXStateBlockDesc desc;
      desc.setBlend(true);
      desc.setZReadWrite(true, false);

      VectorF forwardVec = getTransform().getForwardVector();
      forwardVec.normalize();

       Point3F startPos = forwardVec * -(mArrowLength * 0.5) + getPosition();
      Point3F endPos = forwardVec * (mArrowLength * 0.5) + getPosition();

      ColorI arrowColor = mArrowColor.toColorI();
      arrowColor.alpha = 128;

      GFX->getDrawUtil()->drawArrow(desc, startPos, endPos, arrowColor, mArrowRadius);
   }
}
