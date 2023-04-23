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

#include "app/mainLoop.h"
#include "console/console.h"
#include "console/script.h"
#include "console/engineAPI.h"
#include "console/consoleInternal.h"
#include "gfx/gfxInit.h"

#if defined(TORQUE_OS_WIN)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif


//-----------------------------------------------------------------------------

class TorqueUnitTestListener : public ::testing::EmptyTestEventListener
{
   // Called before a test starts.
   virtual void OnTestStart(const ::testing::TestInfo& testInfo)
   {
      if (mVerbose)
         Con::printf("> Starting Test '%s.%s'",
            testInfo.test_case_name(), testInfo.name());
   }

   // Called after a failed assertion or a SUCCEED() invocation.
   virtual void OnTestPartResult(const ::testing::TestPartResult& testPartResult)
   {
      if (testPartResult.failed())
      {
         Con::warnf(">> Failed with '%s' in '%s' at (line:%d)\n",
            testPartResult.summary(),
            testPartResult.file_name(),
            testPartResult.line_number()
         );
      }
      else if (mVerbose)
      {
         Con::printf(">> Passed with '%s' in '%s' at (line:%d)",
            testPartResult.summary(),
            testPartResult.file_name(),
            testPartResult.line_number()
         );
      }
   }

   // Called after a test ends.
   virtual void OnTestEnd(const ::testing::TestInfo& testInfo)
   {
      if (testInfo.result()->Failed())
      {
         Con::printf("TestClass:%s Test:%s Failed!",
            testInfo.test_case_name(), testInfo.name());
      }

      if (!mVerbose)
         return;

      else if(testInfo.result()->Passed())
      {
         Con::printf("TestClass:%s Test:%s Succeeded!",
            testInfo.test_case_name(), testInfo.name());
      }
      else
      {
         Con::printf("TestClass:%s Test:%s Skipped!",
            testInfo.test_case_name(), testInfo.name());
      }

      Con::printf("> Ending Test\n");

   }

   bool mVerbose;

public:
   TorqueUnitTestListener(bool verbose) : mVerbose(verbose) {}
};

class MemoryLeakDetector : public ::testing::EmptyTestEventListener
{
public:
   virtual void OnTestStart(const ::testing::TestInfo& testInfo)
   {
#if defined(TORQUE_OS_WIN)
      _CrtMemCheckpoint(&memState_);
#endif
   }

   virtual void OnTestEnd(const ::testing::TestInfo& testInfo)
   {
      if (testInfo.result()->Passed())
      {
#if defined(TORQUE_OS_WIN)
         _CrtMemState stateNow, stateDiff;
         _CrtMemCheckpoint(&stateNow);
         int diffResult = _CrtMemDifference(&stateDiff, &memState_, &stateNow);
         if (diffResult)
         {
            FAIL() << "Memory leak of " << stateDiff.lSizes[1] << " byte(s) detected.";
         }
#endif
      }
   }

private:
#if defined(TORQUE_OS_WIN)
   _CrtMemState memState_;
#endif
public:
   MemoryLeakDetector() {}
};

class TorqueScriptFixture : public testing::Test {};

class TorqueScriptTest : public TorqueScriptFixture {
public:
   explicit TorqueScriptTest(const char* pFunctionName) : mFunctionName(pFunctionName) {}
   void TestBody() override
   {
      Con::executef(mFunctionName);
   }

private:
   const char* mFunctionName;
};

int main(int argc, char** argv)
{
   testing::GTEST_FLAG(output) = "xml:test_detail.xml";
   testing::GTEST_FLAG(stack_trace_depth) = 10;

   printf("Running main() from %s\n", __FILE__);
   // Initialize Google Test.
   testing::InitGoogleTest(&argc, argv);

   // torques handle command.
   StandardMainLoop::init();
   // setup torque for testing.
   GFXInit::enumerateAdapters();
   GFXAdapter* a = GFXInit::chooseAdapter(NullDevice, "");
   GFXDevice* newDevice = GFX;
   if (newDevice == NULL)
      newDevice = GFXInit::createDevice(a);
   newDevice->setAllowRender(false);

   // required for tests that add gui elements.
   Con::evaluate("if (!isObject(GuiDefaultProfile)) new GuiControlProfile(GuiDefaultProfile){}; if (!isObject(GuiTooltipProfile)) new GuiControlProfile(GuiTooltipProfile){};");

   // this call is to add the tests that exist in runTests.tscript
   // note these tests will not appear in the test explorer.
   if(argc > 1)
      StandardMainLoop::handleCommandLine(argc, (const char**)argv);

   // run tests.
   int res = RUN_ALL_TESTS();
   StandardMainLoop::shutdown();
   return 0;
}

DefineEngineFunction(addUnitTest, void, (const char* function), ,
   "Add a TorqueScript function as a GTest unit test.\n"
   "@note This is only implemented rudimentarily to open the door for future development in unit-testing the engine.\n"
   "@tsexample\n"
   "function MyTest() {\n"
   "   expectTrue(2+2 == 4, \"basic math should work\");\n"
   "}\n"
   "addUnitTest(MyTest);\n"
   "@endtsexample\n"
   "@see expectTrue")
{
   Namespace::Entry* entry = Namespace::global()->lookup(StringTable->insert(function));
   const char* file = __FILE__;
   U32 ln = __LINE__;
   if (entry != NULL)
   {
      file = entry->mModule->getName();
      U32 inst;
      entry->mModule->findBreakLine(entry->mFunctionOffset, ln, inst);
   }
   else
   {
      Con::warnf("failed to register unit test %s, could not find the function", function);
   }

   testing::RegisterTest("TorqueScriptFixture", function, NULL, NULL, file, ln,
      [=]() -> TorqueScriptFixture* { return new TorqueScriptTest(function); });
}

String scriptFileMessage(const char* message)
{
   Dictionary* frame = Con::getCurrentStackFrame();
   Con::Module* module = frame->module;
   const char* scriptLine = module->getFileLine(frame->ip);
   return  String::ToString("at %s: %s", scriptLine, message);
}

DefineEngineFunction(expectTrue, void, (bool test, const char* message), (""),
   "TorqueScript wrapper around the EXPECT_TRUE assertion in GTest.\n"
   "@tsexample\n"
   "expectTrue(2+2 == 4, \"basic math should work\");\n"
   "@endtsexample")
{
   EXPECT_TRUE(test) << scriptFileMessage(message).c_str();
}
