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
#include <math.h>
#include <intrin.h>

Platform::SystemInfo_struct Platform::SystemInfo;
extern void PlatformBlitInit();
extern void SetProcessorInfo(Platform::SystemInfo_struct::Processor& pInfo,
   char* vendor, U32 processor, U32 properties, U32 properties2); // platform/platformCPU.cc

void Processor::init()
{
   // Reference:
   //    www.cyrix.com
   //    www.amd.com
   //    www.intel.com
   //       http://developer.intel.com/design/PentiumII/manuals/24512701.pdf

   Con::printf("Processor Init:");

   Platform::SystemInfo.processor.type = CPU_X86Compatible;
   Platform::SystemInfo.processor.name = StringTable->insert("Unknown x86 Compatible");
   Platform::SystemInfo.processor.mhz  = 0;
   Platform::SystemInfo.processor.properties = CPU_PROP_C | CPU_PROP_LE;

   char  vendor[0x20];
   dMemset(vendor, 0, sizeof(vendor));
   U32   properties = 0;
   U32   processor  = 0;
   U32   properties2 = 0;

   S32 vendorInfo[4];
   __cpuid(vendorInfo, 0);
   *reinterpret_cast<int*>(vendor) = vendorInfo[1];     // ebx
   *reinterpret_cast<int*>(vendor + 4) = vendorInfo[3]; // edx
   *reinterpret_cast<int*>(vendor + 8) = vendorInfo[2]; // ecx

   S32 cpuInfo[4];
   __cpuid(cpuInfo, 1);
   processor = cpuInfo[0];   // eax
   properties = cpuInfo[3];  // edx
   properties2 = cpuInfo[2]; // ecx

   SetProcessorInfo(Platform::SystemInfo.processor, vendor, processor, properties, properties2);

// now calculate speed of processor...
   U32 nearmhz = 0; // nearest rounded mhz
   U32 mhz = 0; // calculated value.

   LONG result;
   DWORD data = 0;
   DWORD dataSize = 4;
   HKEY hKey;

   result = ::RegOpenKeyExA (HKEY_LOCAL_MACHINE,"Hardware\\Description\\System\\CentralProcessor\\0", 0, KEY_QUERY_VALUE, &hKey);

   if (result == ERROR_SUCCESS)
   {
      result = ::RegQueryValueExA (hKey, "~MHz",NULL, NULL,(LPBYTE)&data, &dataSize);

      if (result == ERROR_SUCCESS)
         nearmhz = mhz = data;

      ::RegCloseKey(hKey);
   }

   Platform::SystemInfo.processor.mhz = mhz;

   if (mhz==0)
   {
      Con::printf("   %s, (Unknown) Mhz", Platform::SystemInfo.processor.name);
      // stick SOMETHING in so it isn't ZERO.
      Platform::SystemInfo.processor.mhz = 200; // seems a decent value.
   }
   else
   {
      if (nearmhz >= 1000)
         Con::printf("   %s, ~%.2f Ghz", Platform::SystemInfo.processor.name, ((float)nearmhz)/1000.0f);
      else
         Con::printf("   %s, ~%d Mhz", Platform::SystemInfo.processor.name, nearmhz);
      if (nearmhz != mhz)
      {
         if (mhz >= 1000)
            Con::printf("     (timed at roughly %.2f Ghz)", ((float)mhz)/1000.0f);
         else
            Con::printf("     (timed at roughly %d Mhz)", mhz);
      }
   }

   if( Platform::SystemInfo.processor.numAvailableCores > 0
       || Platform::SystemInfo.processor.numPhysicalProcessors > 0
       || Platform::SystemInfo.processor.isHyperThreaded )
      Platform::SystemInfo.processor.properties |= CPU_PROP_MP;

   if (Platform::SystemInfo.processor.properties & CPU_PROP_FPU)
      Con::printf( "   FPU detected" );
   if (Platform::SystemInfo.processor.properties & CPU_PROP_MMX)
      Con::printf( "   MMX detected" );
   if (Platform::SystemInfo.processor.properties & CPU_PROP_3DNOW)
      Con::printf( "   3DNow detected" );
   if (Platform::SystemInfo.processor.properties & CPU_PROP_SSE)
      Con::printf( "   SSE detected" );
   if( Platform::SystemInfo.processor.properties & CPU_PROP_SSE2 )
      Con::printf( "   SSE2 detected" );
   if( Platform::SystemInfo.processor.isHyperThreaded )
      Con::printf( "   HT detected" );
   if( Platform::SystemInfo.processor.properties & CPU_PROP_MP )
      Con::printf( "   MP detected [%i cores, %i logical, %i physical]",
         Platform::SystemInfo.processor.numAvailableCores,
         Platform::SystemInfo.processor.numLogicalProcessors,
         Platform::SystemInfo.processor.numPhysicalProcessors );
   Con::printf(" ");
   
   PlatformBlitInit();
}
