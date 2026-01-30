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
   T data;
   TreeNode<T, nullClears>* parent;
   TreeNode(const T& val = T(), TreeNode<T, nullClears>* p = NULL) : data(val), parent(p) {}
   TreeNode(const Vector<TreeNode<T, nullClears>*>& children, TreeNode<T, nullClears>* p = NULL)
      : data(T()), parent(p)
   {
      this->increment(children.size());
      for (U32 i = 0; i < children.size(); ++i) {
         (*this)[i] = children[i];
         if (children[i])
            children[i]->parent = this;
      }
   }
   virtual ~TreeNode()
   {
      deleteChildren();
      parent = NULL;
   }

   //description logic
   inline bool isRoot() const { return parent == NULL; }
   inline bool isLeaf(bool checkNULLs = true) const {
      if (!checkNULLs)
         return this->size() == 0;
      for (U32 i = 0; i < this->size(); ++i) {
         if ((*this)[i] != NULL)
            return false;
      }
      return true;
   }
   // Parent logic
   inline TreeNode<T, nullClears>* getParent() const { return parent; }

   inline void setParent(TreeNode<T, nullClears>* p)
   {
      if (parent == p) return;

      if (parent) parent->removeChild(this);
      parent = p;
      if (parent) parent->push_back_unique(this);
   }

   //children logic
   inline TreeNode<T, nullClears>* addChild(const T& val)
   {
      TreeNode<T, nullClears>* child = new TreeNode<T, nullClears>(val, this);
      this->push_back_unique(child);
      return child;
   }

   inline void addChild(TreeNode<T, nullClears>* child)
   {
      // Prevent duplicate child
      for (U32 i = 0; i < this->size(); i++)
         AssertFatal((*this)[i] != child, "TreeNode::addChild - Attempted to add duplicate child");

#ifdef TORQUE_DEBUG
      // Prevent cycles
      TreeNode<T, nullClears>* ancestor = this;
      while (ancestor) {
         AssertFatal(ancestor != child, "TreeNode::addChild - Would create circular parent relationship");
         ancestor = ancestor->parent;
      }
#endif

      // If child has a parent and it's not this, remove from old parent
      if (child->parent && child->parent != this) {
         child->parent->removeChild(child); // Remove from old parent
      }

      child->parent = this;
      this->push_back_unique(child);
   }

   inline void setChild(U32 i, TreeNode<T, nullClears>* child)
   {
      if (i >= this->size())
      {
         U32 oldSize = this->size();
         this->increment((i + 1) - oldSize);
         for (U32 j = oldSize; j < this->size(); j++)
            (*this)[j] = NULL;
      }

      TreeNode<T, nullClears>* oldChild = (*this)[i];
      if (oldChild == child) return;

      // Unlink old child
      if (oldChild)
         oldChild->parent = NULL;

      // If forcing to NULL, just clear the slot and return
      if (child == NULL)
      {
         if constexpr (nullClears)
            this->erase(i);
         else
            (*this)[i] = NULL;
         return;
      }

#ifdef TORQUE_DEBUG
      // Prevent cycles
      TreeNode<T, nullClears>* ancestor = this;
      while (ancestor) {
         AssertFatal(ancestor != child, "TreeNode::setChild - Would create circular parent relationship");
         ancestor = ancestor->parent;
      }
#endif

      // Remove from old parent if different
      if (child->parent && child->parent != this)
      {
         child->parent->removeChild(child);
      }
      else if (child->parent == this)
      {
         // Moving within same parent, nullify other references
         for (U32 j = 0; j < this->size(); j++)
         {
            if (j != i && (*this)[j] == child)
               if constexpr (nullClears)
                  this->erase(j);
               else
                  (*this)[j] = NULL;
         }
      }

      // Prevent duplicate child
      for (U32 j = 0; j < this->size(); j++)
         AssertFatal(j == i || (*this)[j] != child, "TreeNode::setChild - Attempted to set duplicate child");

      (*this)[i] = child;
      child->parent = this;
   }

   inline TreeNode<T, nullClears>* getChild(U32 i) const
   {
      if (i < this->size())
      {
         // Defensive: validate pointer before returning
         if ((*this)[i] && (*this)[i]->parent != this)
         {
            AssertFatal(false, "TreeNode::getChild - Child parent pointer mismatch");
         }
         return (*this)[i];
      }
      return NULL;
   }


   inline void addChildren(const Vector<TreeNode<T, nullClears>*>* children)
   {
      if (!children) return;
      for (U32 i = 0; i < children->size(); i++)
      {
         TreeNode<T, nullClears>* child = (*children)[i];

         // Prevent duplicate child
         for (U32 j = 0; j < this->size(); j++)
            AssertFatal((*this)[j] != child, "TreeNode::addChildren - Attempted to add duplicate child");

#ifdef TORQUE_DEBUG
         // Prevent cycles
         TreeNode<T, nullClears>* ancestor = this;
         while (ancestor) {
            AssertFatal(ancestor != child, "TreeNode::addChildren - Would create circular parent relationship");
            ancestor = ancestor->parent;
         }
#endif

         // If child has a parent and it's not this, remove from old parent
         if (child->parent && child->parent != this) {
            child->parent->removeChild(child);
         }

         child->parent = this;
         this->push_back_unique(child);
      }
   }

   inline void nullParent(bool orphan = true)
   {
      // Null the parent pointer with optional cleanup
      // @param orphan If true (default), properly removes from parent's children array first.
      //               If false, only nulls parent pointer (use during manual tree destruction).
      if (orphan && parent)
      {
         parent->removeChild(this);
      }
      else
      {
         parent = NULL;
      }
   }

   inline bool isValidTree() const
   {
      // Validate tree structure - check parent-child relationships
      for (U32 i = 0; i < this->size(); i++)
      {
         TreeNode<T, nullClears>* child = (*this)[i];
         if (child && child->parent != this)
            return false;  // Child doesn't point back to parent
      }
      return true;
   }

   inline bool hasChild(TreeNode<T, nullClears>* child) const
   {
      if (!child) return false;
      for (U32 i = 0; i < this->size(); i++)
      {
         if ((*this)[i] == child)
            return true;
      }
      return false;
   }

   inline S32 getChildIndex(TreeNode<T, nullClears>* child) const
   {
      if (!child) return -1;
      for (U32 i = 0; i < this->size(); i++)
      {
         if ((*this)[i] == child)
            return (S32)i;
      }
      return -1;
   }

   inline void clearChildren()
   {
      // Remove all children without deleting them
      for (U32 i = 0; i < this->size(); i++)
      {
         TreeNode<T, nullClears>* child = (*this)[i];
         if (child)
         {
            // Harden: ensure child is actually parented to this node
            if (child->parent != this)
            {
#ifdef TORQUE_DEBUG
               Con::warnf("TreeNode::clearChildren - Child at index %u has incorrect parent pointer (corruption detected)", i);
#endif
               // Detach anyway to avoid dangling pointer
               child->parent = NULL;
            }
            else
            {
               child->parent = NULL;
            }
         }
      }
      clear();
   }

   inline void swapChildren(U32 i, U32 j)
   {
      if (i >= this->size() || j >= this->size() || i == j)
         return;

      TreeNode<T, nullClears>* childI = (*this)[i];
      TreeNode<T, nullClears>* childJ = (*this)[j];

      // Update parent pointers if needed
      if (childI && childI->parent != this)
         childI->parent = this;
      if (childJ && childJ->parent != this)
         childJ->parent = this;

      // Swap the pointers
      (*this)[i] = childJ;
      (*this)[j] = childI;
   }

   inline TreeNode<T, nullClears>* findChild(const T& val)
   {
      for (U32 i = 0; i < this->size(); i++)
      {
         if ((*this)[i] && (*this)[i]->data == val)
            return (*this)[i];
      }
      return NULL;
   }

   inline const TreeNode<T, nullClears>* findChild(const T& val) const
   {
      for (U32 i = 0; i < this->size(); i++)
      {
         if ((*this)[i] && (*this)[i]->data == val)
            return (*this)[i];
      }
      return NULL;
   }

   template<typename Func>
   inline void forEachChild(Func callback)
   {
      for (U32 i = 0; i < this->size(); i++)
      {
         if ((*this)[i])
            callback((*this)[i]);
      }
   }

   template<typename Func>
   inline void forEachInSubtree(Func callback)
   {
      // Pre-order traversal: process node, then children
      callback(this);
      for (U32 i = 0; i < this->size(); i++)
      {
         if ((*this)[i])
            (*this)[i]->forEachInSubtree(callback);
      }
   }
   template<typename Func>
   inline void forEachLeaf(Func callback, bool checkNULLs = true)
   {
      if (isLeaf(checkNULLs))
      {
         callback(this);
      }
      else
      {
         for (U32 i = 0; i < this->size(); i++)
         {
            if ((*this)[i])
               (*this)[i]->forEachLeaf(callback, checkNULLs);
         }
      }
   }

   inline void findLeaves(Vector<TreeNode<T, nullClears>*>& outLeaves, bool checkNULLs = true)
   {
      forEachLeaf([&outLeaves](TreeNode<T, nullClears>* leaf) {
         outLeaves.push_back_unique(leaf);
         }, checkNULLs);
   }
   inline U32 getTreeSize() const
   {
      U32 count = 1;  // Count this node
      for (U32 i = 0; i < this->size(); i++)
      {
         if ((*this)[i])
            count += (*this)[i]->getTreeSize();
      }
      return count;
   }

   inline U32 getMaxDepth() const
   {
      if (isLeaf()) return 0;
      
      U32 maxDepth = 0;
      for (U32 i = 0; i < this->size(); i++)
      {
         if ((*this)[i])
         {
            U32 childDepth = (*this)[i]->getMaxDepth();
            if (childDepth > maxDepth)
               maxDepth = childDepth;
         }
      }
      return maxDepth + 1;
   }

   inline void removeChild(TreeNode<T, nullClears>* child)
   {
      AssertFatal(child != NULL, "TreeNode::removeChild - Attempted to remove NULL child");
      bool found = false;
      for (U32 i = 0; i < this->size(); i++)
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
         // Defensive: attempt to repair if possible
         for (U32 i = 0; i < this->size(); i++)
         {
            if ((*this)[i] && (*this)[i]->parent == this)
            {
               // Child pointer mismatch, but parent pointer matches: repair
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
      AssertFatal(i < this->size(), "TreeNode::removeChild - Index out of bounds");
      TreeNode<T, nullClears>* child = (*this)[i];
      if (child)
         child->parent = NULL;
      if constexpr (nullClears)
         this->erase(i);
      else
         (*this)[i] = NULL;
   }

   inline void replaceChild(TreeNode<T, nullClears>* oldChild, TreeNode<T, nullClears>* newChild)
   {
      AssertFatal(oldChild != NULL, "TreeNode::replaceChild - Attempted to replace NULL child");

      S32 idx = getChildIndex(oldChild);
      AssertFatal(idx != -1, "TreeNode::replaceChild - oldChild not found in children");

      // Use hardened setChild for all safety checks and pointer management
      setChild((U32)idx, newChild);
   }

   inline void compact()
   {
      for (U32 i = 0; i < this->size(); )
      {
         TreeNode<T, nullClears>* child = (*this)[i];
         if constexpr (nullClears)
         {
            // Compact style: erase NULL slots, keep only valid children.
            if (child == NULL)
            {
               this->erase(i);
               continue;
            }
            // Repair parent pointer if needed.
            if (child->parent != this)
               child->parent = this;
            i++;
         }
         else
         {
            // BVH/slot-stable style: leave NULLs, just repair parent pointers.
            if (child && child->parent != this)
               child->parent = this;
            i++;
         }
      }
   }

   inline bool hasChildren() const
   {
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

   inline Vector<TreeNode<T, nullClears>*> getChildren() const
   {
      Vector<TreeNode<T, nullClears>*> children;
      if constexpr (nullClears) {
         // All slots are valid children
         children = *this;
      }
      else {
         // Only non-NULL slots are valid children
         children.reserve(this->size());
         for (U32 i = 0; i < this->size(); ++i)
            if ((*this)[i])
               children.push_back_unique((*this)[i]);
      }
      return children;
   }

   inline void deleteChildren()
   {
      Vector<TreeNode<T, nullClears>*> children;
      for (U32 i = 0; i < this->size(); i++)
      {
         TreeNode<T, nullClears>* child = (*this)[i];
         if (child)
         {
            // Harden: ensure child is actually parented to this node
            if (child->parent != this)
            {
#ifdef TORQUE_DEBUG
               Con::warnf("TreeNode::deleteChildren - Child at index %u has incorrect parent pointer (corruption detected)", i);
#endif
               // Detach anyway to avoid dangling pointer
               child->parent = NULL;
            }
            else
            {
               child->parent = NULL;
            }
         }
         children.push_back_unique(child);
      }
      clear();

      for (U32 i = 0; i < children.size(); i++)
      {
         if (children[i])
         {
            // Child should already be detached
            delete children[i];
         }
      }
   }

   inline void collectSubtree(Vector<TreeNode<T, nullClears>*>& nodes)
   {
      // Pre-order collection of all nodes in subtree
      forEachInSubtree([&nodes](TreeNode<T, nullClears>* n) {
         nodes.push_back_unique(n);
      });
   }

   inline void collectSubtreeData(Vector<T>& dataList)
   {
      // Collect just the data from subtree
      forEachInSubtree([&dataList](TreeNode<T, nullClears>* n) {
         dataList.push_back_unique(n->data);
      });
   }

   void collectAncestors(Vector<TreeNode<T, nullClears>*>& outAncestors) const
   {
      TreeNode<T, nullClears>* node = parent;
      while (node)
      {
         outAncestors.push_back_unique(node);
         node = node->parent;
      }
   }

   //sibling logic
   inline Vector<TreeNode<T, nullClears>*> getSiblings() const
   {
      Vector<TreeNode<T, nullClears>*> siblings;
      if (!parent) return siblings;

      siblings.reserve(parent->size() - 1);
      for (U32 i = 0; i < parent->size(); i++)
      {
         TreeNode<T, nullClears>* sibling = (*parent)[i];
         if (sibling && sibling != this)  // Skip NULLs
            siblings.push_back_unique(sibling);
      }
      return siblings;
   }

   //data logic
   inline T getData() const { return data; }
   inline void setData(const T& val) { data = val; }
   inline void operator =(const T& val) { data = val; }
   inline T* getDataPtr() { return &data; }

   // Traversal helpers
   inline U32 getDepth() const
   {
      U32 depth = 0;
      TreeNode<T, nullClears>* current = parent;
      while (current)
      {
         depth++;
         current = current->parent;
      }
      return depth;
   }

   inline TreeNode<T, nullClears>* getRoot()
   {
      TreeNode<T, nullClears>* current = this;
      while (current->parent)
         current = current->parent;
      return current;
   }

   inline const TreeNode<T, nullClears>* getRoot() const
   {
      const TreeNode<T, nullClears>* current = this;
      while (current->parent)
         current = current->parent;
      return current;
   }

   /// Returns true if this node is present in the given vector (used for cycle detection).
   bool isVisited(const Vector<TreeNode<T, nullClears>*>& visited) const
   {
      for (U32 i = 0; i < visited.size(); ++i)
      {
         if (visited[i] == this)
            return true;
      }
      return false;
   }

   // Gather up to maxCandidates leaves or grandchildren for rotation from a node.
   static U32 gatherRotationCandidates(TreeNode<T, nullClears>* parent, Vector<TreeNode<T, nullClears>*>& outNodes, U32 maxCandidates = 8)
   {
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

   // Finds the best way to pair/group N nodes into two groups of groupSize each, minimizing cost.
   // CostFunc: F32 (*costFunc)(const TreeNode<T, nullClears>*, const TreeNode<T, nullClears>*)
   static bool findBestRotationPairing(
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

   //converters

   template<typename Derived>
   Derived* getChildAs(U32 i) { return static_cast<Derived*>(getChild(i)); }
   template<typename Derived>
   const Derived* getChildAs(U32 i) const { return static_cast<const Derived*>(getChild(i)); }

   template<typename Derived>
   Vector<Derived*> getChildrenAs() const
   {
      Vector<Derived*> out;
      for (U32 i = 0; i < this->size(); ++i)
         if ((*this)[i])
            out.push_back(static_cast<Derived*>((*this)[i]));
      return out;
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
