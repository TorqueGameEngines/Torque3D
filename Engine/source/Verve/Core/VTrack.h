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
#ifndef _VT_VTRACK_H_
#define _VT_VTRACK_H_

#ifndef _VT_VCONTROLLER_H_
#include "Verve/Core/VController.h"
#endif

#ifndef _VT_VEVENT_H_
#include "Verve/Core/VEvent.h"
#endif

#ifndef _VT_TORQUE_SCENEOBJECT_H_
#include "Verve/Torque/TSceneObject.h"
#endif

//-----------------------------------------------------------------------------
class VGroup;
//-----------------------------------------------------------------------------

class VTrack : public VObject
{
    typedef VObject Parent;

public:

    // Controller Members.

    VEvent         *mNextEvent;

public:

    VTrack();

    // Tree Methods.

    virtual void    onAttach( void );
    virtual void    onDetach( void );

    // Controller Methods.

    virtual void    onControllerUpdate( const S32 &pTime, const S32 &pDelta );
    virtual bool    onControllerEvent( VController::eControllerEventType pEvent );

    virtual void    onControllerReset( const S32 &pTime, const bool &pForward );

    // Reference Methods.

    void            sort( void );
    bool            updateNextEvent( void );

    // Console Declaration.

    DECLARE_CONOBJECT( VTrack );

public:

    // Property Methods.

    VGroup   *getGroup( void );
    template <class T> inline bool getGroup( T *&pGroup )
    {
        // Reference Group.
        pGroup = dynamic_cast<T*>( getGroup() );
        // Validate.
        return ( pGroup != NULL );
    }

    VEvent   *getNextEvent( void );
    template <class T> inline bool getNextEvent( T *&pEvent )
    {
        // Reference Object.
        pEvent = dynamic_cast<T*>( getNextEvent() );
        // Validate.
        return ( pEvent != NULL );
    }

    VEvent   *getCurrentEvent( void );
    template <class T> inline bool getCurrentEvent( T *&pEvent )
    {
        // Reference Object.
        pEvent = dynamic_cast<T*>( getCurrentEvent() );
        // Validate.
        return ( pEvent != NULL );
    }

    VEvent   *getPreviousEvent( void );
    template <class T> inline bool getPreviousEvent( T *&pEvent )
    {
        // Reference Object.
        pEvent = dynamic_cast<T*>( getPreviousEvent() );
        // Validate.
        return ( pEvent != NULL );
    }

    F32             calculateInterp( S32 pTime );
    F32            _calculateInterp( S32 pTime );
};

//-----------------------------------------------------------------------------

#endif // _VT_VTRACK_H_