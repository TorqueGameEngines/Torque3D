//-----------------------------------------------------------------------------
// Copyright (c) 2023 tgemit contributors.
// See AUTHORS file and git repository for contributor information.
//
// SPDX-License-Identifier: MIT
//-----------------------------------------------------------------------------

#ifndef _DATACHUNKER_H_
#define _DATACHUNKER_H_

#ifndef _PLATFORM_H_
#  include "platform/platform.h"
#endif
#ifndef _PLATFORMASSERT_H_
#  include "platform/platformAssert.h"
#endif
#ifndef _FRAMEALLOCATOR_H_
#include "core/frameAllocator.h"
#endif

#include <algorithm>
#include <stdint.h>

/// Implements a chunked data allocator.
///
/// This memory allocator allocates data in chunks of bytes, 
/// the default size being ChunkSize.
/// Bytes are sourced from the current head chunk until expended, 
/// in which case a new chunk of bytes will be allocated from 
/// the system memory allocator.
///
template<class T> class BaseDataChunker
{
public:
   enum
   {
      ChunkSize = 16384
   };

   typedef T AlignmentType;

   struct alignas(uintptr_t) DataBlock : public AlignedBufferAllocator<T>
   {
      DataBlock* mNext;

      inline DataBlock* getEnd()
      {
         return this + 1;
      }
   };

protected:
   dsize_t mChunkSize;
   DataBlock* mChunkHead;

public:

   BaseDataChunker(U32 chunkSize = BaseDataChunker<T>::ChunkSize) : mChunkSize(chunkSize), mChunkHead(NULL)
   {
   }

   virtual ~BaseDataChunker()
   {
      freeBlocks(false);
   }

   DataBlock* allocChunk(dsize_t chunkSize)
   {
      DataBlock* newChunk = (DataBlock*)dMalloc(sizeof(DataBlock) + chunkSize);
      constructInPlace(newChunk);
      newChunk->initWithBytes((T*)newChunk->getEnd(), chunkSize);
      newChunk->mNext = mChunkHead;
      mChunkHead = newChunk;
      return newChunk;
   }

   void* alloc(dsize_t numBytes)
   {
      void* theAlloc = mChunkHead ? mChunkHead->allocBytes(numBytes) : NULL;
      if (theAlloc == NULL)
      {
         dsize_t actualSize = std::max<dsize_t>(mChunkSize, numBytes);
         allocChunk(actualSize);
         theAlloc = mChunkHead->allocBytes(numBytes);
         AssertFatal(theAlloc != NULL, "Something really odd going on here");
      }
      return theAlloc;
   }

   void freeBlocks(bool keepOne = false)
   {
      DataBlock* itr = mChunkHead;
      while (itr)
      {
         DataBlock* nextItr = itr->mNext;
         if (nextItr == NULL && keepOne)
         {
            itr->setPosition(0);
            break;
         }
         dFree(itr);
         itr = nextItr;
      }
      mChunkHead = itr;
   }

   U32 countUsedBlocks()
   {
      U32 count = 0;
      for (DataBlock* itr = mChunkHead; itr; itr = itr->mNext)
      {
         count++;
      }
      return count;
   }

   dsize_t countUsedBytes()
   {
      dsize_t count = 0;
      for (DataBlock* itr = mChunkHead; itr; itr = itr->mNext)
      {
         count += itr->getPositionBytes();
      }
      return count;
   }

   void setChunkSize(dsize_t size)
   {
      AssertFatal(mChunkHead == NULL, "Tried setting AFTER init");
      mChunkSize = size;
   }

   bool isManagedByChunker(void* ptr) const
   {
      U8* chkPtr = (U8*)ptr;
      for (DataBlock* itr = mChunkHead; itr; itr = itr->mNext)
      {
         const U8* blockStart = (U8*)itr->getAlignedBuffer();
         const U8* blockEnd = (U8*)itr->getAlignedBufferEnd();
         if (chkPtr >= blockStart && chkPtr < blockEnd)
            return true;
      }
      return false;
   }
};

class DataChunker : public BaseDataChunker<uintptr_t>
{
public:
   DataChunker() : BaseDataChunker<uintptr_t>(BaseDataChunker<uintptr_t>::ChunkSize) { ; }
   explicit DataChunker(dsize_t size) : BaseDataChunker<uintptr_t>(size) { ; }
};



/// Implements a derivative of BaseDataChunker designed for 
/// allocating structs of type T without initialization.
template<class T> class Chunker : private BaseDataChunker<T>
{
public:
   Chunker(dsize_t size = BaseDataChunker<T>::ChunkSize) : BaseDataChunker<T>(std::max(sizeof(T), size))
   {
   }

   T* alloc()
   {
      return (T*)BaseDataChunker<T>::alloc(sizeof(T));
   }

   void clear()
   {
      BaseDataChunker<T>::freeBlocks();
   }
};

/// Implements a derivative of BaseDataChunker designed for 
/// allocating structs of various types Y without initialization.
/// @note: this is horribly suboptimal for types not multiples of uintptr_t in size.
class MultiTypedChunker : private BaseDataChunker<uintptr_t>
{
public:
   typedef uintptr_t AlignmentType;

   MultiTypedChunker(dsize_t size = BaseDataChunker<uintptr_t>::ChunkSize) : BaseDataChunker<uintptr_t>(std::max<uintptr_t>(sizeof(uintptr_t), size))
   {
   }

   template<typename Y> Y* alloc()
   {
      return (Y*)BaseDataChunker<uintptr_t>::alloc(sizeof(Y));
   }

   void clear()
   {
      BaseDataChunker<uintptr_t>::freeBlocks(true);
   }
};

/// Implements a simple linked list for ClassChunker and FreeListChunker.
template<class T> struct ChunkerFreeClassList
{
   ChunkerFreeClassList<T>* mNextList;

   ChunkerFreeClassList() : mNextList(NULL)
   {
   }

   void reset()
   {
      mNextList = NULL;
   }

   bool isEmpty() const
   {
      return mNextList == NULL;
   }

   T* pop()
   {
      ChunkerFreeClassList<T>* oldNext = mNextList;
      mNextList = mNextList ? mNextList->mNextList : NULL;
      return (T*)oldNext;
   }

   void push(ChunkerFreeClassList<T>* other)
   {
      other->mNextList = mNextList;
      mNextList = other;
   }
};

/// Implements a derivative of BaseDataChunker designed for 
/// allocating structs or classes of type T with initialization.
template<class T> class ClassChunker : private BaseDataChunker<T>
{
protected:
   ChunkerFreeClassList<T> mFreeListHead;

public:
   ClassChunker(dsize_t size = BaseDataChunker<T>::ChunkSize)
   {

   }

   T* alloc()
   {
      if (mFreeListHead.isEmpty())
      {
         return constructInPlace((T*)BaseDataChunker<T>::alloc(sizeof(T)));
      }
      else
      {
         return constructInPlace(mFreeListHead.pop());
      }
   }

   void free(T* item)
   {
      destructInPlace(item);
      mFreeListHead.push(reinterpret_cast<ChunkerFreeClassList<T>*>(item));
   }

   void freeBlocks(bool keepOne = false)
   {
      BaseDataChunker<T>::freeBlocks(keepOne);
      mFreeListHead.reset();
   }

   inline bool isManagedByChunker(void* ptr) const
   {
      return BaseDataChunker<T>::isManagedByChunker(ptr);
   }

   inline ChunkerFreeClassList<T>& getFreeListHead() { return mFreeListHead; }
};

/// Implements a chunker which uses the data of another BaseDataChunker 
/// as underlying storage.
template<class T> class FreeListChunker
{
protected:
   BaseDataChunker<T>* mChunker;
   bool mOwnsChunker;
   ChunkerFreeClassList<T> mFreeListHead;

public:
   FreeListChunker(BaseDataChunker<T>* otherChunker) :
      mChunker(otherChunker),
      mOwnsChunker(false)
   {
   }

   FreeListChunker(dsize_t size = BaseDataChunker<T>::ChunkSize)
   {
      mChunker = new BaseDataChunker<T>(size);
      mOwnsChunker = true;
   }

   BaseDataChunker<T>* getChunker()
   {
      return mChunker;
   }

   T* alloc()
   {
      if (mFreeListHead.isEmpty())
      {
         return constructInPlace((T*)mChunker->alloc(sizeof(T)));
      }
      else
      {
         return constructInPlace(mFreeListHead.pop());
      }
   }

   void free(T* item)
   {
      destructInPlace(item);
      mFreeListHead.push(reinterpret_cast<ChunkerFreeClassList<T>*>(item));
   }

   void freeBlocks(bool keepOne = false)
   {
      mChunker->freeBlocks(keepOne);
   }
};

template<const U32 byteSize> struct DWordDataBlob
{
   U32 data[(byteSize + 3)/ 4];
};

/// Implements a three-tiered chunker
/// K1..3 should be ordered from low to high
template<class K1, class K2, class K3> class ThreeTieredChunker
{
public:
   struct Handle
   {
      U32 tier;
      void* ptr;

      Handle() : tier(0), ptr(NULL) { ; }
      Handle(const Handle& other) : tier(other.tier), ptr(other.ptr) { ; }
      Handle(U32 in_tier, void* in_ptr) : tier(in_tier), ptr(in_ptr) { ; }

      Handle& operator=(const Handle& other) {
         tier = other.tier;
         ptr = other.ptr;
         return *this;
      }
   };

protected:

   ClassChunker<K1> mT1;
   ClassChunker<K2> mT2;
   ClassChunker<K3> mT3;

public:

   Handle alloc(U32 byteSize)
   {
      Handle outH;

      if (byteSize > sizeof(K3))
      {
         const U32 wordSize = (byteSize + 3) / 4;
         outH = Handle(0, (void*)(new U32[wordSize]));
      }
      else
      {
         if (byteSize <= sizeof(K1))
         {
            outH = Handle(1, (void*)mT1.alloc());
         }
         else if (byteSize <= sizeof(K2))
         {
            outH = Handle(2, (void*)mT2.alloc());
         }
         else if (byteSize <= sizeof(K3))
         {
            outH = Handle(3, (void*)mT3.alloc());
         }
         else
         {
            outH = Handle(0, NULL);
         }
      }

      return outH;
   }

   void free(Handle& item)
   {
      if (item.ptr == NULL)
         return;

      switch (item.tier)
      {
      case 0:
         delete[] ((U32*)item.ptr);
         break;
      case 1:
         mT1.free((K1*)item.ptr);
         break;
      case 2:
         mT2.free((K2*)item.ptr);
         break;
      case 3:
         mT3.free((K3*)item.ptr);
         break;
      default:
         break;
      }

      item.ptr = NULL;
   }

   void freeBlocks(bool keepOne = false)
   {
      mT1.freeBlocks(keepOne);
      mT2.freeBlocks(keepOne);
      mT3.freeBlocks(keepOne);
   }

   inline ClassChunker<K1>& getT1Chunker() { return mT1; }
   inline ClassChunker<K2>& getT2Chunker() { return mT2; }
   inline ClassChunker<K3>& getT3Chunker() { return mT3; }
};

#endif
