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

//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~~//
// Arcane-FX for MIT Licensed Open Source version of Torque 3D from GarageGames
// Copyright (C) 2015 Faust Logic, Inc.
//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~~//

#ifndef _SCENECONTAINER_H_
#define _SCENECONTAINER_H_

#ifndef _MBOX_H_
#include "math/mBox.h"
#endif

#ifndef _MSPHERE_H_
#include "math/mSphere.h"
#endif

#ifndef _TVECTOR_H_
#include "core/util/tVector.h"
#endif

#ifndef _MPOLYHEDRON_H_
#include "math/mPolyhedron.h"
#endif

#ifndef _SIMOBJECT_H_
#include "console/simObject.h"
#endif

#ifndef _SCENEOBJECT_H_
#include "scene/sceneObject.h"
#endif


/// @file
/// SceneObject database.


class SceneObject;
class AbstractPolyList;
class OptimizedPolyList;
class Frustum;
class Point3F;

struct RayInfo;

inline U32 dCalcBlocks(U32 value, U32 blockSize)
{
   U32 curBlock = value / blockSize;
   U32 nextBlock = curBlock + 1;
   return nextBlock * blockSize;
}

/// Allocates a list of T in blocks of mBlockSize, doesn't shrink unless forced
template<typename T> class LazyItemAllocator
{
protected:
   T* mItems;
   U32 mSize;
   U32 mBlockSize;

public:
   LazyItemAllocator(U32 blockSize) : mItems(NULL), mSize(0), mBlockSize(blockSize)
   {
   }

   ~LazyItemAllocator()
   {
      if (mItems)
         dFree(mItems);
   }

   inline bool isNull() const
   {
      return mItems == NULL;
   }

   inline T* getPtr() const
   {
      return mItems;
   }

   inline bool canFit(U32 count) const
   {
      return count <= mSize;
   }

   inline U32 getCapacity() const
   {
      return mSize;
   }

   void realloc(U32 requiredItems, bool force)
   {
      U32 requiredSize = dCalcBlocks(requiredItems, mBlockSize);
      if (mSize < requiredSize || (force && (mSize != requiredSize)))
      {
         if (mItems == NULL)
            mItems = (T*)dMalloc(sizeof(T) * requiredSize);
         else
            mItems = (T*)dRealloc(mItems, sizeof(T) * requiredSize);

         mSize = requiredSize;
      }
   }
};

/// Maintains a set of bin lists for SceneObjects
/// Use allocList to allocate a list. freeList frees the list, 
/// and reallocList handles reallocating an existing list handle.
template<typename T> class SceneContainerBinRefList
{
public:

   /// Index type for a bin reference
   typedef T BinValue;

   /// Type for number of bins used by a reference list
   typedef T BinCount;

   /// Handle used for bin lists
   typedef U32 ListHandle;

   // Defaults
   enum
   {
      /// Chunk size of reference lists
      ReserveSize = 20000,
      
      /// Chunk count of reference list entries
      DataReserveSize = 20000*4,

      /// Number of unused references when compaction should occur
      CompactionThreshold = 4096
   };

   struct ValueIterator
   {
      T* binList;
      BinCount numElements;
      BinCount currentElement;

      ValueIterator() : binList(NULL), numElements(0), currentElement(0) { ; }
      ValueIterator(T* list, U32 count, U32 idx=0) : binList(list), numElements(count), currentElement(idx)
      {
      }

      T& operator* () const
      {
         return binList[currentElement];
      }

      inline bool isValid() const
      {
         return currentElement < numElements && binList != NULL;
      }

      inline T* getPtr() const
      {
         return &binList[currentElement];
      }

      inline BinCount getIndex() const
      {
         return currentElement;
      }

      inline BinCount getCount() const
      {
         return numElements;
      }

      ValueIterator& operator++()
      {
         if (currentElement < numElements)
            currentElement++;
         return *this;
      }

      ValueIterator& operator++(int other)
      {
         currentElement++;
         currentElement = mMin(currentElement, numElements);
         return *this;
      }

      inline ValueIterator& operator+(const U32 other)
      {
         currentElement += other;
         currentElement = mMin(currentElement, numElements);
         return *this;
      }

      inline ValueIterator& operator=(const ValueIterator& other)
      {
         binList = other.binList;
         numElements = other.numElements;
         currentElement = other.currentElement;
         return *this;
      }

      inline bool operator==(const ValueIterator& other) const
      {
         return binList == other.binList && currentElement == other.currentElement;
      }

      inline bool operator!=(const ValueIterator& other) const
      {
         return !(binList == other.binList && currentElement == other.currentElement);
      }
   };

public:

#pragma pack(2)
   struct BinList
   {
      // Start reference
      U32 startValue;

      /// References allocated
      BinCount numValues;
   };
#pragma pack()

protected:

   /// List of bin lists
   Vector<BinList> mBinLists;

   /// Current bin values
   LazyItemAllocator<BinValue> mBinValues;

   /// Temporary compaction list
   LazyItemAllocator<BinValue> mCompactData;

   /// Offset (+1) of first free mBinLists
   U32 mFreeListStart;

   /// Chunks of mRefList to allocate
   U32 mListChunkSize;

   /// Current used ref count (in mBinValues)
   U32 mUsedValues;

   /// Current reference index we are writing
   U32 mLastValueIdx;

public:

   SceneContainerBinRefList() :
      mBinValues(DataReserveSize),
      mCompactData(DataReserveSize),
      mFreeListStart(0),
      mListChunkSize(ReserveSize),
      mUsedValues(0),
      mLastValueIdx(0)
   {
   }

   ~SceneContainerBinRefList()
   {
   }

   /// Resets the SceneContainerBinRefList
   void clear()
   {
      mBinLists.clear();
      mBinValues.realloc(0, true);
      mCompactData.realloc(0, true);

      mFreeListStart = 0;
      mUsedValues = 0;
      mLastValueIdx = 0;
   }

   /// Gets a BinValue list based on a ListHandle.
   BinValue* getValues(ListHandle handle, U32& numValues)
   {
      if (handle == 0 ||
         handle > mBinLists.size())
      {
         numValues = 0;
         return NULL;
      }

      U32 realIDX = handle - 1;
      BinList& list = mBinLists[realIDX];
      numValues = list.numValues;

      return mBinValues.getPtr() + list.startValue;
   }

   void getValueIterators(ListHandle handle, ValueIterator& start, ValueIterator& end)
   {
      if (handle == 0 ||
         handle > mBinLists.size())
      {
         start = ValueIterator(NULL, 0);
         end = ValueIterator(NULL, 0);
         return;
      }

      U32 realIDX = handle - 1;
      BinList& list = mBinLists[realIDX];

      start = ValueIterator(mBinValues.getPtr() + list.startValue, list.numValues, 0);
      end = ValueIterator(mBinValues.getPtr() + list.startValue, list.numValues, list.numValues);
   }

   ValueIterator getValueIterator(ListHandle handle)
   {
      if (handle == 0 ||
         handle > mBinLists.size())
      {
         return ValueIterator(NULL, 0);
      }

      U32 realIDX = handle - 1;
      BinList& list = mBinLists[realIDX];

      return ValueIterator(mBinValues.getPtr() + list.startValue, list.numValues);
   }

   inline U32 getNextFreeListIndex() const
   {
      return mFreeListStart;
   }

   inline const Vector<BinList>& getBinLists() const
   {
      return mBinLists;
   }

   inline const BinValue* getBin() const
   {
      return mBinValues.getPtr();
   }

   inline const U32 getBinCapacity() const
   {
      return mBinValues.getCapacity();
   }

protected:

   /// Gets a free entry from the free entry list.
   bool getFreeEntry(ListHandle& outIDX)
   {
      if (mFreeListStart > 0)
      {
         outIDX = mFreeListStart - 1;
         mFreeListStart = mBinLists[outIDX].startValue;
         return true;
      }

      return false;
   }

public:

   /// Allocates a new ListHandle with numValue values copied from values.
   ListHandle allocList(BinCount numValues, BinValue* values)
   {
      BinList list;
      ListHandle retHandle = 0;

      list.numValues = numValues;
      list.startValue = mLastValueIdx;

      mLastValueIdx += numValues;
      mUsedValues += numValues;

      // Use free list or push new entry
      if (!getFreeEntry(retHandle))
      {
         mBinLists.push_back(list);
         retHandle = mBinLists.size();
      }
      else
      {
         mBinLists[retHandle++] = list;
      }

      // Manage lists
      mBinLists.reserve(dCalcBlocks(mBinLists.size(), mListChunkSize));
      mBinValues.realloc(mLastValueIdx, false);

      // Copy data
      dCopyArray(mBinValues.getPtr() + list.startValue, values, numValues);
      return retHandle;
   }

   /// Reallocates an existing ListHandle.
   /// Existing memory will be used if numValues is the same, 
   /// otherwise new list memory will be allocated.
   void reallocList(ListHandle handle, BinCount numValues, BinValue* values)
   {
      if (handle == 0 ||
         handle > mBinLists.size())
         return;

      U32 realIDX = handle - 1;
      BinList& list = mBinLists[realIDX];

      if (list.numValues != numValues)
      {
         // Allocate new entry
         mUsedValues -= list.numValues;
         mUsedValues += numValues;

         list.numValues = numValues;
         list.startValue = mLastValueIdx;

         mLastValueIdx += numValues;
         mBinValues.realloc(mLastValueIdx, false);
      }

      dCopyArray(mBinValues.getPtr() + list.startValue, values, numValues);
   }

   /// Frees an existing ListHandle
   void freeList(ListHandle handle)
   {
      if (handle == 0 ||
         handle > mBinLists.size())
         return;

      U32 realIDX = handle - 1;
      BinList& list = mBinLists[realIDX];

      mUsedValues -= list.numValues;
      list.numValues = 0;

      // Add to free list
      list.startValue = mFreeListStart;
      // Next
      mFreeListStart = handle;

      AssertFatal(mLastValueIdx >= mUsedValues, "ref overflow");

      // Automatically compact if we have enough free items
      if ((mLastValueIdx - mUsedValues) > CompactionThreshold)
      {
         compact();
      }
   }

   void replaceListBin(ListHandle handle, BinValue oldValue, BinValue newValue)
   {
      if (handle == 0 ||
         handle > mBinLists.size())
         return;

      U32 realIDX = handle - 1;
      BinList& list = mBinLists[realIDX];

      BinValue* values = mBinValues.getPtr() + list.startValue;
      for (U32 i = 0; i < list.numValues; i++)
      {
         if (values[i] == oldValue)
         {
            values[i] = newValue;
            break;
         }
      }
   }

   bool containsBinItem(ListHandle handle, BinValue value) const
   {
      if (handle == 0 ||
         handle > mBinLists.size())
         return false;

      U32 realIDX = handle - 1;
      const BinList& list = mBinLists[realIDX];

      const BinValue* values = mBinValues.getPtr() + list.startValue;
      for (U32 i = 0; i < list.numValues; i++)
      {
         if (values[i] == value)
            return true;
      }

      return false;
   }

   /// Compacts the BinValue lists. 
   /// This will automatically be called by freeList usually
   /// once CompactionThreshold list values have been freed.
   void compact()
   {
      if (mBinValues.isNull())
         return;

      mCompactData.realloc(mUsedValues, false);
      BinValue* outPtr = mCompactData.getPtr();
      U32 newOutStart = 0;

      // Copy list values to scratch list
      for (BinList& list : mBinLists)
      {
         if (list.numValues == 0)
            continue;

         const BinValue* inPtr = mBinValues.getPtr() + list.startValue;
         dCopyArray(outPtr, inPtr, list.numValues);

         // Update counters
         list.startValue = newOutStart;
         outPtr += list.numValues;
         newOutStart += list.numValues;
      }

      AssertFatal(newOutStart == mUsedValues, "value count mismatch");

      mLastValueIdx = mUsedValues;
      mBinValues.realloc(mLastValueIdx, true);

      const U32 copySize = newOutStart * sizeof(BinValue);
      memcpy(mBinValues.getPtr(), mCompactData.getPtr(), copySize);
   }
};

//----------------------------------------------------------------------------

/// Database for SceneObjects.
///
/// ScenceContainer implements a grid-based spatial subdivision for the contents of a scene.
class SceneContainer
{
   public:
      enum CastRayType
      {
         CollisionGeometry,
         RenderedGeometry,
      };

   public:

      typedef SceneContainerBinRefList<U16> BinValueList;

      /// Base object list type, should conform to Vector
      typedef Vector<SceneObject*> ObjectList;

      /// Type to reference a bin list
      typedef U32 BinListIndex;

      /// Type to reference a bin. This should be changed if there are more than 65536 bins.
      typedef U16 BinRef;

      struct CallbackInfo 
      {
         PolyListContext context;
         AbstractPolyList* polyList;
         Box3F boundingBox;
         SphereF boundingSphere;
         void *key;
      };

   private:

      /// Container queries based on #mCurrSeqKey are are not re-entrant;
      /// this is used to detect when it happens.
      bool mSearchInProgress;

      /// Current sequence key.
      U32 mCurrSeqKey;

      /// Binned object lists
      ObjectList* mBinArray;

      /// Large objects
      ObjectList mOverflowBin;

      /// Every single object not categorized by bin
      ObjectList mGlobalList;

      /// A vector that contains just the water and physical zone
      /// object types which is used to optimize searches.
      ObjectList mWaterAndZones;

      /// Vector that contains just the terrain objects in the container.
      ObjectList mTerrains;

      /// Temporary list for value insert
      Vector<BinValueList::BinValue> mBinValueList;

      /// Maintains a list of bin references
      BinValueList mBinRefLists;

   public:
      /// World units of side of bin
      static const F32 csmBinSize;
      /// World units of entire side of bin grid
      static const F32 csmTotalAxisBinSize;

      /// Size of grid on any axis
      static const U32 csmNumAxisBins;
      /// Index used to store overflow entries
      static const U32 csmOverflowBinIdx;
      /// Total number of bin lists to allocate
      static const U32 csmTotalNumBins;

   public:

      SceneContainer();
      ~SceneContainer();

      /// Return a vector containing all the water and physical zone objects in this container.
      const Vector< SceneObject* >& getWaterAndPhysicalZones() const { return mWaterAndZones; }

      /// Return a vector containing all terrain objects in this container.
      const Vector< SceneObject* >& getTerrains() const { return mTerrains; }

      /// @name Basic database operations
      /// @{

      ///
      typedef void ( *FindCallback )( SceneObject* object, void* key );

      /// Find all objects of the given type(s) and invoke the given callback for each
      /// of them.
      /// @param mask Object type mask (@see SimObjectTypes).
      /// @param callback Pointer to function to invoke for each object.
      /// @param key User data to pass to the "key" argument of @a callback.
      void findObjects( U32 mask, FindCallback callback, void* key = NULL );

      void findObjects( const Box3F& box, U32 mask, FindCallback, void *key = NULL );
      void findObjects( const Frustum& frustum, U32 mask, FindCallback, void *key = NULL );

      void polyhedronFindObjects( const Polyhedron& polyhedron, U32 mask, FindCallback, void *key = NULL );

      /// Find all objects of the given type(s) and add them to the given vector.
      /// @param mask Object type mask (@see SimObjectTypes).
      /// @param outFound Vector to add found objects to.
      void findObjectList( U32 mask, Vector< SceneObject* >* outFound );

      ///
      void findObjectList( const Box3F& box, U32 mask, Vector< SceneObject* >* outFound );

      ///
      void findObjectList( const Frustum& frustum, U32 mask, Vector< SceneObject* >* outFound );

      /// @}

      /// @name Line intersection
      /// @{

      typedef bool ( *CastRayCallback )( RayInfo* ri );

      /// Test against collision geometry -- fast.
      bool castRay( const Point3F &start, const Point3F &end, U32 mask, RayInfo* info, CastRayCallback callback = NULL );

      /// Test against rendered geometry -- slow.
      bool castRayRendered( const Point3F &start, const Point3F &end, U32 mask, RayInfo* info, CastRayCallback callback = NULL );

      bool collideBox(const Point3F &start, const Point3F &end, U32 mask, RayInfo* info);

      /// @}

      /// @name Poly list
      /// @{

      ///
      bool buildPolyList(  PolyListContext context, 
                           const Box3F &box, 
                           U32 typeMask, 
                           AbstractPolyList *polylist );

      /// @}

      /// Add an object to the database.
      /// @param object A SceneObject.
      bool addObject( SceneObject* object );

      /// Remove an object from the database.
      /// @param object A SceneObject.
      bool removeObject( SceneObject* object );

      void insertIntoBins( SceneObject* object );
      void removeFromBins( SceneObject* object );

      /// Make sure that we're not just sticking the object right back
      /// where it came from.  The overloaded insertInto is so we don't calculate
      /// the ranges twice.
      void checkBins( SceneObject* object );
      void insertIntoBins(SceneObject*, const SceneBinRange& range);

      void initRadiusSearch(const Point3F& searchPoint,
         const F32      searchRadius,
         const U32      searchMask);
      void initTypeSearch(const U32      searchMask);
      SceneObject* containerSearchNextObject();
      U32  containerSearchNext();
      F32  containerSearchCurrDist();
      F32  containerSearchCurrRadiusDist();

   private:

      Vector<SimObjectPtr<SceneObject>*>  mSearchList;///< Object searches to support console querying of the database.  ONLY WORKS ON SERVER
      S32                                 mCurrSearchPos;
      Point3F                             mSearchReferencePoint;

      void cleanupSearchVectors();

      /// Base cast ray code
      bool _castRay( U32 type, const Point3F &start, const Point3F &end, U32 mask, RayInfo* info, CastRayCallback callback );

      void _findSpecialObjects( const Vector< SceneObject* >& vector, U32 mask, FindCallback, void *key = NULL );
      void _findSpecialObjects( const Vector< SceneObject* >& vector, const Box3F &box, U32 mask, FindCallback callback, void *key = NULL );   


public:

      static inline void getBinRange( const Point2F minExtents, const Point2F maxExtents, SceneBinRange& outRange )
      {
         U32 outMin, outMax;
         getBinRange(minExtents.x, maxExtents.x, outMin, outMax);
         outRange.minCoord[0] = outMin;
         outRange.maxCoord[0] = outMax;
         getBinRange(minExtents.y, maxExtents.y, outMin, outMax);
         outRange.minCoord[1] = outMin;
         outRange.maxCoord[1] = outMax;
      }

      inline void dumpBin(U32 x, U32 y, Vector<SceneObject*> &list)
      {
         U32 insertX = x % csmNumAxisBins;
         U32 insertY = y * csmNumAxisBins;
         U32 binIDX = insertY + insertX;

         list.clear();
         if (binIDX < csmTotalNumBins)
         {
            for (SceneObject* obj : mBinArray[binIDX])
            {
               list.push_back(obj);
            }
         }
      }

      static void getBinRange( const F32 min, const F32 max, U32& minBin, U32& maxBin );
public:
      Vector<SimObjectPtr<SceneObject>*>& getRadiusSearchList() { return mSearchList; }

};

//-----------------------------------------------------------------------------

inline bool SceneBinRange::shouldOverflow() const
{
   return
      ((getWidth() + 1) >= SceneContainer::csmNumAxisBins ||
         ((getHeight() + 1) >= SceneContainer::csmNumAxisBins));
}

//-----------------------------------------------------------------------------

extern SceneContainer gServerContainer;
extern SceneContainer gClientContainer;

#endif // !_SCENECONTAINER_H_
