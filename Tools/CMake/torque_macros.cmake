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
################# Helper Functions ###################
macro(setupVersionNumbers)
    set(TORQUE_APP_VERSION_MAJOR 1 CACHE STRING "")
    set(TORQUE_APP_VERSION_MINOR 0 CACHE STRING "")
    set(TORQUE_APP_VERSION_PATCH 0 CACHE STRING "")
    set(TORQUE_APP_VERSION_TWEAK 0 CACHE STRING "")

    mark_as_advanced(TORQUE_APP_VERSION_TWEAK)
    MATH(EXPR TORQUE_APP_VERSION "${TORQUE_APP_VERSION_MAJOR} * 1000 + ${TORQUE_APP_VERSION_MINOR} * 100 + ${TORQUE_APP_VERSION_PATCH} * 10 + ${TORQUE_APP_VERSION_TWEAK}")
    set(TORQUE_APP_VERSION_STRING "${TORQUE_APP_VERSION_MAJOR}.${TORQUE_APP_VERSION_MINOR}.${TORQUE_APP_VERSION_PATCH}.${TORQUE_APP_VERSION_TWEAK}")
endmacro()

function(installTemplate templateName)
  message("Prepare Template(${templateName}) install...")

  add_subdirectory("${CMAKE_SOURCE_DIR}/Templates/${templateName}")
endfunction()

MACRO(SUBDIRLIST result curdir)
  FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
  SET(dirlist "")
  FOREACH(child ${children})
    IF(IS_DIRECTORY ${curdir}/${child})
      LIST(APPEND dirlist ${child})
    ENDIF()
  ENDFOREACH()
  SET(${result} ${dirlist})
ENDMACRO()

# Helper function to add a directory to the TORQUE_SOURCE_FILES variable. It automatically searches for .cpp and .h files in the
# specified directory then adds them to the TORQUE_SOURCE_FILES variable.
macro (torqueAddSourceDirectories)
  foreach(ARGUMENT ${ARGV})
    file(GLOB SCANNED_SOURCE_FILES "${ARGUMENT}/*.cpp")
    file(GLOB SCANNED_INCLUDE_FILES "${ARGUMENT}/*.h")

    if (APPLE)
      file(GLOB SCANNED_MAC_FILES "${ARGUMENT}/*.mm")
    endif (APPLE)

    # Set in both current and parent scope so this macro can be used from loaded modules
    set(TORQUE_SOURCE_FILES ${TORQUE_SOURCE_FILES} ${SCANNED_SOURCE_FILES} ${SCANNED_INCLUDE_FILES} ${SCANNED_MAC_FILES})
    set(TORQUE_SOURCE_FILES ${TORQUE_SOURCE_FILES} PARENT_SCOPE)
  endforeach()
endmacro (torqueAddSourceDirectories)

################# Set Conditional Engine Defines ###################
macro (forwardDef flag)
    if (${flag})
        set(TORQUE_COMPILE_DEFINITIONS ${TORQUE_COMPILE_DEFINITIONS} ${flag})
    endif()
endmacro(forwardDef)

macro (advanced_option flag description state)
    option(${flag} ${description} ${state})
    mark_as_advanced(${flag})
endmacro(advanced_option)
################# additional preprocessor defines ###################
macro(__addDef def config)
    # two possibilities: a) target already known, so add it directly, or b) target not yet known, so add it to its cache
    if(TARGET ${PROJECT_NAME})
        #message(STATUS "directly applying defs: ${PROJECT_NAME} with config ${config}: ${def}")
        if("${config}" STREQUAL "")
            set_property(TARGET ${PROJECT_NAME} APPEND PROPERTY COMPILE_DEFINITIONS ${def})
        else()
            set_property(TARGET ${PROJECT_NAME} APPEND PROPERTY COMPILE_DEFINITIONS $<$<CONFIG:${config}>:${def}>)
        endif()
    else()
        if("${config}" STREQUAL "")
            list(APPEND ${PROJECT_NAME}_defs_ ${def})
        else()
            list(APPEND ${PROJECT_NAME}_defs_ $<$<CONFIG:${config}>:${def}>)
        endif()
        #message(STATUS "added definition to cache: ${PROJECT_NAME}_defs_: ${${PROJECT_NAME}_defs_}")
    endif()
endmacro()

# adds a definition: argument 1: Nothing(for all), _DEBUG, _RELEASE, <more build configurations>
macro(addDef def)
    set(def_configs "")
    if(${ARGC} GREATER 1)
        foreach(config ${ARGN})
            __addDef(${def} ${config})
        endforeach()
    else()
        __addDef(${def} "")
    endif()
endmacro()

# this applies cached definitions onto the target must come *after* target_compile_definitions
macro(append_defs)
    if(DEFINED ${PROJECT_NAME}_defs_)
        set_property(TARGET ${PROJECT_NAME} APPEND PROPERTY COMPILE_DEFINITIONS ${${PROJECT_NAME}_defs_})
        #message(STATUS "applying defs to project ${PROJECT_NAME}: ${${PROJECT_NAME}_defs_}")
    else()
        #message(STATUS "NO ${PROJECT_NAME}_defs_ defined!")
    endif()    
endmacro()

################# file filtering ###################
macro (filterOut)
  foreach(ARGUMENT ${ARGV})
    list(REMOVE_ITEM TORQUE_SOURCE_FILES "${CMAKE_SOURCE_DIR}/Engine/source/${ARGUMENT}")
  endforeach()
endmacro (filterOut)

################# apple frameworks ###################
macro(addFramework framework)
	if (APPLE)
		set(TORQUE_LINK_LIBRARIES ${TORQUE_LINK_LIBRARIES} "-framework ${framework}")
	endif()
endmacro()