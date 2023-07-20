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

#include "windowManager/platformWindow.h"
#include "windowManager/platformWindowMgr.h"
#include "platform/platformInput.h"
#include "platform/input/IProcessInput.h"
#include "windowManager/sdl/sdlWindowMgr.h"
#include "core/util/tVector.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::_;
using ::testing::An;
using ::testing::Matcher;
using ::testing::TypedEq;
using ::testing::Return;
using ::testing::AtLeast;

class MockProcessInput : public IProcessInput
{
public:
   MOCK_METHOD(bool, processInputEvent, (InputEventInfo&), ());
};
class MockWindow : public PlatformWindow
{
public:
   MOCK_METHOD(void, setInputController, (MockProcessInput*), ());
   MOCK_METHOD(WindowId, getWindowId, (), ());
   MOCK_METHOD(void*, getSystemWindow, (const WindowSystem), ());
   MOCK_METHOD(GFXDevice*, getGFXDevice, (), ());
   MOCK_METHOD(GFXWindowTarget*, getGFXTarget, (), ());
   MOCK_METHOD(void, setVideoMode, (const GFXVideoMode&), ());
   MOCK_METHOD(GFXVideoMode&, getVideoMode, (), (const));
   MOCK_METHOD(bool, clearFullscreen, (), ());
   MOCK_METHOD(bool, isFullscreen, (), ());
   
   MOCK_METHOD(void, setBackground, (bool), ());
   MOCK_METHOD(bool, getBackground, (), ());
};

class MockWindowManager : public PlatformWindowManagerSDL
{
public:
   MOCK_METHOD(RectI, getPrimaryDesktopArea, (), ());
   MOCK_METHOD(S32, getDesktopBitDepth, (), ());
   MOCK_METHOD(Point2I, getDesktopResolution, (), ());

   MOCK_METHOD(S32, findFirstMatchingMonitor, (const char*), ());
   MOCK_METHOD(U32, getMonitorCount, (), ());
   MOCK_METHOD(RectI, getMonitorRect, (U32), ());
   MOCK_METHOD(RectI, getMonitorUsableRect, (U32), ());
   MOCK_METHOD(U32, getMonitorModeCount, (U32), ());

   MOCK_METHOD(const String, getMonitorMode, (U32, U32), (const));

   MOCK_METHOD(const String, getMonitorDesktopMode, (U32), (const));

   MOCK_METHOD(void, getMonitorRegions, (Vector<RectI>&), ());
   MOCK_METHOD(PlatformWindow*, createWindow, (GFXDevice*, const GFXVideoMode&), ());
   MOCK_METHOD(void, getWindows, (VectorPtr<PlatformWindow*>&), ());
   MOCK_METHOD(PlatformWindow*, getFocusedWindow, (), ());
   MOCK_METHOD(PlatformWindow*, getWindowById, (WindowId), ());
   MOCK_METHOD(PlatformWindow*, getFirstWindow, (), ());
   MOCK_METHOD(void, setParentWindow, (void*), ());
   MOCK_METHOD(void*, getParentWindow, (), ());
   MOCK_METHOD(void, lowerCurtain, (), ());
   MOCK_METHOD(void, raiseCurtain, (), ());
   MOCK_METHOD(void, setDisplayWindow, (bool), ());
   MOCK_METHOD(void, _processCmdLineArgs, (const S32, const char**), ());

};

MockWindowManager* CreateMockPlatformWindowManager()
{
   return new MockWindowManager();
}
// Mysteriously, TEST(WindowManager, BasicAPI) gives an error. Huh.
TEST(WinMgr, CreateTest) {
   MockWindowManager* pwm = CreateMockPlatformWindowManager();
   ASSERT_TRUE(pwm) << "no monitor to test against!";
};

TEST(WinMgr, PrimaryDesktopAreaTest)
{
   MockWindowManager pwm;

   EXPECT_CALL(pwm, getPrimaryDesktopArea()).WillOnce(Return(RectI(0, 0, 5, 5)));
   RectI rect = pwm.getPrimaryDesktopArea();
   EXPECT_TRUE(rect.isValidRect()) << "Got some sort of invalid rect from the window manager!";
}
