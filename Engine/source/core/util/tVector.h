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

#ifndef _TVECTOR_H_
#define _TVECTOR_H_

// TODO: This shouldn't be included in headers... it should
// be included by the source file before all other includes.
#ifndef _PLATFORM_H_
#include "platform/platform.h"
#endif
#include <memory>
#include <type_traits>
#include <algorithm>
#include "console/engineTypes.h"
#include "console/engineTypeInfo.h"
#ifndef _MMATHFN_H_
#include "math/mMathFn.h"
#endif
//-----------------------------------------------------------------------------
// Helper definitions for the vector class.

/// Size of memory blocks to allocate at a time for vectors.
const static S32 VectorBlockSize = 16;

#ifdef TORQUE_DEBUG_GUARD
extern bool VectorResize(U32* aSize, U32* aCount, void** arrayPtr, U32 newCount, U32 elemSize,
   const char* fileName,
   const U32   lineNum);
#else
extern bool VectorResize(U32* aSize, U32* aCount, void** arrayPtr, U32 newCount, U32 elemSize);
#endif

/// Use the following macro to bind a vector to a particular line
///  of the owning class for memory tracking purposes
#ifdef TORQUE_DEBUG_GUARD
#define VECTOR_SET_ASSOCIATION(x) x.setFileAssociation(__FILE__, __LINE__)
#else
#define VECTOR_SET_ASSOCIATION(x)
#endif

//-----------------------------------------------------------------------------
// Custom allocator using dMalloc/dFree

// typetrait defs
template<U32 COUNT>
struct VectorTrackingTokens {
   U32 arraySize() const { return COUNT; }
   U32 elementCount() const { return COUNT; }
   void setArraySize(U32) {} // no-op
   void setElementCount(U32) {}     // no-op
   /*
   bool mOwnsMemory = false;
   bool ownsMemory() const { return mOwnsMemory; }
   void setOwnsMemory(bool owns) { mOwnsMemory = owns; }
   */
};

template<>
struct VectorTrackingTokens<0> {
   U32 mArraySize = 0;
   U32 mElementCount = 0;
   U32 arraySize() const { return mArraySize; }
   U32 elementCount() const { return mElementCount; }
   void setArraySize(U32 sz) { mArraySize = sz; }
   void setElementCount(U32 sz) { mElementCount = sz; }
   /*
   bool mOwnsMemory = false;
   bool ownsMemory() const { return mOwnsMemory; }
   void setOwnsMemory(bool owns) { mOwnsMemory = owns; }
   */
};

template<typename VecT>
struct VectorTraits;

template<typename T, U32 COUNT, typename Allocator>
struct VectorTraits<Vector<T, COUNT, Allocator>>
{
   static constexpr U32 mTCount = COUNT;
   using allocator = Allocator;
   using value_type = T;
};

//-----------------------------------------------------------------------------
// Custom allocator using dMalloc/dFree
template<typename T, U32 COUNT>
struct CustomAllocator
{
   using State = VectorTrackingTokens<COUNT>;
   static T* allocate(U32 count = COUNT)
   {
      if (COUNT > 0)
         return reinterpret_cast<T*>(dMalloc(COUNT * sizeof(T)));
      else
         return reinterpret_cast<T*>(dMalloc(count * sizeof(T)));
   }
   static void deallocate(T* ptr)
   {
      dFree(ptr);
   }
};

//-----------------------------------------------------------------------------
// VectorHelpers namespace
//
// Purpose:
//   - Provides extensible, utility functions for vector operations.
//   - Supports bulk, cross-type, and advanced operations not covered by core vector methods.
//   - Intended for use cases such as batch processing, interoperability, and future extensions (e.g., TreeNode, BVH, SVO).
//
// Usage:
//   - Use VectorHelpers for operations that go beyond standard vector element access and modification.
//   - Suitable for experimental, cross-type, or performance-oriented utilities.
//
// Example operations:
//   - Bulk copy, move, fill, destroy across multiple vectors or specializations.
//   - Generic algorithms and batch utilities for vector-like types.
//   - Integration with advanced data structures or scene systems.
//
namespace VectorHelpers
{
   // Helper for fixed-size capacity checks.
   template<typename VecT>
   inline bool checkFixedCapacity(VecT* vec, U32 required)
   {
      using Traits = VectorTraits<VecT>;
      constexpr U32 COUNT = Traits::COUNT;
      if constexpr (COUNT != 0)
      {
         if (required > COUNT)
         {
            AssertFatal(false, "VectorHelpers::checkFixedCapacity - operation would exceed fixed vector capacity.");
            return false;
         }
      }
      return true;
   }

   // Copies elements from a buffer into a vector, up to n elements, with offset in both buffer and vector.
   template<typename VecT>
   inline void fromBuffer(VecT* vec, const typename VectorTraits<VecT>::value_type* buffer, U32 n, U32 vecOffset = 0, U32 bufferOffset = 0)
   {
      if (!vec || !buffer || n == 0) return;
      using T = typename VectorTraits<VecT>::value_type;
      T* arr = vec->array();
      U32 len = vec->size();
      if (vecOffset >= len || bufferOffset >= n) return;
      if (vecOffset + n > len) n = len - vecOffset;
      if constexpr (std::is_trivially_copyable<T>::value)
         dMemcpy(arr + vecOffset, buffer + bufferOffset, n * sizeof(T));
      else if constexpr (std::is_copy_assignable<T>::value)
         for (U32 i = 0; i < n; ++i) arr[vecOffset + i] = buffer[bufferOffset + i];
      // else: do nothing, not assignable
   }

   // Copies elements from a vector into a buffer, up to n elements, with offset in both vector and buffer.
   template<typename VecT>
   inline void toBuffer(const VecT* vec, typename VectorTraits<VecT>::value_type* buffer, U32 n, U32 vecOffset = 0, U32 bufferOffset = 0)
   {
      if (!vec || !buffer || n == 0) return;
      using T = typename VectorTraits<VecT>::value_type;
      const T* arr = vec->array();
      U32 len = vec->size();
      if (vecOffset >= len || bufferOffset >= n) return;
      if (vecOffset + n > len) n = len - vecOffset;
      if constexpr (std::is_trivially_copyable<T>::value)
         dMemcpy(buffer + bufferOffset, arr + vecOffset, n * sizeof(T));
      else if constexpr (std::is_copy_assignable<T>::value)
         for (U32 i = 0; i < n; ++i) buffer[bufferOffset + i] = arr[vecOffset + i];
      // else: do nothing, not assignable
   }

   // Moves or copies 'n' elements between a buffer and a vector at offset.
   template<typename VecT>
   inline void bufferTransfer(
      VecT& vec,
      typename VectorTraits<VecT>::value_type* buffer,
      typename VectorTraits<VecT>::COUNT n,
      typename VectorTraits<VecT>::COUNT offset,
      bool toBuffer,
      bool moveElements = true)
   {
      using T = typename VectorTraits<VecT>::value_type;
      using U32 = typename VectorTraits<VecT>::COUNT;
      U32 vecCapacity = vec.capacity();
      if (!buffer || n == 0 || offset >= vecCapacity) return;
      if (offset + n > vecCapacity) n = vecCapacity - offset;
      if (offset + n > vec.size()) vec.setSize(offset + n);
      T* vecArray = vec.array();
      if (!moveElements) {
         if (toBuffer) toBuffer(&vec, buffer, n, offset);
         else fromBuffer(&vec, buffer, n, offset);
         return;
      }
      if constexpr (std::is_trivially_copyable<T>::value) {
         if (toBuffer) {
            dMemcpy(buffer, &vecArray[offset], n * sizeof(T));
            dMemset(&vecArray[offset], 0, n * sizeof(T));
         }
         else {
            dMemcpy(&vecArray[offset], buffer, n * sizeof(T));
            dMemset(buffer, 0, n * sizeof(T));
         }
      }
      else if constexpr (std::is_move_assignable<T>::value && std::is_default_constructible<T>::value) {
         if (toBuffer) {
            for (U32 i = 0; i < n; ++i) {
               buffer[i] = std::move(vecArray[offset + i]);
               vecArray[offset + i] = T();
            }
         }
         else {
            for (U32 i = 0; i < n; ++i) {
               vecArray[offset + i] = std::move(buffer[i]);
               buffer[i] = T();
            }
         }
      }
      // else: do nothing, not move-assignable or not default-constructible
   }

   // Merges elements from a source buffer into the end of a vector, resizing if needed.
   template<typename VecT>
   inline void mergeBuffer(VecT* vec, const typename VectorTraits<VecT>::value_type* src, U32 count)
   {
      if (!vec || !src || count == 0) return;
      U32 oldSize = vec->elementCount();
      U32 newSize = oldSize + count;
      if (!checkFixedCapacity(vec, newSize)) return;
      vec->setSize(newSize);
      auto* dest = vec->array() + oldSize;
      for (U32 i = 0; i < count; ++i)
         dest[i] = src[i];
   }

   // Merges elements from a source vector into the end of a target vector, resizing if needed.
   template<typename VecT>
   inline void mergeVector(VecT* vec, const VecT& src)
   {
      if (!vec || src.size() == 0) return;
      U32 oldSize = vec->elementCount();
      U32 count = src.size();
      U32 newSize = oldSize + count;
      if (!checkFixedCapacity(vec, newSize)) return;
      vec->setSize(newSize);
      auto* dest = vec->array() + oldSize;
      auto* srcPtr = src.array();
      for (U32 i = 0; i < count; ++i)
         dest[i] = srcPtr[i];
   }

   // Bulk insert: shift elements once, then copy in bulk.
   template<typename VecT>
   inline void insertBuffer(VecT* vec, const typename VectorTraits<VecT>::value_type* src, U32 count, U32 idx)
   {
      if (!vec || !src || count == 0) return;
      if (!checkFixedCapacity(vec, vec->elementCount() + count)) return;

      // Grow the vector to fit the new elements
      U32 oldCount = vec->elementCount();
      vec->setSize(oldCount + count);

      // Move existing elements after idx up by 'count' slots
      if (oldCount > idx)
         move(vec, vec, oldCount - idx, idx + count, idx);

      // Copy new elements into the gap
      copy(vec, src, count, idx);
   }

   // Permanently redirects the vector's internal T* mArray pointer to an external pool at a given offset and range defined by start/end.
   // For dynamic vectors, update mArraySize/mElementCount if needed.
   // For fixed-size vectors, only updates mArray; user must ensure pool is at least COUNT + start+end elements.
   // Use with caution - this is a low-level operation that can lead to instability if used incorrectly.
   // The caller must ensure the pool remains valid for the vector's lifetime and that no other operations invalidate the pool.
   template<typename VecT>
   inline void rebaseArrayAt(VecT* vec, typename VectorTraits<VecT>::value_type* pool, U32 start, U32 end)
   {
      if (!vec || !pool || end <= start) return;
      using Traits = VectorTraits<VecT>;
      constexpr U32 COUNT = Traits::COUNT;
      if constexpr (COUNT == 0)
         vec->set(pool + start, end - start);
      else {
         if ((end - start) < COUNT) return;
         vec->set(pool + start, COUNT);
      }
   }

   // Applies a function to each element in the source vector.
   // If a target vector is provided, stores the result in the target at targOffset.
   // If no target is provided, applies the function in-place or for side effects.
   template<typename VecT, typename Func>
   inline void forEach(VecT* src, Func fn, U32 srcOffset = 0, U32 n = 0, U32 targOffset = 0, VecT* targ = NULL)
   {
      if (!src) return;
      U32 srcLen = src->size();
      if (srcOffset >= srcLen) return;
      U32 len = (n == 0) ? srcLen - srcOffset : n;
      if (len == 0) return;
      using T = typename VectorTraits<VecT>::value_type;
      T* srcArr = src->array();
      if (targ) {
         U32 targLen = targ->size();
         if (targOffset >= targLen) return;
         len = std::min(len, targLen - targOffset);
         T* targArr = targ->array();
         for (U32 i = 0; i < len; ++i)
            targArr[targOffset + i] = fn(srcArr[srcOffset + i]);
      }
      else {
         for (U32 i = 0; i < len; ++i)
            fn(srcArr[srcOffset + i]);
      }
   }

   // Applies a function to each pair of elements from src and targ vectors.
   // Returns bool for comparison operations; otherwise, void.
   template<typename VecT1, typename VecT2, typename Func>
   inline auto forEachPair(VecT1* src, VecT2* targ, U32 n = 0, U32 srcOffset = 0, U32 targOffset = 0, Func fn = Func())
   {
      if (!src || !targ) {
         using RetType = decltype(fn(*static_cast<typename VectorTraits<VecT1>::value_type*>(NULL),
            *static_cast<typename VectorTraits<VecT2>::value_type*>(NULL)));
         if constexpr (!std::is_void_v<RetType>) return RetType();
         else return;
      }
      U32 srcLen = src->size(), targLen = targ->size();
      if (srcOffset >= srcLen || targOffset >= targLen) {
         using RetType = decltype(fn(*static_cast<typename VectorTraits<VecT1>::value_type*>(NULL),
            *static_cast<typename VectorTraits<VecT2>::value_type*>(NULL)));
         if constexpr (!std::is_void_v<RetType>) return RetType();
         else return;
      }
      U32 len = (n == 0) ? std::min(srcLen - srcOffset, targLen - targOffset) : n;
      if (len == 0) {
         using RetType = decltype(fn(*static_cast<typename VectorTraits<VecT1>::value_type*>(NULL),
            *static_cast<typename VectorTraits<VecT2>::value_type*>(NULL)));
         if constexpr (!std::is_void_v<RetType>) return RetType();
         else return;
      }
      using T = typename VectorTraits<VecT1>::value_type;
      using RetType = decltype(fn(std::declval<T&>(), std::declval<T&>()));
      T* srcArr = src->array();
      T* targArr = targ->array();
      constexpr bool isCompare = std::is_same_v<RetType, bool>;
      if constexpr (isCompare) {
         bool result = true;
         for (U32 i = 0; i < len; ++i)
            result = result && fn(srcArr[srcOffset + i], targArr[targOffset + i]);
         return result;
      }
      else {
         for (U32 i = 0; i < len; ++i)
            fn(srcArr[srcOffset + i], targArr[targOffset + i]);
         if constexpr (!std::is_void_v<RetType>) return RetType();
      }
   }

   // Constructs elements in a vector. Uses std::fill for PODs, constructInPlace for non-PODs.
   template<typename VecT>
   inline void create(VecT* vec, S32 idx = -1, S32 n = 1)
   {
      if (!vec) return;
      U32 len = vec->size();
      U32 start = (idx >= 0) ? static_cast<U32>(idx) : 0;
      U32 count = (n < 1) ? (len - start) : static_cast<U32>(n);
      if (count == 0 || start >= len || start + count > len) return;
      using Traits = VectorTraits<VecT>;
      using T = typename Traits::value_type;
      constexpr U32 COUNT = Traits::COUNT;
      T* arr = vec->array();
      if constexpr (COUNT == 0) {
         // Only construct new elements, do not destruct or move existing ones
         if constexpr (!std::is_trivially_constructible<T>::value)
            for (U32 i = 0; i < count; ++i)
               constructInPlace(&arr[start + i]);
         else
            std::fill(arr + start, arr + start + count, T());
      }
      else {
         if constexpr (!std::is_trivially_constructible<T>::value)
            for (U32 i = 0; i < count; ++i)
               constructInPlace(&arr[start + i]);
         else
            std::fill(arr + start, arr + start + count, T());
         if constexpr (std::is_default_constructible<T>::value)
            std::fill(arr + start + count, arr + COUNT, T());
      }
   }

   // Compacts the vector by moving elements after [start, start+count) down and updating size/backfill.
   // Does NOT destruct any elements.
   template<typename VecT>
   inline void compact(VecT* vec, S32 idx = -1, S32 n = 1)
   {
      if (!vec) return;
      using T = typename VectorTraits<VecT>::value_type;
      using Traits = VectorTraits<VecT>;
      U32 len = vec->size();
      U32 start = (idx >= 0) ? static_cast<U32>(idx) : 0;
      U32 count = (n < 1) ? (len - start) : static_cast<U32>(n);
      if (count == 0 || start >= len || start + count > len) return;
      T* arr = vec->array();

      U32 tail = len - (start + count);
      if (tail > 0)
      {
         if constexpr (std::is_trivially_copyable<T>::value)
         {
            dMemmove(&arr[start], &arr[start + count], tail * sizeof(T));
            // Reset tail region to default value
            std::fill(arr + (start + tail), arr + (start + tail + count), T());
         }
         else if constexpr (std::is_default_constructible<T>::value)
         {
            for (U32 i = 0; i < tail; ++i)
               arr[start + i] = std::move(arr[start + count + i]);
            // Reset tail region to default value
            for (U32 i = start + tail; i < start + tail + count; ++i)
               constructInPlace(&arr[i]);
         }
         // else: do nothing, not default-constructible or not assignable
      }

      if constexpr (Traits::COUNT == 0)
      {
         // Dynamic vector: update size
         vec->setElementCount(len - count);
      }
      else
      {
         // Fixed-size: backfill tail
         for (U32 i = len - count; i < len; ++i)
            constructInPlace(&arr[i]);
      }
   }

   // Destroys elements in a vector, then compacts.
   // Destructs elements in range, then calls compact to move and update size/backfill.
   template<typename VecT>
   inline void destroy(VecT* vec, S32 idx = -1, S32 n = 1)
   {
      if (!vec) return;
      U32 len = vec->size();
      U32 start = (idx >= 0) ? static_cast<U32>(idx) : 0;
      U32 count = (n < 1) ? (len - start) : static_cast<U32>(n);
      if (count == 0 || start >= len || start + count > len) return;
      using T = typename VectorTraits<VecT>::value_type;
      T* arr = vec->array();

      for (U32 i = 0; i < count; ++i)
      {
         if (arr && (start + i) < len)
         {
            destructInPlace(&arr[start + i]);
         }
         vec->setElementCount(len - count);
      }
   }

   // Removes elements matching a predicate
   // Dynamic vectors: compacts and shrinks.
   // Fixed-size vectors: destroys and backfills each matching element with type default.
   template<typename T, U32 COUNT, typename Allocator, typename Func>
   inline void removeIf(Vector<T, COUNT, Allocator>* vec, Func fn, U32 offset = 0, U32 n = 0)
   {
      if (!vec) return;
      U32 len = vec->size();
      if (offset >= len) return;
      U32 end = (n == 0) ? len : getMin(len, offset + n);
      if (end <= offset) return;
      T* arr = vec->array();
      if constexpr (COUNT == 0) {
         U32 write = offset;
         for (U32 read = offset; read < end; ++read)
            if (!fn(arr[read])) {
               if (write != read) arr[write] = std::move(arr[read]);
               ++write;
            }
         VectorHelpers::destroy(vec, write, len - write);
         vec->setSize(write);
      }
      else {
         // Compact and backfill using destroy for fixed-size
         U32 write = offset;
         for (U32 read = offset; read < end; ++read)
            if (!fn(arr[read])) {
               if (write != read) arr[write] = std::move(arr[read]);
               ++write;
            }
         VectorHelpers::destroy(vec, write, len - write);
      }
   }

   // Counts elements matching a predicate.
   template<typename T, U32 COUNT, typename Allocator, typename Func>
   inline U32 countIf(const Vector<T, COUNT, Allocator>* vec, Func fn)
   {
      if (!vec) return 0;
      U32 len = vec->size();
      if (len == 0) return 0;
      U32 n = 0;
      const T* arr = vec->array();
      for (U32 i = 0; i < len; ++i)
         if (fn(arr[i])) ++n;
      return n;
   }

   /// Returns true if any element matches the predicate.
   template<typename T, U32 COUNT, typename Allocator, typename Func>
   inline bool anyOf(const Vector<T, COUNT, Allocator>* vec, Func fn)
   {
      if (!vec) return false;
      U32 len = vec->size();
      if (len == 0) return false;
      const T* arr = vec->array();
      for (U32 i = 0; i < len; ++i)
         if (fn(arr[i])) return true;
      return false;
   }

   /// Returns true if all elements match the predicate.
   template<typename T, U32 COUNT, typename Allocator, typename Func>
   inline bool allOf(const Vector<T, COUNT, Allocator>* vec, Func fn)
   {
      if (!vec) return false;
      U32 len = vec->size();
      if (len == 0) return false;
      const T* arr = vec->array();
      for (U32 i = 0; i < len; ++i)
         if (!fn(arr[i])) return false;
      return true;
   }

   // Copies n elements from src to dst vector.
   // Supports cross-specialization and optimized for PODs.
   template<typename TargVecT, typename SrcVecT>
   inline void copy(TargVecT* targ, const SrcVecT* src, U32 n = 0, U32 targOffset = 0, U32 srcOffset = 0)
   {
      using T = typename VectorTraits<TargVecT>::value_type;
      U32 targLen = targ->size();
      U32 len = n ? n : targLen - targOffset;
      if (len == 0) return;
      if constexpr (std::is_trivially_copyable<T>::value)
         dMemmove(targ->array() + targOffset, src + srcOffset, len * sizeof(T));
      else
         for (U32 i = 0; i < len; ++i)
            targ->array()[targOffset + i] = src[srcOffset + i];
   }

   // Moves n elements from src to dst vector.
   // Supports cross-specialization and optimized for PODs.
   template<typename TargVecT, typename SrcVecT>
   inline void move(TargVecT* targ, SrcVecT* src, U32 n = 0, U32 targOffset = 0, U32 srcOffset = 0)
   {
      using T = typename VectorTraits<TargVecT>::value_type;
      constexpr U32 COUNT = VectorTraits<TargVecT>::COUNT;
      U32 targLen = targ->size();
      U32 len = n ? n : targLen - targOffset;
      if (len == 0) return;
      if constexpr (std::is_trivially_copyable<T>::value)
         dMemmove(targ->array() + targOffset, src->array() + srcOffset, len * sizeof(T));
      else if constexpr (std::is_move_assignable<T>::value && std::is_move_constructible<T>::value)
         for (U32 i = 0; i < len; ++i) {
            targ->array()[targOffset + i] = std::move(src->array()[srcOffset + i]);
            if constexpr (COUNT != 0)
               constructInPlace(&src->array()[srcOffset + i]);
            else
               src->array()[srcOffset + i] = T();
         }
      else if constexpr (std::is_copy_assignable<T>::value)
         for (U32 i = 0; i < len; ++i) {
            targ->array()[targOffset + i] = src->array()[srcOffset + i];
            if constexpr (COUNT != 0)
               constructInPlace(&src->array()[srcOffset + i]);
            else
               src->array()[srcOffset + i] = T();
         }
      else
         static_assert(std::is_copy_assignable<T>::value || std::is_move_assignable<T>::value,
            "VectorHelpers::move: T must be move- or copy-assignable.");
   }

   // Fills n elements starting at offset with value.
   template<typename VecT>
   inline void fill(VecT* vec, const typename VectorTraits<VecT>::value_type& val, U32 n = 0, U32 offset = 0)
   {
      using Traits = VectorTraits<VecT>;
      using T = typename Traits::value_type;
      U32 len = vec->size();
      if (n == 0) n = len - offset;
      if (offset >= len || n == 0) return;
      if constexpr (std::is_trivially_copyable<T>::value) {
         if constexpr (std::is_integral<T>::value || std::is_floating_point<T>::value || std::is_pointer<T>::value) {
            if (val == T()) {
               dMemset(vec->array() + offset, 0, n * sizeof(T));
               return;
            }
         }
         for (U32 i = 0; i < n; ++i)
            vec->array()[offset + i] = val;
      }
      else if constexpr (std::is_copy_assignable<T>::value)
         for (U32 i = 0; i < n; ++i)
            vec->array()[offset + i] = val;
      // else: not assignable, do nothing
   }

   // Assigns n elements from src to targ vector, handling overlap for non-PODs.
   template<typename TargVecT, typename SrcVecT>
   inline void assign(TargVecT* targ, const SrcVecT* src, U32 n = 0, U32 targOffset = 0, U32 srcOffset = 0)
   {
      using Traits = VectorTraits<TargVecT>;
      using T = typename Traits::value_type;
      constexpr bool isPod = std::is_trivially_copyable<T>::value;
      U32 targLen = targ->size(), srcLen = src->size();
      if (n == 0 || targOffset + n > targLen || srcOffset + n > srcLen)
         n = getMin(targLen - targOffset, srcLen - srcOffset);
      if constexpr (Traits::COUNT == 0)
         if (targOffset + n > targ->elementCount())
            targ->setSize(targOffset + n);
      if (n == 0) return;
      if constexpr (isPod)
         dMemmove(targ->array() + targOffset, src->array() + srcOffset, n * sizeof(T));
      else if constexpr (std::is_copy_assignable<T>::value) {
         if (targ == src && std::abs((int)targOffset - (int)srcOffset) < (int)n) {
            std::unique_ptr<T[]> temp(new T[n]);
            toBuffer(src, temp.get(), n, srcOffset);
            fromBuffer(targ, temp.get(), n, targOffset);
         }
         else {
            fromBuffer(targ, src->array() + srcOffset, n, targOffset);
         }
      }
      // else: not copy-assignable, do nothing
   }

   // Swaps n elements between two ranges in one or two vectors.
   template<typename VecT, typename OtherVecT>
   inline void swap(VecT* src, U32 srcOffset, U32 targOffset, U32 n = 0, OtherVecT* targ = NULL)
   {
      using T = typename VectorTraits<VecT>::value_type;
      U32 srcLen = src->size(), targLen = targ ? targ->size() : srcLen;
      U32 len = (n == 0) ? getMin(srcLen - srcOffset, targLen - targOffset) : n;
      T* srcArr = src->array();
      T* targArr = targ ? targ->array() : src->array();
      if constexpr (std::is_move_constructible<T>::value && std::is_move_assignable<T>::value) {
         for (U32 i = 0; i < len; ++i)
            std::swap(srcArr[srcOffset + i], targArr[targOffset + i]);
      }
      else if constexpr (std::is_copy_constructible<T>::value && std::is_copy_assignable<T>::value) {
         // Fallback: use a temp buffer
         std::unique_ptr<T[]> temp(new T[len]);
         for (U32 i = 0; i < len; ++i)
            temp[i] = srcArr[srcOffset + i];
         for (U32 i = 0; i < len; ++i)
            srcArr[srcOffset + i] = targArr[targOffset + i];
         for (U32 i = 0; i < len; ++i)
            targArr[targOffset + i] = temp[i];
      }
      // else: do nothing, not swappable
   }

   // Reverses the order of elements in the vector or a range.
   template<typename VecT>
   inline void reverse(VecT* vec, U32 n = 0, U32 offset = 0)
   {
      using T = typename VectorTraits<VecT>::value_type;
      U32 len = vec->size();
      if (offset >= len) return;
      if (n == 0) n = len - offset;
      if (n < 2) return;
      T* arr = vec->array();
      if constexpr (std::is_move_constructible<T>::value && std::is_move_assignable<T>::value) {
         U32 i = offset, j = offset + n - 1;
         while (i < j) {
            std::swap(arr[i], arr[j]);
            ++i; --j;
         }
      }
      else if constexpr (std::is_copy_constructible<T>::value && std::is_copy_assignable<T>::value) {
         // Fallback: use a temp buffer
         std::unique_ptr<T[]> temp(new T[n]);
         for (U32 i = 0; i < n; ++i)
            temp[i] = arr[offset + n - 1 - i];
         for (U32 i = 0; i < n; ++i)
            arr[offset + i] = temp[i];
      }
      // else: do nothing, not reversible
   }

   // Compares a range of elements between two vectors.
   template<typename VecT, typename OtherVecT>
   inline bool compare(const VecT* src, const OtherVecT* targ, U32 n = 0, U32 srcOffset = 0, U32 targOffset = 0)
   {
      U32 srcLen = src->size(), targLen = targ->size();
      if (srcOffset >= srcLen || targOffset >= targLen) return false;
      if (n == 0) n = getMin(srcLen - srcOffset, targLen - targOffset);
      auto arr1 = src->array(), arr2 = targ->array();
      for (U32 i = 0; i < n; ++i)
         if (!(arr1[srcOffset + i] == arr2[targOffset + i])) return false;
      return true;
   }

   // Finds the index of a value in a vector or range.
   template<typename VecT>
   inline S32 find(const VecT* vec, U32 n, const typename VecT::value_type& value, U32 offset = 0)
   {
      U32 len = vec->size();
      if (offset >= len) return -1;
      if (n <= 0) n = len - offset; //consider n=0 or n=-1 as "search to end"
      auto arr = vec->array();
      for (U32 i = 0; i < n; ++i)
         if (arr[offset + i] == value) return static_cast<S32>(offset + i);
      return -1;
   }

   // Clears or resets a single element at a given index.
   template<typename VecT>
   inline void clearElement(VecT* vec, U32 idx)
   {
      using T = typename VecT::value_type;
      U32 len = vec->size();
      if (idx >= len) return;
      if constexpr (std::is_trivially_copyable<T>::value)
         std::fill(vec->array() + idx, vec->array() + idx + 1, T());
      else if constexpr (std::is_default_constructible<T>::value && std::is_copy_assignable<T>::value)
         vec->array()[idx] = T();
      // else: do nothing, not default-constructible or not assignable
   }

   template<typename VecT>
   inline void moveWithin(VecT* vec, typename VecT::value_type* src, U32 n, U32 destOffset)
   {
      using T = typename VectorTraits<VecT>::value_type;
      if (!vec || !src || n == 0) return;
      T* arr = vec->array();
      if constexpr (std::is_trivially_copyable<T>::value) {
         dMemmove(arr + destOffset, src, n * sizeof(T));
      }
      else if (arr + destOffset > src && arr + destOffset < src + n) {
         for (S32 i = n - 1; i >= 0; --i)
            arr[destOffset + i] = std::move(src[i]);
      }
      else {
         for (U32 i = 0; i < n; ++i)
            arr[destOffset + i] = std::move(src[i]);
      }
   }

   template<typename VecT>
   inline typename VectorTraits<VecT>::value_type* data(VecT* vec)
   {
      return vec ? vec->array() : NULL;
   }

   template<typename VecT>
   inline const typename VectorTraits<VecT>::value_type* data(const VecT* vec)
   {
      return vec ? vec->array() : NULL;
   }

}

// =============================================================================
/// A dynamic array template class.
///
/// The vector grows as you insert or append
/// elements.  Insertion is fastest at the end of the array.  Resizing
/// of the array can be avoided by pre-allocating space using the
/// reserve() method.
///
/// @nosubgrouping
template<typename T, U32 COUNT = 0, typename Allocator = CustomAllocator<T, COUNT>>
class Vector
{
   friend class VectorFieldEngineExport;
protected:
   mutable typename Allocator::State mState;
   T* mArray;        ///< Pointer to the Vector elements.

#ifdef TORQUE_DEBUG_GUARD
   const char* mFileAssociation;
   U32 mLineAssociation;
#endif

   bool  resize(U32); // resizes, and does construction/destruction as apropriate
   void destroy(U32 start, U32 end);   ///< Destructs elements from <i>start</i> to <i>end-1</i>
   void  construct(U32 start, U32 end); ///< Constructs elements from <i>start</i> to <i>end-1</i>
   void construct(U32 start, U32 end, const T* array);

public:
   /// @name Constructors/Destructor
   /// @{
   void zeroState();
   /// Constructs a vector with an optional initial size.
   Vector(const U32 initialSize = 0);
   Vector(const U32 initialSize, const char* fileName, const U32 lineNum);
   Vector(const char* fileName, const U32 lineNum);
   Vector(const Vector&);
   ~Vector();

   /// allocator state access
   typename Allocator::State& state() { return mState; }
   const typename Allocator::State& state() const { return mState; }

#ifdef TORQUE_DEBUG_GUARD
   void setFileAssociation(const char* file, const U32 line);
#endif

   /// @name STL interface
   /// @{

   typedef T        value_type;
   typedef T& reference;
   typedef const T& const_reference;
   typedef T* iterator;
   typedef const T* const_iterator;
   typedef S32      difference_type;
   typedef U32      size_type;
   typedef difference_type(QSORT_CALLBACK* compare_func)(const T* a, const T* b);

   Vector& operator=(const Vector& p);

   iterator       begin();
   const_iterator begin() const;
   iterator       end();
   const_iterator end() const;

   S32 size() const;
   bool empty() const;
   bool contains(const T&) const;

   void insert(iterator, const T&);
   void erase(iterator);

   T& front();
   const T& front() const;
   T& back();
   const T& back() const;

   void push_front(const T&);
   void push_back(const T&);
   U32 push_front_unique(const T&);
   U32 push_back_unique(const T&);
   S32 find_next(const T&, U32 start = 0) const;
   void pop_front();
   void pop_back();

   T& operator[](U32);
   const T& operator[](U32) const;
   T& operator[](S32 i) { return operator[](U32(i)); }
   const T& operator[](S32 i) const { return operator[](U32(i)); }

   void reserve(U32);
   U32 capacity() const;

   /// @}

   /// @name Extended interface
   /// @{

   U32  memSize() const;
   T* address() const;
   U32  setSize(U32);
   void increment();
   void decrement();
   void increment(U32);
   void decrement(U32);
   void insert(U32);
   void insert(U32, const T&);
   void erase(U32);
   void erase_fast(U32);
   void erase(U32 index, U32 count);
   void erase_fast(iterator);
   void clear();
   void compact();
   void sort(compare_func f);
   void fill(const T& value);

   /// Finds the first matching element and erases it.   
   /// @return Returns true if a match is found.
   bool remove(const T&);

   T& first();
   T& last();
   const T& first() const;
   const T& last() const;

   void set(void* addr, U32 sz);

   /// Appends the content of the vector to this one.
   void merge(const Vector& p);

   /// Appends the content of the array to the vector.
   ///
   /// @param addr   A pointer to the first item of the array to merge.
   /// @param count  The number of elements in the array to merge.
   ///
   void merge(const T* addr, U32 count);

   // Reverses the order of elements.
   void reverse();

   /// @}

   // Modern/extra methods (from tVector.h, not in original, but keep at end)
   void insert(const T* src, U32 count, U32 idx);
   void fill(const T& value, U32 count);
   void fill(const T& value, U32 count, U32 offset);

   template<typename Func>
   void removeIf(Func pred);

   template<typename Func>
   void forEach(Func fn);

   template<typename Func>
   U32 countIf(Func fn) const;

   template<typename Func>
   bool anyOf(Func fn) const;

   template<typename Func>
   bool allOf(Func fn) const;

   void reverse(U32 offset, U32 count);

   template<U32 OtherCount, typename OtherAlloc>
   void swap(Vector<T, OtherCount, OtherAlloc>& other);
   template<U32 OtherCount, typename OtherAlloc>
   void swap(Vector<T, OtherCount, OtherAlloc>& other, U32 thisOffset, U32 otherOffset, U32 count);

   template<U32 OtherCount, typename OtherAlloc>
   bool compare(const Vector<T, OtherCount, OtherAlloc>& other) const;
   template<U32 OtherCount, typename OtherAlloc>
   bool compare(const Vector<T, OtherCount, OtherAlloc>& other, U32 thisOffset, U32 otherOffset, U32 count) const;

   void copy(const T* src);

   template<typename SrcVec>
   void assign(const SrcVec* src, U32 n = 0, U32 targOffset = 0, U32 srcOffset = 0);

   template<typename SrcVec>
   void moveFrom(SrcVec& src);

   // Returns the number of elements currently in the Vector.
   inline U32 elementCount() const { return COUNT == 0 ? mState.elementCount() : COUNT; }
   // Returns the number of elements allocated for the Vector.
   inline U32 arraySize() const { return COUNT == 0 ? mState.arraySize() : COUNT; }
   // Returns pointer to the Vector elements.
   inline T* array() const { return mArray; }

   inline void setElementCount(U32 count)
   {
      AssertFatal(count >= 0, "setElementCount: can't set a negative element count!");
      AssertFatal(count <= arraySize(), "setElementCount: count exceeds array size!");
      mState.setElementCount(count);

   }
   inline void setArraySize(U32 size)
   {
      AssertFatal(size >= 0, "setElementCount: can't set a negative array size!");
      mState.setArraySize(size);
      AssertFatal(elementCount() <= arraySize(), "elementCount exceeds arraySize after setArraySize!");
   }
};

class VectorFieldEngineExport
{
public:
   template <class T>
   static EngineFieldTable::Field getArrayField()
   {
      typedef Vector<T> ThisType;
      return _FIELD(mArray, array, 1, "");
   };

   // given EngineFieldTable::Field _sFields[] = {
   // always stops at the first found NULL,
   // keep strict order of most to least likely to be used fields,
   // and put the least likely to be used ones at the end
   // see _IMPLEMENT_STRUCT and _END_IMPLEMENT_STRUCT for further details

   template <class T>
   static EngineFieldTable::Field getElementCountField()
   {
      typedef Vector<T> ThisType;
      if constexpr (VectorTraits<ThisType>::mTCount == 0)
      {
         return EngineFieldTable::Field{
            "elementCount", "", 1,
            TYPE(((ThisType*)16)->mState.mElementCount),
            static_cast<U32>(FIELDOFFSET(mState.mElementCount))
         };
      }
      else
         return { NULL }; //trash
   };
   template <class T>
   static EngineFieldTable::Field getArraySizeField()
   {
      typedef Vector<T> ThisType;

      if constexpr (VectorTraits<ThisType>::mTCount == 0)
      {
         return EngineFieldTable::Field{
            "arraySize", "", 1,
            TYPE(((ThisType*)16)->mState.mArraySize),
            static_cast<U32>(FIELDOFFSET(mState.mArraySize))
         };
      }
      else
         return { NULL };
   };
};

template<typename T, U32 COUNT, typename Allocator>
inline Vector<T, COUNT, Allocator>::~Vector()
{
   // Destroys all elements and deallocates memory.
   clear();
   if constexpr (COUNT == 0)
   {
      if (mArray)
         Allocator::deallocate(mArray);
      mArray = NULL;
   }
   mArray = NULL;
}
template<typename T, U32 COUNT, typename Allocator>
inline void Vector<T, COUNT, Allocator>::zeroState()
{
#ifdef TORQUE_DEBUG_GUARD
   mFileAssociation = NULL;
   mLineAssociation = 0;
#endif
   mArray = NULL;
   setElementCount(0);
   setArraySize(0);
   if constexpr (COUNT != 0)
   {
      mArray = Allocator::allocate(COUNT);
      construct(0, COUNT);
   }
}

template<typename T, U32 COUNT, typename Allocator>
inline Vector<T, COUNT, Allocator>::Vector(const U32 initialSize)
{
   zeroState();

#ifdef TORQUE_DEBUG_GUARD
   mFileAssociation = NULL;
   mLineAssociation = 0;
#endif
   if (initialSize)
      reserve(initialSize);
}
template<typename T, U32 COUNT, typename Allocator>
inline Vector<T, COUNT, Allocator>::Vector(const char* fileName,
   const U32   lineNum)
{
   zeroState();
#ifdef TORQUE_DEBUG_GUARD
   mFileAssociation = fileName;
   mLineAssociation = lineNum;
#else
   //   TORQUE_UNUSED(fileName);
   //   TORQUE_UNUSED(lineNum);
#endif
}

template<typename T, U32 COUNT, typename Allocator>
inline Vector<T, COUNT, Allocator>::Vector(const Vector& p)
{
   if (this == &p)
      return;
   zeroState();
#ifdef TORQUE_DEBUG_GUARD
   mFileAssociation = p.mFileAssociation;
   mLineAssociation = p.mLineAssociation;
#endif
   if constexpr (COUNT == 0)
   {
      resize(p.elementCount());
      construct(0, p.elementCount(), p.mArray);
   }
   else
   {
      construct(0, COUNT, p.mArray);
   }
}
#ifdef TORQUE_DEBUG_GUARD
template<typename T, U32 COUNT, typename Allocator>
inline void Vector<T, COUNT, Allocator>::setFileAssociation(const char* file,
   const U32   line)
{
   mFileAssociation = file;
   mLineAssociation = line;
}
#endif


template<typename T, U32 COUNT, typename Allocator>
inline void Vector<T, COUNT, Allocator>::destroy(U32 start, U32 end) // destroys from start to end-1
{
   // This check is a little generous as we can legitimately get (0,0) as
   // our parameters... so it won't detect every invalid case but it does
   // remain simple.
   AssertFatal(start <= elementCount() && end <= elementCount(), "Vector<T>::destroy - out of bounds start/end.");
   // destroys from start to end-1
   while (start < end)
      destructInPlace(&mArray[start++]);
}

template<typename T, U32 COUNT, typename Allocator>
inline void Vector<T, COUNT, Allocator>::construct(U32 start, U32 end) // allocates from start to end-1
{
   AssertFatal(start <= elementCount() && end <= elementCount(), "Vector<T>::construct - out of bounds start/end.");
   while (start < end)
      constructInPlace(&mArray[start++]);
}

template<typename T, U32 COUNT, typename Allocator>
inline void Vector<T, COUNT, Allocator>::construct(U32 start, U32 end, const T* array) // allocates from start to end-1
{
   AssertFatal(start <= elementCount() && end <= elementCount(), "Vector<T>::construct - out of bounds start/end.");
  while (start < end)
  {
     constructInPlace(&mArray[start], &array[start]);
     start++;
  }
}

template<typename T, U32 COUNT, typename Allocator>
inline U32 Vector<T, COUNT, Allocator>::memSize() const // reserved size in bytes
{
   return capacity() * sizeof(T);
}

template<typename T, U32 COUNT, typename Allocator>
inline T* Vector<T, COUNT, Allocator>::address() const
{
   return mArray;
}

template<typename T, U32 COUNT, typename Allocator>
inline U32 Vector<T, COUNT, Allocator>::setSize(U32 size)
{
   // Sets the number of elements in the vector.
   // If increasing, constructs new elements. If decreasing, destructs removed elements.
   U32 oldSize = elementCount();
   if constexpr (COUNT == 0)
   {
      if (size > oldSize)
      {
         if (size > arraySize())
            resize(size);
         setElementCount(size);
         construct(oldSize, size);
      }
      else if (size < oldSize)
      {
         destroy(size, oldSize);
         setElementCount(size);
      }
      // else, size == oldSize, do nothing
      return elementCount();
   }
   else
   {
      // For fixed-size vectors, just return the count
      return COUNT;
   }
}

template<typename T, U32 COUNT, typename Allocator>
inline void Vector<T, COUNT, Allocator>::increment()
{
   setSize(elementCount() + 1);
}

template<typename T, U32 COUNT, typename Allocator>
inline void Vector<T, COUNT, Allocator>::decrement()
{
   AssertFatal(elementCount(), "Vector<T>::decrement - cannot decrement zero-length vector.");
   setSize(elementCount() - 1);
}

template<typename T, U32 COUNT, typename Allocator>
inline void Vector<T, COUNT, Allocator>::increment(U32 delta)
{
   setSize(elementCount() + delta);
}

template<typename T, U32 COUNT, typename Allocator>
inline void Vector<T, COUNT, Allocator>::decrement(U32 delta)
{
   AssertFatal(elementCount(), "Vector<T>::decrement - cannot decrement zero-length vector.");
   // Determine new count after decrement...
   U32 newCount = (elementCount() > delta) ? elementCount() - delta : 0;
   setSize(newCount);
}

template<typename T, U32 COUNT, typename Allocator>
inline void Vector<T, COUNT, Allocator>::insert(U32 index)
{
   AssertFatal(index <= elementCount(), "Vector<T>::insert - out of bounds index.");
   if constexpr (COUNT == 0)
   {
      setSize(elementCount() + 1);
      dMemmove(&mArray[index + 1], &mArray[index], dsize_t(elementCount() - index - 1) * sizeof(value_type));
      constructInPlace(&mArray[index]);
   }
   else
   {
      /// DO RIGHT!
   }
}

template<typename T, U32 COUNT, typename Allocator>
inline void Vector<T, COUNT, Allocator>::insert(U32 index, const T& x)
{
   if constexpr (COUNT == 0)
   {

      insert(index);
      mArray[index] = x;
   }
   else
   {
      if (index < COUNT)
      {

         insert(index);
         (*this)[index] = x;
      }
   }
}

template<typename T, U32 COUNT, typename Allocator>
inline void Vector<T, COUNT, Allocator>::erase(U32 index)
{
   AssertFatal(index < elementCount(), "Vector<T>::erase - out of bounds index!");

   destructInPlace(&mArray[index]);

   if (index < (elementCount() - 1))
   {
      dMemmove(&mArray[index],
         &mArray[index + 1],
         dsize_t(elementCount() - index - 1) * sizeof(value_type));
   }
   setElementCount(elementCount() - 1);
}

template<typename T, U32 COUNT, typename Allocator>
inline bool Vector<T, COUNT, Allocator>::remove(const T& x)
{
   iterator i = begin();
   while (i != end())
   {
      if (*i == x)
      {
         erase(i);
         return true;
      }

      i++;
   }
   return false;
}

template<typename T, U32 COUNT, typename Allocator>
inline void Vector<T, COUNT, Allocator>::erase(U32 index, U32 count)
{
   AssertFatal(index < elementCount(), "Vector<T>::erase - out of bounds index!");
   AssertFatal(count > 0, "Vector<T>::erase - count must be greater than zero!");
   AssertFatal(index + count <= elementCount(), "Vector<T>::erase - out of bounds count!");
      destroy(index, index + count);

   dMemmove(&mArray[index],
      &mArray[index + count],
      dsize_t(elementCount() - index - count) * sizeof(value_type));
   setElementCount(elementCount() - count);
}

template<typename T, U32 COUNT, typename Allocator>
inline void Vector<T, COUNT, Allocator>::erase_fast(U32 index)
{
   AssertFatal(index < elementCount(), "Vector<T>::erase_fast - out of bounds index.");

   // CAUTION: this operator does NOT maintain list order
   // Copy the last element into the deleted 'hole' and decrement the
   //   size of the vector.
   destructInPlace(&mArray[index]);
   if (index != elementCount() - 1)
      mArray[index] = mArray[elementCount() - 1];
   setElementCount(elementCount() - 1);
}

template<typename T, U32 COUNT, typename Allocator>
inline bool Vector<T, COUNT, Allocator>::contains(const T& x) const
{
   const_iterator i = begin();
   while (i != end())
   {
      if (*i == x)
         return true;
      i++;
   }
   return false;
}

template<typename T, U32 COUNT, typename Allocator>
inline void Vector<T, COUNT, Allocator>::fill(const T& value)
{
   for (U32 i = 0; i < size(); ++i)
      mArray[i] = value;
}

template<typename T, U32 COUNT, typename Allocator>
inline T& Vector<T, COUNT, Allocator>::first()
{
   AssertFatal(elementCount(), "Vector<T>::first - Error, no first element of a zero sized array!");
   return mArray[0];
}

template<typename T, U32 COUNT, typename Allocator>
inline const T& Vector<T, COUNT, Allocator>::first() const
{
   AssertFatal(elementCount(), "Vector<T>::first - Error, no first element of a zero sized array! (const)");
   return mArray[0];
}

template<typename T, U32 COUNT, typename Allocator>
inline T& Vector<T, COUNT, Allocator>::last()
{
   // Returns reference to last element. Asserts if empty.
   AssertFatal(elementCount(), "Vector<T>::last - Error, no last element of a zero sized array!");
   return mArray[elementCount() - 1];
}

template<typename T, U32 COUNT, typename Allocator>
inline const T& Vector<T, COUNT, Allocator>::last() const
{
   AssertFatal(elementCount(), "Vector<T>::last - Error, no last element of a zero sized array! (const)");
   return mArray[elementCount() - 1];
}

template<typename T, U32 COUNT, typename Allocator>
inline void Vector<T, COUNT, Allocator>::clear()
{
   destroy(0, elementCount());
   setElementCount(0);
}

template<typename T, U32 COUNT, typename Allocator>
inline void Vector<T, COUNT, Allocator>::compact()
{
   resize(elementCount());
}

typedef S32(QSORT_CALLBACK* qsort_compare_func)(const void*, const void*);

template<typename T, U32 COUNT, typename Allocator>
inline void Vector<T, COUNT, Allocator>::sort(compare_func f)
{
   qsort(address(), size(), sizeof(T), (qsort_compare_func)f);
}

//-----------------------------------------------------------------------------


template<typename T, U32 COUNT, typename Allocator>
inline Vector<T, COUNT, Allocator>& Vector<T, COUNT, Allocator>::operator=(const Vector& p)
{
   if (this == &p)
      return *this;

   if (elementCount() > p.elementCount())
   {
      destroy(p.elementCount(), elementCount());
   }

   U32 count = getMin(elementCount(), p.elementCount());
   U32 i;
   for (i = 0; i < count; i++)
   {
      mArray[i] = p.mArray[i];
   }

   resize(p.elementCount());

   if (i < p.elementCount())
   {
      construct(i, p.elementCount(), p.mArray);
   }
   return *this;
}

template<typename T, U32 COUNT, typename Allocator>
inline typename Vector<T, COUNT, Allocator>::iterator Vector<T, COUNT, Allocator>::begin()
{
   return mArray;
}

template<typename T, U32 COUNT, typename Allocator>
inline typename Vector<T, COUNT, Allocator>::const_iterator Vector<T, COUNT, Allocator>::begin() const
{
   return mArray;
}

template<typename T, U32 COUNT, typename Allocator>
inline typename Vector<T, COUNT, Allocator>::iterator Vector<T, COUNT, Allocator>::end()
{
   return mArray + elementCount();
}

template<typename T, U32 COUNT, typename Allocator>
inline typename Vector<T, COUNT, Allocator>::const_iterator Vector<T, COUNT, Allocator>::end() const
{
   return mArray + elementCount();
}

template<typename T, U32 COUNT, typename Allocator>
inline S32 Vector<T, COUNT, Allocator>::size() const
{
   if constexpr (COUNT == 0)
      return (S32)elementCount();
   else
      return (S32)COUNT;
}

template<typename T, U32 COUNT, typename Allocator>
inline bool Vector<T, COUNT, Allocator>::empty() const
{
   return size() == 0;
}

template<typename T, U32 COUNT, typename Allocator>
inline void Vector<T, COUNT, Allocator>::insert(iterator p, const T& x)
{
   U32 index = (U32)(p - mArray);
   insert(index);
   mArray[index] = x;
}

template<typename T, U32 COUNT, typename Allocator>
inline void Vector<T, COUNT, Allocator>::erase(iterator q)
{
   erase(U32(q - mArray));
}

template<typename T, U32 COUNT, typename Allocator>
inline void Vector<T, COUNT, Allocator>::erase_fast(iterator q)
{
   erase_fast(U32(q - mArray));
}

template<typename T, U32 COUNT, typename Allocator>
inline typename Vector<T, COUNT, Allocator>::reference Vector<T, COUNT, Allocator>::front()
{
   return *begin();
}

template<typename T, U32 COUNT, typename Allocator>
inline typename Vector<T, COUNT, Allocator>::const_reference Vector<T, COUNT, Allocator>::front() const
{
   return *begin();
}

template<typename T, U32 COUNT, typename Allocator>
inline typename Vector<T, COUNT, Allocator>::reference Vector<T, COUNT, Allocator>::back()
{
   AssertFatal(elementCount(), "Vector<T>::back - cannot access last element of zero-length vector.");
   return *(end() - 1);
}

template<typename T, U32 COUNT, typename Allocator>
inline typename Vector<T, COUNT, Allocator>::const_reference Vector<T, COUNT, Allocator>::back() const
{
   AssertFatal(elementCount(), "Vector<T>::back - cannot access last element of zero-length vector.");
   return *(end() - 1);
}

template<typename T, U32 COUNT, typename Allocator>
inline void Vector<T, COUNT, Allocator>::push_front(const T& x)
{
   insert(0);
   mArray[0] = x;
}

template<typename T, U32 COUNT, typename Allocator>
inline void Vector<T, COUNT, Allocator>::push_back(const T& x)
{
   increment();
   mArray[elementCount() - 1] = x;
}

template<typename T, U32 COUNT, typename Allocator>
inline U32 Vector<T, COUNT, Allocator>::push_front_unique(const T& x)
{
   S32 index = find_next(x);
   if (index == -1)
   {
      index = 0;
      insert(index);
      mArray[index] = x;
   }
   return index;
}

template<typename T, U32 COUNT, typename Allocator>
inline U32 Vector<T, COUNT, Allocator>::push_back_unique(const T& x)
{
   S32 index = find_next(x);
   if (index == -1)
   {
      increment();
      index = elementCount() - 1;
      mArray[index] = x;
   }
   return index;
}

template<typename T, U32 COUNT, typename Allocator>
inline S32 Vector<T, COUNT, Allocator>::find_next(const T& x, U32 start) const
{
   S32 index = -1;
   if (start < elementCount())
   {
      for (U32 i = start; i < elementCount(); i++)
      {
         if (mArray[i] == x)
         {
            index = i;
            break;
         }
      }
   }
   return index;
}

template<typename T, U32 COUNT, typename Allocator>
inline void Vector<T, COUNT, Allocator>::pop_front()
{
   AssertFatal(elementCount(), "Vector<T>::pop_front - cannot pop the front of a zero-length vector.");
   erase(U32(0));
}

template<typename T, U32 COUNT, typename Allocator>
inline void Vector<T, COUNT, Allocator>::pop_back()
{
   AssertFatal(elementCount(), "Vector<T>::pop_back - cannot pop the back of a zero-length vector.");
   decrement();
}

template<typename T, U32 COUNT, typename Allocator>
inline T& Vector<T, COUNT, Allocator>::operator[](U32 index)
{
   AssertFatal(mArray != NULL, "Vector::operator[] - mArray is NULL");
   AssertFatal(index < elementCount(), avar("Vector<T>::operator[%i/%i] - out of bounds array access!", index,elementCount()));
   return mArray[index];
}

template<typename T, U32 COUNT, typename Allocator>
inline const T& Vector<T, COUNT, Allocator>::operator[](U32 index) const
{
   AssertFatal(index < elementCount(), avar("Vector<T>::operator[%i/%i] - out of bounds array access!", index,elementCount()));
   return mArray[index];
}

template<typename T, U32 COUNT, typename Allocator>
inline void Vector<T, COUNT, Allocator>::reserve(U32 size)
{
   if constexpr (COUNT == 0)
   {
      if (size <= arraySize())
         return;

      const U32 ec = elementCount();
      if (resize(size))
         setElementCount(ec);
   }
}

template<typename T, U32 COUNT, typename Allocator>
inline U32 Vector<T, COUNT, Allocator>::capacity() const
{
   if constexpr (COUNT == 0)
      return arraySize();
   else
      return COUNT;
}

template<typename T, U32 COUNT, typename Allocator>
inline void Vector<T, COUNT, Allocator>::set(void* addr, U32 sz)
{
   if (!addr)
      sz = 0;

   setSize(sz);

   if (addr && sz > 0)
      dMemcpy(address(), addr, sz * sizeof(T));
}

//-----------------------------------------------------------------------------

template<typename T, U32 COUNT, typename Allocator>
inline bool Vector<T, COUNT, Allocator>::resize(U32 ecount)
{
   bool ret = false;
   U32 tArraySize = arraySize();
   U32 tElementCount = elementCount();
#ifdef TORQUE_DEBUG_GUARD
   ret = VectorResize(&tArraySize, &tElementCount, (void**)&mArray, ecount, sizeof(T),
      mFileAssociation, mLineAssociation);
#else
   ret = VectorResize(&tArraySize, &tElementCount, (void**)&mArray, ecount, sizeof(T));
#endif
   setArraySize(tArraySize);
   setElementCount(tElementCount);
   // No construct/destroy here for COUNT == 0
   // For fixed-size vectors, we may still want to backfill
   if constexpr (COUNT > 0) {
      AssertFatal(tElementCount <= tArraySize, "Vector::resize - elementCount exceeds arraySize after resize");
      AssertFatal(mArray != NULL || ecount == 0, "Vector::resize - mArray should be valid or NULL if ecount == 0");
      for (U32 i = ecount; i < arraySize(); ++i)
         constructInPlace(&mArray[i]);
   }
   else
   {
      if (ecount == 0)
         mArray = NULL;
   }
   return ret;
}

template<typename T, U32 COUNT, typename Allocator>
inline void Vector<T, COUNT, Allocator>::merge(const Vector& p)
{
   if (!p.size())
      return;
   const U32 oldSize = elementCount();
   const U32 newSize = oldSize + p.size();
   if (newSize > arraySize())
      resize(newSize);
   T* dest = mArray + oldSize;
   const T* src = p.mArray;
   while (dest < mArray + newSize)
      constructInPlace(dest++, src++);
   setElementCount(newSize);
}

template<typename T, U32 COUNT, typename Allocator>
inline void Vector<T, COUNT, Allocator>::merge(const T* addr, U32 count)
{
   const U32 oldSize = elementCount();
   const U32 newSize = oldSize + count;
   if (newSize > arraySize())
      resize(newSize);
   T* dest = mArray + oldSize;
   while (dest < mArray + newSize)
      constructInPlace(dest++, addr++);
   setElementCount(newSize);
}

template<typename T, U32 COUNT, typename Allocator>
inline void Vector<T, COUNT, Allocator>::reverse()
{
   // Reverses the order of elements in the vector.
   for (U32 i = 0, j = size(); (i != j) && (i != --j); ++i)
      std::swap(mArray[i], mArray[j]);
}

template<typename T, U32 COUNT, typename Allocator>
inline void Vector<T, COUNT, Allocator>::insert(const T* src, U32 count, U32 idx)
{
   // Inserts a block of elements at index.
   if (!src || count == 0)
      return;
   if constexpr (COUNT == 0)
   {
      auto* self = static_cast<Vector<T, 0, Allocator>*>(this);
      AssertFatal(idx <= self->elementCount(), "Vector::insert - out of bounds index.");
      self->setSize(self->elementCount() + count);
      U32 moveCount = self->elementCount() - idx - count;
      if (moveCount > 0)
         dMemmove(&self->mArray[idx + count], &self->mArray[idx], moveCount * sizeof(T));
      for (U32 i = 0; i < count; ++i)
         self->mArray[idx + i] = src[i];
   }
   else
   {
      AssertFatal(idx < COUNT, "Vector::insert - out of bounds index.");
      U32 moveCount = COUNT - idx - count;
      if (moveCount > 0)
         dMemmove(&mArray[idx + count], &mArray[idx], moveCount * sizeof(T));
      for (U32 i = 0; i < count; ++i)
         mArray[idx + i] = src[i];
   }
}

template<typename T, U32 COUNT, typename Allocator>
inline void Vector<T, COUNT, Allocator>::fill(const T& value, U32 count)
{
   // Fills first 'count' elements with value.
   U32 n = (count > size()) ? size() : count;
   for (U32 i = 0; i < n; ++i)
      mArray[i] = value;
}

template<typename T, U32 COUNT, typename Allocator>
inline void Vector<T, COUNT, Allocator>::fill(const T& value, U32 count, U32 offset)
{
   // Fills 'count' elements starting at 'offset' with value.
   U32 start = offset;
   U32 n = (count == (U32)-1) ? (this->size() - start) : count;
   U32 limit = this->size();
   if (start >= limit)
      return;
   if (start + n > limit)
      n = limit - start;
   for (U32 i = 0; i < n; ++i)
      mArray[start + i] = value;
}


template<typename T, U32 COUNT, typename Allocator>
inline void Vector<T, COUNT, Allocator>::copy(const T* src)
{
   // Copies data from an external array to the vector.
   if (!src || size() == 0)
      return;
   for (U32 i = 0; i < size(); ++i)
      mArray[i] = src[i];
}

template<typename T, U32 COUNT, typename Allocator>
template<typename SrcVec>
inline void Vector<T, COUNT, Allocator>::moveFrom(SrcVec& src)
{
   // Moves data from another vector, leaving it in a valid but unspecified state.
   U32 n = mMin(COUNT > 0 ? COUNT : this->arraySize(), src.size());
   for (U32 i = 0; i < n; ++i)
      mArray[i] = std::move(src.mArray[i]);
   src.clear();
}


//// review these!

template<typename T, U32 COUNT, typename Allocator>
template<typename Func>
inline U32 Vector<T, COUNT, Allocator>::countIf(Func fn) const
{
   // Counts elements matching a predicate.
   U32 n = 0;
   for (U32 i = 0; i < size(); ++i)
      if (fn(mArray[i]))
         ++n;
   return n;
}

template<typename T, U32 COUNT, typename Allocator>
template<typename Func>
inline bool Vector<T, COUNT, Allocator>::anyOf(Func fn) const
{
   // Returns true if any element matches the predicate.
   for (U32 i = 0; i < size(); ++i)
      if (fn(mArray[i]))
         return true;
}

template<typename T, U32 COUNT, typename Allocator>
template<typename Func>
inline bool Vector<T, COUNT, Allocator>::allOf(Func fn) const
{
   // Returns true if all elements match the predicate.
   for (U32 i = 0; i < size(); ++i)
      if (!fn(mArray[i]))
         return false;
   return true;
}

// brief Assigns elements from another vector to this vector.
// // Copies up to n elements from the source vector (starting at srcOffset) to this vector (starting at targOffset).
// Handles overlapping ranges safely and resizes this vector if needed (for dynamic vectors).
// For fixed-size vectors, only copies up to the available capacity.
template<typename T, U32 COUNT, typename Allocator>
template<typename SrcVec>
inline void Vector<T, COUNT, Allocator>::assign(const SrcVec* src, U32 n, U32 targOffset, U32 srcOffset)
{
   U32 targLen = this->size();
   U32 srcLen = src->size();
   if (n == 0 || targOffset + n > targLen || srcOffset + n > srcLen)
      n = mMin(targLen - targOffset, srcLen - srcOffset);
   if constexpr (COUNT == 0)
      if (targOffset + n > this->elementCount())
         this->setSize(targOffset + n);
   if (n == 0)
      return;
   for (U32 i = 0; i < n; ++i)
      this->mArray[targOffset + i] = src->mArray[srcOffset + i];
}




template<typename T, U32 COUNT, typename Allocator>
inline void Vector<T, COUNT, Allocator>::reverse(U32 offset, U32 count)
{
   // Reverses the order of a range of elements.
   U32 limit = this->size();
   if (offset >= limit || count < 2)
      return;
   if (offset + count > limit)
      count = limit - offset;
   VectorHelpers::reverse(this, count, offset);
}

template<typename T, U32 COUNT, typename Allocator>
template<U32 OtherCount, typename OtherAlloc>
void Vector<T, COUNT, Allocator>::swap(Vector<T, OtherCount, OtherAlloc>& other)
{
   // Swaps elements with another vector.
   U32 n = mMin(this->size(), other.size());
   for (U32 i = 0; i < n; ++i)
      std::swap(this->mArray[i], other.mArray[i]);
}

template<typename T, U32 COUNT, typename Allocator>
template<U32 OtherCount, typename OtherAlloc>
void Vector<T, COUNT, Allocator>::swap(Vector<T, OtherCount, OtherAlloc>& other, U32 thisOffset, U32 otherOffset, U32 count)
{
   // Swaps a range of elements with another vector.
   U32 thisLimit = this->size();
   U32 otherLimit = other.size();
   U32 n = count;
   if (thisOffset >= thisLimit || otherOffset >= otherLimit)
      return;
   if (thisOffset + n > thisLimit)
      n = thisLimit - thisOffset;
   if (otherOffset + n > otherLimit)
      n = otherLimit - otherOffset;
   for (U32 i = 0; i < n; ++i)
      std::swap(this->mArray[thisOffset + i], other.mArray[otherOffset + i]);
}

template<typename T, U32 COUNT, typename Allocator>
template<typename Func>
inline void Vector<T, COUNT, Allocator>::forEach(Func fn)
{
   // Applies a function to each element in the vector.
   for (U32 i = 0; i < size(); ++i)
      fn(mArray[i]);
}

template<typename T, U32 COUNT, typename Allocator>
template<typename Func>
inline void Vector<T, COUNT, Allocator>::removeIf(Func fn)
{
   // Removes elements matching a predicate.
   U32 write = 0;
   for (U32 read = 0; read < elementCount(); ++read)
   {
      if (!fn(mArray[read]))
      {
         if (write != read)
            mArray[write] = std::move(mArray[read]);
         ++write;
      }
      else
         destructInPlace(&mArray[read]);
   }
   setElementCount(write);
}

template<typename T, U32 COUNT, typename Allocator>
template<U32 OtherCount, typename OtherAlloc>
inline bool Vector<T, COUNT, Allocator>::compare(const Vector<T, OtherCount, OtherAlloc>& other) const
{
   U32 n = mMin(this->size(), other.size());
   return VectorHelpers::compare(this, &other, n, 0, 0);
}

template<typename T, U32 COUNT, typename Allocator>
template<U32 OtherCount, typename OtherAlloc>
inline bool Vector<T, COUNT, Allocator>::compare(const Vector<T, OtherCount, OtherAlloc>& other, U32 thisOffset, U32 otherOffset, U32 count) const
{
   U32 thisLimit = this->size();
   U32 otherLimit = other.size();
   U32 n = count;
   if (thisOffset >= thisLimit || otherOffset >= otherLimit)
      return false;
   if (thisOffset + n > thisLimit)
      n = thisLimit - thisOffset;
   if (otherOffset + n > otherLimit)
      n = otherLimit - otherOffset;
   return VectorHelpers::compare(this, &other, n, thisOffset, otherOffset);
}

template<typename T, U32 COUNT, typename Allocator>
inline Vector<T, COUNT, Allocator>::Vector(const U32 initialSize, const char* fileName, const U32 lineNum)
{
   zeroState();
#ifdef TORQUE_DEBUG_GUARD
   mFileAssociation = fileName;
   mLineAssociation = lineNum;
#else
   //   TORQUE_UNUSED(fileName);
   //   TORQUE_UNUSED(lineNum);
#endif
   if constexpr (COUNT == 0)
   {
      if (initialSize)
         reserve(initialSize);
   }
}

//-----------------------------------------------------------------------------
/// Template for vectors of pointers.
template <class T>
class VectorPtr : public Vector<void*, 0>
{
   /// @deprecated Disallowed.
   VectorPtr(const VectorPtr&);  // Disallowed

public:
   VectorPtr();
   VectorPtr(const char* fileName, const U32 lineNum);

   /// @name STL interface
   /// @{

   typedef T        value_type;
   typedef T& reference;
   typedef const T& const_reference;
   typedef T* iterator;
   typedef const T* const_iterator;
   typedef U32      difference_type;
   typedef U32      size_type;

   iterator       begin();
   const_iterator begin() const;
   iterator       end();
   const_iterator end() const;

   void insert(iterator, const T&);
   void insert(S32 idx) { Parent::insert(idx); }
   void erase(iterator);

   T& front();
   const T& front() const;
   T& back();
   const T& back() const;
   void     push_front(const T&);
   void     push_back(const T&);

   T& operator[](U32);
   const T& operator[](U32) const;

   /// @}

   /// @name Extended interface
   /// @{

   typedef Vector<void*, 0> Parent;
   T& first();
   T& last();
   const T& first() const;
   const T& last() const;
   void erase_fast(U32);
   void erase_fast(iterator);

   /// @}
};


//-----------------------------------------------------------------------------
template <class T> inline VectorPtr<T>::VectorPtr()
{
   //
}

template <class T> inline VectorPtr<T>::VectorPtr(const char* fileName,
   const U32   lineNum)
   : Vector<void*>(fileName, lineNum)
{
   //
}

template <class T> inline T& VectorPtr<T>::first()
{
   return (T&)Parent::first();
}

template <class T> inline const T& VectorPtr<T>::first() const
{
   return (const T)Parent::first();
}

template <class T> inline T& VectorPtr<T>::last()
{
   return (T&)Parent::last();
}

template <class T> inline const T& VectorPtr<T>::last() const
{
   return (const T&)Parent::last();
}

template <class T> inline typename VectorPtr<T>::iterator VectorPtr<T>::begin()
{
   return (iterator)Parent::begin();
}

template <class T> inline typename VectorPtr<T>::const_iterator VectorPtr<T>::begin() const
{
   return (const_iterator)Parent::begin();
}

template <class T> inline typename VectorPtr<T>::iterator VectorPtr<T>::end()
{
   return (iterator)Parent::end();
}

template <class T> inline typename VectorPtr<T>::const_iterator VectorPtr<T>::end() const
{
   return (const_iterator)Parent::end();
}

template <class T> inline void VectorPtr<T>::insert(iterator i, const T& x)
{
   Parent::insert((Parent::iterator)i, (Parent::reference)x);
}

template <class T> inline void VectorPtr<T>::erase(iterator i)
{
   Parent::erase((Parent::iterator)i);
}

template <class T> inline void VectorPtr<T>::erase_fast(U32 index)
{
   AssertFatal(index < elementCount(), "VectorPtr<T>::erase_fast - out of bounds index.");

   // CAUTION: this operator does not maintain list order
   // Copy the last element into the deleted 'hole' and decrement the
   //   size of the vector.
   // Assert: index >= 0 && index < elementCount()
   if (index < (elementCount() - 1))
      mArray[index] = mArray[elementCount() - 1];
   decrement();
}

template <class T> inline void VectorPtr<T>::erase_fast(iterator i)
{
   erase_fast(U32(i - iterator(mArray)));
}

template <class T> inline T& VectorPtr<T>::front()
{
   return *begin();
}

template <class T> inline const T& VectorPtr<T>::front() const
{
   return *begin();
}

template <class T> inline T& VectorPtr<T>::back()
{
   AssertFatal(elementCount(), "Vector<T>::back - cannot access last element of zero-length vector.");
   return *(end() - 1);
}

template <class T> inline const T& VectorPtr<T>::back() const
{
   AssertFatal(elementCount(), "Vector<T>::back - cannot access last element of zero-length vector.");
   return *(end() - 1);
}

template <class T> inline void VectorPtr<T>::push_front(const T& x)
{
   Parent::push_front((Parent::const_reference)x);
}

template <class T> inline void VectorPtr<T>::push_back(const T& x)
{
   Parent::push_back((Parent::const_reference)x);
}

template <class T> inline T& VectorPtr<T>::operator[](U32 index)
{
   return (T&)Parent::operator[](index);
}

template <class T> inline const T& VectorPtr<T>::operator[](U32 index) const
{
   return (const T&)Parent::operator[](index);
}
//------------------------------------------------------------------------------
template<typename T, U32 COUNT> struct CustomAllocator;
template<typename T, U32 COUNT, typename Allocator> class Vector;
template <class T> class VectorSet : public Vector<T>
{
public:
   void insert(T dat)
   {
      if (VectorHelpers::find(this, -1, dat) == -1)
         push_back(dat);
   }
};



// Include vector specializations
#ifndef _TVECTORSPEC_H_
#include "core/util/tVectorSpecializations.h"
#endif

#endif //_TVECTOR_H_
