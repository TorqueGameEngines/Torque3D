#include "platform/platform.h"
#include <string>

bool Platform::openWebBrowser( const char* webAddress )
{
    std::string startingURL(webAddress);
    std::string filteredURL;

    unsigned short length = startingURL.length();
    for(unsigned short i = 0; i < length; i++)
    {
        filteredURL = filteredURL + '\\' + startingURL.at(i);
    }

    std::string runCommand = "URL=" + filteredURL + "; xdg-open $URL > /dev/null 2> /dev/null";

    short statusCode;
    statusCode = system(runCommand.c_str());

    if(statusCode == 0)
        return true;

    return false;
}

#ifdef TORQUE_DEDICATED
// XA: New class for the unix unicode font
class PlatformFont;
PlatformFont *createPlatformFont(const char *name, dsize_t size, U32 charset /* = TGE_ANSI_CHARSET */) { return NULL; }
#endif
