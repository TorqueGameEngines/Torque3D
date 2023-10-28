//-----------------------------------------------------------------------------
// Copyright (c) 2023 tgemit contributors.
// See AUTHORS file and git repository for contributor information.
//
// SPDX-License-Identifier: MIT
//-----------------------------------------------------------------------------

#pragma once
#define _DATACHUNKER_H_

#ifndef _PLATFORM_H_
#  include "platform/platform.h"
#endif
#ifndef _PLATFORMASSERT_H_
#  include "platform/platformAssert.h"
#endif

#include <algorithm>
#include <stdint.h>
#include "core/frameAllocator.h"
//#include "math/mMathFn.h" // tgemit - needed here for the moment

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

   bool isEmpty()
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

   void freeBlocks(bool keepOne=false)
   {
      BaseDataChunker<T>::freeBlocks(keepOne);
   }
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

   void freeBlocks(bool keepOne)
   {
      BaseDataChunker<T>::freeBlocks(keepOne);
   }
};
