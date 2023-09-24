#include "testing/unitTesting.h"

#include "platform/platform.h"
#include "console/simBase.h"
#include "console/consoleTypes.h"
#include "console/scriptObjects.h"
#include "console/simBase.h"
#include "console/engineAPI.h"
#include "math/mMath.h"
#include "console/stringStack.h"
#include "scene/sceneContainer.h"
#include "T3D/missionMarker.h"
#include "collision/clippedPolyList.h"


using ::testing::Matcher;
using ::testing::TypedEq;

class LazyItemAllocatorTest : public ::testing::Test
{
protected:
   LazyItemAllocatorTest()
   {
   }

   void SetUp() override
   {
      
   }
   
   
};

TEST_F(LazyItemAllocatorTest, realloc)
{
   LazyItemAllocator<U32> testAllocator(1024);

   EXPECT_EQ(testAllocator.isNull(), true);
   EXPECT_EQ(testAllocator.getPtr(), (U32*)NULL);
   EXPECT_EQ(testAllocator.canFit(1), false);

   // Should alloc memory
   testAllocator.realloc(1, false);
   void* oldPtr = testAllocator.getPtr();

   EXPECT_EQ(testAllocator.isNull(), false);
   EXPECT_NE(testAllocator.getPtr(), (U32*)NULL);
   EXPECT_EQ(testAllocator.canFit(1), true);
   EXPECT_EQ(testAllocator.canFit(2), true);
   EXPECT_EQ(testAllocator.canFit(1024), true);
   EXPECT_EQ(testAllocator.canFit(1025), false);

   // Should be the same
   testAllocator.realloc(2, false);
   EXPECT_EQ(testAllocator.canFit(3), true);
   EXPECT_EQ(testAllocator.getPtr(), oldPtr);

   // Alloc more and then return to normal
   testAllocator.realloc(1025, false);
   EXPECT_EQ(testAllocator.canFit(1025), true);
   testAllocator.realloc(1022, true);
   EXPECT_EQ(testAllocator.canFit(1025), false);
}


class SceneContainerBinRefListTest : public ::testing::Test
{
protected:
   SceneContainerBinRefListTest()
   {
   }

   void SetUp() override
   {

   }


};

TEST_F(SceneContainerBinRefListTest, getValues)
{
   SceneContainerBinRefList<U32> testList;

   srand(11891830);

   // Add some items
   U32 valueList[10];
   U32 valueList2[10];
   for (U32 i = 0; i < 10; i++)
   {
      valueList[i] = rand() % 1024;
      valueList2[i] = rand() % 1024;
   }
   
   auto listHandle1 = testList.allocList(10, valueList);
   auto listHandle2 = testList.allocList(5, valueList2);

   // Grab some items
   U32 numValues1 = 0;
   U32 numValues2 = 0;
   auto newValueList1 = testList.getValues(listHandle1, numValues1);
   auto newValueList2 = testList.getValues(listHandle2, numValues2);

   // Should be sequential
   EXPECT_GT(newValueList2, newValueList1);

   EXPECT_EQ(numValues1, 10);
   EXPECT_EQ(numValues2, 5);

   bool allOk = true;
   for (U32 i = 0; i < 10; i++)
   {
      if (valueList[i] != newValueList1[i])
         allOk = false;
   }
   for (U32 i = 0; i < 5; i++)
   {
      if (valueList2[i] != newValueList2[i])
         allOk = false;
   }
   EXPECT_EQ(allOk, true);

   // Free item, no longer valid
   testList.freeList(listHandle1);
   auto newValueList3 = testList.getValues(listHandle1, numValues1);

   // NOTE: this is not NULL since item gets put in a free list
   EXPECT_NE(newValueList3, (U32*)NULL);
   EXPECT_EQ(numValues1, 0);

   // Grab some more items (they should appear AFTER the last alloc)
   U32 numValues4 = 0;
   auto listHandle4 = testList.allocList(1, valueList2);
   auto newValueList4 = testList.getValues(listHandle4, numValues4);

   EXPECT_EQ(numValues4, 1);
   EXPECT_GT(newValueList4, newValueList2);
}

TEST_F(SceneContainerBinRefListTest, getValueIterators)
{
   SceneContainerBinRefList<U32> testList;

   srand(1111830);

   // Add some items
   U32 valueList[10];
   U32 valueList2[10];
   for (U32 i = 0; i < 10; i++)
   {
      valueList[i] = rand() % 1024;
      valueList2[i] = rand() % 1024;
   }

   auto listHandle1 = testList.allocList(10, valueList);
   auto listHandle2 = testList.allocList(5, valueList2);

   // Grab some items
   SceneContainerBinRefList<U32>::ValueIterator start1;
   SceneContainerBinRefList<U32>::ValueIterator end1;
   SceneContainerBinRefList<U32>::ValueIterator start2;
   SceneContainerBinRefList<U32>::ValueIterator end2;
   testList.getValueIterators(listHandle1, start1, end1);
   testList.getValueIterators(listHandle2, start2, end2);

   EXPECT_EQ((end1.getPtr() - start1.getPtr()), 10);
   EXPECT_EQ((end2.getPtr() - start2.getPtr()), 5);
   EXPECT_GT(start2.getPtr(), start1.getPtr());

   // We can update the value
   start1++;
   *start1 = 2040;
   EXPECT_EQ(*(start1.getPtr()), 2040);
   EXPECT_EQ((end1.getPtr() - 10)[1], 2040);

   // Iterators are NULL for an OOB item
   testList.getValueIterators(100, start1, end1);
   EXPECT_EQ((start1.getPtr()), (U32*)NULL);
   EXPECT_EQ((end1.getPtr()), (U32*)NULL);
   EXPECT_EQ((end1.isValid()), false);
}


TEST_F(SceneContainerBinRefListTest, getValueIterator)
{
   SceneContainerBinRefList<U32> testList;

   srand(1111830);

   // Add some items
   U32 valueList[10];
   U32 valueList2[10];
   for (U32 i = 0; i < 10; i++)
   {
      valueList[i] = rand() % 1024;
      valueList2[i] = rand() % 1024;
   }

   testList.allocList(2, valueList);
   auto listHandle2 = testList.allocList(3, valueList2);

   auto handleItr = testList.getValueIterator(listHandle2);
   EXPECT_NE((handleItr.getPtr()), (U32*)NULL);
   EXPECT_EQ((handleItr.isValid()), true);
   EXPECT_EQ((*handleItr), valueList2[0]);

   EXPECT_EQ((handleItr.getCount()), 3);
   handleItr++;
   EXPECT_EQ((handleItr.getIndex()), 1);
   EXPECT_EQ((*handleItr), valueList2[1]);
   handleItr++;
   EXPECT_EQ((*handleItr), valueList2[2]);
   handleItr++;
   EXPECT_EQ((handleItr.isValid()), false);

   // Iterators are NULL for an OOB item
   auto oobItr = testList.getValueIterator(100);
   EXPECT_EQ((oobItr.getPtr()), (U32*)NULL);
   EXPECT_EQ((oobItr.isValid()), false);
}


TEST_F(SceneContainerBinRefListTest, allocList)
{
   SceneContainerBinRefList<U32> testList;

   srand(1131830);

   // Set base values
   U32 valueList[10];
   U32 valueList2[10];
   for (U32 i = 0; i < 10; i++)
   {
      valueList[i] = rand() % 1024;
      valueList2[i] = rand() % 1024;
   }

   // Check allocations

   auto listHandle2 = testList.allocList(3, valueList2);

   EXPECT_EQ(testList.getBinLists().size(), 1);
   EXPECT_EQ(testList.getBinLists()[0].numValues, 3);
   EXPECT_EQ(testList.getBinLists()[0].startValue, 0);

   auto listHandle3 = testList.allocList(4, valueList);

   EXPECT_EQ(testList.getBinLists().size(), 2);
   EXPECT_EQ(testList.getBinLists()[1].numValues, 4);
   EXPECT_EQ(testList.getBinLists()[1].startValue, 3);

   // Zero alloc should still return a list

   auto listHandle5 = testList.allocList(0, NULL);

   EXPECT_EQ(testList.getBinLists().size(), 3);
   EXPECT_EQ(testList.getBinLists()[2].numValues, 0);
   EXPECT_EQ(testList.getBinLists()[2].startValue, 7);
}

TEST_F(SceneContainerBinRefListTest, reallocList)
{
   SceneContainerBinRefList<U32> testList;

   srand(1131830);

   // Set base values
   U32 valueList[10];
   U32 valueList2[10];
   for (U32 i = 0; i < 10; i++)
   {
      valueList[i] = rand() % 1024;
      valueList2[i] = rand() % 1024;
   }

   // Reallocating should puts new items at the end

   auto listHandle1 = testList.allocList(2, valueList2);
   testList.reallocList(listHandle1, 1, valueList2);

   EXPECT_EQ(testList.getBinLists().size(), 1);
   EXPECT_EQ(testList.getBinLists()[0].numValues, 1);
   EXPECT_EQ(testList.getBinLists()[0].startValue, 2);

   auto listHandle3 = testList.allocList(3, valueList);
   testList.reallocList(listHandle3, 5, valueList2);

   EXPECT_EQ(testList.getBinLists().size(), 2);
   EXPECT_EQ(testList.getBinLists()[1].numValues, 5);
   EXPECT_EQ(testList.getBinLists()[1].startValue, 6);

   // Unless it has the same number of items

   testList.reallocList(listHandle3, 5, valueList2);

   EXPECT_EQ(testList.getBinLists().size(), 2);
   EXPECT_EQ(testList.getBinLists()[1].numValues, 5);
   EXPECT_EQ(testList.getBinLists()[1].startValue, 6);

   // Should handle invalid handles
   testList.reallocList(100, 5, valueList2);
   EXPECT_EQ(testList.getBinLists().size(), 2);
   EXPECT_EQ(testList.getBinLists()[0].numValues, 1);
   EXPECT_EQ(testList.getBinLists()[0].startValue, 2);
   EXPECT_EQ(testList.getBinLists()[1].numValues, 5);
   EXPECT_EQ(testList.getBinLists()[1].startValue, 6);
}

TEST_F(SceneContainerBinRefListTest, freeList)
{
   SceneContainerBinRefList<U32> testList;

   srand(6131830);

   // Set base values
   U32 valueList[10];
   U32 valueList2[10];
   for (U32 i = 0; i < 10; i++)
   {
      valueList[i] = rand() % 1024;
      valueList2[i] = rand() % 1024;
   }

   // Make some items

   testList.allocList(2, valueList);
   auto listHandle2 = testList.allocList(3, valueList2);
   auto listHandle3 = testList.allocList(4, valueList);
   auto listHandle4 = testList.allocList(5, valueList2);

   // Free the middle one, should now be a hole
   testList.freeList(listHandle3);
   EXPECT_EQ(testList.getBinLists().size(), 4);
   //
   EXPECT_EQ(testList.getBinLists()[0].numValues, 2);
   EXPECT_EQ(testList.getBinLists()[0].startValue, 0);
   //
   EXPECT_EQ(testList.getBinLists()[1].numValues, 3);
   EXPECT_EQ(testList.getBinLists()[1].startValue, 2);
   //
   EXPECT_EQ(testList.getBinLists()[2].numValues, 0);
   EXPECT_EQ(testList.getBinLists()[2].startValue, 0);
   //
   EXPECT_EQ(testList.getBinLists()[3].numValues, 5);
   EXPECT_EQ(testList.getBinLists()[3].startValue, 9);
   EXPECT_EQ(testList.getNextFreeListIndex(), listHandle3);

   // Freeing more will make a stack
   testList.freeList(listHandle2);
   EXPECT_EQ(testList.getNextFreeListIndex(), listHandle2);
   EXPECT_EQ(testList.getBinLists().size(), 4);
   //
   EXPECT_EQ(testList.getBinLists()[0].numValues, 2);
   EXPECT_EQ(testList.getBinLists()[0].startValue, 0);
   //
   EXPECT_EQ(testList.getBinLists()[1].numValues, 0);
   EXPECT_EQ(testList.getBinLists()[1].startValue, 3);
   //
   EXPECT_EQ(testList.getBinLists()[2].numValues, 0);
   EXPECT_EQ(testList.getBinLists()[2].startValue, 0);
   //
   EXPECT_EQ(testList.getBinLists()[3].numValues, 5);
   EXPECT_EQ(testList.getBinLists()[3].startValue, 9);

   // ... which can be popped like this
   auto listHandle5 = testList.allocList(1, valueList);
   EXPECT_EQ(testList.getNextFreeListIndex(), listHandle3);
   auto listHandle6 = testList.allocList(1, valueList);
   EXPECT_EQ(testList.getNextFreeListIndex(), 0);
   EXPECT_EQ(testList.getBinLists().size(), 4);

   // Should handle invalid handles
   testList.freeList(10);
   EXPECT_EQ(testList.getBinLists().size(), 4);

   // Compaction will occur if we free more than CompactionThreshold items in total
   U32* bigList = new U32[SceneContainerBinRefList<U32>::CompactionThreshold];
   memset(bigList, 0, SceneContainerBinRefList<U32>::CompactionThreshold * sizeof(U32));
   auto listHandle8 = testList.allocList(SceneContainerBinRefList<U32>::CompactionThreshold, bigList);
   auto listHandle9 = testList.allocList(SceneContainerBinRefList<U32>::CompactionThreshold, bigList);
   EXPECT_EQ(testList.getBinLists().size(), 6);
   //
   EXPECT_EQ(testList.getBinLists()[4].numValues, SceneContainerBinRefList<U32>::CompactionThreshold);
   EXPECT_EQ(testList.getBinLists()[4].startValue, 16);
   //
   EXPECT_EQ(testList.getBinLists()[5].numValues, SceneContainerBinRefList<U32>::CompactionThreshold);
   EXPECT_EQ(testList.getBinLists()[5].startValue, 16 + (SceneContainerBinRefList<U32>::CompactionThreshold));
   //
   testList.freeList(listHandle8);
   EXPECT_EQ(testList.getBinLists().size(), 6);

   // NOTE: everying unused should get reset to 0

   //
   EXPECT_EQ(testList.getBinLists()[0].numValues, 2);
   EXPECT_EQ(testList.getBinLists()[0].startValue, 0);
   //
   EXPECT_EQ(testList.getBinLists()[1].numValues, 1); // listHandle5
   EXPECT_EQ(testList.getBinLists()[1].startValue, 2);
   //
   EXPECT_EQ(testList.getBinLists()[2].numValues, 1); // listHandle6
   EXPECT_EQ(testList.getBinLists()[2].startValue, 3);
   //
   EXPECT_EQ(testList.getBinLists()[3].numValues, 5);
   EXPECT_EQ(testList.getBinLists()[3].startValue, 4);
   //
   EXPECT_EQ(testList.getBinLists()[4].numValues, 0);
   EXPECT_EQ(testList.getBinLists()[4].startValue, 0);
   //
   EXPECT_EQ(testList.getBinLists()[5].numValues, SceneContainerBinRefList<U32>::CompactionThreshold);
   EXPECT_EQ(testList.getBinLists()[5].startValue, 9);
}

TEST_F(SceneContainerBinRefListTest, replaceListBin)
{
   SceneContainerBinRefList<U32> testList;

   // Set base values
   U32 valueList[] = { 1, 2, 3, 1, 2 };
   U32 valueList2[] = { 256, 700, 1, 1000 };

   // Make some items

   auto listHandle2 = testList.allocList(5, valueList);
   auto listHandle3 = testList.allocList(4, valueList2);

   // Replace items in the list

   testList.replaceListBin(listHandle2, 1, 100);
   testList.replaceListBin(listHandle2, 2, 1010);
   testList.replaceListBin(listHandle2, 3, 101010);

   // First instances of the items should get replaced

   auto itr1 = testList.getValueIterator(listHandle2);
   auto itr2 = testList.getValueIterator(listHandle3);

   EXPECT_EQ(*itr1, 100); itr1++;
   EXPECT_EQ(*itr1, 1010); itr1++;
   EXPECT_EQ(*itr1, 101010); itr1++;
   EXPECT_EQ(*itr1, 1); itr1++;
   EXPECT_EQ(*itr1, 2); itr1++;
   //
   EXPECT_EQ(*itr2, 256); itr2++;
   EXPECT_EQ(*itr2, 700); itr2++;
   EXPECT_EQ(*itr2, 1); itr2++;
   EXPECT_EQ(*itr2, 1000); itr2++;
}

TEST_F(SceneContainerBinRefListTest, containsBinItem)
{
   SceneContainerBinRefList<U32> testList;

   // Set base values
   U32 valueList[] = { 1,2,3 };
   U32 valueList2[] = { 256, 700, 900, 1000 };

   // Make some items

   auto listHandle2 = testList.allocList(3, valueList);
   auto listHandle3 = testList.allocList(4, valueList2);

   // Checks should pass

   EXPECT_EQ(testList.containsBinItem(listHandle2, 1), true);
   EXPECT_EQ(testList.containsBinItem(listHandle2, 2), true);
   EXPECT_EQ(testList.containsBinItem(listHandle2, 3), true);
   EXPECT_EQ(testList.containsBinItem(listHandle2, 256), false);
   EXPECT_EQ(testList.containsBinItem(listHandle2, 700), false);
   EXPECT_EQ(testList.containsBinItem(listHandle2, 900), false);
   EXPECT_EQ(testList.containsBinItem(listHandle2, 1000), false);
   //
   EXPECT_EQ(testList.containsBinItem(listHandle3, 1), false);
   EXPECT_EQ(testList.containsBinItem(listHandle3, 2), false);
   EXPECT_EQ(testList.containsBinItem(listHandle3, 3), false);
   EXPECT_EQ(testList.containsBinItem(listHandle3, 256), true);
   EXPECT_EQ(testList.containsBinItem(listHandle3, 700), true);
   EXPECT_EQ(testList.containsBinItem(listHandle3, 900), true);
   EXPECT_EQ(testList.containsBinItem(listHandle3, 1000), true);

   // Invalid handles should return false

   EXPECT_EQ(testList.containsBinItem(62, 1000), false);
}

TEST_F(SceneContainerBinRefListTest, compact)
{
   SceneContainerBinRefList<U32> testList;

   srand(7131830);

   // Set base values
   U32 valueList[10];
   U32 valueList2[10];
   for (U32 i = 0; i < 10; i++)
   {
      valueList[i] = rand() % 1024;
      valueList2[i] = rand() % 1024;
   }

   // Unallocated list should do nothing
   testList.compact();
   EXPECT_EQ(testList.getBin(), (U32*)NULL);

   // Check allocations

   auto listHandle2 = testList.allocList(3, valueList2);
   auto listHandle3 = testList.allocList(4, valueList2);

   EXPECT_EQ(testList.getBinLists().size(), 2);
   //
   EXPECT_EQ(testList.getBinLists()[0].numValues, 3);
   EXPECT_EQ(testList.getBinLists()[0].startValue, 0);
   //
   EXPECT_EQ(testList.getBinLists()[1].numValues, 4);
   EXPECT_EQ(testList.getBinLists()[1].startValue, 3);

   testList.compact();

   EXPECT_EQ(testList.getBinLists().size(), 2);
   //
   EXPECT_EQ(testList.getBinLists()[0].numValues, 3);
   EXPECT_EQ(testList.getBinLists()[0].startValue, 0);
   //
   EXPECT_EQ(testList.getBinLists()[1].numValues, 4);
   EXPECT_EQ(testList.getBinLists()[1].startValue, 3);

   // Make lots of tiny allocations
   U32 totalAllocItems = 0;
   for (U32 i = 0; i < SceneContainerBinRefList<U32>::CompactionThreshold / 2; i++)
   {
      auto listHandle = testList.allocList(1, valueList2);
      testList.freeList(listHandle);
      totalAllocItems++;
   }

   // 
   auto endListHandle = testList.allocList(4, valueList2);

   EXPECT_EQ(testList.getBinLists().size(), 3);
   //
   EXPECT_EQ(testList.getBinLists()[0].numValues, 3);
   EXPECT_EQ(testList.getBinLists()[0].startValue, 0);
   //
   EXPECT_EQ(testList.getBinLists()[1].numValues, 4);
   EXPECT_EQ(testList.getBinLists()[1].startValue, 3);
   //
   EXPECT_EQ(testList.getBinLists()[2].numValues, 4);
   EXPECT_EQ(testList.getBinLists()[2].startValue, 7 + totalAllocItems);

   // Compact should compact everything
   testList.compact();

   EXPECT_EQ(testList.getBinLists().size(), 3);
   //
   EXPECT_EQ(testList.getBinLists()[0].numValues, 3);
   EXPECT_EQ(testList.getBinLists()[0].startValue, 0);
   //
   EXPECT_EQ(testList.getBinLists()[1].numValues, 4);
   EXPECT_EQ(testList.getBinLists()[1].startValue, 3);
   //
   EXPECT_EQ(testList.getBinLists()[2].numValues, 4);
   EXPECT_EQ(testList.getBinLists()[2].startValue, 7);

}

TEST_F(SceneContainerBinRefListTest, clear)
{
   SceneContainerBinRefList<U32> testList;

   srand(1131830);

   // Set base values
   U32 valueList[10];
   U32 valueList2[10];
   for (U32 i = 0; i < 10; i++)
   {
      valueList[i] = rand() % 1024;
      valueList2[i] = rand() % 1024;
   }

   testList.allocList(3, valueList);
   testList.allocList(4, valueList2);

   EXPECT_EQ(testList.getBinLists().size(), 2);
   testList.clear();
   EXPECT_EQ(testList.getBinLists().size(), 0);
}

extern bool gEditingMission;

class SceneObjectTestVariant : public SceneObject
{
   typedef SceneObject Parent;
public:
   std::function<void() > mAddCallback;

   U32 mNumCastRayCalls;
   U32 mNumBuildConvexCalls;
   U32 mNumBuildPolyListCalls;
   U32 mNumCollideBoxCalls;
   U32 mNumCastRayRenderedCalls;

   bool mReturnCastRay;
   RayInfo mRayInfo;

   bool onAdd()
   {
      if (Parent::onAdd())
      {
         mNumCastRayCalls = 0;
         mNumBuildConvexCalls = 0;
         mNumBuildPolyListCalls = 0;
         mNumCollideBoxCalls = 0;
         mNumCastRayRenderedCalls = 0;
         mReturnCastRay = false;
         mRayInfo = {};

         if (mAddCallback)
            mAddCallback();

         return true;
      }
      return false;
   }

   void onRemove()
   {
      removeFromScene();
      Parent::onRemove();
   }

   void setTypeMask(U32 mask)
   {
      mTypeMask = mask;
   }

   virtual void buildConvex(const Box3F& box, Convex* convex)
   {
      mNumBuildConvexCalls++;
   }

   virtual bool buildPolyList(PolyListContext context, AbstractPolyList* polyList, const Box3F& box, const SphereF& sphere)
   {
      mNumBuildPolyListCalls++;
      return false;
   }

   virtual bool castRay(const Point3F& start, const Point3F& end, RayInfo* info)
   {
      mNumCastRayCalls++;
      if (!mReturnCastRay)
         return false;

      *info = mRayInfo;

      return true;
   }

   virtual bool castRayRendered(const Point3F& start, const Point3F& end, RayInfo* info)
   {
      mNumCastRayRenderedCalls++;
      if (!mReturnCastRay)
         return false;

      *info = mRayInfo;

      return false;
   }

   virtual bool collideBox(const Point3F& start, const Point3F& end, RayInfo* info)
   {
      mNumCollideBoxCalls++;
      return false;
   }

   void setWorldBox(const Box3F& box)
   {
      mWorldBox = box;
   }
};

class SceneContainerTest : public ::testing::Test
{
protected:

   SimGroup* mGroup;

   SceneContainerTest()
   {
   }

   void SetUp() override
   {
      mGroup = new SimGroup();
      gEditingMission = true;

      SceneObjectTestVariant* so1 = new SceneObjectTestVariant;
      so1->registerObject("SO1");
      SceneObjectTestVariant* so2 = new SceneObjectTestVariant;
      so2->registerObject("SO2");
      SceneObjectTestVariant* so3 = new SceneObjectTestVariant;
      so3->registerObject("SO3");
      SceneObjectTestVariant* so4 = new SceneObjectTestVariant;
      so4->registerObject("SO4");
      SceneObjectTestVariant* so5 = new SceneObjectTestVariant;
      so5->registerObject("SO5");

      mGroup->addObject(so1);
      mGroup->addObject(so2);
      mGroup->addObject(so3);
      mGroup->addObject(so4);
      mGroup->addObject(so5);

      gEditingMission = false;
   }

   void TearDown() override
   {
      mGroup->deleteObject();
   }


};

TEST_F(SceneContainerTest, findObjects)
{
   // Set up the objects
   SceneObjectTestVariant* so1 = NULL;
   SceneObjectTestVariant* so2 = NULL;
   SceneObjectTestVariant* so3 = NULL;
   SceneObjectTestVariant* so4 = NULL;
   SceneObjectTestVariant* so5 = NULL;

   Sim::findObject("SO1", so1);
   Sim::findObject("SO2", so2);
   Sim::findObject("SO3", so3);
   Sim::findObject("SO4", so4);
   Sim::findObject("SO5", so5);

   so1->setTypeMask(MarkerObjectType);
   so3->setTypeMask(MarkerObjectType);
   so4->setTypeMask(MarkerObjectType);
   so1->addToScene();
   so2->addToScene();
   so3->addToScene();
   so4->addToScene();
   so5->addToScene();

   // Should find all 3 objects we put there in the setup

   SceneContainer::ObjectList outList;
   gServerSceneGraph->getContainer()->findObjectList(MarkerObjectType, &outList);

   EXPECT_EQ(outList.size(), 3);

   EXPECT_EQ(outList[0], so1);
   EXPECT_EQ(outList[1], so3);
   EXPECT_EQ(outList[2], so4);

   outList.clear();

   // Won't find other objects

   gServerSceneGraph->getContainer()->findObjectList(PlayerObjectType, &outList);

   EXPECT_EQ(outList.size(), 0);

   so1->removeFromScene();
   so2->removeFromScene();
   so3->removeFromScene();
   so4->removeFromScene();
   so5->removeFromScene();
}

TEST_F(SceneContainerTest, polyhedronFindObjects)
{
   // Basically: only gets called on objects in the right bin
   SceneObjectTestVariant* so1 = NULL;
   Polyhedron shape;


   shape.buildBox(MatrixF(1), Box3F(Point3F(0,0,0), Point3F(100,100,100)), true);

   Sim::findObject("SO1", so1);

   MatrixF m(1);
   m.setPosition(Point3F(SceneContainer::csmBinSize, SceneContainer::csmBinSize, 0));
   so1->setTypeMask(MarkerObjectType);
   so1->setTransform(m);

   gClientSceneGraph->getContainer()->addObject(so1);

   static Vector<SceneObject*> foundList;
   foundList.clear();
   RayInfo info;
   gClientSceneGraph->getContainer()->polyhedronFindObjects(shape, MarkerObjectType, [](SceneObject* object, void* key) {

      });

   gClientSceneGraph->getContainer()->removeObject(so1);
}

TEST_F(SceneContainerTest, findObjectList)
{
   // Basically: only gets called on objects in the right bin
   SceneObjectTestVariant* so1 = NULL;

   Sim::findObject("SO1", so1);

   MatrixF m(1);
   m.setPosition(Point3F(SceneContainer::csmBinSize, SceneContainer::csmBinSize, 0));
   so1->setTypeMask(MarkerObjectType);
   so1->setTransform(m);

   gClientSceneGraph->getContainer()->addObject(so1);

   Vector<SceneObject*> foundList;
   PolyListContext ctx;
   Box3F box(Point3F(0, 0, 0), Point3F(0, 100, 0));
   RayInfo info;
   gClientSceneGraph->getContainer()->findObjectList(box, MarkerObjectType, &foundList);

   EXPECT_EQ(foundList.size(), 0);

   foundList.clear();
   box = Box3F(Point3F(0, 0, 0), Point3F(100, 100, 0));
   gClientSceneGraph->getContainer()->findObjectList(box, MarkerObjectType, &foundList);

   EXPECT_EQ(foundList.size(), 1);

   gClientSceneGraph->getContainer()->removeObject(so1);
}

TEST_F(SceneContainerTest, castRay)
{
   // Basically: only gets called on objects in the right bin
   SceneObjectTestVariant* so1 = NULL;

   Sim::findObject("SO1", so1);

   MatrixF m(1);
   m.setPosition(Point3F(SceneContainer::csmBinSize, SceneContainer::csmBinSize, 0));
   so1->setTypeMask(MarkerObjectType);
   so1->setTransform(m);
   so1->setWorldBox(Box3F(m.getPosition(), m.getPosition() + Point3F(SceneContainer::csmBinSize-2, SceneContainer::csmBinSize-2, 10)));

   gClientSceneGraph->getContainer()->addObject(so1);

   Point3F start(0, 0, 0);
   Point3F end(0, 100, 0);
   RayInfo info;
   bool castCheck = gClientSceneGraph->getContainer()->castRay(start, end, MarkerObjectType, &info);

   EXPECT_EQ(so1->mNumCastRayCalls, 0);

   start = Point3F(SceneContainer::csmBinSize + 1, SceneContainer::csmBinSize + 1, 0);
   castCheck = gClientSceneGraph->getContainer()->castRay(start, end, MarkerObjectType, &info);

   EXPECT_EQ(so1->mNumCastRayCalls, 1);

   gClientSceneGraph->getContainer()->removeObject(so1);
}


TEST_F(SceneContainerTest, castRay_order)
{
   SceneObjectTestVariant* so1 = NULL;
   SceneObjectTestVariant* so2 = NULL;

   Sim::findObject("SO1", so1);
   Sim::findObject("SO2", so2);

   MatrixF m(1);
   m.setPosition(Point3F(0, 0, 0));
   so1->setTypeMask(MarkerObjectType);
   so1->setTransform(m);
   so1->setWorldBox(Box3F(m.getPosition() - Point3F(5, 5, 5), m.getPosition() + Point3F(5,5,5)));

   so2->setTypeMask(MarkerObjectType);
   so2->setGlobalBounds();

   so1->mReturnCastRay = true;
   so2->mReturnCastRay = true;

   gClientSceneGraph->getContainer()->addObject(so1);
   gClientSceneGraph->getContainer()->addObject(so2);

   // Here we need to ensure that so1 or so2 will be picked based on shortest distance
   RayInfo closeInfo = {};
   RayInfo farInfo = {};

   closeInfo.t = 5 / 100.0;
   farInfo.t = 10 / 100.0;

   // so1=far, so2=close
   {
      so1->mRayInfo = farInfo;
      so1->mRayInfo.object = so1;
      so2->mRayInfo = closeInfo;
      so2->mRayInfo.object = so2;

      Point3F start(0, 0, 0);
      Point3F end(0, 0, -100);
      RayInfo info;
      bool castCheck = gClientSceneGraph->getContainer()->castRay(start, end, MarkerObjectType, &info);

      EXPECT_EQ(castCheck, true);
      EXPECT_EQ(so1->mNumCastRayCalls, 1);
      EXPECT_EQ(so2->mNumCastRayCalls, 1);

      EXPECT_EQ(info.distance, 5);
      EXPECT_EQ(info.object, so2);
   }

   // so2=far, so1=close
   {
      so2->mRayInfo = farInfo;
      so2->mRayInfo.object = so2;
      so1->mRayInfo = closeInfo;
      so1->mRayInfo.object = so1;

      Point3F start(0, 0, 0);
      Point3F end(0, 0, -100);
      RayInfo info;
      bool castCheck = gClientSceneGraph->getContainer()->castRay(start, end, MarkerObjectType, &info);

      EXPECT_EQ(castCheck, true);
      EXPECT_EQ(so1->mNumCastRayCalls, 2);
      EXPECT_EQ(so2->mNumCastRayCalls, 2);

      EXPECT_EQ(info.distance, 5);
      EXPECT_EQ(info.object, so1);
   }

   gClientSceneGraph->getContainer()->removeObject(so1);
   gClientSceneGraph->getContainer()->removeObject(so2);
}


TEST_F(SceneContainerTest, castRayRendered)
{
   // Basically: only gets called on objects in the right bin
   SceneObjectTestVariant* so1 = NULL;

   Sim::findObject("SO1", so1);

   MatrixF m(1);
   m.setPosition(Point3F(SceneContainer::csmBinSize, SceneContainer::csmBinSize, 0));
   so1->setTypeMask(MarkerObjectType);
   so1->setTransform(m);
   so1->setWorldBox(Box3F(m.getPosition(), m.getPosition() + Point3F(SceneContainer::csmBinSize - 2, SceneContainer::csmBinSize - 2, 10)));

   gClientSceneGraph->getContainer()->addObject(so1);

   Point3F start(0, 0, 0);
   Point3F end(0, 100, 0);
   RayInfo info;
   bool castCheck = gClientSceneGraph->getContainer()->castRayRendered(start, end, MarkerObjectType, &info);

   EXPECT_EQ(so1->mNumCastRayRenderedCalls, 0);

   start = Point3F(SceneContainer::csmBinSize + 1, SceneContainer::csmBinSize + 1, 0);
   castCheck = gClientSceneGraph->getContainer()->castRayRendered(start, end, MarkerObjectType, &info);

   EXPECT_EQ(so1->mNumCastRayRenderedCalls, 1);

   gClientSceneGraph->getContainer()->removeObject(so1);
}

TEST_F(SceneContainerTest, collideBox)
{
   // Basically: only gets called on objects in the right bin
   SceneObjectTestVariant* so1 = NULL;

   Sim::findObject("SO1", so1);

   MatrixF m(1);
   m.setPosition(Point3F(SceneContainer::csmBinSize, SceneContainer::csmBinSize, 0));
   so1->setTypeMask(MarkerObjectType);
   so1->setTransform(m);

   gClientSceneGraph->getContainer()->addObject(so1);

   Point3F start(0, 0, 0);
   Point3F end(0, 100, 0);
   RayInfo info;
   bool castCheck = gClientSceneGraph->getContainer()->collideBox(start, end, 0xFFFFFFFF, &info);

   EXPECT_EQ(so1->mNumCollideBoxCalls, 0);

   start = Point3F(SceneContainer::csmBinSize + 1, SceneContainer::csmBinSize + 1, 0);
   castCheck = gClientSceneGraph->getContainer()->collideBox(start, end, 0xFFFFFFFF, &info);

   EXPECT_EQ(so1->mNumCollideBoxCalls, 1);

   gClientSceneGraph->getContainer()->removeObject(so1);
}

TEST_F(SceneContainerTest, buildPolyList)
{
   // Basically: only gets called on objects in the right bin
   SceneObjectTestVariant* so1 = NULL;

   Sim::findObject("SO1", so1);

   MatrixF m(1);
   m.setPosition(Point3F(SceneContainer::csmBinSize, SceneContainer::csmBinSize, 0));
   so1->setTypeMask(MarkerObjectType);
   so1->setTransform(m);

   gClientSceneGraph->getContainer()->addObject(so1);

   ClippedPolyList polyList;
   Box3F box(Point3F(0, 0, 0), Point3F(10, 10, 0));
   RayInfo info;
   bool castCheck = gClientSceneGraph->getContainer()->buildPolyList(PLC_Collision, box, 0xFFFFFFFF, &polyList);

   EXPECT_EQ(so1->mNumBuildPolyListCalls, 0);

   box = Box3F(Point3F(0, 0, 0), Point3F(100, 100, 0));
   castCheck = gClientSceneGraph->getContainer()->buildPolyList(PLC_Collision, box, 0xFFFFFFFF, &polyList);

   EXPECT_EQ(so1->mNumBuildPolyListCalls, 1);

   gClientSceneGraph->getContainer()->removeObject(so1);
}

TEST_F(SceneContainerTest, addObject)
{
   // Set up the objects
   SceneObjectTestVariant* so1 = NULL;
   SceneObjectTestVariant* so2 = NULL;
   SceneObjectTestVariant* so3 = NULL;
   SceneObjectTestVariant* so4 = NULL;
   SceneObjectTestVariant* so5 = NULL;

   Sim::findObject("SO1", so1);
   Sim::findObject("SO2", so2);
   Sim::findObject("SO3", so3);
   Sim::findObject("SO4", so4);
   Sim::findObject("SO5", so5);

   so1->setTypeMask(MarkerObjectType);
   so3->setTypeMask(MarkerObjectType);
   so4->setTypeMask(MarkerObjectType);

   MatrixF m(1);
   m.setPosition(Point3F(SceneContainer::csmBinSize, 0, 0));
   so1->setTransform(m);

   m.setPosition(Point3F(0, SceneContainer::csmBinSize, 0));
   so2->setTransform(m);

   m.setPosition(Point3F(SceneContainer::csmBinSize * 2, 0, 0));
   so3->setTransform(m);

   m.setPosition(Point3F(SceneContainer::csmBinSize * 2, SceneContainer::csmBinSize * 2, 0));
   so4->setTransform(m);

   gClientSceneGraph->getContainer()->addObject(so1);
   gClientSceneGraph->getContainer()->addObject(so2);
   gClientSceneGraph->getContainer()->addObject(so3);
   gClientSceneGraph->getContainer()->addObject(so4);
   gClientSceneGraph->getContainer()->addObject(so5);

   EXPECT_EQ(so1->getContainer(), gClientSceneGraph->getContainer());
   EXPECT_EQ(so2->getContainer(), gClientSceneGraph->getContainer());
   EXPECT_EQ(so3->getContainer(), gClientSceneGraph->getContainer());
   EXPECT_EQ(so4->getContainer(), gClientSceneGraph->getContainer());
   EXPECT_EQ(so5->getContainer(), gClientSceneGraph->getContainer());

   // Should be put in correct bins

   U32 startIndex = so1->getRootContainerIndex();

   EXPECT_EQ(so2->getRootContainerIndex(), startIndex + 1);
   EXPECT_EQ(so3->getRootContainerIndex(), startIndex + 2);
   EXPECT_EQ(so4->getRootContainerIndex(), startIndex + 3);
   EXPECT_EQ(so5->getRootContainerIndex(), startIndex + 4);

   SceneBinListLookup lookup = {};
   lookup.mRange.minCoord[0] = 1;
   lookup.mRange.maxCoord[0] = 1;
   lookup.mRange.minCoord[1] = 0;
   lookup.mRange.maxCoord[1] = 0;
   EXPECT_EQ(so1->getContainerLookupInfo().mRange, lookup.mRange);
   lookup.mRange.minCoord[0] = 0;
   lookup.mRange.maxCoord[0] = 0;
   lookup.mRange.minCoord[1] = 1;
   lookup.mRange.maxCoord[1] = 1;
   EXPECT_EQ(so2->getContainerLookupInfo().mRange, lookup.mRange);
   lookup.mRange.minCoord[0] = 2;
   lookup.mRange.maxCoord[0] = 2;
   lookup.mRange.minCoord[1] = 0;
   lookup.mRange.maxCoord[1] = 0;
   EXPECT_EQ(so3->getContainerLookupInfo().mRange, lookup.mRange);
   lookup.mRange.minCoord[0] = 2;
   lookup.mRange.maxCoord[0] = 2;
   lookup.mRange.minCoord[1] = 2;
   lookup.mRange.maxCoord[1] = 2;
   EXPECT_EQ(so4->getContainerLookupInfo().mRange, lookup.mRange);
   lookup.mRange.minCoord[0] = 0;
   lookup.mRange.maxCoord[0] = 0;
   lookup.mRange.minCoord[1] = 0;
   lookup.mRange.maxCoord[1] = 0;
   EXPECT_EQ(so5->getContainerLookupInfo().mRange, lookup.mRange);

   // Check a bin
   Vector<SceneObject*> list;
   gClientSceneGraph->getContainer()->dumpBin(1, 0, list);
   EXPECT_EQ(list.size(), 1);
   EXPECT_EQ(list[0], so1);

   gClientSceneGraph->getContainer()->removeObject(so1);
   gClientSceneGraph->getContainer()->removeObject(so2);
   gClientSceneGraph->getContainer()->removeObject(so3);
   gClientSceneGraph->getContainer()->removeObject(so4);
   gClientSceneGraph->getContainer()->removeObject(so5);
}

TEST_F(SceneContainerTest, removeObject)
{
   // Set up the objects
   SceneObjectTestVariant* so1 = NULL;
   SceneObjectTestVariant* so2 = NULL;
   SceneObjectTestVariant* so3 = NULL;

   Sim::findObject("SO1", so1);
   Sim::findObject("SO2", so2);
   Sim::findObject("SO3", so3);

   MatrixF m(1);
   m.setPosition(Point3F(SceneContainer::csmBinSize, 0, 0));
   so1->setTransform(m);

   m.setPosition(Point3F(0, SceneContainer::csmBinSize, 0));
   so2->setTransform(m);

   m.setPosition(Point3F(SceneContainer::csmBinSize * 2, 0, 0));
   so3->setTransform(m);

   gClientSceneGraph->getContainer()->addObject(so1);
   gClientSceneGraph->getContainer()->addObject(so2);
   gClientSceneGraph->getContainer()->addObject(so3);

   EXPECT_EQ(so1->getContainer(), gClientSceneGraph->getContainer());
   EXPECT_EQ(so2->getContainer(), gClientSceneGraph->getContainer());
   EXPECT_EQ(so3->getContainer(), gClientSceneGraph->getContainer());

   // Should get removed correctly
   gClientSceneGraph->getContainer()->removeObject(so2);
   EXPECT_EQ(so1->getContainer(), gClientSceneGraph->getContainer());
   EXPECT_EQ(so2->getContainer(), (SceneContainer*)NULL);
   EXPECT_EQ(so3->getContainer(), gClientSceneGraph->getContainer());

   gClientSceneGraph->getContainer()->removeObject(so1);
   gClientSceneGraph->getContainer()->removeObject(so3);

   EXPECT_EQ(so1->getContainer(), (SceneContainer*)NULL);
   EXPECT_EQ(so2->getContainer(), (SceneContainer*)NULL);
   EXPECT_EQ(so3->getContainer(), (SceneContainer*)NULL);
}

TEST_F(SceneContainerTest, insertIntoBins)
{
   // Set up the objects
   SceneObjectTestVariant* so1 = NULL;
   SceneObjectTestVariant* so2 = NULL;
   SceneObjectTestVariant* so3 = NULL;
   SceneObjectTestVariant* so4 = NULL;
   SceneObjectTestVariant* so5 = NULL;

   Sim::findObject("SO1", so1);
   Sim::findObject("SO2", so2);
   Sim::findObject("SO3", so3);
   Sim::findObject("SO4", so4);
   Sim::findObject("SO5", so5);

   so1->setTypeMask(MarkerObjectType);
   so3->setTypeMask(MarkerObjectType);
   so4->setTypeMask(MarkerObjectType);

   MatrixF m(1);
   m.setPosition(Point3F(SceneContainer::csmBinSize,0,0));
   so1->setTransform(m);

   m.setPosition(Point3F(0, SceneContainer::csmBinSize, 0));
   so2->setTransform(m);

   m.setPosition(Point3F(SceneContainer::csmBinSize*2, 0, 0));
   so3->setTransform(m);

   m.setPosition(Point3F(SceneContainer::csmBinSize*2, SceneContainer::csmBinSize*2, 0));
   so4->setTransform(m);

   gClientSceneGraph->getContainer()->insertIntoBins(so1);
   gClientSceneGraph->getContainer()->insertIntoBins(so2);
   gClientSceneGraph->getContainer()->insertIntoBins(so3);
   gClientSceneGraph->getContainer()->insertIntoBins(so4);
   gClientSceneGraph->getContainer()->insertIntoBins(so5);

   EXPECT_EQ(so1->getContainer(), (SceneContainer*)NULL);
   EXPECT_EQ(so2->getContainer(), (SceneContainer*)NULL);
   EXPECT_EQ(so3->getContainer(), (SceneContainer*)NULL);
   EXPECT_EQ(so4->getContainer(), (SceneContainer*)NULL);
   EXPECT_EQ(so5->getContainer(), (SceneContainer*)NULL);

   // Should be put in correct bins

   SceneBinListLookup lookup = {};
   lookup.mRange.minCoord[0] = 1;
   lookup.mRange.maxCoord[0] = 1;
   lookup.mRange.minCoord[1] = 0;
   lookup.mRange.maxCoord[1] = 0;
   EXPECT_EQ(so1->getContainerLookupInfo().mRange, lookup.mRange);
   lookup.mRange.minCoord[0] = 0;
   lookup.mRange.maxCoord[0] = 0;
   lookup.mRange.minCoord[1] = 1;
   lookup.mRange.maxCoord[1] = 1;
   EXPECT_EQ(so2->getContainerLookupInfo().mRange, lookup.mRange);
   lookup.mRange.minCoord[0] = 2;
   lookup.mRange.maxCoord[0] = 2;
   lookup.mRange.minCoord[1] = 0;
   lookup.mRange.maxCoord[1] = 0;
   EXPECT_EQ(so3->getContainerLookupInfo().mRange, lookup.mRange);
   lookup.mRange.minCoord[0] = 2;
   lookup.mRange.maxCoord[0] = 2;
   lookup.mRange.minCoord[1] = 2;
   lookup.mRange.maxCoord[1] = 2;
   EXPECT_EQ(so4->getContainerLookupInfo().mRange, lookup.mRange);
   lookup.mRange.minCoord[0] = 0;
   lookup.mRange.maxCoord[0] = 0;
   lookup.mRange.minCoord[1] = 0;
   lookup.mRange.maxCoord[1] = 0;
   EXPECT_EQ(so5->getContainerLookupInfo().mRange, lookup.mRange);

   // Check a bin
   Vector<SceneObject*> list;
   gClientSceneGraph->getContainer()->dumpBin(1, 0, list);
   EXPECT_EQ(list.size(), 1);
   EXPECT_EQ(list[0], so1);

   gClientSceneGraph->getContainer()->removeFromBins(so1);
   gClientSceneGraph->getContainer()->removeFromBins(so2);
   gClientSceneGraph->getContainer()->removeFromBins(so3);
   gClientSceneGraph->getContainer()->removeFromBins(so4);
   gClientSceneGraph->getContainer()->removeFromBins(so5);

   EXPECT_EQ(so1->getContainer(), (SceneContainer*)NULL);
   EXPECT_EQ(so2->getContainer(), (SceneContainer*)NULL);
   EXPECT_EQ(so3->getContainer(), (SceneContainer*)NULL);
   EXPECT_EQ(so4->getContainer(), (SceneContainer*)NULL);
   EXPECT_EQ(so5->getContainer(), (SceneContainer*)NULL);
}

TEST_F(SceneContainerTest, removeFromBins)
{
   // Set up the objects
   SceneObjectTestVariant* so1 = NULL;
   SceneObjectTestVariant* so2 = NULL;
   SceneObjectTestVariant* so3 = NULL;
   SceneObjectTestVariant* so4 = NULL;
   SceneObjectTestVariant* so5 = NULL;

   Sim::findObject("SO1", so1);
   Sim::findObject("SO2", so2);
   Sim::findObject("SO3", so3);
   Sim::findObject("SO4", so4);
   Sim::findObject("SO5", so5);

   so1->setTypeMask(MarkerObjectType);
   so3->setTypeMask(MarkerObjectType);
   so4->setTypeMask(MarkerObjectType);

   MatrixF m(1);
   m.setPosition(Point3F(SceneContainer::csmBinSize, 0, 0));
   so1->setTransform(m);

   m.setPosition(Point3F(0, SceneContainer::csmBinSize*3, 0));
   so2->setTransform(m);

   m.setPosition(Point3F(SceneContainer::csmBinSize * 2, 0, 0));
   so3->setTransform(m);

   m.setPosition(Point3F(SceneContainer::csmBinSize * 2, SceneContainer::csmBinSize * 2, 0));
   so4->setTransform(m);

   gClientSceneGraph->getContainer()->insertIntoBins(so1);
   gClientSceneGraph->getContainer()->insertIntoBins(so2);
   gClientSceneGraph->getContainer()->insertIntoBins(so3);
   gClientSceneGraph->getContainer()->insertIntoBins(so4);
   gClientSceneGraph->getContainer()->insertIntoBins(so5);

   gClientSceneGraph->getContainer()->removeFromBins(so1);
   gClientSceneGraph->getContainer()->removeFromBins(so2);
   gClientSceneGraph->getContainer()->removeFromBins(so3);
   gClientSceneGraph->getContainer()->removeFromBins(so4);
   gClientSceneGraph->getContainer()->removeFromBins(so5);

   EXPECT_EQ(so1->getContainer(), (SceneContainer*)NULL);
   EXPECT_EQ(so2->getContainer(), (SceneContainer*)NULL);
   EXPECT_EQ(so3->getContainer(), (SceneContainer*)NULL);
   EXPECT_EQ(so4->getContainer(), (SceneContainer*)NULL);
   EXPECT_EQ(so5->getContainer(), (SceneContainer*)NULL);
}

TEST_F(SceneContainerTest, checkBins)
{
   // Set up the objects
   SceneObjectTestVariant* so1 = NULL;

   Sim::findObject("SO1", so1);

   MatrixF m(1);
   m.setPosition(Point3F(SceneContainer::csmBinSize, 0, 0));
   so1->setTransform(m);

   gClientSceneGraph->getContainer()->addObject(so1);

   EXPECT_EQ(so1->getContainer(), gClientSceneGraph->getContainer());

   // Should be put in correct bins

   SceneBinListLookup lookup = {};
   lookup.mRange.minCoord[0] = 1;
   lookup.mRange.maxCoord[0] = 1;
   lookup.mRange.minCoord[1] = 0;
   lookup.mRange.maxCoord[1] = 0;
   EXPECT_EQ(so1->getContainerLookupInfo().mRange, lookup.mRange);

   // Check a bin
   Vector<SceneObject*> list;
   gClientSceneGraph->getContainer()->dumpBin(1, 0, list);
   EXPECT_EQ(list.size(), 1);
   EXPECT_EQ(list[0], so1);

   // Move it
   m.setPosition(Point3F(SceneContainer::csmBinSize*2, 0, 0));
   so1->setTransform(m);

   gClientSceneGraph->getContainer()->checkBins(so1);
   lookup.mRange.minCoord[0] = 2;
   lookup.mRange.maxCoord[0] = 2;
   lookup.mRange.minCoord[1] = 0;
   lookup.mRange.maxCoord[1] = 0;
   EXPECT_EQ(so1->getContainerLookupInfo().mRange, lookup.mRange);


   gClientSceneGraph->getContainer()->dumpBin(2, 0, list);
   EXPECT_EQ(list.size(), 1);
   EXPECT_EQ(list[0], so1);

   gClientSceneGraph->getContainer()->removeObject(so1);
}

TEST_F(SceneContainerTest, initRadiusSearch)
{
   // Set up the objects
   SceneObjectTestVariant* so1 = NULL;

   Sim::findObject("SO1", so1);

   MatrixF m(1);
   m.setPosition(Point3F(SceneContainer::csmBinSize, 0, 0));
   so1->setTransform(m);
   so1->setTypeMask(MarkerObjectType);

   gClientSceneGraph->getContainer()->addObject(so1);

   // Should be put in correct bins

   SceneBinListLookup lookup = {};
   lookup.mRange.minCoord[0] = 1;
   lookup.mRange.maxCoord[0] = 1;
   lookup.mRange.minCoord[1] = 0;
   lookup.mRange.maxCoord[1] = 0;
   EXPECT_EQ(so1->getContainerLookupInfo().mRange, lookup.mRange);

   // Check a bin
   Vector<SceneObject*> list;
   gClientSceneGraph->getContainer()->initRadiusSearch(Point3F(0,0,0), 100.0f, MarkerObjectType);
   EXPECT_EQ(gClientSceneGraph->getContainer()->getRadiusSearchList().size(), 1);
   EXPECT_EQ(gClientSceneGraph->getContainer()->getRadiusSearchList()[0]->getPointer(), so1);

   gClientSceneGraph->getContainer()->removeObject(so1);
}

TEST_F(SceneContainerTest, initTypeSearch)
{
   // Set up the objects
   SceneObjectTestVariant* so1 = NULL;

   Sim::findObject("SO1", so1);

   MatrixF m(1);
   m.setPosition(Point3F(SceneContainer::csmBinSize, 0, 0));
   so1->setTransform(m);
   so1->setTypeMask(MarkerObjectType);

   gClientSceneGraph->getContainer()->addObject(so1);

   // Check
   Vector<SceneObject*> list;
   gClientSceneGraph->getContainer()->initTypeSearch(MarkerObjectType);
   EXPECT_EQ(gClientSceneGraph->getContainer()->getRadiusSearchList().size(), 1);
   EXPECT_EQ(gClientSceneGraph->getContainer()->getRadiusSearchList()[0]->getPointer(), so1);

   gClientSceneGraph->getContainer()->removeObject(so1);
}

TEST_F(SceneContainerTest, getBinRange)
{
   U32 minBin = 0;
   U32 maxBin = 0;
   SceneContainer::getBinRange(0, 0, minBin, maxBin);
   EXPECT_EQ(minBin == 0 && maxBin == 0, true);
   SceneContainer::getBinRange(0, SceneContainer::csmBinSize*0.5, minBin, maxBin);
   EXPECT_EQ(minBin == 0 && maxBin == 0, true);
   SceneContainer::getBinRange(SceneContainer::csmBinSize * 0.5, SceneContainer::csmBinSize * 0.5, minBin, maxBin);
   EXPECT_EQ(minBin == 0 && maxBin == 0, true);
   SceneContainer::getBinRange(0, SceneContainer::csmBinSize, minBin, maxBin);
   EXPECT_EQ(minBin == 0 && maxBin == 1, true);
   SceneContainer::getBinRange(SceneContainer::csmBinSize * 1.5, SceneContainer::csmBinSize * 1.5, minBin, maxBin);
   EXPECT_EQ(minBin == 1 && maxBin == 1, true);
   SceneContainer::getBinRange(SceneContainer::csmBinSize, SceneContainer::csmBinSize, minBin, maxBin);
   EXPECT_EQ(minBin == 1 && maxBin == 1, true);
   SceneContainer::getBinRange(SceneContainer::csmBinSize*2, SceneContainer::csmBinSize*2, minBin, maxBin);
   EXPECT_EQ(minBin == 2 && maxBin == 2, true);


   SceneContainer::getBinRange(-1, -1, minBin, maxBin);
   EXPECT_EQ(minBin == (SceneContainer::csmNumAxisBins-1) && maxBin == (SceneContainer::csmNumAxisBins - 1), true);
   SceneContainer::getBinRange(SceneContainer::csmTotalAxisBinSize, SceneContainer::csmTotalAxisBinSize, minBin, maxBin);
   EXPECT_EQ(minBin == 0 && maxBin == 0, true);
   SceneContainer::getBinRange(SceneContainer::csmTotalAxisBinSize + SceneContainer::csmBinSize, SceneContainer::csmTotalAxisBinSize + SceneContainer::csmBinSize, minBin, maxBin);
   EXPECT_EQ(minBin == 1 && maxBin == 1, true);

   SceneContainer::getBinRange(-5, SceneContainer::csmTotalAxisBinSize + SceneContainer::csmBinSize, minBin, maxBin);
   EXPECT_EQ(minBin == 15 && maxBin == 30, true);
}




