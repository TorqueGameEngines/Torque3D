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
#include "VPathNode.h"
#include "VPath.h"

#include "core/stream/bitStream.h"
#include "core/strings/stringUnit.h"
#include "sim/netConnection.h"

//-----------------------------------------------------------------------------

static U32 gOrientationTypeBits = getBinLog2( getNextPow2( VPathNode::k_OrientationTypeSize ) );

//-----------------------------------------------------------------------------

VPathNode::VPathNode( void ) :
        mPath( NULL ),
        mLocalPosition( Point3F( 0.f, 0.f, 0.f ) ),
        mLocalRotation( QuatF( 0.f, 0.f, 0.f, 1.f ) ),
        mWorldPosition( Point3F( 0.f, 0.f, 0.f ) ),
        mWorldRotation( QuatF( 0.f, 0.f, 0.f, 1.f ) ),
        mWeight( 10.f ),
        mLength( 0.f )
{
    // Init.
    mOrientationMode.Type   = k_OrientationFree;
    mOrientationMode.Point  = Point3F::Zero;

    // Set the initial mask.
    mNetState.setMaskBits( k_StateInit );

    VECTOR_SET_ASSOCIATION( mNetState );
}

VPathNode::~VPathNode( void )
{
    mNetState.clear();
}

//-----------------------------------------------------------------------------
//
// Network Methods.
//
//-----------------------------------------------------------------------------

U32 VPathNode::packNode( NetConnection *pConnection, BitStream *pStream )
{
    // Init Return Mask.
    U32 retMask = 0;

    // Fetch State.
    VNetStateInfo *state = getState( pConnection );

    // Note: This is out of sync with VPathNode::unpackUpdate().
    //       If you're ever going to use these methods outside of VPath, you
    //       will need to read a flag *before* calling unpack!

    // Was the Node Created?
    if ( pStream->writeFlag( state->Mask & k_StateCreate ) )
    {
        // Clear Update.
        state->Mask &= ~k_StateCreate;
    }

    // Send mLocalPosition?
    if ( pStream->writeFlag( state->Mask & k_StateUpdatePosition ) )
    {
        // Write mLocalPosition.
        pStream->write( mLocalPosition.x );
        pStream->write( mLocalPosition.y );
        pStream->write( mLocalPosition.z );

        // Clear Update.
        state->Mask &= ~k_StateUpdatePosition;
    }

    // Send mLocalRotation?
    if ( pStream->writeFlag( state->Mask & k_StateUpdateRotation ) )
    {
        // Write mLocalRotation.
        pStream->write( mLocalRotation.x );
        pStream->write( mLocalRotation.y );
        pStream->write( mLocalRotation.z );
        pStream->write( mLocalRotation.w );

        // Clear Update.
        state->Mask &= ~k_StateUpdateRotation;
    }

    // Send mWeight?
    if ( pStream->writeFlag( state->Mask & k_StateUpdateWeight ) )
    {
        // Write mWeight.
        pStream->write( mWeight );

        // Clear Update.
        state->Mask &= ~k_StateUpdateWeight;
    }

    // Send Orientation Update?
    if ( pStream->writeFlag( state->Mask & k_StateUpdateOrientation ) )
    {
        // Clear Update?
        bool clearUpdate = true;

        // Write State.
        pStream->writeInt( mOrientationMode.Type, gOrientationTypeBits );

        switch ( mOrientationMode.Type )
        {
            case k_OrientationToPoint :
                {
                    // Write Point.
                    pStream->write( mOrientationMode.Point.x );
                    pStream->write( mOrientationMode.Point.y );
                    pStream->write( mOrientationMode.Point.z );

                } break;
        }

        if ( clearUpdate )
        {
            // Clear Update.
            state->Mask &= ~k_StateUpdateOrientation;
        }
    }

    // Return Mask.
    return retMask;
}

void VPathNode::unpackNode( NetConnection *pConnection, BitStream *pStream )
{
    // Note: This is out of sync with VPathNode::packUpdate().
    //       If you're ever going to use these methods outside of VPath, you
    //       will need to read a flag *before* calling unpack!

    // Update World Data.
    bool updateWorld = false;

    // Update Local Position?
    if ( pStream->readFlag() )
    {
        // Read Local Position.
        pStream->read( &mLocalPosition.x );
        pStream->read( &mLocalPosition.y );
        pStream->read( &mLocalPosition.z );

        updateWorld = true;
    }
    
    // Update Local Rotation?
    if ( pStream->readFlag() )
    {
        // Read Local Rotation.
        pStream->read( &mLocalRotation.x );
        pStream->read( &mLocalRotation.y );
        pStream->read( &mLocalRotation.z );
        pStream->read( &mLocalRotation.w );

        updateWorld = true;
    }
    
    // Update Weight?
    if ( pStream->readFlag() )
    {
        // Read Weight.
        pStream->read( &mWeight );
    }
    
    // Update Orientation?
    if ( pStream->readFlag() )
    {
        // Read Orientation Mode.
        mOrientationMode.Type = ( eOrientationType )pStream->readInt( gOrientationTypeBits );

        switch ( mOrientationMode.Type )
        {
            case k_OrientationToPoint :
                {
                    // Read Point.
                    pStream->read( &mOrientationMode.Point.x );
                    pStream->read( &mOrientationMode.Point.y );
                    pStream->read( &mOrientationMode.Point.z );

                } break;
        }
    }

    if ( updateWorld )
    {
        // Update World Position.
        updateWorldData();
    }
}

String VPathNode::toString( void )
{
    String retBuffer;

    // Buffer Node Properties.
    // {Position} {Rotation} {Weight}
    const AngAxisF aa( mLocalRotation );
    retBuffer = String::ToString( "%f %f %f %f %f %f %f %f", mLocalPosition.x, mLocalPosition.y, mLocalPosition.z,
                                                             aa.axis.x, aa.axis.y, aa.axis.z, aa.angle,
                                                             mWeight );

    // Add Tab.
    retBuffer += "\t";

    // Determine the Type.
    StringTableEntry typeString = getOrientationTypeLabel( mOrientationMode.Type );
    switch( mOrientationMode.Type )
    {
        case k_OrientationFree :
            {
                // Buffer String.
                retBuffer += typeString;

            } break;

        case k_OrientationToPoint:
            {
                // Fetch Point.
                const Point3F &lookAtPoint = mOrientationMode.Point;

                // Buffer String.
                retBuffer += String::ToString( "%s %f %f %f", typeString, lookAtPoint.x, lookAtPoint.y, lookAtPoint.z );

            } break;
    }

    // Return String.
    return retBuffer;
}

bool VPathNode::fromString( const String &pString )
{
    // Split Data.
    // {Position} {Rotation} {Weight}
    const char *baseData = StringUnit::getUnit( pString.c_str(), 0, "\t" );

    Point3F  pos;
    AngAxisF aa;
    F32      weight;

    // Scan Base.
    dSscanf( baseData, "%g %g %g %g %g %g %g %g", &pos.x, &pos.y, &pos.z,
                                                  &aa.axis.x, &aa.axis.y, &aa.axis.z, &aa.angle,
                                                  &weight );

    // Apply Changes.
    setLocalPosition( pos );
    setLocalRotation( QuatF( aa ) );
    setWeight( weight );

    // Fetch Orientation Data.
    String orientationData = StringUnit::getUnit( pString.c_str(), 1, "\t" );

    // Fetch Orientation Type.
    String orientationTypeString = orientationData;
    if ( orientationData.find( " " ) )
    {
        // Use First Word.
        orientationTypeString = orientationData.substr( 0, orientationData.find( " " ) );
    }

    // Set Orientation Type.
    const eOrientationType &orientationType = getOrientationTypeEnum( orientationTypeString.c_str() );
    switch( orientationType )
    {
        case k_OrientationFree : 
            {
                // Apply Mode.
                setOrientationMode( orientationType );

            } break;

        case k_OrientationToPoint:
            {
                // Fetch Point.
                Point3F lookAtPoint;
                // Buffer String.
                dSscanf( orientationData.c_str(), "%*s %f %f %f", &lookAtPoint.x, &lookAtPoint.y, &lookAtPoint.z );

                // Apply Mode.
                setOrientationMode( orientationType, lookAtPoint );

            } break;
    }

    return true;
}

//-----------------------------------------------------------------------------
//
// Property Methods.
//
//-----------------------------------------------------------------------------

Point3F VPathNode::getWorldPosition( void ) const
{
    return mWorldPosition;
}

QuatF VPathNode::getWorldRotation( void ) const
{
    return mWorldRotation;
}

MatrixF VPathNode::getWorldTransform( void ) const
{
    MatrixF mat;
    getWorldRotation().setMatrix( &mat );
    mat.setPosition( getWorldPosition() );

    return mat;
}

void VPathNode::setLocalPosition( const Point3F &pPosition )
{
    // Update?
    if ( mLocalPosition != pPosition )
    {
        // Apply.
        mLocalPosition = pPosition;

        // Update World Position.
        updateWorldData();

        // Flag Update.
        setMaskBits( k_StateUpdatePosition );
    }
}

void VPathNode::setLocalRotation( const QuatF &pRotation )
{
    // Update?
    if ( mLocalRotation != pRotation )
    {
        // Apply.
        mLocalRotation = pRotation;

        // Update World Rotation.
        updateWorldData();

        // Flag Update.
        setMaskBits( k_StateUpdateRotation );
    }
}

void VPathNode::setWeight( const F32 &pWeight )
{
    // Update?
    if ( mWeight != pWeight )
    {
        // Apply.
        mWeight = pWeight;

        // Flag Update.
        setMaskBits( k_StateUpdateWeight );
    }
}

void VPathNode::setOrientationMode( const eOrientationType &pType )
{
    // Update?
    if ( mOrientationMode.Type != pType )
    {
        // Update.
        mOrientationMode.Type = pType;

        // Flag Update.
        setMaskBits( k_StateUpdateOrientation );
    }
}

void VPathNode::setOrientationMode( const eOrientationType &pType, const Point3F &pPoint )
{
    AssertFatal( pType == k_OrientationToPoint, "VPathNode::setOrientationMode() - Invalid mOrientation Type." );

    // Update?
    if ( ( mOrientationMode.Type != pType ) || ( mOrientationMode.Point != pPoint ) )
    {
        // Update.
        mOrientationMode.Type  = pType;
        mOrientationMode.Point = pPoint;

        // Flag Update.
        setMaskBits( k_StateUpdateOrientation );
    }
}

void VPathNode::updateWorldData( void )
{
    if ( !mPath )
    {
        setWorldPosition( getLocalPosition() );
        setWorldRotation( getLocalRotation() );
        return;
    }

    // Fetch Path Details.
    const MatrixF &pathTransform = mPath->getTransform();
    const QuatF   &pathRotation( pathTransform );

    // Calculate the World Position.
    Point3F newPosition = getLocalPosition();
    newPosition.convolve( mPath->getScale() );
    pathTransform.mulP( newPosition );

    // Calculate the new Rotation.
    QuatF newRotation;
    newRotation.mul( getLocalRotation(), pathRotation );

    // Apply.
    setWorldPosition( newPosition );
    setWorldRotation( newRotation );
}

//-----------------------------------------------------------------------------
//
// Enumeration Methods.
//
//-----------------------------------------------------------------------------

// Implement the Orientation Type enum list.
ImplementEnumType( VPathNodeOrientationType,"" )
    { VPathNode::k_OrientationFree,    "FREE"    },
    { VPathNode::k_OrientationToPoint, "TOPOINT" },
EndImplementEnumType;

VPathNode::eOrientationType VPathNode::getOrientationTypeEnum( const char *pLabel )
{
    VPathNode::eOrientationType out;
    if ( !castConsoleTypeFromString( out, pLabel ) )
    {
        // Bah!
        return VPathNode::k_OrientationFree;
    }

    // Return.
    return out;
}

StringTableEntry VPathNode::getOrientationTypeLabel( const eOrientationType &pType )
{
    // Return.
    return castConsoleTypeToString( pType );
}