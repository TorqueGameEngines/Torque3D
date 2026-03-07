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
#include "core/util/tVector.h"

#include "platform/profiler.h"
#include "console/engineAPI.h"


#ifdef TORQUE_DEBUG_GUARD

bool VectorResize(U32* aSize, U32* aCount, void** arrayPtr, U32 newCount, U32 elemSize,
   const char* fileName,
   const U32   lineNum)
{
   PROFILE_SCOPE(VectorResize);

   if (newCount > 0)
   {
      U32 blocks = newCount / VectorBlockSize;
      if (newCount % VectorBlockSize)
         blocks++;
      S32 mem_size = blocks * VectorBlockSize * elemSize;

      const char* pUseFileName = fileName != NULL ? fileName : __FILE__;
      U32 useLineNum = fileName != NULL ? lineNum : __LINE__;

      if (*arrayPtr != NULL)
         *arrayPtr = dRealloc_r(*arrayPtr, mem_size, pUseFileName, useLineNum);
      else
         *arrayPtr = dMalloc_r(mem_size, pUseFileName, useLineNum);

      AssertFatal(*arrayPtr, "VectorResize - Allocation failed.");

      *aCount = newCount;
      *aSize = blocks * VectorBlockSize;
      return true;
   }

   if (*arrayPtr)
   {
      dFree(*arrayPtr);
      *arrayPtr = 0;
   }

   *aSize = 0;
   *aCount = 0;
   return true;
}

#else

bool VectorResize(U32* aSize, U32* aCount, void** arrayPtr, U32 newCount, U32 elemSize)
{
   PROFILE_SCOPE(VectorResize);

   if (newCount > 0)
   {
      U32 blocks = newCount / VectorBlockSize;
      if (newCount % VectorBlockSize)
         blocks++;
      S32 mem_size = blocks * VectorBlockSize * elemSize;
      *arrayPtr = *arrayPtr ? dRealloc(*arrayPtr, mem_size) :
         dMalloc(mem_size);

      *aCount = newCount;
      *aSize = blocks * VectorBlockSize;
      return true;
   }

   if (*arrayPtr)
   {
      dFree(*arrayPtr);
      *arrayPtr = 0;
   }

   *aSize = 0;
   *aCount = 0;
   return true;
}

#endif

void test_Vector_dynamic() {
   Vector<U8> v;
   AssertFatal(v.size() == 0, "Initial size should be 0");
   AssertFatal(v.empty(), "Vector should be empty");

   // push_back, push_front, front, back
   v.push_back(42);
   AssertFatal(v.size() == 1, "Size after push_back should be 1");
   AssertFatal(v[0] == 42, "push_back value incorrect");
   v.push_front(7);
   AssertFatal(v.size() == 2, "Size after push_front should be 2");
   AssertFatal(v[0] == 7 && v[1] == 42, "push_front value incorrect");
   AssertFatal(v.front() == 7, "front() incorrect");
   AssertFatal(v.back() == 42, "back() incorrect");

   // insert, erase, erase_fast
   v.insert(1, 99);
   AssertFatal(v.size() == 3, "Size after insert should be 3");
   AssertFatal(v[1] == 99, "insert value incorrect");
   v.erase(1);
   AssertFatal(v.size() == 2, "Size after erase should be 2");
   v.push_back(55);
   v.erase_fast(static_cast < U32>(0));
   AssertFatal(v.size() == 2, "Size after erase_fast should be 2");

   // find_next, contains, remove
   AssertFatal(v.find_next(42) != -1, "find_next failed");
   AssertFatal(v.contains(42), "contains failed");
   AssertFatal(v.remove(42), "remove failed");
   AssertFatal(!v.contains(42), "remove did not remove value");

   // pop_front, pop_back
   v.push_back(88);
   v.pop_front();
   AssertFatal(v.size() == 1, "pop_front failed");
   v.pop_back();
   AssertFatal(v.size() == 0, "pop_back failed");

   // reserve, capacity, setSize, set, clear, compact, fill, copy, merge, reverse
   v.reserve(5);
   AssertFatal(v.capacity() >= 5, "reserve/capacity failed");
   v.setSize(3);
   AssertFatal(v.size() == 3, "setSize failed");
   U8 arr[3] = { 1,2,3 };
   v.set(arr, 3);
   for (U32 i = 0; i < 3; ++i) AssertFatal(v[i] == arr[i], "set failed");
   v.clear();
   AssertFatal(v.size() == 0, "clear failed");
   v.setSize(3);
   v.fill(9);
   for (U32 i = 0; i < 3; ++i) AssertFatal(v[i] == 9, "fill failed");
   U8 arr2[3] = { 4,5,6 };
   v.copy(arr2);
   for (U32 i = 0; i < 3; ++i) AssertFatal(v[i] == arr2[i], "copy failed");
   v.reverse();
   AssertFatal(v[0] == 6 && v[2] == 4, "reverse failed");
   Vector<U8> v2;
   v2.set(arr, 3);
   v.merge(v2);
   AssertFatal(v.size() == 6, "merge failed");

   // increment, decrement
   v.increment();
   AssertFatal(v.size() == 7, "increment failed");
   v.decrement();
   AssertFatal(v.size() == 6, "decrement failed");
   v.increment(2);
   AssertFatal(v.size() == 8, "increment(n) failed");
   v.decrement(2);
   AssertFatal(v.size() == 6, "decrement(n) failed");

   // insert (block), fill(count), fill(count, offset)
   U8 block[2] = { 10,11 };
   v.insert(block, 2, 2);
   AssertFatal(v[2] == 10 && v[3] == 11, "block insert failed");
   v.fill(7, 2);
   for (U32 i = 0; i < 2; ++i) AssertFatal(v[i] == 7, "fill(count) failed");
   v.fill(8, 2, 2);
   AssertFatal(v[2] == 8 && v[3] == 8, "fill(count,offset) failed");

   // assign, moveFrom, swap, compare, forEach, removeIf, countIf, anyOf, allOf
   Vector<U8> v3;
   v3.set(arr, 3);
   v.assign(&v3, 3, 0, 0);
   for (U32 i = 0; i < 3; ++i) AssertFatal(v[i] == arr[i], "assign failed");
   v3.moveFrom(v);
   AssertFatal(v3.size() == 3 && v.size() == 0, "moveFrom failed");
   v.set(arr, 3);
   v.swap(v3);
   for (U32 i = 0; i < 3; ++i) AssertFatal(v[i] == arr[i], "swap failed");
   AssertFatal(v.compare(v3), "compare failed");
   v.forEach([](U8& x) { x = 1; });
   for (U32 i = 0; i < v.size(); ++i) AssertFatal(v[i] == 1, "forEach failed");
   v.removeIf([](U8 x) { return x == 1; });
   AssertFatal(v.size() == 0, "removeIf failed");
   v.set(arr, 3);
   AssertFatal(v.countIf([](U8 x) { return x > 1; }) == 2, "countIf failed");
   AssertFatal(v.anyOf([](U8 x) { return x == 2; }), "anyOf failed");
   AssertFatal(v.allOf([](U8 x) { return x > 0; }), "allOf failed");
}

void test_Vector_fixed() {
   Vector<U8, 10> v;
   AssertFatal(v.size() == 10, "Fixed vector size should be 10");

   // fill, operator[], front, back, first, last
   v.fill(5);
   for (U32 i = 0; i < v.size(); ++i) AssertFatal(v[i] == 5, "fill failed");
   v[3] = 99;
   AssertFatal(v[3] == 99, "operator[] failed");
   AssertFatal(v.front() == 5, "front failed");
   AssertFatal(v.back() == 5, "back failed");
   AssertFatal(v.first() == 5, "first failed");
   AssertFatal(v.last() == 5, "last failed");

   // reverse, swap, erase, erase_fast, contains, remove
   v.reverse();
   AssertFatal(v[6] == 99, "reverse failed");
   Vector<U8, 10> v2;
   v2.fill(1);
   v.swap(v2);
   for (U32 i = 0; i < v.size(); ++i) AssertFatal(v[i] == 1 && v2[i] == 5, "swap failed");
   v.erase(static_cast <U32>(0));
   AssertFatal(v.size() == 10, "erase should not change size for fixed vector");
   v.erase_fast(1);
   AssertFatal(v.size() == 10, "erase_fast should not change size for fixed vector");
   AssertFatal(v.contains(1), "contains failed");
   v.remove(1);
   AssertFatal(v.contains(1), "remove should not change size for fixed vector");

   // fill(count), fill(count, offset), copy, merge, assign, compare
   v.fill(2, 5);
   for (U32 i = 0; i < 5; ++i) AssertFatal(v[i] == 2, "fill(count) failed");
   v.fill(3, 2, 5);
   AssertFatal(v[5] == 3 && v[6] == 3, "fill(count,offset) failed");
   U8 arr[10] = { 0,1,2,3,4,5,6,7,8,9 };
   v.copy(arr);
   for (U32 i = 0; i < 10; ++i) AssertFatal(v[i] == arr[i], "copy failed");
   v2.copy(arr);
   v.merge(v2);
   AssertFatal(v.size() == 10, "merge should not change size for fixed vector");
   v.assign(&v2, 10, 0, 0);
   for (U32 i = 0; i < 10; ++i) AssertFatal(v[i] == arr[i], "assign failed");
   AssertFatal(v.compare(v2), "compare failed");

   // forEach, removeIf, countIf, anyOf, allOf
   v.forEach([](U8& x) { x = 4; });
   for (U32 i = 0; i < v.size(); ++i) AssertFatal(v[i] == 4, "forEach failed");
   v.removeIf([](U8 x) { return x == 4; });
   AssertFatal(v.size() == 10, "removeIf should not change size for fixed vector");
   v.copy(arr);
   AssertFatal(v.countIf([](U8 x) { return x > 5; }) == 4, "countIf failed");
   AssertFatal(v.anyOf([](U8 x) { return x == 7; }), "anyOf failed");
   AssertFatal(v.allOf([](U8 x) { return x < 10; }), "allOf failed");
}

DefineEngineFunction(test_Vector, void, (), ,
   "Test the Vector class with both dynamic and fixed-size vectors.")
{
   test_Vector_dynamic();
   test_Vector_fixed();
}
