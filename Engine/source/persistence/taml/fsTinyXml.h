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

   // Re-implement protected functionality in TinyXML2 library, and make it public
   // (This is a bit dirty, but it's necessary for the PrettyXMLPrinter)
   bool CompactMode(const tinyxml2::XMLElement& element) override { return tinyxml2::XMLPrinter::CompactMode(element); }
   void PrintSpace(int depth) override { tinyxml2::XMLPrinter::PrintSpace(depth); }
   inline void Write(const char* data) { Write(data, strlen(data)); }

   // Add VFS friendly implementations of output functions
   void Print(const char* format, ...) override;
   void Write(const char* data, size_t size) override;
   void Putc(char ch) override;

   // Accept a virtual FileStream instead of a FILE pointer
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

class PrettyXMLPrinter : public tinyxml2::XMLPrinter
{
   // Re-implement private functionality in TinyXML2
   static const char LINE_FEED = static_cast<char>(0x0a); // all line endings are normalized to LF
   static const char LF = LINE_FEED;
   static const char CARRIAGE_RETURN = static_cast<char>(0x0d); // CR gets filtered out
   static const char CR = CARRIAGE_RETURN;
   static const char SINGLE_QUOTE = '\'';
   static const char DOUBLE_QUOTE = '\"';

   struct Entity
   {
      const char* pattern;
      int length;
      char value;
   };

   static const int NUM_ENTITIES = 5;
   static constexpr  Entity entities[NUM_ENTITIES] = {
      {"quot", 4, DOUBLE_QUOTE},
      {"amp", 3, '&'},
      {"apos", 4, SINGLE_QUOTE},
      {"lt", 2, '<'},
      {"gt", 2, '>'}
   };
public:
   PrettyXMLPrinter(VfsXMLPrinter& innerPrinter, int depth = 0);

   /// Visit a document.
   virtual bool VisitEnter(const tinyxml2::XMLDocument& doc)
   {
      mProcessEntities = doc.ProcessEntities();
      return mInnerPrinter.VisitEnter(doc);
   }

   /// Visit a document.
   virtual bool VisitExit(const tinyxml2::XMLDocument& doc)
   {
      return mInnerPrinter.VisitExit(doc);
   }

   /// Visit an element.
   virtual bool VisitEnter(const tinyxml2::XMLElement& element, const tinyxml2::XMLAttribute* firstAttribute);
   /// Visit an element.
   virtual bool VisitExit(const tinyxml2::XMLElement& element)
   {
      mDepth--;
      return mInnerPrinter.VisitExit(element);
   }

   /// Visit a declaration.
   virtual bool Visit(const tinyxml2::XMLDeclaration& declaration)
   {
      return mInnerPrinter.Visit(declaration);
   }

   /// Visit a text node.
   virtual bool Visit(const tinyxml2::XMLText& text)
   {
      return mInnerPrinter.Visit(text);
   }

   /// Visit a comment node.
   virtual bool Visit(const tinyxml2::XMLComment& comment)
   {
      return mInnerPrinter.Visit(comment);
   }

   /// Visit an unknown node.
   virtual bool Visit(const tinyxml2::XMLUnknown& unknown)
   {
      return mInnerPrinter.Visit(unknown);
   }
   
   void PushAttribute(const char* name, const char* value, bool compactMode);

   // Re-implement private functionality in TinyXML2 library, this is just a copy-paste job
   void PrintString(const char*, bool restrictedEntitySet); // prints out, after detecting entities.

   // The inner printer we are wrapping, we only support VfsXMLPrinter based classes because
   // stock tinyxml printer is very closed
   VfsXMLPrinter& mInnerPrinter;

   // Track private fields that are necessary for private functionality in TinyXML2
   int mDepth;
   bool mProcessEntities;
   bool mCompactMode;

   enum
   {
      ENTITY_RANGE = 64,
      BUF_SIZE = 200
   };

   bool mEntityFlag[ENTITY_RANGE];
   bool mRestrictedEntityFlag[ENTITY_RANGE];
};


#endif //_FSTINYXML_H_
