#include "platform/platform.h"
#include <SDL.h>
bool Platform::openWebBrowser(const char* webAddress)
{
#if defined(TORQUE_SDL)
   SDL_OpenURL(webAddress);
   return true;
#endif
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

#ifdef TORQUE_DEDICATED
// XA: New class for the unix unicode font
class PlatformFont;
PlatformFont *createPlatformFont(const char *name, dsize_t size, U32 charset /* = TGE_ANSI_CHARSET */) { return NULL; }
#endif
