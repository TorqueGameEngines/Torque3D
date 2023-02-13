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

   setProcessTicks();
}

GuiAudioCtrl::~GuiAudioCtrl()
{
   SFX_DELETE(mSoundPlaying);
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
      INITPERSISTFIELD_SOUNDASSET(Sound, GuiAudioCtrl, "Looping SFXProfile effect to play while GuiAudioCtrl is active.");
      addField("tickPeriodMS", TypeS32, Offset(mTickPeriodMS, GuiAudioCtrl),
         "@brief Time in milliseconds between calls to onTick().\n\n"
         "@see onTickTrigger()\n");
      addField("playIf", TypeCommand, Offset(mPlayIf, GuiAudioCtrl), "evaluation condition to trip playback (true/false)");
      addField("useTrackDescriptionOnly", TypeBool, Offset(mUseTrackDescriptionOnly, GuiAudioCtrl),
         "If this is true, all fields except for #playOnAdd and #track are ignored on the emitter object.\n"
         "This is useful to prevent fields in the #track's description from being overridden by emitter fields.");
      addField("isLooping", TypeBool, Offset(mDescription.mIsLooping, GuiAudioCtrl),
         "Whether to play #fileName in an infinite loop.\n"
         "If a #track is assigned, the value of this field is ignored.\n"
         "@see SFXDescription::isLooping");
      addField("isStreaming", TypeBool, Offset(mDescription.mIsStreaming, GuiAudioCtrl),
         "Whether to use streamed playback for #fileName.\n"
         "If a #track is assigned, the value of this field is ignored.\n"
         "@see SFXDescription::isStreaming\n\n"
         "@ref SFX_streaming");
      addField("sourceGroup", TypeSFXSourceName, Offset(mDescription.mSourceGroup, GuiAudioCtrl),
         "The SFXSource to which to assign the sound of this emitter as a child.\n"
         "@note This field is ignored if #useTrackDescriptionOnly is true.\n\n"
         "@see SFXDescription::sourceGroup");
      addField("volume", TypeF32, Offset(mDescription.mVolume, GuiAudioCtrl),
         "Volume level to apply to the sound.\n"
         "@note This field is ignored if #useTrackDescriptionOnly is true.\n\n"
         "@see SFXDescription::volume");
      addField("pitch", TypeF32, Offset(mDescription.mPitch, GuiAudioCtrl),
         "Pitch shift to apply to the sound.  Default is 1 = play at normal speed.\n"
         "@note This field is ignored if #useTrackDescriptionOnly is true.\n\n"
         "@see SFXDescription::pitch");
      addField("fadeInTime", TypeF32, Offset(mDescription.mFadeInTime, GuiAudioCtrl),
         "Number of seconds to gradually fade in volume from zero when playback starts.\n"
         "@note This field is ignored if #useTrackDescriptionOnly is true.\n\n"
         "@see SFXDescription::fadeInTime");
      addField("fadeOutTime", TypeF32, Offset(mDescription.mFadeOutTime, GuiAudioCtrl),
         "Number of seconds to gradually fade out volume down to zero when playback is stopped or paused.\n"
         "@note This field is ignored if #useTrackDescriptionOnly is true.\n\n"
         "@see SFXDescription::fadeOutTime");
   endGroup("Sounds");

   Parent::initPersistFields();
}

void GuiAudioCtrl::onStaticModified(const char* slotName, const char* newValue)
{
   // Lookup and store the property names once here
   // and we can then just do pointer compares. 
   static StringTableEntry slotTrack = StringTable->lookup("track");
   static StringTableEntry slotFilename = StringTable->lookup("fileName");
   static StringTableEntry slotVolume = StringTable->lookup("volume");
   static StringTableEntry slotPitch = StringTable->lookup("pitch");
   static StringTableEntry slotIsLooping = StringTable->lookup("isLooping");
   static StringTableEntry slotIsStreaming = StringTable->lookup("isStreaming");
   static StringTableEntry slotFadeInTime = StringTable->lookup("fadeInTime");
   static StringTableEntry slotFadeOutTime = StringTable->lookup("fadeOutTime");
   static StringTableEntry slotSourceGroup = StringTable->lookup("sourceGroup");
   static StringTableEntry slotUseTrackDescriptionOnly = StringTable->lookup("useTrackDescriptionOnly");

   // Set the dirty flags.
   mDirty.clear();
   if (slotName == slotTrack)
      mDirty.set(Track);

   else if (slotName == slotFilename)
      mDirty.set(Filename);

   else if (slotName == slotVolume)
      mDirty.set(Volume);

   else if (slotName == slotPitch)
      mDirty.set(Pitch);

   else if (slotName == slotIsLooping)
      mDirty.set(IsLooping);

   else if (slotName == slotIsStreaming)
      mDirty.set(IsStreaming);

   else if (slotName == slotFadeInTime)
      mDirty.set(FadeInTime);

   else if (slotName == slotFadeOutTime)
      mDirty.set(FadeOutTime);

   else if (slotName == slotSourceGroup)
      mDirty.set(SourceGroup);

   else if (slotName == slotUseTrackDescriptionOnly)
      mDirty.set(TrackOnly);
}

void GuiAudioCtrl::_update()
{
   // Store the playback status so we
   // we can restore it.
   SFXStatus prevState = mSoundPlaying ? mSoundPlaying->getStatus() : SFXStatusNull;

   if (mSoundAsset.notNull() && mDirty.test(Track | Filename))
   {
      //mLocalProfile = *mSoundAsset->getSfxProfile();
      mDescription = *mSoundAsset->getSfxDescription();
   }

   // Make sure all the settings are valid.
   mDescription.validate();

   // Did we change the source?
   if (mDirty.test(Track | Filename | IsLooping | IsStreaming | TrackOnly))
   {
      SFX_DELETE(mSoundPlaying);

      // Do we have a track?
      if (mSoundAsset && mSoundAsset->getSfxProfile())
      {
         mSoundPlaying = SFX->createSource(getSoundProfile());
         if (!mSoundPlaying)
            Con::errorf("SFXEmitter::_update() - failed to create sound for track %i (%s)",
               mSoundAsset->getSfxProfile()->getId(), mSoundAsset->getSfxProfile()->getName());

         // If we're supposed to play when the emitter is 
         // added to the scene then also restart playback 
         // when the profile changes.
         prevState = testCondition() ? SFXStatusPlaying : prevState;

         // Force an update of properties set on the local description.

         mDirty.set(AllDirtyMask);
      }

      mDirty.clear(Track | Filename | IsLooping | IsStreaming | TrackOnly);
   }

   // Cheat if the editor is open and the looping state
   // is toggled on a local profile sound.  It makes the
   // editor feel responsive and that things are working.
   if ((mSoundAsset.isNull() || !mSoundAsset->getSfxProfile()) && testCondition() && mDirty.test(IsLooping))
      prevState = SFXStatusPlaying;

   bool useTrackDescriptionOnly = (mUseTrackDescriptionOnly && mSoundAsset.notNull() && mSoundAsset->getSfxProfile());

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

   // The rest only applies if we have a source.
   if (mSoundPlaying)
   {
      // Set the volume irrespective of the profile.
      if (mDirty.test(Volume) && !useTrackDescriptionOnly)
         mSoundPlaying->setVolume(mDescription.mVolume);

      if (mDirty.test(Pitch) && !useTrackDescriptionOnly)
         mSoundPlaying->setPitch(mDescription.mPitch);

      if (mDirty.test(FadeInTime | FadeOutTime) && !useTrackDescriptionOnly)
         mSoundPlaying->setFadeTimes(mDescription.mFadeInTime, mDescription.mFadeOutTime);

      if (mDirty.test(SourceGroup) && mDescription.mSourceGroup && !useTrackDescriptionOnly)
         mDescription.mSourceGroup->addObject(mSoundPlaying);

      // Restore the pre-update playback state.
      if (prevState == SFXStatusPlaying)
         mSoundPlaying->play();

      mDirty.clear(Volume | Pitch | FadeInTime | FadeOutTime | SourceGroup);
   }
}
