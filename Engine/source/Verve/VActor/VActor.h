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
#ifndef _VT_VACTOR_H_
#define _VT_VACTOR_H_

#ifndef _VT_VACTORDATA_H_
#include "VActorData.h"
#endif

#ifndef _VT_TYPES_H_
#include "Types/VTypes.h"
#endif

//-----------------------------------------------------------------------------
class VActorAnimationController;
class VActorPhysicsController;
//-----------------------------------------------------------------------------

class VActor : public ShapeBase
{
    typedef ShapeBase Parent;

public:

    enum eMaskBits
    {
        // Physics Bits.
        MoveMask     = Parent::NextFreeMask << 0,
        PhysicsMask  = ( MoveMask ),

        NextFreeMask = Parent::NextFreeMask << 1,
    };

    enum eEventType
    {
        k_MountEvent,
        k_UnmountEvent,
    };

    typedef Signal<void( const eEventType& )>    tEventSignal;

protected:

    VActorData     *mDataBlock;

    // Event Signal.
    tEventSignal    mEventSignal;

public:

    VActor( void );
    ~VActor( void );

    // Initialisation Methods.

    bool            onAdd( void );
    void            onRemove( void );

    bool            onNewDataBlock( GameBaseData *pDataBlock, bool pReload );

    // Update Methods.

    virtual void    processTick( const Move *pMove );

    virtual U32     packUpdate( NetConnection *pConnection, U32 pMask, BitStream *pStream );
    virtual void    unpackUpdate( NetConnection *pConnection, BitStream *pStream );

    DECLARE_CONOBJECT( VActor );

public:

    // Accessor Methods.

    inline VActorData     *getDataBlock( void ) { return mDataBlock; };
    inline tEventSignal   &getEventSignal( void ) { return mEventSignal; };

    // Animation Methods.

    /// Get Animation Controller.
    virtual VActorAnimationController *getAnimationController( void ) { return NULL; };

    // Physics Methods.

    /// Set Transform.
    virtual void setTransform( const MatrixF &pMatrix );

    /// Get Physics Controller.
    virtual VActorPhysicsController *getPhysicsController( void ) { return NULL; };

    /// On Mount.
    virtual void onMount( SceneObject *pObject, S32 pNode );
    /// On Unmount.
    virtual void onUnmount( SceneObject *pObject, S32 pNode );
};

#endif // _VT_VACTOR_H_