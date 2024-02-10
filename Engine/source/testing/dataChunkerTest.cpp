//-----------------------------------------------------------------------------
// Copyright (c) 2023-2024 tgemit contributors.
// See AUTHORS file and git repository for contributor information.
//
// SPDX-License-Identifier: MIT
//-----------------------------------------------------------------------------

#ifdef TORQUE_TESTS_ENABLED
#include "testing/unitTesting.h"
#include "core/dataChunker.h"

struct TestClassChunkerStruct
{
   U32 value;
   U32 value2;

   TestClassChunkerStruct()
   {
      value  = 0xC001B33F;
      value2 = 0x10101010;
   }
   
   ~TestClassChunkerStruct()
   {
      value  = 0;
      value2 = 0;
   }
};


TEST(BaseDataChunkerTest, BaseDataChunker_Should_Function_Correctly)
{
   BaseDataChunker<TestClassChunkerStruct> testChunks(1024);
   BaseDataChunker<U32> testChunk4(1024);
   BaseDataChunker<U64> testChunk8(1024);

   EXPECT_TRUE(testChunks.countUsedBlocks() == 0);
   EXPECT_TRUE(testChunk4.countUsedBlocks() == 0);
   EXPECT_TRUE(testChunk8.countUsedBlocks() == 0);

   testChunks.alloc(1);
   testChunk4.alloc(1);
   testChunk8.alloc(1);

   EXPECT_TRUE(testChunks.countUsedBlocks() == 1);
   EXPECT_TRUE(testChunk4.countUsedBlocks() == 1);
   EXPECT_TRUE(testChunk8.countUsedBlocks() == 1);

   testChunks.alloc(1);
   testChunk4.alloc(1);
   testChunk8.alloc(1);

   EXPECT_TRUE(testChunks.countUsedBlocks() == 1);
   EXPECT_TRUE(testChunk4.countUsedBlocks() == 1);
   EXPECT_TRUE(testChunk8.countUsedBlocks() == 1);

   EXPECT_TRUE(testChunks.countUsedBytes() == (sizeof(TestClassChunkerStruct) * 2));
   EXPECT_TRUE(testChunk4.countUsedBytes() == (sizeof(U32) * 2));
   EXPECT_TRUE(testChunk8.countUsedBytes() == (sizeof(U64) * 2));

   testChunks.freeBlocks(true);
   testChunk4.freeBlocks(true);
   testChunk8.freeBlocks(true);
   
   EXPECT_TRUE(testChunks.countUsedBlocks() == 1);
   EXPECT_TRUE(testChunk4.countUsedBlocks() == 1);
   EXPECT_TRUE(testChunk8.countUsedBlocks() == 1);
   
   testChunks.freeBlocks(false);
   testChunk4.freeBlocks(false);
   testChunk8.freeBlocks(false);
   
   EXPECT_TRUE(testChunks.countUsedBlocks() == 0);
   EXPECT_TRUE(testChunk4.countUsedBlocks() == 0);
   EXPECT_TRUE(testChunk8.countUsedBlocks() == 0);

   testChunks.setChunkSize(sizeof(TestClassChunkerStruct));
   testChunks.alloc(1);
   EXPECT_TRUE(testChunks.countUsedBlocks() == 1);
   testChunks.alloc(1);
   EXPECT_TRUE(testChunks.countUsedBlocks() == 2);
}

TEST(DataChunkerTest, DataChunker_Should_Function_Correctly)
{
   DataChunker testChunk(1024);

   testChunk.alloc(1024);

   EXPECT_TRUE(testChunk.countUsedBlocks() == 1);

   testChunk.alloc(1024);

   EXPECT_TRUE(testChunk.countUsedBlocks() == 2);

   testChunk.alloc(4096);
   
   EXPECT_TRUE(testChunk.countUsedBytes() == (1024+1024+4096));

   EXPECT_TRUE(testChunk.countUsedBlocks() == 3);

   testChunk.alloc(12);

   EXPECT_TRUE(testChunk.countUsedBlocks() == 4);

   testChunk.alloc(12);

   EXPECT_TRUE(testChunk.countUsedBlocks() == 4);
   
   U32 reqEls = AlignedBufferAllocator<uintptr_t>::calcRequiredElementSize(12) * sizeof(uintptr_t);
   
   EXPECT_TRUE(testChunk.countUsedBytes() == (1024+1024+4096+reqEls+reqEls));

   testChunk.freeBlocks(true);
   EXPECT_TRUE(testChunk.countUsedBlocks() == 1);
   testChunk.freeBlocks(false);
   EXPECT_TRUE(testChunk.countUsedBlocks() == 0);

   // Large block cases

   testChunk.alloc(8192);
   EXPECT_TRUE(testChunk.countUsedBlocks() == 1);
   testChunk.freeBlocks(true);
   EXPECT_TRUE(testChunk.countUsedBlocks() == 1);

   testChunk.alloc(8192);
   testChunk.alloc(1024);
   EXPECT_TRUE(testChunk.countUsedBlocks() == 2);
   testChunk.freeBlocks(true);
   EXPECT_TRUE(testChunk.countUsedBlocks() == 1);
   testChunk.freeBlocks(false);
   EXPECT_TRUE(testChunk.countUsedBlocks() == 0);
   
   // Instead using the chunk size
   
   for (U32 i=0; i<8; i++)
   {
      testChunk.alloc(1024);
   }
   EXPECT_TRUE(testChunk.countUsedBlocks() == 8);
   testChunk.freeBlocks(false);
   EXPECT_TRUE(testChunk.countUsedBlocks() == 0);
}

TEST(ChunkerTest,Chunker_Should_Function_Correctly)
{
   Chunker<TestClassChunkerStruct> foo;
   TestClassChunkerStruct* value = foo.alloc();
   EXPECT_TRUE(value->value != 0xC001B33F);
   EXPECT_TRUE(value->value2 != 0x10101010);
   // Should otherwise just act like DataChunker
}

TEST(MultiTypedChunkerTest,MultiTypedChunker_Should_Function_Correctly)
{
   struct TVS1
   {
      int a;
      int b;
   };
   struct TVS2
   {
      int a;
      int b;
      int c;
   };
   MultiTypedChunker chunker;
   TVS1* v1 = chunker.alloc<TVS1>();
   TVS2* v2 = chunker.alloc<TVS2>();
   TVS2* v3 = chunker.alloc<TVS2>();

   EXPECT_TRUE(((U8*)v2) - ((U8*)v1) == sizeof(TVS1));
   EXPECT_TRUE(((U8*)v3) - ((U8*)v2) == AlignedBufferAllocator<MultiTypedChunker::AlignmentType>::calcRequiredPaddedByteSize(sizeof(TVS2)));
}

TEST(ChunkerFreeClassListTest,ChunkerFreeClassList_Should_Function_Correctly)
{
   TestClassChunkerStruct list[5];
   ChunkerFreeClassList<TestClassChunkerStruct> freeListTest;
   
   // Push & pop works as expected
   EXPECT_TRUE(freeListTest.isEmpty() == true);
   freeListTest.push((ChunkerFreeClassList<TestClassChunkerStruct>*)&list[0]);
   EXPECT_TRUE(freeListTest.isEmpty() == false);
   freeListTest.push((ChunkerFreeClassList<TestClassChunkerStruct>*)&list[4]);
   EXPECT_TRUE(freeListTest.pop() == &list[4]);
   EXPECT_TRUE(freeListTest.pop() == &list[0]);
   EXPECT_TRUE(freeListTest.pop() == NULL);
   
   // Reset clears list head
   freeListTest.push((ChunkerFreeClassList<TestClassChunkerStruct>*)&list[4]);
   freeListTest.reset();
   EXPECT_TRUE(freeListTest.pop() == NULL);
}


TEST(FreeListChunkerTest, FreeListChunkerTest_Should_Function_Correctly)
{
   FreeListChunker<TestClassChunkerStruct> testFreeList;
   
   TestClassChunkerStruct* s1 = testFreeList.alloc();
   TestClassChunkerStruct* s2 = testFreeList.alloc();
   
   // Allocation is sequential
   EXPECT_TRUE(s2 > s1);
   EXPECT_TRUE(((s2 - s1) == 1));
   
   testFreeList.free(s1);
   
   // But previous reallocations are reused
   TestClassChunkerStruct* s3 = testFreeList.alloc();
   TestClassChunkerStruct* s4 = testFreeList.alloc();
   
   EXPECT_TRUE(s1 == s3);
   EXPECT_TRUE(((s4 - s2) == 1)); // continues from previous free alloc
   
   // Check sharing
   
   FreeListChunker<TestClassChunkerStruct> sharedChunker(testFreeList.getChunker());
   
   s2 = testFreeList.alloc();
   EXPECT_TRUE(((s2 - s4) == 1));
}

TEST(ClassChunkerTest, ClassChunker_Should_Function_Correctly)
{
   ClassChunker<TestClassChunkerStruct> testClassList;
   
   TestClassChunkerStruct* s1 = testClassList.alloc();
   TestClassChunkerStruct* s2 = testClassList.alloc();
   
   // Allocation is sequential
   EXPECT_TRUE(s2 > s1);
   EXPECT_TRUE(((s2 - s1) == 1));
   
   testClassList.free(s1);
   EXPECT_TRUE(s1->value == 0);
   EXPECT_TRUE(s1->value2 == 0);
   
   // But previous reallocations are reused
   TestClassChunkerStruct* s3 = testClassList.alloc();
   TestClassChunkerStruct* s4 = testClassList.alloc();
   
   EXPECT_TRUE(s1 == s3);
   EXPECT_TRUE(((s4 - s2) == 1)); // continues from previous free alloc
   
   // Values should be initialized correctly for all allocs at this point
   EXPECT_TRUE(s1->value == 0xC001B33F);
   EXPECT_TRUE(s1->value2 == 0x10101010);
   EXPECT_TRUE(s2->value == 0xC001B33F);
   EXPECT_TRUE(s2->value2 == 0x10101010);
   EXPECT_TRUE(s3->value == 0xC001B33F);
   EXPECT_TRUE(s3->value2 == 0x10101010);
   EXPECT_TRUE(s4->value == 0xC001B33F);
   EXPECT_TRUE(s4->value2 == 0x10101010);
   
   // Should still be valid if using freeBlocks
   testClassList.freeBlocks(true);
   EXPECT_TRUE(s1->value == 0xC001B33F);
   EXPECT_TRUE(s1->value2 == 0x10101010);
   EXPECT_TRUE(s2->value == 0xC001B33F);
   EXPECT_TRUE(s2->value2 == 0x10101010);
   EXPECT_TRUE(s3->value == 0xC001B33F);
   EXPECT_TRUE(s3->value2 == 0x10101010);
   EXPECT_TRUE(s4->value == 0xC001B33F);
   EXPECT_TRUE(s4->value2 == 0x10101010);
}


TEST(ThreeTieredChunkerTest,ThreeTieredChunker_Should_Function_Correctly)
{
   struct TThreeSA
   {
      uintptr_t a;
   };
   struct TThreeSB
   {
      uintptr_t a;
      uintptr_t b;
   };
   struct TThreeSC
   {
      uintptr_t a;
      uintptr_t b;
      uintptr_t c;
   };
   struct TThreeSD
   {
      uintptr_t a;
      uintptr_t b;
      uintptr_t c;
      uintptr_t d;
   };
   ThreeTieredChunker<TThreeSA, TThreeSB, TThreeSC> threeChunker;

   // Alloc should alloc in the correct lists

   auto h1 = threeChunker.alloc(sizeof(TThreeSA));
   auto h2 = threeChunker.alloc(sizeof(TThreeSB));
   auto h3 = threeChunker.alloc(sizeof(TThreeSC));
   auto h4 = threeChunker.alloc(sizeof(TThreeSD));

   EXPECT_TRUE(threeChunker.getT1Chunker().isManagedByChunker(h3.ptr) == false);
   EXPECT_TRUE(threeChunker.getT2Chunker().isManagedByChunker(h3.ptr) == false);
   EXPECT_TRUE(threeChunker.getT3Chunker().isManagedByChunker(h3.ptr) == true);
   EXPECT_TRUE(h3.tier == 3);

   EXPECT_TRUE(threeChunker.getT1Chunker().isManagedByChunker(h2.ptr) == false);
   EXPECT_TRUE(threeChunker.getT2Chunker().isManagedByChunker(h2.ptr) == true);
   EXPECT_TRUE(threeChunker.getT3Chunker().isManagedByChunker(h2.ptr) == false);
   EXPECT_TRUE(h2.tier == 2);

   EXPECT_TRUE(threeChunker.getT1Chunker().isManagedByChunker(h1.ptr) == true);
   EXPECT_TRUE(threeChunker.getT2Chunker().isManagedByChunker(h1.ptr) == false);
   EXPECT_TRUE(threeChunker.getT3Chunker().isManagedByChunker(h1.ptr) == false);
   EXPECT_TRUE(h1.tier == 1);

   EXPECT_TRUE(threeChunker.getT1Chunker().isManagedByChunker(h4.ptr) == false);
   EXPECT_TRUE(threeChunker.getT2Chunker().isManagedByChunker(h4.ptr) == false);
   EXPECT_TRUE(threeChunker.getT3Chunker().isManagedByChunker(h4.ptr) == false);
   EXPECT_TRUE(h4.tier == 0);

   threeChunker.free(h1);
   threeChunker.free(h2);
   threeChunker.free(h3);
   threeChunker.free(h4);

   EXPECT_TRUE(h1.ptr == NULL);
   EXPECT_TRUE(h2.ptr == NULL);
   EXPECT_TRUE(h3.ptr == NULL);
   EXPECT_TRUE(h4.ptr == NULL);

   // freeBlocks should also clear ALL the list heads

   EXPECT_FALSE(threeChunker.getT1Chunker().getFreeListHead().isEmpty());
   EXPECT_FALSE(threeChunker.getT2Chunker().getFreeListHead().isEmpty());
   EXPECT_FALSE(threeChunker.getT3Chunker().getFreeListHead().isEmpty());

   threeChunker.freeBlocks(false);

   EXPECT_TRUE(threeChunker.getT1Chunker().getFreeListHead().isEmpty());
   EXPECT_TRUE(threeChunker.getT2Chunker().getFreeListHead().isEmpty());
   EXPECT_TRUE(threeChunker.getT3Chunker().getFreeListHead().isEmpty());
}


#endif
