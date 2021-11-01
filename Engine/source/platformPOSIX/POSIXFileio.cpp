#include "core/fileio.h"
#include "core/util/tVector.h"
#include "core/stringTable.h"
#include "console/console.h"
#include "core/strings/stringFunctions.h"
#include "util/tempAlloc.h"
#include "cinterface/c_controlInterface.h"
#include "core/volume.h"

/* these are for reading directors, getting stats, etc. */
#include <dirent.h>
#include <sys/stat.h>

const int MaxPath = PATH_MAX;

//------------------------------------------------------------------------------
// munge the case of the specified pathName.  This means try to find the actual
// filename in with case-insensitive matching on the specified pathName, and
// store the actual found name.
bool ResolvePathCaseInsensitive(char* pathName, S32 pathNameSize, bool requiredAbsolute)
{
    char tempBuf[MaxPath];
    dStrncpy(tempBuf, pathName, pathNameSize);

    // Check if we're an absolute path
    if (pathName[0] != '/')
    {
        AssertFatal(!requiredAbsolute, "PATH must be absolute");
        return false;
    }

    struct stat filestat;
    const int MaxPathEl = 200;
    char *currChar = pathName;
    char testPath[MaxPath];
    char pathEl[MaxPathEl];
    bool done = false;
    bool foundMatch = false;

    dStrncpy(tempBuf, "/", MaxPath);
    currChar++;

    while (!done)
    {
        char* termChar = dStrchr(currChar, '/');
        if (termChar == NULL)
            termChar = dStrchr(currChar, '\0');
        AssertFatal(termChar, "Can't find / or NULL terminator");

        S32 pathElLen = (termChar - currChar);
        dStrncpy(pathEl, currChar, pathElLen);
        pathEl[pathElLen] = '\0';
        dStrncpy(testPath, tempBuf, MaxPath);
        dStrcat(testPath, pathEl, MaxPath);
        if (stat(testPath, &filestat) != -1)
        {
            dStrncpy(tempBuf, testPath, MaxPath);
        }
        else
        {
            DIR *dir = opendir(tempBuf);
            struct dirent* ent;
            while (dir != NULL && (ent = readdir(dir)) != NULL)
            {
                if (dStricmp(pathEl, ent->d_name) == 0)
                {
                    foundMatch = true;
                    dStrcat(tempBuf, ent->d_name, MaxPath);
                    break;
                }
            }

            if (!foundMatch)
                dStrncpy(tempBuf, testPath, MaxPath);
            if (dir)
                closedir(dir);
        }
        if (*termChar == '/')
        {
            dStrcat(tempBuf, "/", MaxPath);
            termChar++;
            currChar = termChar;
        }
        else
            done = true;
    }

    dStrncpy(pathName, tempBuf, pathNameSize);
    return foundMatch;
}