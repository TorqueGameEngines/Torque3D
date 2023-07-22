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

#include "testing/unitTesting.h"
#include "platform/platform.h"
#include "core/fileio.h"
#include "core/util/tVector.h"
#include "console/console.h"

class PlatformFileIOTest : public ::testing::Test
{
protected:
   PlatformFileIOTest()
   {
      // create a file for tests.
      f.open("testTouch.file", File::WriteAppend);
      f.close();
      Platform::getFileTimes("testTouch.file", &initCreate, NULL);
   }

   void SetUp() override
   {
   }
   File f;
   FileTime initCreate;

   void TearDown() override
   {
      // Clean up..
      dFileDelete("testTouch.file");
   }

};

TEST_F(PlatformFileIOTest, ExcludedDirectories)
{
   // Just dump everything under the current directory. We should
   // find at least one file.

   // Exclude .svn and CVS
   Platform::clearExcludedDirectories();
   Platform::addExcludedDirectory(".svn");
   Platform::addExcludedDirectory("CVS");

   EXPECT_TRUE(Platform::isExcludedDirectory(".svn"))
      << "On list, should be excluded.";
   EXPECT_TRUE(Platform::isExcludedDirectory("CVS"))
      << "On list, should be excluded.";
   EXPECT_FALSE(Platform::isExcludedDirectory("foo"))
      << "Doesn't match list, shouldn't be excluded.";
   EXPECT_FALSE(Platform::isExcludedDirectory(".svnCVS"))
      << "Looks like a duck, but it shouldn't be excluded cuz it's distinct from all entries on the exclusion list.";

   // Ok, now our exclusion list is setup, so let's dump some paths.
   Vector<Platform::FileInfo> pathInfo;
   Platform::dumpPath(Platform::getCurrentDirectory(), pathInfo, 2);
   EXPECT_GT(pathInfo.size(), 0)
      << "Should find at least SOMETHING in the current directory!";

   // This'll nuke info if we run it in a live situation... so don't run unit
   // tests in a live situation. ;)
   Platform::clearExcludedDirectories();
};

TEST_F(PlatformFileIOTest, CreateTest)
{
   EXPECT_TRUE(Platform::isFile("testTouch.file"))
      << "Class should have created this file.";
}

TEST_F(PlatformFileIOTest, CreateTimeTest)
{
   FileTime testCreate;

   Platform::getFileTimes("testTouch.file", &testCreate, NULL);

   EXPECT_EQ(Platform::compareFileTimes(testCreate, initCreate), 0)
      << "Create timestamps should match.";
}

TEST_F(PlatformFileIOTest, ModifyTimesTest)
{
   FileTime modify[2];

   // Touch a file and note its last-modified.
   dFileTouch("testTouch.file");

   Platform::getFileTimes("testTouch.file", NULL, &modify[0]);

   // Sleep for a second
   Platform::sleep(1000);

   dFileTouch("testTouch.file");
   Platform::getFileTimes("testTouch.file", NULL, &modify[1]);

   // Now compare the times...
   EXPECT_LT(Platform::compareFileTimes(modify[0], modify[1]), 0)
      << "Timestamps are wrong - modify[0] should be before modify[1]!";
};

TEST_F(PlatformFileIOTest, DeleteFileTest)
{
   // Clean up..
   dFileDelete("testTouch.file");
   EXPECT_FALSE(Platform::isFile("testTouch.file"))
      << "Somehow failed to delete our test file.";
}

// Mac/Linux have no implementations for these functions, so we 'def it out for now.
#ifdef WIN32
TEST_F(PlatformFileIOTest, Volumes)
{
   Vector<const char*> names;
   Platform::getVolumeNamesList(names);

   EXPECT_GT(names.size(), 0)
      << "We should have at least one volume...";

   Vector<Platform::VolumeInformation> info;
   Platform::getVolumeInformationList(info);

   EXPECT_EQ(names.size(), info.size())
      << "Got inconsistent number of volumes back from info vs. name list functions!";
};
#endif

