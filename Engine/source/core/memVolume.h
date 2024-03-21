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
#ifndef _MEMVOLUME_H_
#define _MEMVOLUME_H_

#ifndef _VOLUME_H_
#include "core/volume.h"
#endif

#ifndef _TDICTIONARY_H_
#include "core/util/tDictionary.h"
#endif 

namespace Torque
{
   using namespace FS;

   namespace Mem
   {

      struct MemFileData;
      struct MemDirectoryData;
      class MemDirectory;

      //-----------------------------------------------------------------------------
      class MemFileSystem: public FileSystem
      {
      public:
         MemFileSystem(String volume);
         ~MemFileSystem();

         String   getTypeStr() const override { return "Mem"; }

         FileNodeRef resolve(const Path& path) override;
         FileNodeRef create(const Path& path,FileNode::Mode) override;
         bool remove(const Path& path) override;
         bool rename(const Path& from,const Path& to) override;
         Path mapTo(const Path& path) override;
         Path mapFrom(const Path& path) override;

      private:
         String mVolume;
         MemDirectoryData* mRootDir;

         MemDirectory* getParentDir(const Path& path, FileNodeRef& parentRef);
      };

      //-----------------------------------------------------------------------------
      /// Mem stdio file access.
      /// This class makes use the fopen, fread and fwrite for buffered io.
      class MemFile: public File
      {
      public:
         MemFile(MemFileSystem* fs, MemFileData* fileData);
         virtual ~MemFile();

         Path getName() const override;
         NodeStatus getStatus() const override;
         bool getAttributes(Attributes*) override;

         U32 getPosition() override;
         U32 setPosition(U32,SeekMode) override;

         bool open(AccessMode) override;
         bool close() override;

         U32 read(void* dst, U32 size) override;
         U32 write(const void* src, U32 size) override;

      private:
         U32 calculateChecksum() override;

         MemFileSystem* mFileSystem;
         MemFileData* mFileData;
         NodeStatus   mStatus;
         U32 mCurrentPos;

         bool _updateInfo();
         void _updateStatus();
      };


      //-----------------------------------------------------------------------------

      class MemDirectory: public Directory
      {
      public:
         MemDirectory(MemFileSystem* fs, MemDirectoryData* dir);
         ~MemDirectory();

         Path getName() const override;
         NodeStatus getStatus() const override;
         bool getAttributes(Attributes*) override;

         bool open() override;
         bool close() override;
         bool read(Attributes*) override;

      private:
         friend class MemFileSystem;
         MemFileSystem* mFileSystem;
         MemDirectoryData* mDirectoryData;

         U32 calculateChecksum() override;         
         
         NodeStatus   mStatus;
         U32 mSearchIndex;         
      };

   } // Namespace
} // Namespace

#endif
