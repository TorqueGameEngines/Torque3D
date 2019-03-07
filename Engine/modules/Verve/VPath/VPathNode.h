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
#ifndef _VT_VPATHNODE_H_
#define _VT_VPATHNODE_H_

#ifndef _GAMEBASE_H_
#include "T3D/gameBase/gameBase.h"
#endif

#ifndef _VNETSTATE_H_
#include "VNetState.h"
#endif

//-----------------------------------------------------------------------------

class VPath;
class VPathNode
{
public:

    enum eState
    {
        k_StateUpdatePosition    = BIT( 0 ),
        k_StateUpdateRotation    = BIT( 1 ),
        k_StateUpdateWeight      = BIT( 2 ),

        k_StateUpdateOrientation = BIT( 3 ),

        k_StateCreate            = BIT( 4 ),
        k_StateDelete            = BIT( 5 ),

        k_StateUpdate            = ( k_StateUpdatePosition | k_StateUpdateRotation | k_StateUpdateWeight | k_StateUpdateOrientation ),

        k_StateInit              = ( k_StateCreate | k_StateUpdate ),
    };

    enum eOrientationType
    {
        k_OrientationFree,
        k_OrientationToPoint,

        k_OrientationTypeSize,
    };

    struct sOrientation
    {
        eOrientationType    Type;

        // k_OrientationToPoint
        Point3F             Point;
    };

protected:

    VPath          *mPath;

    VNetState       mNetState;

    sOrientation    mOrientationMode;

    Point3F         mLocalPosition;
    QuatF           mLocalRotation;

    Point3F         mWorldPosition;
    QuatF           mWorldRotation;

    F32             mWeight;
    F32             mLength;

public:

    VPathNode( void );
    virtual ~VPathNode( void );

    // Serialisation Methods.

    virtual U32             packNode( NetConnection *pConnection, BitStream *pStream );
    virtual void            unpackNode( NetConnection *pConnection, BitStream *pStream );

    virtual String          toString( void );
    virtual bool            fromString( const String &pString );

    //-------------------------------------------------------------------------
    //
    // Gets
    //
    //-------------------------------------------------------------------------

    inline VPath               *getPath( void ) const { return mPath; };

    inline const Point3F       &getLocalPosition( void ) const { return mLocalPosition; };
    inline const QuatF         &getLocalRotation( void ) const { return mLocalRotation; };

    virtual Point3F             getWorldPosition( void ) const;
    virtual QuatF               getWorldRotation( void ) const;
    virtual MatrixF             getWorldTransform( void ) const;

    inline const F32            &getWeight( void ) const { return mWeight; };
    inline const F32            &getLength( void ) const { return mLength; };

    inline const sOrientation   &getOrientationMode( void ) const { return mOrientationMode; };

    //-------------------------------------------------------------------------
    //
    // Sets
    //
    //-------------------------------------------------------------------------

    inline void             setPath( VPath *pPath ) { mPath = pPath; };

    void                    setLocalPosition( const Point3F &pPosition );
    void                    setLocalRotation( const QuatF &pRotation );

    inline void             setWorldPosition( const Point3F &pPosition ) { mWorldPosition = pPosition; };
    inline void             setWorldRotation( const QuatF &pRotation ) { mWorldRotation = pRotation; };

    void                    setWeight( const F32 &pWeight );
    inline void             setLength( const F32 &pLength ) { mLength = pLength; };
    
    void                    setOrientationMode( const eOrientationType &pType );
    void                    setOrientationMode( const eOrientationType &pType, const Point3F &pPoint );

    void                    updateWorldData( void );

    // Net State Methods.

    inline VNetStateInfo   *getState( NetConnection *pConnection ) { return mNetState.getState( pConnection );         };

    inline void             setMaskBits( const U32 &pMask ) { mNetState.setMaskBits( pMask );                          };
    inline void             clearMaskBits( const U32 &pMask ) { mNetState.clearMaskBits( pMask );                      };

    inline bool             isConnection( NetConnection *pConnection ) { return mNetState.isConnection( pConnection ); };
    inline void             addConnection( NetConnection *pConnection ) { mNetState.addConnection( pConnection );      };
    inline void             clearConnection( NetConnection *pConnection ) { mNetState.clearConnection( pConnection );  };

    // Enum Methods.

    static eOrientationType    getOrientationTypeEnum( const char *pLabel );
    static StringTableEntry    getOrientationTypeLabel( const eOrientationType &pType );
};

//-----------------------------------------------------------------------------

// Define Types.
typedef VPathNode::eOrientationType VPathNodeOrientationType;

// Declare Enum Types.
DefineEnumType( VPathNodeOrientationType );

//-----------------------------------------------------------------------------

#endif // _VT_VPATHNODE_H_