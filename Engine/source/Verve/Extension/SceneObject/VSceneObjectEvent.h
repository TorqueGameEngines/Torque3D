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
#ifndef _VT_VSCENEOBJECTEVENT_H_
#define _VT_VSCENEOBJECTEVENT_H_

#ifndef _VT_VEVENT_H_
#include "Verve/Core/VTrack.h"
#endif

#ifndef _VT_VSCENEOBJECTGROUP_H_
#include "Verve/Extension/SceneObject/VSceneObjectGroup.h"
#endif

//-----------------------------------------------------------------------------

class VSceneObjectEvent : public VEvent
{
    typedef VEvent Parent;

public:

    VSceneObjectEvent( void );

    // Reference Methods.

    VTorque::SceneObjectType   *getSceneObject( void );
    template <class T> inline bool getSceneObject( T *&pSceneObject )
    {
        // Reference Scene Object.
        pSceneObject = dynamic_cast<T*>( getSceneObject() );

        // Valid?
        return ( pSceneObject != NULL );
    }

    // Console Declaration.

    DECLARE_CONOBJECT( VSceneObjectEvent );
};

//-----------------------------------------------------------------------------

#endif // _VT_VSCENEOBJECTEVENT_H_