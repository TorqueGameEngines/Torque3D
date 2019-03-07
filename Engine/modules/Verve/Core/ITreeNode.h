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
#ifndef _VT_ITREENODE_H_
#define _VT_ITREENODE_H_

//-----------------------------------------------------------------------------

class ITreeNode
{
public:

    ITreeNode   *mParentNode;
    ITreeNode   *mChildNode;

    ITreeNode   *mSiblingPrevNode;
    ITreeNode   *mSiblingNextNode;

public:

    ITreeNode( void ) :
            mParentNode( 0 ),
            mChildNode( 0 ),
            mSiblingPrevNode( 0 ),
            mSiblingNextNode( 0 )
    {
        // Void.
    };

    virtual ~ITreeNode( void )
    {
        // Void.
    };

    virtual void               clear( void ) = 0;                              // Clear the Node.

    virtual ITreeNode         *getRoot( void ) = 0;                            // Get Root Node.
    virtual ITreeNode         *getParent( void ) = 0;                          // Get Parent Node.
    virtual ITreeNode         *getChild( void ) = 0;                           // Get Child Node.
    virtual ITreeNode         *getLastChild( void ) = 0;                       // Get Last Child Node.

    virtual ITreeNode         *getPrevSibling( void ) = 0;                     // Get Previous Sibling Node.
    virtual ITreeNode         *getNextSibling( void ) = 0;                     // Get Next Sibling Node.

    virtual void               addTo( ITreeNode *pNode ) = 0;                  // Add Node to target node.
    virtual void               remove( void ) = 0;                             // Remove this Node from the tree.
    virtual void               moveTo( ITreeNode* node ) = 0;                  // Move to specified Node.

    virtual void               onAttach( void ) = 0;                           // Attach Callback.
    virtual void               onDetach( void ) = 0;                           // Detach Callback.

    virtual bool               inTree( void ) = 0;                             // Is Node in a tree?
};

//-----------------------------------------------------------------------------

#endif // _VT_ITREENODE_H_