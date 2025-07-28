#include "navMeshTestTool.h"
#include "navigation/guiNavEditorCtrl.h"
#include "console/consoleTypes.h"
#include "gfx/gfxDrawUtil.h"
#include "scene/sceneManager.h"
#include "math/mathUtils.h"
#include "T3D/gameBase/gameConnection.h"
#include "T3D/AI/AIController.h"

IMPLEMENT_CONOBJECT(NavMeshTestTool);

////  take control
//   GameConnection* conn = GameConnection::getConnectionToServer();
//   if (conn)
//      conn->setControlObject(static_cast<GameBase*>(obj));
//}

static void renderBoxOutline(const Box3F& box, const ColorI& col)
{
   if (box != Box3F::Invalid)
   {
      GFXStateBlockDesc desc;
      desc.setCullMode(GFXCullNone);
      desc.setFillModeSolid();
      desc.setZReadWrite(true, false);
      desc.setBlend(true);
      GFX->getDrawUtil()->drawCube(desc, box, ColorI(col, 20));
      desc.setFillModeWireframe();
      desc.setBlend(false);
      GFX->getDrawUtil()->drawCube(desc, box, ColorI(col, 255));
   }
}

void NavMeshTestTool::spawnPlayer(const Point3F& position)
{
   if (mSpawnClass.isEmpty() || mSpawnDatablock.isEmpty())
   {
      Con::warnf("NavMeshTestTool::spawnPlayer - spawn class/datablock not set!");
      return;
   }

   SimObject* spawned = Sim::spawnObject(mSpawnClass, mSpawnDatablock);
   SceneObject* obj = dynamic_cast<SceneObject*>(spawned);

   if (!obj)
   {
      Con::warnf("NavMeshTestTool::spawnPlayer - spawn failed or not a SceneObject");
      if (spawned)
         spawned->deleteObject();
      return;
   }

   obj->setPosition(position);
   SimObject* cleanup = Sim::findObject("MissionCleanup");
   if (cleanup)
   {
      SimGroup* missionCleanup = dynamic_cast<SimGroup*>(cleanup);
      missionCleanup->addObject(obj);
   }
   mPlayer = obj;
   Con::executef(this, "onPlayerSpawned", obj->getIdString());

#ifdef TORQUE_NAVIGATION_ENABLED
   AIPlayer* asAIPlayer = dynamic_cast<AIPlayer*>(mPlayer.getPointer());
   if (asAIPlayer)
   {
      Con::executef(this, "onPlayerSelected");
   }
   else
   {
      ShapeBase* sbo = dynamic_cast<ShapeBase*>(mPlayer.getPointer());
      if (sbo && sbo->getAIController() && sbo->getAIController()->mControllerData)
      {
         Con::executef(this, "onPlayerSelected");
      }
      else
      {
         Con::executef(this, "onPlayerSelected");
      }
   }
#else
   Con::executef(this, "onPlayerSelected");
#endif
}

void NavMeshTestTool::drawAgent(duDebugDrawTorque& dd, const F32* pos, F32 r, F32 h, F32 c, const U32 col)
{
   dd.depthMask(false);

   // Agent dimensions.	
   duDebugDrawCylinderWire(&dd, pos[0] - r, pos[1] + 0.02f, pos[2] - r, pos[0] + r, pos[1] + h, pos[2] + r, col, 2.0f);

   duDebugDrawCircle(&dd, pos[0], pos[1] + c, pos[2], r, duRGBA(0, 0, 0, 64), 1.0f);

   U32 colb = duRGBA(0, 0, 0, 196);
   dd.begin(DU_DRAW_LINES);
   dd.vertex(pos[0], pos[1] - c, pos[2], colb);
   dd.vertex(pos[0], pos[1] + c, pos[2], colb);
   dd.vertex(pos[0] - r / 2, pos[1] + 0.02f, pos[2], colb);
   dd.vertex(pos[0] + r / 2, pos[1] + 0.02f, pos[2], colb);
   dd.vertex(pos[0], pos[1] + 0.02f, pos[2] - r / 2, colb);
   dd.vertex(pos[0], pos[1] + 0.02f, pos[2] + r / 2, colb);
   dd.end();

   dd.depthMask(true);
}

NavMeshTestTool::NavMeshTestTool()
{
   mSpawnClass = String::EmptyString;
   mSpawnDatablock = String::EmptyString;
   mPlayer = NULL;
   mCurPlayer = NULL;

   mFollowObject = NULL;
   mCurFollowObject = NULL;

   mPathStart = Point3F::Max;
   mPathEnd = Point3F::Max;

   mTestPath = NULL;

   mLinkTypes = LinkData(AllFlags);
   mFilter.setIncludeFlags(mLinkTypes.getFlags());
   mFilter.setExcludeFlags(0);
   mSelectFollow = false;
}

void NavMeshTestTool::onActivated(const Gui3DMouseEvent& evt)
{
   mSelectFollow = false;
   Con::executef(this, "onActivated");
}

void NavMeshTestTool::onDeactivated()
{
   if (mTestPath != NULL) {
      mTestPath->deleteObject();
      mTestPath = NULL;
   }

   if (mPlayer != NULL)
   {
      mPlayer = NULL;
      Con::executef(this, "onPlayerDeselected");
   }

   mSelectFollow = false;

   Con::executef(this, "onDeactivated");
}

void NavMeshTestTool::on3DMouseDown(const Gui3DMouseEvent& evt)
{
   if (mNavMesh.isNull())
      return;

   Point3F startPnt = evt.pos;
   Point3F endPnt = evt.pos + evt.vec * 1000.0f;

   RayInfo ri;
   bool shift = evt.modifier & SI_LSHIFT;
   bool ctrl = evt.modifier & SI_LCTRL;

   if (ctrl)
   {
      if (gServerContainer.castRay(startPnt, endPnt, StaticObjectType, &ri))
      {
         spawnPlayer(ri.point);
      }
      return;
   }

   if (shift)
   {
      mPlayer = NULL;
      Con::executef(this, "onPlayerDeselected");
      return;
   }

   if (gServerContainer.castRay(startPnt, endPnt, PlayerObjectType | VehicleObjectType, &ri))
   {
      if (!ri.object)
         return;
      if (mSelectFollow)
      {
         mFollowObject = ri.object;
         Con::executef(this, "onFollowSelected");
         mSelectFollow = false;
         return;
      }
      else
      {
         mPlayer = ri.object;
      }

#ifdef TORQUE_NAVIGATION_ENABLED
      AIPlayer* asAIPlayer = dynamic_cast<AIPlayer*>(mPlayer.getPointer());
      if (asAIPlayer)
      {
         Con::executef(this, "onPlayerSelected");
      }
      else
      {
         ShapeBase* sbo = dynamic_cast<ShapeBase*>(mPlayer.getPointer());
         if (sbo && sbo->getAIController() && sbo->getAIController()->mControllerData)
         {
            Con::executef(this, "onPlayerSelected");
         }
         else
         {
            Con::executef(this, "onPlayerSelected");
         }
      }
#else
      Con::executef(this, "onPlayerSelected");
#endif
   }
   else if (gServerContainer.castRay(startPnt, endPnt, StaticObjectType, &ri))
   {
      if (mPlayer.isNull())
      {
         if (mPathStart != Point3F::Max && mPathEnd != Point3F::Max) // start a new path.
         {
            mPathStart = Point3F::Max;
            mPathEnd = Point3F::Max;
         }

         if (mPathStart != Point3F::Max)
         {
            mPathEnd = ri.point;
            mTestPath = new NavPath();

            mTestPath->mMesh = mNavMesh;
            mTestPath->mFrom = mPathStart;
            mTestPath->mTo = mPathEnd;
            mTestPath->mFromSet = mTestPath->mToSet = true;
            mTestPath->mAlwaysRender = true;
            mTestPath->mLinkTypes = mLinkTypes;
            mTestPath->mFilter = mFilter;
            mTestPath->mXray = true;
            // Paths plan automatically upon being registered.
            if (!mTestPath->registerObject())
            {
               delete mTestPath;
               return;
            }
         }
         else
         {
            mPathStart = ri.point;
            if (mTestPath != NULL) {
               mTestPath->deleteObject();
               mTestPath = NULL;
            }
         }
      }
      else
      {
         AIPlayer* asAIPlayer = dynamic_cast<AIPlayer*>(mPlayer.getPointer());
         if (asAIPlayer) //try direct
         {
            asAIPlayer->setPathDestination(ri.point);
            mPathStart = mPlayer->getPosition();
            mPathEnd = ri.point;
         }
         else
         {
            ShapeBase* sbo = dynamic_cast<ShapeBase*>(mPlayer.getPointer());
            if (sbo->getAIController())
            {
               if (sbo->getAIController()->mControllerData)
               {
                  sbo->getAIController()->getNav()->setPathDestination(ri.point, true);
                  mPathStart = mPlayer->getPosition();
                  mPathEnd = ri.point;
               }
            }
         }
      }
   }

}

void NavMeshTestTool::on3DMouseMove(const Gui3DMouseEvent& evt)
{
   if (mNavMesh.isNull())
      return;

   Point3F startPnt = evt.pos;
   Point3F endPnt = evt.pos + evt.vec * 1000.0f;

   RayInfo ri;

   if (gServerContainer.castRay(startPnt, endPnt, PlayerObjectType | VehicleObjectType, &ri))
   {
      if (mSelectFollow)
         mCurFollowObject = ri.object;
      else
         mCurPlayer = ri.object;
   }
   else
   {
      mCurFollowObject = NULL;
      mCurPlayer = NULL;
   }
}

void NavMeshTestTool::onRender3D()
{
   if (mNavMesh.isNull())
      return;

   static const U32 startCol = duRGBA(128, 25, 0, 192);
   static const U32 endCol = duRGBA(51, 102, 0, 129);

   const F32 agentRadius = mNavMesh->mWalkableRadius;
   const F32 agentHeight = mNavMesh->mWalkableHeight;
   const F32 agentClimb = mNavMesh->mWalkableClimb;

   duDebugDrawTorque dd;
   dd.depthMask(false);
   if (mPathStart != Point3F::Max)
   {
      drawAgent(dd, DTStoRC(mPathStart), agentRadius, agentHeight, agentClimb, startCol);
   }

   if (mPathEnd != Point3F::Max)
   {
      drawAgent(dd, DTStoRC(mPathEnd), agentRadius, agentHeight, agentClimb, endCol);
   }
   dd.depthMask(true);

   mNavMesh->renderSearch(dd);

   dd.immediateRender();

   if (!mCurFollowObject.isNull())
      renderBoxOutline(mCurFollowObject->getWorldBox(), ColorI::LIGHT);
   if (!mCurPlayer.isNull())
      renderBoxOutline(mCurPlayer->getWorldBox(), ColorI::BLUE);
   if (!mPlayer.isNull())
      renderBoxOutline(mPlayer->getWorldBox(), ColorI::GREEN);
   if (!mFollowObject.isNull())
      renderBoxOutline(mFollowObject->getWorldBox(), ColorI::WHITE);
   
}

bool NavMeshTestTool::updateGuiInfo()
{
   SimObject* statusbar;
   Sim::findObject("EditorGuiStatusBar", statusbar);

   GuiTextCtrl* selectionBar;
   Sim::findObject("EWorldEditorStatusBarSelection", selectionBar);

   String text;

   if (mPlayer)
      text = "LMB To Select move Destination. LSHIFT+LMB To Deselect Current Bot.";
   if (mCurPlayer != NULL && mCurPlayer != mPlayer)
      text = "LMB To select Bot.";

   if (mPlayer == NULL)
   {
      text = "LMB To place start/end for test path.";
   }

   if (mSpawnClass != String::EmptyString && mSpawnDatablock != String::EmptyString)
      text += " CTRL+LMB To spawn a new Bot.";

   if (mSelectFollow)
      text = "LMB To select Follow Target.";

   if (statusbar)
      Con::executef(statusbar, "setInfo", text.c_str());

   text = "";
   if (mPlayer)
      text = String::ToString("Bot Selected: %d", mPlayer->getId());

   if (selectionBar)
      selectionBar->setText(text);

   return true;
}

S32 NavMeshTestTool::getPlayerId()
{
   return mPlayer.isNull() ? 0 : mPlayer->getId();
}

S32 NavMeshTestTool::getFollowObjectId()
{
   return mFollowObject.isNull() ? 0 : mFollowObject->getId();
}


DefineEngineMethod(NavMeshTestTool, getPlayer, S32, (), ,
   "@brief Return the current player id.")
{
   return object->getPlayerId();
}

DefineEngineMethod(NavMeshTestTool, getFollowObject, S32, (), ,
   "@brief Return the current follow object id.")
{
   return object->getFollowObjectId();
}

DefineEngineMethod(NavMeshTestTool, setSpawnClass, void, (String className), , "")
{
   object->setSpawnClass(className);
}

DefineEngineMethod(NavMeshTestTool, setSpawnDatablock, void, (String dbName), , "")
{
   object->setSpawnDatablock(dbName);
}

DefineEngineMethod(NavMeshTestTool, followSelectMode, void, (), ,
   "@brief Set NavMeshTool to select a follow object.")
{
   return object->followSelectMode();
}

