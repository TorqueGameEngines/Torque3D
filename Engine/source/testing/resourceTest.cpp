//-----------------------------------------------------------------------------
// Copyright (c) 2014 GarageGames, LLC
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
#include "unitTesting.h"

#include "platform/platform.h"

#include "core/util/fourcc.h"
#include "console/console.h"
#include "core/resourceManager.h"
static bool destructorCalled;

struct TestResource
{
public:
   U64 values[4] = { 0,0,0,0 };
   virtual ~TestResource() { destructorCalled = true; }

   static Resource< TestResource > load(const Torque::Path& path);
   static ResourceRegisterPostLoadSignal< TestResource > _smAutoLoad;
   static void _onTestLoaded(Resource< TestResource >& test);
};

template<> ResourceBase::Signature  Resource<TestResource>::signature()
{
   return MakeFourCC('T', 'E', 'S', 'T'); // Direct Draw Surface
}
template<> void* Resource<TestResource>::create(const Torque::Path& path)
{
   TestResource* testRes = new TestResource;

   return testRes;
}

Resource<TestResource> TestResource::load(const Torque::Path& path)
{
   Resource<TestResource> testRes = ResourceManager::get().load(path);

   return testRes;
}

ResourceRegisterPostLoadSignal< TestResource > TestResource::_smAutoLoad(&TestResource::_onTestLoaded);

void TestResource::_onTestLoaded(Resource<TestResource>& test)
{
   test->values[0] = 1;
   test->values[1] = 1;
   test->values[2] = 1;
   test->values[3] = 1;
}
TEST(ResourceManagerTests, All_Resource_Functionality)
{
   if (true)
   {
      Resource<TestResource> testRes;

      testRes = TestResource::load("empty");

      EXPECT_EQ(testRes.signature(), MakeFourCC('T', 'E', 'S', 'T')) << "Incorrect resource type returned!";

      EXPECT_EQ(testRes.getPath(), "empty") << "Wrong path!";

      U64 postLoadValues[4];
      postLoadValues[0] = 1;
      postLoadValues[1] = 1;
      postLoadValues[2] = 1;
      postLoadValues[3] = 1;

      for (U32 i = 0; i < 4; i++)
      {
         EXPECT_EQ(testRes->values[i], postLoadValues[i]) << "Array not equal";
      }

      EXPECT_EQ(destructorCalled, false) << "Destructor true should be false";
   }

   EXPECT_EQ(destructorCalled, true) << "Destructor false should be true";
}

