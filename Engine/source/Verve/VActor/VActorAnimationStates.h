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
#ifndef _VT_VACTORANIMATIONSTATES_H_
#define _VT_VACTORANIMATIONSTATES_H_

#ifndef _VT_VACTORSTATETABLE_H_
#include "VActorStateTable.h"
#endif

#ifndef _TSINGLETON_H_
#include "core/util/tSingleton.h"
#endif

//-----------------------------------------------------------------------------

class VActorAnimationState : public VActorState
{
public:

    virtual void    exit( VActor *pObject ) {};
};

//-----------------------------------------------------------------------------

#define DeclareActorAnimationState( name )                                    \
    class VActor##name##AnimationState : public VActorAnimationState          \
    {                                                                         \
    public:                                                                   \
        void            enter( VActor *pObject );                    \
        bool            execute( VActor *pObject );                  \
    }

#define ActorAnimationStateInstance( name )                                   \
    Singleton<VActor##name##AnimationState>::instance()

#define ImplementActorAnimationState( name, sequence )                        \
    void VActor##name##AnimationState::enter( VActor *pObject ) { pObject->getAnimationController()->setAnimation( sequence ); }

#define ExecuteActorAnimationState( name )                                    \
    bool VActor##name##AnimationState::execute( VActor *pObject )

//-----------------------------------------------------------------------------

#endif // _VT_VACTORANIMATIONSTATES_H_