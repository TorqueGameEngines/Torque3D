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

#ifndef __APPLE__

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "platform/platform.h"
#include "platformPOSIX/platformPOSIX.h"
#include "platform/platformCPUCount.h"

#include "console/console.h"

#include <unistd.h>

Platform::SystemInfo_struct Platform::SystemInfo;

static inline void rtrim(std::string &s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
}

static inline void ltrim(std::string &s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
}

static void getCPUInformation()
{
    std::string vendorString;
    std::string brandString;

    std::ifstream cpuInfo("/proc/cpuinfo");

    U32 logicalCoreCount = 0;
    U32 physicalCoreCount = 1;

    if (cpuInfo.is_open())
    {
        // Load every line of the CPU Info
        std::string line;

        while (std::getline(cpuInfo, line))
        {
            std::string fieldName = line.substr(0, line.find(":"));
            rtrim(fieldName);

            // Entries are newline separated
            if (fieldName == "")
            {
                ++logicalCoreCount;
                continue;
            }

            std::string fieldValue = line.substr(line.find(":") + 1, line.length());
            ltrim(fieldValue);
            rtrim(fieldValue);

            // Load fields
            if (fieldName == "vendor_id")
            {
                vendorString = fieldValue.c_str();
            }
            else if (fieldName == "model name")
            {
                brandString = fieldValue.c_str();
            }
            else if (fieldName == "cpu cores")
            {
                physicalCoreCount = dAtoui(fieldValue.c_str());
            }
            else if (fieldName == "flags")
            {
                std::vector<std::string> flags;
                std::istringstream flagStream(fieldValue);

                std::string currentFlag;
                while (std::getline(flagStream, currentFlag, ' '))
                {
                    flags.push_back(currentFlag);
                }

                // Set CPU flags
                if (std::find(flags.begin(), flags.end(), "fpu") != flags.end())
                {
                    Platform::SystemInfo.processor.properties |= CPU_PROP_FPU;
                }

                if (std::find(flags.begin(), flags.end(), "sse3") != flags.end())
                {
                    Platform::SystemInfo.processor.properties |= CPU_PROP_SSE3;
                }

                if (std::find(flags.begin(), flags.end(), "avx") != flags.end())
                {
                    Platform::SystemInfo.processor.properties |= CPU_PROP_AVX;
                }

                if (std::find(flags.begin(), flags.end(), "ssse3") != flags.end())
                {
                    Platform::SystemInfo.processor.properties |= CPU_PROP_SSE3ex;
                }

                if (std::find(flags.begin(), flags.end(), "sse") != flags.end())
                {
                    Platform::SystemInfo.processor.properties |= CPU_PROP_SSE;
                }

                if (std::find(flags.begin(), flags.end(), "sse2") != flags.end())
                {
                    Platform::SystemInfo.processor.properties |= CPU_PROP_SSE2;
                }

                if (std::find(flags.begin(), flags.end(), "sse4_1") != flags.end())
                {
                    Platform::SystemInfo.processor.properties |= CPU_PROP_SSE4_1;
                }

                if (std::find(flags.begin(), flags.end(), "sse4_2") != flags.end())
                {
                    Platform::SystemInfo.processor.properties |= CPU_PROP_SSE4_2;
                }

                if (std::find(flags.begin(), flags.end(), "mmx") != flags.end())
                {
                    Platform::SystemInfo.processor.properties |= CPU_PROP_MMX;
                }
            }
        }

        cpuInfo.close();
    }
    else
    {
        logicalCoreCount = 1;
    }

    Platform::SystemInfo.processor.numLogicalProcessors = logicalCoreCount;
    Platform::SystemInfo.processor.numPhysicalProcessors = physicalCoreCount;
    Platform::SystemInfo.processor.isHyperThreaded = logicalCoreCount != physicalCoreCount;
    Platform::SystemInfo.processor.isMultiCore = physicalCoreCount != 1;
    Platform::SystemInfo.processor.numLogicalProcessors = logicalCoreCount;
    Platform::SystemInfo.processor.numPhysicalProcessors = physicalCoreCount;
    if (Platform::SystemInfo.processor.isMultiCore)
    {
        Platform::SystemInfo.processor.properties |= CPU_PROP_MP;
    }

    // Load processor base frequency
    std::ifstream baseFrequencyStream("/sys/devices/system/cpu/cpu0/cpufreq/base_frequency");
    if (baseFrequencyStream.is_open())
    {
        U32 baseFrequencyKHz = 0;
        baseFrequencyStream >> baseFrequencyKHz;

        Platform::SystemInfo.processor.mhz = baseFrequencyKHz / 1000;
        baseFrequencyStream.close();
    }

    SetProcessorInfo(Platform::SystemInfo.processor, vendorString.c_str(), brandString.c_str());
}

void Processor::init() 
{
    getCPUInformation();

#if defined(TORQUE_CPU_X64) || defined(TORQUE_CPU_X32)
    // Set sane default information
    Platform::SystemInfo.processor.properties |= CPU_PROP_C | CPU_PROP_FPU | CPU_PROP_LE ;

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

    // Once CPU information is resolved, produce an output like Windows does
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
    if (Platform::SystemInfo.processor.properties & CPU_PROP_SSE4_1)
        Con::printf("      SSE4.1 detected" );
    if (Platform::SystemInfo.processor.properties & CPU_PROP_SSE4_2)
        Con::printf("      SSE4.2 detected" );
    if (Platform::SystemInfo.processor.properties & CPU_PROP_AVX)
        Con::printf("      AVX detected" );
    if (Platform::SystemInfo.processor.properties & CPU_PROP_SSE3ex)
        Con::printf("      SSE3ex detected" );
    if (Platform::SystemInfo.processor.properties & CPU_PROP_MP)
        Con::printf("   MultiCore CPU detected [%i cores, %i logical]", Platform::SystemInfo.processor.numPhysicalProcessors, Platform::SystemInfo.processor.numLogicalProcessors);

    Con::printf(" ");
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

#endif