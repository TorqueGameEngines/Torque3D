//-----------------------------------------------------------------------------
// Copyright (c) 2013 GarageGames, LLC
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

#ifndef _FSTINYXML_H_
#define _FSTINYXML_H_


#ifndef TINYXML_INCLUDED
#include "tinyxml/tinyxml2.h"
#endif

#include "platform/platform.h"

#ifndef _FILESTREAM_H_
#include "core/stream/fileStream.h"
#endif

class VfsXMLPrinter : public tinyxml2::XMLPrinter
{
public:
   VfsXMLPrinter(FileStream& stream, bool compact = false, int depth = 0);
   ~VfsXMLPrinter() override;

   void Print(const char* format, ...) override;
   void Write(const char* data, size_t size) override;
   void Putc(char ch) override;
   FileStream& m_Stream;
};

class VfsXMLDocument : public tinyxml2::XMLDocument
{
public:
   bool LoadFile(FileStream& stream);
   bool SaveFile(FileStream& stream);
   /// Load a file using the given filename. Returns true if successful.
   bool LoadFile(const char* filename);
   /// Save a file using the given filename. Returns true if successful.
   bool SaveFile(const char* filename);

   /// Clears the error flags.
   void ClearError();


   tinyxml2::XMLError _errorID;
   mutable tinyxml2::StrPair _errorStr;
   int _errorLineNum;

   // Create a parallel SetError implementation since it is private in tinyxml2
   void SetError(tinyxml2::XMLError error, int lineNum, const char* format, ...);

   /// Return true if there was an error parsing the document.
   bool Error() const
   {
      return _errorID != tinyxml2::XML_SUCCESS || XMLDocument::Error();
   }

   /// Return the errorID.
   tinyxml2::XMLError ErrorID() const
   {
      if (XMLDocument::Error())
      {
         return XMLDocument::ErrorID();
      }
      else
      {
         return _errorID;
      }
   }

   const char* ErrorName() const
   {
      if (XMLDocument::Error())
      {
         return XMLDocument::ErrorName();
      }
      else
      {
         return ErrorIDToName(_errorID);
      }
   }

   /** Returns a "long form" error description. A hopefully helpful
       diagnostic with location, line number, and/or additional info.
   */
   const char* ErrorStr() const
   {
      if (XMLDocument::Error())
      {
         return XMLDocument::ErrorStr();
      }
      else
      {
         return _errorStr.Empty() ? "" : _errorStr.GetStr();
      }
   }

   /// Return the line where the error occurred, or zero if unknown.
   int ErrorLineNum() const
   {
      if (XMLDocument::Error())
      {
         return XMLDocument::ErrorLineNum();
      }
      else
      {
         return _errorLineNum;
      }
   }
};

#endif //_FSTINYXML_H_
