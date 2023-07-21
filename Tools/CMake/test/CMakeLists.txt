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

cmake_minimum_required(VERSION 3.10)

project(${TORQUE_APP_NAME}_TEST)

enable_testing()

include(GoogleTest)

addPath(${srcDir}/testing/)
#not sure if these includes are needed??
addInclude(${libDir}/) # for tinyxml
addInclude(${libDir}/tinyxml)
addInclude("${srcDir}/")
addInclude("${projectSrcDir}")
addInclude(${srcDir}/testing)

if(MSVC)
set(CMAKE_EXE_LINKER_FLAGS "/SUBSYSTEM:CONSOLE")
endif()

finishExecutable()
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

addLib(gtest)
addLib(gmock)
addLib(${TORQUE_APP_NAME})
addDef( "_VARIADIC_MAX" 10 )
addDef(TORQUE_DEBUG Debug)
addDef(TORQUE_RELEASE "RelWithDebInfo;Release")
if(MSVC)
set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${TORQUE_APP_NAME}_TEST)
endif()
