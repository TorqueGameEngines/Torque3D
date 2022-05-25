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

#import <sys/types.h>
#import <sys/sysctl.h>
#import <mach/machine.h>
#import <math.h>
#import <CoreServices/CoreServices.h>

#import "platform/platformAssert.h"
#import "console/console.h"
#import "core/stringTable.h"
#import "platform/platformCPUCount.h"

// Gestalt has been deprecated
// we now have to use NSProcessInfo
#import <Foundation/Foundation.h>

// Original code by Sean O'Brien (http://www.garagegames.com/community/forums/viewthread/81815).


// Reads sysctl() string value into buffer at DEST with maximum length MAXLEN
// Return: 0 on success, non-zero is error in accordance with stdlib and <errno.h>
int _getSysCTLstring(const char key[], char * dest, size_t maxlen) {
	size_t len = 0;
	int err;
	// Call with NULL for 'dest' to have the required size stored in 'len'. If the 'key'
	// doesn't exist, 'err' will be -1 and if all goes well, it will be 0.
	err = sysctlbyname(key, NULL, &len, NULL, 0);
	if (err == 0) {
		AssertWarn((len <= maxlen), ("Insufficient buffer length for SYSCTL() read. Truncating.\n"));
		if (len > maxlen)
			len = maxlen;
		// Call with actual pointers to 'dest' and clamped 'len' fields to perform the read.
		err = sysctlbyname(key, dest, &len, NULL, 0);
	}
	return err;
}

// TEMPLATED Reads sysctl() integer value into variable DEST of type T
// The two predominant types used are unsigned longs and unsiged long longs
// and the size of the argument is on a case-by-case value. As a "guide" the
// resources at Apple claim that any "byte count" or "frequency" values will
// be returned as ULL's and most everything else will be UL's.
// Return: 0 on success, non-zero is error in accordance with stdlib and <errno.h>
template <typename T>
int _getSysCTLvalue(const char key[], T * dest) {
	size_t len = 0;
	int err;
	// Call with NULL for 'dest' to get the size. If the 'key' doesn't exist, the
	// 'err' returned will be -1, so 0 indicates success.
	err = sysctlbyname(key, NULL, &len, NULL, 0);
	if (err == 0) {
		AssertFatal((len == sizeof(T)), "Mis-matched destination type for SYSCTL() read.\n");
		// We're just double-checking that we're being called with the correct type of
		// pointer for 'dest' so we don't clobber anything nearby when writing back.
		err = sysctlbyname(key, dest, &len, NULL, 0);
	}
	return err;
}

Platform::SystemInfo_struct Platform::SystemInfo;

#define BASE_MHZ_SPEED 1000
#define BASE_APPLE_SILICON_MHZ_SPEED 3200

static void detectCpuFeatures(U32 &procflags)
{
   // Now we can directly query the system about a litany of "Optional" processor capabilities
   // and determine the status by using BOTH the 'err' value and the 'lraw' value. If we request
   // a non-existant feature from SYSCTL(), the 'err' result will be -1; 0 denotes it exists
   // >>>> BUT <<<<<
   // it may not be supported, only defined. Thus we need to check 'lraw' to determine if it's
   // actually supported/implemented by the processor: 0 = no, 1 = yes, others are undefined.
   
   int err;
   U32 lraw;
   
   // All Cpus have fpu
   procflags = CPU_PROP_C | CPU_PROP_FPU;
   
#if defined(TORQUE_CPU_X86) || defined(TORQUE_CPU_X64)
   
   // List of chip-specific features
   err = _getSysCTLvalue<U32>("hw.optional.mmx", &lraw);
   if ((err==0)&&(lraw==1))
      procflags |= CPU_PROP_MMX;
   err = _getSysCTLvalue<U32>("hw.optional.sse", &lraw);
   if ((err==0)&&(lraw==1))
      procflags |= CPU_PROP_SSE;
   err = _getSysCTLvalue<U32>("hw.optional.sse2", &lraw);
   if ((err==0)&&(lraw==1))
      procflags |= CPU_PROP_SSE2;
   err = _getSysCTLvalue<U32>("hw.optional.sse3", &lraw);
   if ((err==0)&&(lraw==1))
      procflags |= CPU_PROP_SSE3;
   err = _getSysCTLvalue<U32>("hw.optional.supplementalsse3", &lraw);
   if ((err==0)&&(lraw==1))
      procflags |= CPU_PROP_SSE3ex;
   err = _getSysCTLvalue<U32>("hw.optional.sse4_1", &lraw);
   if ((err==0)&&(lraw==1))
      procflags |= CPU_PROP_SSE4_1;
   err = _getSysCTLvalue<U32>("hw.optional.sse4_2", &lraw);
   if ((err==0)&&(lraw==1))
      procflags |= CPU_PROP_SSE4_2;
   err = _getSysCTLvalue<U32>("hw.optional.avx1_0", &lraw);
   if ((err==0)&&(lraw==1))
      procflags |= CPU_PROP_AVX;
   
#elif defined(TORQUE_CPU_ARM64)
   
   err = _getSysCTLvalue<U32>("hw.optional.neon", &lraw);
   if ((err==0)&&(lraw==1))
      procflags |= CPU_PROP_NEON;
   
#endif

   err = _getSysCTLvalue<U32>("hw.ncpu", &lraw);
   if ((err==0)&&(lraw>1))
      procflags |= CPU_PROP_MP;
   err = _getSysCTLvalue<U32>("hw.cpu64bit_capable", &lraw);
   if ((err==0)&&(lraw==1))
      procflags |= CPU_PROP_64bit;
   err = _getSysCTLvalue<U32>("hw.byteorder", &lraw);
   if ((err==0)&&(lraw==1234))
      procflags |= CPU_PROP_LE;
}

void Processor::init()
{
	U32 procflags = 0;
	int err, cpufam, cputype, cpusub;
	char buf[255];
	U32 lraw;
	U64 llraw;

   // Availability: Mac OS 10.2 or greater.
   NSString *osVersionStr = [[NSProcessInfo processInfo] operatingSystemVersionString];

   S32 ramMB;
	err = _getSysCTLvalue<U64>("hw.memsize", &llraw);
	if (err)
      ramMB = 512;
	else
      ramMB = llraw >> 20;
	
   char brandString[256];
   err = _getSysCTLstring("machdep.cpu.brand_string", brandString, sizeof(brandString));
   if (err)
      brandString[0] = '\0';
   
   char vendor[256];
   err = _getSysCTLstring("machdep.cpu.vendor", vendor, sizeof(vendor));
   if (err)
      vendor[0] = '\0';
   
   // Note: hw.cpufrequency seems to be missing on the M1. For Apple Silicon,
   // we will assume the base frequency of the M1 which is 3.2ghz
	err = _getSysCTLvalue<U64>("hw.cpufrequency", &llraw);
	if (err) {
#if defined(TORQUE_CPU_ARM64)
      llraw = BASE_APPLE_SILICON_MHZ_SPEED;
#else
		llraw = BASE_MHZ_SPEED;
#endif
	} else {
		llraw /= 1000000;
	}
	Platform::SystemInfo.processor.mhz = (unsigned int)llraw;
	
   detectCpuFeatures(procflags);
   
   Platform::SystemInfo.processor.properties = procflags;
   SetProcessorInfo(Platform::SystemInfo.processor, vendor, brandString);
   
   
   Con::printf("System & Processor Information:");
   Con::printf("   MacOS Version: %s", [osVersionStr UTF8String]);
   Con::printf("   Physical memory installed: %d MB", ramMB);
   Con::printf("   Processor: %s", Platform::SystemInfo.processor.name);
	if (Platform::SystemInfo.processor.properties & CPU_PROP_MMX)
		Con::printf("      MMX detected");
	if (Platform::SystemInfo.processor.properties & CPU_PROP_SSE)
		Con::printf("      SSE detected");
	if (Platform::SystemInfo.processor.properties & CPU_PROP_SSE2)
		Con::printf("      SSE2 detected");
	if (Platform::SystemInfo.processor.properties & CPU_PROP_SSE3)
		Con::printf("      SSE3 detected");
   if (Platform::SystemInfo.processor.properties & CPU_PROP_SSE3ex)
      Con::printf("      SSE3ex detected");
	if (Platform::SystemInfo.processor.properties & CPU_PROP_SSE4_1)
		Con::printf("      SSE4.1 detected");
	if (Platform::SystemInfo.processor.properties & CPU_PROP_SSE4_2)
		Con::printf("      SSE4.2 detected");
   if (Platform::SystemInfo.processor.properties & CPU_PROP_AVX)
      Con::printf("      AVX detected");
	if (Platform::SystemInfo.processor.properties & CPU_PROP_NEON)
      Con::printf("      Neon detected");

   if (Platform::SystemInfo.processor.properties & CPU_PROP_MP)
      Con::printf("   MultiCore CPU detected [%i cores, %i logical]", Platform::SystemInfo.processor.numPhysicalProcessors, Platform::SystemInfo.processor.numLogicalProcessors);
   
	Con::printf( "" );
   
   // Trigger the signal
   Platform::SystemInfoReady.trigger();
}


namespace CPUInfo {
   EConfig CPUCount(U32 &logical, U32 &physical) {
      U32 lraw;
      int err;
      
      err = _getSysCTLvalue<U32>("hw.physicalcpu", &lraw);
      if (err == 0)
         physical = lraw;
      else
         physical = 1;
      
      err = _getSysCTLvalue<U32>("hw.logicalcpu", &lraw);
      if (err == 0)
      {
         logical = lraw;
      }
      else
      {
         // fallback to querying the number of cpus. If that fails, then assume same as number of cores
         err = _getSysCTLvalue<U32>("hw.ncpu", &lraw);
         if (err == 0)
            logical = lraw;
         else
            logical = physical;
      }
      
      const bool smtEnabled = logical > physical;
      
      if (physical == 1)
         return smtEnabled ? CONFIG_SingleCoreHTEnabled : CONFIG_SingleCoreAndHTNotCapable;
      
      return smtEnabled ? CONFIG_MultiCoreAndHTEnabled : CONFIG_MultiCoreAndHTNotCapable;
   }
}
