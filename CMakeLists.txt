cmake_minimum_required (VERSION 3.10.2)
set (CMAKE_CXX_STANDARD 17)

project(Torque3D)

# An application name must be set first
set(TORQUE_APP_NAME "" CACHE STRING "the app name")
if("${TORQUE_APP_NAME}" STREQUAL "")
	message(FATAL_ERROR "Please set TORQUE_APP_NAME first")
endif()

# Detect CPU Information
if (CMAKE_SYSTEM_PROCESSOR MATCHES "arm")
    if( CMAKE_CXX_SIZEOF_DATA_PTR EQUAL 8 )
        set( TORQUE_CPU_ARM64 ON )
    elseif( CMAKE_CXX_SIZEOF_DATA_PTR EQUAL 4 )
        set( TORQUE_CPU_ARM32 ON )
    endif()
else()
    if( CMAKE_CXX_SIZEOF_DATA_PTR EQUAL 8 )
        set( TORQUE_CPU_X64 ON )
    elseif( CMAKE_CXX_SIZEOF_DATA_PTR EQUAL 4 )
        set( TORQUE_CPU_X32 ON )
    endif()
endif()

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

include("${CMAKE_SOURCE_DIR}/Tools/CMake/basics.cmake")
setupVersionNumbers()

# Install Torque template
if(NOT TORQUE_TEMPLATE)
    set(TORQUE_TEMPLATE "BaseGame" CACHE STRING "the template to use")
endif()
installTemplate(${TORQUE_TEMPLATE})

# Generate torqueConfig.h in our temp directory
CONFIGURE_FILE("${CMAKE_SOURCE_DIR}/Tools/CMake/torqueConfig.h.in" "${CMAKE_BINARY_DIR}/temp/torqueConfig.h")

add_subdirectory(Engine)
