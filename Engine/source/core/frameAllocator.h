//-----------------------------------------------------------------------------
// Copyright (c) 2013 GarageGames, LLC
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

#ifndef _FRAMEALLOCATOR_H_
#define _FRAMEALLOCATOR_H_

#ifndef _PLATFORM_H_
#include "platform/platform.h"
#endif

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

   inline void initWithElements(T* ptr, U32 numElements)
   {
      mBuffer = ptr;
      mHighWaterMark = numElements;
      mWaterMark = 0;
   }

   inline void initWithBytes(T* ptr, dsize_t bytes)
   {
      mBuffer = ptr;
      mHighWaterMark = (U32)(calcMaxElementSize(bytes));
      mWaterMark = 0;
   }

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

   inline T* getAlignedBuffer() const
   {
      return mBuffer;
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

/// Temporary memory pool for per-frame allocations.
///
/// In the course of rendering a frame, it is often necessary to allocate
/// many small chunks of memory, then free them all in a batch. For instance,
/// say we're allocating storage for some vertex calculations:
///
/// @code
///   // Get FrameAllocator memory...
///   U32 waterMark = FrameAllocator::getWaterMark();
///   F32 * ptr = (F32*)FrameAllocator::alloc(sizeof(F32)*2*targetMesh->vertsPerFrame);
///
///   ... calculations ...
///
///   // Free frameAllocator memory
///   FrameAllocator::setWaterMark(waterMark);
/// @endcode
class FrameAllocator
{
public:
   static dsize_t   smMaxFrameAllocation;
#ifdef TORQUE_MEM_DEBUG
   static thread_local dsize_t   smAllocatedBytes;
#endif
   typedef AlignedBufferAllocator<U32> FrameAllocatorType;

   inline static void init(const U32 frameSize)
   {
      FrameAllocatorType::ValueType* curPtr = smMainInstance.getAlignedBuffer();
      AssertFatal(curPtr == NULL, "Error, already initialized");
      if (curPtr)
         return;

#ifdef TORQUE_MEM_DEBUG
      smAllocatedBytes = 0;
#endif

      U32 elementSize = FrameAllocatorType::calcRequiredElementSize(frameSize);
      FrameAllocatorType::ValueType* newAlignedBuffer = new FrameAllocatorType::ValueType[elementSize];
      smMainInstance.initWithElements(newAlignedBuffer, elementSize);
   }

   inline static void destroy()
   {
      FrameAllocatorType::ValueType* curPtr = smMainInstance.getAlignedBuffer();
      AssertFatal(smMainInstance.getAlignedBuffer() != NULL, "Error, not initialized");
      if (curPtr == NULL)
         return;

      delete[] curPtr;
      smMainInstance.initWithElements(NULL, 0);
   }

   inline static void* alloc(const U32 allocSize)
   {
      void* outPtr = smMainInstance.allocBytes(allocSize);

#ifdef TORQUE_MEM_DEBUG
      smAllocatedBytes += allocSize;
      if (smAllocatedBytes > smMaxFrameAllocation)
      {
         smMaxFrameAllocation = smAllocatedBytes;
      }
#endif

      return outPtr;
   }

   inline static void setWaterMark(const U32 waterMark)
   {
#ifdef TORQUE_MEM_DEBUG
      AssertFatal(waterMark % sizeof(FrameAllocatorType::ValueType) == 0, "Misaligned watermark");
      smAllocatedBytes = waterMark;
#endif
      smMainInstance.setPosition(waterMark / sizeof(FrameAllocatorType::ValueType));
   }

   inline static U32  getWaterMark()
   {
      return smMainInstance.getPositionBytes();
   }

   inline static U32  getHighWaterMark()
   {
      return smMainInstance.getSizeBytes();
   }

   static thread_local FrameAllocatorType smMainInstance;
};

/// Helper class to deal with FrameAllocator usage.
///
/// The purpose of this class is to make it simpler and more reliable to use the
/// FrameAllocator. Simply use it like this:
///
/// @code
/// FrameAllocatorMarker mem;
///
/// char *buff = (char*)mem.alloc(100);
/// @endcode
///
/// When you leave the scope you defined the FrameAllocatorMarker in, it will
/// automatically restore the watermark on the FrameAllocator. In situations
/// with complex branches, this can be a significant headache remover, as you
/// don't have to remember to reset the FrameAllocator on every posssible branch.
class FrameAllocatorMarker
{
   U32 mMarker;

public:
   FrameAllocatorMarker()
   {
      mMarker = FrameAllocator::getWaterMark();
   }

   ~FrameAllocatorMarker()
   {
      FrameAllocator::setWaterMark(mMarker);
   }

   void* alloc(const U32 allocSize) const
   {
      return FrameAllocator::alloc(allocSize);
   }
};

/// Class for temporary variables that you want to allocate easily using
/// the FrameAllocator. For example:
/// @code
/// FrameTemp<char> tempStr(32); // NOTE! This parameter is NOT THE SIZE IN BYTES. See constructor docs.
/// dStrcat( tempStr, SomeOtherString );
/// tempStr[2] = 'l';
/// Con::printf( tempStr );
/// Con::printf( "Foo: %s", ~tempStr );
/// @endcode
///
/// This will automatically handle getting and restoring the watermark of the
/// FrameAllocator when it goes out of scope. You should notice the strange
/// operator infront of tempStr on the printf call. This is normally a unary
/// operator for ones-complement, but in this class it will simply return the
/// memory of the allocation. It's the same as doing (const char *)tempStr
/// in the above case. The reason why it is necessary for the second printf
/// and not the first is because the second one is taking a variable arg
/// list and so it isn't getting the cast so that it's cast operator can
/// properly return the memory instead of the FrameTemp object itself.
///
/// @note It is important to note that this object is designed to just be a
/// temporary array of a dynamic size. Some wierdness may occur if you try
/// do perform crazy pointer stuff with it using regular operators on it.
/// I implemented what I thought were the most common operators that it
/// would be used for. If strange things happen, you will need to debug
/// them yourself.
template<class T>
class FrameTemp
{
protected:
   U32 mWaterMark;
   T* mMemory;
   U32 mNumObjectsInMemory;

public:
   /// Constructor will store the FrameAllocator watermark and allocate the memory off
   /// of the FrameAllocator.
   ///
   /// @note It is important to note that, unlike the FrameAllocatorMarker and the
   /// FrameAllocator itself, the argument to allocate is NOT the size in bytes,
   /// doing:
   /// @code
   /// FrameTemp<F64> f64s(5);
   /// @endcode
   /// Is the same as
   /// @code
   /// F64 *f64s = new F64[5];
   /// @endcode
   ///
   /// @param   count   The number of objects to allocate
   FrameTemp(const U32 count = 1) : mNumObjectsInMemory(count)
   {
      AssertFatal(count > 0, "Allocating a FrameTemp with less than one instance");
      mWaterMark = FrameAllocator::getWaterMark();
      mMemory = reinterpret_cast<T*>(FrameAllocator::alloc(sizeof(T) * count));

      for (U32 i = 0; i < mNumObjectsInMemory; i++)
         constructInPlace<T>(&mMemory[i]);
   }

   /// Destructor restores the watermark
   ~FrameTemp()
   {
      // Call destructor
      for (U32 i = 0; i < mNumObjectsInMemory; i++)
         destructInPlace<T>(&mMemory[i]);

      FrameAllocator::setWaterMark(mWaterMark);
   }

   U32 getObjectCount(void) const { return mNumObjectsInMemory; }
   U32 size(void) const { return mNumObjectsInMemory; }

   T& operator *() { return *mMemory; };
   const T& operator *() const { return *mMemory; }

   T** operator &() { return &mMemory; }
   const T** operator &() const { return &mMemory; }

   operator T* () { return mMemory; }
   operator const T* () const { return mMemory; }

   operator T& () { return *mMemory; }
   operator const T& () const { return *mMemory; }

   operator T() { return *mMemory; }
   operator const T() const { return *mMemory; }

   inline T* address() const { return mMemory; }

   // This ifdef is to satisfy the ever so pedantic GCC compiler
   //  Which seems to upset visual studio.
   T& operator[](const U32 idx) { return mMemory[idx]; }
   const T& operator[](const U32 idx) const { return mMemory[idx]; }
   T& operator[](const S32 idx) { return mMemory[idx]; }
   const T& operator[](const S32 idx) const { return mMemory[idx]; }
};

//-----------------------------------------------------------------------------

#endif  // _H_FRAMEALLOCATOR_
