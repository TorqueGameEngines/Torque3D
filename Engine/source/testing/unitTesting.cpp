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

#include "console/console.h"
#include "console/codeBlock.h"
#include "console/engineAPI.h"
#include "console/consoleInternal.h"
#include "unitTesting.h"
#include "memoryTester.h"

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

String scriptFileMessage(const char* message)
{
   Dictionary* frame = &gEvalState.getCurrentFrame();
   CodeBlock* code = frame->code;
   const char* scriptLine = code->getFileLine(frame->ip);
   return  String::ToString("at %s: %s", scriptLine, message);
}
