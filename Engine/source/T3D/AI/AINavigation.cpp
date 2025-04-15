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

   // If we're following, get their position.
   mPathData.path->mTo = mControllerRef->getGoal()->getPosition();
   // Update from position and replan.
   mPathData.path->mFrom = mControllerRef->getAIInfo()->getPosition();
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
   mControllerRef->mMovement.mMoveState = AIController::ModeMove;
   mControllerRef->mMovement.mMoveSlowdown = slowdown;
   mControllerRef->mMovement.mMoveStuckTestCountdown = mControllerRef->mControllerData->mMoveStuckTestDelay;
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
      getCtrl()->throwCallback("onReachDestination");
}

bool AINavigation::setPathDestination(const Point3F& pos)
{
   if (!mNavMesh)
      updateNavMesh();
   // If we can't find a mesh, just move regularly.
   if (!mNavMesh)
   {
      //setMoveDestination(pos);
      mControllerRef->throwCallback("onPathFailed");
      return false;
   }

   // Create a new path.
   NavPath* path = new NavPath();

   path->mMesh = mNavMesh;
   path->mFrom = mControllerRef->getAIInfo()->getPosition();
   path->mTo = pos;
   path->mFromSet = path->mToSet = true;
   path->mAlwaysRender = true;
   path->mLinkTypes = mControllerRef->mControllerData->mLinkTypes;
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
      mControllerRef->clearCover();
      clearFollow();
      // Store new path.
      mPathData.path = path;
      mPathData.owned = true;
      // Skip node 0, which we are currently standing on.
      moveToNode(1);
      mControllerRef->throwCallback("onPathSuccess");
      return true;
   }
   else
   {
      // Just move normally if we can't path.
      //setMoveDestination(pos, true);
      //return;
      mControllerRef->throwCallback("onPathFailed");
      path->deleteObject();
      return false;
   }
}

void AINavigation::followObject(AIInfo* targ)
{
   if (!targ) return;

   if (targ->getDist() < mControllerRef->mControllerData->mMoveTolerance)
      return;

   if (setPathDestination(targ->getPosition()))
   {
      mControllerRef->clearCover();
      mControllerRef->setGoal(targ);
   }
}

void AINavigation::followObject(SceneObject* obj, F32 radius)
{
   mControllerRef->setGoal(obj, radius);
   followObject(mControllerRef->getGoal());
}

void AINavigation::clearFollow()
{
   mControllerRef->clearGoal();
}

void AINavigation::followNavPath(NavPath* path)
{
   // Get rid of our current path.
   clearPath();
   mControllerRef->clearCover();
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
