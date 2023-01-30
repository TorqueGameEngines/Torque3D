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
#ifndef _VT_VSOUNDEFFECTEVENT_H_
#define _VT_VSOUNDEFFECTEVENT_H_

#ifndef _VT_VSCENEOBJECTEVENT_H_
#include "Verve/Extension/SceneObject/VSceneObjectEvent.h"
#endif

#ifndef _VT_TORQUE_SOUNDEFFECT_H_
#include "Verve/Torque/TSoundEffect.h"
#endif

//-----------------------------------------------------------------------------

class VSoundEffectEvent : public VSceneObjectEvent
{
    typedef VSceneObjectEvent Parent;

    enum
    {
        SFXStartBuffer = 100,
    };

public:

    SimObjectPtr<VTorque::SoundEffectType>    mSoundEffect;

public:

    VSoundEffectEvent( void );

    static void     initPersistFields();

    static bool     setSoundData( void *pObject, const char *pArray, const char *pData );

    // Event Methods.

    virtual void    onTrigger( const S32 &pTime, const S32 &pDelta );

    // Console Declaration.

    DECLARE_CONOBJECT( VSoundEffectEvent );

public:

    // Property Methods.

    virtual void    setDuration( const S32 &pDuration );
};

//-----------------------------------------------------------------------------

#endif // _VT_VSOUNDEFFECTEVENT_H_