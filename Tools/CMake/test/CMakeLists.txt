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

addLib(gtest)
addLib(gmock)
addLib(gmock_main)
addLib(${TORQUE_APP_NAME})
addDef( "_VARIADIC_MAX" 10 )
if(MSVC)
set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${TORQUE_APP_NAME}_TEST)
endif()
