#include "platform/platform.h"
#ifndef TORQUE_SDL
bool Platform::openWebBrowser(const char* webAddress)
{
   String startingURL(webAddress);
   String filteredURL;

   U32 length = startingURL.length();
   for(U32 i = 0; i < length; i++)
   {
      filteredURL = filteredURL + '\\' + startingURL[i];
   }

   String runCommand = "URL=" + filteredURL + "; xdg-open $URL > /dev/null 2> /dev/null";

   S32 statusCode;
   statusCode = system(runCommand.c_str());

   if(statusCode == 0)
   {
      return true;
   }

   return false;
}
#endif
#ifdef TORQUE_DEDICATED
// XA: New class for the unix unicode font
class PlatformFont;
PlatformFont *createPlatformFont(const char *name, dsize_t size, U32 charset /* = TGE_ANSI_CHARSET */) { return NULL; }
#endif
