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


class SceneContainerTest : public ::testing::Test
{
protected:
   SceneContainerTest()
   {
   }

   void SetUp() override
   {

   }


};


TEST_F(SceneContainerTest, findObjects)
{
}

TEST_F(SceneContainerTest, polyhedronFindObjects)
{
}

TEST_F(SceneContainerTest, findObjectList)
{
}

TEST_F(SceneContainerTest, castRay)
{
}

TEST_F(SceneContainerTest, castRayRendered)
{
}

TEST_F(SceneContainerTest, collideBox)
{
}

TEST_F(SceneContainerTest, buildPolyList)
{
}

TEST_F(SceneContainerTest, addObject)
{
}

TEST_F(SceneContainerTest, removeObject)
{
}

TEST_F(SceneContainerTest, insertIntoBins)
{
}

TEST_F(SceneContainerTest, removeFromBins)
{
}

TEST_F(SceneContainerTest, checkBins)
{
}

TEST_F(SceneContainerTest, initRadiusSearch)
{
}

TEST_F(SceneContainerTest, initTypeSearch)
{
}

TEST_F(SceneContainerTest, getBinRange)
{
}




