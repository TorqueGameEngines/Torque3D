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

#include "util/fpsTracker.h"
#include "console/console.h"
#include "console/engineAPI.h"

FPSTracker gFPS;

FPSTracker::FPSTracker()
{
   mUpdateInterval = 0.25f;
   reset();
}

void FPSTracker::reset()
{
   fpsNext         = (F32)Platform::getRealMilliseconds()/1000.0f + mUpdateInterval;

   fpsAccumTime      = 0.0f;
   fpsAccumVirtualTime = 0.0f;
   fpsRealLast       = 0.0f;
   fpsReal           = 0.0f;
   fpsRealMin        = 0.000001f; // Avoid division by zero.
   fpsRealMax        = 1.0f;
   fpsVirtualLast    = 0.0f;
   fpsVirtual        = 0.0f;
   fpsFrames         = 0;
}

void FPSTracker::update()
{
   const F32 alpha  = 0.07f;
   F32 realSeconds    = (F32)Platform::getRealMilliseconds()/1000.0f;
   F32 virtualSeconds = (F32)Platform::getVirtualMilliseconds()/1000.0f;

   if (fpsRealLast == 0.0f)
   {
      fpsRealLast = realSeconds;
      fpsVirtualLast = virtualSeconds;
      return;
   }

   F32 frameTimeReal = realSeconds - fpsRealLast;
   F32 frameTimeVirtual = virtualSeconds - fpsVirtualLast;

   fpsRealLast = realSeconds;
   fpsVirtualLast = virtualSeconds;

   // Accumulate for windowed FPS calculation
   fpsFrames++;
   fpsAccumTime += frameTimeReal;
   fpsAccumVirtualTime += frameTimeVirtual;

   // Only update console values at interval
   if (realSeconds >= fpsNext)
   {
      fpsReal = 0.0f;
      fpsVirtual = 0.0f;

      if (fpsAccumTime > 0.0f)
         fpsReal = fpsFrames / fpsAccumTime;

      if (fpsAccumVirtualTime > 0.0f)
         fpsVirtual = fpsFrames / fpsAccumVirtualTime;

      // Update min/max correctly (these are FPS now)
      if (fpsReal > 0.0f)
      {
         if (fpsReal < fpsRealMin)
            fpsRealMin = fpsReal;

         if (fpsReal > fpsRealMax)
            fpsRealMax = fpsReal;
      }

      // frameDelta = actual accumulated real time over window
      Con::setVariable("fps::frameTimeMs",   avar("%4.3f", (fpsAccumTime / fpsFrames) * 1000.0f));
      Con::setVariable("fps::frameDelta",    avar("%g", fpsAccumTime));
      Con::setVariable("fps::real",          avar("%4.1f", fpsReal));
      Con::setVariable("fps::realMin",       avar("%4.1f", fpsRealMin));
      Con::setVariable("fps::realMax",       avar("%4.1f", fpsRealMax));
      Con::setVariable("fps::virtual",       avar("%4.1f", fpsVirtual));

      // Reset window
      fpsFrames = 0;
      fpsAccumTime = 0.0f;
      fpsAccumVirtualTime = 0.0f;

      fpsNext = realSeconds + mUpdateInterval;
   }
}

DefineEngineFunction( resetFPSTracker, void, (), , "()"
   "@brief Reset FPS stats (fps::)\n\n"
   "@ingroup Game")
{
   gFPS.reset();
}
