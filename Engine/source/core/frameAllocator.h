//-----------------------------------------------------------------------------
// Copyright (C) 2023-2024 tgemit contributors.
// See AUTHORS file and git repository for contributor information.
//
// SPDX-License-Identifier: MIT
//-----------------------------------------------------------------------------

#ifndef _FRAMEALLOCATOR_H_
#define _FRAMEALLOCATOR_H_

#ifndef _PLATFORM_H_
#include "platform/platform.h"
#endif

/// Implements an buffer which allocates data based on the alignment of type T.
/// 
/// Example usage:
///
/// @code
///   AlignedBufferAllocator<U32> alloc32;
///   alloc32.initWithElements(new U32[10], 10);
///
///   void* ptr = alloc32.allocBytes(2);
///   // Reset back to start
///   alloc32.setPosition(0);
/// @endcode
/// 
template<typename T> class AlignedBufferAllocator
{
protected:
   T* mBuffer;
   U32 mHighWaterMark;
   U32 mWaterMark;

public:

   typedef T ValueType;

   AlignedBufferAllocator() : mBuffer(NULL), mHighWaterMark(0), mWaterMark(0)
   {
   }

   /// Inits allocator based on a ptr to a memory block of size numElements * sizeof(T)
   inline void initWithElements(T* ptr, U32 numElements)
   {
      mBuffer = ptr;
      mHighWaterMark = numElements;
      mWaterMark = 0;
   }

   /// Inits allocator based on a ptr to a memory block of size bytes
   inline void initWithBytes(T* ptr, dsize_t bytes)
   {
      mBuffer = ptr;
      mHighWaterMark = (U32)(calcMaxElementSize(bytes));
      mWaterMark = 0;
   }

   /// Allocs numBytes worth of elements
   inline T* allocBytes(const size_t numBytes)
   {
      T* ptr = &mBuffer[mWaterMark];
      size_t numElements = calcRequiredElementSize(numBytes);
      if (((size_t)mWaterMark + (size_t)numElements) > (size_t)mHighWaterMark) // safety check
      {
#ifdef TORQUE_MEM_DEBUG
         AssertFatal(false, "Overflow");
#endif
         return NULL;
      }
      mWaterMark += (U32)numElements;
      return ptr;
   }

   /// Allocates numElements elements
   inline T* allocElements(const U32 numElements)
   {
      T* ptr = &mBuffer[mWaterMark];
      if (((size_t)mWaterMark + (size_t)numElements) > (size_t)mHighWaterMark) // safety check
      {
#ifdef TORQUE_MEM_DEBUG
         AssertFatal(false, "Overflow");
#endif
         return NULL;
      }
      mWaterMark += numElements;
      return ptr;
   }

   /// Sets current aligned watermark position
   inline void setPosition(const U32 waterMark)
   {
      AssertFatal(waterMark <= mHighWaterMark, "Error, invalid waterMark");
      mWaterMark = waterMark;
   }

   /// Calculates maximum elements required to store numBytes bytes (may overshoot)
   static inline U32 calcRequiredElementSize(const dsize_t numBytes)
   {
      return (U32)((numBytes + (sizeof(T) - 1)) / sizeof(T));
   }

   /// Calculates maximum elements required to store numBytes bytes
   static inline U32 calcMaxElementSize(const dsize_t numBytes)
   {
      return (U32)(numBytes / sizeof(T));
   }

   static inline U32 calcRequiredPaddedByteSize(const dsize_t numBytes)
   {
      return calcRequiredElementSize(numBytes) * sizeof(T);
   }

   inline T* getAlignedBuffer() const
   {
      return mBuffer;
   }

   inline T* getAlignedBufferEnd() const
   {
      return mBuffer + mHighWaterMark;
   }

   inline U32 getPosition() const
   {
      return mWaterMark;
   }

   inline U32 getSize() const
   {
      return mHighWaterMark;
   }

   inline U32 getElementsLeft() const
   {
      return mHighWaterMark - mWaterMark;
   }

   inline dsize_t getPositionBytes() const
   {
      return mWaterMark * sizeof(T);
   }

   inline dsize_t getSizeBytes() const
   {
      return mHighWaterMark * sizeof(T);
   }
};

///
/// Implements an AlignedBufferAllocator<T> which manages its own memory.
///
template<typename T> class ManagedAlignedBufferAllocator : public AlignedBufferAllocator<T>
{
typedef AlignedBufferAllocator<T> Parent;
public:
   T* mMemory;

   ManagedAlignedBufferAllocator() : mMemory(NULL)
   {
   }

   ~ManagedAlignedBufferAllocator()
   {
      destroy();
   }

   void init(const dsize_t byteSize)
   {
      AssertFatal(mMemory ==  NULL, "ManagedAlignedBufferAllocator already initialized");
      U32 frameSize = Parent::calcRequiredElementSize(byteSize);
      mMemory = new U32[frameSize];
      AlignedBufferAllocator<T>::initWithElements(mMemory, frameSize);
   }

   void destroy()
   {
      Parent::setPosition(0);
      delete[] mMemory;
      mMemory = NULL;
   }
};

/// Implements a thread-local global buffer for frame-based allocations.
/// All allocations are aligned to U32.
/// 
/// Example usage:
///
/// @code
///   U32 waterMark = FrameAllocator::getWaterMark();
///   void* ptr = FrameAllocator::alloc(10);
///   // Cleanup...
///   FrameAllocator::setWaterMark(waterMark);
/// @endcode
///
/// See also: FrameAllocatorMarker, FrameTemp.
///
/// NOTE: worker threads which use FrameAllocator should call init and destroy. i.e.
///
/// @code
///   FrameAllocator::init(1024 * 1024 * 12);
///   // Do work...
///   FrameAllocator::destroy();
/// @endcode
/// 
class FrameAllocator
{
protected:

   static thread_local ManagedAlignedBufferAllocator<U32> smFrameAllocator;
#ifdef TORQUE_MEM_DEBUG
   static thread_local dsize_t smMaxAllocationBytes;
#endif

public:

   inline TORQUE_FORCEINLINE static void init(const dsize_t byteSize) { return smFrameAllocator.init(byteSize); }
   inline TORQUE_FORCEINLINE static void destroy() { smFrameAllocator.destroy(); }

   inline TORQUE_FORCEINLINE static void* alloc(const dsize_t numBytes)
   {
#ifdef TORQUE_MEM_DEBUG
      const dsize_t allocBytes = smFrameAllocator.getPositionBytes();
      smMaxAllocationBytes = allocBytes > smMaxAllocationBytes ? allocBytes : smMaxAllocationBytes;
#endif
      return smFrameAllocator.allocBytes(numBytes);
   }

   inline TORQUE_FORCEINLINE static U32 getWaterMark() { return smFrameAllocator.getPosition(); }
   inline TORQUE_FORCEINLINE static dsize_t getWaterMarkBytes() { return smFrameAllocator.getPositionBytes(); }
   inline TORQUE_FORCEINLINE static void setWaterMark(U32 pos) { return smFrameAllocator.setPosition(pos); }

   inline TORQUE_FORCEINLINE static U32 getHighWaterMark() { return smFrameAllocator.getSizeBytes(); }
};

/// Helper class which saves and restores the previous water mark level from FrameAllocator based on scope.
///
/// Example usage:
///
/// @code
/// FrameAllocatorMarker marker;
/// void* ptr = marker.alloc(1024);
/// @endcode
/// 
class FrameAllocatorMarker
{
   U32 mPosition;

public:

   FrameAllocatorMarker()
   {
      mPosition = FrameAllocator::getWaterMark();
   }

   ~FrameAllocatorMarker()
   {
      FrameAllocator::setWaterMark(mPosition);
   }

   /// Allocs numBytes of memory from FrameAllocator
   inline TORQUE_FORCEINLINE static void* alloc(const dsize_t numBytes)
   {
      return FrameAllocator::alloc(numBytes);
   }
};

/// Helper class which temporarily allocates a set of elements of type T from FrameAllocator,
/// restoring the water mark when the scope has ended as with FrameAllocatorMarker.
///
/// Example usage:
///
/// @code
///   FrameTemp<UTF8> textMarker(64);
///   for (U32 i=0; i<textMarker.size(); i++)
///   {
///     textMarker[i] = '\0';
///   }
/// @endcode
///
/// 
template<class T>
class FrameTemp
{
   T* mData;
   U32 mSize;
   U32 mPosition;

public:

   FrameTemp(const U32 numElements = 0)
   {
      mPosition = FrameAllocator::getWaterMark();
      mData = (T*)FrameAllocator::alloc(sizeof(T) * numElements);
      mSize = numElements;
   }

   ~FrameTemp()
   {
      for (U32 i = 0; i < mSize; i++)
         destructInPlace(&mData[i]);
      FrameAllocator::setWaterMark(mPosition);
   }

   // Operators

   inline TORQUE_FORCEINLINE T&       operator*() { return *mData; }
   inline TORQUE_FORCEINLINE const T& operator*() const { return *mData; }

   inline TORQUE_FORCEINLINE T**        operator&() { return &mData; }
   inline TORQUE_FORCEINLINE T* const * operator&() const { return &mData; }

   inline TORQUE_FORCEINLINE operator T&() { return *mData; }
   inline TORQUE_FORCEINLINE operator const T&() const { return *mData; }

   inline TORQUE_FORCEINLINE operator T* () { return mData; }
   inline TORQUE_FORCEINLINE operator const T* () const { return mData; }

   inline TORQUE_FORCEINLINE operator T () { return *mData; }
   inline TORQUE_FORCEINLINE operator const T () const { return *mData; }

   inline TORQUE_FORCEINLINE T& operator[](const dsize_t idx) { return mData[idx]; }
   inline TORQUE_FORCEINLINE const T& operator[](const dsize_t idx) const { return mData[idx]; }

   // Utils

   inline TORQUE_FORCEINLINE T* address() const { return mData; }
   inline TORQUE_FORCEINLINE const U32 size() const { return mSize; }
   inline TORQUE_FORCEINLINE const U32 getObjectCount() const { return mSize; }
};


#endif  // _H_FRAMEALLOCATOR_
