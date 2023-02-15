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

#ifndef _GUIAUDIOCTRL_H_
#define _GUIAUDIOCTRL_H_

#ifndef _GUITICKCTRL_H_
#include "gui/shiny/guiTickCtrl.h"
#endif

#ifndef SOUND_ASSET_H
#include "T3D/assets/SoundAsset.h"
#endif

/// This Gui Control is designed to be subclassed to let people create controls
/// which want to receive update ticks at a constant interval. This class was
/// created to be the Parent class of a control which used a DynamicTexture
/// along with a VectorField to create warping effects much like the ones found
/// in visualization displays for iTunes or Winamp. Those displays are updated
/// at the framerate frequency. This works fine for those effects, however for
/// an application of the same type of effects for things like Gui transitions
/// the framerate-driven update frequency is not desirable because it does not
/// allow the developer to be able to have any idea of a consistent user-experience.
///
/// Enter the ITickable interface. This lets the Gui control, in this case, update
/// the dynamic texture at a constant rate of once per tick, even though it gets
/// rendered every frame, thus creating a framerate-independent update frequency
/// so that the effects are at a consistent speed regardless of the specifics
/// of the system the user is on. This means that the screen-transitions will
/// occur in the same time on a machine getting 300fps in the Gui shell as a
/// machine which gets 150fps in the Gui shell.
/// @see ITickable
class GuiAudioCtrl : public GuiTickCtrl
{
   typedef GuiTickCtrl Parent;

private:

protected:

   // So this can be instantiated and not be a pure virtual class
   void interpolateTick( F32 delta ) {};
   void processTick();
   void advanceTime( F32 timeDelta ) {};

   S32 mTickPeriodMS;
   U32 mLastThink;
   U32 mCurrTick;
   String mPlayIf;
   SFXSource* mSoundPlaying;
   /// Whether to leave sound setup exclusively to the assigned mTrack and not
   /// override part of the track's description with emitter properties.
   bool mUseTrackDescriptionOnly;

   /// The description and variant values used by the local profile.
   SFXDescription mDescription;
   SFXSource* mSourceGroup;
   F32 mVolume;
   F32 mPitch;
   F32 mFadeInTime;
   F32 mFadeOutTime;

   /// Called when the emitter state has been marked
   /// dirty and the source needs to be updated.
   void _update();

public:
   DECLARE_SOUNDASSET(GuiAudioCtrl, Sound);
   DECLARE_ASSET_SETGET(GuiAudioCtrl, Sound);
   GuiAudioCtrl();
   ~GuiAudioCtrl();
   // GuiControl.
   bool onWake();
   void onSleep();
   void setActive(bool value) {};
   bool testCondition();
   static void initPersistFields();
   DECLARE_CONOBJECT(GuiAudioCtrl);
   DECLARE_CATEGORY( "Gui Other" );
};


#endif
