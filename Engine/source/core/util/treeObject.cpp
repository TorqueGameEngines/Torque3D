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
#include "treeObject.h"
#include "console/engineAPI.h"

IMPLEMENT_CONOBJECT(TreeObject);

TreeObject::~TreeObject()
{
   if (mRoot != NULL)
      _deleteNode(mRoot, false);

   mKeyMap.clear();
}

void TreeObject::initPersistFields()
{
   addProtectedField("treeType", TypeString, Offset(mTreeType, TreeObject), &_setType, &defaultProtectedGetFn, "Set type by name.");
   Parent::initPersistFields();
}

void TreeObject::_internalSetType(const char* typeName)
{
   if (!typeName || !typeName[0]) return;

   ConsoleBaseType* newType = ConsoleBaseType::getTypeByName(typeName);

   if (newType)
      mTreeType = newType;
   else
      Con::errorf("TreeObject: Invalid type '%s'. Use 'TypeS32', 'TypePoint3F', etc.", typeName);
}

bool TreeObject::_setType(void* obj, const char* index, const char* data)
{
   TreeObject* tree = static_cast<TreeObject*>(obj);
   if (tree != NULL)
      tree->_internalSetType(data);

   return false;
}

void TreeObject::setType(const char* typeName)
{
   if (typeName && typeName[0])
   {
      ConsoleBaseType* newType = ConsoleBaseType::getTypeByName(typeName);
      if (newType)
         mTreeType = newType;
      else
         Con::errorf("TreeObject::setTreeType - Unknown console type '%s'! use listConsoleTypes for options", typeName);
   }
}

S32 TreeObject::addNode(S32 parentKey, const char* scriptData, S32 forcedKey)
{
   if (mTreeType == NULL)
   {
      Con::errorf("TreeObject::addNode - treeType not set. Cannot allocate node data.");
      return -1;
   }

   S32 finalKey = (forcedKey == -1) ? mNextFreeKey++ : forcedKey;

   if (forcedKey != -1)
   {
      if (findNode(finalKey))
      {
         Con::errorf("TreeObject::addNode - Key collision! Key %d already exists.", finalKey);
         return -1;
      }
      if (finalKey >= mNextFreeKey)
         mNextFreeKey = finalKey + 1;
   }

   void* newData = dMalloc(mTreeType->getTypeSize());
   dMemset(newData, 0, mTreeType->getTypeSize());

   if (scriptData && scriptData[0])
   {
      const char* scriptArgv[] = { scriptData };
      mTreeType->setData(newData, 1, scriptArgv, NULL, 0);
   }

   Node* newNode = new Node(finalKey, mTreeType);
   newNode->data = newData;

   Node* parent = findNode(parentKey);
   if (parent)
   {
      parent->push_back(newNode);
      newNode->parent = parent;
   }
   else
   {
      if (mRoot == NULL)
      {
         mRoot = newNode;
         newNode->parent = NULL;
      }
      else
      {
         mRoot->push_back(newNode);
         newNode->parent = mRoot;
      }
   }

   mKeyMap.insert(finalKey, newNode);

   return finalKey;
}

void TreeObject::deleteNode(S32 key)
{
   Node* node = findNode(key);
   if (node == NULL)
      return;

   if (node->parent != NULL)
   {
      Node* parentNode = static_cast<Node*>(node->parent);
      for (S32 i = 0; i < parentNode->size(); i++)
      {
         if ((*parentNode)[i] == static_cast<TreeNode<void*>*>(node))
         {
            parentNode->erase(i);
            break;
         }
      }
   }
   if (node == mRoot)
      mRoot = NULL;
   _deleteNode(node, true);
}

void TreeObject::_deleteNode(Node* node, bool unlinkFromMap)
{
   if (!node) return;

   for (U32 i = 0; i < node->size(); i++)
   {
      Node* child = static_cast<Node*>((*node)[i]);
      _deleteNode(child, unlinkFromMap);
   }

   if (unlinkFromMap) {
      mKeyMap.erase(node->key);
   }

   if (node == mRoot) mRoot = NULL;
   delete node;
}

TreeObject::Node* TreeObject::findNode(S32 key)
{
   Map<S32, Node*>::Iterator iter = mKeyMap.find(key);
   return (iter != mKeyMap.end()) ? iter->value : NULL;
}

S32 TreeObject::getParent(S32 key)
{
   Node* n = findNode(key);
   if (n == NULL || n->parent == NULL)
      return -1;
   return static_cast<Node*>(n->getParent())->key;
}

bool TreeObject::toParent(S32 key, S32 newParentKey)
{
   Node* targetNode = findNode(key);
   Node* newParentNode = findNode(newParentKey);

   if (!targetNode || !newParentNode || key == newParentKey)
      return false;

   Node* checkNode = newParentNode;
   while (checkNode != NULL)
   {
      if (checkNode->key == key)
         return false;
      checkNode = static_cast<Node*>(checkNode->parent);
   }
   if (targetNode->parent)
   {
      TreeNode<void*>* oldParent = targetNode->parent;
      for (S32 i = 0; i < oldParent->size(); i++) {
         if ((*oldParent)[i] == targetNode) {
            oldParent->erase(i);
            break;
         }
      }
   }

   targetNode->parent = newParentNode;
   newParentNode->push_back(targetNode);

   return true;
}

Vector<S32> TreeObject::getChildren(S32 key)
{
   Vector<S32> keys;
   Node* n = findNode(key);
   if (n)
   {
      Vector<TreeNode<void*>*> children = n->getChildren();
      keys.reserve(children.size());
      for (U32 i = 0; i < children.size(); i++)
         keys.push_back(static_cast<Node*>(children[i])->key);
   }
   return keys;
}

Vector<S32> TreeObject::getSiblings(S32 key)
{
   Vector<S32> keys;
   Node* n = findNode(key);
   if (n)
   {
      Vector<TreeNode<void*>*> siblings = n->getSiblings();
      keys.reserve(siblings.size());
      for (U32 i = 0; i < siblings.size(); i++)
         keys.push_back(static_cast<Node*>(siblings[i])->key);
   }
   return keys;
}

const char* TreeObject::nodesToString(const Vector<S32>& keys)
{
   if (keys.empty())
      return "";

   static const U32 bufSize = 1024;
   char* returnBuffer = Con::getReturnBuffer(bufSize);
   returnBuffer[0] = '\0';

   bool first = true;
   for (S32 i = 0; i < keys.size(); i++)
   {
      char keyBuf[16];
      dSprintf(keyBuf, sizeof(keyBuf), "%d", keys[i]);

      if (!first)
         dStrcat(returnBuffer, " ", bufSize);

      dStrcat(returnBuffer, keyBuf, bufSize);
      first = false;
   }

   return returnBuffer;
}

const char* TreeObject::toString()
{
   if (!mRoot || !mTreeType) return "";

   const U32 bufSize = 16384;
   char* heapBuffer = (char*)dMalloc(bufSize);
   dMemset(heapBuffer, 0, bufSize);

   dSprintf(heapBuffer, bufSize, "%s\n", mTreeType->getTypeName());
   U32 bufferPos = dStrlen(heapBuffer);

   _toStringRecursive(mRoot, heapBuffer, bufferPos, bufSize);
   heapBuffer[bufferPos] = '\0';

   char* returnBuffer = Con::getReturnBuffer(bufSize);
   dStrcpy(returnBuffer, heapBuffer, bufSize);
   dFree(heapBuffer);

   return returnBuffer;
}

void TreeObject::_toStringRecursive(Node* node, char* buffer, U32& bufferPos, U32 bufSize)
{
   if (!node || bufferPos >= (bufSize - 1)) return;

   char localDataStr[512] = "";
   if (node->data && node->type) {
      const char* tempStr = node->type->getData(node->data, NULL, 0);
      if (tempStr) {
         dStrncpy(localDataStr, tempStr, sizeof(localDataStr) - 1);
         localDataStr[sizeof(localDataStr) - 1] = '\0';
      }
   }

   S32 pKey = (node->parent) ? static_cast<Node*>(node->parent)->key : -1;

   char line[1024];
   dSprintf(line, sizeof(line), "%d %d \"%s\"\n", node->key, pKey, localDataStr);
   U32 lineLen = dStrlen(line);

   if (bufferPos + lineLen < bufSize) {
      dStrcpy(buffer + bufferPos, line, bufSize - bufferPos);
      bufferPos += lineLen;
   }

   for (U32 i = 0; i < node->size(); i++) {
      Node* child = static_cast<Node*>((*node)[i]);
      _toStringRecursive(child, buffer, bufferPos, bufSize);
   }
}

void TreeObject::fromString(const char* data)
{
   if (!data || !*data)
      return;

   if (mRoot)
      _deleteNode(mRoot, true);

   mKeyMap.clear();
   mNextFreeKey = 0;

   const char* pipe = dStrchr(data, '\n');
   if (pipe)
   {
      char typeName[256];
      U32 typeLen = pipe - data;
      if (typeLen > 1)
      {
         dStrncpy(typeName, data, typeLen);
         typeName[typeLen] = '\0';
         setType(typeName);
      }
      _fromStringRecursive(pipe + 1, -1);
   }
}

void TreeObject::_fromStringRecursive(const char* str, S32 ignored)
{
   if (!str || !*str) return;
   const char* p = str;

   while (*p) {
      while (*p && (*p == '\n' || *p == '\r' || *p == ' ')) p++;
      if (!*p) break;

      S32 key = 0;
      S32 parentID = -1;
      char dataBuf[1024] = "";

      if (dSscanf(p, "%d %d \"%[^\"]\"", &key, &parentID, dataBuf) < 3) {
         const char* nextLine = dStrchr(p, '\n');
         if (!nextLine) break;
         p = nextLine + 1;
         continue;
      }

      addNode(parentID, dataBuf, key);
      const char* nextLine = dStrchr(p, '\n');
      if (!nextLine) break;
      p = nextLine + 1;
   }
}

//==============================================================
DefineEngineMethod(TreeObject, setTreeType, void, (const char* typeName), ,
   "@brief Sets the data type for the tree at runtime.\n"
   "@param typeName The name of the type (e.g., 'Point3F', 'TransformF').")
{
   object->setType(typeName);
}

DefineEngineMethod(TreeObject, addNode, S32, (S32 parentKey, const char* data, S32 forcedKey), (-1),
   "@brief Adds a node to the hierarchy.\n"
   "@param parentKey The ID of the parent (-1 for root).\n"
   "@param data The data string (TransformF/Point3F).\n"
   "@param forcedKey Optional S32 ID. If -1, one is generated.\n"
   "@return The S32 key assigned to the node.")
{
   return object->addNode(parentKey, data, forcedKey);
}

DefineEngineMethod(TreeObject, deleteNode, void, (S32 key), ,
   "Removes a node and its entire subtree from the armature using its S32 key.")
{
   object->deleteNode(key);
}

DefineEngineMethod(TreeObject, getNode, const char*, (S32 key), ,
   "@brief Retrieves the data string stored in a specific node.\n"
   "@param key The unique ID of the node.\n"
   "@return The data string, or an empty string if the node/data is not found.")
{
   TreeObject::Node* node = object->findNode(key);
   if (node && node->data && node->type)
   {
      const char* dataVal = node->type->getData(node->data, NULL, 0);
      return dataVal ? dataVal : "";
   }
   return "";
}

DefineEngineMethod(TreeObject, toParent, bool, (S32 key, S32 newParentKey), ,
   "@brief Shifts a node to a new parent in the hierarchy.\n"
   "@param key The ID of the node to move.\n"
   "@param newParentKey The ID of the new parent, or -1 for root.\n"
   "@return True on success.")
{
   return object->toParent(key, newParentKey);
}

DefineEngineMethod(TreeObject, getParent, S32, (S32 key), , "Returns parent key.")
{
   return object->getParent(key);
}

DefineEngineMethod(TreeObject, getChildren, const char*, (S32 key), , "Returns space-separated child keys.")
{
   return object->nodesToString(object->getChildren(key));
}

DefineEngineMethod(TreeObject, getNumChildren, S32, (S32 key), ,
   "@brief Returns the number of children attached to the node identified by key.\n"
   "@param key The S32 identifier of the node.")
{
   return object->getNumChildren(key);
}

DefineEngineMethod(TreeObject, getSiblings, const char*, (S32 key), , "Returns space-separated sibling keys.")
{
   return object->nodesToString(object->getSiblings(key));
}

DefineEngineMethod(TreeObject, getNumSiblings, S32, (S32 key), ,
   "@brief Returns the number of siblings for the node identified by key.\n"
   "@param key The S32 identifier of the node.")
{
   return object->getNumSiblings(key);
}

DefineEngineMethod(TreeObject, toString, const char*, (), ,
   "Serializes the tree to a single string with a type header.")
{
   return object->toString();
}

DefineEngineMethod(TreeObject, fromString, void, (const char* data), ,
   "Rebuilds the tree from a serialized string.")
{
   object->fromString(data);
}


//==============================================================
DefineEngineFunction(listConsoleTypes, void, (), , "Lists all registered ConsoleBaseTypes.")
{
   for (ConsoleBaseType* type = ConsoleBaseType::getListHead(); type != NULL; type = type->getListNext())
   {
      Con::printf("%s", type->getTypeName());
   }
}
