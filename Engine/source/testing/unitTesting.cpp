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

#ifdef TORQUE_TESTS_ENABLED

#include "console/console.h"
#include "console/codeBlock.h"
#include "console/engineAPI.h"
#include "console/consoleInternal.h"
#include "unitTesting.h"
#include "memoryTester.h"

#include <gtest/src/gtest-all.cc>

//-----------------------------------------------------------------------------

class TorqueUnitTestListener : public ::testing::EmptyTestEventListener
{
   // Called before a test starts.
   virtual void OnTestStart( const ::testing::TestInfo& testInfo )
   {
      if( mVerbose )
         Con::printf("> Starting Test '%s.%s'",
            testInfo.test_case_name(), testInfo.name());
   }

   // Called after a failed assertion or a SUCCEED() invocation.
   virtual void OnTestPartResult( const ::testing::TestPartResult& testPartResult )
   {
      if ( testPartResult.failed() )
      {
         Con::warnf(">> Failed with '%s' in '%s' at (line:%d)\n",
            testPartResult.summary(),
            testPartResult.file_name(),
            testPartResult.line_number()
            );
      }
      else if( mVerbose )
      {
         Con::printf(">> Passed with '%s' in '%s' at (line:%d)",
            testPartResult.summary(),
            testPartResult.file_name(),
            testPartResult.line_number()
            );
      }
   }

   // Called after a test ends.
   virtual void OnTestEnd( const ::testing::TestInfo& testInfo )
   {
      if( mVerbose )
         Con::printf("> Ending Test '%s.%s'\n",
            testInfo.test_case_name(), testInfo.name());
   }

   bool mVerbose;

public:
   TorqueUnitTestListener( bool verbose ) : mVerbose( verbose ) {}
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

DefineEngineFunction( addUnitTest, void, (const char* function),,
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
      file = entry->mCode->name;
      U32 inst;
      entry->mCode->findBreakLine(entry->mFunctionOffset, ln, inst);
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
   Dictionary* frame = &gEvalState.getCurrentFrame();
   CodeBlock* code = frame->code;
   const char* scriptLine = code->getFileLine(frame->ip);
   return  String::ToString("at %s: %s", scriptLine, message);
}

DefineEngineFunction( expectTrue, void, (bool test, const char* message),(""),
   "TorqueScript wrapper around the EXPECT_TRUE assertion in GTest.\n"
   "@tsexample\n"
   "expectTrue(2+2 == 4, \"basic math should work\");\n"
   "@endtsexample")
{
   EXPECT_TRUE(test) << scriptFileMessage(message).c_str();
}

DefineEngineFunction( runAllUnitTests, int, (const char* testSpecs, const char* reportFormat), (""),
   "Runs engine unit tests. Some tests are marked as 'stress' tests which do not "
   "necessarily check correctness, just performance or possible nondeterministic "
   "glitches. There may also be interactive or networking tests which may be "
   "excluded by using the testSpecs argument.\n"
   "This function should only be called once per executable run, because of "
   "googletest's design.\n\n"

   "@param testSpecs A space-sepatated list of filters for test cases. "
   "See https://code.google.com/p/googletest/wiki/AdvancedGuide#Running_a_Subset_of_the_Tests "
   "and http://stackoverflow.com/a/14021997/945863 "
   "for a description of the flag format.")
{
   Vector<char*> args;
   args.push_back(NULL); // Program name is unused by googletest.
   String specsArg;
   if ( dStrlen( testSpecs ) > 0 )
   {
      specsArg = testSpecs;
      specsArg.replace(' ', ':');
      specsArg.insert(0, "--gtest_filter=");
      args.push_back(const_cast<char*>(specsArg.c_str()));
   }

   String reportFormatArg;
   if ( dStrlen(reportFormat) > 0 )
   {
      reportFormatArg = String::ToString("--gtest_output=%s", reportFormat);
      args.push_back(const_cast<char*>(reportFormatArg.c_str()));
   }
   S32 argc = args.size();

   // Initialize Google Test.
   testing::InitGoogleTest( &argc, args.address() );

   // Fetch the unit test instance.
   testing::UnitTest& unitTest = *testing::UnitTest::GetInstance();

   // Fetch the unit test event listeners.
   testing::TestEventListeners& listeners = unitTest.listeners();

   // Release the default listener.
   delete listeners.Release( listeners.default_result_printer() );

   if ( Con::getBoolVariable( "$Testing::CheckMemoryLeaks", false ) ) {
      // Add the memory leak tester.
      listeners.Append( new testing::MemoryLeakDetector );
   }

   // Add the Torque unit test listener.
   listeners.Append( new TorqueUnitTestListener(false) );

   // Perform googletest run.
   Con::printf( "\nUnit Tests Starting...\n" );
   const S32 result = RUN_ALL_TESTS();
   Con::printf( "... Unit Tests Ended.\n" );

   return result;
}

#endif // TORQUE_TESTS_ENABLED
