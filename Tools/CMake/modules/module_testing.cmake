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

option(TORQUE_TESTING "Enable unit test module" OFF)
mark_as_advanced(TORQUE_TESTING)

if(TORQUE_TESTING)
    message("Enabling Unit Testing")
    # Project defines
    set(TORQUE_COMPILE_DEFINITIONS ${TORQUE_COMPILE_DEFINITIONS} TORQUE_TESTS_ENABLED)
    set(TORQUE_COMPILE_DEFINITIONS ${TORQUE_COMPILE_DEFINITIONS} "_VARIADIC_MAX=10")
    
    file(GLOB_RECURSE TORQUE_TESTS_SOURCES "${CMAKE_SOURCE_DIR}/Engine/source/testing/*.cpp" "${CMAKE_SOURCE_DIR}/Engine/source/testing/*.h" )
    set(TORQUE_SOURCE_FILES ${TORQUE_SOURCE_FILES} ${TORQUE_TESTS_SOURCES})
    
    file(GLOB_RECURSE TORQUE_GTESTS_SOURCES "${CMAKE_SOURCE_DIR}/Engine/lib/gtest/*.cpp" "${CMAKE_SOURCE_DIR}/Engine/lib/gtest/*.h" )
    set(TORQUE_SOURCE_FILES ${TORQUE_SOURCE_FILES} ${TORQUE_GTESTS_SOURCES})
endif()
