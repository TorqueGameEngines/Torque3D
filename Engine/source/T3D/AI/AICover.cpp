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
#include "AICover.h"
#include "AIController.h"

struct CoverSearch
{
   Point3F loc;
   Point3F from;
   F32 dist;
   F32 best;
   CoverPoint* point;
   CoverSearch() : loc(0, 0, 0), from(0, 0, 0)
   {
      best = -FLT_MAX;
      point = NULL;
      dist = FLT_MAX;
   }
};

static void findCoverCallback(SceneObject* obj, void* key)
{
   CoverPoint* p = dynamic_cast<CoverPoint*>(obj);
   if (!p || p->isOccupied())
      return;
   CoverSearch* s = static_cast<CoverSearch*>(key);
   Point3F dir = s->from - p->getPosition();
   dir.normalizeSafe();
   // Score first based on angle of cover point to enemy.
   F32 score = mDot(p->getNormal(), dir);
   // Score also based on distance from seeker.
   score -= (p->getPosition() - s->loc).len() / s->dist;
   // Finally, consider cover size.
   score += (p->getSize() + 1) / CoverPoint::NumSizes;
   score *= p->getQuality();
   if (score > s->best)
   {
      s->best = score;
      s->point = p;
   }
}

bool AIController::findCover(const Point3F& from, F32 radius)
{
   if (radius <= 0)
      return false;

   // Create a search state.
   CoverSearch s;
   s.loc = getAIInfo()->getPosition();
   s.dist = radius;
   // Direction we seek cover FROM.
   s.from = from;

   // Find cover points.
   Box3F box(radius * 2.0f);
   box.setCenter(getAIInfo()->getPosition());
   getAIInfo()->mObj->getContainer()->findObjects(box, MarkerObjectType, findCoverCallback, &s);

   // Go to cover!
   if (s.point)
   {
      // Calling setPathDestination clears cover...
      bool foundPath = getNav()->setPathDestination(s.point->getPosition(), true);
      setCover(s.point);
      s.point->setOccupied(true);
      return foundPath;
   }
   return false;
}


DefineEngineMethod(AIController, findCover, S32, (Point3F from, F32 radius), ,
   "@brief Tells the AI to find cover nearby.\n\n"

   "@param from   Location to find cover from (i.e., enemy position).\n"
   "@param radius Distance to search for cover.\n"
   "@return Cover point ID if cover was found, -1 otherwise.\n\n")
{
   if (object->findCover(from, radius))
   {
      CoverPoint* cover = object->getCover()->mCoverPoint.getObject();
      return cover ? cover->getId() : -1;
   }
   else
   {
      return -1;
   }
}
