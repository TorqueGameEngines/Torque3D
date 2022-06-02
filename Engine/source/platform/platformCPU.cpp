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

// fill the specified structure with information obtained from asm code
void SetProcessorInfo(Platform::SystemInfo_struct::Processor& pInfo, const char* vendor, const char* brand)
{
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
   CPUInfo::EConfig config = CPUInfo::CPUCount( pInfo.numLogicalProcessors, pInfo.numPhysicalProcessors );
   pInfo.isHyperThreaded = CPUInfo::isHyperThreaded( config );
   pInfo.isMultiCore = CPUInfo::isMultiCore( config );

   // Trigger the signal
   Platform::SystemInfoReady.trigger();
}