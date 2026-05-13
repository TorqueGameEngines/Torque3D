#ifndef GL_CIRCULAR_VOLATILE_BUFFER_H
#define GL_CIRCULAR_VOLATILE_BUFFER_H

#include "gfx/gl/gfxGLDevice.h"
#include "gfx/gl/gfxGLUtils.h"

class GLCircularVolatileBuffer
{
public:
   GLCircularVolatileBuffer(GLuint binding)
      : mBinding(binding),
      mBufferName(0),
      mBufferPtr(nullptr),
      mBufferSize(0),
      mBufferFreePos(0),
      mCurrentRangeStart(0),
      mMapped(false)
   {
      init();
   }

   ~GLCircularVolatileBuffer()
   {
      // Ensure any active non-persistent mapping is released before we
      // block on fences — unmap requires the buffer to be bound.
      if (mMapped && !GFXGL->mCapabilities.bufferStorage)
      {
         PRESERVE_BUFFER(mBinding);
         glBindBuffer(mBinding, mBufferName);
         glUnmapBuffer(mBinding);
         mMapped = false;
      }

      waitAll();
      glDeleteBuffers(1, &mBufferName);
   }

   // Non-copyable: owns GL resources and raw fence handles.
   GLCircularVolatileBuffer(const GLCircularVolatileBuffer&) = delete;
   GLCircularVolatileBuffer& operator=(const GLCircularVolatileBuffer&) = delete;

   void init()
   {
      glGenBuffers(1, &mBufferName);

      PRESERVE_BUFFER(mBinding);
      glBindBuffer(mBinding, mBufferName);

      const U32 cSizeInMB = 10;
      mBufferSize = (cSizeInMB << 20);

      if (GFXGL->mCapabilities.bufferStorage)
      {
         const GLbitfield flags = GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT;
         glBufferStorage(mBinding, mBufferSize, nullptr, flags);
         mBufferPtr = glMapBufferRange(mBinding, 0, mBufferSize, flags);
      }
      else
      {
         glBufferData(mBinding, mBufferSize, nullptr, GL_DYNAMIC_DRAW);
      }
   }

   // Acquire a sub-range of [size] bytes aligned to [offsetAlign].
   // On return, [outOffset] is the byte offset into the buffer and
   // [outPtr] is the CPU-writable pointer.  Call unlock() when done writing.
   void lock(const U32 size, U32 offsetAlign, U32& outOffset, void*& outPtr)
   {
      AssertFatal(size > 0, "Size must be > 0");
      AssertFatal(!mMapped, "lock() called while a range is already mapped");

      align(mBufferFreePos, offsetAlign);

      // Wrap-around: protect whatever has been written since the last protect
      // call, then reset the write cursor to the start of the buffer.
      if (mBufferFreePos + size > mBufferSize)
      {
         if (mCurrentRangeStart < mBufferFreePos)
            protectRange(mCurrentRangeStart, mBufferFreePos - 1);

         mBufferFreePos = 0;
         mCurrentRangeStart = 0;
         align(mBufferFreePos, offsetAlign);
      }

      // Block until the GPU has finished reading any overlapping region.
      waitOverlap(mBufferFreePos, mBufferFreePos + size - 1);

      outOffset = mBufferFreePos;

      if (GFXGL->mCapabilities.bufferStorage)
      {
         outPtr = static_cast<U8*>(mBufferPtr) + mBufferFreePos;
      }
      else
      {
         PRESERVE_BUFFER(mBinding);
         glBindBuffer(mBinding, mBufferName);
         outPtr = glMapBufferRange(
            mBinding,
            outOffset,
            size,
            GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT
         );
         mMapped = (outPtr != nullptr);
      }

      mBufferFreePos += size;
      align(mBufferFreePos, 4);
   }

   // Release the CPU mapping for non-persistent paths.  Safe to call on
   // persistent-mapped buffers (no-op).
   void unlock()
   {
      if (!GFXGL->mCapabilities.bufferStorage && mMapped)
      {
         PRESERVE_BUFFER(mBinding);
         glBindBuffer(mBinding, mBufferName);
         glUnmapBuffer(mBinding);
         mMapped = false;
      }
   }

   // Insert a fence covering everything written since the last protect call.
   // Call this after submitting draw calls that read from the buffer so that
   // lock() can wait for completion before re-using the same bytes.
   void protectUsedRange()
   {
      if (mCurrentRangeStart < mBufferFreePos)
      {
         protectRange(mCurrentRangeStart, mBufferFreePos - 1);
         mCurrentRangeStart = mBufferFreePos;
      }
   }

   GLuint getHandle() const { return mBufferName; }

protected:

   struct FenceRange
   {
      U32    start;
      U32    end;
      GLsync fence;
   };

   GLuint          mBinding;
   GLuint          mBufferName;
   void* mBufferPtr;
   U32             mBufferSize;
   U32             mBufferFreePos;
   U32             mCurrentRangeStart;
   bool            mMapped;           // true while a non-persistent mapping is live
   Vector<FenceRange> mFenceRanges;

   // -----------------------------------------------------------------------
   // Helpers
   // -----------------------------------------------------------------------

   static void align(U32& value, U32 alignment)
   {
      if (alignment)
         value = (value + alignment - 1) & ~(alignment - 1);
   }

   static bool overlaps(U32 a0, U32 a1, U32 b0, U32 b1)
   {
      return a0 <= b1 && b0 <= a1;
   }

   // Block until [fence] is signalled.  Returns false if the driver reports
   // GL_WAIT_FAILED (context loss or similar), true otherwise.
   static bool waitFence(GLsync fence)
   {
      // GL_SYNC_FLUSH_COMMANDS_BIT ensures the commands are actually submitted
      // to the GPU before we block, preventing a deadlock when the command
      // queue has not yet been flushed.
      // GL_TIMEOUT_IGNORED makes the call block until the fence is signalled
      // rather than polling with a zero-nanosecond timeout.
      const GLenum result =
         glClientWaitSync(fence, GL_SYNC_FLUSH_COMMANDS_BIT, GL_TIMEOUT_IGNORED);

      AssertWarn(result != GL_WAIT_FAILED,
         "GLCircularVolatileBuffer: glClientWaitSync returned GL_WAIT_FAILED "
         "(possible context loss).");

      return result != GL_WAIT_FAILED;
   }

   void protectRange(U32 start, U32 end)
   {
      FenceRange r;
      r.start = start;
      r.end = end;
      r.fence = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);
      mFenceRanges.push_back(r);
   }

   void waitOverlap(U32 start, U32 end)
   {
      // Collect indices of completed (or waited-on) fences into a separate
      // list so we can erase them without invalidating the iterator mid-loop.
      Vector<U32> toErase;

      for (U32 i = 0; i < mFenceRanges.size(); ++i)
      {
         if (!overlaps(start, end, mFenceRanges[i].start, mFenceRanges[i].end))
            continue;

         waitFence(mFenceRanges[i].fence);
         glDeleteSync(mFenceRanges[i].fence);
         toErase.push_back(i);
      }

      // Erase in reverse order so indices remain valid.
      for (S32 i = (S32)toErase.size() - 1; i >= 0; --i)
         mFenceRanges.erase(mFenceRanges.begin() + toErase[i]);
   }

   void waitAll()
   {
      for (auto& r : mFenceRanges)
      {
         waitFence(r.fence);
         glDeleteSync(r.fence);
      }
      mFenceRanges.clear();
   }
};

#endif
