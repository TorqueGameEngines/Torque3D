#include "SceneGroup.h"

#include "gameBase/gameConnection.h"
#include "gfx/gfxDrawUtil.h"
#include "gfx/gfxTransformSaver.h"
#include "gui/editor/inspector/group.h"
#include "gui/worldEditor/editor.h"
#include "math/mathIO.h"
#include "physics/physicsShape.h"
#include "renderInstance/renderPassManager.h"
#include "scene/sceneRenderState.h"
#include "Scene.h"

IMPLEMENT_CO_NETOBJECT_V1(SceneGroup);

ConsoleDocClass(SceneGroup,
   "@brief A collection of arbitrary objects which can be allocated and manipulated as a group.\n\n"

   "%SceneGroup always points to a (.SceneGroup) file which defines its objects. In "
   "fact more than one %SceneGroup can reference this file and both will update "
   "if the file is modified.\n\n"

   "%SceneGroup is a very simple object and only exists on the server. When it is "
   "created it allocates children objects by reading the (.SceneGroup) file like "
   "a list of instructions.  It then sets their transform relative to the %SceneGroup "
   "and Torque networking handles the rest by ghosting the new objects to clients. "
   "%SceneGroup itself is not ghosted.\n\n"

   "@ingroup enviroMisc"
);

SceneGroup::SceneGroup()
{
   // Not ghosted unless we're editing
   mNetFlags.clear(Ghostable | ScopeAlways);

   mTypeMask |= StaticObjectType;
}

SceneGroup::~SceneGroup()
{
}

void SceneGroup::initPersistFields()
{
   docsURL;

   addGroup("SceneGroup");
   endGroup("SceneGroup");

   Parent::initPersistFields();
}

bool SceneGroup::onAdd()
{
   if (!Parent::onAdd())
      return false;

   mObjBox.set(Point3F(-0.5f, -0.5f, -0.5f),
      Point3F(0.5f, 0.5f, 0.5f));

   resetWorldBox();

   // Not added to the scene unless we are editing.
   if (gEditingMission)
      onEditorEnable();

   addToScene();

   return true;
}

void SceneGroup::onRemove()
{
   removeFromScene();
   Parent::onRemove();
}

void SceneGroup::onEditorEnable()
{
   if (isClientObject())
      return;

   // Just in case we are already in the scene, lets not cause an assert.   
   if (mContainer != NULL)
      return;

   // Enable ghosting so we can see this on the client.
   mNetFlags.set(Ghostable);
   setScopeAlways();
   addToScene();

   Parent::onEditorEnable();
}

void SceneGroup::onEditorDisable()
{
   if (isClientObject())
      return;

   // Just in case we are not in the scene, lets not cause an assert.   
   if (mContainer == NULL)
      return;

   // Do not need this on the client if we are not editing.
   removeFromScene();
   mNetFlags.clear(Ghostable);
   clearScopeAlways();

   Parent::onEditorDisable();
}

void SceneGroup::inspectPostApply()
{
   Parent::inspectPostApply();
}

void SceneGroup::onInspect(GuiInspector* inspector)
{
   Parent::onInspect(inspector);

#ifdef TORQUE_TOOLS
   
   //Put the SubScene group before everything that'd be SubScene-effecting, for orginazational purposes
   GuiInspectorGroup* sceneGroupGrp = inspector->findExistentGroup(StringTable->insert("Editing"));
   if (!sceneGroupGrp)
      return;

   GuiControl* stack = dynamic_cast<GuiControl*>(sceneGroupGrp->findObjectByInternalName(StringTable->insert("Stack")));

   //Regen bounds button
   GuiInspectorField* regenFieldGui = sceneGroupGrp->createInspectorField();
   regenFieldGui->init(inspector, sceneGroupGrp);

   regenFieldGui->setSpecialEditField(true);
   regenFieldGui->setTargetObject(this);

   StringTableEntry fldnm = StringTable->insert("RegenerateBounds");

   regenFieldGui->setSpecialEditVariableName(fldnm);

   regenFieldGui->setInspectorField(NULL, fldnm);
   regenFieldGui->setDocs("");

   stack->addObject(regenFieldGui);

   GuiButtonCtrl* regenButton = new GuiButtonCtrl();
   regenButton->registerObject();
   regenButton->setDataField(StringTable->insert("profile"), NULL, "ToolsGuiButtonProfile");
   regenButton->setText("Regenerate Bounds");
   regenButton->resize(Point2I::Zero, regenFieldGui->getExtent());
   regenButton->setHorizSizing(GuiControl::horizResizeWidth);
   regenButton->setVertSizing(GuiControl::vertResizeHeight);

   char rgBuffer[512];
   dSprintf(rgBuffer, 512, "%d.recalculateBounds();", this->getId());
   regenButton->setConsoleCommand(rgBuffer);

   regenFieldGui->addObject(regenButton);

   //
    //Regen bounds button
   GuiInspectorField* reparentFieldGui = sceneGroupGrp->createInspectorField();
   reparentFieldGui->init(inspector, sceneGroupGrp);

   reparentFieldGui->setSpecialEditField(true);
   reparentFieldGui->setTargetObject(this);

   fldnm = StringTable->insert("ReparentOOBObjs");

   reparentFieldGui->setSpecialEditVariableName(fldnm);

   reparentFieldGui->setInspectorField(NULL, fldnm);
   reparentFieldGui->setDocs("");

   stack->addObject(reparentFieldGui);

   GuiButtonCtrl* reparentButton = new GuiButtonCtrl();
   reparentButton->registerObject();
   reparentButton->setDataField(StringTable->insert("profile"), NULL, "ToolsGuiButtonProfile");
   reparentButton->setText("Reparent Out-of-bounds Objs");
   reparentButton->resize(Point2I::Zero, regenFieldGui->getExtent());
   reparentButton->setHorizSizing(GuiControl::horizResizeWidth);
   reparentButton->setVertSizing(GuiControl::vertResizeHeight);

   char rprntBuffer[512];
   dSprintf(rprntBuffer, 512, "%d.reparentOOBObjects();", this->getId());
   reparentButton->setConsoleCommand(rprntBuffer);

   reparentFieldGui->addObject(reparentButton);
#endif
}

void SceneGroup::setTransform(const MatrixF& mat)
{
   if (isServerObject())
   {
      setMaskBits(TransformMask);

      MatrixF newXform = mat;
      MatrixF oldXform = getTransform();
      oldXform.affineInverse();

      MatrixF offset;
      offset.mul(newXform, oldXform);

      // Update all child transforms
      for (SimSetIterator itr(this); *itr; ++itr)
      {
         SceneObject* child = dynamic_cast<SceneObject*>(*itr);
         if (child)
         {
            MatrixF childMat;

            //add the "offset" caused by the parents change, and add it to it's own
            // This is needed by objects that update their own render transform thru interpolate tick
            // Mostly for stationary objects.
            childMat.mul(offset, child->getTransform());
            child->setTransform(childMat);

            PhysicsShape* childPS = dynamic_cast<PhysicsShape*>(child);
            if (childPS)
               childPS->storeRestorePos();
         }
      }
   }

   Parent::setTransform(mat);
}

void SceneGroup::setRenderTransform(const MatrixF& mat)
{
   MatrixF newXform = mat;
   MatrixF oldXform = getRenderTransform();
   oldXform.affineInverse();

   MatrixF offset;
   offset.mul(newXform, oldXform);

   // Update all child transforms
   for (SimSetIterator itr(this); *itr; ++itr)
   {
      SceneObject* child = dynamic_cast<SceneObject*>(*itr);
      if (child)
      {
         MatrixF childMat;

         //add the "offset" caused by the parents change, and add it to it's own
         // This is needed by objects that update their own render transform thru interpolate tick
         // Mostly for stationary objects.
         childMat.mul(offset, child->getRenderTransform());
         child->setRenderTransform(childMat);

         PhysicsShape* childPS = dynamic_cast<PhysicsShape*>(child);
         if (childPS)
            childPS->storeRestorePos();
      }
   }

   Parent::setRenderTransform(mat);
}

void SceneGroup::addObject(SimObject* object)
{
   Parent::addObject(object);

   // Recalculate the bounding box from scratch (simpler but potentially costly)
   recalculateBoundingBox();
}

void SceneGroup::removeObject(SimObject* object)
{
   Parent::removeObject(object);

   // Recalculate the bounding box from scratch (simpler but potentially costly)
   recalculateBoundingBox();
}

void SceneGroup::recalculateBoundingBox()
{
   if (empty())
      return;

   // Reset the bounding box
   Box3F bounds;

   bounds.minExtents.set(1e10, 1e10, 1e10);
   bounds.maxExtents.set(-1e10, -1e10, -1e10);

   // Extend the bounding box to include each child's bounding box
   for (SimSetIterator itr(this); *itr; ++itr)
   {
      SceneObject* child = dynamic_cast<SceneObject*>(*itr);
      if (child)
      {
         const Box3F& childBox = child->getWorldBox();

         bounds.minExtents.setMin(childBox.minExtents);
         bounds.maxExtents.setMax(childBox.maxExtents);
      }
   }

   MatrixF newTrans = mObjToWorld;
   newTrans.setPosition(bounds.getCenter());
   Parent::setTransform(newTrans);

   mObjScale = Point3F(bounds.len_x(), bounds.len_y(), bounds.len_z());
   mWorldBox = bounds;
   resetObjectBox();

   setMaskBits(TransformMask);
}

void SceneGroup::reparentOOBObjects()
{
   if (empty())
      return;

   // Extend the bounding box to include each child's bounding box
   for (SimSetIterator itr(this); *itr; ++itr)
   {
      SceneObject* child = dynamic_cast<SceneObject*>(*itr);
      if (child)
      {
         const Box3F& childBox = child->getWorldBox();

         if(!mWorldBox.isOverlapped(childBox))
         {
            Scene::getRootScene()->addObject(child);
         }
      }
   }
}

U32 SceneGroup::packUpdate(NetConnection* conn, U32 mask, BitStream* stream)
{
   U32 retMask = Parent::packUpdate(conn, mask, stream);

   mathWrite(*stream, mObjBox);

   if (stream->writeFlag(mask & TransformMask))
   {
      mathWrite(*stream, getTransform());
      mathWrite(*stream, getScale());
   }

   return retMask;
}

void SceneGroup::unpackUpdate(NetConnection* conn, BitStream* stream)
{
   Parent::unpackUpdate(conn, stream);

   mathRead(*stream, &mObjBox);
   resetWorldBox();

   // TransformMask
   if (stream->readFlag())
   {
      mathRead(*stream, &mObjToWorld);
      mathRead(*stream, &mObjScale);

      setTransform(mObjToWorld);
   }
}

void SceneGroup::getUtilizedAssets(Vector<StringTableEntry>* usedAssetsList)
{
}

DefineEngineMethod(SceneGroup, recalculateBounds, void, (), ,
   "Recalculates the SceneGroups' bounds and centerpoint.\n")
{
   object->recalculateBoundingBox();
}

DefineEngineMethod(SceneGroup, reparentOOBObjects, void, (), ,
   "Finds objects that are children of the SceneGroup and, if not overlapping or in the bounds, reparents them to the root scene.\n")
{
   object->reparentOOBObjects();
}
