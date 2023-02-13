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

#ifndef _HTTPOBJECT_H_
#define _HTTPOBJECT_H_

#ifndef _TVECTOR_H_
#include "core/util/tVector.h"
#endif
#ifndef _TCPOBJECT_H_
#include "app/net/tcpObject.h"
#endif

#include <curl/curl.h>
#include <string>
#include <unordered_map>

class HTTPObject : public SimObject
{
private:
   typedef SimObject Parent;
protected:
   CURL *mCurl;
   U8 *mBuffer;
   U32 mBufferSize;
   U32 mBufferUsed;

   std::string mUrl;
   std::string mValues;

   bool mDownload;
   std::string mDownloadPath;

   curl_slist *mHeaders;
   std::unordered_map<std::string, std::string> mRecieveHeaders;

   static CURLM *gCurlMulti;
   static int gCurlMultiTotal;
   static std::unordered_map<CURL *, HTTPObject *> gCurlMap;

   static size_t writeCallback(char *buffer, size_t size, size_t nitems, HTTPObject *object);
   static size_t headerCallback(char *buffer, size_t size, size_t nitems, HTTPObject *object);

   bool ensureBuffer(U32 length);
   size_t processData(char *buffer, size_t size, size_t nitems);
   size_t processHeader(char *buffer, size_t size, size_t nitems);

   void start();
   void processLines();
   void finish(CURLcode errorCode);

   void onConnected();
   void onConnectFailed();
   void onLine(const std::string& line);
   void onDownload(const std::string& path);
   void onDownloadFailed(const std::string& path);
   void onDisconnect();

public:
   HTTPObject();
   ~HTTPObject() override;

   void setOption(const std::string &option, const std::string &value);
   void setDownloadPath(const std::string &path);
   void addHeader(const std::string &name, const std::string &value);

   void get(const std::string &address, const std::string &uri, const std::string &query);
   void post(const std::string &address, const std::string &uri, const std::string &query, const std::string &data);

   static void init();
   static void process();
   static void shutdown();

   DECLARE_CONOBJECT(HTTPObject);
};


#endif  // _H_HTTPOBJECT_
