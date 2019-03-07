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
#ifndef _VT_VTREENODE_H_
#define _VT_VTREENODE_H_

#ifndef _VT_ITREENODE_H_
#include "Verve/Core/ITreeNode.h"
#endif

//-----------------------------------------------------------------------------

class VTreeNode : public ITreeNode
{
    typedef ITreeNode Parent;

public:

    VTreeNode( void );
    ~VTreeNode( void );

    // Reference Methods.

    virtual void               clear( void );

    // ITreeNode Methods.

    virtual ITreeNode         *getRoot( void );
    virtual ITreeNode         *getParent( void );
    virtual ITreeNode         *getChild( void );
    virtual ITreeNode         *getLastChild( void );

    virtual ITreeNode         *getPrevSibling( void );
    virtual ITreeNode         *getNextSibling( void );

    virtual ITreeNode         *at( const int pIndex );
    virtual int                size( void );

    virtual int                getIndex( void );

    virtual void               addTo( ITreeNode *pNode );
    virtual void               addToFront( ITreeNode *pNode );
    virtual void               remove( void );
    virtual void               moveTo( ITreeNode *pNode );

    virtual void               onAttach( void );
    virtual void               onDetach( void );

    virtual bool               inTree( void );
};

//-----------------------------------------------------------------------------

#endif // _VT_VTREENODE_H_