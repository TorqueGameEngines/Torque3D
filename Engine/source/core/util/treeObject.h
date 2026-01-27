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

template <class T>
class TreeNode : public Vector<TreeNode<T>*> {
public:
   T data;
   TreeNode<T>* parent;
   TreeNode(const T& val = T(), TreeNode<T>* p = NULL) : data(val), parent(p) {}
   virtual ~TreeNode()
   {
      deleteChildren();
      if (parent)
      {
         for (U32 i = 0; i < parent->size(); i++)
         {
            if ((*parent)[i] == this)
            {
               parent->erase(i);
               break;
            }
         }
         parent = NULL;
      }
   }

   //description logic
   inline bool isRoot() const { return parent == NULL; }
   inline bool isLeaf() const { return size() == 0; }
   // Parent logic
   inline TreeNode<T>* getParent() const { return parent; }

   inline void setParent(TreeNode<T>* p)
   {
      if (parent == p) return;

      if (parent) parent->removeChild(this);
      parent = p;
      if (parent) parent->push_back(this);
   }

   //children logic
   inline TreeNode<T>* addChild(const T& val)
   {
      TreeNode<T>* child = new TreeNode<T>(val, this);
      push_back(child);
      return child;
   }
   inline void addChild(TreeNode<T>* child)
   {
      if (!child) return;

      // Check if already a child to prevent duplicates
      for (U32 i = 0; i < size(); i++)
      {
         if ((*this)[i] == child)
            return;  // Already a child
      }

      // Remove from old parent if needed
      if (child->parent && child->parent != this)
         child->parent->removeChild(child);

      child->parent = this;
      push_back(child);
   }
   inline void setChild(U32 i, TreeNode<T>* child)
   {
      if (i >= size())
      {
         U32 oldSize = size();
         increment((i + 1) - oldSize);
         for (U32 j = oldSize; j < size(); j++)
            (*this)[j] = NULL;
      }

      TreeNode<T>* oldChild = (*this)[i];
      if (oldChild == child) return;

      // Unlink old child
      if (oldChild)
      {
         oldChild->parent = NULL;
      }

      if (child == NULL)
      {
         (*this)[i] = NULL;
      }
      else
      {
         // Handle moving from different parent vs same parent
         if (child->parent && child->parent != this)
         {
            child->parent->removeChild(child);
         }
         else if (child->parent == this)
         {
            // Moving within same parent - find and remove from old slot
            for (U32 j = 0; j < size(); j++)
            {
               if (j != i && (*this)[j] == child)
               {
                  erase(j);
                  if (j < i)
                     i--;
                  break;
               }
            }
         }

         (*this)[i] = child;
         child->parent = this;
      }
   }

   inline TreeNode<T>* getChild(U32 i) const
   {
      if (i < size())
         return (*this)[i];
      return NULL;
   }

   inline void addChildren(const Vector<T>* children)
   {
      if (!children) return;
      for (U32 i = 0; i < children->size(); i++)
      {
         TreeNode<T>* child = new TreeNode<T>((*children)[i], this);
         push_back(child);
      }
   }

   inline void removeChild(TreeNode<T>* child)
   {
      if (!child) return;

      for (U32 i = 0; i < size(); i++)
      {
         if ((*this)[i] == child)
         {
            child->parent = NULL;
            erase(i);
            return;
         }
      }
   }

   inline void removeChild(U32 i)
   {
      if (i < size())
      {
         TreeNode<T>* child = (*this)[i];
         if (child)
            child->parent = NULL;
         erase(i);
      }
   }
   inline void replaceChild(TreeNode<T>* oldChild, TreeNode<T>* newChild)
   {
      if (!oldChild) return;

      for (U32 i = 0; i < size(); i++)
      {
         if ((*this)[i] == oldChild)
         {
            oldChild->parent = NULL;

            if (newChild)
            {
               // Handle moving from different parent vs same parent
               if (newChild->parent && newChild->parent != this)
               {
                  newChild->parent->removeChild(newChild);
               }
               else if (newChild->parent == this)
               {
                  // Moving within same parent - find and remove from old slot
                  for (U32 j = 0; j < size(); j++)
                  {
                     if (j != i && (*this)[j] == newChild)
                     {
                        erase(j);
                        if (j < i)
                           i--;
                        break;
                     }
                  }
               }

               (*this)[i] = newChild;
               newChild->parent = this;
            }
            else
            {
               (*this)[i] = NULL;
            }
            return;
         }
      }
   }

   inline void compact()
   {
      // Remove NULL entries from children array
      for (U32 i = 0; i < size(); )
      {
         if ((*this)[i] == NULL)
            erase(i);
         else
            i++;
      }
   }

   void operator =(Vector<T>* other) { clear(); addChildren(other); }

   inline U32 getNumChildren() const { return size(); }
   inline bool hasChildren() const { return size() > 0; }
   inline Vector<TreeNode<T>*> getChildren() const
   {
      Vector<TreeNode<T>*> children;
      children.reserve(size());
      for (U32 i = 0; i < size(); i++)
      {
         if ((*this)[i])  // Skip NULLs
            children.push_back((*this)[i]);
      }
      return children;
   }

   inline void deleteChildren()
   {
      Vector<TreeNode<T>*> children;
      for (U32 i = 0; i < size(); i++)
      {
         children.push_back((*this)[i]);
      }
      clear();

      for (U32 i = 0; i < children.size(); i++)
      {
         if (children[i])
         {
            children[i]->parent = NULL;
            delete children[i];
         }
      }
   }

   //sibling logic
   inline Vector<TreeNode<T>*> getSiblings() const
   {
      Vector<TreeNode<T>*> siblings;
      if (!parent) return siblings;

      siblings.reserve(parent->size() - 1);
      for (U32 i = 0; i < parent->size(); i++)
      {
         TreeNode<T>* sibling = (*parent)[i];
         if (sibling && sibling != this)  // Skip NULLs
            siblings.push_back(sibling);
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
      TreeNode<T>* current = parent;
      while (current)
      {
         depth++;
         current = current->parent;
      }
      return depth;
   }

   inline TreeNode<T>* getRoot()
   {
      TreeNode<T>* current = this;
      while (current->parent)
         current = current->parent;
      return current;
   }

   inline const TreeNode<T>* getRoot() const
   {
      const TreeNode<T>* current = this;
      while (current->parent)
         current = current->parent;
      return current;
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
