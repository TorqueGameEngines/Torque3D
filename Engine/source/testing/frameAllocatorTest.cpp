//-----------------------------------------------------------------------------
// Copyright (c) 2023-2024 tgemit contributors.
// See AUTHORS file and git repository for contributor information.
//
// SPDX-License-Identifier: MIT
//-----------------------------------------------------------------------------

#ifdef TORQUE_TESTS_ENABLED
#include "testing/unitTesting.h"
#include "core/frameAllocator.h"

struct TestAlignmentStruct
{
   U64 values[4];
};

TEST(AlignedBufferAllocatorTest, AlignedBufferAllocator_Should_Function_Correctly)
{
   AlignedBufferAllocator<U32> ba4;
   AlignedBufferAllocator<U64> ba8;
   AlignedBufferAllocator<TestAlignmentStruct> bas;
   
   const U32 bufSize32 = (sizeof(TestAlignmentStruct) / 4) * 20;
   U32 testAlignmentBuffer[bufSize32];
   for (U32 i=0; i<bufSize32; i++)
   {
      testAlignmentBuffer[i] = i;
   }
   
   EXPECT_TRUE(ba4.calcRequiredElementSize(20) == 5);
   EXPECT_TRUE(ba8.calcRequiredElementSize(20) == 3);
   EXPECT_TRUE(bas.calcRequiredElementSize(20) == 1);
   EXPECT_TRUE(bas.calcRequiredElementSize(32) == 1);
   EXPECT_TRUE(bas.calcRequiredElementSize(33) == 2);
   EXPECT_TRUE(bas.calcRequiredElementSize(64) == 2);
   
   
   EXPECT_TRUE(ba4.calcMaxElementSize(20) == 5);
   EXPECT_TRUE(ba8.calcMaxElementSize(20) == 2);
   EXPECT_TRUE(bas.calcMaxElementSize(20) == 0);
   EXPECT_TRUE(bas.calcMaxElementSize(32) == 1);
   EXPECT_TRUE(bas.calcMaxElementSize(33) == 1);
   EXPECT_TRUE(bas.calcMaxElementSize(64) == 2);
   
   ba4.initWithBytes((U32*)testAlignmentBuffer, sizeof(testAlignmentBuffer));
   ba8.initWithBytes((U64*)testAlignmentBuffer,  sizeof(testAlignmentBuffer));
   bas.initWithBytes((TestAlignmentStruct*)testAlignmentBuffer,  sizeof(testAlignmentBuffer));
   
   EXPECT_TRUE(ba4.getElementsLeft() == 160);
   EXPECT_TRUE(ba8.getElementsLeft() == 80);
   EXPECT_TRUE(bas.getElementsLeft() == 20);
   
   EXPECT_TRUE(ba4.getSizeBytes() == 640);
   EXPECT_TRUE(ba8.getSizeBytes() == 640);
   EXPECT_TRUE(bas.getSizeBytes() == 640);
   
   EXPECT_TRUE(ba4.allocElements(1) == &testAlignmentBuffer[0]);
   EXPECT_TRUE(ba4.getPosition() == 1);
   EXPECT_TRUE(ba4.getPositionBytes() == 4);
   EXPECT_TRUE(ba4.getElementsLeft() == 159);
   
   EXPECT_TRUE(ba4.allocElements(7) == &testAlignmentBuffer[1]);
   EXPECT_TRUE(ba4.getPosition() == 8);
   EXPECT_TRUE(ba4.getPositionBytes() == 32);
   EXPECT_TRUE(ba4.getElementsLeft() == 152);
   
   ba4.setPosition(100);
   
   EXPECT_TRUE(ba4.allocElements(1) == &testAlignmentBuffer[100]);
   EXPECT_TRUE(ba4.getPosition() == 101);
   EXPECT_TRUE(ba4.getPositionBytes() == 404);
   EXPECT_TRUE(ba4.getElementsLeft() == 59);
   
   ba4.setPosition(160);
   EXPECT_TRUE(ba4.allocElements(1) == NULL);
   EXPECT_TRUE(ba4.getPosition() == 160);
   EXPECT_TRUE(ba4.getPositionBytes() == (160*4));
   EXPECT_TRUE(ba4.getElementsLeft() == 0);
}

TEST(FrameAllocatorTest, FrameAllocator_Should_Function_Correctly)
{
   // NOTE: assuming alloc and destroy already work
   
   EXPECT_TRUE(FrameAllocator::getWaterMark() == 0);
   FrameAllocator::setWaterMark(100);
   EXPECT_TRUE(FrameAllocator::getWaterMark() == 100);
   FrameAllocator::setWaterMark(104);
   EXPECT_TRUE(FrameAllocator::getWaterMark() == 104);
   
   FrameAllocator::alloc(1);
   EXPECT_TRUE(FrameAllocator::getWaterMark() == 105);
   FrameAllocator::alloc(5);
   EXPECT_TRUE(FrameAllocator::getWaterMark() == 107); // 5 bytes == 2 ints
   
   FrameAllocator::setWaterMark(0);
   FrameAllocator::alloc(1);
   EXPECT_TRUE(FrameAllocator::getWaterMarkBytes() == 4);
   
   FrameAllocator::setWaterMark(0);
}


TEST(FrameAllocatorMarker, FrameAllocatorMarker_Should_Function_Correctly)
{
   U32 markerValue = 0;
   FrameAllocator::setWaterMark(8);

   // Marker should act as a bookmark for the FrameAllocator
   {
      FrameAllocatorMarker marker;
      FrameAllocator::alloc(100);
      markerValue = FrameAllocator::getWaterMark();
      EXPECT_TRUE(markerValue != 8);
      marker.alloc(4);
      EXPECT_TRUE(markerValue != FrameAllocator::getWaterMark());
   }

   // Going out of scope sets watermark
   EXPECT_TRUE(FrameAllocator::getWaterMark() == 8);
}

static U32 gFTDestructTest = 0;

TEST(FrameTempTest, FrameTempShould_Function_Correctly)
{
   FrameAllocator::setWaterMark(0);
   {
      FrameTemp<TestAlignmentStruct> fooTemp(20);
      EXPECT_TRUE(FrameAllocator::getWaterMarkBytes() == sizeof(TestAlignmentStruct)*20);
      EXPECT_TRUE(&fooTemp[0] == fooTemp.address());
      EXPECT_TRUE((&fooTemp[1] - &fooTemp[0]) == 1);
      EXPECT_TRUE(fooTemp.getObjectCount() == 20);
      EXPECT_TRUE(fooTemp.size() == 20);

      const FrameTemp<TestAlignmentStruct>& fooC = fooTemp;
      EXPECT_TRUE(&fooC[0] == fooC.address());
      EXPECT_TRUE((&fooC[1] - &fooC[0]) == 1);
      EXPECT_TRUE(fooC.getObjectCount() == 20);
      EXPECT_TRUE(fooC.size() == 20);

      // Accessors should work

      // Call the overloaded operators by name
      TestAlignmentStruct& value = fooTemp.operator*();
      TestAlignmentStruct** ptr = fooTemp.operator&();
      const TestAlignmentStruct* constPtr = fooTemp.operator const TestAlignmentStruct * ();
      TestAlignmentStruct& ref = fooTemp.operator TestAlignmentStruct & ();
      const TestAlignmentStruct& constRef = fooTemp.operator const TestAlignmentStruct & ();
      TestAlignmentStruct copy = fooTemp.operator TestAlignmentStruct();

      EXPECT_TRUE(*ptr == fooTemp.address());
      EXPECT_TRUE(&value == fooTemp.address());
      EXPECT_TRUE(constPtr == fooTemp.address());
      EXPECT_TRUE(&ref == fooTemp.address());
      EXPECT_TRUE(&constRef == fooTemp.address());
      EXPECT_TRUE(&copy != fooTemp.address());

      // Same for fooC
      const TestAlignmentStruct& Cvalue = fooC.operator*();
      TestAlignmentStruct* const* Cptr = fooC.operator&();
      const TestAlignmentStruct* CconstPtr = fooC.operator const TestAlignmentStruct * ();
      const TestAlignmentStruct& CconstRef = fooC.operator const TestAlignmentStruct & ();

      EXPECT_TRUE(*Cptr == fooC.address());
      EXPECT_TRUE(&Cvalue == fooC.address());
      EXPECT_TRUE(CconstPtr == fooC.address());
      EXPECT_TRUE(&CconstRef == fooC.address());
      EXPECT_TRUE(&ref == fooC.address());
      EXPECT_TRUE(&constRef == fooC.address());
   }

   // Exiting scope sets watermark
   EXPECT_TRUE(FrameAllocator::getWaterMarkBytes() == 0);

   // Test the destructor actually gets called

   struct FTDestructTest
   {
      ~FTDestructTest()
      {
         gFTDestructTest++;
      }
   };

   {
      gFTDestructTest = 0;
      FrameTemp<FTDestructTest> foo2Temp(10);
   }

   EXPECT_TRUE(gFTDestructTest == 10);
}


#endif
