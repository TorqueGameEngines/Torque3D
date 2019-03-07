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
#ifndef _VT_VACTORSTATETABLE_H_
#define _VT_VACTORSTATETABLE_H_

#ifndef _TVECTOR_H
#include "core/util/tVector.h"
#endif

//-----------------------------------------------------------------------------
class VActor;
class VActorStateTable;
//-----------------------------------------------------------------------------

class VActorState
{
public:

    VActorState( void ) { };
    virtual ~VActorState( void ) { };

    virtual void         enter( VActor *pObject )   = 0;
    virtual bool         execute( VActor *pObject ) = 0;
    virtual void         exit( VActor *pObject )    = 0;
};

//-----------------------------------------------------------------------------

class VActorStateTable
{
public:

    struct sStateRef
    {
        VActorState   *State;
        F32            Priority;
    };

    typedef Vector<sStateRef>            tStateVector;
    typedef tStateVector::iterator       tStateIterator;
    typedef tStateVector::const_iterator tStateConstIterator;

protected:

    tStateVector          mStateVector;

    VActor               *mObject;

    VActorState          *mLastState;
    VActorState          *mCurrentState;

public:

    VActorStateTable( void ) :
        mObject( NULL ),
        mLastState( NULL ),
        mCurrentState( NULL )
    {
        VECTOR_SET_ASSOCIATION( mStateVector );
    };

    virtual ~VActorStateTable( void )
    {
        // Clear Table.
        clear();
    };

    void                   registerState( VActorState *pState, const F32 &pPriority = 0.5f );

    virtual void           enter( void ) { };
    virtual VActorState   *execute( void );
    virtual void           exit( void )  { };

    //-------------------------------------------------------------------------
    //
    // Gets
    //
    //-------------------------------------------------------------------------

    inline VActor         *getObject( void )       { return mObject; };

    bool                   isRegisteredState( VActorState *pState );

    inline VActorState    *getCurrentState( void ) { return mCurrentState; };
    inline VActorState    *getLastState( void )    { return mLastState; };

    //-------------------------------------------------------------------------
    //
    // Sets
    //
    //-------------------------------------------------------------------------

    void                   clear( void );
    void                   sort( void );

    inline void            setObject( VActor *pObject ) { mObject = pObject; };
    void                   setState( VActorState *pState );

    //-------------------------------------------------------------------------
    //
    // Accessors
    //
    //-------------------------------------------------------------------------

    tStateConstIterator    begin( void ) const { return mStateVector.begin(); };
    tStateConstIterator    end( void )   const { return mStateVector.end(); };
    S32                    size( void )  const { return mStateVector.size(); };

protected:

    static S32 QSORT_CALLBACK _onSortCallback( const VActorStateTable::sStateRef *pA, const VActorStateTable::sStateRef *pB );
};

#endif // _VT_VACTORSTATETABLE_H_