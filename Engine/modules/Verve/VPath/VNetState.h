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
#ifndef _VT_VNETSTATE_H_
#define _VT_VNETSTATE_H_

#ifndef _NETCONNECTION_H_
#include "sim/netConnection.h"
#endif

#ifndef _TVECTOR_H_
#include "core/util/tVector.h"
#endif

//-----------------------------------------------------------------------------

struct VNetStateInfo
{
    SimObjectPtr<NetConnection>    Connection;
    U32                            Mask;

    VNetStateInfo( void ) :
        Connection( NULL ),
        Mask( 0 )
    {
        // Void.
    };

    VNetStateInfo( NetConnection *pConnection, U32 pMask )
    {
        Connection = pConnection;
        Mask       = pMask;
    };
};

//-----------------------------------------------------------------------------

class VNetState : public Vector<VNetStateInfo*>
{
protected:

    static U32 gInvalidMask;

    U32    mMask;

public:

    VNetState( void );
    virtual ~VNetState( void );

    // Connection Methods.

    bool             isConnection( NetConnection *pConnection );
    void             addConnection( NetConnection *pConnection );
    void             clearConnection( NetConnection *pConnection );

    // Property Methods.

    VNetStateInfo   *getState( NetConnection *pConnection );

    void             setMaskBits( const U32 &pMask );
    void             clearMaskBits( const U32 &pMask );
};

#endif // _VT_VNETSTATE_H_