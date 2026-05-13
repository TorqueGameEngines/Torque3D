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

// Add nullClears as a template argument (default: true. set false for BVH/quad/octrees)
template <class T, bool nullClears = true>
class TreeNode : public Vector<TreeNode<T, nullClears>*> {
public:
   //-------------------------------------------------------------------------
   // Data Members
   //-------------------------------------------------------------------------
   T data;
   TreeNode<T, nullClears>* parent;

   //-------------------------------------------------------------------------
   // Constructors / Destructor
   //-------------------------------------------------------------------------
   inline TreeNode(const T& val = T(), TreeNode<T, nullClears>* p = NULL)
      : data(val), parent(p) {}

   inline TreeNode(const Vector<TreeNode<T, nullClears>*>& children, TreeNode<T, nullClears>* p = NULL)
      : data(T()), parent(p)
   {
      increment(children.size());
      for (U32 i = 0; i < children.size(); ++i) {
         (*this)[i] = children[i];
         if (children[i]) {
            AssertFatal(children[i] != this, "TreeNode::Constructor - Circular parent relationship");
            children[i]->parent = this;
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
   // Creates a deep copy of this node and its entire subtree.
   inline TreeNode<T, nullClears>* clone() const {
      auto* copy = new TreeNode<T, nullClears>(data, NULL);
      for (U32 i = 0; i < this->size(); ++i)
         if ((*this)[i])
            copy->addChild((*this)[i]->clone());
      return copy;
   }

   template<typename Func>
   inline TreeNode<T, nullClears>* cloneIf(Func pred) const {
      if (!pred(this)) return NULL;
      auto* newNode = new TreeNode<T, nullClears>(data, NULL);
      for (U32 i = 0; i < this->size(); ++i)
         if ((*this)[i]) {
            auto* filteredChild = (*this)[i]->cloneIf(pred);
            if (filteredChild)
               newNode->addChild(filteredChild);
         }
      return newNode;
   }

   inline bool equals(const TreeNode<T, nullClears>* other) const {
      if (!other || data != other->data || this->size() != other->size())
         return false;
      for (U32 i = 0; i < this->size(); ++i) {
         if ((*this)[i] && other->getChild(i)) {
            if (!(*this)[i]->equals(other->getChild(i)))
               return false;
         }
         else if ((*this)[i] || other->getChild(i)) {
            return false;
         }
      }
      return true;
   }

   static inline TreeNode<T, nullClears>* mergeAt(TreeNode<T, nullClears>* atNode, TreeNode<T, nullClears>* subtree) {
      if (!atNode || !subtree)
         return NULL;
      atNode->addChild(subtree);
      return subtree;
   }

   static inline TreeNode<T, nullClears>* cloneAt(TreeNode<T, nullClears>* atNode, const TreeNode<T, nullClears>* subtree) {
      if (!atNode || !subtree)
         return NULL;
      TreeNode<T, nullClears>* newClone = subtree->clone();
      atNode->addChild(newClone);
      return newClone;
   }

   inline bool isSubtreeOf(const TreeNode<T, nullClears>* other) const {
      if (!other) return false;
      if (equals(other)) return true;
      for (U32 i = 0; i < other->size(); ++i)
         if ((*other)[i] && isSubtreeOf((*other)[i]))
            return true;
      return false;
   }
   // Assignment operator: shallow copy of data and parent pointer only.
   // Does NOT copy children or subtree.

   inline TreeNode<T, nullClears>& operator=(const TreeNode<T, nullClears>& other) {
      if (this == &other)
         return *this;
      data = other.data;
      parent = other.parent;
      // Children are NOT copied; this is a shallow assignment.
      return *this;
   }
   //-------------------------------------------------------------------------
   // Node Type & Relationship Queries
   //-------------------------------------------------------------------------
   inline bool isRoot() const { return parent == NULL; }
   inline bool isLeaf() const {
      if constexpr (nullClears)
         return this->size() == 0;
      else {
         for (U32 i = 0; i < this->size(); ++i) {
            if ((*this)[i] != NULL)
               return false;
         }
         return true;
      }
   }
   inline bool hasChildren() const {
      if constexpr (nullClears)
         return this->size() > 0;
      else {
         for (U32 i = 0; i < this->size(); ++i)
            if ((*this)[i]) return true;
         return false;
      }
   }
   inline U32 getNumChildren() const {
      if constexpr (nullClears)
         return this->size();
      else {
         U32 count = 0;
         for (U32 i = 0; i < this->size(); ++i)
            if ((*this)[i]) ++count;
         return count;
      }
   }
   inline bool hasChild(TreeNode<T, nullClears>* child) const {
      if (!child) return false;
      for (U32 i = 0; i < this->size(); i++)
         if ((*this)[i] == child)
            return true;
      return false;
   }
   inline S32 getChildIndex(TreeNode<T, nullClears>* child) const {
      if (!child) return -1;
      for (U32 i = 0; i < this->size(); i++)
         if ((*this)[i] == child)
            return (S32)i;
      return -1;
   }
   inline bool isValidTree() const {
      for (U32 i = 0; i < this->size(); i++) {
         TreeNode<T, nullClears>* child = (*this)[i];
         if (child && child->parent != this)
            return false;
      }
      return true;
   }
   inline bool isVisited(const Vector<TreeNode<T, nullClears>*>& visited) const {
      for (U32 i = 0; i < visited.size(); ++i)
         if (visited[i] == this)
            return true;
      return false;
   }
   template<typename Func>
   inline TreeNode<T, nullClears>* findLeafIf(Func pred) {
      if (isLeaf() && pred(this)) return this;
      for (U32 i = 0; i < this->size(); ++i)
         if ((*this)[i]) {
            auto* found = (*this)[i]->findLeafIf(pred);
            if (found) return found;
         }
      return NULL;
   }
   //-------------------------------------------------------------------------
   // Parent/Ancestor Logic
   //-------------------------------------------------------------------------
   inline TreeNode<T, nullClears>* getParent() { return parent; }
   inline const TreeNode<T, nullClears>* getParent() const { return parent; }
   inline TreeNode<T, nullClears>* getRoot() {
      TreeNode<T, nullClears>* current = this;
      while (current->parent)
         current = current->parent;
      return current;
   }
   inline const TreeNode<T, nullClears>* getRoot() const {
      const TreeNode<T, nullClears>* current = this;
      while (current->parent)
         current = current->parent;
      return current;
   }
   inline bool isAncestorOf(const TreeNode<T, nullClears>* other) const {
      const TreeNode<T, nullClears>* node = other->parent;
      while (node) {
         if (node == this) return true;
         node = node->parent;
      }
      return false;
   }
   inline bool isDescendantOf(const TreeNode<T, nullClears>* other) const {
      return other->isAncestorOf(this);
   }
   inline TreeNode<T, nullClears>* lowestCommonAncestor(TreeNode<T, nullClears>* other) {
      Vector<TreeNode<T, nullClears>*> pathA, pathB;
      getPathToRoot(pathA);
      other->getPathToRoot(pathB);
      TreeNode<T, nullClears>* lca = NULL;
      S32 i = pathA.size() - 1, j = pathB.size() - 1;
      while (i >= 0 && j >= 0 && pathA[i] == pathB[j]) {
         lca = pathA[i];
         --i; --j;
      }
      return lca;
   }
   inline void getPathToRoot(Vector<const TreeNode<T, nullClears>*>& out) const {
      const TreeNode<T, nullClears>* node = this;
      while (node) {
         out.push_back(node);
         node = node->parent;
      }
   }
   inline void setParent(TreeNode<T, nullClears>* p) {
      if (parent == p) return;
      if (parent) parent->removeChild(this);
      parent = p;
      if (parent) parent->push_back_unique(this);
   }
   inline void nullParent(bool orphan = true) {
      if (orphan && parent)
         parent->removeChild(this);
      parent = NULL;
   }
   static inline void safeDetachFromParent(TreeNode<T, nullClears>* node) {
      if (!node) return;
      if (node->parent) {
         for (U32 i = 0; i < node->parent->size(); ++i) {
            if ((*node->parent)[i] == node) {
               node->parent->removeChild(node);
               break;
            }
         }
      }
      node->parent = NULL;
   }
   inline void collectAncestors(Vector<TreeNode<T, nullClears>*>& outAncestors) const {
      TreeNode<T, nullClears>* node = parent;
      while (node) {
         outAncestors.push_back_unique(node);
         node = node->parent;
      }
   }
   inline void collectAncestorsSortedByDepth(const Vector<TreeNode<T, nullClears>*>& leaves, Vector<TreeNode<T, nullClears>*>& outAncestors) const {
      Map<TreeNode<T, nullClears>*, bool> ancestorSet;
      for (U32 i = 0; i < leaves.size(); ++i) {
         TreeNode<T, nullClears>* node = leaves[i]->getParent();
         while (node) {
            ancestorSet.insert(node, true);
            node = node->getParent();
         }
      }
      outAncestors.clear();
      outAncestors.reserve(ancestorSet.size());
      for (typename Map<TreeNode<T, nullClears>*, bool>::Iterator iter = ancestorSet.begin(); iter != ancestorSet.end(); ++iter)
         outAncestors.push_back(iter->key);
      outAncestors.sort([](TreeNode<T, nullClears>* a, TreeNode<T, nullClears>* b) {
         U32 depthA = a->getDepth();
         U32 depthB = b->getDepth();
         return (depthA > depthB) ? -1 : (depthA < depthB) ? 1 : 0;
      });
   }
   inline U32 getDepth() const {
      U32 depth = 0;
      TreeNode<T, nullClears>* current = parent;
      while (current) {
         depth++;
         current = current->parent;
      }
      return depth;
   }
   template<typename Func>
   inline void forEachAncestor(Func callback) const {
      const TreeNode<T, nullClears>* node = parent;
      while (node) {
         callback(node);
         node = node->parent;
      }
   }
   //-------------------------------------------------------------------------
   // Child Logic
   //-------------------------------------------------------------------------
   inline TreeNode<T, nullClears>* addChild(const T& val) {
      TreeNode<T, nullClears>* child = new TreeNode<T, nullClears>(val, this);
      push_back_unique(child);
      return child;
   }
   inline void addChild(TreeNode<T, nullClears>* child) {
      for (U32 i = 0; i < this->size(); i++)
         AssertFatal((*this)[i] != child, "TreeNode::addChild - Attempted to add duplicate child");
#ifdef TORQUE_DEBUG
      TreeNode<T, nullClears>* ancestor = this;
      while (ancestor) {
         AssertFatal(ancestor != child, "TreeNode::addChild - Would create circular parent relationship");
         ancestor = ancestor->parent;
      }
#endif
      if (child->parent && child->parent != this) {
         child->parent->removeChild(child);
      }
      child->parent = this;
      push_back_unique(child);
   }
   inline void setChild(U32 i, TreeNode<T, nullClears>* child) {
      if (i >= this->size()) {
         U32 oldSize = this->size();
         increment((i + 1) - oldSize);
         for (U32 j = oldSize; j < this->size(); j++)
            (*this)[j] = NULL;
      }
      TreeNode<T, nullClears>* oldChild = (*this)[i];
      if (oldChild == child) return;
      if (oldChild)
         oldChild->parent = NULL;
      if (child == NULL) {
         if constexpr (nullClears)
            this->erase(i);
         else
            (*this)[i] = NULL;
         return;
      }
#ifdef TORQUE_DEBUG
      TreeNode<T, nullClears>* ancestor = this;
      while (ancestor) {
         AssertFatal(ancestor != child, "TreeNode::setChild - Would create circular parent relationship");
         ancestor = ancestor->parent;
      }
#endif
      if (child->parent && child->parent != this) {
         child->parent->removeChild(child);
      }
      else if (child->parent == this) {
         for (U32 j = 0; j < this->size(); j++) {
            if (j != i && (*this)[j] == child)
               if constexpr (nullClears)
                  this->erase(j);
               else
                  (*this)[j] = NULL;
         }
      }
      for (U32 j = 0; j < this->size(); j++)
         AssertFatal(j == i || (*this)[j] != child, "TreeNode::setChild - Attempted to set duplicate child");
      (*this)[i] = child;
      child->parent = this;
   }
   inline TreeNode<T, nullClears>* getChild(U32 i) {
      if (i < this->size()) {
         if ((*this)[i] && (*this)[i]->parent != this) {
            AssertFatal(false, "TreeNode::getChild - Child parent pointer mismatch");
         }
         return (*this)[i];
      }
      return NULL;
   }
   inline const TreeNode<T, nullClears>* getChild(U32 i) const {
      if (i < this->size()) {
         if ((*this)[i] && (*this)[i]->parent != this) {
            AssertFatal(false, "TreeNode::getChild - Child parent pointer mismatch");
         }
         return (*this)[i];
      }
      return NULL;
   }
   inline Vector<TreeNode<T, nullClears>*> getChildren() const
   {
      Vector<TreeNode<T, nullClears>*> children;
      for (U32 i = 0; i < this->size(); ++i) {
         if ((*this)[i])
            children.push_back((*this)[i]);
      }
      return children;
   }

   inline void addChildren(const Vector<TreeNode<T, nullClears>*>* children) {
      if (!children) return;
      for (U32 i = 0; i < children->size(); i++) {
         TreeNode<T, nullClears>* child = (*children)[i];
         if (!child)
            continue;
         bool isDuplicate = false;
         for (U32 j = 0; j < this->size(); j++) {
            if ((*this)[j] == child) {
               isDuplicate = true;
               break;
            }
         }
         if (isDuplicate)
            continue;
#ifdef TORQUE_DEBUG
         TreeNode<T, nullClears>* ancestor = this;
         while (ancestor) {
            AssertFatal(ancestor != child, "TreeNode::addChildren - Would create circular parent relationship");
            ancestor = ancestor->parent;
         }
#endif
         if (child->parent && child->parent != this) {
            bool foundInParent = false;
            for (U32 k = 0; k < child->parent->size(); ++k) {
               if ((*child->parent)[k] == child) {
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
         push_back_unique(child);
      }
   }
   inline void clearChildren() {
      for (U32 i = 0; i < this->size(); i++) {
         TreeNode<T, nullClears>* child = (*this)[i];
         if (child) {
            if (child->parent != this) {
#ifdef TORQUE_DEBUG
               Con::warnf("TreeNode::clearChildren - Child at index %u has incorrect parent pointer (corruption detected)", i);
#endif
               child->parent = NULL;
            }
            else {
               child->parent = NULL;
            }
         }
      }
      this->clear();
   }
   inline void deleteChildren() {
      Vector<TreeNode<T, nullClears>*> children;
      for (U32 i = 0; i < this->size(); i++) {
         TreeNode<T, nullClears>* child = (*this)[i];
         if (child) {
            if (child->parent != this) {
#ifdef TORQUE_DEBUG
               Con::warnf("TreeNode::deleteChildren - Child at index %u has incorrect parent pointer (corruption detected)", i);
#endif
               child->parent = NULL;
            }
            else {
               child->parent = NULL;
            }
         }
         children.push_back_unique(child);
      }
      this->clear();
      for (U32 i = 0; i < children.size(); i++) {
         if (children[i]) {
            delete children[i];
         }
      }
   }
   inline void removeChild(TreeNode<T, nullClears>* child) {
      AssertFatal(child != NULL, "TreeNode::removeChild - Attempted to remove NULL child");
      bool found = false;
      for (U32 i = 0; i < this->size(); i++) {
         if ((*this)[i] == child) {
            child->parent = NULL;
            if constexpr (nullClears)
               this->erase(i);
            else
               (*this)[i] = NULL;
            found = true;
            break;
         }
      }
      if (!found) {
#ifdef TORQUE_DEBUG
         for (U32 i = 0; i < this->size(); i++) {
            if ((*this)[i] && (*this)[i]->parent == this) {
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
   inline void removeChild(U32 i) {
      AssertFatal(i < this->size(), "TreeNode::removeChild - Index out of bounds");
      TreeNode<T, nullClears>* child = (*this)[i];
      if (child)
         child->parent = NULL;
      if constexpr (nullClears)
         this->erase(i);
      else
         (*this)[i] = NULL;
   }
   inline void replaceChild(TreeNode<T, nullClears>* oldChild, TreeNode<T, nullClears>* newChild) {
      AssertFatal(oldChild != NULL, "TreeNode::replaceChild - Attempted to replace NULL child");
      S32 idx = getChildIndex(oldChild);
      AssertFatal(idx != -1, "TreeNode::replaceChild - oldChild not found in children");
      setChild((U32)idx, newChild);
   }
   inline void nullChild(U32 i) {
      if (i >= this->size())
         return;
      TreeNode<T, nullClears>* child = (*this)[i];
      if (child && child->parent == this)
         child->parent = NULL;
      (*this)[i] = NULL;
   }
   inline void swapChildren(U32 i, U32 j) {
      if (i >= this->size() || j >= this->size() || i == j)
         return;
      TreeNode<T, nullClears>* childI = (*this)[i];
      TreeNode<T, nullClears>* childJ = (*this)[j];
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
   inline Vector<TreeNode<T, nullClears>*> getSiblings() const {
      Vector<TreeNode<T, nullClears>*> siblings;
      if (!parent) return siblings;
      siblings.reserve(parent->size() - 1);
      for (U32 i = 0; i < parent->size(); i++) {
         TreeNode<T, nullClears>* sibling = (*parent)[i];
         if (sibling && sibling != this)
            siblings.push_back_unique(sibling);
      }
      return siblings;
   }

   //-------------------------------------------------------------------------
   // Traversal & Collection
   //-------------------------------------------------------------------------
   inline void findLeaves(Vector<TreeNode<T, nullClears>*>& out) {
      if (isLeaf())
         out.push_back_unique(this);
      else
         for (U32 i = 0; i < this->size(); ++i)
            if ((*this)[i])
               (*this)[i]->getLeaves(out);
   }
   inline void collectSubtree(Vector<TreeNode<T, nullClears>*>& nodes) {
      nodes.push_back_unique(this);
      for (U32 i = 0; i < this->size(); ++i)
         if ((*this)[i])
            (*this)[i]->collectSubtree(nodes);
   }
   inline void collectSubtreeData(Vector<T>& dataList) {
      dataList.push_back_unique(data);
      for (U32 i = 0; i < this->size(); ++i)
         if ((*this)[i])
            (*this)[i]->collectSubtreeData(dataList);
   }
   // callback signature: void(TreeNode<T, nullClears>*)
   template<typename Func>
   inline void forEachChild(Func callback) {
      for (U32 i = 0; i < this->size(); i++)
         if ((*this)[i])
            callback((*this)[i]);
   }
   // callback signature: void(const TreeNode<T, nullClears>*)
   template<typename Func>
   inline void forEachChild(Func callback) const {
      for (U32 i = 0; i < this->size(); i++)
         if ((*this)[i])
            callback((*this)[i]);
   }
   // callback signature: void(TreeNode<T, nullClears>*)
   template<typename Func>
   inline void forEachInSubtree(Func callback) {
      callback(this);
      for (U32 i = 0; i < this->size(); i++)
         if ((*this)[i])
            (*this)[i]->forEachInSubtree(callback);
   }
   // callback signature: void(const TreeNode<T, nullClears>*)
   template<typename Func>
   inline void forEachLeaf(Func callback) {
      if (isLeaf())
         callback(this);
      else
         for (U32 i = 0; i < this->size(); i++)
            if ((*this)[i])
               (*this)[i]->forEachLeaf(callback);
   }
   // callback signature: void(TreeNode<T, nullClears>*)
   template<typename Func>
   inline void traverseBreadthFirst(Func callback) {
      Vector<TreeNode<T, nullClears>*> queue;
      queue.push_back(this);
      while (!queue.empty()) {
         TreeNode<T, nullClears>* node = queue.first();
         queue.erase(0);
         callback(node);
         for (U32 i = 0; i < node->size(); ++i)
            if ((*node)[i])
               queue.push_back((*node)[i]);
      }
   }
   // Calls the provided functor on each ancestor up to the root (excluding this node).
   // Typically used for propagating updates up the tree (e.g., refitting bounds).
   // callback signature: void(TreeNode<T, nullClears>*)
   template<typename Func>
   inline void refitPathToRoot(Func refitFunc) {
      TreeNode<T, nullClears>* node = parent;
      while (node) {
         refitFunc(node);
         node = node->parent;
      }
   }
   // callback signature: TreeNode<T, nullClears>* pred(TreeNode<T, nullClears>*)
   template<typename Func>
   inline TreeNode<T, nullClears>* findIf(Func pred) {
      if (pred(this)) return this;
      for (U32 i = 0; i < this->size(); ++i)
         if ((*this)[i]) {
            auto* found = (*this)[i]->findIf(pred);
            if (found) return found;
         }
      return NULL;
   }
   // callback signature: const TreeNode<T, nullClears>* pred(const TreeNode<T, nullClears>*)
   template<typename Func>
   inline void findAllIf(Func pred, Vector<TreeNode<T, nullClears>*>& out) {
      if (pred(this))
         out.push_back(this);
      for (U32 i = 0; i < this->size(); ++i)
         if ((*this)[i])
            (*this)[i]->findAllIf(pred, out);
   }
   // callback signature: const TreeNode<T, nullClears>* pred(const TreeNode<T, nullClears>*)
   template<typename Func>
   inline U32 countIf(Func pred) const {
      U32 count = pred(this) ? 1 : 0;
      for (U32 i = 0; i < this->size(); ++i)
         if ((*this)[i])
            count += (*this)[i]->countIf(pred);
      return count;
   }
   // callback signature: bool pred(TreeNode<T, nullClears>*)
   template<typename Func>
   inline void removeIf(Func pred) {
      for (S32 i = this->size() - 1; i >= 0; --i) {
         if ((*this)[i] && pred((*this)[i])) {
            delete (*this)[i];
            if constexpr (nullClears)
               this->erase(i);
            else
               (*this)[i] = NULL;
         }
         else if ((*this)[i]) {
            (*this)[i]->removeIf(pred);
         }
      }
   }
   //-------------------------------------------------------------------------
   // Tree Metrics
   //-------------------------------------------------------------------------
   inline U32 getTreeSize() const {
      U32 count = 1;
      for (U32 i = 0; i < this->size(); i++)
         if ((*this)[i])
            count += (*this)[i]->getTreeSize();
      return count;
   }
   inline U32 getMaxDepth() const {
      if (isLeaf()) return 0;
      U32 maxDepth = 0;
      for (U32 i = 0; i < this->size(); i++)
         if ((*this)[i]) {
            U32 childDepth = (*this)[i]->getMaxDepth();
            if (childDepth > maxDepth)
               maxDepth = childDepth;
         }
      return maxDepth + 1;
   }

   //-------------------------------------------------------------------------
   // Rotation/Balance Utilities
   //-------------------------------------------------------------------------
   static inline U32 gatherRotationCandidates(TreeNode<T, nullClears>* parent, Vector<TreeNode<T, nullClears>*>& outNodes, U32 maxCandidates = 8) {
      outNodes.clear();
      for (U32 i = 0; i < parent->size() && outNodes.size() < maxCandidates; ++i) {
         TreeNode<T, nullClears>* child = (*parent)[i];
         if (!child) continue;
         if (child->isLeaf()) {
            outNodes.push_back_unique(child);
         }
         else {
            for (U32 j = 0; j < child->size() && outNodes.size() < maxCandidates; ++j) {
               TreeNode<T, nullClears>* grandChild = (*child)[j];
               if (grandChild) outNodes.push_back_unique(grandChild);
            }
         }
      }
      return outNodes.size();
   }
   static inline bool findBestRotationPairing(
      const Vector<TreeNode<T, nullClears>*>& nodes,
      U32 groupSize,
      F32(*costFunc)(const TreeNode<T, nullClears>*, const TreeNode<T, nullClears>*),
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
      while (true) {
         for (U32 i = 0; i < groupSize; ++i)
            groupA[i] = indices[i];
         U32 bIdx = 0;
         for (U32 i = groupSize; i < n; ++i)
            groupB[bIdx++] = indices[i];
         if (bIdx == groupSize) {
            F32 costA = costFunc(nodes[groupA[0]], nodes[groupA[1]]);
            F32 costB = costFunc(nodes[groupB[0]], nodes[groupB[1]]);
            F32 totalCost = costA + costB;
            if (totalCost < outBestCost) {
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
         for (U32 i = k + 1, j = n - 1; i < j; ++i, --j) {
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
   inline Vector<Derived*> getChildrenAs() {
      Vector<Derived*> out;
      for (U32 i = 0; i < this->size(); ++i)
         if ((*this)[i])
            out.push_back(static_cast<Derived*>((*this)[i]));
      return out;
   }
   template<typename Derived>
   inline Vector<const Derived*> getChildrenAs() const {
      Vector<const Derived*> out;
      for (U32 i = 0; i < this->size(); ++i)
         if ((*this)[i])
            out.push_back(static_cast<const Derived*>((*this)[i]));
      return out;
   }
   template<typename Derived, typename Func>
   inline void forEachLeafAs(Func callback) {
      if (isLeaf())
         callback(static_cast<Derived*>(this));
      else
         for (U32 i = 0; i < this->size(); i++)
            if ((*this)[i])
               (*this)[i]->template forEachLeafAs<Derived>(callback);
   }
   template<typename Derived, typename Func>
   inline void forEachLeafAs(Func callback) const {
      if (isLeaf())
         callback(static_cast<const Derived*>(this));
      else
         for (U32 i = 0; i < this->size(); i++)
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
