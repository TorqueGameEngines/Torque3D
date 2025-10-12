#include "persistence/taml/binary/tamlBinaryParser.h"
#include "console/console.h"
#include "core/util/zip/zipSubStream.h"
#include "platform/profiler.h"
#include "persistence/taml/taml.h"

bool TamlBinaryParser::accept(const char* pFilename, TamlVisitor& visitor)
{
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
   return true;
}

//-----------------------------------------------------------------------------

bool TamlBinaryParser::parseElement(Stream& stream, TamlVisitor& visitor, const U32 versionId)
{
   PROFILE_SCOPE(TamlBinaryParser_ParseElement);

   // Read the type and name.
   StringTableEntry typeName = stream.readSTString();
   StringTableEntry objectName = stream.readSTString();

   // Read references.
   U32 refId, refToId;
   stream.read(&refId);
   stream.read(&refToId);

   // Create a property visitor state.
   TamlVisitor::PropertyState propertyState;
   propertyState.setObjectName(typeName, false);

   if (objectName != StringTable->EmptyString())
      propertyState.setProperty("Name", objectName);

   if (!visitor.visit(*this, propertyState))
      return false;

   // Parse attributes.
   U32 attrCount;
   stream.read(&attrCount);

   char valueBuffer[4096];
   for (U32 i = 0; i < attrCount; ++i)
   {
      StringTableEntry attrName = stream.readSTString();
      stream.readLongString(sizeof(valueBuffer), valueBuffer);
      propertyState.setProperty(attrName, valueBuffer);
      visitor.visit(*this, propertyState);
   }

   // Parse children.
   U32 childCount;
   stream.read(&childCount);
   for (U32 c = 0; c < childCount; ++c)
   {
      if (!parseElement(stream, visitor, versionId))
         return false;
   }

   // Parse custom nodes.
   U32 customCount;
   stream.read(&customCount);
   for (U32 cn = 0; cn < customCount; ++cn)
   {
      StringTableEntry customNodeName = stream.readSTString();
      propertyState.setProperty("CustomNode", customNodeName);
      visitor.visit(*this, propertyState);
      parseCustomNode(stream, visitor, versionId);
   }

   return true;
}

//-----------------------------------------------------------------------------

bool TamlBinaryParser::parseCustomNode(Stream& stream, TamlVisitor& visitor, const U32 versionId)
{
   PROFILE_SCOPE(TamlBinaryParser_ParseCustomNode);

   bool isProxyObject;
   stream.read(&isProxyObject);

   if (isProxyObject)
   {
      // Parse nested proxy element.
      return parseElement(stream, visitor, versionId);
   }

   // Read custom node name and text.
   StringTableEntry nodeName = stream.readSTString();

   char textBuffer[1024];
   stream.readLongString(sizeof(textBuffer), textBuffer);

   // Create visitor state for the node.
   TamlVisitor::PropertyState nodeState;
   nodeState.setObjectName(nodeName, false);
   nodeState.setProperty("Text", textBuffer);
   visitor.visit(*this, nodeState);

   // Parse child nodes.
   U32 childCount;
   stream.read(&childCount);
   for (U32 i = 0; i < childCount; ++i)
   {
      if (!parseCustomNode(stream, visitor, versionId))
         return false;
   }

   // Parse fields.
   U32 fieldCount;
   stream.read(&fieldCount);

   char valueBuffer[1024];
   for (U32 f = 0; f < fieldCount; ++f)
   {
      StringTableEntry fieldName = stream.readSTString();
      stream.readLongString(sizeof(valueBuffer), valueBuffer);
      nodeState.setProperty(fieldName, valueBuffer);
      visitor.visit(*this, nodeState);
   }

   return true;
}
