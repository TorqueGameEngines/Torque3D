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
#include "sfx/sfxTypes.h"

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

   mUseTrackDescriptionOnly = false;
   mDescription.mIs3D = false;
   mDescription.mIsLooping = true;
   mDescription.mIsStreaming = false;
   mDescription.mFadeInTime = -1.f;
   mDescription.mFadeOutTime = -1.f;

   mVolume = 1;
   mPitch = 1;
   mFadeInTime = -1;
   mFadeOutTime = -1;
   mSourceGroup = NULL;
   setProcessTicks();
}

GuiAudioCtrl::~GuiAudioCtrl()
{
   if (mSoundPlaying)
      mSoundPlaying->stop();
   SFX_DELETE(mSoundPlaying);
}

bool GuiAudioCtrl::onWake()
{
   return Parent::onWake();
}

void GuiAudioCtrl::onSleep()
{
   if (mSoundPlaying)
      mSoundPlaying->stop();
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
         _update();
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
      INITPERSISTFIELD_SOUNDASSET(Sound, GuiAudioCtrl, "Looping SoundAsset to play while GuiAudioCtrl is active.");
      addField("tickPeriodMS", TypeS32, Offset(mTickPeriodMS, GuiAudioCtrl),
         "@brief Time in milliseconds between calls to onTick().\n\n"
         "@see onTickTrigger()\n");
      addField("playIf", TypeCommand, Offset(mPlayIf, GuiAudioCtrl), "evaluation condition to trip playback (true/false)");
      addField("useTrackDescriptionOnly", TypeBool, Offset(mUseTrackDescriptionOnly, GuiAudioCtrl),
         "If this is true, all fields except for #playOnAdd and #track are ignored on the emitter object.\n"
         "This is useful to prevent fields in the #track's description from being overridden by emitter fields.");
      addField("sourceGroup", TypeSFXSourceName, Offset(mSourceGroup, GuiAudioCtrl),
         "The SFXSource to which to assign the sound of this emitter as a child.\n"
         "@note This field is ignored if #useTrackDescriptionOnly is true.\n\n"
         "@see SFXDescription::sourceGroup");
      addField("volume", TypeF32, Offset(mVolume, GuiAudioCtrl),
         "Volume level to apply to the sound.\n"
         "@note This field is ignored if #useTrackDescriptionOnly is true.\n\n"
         "@see SFXDescription::volume");
      addField("pitch", TypeF32, Offset(mPitch, GuiAudioCtrl),
         "Pitch shift to apply to the sound.  Default is 1 = play at normal speed.\n"
         "@note This field is ignored if #useTrackDescriptionOnly is true.\n\n"
         "@see SFXDescription::pitch");
      addField("fadeInTime", TypeF32, Offset(mFadeInTime, GuiAudioCtrl),
         "Number of seconds to gradually fade in volume from zero when playback starts.\n"
         "@note This field is ignored if #useTrackDescriptionOnly is true.\n\n"
         "@see SFXDescription::fadeInTime");
      addField("fadeOutTime", TypeF32, Offset(mFadeOutTime, GuiAudioCtrl),
         "Number of seconds to gradually fade out volume down to zero when playback is stopped or paused.\n"
         "@note This field is ignored if #useTrackDescriptionOnly is true.\n\n"
         "@see SFXDescription::fadeOutTime");
   endGroup("Sounds");

   Parent::initPersistFields();
}

void GuiAudioCtrl::_update()
{
   if (isSoundValid())
   {
      //mLocalProfile = *mSoundAsset->getSfxProfile();
      mDescription = *mSoundAsset->getSfxDescription();
   }

   // Make sure all the settings are valid.
   mDescription.validate();

   bool useTrackDescriptionOnly = (mUseTrackDescriptionOnly && getSoundProfile());

   if (getSoundProfile())
   {
      if (mSoundPlaying == NULL)
      {
         mSoundPlaying = SFX->createSource(getSoundProfile());
      }
   }

   // The rest only applies if we have a source.
   if (mSoundPlaying && !useTrackDescriptionOnly)
   {
      
      // Set the volume irrespective of the profile.
      if (mSourceGroup)
      {
         mSourceGroup->addObject(mSoundPlaying);
         mSoundPlaying->setVolume(mSourceGroup->getVolume() * mVolume);
      }
      else
      {
         mSoundPlaying->setVolume(mVolume);
      }

      mSoundPlaying->setPitch(mPitch);
      mSoundPlaying->setFadeTimes(mFadeInTime, mFadeOutTime);

   }

   if (testCondition() && isActive() && isAwake())
   {
      if (mSoundPlaying && !mSoundPlaying->isPlaying())
      {
         mSoundPlaying->play();
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
