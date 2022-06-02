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
#include "platformWin32/platformWin32.h"
#include "console/console.h"
#include "core/stringTable.h"
#include "platform/platformCPUCount.h"
#include <math.h>
#include <intrin.h>

Platform::SystemInfo_struct Platform::SystemInfo;
extern void PlatformBlitInit();

static void getBrand(char* brand)
{
   S32 extendedInfo[4];
   __cpuid(extendedInfo, 0x80000000);
   S32 numberExtendedIds = extendedInfo[0];

   // Sets brand
   if (numberExtendedIds >= 0x80000004)
   {
      int offset = 0;
      for (int i = 0; i < 3; ++i)
      {
         S32 brandInfo[4];
         __cpuidex(brandInfo, 0x80000002 + i, 0);

         *reinterpret_cast<int*>(brand + offset + 0) = brandInfo[0];
         *reinterpret_cast<int*>(brand + offset + 4) = brandInfo[1];
         *reinterpret_cast<int*>(brand + offset + 8) = brandInfo[2];
         *reinterpret_cast<int*>(brand + offset + 12) = brandInfo[3];

         offset += sizeof(S32) * 4;
      }
   }
}

enum CpuFlags
{
   // EDX Register flags
   BIT_MMX = BIT(23),
   BIT_SSE = BIT(25),
   BIT_SSE2 = BIT(26),
   BIT_3DNOW = BIT(31), // only available for amd cpus in x86

   // These use a different value for comparison than the above flags (ECX Register)
   BIT_SSE3 = BIT(0),
   BIT_SSE3ex = BIT(9),
   BIT_SSE4_1 = BIT(19),
   BIT_SSE4_2 = BIT(20),

   BIT_XSAVE_RESTORE = BIT(27),
   BIT_AVX = BIT(28),
};

static void detectCpuFeatures(Platform::SystemInfo_struct::Processor &processor)
{
   S32 cpuInfo[4];
   __cpuid(cpuInfo, 1);
   U32 eax = cpuInfo[0];   // eax
   U32 edx = cpuInfo[3];  // edx
   U32 ecx = cpuInfo[2]; // ecx

   processor.properties |= (edx & BIT_MMX) ? CPU_PROP_MMX : 0;
   processor.properties |= (edx & BIT_SSE) ? CPU_PROP_SSE : 0;
   processor.properties |= (edx & BIT_SSE2) ? CPU_PROP_SSE2 : 0;
   processor.properties |= (ecx & BIT_SSE3) ? CPU_PROP_SSE3 : 0;
   processor.properties |= (ecx & BIT_SSE3ex) ? CPU_PROP_SSE3ex : 0;
   processor.properties |= (ecx & BIT_SSE4_1) ? CPU_PROP_SSE4_1 : 0;
   processor.properties |= (ecx & BIT_SSE4_2) ? CPU_PROP_SSE4_2 : 0;

   // AVX detection requires that xsaverestore is supported
   if (ecx & BIT_XSAVE_RESTORE && ecx & BIT_AVX)
   {
      bool supportsAVX = _xgetbv(_XCR_XFEATURE_ENABLED_MASK) & 0x6;
      if (supportsAVX)
      {
         processor.properties |= CPU_PROP_AVX;
      }
   }

   if (processor.isMultiCore)
      processor.properties |= CPU_PROP_MP;

#ifdef TORQUE_CPU_X64
   processor.properties |= CPU_PROP_64bit;
#endif
}

void Processor::init()
{
   // Reference:
   //    www.cyrix.com
   //    www.amd.com
   //    www.intel.com
   //       http://developer.intel.com/design/PentiumII/manuals/24512701.pdf

   Platform::SystemInfo.processor.type = CPU_X86Compatible;
   Platform::SystemInfo.processor.name = StringTable->insert("Unknown x86 Compatible");
   Platform::SystemInfo.processor.mhz  = 0;
   Platform::SystemInfo.processor.properties = CPU_PROP_C | CPU_PROP_FPU | CPU_PROP_LE;

   char  vendor[0x20];
   dMemset(vendor, 0, sizeof(vendor));

   S32 vendorInfo[4];
   __cpuid(vendorInfo, 0);
   *reinterpret_cast<int*>(vendor) = vendorInfo[1];     // ebx
   *reinterpret_cast<int*>(vendor + 4) = vendorInfo[3]; // edx
   *reinterpret_cast<int*>(vendor + 8) = vendorInfo[2]; // ecx

   char brand[0x40];
   dMemset(brand, 0, sizeof(brand));
   getBrand(brand);

   SetProcessorInfo(Platform::SystemInfo.processor, vendor, brand);
   detectCpuFeatures(Platform::SystemInfo.processor);

   U32 mhz = 1000; // default if it can't be found

   LONG result;
   DWORD data = 0;
   DWORD dataSize = 4;
   HKEY hKey;

   result = ::RegOpenKeyExA (HKEY_LOCAL_MACHINE,"Hardware\\Description\\System\\CentralProcessor\\0", 0, KEY_QUERY_VALUE, &hKey);

   if (result == ERROR_SUCCESS)
   {
      result = ::RegQueryValueExA (hKey, "~MHz",NULL, NULL,(LPBYTE)&data, &dataSize);

      if (result == ERROR_SUCCESS)
         mhz = data;

      ::RegCloseKey(hKey);
   }

   Platform::SystemInfo.processor.mhz = mhz;

   Con::printf("Processor Init:");
   Con::printf("   Processor: %s", Platform::SystemInfo.processor.name);
   if (Platform::SystemInfo.processor.properties & CPU_PROP_MMX)
      Con::printf("      MMX detected" );
   if (Platform::SystemInfo.processor.properties & CPU_PROP_SSE)
      Con::printf("      SSE detected" );
   if (Platform::SystemInfo.processor.properties & CPU_PROP_SSE2)
      Con::printf("      SSE2 detected" );
   if (Platform::SystemInfo.processor.properties & CPU_PROP_SSE3)
      Con::printf("      SSE3 detected" );
   if (Platform::SystemInfo.processor.properties & CPU_PROP_SSE3ex)
      Con::printf("      SSE3ex detected ");
   if (Platform::SystemInfo.processor.properties & CPU_PROP_SSE4_1)
      Con::printf("      SSE4.1 detected" );
   if (Platform::SystemInfo.processor.properties & CPU_PROP_SSE4_2)
      Con::printf("      SSE4.2 detected" );
   if (Platform::SystemInfo.processor.properties & CPU_PROP_AVX)
      Con::printf("      AVX detected");

   if (Platform::SystemInfo.processor.properties & CPU_PROP_MP)
      Con::printf("   MultiCore CPU detected [%i cores, %i logical]", Platform::SystemInfo.processor.numPhysicalProcessors, Platform::SystemInfo.processor.numLogicalProcessors);

   Con::printf(" ");
   
   PlatformBlitInit();
}
