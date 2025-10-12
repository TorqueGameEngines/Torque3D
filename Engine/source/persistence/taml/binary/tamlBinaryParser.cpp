#include "persistence/taml/binary/tamlBinaryParser.h"
#include "console/console.h"
#include "core/util/zip/zipSubStream.h"
#include "platform/profiler.h"
#include "persistence/taml/taml.h"

bool TamlBinaryParser::accept(const char* pFilename, TamlVisitor& visitor)
{
   isRoot = true;
   PROFILE_SCOPE(TamlBinaryParser_Accept);
   AssertFatal(pFilename != NULL, "TamlBinaryParser::accept - NULL filename.");

   char filenameBuffer[1024];
   Con::expandScriptFilename(filenameBuffer, sizeof(filenameBuffer), pFilename);

   FileStream stream;
   if (!stream.open(filenameBuffer, Torque::FS::File::Read))
   {
      Con::warnf("TamlBinaryParser::accept - Could not open file '%s'.", filenameBuffer);
      return false;
   }

   // Read TAML signature.
   StringTableEntry signature = stream.readSTString();
   if (signature != StringTable->insert(TAML_SIGNATURE))
   {
      Con::warnf("TamlBinaryParser::accept - Invalid signature in '%s'.", filenameBuffer);
      stream.close();
      return false;
   }

   setParsingFilename(pFilename);

   U32 versionId;
   stream.read(&versionId);

   bool compressed;
   stream.read(&compressed);

   if (compressed)
   {
      ZipSubRStream zipStream;
      zipStream.attachStream(&stream);
      parseElement(zipStream, visitor, versionId);
      zipStream.detachStream();
   }
   else
   {
      parseElement(stream, visitor, versionId);
   }

   stream.close();

   setParsingFilename(StringTable->EmptyString());

   return true;
}

//-----------------------------------------------------------------------------

bool TamlBinaryParser::parseElement(Stream& stream, TamlVisitor& visitor, const U32 versionId)
{
   PROFILE_SCOPE(TamlBinaryParser_ParseElement);

   // --- Read element header ---
   StringTableEntry pElementName = stream.readSTString();
   StringTableEntry pObjectName = stream.readSTString();

   // Read references.
   U32 refId, refToId;
   stream.read(&refId);
   stream.read(&refToId);

   // If this is a reference to another object, skip it.
   if (refToId != 0)
      return true;

   // Create a property visitor state.
   TamlVisitor::PropertyState propertyState;

   propertyState.setObjectName(pElementName, isRoot);
   if (pObjectName != StringTable->EmptyString())
      propertyState.setProperty("Name", pObjectName);

   if(isRoot)
      isRoot = false;

   // --- Attributes ---
   parseAttributes(stream, visitor, versionId, propertyState);
   // --- Children ---
   parseChildren(stream, visitor, versionId);
   // --- Custom elements ---
   parseCustomElements(stream, visitor, versionId);


   return true;
}

void TamlBinaryParser::parseAttributes(Stream& stream, TamlVisitor& visitor, const U32 versionId, TamlVisitor::PropertyState& state)
{
   PROFILE_SCOPE(TamlBinaryParser_ParseAttributes);

   U32 attributeCount;
   stream.read(&attributeCount);
   if (attributeCount == 0)
      return;

   char valueBuffer[4096];
   for (U32 i = 0; i < attributeCount; ++i)
   {
      StringTableEntry attrName = stream.readSTString();
      stream.readLongString(4096, valueBuffer);
      state.setProperty(attrName, valueBuffer);
      const bool visitStatus = visitor.visit(*this, state);
      if (!visitStatus)
         return;
   }
}

//-----------------------------------------------------------------------------

void TamlBinaryParser::parseChildren(Stream& stream, TamlVisitor& visitor, const U32 versionId)
{
   PROFILE_SCOPE(TamlBinaryParser_ParseChildren);

   U32 childCount = 0;
   stream.read(&childCount);
   if (childCount == 0)
      return;

   for (U32 i = 0; i < childCount; ++i)
   {
      parseElement(stream, visitor, versionId);
   }
}

//-----------------------------------------------------------------------------

void TamlBinaryParser::parseCustomElements(Stream& stream, TamlVisitor& visitor, const U32 versionId)
{
   PROFILE_SCOPE(TamlBinaryParser_ParseCustomElements);

   U32 customNodeCount = 0;
   stream.read(&customNodeCount);
   if (customNodeCount == 0)
      return;

   TamlVisitor::PropertyState state;

   for (U32 nodeIndex = 0; nodeIndex < customNodeCount; ++nodeIndex)
   {
      StringTableEntry nodeName = stream.readSTString();
      state.setObjectName(nodeName, false);

      U32 nodeChildrenCount = 0;
      stream.read(&nodeChildrenCount);
      if (nodeChildrenCount == 0)
         return;

      for(U32 nodeChild = 0; nodeChild < nodeChildrenCount; ++nodeChild)
         parseCustomNode(stream, visitor, versionId, state);
   }

}


//-----------------------------------------------------------------------------

bool TamlBinaryParser::parseCustomNode(Stream& stream, TamlVisitor& visitor, const U32 versionId, TamlVisitor::PropertyState& state)
{
   PROFILE_SCOPE(TamlBinaryParser_ParseCustomNode);

   bool isProxyObject;
   stream.read(&isProxyObject);
   if (isProxyObject)
   {
      // Parse nested proxy element.
      return parseElement(stream, visitor, versionId);
   }

   StringTableEntry nodeName = stream.readSTString();

   char nodeValue[MAX_TAML_NODE_FIELDVALUE_LENGTH];

   stream.readLongString(MAX_TAML_NODE_FIELDVALUE_LENGTH, nodeValue);

   U32 childCount;
   stream.read(&childCount);
   for (U32 i = 0; i < childCount; ++i)
   {
      if (!parseCustomNode(stream, visitor, versionId, state))
         return false;
   }

   U32 fieldCount;
   stream.read(&fieldCount);

   if (fieldCount > 0)
   {
      char valueBuffer[MAX_TAML_NODE_FIELDVALUE_LENGTH];
      for (U32 f = 0; f < fieldCount; ++f)
      {
         StringTableEntry fieldName = stream.readSTString();
         stream.readLongString(MAX_TAML_NODE_FIELDVALUE_LENGTH, valueBuffer);
         state.setProperty(fieldName, valueBuffer);
         const bool visitStatus = visitor.visit(*this, state);
         if (!visitStatus)
            return false;
      }
   }

   return true;
}
