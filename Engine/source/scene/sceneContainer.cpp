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

#include "platform/platform.h"
#include "scene/sceneContainer.h"

#include "collision/extrudedPolyList.h"
#include "collision/earlyOutPolyList.h"
#include "scene/sceneObject.h"
#include "platform/profiler.h"
#include "console/engineAPI.h"
#include "math/util/frustum.h"


// [rene, 02-Mar-11]
//  - *Loads* of copy&paste sin in this file (among its many other sins); all the findObjectXXX methods
//    are trivial permutations of the same snippet of copy&pasted code
//  - FindCallback should return a bool so it's possible to use the findObjectXXX methods to look
//    for the first object matching a certain criteria


SceneContainer gServerContainer;
SceneContainer gClientContainer;

const U32 SceneContainer::csmNumAxisBins = 16; // 16*16 = 256 possible bins
const F32 SceneContainer::csmBinSize = 64;
const F32 SceneContainer::csmTotalAxisBinSize = SceneContainer::csmBinSize * SceneContainer::csmNumAxisBins;
const U32 SceneContainer::csmOverflowBinIdx = (SceneContainer::csmNumAxisBins * SceneContainer::csmNumAxisBins);
const U32 SceneContainer::csmTotalNumBins = SceneContainer::csmOverflowBinIdx + 1;


// Statics used by buildPolyList methods
static AbstractPolyList* sPolyList;
static SphereF sBoundingSphere;
static Box3F sBoundingBox;

struct SceneRayHelper
{
   struct State
   {
      // Vector range
      Point3F mNormalStart;
      Point3F mNormalEnd;

      // Bin range
      U32 mMinX;
      U32 mMaxX;
      U32 mMinY;
      U32 mMaxY;

      F32 mCurrentT;

      /// Setup raycast. Returns true if applyBin can be used
      bool setup(Point3F start, Point3F end)
      {
         // These are just for rasterizing the line against the grid.  We want the x coord
         //  of the start to be <= the x coord of the end
         if (start.x <= end.x)
         {
            mNormalStart = start;
            mNormalEnd   = end;
         }
         else
         {
            mNormalStart = end;
            mNormalEnd   = start;
         }

         // Ok, let's scan the grids.  The simplest way to do this will be to scan across in
         //  x, finding the y range for each affected bin...
         //if (mNormalStart.x == mNormalEnd.x)
         //   Con::printf("X start = %g, end = %g", mNormalStart.x, mNormalEnd.x);

         SceneContainer::getBinRange(mNormalStart.x, mNormalEnd.x, mMinX, mMaxX);
         SceneContainer::getBinRange(getMin(mNormalStart.y, mNormalEnd.y),
                                     getMax(mNormalStart.y, mNormalEnd.y), mMinY, mMaxY);

         //if (mNormalStart.x == mNormalEnd.x && minX != maxX)
         //   Con::printf("X min = %d, max = %d", minX, maxX);
         //if (mNormalStart.y == mNormalEnd.y && minY != maxY)
         //   Con::printf("Y min = %d, max = %d", minY, maxY);

         mCurrentT = F32_MAX;

         return canUseSimpleCase();
      }

      /// Returns whether or not we can use castInBin
      inline bool canUseSimpleCase() const
      {
         return (
            (mFabs(mNormalStart.x - mNormalEnd.x) < SceneContainer::csmTotalAxisBinSize && mMinX == mMaxX) ||
            (mFabs(mNormalStart.y - mNormalEnd.y) < SceneContainer::csmTotalAxisBinSize && mMinY == mMaxY));
      }
   };

   struct QueryParams
   {
      const Point3F* start;
      const Point3F* end;
      U32 mask;
      U32 seqKey;
      SceneContainer::CastRayType type;
   };

   /// Performs raycast in a line, where the range is contiguous and 
   /// does not cross the edge boundary.
   /// Invokes Delegate::checkFunc to locate candidates.
   template<typename DEL> static bool castInBinSimple(
      const QueryParams params,
      State& state,
      SceneContainer::ObjectList* binLists,
      RayInfo* info, DEL del)
   {
      U32 count;
      U32 incX, incY;
      F32 currentT = state.mCurrentT;
      bool foundCandidate = false;

      if (state.mMinX == state.mMaxX)
      {
         count = state.mMaxY - state.mMinY + 1;
         incX  = 0;
         incY  = 1;
      }
      else
      {
         count = state.mMaxX - state.mMinX + 1;
         incX  = 1;
         incY  = 0;
      }

      U32 x = state.mMinX;
      U32 y = state.mMinY;
      for (U32 i = 0; i < count; i++)
      {
         U32 checkX = x % SceneContainer::csmNumAxisBins;
         U32 checkY = y % SceneContainer::csmNumAxisBins;

         SceneContainer::ObjectList& chainList = binLists[(checkY * SceneContainer::csmNumAxisBins) + checkX];
         for(SceneObject* ptr : chainList)
         {
            if (ptr->getContainerSeqKey() == params.seqKey)
               continue;

            if (del.checkFunc(params, ptr, info, currentT) && !foundCandidate)
               foundCandidate = true;

            ptr->setContainerSeqKey(params.seqKey);
         }

         x += incX;
         y += incY;
      }

      state.mCurrentT = currentT;
      return foundCandidate;
   }

   /// Performs raycast in a specific bin idx
   /// Invokes Delegate::checkFunc to locate candidates.
   template<typename DEL> static bool castInBinIdx(
      const QueryParams params,
      State& state,
      SceneContainer::ObjectList* binLists,
      U32 idx,
      RayInfo* info,
      DEL del)
   {
      F32 currentT = state.mCurrentT;
      bool foundCandidate = false;

      SceneContainer::ObjectList& chainList = binLists[idx];
      for(SceneObject* ptr : chainList)
      {
         if (ptr->getContainerSeqKey() == params.seqKey)
            continue;

         if (del.checkFunc(params, ptr, info, currentT) && !foundCandidate)
            foundCandidate = true;

         ptr->setContainerSeqKey(params.seqKey);
      }

      state.mCurrentT = currentT;
      return foundCandidate;
   }

   /// Performs raycast based on rasterizing the line vector,
   /// also handling any cases where the edge boundary is crossed.
   /// Invokes Delegate::checkFunc to locate candidates.
   template<typename DEL> static bool castInBins(
      const QueryParams params,
      State& state,
      SceneContainer::ObjectList* binLists,
      RayInfo* info,
      DEL del)
   {
      bool foundCandidate = false;
      F32 currStartX = state.mNormalStart.x;
      F32 currentT = state.mCurrentT;

      AssertFatal(currStartX != state.mNormalEnd.x, "This is going to cause problems in SceneContainer::castRay");
      if(mIsNaN_F(currStartX))
      {
         return false;
      }

      // Copy these to local variables
      Point2F normalStart = state.mNormalStart.asPoint2F();
      Point2F normalEnd = state.mNormalEnd.asPoint2F();

      while (currStartX != normalEnd.x)
      {
         F32 currEndX   = getMin(currStartX + SceneContainer::csmTotalAxisBinSize, normalEnd.x);

         F32 currStartT = (currStartX - normalStart.x) / (normalEnd.x - normalStart.x);
         F32 currEndT   = (currEndX   - normalStart.x) / (normalEnd.x - normalStart.x);

         F32 y1 = normalStart.y + (normalEnd.y - normalStart.y) * currStartT;
         F32 y2 = normalStart.y + (normalEnd.y - normalStart.y) * currEndT;

         U32 subMinX, subMaxX;
         SceneContainer::getBinRange(currStartX, currEndX, subMinX, subMaxX);

         F32 subStartX = currStartX;
         F32 subEndX   = currStartX;

         if (currStartX < 0.0f)
            subEndX -= mFmod(subEndX, SceneContainer::csmBinSize);
         else
            subEndX += (SceneContainer::csmBinSize - mFmod(subEndX, SceneContainer::csmBinSize));

         for (U32 currXBin = subMinX; currXBin <= subMaxX; currXBin++)
         {
            U32 checkX = currXBin % SceneContainer::csmNumAxisBins;

            F32 subStartT = (subStartX - currStartX) / (currEndX - currStartX);
            F32 subEndT   = getMin(F32((subEndX   - currStartX) / (currEndX - currStartX)), 1.f);

            F32 subY1 = y1 + (y2 - y1) * subStartT;
            F32 subY2 = y1 + (y2 - y1) * subEndT;

            U32 newMinY, newMaxY;
            SceneContainer::getBinRange(getMin(subY1, subY2), getMax(subY1, subY2), newMinY, newMaxY);

            for (U32 i = newMinY; i <= newMaxY; i++)
            {
               U32 checkY = i % SceneContainer::csmNumAxisBins;

               SceneContainer::ObjectList& chainList = binLists[(checkY * SceneContainer::csmNumAxisBins) + checkX];
               for(SceneObject* ptr : chainList)
               {
                  if (ptr->getContainerSeqKey() == params.seqKey)
                     continue;

                  if (del.checkFunc(params, ptr, info, currentT) && !foundCandidate)
                     foundCandidate = true;

                  ptr->setContainerSeqKey(params.seqKey);
               }
            }

            subStartX = subEndX;
            subEndX   = getMin(subEndX + SceneContainer::csmBinSize, currEndX);
         }

         currStartX = currEndX;
      }

      state.mCurrentT = currentT;
      return foundCandidate;
   }

   /// Tests an object against a ray
   template<typename CBFunc> struct CheckObjectRayDelegate
   {
      CBFunc mFunc;

      CheckObjectRayDelegate(CBFunc& func) : mFunc(func)
      {
      }

      inline bool checkFunc(QueryParams params, SceneObject* ptr, RayInfo* info, F32& currentT) const
      {
         // Ignore disabled collision
         if (!ptr->isCollisionEnabled())
            return false;

         if ((ptr->getTypeMask() & params.mask) != 0)
         {
            if (ptr->isGlobalBounds() ||
               ptr->getWorldBox().collideLine(*params.start, *params.end))
            {
               Point3F xformedStart, xformedEnd;
               ptr->mWorldToObj.mulP(*params.start, &xformedStart);
               ptr->mWorldToObj.mulP(*params.end, &xformedEnd);
               xformedStart.convolveInverse(ptr->mObjScale);
               xformedEnd.convolveInverse(ptr->mObjScale);

               RayInfo ri;
               ri.generateTexCoord = info->generateTexCoord;

               if (mFunc && !mFunc(ptr))
                  return false;

               bool result = false;
               if (params.type == SceneContainer::CollisionGeometry)
                  result = ptr->castRay(xformedStart, xformedEnd, &ri);
               else if (params.type == SceneContainer::RenderedGeometry)
                  result = ptr->castRayRendered(xformedStart, xformedEnd, &ri);

               if (result)
               {
                  if (ri.t < currentT)
                  {
                     *info = ri;
                     info->point.interpolate(*params.start, *params.end, info->t);
                     currentT = ri.t;
                     info->distance = (*params.start - info->point).len();
                     return true;
                  }
               }
            }
         }

         return false;
      }
   };

};


//=============================================================================
//    SceneContainer.
//=============================================================================

//-----------------------------------------------------------------------------

SceneContainer::SceneContainer()
{
   mSearchInProgress = false;
   mCurrSeqKey = 0;

   mBinArray = new ObjectList[csmTotalNumBins];
   for (U32 i=0; i<csmTotalNumBins; i++)
   {
      VECTOR_SET_ASSOCIATION( mBinArray[i] );
   }

   VECTOR_SET_ASSOCIATION( mSearchList );
   VECTOR_SET_ASSOCIATION( mWaterAndZones );
   VECTOR_SET_ASSOCIATION( mTerrains );

   cleanupSearchVectors();
}

//-----------------------------------------------------------------------------

SceneContainer::~SceneContainer()
{
   for (U32 i = 0; i < csmTotalNumBins; i++)
   {
      ObjectList& list = mBinArray[i];
      std::for_each(list.begin(), list.end(), [](SceneObject* obj) {
         // Depressingly, this can give weird results if its pointing at bad memory...
         Con::warnf("Error, a %s (%x) isn't properly out of the bins!", obj->getClassName(), obj);

         // If you're getting this it means that an object created didn't
         // remove itself from its container before we destroyed the
         // container. Typically you get this behavior from particle
         // emitters, as they try to hang around until all their particles
         // die. In general it's benign, though if you get it for things
         // that aren't particle emitters it can be a bad sign!
      });
   }

   delete[] mBinArray;

   cleanupSearchVectors();
}

//-----------------------------------------------------------------------------

bool SceneContainer::addObject(SceneObject* obj)
{
   AssertFatal(obj->mContainer == NULL, "Adding already added object.");

   obj->mContainerIndex = mGlobalList.size();
   obj->mContainer = this;
   mGlobalList.push_back(obj);

   insertIntoBins(obj);

   // Also insert water and physical zone types into the special vector.
   if ( obj->getTypeMask() & ( WaterObjectType | PhysicalZoneObjectType ) )
      mWaterAndZones.push_back(obj);
   if( obj->getTypeMask() & TerrainObjectType )
      mTerrains.push_back( obj );

   return true;
}

//-----------------------------------------------------------------------------

bool SceneContainer::removeObject(SceneObject* obj)
{
   U32 existingIndex = obj->mContainerIndex;
   AssertFatal(obj->mContainer == this, "Trying to remove from wrong container.");
   obj->mContainerIndex = 0;
   obj->mContainer = NULL;

   removeFromBins(obj);

   Vector<SceneObject*>::iterator iter = mGlobalList.begin() + existingIndex;
   mGlobalList.erase_fast(iter);
   if (existingIndex < mGlobalList.size())
   {
      // Update index of swapped element
      mGlobalList[existingIndex]->mContainerIndex = existingIndex;
   }

   // Remove water and physical zone types from the special vector.
   if ( obj->getTypeMask() & ( WaterObjectType | PhysicalZoneObjectType ) )
   {
      iter = std::find( mWaterAndZones.begin(), mWaterAndZones.end(), obj );
      if( iter != mTerrains.end() )
         mWaterAndZones.erase_fast(iter);
   }

   // Remove terrain objects from special vector.
   if( obj->getTypeMask() & TerrainObjectType )
   {
      iter = std::find( mTerrains.begin(), mTerrains.end(), obj );
      if( iter != mTerrains.end() )
         mTerrains.erase_fast(iter);
   }

   return true;
}

//-----------------------------------------------------------------------------

void SceneContainer::insertIntoBins(SceneObject* obj)
{
   AssertFatal(obj != NULL, "No object?");

   if (obj->isGlobalBounds())
   {
      // This goes straight into the overflow bin
      insertIntoBins(obj, SceneBinRange::makeGlobal());
   }
   else
   {
      // The first thing we do is find which bins are covered in x and y...
      const Box3F& wBox = obj->getWorldBox();

      SceneBinRange range;
      getBinRange(wBox.minExtents.asPoint2F(), wBox.maxExtents.asPoint2F(), range);

      insertIntoBins(obj, range);
   }
}

//-----------------------------------------------------------------------------

void SceneContainer::insertIntoBins(SceneObject* obj,
                               const SceneBinRange& range)
{
   PROFILE_START(SceneContainer_InsertIntoBins);
   AssertFatal(obj != NULL, "No object?");

   mBinValueList.clear();
   SceneBinListLookup binLookup;
   binLookup.mRange = range;

   // For huge objects, dump them into the overflow bin.  Otherwise, everything
   //  goes into the grid...
   //
   if (!(range.isGlobal() || 
         range.shouldOverflow()))
   {
      for (U32 i = (U32)range.minCoord[1]; i <= (U32)range.maxCoord[1]; i++)
      {
         U32 insertY = i % csmNumAxisBins;
         U32 base    = insertY * csmNumAxisBins;
         for (U32 j = (U32)range.minCoord[0]; j <= (U32)range.maxCoord[0]; j++)
         {
            const U32 insertX = j % csmNumAxisBins;
            const U32 binIDX = base + insertX;

            mBinValueList.push_back(binIDX);
            mBinArray[binIDX].push_back(obj);
         }
      }

      // Add lookup
      binLookup.mListHandle = mBinRefLists.allocList(mBinValueList.size(), mBinValueList.address());
      obj->mContainerLookup = binLookup;
   }
   else
   {
      // Straight into the overflow bin
      BinValueList::BinValue overflowID = csmOverflowBinIdx;
      
      binLookup.mListHandle = mBinRefLists.allocList(1, &overflowID);
      mBinArray[csmOverflowBinIdx].push_back(obj);

      obj->mContainerLookup = binLookup;
   }

   PROFILE_END();
}

//-----------------------------------------------------------------------------

void SceneContainer::removeFromBins(SceneObject* object)
{
   PROFILE_START(RemoveFromBins);
   AssertFatal(object != NULL, "No object?");
   AssertFatal(object->mContainerLookup.mListHandle != 0, "SceneContainer::removeFromBins - object not in bins");
   
   BinValueList::ListHandle listHandle = (BinValueList::ListHandle)object->mContainerLookup.mListHandle;
   U32 numValues = 0;

   // Remove all references to obj in the bin list
   BinValueList::BinValue* entryList = mBinRefLists.getValues(listHandle, numValues);
   for (U32 i = 0; i < numValues; i++)
   {
      const BinValueList::BinValue binIDX = entryList[i];
      AssertFatal(binIDX < csmTotalNumBins, "invalid");

      ObjectList& list = mBinArray[binIDX];

      ObjectList::iterator itr = std::find(list.begin(), list.end(), object);
      if (itr != list.end())
      {
         list.erase_fast(itr);
      }
   }

   // Finally remove the bin list record
   mBinRefLists.freeList(listHandle);
   object->mContainerLookup.mListHandle = 0;

   PROFILE_END();
}

//-----------------------------------------------------------------------------

void SceneContainer::checkBins(SceneObject* object)
{
   AssertFatal(object != NULL, "Invalid object");

   if ((BinValueList::ListHandle)object->mContainerLookup.mListHandle == 0)
   {
      // Failsafe case
      insertIntoBins(object);
      return;
   }

   SceneBinRange lookupRange = object->mContainerLookup.mRange;
   SceneBinRange compareRange;

   if (!object->isGlobalBounds())
   {
      // Find bin range
      const Box3F& wBox = object->getWorldBox();

      SceneContainer::getBinRange(wBox.minExtents.asPoint2F(), wBox.maxExtents.asPoint2F(), compareRange);
   }
   else
   {
      // Simple case: global
      compareRange.setGlobal();
   }

   // Finally re-insert if required
   if (lookupRange != compareRange)
   {
      removeFromBins(object);
      insertIntoBins(object);
   }
}

//-----------------------------------------------------------------------------

void SceneContainer::findObjects(const Box3F& box, U32 mask, FindCallback callback, void *key)
{
   PROFILE_SCOPE(ContainerFindObjects_Box);

   // If we're searching for just water, just physical zones, or
   // just water and physical zones then use the optimized path.
   if ( mask == WaterObjectType || 
        mask == PhysicalZoneObjectType ||
        mask == (WaterObjectType|PhysicalZoneObjectType) )
   {
      _findSpecialObjects( mWaterAndZones, box, mask, callback, key );
      return;
   }
   else if( mask == TerrainObjectType )
   {
      _findSpecialObjects( mTerrains, box, mask, callback, key );
      return;
   }

   AssertFatal( !mSearchInProgress, "SceneContainer::findObjects - Container queries are not re-entrant" );
   mSearchInProgress = true;

   U32 minX, maxX, minY, maxY;
   getBinRange(box.minExtents.x, box.maxExtents.x, minX, maxX);
   getBinRange(box.minExtents.y, box.maxExtents.y, minY, maxY);
   mCurrSeqKey++;

   for (U32 i = minY; i <= maxY; i++)
   {
      U32 insertY = i % csmNumAxisBins;
      U32 base    = insertY * csmNumAxisBins;
      for (U32 j = minX; j <= maxX; j++)
      {
         U32 insertX = j % csmNumAxisBins;

         ObjectList& chainList = mBinArray[base + insertX];
         for(SceneObject* object : chainList)
         {
            if (object->getContainerSeqKey() != mCurrSeqKey)
            {
               object->setContainerSeqKey(mCurrSeqKey);

               if ((object->getTypeMask() & mask) != 0 &&
                   object->isCollisionEnabled())
               {
                  if (object->getWorldBox().isOverlapped(box) || object->isGlobalBounds())
                  {
                     (*callback)(object,key);
                  }
               }
            }
         }
      }
   }

   ObjectList& overflowList = mBinArray[csmOverflowBinIdx];
   for(SceneObject* object : overflowList)
   {
      if (object->getContainerSeqKey() != mCurrSeqKey)
      {
         object->setContainerSeqKey(mCurrSeqKey);

         if ((object->getTypeMask() & mask) != 0 &&
             object->isCollisionEnabled())
         {
            if (object->getWorldBox().isOverlapped(box) || object->isGlobalBounds())
            {
               (*callback)(object,key);
            }
         }
      }
   }

   mSearchInProgress = false;
}

//-----------------------------------------------------------------------------

void SceneContainer::findObjects( const Frustum &frustum, U32 mask, FindCallback callback, void *key )
{
   PROFILE_SCOPE(ContainerFindObjects_Frustum);

   Box3F searchBox = frustum.getBounds();

   if (  mask == WaterObjectType || 
         mask == PhysicalZoneObjectType ||
         mask == (WaterObjectType|PhysicalZoneObjectType) )
   {
      _findSpecialObjects( mWaterAndZones, searchBox, mask, callback, key );
      return;
   }
   else if( mask == TerrainObjectType )
   {
      _findSpecialObjects( mTerrains, searchBox, mask, callback, key );
      return;
   }

   AssertFatal( !mSearchInProgress, "SceneContainer::findObjects - Container queries are not re-entrant" );
   mSearchInProgress = true;

   U32 minX, maxX, minY, maxY;
   getBinRange(searchBox.minExtents.x, searchBox.maxExtents.x, minX, maxX);
   getBinRange(searchBox.minExtents.y, searchBox.maxExtents.y, minY, maxY);
   mCurrSeqKey++;

   for (U32 i = minY; i <= maxY; i++)
   {
      U32 insertY = i % csmNumAxisBins;
      U32 base    = insertY * csmNumAxisBins;
      for (U32 j = minX; j <= maxX; j++)
      {
         U32 insertX = j % csmNumAxisBins;

         ObjectList& chainList = mBinArray[base + insertX];
         for(SceneObject* object : chainList)
         {
            if (object->getContainerSeqKey() != mCurrSeqKey)
            {
               object->setContainerSeqKey(mCurrSeqKey);

               if ((object->getTypeMask() & mask) != 0 &&
                  object->isCollisionEnabled())
               {
                  const Box3F &worldBox = object->getWorldBox();
                  if ( object->isGlobalBounds() || worldBox.isOverlapped(searchBox) )
                  {
                     if ( !frustum.isCulled( worldBox ) )
                        (*callback)(object,key);
                  }
               }
            }
         }
      }
   }

   ObjectList& overflowList = mBinArray[csmOverflowBinIdx];
   for(SceneObject* object : overflowList)
   {
      if (object->getContainerSeqKey() != mCurrSeqKey)
      {
         object->setContainerSeqKey(mCurrSeqKey);

         if ((object->getTypeMask() & mask) != 0 &&
            object->isCollisionEnabled())
         {
            const Box3F &worldBox = object->getWorldBox();

            if ( object->isGlobalBounds() || worldBox.isOverlapped(searchBox) )
            {
               if ( !frustum.isCulled( worldBox ) )
                  (*callback)(object,key);
            }
         }
      }
   }

   mSearchInProgress = false;
}

//-----------------------------------------------------------------------------

void SceneContainer::polyhedronFindObjects(const Polyhedron& polyhedron, U32 mask, FindCallback callback, void *key)
{
   PROFILE_SCOPE(ContainerFindObjects_polyhedron);

   U32 i;
   Box3F box;
   box.minExtents.set(1e9, 1e9, 1e9);
   box.maxExtents.set(-1e9, -1e9, -1e9);

   for (i = 0; i < polyhedron.mPointList.size(); i++)
   {
      box.minExtents.setMin(polyhedron.mPointList[i]);
      box.maxExtents.setMax(polyhedron.mPointList[i]);
   }

   if (  mask == WaterObjectType || 
         mask == PhysicalZoneObjectType ||
         mask == (WaterObjectType|PhysicalZoneObjectType) )
   {
      _findSpecialObjects( mWaterAndZones, box, mask, callback, key );
      return;
   }
   else if( mask == TerrainObjectType )
   {
      _findSpecialObjects( mTerrains, mask, callback, key );
      return;
   }

   AssertFatal( !mSearchInProgress, "SceneContainer::polyhedronFindObjects - Container queries are not re-entrant" );
   mSearchInProgress = true;

   U32 minX, maxX, minY, maxY;
   getBinRange(box.minExtents.x, box.maxExtents.x, minX, maxX);
   getBinRange(box.minExtents.y, box.maxExtents.y, minY, maxY);
   mCurrSeqKey++;

   for (i = minY; i <= maxY; i++)
   {
      U32 insertY = i % csmNumAxisBins;
      U32 base    = insertY * csmNumAxisBins;
      for (U32 j = minX; j <= maxX; j++)
      {
         U32 insertX = j % csmNumAxisBins;

         ObjectList& chainList = mBinArray[base + insertX];
         for(SceneObject* object : chainList)
         {
            if (object->getContainerSeqKey() != mCurrSeqKey)
            {
               object->setContainerSeqKey(mCurrSeqKey);

               if ((object->getTypeMask() & mask) != 0 &&
                   object->isCollisionEnabled())
               {
                  if (object->getWorldBox().isOverlapped(box) || object->isGlobalBounds())
                  {
                     (*callback)(object,key);
                  }
               }
            }
         }
      }
   }

   ObjectList& overflowList = mBinArray[csmOverflowBinIdx];
   for(SceneObject* object : overflowList)
   {
      if (object->getContainerSeqKey() != mCurrSeqKey)
      {
         object->setContainerSeqKey(mCurrSeqKey);

         if ((object->getTypeMask() & mask) != 0 &&
             object->isCollisionEnabled())
         {
            if (object->getWorldBox().isOverlapped(box) || object->isGlobalBounds())
            {
               (*callback)(object,key);
            }
         }
      }
   }

   mSearchInProgress = false;
}

//-----------------------------------------------------------------------------

void SceneContainer::findObjectList( const Box3F& searchBox, U32 mask, Vector<SceneObject*> *outFound )
{
   PROFILE_SCOPE( Container_FindObjectList_Box );

   AssertFatal( !mSearchInProgress, "SceneContainer::findObjectList - Container queries are not re-entrant" );
   mSearchInProgress = true;

   U32 minX, maxX, minY, maxY;
   getBinRange(searchBox.minExtents.x, searchBox.maxExtents.x, minX, maxX);
   getBinRange(searchBox.minExtents.y, searchBox.maxExtents.y, minY, maxY);
   mCurrSeqKey++;

   for (U32 i = minY; i <= maxY; i++)
   {
      U32 insertY = i % csmNumAxisBins;
      U32 base    = insertY * csmNumAxisBins;
      for (U32 j = minX; j <= maxX; j++)
      {
         U32 insertX = j % csmNumAxisBins;

         ObjectList& chainList = mBinArray[base + insertX];
         for(SceneObject* object : chainList)
         {
            if (object->getContainerSeqKey() != mCurrSeqKey)
            {
               object->setContainerSeqKey(mCurrSeqKey);

               if ((object->getTypeMask() & mask) != 0 &&
                  object->isCollisionEnabled())
               {
                  const Box3F &worldBox = object->getWorldBox();
                  if ( object->isGlobalBounds() || worldBox.isOverlapped( searchBox ) )
                  {
                     outFound->push_back( object );
                  }
               }
            }
         }
      }
   }

   ObjectList& overflowList = mBinArray[csmOverflowBinIdx];
   for(SceneObject* object : overflowList)
   {
      if (object->getContainerSeqKey() != mCurrSeqKey)
      {
         object->setContainerSeqKey(mCurrSeqKey);

         if ((object->getTypeMask() & mask) != 0 &&
            object->isCollisionEnabled())
         {
            const Box3F &worldBox = object->getWorldBox();

            if ( object->isGlobalBounds() || worldBox.isOverlapped( searchBox ) )
            {
               outFound->push_back( object );
            }
         }
      }
   }

   mSearchInProgress = false;
}

//-----------------------------------------------------------------------------

void SceneContainer::findObjectList( const Frustum &frustum, U32 mask, Vector<SceneObject*> *outFound )
{
   PROFILE_SCOPE( Container_FindObjectList_Frustum );

   // Do a box find first.
   findObjectList( frustum.getBounds(), mask, outFound );

   // Now do the frustum testing.
   for ( U32 i=0; i < outFound->size(); )
   {
      const Box3F &worldBox = (*outFound)[i]->getWorldBox();
      if ( frustum.isCulled( worldBox ) )
         outFound->erase_fast( i );
      else
         i++;
   }
}

//-----------------------------------------------------------------------------

void SceneContainer::findObjectList( U32 mask, Vector<SceneObject*> *outFound )
{
   for (SceneObject* ptr : mGlobalList)
   {
      if ( ( ptr->getTypeMask() & mask ) != 0 )
         outFound->push_back( ptr );
   }
}

//-----------------------------------------------------------------------------

void SceneContainer::findObjects( U32 mask, FindCallback callback, void *key )
{
   for (SceneObject* ptr : mGlobalList)
   {
      if ((ptr->getTypeMask() & mask) != 0 && !ptr->mCollisionCount)
         (*callback)(ptr,key);
   }
}

//-----------------------------------------------------------------------------

void SceneContainer::_findSpecialObjects( const Vector< SceneObject* >& vector, U32 mask, FindCallback callback, void *key )
{
   PROFILE_SCOPE( Container_findSpecialObjects );

   Vector<SceneObject*>::const_iterator iter = vector.begin();
   for ( ; iter != vector.end(); iter++ )
   {
      if ( (*iter)->getTypeMask() & mask )
         callback( *iter, key );
   }   
}

//-----------------------------------------------------------------------------

void SceneContainer::_findSpecialObjects( const Vector< SceneObject* >& vector, const Box3F &box, U32 mask, FindCallback callback, void *key )
{
   PROFILE_SCOPE( Container_findSpecialObjects_Box );

   Vector<SceneObject*>::const_iterator iter = vector.begin();

   for ( ; iter != vector.end(); iter++ )
   {
      SceneObject *pObj = *iter;
      
      if ( pObj->getTypeMask() & mask &&
           ( pObj->isGlobalBounds() || pObj->getWorldBox().isOverlapped(box) ) )
      {
         callback( pObj, key );
      }
   }  
}

//-----------------------------------------------------------------------------

bool SceneContainer::castRay( const Point3F& start, const Point3F& end, U32 mask, RayInfo* info, CastRayCallback callback )
{
   AssertFatal( info->userData == NULL, "SceneContainer::castRay - RayInfo->userData cannot be used here!" );

   PROFILE_START( SceneContainer_CastRay );
   bool result = _castRay( CollisionGeometry, start, end, mask, info, callback );
   PROFILE_END();
   return result;
}

//-----------------------------------------------------------------------------

bool SceneContainer::castRayRendered( const Point3F& start, const Point3F& end, U32 mask, RayInfo* info, CastRayCallback callback )
{
   AssertFatal( info->userData == NULL, "SceneContainer::castRayRendered - RayInfo->userData cannot be used here!" );

   PROFILE_START( SceneContainer_CastRayRendered );
   bool result = _castRay( RenderedGeometry, start, end, mask, info, callback );
   PROFILE_END();
   return result;
}

//-----------------------------------------------------------------------------

// DMMNOTE: There are still some optimizations to be done here.  In particular:
//           - After checking the overflow bin, we can potentially shorten the line
//             that we rasterize against the grid if there is a collision with say,
//             the terrain.
//           - The optimal grid size isn't necessarily what we have set here. possibly
//             a resolution of 16 meters would give better results
//           - The line rasterizer is pretty lame.  Unfortunately we can't use a
//             simple bres. here, since we need to check every grid element that the line
//             passes through, which bres does _not_ do for us.  Possibly there's a
//             rasterizer for anti-aliased lines that will serve better than what
//             we have below.

bool SceneContainer::_castRay( U32 type, const Point3F& start, const Point3F& end, U32 mask, RayInfo* info, CastRayCallback callbackFunc )
{
   AssertFatal( !mSearchInProgress, "SceneContainer::_castRay - Container queries are not re-entrant" );
   bool foundCandidate = false;
   mSearchInProgress = true;

   mCurrSeqKey++;

   SceneRayHelper::CheckObjectRayDelegate<CastRayCallback> del(callbackFunc);
   SceneRayHelper::State rayQuery;

   bool simpleCase = rayQuery.setup(start, end);
   SceneRayHelper::QueryParams rayParams;
   rayParams.start = &start;
   rayParams.end = &end;
   rayParams.mask = mask;
   rayParams.seqKey = mCurrSeqKey;
   rayParams.type = (SceneContainer::CastRayType)type;

   // First check overflow
   foundCandidate = SceneRayHelper::castInBinIdx(rayParams, rayQuery, mBinArray, SceneContainer::csmOverflowBinIdx, info, del);

   if (simpleCase)
   {
      if (SceneRayHelper::castInBinSimple(rayParams, rayQuery, mBinArray, info, del))
         foundCandidate = true;
   }
   else
   {
      if (SceneRayHelper::castInBins(rayParams, rayQuery, mBinArray, info, del))
         foundCandidate = true;
   }

   mSearchInProgress = false;

   // Bump the normal into worldspace if appropriate.
   if(foundCandidate)
   {
      PlaneF fakePlane;
      fakePlane.x = info->normal.x;
      fakePlane.y = info->normal.y;
      fakePlane.z = info->normal.z;
      fakePlane.d = 0;

      PlaneF result;
      mTransformPlane(info->object->getTransform(), info->object->getScale(), fakePlane, &result);
      info->normal = result;

      return true;
   }
   else
   {
      // Do nothing and exit...
      return false;
   }
}

//-----------------------------------------------------------------------------

// collide with the objects projected object box
bool SceneContainer::collideBox(const Point3F &start, const Point3F &end, U32 mask, RayInfo * info)
{
   AssertFatal( !mSearchInProgress, "SceneContainer::_castRay - Container queries are not re-entrant" );
   AssertFatal( info->userData == NULL, "SceneContainer::collideBox - RayInfo->userData cannot be used here!" );

   bool foundCandidate = false;
   mSearchInProgress = true;

   mCurrSeqKey++;

   struct BoxRayCallbackDelegate
   {
      inline bool checkFunc(SceneRayHelper::QueryParams delParams, SceneObject* ptr, RayInfo* delInfo, F32& currentT) const
      {
         // Ignore disabled collision
         if (!ptr->isCollisionEnabled())
            return false;

         if (ptr->getTypeMask() & delParams.mask)
         {
            Point3F xformedStart, xformedEnd;
            ptr->mWorldToObj.mulP(*delParams.start, &xformedStart);
            ptr->mWorldToObj.mulP(*delParams.end,   &xformedEnd);
            xformedStart.convolveInverse(ptr->mObjScale);
            xformedEnd.convolveInverse(ptr->mObjScale);

            RayInfo ri;
            if(ptr->collideBox(xformedStart, xformedEnd, &ri))
            {
               if(ri.t < currentT)
               {
                  *delInfo = ri;
                  delInfo->point.interpolate(*delParams.start, *delParams.end, delInfo->t);
                  currentT = ri.t;
                  return true;
               }
            }
         }

         return true;
      }
   };

   struct BoxRayOverflowCallbackDelegate
   {
      inline bool checkFunc(SceneRayHelper::QueryParams delParams, SceneObject* ptr, RayInfo* delInfo, F32& currentT) const
      {
         // Ignore global bounds or disabled collision
         if (ptr->isGlobalBounds() || !ptr->isCollisionEnabled())
            return false;

         if (ptr->getTypeMask() & delParams.mask)
         {
            Point3F xformedStart, xformedEnd;
            ptr->mWorldToObj.mulP(*delParams.start, &xformedStart);
            ptr->mWorldToObj.mulP(*delParams.end,   &xformedEnd);
            xformedStart.convolveInverse(ptr->mObjScale);
            xformedEnd.convolveInverse(ptr->mObjScale);

            RayInfo ri;
            if(ptr->collideBox(xformedStart, xformedEnd, &ri))
            {
               if(ri.t < currentT)
               {
                  *delInfo = ri;
                  delInfo->point.interpolate(*delParams.start, *delParams.end, delInfo->t);
                  currentT = ri.t;
                  return true;
               }
            }
         }

         return false;
      }
   };

   SceneRayHelper::State rayQuery;
   bool simpleCase = rayQuery.setup(start, end);
   SceneRayHelper::QueryParams rayParams;
   rayParams.start = &start;
   rayParams.end = &end;
   rayParams.mask = mask;
   rayParams.seqKey = mCurrSeqKey;
   rayParams.type = CollisionGeometry;

   // First check overflow
   foundCandidate = SceneRayHelper::castInBinIdx(rayParams, rayQuery, mBinArray, SceneContainer::csmOverflowBinIdx, info, BoxRayOverflowCallbackDelegate());

   if (simpleCase)
   {
      if (SceneRayHelper::castInBinSimple(rayParams, rayQuery, mBinArray, info, BoxRayCallbackDelegate()))
         foundCandidate = true;
   }
   else
   {
      if (SceneRayHelper::castInBins(rayParams, rayQuery, mBinArray, info, BoxRayCallbackDelegate()))
         foundCandidate = true;
   }

   mSearchInProgress = false;
   return foundCandidate;
}

//-----------------------------------------------------------------------------

static void buildCallback(SceneObject* object,void *key)
{
   SceneContainer::CallbackInfo* info = reinterpret_cast<SceneContainer::CallbackInfo*>(key);
   object->buildPolyList(info->context,info->polyList,info->boundingBox,info->boundingSphere);
}

bool SceneContainer::buildPolyList(PolyListContext context, const Box3F &box, U32 mask, AbstractPolyList *polyList)
{
   CallbackInfo info;
   info.context = context;
   info.boundingBox = box;
   info.polyList = polyList;

   // Build bounding sphere
   info.boundingSphere.center = (info.boundingBox.minExtents + info.boundingBox.maxExtents) * 0.5;
   VectorF bv = box.maxExtents - info.boundingSphere.center;
   info.boundingSphere.radius = bv.len();

   sPolyList = polyList;
   findObjects(box,mask,buildCallback,&info);
   return !polyList->isEmpty();
}

//-----------------------------------------------------------------------------

void SceneContainer::cleanupSearchVectors()
{
   for (U32 i = 0; i < mSearchList.size(); i++)
      delete mSearchList[i];
   mSearchList.clear();
   mCurrSearchPos = -1;
}

//-----------------------------------------------------------------------------

static Point3F sgSortReferencePoint;
static S32 QSORT_CALLBACK cmpSearchPointers(const void* inP1, const void* inP2)
{
   SimObjectPtr<SceneObject>** p1 = (SimObjectPtr<SceneObject>**)inP1;
   SimObjectPtr<SceneObject>** p2 = (SimObjectPtr<SceneObject>**)inP2;

   Point3F temp;
   F32 d1, d2;

   if (bool(**p1))
   {
      (**p1)->getWorldBox().getCenter(&temp);
      d1 = (temp - sgSortReferencePoint).len();
   }
   else
   {
      d1 = 0;
   }
   if (bool(**p2))
   {
      (**p2)->getWorldBox().getCenter(&temp);
      d2 = (temp - sgSortReferencePoint).len();
   }
   else
   {
      d2 = 0;
   }

   if (d1 > d2)
      return 1;
   else if (d1 < d2)
      return -1;
   else
      return 0;
}

void SceneContainer::initRadiusSearch(const Point3F& searchPoint,
                                 const F32      searchRadius,
                                 const U32      searchMask)
{
   cleanupSearchVectors();

   mSearchReferencePoint = searchPoint;

   Box3F queryBox(searchPoint, searchPoint);
   queryBox.minExtents -= Point3F(searchRadius, searchRadius, searchRadius);
   queryBox.maxExtents += Point3F(searchRadius, searchRadius, searchRadius);

   SimpleQueryList queryList;
   findObjects(queryBox, searchMask, SimpleQueryList::insertionCallback, &queryList);

   F32 radiusSquared = searchRadius * searchRadius;

   const F32* pPoint = &searchPoint.x;
   for (U32 i = 0; i < queryList.mList.size(); i++)
   {
      const F32* bMins;
      const F32* bMaxs;
      bMins = &queryList.mList[i]->getWorldBox().minExtents.x;
      bMaxs = &queryList.mList[i]->getWorldBox().maxExtents.x;
      F32 sum = 0;
      for (U32 j = 0; j < 3; j++)
      {
         if (pPoint[j] < bMins[j])
            sum += (pPoint[j] - bMins[j])*(pPoint[j] - bMins[j]);
         else if (pPoint[j] > bMaxs[j])
            sum += (pPoint[j] - bMaxs[j])*(pPoint[j] - bMaxs[j]);
      }
      if (sum < radiusSquared || queryList.mList[i]->isGlobalBounds())
      {
         mSearchList.push_back(new SimObjectPtr<SceneObject>);
         *(mSearchList.last()) = queryList.mList[i];
      }
   }
   if (mSearchList.size() != 0)
   {
      sgSortReferencePoint = mSearchReferencePoint;
      dQsort(mSearchList.address(), mSearchList.size(),
             sizeof(SimObjectPtr<SceneObject>*), cmpSearchPointers);
   }
}

//-----------------------------------------------------------------------------

void SceneContainer::initTypeSearch(const U32      searchMask)
{
   cleanupSearchVectors();

   SimpleQueryList queryList;
   findObjects(searchMask, SimpleQueryList::insertionCallback, &queryList);

   for (U32 i = 0; i < queryList.mList.size(); i++)
   {
         mSearchList.push_back(new SimObjectPtr<SceneObject>);
         *(mSearchList.last()) = queryList.mList[i];
   }
   if (mSearchList.size() != 0)
   {
      sgSortReferencePoint = mSearchReferencePoint;
      dQsort(mSearchList.address(), mSearchList.size(),
             sizeof(SimObjectPtr<SceneObject>*), cmpSearchPointers);
   }
}

//-----------------------------------------------------------------------------

SceneObject* SceneContainer::containerSearchNextObject()
{
   if (mCurrSearchPos >= mSearchList.size())
      return NULL;

   mCurrSearchPos++;
   while (mCurrSearchPos < mSearchList.size() && bool(*mSearchList[mCurrSearchPos]) == false)
      mCurrSearchPos++;

   if (mCurrSearchPos == mSearchList.size())
      return NULL;

   return (*mSearchList[mCurrSearchPos]);
}

//-----------------------------------------------------------------------------

U32 SceneContainer::containerSearchNext()
{
   SceneObject* object = containerSearchNextObject();
   if( !object )
      return 0;
   return object->getId();
}

//-----------------------------------------------------------------------------

F32 SceneContainer::containerSearchCurrDist()
{
   AssertFatal(mCurrSearchPos != -1, "Error, must call containerSearchNext before containerSearchCurrDist");

   if (mCurrSearchPos == -1 || mCurrSearchPos >= mSearchList.size() ||
       bool(*mSearchList[mCurrSearchPos]) == false)
      return 0.0;

   Point3F pos;
   (*mSearchList[mCurrSearchPos])->getWorldBox().getCenter(&pos);
   return (pos - mSearchReferencePoint).len();
}

//-----------------------------------------------------------------------------

F32 SceneContainer::containerSearchCurrRadiusDist()
{
   AssertFatal(mCurrSearchPos != -1, "Error, must call containerSearchNext before containerSearchCurrDist");

   if (mCurrSearchPos == -1 || mCurrSearchPos >= mSearchList.size() ||
       bool(*mSearchList[mCurrSearchPos]) == false)
      return 0.0;

   Point3F pos;
   Box3F worldBox = (*mSearchList[mCurrSearchPos])->getWorldBox();
   worldBox.getCenter(&pos);

   F32 dist = (pos - mSearchReferencePoint).len();

   F32 min = worldBox.len_x();
   if (worldBox.len_y() < min)
      min = worldBox.len_y();
   if (worldBox.len_z() < min)
      min = worldBox.len_z();

   dist -= min;
   if (dist < 0)
      dist = 0;

   return dist;
}

//-----------------------------------------------------------------------------

void SceneContainer::getBinRange( const F32 min, const F32 max, U32& minBin, U32& maxBin )
{
   AssertFatal(max >= min, avar("Error, bad range in getBinRange. min: %f, max: %f", min, max));

   if ((max - min) >= (SceneContainer::csmTotalAxisBinSize - SceneContainer::csmBinSize))
   {
      F32 minCoord = mFmod(min, SceneContainer::csmTotalAxisBinSize);
      if (minCoord < 0.0f) 
      {
         minCoord += SceneContainer::csmTotalAxisBinSize;

         // This is truly lame, but it can happen.  There must be a better way to
         //  deal with this.
         if (minCoord == SceneContainer::csmTotalAxisBinSize)
            minCoord = SceneContainer::csmTotalAxisBinSize - 0.01f;
      }

      AssertFatal(minCoord >= 0.0 && minCoord < SceneContainer::csmTotalAxisBinSize, "Bad minCoord");

      minBin = U32(minCoord / SceneContainer::csmBinSize);
      AssertFatal(minBin < SceneContainer::csmNumAxisBins, avar("Error, bad clipping! (%g, %d)", minCoord, minBin));

      maxBin = minBin + (SceneContainer::csmNumAxisBins - 1);
      return;
   }
   else 
   {

      F32 minCoord = mFmod(min, SceneContainer::csmTotalAxisBinSize);
      
      if (minCoord < 0.0f) 
      {
         minCoord += SceneContainer::csmTotalAxisBinSize;

         // This is truly lame, but it can happen.  There must be a better way to
         //  deal with this.
         if (minCoord == SceneContainer::csmTotalAxisBinSize)
            minCoord = SceneContainer::csmTotalAxisBinSize - 0.01f;
      }
      AssertFatal(minCoord >= 0.0 && minCoord < SceneContainer::csmTotalAxisBinSize, "Bad minCoord");

      F32 maxCoord = mFmod(max, SceneContainer::csmTotalAxisBinSize);
      if (maxCoord < 0.0f) {
         maxCoord += SceneContainer::csmTotalAxisBinSize;

         // This is truly lame, but it can happen.  There must be a better way to
         //  deal with this.
         if (maxCoord == SceneContainer::csmTotalAxisBinSize)
            maxCoord = SceneContainer::csmTotalAxisBinSize - 0.01f;
      }
      AssertFatal(maxCoord >= 0.0 && maxCoord < SceneContainer::csmTotalAxisBinSize, "Bad maxCoord");

      minBin = U32(minCoord / SceneContainer::csmBinSize);
      maxBin = U32(maxCoord / SceneContainer::csmBinSize); // NOTE: this should use same logic as minBin to allow for simplification case when coords match
      maxBin = maxBin >= SceneContainer::csmNumAxisBins ? SceneContainer::csmNumAxisBins-1 : maxBin;
      AssertFatal(minBin < SceneContainer::csmNumAxisBins, avar("Error, bad clipping(min)! (%g, %d)", maxCoord, minBin));
      AssertFatal(maxBin < SceneContainer::csmNumAxisBins, avar("Error, bad clipping(max)! (%g, %d)", maxCoord, maxBin));

      // MSVC6 seems to be generating some bad floating point code around
      // here when full optimizations are on.  The min != max test should
      // not be needed, but it clears up the VC issue.
      if (min != max && minCoord > maxCoord)
         maxBin += SceneContainer::csmNumAxisBins;

      AssertFatal(maxBin >= minBin, "Error, min should always be less than max!");
   }
}

//=============================================================================
//    Console API.
//=============================================================================
// MARK: ---- Console API ----

ConsoleFunctionGroupBegin( Containers,  "Functions for ray casting and spatial queries.\n\n");

//-----------------------------------------------------------------------------

DefineEngineFunction( containerBoxEmpty, bool,
   ( U32 mask, Point3F center, F32 xRadius, F32 yRadius, F32 zRadius, bool useClientContainer ), ( -1, -1, false ),
   "@brief See if any objects of the given types are present in box of given extent.\n\n"
   "@note Extent parameter is last since only one radius is often needed.  If "
   "one radius is provided, the yRadius and zRadius are assumed to be the same.  Unfortunately, "
   "if you need to use the client container, you'll need to set all of the radius parameters.  "
   "Fortunately, this function is mostly used on the server.\n"
   "@param  mask   Indicates the type of objects we are checking against.\n"
   "@param  center Center of box.\n"
   "@param  xRadius Search radius in the x-axis. See note above.\n"
   "@param  yRadius Search radius in the y-axis. See note above.\n"
   "@param  zRadius Search radius in the z-axis. See note above.\n"
   "@param useClientContainer Optionally indicates the search should be within the "
   "client container.\n"
   "@return true if the box is empty, false if any object is found.\n"
   "@ingroup Game")
{
   Point3F extent( xRadius, yRadius, zRadius );
   extent.y = extent.y >= 0 ? extent.y : extent.x;
   extent.z = extent.z >= 0 ? extent.z : extent.x;

   Box3F    B(center - extent, center + extent, true);

   EarlyOutPolyList polyList;
   polyList.mPlaneList.clear();
   polyList.mNormal.set(0,0,0);
   polyList.mPlaneList.setSize(6);
   polyList.mPlaneList[0].set(B.minExtents, VectorF(-1,0,0));
   polyList.mPlaneList[1].set(B.maxExtents, VectorF(0,1,0));
   polyList.mPlaneList[2].set(B.maxExtents, VectorF(1,0,0));
   polyList.mPlaneList[3].set(B.minExtents, VectorF(0,-1,0));
   polyList.mPlaneList[4].set(B.minExtents, VectorF(0,0,-1));
   polyList.mPlaneList[5].set(B.maxExtents, VectorF(0,0,1));

   SceneContainer* pContainer = useClientContainer ? &gClientContainer : &gServerContainer;

   return ! pContainer->buildPolyList(PLC_Collision, B, mask, &polyList);
}

//-----------------------------------------------------------------------------

DefineEngineFunction( initContainerRadiusSearch, void, ( Point3F pos, F32 radius, U32 mask, bool useClientContainer ), ( false ),
   "@brief Start a search for items at the given position and within the given radius, filtering by mask.\n\n"

   "@param pos Center position for the search\n"
   "@param radius Search radius\n"
   "@param mask Bitmask of object types to include in the search\n"
   "@param useClientContainer Optionally indicates the search should be within the "
   "client container.\n"

   "@see containerSearchNext\n" 
   "@ingroup Game")
{
   SceneContainer* pContainer = useClientContainer ? &gClientContainer : &gServerContainer;

   pContainer->initRadiusSearch( pos, radius, mask );
}

//-----------------------------------------------------------------------------

DefineEngineFunction( initContainerTypeSearch, void, ( U32 mask, bool useClientContainer ), ( false ),
   "@brief Start a search for all items of the types specified by the bitset mask.\n\n"

   "@param mask Bitmask of object types to include in the search\n"
   "@param useClientContainer Optionally indicates the search should be within the "
   "client container.\n"

   "@see containerSearchNext\n" 
   "@ingroup Game")
{
   SceneContainer* pContainer = useClientContainer ? &gClientContainer : &gServerContainer;

   pContainer->initTypeSearch( mask );
}

//-----------------------------------------------------------------------------

DefineEngineFunction( containerSearchNext, SceneObject*, ( bool useClientContainer ), ( false ),
   "@brief Get next item from a search started with initContainerRadiusSearch() or "
   "initContainerTypeSearch().\n\n"

   "@param useClientContainer Optionally indicates the search should be within the "
   "client container.\n"
   "@return the next object found in the search, or null if no more\n"

   "@tsexample\n"
   "// print the names of all nearby ShapeBase derived objects\n"
   "%position = %obj.getPosition;\n"
   "%radius = 20;\n"
   "%mask = $TypeMasks::ShapeBaseObjectType;\n"
   "initContainerRadiusSearch( %position, %radius, %mask );\n"
   "while ( (%targetObject = containerSearchNext()) != 0 )\n"
   "{\n"
   "   echo( \"Found: \" @ %targetObject.getName() );\n"
   "}\n"
   "@endtsexample\n"

   "@see initContainerRadiusSearch()\n"
   "@see initContainerTypeSearch()\n"
   "@ingroup Game")
{
   SceneContainer* pContainer = useClientContainer ? &gClientContainer : &gServerContainer;

   return pContainer->containerSearchNextObject();
}

//-----------------------------------------------------------------------------

DefineEngineFunction( containerSearchCurrDist, F32, ( bool useClientContainer ), ( false ),
   "@brief Get distance of the center of the current item from the center of the "
   "current initContainerRadiusSearch.\n\n"

   "@param useClientContainer Optionally indicates the search should be within the "
   "client container.\n"
   "@return distance from the center of the current object to the center of "
   "the search\n"

   "@see containerSearchNext\n"
   "@ingroup Game")
{
   SceneContainer* pContainer = useClientContainer ? &gClientContainer : &gServerContainer;

   return pContainer->containerSearchCurrDist();
}

//-----------------------------------------------------------------------------

DefineEngineFunction( containerSearchCurrRadiusDist, F32, ( bool useClientContainer ), ( false ),
   "@brief Get the distance of the closest point of the current item from the center "
   "of the current initContainerRadiusSearch.\n\n"

   "@param useClientContainer Optionally indicates the search should be within the "
   "client container.\n"
   "@return distance from the closest point of the current object to the "
   "center of the search\n"

   "@see containerSearchNext\n" 
   "@ingroup Game")
{
   SceneContainer* pContainer = useClientContainer ? &gClientContainer : &gServerContainer;

   return pContainer->containerSearchCurrRadiusDist();
}

//-----------------------------------------------------------------------------

//TODO: make RayInfo an API type
DefineEngineFunction( containerRayCast, const char*,
   ( Point3F start, Point3F end, U32 mask, SceneObject *pExempt, bool useClientContainer ), ( nullAsType<SceneObject*>(), false ),
   "@brief Cast a ray from start to end, checking for collision against items matching mask.\n\n"

   "If pExempt is specified, then it is temporarily excluded from collision checks (For "
   "instance, you might want to exclude the player if said player was firing a weapon.)\n"

   "@param start An XYZ vector containing the tail position of the ray.\n"
   "@param end An XYZ vector containing the head position of the ray\n"
   "@param mask A bitmask corresponding to the type of objects to check for\n"
   "@param pExempt An optional ID for a single object that ignored for this raycast\n"
   "@param useClientContainer Optionally indicates the search should be within the "
   "client container.\n"

   "@returns A string containing either null, if nothing was struck, or these fields:\n"
   "<ul><li>The ID of the object that was struck.</li>"
   "<li>The x, y, z position that it was struck.</li>"
   "<li>The x, y, z of the normal of the face that was struck.</li>"
   "<li>The distance between the start point and the position we hit.</li></ul>" 

   "@ingroup Game")
{
   if (pExempt)
      pExempt->disableCollision();

   SceneContainer* pContainer = useClientContainer ? &gClientContainer : &gServerContainer;

   RayInfo rinfo;
   S32 ret = 0;
   if (pContainer->castRay(start, end, mask, &rinfo) == true)
      ret = rinfo.object->getId();

   if (pExempt)
      pExempt->enableCollision();

   // add the hit position and normal?
   static const U32 bufSize = 256;
   char *returnBuffer = Con::getReturnBuffer(bufSize);
   if(ret)
   {
      dSprintf(returnBuffer, bufSize, "%d %g %g %g %g %g %g %g",
               ret, rinfo.point.x, rinfo.point.y, rinfo.point.z,
               rinfo.normal.x, rinfo.normal.y, rinfo.normal.z, rinfo.distance);
   }
   else
   {
      returnBuffer[0] = '0';
      returnBuffer[1] = '\0';
   }

   return(returnBuffer);
}

DefineEngineFunction(materialRayCast, const char*,
(Point3F start, Point3F end, U32 mask, SceneObject* pExempt, bool useClientContainer), (nullAsType<SceneObject*>(), false),
"@brief Cast a ray from start to end, checking for collision against items matching mask.\n\n"

"If pExempt is specified, then it is temporarily excluded from collision checks (For "
"instance, you might want to exclude the player if said player was firing a weapon.)\n"

"@param start An XYZ vector containing the tail position of the ray.\n"
"@param end An XYZ vector containing the head position of the ray\n"
"@param mask A bitmask corresponding to the type of objects to check for\n"
"@param pExempt An optional ID for a single object that ignored for this raycast\n"
"@param useClientContainer Optionally indicates the search should be within the "
"client container.\n"

"@returns A string containing either null, if nothing was struck, or these fields:\n"
"<ul><li>The ID of the object that was struck.</li>"
"<li>The x, y, z position that it was struck.</li>"
"<li>The x, y, z of the normal of the face that was struck.</li>"
"<li>The distance between the start point and the position we hit.</li></ul>"

"@ingroup Game")
{
   if (pExempt)
      pExempt->disableCollision();

   SceneContainer* pContainer = useClientContainer ? &gClientContainer : &gServerContainer;

   RayInfo rinfo;
   S32 ret = 0;
   if (pContainer->castRayRendered(start, end, mask, &rinfo) == true)
      ret = rinfo.object->getId();

   if (pExempt)
      pExempt->enableCollision();

   // add the hit position and normal?
   static const U32 bufSize = 512;
   char* returnBuffer = Con::getReturnBuffer(bufSize);
   if (ret)
   {
      dSprintf(returnBuffer, bufSize, "%d %g %g %g %g %g %g %g %g %g %s",
         ret, rinfo.point.x, rinfo.point.y, rinfo.point.z,
         rinfo.normal.x, rinfo.normal.y, rinfo.normal.z, rinfo.distance, rinfo.texCoord.x, rinfo.texCoord.y, rinfo.material ? rinfo.material->getMaterial()->getName() : "");
   }
   else
   {
      returnBuffer[0] = '0';
      returnBuffer[1] = '\0';
   }

   return(returnBuffer);
}

ConsoleFunctionGroupEnd( Containers );
