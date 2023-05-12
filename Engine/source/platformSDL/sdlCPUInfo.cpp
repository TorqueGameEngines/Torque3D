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
// XXTH used for FreeBSD
// Note: SDL_cpuinfo have not all information, but better than using
//       "sysctl hw"
//
//-----------------------------------------------------------------------------
#if defined( __FreeBSD__ )
#include "SDL.h"

#include "platform/platformCPUCount.h"
#include "console/console.h"
#include <math/mMathFn.h>

Platform::SystemInfo_struct Platform::SystemInfo;

void Processor::init()
{

   S32 lCpuCount = SDL_GetCPUCount();
   Platform::SystemInfo.processor.numLogicalProcessors    = lCpuCount;
   //sdl dont have logical/physical CPU count so ... time to guess
   if (lCpuCount > 1)
   {
      Platform::SystemInfo.processor.numPhysicalProcessors = mFloor(lCpuCount / 2); // guessing ;
      Platform::SystemInfo.processor.isMultiCore = true;
      //modern CPU should have isHyperThreaded
      Platform::SystemInfo.processor.isHyperThreaded = true;
   }
   else {
      Platform::SystemInfo.processor.numPhysicalProcessors = lCpuCount; // guessing ;
      Platform::SystemInfo.processor.isMultiCore = false;
      Platform::SystemInfo.processor.isHyperThreaded = false;
   }

   //hackfest
   Platform::SystemInfo.processor.mhz   = 2666;
#if defined(TORQUE_CPU_X64) || defined(TORQUE_CPU_X32)
    // Set sane default information
    Platform::SystemInfo.processor.name  = StringTable->insert("Unknown Processor");
    Platform::SystemInfo.processor.properties |= CPU_PROP_C | CPU_PROP_FPU | CPU_PROP_LE ;
   Platform::SystemInfo.processor.type  = CPU_X86Compatible;

#elif defined(TORQUE_CPU_ARM32) || defined(TORQUE_CPU_ARM64)
    Platform::SystemInfo.processor.type = CPU_ArmCompatible;
    Platform::SystemInfo.processor.name = StringTable->insert("Unknown ARM Processor");
    Platform::SystemInfo.processor.properties = CPU_PROP_C;
#else
#warning Unsupported CPU
#endif
    // Set 64bit flag
#if defined(TORQUE_CPU_X64) || defined(TORQUE_CPU_ARM64)
    Platform::SystemInfo.processor.properties |= CPU_PROP_64bit;
#endif

   Con::printf("Processor Init:");
   Con::printf("      CPU count: %d", lCpuCount);
   Con::printf("      CacheLine size: %d", SDL_GetCPUCacheLineSize());
   if (lCpuCount > 1) {
       Platform::SystemInfo.processor.properties |= CPU_PROP_MP;
       Con::printf("      MultiCore CPU detected" );
   }
   Con::printf("      RAM: %d MB", SDL_GetSystemRAM());
   if (SDL_HasMMX()) {
       Platform::SystemInfo.processor.properties |= CPU_PROP_MMX;
       Con::printf("      MMX detected" );
   }
   if (SDL_HasSSE()) {
       Platform::SystemInfo.processor.properties |= CPU_PROP_SSE;
       Con::printf("      SSE detected" );
   }
   if (SDL_HasSSE2()) {
       Platform::SystemInfo.processor.properties |= CPU_PROP_SSE2;
       Con::printf("      SSE2 detected" );
   }
   if (SDL_HasSSE3()) {
       Platform::SystemInfo.processor.properties |= CPU_PROP_SSE3;
       Con::printf("      SSE3 detected" );
   }
   if (SDL_HasSSE41()) {
       Platform::SystemInfo.processor.properties |= CPU_PROP_SSE4_1;
       Con::printf("      SSE4.1 detected" );
   }
   if (SDL_HasSSE42()) {
       Platform::SystemInfo.processor.properties |= CPU_PROP_SSE4_2;
       Con::printf("      SSE4.2 detected" );
   }
   if (SDL_HasSSE42()) {
       Platform::SystemInfo.processor.properties |= CPU_PROP_SSE4_2;
       Con::printf("      SSE4.2 detected" );
   }
   if (SDL_HasAVX() || SDL_HasAVX2()) {
       Platform::SystemInfo.processor.properties |= CPU_PROP_AVX;
       Con::printf("      AVX detected" );
   }
   if (SDL_HasNEON()) {
       Platform::SystemInfo.processor.properties |= CPU_PROP_NEON;
       Con::printf("      NEON detected" );
   }

   Con::printf(" ");

   SetProcessorInfo(Platform::SystemInfo.processor, "Unknown", "Unknown");

}

namespace CPUInfo
{
    EConfig CPUCount(U32 &logical, U32 &physical)
    {
        // We don't set logical or physical here because it's already been determined by this point
        if (Platform::SystemInfo.processor.isHyperThreaded && Platform::SystemInfo.processor.numPhysicalProcessors == 1)
        {
            return CONFIG_SingleCoreHTEnabled;
        }
        else if (!Platform::SystemInfo.processor.isHyperThreaded && Platform::SystemInfo.processor.numPhysicalProcessors > 1)
        {
            return CONFIG_MultiCoreAndHTNotCapable;
        }
        else if (!Platform::SystemInfo.processor.isHyperThreaded && Platform::SystemInfo.processor.numPhysicalProcessors == 1)
        {
            return CONFIG_SingleCoreAndHTNotCapable;
        }

        return CONFIG_MultiCoreAndHTEnabled;
    }
}; // namespace CPUInfo

#endif // defined( __FreeBSD__ )
