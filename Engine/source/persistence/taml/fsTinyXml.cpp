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

#include "fsTinyXml.h"

#include <cassert>

#include "console/console.h"

bool VfsXMLDocument::LoadFile(const char* pFilename)
{
   // Expand the file-path.
   char filenameBuffer[1024];
   Con::expandScriptFilename(filenameBuffer, sizeof(filenameBuffer), pFilename);

   FileStream stream;

#ifdef TORQUE_OS_ANDROID
   if (strlen(pFilename) > strlen(filenameBuffer)) {
      dStrcpy(filenameBuffer, pFilename, 1024);
   }
#endif

   // File open for read?
   if (!stream.open(filenameBuffer, Torque::FS::File::Read))
   {
      // No, so warn.
      Con::warnf("TamlXmlParser::parse() - Could not open filename '%s' for parse.", filenameBuffer);
      return false;
   }

   // Load document from stream.
   if (!LoadFile(stream))
   {
      // Warn!
      Con::warnf("TamlXmlParser: Could not load Taml XML file from stream.");
      return false;
   }

   // Close the stream.
   stream.close();
   return true;
}

bool VfsXMLDocument::SaveFile(const char* pFilename)
{
   // Expand the file-name into the file-path buffer.
   char filenameBuffer[1024];
   Con::expandScriptFilename(filenameBuffer, sizeof(filenameBuffer), pFilename);

   FileStream stream;

   // File opened?
   if (!stream.open(filenameBuffer, Torque::FS::File::Write))
   {
      // No, so warn.
      Con::warnf("Taml::writeFile() - Could not open filename '%s' for write.", filenameBuffer);
      return false;
   }

   bool ret = SaveFile(stream);

   stream.close();
   return ret;
}

void VfsXMLDocument::ClearError()
{
   _errorID = tinyxml2::XML_SUCCESS;
   _errorLineNum = 0;
   _errorStr.Reset();

   tinyxml2::XMLDocument::ClearError();
}

void VfsXMLDocument::SetError(tinyxml2::XMLError error, int lineNum, const char* format, ...)
{
   TIXMLASSERT(error >= 0 && error < tinyxml2::XML_ERROR_COUNT);
   _errorID = error;
   _errorLineNum = lineNum;
   _errorStr.Reset();

   const size_t BUFFER_SIZE = 1000;
   char* buffer = new char[BUFFER_SIZE];

   TIXMLASSERT(sizeof(error) <= sizeof(int));
   dSprintf(buffer, BUFFER_SIZE, "Error=%s ErrorID=%d (0x%x) Line number=%d", ErrorIDToName(error), int(error), int(error), lineNum);

   if (format) {
      size_t len = strlen(buffer);
      dSprintf(buffer + len, BUFFER_SIZE - len, ": ");
      len = strlen(buffer);

      va_list va;
      va_start(va, format);
      dSprintf(buffer + len, BUFFER_SIZE - len, format, va);
      va_end(va);
   }
   _errorStr.SetStr(buffer);
   delete[] buffer;
}

VfsXMLPrinter::VfsXMLPrinter(FileStream& stream, bool compact, int depth)
   : XMLPrinter(NULL, compact, depth),
     m_Stream(stream)
{
}

VfsXMLPrinter::~VfsXMLPrinter()
{
   m_Stream.flush();
   m_Stream.close();
}

void VfsXMLPrinter::Print(const char* format, ...)
{
   va_list     va;
   va_start(va, format);

   m_Stream.writeFormattedBuffer(format, va);

   va_end(va);
}

void VfsXMLPrinter::Write(const char* data, size_t size)
{
   m_Stream.write(size, data);
}

void VfsXMLPrinter::Putc(char ch)
{
   m_Stream.write(static_cast<U8>(ch));
}

bool VfsXMLDocument::LoadFile(FileStream& stream)
{
   // Delete the existing data:
   Clear();
   // Clear shadowed error
   ClearError();
   //TODO: Can't clear location, investigate if this gives issues.
   //doc.location.Clear();

   // Get the file size, so we can pre-allocate the string. HUGE speed impact.
   long length = stream.getStreamSize();

   // Strange case, but good to handle up front.
   if (length <= 0)
   {
      SetError(tinyxml2::XML_ERROR_EMPTY_DOCUMENT, 0, 0);
      return false;
   }

   // Subtle bug here. TinyXml did use fgets. But from the XML spec:
   // 2.11 End-of-Line Handling
   // <snip>
   // <quote>
   // ...the XML processor MUST behave as if it normalized all line breaks in external 
   // parsed entities (including the document entity) on input, before parsing, by translating 
   // both the two-character sequence #xD #xA and any #xD that is not followed by #xA to 
   // a single #xA character.
   // </quote>
   //
   // It is not clear fgets does that, and certainly isn't clear it works cross platform. 
   // Generally, you expect fgets to translate from the convention of the OS to the c/unix
   // convention, and not work generally.

   /*
   while( fgets( buf, sizeof(buf), file ) )
   {
   data += buf;
   }
   */

   char* buf = new char[length + 1];
   buf[0] = 0;

   if (!stream.read(length, buf))
   {
      delete [] buf;
      SetError(tinyxml2::XML_ERROR_FILE_COULD_NOT_BE_OPENED, 0, 0);
      return false;
   }

   // Process the buffer in place to normalize new lines. (See comment above.)
   // Copies from the 'p' to 'q' pointer, where p can advance faster if
   // a newline-carriage return is hit.
   //
   // Wikipedia:
   // Systems based on ASCII or a compatible character set use either LF  (Line feed, '\n', 0x0A, 10 in decimal) or 
   // CR (Carriage return, '\r', 0x0D, 13 in decimal) individually, or CR followed by LF (CR+LF, 0x0D 0x0A)...
   //                * LF:    Multics, Unix and Unix-like systems (GNU/Linux, AIX, Xenix, Mac OS X, FreeBSD, etc.), BeOS, Amiga, RISC OS, and others
   //                * CR+LF: DEC RT-11 and most other early non-Unix, non-IBM OSes, CP/M, MP/M, DOS, OS/2, Microsoft Windows, Symbian OS
   //                * CR:    Commodore 8-bit machines, Apple II family, Mac OS up to version 9 and OS-9

   const char* p = buf; // the read head
   char* q = buf; // the write head
   const char CR = 0x0d;
   const char LF = 0x0a;

   buf[length] = 0;
   while (*p)
   {
      assert(p < (buf+length));
      assert(q <= (buf+length));
      assert(q <= p);

      if (*p == CR)
      {
         *q++ = LF;
         p++;
         if (*p == LF)
         {
            // check for CR+LF (and skip LF)
            p++;
         }
      }
      else
      {
         *q++ = *p++;
      }
   }
   assert(q <= (buf+length));
   *q = 0;

   Parse(buf, length);

   delete [] buf;
   return !Error();
}

bool VfsXMLDocument::SaveFile(FileStream& stream)
{
   // Clear any error from the last save, otherwise it will get reported
   // for *this* call.
   ClearError();
   VfsXMLPrinter printer(stream, false, 0);
   Print(&printer);
   return !Error();
}
