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

#ifndef _TVECTOROBJECT_H_
#define _TVECTOROBJECT_H_

#include "console/simObject.h"

class VectorObject : public SimObject {
   typedef SimObject Parent;

protected:
   ConsoleBaseType* mVarType;
   Vector<void*> mData;
public:
   VectorObject(): mVarType(NULL) {};
   DECLARE_CONOBJECT(VectorObject);

   static void initPersistFields();

   void _internalSetType(const char* typeName);
   static bool _setType(void* obj, const char* index, const char* data);
   void setType(const char* typeName);
   ConsoleBaseType* getVarType() { return mVarType; };

   U32 size() const { return mData.size(); };
   void* get(U32 index);
   void set(U32 index, void* data);
   void push_back(void* data);
   void insert(U32 index, void* data);
   void erase(U32 index);
   void clear();
   void fromString(char* data);
   char* toString();
};

DefineConsoleType(TypeVector, VectorObject*);

template<typename T>
static inline S32 VecType() {
   return TYPEID<VectorObject*>();
}

#endif
