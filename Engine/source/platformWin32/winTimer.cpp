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

// Grab the win32 headers so we can access QPC
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "platform/platformTimer.h"
#include "math/mMath.h"

class Win32Timer : public PlatformTimer
{
private:
   S64 mPerfCountCurrent;
   S64 mPerfCountNext;
   S64 mFrequency;
   F64 mPerfCountRemainderCurrent;
   F64 mPerfCountRemainderNext;
public:

   Win32Timer()
   {
      mPerfCountRemainderCurrent = 0.0f;
      mPerfCountRemainderNext = 0.0f;

      QueryPerformanceFrequency((LARGE_INTEGER *) &mFrequency);
      QueryPerformanceCounter((LARGE_INTEGER *) &mPerfCountCurrent);
      mPerfCountNext = 0.0;
   }

   const S32 getElapsedMs() override
   {
      // Use QPC, update remainders so we don't leak time, and return the elapsed time.
      QueryPerformanceCounter( (LARGE_INTEGER *) &mPerfCountNext);
      F64 elapsedF64 = (1000.0 * F64(mPerfCountNext - mPerfCountCurrent) / F64(mFrequency));
      elapsedF64 += mPerfCountRemainderCurrent;
      U32 elapsed = (U32)mFloor(elapsedF64);
      mPerfCountRemainderNext = elapsedF64 - F64(elapsed);

      return elapsed;
   }

   void reset() override
   {
      // Do some simple copying to reset the timer to 0.
      mPerfCountCurrent = mPerfCountNext;
      mPerfCountRemainderCurrent = mPerfCountRemainderNext;
   }
};

PlatformTimer *PlatformTimer::create()
{
   return new Win32Timer();
}
