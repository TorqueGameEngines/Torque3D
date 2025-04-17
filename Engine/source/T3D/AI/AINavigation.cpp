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
#include "AINavigation.h"
#include "AIController.h"

AINavigation::AINavigation(AIController* controller)
{
   mControllerRef = controller;
   mJump = None;
   mNavSize = Regular;
}

NavMesh* AINavigation::findNavMesh() const
{
   GameBase* gbo = dynamic_cast<GameBase*>(mControllerRef->getAIInfo()->mObj.getPointer());
   // Search for NavMeshes that contain us entirely with the smallest possible
   // volume.
   NavMesh* mesh = NULL;
   SimSet* set = NavMesh::getServerSet();
   for (U32 i = 0; i < set->size(); i++)
   {
      NavMesh* m = static_cast<NavMesh*>(set->at(i));
      if (m->getWorldBox().isContained(gbo->getWorldBox()))
      {
         // Check that mesh size is appropriate.
         if (gbo->isMounted())
         {
            if (!m->mVehicles)
               continue;
         }
         else
         {
            if ((getNavSize() == Small && !m->mSmallCharacters) ||
               (getNavSize() == Regular && !m->mRegularCharacters) ||
               (getNavSize() == Large && !m->mLargeCharacters))
               continue;
         }
         if (!mesh || m->getWorldBox().getVolume() < mesh->getWorldBox().getVolume())
            mesh = m;
      }
   }
   return mesh;
}

void AINavigation::updateNavMesh()
{
   GameBase* gbo = dynamic_cast<GameBase*>(mControllerRef->getAIInfo()->mObj.getPointer());
   NavMesh* old = mNavMesh;
   if (mNavMesh.isNull())
      mNavMesh = findNavMesh();
   else
   {
      if (!mNavMesh->getWorldBox().isContained(gbo->getWorldBox()))
         mNavMesh = findNavMesh();
   }
   // See if we need to update our path.
   if (mNavMesh != old && !mPathData.path.isNull())
   {
      setPathDestination(mPathData.path->mTo);
   }
}

void AINavigation::moveToNode(S32 node)
{
   if (mPathData.path.isNull())
      return;

   // -1 is shorthand for 'last path node'.
   if (node == -1)
      node = mPathData.path->size() - 1;

   // Consider slowing down on the last path node.
   setMoveDestination(mPathData.path->getNode(node), false);

   // Check flags for this segment.
   if (mPathData.index)
   {
      U16 flags = mPathData.path->getFlags(node - 1);
      // Jump if we must.
      if (flags & LedgeFlag)
         mJump = Ledge;
      else if (flags & JumpFlag)
         mJump = Now;
      else
         // Catch pathing errors.
         mJump = None;
   }

   // Store current index.
   mPathData.index = node;
}

void AINavigation::repath()
{
   // Ineffectual if we don't have a path, or are using someone else's.
   if (mPathData.path.isNull() || !mPathData.owned)
      return;

   if (!getCtrl()->getGoal()) return;

   // If we're following, get their position.
   mPathData.path->mTo = getCtrl()->getGoal()->getPosition();
   // Update from position and replan.
   mPathData.path->mFrom = getCtrl()->getAIInfo()->getPosition();
   mPathData.path->plan();
   // Move to first node (skip start pos).
   moveToNode(1);
}

Point3F AINavigation::getPathDestination() const
{
   if (!mPathData.path.isNull())
      return mPathData.path->mTo;
   return Point3F(0, 0, 0);

}

void AINavigation::setMoveDestination(const Point3F& location, bool slowdown)
{
   mMoveDestination = location;
   getCtrl()->mMovement.mMoveState = AIController::ModeMove;
   getCtrl()->mMovement.mMoveSlowdown = slowdown;
   getCtrl()->mMovement.mMoveStuckTestCountdown = getCtrl()->mControllerData->mMoveStuckTestDelay;
}

void AINavigation::onReachDestination()
{

#ifdef TORQUE_NAVIGATION_ENABLED
   if (!getPath().isNull())
   {
      if (mPathData.index == getPath()->size() - 1)
      {
         // Handle looping paths.
         if (getPath()->mIsLooping)
            moveToNode(0);
         // Otherwise end path.
         else
         {
            clearPath();
            getCtrl()->throwCallback("onReachDestination");
         }
      }
      else
      {
         moveToNode(mPathData.index + 1);
         // Throw callback every time if we're on a looping path.
         //if(mPathData.path->mIsLooping)
            //throwCallback("onReachDestination");
      }
   }
   else
#endif
   {
      getCtrl()->throwCallback("onReachDestination");
      getCtrl()->mMovement.mMoveState = AIController::ModeStop;
   }
}

bool AINavigation::setPathDestination(const Point3F& pos)
{
   if (!mNavMesh)
      updateNavMesh();
   // If we can't find a mesh, just move regularly.
   if (!mNavMesh)
   {
      //setMoveDestination(pos);
      getCtrl()->throwCallback("onPathFailed");
      return false;
   }

   // Create a new path.
   NavPath* path = new NavPath();

   path->mMesh = mNavMesh;
   path->mFrom = getCtrl()->getAIInfo()->getPosition();
   path->mTo = pos;
   path->mFromSet = path->mToSet = true;
   path->mAlwaysRender = true;
   path->mLinkTypes = getCtrl()->mControllerData->mLinkTypes;
   path->mXray = true;
   // Paths plan automatically upon being registered.
   if (!path->registerObject())
   {
      delete path;
      return false;
   }

   if (path->success())
   {
      // Clear any current path we might have.
      clearPath();
      getCtrl()->clearCover();
      clearFollow();
      // Store new path.
      mPathData.path = path;
      mPathData.owned = true;
      // Skip node 0, which we are currently standing on.
      moveToNode(1);
      getCtrl()->throwCallback("onPathSuccess");
      return true;
   }
   else
   {
      // Just move normally if we can't path.
      //setMoveDestination(pos, true);
      //return;
      getCtrl()->throwCallback("onPathFailed");
      path->deleteObject();
      return false;
   }
}

void AINavigation::followObject()
{
   if (getCtrl()->getGoal()->getDist() < getCtrl()->mControllerData->mMoveTolerance)
      return;

   if (setPathDestination(getCtrl()->getGoal()->getPosition()))
   {
      getCtrl()->clearCover();
   }
}

void AINavigation::followObject(SceneObject* obj, F32 radius)
{
   getCtrl()->setGoal(obj, radius);
   followObject();
}

void AINavigation::clearFollow()
{
   getCtrl()->clearGoal();
}

void AINavigation::followNavPath(NavPath* path)
{
   // Get rid of our current path.
   clearPath();
   getCtrl()->clearCover();
   clearFollow();

   // Follow new path.
   mPathData.path = path;
   mPathData.owned = false;
   // Start from 0 since we might not already be there.
   moveToNode(0);
}

void AINavigation::clearPath()
{
   // Only delete if we own the path.
   if (!mPathData.path.isNull() && mPathData.owned)
      mPathData.path->deleteObject();
   // Reset path data.
   mPathData = PathData();
}

DefineEngineMethod(AIController, setMoveDestination, void, (Point3F goal, bool slowDown), (true),
   "@brief Tells the AI to move to the location provided\n\n"

   "@param goal Coordinates in world space representing location to move to.\n"
   "@param slowDown A boolean value. If set to true, the bot will slow down "
   "when it gets within 5-meters of its move destination. If false, the bot "
   "will stop abruptly when it reaches the move destination. By default, this is true.\n\n"

   "@note Upon reaching a move destination, the bot will clear its move destination and "
   "calls to getMoveDestination will return \"0 0 0\"."

   "@see getMoveDestination()\n")
{
   object->getNav()->setMoveDestination(goal, slowDown);
}


DefineEngineMethod(AIController, getMoveDestination, Point3F, (), ,
   "@brief Get the AIPlayer's current destination.\n\n"

   "@return Returns a point containing the \"x y z\" position "
   "of the AIPlayer's current move destination. If no move destination "
   "has yet been set, this returns \"0 0 0\"."

   "@see setMoveDestination()\n")
{
   return object->getNav()->getMoveDestination();
}

DefineEngineMethod(AIController, setPathDestination, bool, (Point3F goal), ,
   "@brief Tells the AI to find a path to the location provided\n\n"

   "@param goal Coordinates in world space representing location to move to.\n"
   "@return True if a path was found.\n\n"

   "@see getPathDestination()\n"
   "@see setMoveDestination()\n")
{
   return object->getNav()->setPathDestination(goal);
}


DefineEngineMethod(AIController, getPathDestination, Point3F, (), ,
   "@brief Get the AIPlayer's current pathfinding destination.\n\n"

   "@return Returns a point containing the \"x y z\" position "
   "of the AIPlayer's current path destination. If no path destination "
   "has yet been set, this returns \"0 0 0\"."

   "@see setPathDestination()\n")
{
   return object->getNav()->getPathDestination();
}

DefineEngineMethod(AIController, followNavPath, void, (SimObjectId obj), ,
   "@brief Tell the AIPlayer to follow a path.\n\n"

   "@param obj ID of a NavPath object for the character to follow.")
{
   NavPath* path;
   if (Sim::findObject(obj, path))
      object->getNav()->followNavPath(path);
}

DefineEngineMethod(AIController, followObject, void, (SimObjectId obj, F32 radius), ,
   "@brief Tell the AIPlayer to follow another object.\n\n"

   "@param obj ID of the object to follow.\n"
   "@param radius Maximum distance we let the target escape to.")
{
   SceneObject* follow;
   object->getNav()->clearPath();
   object->clearCover();
   object->getNav()->clearFollow();

   if (Sim::findObject(obj, follow))
      object->getNav()->followObject(follow, radius);
}


DefineEngineMethod(AIController, repath, void, (), ,
   "@brief Tells the AI to re-plan its path. Does nothing if the character "
   "has no path, or if it is following a mission path.\n\n")
{
   object->getNav()->repath();
}

DefineEngineMethod(AIController, findNavMesh, S32, (), ,
   "@brief Get the NavMesh object this AIPlayer is currently using.\n\n"

   "@return The ID of the NavPath object this character is using for "
   "pathfinding. This is determined by the character's location, "
   "navigation type and other factors. Returns -1 if no NavMesh is "
   "found.")
{
   NavMesh* mesh = object->getNav()->getNavMesh();
   return mesh ? mesh->getId() : -1;
}

DefineEngineMethod(AIController, getNavMesh, S32, (), ,
   "@brief Return the NavMesh this AIPlayer is using to navigate.\n\n")
{
   NavMesh* m = object->getNav()->getNavMesh();
   return m ? m->getId() : 0;
}

DefineEngineMethod(AIController, setNavSize, void, (const char* size), ,
   "@brief Set the size of NavMesh this character uses. One of \"Small\", \"Regular\" or \"Large\".")
{
   if (!String::compare(size, "Small"))
      object->getNav()->setNavSize(AINavigation::Small);
   else if (!String::compare(size, "Regular"))
      object->getNav()->setNavSize(AINavigation::Regular);
   else if (!String::compare(size, "Large"))
      object->getNav()->setNavSize(AINavigation::Large);
   else
      Con::errorf("AIPlayer::setNavSize: no such size '%s'.", size);
}

DefineEngineMethod(AIController, getNavSize, const char*, (), ,
   "@brief Return the size of NavMesh this character uses for pathfinding.")
{
   switch (object->getNav()->getNavSize())
   {
   case AINavigation::Small:
      return "Small";
   case AINavigation::Regular:
      return "Regular";
   case AINavigation::Large:
      return "Large";
   }
   return "";
}
