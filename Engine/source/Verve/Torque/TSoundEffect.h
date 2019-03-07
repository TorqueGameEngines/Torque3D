//-----------------------------------------------------------------------------
// Verve
// Copyright (C) 2014 - Violent Tulip
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
#ifndef _VT_TORQUE_SOUNDEFFECT_H_
#define _VT_TORQUE_SOUNDEFFECT_H_

#ifndef _SFXPROFILE_H_
#include "sfx/sfxProfile.h"
#endif

#ifndef _SFXSOUND_H_
#include "sfx/sfxSound.h"
#endif

#ifndef _VT_TORQUE_SCENEOBJECT_H_
#include "Verve/Torque/TSceneObject.h"
#endif

namespace VTorque
{
    typedef SFXProfile     SoundEffectType;
    typedef SFXSound       SoundSourceType;

    bool                   isSoundLooping( SoundEffectType *pSoundProfile );
    S32                    getSoundDuration( SoundEffectType *pSoundProfile );

    SoundSourceType       *playSound( SoundEffectType *pSoundProfile, const U32 &pPosition, const F32 &pPitch );
    SoundSourceType       *playSound( SoundEffectType *pSoundProfile, SceneObjectType *pObject, const U32 &pPosition, const F32 &pPitch );

    void                   playSound( SoundSourceType *pSource );
    void                   pauseSound( SoundSourceType *pSource );
    void                   stopSound( SoundSourceType *pSource );

    void                   setSoundPosition( SoundSourceType *pSource, const U32 &pPosition );
    void                   setSoundPitch( SoundSourceType *pSource, const F32 &pPitch );
};

#endif // _VT_TORQUE_SOUNDEFFECT_H_