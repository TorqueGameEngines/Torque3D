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

project(${TORQUE_APP_NAME})

if(UNIX)
    if(NOT CXX_FLAG32)
        set(CXX_FLAG32 "")
    endif()
    #set(CXX_FLAG32 "-m32") #uncomment for build x32 on OSx64

    if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX_FLAG32} -Wundef -pipe -Wfatal-errors -Wno-return-type-c-linkage -Wno-unused-local-typedef ${TORQUE_ADDITIONAL_LINKER_FLAGS}")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CXX_FLAG32} -Wundef -pipe -Wfatal-errors -Wno-return-type-c-linkage -Wno-unused-local-typedef ${TORQUE_ADDITIONAL_LINKER_FLAGS}")

        # Only use SSE on x86 devices
        if (TORQUE_CPU_X32 OR TORQUE_CPU_X64)
            set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -msse")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse")
        endif()
    else()
        # default compiler flags
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX_FLAG32} -Wundef -pipe -Wfatal-errors -no-pie ${TORQUE_ADDITIONAL_LINKER_FLAGS} -Wl,-rpath,'$ORIGIN'")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CXX_FLAG32} -Wundef -pipe -Wfatal-errors ${TORQUE_ADDITIONAL_LINKER_FLAGS} -Wl,-rpath,'$ORIGIN'")

        # Only use SSE on x86 devices
        if (TORQUE_CPU_X32 OR TORQUE_CPU_X64)
            set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -msse")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse")
        endif()
    endif()
endif()

###############################################################################
# modules
###############################################################################
option(TORQUE_SFX_VORBIS "Vorbis Sound" ON)
mark_as_advanced(TORQUE_SFX_VORBIS)
option(TORQUE_THEORA "Theora Video Support" ON)
mark_as_advanced(TORQUE_THEORA)
option(TORQUE_ADVANCED_LIGHTING "Advanced Lighting" ON)
mark_as_advanced(TORQUE_ADVANCED_LIGHTING)
option(TORQUE_BASIC_LIGHTING "Basic Lighting" ON)
mark_as_advanced(TORQUE_BASIC_LIGHTING)
# option(TORQUE_SFX_DirectX "DirectX Sound" OFF)
# mark_as_advanced(TORQUE_SFX_DirectX)
option(TORQUE_SFX_OPENAL "OpenAL Sound" ON)
mark_as_advanced(TORQUE_APP_PASSWORD)
set(TORQUE_APP_PASSWORD "changeme" CACHE STRING "zip file password")
#windows uses openal-soft
if(WIN32)
    #disable a few things that are not required
    set(ALSOFT_TESTS OFF CACHE BOOL "Build and install test programs" FORCE)
    set(ALSOFT_UTILS OFF CACHE BOOL "Build and install utility programs" FORCE)
    set(ALSOFT_EXAMPLES OFF CACHE BOOL "Build and install example programs" FORCE)
    set(ALSOFT_INSTALL_CONFIG OFF CACHE BOOL "Install alsoft.conf sample configuration file" FORCE)
    set(ALSOFT_INSTALL OFF CACHE BOOL "Install headers and libraries" FORCE)
    set(ALSOFT_NO_CONFIG_UTIL OFF CACHE BOOL "Disable building the alsoft-config utility" FORCE)
    set(ALSOFT_INSTALL_HRTF_DATA OFF CACHE BOOL "Install HRTF definition files" FORCE)
    set(ALSOFT_INSTALL_AMBDEC_PRESETS OFF CACHE BOOL "Install AmbDec presets" FORCE)
    set(ALSOFT_EMBED_HRTF_DATA OFF CACHE BOOL "Embed the HRTF data (increases library footprint)" FORCE)
    
    add_subdirectory( ${libDir}/openal-soft ${CMAKE_CURRENT_BINARY_DIR}/openal-soft)
endif()

if(TORQUE_SFX_OPENAL)
    #Hide some unnecessary fields as advanced
    mark_as_advanced(ALSOFT_INSTALL_AMBDEC_PRESETS)
    mark_as_advanced(ALSOFT_BACKEND_DSOUND)
    mark_as_advanced(ALSOFT_BACKEND_MMDEVAPI)
    mark_as_advanced(ALSOFT_BACKEND_WAVE)
    mark_as_advanced(ALSOFT_BACKEND_WINMM)
    mark_as_advanced(ALSOFT_INSTALL_CONFIG)
    mark_as_advanced(ALSOFT_CPUEXT_SSE)
    mark_as_advanced(ALSOFT_CPUEXT_SSE2)
    mark_as_advanced(ALSOFT_CPUEXT_SSE3)
    mark_as_advanced(ALSOFT_CPUEXT_SSE4_1)
    mark_as_advanced(ALSOFT_DLOPEN)
    mark_as_advanced(ALSOFT_EMBED_HRTF_DATA)
    mark_as_advanced(ALSOFT_EXAMPLES)
    mark_as_advanced(ALSOFT_INSTALL_HRTF_DATA)
    mark_as_advanced(ALSOFT_INSTALL)
    mark_as_advanced(ALSOFT_NO_CONFIG_UTIL)
    mark_as_advanced(ALSOFT_NO_UID_DEFS)
    mark_as_advanced(ALSOFT_REQUIRE_ALSA)
    mark_as_advanced(ALSOFT_REQUIRE_COREAUDIO)
    mark_as_advanced(ALSOFT_REQUIRE_DSOUND)
    mark_as_advanced(ALSOFT_REQUIRE_JACK)
    mark_as_advanced(ALSOFT_REQUIRE_MMDEVAPI)
    mark_as_advanced(ALSOFT_REQUIRE_NEON)
    mark_as_advanced(ALSOFT_REQUIRE_OPENSL)
    mark_as_advanced(ALSOFT_REQUIRE_OSS)
    mark_as_advanced(ALSOFT_REQUIRE_PORTAUDIO)
    mark_as_advanced(ALSOFT_REQUIRE_PULSEAUDIO)
    mark_as_advanced(ALSOFT_REQUIRE_QSA)
    mark_as_advanced(ALSOFT_REQUIRE_SNDIO)
    mark_as_advanced(ALSOFT_REQUIRE_SOLARIS)
    mark_as_advanced(ALSOFT_REQUIRE_SSE)
    mark_as_advanced(ALSOFT_REQUIRE_SSE2)
    mark_as_advanced(ALSOFT_REQUIRE_SSE4_1)
    mark_as_advanced(ALSOFT_REQUIRE_WINMM)
    mark_as_advanced(ALSOFT_TESTS)
    mark_as_advanced(ALSOFT_UTILS)
    mark_as_advanced(ALSOFT_WERROR)
    mark_as_advanced(COREAUDIO_FRAMEWORK)
    mark_as_advanced(CMAKE_DEBUG_POSTFIX)
    mark_as_advanced(FORCE_STATIC_VCRT)
    mark_as_advanced(ALSOFT_BACKEND_WASAPI)
    mark_as_advanced(ALSOFT_BUILD_ROUTER)
    mark_as_advanced(ALSOFT_REQUIRE_SDL2)
    mark_as_advanced(ALSOFT_REQUIRE_WASAPI)
    #the following is from openal-soft
    mark_as_advanced(SDL2MAIN_LIBRARY)
    mark_as_advanced(SDL2_CORE_LIBRARY)
    mark_as_advanced(SDL2_INCLUDE_DIR)
endif()

mark_as_advanced(TORQUE_SFX_OPENAL)
option(TORQUE_HIFI "HIFI? support" OFF)
mark_as_advanced(TORQUE_HIFI)
option(TORQUE_EXTENDED_MOVE "Extended move support" OFF)
mark_as_advanced(TORQUE_EXTENDED_MOVE)

set(TORQUE_SDL ON) # we need sdl to do our platform interop

if(WIN32)
	option(TORQUE_OPENGL "Allow OpenGL render" ON)
	#mark_as_advanced(TORQUE_OPENGL)
else()
	set(TORQUE_OPENGL ON) # we need OpenGL to render on Linux/Mac
endif()

if(WIN32)
	option(TORQUE_D3D11 "Allow Direct3D 11 render" ON)

	addDef(TORQUE_D3D11)
endif()

option(TORQUE_DEDICATED "Torque dedicated" OFF)
mark_as_advanced(TORQUE_DEDICATED)

###############################################################################
# options
###############################################################################
option(TORQUE_SECURE_VFS "Secure VFS configuration. Arbitrary script access to file system will be heavily restricted." OFF)
mark_as_advanced(TORQUE_SECURE_VFS)

option(TORQUE_MULTITHREAD "Multi Threading" ON)
mark_as_advanced(TORQUE_MULTITHREAD)

option(TORQUE_POSIX_PATH_CASE_INSENSITIVE "POSIX Pathing Case Insensitivity" ON)
mark_as_advanced(TORQUE_POSIX_PATH_CASE_INSENSITIVE)

option(TORQUE_ZIP_PATH_CASE_INSENSITIVE "ZIP Pathing Case Insensitivity" ON)
mark_as_advanced(TORQUE_ZIP_PATH_CASE_INSENSITIVE)

option(TORQUE_DISABLE_MEMORY_MANAGER "Disable memory manager" ON)
mark_as_advanced(TORQUE_DISABLE_MEMORY_MANAGER)

option(TORQUE_DISABLE_VIRTUAL_MOUNT_SYSTEM "Disable virtual mount system" OFF)
mark_as_advanced(TORQUE_DISABLE_VIRTUAL_MOUNT_SYSTEM)

option(TORQUE_DISABLE_FIND_ROOT_WITHIN_ZIP "Disable reading root path from zip. Zips will be mounted in-place with file name as directory name." ON)
mark_as_advanced(TORQUE_DISABLE_FIND_ROOT_WITHIN_ZIP)

option(TORQUE_ZIP_DISK_LAYOUT "All zips must be placed in the executable directory and contain full paths to the files." OFF)
mark_as_advanced(TORQUE_ZIP_DISK_LAYOUT)

option(TORQUE_PLAYER "Playback only?" OFF)
mark_as_advanced(TORQUE_PLAYER)

option(TORQUE_TOOLS "Enable or disable the tools" ON)
mark_as_advanced(TORQUE_TOOLS)

option(TORQUE_ENABLE_PROFILER "Enable or disable the profiler" OFF)
mark_as_advanced(TORQUE_ENABLE_PROFILER)

option(TORQUE_DEBUG "T3D Debug mode" OFF)
mark_as_advanced(TORQUE_DEBUG)

option(TORQUE_SHIPPING "T3D Shipping build?" OFF)
mark_as_advanced(TORQUE_SHIPPING)

option(TORQUE_DEBUG_NET "debug network" OFF)
mark_as_advanced(TORQUE_DEBUG_NET)

option(TORQUE_DEBUG_NET_MOVES "debug network moves" OFF)
mark_as_advanced(TORQUE_DEBUG_NET_MOVES)

option(TORQUE_ENABLE_ASSERTS "enables or disable asserts" OFF)
mark_as_advanced(TORQUE_ENABLE_ASSERTS)

option(TORQUE_DEBUG_GFX_MODE "triggers graphics debug mode" OFF)
mark_as_advanced(TORQUE_DEBUG_GFX_MODE)

#option(DEBUG_SPEW "more debug" OFF)
set(TORQUE_NO_DSO_GENERATION ON)

if(NOT TORQUE_SCRIPT_EXTENSION)
    set(TORQUE_SCRIPT_EXTENSION "tscript" CACHE STRING "The default script extension to use for TorqueScript files")
endif()

mark_as_advanced(TORQUE_SCRIPT_EXTENSION)

option(TORQUE_USE_ZENITY "use the Zenity backend for NFD" OFF)
mark_as_advanced(TORQUE_USE_ZENITY)

option(TORQUE_SHOW_LEGACY_FILE_FIELDS "If on, shows legacy direct file path fields in the inspector." OFF)
mark_as_advanced(TORQUE_SHOW_LEGACY_FILE_FIELDS)

if(WIN32)
    # warning C4800: 'XXX' : forcing value to bool 'true' or 'false' (performance warning)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -wd4800")
    # warning C4018: '<' : signed/unsigned mismatch
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -wd4018")
    # warning C4244: 'initializing' : conversion from 'XXX' to 'XXX', possible loss of data
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -wd4244")
	if(TORQUE_SFX_DirectX) 
		if( TORQUE_CPU_X64 )
			link_directories($ENV{DXSDK_DIR}/Lib/x64)
		else()
			link_directories($ENV{DXSDK_DIR}/Lib/x86)
		endif()
	endif()
endif()

###############################################################################
# Always enabled paths first
###############################################################################
addPath("${srcDir}/") # must come first :)
addPath("${srcDir}/app")
addPath("${srcDir}/sfx/media")
addPath("${srcDir}/sfx/null")
addPath("${srcDir}/sfx")
addPath("${srcDir}/console")
addPath("${srcDir}/console/test")
addPath("${srcDir}/core")
addPath("${srcDir}/core/stream")
addPath("${srcDir}/core/strings")
addPath("${srcDir}/core/util")
addPath("${srcDir}/core/util/test")
addPath("${srcDir}/core/util/journal")
addPath("${srcDir}/core/util/journal/test")
addPath("${srcDir}/core/util/zip")
addPath("${srcDir}/core/util/zip/test")
addPath("${srcDir}/core/util/zip/compressors")
addPath("${srcDir}/i18n")
addPath("${srcDir}/sim")
addPath("${srcDir}/util")
addPath("${srcDir}/windowManager")
addPath("${srcDir}/windowManager/torque")
addPath("${srcDir}/windowManager/test")
addPath("${srcDir}/math")
addPath("${srcDir}/math/util")
addPath("${srcDir}/math/test")

addPath("${srcDir}/platform")
if(NOT TORQUE_SDL)
   set(BLACKLIST "fileDialog.cpp" )
endif()
addPath("${srcDir}/platform/nativeDialogs")
set(BLACKLIST "" )

addPath("${srcDir}/cinterface")

if( NOT TORQUE_DEDICATED )
    addPath("${srcDir}/platform/menus")
endif()
addPath("${srcDir}/platform/test")
addPath("${srcDir}/platform/threads")
addPath("${srcDir}/platform/threads/test")
addPath("${srcDir}/platform/async")
addPath("${srcDir}/platform/async/test")
addPath("${srcDir}/platform/input")
addPath("${srcDir}/platform/output")
addPath("${srcDir}/app")

if (NOT TORQUE_NET_CURL)
    set(BLACKLIST "httpObject.h" "httpObject.cpp" )
endif()
addPath("${srcDir}/app/net")
set(BLACKLIST "")

addPath("${srcDir}/util/messaging")
addPath("${srcDir}/gfx/Null")
addPath("${srcDir}/gfx/test")
addPath("${srcDir}/gfx/bitmap")
addPath("${srcDir}/gfx/bitmap/loaders")
addPath("${srcDir}/gfx/util")
addPath("${srcDir}/gfx/video")
addPath("${srcDir}/gfx")
addPath("${srcDir}/shaderGen")
addPath("${srcDir}/gfx/sim")
addPath("${srcDir}/gui/buttons")
addPath("${srcDir}/gui/containers")
addPath("${srcDir}/gui/controls")
addPath("${srcDir}/gui/core")
addPath("${srcDir}/gui/game")
addPath("${srcDir}/gui/shiny")
addPath("${srcDir}/gui/utility")
addPath("${srcDir}/gui")
addPath("${srcDir}/collision")
addPath("${srcDir}/materials")
addPath("${srcDir}/lighting")
addPath("${srcDir}/lighting/common")
addPath("${srcDir}/renderInstance")
addPath("${srcDir}/renderInstance/debug")
addPath("${srcDir}/scene")
addPath("${srcDir}/scene/culling")
addPath("${srcDir}/scene/zones")
addPath("${srcDir}/scene/mixin")
addPath("${srcDir}/shaderGen")
addPath("${srcDir}/terrain")
addPath("${srcDir}/environment")
addPath("${srcDir}/forest")
addPath("${srcDir}/forest/ts")
addPath("${srcDir}/ts")
addPath("${srcDir}/ts/arch")
addPath("${srcDir}/physics")
addPath("${srcDir}/gui/3d")
addPath("${srcDir}/postFx")

addPath("${srcDir}/T3D")
set(BLACKLIST "" )

addPath("${srcDir}/T3D/examples")
addPath("${srcDir}/T3D/fps")
addPath("${srcDir}/T3D/fx")
addPath("${srcDir}/T3D/vehicles")
addPath("${srcDir}/T3D/physics")
addPath("${srcDir}/T3D/decal")
addPath("${srcDir}/T3D/sfx")
addPath("${srcDir}/T3D/gameBase")
addPath("${srcDir}/T3D/turret")
addPath("${srcDir}/T3D/lighting")
addPath("${srcDir}/T3D/gameObjects")
addPathRec("${srcDir}/T3D/components/")
addPathRec("${srcDir}/T3D/systems")

addPath("${srcDir}/main/")
addPath("${srcDir}/assets")
addPath("${srcDir}/module")
addPathRec("${srcDir}/T3D/assets")
addPathRec("${srcDir}/persistence")
addPathRec("${srcDir}/ts/collada")
addPathRec("${srcDir}/ts/assimp")
addPathRec("${srcDir}/ts/loader")
addPathRec("${projectSrcDir}")

# Load module-based files
if(EXISTS ${TORQUE_APP_DIR}/game/data)
    message("Reading modules in ${TORQUE_APP_DIR}/game/data path...")
	
	subDirCmake(MODULEDIRS ${TORQUE_APP_DIR}/game/data)
	foreach(modDir ${MODULEDIRS})
		addInclude("${modDir}/source")
		addPathRec("${modDir}/source")
		file(GLOB modules "${modDir}/lib/*.cmake")
		foreach(module ${modules})
			set(moduleLibDir "${modDir}/lib")
			include(${module})
		endforeach()
		
	endforeach()
endif()

if(EXISTS ${TORQUE_APP_DIR}/game/tools)
    message("Reading modules in ${TORQUE_APP_DIR}/game/tools path...")

    addInclude("${TORQUE_APP_DIR}/game/tools")
    addPathRec("${TORQUE_APP_DIR}/game/tools")
endif()

###############################################################################
# modular paths
###############################################################################
# lighting
if(TORQUE_ADVANCED_LIGHTING)
    addPath("${srcDir}/lighting/advanced")
    addPathRec("${srcDir}/lighting/shadowMap")
    if(WIN32)
		addPathRec("${srcDir}/lighting/advanced/hlsl")
	endif()
	if(TORQUE_OPENGL)
		addPathRec("${srcDir}/lighting/advanced/glsl")
	endif()
    addDef(TORQUE_ADVANCED_LIGHTING)
endif()
if(TORQUE_BASIC_LIGHTING)
    addPathRec("${srcDir}/lighting/basic")
    addPathRec("${srcDir}/lighting/shadowMap")
    addDef(TORQUE_BASIC_LIGHTING)
endif()

# DirectX Sound
if(TORQUE_SFX_DirectX)
    addLib(x3daudio.lib)
    addPathRec("${srcDir}/sfx/dsound")
    addPathRec("${srcDir}/sfx/xaudio")
endif()

# OpenAL
if(TORQUE_SFX_OPENAL AND NOT TORQUE_DEDICATED)
    addPath("${srcDir}/sfx/openal")
    if(WIN32)
      option(AL_ALEXT_PROTOTYPES "Use Extended OpenAL options" ON)
      addPath("${srcDir}/sfx/openal/win32")
      addInclude("${libDir}/openal-soft/include")
    endif()
      if(UNIX AND NOT APPLE)
         option(AL_ALEXT_PROTOTYPES "Use Extended OpenAL options" ON)
         addPath("${srcDir}/sfx/openal/linux")
      endif()
   if(APPLE)
      option(AL_ALEXT_PROTOTYPES "Use Extended OpenAL options" OFF)
      addPath("${srcDir}/sfx/openal/mac")
      addFramework("OpenAL")
    endif()
endif()

mark_as_advanced(AL_ALEXT_PROTOTYPES)
if(AL_ALEXT_PROTOTYPES)
	addDef( "AL_ALEXT_PROTOTYPES" )
endif()

# Vorbis
if(TORQUE_SFX_VORBIS)
    addInclude(${libDir}/libvorbis/include)
    addDef(TORQUE_OGGVORBIS)
    addLib(libvorbis)
    addLib(libogg)
endif()

# Theora
if(TORQUE_THEORA)
    addPath("${srcDir}/core/ogg")
    addPath("${srcDir}/gfx/video")
    addPath("${srcDir}/gui/theora")

    addDef(TORQUE_OGGTHEORA)
    addDef(TORQUE_OGGVORIBS)
    addInclude(${libDir}/libtheora/include)
    addLib(libtheora)
endif()

# Include tools for non-tool builds (or define player if a tool build)
if(TORQUE_TOOLS)
    addPath("${srcDir}/gui/worldEditor")
    addPath("${srcDir}/gui/worldEditor/tools")
    addPath("${srcDir}/environment/editors")
    addPath("${srcDir}/forest/editor")
    addPath("${srcDir}/gui/editor")
    addPath("${srcDir}/gui/editor/inspector")
    set(BLACKLIST "" )
endif()

if(TORQUE_HIFI)
    addPath("${srcDir}/T3D/gameBase/hifi")
    addDef(TORQUE_HIFI_NET)
endif()

if(TORQUE_EXTENDED_MOVE)
    addPath("${srcDir}/T3D/gameBase/extended")
    addDef(TORQUE_EXTENDED_MOVE)
else()
    addPath("${srcDir}/T3D/gameBase/std")
endif()

if(TORQUE_SDL)
    addPathRec("${srcDir}/windowManager/sdl")

    if(NOT TORQUE_OPENGL)
        set(BLACKLIST "sdlPlatformGL.cpp")
    endif()

    addPathRec("${srcDir}/platformSDL")
    set(BLACKLIST "")

    if(TORQUE_OPENGL)
      addPathRec("${srcDir}/gfx/gl/sdl")
    endif()

    if(UNIX AND NOT APPLE)
       #set(CMAKE_SIZEOF_VOID_P 4) #force 32 bit
       set(ENV{CFLAGS} "${CXX_FLAG32} -g -O3")
       if("${TORQUE_ADDITIONAL_LINKER_FLAGS}" STREQUAL "")
         set(ENV{LDFLAGS} "${CXX_FLAG32}")
       else()
         set(ENV{LDFLAGS} "${CXX_FLAG32} ${TORQUE_ADDITIONAL_LINKER_FLAGS}")
       endif()

       find_package(PkgConfig REQUIRED)
       pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

       # Setup CMake to use GTK+, tell the compiler where to look for headers
       # and to the linker where to look for libraries
       include_directories(${GTK3_INCLUDE_DIRS})
       link_directories(${GTK3_LIBRARY_DIRS})

       # Add other flags to the compiler
       add_definitions(${GTK3_CFLAGS_OTHER})

       if(TORQUE_USE_ZENITY)
          set(BLACKLIST "nfd_win.cpp" "nfd_cocoa.m" "nfd_gtk.c" )
       else()
          set(BLACKLIST "nfd_win.cpp" "nfd_cocoa.m" "simple_exec.h" "nfd_zenity.c")
       endif()
       addLib(nativeFileDialogs)

       set(BLACKLIST ""  )
       target_link_libraries(nativeFileDialogs ${GTK3_LIBRARIES})
  elseif(APPLE)
      set(BLACKLIST "nfd_gtk.c" "nfd_win.cpp" )
      addLib(nativeFileDialogs)
      set(BLACKLIST ""  )
 	else()
 	   set(BLACKLIST "nfd_gtk.c" "nfd_cocoa.m" "simple_exec.h" "nfd_zenity.c")
 	   addLib(nativeFileDialogs)
     set(BLACKLIST ""  )
 	   addLib(comctl32)
  endif()

    #override and hide SDL2 cache variables
    #set apple to sue sdl static lib, other platforms use dynamic
    if(APPLE)
      set(SDL_SHARED OFF CACHE BOOL "Build a shared version of the library" FORCE)
      set(SDL_STATIC ON CACHE BOOL "Build a static version of the library" FORCE)
    else()
      set(SDL_SHARED ON CACHE BOOL "Build a shared version of the library" FORCE)
      set(SDL_STATIC OFF CACHE BOOL "Build a static version of the library" FORCE)
    endif()
    add_subdirectory( ${libDir}/sdl ${CMAKE_CURRENT_BINARY_DIR}/sdl2 EXCLUDE_FROM_ALL)
    link_directories( ${libDir}/sdl ${CMAKE_CURRENT_BINARY_DIR}/sdl2)
endif()

if(TORQUE_DEDICATED)
    addDef(TORQUE_DEDICATED)
endif()

#modules dir
file(GLOB modules "modules/*.cmake")
foreach(module ${modules})
	include(${module})
endforeach()

###############################################################################
# platform specific things
###############################################################################
if(WIN32)
    addPath("${srcDir}/platformWin32")
    if(TORQUE_SDL)
 		set(BLACKLIST "fileDialog.cpp" )
 	endif()
    addPath("${srcDir}/platformWin32/nativeDialogs")
    set(BLACKLIST "" )
    addPath("${srcDir}/platformWin32/menus")
    if(NOT TORQUE_SDL)
       addPath("${srcDir}/platformWin32/threads")
    endif()
    addPath("${srcDir}/platformWin32/videoInfo")
    addPath("${srcDir}/platformWin32/minidump")
    addPath("${srcDir}/windowManager/win32")
	if(TORQUE_D3D11)
		addPath("${srcDir}/gfx/D3D11")
	endif()
    addPath("${srcDir}/shaderGen/HLSL")
    addPath("${srcDir}/terrain/hlsl")
    addPath("${srcDir}/forest/hlsl")
    # add windows rc file for the icon
    addFile("${projectSrcDir}/torque.rc")
endif()

if(APPLE)
    addPath("${srcDir}/platformMac")
    addPath("${srcDir}/platformPOSIX")
endif()

if (UNIX AND NOT APPLE)
    addPath("${srcDir}/platformX11")
endif()

if(UNIX AND NOT APPLE)
    # linux_dedicated
    if(TORQUE_DEDICATED)
		addPath("${srcDir}/windowManager/dedicated")
		# ${srcDir}/UNIX/*.client.* files are not needed
		# @todo: move to separate file
		file( GLOB tmp_files
             ${srcDir}/platformX86UNIX/*.cpp
             ${srcDir}/platformX86UNIX/*.c
             ${srcDir}/platformX86UNIX/*.cc
             ${srcDir}/platformX86UNIX/*.h )
        file( GLOB tmp_remove_files ${srcDir}/platformX86UNIX/*client.* )
        LIST( REMOVE_ITEM tmp_files ${tmp_remove_files} )
        foreach( f ${tmp_files} )
            addFile( ${f} )
        endforeach()
    else()
        addPath("${srcDir}/platformX86UNIX")
        addPath("${srcDir}/platformX86UNIX/nativeDialogs")
    endif()
    # linux
    addPath("${srcDir}/platformPOSIX")
endif()

if( TORQUE_OPENGL )
    addPath("${srcDir}/shaderGen/GLSL")
    if( TORQUE_OPENGL AND NOT TORQUE_DEDICATED )
        addPath("${srcDir}/gfx/gl")
        addPath("${srcDir}/gfx/gl/tGL")
        addPath("${srcDir}/shaderGen/GLSL")
        addPath("${srcDir}/terrain/glsl")
        addPath("${srcDir}/forest/glsl")
    endif()

    if(WIN32 AND NOT TORQUE_SDL)
      addPath("${srcDir}/gfx/gl/win32")
    endif()
endif()

###############################################################################
###############################################################################
finishExecutable()
###############################################################################
###############################################################################

# Set Visual Studio startup project
if(MSVC)
set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${TORQUE_APP_NAME})
endif()

message(STATUS "writing ${projectSrcDir}/torqueConfig.h")
CONFIGURE_FILE("${cmakeDir}/torqueConfig.h.in" "${projectSrcDir}/torqueConfig.h")

# configure the relevant files only once

if(APPLE)
  #icon
  if(NOT EXISTS "${projectSrcDir}/torque.icns")
      CONFIGURE_FILE("${cmakeDir}/torque.icns" "${projectSrcDir}/torque.icns" COPYONLY)
  endif()
  #plist
  if(NOT EXISTS "${projectSrcDir}/Info.plist")
      CONFIGURE_FILE("${cmakeDir}/Info.plist.in" "${projectSrcDir}/Info.plist" COPYONLY)
  endif()
  #target properties for mac
  set_target_properties("${PROJECT_NAME}" PROPERTIES MACOSX_BUNDLE_INFO_PLIST "${projectSrcDir}/Info.plist")
else()
  if(NOT EXISTS "${projectSrcDir}/torque.ico")
      CONFIGURE_FILE("${cmakeDir}/torque.ico" "${projectSrcDir}/torque.ico" COPYONLY)
  endif()
endif()

if(NOT EXISTS "${projectOutDir}/${PROJECT_NAME}.torsion")
    CONFIGURE_FILE("${cmakeDir}/template.torsion.in" "${projectOutDir}/${PROJECT_NAME}.torsion")
endif()
if(EXISTS "${CMAKE_SOURCE_DIR}/Templates/${TORQUE_TEMPLATE}/game/main.tscript.in")
    CONFIGURE_FILE("${CMAKE_SOURCE_DIR}/Templates/${TORQUE_TEMPLATE}/game/main.tscript.in" "${projectOutDir}/main.${TORQUE_SCRIPT_EXTENSION}")
else()
    if(EXISTS "${CMAKE_SOURCE_DIR}/Templates/${TORQUE_TEMPLATE}/game/main.${TORQUE_SCRIPT_EXTENSION}.in")
        CONFIGURE_FILE("${CMAKE_SOURCE_DIR}/Templates/${TORQUE_TEMPLATE}/game/main.${TORQUE_SCRIPT_EXTENSION}.in" "${projectOutDir}/main.${TORQUE_SCRIPT_EXTENSION}")
    endif()
endif()
if(WIN32)
    if(NOT EXISTS "${projectSrcDir}/torque.rc")
        CONFIGURE_FILE("${cmakeDir}/torque-win.rc.in" "${projectSrcDir}/torque.rc")
    endif()
    if(NOT EXISTS "${projectOutDir}/${PROJECT_NAME}-debug.bat")
        CONFIGURE_FILE("${cmakeDir}/app-debug-win.bat.in" "${projectOutDir}/${PROJECT_NAME}-debug.bat")
    endif()
    if(NOT EXISTS "${projectOutDir}/cleanup.bat")
        CONFIGURE_FILE("${cmakeDir}/cleanup-win.bat.in" "${projectOutDir}/cleanup.bat")
    endif()
endif()

###############################################################################
# Common Libraries
###############################################################################
addLib(lpng)
addLib(ljpeg)
addLib(zlib)
addLib(tinyxml)
addLib(opcode)
addLib(squish)
addLib(collada)
addLib(pcre)
addLib(convexDecomp)
if (TORQUE_OPENGL)
   addLib(glad)
endif()
addLib(assimp)

if(WIN32)
    # copy pasted from T3D build system, some might not be needed
    set(TORQUE_EXTERNAL_LIBS "COMCTL32.LIB;COMDLG32.LIB;USER32.LIB;ADVAPI32.LIB;GDI32.LIB;WINMM.LIB;WS2_32.LIB;vfw32.lib;Imm32.lib;ole32.lib;shell32.lib;oleaut32.lib;version.lib" CACHE STRING "external libs to link against")
    mark_as_advanced(TORQUE_EXTERNAL_LIBS)
    addLib("${TORQUE_EXTERNAL_LIBS}")

   if(TORQUE_OPENGL)
      addLib(OpenGL32.lib)
   endif()
endif()

if (APPLE)
  addFramework("Cocoa")
  addFramework("OpenGL")
  #These are needed by sdl2 static lib
  addFramework("CoreAudio")
  addFramework("AudioUnit")
  addFramework("ForceFeedback")
  addFramework("IOKit")
  addFramework("CoreVideo")
  #grrr damn you sdl!
  addFramework("Carbon")
  addFramework("AudioToolbox")
  addLib("iconv")
endif()

#detect Architecture
if (APPLE AND NOT IOS)
  option(TORQUE_MACOS_UNIVERSAL_BINARY OFF)

  # Detect architecture if not using universal
  if (TORQUE_MACOS_UNIVERSAL_BINARY)
    set(ARCHITECTURE_STRING_APPLE "x86_64;arm64")
    set(DEPLOYMENT_TARGET_APPLE "10.14")
  else()
    if (CMAKE_SYSTEM_PROCESSOR MATCHES "arm64")
      set(ARCHITECTURE_STRING_APPLE "arm64")
      set(DEPLOYMENT_TARGET_APPLE "11.0")
    else()
      set(ARCHITECTURE_STRING_APPLE "x86_64")
      set(DEPLOYMENT_TARGET_APPLE "10.14")
    endif()
  endif()

  set(CMAKE_OSX_ARCHITECTURES ${ARCHITECTURE_STRING_APPLE} CACHE STRING "OSX Architecture" FORCE)
  set(CMAKE_OSX_DEPLOYMENT_TARGET ${DEPLOYMENT_TARGET_APPLE} CACHE STRING "OSX Deployment target" FORCE)
endif()

if(UNIX AND NOT APPLE)
    # copy pasted from T3D build system, some might not be needed
	set(TORQUE_EXTERNAL_LIBS "dl Xxf86vm Xext X11 Xft stdc++ pthread GL" CACHE STRING "external libs to link against")
	mark_as_advanced(TORQUE_EXTERNAL_LIBS)

    string(REPLACE " " ";" TORQUE_EXTERNAL_LIBS_LIST ${TORQUE_EXTERNAL_LIBS})
    addLib( "${TORQUE_EXTERNAL_LIBS_LIST}" )
endif()

###############################################################################
# Always enabled Definitions
###############################################################################
addDef(TORQUE_DEBUG Debug)
addDef(TORQUE_RELEASE "RelWithDebInfo;Release")
addDef(TORQUE_ENABLE_ASSERTS "Debug;RelWithDebInfo")
addDef(TORQUE_DEBUG_GFX_MODE "RelWithDebInfo")
addDef(TORQUE_SHADERGEN)
addDef(INITGUID)
addDef(NTORQUE_SHARED)
addDef(UNICODE)
addDef(_UNICODE) # for VS
addDef(TORQUE_UNICODE)
#addDef(TORQUE_SHARED) # not used anymore as the game is the executable directly
addDef(LTC_NO_PROTOTYPES) # for libTomCrypt
addDef(BAN_OPCODE_AUTOLINK)
addDef(ICE_NO_DLL)
addDef(TORQUE_OPCODE)
addDef(TORQUE_COLLADA)
addDef(TORQUE_ASSIMP)
addDef(DOM_INCLUDE_TINYXML)
addDef(PCRE_STATIC)
addDef(_CRT_SECURE_NO_WARNINGS)
addDef(_CRT_SECURE_NO_DEPRECATE)

if(UNIX AND NOT APPLE)
	addDef(LINUX)
endif()

if(TORQUE_OPENGL)
	addDef(TORQUE_OPENGL)
endif()

if(TORQUE_SDL)
    addDef(TORQUE_SDL)
    addInclude(${libDir}/sdl/include)
    if(APPLE)
       addLib(SDL2main)
       addLib(SDL2-static)
       add_dependencies(${TORQUE_APP_NAME} SDL2main SDL2-static)
    else()
       addLib(SDL2)
    endif()

    SET(SDL_WAYLAND OFF CACHE BOOL "" FORCE)
    mark_as_advanced(SDL_3DNOW)
    mark_as_advanced(SDL_ALSA)
    mark_as_advanced(SDL_ALTIVEC)
    mark_as_advanced(SDL_ARTS)
    mark_as_advanced(SDL_ASSEMBLY)
    mark_as_advanced(SDL_ASSERTIONS)
    mark_as_advanced(SDL_DIRECTX)
    mark_as_advanced(SDL_DISKAUDIO)
    mark_as_advanced(SDL_DUMMYAUDIO)
    mark_as_advanced(SDL_ESD)
    mark_as_advanced(SDL_FUSIONSOUND)
    mark_as_advanced(SDL_INPUT_TSLIB)
    mark_as_advanced(SDL_LIBC)
    mark_as_advanced(SDL_MMX)
    mark_as_advanced(SDL_NAS)
    mark_as_advanced(SDL_NAS_SHARED)
    mark_as_advanced(SDL_OSS)
    mark_as_advanced(SDL_PTHREADS)
    mark_as_advanced(SDL_PULSEAUDIO)
    mark_as_advanced(SDL_RENDER_D3D)
    mark_as_advanced(SDL_RPATH)
    mark_as_advanced(SDL_SNDIO)
    mark_as_advanced(SDL_SSE)
    mark_as_advanced(SDL_SSE2)
    mark_as_advanced(SDL_SSEMATH)
    mark_as_advanced(SDL_WINDRES)
    mark_as_advanced(SDL_ATOMIC)
    mark_as_advanced(SDL_AUDIO)
    mark_as_advanced(SDL_CPUINFO)
    mark_as_advanced(SDL_DLOPEN)
    mark_as_advanced(SDL_EVENTS)
    mark_as_advanced(SDL_FILE)
    mark_as_advanced(SDL_FILESYSTEM)
    mark_as_advanced(SDL_HAPTIC)
    mark_as_advanced(SDL_JOYSTICK)
    mark_as_advanced(SDL_LOADSO)
    mark_as_advanced(SDL_POWER)
    mark_as_advanced(SDL_RENDER)
    mark_as_advanced(SDL_SHARED)
    mark_as_advanced(SDL_STATIC)
    mark_as_advanced(SDL_THREADS)
    mark_as_advanced(SDL_TIMERS)
    mark_as_advanced(SDL_VIDEO)
    mark_as_advanced(SDL_CLOCK_GETTIME)
    mark_as_advanced(SDL_GCC_ATOMICS)
    mark_as_advanced(SDL_WAYLAND)
    set(SDL_WAYLAND OFF)
    mark_as_advanced(SDL_COCOA)
    mark_as_advanced(SDL_DIRECTFB)
    mark_as_advanced(SDL_DUMMY)
    mark_as_advanced(SDL_MIR)
    mark_as_advanced(SDL_OPENGL)
    mark_as_advanced(SDL_OPENGLES)
    set(SDL_OPENGLES OFF)
    mark_as_advanced(SDL_RPI)
    set(SDL_RPI OFF)
    mark_as_advanced(SDL_VIVANTE)
    set(SDL_VIVANTE OFF)
    mark_as_advanced(VIDEO_X11)
    set(SDL_X11 OFF)
    mark_as_advanced(SDL_VULKAN)
    set(SDL_VULKAN OFF)
    mark_as_advanced(SDL_KMSDRM)
    set(SDL_KMSDRM OFF)
    mark_as_advanced(SDL_WASAPI)
    mark_as_advanced(SDL_SSE3)
    mark_as_advanced(SDL_TEST)
    set(SDL_TEST OFF)
    mark_as_advanced(SDL_SENSOR)
    set(SDL_SENSOR OFF)
    mark_as_advanced(SDL_BACKGROUNDING_SIGNAL)
    mark_as_advanced(SDL_FOREGROUNDING_SIGNAL)
    set(SDL_Metal OFF)
    mark_as_advanced(SDL_METAL)
    mark_as_advanced(SDL2_DISABLE_INSTALL)
    mark_as_advanced(SDL2_DISABLE_SDL2MAIN)
    mark_as_advanced(SDL2_DISABLE_UNINSTALL)
    mark_as_advanced(SDL_ARMNEON)
    mark_as_advanced(SDL_ARMSIMD)
    mark_as_advanced(SDL_ASAN)
    mark_as_advanced(SDL_DUMMYVIDEO)
    mark_as_advanced(SDL_HIDAPI)
    mark_as_advanced(SDL_HIDAPI_JOYSTICK)
    mark_as_advanced(SDL_INSTALL_TESTS)
    mark_as_advanced(SDL_JACK)
    mark_as_advanced(SDL_LIBSAMPLERATE)
    mark_as_advanced(SDL_LOCALE)
    mark_as_advanced(SDL_MISC)
    mark_as_advanced(SDL_OFFSCREEN)
    mark_as_advanced(SDL_PIPEWIRE)
    mark_as_advanced(SDL_PTHREADS_SEM)
    mark_as_advanced(SDL_RENDER_METAL)
    mark_as_advanced(SDL_SNDIO_SHARED)
    mark_as_advanced(SDL_STATIC_PIC)
    mark_as_advanced(SDL_VIRTUAL_JOYSTICK)
    mark_as_advanced(SDL_X11)
    mark_as_advanced(SDL_XINPUT)
endif()

if(TORQUE_STATIC_CODE_ANALYSIS)
    addDef( "ON_FAIL_ASSERTFATAL=exit(1)" )
endif()

###############################################################################
# Include Paths
###############################################################################
addInclude("${projectSrcDir}")
addInclude("${srcDir}/")
addInclude("${libDir}/lmpg")
addInclude("${libDir}/lpng")
addInclude("${libDir}/ljpeg")
addInclude("${libDir}/lungif")
addInclude("${libDir}/zlib")
addInclude("${libDir}/") # for tinyxml
addInclude("${libDir}/tinyxml")
addInclude("${libDir}/squish")
addInclude("${libDir}/convexDecomp")
addInclude("${libDir}/libogg/include")
addInclude("${libDir}/opcode")
addInclude("${libDir}/collada/include")
addInclude("${libDir}/collada/include/1.4")
addInclude("${libDir}/assimp/include")
if(TORQUE_SDL)
   addInclude("${libDir}/nativeFileDialogs/include")
endif()
if(TORQUE_OPENGL)
	addInclude("${libDir}/glad/include")
endif()

if(UNIX AND NOT APPLE)
	addInclude("/usr/include/freetype2/freetype")
	addInclude("/usr/include/freetype2")
endif()

if(MSVC)
    # Match projectGenerator naming for executables
    set(OUTPUT_CONFIG DEBUG MINSIZEREL RELWITHDEBINFO)
    set(OUTPUT_SUFFIX DEBUG MINSIZE    OPTIMIZEDDEBUG)
    foreach(INDEX RANGE 2)
        list(GET OUTPUT_CONFIG ${INDEX} CONF)
        list(GET OUTPUT_SUFFIX ${INDEX} SUFFIX)
        set_property(TARGET ${PROJECT_NAME} PROPERTY OUTPUT_NAME_${CONF} ${PROJECT_NAME}_${SUFFIX})
    endforeach()
endif()

###############################################################################
# Project-specific configuration:
###############################################################################

include(${TORQUE_APP_DIR}/${PROJECT_NAME}.cmake OPTIONAL)

###############################################################################
# Installation
###############################################################################

if(TORQUE_TEMPLATE)
    message("Prepare Template(${TORQUE_TEMPLATE}) install...")
    file(GLOB_RECURSE INSTALL_FILES_AND_DIRS "${CMAKE_SOURCE_DIR}/Templates/${TORQUE_TEMPLATE}/game/*")

    IF( NOT TORQUE_D3D11)
        list(REMOVE_ITEM INSTALL_FILES_AND_DIRS "${CMAKE_SOURCE_DIR}/Templates/${TORQUE_TEMPLATE}/game/D3DCompiler_47.dll")
    ENDIF()
    list(REMOVE_ITEM INSTALL_FILES_AND_DIRS "${CMAKE_SOURCE_DIR}/Templates/${TORQUE_TEMPLATE}/game/main.tscript.in")

    foreach(ITEM ${INSTALL_FILES_AND_DIRS})
        get_filename_component( dir ${ITEM} DIRECTORY )
        get_filename_component( scriptName ${ITEM} NAME )
        STRING(REGEX REPLACE "${CMAKE_SOURCE_DIR}/Templates/${TORQUE_TEMPLATE}/" "${TORQUE_APP_DIR}/" INSTALL_DIR ${dir})
        STRING(REGEX REPLACE ".tscript" ".${TORQUE_SCRIPT_EXTENSION}" newScriptName ${scriptName})
        install( FILES ${ITEM} DESTINATION ${INSTALL_DIR} RENAME ${newScriptName} )
    endforeach()

    if(WIN32)
        INSTALL(FILES "${CMAKE_SOURCE_DIR}/Templates/${TORQUE_TEMPLATE}/cleanShaders.bat"     DESTINATION "${TORQUE_APP_DIR}")
        INSTALL(FILES "${CMAKE_SOURCE_DIR}/Templates/${TORQUE_TEMPLATE}/DeleteCachedDTSs.bat" DESTINATION "${TORQUE_APP_DIR}")
        INSTALL(FILES "${CMAKE_SOURCE_DIR}/Templates/${TORQUE_TEMPLATE}/DeleteDSOs.bat"       DESTINATION "${TORQUE_APP_DIR}")
        INSTALL(FILES "${CMAKE_SOURCE_DIR}/Templates/${TORQUE_TEMPLATE}/DeletePrefs.bat"      DESTINATION "${TORQUE_APP_DIR}")
    endif()
endif()

###############################################################################
# Properties folder
###############################################################################
# we only need to add libs that we add via add_subdirectory command, basics.cmake
# will take care of the other source libs added via addLib 

if(TORQUE_SFX_OPENAL AND WIN32)
    set_target_properties(OpenAL PROPERTIES FOLDER ${TORQUE_LIBS_FOLDER_NAME})
     #why is openal adding these two?
    set_target_properties(common PROPERTIES FOLDER ${TORQUE_LIBS_FOLDER_NAME})
    set_target_properties(ex-common PROPERTIES FOLDER ${TORQUE_LIBS_FOLDER_NAME})
endif()

if(TORQUE_SDL)
    # Apple config has slightly different target names
    if (APPLE)
        set_target_properties(SDL2main PROPERTIES FOLDER ${TORQUE_LIBS_FOLDER_NAME})
        set_target_properties(SDL2-static PROPERTIES FOLDER ${TORQUE_LIBS_FOLDER_NAME})
    else()
        set_target_properties(SDL2 PROPERTIES FOLDER ${TORQUE_LIBS_FOLDER_NAME})
    endif()
endif()
