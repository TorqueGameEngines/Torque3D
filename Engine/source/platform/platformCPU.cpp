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

#include "platform/platform.h"
#include "platform/platformCPUCount.h"
#include "core/strings/stringFunctions.h"
#include "core/stringTable.h"
#include "core/util/tSignal.h"

Signal<void(void)> Platform::SystemInfoReady;

enum CPUFlags
{
   // EDX Register flags
   BIT_RDTSC   = BIT(4),
   BIT_MMX     = BIT(23),
   BIT_SSE     = BIT(25),
   BIT_SSE2    = BIT(26),
   BIT_3DNOW   = BIT(31), // only available for amd cpus in x86

   // These use a different value for comparison than the above flags (ECX Register)
   BIT_SSE3    = BIT(0),
   BIT_SSE3xt  = BIT(9),
   BIT_SSE4_1  = BIT(19),
   BIT_SSE4_2  = BIT(20),
};

// fill the specified structure with information obtained from asm code
void SetProcessorInfo(Platform::SystemInfo_struct::Processor& pInfo,
   char* vendor, char* brand, U32 processor, U32 properties, U32 properties2)
{
   // always assume FPU is available in 2021...
   pInfo.properties |= CPU_PROP_FPU;

#if defined(TORQUE_CPU_X86) || defined(TORQUE_CPU_X64) || defined(TORQUE_CPU_ARM64)
   pInfo.properties |= CPU_PROP_LE;
#endif

#if defined(TORQUE_CPU_X64) || defined(TORQUE_CPU_ARM64)
   pInfo.properties |= CPU_PROP_64bit;
#endif

#if defined(TORQUE_CPU_X86) || defined(TORQUE_CPU_X64)
   pInfo.properties |= (properties & BIT_RDTSC)   ? CPU_PROP_RDTSC : 0;
   pInfo.properties |= (properties & BIT_MMX)     ? CPU_PROP_MMX : 0;
   pInfo.properties |= (properties & BIT_SSE)     ? CPU_PROP_SSE : 0;
   pInfo.properties |= (properties & BIT_SSE2)    ? CPU_PROP_SSE2 : 0;
   pInfo.properties |= (properties2 & BIT_SSE3)   ? CPU_PROP_SSE3 : 0;
   pInfo.properties |= (properties2 & BIT_SSE3xt) ? CPU_PROP_SSE3xt : 0;
   pInfo.properties |= (properties2 & BIT_SSE4_1) ? CPU_PROP_SSE4_1 : 0;
   pInfo.properties |= (properties2 & BIT_SSE4_2) ? CPU_PROP_SSE4_2 : 0;
#endif

   if (dStricmp(vendor, "GenuineIntel") == 0)
   {
      pInfo.type = CPU_Intel;
      pInfo.name = StringTable->insert(brand ? brand : "Intel (Unknown)");
   }
   //--------------------------------------
   else if (dStricmp(vendor, "AuthenticAMD") == 0)
   {
      pInfo.name = StringTable->insert(brand ? brand : "AMD (unknown)");
      pInfo.type = CPU_AMD;

      // 3dnow! is only available in AMD cpus on x86. Otherwise its not reliably set.
      pInfo.properties |= (properties & BIT_3DNOW) ? CPU_PROP_3DNOW : 0;
   }
   else if (dStricmp(vendor, "Apple") == 0)
   {
      pInfo.name = StringTable->insert(brand ? brand : "Apple (unknown)");
      pInfo.type = CPU_Apple;
   }
   else
   {
#if defined(TORQUE_CPU_X86) || defined(TORQUE_CPU_X64)
      pInfo.name = StringTable->insert(brand ? brand : "x86 Compatible (unknown)");
      pInfo.type = CPU_X86Compatible;
#elif defined(TORQUE_CPU_ARM64)
      pInfo.name = StringTable->insert(brand ? brand : "Arm Compatible (unknown)");
      pInfo.type = CPU_ArmCompatible;
#else
#error "Unknown CPU Architecture"
#endif
   }

   // Get multithreading caps.
   CPUInfo::EConfig config = CPUInfo::CPUCount( pInfo.numLogicalProcessors, pInfo.numAvailableCores, pInfo.numPhysicalProcessors );
   pInfo.isHyperThreaded = CPUInfo::isHyperThreaded( config );
   pInfo.isMultiCore = CPUInfo::isMultiCore( config );

   // Trigger the signal
   Platform::SystemInfoReady.trigger();
}
