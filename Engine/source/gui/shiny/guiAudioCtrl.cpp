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
#include "gui/shiny/guiAudioCtrl.h"
#include "console/engineAPI.h"
#include "sfx/sfxSystem.h"
#include "sfx/sfxTrack.h"
#include "sfx/sfxSource.h"

#define TickMs      32

IMPLEMENT_CONOBJECT( GuiAudioCtrl );

ConsoleDocClass( GuiAudioCtrl,
	"@brief Brief Description.\n\n"
	"Audio PLayback.\n\n"

	"@ingroup GuiUtil\n");

GuiAudioCtrl::GuiAudioCtrl()
{
   INIT_ASSET(Sound);
   mTickPeriodMS = 100;
   mLastThink = 0;
   mCurrTick = 0;
   mPlayIf = "";
   mSoundPlaying = NULL;
   setProcessTicks();
}

bool GuiAudioCtrl::onWake()
{
   return Parent::onWake();
}

void GuiAudioCtrl::onSleep()
{
   SFX_DELETE(mSoundPlaying);
   Parent::onSleep();
}

void GuiAudioCtrl::processTick()
{

   if (mLastThink + mTickPeriodMS < mCurrTick)
   {
      mCurrTick = 0;
      mLastThink = 0;
      if (isSoundValid())
      {
         if (testCondition())
         {
            if (getSoundProfile())
            {
               if (mSoundPlaying == NULL)
               {
                  mSoundPlaying = SFX->createSource(getSoundProfile());
               }
               if (mSoundPlaying && !mSoundPlaying->isPlaying())
               {
                  mSoundPlaying->play();
               }
            }
         }
         else
         {
            if (mSoundPlaying != NULL)
            {
               mSoundPlaying->stop();
            }
         }
      }
   }
   else
   {
      mCurrTick += TickMs;
   }
}

bool GuiAudioCtrl::testCondition()
{
   if (mPlayIf.isEmpty())
      return true; //we've got no tests to run so just do it

   //test the mapper plugged in condition line
   String resVar = getIdString() + String(".result");
   Con::setBoolVariable(resVar.c_str(), false);
   String command = resVar + "=" + mPlayIf + ";";
   Con::evaluatef(command.c_str());
   if (Con::getBoolVariable(resVar.c_str()) == 1)
   {
      return true;
   }
   return false;
}

void GuiAudioCtrl::initPersistFields()
{
   addGroup("Sounds");
      INITPERSISTFIELD_SOUNDASSET(Sound, GuiAudioCtrl, "Looping SFXProfile effect to play while GuiAudioCtrl is active.");
      addField("tickPeriodMS", TypeS32, Offset(mTickPeriodMS, GuiAudioCtrl),
         "@brief Time in milliseconds between calls to onTick().\n\n"
         "@see onTickTrigger()\n");
      addField("playIf", TypeCommand, Offset(mPlayIf, GuiAudioCtrl), "evaluation condition to trip playback (true/false)");
   endGroup("Sounds");

   Parent::initPersistFields();
}
