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
#include "VPathObject.h"
#include "VPath.h"

#include "core/stream/bitStream.h"
#include "sim/netConnection.h"

//-----------------------------------------------------------------------------

static U32 gOrientationTypeBits = getBinLog2( getNextPow2( VPathObject::k_OrientationTypeSize ) );

//-----------------------------------------------------------------------------

VPathObject::VPathObject( void ) :
        mActive( false ),
        mLastTime( 0 ),
        mLastDelta( 0.f ),
        mObject( NULL ),
        mTimeInterp( 0.f ),
        mPathInterp( 0.f ),
        mPosition( 0.f, 0.f, 0.f ),
        mOffset( 0.f, 0.f, 0.f ),
        mOrientation( 0.f, 1.f, 0.f ),
        mForward( true ),
        mSpeed( 10.f ),
        mSourceNode( 0 ),
        mDestinationNode( 0 ),
        mStartNode( 0 ),
        mEndNode( 0 )
{
    // Init.
    mOrientationMode.Type   = k_OrientationToPath;
    mOrientationMode.Object = NULL;
    mOrientationMode.Point  = Point3F::Zero;

    // Set the initial mask.
    mNetState.setMaskBits( k_StateInit );

    // Reset Time.
    resetTime();

    // Reset Delta.
    resetDelta();

    VECTOR_SET_ASSOCIATION( mNetState );
}

VPathObject::~VPathObject( void )
{
    // Void.
}

//-----------------------------------------------------------------------------
//
// Network Methods.
//
//-----------------------------------------------------------------------------

U32 VPathObject::packUpdate( NetConnection *pConnection, BitStream *pStream )
{
    // Init Return Mask.
    U32 retMask = 0;

    // Fetch State.
    VNetStateInfo *state = getState( pConnection );

    // Write Active.
    pStream->writeFlag( mActive );

    // Send Object Update?
    if ( pStream->writeFlag( state->Mask & k_StateUpdateObject ) )
    {
        // Successful Send?
        bool success = false;

        // Valid Object?
        if ( !mObject )
        {
            // No Object.
            pStream->writeFlag( false );
        }
        else
        {
            // Write Ghost Index.
            const S32 ghostIndex = pConnection->getGhostIndex( mObject );
            if ( pStream->writeFlag( ghostIndex != -1 ) )
            {
                // Write Ghost Id.
                pStream->writeInt( ghostIndex, NetConnection::GhostIdBitSize );

                // Success!
                success = true;
                // Clear Update.
                state->Mask &= ~k_StateUpdateObject;
            }
        }

        if ( !success )
        {
            // Try Again Later.
            retMask |= VPath::ObjectUpdateMask;
        }
    }

    // Send Mount Update?
    if ( pStream->writeFlag( state->Mask & k_StateUpdateMount ) )
    {
        // Successful Send?
        bool success = false;

        // Valid Objects?
        if ( !mObject || !mObject->getObjectMount() || ( state->Mask & k_StateUpdateObject ) )
        {
            // No Object.
            pStream->writeFlag( false );
        }
        else
        {
            // Write Ghost Index.
            const S32 ghostIndex = pConnection->getGhostIndex( mObject->getObjectMount() );
            if ( pStream->writeFlag( ghostIndex != -1 ) )
            {
                // Write Ghost Id.
                pStream->writeInt( ghostIndex, NetConnection::GhostIdBitSize );
                // Write Mount Node.
                pStream->writeInt( mObject->getMountNode(), SceneObject::NumMountPointBits );

                // Success!
                success = true;
                // Clear Update.
                state->Mask &= ~k_StateUpdateMount;
            }
        }

        if ( !success )
        {
            // Try Again Later.
            retMask |= VPath::ObjectUpdateMask;
        }
    }

    // Send Position Update?
    if ( pStream->writeFlag( state->Mask & k_StateUpdatePosition ) )
    {
        // Write Position.
        pStream->write( mTimeInterp );
        pStream->write( mPathInterp );

        pStream->write( mPosition.x );
        pStream->write( mPosition.y );
        pStream->write( mPosition.z );

        pStream->write( mOrientation.x );
        pStream->write( mOrientation.y );
        pStream->write( mOrientation.z );

        pStream->writeInt( mSourceNode,      VPath::gMaxNodeBits );
        pStream->writeInt( mDestinationNode, VPath::gMaxNodeBits );

        // Clear Update.
        state->Mask &= ~k_StateUpdatePosition;
    }

    // Send State Update?
    if ( pStream->writeFlag( state->Mask & k_StateUpdateState ) )
    {
        // Successful Send?
        bool success = true;

        // Write State.
        pStream->writeInt( mOrientationMode.Type, gOrientationTypeBits );

        switch ( mOrientationMode.Type )
        {
            case k_OrientationToObject :
                {
                    // Write Ghost Index.
                    const S32 ghostIndex = pConnection->getGhostIndex( mOrientationMode.Object );
                    if ( pStream->writeFlag( ghostIndex != -1 ) )
                    {
                        pStream->writeInt( ghostIndex, NetConnection::GhostIdBitSize );
                    }
                    else
                    {
                        // Failed.
                        success = false;
                    }

                } break;

            case k_OrientationToPoint :
                {
                    // Write Point.
                    pStream->write( mOrientationMode.Point.x );
                    pStream->write( mOrientationMode.Point.y );
                    pStream->write( mOrientationMode.Point.z );

                } break;
        }

        pStream->writeFlag( mForward );
        pStream->write( mSpeed );

        // Write Offset.
        pStream->write( mOffset.x );
        pStream->write( mOffset.y );
        pStream->write( mOffset.z );

        pStream->writeInt( mStartNode, VPath::gMaxNodeBits );
        pStream->writeInt( mEndNode,   VPath::gMaxNodeBits );

        if ( success )
        {
            // Clear Update.
            state->Mask &= ~k_StateUpdateState;
        }
        else
        {
            // Try Again Later.
            retMask |= VPath::ObjectUpdateMask;
        }
    }

    // Return Mask.
    return retMask;
}

void VPathObject::unpackUpdate( NetConnection *pConnection, BitStream *pStream )
{
    // Read Active.
    setActive( pStream->readFlag() );

    // Update Object?
    if ( pStream->readFlag() )
    {
        if ( pStream->readFlag() )
        {
            // Read Ghost Index.
            const S32 ghostIndex = pStream->readInt( NetConnection::GhostIdBitSize );

            // Resolve Object.
            setObject( static_cast<SceneObject*>( pConnection->resolveGhost( ghostIndex ) ) );

            // Reset Delta.
            resetDelta();
        }
        else
        {
            // Clear Object.
            mObject = NULL;
        }
    }

    // Update Mount?
    if ( pStream->readFlag() )
    {
        if ( pStream->readFlag() )
        {
            // Read Ghost Index.
            const S32 ghostIndex = pStream->readInt( NetConnection::GhostIdBitSize );
            // Read Mount Node.
            const S32 nodeIndex = pStream->readInt( SceneObject::NumMountPointBits );

            // Resolve Object.
            SceneObject *mountObject = static_cast<SceneObject*>( pConnection->resolveGhost( ghostIndex ) );
            // Mount Object.
            mountObject->mountObject( mObject, nodeIndex );
        }
        else
        {
            // ... unmount?
        }
    }

    // Update Position?
    if ( pStream->readFlag() )
    {
        // Read Updates.
        pStream->read( &mTimeInterp );
        pStream->read( &mPathInterp );

        pStream->read( &mPosition.x );
        pStream->read( &mPosition.y );
        pStream->read( &mPosition.z );

        pStream->read( &mOrientation.x );
        pStream->read( &mOrientation.y );
        pStream->read( &mOrientation.z );

        mSourceNode      = pStream->readInt( VPath::gMaxNodeBits );
        mDestinationNode = pStream->readInt( VPath::gMaxNodeBits );
    }

    // Update Heading?
    if ( pStream->readFlag() )
    {
        // Read Orientation Mode.
        mOrientationMode.Type = ( eOrientationType )pStream->readInt( gOrientationTypeBits );

        switch ( mOrientationMode.Type )
        {
            case VPathObject::k_OrientationToObject :
                {
                    if ( pStream->readFlag() )
                    {
                        // Read Ghost Index.
                        const S32 ghostIndex = pStream->readInt( NetConnection::GhostIdBitSize );
                        // Resolve Object.
                        mOrientationMode.Object = static_cast<SceneObject*>( pConnection->resolveGhost( ghostIndex ) );
                    }

                } break;

            case VPathObject::k_OrientationToPoint :
                {
                    // Read Point.
                    pStream->read( &mOrientationMode.Point.x );
                    pStream->read( &mOrientationMode.Point.y );
                    pStream->read( &mOrientationMode.Point.z );

                } break;
        }

        // Read Updates.
        mForward = pStream->readFlag();

        pStream->read( &mSpeed );

        pStream->read( &mOffset.x );
        pStream->read( &mOffset.y );
        pStream->read( &mOffset.z );

        mStartNode = pStream->readInt( VPath::gMaxNodeBits );
        mEndNode   = pStream->readInt( VPath::gMaxNodeBits );
    }
}

//-----------------------------------------------------------------------------
//
// Property Methods.
//
//-----------------------------------------------------------------------------

Point3F VPathObject::getWorldPosition( void )
{
    return ( mPosition + mOffset );
}

Point3F VPathObject::getRenderWorldPosition( const F32 &pDelta )
{
    return ( getPositionDelta( pDelta ) + mOffset );
}

MatrixF VPathObject::getTransform( void )
{
    MatrixF mat( true );
    switch ( mOrientationMode.Type )
    {
        case k_OrientationInterpolate :
        case k_OrientationToObject :
        case k_OrientationToPoint :
        case k_OrientationToPath :
            {
                // Y-Axis.
                VectorF yVec = mOrientation;
                yVec.normalize();

                // X-Axis.
                VectorF xVec = mCross( yVec, VPath::gBezierUp );
                xVec.normalize();

                // Z-Axis.
                VectorF zVec = mCross( xVec, yVec );
                zVec.normalize();

                // Setup Object Transform.
                mat.setColumn( 0, xVec );
                mat.setColumn( 1, yVec );
                mat.setColumn( 2, zVec );
                mat.setColumn( 3, getWorldPosition() );

            } break;

        case k_OrientationFree :
            {
                // Fetch Current Transform.
                mat = mObject->getTransform();
                mat.setPosition( getWorldPosition() );

            } break;
    }

    // Return.
    return mat;
}

MatrixF VPathObject::getRenderTransform( const F32 &pDelta )
{
    MatrixF mat( true );
    switch ( mOrientationMode.Type )
    {
        case k_OrientationInterpolate :
        case k_OrientationToObject :
        case k_OrientationToPoint :
        case k_OrientationToPath :
            {
                // Y-Axis.
                VectorF yVec = getOrientationDelta( pDelta );
                yVec.normalize();

                // X-Axis.
                VectorF xVec = mCross( yVec, VPath::gBezierUp );
                xVec.normalize();

                // Z-Axis.
                VectorF zVec = mCross( xVec, yVec );
                zVec.normalize();

                // Setup Object Transform.
                mat.setColumn( 0, xVec );
                mat.setColumn( 1, yVec );
                mat.setColumn( 2, zVec );
                mat.setColumn( 3, getRenderWorldPosition( pDelta ) );

            } break;

        case k_OrientationFree :
            {
                // Fetch Current Transform.
                mat = mObject->getRenderTransform();
                mat.setPosition( getRenderWorldPosition( pDelta ) );

            } break;
    }

    // Return.
    return mat;
}

void VPathObject::setActive( const bool &pActive )
{
    // Update?
    if ( pActive != mActive )
    {
        // Apply.
        mActive = pActive;
        // Flag Update.
        setMaskBits( k_StateUpdatePosition );
    }
}

void VPathObject::setObject( SceneObject *pObject )
{
    // Update?
    if ( pObject != mObject )
    {
        // Apply.
        mObject = pObject;
        // Flag Update.
        setMaskBits( k_StateUpdateObject );
    }
}

void VPathObject::setTimeInterp( const F32 &pInterp )
{
    // Update?
    if ( mTimeInterp != pInterp )
    {
        // Apply.
        mTimeInterp = pInterp;
        // Flag Update.
        setMaskBits( k_StateUpdatePosition );
    }
}

void VPathObject::setPathInterp( const F32 &pInterp )
{
    // Update?
    if ( mPathInterp != pInterp )
    {
        // Apply.
        mPathInterp = pInterp;
        // Flag Update.
        setMaskBits( k_StateUpdatePosition );
    }
}

void VPathObject::setPosition( const Point3F &pPosition )
{
    // Update?
    if ( mPosition != pPosition )
    {
        // Update.
        mPosition = pPosition;
        // Flag Update.
        setMaskBits( k_StateUpdatePosition );
    }
}

void VPathObject::setOffset( const Point3F &pOffset )
{
    // Update?
    if ( mOffset != pOffset )
    {
        // Update.
        mOffset = pOffset;
        // Flag Update.
        setMaskBits( k_StateUpdateState );
    }
}

void VPathObject::setOrientation( const VectorF &pOrientation )
{
    // Update?
    if ( mOrientation != pOrientation )
    {
        // Update.
        mOrientation = pOrientation;
        // Flag Update.
        setMaskBits( k_StateUpdatePosition );
    }
}

void VPathObject::setOrientationMode( const eOrientationType &pType )
{
    // Update?
    if ( mOrientationMode.Type != pType )
    {
        // Update.
        mOrientationMode.Type = pType;
        // Flag Update.
        setMaskBits( k_StateUpdateState );
    }
}

void VPathObject::setOrientationMode( const eOrientationType &pType, SceneObject *pObject )
{
    AssertFatal( ( pType == k_OrientationToObject ) && ( pObject != NULL ), "VPathObject::setOrientationMode() - Invalid mOrientation Type." );

    // Update?
    if ( ( mOrientationMode.Type != pType ) || ( mOrientationMode.Object != pObject ) )
    {
        // Update.
        mOrientationMode.Type   = pType;
        mOrientationMode.Object = pObject;
        // Flag Update.
        setMaskBits( k_StateUpdateState );
    }
}

void VPathObject::setOrientationMode( const eOrientationType &pType, const Point3F &pPoint )
{
    AssertFatal( pType == k_OrientationToPoint, "VPathObject::setOrientationMode() - Invalid mOrientation Type." );

    // Update?
    if ( ( mOrientationMode.Type != pType ) || ( mOrientationMode.Point != pPoint ) )
    {
        // Update.
        mOrientationMode.Type  = pType;
        mOrientationMode.Point = pPoint;
        // Flag Update.
        setMaskBits( k_StateUpdateState );
    }
}

void VPathObject::setForward( const bool &pForward )
{
    // Update?
    if ( mForward != pForward )
    {
        // Update.
        mForward = pForward;
        // Flag Update.
        setMaskBits( k_StateUpdateState );
    }
}

void VPathObject::setSpeed( const F32 &pSpeed )
{
    // Update?
    if ( mSpeed != pSpeed )
    {
        // Update.
        mSpeed = pSpeed;
        // Flag Update.
        setMaskBits( k_StateUpdateState );
    }
}

void VPathObject::setNode( const S32 &pSourceNodeIndex, const S32 &pDestinationNodeIndex )
{
    // Update?
    if ( ( mSourceNode != pSourceNodeIndex ) || ( mDestinationNode != pDestinationNodeIndex ) )
    {
        // Update.
        mSourceNode      = pSourceNodeIndex;
        mDestinationNode = pDestinationNodeIndex;
        // Flag Update.
        setMaskBits( k_StateUpdatePosition );
    }
}

void VPathObject::setStartNode( const S32 &pNodeIndex )
{
    // Update?
    if ( mStartNode != pNodeIndex )
    {
        // Update.
        mStartNode = pNodeIndex;
        // Flag Update.
        setMaskBits( k_StateUpdateState );
    }
}

void VPathObject::setEndNode( const S32 &pNodeIndex )
{
    // Update?
    if ( mEndNode != pNodeIndex )
    {
        // Update.
        mEndNode = pNodeIndex;
        // Flag Update.
        setMaskBits( k_StateUpdateState );
    }
}

//-----------------------------------------------------------------------------
//
// Delta Methods.
//
//-----------------------------------------------------------------------------

void VPathObject::resetDelta( void )
{
    mDelta.Position[0]    = mPosition;
    mDelta.Position[1]    = mPosition;
    mDelta.Orientation[0] = mOrientation;
    mDelta.Orientation[1] = mOrientation;
}

void VPathObject::resetDelta( const Point3F &pPosition, const VectorF &pOrientation )
{
    mDelta.Position[0]    = pPosition;
    mDelta.Position[1]    = pPosition;
    mDelta.Orientation[0] = pOrientation;
    mDelta.Orientation[1] = pOrientation;
}

void VPathObject::popDelta( void )
{
    mDelta.Position[0]    = mDelta.Position[1];
    mDelta.Orientation[0] = mDelta.Orientation[1];
}

void VPathObject::pushDelta( const Point3F &pPosition, const VectorF &pOrientation )
{
    mDelta.Position[1]    = pPosition;
    mDelta.Orientation[1] = pOrientation;
}

Point3F VPathObject::getPositionDelta( const F32 &pInterp )
{
    Point3F interpPosition;
    interpPosition.interpolate( mDelta.Position[1], mDelta.Position[0], pInterp );

    return interpPosition;
}

VectorF VPathObject::getOrientationDelta( const F32 &pInterp )
{
    VectorF interpOrientation;
    interpOrientation.interpolate( mDelta.Orientation[1], mDelta.Orientation[0], pInterp );
    interpOrientation.normalize();

    return interpOrientation;
}

//-----------------------------------------------------------------------------
//
// Enumeration Methods.
//
//-----------------------------------------------------------------------------

// Implement the Orientation Type enum list.
ImplementEnumType( VPathObjectOrientationType, "" )
    { VPathObject::k_OrientationFree,        "FREE"        },
    { VPathObject::k_OrientationInterpolate, "INTERPOLATE" },
    { VPathObject::k_OrientationToPath,      "TOPATH"      },
    { VPathObject::k_OrientationToObject,    "TOOBJECT"    },
    { VPathObject::k_OrientationToPoint,     "TOPOINT"     },
EndImplementEnumType;

VPathObject::eOrientationType VPathObject::getOrientationTypeEnum( const char *pLabel )
{
    VPathObject::eOrientationType out;
    if ( !castConsoleTypeFromString( out, pLabel ) )
    {
        // Bah!
        return VPathObject::k_OrientationFree;
    }

    // Return.
    return out;
}

StringTableEntry VPathObject::getOrientationTypeLabel( const eOrientationType &pType )
{
    // Return.
    return castConsoleTypeToString( pType );
}