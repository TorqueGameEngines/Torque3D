//-----------------------------------------------------------------------------
// Copyright (c) 2012 GarageGames, LLC
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

#ifndef _TREEOBJECT_H_
#define _TREEOBJECT_H_
#include "core/util/tVector.h"
#include "console/simObject.h"
#include "core/util/tDictionary.h"
#include "console/consoleTypes.h"

// Treenode class for multilateral or fixed (BVH/quad/oct) branching vectors.
// - CHILD_COUNT == 0  => dynamic children list (Vector grows/shrinks normally).
// - CHILD_COUNT != 0  => fixed slot array of children of size CHILD_COUNT.
//   In fixed mode we require nullClears == false so empty slots are represented as NULL. 
template <class T, bool nullClears = true, U32 CHILD_COUNT = 0>
class TreeNode : public Vector<TreeNode<T, nullClears, CHILD_COUNT>*, CHILD_COUNT>
{
public:
   using Node = TreeNode<T, nullClears, CHILD_COUNT>;
   using NodePtr = Node*;
   using BaseVec = Vector<NodePtr, CHILD_COUNT>;

   static constexpr bool mTFixedChildren = (CHILD_COUNT != 0);

   static_assert(!mTFixedChildren && (nullClears == true),
      "TreeNode<T, nullClears, CHILD_COUNT>: fixed CHILD_COUNT requires nullClears=false (use NULL slots).");

   //-------------------------------------------------------------------------
   // Data Members
   //-------------------------------------------------------------------------
   T data;
   NodePtr parent;

private:
   //-------------------------------------------------------------------------
   // Fixed/dynamic child storage helpers
   //-------------------------------------------------------------------------
   inline void _initChildrenStorage()
   {
      if constexpr (mTFixedChildren)
      {
         // Vector<T*, COUNT> default-constructs elements; pointer values are not guaranteed to be nullptr.
         // Ensure we start with all empty slots.
         for (U32 i = 0; i < CHILD_COUNT; ++i)
            (*this)[i] = NULL;
      }
   }

   inline bool _containsChildPtr(NodePtr child) const
   {
      if (!child) return false;
      for (U32 i = 0; i < this->size(); ++i)
         if ((*this)[i] == child)
            return true;
      return false;
   }

   inline bool _insertChildPtrUnique(NodePtr child)
   {
      if (!child) return false;

      if constexpr (!mTFixedChildren)
      {
         this->push_back_unique(child);
         return true;
      }
      else
      {
         // Fixed: place into first NULL slot, do not grow.
         for (U32 i = 0; i < CHILD_COUNT; ++i)
         {
            if ((*this)[i] == child)
               return true; // already present
         }

         for (U32 i = 0; i < CHILD_COUNT; ++i)
         {
            if ((*this)[i] == NULL)
            {
               (*this)[i] = child;
               return true;
            }
         }

         AssertFatal(false, "TreeNode - fixed child capacity exceeded.");
         return false;
      }
   }

   inline void _clearAllChildSlots()
   {
      if constexpr (!mTFixedChildren)
      {
         this->clear();
      }
      else
      {
         for (U32 i = 0; i < CHILD_COUNT; ++i)
            (*this)[i] = NULL;
      }
   }

public:
   //-------------------------------------------------------------------------
   // Constructors / Destructor
   //-------------------------------------------------------------------------
   inline TreeNode(const T& val = T(), NodePtr p = NULL)
      : data(val), parent(p)
   {
      _initChildrenStorage();
   }

   template<U32 OtherCount, typename OtherAllocator>
   inline TreeNode(const Vector<NodePtr, OtherCount, OtherAllocator>& children, NodePtr p = NULL)
      : data(T()), parent(p)
   {
      _initChildrenStorage();

      if constexpr (!mTFixedChildren)
      {
         this->increment(children.size());
         for (U32 i = 0; i < children.size(); ++i)
         {
            (*this)[i] = children[i];
            if (children[i])
            {
               AssertFatal(children[i] != this, "TreeNode::Constructor - Circular parent relationship");
               children[i]->parent = this;
            }
         }
      }
      else
      {
         const U32 n = getMin(children.size(), CHILD_COUNT);
         for (U32 i = 0; i < n; ++i)
         {
            (*this)[i] = children[i];
            if (children[i])
            {
               AssertFatal(children[i] != this, "TreeNode::Constructor - Circular parent relationship");
               children[i]->parent = this;
            }
         }
      }
   }

   virtual ~TreeNode()
   {
      deleteChildren();
      parent = NULL;
   }

   //-------------------------------------------------------------------------
   // Deep Copy / Cloning
   //-------------------------------------------------------------------------
   inline NodePtr clone() const
   {
      auto* copy = new Node(data, NULL);
      for (U32 i = 0; i < this->size(); ++i)
         if ((*this)[i])
            copy->addChild((*this)[i]->clone());
      return copy;
   }

   template<typename Func>
   inline NodePtr cloneIf(Func pred) const
   {
      if (!pred(this)) return NULL;
      auto* newNode = new Node(data, NULL);
      for (U32 i = 0; i < this->size(); ++i)
         if ((*this)[i])
         {
            auto* filteredChild = (*this)[i]->cloneIf(pred);
            if (filteredChild)
               newNode->addChild(filteredChild);
         }
      return newNode;
   }

   inline bool equals(const NodePtr other) const
   {
      if (!other || data != other->data || this->size() != other->size())
         return false;

      for (U32 i = 0; i < this->size(); ++i)
      {
         if ((*this)[i] && other->getChild(i))
         {
            if (!(*this)[i]->equals(other->getChild(i)))
               return false;
         }
         else if ((*this)[i] || other->getChild(i))
         {
            return false;
         }
      }
      return true;
   }

   static inline NodePtr mergeAt(NodePtr atNode, NodePtr subtree)
   {
      if (!atNode || !subtree)
         return NULL;
      atNode->addChild(subtree);
      return subtree;
   }

   static inline NodePtr cloneAt(NodePtr atNode, const NodePtr subtree)
   {
      if (!atNode || !subtree)
         return NULL;
      NodePtr newClone = subtree->clone();
      atNode->addChild(newClone);
      return newClone;
   }

   inline bool isSubtreeOf(const NodePtr other) const
   {
      if (!other) return false;
      if (equals(other)) return true;
      for (U32 i = 0; i < other->size(); ++i)
         if ((*other)[i] && isSubtreeOf((*other)[i]))
            return true;
      return false;
   }

   // Assignment operator: shallow copy of data and parent pointer only.
   // Does NOT copy children or subtree.
   inline Node& operator=(const Node& other)
   {
      if (this == &other)
         return *this;
      data = other.data;
      parent = other.parent;
      return *this;
   }

   //-------------------------------------------------------------------------
   // Node Type & Relationship Queries
   //-------------------------------------------------------------------------
   inline bool isRoot() const { return parent == NULL; }

   inline bool isLeaf() const
   {
      if constexpr (nullClears)
         return this->size() == 0;
      else
      {
         for (U32 i = 0; i < this->size(); ++i)
            if ((*this)[i] != NULL)
               return false;
         return true;
      }
   }

   inline bool hasChildren() const
   {
      if constexpr (nullClears)
         return this->size() > 0;
      else
      {
         for (U32 i = 0; i < this->size(); ++i)
            if ((*this)[i]) return true;
         return false;
      }
   }

   inline U32 getNumChildren() const
   {
      if constexpr (nullClears)
         return this->size();
      else
      {
         U32 count = 0;
         for (U32 i = 0; i < this->size(); ++i)
            if ((*this)[i]) ++count;
         return count;
      }
   }

   inline bool hasChild(NodePtr child) const
   {
      return _containsChildPtr(child);
   }

   inline S32 getChildIndex(NodePtr child) const
   {
      if (!child) return -1;
      for (U32 i = 0; i < this->size(); i++)
         if ((*this)[i] == child)
            return (S32)i;
      return -1;
   }

   inline bool isValidTree() const
   {
      for (U32 i = 0; i < this->size(); i++)
      {
         NodePtr child = (*this)[i];
         if (child && child->parent != this)
            return false;
      }
      return true;
   }

   inline bool isVisited(const Vector<NodePtr>& visited) const
   {
      for (U32 i = 0; i < visited.size(); ++i)
         if (visited[i] == this)
            return true;
      return false;
   }

   template<typename Func>
   inline NodePtr findLeafIf(Func pred)
   {
      if (isLeaf() && pred(this)) return this;
      for (U32 i = 0; i < this->size(); ++i)
         if ((*this)[i])
         {
            auto* found = (*this)[i]->findLeafIf(pred);
            if (found) return found;
         }
      return NULL;
   }

   //-------------------------------------------------------------------------
   // Parent/Ancestor Logic
   //-------------------------------------------------------------------------
   inline NodePtr getParent() { return parent; }
   inline const NodePtr getParent() const { return parent; }

   inline NodePtr getRoot()
   {
      NodePtr current = this;
      while (current->parent)
         current = current->parent;
      return current;
   }

   inline const NodePtr getRoot() const
   {
      const NodePtr current = const_cast<NodePtr>(this);
      NodePtr c = current;
      while (c->parent)
         c = c->parent;
      return c;
   }

   inline bool isAncestorOf(const NodePtr other) const
   {
      const Node* node = other ? other->parent : NULL;
      while (node)
      {
         if (node == this) return true;
         node = node->parent;
      }
      return false;
   }

   inline bool isDescendantOf(const NodePtr other) const
   {
      return other ? other->isAncestorOf(const_cast<NodePtr>(this)) : false;
   }

   inline NodePtr lowestCommonAncestor(NodePtr other)
   {
      Vector<NodePtr> pathA, pathB;
      getPathToRoot(pathA);
      other->getPathToRoot(pathB);

      NodePtr lca = NULL;
      S32 i = pathA.size() - 1, j = pathB.size() - 1;
      while (i >= 0 && j >= 0 && pathA[i] == pathB[j])
      {
         lca = pathA[i];
         --i; --j;
      }
      return lca;
   }

   inline void getPathToRoot(Vector<NodePtr>& out) const
   {
      NodePtr node = const_cast<NodePtr>(this);
      while (node)
      {
         out.push_back(node);
         node = node->parent;
      }
   }

   inline void setParent(NodePtr p)
   {
      if (parent == p) return;
      if (parent) parent->removeChild(this);
      parent = p;
      if (parent)
         parent->_insertChildPtrUnique(this);
   }

   inline void nullParent(bool orphan = true)
   {
      if (orphan && parent)
         parent->removeChild(this);
      parent = NULL;
   }

   static inline void safeDetachFromParent(NodePtr node)
   {
      if (!node) return;
      if (node->parent)
      {
         for (U32 i = 0; i < node->parent->size(); ++i)
         {
            if ((*node->parent)[i] == node)
            {
               node->parent->removeChild(node);
               break;
            }
         }
      }
      node->parent = NULL;
   }

   inline void collectAncestors(Vector<NodePtr>& outAncestors) const
   {
      NodePtr node = parent;
      while (node)
      {
         outAncestors.push_back_unique(node);
         node = node->parent;
      }
   }

   inline void collectAncestorsSortedByDepth(const Vector<NodePtr>& leaves, Vector<NodePtr>& outAncestors) const
   {
      Map<NodePtr, bool> ancestorSet;
      for (U32 i = 0; i < leaves.size(); ++i)
      {
         NodePtr node = leaves[i]->getParent();
         while (node)
         {
            ancestorSet.insert(node, true);
            node = node->getParent();
         }
      }

      outAncestors.clear();
      outAncestors.reserve(ancestorSet.size());
      for (typename Map<NodePtr, bool>::Iterator iter = ancestorSet.begin(); iter != ancestorSet.end(); ++iter)
         outAncestors.push_back(iter->key);

      outAncestors.sort([](NodePtr a, NodePtr b) {
         U32 depthA = a->getDepth();
         U32 depthB = b->getDepth();
         return (depthA > depthB) ? -1 : (depthA < depthB) ? 1 : 0;
      });
   }

   inline U32 getDepth() const
   {
      U32 depth = 0;
      NodePtr current = parent;
      while (current)
      {
         depth++;
         current = current->parent;
      }
      return depth;
   }

   template<typename Func>
   inline void forEachAncestor(Func callback) const
   {
      const Node* node = parent;
      while (node)
      {
         callback(node);
         node = node->parent;
      }
   }

   //-------------------------------------------------------------------------
   // Child Logic
   //-------------------------------------------------------------------------
   inline NodePtr addChild(const T& val)
   {
      NodePtr child = new Node(val, this);
      _insertChildPtrUnique(child);
      return child;
   }

   inline void addChild(NodePtr child)
   {
      AssertFatal(child != NULL, "TreeNode::addChild - Attempted to add NULL child");

      // Prevent duplicates.
      for (U32 i = 0; i < this->size(); i++)
         AssertFatal((*this)[i] != child, "TreeNode::addChild - Attempted to add duplicate child");

#ifdef TORQUE_DEBUG
      NodePtr ancestor = this;
      while (ancestor)
      {
         AssertFatal(ancestor != child, "TreeNode::addChild - Would create circular parent relationship");
         ancestor = ancestor->parent;
      }
#endif

      if (child->parent && child->parent != this)
         child->parent->removeChild(child);

      child->parent = this;
      _insertChildPtrUnique(child);
   }

   inline void setChild(U32 i, NodePtr child)
   {
      if constexpr (mTFixedChildren)
      {
         AssertFatal(i < CHILD_COUNT, "TreeNode::setChild - Index out of bounds for fixed child TreeNode");
      }
      else
      {
         if (i >= (U32)this->size())
         {
            U32 oldSize = this->size();
            this->increment((i + 1) - oldSize);
            for (U32 j = oldSize; j < (U32)this->size(); j++)
               (*this)[j] = NULL;
         }
      }

      NodePtr oldChild = (*this)[i];
      if (oldChild == child) return;

      if (oldChild)
         oldChild->parent = NULL;

      if (child == NULL)
      {
         if constexpr (nullClears)
            this->erase(i);
         else
            (*this)[i] = NULL;
         return;
      }

#ifdef TORQUE_DEBUG
      NodePtr ancestor = this;
      while (ancestor)
      {
         AssertFatal(ancestor != child, "TreeNode::setChild - Would create circular parent relationship");
         ancestor = ancestor->parent;
      }
#endif

      if (child->parent && child->parent != this)
      {
         child->parent->removeChild(child);
      }
      else if (child->parent == this)
      {
         for (U32 j = 0; j < (U32)this->size(); j++)
         {
            if (j != i && (*this)[j] == child)
            {
               if constexpr (nullClears)
                  this->erase(j);
               else
                  (*this)[j] = NULL;
            }
         }
      }

      for (U32 j = 0; j < (U32)this->size(); j++)
         AssertFatal(j == i || (*this)[j] != child, "TreeNode::setChild - Attempted to set duplicate child");

      (*this)[i] = child;
      child->parent = this;
   }

   inline NodePtr getChild(U32 i)
   {
      if (i < (U32)this->size())
      {
         if ((*this)[i] && (*this)[i]->parent != this)
            AssertFatal(false, "TreeNode::getChild - Child parent pointer mismatch");
         return (*this)[i];
      }
      return NULL;
   }

   inline const NodePtr getChild(U32 i) const
   {
      if (i < (U32)this->size())
      {
         if ((*this)[i] && (*this)[i]->parent != this)
            AssertFatal(false, "TreeNode::getChild - Child parent pointer mismatch");
         return (*this)[i];
      }
      return NULL;
   }

   inline Vector<NodePtr> getChildren() const
   {
      Vector<NodePtr> children;
      for (U32 i = 0; i < (U32)this->size(); ++i)
         if ((*this)[i])
            children.push_back((*this)[i]);
      return children;
   }

   inline void addChildren(const Vector<NodePtr>* children)
   {
      if (!children) return;
      for (U32 i = 0; i < (U32)children->size(); i++)
      {
         NodePtr child = (*children)[i];
         if (!child)
            continue;

         if (_containsChildPtr(child))
            continue;

#ifdef TORQUE_DEBUG
         NodePtr ancestor = this;
         while (ancestor)
         {
            AssertFatal(ancestor != child, "TreeNode::addChildren - Would create circular parent relationship");
            ancestor = ancestor->parent;
         }
#endif

         if (child->parent && child->parent != this)
         {
            bool foundInParent = false;
            for (U32 k = 0; k < (U32)child->parent->size(); ++k)
            {
               if ((*child->parent)[k] == child)
               {
                  foundInParent = true;
                  break;
               }
            }
            if (foundInParent)
               child->parent->removeChild(child);
            else
               child->parent = NULL;
         }

         if (child->parent == this)
            continue;

         child->parent = this;
         _insertChildPtrUnique(child);
      }
   }

   inline void clearChildren()
   {
      for (U32 i = 0; i < (U32)this->size(); i++)
      {
         NodePtr child = (*this)[i];
         if (child)
         {
            if (child->parent != this)
            {
#ifdef TORQUE_DEBUG
               Con::warnf("TreeNode::clearChildren - Child at index %u has incorrect parent pointer (corruption detected)", i);
#endif
               child->parent = NULL;
            }
            else
            {
               child->parent = NULL;
            }
         }
      }

      _clearAllChildSlots();
   }

   inline void deleteChildren()
   {
      Vector<NodePtr> children;
      for (U32 i = 0; i < (U32)this->size(); i++)
      {
         NodePtr child = (*this)[i];
         if (child)
         {
            if (child->parent != this)
            {
#ifdef TORQUE_DEBUG
               Con::warnf("TreeNode::deleteChildren - Child at index %u has incorrect parent pointer (corruption detected)", i);
#endif
               child->parent = NULL;
            }
            else
            {
               child->parent = NULL;
            }
         }
         children.push_back_unique(child);
      }

      _clearAllChildSlots();

      for (U32 i = 0; i < (U32)children.size(); i++)
      {
         if (children[i])
            delete children[i];
      }
   }

   inline void removeChild(NodePtr child)
   {
      AssertFatal(child != NULL, "TreeNode::removeChild - Attempted to remove NULL child");
      bool found = false;

      for (U32 i = 0; i < (U32)this->size(); i++)
      {
         if ((*this)[i] == child)
         {
            child->parent = NULL;
            if constexpr (nullClears)
               this->erase(i);
            else
               (*this)[i] = NULL;
            found = true;
            break;
         }
      }

      if (!found)
      {
#ifdef TORQUE_DEBUG
         for (U32 i = 0; i < (U32)this->size(); i++)
         {
            if ((*this)[i] && (*this)[i]->parent == this)
            {
               (*this)[i]->parent = NULL;
               if constexpr (nullClears)
                  this->erase(i);
               else
                  (*this)[i] = NULL;
               Con::warnf("TreeNode::removeChild - Repaired mismatched child pointer at index %u", i);
               found = true;
               break;
            }
         }
         if (!found)
            Con::errorf("TreeNode::removeChild - Child not found in parent's children array (corruption detected)");
#endif
      }

      AssertFatal(found, "TreeNode::removeChild - Child not found in parent's children array");
   }

   inline void removeChild(U32 i)
   {
      AssertFatal(i < (U32)this->size(), "TreeNode::removeChild - Index out of bounds");
      NodePtr child = (*this)[i];
      if (child)
         child->parent = NULL;

      if constexpr (nullClears)
         this->erase(i);
      else
         (*this)[i] = NULL;
   }

   inline void replaceChild(NodePtr oldChild, NodePtr newChild)
   {
      AssertFatal(oldChild != NULL, "TreeNode::replaceChild - Attempted to replace NULL child");
      S32 idx = getChildIndex(oldChild);
      AssertFatal(idx != -1, "TreeNode::replaceChild - oldChild not found in children");
      setChild((U32)idx, newChild);
   }

   inline void nullChild(U32 i)
   {
      if (i >= (U32)this->size())
         return;
      NodePtr child = (*this)[i];
      if (child && child->parent == this)
         child->parent = NULL;
      (*this)[i] = NULL;
   }

   inline void swapChildren(U32 i, U32 j)
   {
      if (i >= (U32)this->size() || j >= (U32)this->size() || i == j)
         return;

      NodePtr childI = (*this)[i];
      NodePtr childJ = (*this)[j];
      if (childI && childI->parent != this)
         childI->parent = this;
      if (childJ && childJ->parent != this)
         childJ->parent = this;

      (*this)[i] = childJ;
      (*this)[j] = childI;
   }

   //-------------------------------------------------------------------------
   // Sibling Logic
   //-------------------------------------------------------------------------
   inline Vector<NodePtr> getSiblings() const
   {
      Vector<NodePtr> siblings;
      if (!parent) return siblings;
      siblings.reserve(parent->size() - 1);
      for (U32 i = 0; i < (U32)parent->size(); i++)
      {
         NodePtr sibling = (*parent)[i];
         if (sibling && sibling != this)
            siblings.push_back_unique(sibling);
      }
      return siblings;
   }

   //-------------------------------------------------------------------------
   // Traversal & Collection
   //-------------------------------------------------------------------------
   inline void findLeaves(Vector<NodePtr>& out)
   {
      if (isLeaf())
         out.push_back_unique(this);
      else
         for (U32 i = 0; i < (U32)this->size(); ++i)
            if ((*this)[i])
               (*this)[i]->getLeaves(out);
   }

   inline void collectSubtree(Vector<NodePtr>& nodes)
   {
      nodes.push_back_unique(this);
      for (U32 i = 0; i < (U32)this->size(); ++i)
         if ((*this)[i])
            (*this)[i]->collectSubtree(nodes);
   }

   inline void collectSubtreeData(Vector<T>& dataList)
   {
      dataList.push_back_unique(data);
      for (U32 i = 0; i < (U32)this->size(); ++i)
         if ((*this)[i])
            (*this)[i]->collectSubtreeData(dataList);
   }

   template<typename Func>
   inline void forEachChild(Func callback)
   {
      for (U32 i = 0; i < (U32)this->size(); i++)
         if ((*this)[i])
            callback((*this)[i]);
   }

   template<typename Func>
   inline void forEachChild(Func callback) const
   {
      for (U32 i = 0; i < (U32)this->size(); i++)
         if ((*this)[i])
            callback((*this)[i]);
   }

   template<typename Func>
   inline void forEachInSubtree(Func callback)
   {
      callback(this);
      for (U32 i = 0; i < (U32)this->size(); i++)
         if ((*this)[i])
            (*this)[i]->forEachInSubtree(callback);
   }

   template<typename Func>
   inline void forEachLeaf(Func callback)
   {
      if (isLeaf())
         callback(this);
      else
         for (U32 i = 0; i < (U32)this->size(); i++)
            if ((*this)[i])
               (*this)[i]->forEachLeaf(callback);
   }

   template<typename Func>
   inline void traverseBreadthFirst(Func callback)
   {
      Vector<NodePtr> queue;
      queue.push_back(this);
      while (!queue.empty())
      {
         NodePtr node = queue.first();
         queue.erase(0);
         callback(node);
         for (U32 i = 0; i < (U32)node->size(); ++i)
            if ((*node)[i])
               queue.push_back((*node)[i]);
      }
   }

   template<typename Func>
   inline void refitPathToRoot(Func refitFunc)
   {
      NodePtr node = parent;
      while (node)
      {
         refitFunc(node);
         node = node->parent;
      }
   }

   template<typename Func>
   inline NodePtr findIf(Func pred)
   {
      if (pred(this)) return this;
      for (U32 i = 0; i < (U32)this->size(); ++i)
         if ((*this)[i])
         {
            auto* found = (*this)[i]->findIf(pred);
            if (found) return found;
         }
      return NULL;
   }

   template<typename Func>
   inline void findAllIf(Func pred, Vector<NodePtr>& out)
   {
      if (pred(this))
         out.push_back(this);
      for (U32 i = 0; i < (U32)this->size(); ++i)
         if ((*this)[i])
            (*this)[i]->findAllIf(pred, out);
   }

   template<typename Func>
   inline U32 countIf(Func pred) const
   {
      U32 count = pred(this) ? 1 : 0;
      for (U32 i = 0; i < (U32)this->size(); ++i)
         if ((*this)[i])
            count += (*this)[i]->countIf(pred);
      return count;
   }

   template<typename Func>
   inline void removeIf(Func pred)
   {
      for (S32 i = this->size() - 1; i >= 0; --i)
      {
         if ((*this)[i] && pred((*this)[i]))
         {
            delete (*this)[i];
            if constexpr (nullClears)
               this->erase(i);
            else
               (*this)[i] = NULL;
         }
         else if ((*this)[i])
         {
            (*this)[i]->removeIf(pred);
         }
      }
   }

   //-------------------------------------------------------------------------
   // Tree Metrics
   //-------------------------------------------------------------------------
   inline U32 getTreeSize() const
   {
      U32 count = 1;
      for (U32 i = 0; i < (U32)this->size(); i++)
         if ((*this)[i])
            count += (*this)[i]->getTreeSize();
      return count;
   }

   inline U32 getMaxDepth() const
   {
      if (isLeaf()) return 0;
      U32 maxDepth = 0;
      for (U32 i = 0; i < (U32)this->size(); i++)
         if ((*this)[i])
         {
            U32 childDepth = (*this)[i]->getMaxDepth();
            if (childDepth > maxDepth)
               maxDepth = childDepth;
         }
      return maxDepth + 1;
   }

   //-------------------------------------------------------------------------
   // Rotation/Balance Utilities
   //-------------------------------------------------------------------------
   static inline U32 gatherRotationCandidates(NodePtr parent, Vector<NodePtr>& outNodes, U32 maxCandidates = 8)
   {
      outNodes.clear();
      for (U32 i = 0; i < (U32)parent->size() && outNodes.size() < maxCandidates; ++i)
      {
         NodePtr child = (*parent)[i];
         if (!child) continue;
         if (child->isLeaf())
         {
            outNodes.push_back_unique(child);
         }
         else
         {
            for (U32 j = 0; j < (U32)child->size() && outNodes.size() < maxCandidates; ++j)
            {
               NodePtr grandChild = (*child)[j];
               if (grandChild) outNodes.push_back_unique(grandChild);
            }
         }
      }
      return outNodes.size();
   }

   static inline bool findBestRotationPairing(
      const Vector<NodePtr>& nodes,
      U32 groupSize,
      F32(*costFunc)(const Node*, const Node*),
      Vector<U32>& outGroupA,
      Vector<U32>& outGroupB,
      F32& outBestCost)
   {
      const U32 n = nodes.size();
      if (n < 2 * groupSize) return false;
      outBestCost = F32_MAX;
      bool found = false;

      Vector<U32> indices;
      indices.setSize(n);
      for (U32 i = 0; i < n; ++i) indices[i] = i;

      Vector<U32> groupA, groupB;
      groupA.setSize(groupSize);
      groupB.setSize(groupSize);

      while (true)
      {
         for (U32 i = 0; i < groupSize; ++i)
            groupA[i] = indices[i];

         U32 bIdx = 0;
         for (U32 i = groupSize; i < n; ++i)
            groupB[bIdx++] = indices[i];

         if (bIdx == groupSize)
         {
            F32 costA = costFunc(nodes[groupA[0]], nodes[groupA[1]]);
            F32 costB = costFunc(nodes[groupB[0]], nodes[groupB[1]]);
            F32 totalCost = costA + costB;
            if (totalCost < outBestCost)
            {
               outBestCost = totalCost;
               outGroupA = groupA;
               outGroupB = groupB;
               found = true;
            }
         }

         S32 k = n - 2;
         while (k >= 0 && indices[k] >= indices[k + 1]) --k;
         if (k < 0) break;

         S32 l = n - 1;
         while (indices[k] >= indices[l]) --l;

         U32 tmp = indices[k]; indices[k] = indices[l]; indices[l] = tmp;

         for (U32 i = k + 1, j = n - 1; i < j; ++i, --j)
         {
            tmp = indices[i]; indices[i] = indices[j]; indices[j] = tmp;
         }
      }

      return found;
   }

   //-------------------------------------------------------------------------
   // Data Accessors
   //-------------------------------------------------------------------------
   inline T getData() const { return data; }
   inline void setData(const T& val) { data = val; }
   inline void operator =(const T& val) { data = val; }
   inline T* getDataPtr() { return &data; }
   inline const T* getDataPtr() const { return &data; }

   //-------------------------------------------------------------------------
   // Type Conversion Helpers
   //-------------------------------------------------------------------------
   template<typename Derived>
   inline Derived* getChildAs(U32 i) { return static_cast<Derived*>(getChild(i)); }
   template<typename Derived>
   inline const Derived* getChildAs(U32 i) const { return static_cast<const Derived*>(getChild(i)); }

   template<typename Derived>
   inline Vector<Derived*> getChildrenAs()
   {
      Vector<Derived*> out;
      for (U32 i = 0; i < (U32)this->size(); ++i)
         if ((*this)[i])
            out.push_back(static_cast<Derived*>((*this)[i]));
      return out;
   }

   template<typename Derived>
   inline Vector<const Derived*> getChildrenAs() const
   {
      Vector<const Derived*> out;
      for (U32 i = 0; i < (U32)this->size(); ++i)
         if ((*this)[i])
            out.push_back(static_cast<const Derived*>((*this)[i]));
      return out;
   }

   template<typename Derived, typename Func>
   inline void forEachLeafAs(Func callback)
   {
      if (isLeaf())
         callback(static_cast<Derived*>(this));
      else
         for (U32 i = 0; i < (U32)this->size(); i++)
            if ((*this)[i])
               (*this)[i]->template forEachLeafAs<Derived>(callback);
   }

   template<typename Derived, typename Func>
   inline void forEachLeafAs(Func callback) const
   {
      if (isLeaf())
         callback(static_cast<const Derived*>(this));
      else
         for (U32 i = 0; i < (U32)this->size(); i++)
            if ((*this)[i])
               (*this)[i]->template forEachLeafAs<Derived>(callback);
   }
};

class TreeObject : public SimObject {
   typedef SimObject Parent;

public:
   struct Node : public TreeNode<void*> {
      S32 key;
      ConsoleBaseType* type;
      Node(S32 k, ConsoleBaseType* t) : TreeNode<void*>(NULL, NULL), key(k), type(t) {}
      ~Node() {
         if (data)
         {
            dFree(data);
            data = NULL;
         }
      }
   };

   S32 mNextFreeKey;
   Map<S32, Node*> mKeyMap;
   Node* mRoot;
   ConsoleBaseType* mTreeType;

   TreeObject() : mRoot(NULL), mNextFreeKey(0)
   {
      mTreeType = ConsoleBaseType::getType(TypeS32);
   }
   ~TreeObject();

   void _internalSetType(const char* typeName);
   static bool _setType(void* obj, const char* index, const char* data);
   void setType(const char* typeName);
   static void initPersistFields();

   S32 addNode(S32 parentKey, const char* scriptData, S32 forcedKey = -1);
   Node* findNode(S32 key);
   void deleteNode(S32 key);
   void _deleteNode(Node* node, bool unlinkFromMap);

   S32 getParent(S32 key);
   bool toParent(S32 key, S32 newParentKey);

   Vector<S32>  getChildren(S32 key);
   S32 getNumChildren(S32 key) { return getChildren(key).size(); };

   Vector<S32>  getSiblings(S32 key);
   S32 getNumSiblings(S32 key) { return getSiblings(key).size(); };

   const char* nodesToString(const Vector<S32>& keys);
   const char* toString();
   void _toStringRecursive(Node* node, char* buffer, U32& bufferPos, U32 bufSize);

   void fromString(const char* data);
   void _fromStringRecursive(const char* str, S32 parentKey);

   DECLARE_CONOBJECT(TreeObject);
};
#endif //_TREEOBJECT_H_
