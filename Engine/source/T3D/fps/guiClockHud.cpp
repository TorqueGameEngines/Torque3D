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

#include "platform/platform.h"

#include "gui/core/guiControl.h"
#include "console/consoleTypes.h"
#include "T3D/shapeBase.h"
#include "gfx/gfxDrawUtil.h"
#include "console/engineAPI.h"

//-----------------------------------------------------------------------------

/// Vary basic HUD clock.
/// Displays the current simulation time offset from some base. The base time
/// is usually synchronized with the server as mission start time.  This hud
/// currently only displays minutes:seconds.
class GuiClockHud : public GuiControl
{
   typedef GuiControl Parent;

   bool     mShowFrame;
   bool     mShowFill;
   bool     mTimeReversed;

   LinearColorF   mFillColor;
   LinearColorF   mFrameColor;
   LinearColorF   mTextColor;

   S32      mTimeOffset;
   bool     mIsPaused;
   S32      mPausedTime;
   S32      mSignificantTime;
   bool     mSignificantTimeReached;

public:
   GuiClockHud();

   void setTime(F32 newTime);
   void setReverseTime(F32 reverseTime);
   F32  getTime();
   static bool pauseTime(void* object, const char* index, const char* data);
   static bool reverseTime(void* object, const char* index, const char* data);
   static bool setSignificantTime(void* object, const char* index, const char* data);

   void onRender( Point2I, const RectI &) override;
   static void initPersistFields();
   DECLARE_CONOBJECT( GuiClockHud );
   DECLARE_CATEGORY( "Gui Game" );
   DECLARE_DESCRIPTION( "Basic HUD clock. Displays the current simulation time offset from some base." );
   DECLARE_CALLBACK(void, onSignificantTimeReached, (GuiClockHud* obj));
};

IMPLEMENT_CALLBACK(GuiClockHud, onSignificantTimeReached, void, (GuiClockHud* obj), (obj), "Called when the significant time is reached.");

//-----------------------------------------------------------------------------

IMPLEMENT_CONOBJECT( GuiClockHud );

ConsoleDocClass( GuiClockHud,
   "@brief Basic HUD clock. Displays the current simulation time offset from some base.\n"

   "@tsexample\n"
		"\n new GuiClockHud()"
		"{\n"
		"	fillColor = \"0.0 1.0 0.0 1.0\"; // Fills with a solid green color\n"
		"	frameColor = \"1.0 1.0 1.0 1.0\"; // Solid white frame color\n"
		"	textColor = \"1.0 1.0 1.0 1.0\"; // Solid white text Color\n"
		"	showFill = \"true\";\n"
		"	showFrame = \"true\";\n"
		"};\n"
   "@endtsexample\n\n"

   "@ingroup GuiGame\n"
);

GuiClockHud::GuiClockHud()
{
   mShowFrame = mShowFill = true;
   mTimeReversed = false;
   mFillColor.set(0, 0, 0, 0.5);
   mFrameColor.set(0, 1, 0, 1);
   mTextColor.set( 0, 1, 0, 1 );

   mTimeOffset = 0;
   mIsPaused = false;
   mPausedTime = 0;
   mSignificantTime = 0;
   mSignificantTimeReached = false;
}

void GuiClockHud::initPersistFields()
{
   docsURL;
   addGroup("Misc");		
   addField( "showFill", TypeBool, Offset( mShowFill, GuiClockHud ), "If true, draws a background color behind the control.");
   addField( "showFrame", TypeBool, Offset( mShowFrame, GuiClockHud ), "If true, draws a frame around the control." );
   addField( "fillColor", TypeColorF, Offset( mFillColor, GuiClockHud ), "Standard color for the background of the control." );
   addField( "frameColor", TypeColorF, Offset( mFrameColor, GuiClockHud ), "Color for the control's frame." );
   addField( "textColor", TypeColorF, Offset( mTextColor, GuiClockHud ), "Color for the text on this control." );
   addProtectedField("pause", TypeBool, Offset(mIsPaused, GuiClockHud), &GuiClockHud::pauseTime, &defaultProtectedGetFn, "Pause");
   addProtectedField("reversed", TypeBool, Offset(mTimeReversed, GuiClockHud), &GuiClockHud::reverseTime, &defaultProtectedGetFn, "reversed");
   addProtectedField("significantTime", TypeS32, Offset(mSignificantTime, GuiClockHud), &GuiClockHud::setSignificantTime, &defaultProtectedGetFn, "set significant timestamp");
   endGroup("Misc");

   Parent::initPersistFields();
}


//-----------------------------------------------------------------------------

void GuiClockHud::onRender(Point2I offset, const RectI &updateRect)
{
   GFXDrawUtil* drawUtil = GFX->getDrawUtil();

   // Background first
   if (mShowFill)
      drawUtil->drawRectFill(updateRect, mFillColor.toColorI());

   // Convert ms time into hours, minutes and seconds.
   S32 time = mIsPaused ? mPausedTime : S32(getTime());
   S32 secs = time % 60;
   S32 mins = (time % 3600) / 60;

   // Currently only displays min/sec
   char buf[256];
   dSprintf(buf,sizeof(buf), "%02d:%02d",mins,secs);

   // Center the text
   offset.x += (getWidth() - mProfile->mFont->getStrWidth((const UTF8 *)buf)) / 2;
   offset.y += (getHeight() - mProfile->mFont->getHeight()) / 2;
   drawUtil->setBitmapModulation(mTextColor.toColorI());
   drawUtil->drawText(mProfile->mFont, offset, buf);
   drawUtil->clearBitmapModulation();

   // Border last
   if (mShowFrame)
      drawUtil->drawRect(updateRect, mFrameColor.toColorI());

   if (!mIsPaused && !mSignificantTimeReached)
   {
      if (mTimeReversed && time < mSignificantTime)
      {
         onSignificantTimeReached_callback(this);
         mSignificantTimeReached = true;
      }
      else if (time > mSignificantTime)
      {
         onSignificantTimeReached_callback(this);
         mSignificantTimeReached = true;
      }
   }
}


//-----------------------------------------------------------------------------

void GuiClockHud::setReverseTime(F32 time)  
{  
   // Set the current time in seconds.  
   mTimeReversed = true;  
   mTimeOffset = S32(time * 1000) + Platform::getVirtualMilliseconds();
   mSignificantTimeReached = false;
   mPausedTime = getTime();
}

void GuiClockHud::setTime(F32 time)
{
   // Set the current time in seconds.
   mTimeReversed = false;
   mTimeOffset = S32(time * 1000) - Platform::getVirtualMilliseconds();
   mSignificantTimeReached = false;
   mPausedTime = getTime();
}

F32 GuiClockHud::getTime()
{
   // Return elapsed time in seconds.
   if(mTimeReversed)
      return F32(mTimeOffset - Platform::getVirtualMilliseconds()) / 1000;  
   else
      return F32(mTimeOffset + Platform::getVirtualMilliseconds()) / 1000;
}

bool GuiClockHud::pauseTime(void* object, const char* index, const char* data)
{
   GuiClockHud* obj = reinterpret_cast<GuiClockHud*>(object);
   obj->mIsPaused = dAtob(data);

   if (obj->mIsPaused)
      obj->mPausedTime = S32(obj->getTime());
   else
      obj->setTime(obj->mPausedTime);

   return true;
}

bool GuiClockHud::reverseTime(void* object, const char* index, const char* data)
{
   GuiClockHud* obj = reinterpret_cast<GuiClockHud*>(object);
   F32 curTime = obj->getTime();

   bool setReverse = dAtob(data);
   if (setReverse)
      obj->setReverseTime(curTime);
   else
      obj->setTime(curTime);

   return true;
}

bool GuiClockHud::setSignificantTime(void* object, const char* index, const char* data)
{
   GuiClockHud* obj = reinterpret_cast<GuiClockHud*>(object);
   obj->mSignificantTime = dAtoi(data);
   obj->mSignificantTimeReached = false;
   return true;
}

DefineEngineMethod(GuiClockHud, setTime, void, (F32 timeInSeconds),(60), "Sets the current base time for the clock.\n"
													"@param timeInSeconds Time to set the clock, in seconds (IE: 00:02 would be 120)\n"
													"@tsexample\n"
														"// Define the time, in seconds\n"
														"%timeInSeconds = 120;\n\n"
														"// Change the time on the GuiClockHud control\n"
														"%guiClockHud.setTime(%timeInSeconds);\n"
													"@endtsexample\n"
				  )
{
   object->setTime(timeInSeconds);
}

DefineEngineMethod(GuiClockHud, setReverseTime, void, (F32 timeInSeconds),(60), "@brief Sets a time for a countdown clock.\n\n"
   												"Setting the time like this will cause the clock to count backwards from the specified time.\n\n"
													"@param timeInSeconds Time to set the clock, in seconds (IE: 00:02 would be 120)\n\n"
													"@see setTime\n"
				  )
{
   object->setReverseTime(timeInSeconds);
}

DefineEngineMethod(GuiClockHud, getTime, F32, (),, "Returns the current time, in seconds.\n"
													"@return timeInseconds Current time, in seconds\n"
													"@tsexample\n"
														"// Get the current time from the GuiClockHud control\n"
														"%timeInSeconds = %guiClockHud.getTime();\n"
													"@endtsexample\n"
				  )
{
   return object->getTime();
}
