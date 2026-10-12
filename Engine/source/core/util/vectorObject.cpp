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

#include "vectorObject.h"
#include "console/consoleTypes.h"
#include "console/engineAPI.h"

IMPLEMENT_CONOBJECT(VectorObject);

void VectorObject::initPersistFields()
{
   addProtectedField("varType", TypeString, Offset(mVarType, VectorObject), &_setType, &defaultProtectedGetFn, "Set type by name.");
   Parent::initPersistFields();
}

void VectorObject::_internalSetType(const char* typeName)
{
   if (!typeName || !typeName[0]) return;

   ConsoleBaseType* newType = ConsoleBaseType::getTypeByName(typeName);

   if (newType)
      mVarType = newType;
   else
      Con::errorf("VectorObject: Invalid type '%s'. Use 'TypeS32', 'TypePoint3F', etc.", typeName);
}

bool VectorObject::_setType(void* obj, const char* index, const char* data)
{
   VectorObject* tree = static_cast<VectorObject*>(obj);
   if (tree != NULL)
      tree->_internalSetType(data);

   return false;
}

void VectorObject::setType(const char* typeName)
{
   if (typeName && typeName[0])
   {
      ConsoleBaseType* newType = ConsoleBaseType::getTypeByName(typeName);
      if (newType)
         mVarType = newType;
      else
         Con::errorf("VectorObject::setType - Unknown console type '%s'! use listConsoleTypes for options", typeName);
   }
}

void* VectorObject::get(U32 index)
{
   if (index >= mData.size())
   {
      Con::errorf("VectorObject::get - Index %d out of bounds (size: %d)", index, mData.size());
      return NULL;
   }
   return mData[index];
}

void VectorObject::set(U32 index, void* data)
{
   if (index >= mData.size())
   {
      Con::errorf("VectorObject::set - Index %d out of bounds (size: %d)", index, mData.size());
      return;
   }
   mData.set(data, index );
}

void VectorObject::push_back(void* data)
{
   mData.push_back(data);
}

void VectorObject::insert(U32 index, void* data)
{
   if (index > mData.size())
   {
      Con::errorf("VectorObject::insert - Index %d out of bounds (size: %d)", index, mData.size());
      return;
   }
   mData.insert(index, data);
}

void VectorObject::erase(U32 index)
{
   if (index >= mData.size())
   {
      Con::errorf("VectorObject::erase - Index %d out of bounds (size: %d)", index, mData.size());
      return;
   }
   mData.erase(index);
}

void VectorObject::clear()
{
   mData.clear();
}

void VectorObject::fromString(char* dataString)
{
   clear();

   if (!mVarType || !dataString || !dataString[0])
      return;

   String dataStr(dataString);
   Vector<String> tokens;
   dataStr.split(" \t\n\r", tokens);
   const U32 typeSize = 128;
   for (U32 i = 0; i < tokens.size(); ++i)
   {
      const char* tokenStr = tokens[i].c_str();

      void* nativeVar = mVarType->getNativeVariable();
      Con::setData(mVarType->getTypeID(), nativeVar, 0, 1, &tokenStr);

      void* persistentData = dMalloc(typeSize);
      dMemcpy(persistentData, nativeVar, typeSize);

      mData.push_back(persistentData);
   }
}

char* VectorObject::toString()
{
   if (!mVarType || mData.empty())
      return "";

   char* returnBuffer = Con::getReturnBuffer(16384);
   returnBuffer[0] = '\0';

   for (U32 i = 0; i < mData.size(); ++i)
   {
      const char* valString = Con::getData(mVarType->getTypeID(), mData[i], 0);

      if (!valString) continue;

      if (i > 0)
         dStrcat(returnBuffer, " ", 16384);

      dStrcat(returnBuffer, valString, 16384);
   }

   return returnBuffer;
}

//--- ENGINE METHODS ---//
DefineEngineMethod(VectorObject, setType, void, (const char* typeName), ,
   "@brief Sets the data type for the vector at runtime.\n"
   "@param typeName The name of the type (e.g., 'Point3F', 'TransformF').")
{
   object->setType(typeName);
}

DefineEngineMethod(VectorObject, getType, const char*, (), ,
   "@brief Returns the name of the currently assigned ConsoleBaseType.\n"
   "@return The type name as a string.")
{
   ConsoleBaseType* type = object->getVarType();
   return type ? type->getTypeName() : "";
}

DefineEngineMethod(VectorObject, size, S32, (), ,
   "@brief Returns the number of elements in the vector.\n"
   "@return The number of elements.")
{
   return object->size();
}

DefineEngineMethod(VectorObject, clear, void, (), ,
   "@brief Clears all elements from the vector.")
{
   object->clear();
}

DefineEngineMethod(VectorObject, push_back, void, (const char* data), ,
   "@brief Appends an element to the end of the vector.\n"
   "@param data The data string (TransformF/Point3F/etc).")
{
   if (!object->getVarType())
   {
      Con::errorf("VectorObject::push_back - No variable type set!");
      return;
   }
   const char* dataStr = data;
   void* nativeVar = object->getVarType()->getNativeVariable();
   Con::setData(object->getVarType()->getTypeID(), nativeVar, 0, 1, &dataStr);
   const U32 typeSize = 128;
   void* persistentData = dMalloc(typeSize);
   dMemcpy(persistentData, nativeVar, typeSize);
   object->push_back(persistentData);
}

DefineEngineMethod(VectorObject, get, const char*, (S32 index), ,
   "@brief Retrieves an element from the vector.\n"
   "@param index The index of the element to retrieve.\n"
   "@return The data string (TransformF/Point3F/etc).")
{
   if (!object->getVarType())
   {
      Con::errorf("VectorObject::get - No variable type set!");
      return "";
   }
   void* data = object->get(index);
   if (!data)
      return "";
   return Con::getData(object->getVarType()->getTypeID(), data, 0);
}

DefineEngineMethod(VectorObject, set, void, (S32 index, const char* data), ,
   "@brief Sets an element in the vector.\n"
   "@param index The index of the element to set.\n"
   "@param data The data string (TransformF/Point3F/etc).")
{
   if (!object->getVarType())
   {
      Con::errorf("VectorObject::set - No variable type set!");
      return;
   }
   const char* dataStr = data;
   void* nativeVar = object->getVarType()->getNativeVariable();
   Con::setData(object->getVarType()->getTypeID(), nativeVar, 0, 1, &dataStr);
   const U32 typeSize = 128;
   void* persistentData = dMalloc(typeSize);
   dMemcpy(persistentData, nativeVar, typeSize);
   object->set(index, persistentData);
}

DefineEngineMethod(VectorObject, insert, void, (S32 index, const char* data), ,
   "@brief Inserts an element into the vector at the specified index.\n"
   "@param index The index at which to insert the element.\n"
   "@param data The data string (TransformF/Point3F/etc).")
{
   if (!object->getVarType())
   {
      Con::errorf("VectorObject::insert - No variable type set!");
      return;
   }
   const char* dataStr = data;
   void* nativeVar = object->getVarType()->getNativeVariable();
   Con::setData(object->getVarType()->getTypeID(), nativeVar, 0, 1, &dataStr);
   const U32 typeSize = 128;
   void* persistentData = dMalloc(typeSize);
   dMemcpy(persistentData, nativeVar, typeSize);
   object->insert(index, persistentData);
}

DefineEngineMethod(VectorObject, erase, void, (S32 index), ,
   "@brief Removes an element from the vector at the specified index.\n"
   "@param index The index of the element to remove.")
{
   object->erase(index);
}

DefineEngineMethod(VectorObject, fromString, void, (const char* data), ,
   "@brief Populates the vector from a space-separated string of data.\n"
   "@param data The space-separated data string.")
{
   char* dataCopy = dStrdup(data);
   object->fromString(dataCopy);
   dFree(dataCopy);
}

DefineEngineMethod(VectorObject, toString, const char*, (), ,
   "@brief Converts the vector's contents to a space-separated string.\n"
   "@return The space-separated data string.")
{
   return object->toString();
}

ConsoleType(TypeVector, TypeVector, VectorObject*, NULL)
ImplementConsoleTypeCasters(TypeVector, VectorObject*);

ConsoleGetType(TypeVector)
{
   VectorObject* vObj = *((VectorObject**)dptr);
   if (!vObj) return "";

   // Returns "TypeName Element1 Element2 ..."
   const char* typeName = vObj->getVarType() ? vObj->getVarType()->getTypeName() : "TypeVoid";

   static const U32 bufSize = 16384;
   char* returnBuffer = Con::getReturnBuffer(bufSize);
   dSprintf(returnBuffer, bufSize, "%s %s", typeName, vObj->toString());

   return returnBuffer;
}

ConsoleSetType(TypeVector)
{
   if (argc < 1) return;

   VectorObject** vObjPtr = (VectorObject**)dptr;
   VectorObject* vObj = *vObjPtr;

   if (vObj)
   {
      // Tokenize the input: The first entry is the TYPE
      String dataStr(argv[0]);
      Vector<String> tokens;
      dataStr.split(" \t\n\r", tokens);

      if (tokens.size() > 0)
      {
         // 1. Set the VarType from the first token (e.g., "TypePoint3F")
         vObj->setType(tokens[0].c_str());

         // 2. Process the rest as elements
         if (tokens.size() > 1)
         {
            // Re-concatenate the remaining tokens into a data string
            String remainingData = "";
            for (U32 i = 1; i < tokens.size(); ++i)
            {
               remainingData += tokens[i];
               if (i < tokens.size() - 1) remainingData += " ";
            }
            vObj->fromString(const_cast<char*>(remainingData.c_str()));
         }
      }
   }
   else
   {
      // If the field is currently null, attempt to resolve argv as an object name
      if (!Sim::findObject(argv[0], *vObjPtr))
         Con::warnf("TypeVector::setData - Could not resolve VectorObject: %s", argv[0]);
   }
}
