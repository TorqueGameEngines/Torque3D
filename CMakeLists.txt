cmake_minimum_required (VERSION 3.10.2)
set (CMAKE_CXX_STANDARD 17)

# Ensure multi-core compilation is enabled for everything
add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)

project(Torque3D)

# An application name must be set first
set(TORQUE_APP_NAME "" CACHE STRING "the app name")
if("${TORQUE_APP_NAME}" STREQUAL "")
	message(FATAL_ERROR "Please set TORQUE_APP_NAME first")
endif()

# Once an app name is determined, we know what our project pathing structure should look like
set(TORQUE_APP_ROOT_DIRECTORY "${CMAKE_SOURCE_DIR}/My Projects/${TORQUE_APP_NAME}")
set(TORQUE_APP_GAME_DIRECTORY "${TORQUE_APP_ROOT_DIRECTORY}/game")

# Ensure all possible configurations end up in the project directory
set(CMAKE_INSTALL_PREFIX "${TORQUE_APP_ROOT_DIRECTORY}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${TORQUE_APP_GAME_DIRECTORY}")
foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
    string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} "${TORQUE_APP_GAME_DIRECTORY}" )
endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )

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

set(TORQUE_MODULE_USER_PATH "" CACHE PATH "Additional search path for modules aside from the default Tools/CMake/modules.")
mark_as_advanced(TORQUE_MODULE_USER_PATH)

option(TORQUE_USE_ZENITY "use the Zenity backend for NFD" OFF)
mark_as_advanced(TORQUE_USE_ZENITY)

option(TORQUE_SHOW_LEGACY_FILE_FIELDS "If on, shows legacy direct file path fields in the inspector." OFF)
mark_as_advanced(TORQUE_SHOW_LEGACY_FILE_FIELDS)

option(TORQUE_SFX_VORBIS "Vorbis Sound" ON)
mark_as_advanced(TORQUE_SFX_VORBIS)

option(TORQUE_THEORA "Theora Video Support" ON)
mark_as_advanced(TORQUE_THEORA)

option(TORQUE_ADVANCED_LIGHTING "Advanced Lighting" ON)
mark_as_advanced(TORQUE_ADVANCED_LIGHTING)

option(TORQUE_BASIC_LIGHTING "Basic Lighting" ON)
mark_as_advanced(TORQUE_APP_PASSWORD)

option(TORQUE_DYNAMIC_LIBRARY "Whether or not to build Torque as a dynamic library." OFF)
mark_as_advanced(TORQUE_DYNAMIC_LIBRARY)

set(TORQUE_APP_PASSWORD "changeme" CACHE STRING "zip file password")

if(WIN32)
	option(TORQUE_OPENGL "Allow OpenGL render" ON)
else()
	set(TORQUE_OPENGL ON) # we need OpenGL to render on Linux/Mac
endif()

if(WIN32)
	option(TORQUE_D3D11 "Allow Direct3D 11 render" ON)
endif()

include("${CMAKE_SOURCE_DIR}/Tools/CMake/basics.cmake")
setupVersionNumbers()

# Install Torque template
if(NOT TORQUE_TEMPLATE)
    set(TORQUE_TEMPLATE "BaseGame" CACHE STRING "the template to use")
endif()

if (NOT TORQUE_INSTALLED_TEMPLATE)
    installTemplate(${TORQUE_TEMPLATE})
    set(TORQUE_INSTALLED_TEMPLATE TRUE CACHE BOOL "Whether or not the game template is installed. This may be reset to false (or removed) to force a reinstall.")
endif(NOT TORQUE_INSTALLED_TEMPLATE)

# Generate torqueConfig.h in our temp directory
configure_file("${CMAKE_SOURCE_DIR}/Tools/CMake/torqueConfig.h.in" "${CMAKE_BINARY_DIR}/temp/torqueConfig.h")

add_subdirectory(Engine)
