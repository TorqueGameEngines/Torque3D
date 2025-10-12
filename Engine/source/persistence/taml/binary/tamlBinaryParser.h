#pragma once
#ifndef _TAML_BINARYPARSER_H_

#ifndef _TAML_PARSER_H_
#include "persistence/taml/tamlParser.h"
#endif

#ifndef _TAML_VISITOR_H_
#include "persistence/taml/tamlVisitor.h"
#endif

#ifndef _STREAM_H_
#include "core/stream/stream.h"
#endif

#ifndef _FILESTREAM_H_
#include "core/stream/fileStream.h"
#endif

class TamlBinaryParser : public TamlParser
{
public:
   TamlBinaryParser() {}
   virtual ~TamlBinaryParser() {}

   /// Whether the parser can change a property or not.
   bool canChangeProperty(void) override { return false; }

   /// Accept visitor.
   bool accept(const char* pFilename, TamlVisitor& visitor) override;

private:
   bool parseElement(Stream& stream, TamlVisitor& visitor, const U32 versionId);
   void parseAttributes(Stream& stream, TamlVisitor& visitor, const U32 versionId, TamlVisitor::PropertyState& state);
   void parseChildren(Stream& stream, TamlVisitor& visitor, const U32 versionId);
   void parseCustomElements(Stream& stream, TamlVisitor& visitor, const U32 versionId);
   bool parseCustomNode(Stream& stream, TamlVisitor& visitor, const U32 versionId, TamlVisitor::PropertyState& state);

   bool isRoot;
};

#endif // !_TAML_BINARYPARSER_H_
