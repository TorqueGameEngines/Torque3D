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
#include "Verve/Core/VTreeNode.h"
#include "console/simObject.h"
#include "platform/platform.h"

//-----------------------------------------------------------------------------

VTreeNode::VTreeNode( void )
{
    mParentNode      = NULL;
    mChildNode       = NULL;
    mSiblingPrevNode = NULL;
    mSiblingNextNode = NULL;
}

VTreeNode::~VTreeNode( void )
{
    // Delete Children.
    clear();

    // Detach.
    remove();
}

//-----------------------------------------------------------------------------
//
// Reference Methods.
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// 
// VTreeNode::clear();
// 
// Delete all child nodes.
// 
//-----------------------------------------------------------------------------
void VTreeNode::clear( void )
{
    if ( !mChildNode )
    {
        return;
    }

    while ( mChildNode )
    {
        // Fetch Child Node.
        ITreeNode *node = mChildNode;

        // Clear It.
        node->clear();

        // Detach It.
        node->remove();

        // Delete It.
        SimObject *object = dynamic_cast<SimObject*>( node );
        if ( object )
        {
            object->deleteObject();
        }
        else
        {
            delete node;
        }
    }
}

//-----------------------------------------------------------------------------
//
// ITreeNode Methods.
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// 
// VTreeNode::getRoot();
// 
// Returns the root object.
// 
//-----------------------------------------------------------------------------
ITreeNode *VTreeNode::getRoot( void )
{
    ITreeNode *parent = this;
    while ( parent->mParentNode )
    {
        parent = parent->mParentNode;
    }

    return parent;
}

//-----------------------------------------------------------------------------
// 
// VTreeNode::getParent();
// 
// Returns the parent object.
// 
//-----------------------------------------------------------------------------
ITreeNode *VTreeNode::getParent( void )
{
    return mParentNode;
}

//-----------------------------------------------------------------------------
// 
// VTreeNode::getChild();
// 
// Returns the first child object.
// 
//-----------------------------------------------------------------------------
ITreeNode *VTreeNode::getChild( void )
{
    return mChildNode;
}

//-----------------------------------------------------------------------------
// 
// VTreeNode::getChild();
// 
// Returns the first child object.
// 
//-----------------------------------------------------------------------------
ITreeNode *VTreeNode::getLastChild( void )
{
    // Any Nodes?
    if ( !mChildNode )
    {
        // Null.
        return NULL;
    }

    // Front Node.
    ITreeNode *lastNode = mChildNode;

    // Fetch Last Node.
    while ( lastNode->mSiblingNextNode )
    {
        lastNode = lastNode->mSiblingNextNode;
    }

    // Return.
    return lastNode;
}

//-----------------------------------------------------------------------------
// 
// VTreeNode::getPrevSibling();
// 
// Returns the previous object in the linked list.
// 
//-----------------------------------------------------------------------------
ITreeNode *VTreeNode::getPrevSibling( void )
{
    return mSiblingPrevNode;
}

//-----------------------------------------------------------------------------
// 
// VTreeNode::getNextSibling();
// 
// Returns the next object in the linked list.
// 
//-----------------------------------------------------------------------------
ITreeNode *VTreeNode::getNextSibling( void )
{
    return mSiblingNextNode;
}

//-----------------------------------------------------------------------------
// 
// VTreeNode::size();
// 
// Returns the number of child objects. Only includes top level.
// 
//-----------------------------------------------------------------------------
int VTreeNode::size( void )
{
    int size = 0;

    ITreeNode *node = mChildNode;
    while ( node )
    {
        size++;

        node = node->mSiblingNextNode;
    }

    return size;
}

//-----------------------------------------------------------------------------
// 
// VTreeNode::at( pIndex );
// 
// Returns the object at the given index.
// 
//-----------------------------------------------------------------------------
ITreeNode *VTreeNode::at( const int pIndex )
{
    int index = 0;

    ITreeNode *node = mChildNode;
    while ( node )
    {
        if ( index++ == pIndex )
        {
            return node;
        }

        node = node->mSiblingNextNode;
    }

    return NULL;
}

//-----------------------------------------------------------------------------
// 
// VTreeNode::getIndex();
// 
// Returns the index of the object in relation to the sibling nodes.
// 
//-----------------------------------------------------------------------------
int VTreeNode::getIndex( void )
{
    if ( !inTree() )
    {
        // No Index.
        return 0;
    }

    ITreeNode *walk = NULL;
    if ( mParentNode )
    {
        walk = mParentNode->mChildNode;
    }
    else
    {
        walk = this;
        while ( walk->mSiblingPrevNode )
        {
            // Walk Up.
            walk = walk->mSiblingPrevNode;
        }
    }

    for ( int i = 0; walk; walk = walk->mSiblingNextNode, i++ )
    {
        if ( walk == this )
        {
            return i;
        }
    }

    AssertFatal( false, "VTreeNode::getIndex() - Node List Broken?" );

    return 0;
}

//-----------------------------------------------------------------------------
// 
// VTreeNode::addTo( pNode );
// 
// Attach this node to the back of the target node.
// 
//-----------------------------------------------------------------------------
void VTreeNode::addTo( ITreeNode *pNode )
{
    if ( inTree() )
    {
        // Already In Tree.
        return;
    }

    // Set Parent.
    mParentNode = pNode;

    if ( !pNode->mChildNode )
    {
        // Store Child Node.
        pNode->mChildNode = this;
    }
    else
    {
        // Front Node.
        ITreeNode *headNode = pNode->mChildNode;

        // Fetch Head Node.
        while ( headNode->mSiblingNextNode )
        {
            headNode = headNode->mSiblingNextNode;
        }

        // Reference Next Node.
        headNode->mSiblingNextNode = this;

        // Reference Previous Node.
        mSiblingPrevNode = headNode;
    }

    // Callback.
    onAttach();
}

//-----------------------------------------------------------------------------
// 
// VTreeNode::addToFront( pNode );
// 
// Attach this node to the front of the target node.
// 
//-----------------------------------------------------------------------------
void VTreeNode::addToFront( ITreeNode *pNode )
{
    if ( inTree() )
    {
        // Already In Tree.
        return;
    }

    // Set Parent.
    mParentNode = pNode;

    if ( !pNode->mChildNode )
    {
        // Store Child Node.
        pNode->mChildNode = this;
    }
    else
    {
        // First Node.
        ITreeNode *childNode = pNode->mChildNode;

        // Reference Previous Node.
        childNode->mSiblingPrevNode = this;

        // Reference Next Node.
        mSiblingNextNode = childNode;

        // Store Child Node.
        pNode->mChildNode = this;
    }

    // Callback.
    onAttach();
}

//-----------------------------------------------------------------------------
// 
// VTreeNode::remove();
// 
// Detach this node from the current parent node.
// 
//-----------------------------------------------------------------------------
void VTreeNode::remove( void )
{
    if ( !inTree() )
    {
        return;
    }

    // Callback.
    onDetach();

    if ( mParentNode && mParentNode->mChildNode == this )
    {
        // Update Parent Reference.
        mParentNode->mChildNode = mSiblingNextNode;
    }

    if ( mSiblingNextNode )
    {
        // Update Previous Node.
        mSiblingNextNode->mSiblingPrevNode = mSiblingPrevNode;
    }

    if ( mSiblingPrevNode )
    {
        // Update Next Node.
        mSiblingPrevNode->mSiblingNextNode = mSiblingNextNode;
    }

    // Remove References.
    mParentNode = mSiblingPrevNode = mSiblingNextNode = NULL;
}

//-----------------------------------------------------------------------------
// 
// VTreeNode::moveTo( pNode );
// 
// Detach this node and attach it to the target node.
// 
//-----------------------------------------------------------------------------
void VTreeNode::moveTo( ITreeNode *pNode )
{
    if ( inTree() )
    {
        // Remove from Tree.
        remove();
    }

    // Add to tree.
    addTo( pNode );
}

//-----------------------------------------------------------------------------
// 
// VTreeNode::onAttach();
// 
// This method will be called when this node, or a parent node, is attached to
// a node.
// 
//-----------------------------------------------------------------------------
void VTreeNode::onAttach( void )
{
    // Notify Children.
    for ( ITreeNode *node = mChildNode; node != NULL; node = node->mSiblingNextNode )
    {
        node->onAttach();
    }
}

//-----------------------------------------------------------------------------
// 
// VTreeNode::onDetach();
// 
// This method will be called when this node, or a parent node, is detached.
// 
//-----------------------------------------------------------------------------
void VTreeNode::onDetach( void )
{
    // Notify Children.
    for ( ITreeNode *node = mChildNode; node != NULL; node = node->mSiblingNextNode )
    {
        node->onDetach();
    }
}

//-----------------------------------------------------------------------------
// 
// VTreeNode::inTree();
// 
// Returns true if the node is the a member of a node tree.
// 
//-----------------------------------------------------------------------------
bool VTreeNode::inTree( void )
{
    return !( mParentNode == NULL &&
              mSiblingPrevNode == NULL &&
              mSiblingNextNode == NULL );
}