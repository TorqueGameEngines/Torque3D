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
#ifndef _VT_VTORQUE3D_POSTEFFECT_H_
#define _VT_VTORQUE3D_POSTEFFECT_H_

#ifndef _VT_TORQUE_POSTEFFECT_H_
#include "Verve/Torque/TPostEffect.h"
#endif

#ifndef _NETCONNECTION_H_
#include "sim/netConnection.h"
#endif

class VPostEffectNetEvent : public NetEvent
{
    typedef NetEvent Parent;

public:

    StringTableEntry    mPostEffect;
    bool                mEnabled;

public:

    VPostEffectNetEvent( void );

    void            write( NetConnection *pConnection, BitStream *pStream );
    void            pack( NetConnection *pConnection, BitStream *pStream );
    void            unpack( NetConnection *pConnection, BitStream *pStream );
    void            process( NetConnection *pConnection );

    DECLARE_CONOBJECT( VPostEffectNetEvent );
};

#endif // _VT_VTORQUE3D_POSTEFFECT_H_