#include "SubScene.h"

#include "gameMode.h"
#include "console/persistenceManager.h"
#include "console/script.h"
#include "environment/meshRoad.h"
#include "environment/river.h"
#include "scene/sceneRenderState.h"
#include "renderInstance/renderPassManager.h"
#include "gfx/gfxDrawUtil.h"
#include "gfx/gfxTransformSaver.h"
#include "gui/editor/inspector/group.h"
#include "T3D/gameBase/gameBase.h"

bool SubScene::smTransformChildren = false;

IMPLEMENT_CO_NETOBJECT_V1(SubScene);

S32 SubScene::mUnloadTimeoutMs = 5000;

IMPLEMENT_CALLBACK(SubScene, onLoaded, void, (), (),
   "@brief Called when a subScene has been loaded and has game mode implications.\n\n");
IMPLEMENT_CALLBACK(SubScene, onUnloaded, void, (), (),
   "@brief Called when a subScene has been unloaded and has game mode implications.\n\n");

SubScene::SubScene() :
   mLevelAssetId(StringTable->EmptyString()),
   mGameModesNames(StringTable->EmptyString()),
   mScopeDistance(-1),
   mLoaded(false),
   mFreezeLoading(false),
   mTickPeriodMS(1000),
   mCurrTick(0),
   mGlobalLayer(false),
   mSaving(false)
{
   mNetFlags.set(Ghostable | ScopeAlways);

   mTypeMask |= StaticObjectType;
}

SubScene::~SubScene()
{
}

bool SubScene::onAdd()
{
   if (!Parent::onAdd())
     return false;

   setProcessTick(true);

    return true;
}

void SubScene::onRemove()
{
    if (isClientObject())
      removeFromScene();

    unload();

    Parent::onRemove();
}

void SubScene::initPersistFields()
{
   addGroup("SubScene");
   addField("isGlobalLayer", TypeBool, Offset(mGlobalLayer, SubScene), "");
   INITPERSISTFIELD_LEVELASSET(Level, SubScene, "The level asset to load.");
   addField("tickPeriodMS", TypeS32, Offset(mTickPeriodMS, SubScene), "evaluation rate (ms)");
   addField("gameModes", TypeGameModeList, Offset(mGameModesNames, SubScene), "The game modes that this subscene is associated with.");
   endGroup("SubScene");

   addGroup("LoadingManagement");
   addField("freezeLoading", TypeBool, Offset(mFreezeLoading, SubScene), "If true, will prevent the zone from being changed from it's current loading state.");
   addField("loadIf", TypeCommand, Offset(mLoadIf, SubScene), "evaluation condition (true/false)");

   addField("tickPeriodMS", TypeS32, Offset(mTickPeriodMS, SubScene), "evaluation rate (ms)");

   addField("onLoadCommand", TypeCommand, Offset(mOnLoadCommand, SubScene), "The command to execute when the subscene is loaded. Maximum 1023 characters.");
   addField("onUnloadCommand", TypeCommand, Offset(mOnUnloadCommand, SubScene), "The command to execute when subscene is unloaded. Maximum 1023 characters.");
   endGroup("LoadingManagement");


   Parent::initPersistFields();
}

void SubScene::consoleInit()
{
   Parent::consoleInit();

   Con::addVariable("$SubScene::UnloadTimeoutMS", TypeBool, &SubScene::mUnloadTimeoutMs, "The amount of time in milliseconds it takes for a SubScene to be unloaded if it's inactive.\n"
      "@ingroup Editors\n");

   Con::addVariable("$SubScene::transformChildren", TypeBool, &SubScene::smTransformChildren,
      "@brief If true, then transform manipulations modify child objects. If false, only triggering bounds is manipulated\n\n"
      "@ingroup Editors");
}

void SubScene::addObject(SimObject* object)
{
   SceneObject::addObject(object);
}

void SubScene::removeObject(SimObject* object)
{
   SceneObject::removeObject(object);
}

U32 SubScene::packUpdate(NetConnection* conn, U32 mask, BitStream* stream)
{
   U32 retMask = Parent::packUpdate(conn, mask, stream);

   stream->writeFlag(mGlobalLayer);

   return retMask;
}

void SubScene::unpackUpdate(NetConnection* conn, BitStream* stream)
{
   Parent::unpackUpdate(conn, stream);

   mGlobalLayer = stream->readFlag();

}

void SubScene::onInspect(GuiInspector* inspector)
{
   Parent::onInspect(inspector);

   //Put the SubScene group before everything that'd be SubScene-effecting, for orginazational purposes
   GuiInspectorGroup* subsceneGrp = inspector->findExistentGroup(StringTable->insert("SubScene"));
   if (!subsceneGrp)
      return;

   GuiControl* stack = dynamic_cast<GuiControl*>(subsceneGrp->findObjectByInternalName(StringTable->insert("Stack")));

   //Save button
   GuiInspectorField* saveFieldGui = subsceneGrp->createInspectorField();
   saveFieldGui->init(inspector, subsceneGrp);

   saveFieldGui->setSpecialEditField(true);
   saveFieldGui->setTargetObject(this);

   StringTableEntry fldnm = StringTable->insert("SaveSubScene");

   saveFieldGui->setSpecialEditVariableName(fldnm);

   saveFieldGui->setInspectorField(NULL, fldnm);
   saveFieldGui->setDocs("");

   stack->addObject(saveFieldGui);

   GuiButtonCtrl* saveButton = new GuiButtonCtrl();
   saveButton->registerObject();
   saveButton->setDataField(StringTable->insert("profile"), NULL, "ToolsGuiButtonProfile");
   saveButton->setText("Save SubScene");
   saveButton->resize(Point2I::Zero, saveFieldGui->getExtent());
   saveButton->setHorizSizing(GuiControl::horizResizeWidth);
   saveButton->setVertSizing(GuiControl::vertResizeHeight);

   char szBuffer[512];
   dSprintf(szBuffer, 512, "%d.save();", this->getId());
   saveButton->setConsoleCommand(szBuffer);

   saveFieldGui->addObject(saveButton);
}

void SubScene::inspectPostApply()
{
   Parent::inspectPostApply();
   setMaskBits(-1);
}

void SubScene::setTransform(const MatrixF& mat)
{
   if(SubScene::smTransformChildren)
   {
      Parent::setTransform(mat);
   }
   else
   {
      SceneObject::setTransform(mat);
   }
}

void SubScene::setRenderTransform(const MatrixF& mat)
{
   if (SubScene::smTransformChildren)
   {
      Parent::setRenderTransform(mat);
   }
   else
   {
      SceneObject::setRenderTransform(mat);
   }
}

bool SubScene::evaluateCondition()
{
   if (!mLoadIf.isEmpty())
   {
      //test the mapper plugged in condition line
      String resVar = getIdString() + String(".result");
      Con::setBoolVariable(resVar.c_str(), false);
      String command = resVar + "=" + mLoadIf + ";";

      Con::evaluatef(command.c_str());
      return Con::getBoolVariable(resVar.c_str());
   }
   return true;
}

bool SubScene::testBox(const Box3F& testBox)
{
   bool passes = mGlobalLayer;

   if (!passes)
      passes = getWorldBox().isOverlapped(testBox);

   if (passes)
      passes = evaluateCondition();
   return passes;
}

void SubScene::write(Stream& stream, U32 tabStop, U32 flags)
{
   MutexHandle handle;
   handle.lock(mMutex);

   // export selected only?
   if ((flags & SelectedOnly) && !isSelected())
   {
      for (U32 i = 0; i < size(); i++)
         (*this)[i]->write(stream, tabStop, flags);

      return;

   }

   stream.writeTabs(tabStop);
   char buffer[2048];
   const U32 bufferWriteLen = dSprintf(buffer, sizeof(buffer), "new %s(%s) {\r\n", getClassName(), getName() && !(flags & NoName) ? getName() : "");
   stream.write(bufferWriteLen, buffer);
   writeFields(stream, tabStop + 1);

   //The only meaningful difference between this and simSet for writing is we skip the children, since they're just the levelAsset contents

   stream.writeTabs(tabStop);
   stream.write(4, "};\r\n");
}

void SubScene::processTick(const Move* move)
{
   mCurrTick += TickMs;
   if (mCurrTick > mTickPeriodMS)
   {
      mCurrTick = 0;
      //re-evaluate
      if (!evaluateCondition())
         unload();
   }
}

void SubScene::_onFileChanged(const Torque::Path& path)
{
   if(mLevelAsset.isNull() || Torque::Path(mLevelAsset->getLevelPath()) != path)
      return;

   if (mSaving)
      return;

   AssertFatal(path == mLevelAsset->getLevelPath(), "Prefab::_onFileChanged - path does not match filename.");

   _closeFile(false);
   _loadFile(false);
   setMaskBits(U32_MAX);
}

void SubScene::_removeContents(SimGroupIterator set)
{
   for (SimGroupIterator itr(set); *itr; ++itr)
   {

      SimGroup* child = dynamic_cast<SimGroup*>(*itr);
      if (child)
      {
         _removeContents(SimGroupIterator(child));

         GameBase* asGameBase = dynamic_cast<GameBase*>(child);
         if (asGameBase)
         {
            asGameBase->scriptOnRemove();
         }

         Sim::cancelPendingEvents(child);

         child->safeDeleteObject();
      }
   }
}

void SubScene::_closeFile(bool removeFileNotify)
{
   AssertFatal(isServerObject(), "Trying to close out a subscene file on the client is bad!");

   _removeContents(SimGroupIterator(this));

   if (removeFileNotify && mLevelAsset.notNull() && mLevelAsset->getLevelPath() != StringTable->EmptyString())
   {
      Torque::FS::RemoveChangeNotification(mLevelAsset->getLevelPath(), this, &SubScene::_onFileChanged);
   }

   mGameModesList.clear();
}

void SubScene::_loadFile(bool addFileNotify)
{
   AssertFatal(isServerObject(), "Trying to load a SubScene file on the client is bad!");

   if(mLevelAsset.isNull() || mLevelAsset->getLevelPath() == StringTable->EmptyString())
      return;

   String evalCmd = String::ToString("exec(\"%s\");", mLevelAsset->getLevelPath());

   String instantGroup = Con::getVariable("InstantGroup");
   Con::setIntVariable("InstantGroup", this->getId());
   Con::evaluate((const char*)evalCmd.c_str(), false, mLevelAsset->getLevelPath());
   Con::setVariable("InstantGroup", instantGroup.c_str());

   if (addFileNotify)
      Torque::FS::AddChangeNotification(mLevelAsset->getLevelPath(), this, &SubScene::_onFileChanged);
}

void SubScene::load()
{
   mStartUnloadTimerMS = -1; //reset unload timers

   //no need to load multiple times
   if (mLoaded)
      return;

   if (mFreezeLoading)
      return;

   if (mSaving)
      return;

   GameMode::findGameModes(mGameModesNames, &mGameModesList);
   if (!isSelected() && (String(mGameModesNames).isNotEmpty() && mGameModesList.size() == 0) || !evaluateCondition())
   {
      mLoaded = false;
      return;
   }

   _loadFile(true);
   mLoaded = true;

   onLoaded_callback();
   for (U32 i = 0; i < mGameModesList.size(); i++)
   {
      mGameModesList[i]->onSubsceneLoaded_callback(this);
   }

}

void SubScene::unload()
{
   if (!mLoaded)
      return;

   if (mFreezeLoading)
      return;

   if (mSaving)
      return;

   if (isSelected())
   {
      mStartUnloadTimerMS = Sim::getCurrentTime();
      return; //if a child is selected, then we don't want to unload
   }

   //scan down through our child objects, see if any are marked as selected,
   //if so, skip unloading and reset the timer
   for (SimGroupIterator itr(this); *itr; ++itr)
   {
      SimGroup* childGrp = dynamic_cast<SimGroup*>(*itr);
      if (childGrp)
      {
         if (childGrp->isSelected())
         {
            mStartUnloadTimerMS = Sim::getCurrentTime();
            return; //if a child is selected, then we don't want to unload
         }
         for (SimGroupIterator cldItr(childGrp); *cldItr; ++cldItr)
         {
            SimObject* chldChld = dynamic_cast<SimObject*>(*cldItr);
            if (chldChld && chldChld->isSelected())
            {
               mStartUnloadTimerMS = Sim::getCurrentTime();
               return; //if a child is selected, then we don't want to unload
            }
         }
      }
   }

   onUnloaded_callback();
   for (U32 i = 0; i < mGameModesList.size(); i++)
   {
      mGameModesList[i]->onSubsceneUnloaded_callback(this);
   }

   if (!mOnUnloadCommand.isEmpty())
   {
      String command = "%this = " + String(getIdString()) + "; " + mOnUnloadCommand + ";";
      Con::evaluatef(command.c_str());
   }

   _closeFile(true);
   mLoaded = false;

}

bool SubScene::save()
{
   if (!isServerObject())
      return false;

   //if there's nothing TO save, don't bother
   if (size() == 0 || !isLoaded())
      return false;

   if (mLevelAsset.isNull())
      return false;

   if (mSaving)
      return false;

   //If we're flagged for unload, push back the unload timer so we can't accidentally trip be saving partway through an unload
   if (mStartUnloadTimerMS != -1)
      mStartUnloadTimerMS = Sim::getCurrentTime();

   mSaving = true;

   PersistenceManager prMger;

   StringTableEntry levelPath = mLevelAsset->getLevelPath();

   FileStream fs;
   fs.open(levelPath, Torque::FS::File::Write);
   fs.close();

   for (SimGroupIterator itr(this); *itr; ++itr)
   {
      SimObject* childObj = (*itr);

      if (!prMger.isDirty(childObj))
      {
         if ((*itr)->isMethod("onSaving"))
         {
            Con::executef((*itr), "onSaving", mLevelAssetId);
         }

         if (childObj->getGroup() == this)
         {
            prMger.setDirty((*itr), levelPath);
         }
      }

      if(dynamic_cast<MeshRoad*>(childObj) || dynamic_cast<River*>(childObj))
      {
         prMger.addRemoveField(childObj, "position");
      }
   }

   prMger.saveDirty();

   //process our gameModeList and write it out to the levelAsset for metadata stashing
   bool saveSuccess = false;

   //Get the level asset
   if (mLevelAsset.isNull())
      return saveSuccess;

   //update the gamemode list as well
   mLevelAsset->setDataField(StringTable->insert("gameModesNames"), NULL, StringTable->insert(mGameModesNames));

   //Finally, save
   saveSuccess = mLevelAsset->saveAsset();

   mSaving = false;

   return saveSuccess;
}

void SubScene::_onSelected()
{
   if (!isLoaded() && isServerObject())
      load();
}

void SubScene::_onUnselected()
{
}

void SubScene::prepRenderImage(SceneRenderState* state)
{
   // only render if selected or render flag is set
   if (/*!smRenderTriggers && */!isSelected())
      return;

   ObjectRenderInst* ri = state->getRenderPass()->allocInst<ObjectRenderInst>();
   ri->renderDelegate.bind(this, &SubScene::renderObject);
   ri->type = RenderPassManager::RIT_Editor;
   ri->translucentSort = true;
   ri->defaultKey = 1;
   state->getRenderPass()->addInst(ri);
}

void SubScene::renderObject(ObjectRenderInst* ri,
   SceneRenderState* state,
   BaseMatInstance* overrideMat)
{
   if (overrideMat)
      return;

   GFXStateBlockDesc desc;
   desc.setZReadWrite(true, false);
   desc.setBlend(true);

   // Trigger polyhedrons are set up with outward facing normals and CCW ordering
   // so can't enable backface culling.
   desc.setCullMode(GFXCullNone);

   GFXTransformSaver saver;

   MatrixF mat = getRenderTransform();
   GFX->multWorld(mat);

   GFXDrawUtil* drawer = GFX->getDrawUtil();

   //Box3F scale = getScale()
   //Box3F bounds = Box3F(-m)

   Point3F scale = getScale();
   Box3F bounds = Box3F(-scale/2, scale/2);

   ColorI boundsColor = ColorI(135, 206, 235, 50);

   if (mGlobalLayer)
      boundsColor = ColorI(200, 100, 100, 25);
   else if (mLoaded)
      boundsColor = ColorI(50, 200, 50, 50);

   drawer->drawCube(desc, bounds, boundsColor);

   // Render wireframe.

   desc.setFillModeWireframe();
   drawer->drawCube(desc, bounds, ColorI::BLACK);
}

DefineEngineMethod(SubScene, save, bool, (),,
   "Save out the subScene.\n")
{
   return object->save();
}


DefineEngineMethod(SubScene, load, void, (), ,
   "Loads the SubScene's level file.\n")
{
   object->load();
}

DefineEngineMethod(SubScene, unload, void, (), ,
   "Unloads the SubScene's level file.\n")
{
   object->unload();
}
