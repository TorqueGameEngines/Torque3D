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

#ifdef TORQUE_SHARED

#ifdef WIN32

#include <windows.h>
#include <string>

extern "C"
{
   int (*torque_winmain)( HINSTANCE hInstance, HINSTANCE h, LPSTR lpszCmdLine, int nShow) = NULL;
};

bool getDllName(std::wstring& dllName, const std::wstring& suffix)
{
   wchar_t filenameBuf[MAX_PATH];
   DWORD length = GetModuleFileNameW( NULL, filenameBuf, MAX_PATH );
   if(length == 0) return false;
   dllName = std::wstring(filenameBuf);
   size_t dotPos = dllName.find_last_of(L".");
   if(dotPos == std::wstring::npos)
   {
      dllName.clear();
      return false;
   }
   dllName.erase(dotPos);
   dllName += suffix + L".dll";
   return true;
}

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCommandShow)
{
   // Try to find the game DLL, which may have one of several file names.
   HMODULE hGame = NULL;
   std::wstring dllName = std::wstring();
   // The file name is the same as this executable's name, plus a suffix.
   const std::wstring dllSuffices[] = {L" DLL", L""};
   const unsigned int numSuffices = sizeof(dllSuffices) / sizeof(std::wstring);

   for (unsigned int i = 0; i < numSuffices; i++)
   {
      // Attempt to glue the suffix onto the current filename.
      if(!getDllName(dllName, dllSuffices[i]))
         continue;
      // Load the DLL at that address.
      hGame = LoadLibraryW(dllName.c_str());
      if (hGame)
         break;
   }

   if(!dllName.length())
   {
      MessageBoxW(NULL, L"Unable to find game dll", L"Error",  MB_OK|MB_ICONWARNING);
      return -1;
   }

   enum { errorSize = 4096 };
   if (!hGame)
   {
      wchar_t error[errorSize];
      _swprintf_l(error, errorSize, L"Unable to load game library: %s.  Please make sure it exists and the latest DirectX is installed.", _get_current_locale(), dllName.c_str());
      MessageBoxW(NULL, error, L"Error",  MB_OK|MB_ICONWARNING);
      return -1;
   }

   torque_winmain = (int (*)(HINSTANCE hInstance, HINSTANCE h, LPSTR lpszCmdLine, int nShow))GetProcAddress(hGame, "torque_winmain");
   if (!torque_winmain)
   {
      wchar_t error[errorSize];
      _swprintf_l(error, errorSize, L"Missing torque_winmain export in game library: %s.  Please make sure that it exists and the latest DirectX is installed.", _get_current_locale(), dllName.c_str());
      MessageBoxW(NULL, error, L"Error",  MB_OK|MB_ICONWARNING);
      return -1;
   }

   int ret = torque_winmain(hInstance, hPrevInstance, lpszCmdLine, nCommandShow);

   FreeLibrary(hGame);
   return ret;
}
#endif // WIN32

#ifdef __MACOSX__

#include <dlfcn.h>
#include <stdio.h>
#include <unistd.h>
#include <libgen.h> // for dirname
#include <filesystem>
#include <mach-o/dyld.h> // for _NSGetExecutablePath
#include <Carbon/Carbon.h>

extern "C" {

   int (*torque_macmain)(int argc, const char **argv) = 0;

}  

int main(int argc, const char **argv)
{
   char path[PATH_MAX];
   uint32_t pathLen = sizeof(path);
   int err = _NSGetExecutablePath(path, &pathLen);

   char* executableDirectory = dirname(path);

   // Once the executable directory is determined, we search two possibilities: The frameworks and next to the app bundle
   chdir(executableDirectory);
   chdir("../Frameworks");

   void *gameLib = dlopen("libTorqueEngine.dylib", RTLD_LAZY | RTLD_LOCAL);
   if (!gameLib)
   {
      return -1;
   }

   torque_macmain = (int (*)(int argc, const char **argv)) dlsym(gameLib, "torque_macmain");

   if (!torque_macmain)
      return -2;

   return torque_macmain(argc, argv);
}

#endif // __MACOSX

#ifdef __linux__

#include <dlfcn.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

extern "C"
{
   int (*torque_unixmain)(int argc, const char **argv) = NULL;
   void(*setExePathName)(const char *exePathName) = NULL;
}

int main(int argc, const char **argv)
{
   // assume bin name is in argv[0]
   int len = strlen(argv[0]);
   char *libName = new char[len+4]; // len + .so + NUL

   strcpy(libName, argv[0]);
   strcat(libName, ".so");

   // try to load the game lib
   void *gameLib = dlopen(libName, RTLD_LAZY | RTLD_LOCAL);
   delete [] libName;

   if(gameLib == NULL)
   {
      printf("%s\n", dlerror());
      return -1;
   }

   // set the filename of the exe image
   setExePathName = (void(*)(const char *)) dlsym(gameLib, "setExePathName");
   if(setExePathName == NULL)
   {
      printf("%s\n", dlerror());
      return -1;
   }
   setExePathName(argv[0]);

   // try to load the lib entry point
   torque_unixmain = (int(*)(int argc, const char **argv)) dlsym(gameLib, "torque_unixmain");

   if(torque_unixmain == NULL)
   {
      printf("%s\n", dlerror());
      return -1;
   }

   // Go!
   return torque_unixmain(argc, argv);
}
#endif // __linux__


#else //static exe build

#include "platform/platform.h"
#include "app/mainLoop.h"
#include "T3D/gameFunctions.h"

#if defined(WIN32) || defined(_WIN32)
//tell switchable graphics supported systems that they need to use the beefier GPU
#include <windows.h>
extern "C" { __declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001; }
extern "C" { __declspec(dllexport) DWORD AmdPowerXpressRequestHighPerformance = 0x00000001; }
#else
extern "C" { int NvOptimusEnablement = 1; }
extern "C" { int AmdPowerXpressRequestHighPerformance = 1; }
#endif

// Entry point for your game.
//
// This is build by default using the "StandardMainLoop" toolkit. Feel free
// to bring code over directly as you need to modify or extend things. You
// will need to merge against future changes to the SML code if you do this.
S32 TorqueMain(S32 argc, const char **argv)
{
   // Some handy debugging code:
   //   if (argc == 1) {
   //      static const char* argvFake[] = { "dtest.exe", "-jload", "test.jrn" };
   //      argc = 3;
   //      argv = argvFake;
   //   }

   //   Memory::enableLogging("testMem.log");
   //   Memory::setBreakAlloc(104717);

   // Initialize the subsystems.
   StandardMainLoop::init();

   // Handle any command line args.
   if(!StandardMainLoop::handleCommandLine(argc, argv))
   {
      Platform::AlertOK("Error", "Failed to initialize game, shutting down.");

      return 1;
   }

   // Main loop
   while(StandardMainLoop::doMainLoop());

   // Clean everything up.
   StandardMainLoop::shutdown();

   // Do we need to restart?
   if( StandardMainLoop::requiresRestart() )
      Platform::restartInstance();

   // Return.
   return StandardMainLoop::getReturnStatus();
}

#endif //TORQUE_SHARED
