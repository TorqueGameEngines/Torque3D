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
#ifndef _VT_VCAMERAGROUP_H_
#define _VT_VCAMERAGROUP_H_

#ifndef _VT_VSCENEOBJECTGROUP_H_
#include "Verve/Extension/SceneObject/VSceneObjectGroup.h"
#endif

#ifndef _VT_VCONTROLLER_H
#include "Verve/Core/VController.h"
#endif

//-----------------------------------------------------------------------------

class VCameraGroup;

//-----------------------------------------------------------------------------

class VCameraGroup : public VSceneObjectGroup
{
    typedef VSceneObjectGroup Parent;

public:

    enum eCameraEventType
    {
        k_EventActivate,
        k_EventDeactivate,
    };

    typedef Signal<bool( const eCameraEventType & )> CameraEventSignal;
    typedef Signal<void( VCameraGroup* )>            CameraChangeSignal;

protected:

    static VCameraGroup         *mActiveGroup;
    static CameraChangeSignal    mCameraChangeSignal;

    CameraEventSignal            mCameraEventSignal;

public:

    VCameraGroup( void );

    // Tree Methods.

    void                   onAttach( void );
    void                   onDetach( void );

    // Controller Methods.

    bool                   onControllerEvent( VController::eControllerEventType pEvent );

    // Camera Methods.

    inline bool            isActive( void ) { return ( bool )( this == getActiveGroup() ); };
    inline VCameraGroup   *getActiveGroup( void ) { return mActiveGroup; };

    void                   setActive( void );

    static void            clearActiveGroup( void );
    static void            setActiveGroup( VCameraGroup *pCameraGroup );

    // Signal Methods.

    static inline CameraChangeSignal   &getCameraChangeSignal( void ) { return mCameraChangeSignal; };
    inline CameraEventSignal           &getCameraEventSignal( void ) { return mCameraEventSignal; };

    // Console Declaration.

    DECLARE_CONOBJECT( VCameraGroup );
};

//-----------------------------------------------------------------------------

#endif // _VT_VCAMERAGROUP_H_