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
#ifndef _AINAVIGATION_H_
#define _AINAVIGATION_H_

#include "AIInfo.h"

#include "navigation/navPath.h"
#include "navigation/navMesh.h"

class AIController;
struct AINavigation
{
   AIController* mControllerRef;
   AIController* getCtrl() { return mControllerRef; };

   AINavigation() = delete;
   AINavigation(AIController* controller);
   ~AINavigation();
   Point3F mMoveDestination;
   void setMoveDestination(const Point3F& location, bool slowdown);
   Point3F getMoveDestination() const { return mMoveDestination; };
   bool setPathDestination(const Point3F& pos, bool replace = false);
   Point3F getPathDestination() const;

   void onReachDestination();

   void followObject();
   void followObject(SceneObject* obj, F32 radius);
   void clearFollow();

#ifdef TORQUE_NAVIGATION_ENABLED
   /// Stores information about a path.
   struct PathData {
      /// Pointer to path object.
      SimObjectPtr<NavPath> path;
      /// Do we own our path? If so, we will delete it when finished.
      bool owned;
      /// Path node we're at.
      U32 index;
      /// Default constructor.
      PathData() : path(NULL)
      {
         owned = false;
         index = 0;
      }
   };

   /// Should we jump?
   enum JumpStates {
      None,  ///< No, don't jump.
      Now,   ///< Jump immediately.
      Ledge, ///< Jump when we walk off a ledge.
   };

   enum NavSize {
      Small,
      Regular,
      Large
   } mNavSize;
   void setNavSize(NavSize size) { mNavSize = size; updateNavMesh(); }
   NavSize getNavSize() const { return mNavSize; }

   /// NavMesh we pathfind on.
   SimObjectPtr<NavMesh> mNavMesh;
   NavMesh* findNavMesh() const;
   void updateNavMesh();
   NavMesh* getNavMesh() const { return mNavMesh; }
   PathData mPathData;
   JumpStates mJump;

   /// Clear out the current path.
   void clearPath();
   void repath();

   /// Get the current path we're following.
   SimObjectPtr<NavPath> getPath() { return mPathData.path; };
   void followNavPath(NavPath* path);

   /// Move to the specified node in the current path.
   void moveToNode(S32 node);
   bool avoidObstacles();
   bool flock();
#endif
};

#endif
