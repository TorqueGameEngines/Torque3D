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
#ifndef _VT_TORQUE_ANIMATION_H_
#define _VT_TORQUE_ANIMATION_H_

#ifndef _VT_TORQUE_SCENEOBJECT_H_
#include "Verve/Torque/TSceneObject.h"
#endif

namespace VTorque
{
    bool                isAnimationLooping( SceneObjectType *pObject, const char *pData );

    String              getAnimation( SceneObjectType *pObject, const U32 &pThreadIndex );
    F32                 getAnimationDuration( SceneObjectType *pObject, const char *pData );
    void                setAnimationPosition( SceneObjectType *pObject, const U32 &pThreadIndex, const F32 &pPosition );
    void                setAnimationTimeScale( SceneObjectType *pObject, const U32 &pThreadIndex, const F32 &pTimeScale );

    void                playAnimation( SceneObjectType *pObject, const U32 &pThreadIndex, const char *pData );
    void                playAnimation( SceneObjectType *pObject, const U32 &pThreadIndex );
    void                stopAnimation( SceneObjectType *pObject, const U32 &pThreadIndex );
    void                pauseAnimation( SceneObjectType *pObject, const U32 &pThreadIndex );
};

#endif // _VT_TORQUE_ANIMATION_H_