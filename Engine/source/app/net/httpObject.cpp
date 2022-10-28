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

//-----------------------------------------------------------------------------
// Copyright (c) 2017 The Platinum Team
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
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//-----------------------------------------------------------------------------

#include "app/net/httpObject.h"

#include "platform/platform.h"
#include "core/stream/fileStream.h"
#include "console/simBase.h"
#include "console/consoleInternal.h"
#include "console/engineAPI.h"
#include <string.h>

IMPLEMENT_CONOBJECT(HTTPObject);

ConsoleDocClass(HTTPObject,
   "@brief Allows communications between the game and a server using HTTP.\n\n"
   
   "HTTPObject is derrived from TCPObject and makes use of the same callbacks for dealing with "
   "connections and received data.  However, the way in which you use HTTPObject to connect "
   "with a server is different than TCPObject.  Rather than opening a connection, sending data, "
   "waiting to receive data, and then closing the connection, you issue a get() or post() and "
   "handle the response.  The connection is automatically created and destroyed for you.\n\n"
   
   "@tsexample\n"
      "// In this example we'll retrieve the weather in Las Vegas using\n"
      "// Google's API.  The response is in XML which could be processed\n"
      "// and used by the game using SimXMLDocument, but we'll just output\n"
      "// the results to the console in this example.\n\n"

      "// Define callbacks for our specific HTTPObject using our instance's\n"
      "// name (WeatherFeed) as the namespace.\n\n"

      "// Handle an issue with resolving the server's name\n"
      "function WeatherFeed::onDNSFailed(%this)\n"
      "{\n"
      "   // Store this state\n"
      "   %this.lastState = \"DNSFailed\";\n\n"

      "   // Handle DNS failure\n"
      "}\n\n"

      "function WeatherFeed::onConnectFailed(%this)\n"
      "{\n"
      "   // Store this state\n"
      "   %this.lastState = \"ConnectFailed\";\n\n"
      "   // Handle connection failure\n"
      "}\n\n"

      "function WeatherFeed::onDNSResolved(%this)\n"
      "{\n"
      "   // Store this state\n"
      "   %this.lastState = \"DNSResolved\";\n\n"
      "}\n\n"

      "function WeatherFeed::onConnected(%this)\n"
      "{\n"
      "   // Store this state\n"
      "   %this.lastState = \"Connected\";\n\n"

      "   // Clear our buffer\n"
      "   %this.buffer = \"\";\n"
      "}\n\n"

      "function WeatherFeed::onDisconnect(%this)\n"
      "{\n"
      "   // Store this state\n"
      "   %this.lastState = \"Disconnected\";\n\n"

      "   // Output the buffer to the console\n"
      "   echo(\"Google Weather Results:\");\n"
      "   echo(%this.buffer);\n"
      "}\n\n"

      "// Handle a line from the server\n"
      "function WeatherFeed::onLine(%this, %line)\n"
      "{\n"
      "   // Store this line in out buffer\n"
      "   %this.buffer = %this.buffer @ %line;\n"
      "}\n\n"

      "// Create the HTTPObject\n"
      "%feed = new HTTPObject(WeatherFeed);\n\n"

      "// Define a dynamic field to store the last connection state\n"
      "%feed.lastState = \"None\";\n\n"

      "// Send the GET command\n"
      "%feed.get(\"www.google.com:80\", \"/ig/api\", \"weather=Las-Vegas,US\");\n"
   "@endtsexample\n\n"
   
   "@see TCPObject\n"

   "@ingroup Networking\n"
);

CURLM *HTTPObject::gCurlMulti = nullptr;
int HTTPObject::gCurlMultiTotal = 0;
std::unordered_map<CURL *, HTTPObject *> HTTPObject::gCurlMap;

size_t HTTPObject::writeCallback(char *buffer, size_t size, size_t nitems, HTTPObject *object) {
   return object->processData(buffer, size, nitems);
}


size_t HTTPObject::headerCallback(char *buffer, size_t size, size_t nitems, HTTPObject *object) {
   return object->processHeader(buffer, size, nitems);
}

//--------------------------------------

HTTPObject::HTTPObject()
   : mCurl(nullptr),
   mBuffer(nullptr),
   mBufferSize(0),
   mBufferUsed(0),
   mDownload(false),
   mHeaders(nullptr)
{
   CURL *request = curl_easy_init();
   curl_easy_setopt(request, CURLOPT_VERBOSE, false);
   curl_easy_setopt(request, CURLOPT_FOLLOWLOCATION, true);
   curl_easy_setopt(request, CURLOPT_TRANSFERTEXT, true);
   curl_easy_setopt(request, CURLOPT_USERAGENT, "Torque 1.0");
   curl_easy_setopt(request, CURLOPT_ENCODING, "ISO 8859-1");

   mCurl = request;
   gCurlMap[request] = this;

   curl_easy_setopt(request, CURLOPT_WRITEDATA, this);
   curl_easy_setopt(request, CURLOPT_WRITEFUNCTION, writeCallback);
   curl_easy_setopt(request, CURLOPT_HEADERDATA, this);
   curl_easy_setopt(request, CURLOPT_HEADERFUNCTION, headerCallback);
}

HTTPObject::~HTTPObject()
{
}

//--------------------------------------

bool HTTPObject::ensureBuffer(U32 length)
{
   if (mBufferSize < length) {
      //CURL_MAX_WRITE_SIZE is the maximum packet size we'll be given. So round
      // off to that and we should not have to allocate too often.
      length = ((length / CURL_MAX_WRITE_SIZE) + 1) * CURL_MAX_WRITE_SIZE;
      void *alloced = dRealloc(mBuffer, length * sizeof(char));

      //Out of memory
      if (!alloced) {
         return false;
      }

      mBuffer = (U8 *)alloced;
      mBufferSize = length;
   }
   return true;
}

size_t HTTPObject::processData(char *buffer, size_t size, size_t nitems)
{
   size_t writeSize = size * nitems + 1;

   if (!ensureBuffer(mBufferUsed + writeSize)) {
      //Error
      return 0;
   }

   memcpy(mBuffer + mBufferUsed, buffer, size * nitems);
   mBufferUsed += size * nitems;
   mBuffer[mBufferUsed] = 0;

   return size * nitems;
}

size_t HTTPObject::processHeader(char *buffer, size_t size, size_t nitems)
{
   char *colon = strchr(buffer, ':');
   if (colon != NULL) {
      std::string key(buffer, colon - buffer);
      std::string value(colon + 2);

      if (value[value.length() - 1] == '\n')
         value.erase(value.length() - 1, 1);
      if (value[value.length() - 1] == '\r')
         value.erase(value.length() - 1, 1);

      mRecieveHeaders[key] = value;
   }

   return size * nitems;
}

void HTTPObject::start()
{
   CURLMcode result = curl_multi_add_handle(gCurlMulti, mCurl);
   if (result != CURLM_OK) {
      Con::errorf("curl_easy_perform failed (%d): %s", result, curl_multi_strerror(result));
      return;
   }
   ++gCurlMultiTotal;
}

void HTTPObject::processLines()
{
   if (mDownload) {
      const std::string &dlPath = mDownloadPath;
      int lastSlash = dlPath.find_last_of('/');

      const char *path;
      const char *file;

      if (lastSlash == std::string::npos) {
         //No
         return;
      } else {
         path = StringTable->insert(dlPath.c_str(), false);
         file = StringTable->insert(dlPath.substr(lastSlash + 1).c_str(), false);
      }

      //Don't download unless we get an OK
      long responseCode;
      curl_easy_getinfo(mCurl, CURLINFO_RESPONSE_CODE, &responseCode);
      if (responseCode != 200) {
         onDownloadFailed(path);
         return;
      }

      //Write to the output file
      FileStream *stream = new FileStream();

      if (!stream->open(path, Torque::FS::File::Write)) {
         Con::errorf("Could not download %s: error opening stream.");
         onDownloadFailed(path);
         return;
      }

      stream->write(mBufferUsed, mBuffer);
      stream->close();

      onDownload(path);

      delete stream;
   } else {

      //Pull all the lines out of mBuffer
      char *str = (char *)mBuffer;
      char *nextLine = str;
      while (str && nextLine) {
         nextLine = strchr(str, '\n');

         //Get how long the current line for allocating
         U32 lineSize = 0;
         if (nextLine == NULL) {
            lineSize = strlen(str);
            if (lineSize == 0) {
               break;
            }
         } else {
            lineSize = nextLine - str;
         }

         //Copy into a return buffer for the script
         char *line = Con::getReturnBuffer(lineSize + 1);
         memcpy(line, str, lineSize);
         line[lineSize] = 0;

         //Strip the \r from \r\n
         if (lineSize > 0 && line[lineSize - 1] == '\r') {
            line[lineSize - 1] = 0;
         }

         onLine(line);

         if (nextLine) {
            //Strip the \n
            str = nextLine + 1;
         }
      }
   }
}

void HTTPObject::finish(CURLcode errorCode)
{
   bool status = (errorCode == CURLE_OK);
   Con::printf("Request %d finished with %s", getId(), (status ? "success" : "failure"));

   //Get HTTP response code
   long responseCode;
   curl_easy_getinfo(mCurl, CURLINFO_RESPONSE_CODE, &responseCode);
   Con::printf("HTTP Response code: %d", responseCode);

   if (status) {
      //We're done
      processLines();
   } else {
      Con::errorf("Error info: Code %d: %s", errorCode, curl_easy_strerror(errorCode));
   }

   //Clean up
   if (mBuffer) {
      dFree(mBuffer);
   }

   //Then delete the request
   curl_multi_remove_handle(gCurlMulti, mCurl);
   --gCurlMultiTotal;
   curl_easy_cleanup(mCurl);

   //Send a disconnect
   onDisconnect();
}

//--------------------------------------

void HTTPObject::init()
{
   gCurlMulti = curl_multi_init();
}

void HTTPObject::process()
{
   int runningHandles = 0;
   CURLMcode code = curl_multi_perform(gCurlMulti, &runningHandles);
   if (code != CURLM_OK) {
      Con::errorf("curl_multi_perform failed (%d): %s", code, curl_multi_strerror(code));
      return;
   }
   if (runningHandles >= gCurlMultiTotal) {
      return;
   }
   while (true) {
      int queueSize = 0;
      CURLMsg *msg = curl_multi_info_read(gCurlMulti, &queueSize);
      if (!msg) {
         break;
      }
      if (msg->msg != CURLMSG_DONE) {
         continue;
      }
      auto it = gCurlMap.find(msg->easy_handle);
      if (it == gCurlMap.end()) {
         continue;
      }
      it->second->finish(msg->data.result);
      gCurlMap.erase(it);
   }

}

void HTTPObject::shutdown()
{
   curl_multi_cleanup(gCurlMulti);
   gCurlMulti = nullptr;
}

//--------------------------------------

void HTTPObject::setOption(const std::string &option, const std::string &value)
{
   if      (option == "verbose")     { /* opt = new curlpp::options::Verbose(StringMath::scan<bool>(value)); */ }
   else if (option == "user-agent")  { curl_easy_setopt(mCurl, CURLOPT_USERAGENT, value.c_str()); }
   else if (option == "cookie")      { curl_easy_setopt(mCurl, CURLOPT_COOKIE, value.c_str()); }
   else if (option == "verify-peer") { curl_easy_setopt(mCurl, CURLOPT_SSL_VERIFYPEER, value == "true"); }
   else {
      Con::errorf("HTTPObject::setOption unknown option %s", option.c_str());
   }
}

void HTTPObject::setDownloadPath(const std::string &path)
{
   char expanded[0x100];
   Con::expandScriptFilename(expanded, 0x100, path.c_str());
   mDownloadPath = std::string(expanded);
   mDownload = true;
}

void HTTPObject::addHeader(const std::string &name, const std::string &value)
{
   std::string header = name + ": " + value;

   //Formatting: Replace spaces with hyphens
   size_t nameLen = name.size();
   for (U32 i = 0; i < nameLen; i ++) {
      if (header[i] == ' ')
         header[i] = '-';
   }

   mHeaders = curl_slist_append(mHeaders, header.c_str());
}

void HTTPObject::get(const std::string &address, const std::string &uri, const std::string &query)
{
   mUrl = address + uri + (query.empty() ? std::string("") : std::string("?") + query);
   curl_easy_setopt(mCurl, CURLOPT_URL, mUrl.c_str());

   start();
}

void HTTPObject::post(const std::string &address, const std::string &uri, const std::string &query, const std::string &data)
{
   mUrl = address + uri + (query.empty() ? std::string("") : std::string("?") + query);
   curl_easy_setopt(mCurl, CURLOPT_URL, mUrl.c_str());
   mValues = data;

   curl_easy_setopt(mCurl, CURLOPT_POST, true);
   curl_easy_setopt(mCurl, CURLOPT_POSTFIELDS, mValues.c_str());

   start();
}

//--------------------------------------

void HTTPObject::onConnected()
{
   Con::executef(this, "onConnected");
}

void HTTPObject::onConnectFailed()
{
   Con::executef(this, "onConnectFailed");
}

void HTTPObject::onLine(const std::string& line)
{
   Con::executef(this, "onLine", line.c_str());
}

void HTTPObject::onDownload(const std::string& path)
{
   Con::executef(this, "onDownload", path.c_str());
}

void HTTPObject::onDownloadFailed(const std::string& path)
{
   Con::executef(this, "onDownloadFailed", path.c_str());
}

void HTTPObject::onDisconnect()
{
   Con::executef(this, "onDisconncted");
}

//--------------------------------------
DefineEngineMethod(HTTPObject, get, void, (const char* Address, const char* requirstURI, const char* query), (""),
   "@brief Send a GET command to a server to send or retrieve data.\n\n"

   "@param Address HTTP web address to send this get call to. Be sure to include the port at the end (IE: \"www.garagegames.com:80\").\n"
   "@param requirstURI Specific location on the server to access (IE: \"index.php\".)\n"
   "@param query Optional. Actual data to transmit to the server. Can be anything required providing it sticks with limitations of the HTTP protocol. "
   "If you were building the URL manually, this is the text that follows the question mark.  For example: http://www.google.com/ig/api?<b>weather=Las-Vegas,US</b>\n"
   
   "@tsexample\n"
      "// Create an HTTP object for communications\n"
      "%httpObj = new HTTPObject();\n\n"
      "// Specify a URL to transmit to\n"
      "%url = \"www.garagegames.com:80\";\n\n"
      "// Specify a URI to communicate with\n"
      "%URI = \"/index.php\";\n\n"
      "// Specify a query to send.\n"
      "%query = \"\";\n\n"
      "// Send the GET command to the server\n"
      "%httpObj.get(%url,%URI,%query);\n"
   "@endtsexample\n\n")
{
   if(!query || !query[ 0 ])
      object->get(Address, requirstURI, "");
   else
      object->get(Address, requirstURI, query);
}

DefineEngineMethod(HTTPObject, post, void, (const char* Address, const char* requirstURI, const char* query, const char* post),,
   "@brief Send POST command to a server to send or retrieve data.\n\n"

   "@param Address HTTP web address to send this get call to. Be sure to include the port at the end (IE: \"www.garagegames.com:80\").\n"
   "@param requirstURI Specific location on the server to access (IE: \"index.php\".)\n"
   "@param query Actual data to transmit to the server. Can be anything required providing it sticks with limitations of the HTTP protocol. \n"
   "@param post Submission data to be processed.\n"

   "@tsexample\n"
      "// Create an HTTP object for communications\n"
      "%httpObj = new HTTPObject();\n\n"
      "// Specify a URL to transmit to\n"
      "%url = \"www.garagegames.com:80\";\n\n"
      "// Specify a URI to communicate with\n"
      "%URI = \"/index.php\";\n\n"
      "// Specify a query to send.\n"
      "%query = \"\";\n\n"
      "// Specify the submission data.\n"
      "%post = \"\";\n\n"
      "// Send the POST command to the server\n"
      "%httpObj.POST(%url,%URI,%query,%post);\n"
   "@endtsexample\n\n")
{
   object->post(Address, requirstURI, query, post);
}

DefineEngineMethod(HTTPObject, setOption, void, (const char* option, const char* value),, "HTTPObject.setOption(option, value)")
{
   object->setOption(option, value);
}

DefineEngineMethod(HTTPObject, setDownloadPath, void, (const char* path),, "HTTPObject.setDownloadPath(path)")
{
   object->setDownloadPath(path);
}

DefineEngineMethod(HTTPObject, addHeader, void, (const char* name, const char* value),, "HTTPObject.addHeader(name, value)")
{
   object->addHeader(name, value);
}
