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

#include "platform/platformMemory.h"
#include "console/dynamicTypes.h"
#include "console/engineAPI.h"
#include "core/stream/fileStream.h"
#include "core/strings/stringFunctions.h"
#include "console/console.h"
#include "platform/profiler.h"
#include "platform/threads/mutex.h"
#include "core/module.h"

#ifdef _WIN32
#include <windows.h>
#include <dbghelp.h>
#pragma comment(lib, "Dbghelp.lib")
#else
#include <execinfo.h>
#endif
#include <ctime>
#include <string>

// If profile paths are enabled, disable profiling of the
// memory manager as that would cause a cyclic dependency
// through the string table's allocation stuff used by the
// profiler (talk about a long sentence...)

#ifdef TORQUE_ENABLE_PROFILE_PATH
#  undef PROFILE_START
#  undef PROFILE_END
#  undef PROFILE_SCOPE
#  define PROFILE_START( x )
#  define PROFILE_END()
#  define PROFILE_SCOPE( x )
#endif

#ifdef TORQUE_MULTITHREAD
void* gMemMutex = NULL;
#endif
   
//-------------------------------------- Make sure we don't have the define set
#ifdef new
#undef new
#endif

//---------------------------------------------------------------------------

namespace Memory
{
#if !defined(TORQUE_DISABLE_MEMORY_MANAGER)


   static const U32 MaxAllocs = 10240;
   static MemInfo allocList[MaxAllocs];
   static U32 allocCount = 0;
   static U32 currentAllocId = 0;
   static bool initialized = false;
   char gLogFilename[256] = { 0 };
   bool gStackTrace = true;
   bool gFromScript = false;

   struct memReport
   {
      std::string report;
      bool skip;
      U32 count = 1;
      U32 total = 0;
   } memLog[MaxAllocs];

   void init()
   {
      if (initialized) return;
      std::memset(allocList, 0, sizeof(allocList));
      allocCount = 0;
      currentAllocId = 0;
      initialized = true;

      // Generate timestamped log filename
      std::time_t now = std::time(nullptr);
      std::tm* localTime = std::localtime(&now);
      std::strftime(gLogFilename, sizeof(gLogFilename), "memlog_%Y-%m-%d_%H-%M-%S.txt", localTime);
   }

   void shutdown()
   {
      if (!initialized) return;

      FILE* log = std::fopen(gLogFilename, "w");
      if (!log)
         return;

      std::fprintf(log, "\n--- Memory Leak Report ---\n");

      U32 start = 0;
      U32 stop = allocCount;
      if (gFromScript) //filter out the bits from console
      {
         start = 6;
         stop = allocCount - 8;
      }
      for (U32 curRep = start; curRep < stop; ++curRep)
      {
         if (allocList[curRep].ptr != nullptr)
         {
            char entry[512] = "";
            std::sprintf(entry, "from %s:%u\n", allocList[curRep].file ? allocList[curRep].file : "(null)", allocList[curRep].line);

            memLog[curRep].skip = false;
            std::string report = entry;

            if (gStackTrace)
            {
               char stack[512] = "";
#ifdef _WIN32
               SYMBOL_INFO* symbol = (SYMBOL_INFO*)malloc(sizeof(SYMBOL_INFO) + 256);
               symbol->MaxNameLen = 255;
               symbol->SizeOfStruct = sizeof(SYMBOL_INFO);

               HANDLE process = GetCurrentProcess();
               SymInitialize(process, NULL, TRUE);

               for (int curStack = 0; curStack < allocList[curRep].backtraceSize; ++curStack)
               {
                  DWORD64 addr = (DWORD64)(allocList[curRep].backtracePtrs[curStack]);
                  if (SymFromAddr(process, addr, 0, symbol))
                  {
                     std::sprintf(stack, "  [%d] %s - 0x%0llX\n", curStack, symbol->Name, symbol->Address);
                  }
                  else
                  {
                     std::sprintf(stack, "  [%d] ??? - 0x%0llX\n", curStack, addr);
                  }
                  report += stack;
               }

               std::free(symbol);
#else
               char** symbols = backtrace_symbols(allocList[curRep].backtracePtrs, allocList[i].backtraceSize);
               for (int curStack = 0; curStack < allocList[curRep].backtraceSize; ++curStack)
               {
                  std::sprintf(stack, "  [%d] %s\n", curStack, symbols[curStack]);
                  report += stack;
               }
               std::free(symbols);
#endif
            }

            if (report.find("getDocsLink") != std::string::npos)
            {
               //known issue. one off allocation
               memLog[curRep].skip = true;
            }

            for (U32 oldRep = start; oldRep < curRep; ++oldRep)
            {
               if (!memLog[oldRep].skip && (memLog[oldRep].report.find(report) != std::string::npos))
               {
                  //inc origional
                  memLog[oldRep].count++;
                  memLog[oldRep].total += allocList[curRep].size;
                  //skip dupe report
                  memLog[curRep].skip = true;
               }
            }
            if (!memLog[curRep].skip)
            {
               memLog[curRep].report = report;
               memLog[curRep].count = 1;
               memLog[curRep].total = allocList[curRep].size;
            }
         }
      }

      for (U32 ntry = start; ntry < stop; ++ntry)
      {
         if (!memLog[ntry].skip)
         {
            std::fprintf(log, "Leak-count[%i]total[%i]:%s", memLog[ntry].count, memLog[ntry].total, memLog[ntry].report.c_str());
            memLog[ntry].report.clear();
         }
      }

      std::fclose(log);
      initialized = false;
   }

   void checkPtr(void* ptr)
   {
      for (U32 i = 0; i < allocCount; ++i)
         if (allocList[i].ptr == ptr)
            return;

      Platform::debugBreak();
   }

   static void* alloc(dsize_t size, bool array, const char* fileName, U32 line)
   {
      if (size == 0)
         return nullptr;

      void* ptr = std::malloc(size);
      if (!ptr)
         return nullptr;

      if (!initialized || allocCount >= MaxAllocs)
         return ptr;

      MemInfo& info = allocList[allocCount++];
      info.ptr = ptr;
      info.size = size;
      info.file = fileName ? fileName : "unknown";
      info.line = line;
      info.allocId = currentAllocId++;
      info.flagged = false;

      if (gStackTrace)
      {
#ifdef _WIN32
         info.backtraceSize = CaptureStackBackTrace(0, 16, info.backtracePtrs, nullptr);
#else
         info.backtraceSize = backtrace(info.backtracePtrs, MaxBacktraceDepth);
#endif
      }

      return ptr;
   }

   static void free(void* ptr, bool array)
   {
      if (!ptr || !initialized)
         return;


      for (U32 i = 0; i < allocCount; ++i)
      {
         if (allocList[i].ptr == ptr)
         {
            std::free(ptr);
            allocList[i] = allocList[allocCount - 1];
            allocList[--allocCount] = {};
            return;
         }
      }

      // Unknown pointer, still free it.
      std::free(ptr);
   }

   void getMemoryInfo(void* ptr, MemInfo& info)
   {
      if (!ptr || !initialized)
         return;

      for (U32 i = 0; i < allocCount; ++i)
      {
         if (allocList[i].ptr == ptr)
         {
            info = allocList[i];
            return;
         }
      }
   }

   static void* realloc(void* oldPtr, dsize_t newSize, const char* fileName, U32 line)
   {
      if (!initialized)
         return std::realloc(oldPtr, newSize); // fallback if not tracking

      if (newSize == 0)
      {
         free(oldPtr, false);
         return nullptr;
      }

      if (oldPtr == nullptr)
         return alloc(newSize, false, fileName, line);


      void* newPtr = std::realloc(oldPtr, newSize);
      if (!newPtr)
         return nullptr;


      // Update existing record
      for (U32 i = 0; i < allocCount; ++i)
      {
         if (allocList[i].ptr == oldPtr)
         {
            allocList[i].ptr = newPtr;
            allocList[i].size = newSize;
            allocList[i].file = fileName;
            allocList[i].line = line;
            allocList[i].allocId = currentAllocId++;
            return newPtr;
         }
      }

      // Not found — see if newPtr is already being tracked
      for (U32 i = 0; i < allocCount; ++i)
      {
         if (allocList[i].ptr == newPtr)
         {
            allocList[i].size = newSize;
            allocList[i].file = fileName;
            allocList[i].line = line;
            allocList[i].allocId = currentAllocId++;

            return newPtr;
         }
      }

      // Still not found — treat as a new allocation
      if (allocCount < MaxAllocs)
      {
         MemInfo& info = allocList[allocCount++];
         info = {};
         info.ptr = newPtr;
         info.size = newSize;
         info.file = fileName;
         info.line = line;
         info.allocId = currentAllocId++;
      }
      return newPtr;
   }

#endif
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

#if !defined(TORQUE_DISABLE_MEMORY_MANAGER)

// Manage our own memory, add overloaded memory operators and functions

void* FN_CDECL operator new(dsize_t size, const char* fileName, const U32 line)
{
   return Memory::alloc(size, false, fileName, line);
}

void* FN_CDECL operator new[](dsize_t size, const char* fileName, const U32 line)
{
   return Memory::alloc(size, true, fileName, line);
}

void* FN_CDECL operator new(dsize_t size)
{
   return Memory::alloc(size, false, NULL, 0);
}

void* FN_CDECL operator new[](dsize_t size)
{
   return Memory::alloc(size, true, NULL, 0);
}

void FN_CDECL operator delete(void* mem)
{
   Memory::free(mem, false);
}

void FN_CDECL operator delete[](void* mem)
{
   Memory::free(mem, true);
}

void* dMalloc_r(dsize_t in_size, const char* fileName, const dsize_t line)
{
   return Memory::alloc(in_size, false, fileName, line);
}

void dFree(void* in_pFree)
{
   Memory::free(in_pFree, false);
}

void* dRealloc_r(void* in_pResize, dsize_t in_size, const char* fileName, const dsize_t line)
{
   return Memory::realloc(in_pResize, in_size, fileName, line);
}

DefineEngineFunction(LeakTrace, void, (bool start, bool stackTrace), (true, true), "start/stop tracing leaks")
{
   if (Memory::initialized) Memory::shutdown();
   if (start) Memory::init();
   Memory::gFromScript = true;
   Memory::gStackTrace = stackTrace;
}

#else

// Don't manage our own memory
void* dMalloc_r(dsize_t in_size, const char* fileName, const dsize_t line)
{
   return malloc(in_size);
}

void dFree(void* in_pFree)
{
   free(in_pFree);
}

void* dRealloc_r(void* in_pResize, dsize_t in_size, const char* fileName, const dsize_t line)
{
   return realloc(in_pResize,in_size);
}

#endif
