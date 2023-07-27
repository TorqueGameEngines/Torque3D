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

#include "windowManager/platformWindow.h"
#include "windowManager/platformWindowMgr.h"
#include "platform/platformInput.h"
#include "platform/input/IProcessInput.h"
#include "windowManager/sdl/sdlWindowMgr.h"
#include "core/util/tVector.h"

#include <SDL.h>

using ::testing::Matcher;
using ::testing::TypedEq;

class PlatformWindowManagerSDLTest : public ::testing::Test
{
protected:
   PlatformWindowManagerSDLTest()
   {
      putenv("SDL_VIDEODRIVER=dummy");
      putenv("SDL_AUDIODRIVER=dummy");

      // for tests in this class we probably only need the init_video an nothing else.
      SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_HAPTIC | SDL_INIT_GAMECONTROLLER | SDL_INIT_EVENTS | SDL_INIT_NOPARACHUTE);
   }

   void SetUp() override
   {
   }

   void TearDown() override
   {
   }
};

TEST_F(PlatformWindowManagerSDLTest, Constructor)
{
   PlatformWindowManagerSDL* pwm = static_cast<PlatformWindowManagerSDL*>(CreatePlatformWindowManager());
   ASSERT_TRUE(pwm) << "no monitor to test against!";
}

TEST_F(PlatformWindowManagerSDLTest, PrimaryRectTest)
{
   PlatformWindowManagerSDL* pwm = static_cast<PlatformWindowManagerSDL*>(CreatePlatformWindowManager());
   // Check out the primary desktop area...
   RectI primary = pwm->getPrimaryDesktopArea();

   EXPECT_TRUE(primary.isValidRect())
      << "Got some sort of invalid rect from the window manager!";
}

TEST_F(PlatformWindowManagerSDLTest, MonitorRectsValid)
{
   PlatformWindowManagerSDL* pwm = static_cast<PlatformWindowManagerSDL*>(CreatePlatformWindowManager());
   // Now try to get info about all the monitors.
   Vector<RectI> monitorRects;
   pwm->getMonitorRegions(monitorRects);

   // should override the function above to test this with multiple setups.
   for (S32 i = 0; i < monitorRects.size(); i++)
   {
      EXPECT_TRUE(monitorRects[i].isValidRect())
         << "Got an invalid rect for this monitor - no good.";
   }
}

TEST_F(PlatformWindowManagerSDLTest, MonitorRectsAtLeastOne)
{
   PlatformWindowManagerSDL* pwm = static_cast<PlatformWindowManagerSDL*>(CreatePlatformWindowManager());
   // Now try to get info about all the monitors.
   Vector<RectI> monitorRects;
   pwm->getMonitorRegions(monitorRects);

   EXPECT_GT(monitorRects.size(), 0)
      << "Should get at least one monitor rect back from getMonitorRegions!";
}

TEST_F(PlatformWindowManagerSDLTest, MonitorRectsOverflow)
{
   PlatformWindowManagerSDL* pwm = static_cast<PlatformWindowManagerSDL*>(CreatePlatformWindowManager());
   // Now try to get info about all the monitors.
   Vector<RectI> monitorRects;
   pwm->getMonitorRegions(monitorRects);

   // This test is here just to detect overflow/runaway situations. -- BJG
   EXPECT_LT(monitorRects.size(), 64)
      << "Either something's wrong, or you have a lot of monitors...";
}
