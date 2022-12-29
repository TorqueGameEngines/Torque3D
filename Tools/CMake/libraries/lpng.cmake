# -----------------------------------------------------------------------------
# Copyright (c) 2014 GarageGames, LLC
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to
# deal in the Software without restriction, including without limitation the
# rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
# sell copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
# IN THE SOFTWARE.
# -----------------------------------------------------------------------------

project(lpng)

if (APPLE AND TORQUE_MACOS_UNIVERSAL_BINARY)
    addPath("${libDir}/lpng/arm")

    set(CMAKE_XCODE_ATTRIBUTE_PER_ARCH_CFLAGS_x86_64 "-DPNG_INTEL_SSE_OPT=1 -DPNG_ARM_NEON_OPT=0")
    set(CMAKE_XCODE_ATTRIBUTE_PER_ARCH_CFLAGS_arm64 "-DPNG_ARM_NEON_OPT=1 -DPNG_INTEL_SSE_OPT=0")
else()
    # Enables NEON for libpng
    if ( TORQUE_CPU_ARM32 OR TORQUE_CPU_ARM64 )
        set(PNG_ARM_NEON on CACHE STRING "" FORCE)
        add_definitions(-DPNG_ARM_NEON_OPT=1)
        addPath("${libDir}/lpng/arm")
    else()
        set(PNG_ARM_NEON off CACHE STRING "" FORCE)
        add_definitions(-DPNG_ARM_NEON_OPT=0)
    endif()

    # Enables SSE for libpng - also takes care of compiler warnings.
    if ( TORQUE_CPU_X32 OR TORQUE_CPU_X64 )
        set(PNG_INTEL_SSE on CACHE STRING "" FORCE)
        add_definitions(-DPNG_INTEL_SSE_OPT=1)
        addPath("${libDir}/lpng/intel")
    else()
        set(PNG_INTEL_SSE off CACHE STRING "" FORCE)
        add_definitions(-DPNG_INTEL_SSE_OPT=0)
    endif()
endif()

mark_as_advanced(PNG_INTEL_SSE)
mark_as_advanced(PNG_ARM_NEON)

addInclude(${libDir}/zlib)

finishLibrary("${libDir}/${PROJECT_NAME}")

