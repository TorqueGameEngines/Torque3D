################# Initialize Common Variables ###################
# Pin to a specific vcpkg release so installs are reproducible without
# needing git to resolve a baseline. Bump this when you want newer ports.
set(TORQUE_VCPKG_TAG "2025.06.13" CACHE STRING "vcpkg release tag to bootstrap")
set(VCPKG_ROOT "${CMAKE_SOURCE_DIR}/Tools/CMake/vcpkg/local" CACHE PATH "VCPKG Root")

if(NOT EXISTS "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
    message(STATUS "vcpkg not found at ${VCPKG_ROOT} — fetching ${TORQUE_VCPKG_TAG} now (one-time)...")

    if(GIT_IN_USE)
        execute_process(
            COMMAND git clone --branch ${TORQUE_VCPKG_TAG} --depth 1
                    https://github.com/microsoft/vcpkg.git "${VCPKG_ROOT}"
            RESULT_VARIABLE _TORQUE_VCPKG_FETCH_RESULT)
    else()
        set(VCPKG_ZIP_FILE "${CMAKE_BINARY_DIR}/vcpkg-${TORQUE_VCPKG_TAG}.zip")
        set(VCPKG_EXTRACT_DEST "${CMAKE_BINARY_DIR}/vcpkg-extracted-temp")

        if(NOT EXISTS "${VCPKG_ZIP_FILE}")
            message(STATUS "Downloading vcpkg ${TORQUE_VCPKG_TAG} archive...")
            file(DOWNLOAD "https://github.com/microsoft/vcpkg/archive/refs/tags/${TORQUE_VCPKG_TAG}.zip"
                 "${VCPKG_ZIP_FILE}" SHOW_PROGRESS
                 STATUS _TORQUE_VCPKG_DOWNLOAD_STATUS)
            list(GET _TORQUE_VCPKG_DOWNLOAD_STATUS 0 _TORQUE_VCPKG_FETCH_RESULT)
        else()
            set(_TORQUE_VCPKG_FETCH_RESULT 0)
        endif()

        if(_TORQUE_VCPKG_FETCH_RESULT EQUAL 0)
            file(ARCHIVE_EXTRACT INPUT "${VCPKG_ZIP_FILE}" DESTINATION "${VCPKG_EXTRACT_DEST}")
            file(GLOB VCPKG_SOURCE_DIR_TMP "${VCPKG_EXTRACT_DEST}/vcpkg-*")
            file(RENAME "${VCPKG_SOURCE_DIR_TMP}" "${VCPKG_ROOT}")
            file(REMOVE_RECURSE "${VCPKG_EXTRACT_DEST}")
        endif()
    endif()

    if(NOT EXISTS "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
        message(FATAL_ERROR
            "Could not fetch vcpkg into ${VCPKG_ROOT}. If this machine has no network "
            "access either, copy an existing Tools/CMake/vcpkg checkout from a teammate "
            "or your build server instead.")
    endif()

    message(STATUS "vcpkg fetched into ${VCPKG_ROOT} — future configures will skip this step.")
endif()

# The vcpkg *tool* binary is platform-specific and isn't fetched/committed by
# the step above — bootstrap builds/downloads it locally, once per platform.
if(WIN32)
    set(_TORQUE_VCPKG_EXE "${VCPKG_ROOT}/vcpkg.exe")
else()
    set(_TORQUE_VCPKG_EXE "${VCPKG_ROOT}/vcpkg")
endif()

if(NOT EXISTS "${_TORQUE_VCPKG_EXE}")
    message(STATUS "Bootstrapping vcpkg tool (one-time per platform)...")
    if(WIN32)
        execute_process(COMMAND "${VCPKG_ROOT}/bootstrap-vcpkg.bat")
    else()
        execute_process(COMMAND "${VCPKG_ROOT}/bootstrap-vcpkg.sh")
    endif()
    if(NOT EXISTS "${_TORQUE_VCPKG_EXE}")
        message(FATAL_ERROR "Failed to bootstrap the vcpkg tool — see output above.")
    endif()
endif()

set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")
set(VCPKG_MANIFEST_MODE OFF CACHE BOOL "Disable vcpkg manifest mode" FORCE)
set(VCPKG_INSTALL_OPTIONS "--clean-after-build" CACHE STRING "")
set(VCPKG_OVERLAY_TRIPLETS "${CMAKE_SOURCE_DIR}/Tools/CMake/vcpkg/triplets" CACHE STRING "")
set(ENV{VCPKG_LIB_SOURCE_ROOT} "${CMAKE_SOURCE_DIR}/Engine/lib")
set(ENV{VCPKG_KEEP_ENV_VARS} "VCPKG_LIB_SOURCE_ROOT")
set(TORQUE_VCPKG_ASSET_CACHE "${CMAKE_SOURCE_DIR}/Tools/CMake/vcpkg/vcpkg-assets" CACHE PATH "Local directory of cached vcpkg port source archives")
file(MAKE_DIRECTORY "${TORQUE_VCPKG_ASSET_CACHE}")
set(ENV{X_VCPKG_ASSET_SOURCES} "clear;x-azurl,file:///${TORQUE_VCPKG_ASSET_CACHE},,readwrite")

if(WIN32)
    if(GIT_CI_BUILD)
        set(VCPKG_TARGET_TRIPLET "x64-windows-mixed-release" CACHE STRING "")
    else()
        set(VCPKG_TARGET_TRIPLET "x64-windows-mixed" CACHE STRING "")
    endif()
else()
    if(APPLE)
        if(GIT_CI_BUILD)
            set(VCPKG_TARGET_TRIPLET "universal-osx-11-release" CACHE STRING "")
        else()
            set(VCPKG_TARGET_TRIPLET "universal-osx-11" CACHE STRING "")
        endif()
    endif(APPLE)
    if(UNIX AND NOT APPLE)
        if(GIT_CI_BUILD)
            set(VCPKG_TARGET_TRIPLET "x64-linux-mixed-release" CACHE STRING "")
        else()
            set(VCPKG_TARGET_TRIPLET "x64-linux-mixed" CACHE STRING "")
        endif()
    endif()
endif()

# Single source of truth for everything we get from vcpkg. Add to this list
# as you migrate more dependencies — there is no separate manifest to keep
# in sync any more. (assimp stays out of this list; it's still built from
# Engine/lib/assimp via add_subdirectory.)
set(TORQUE_VCPKG_PACKAGES
    zlib
    libpng
    sdl2
    openal-soft
    pcre
    tinyxml2
    bullet3
    recastnavigation
    libogg libvorbis libflac opus libtheora
    libsndfile[core,external-libs] 
    libsquish
)
if(TORQUE_TESTING)
    list(APPEND TORQUE_VCPKG_PACKAGES gtest)
endif()
if(UNIX AND NOT APPLE)
    list(APPEND TORQUE_VCPKG_PACKAGES freetype)
endif()

execute_process(
    COMMAND "${VCPKG_ROOT}/vcpkg" install
        --triplet=${VCPKG_TARGET_TRIPLET}
        --overlay-ports=${VCPKG_OVERLAY_PORTS}
        --overlay-triplets=${VCPKG_OVERLAY_TRIPLETS}
        ${TORQUE_VCPKG_PACKAGES}
    WORKING_DIRECTORY ${VCPKG_ROOT}
    RESULT_VARIABLE TORQUE_VCPKG_INSTALL_RESULT)
if(NOT TORQUE_VCPKG_INSTALL_RESULT EQUAL 0)
    message(FATAL_ERROR "vcpkg install failed (see above) — third-party dependencies could not be installed.")
endif()

# All include directories to search...
set(TORQUE_INCLUDE_DIRECTORIES "")
set(TORQUE_ADDITIONAL_LIBRARY_BINARIES "")
set(TORQUE_COMPILE_DEFINITIONS ICE_NO_DLL PCRE_STATIC TORQUE_ADVANCED_LIGHTING TORQUE_SHADERGEN
                               TORQUE_OPCODE TORQUE_ASSIMP TORQUE_SDL TORQUE_COLLADA
                               TORQUE_UNICODE UNICODE _UNICODE)

set(TORQUE_LINK_LIBRARIES collada opcode assimp convexMath glad)
# All library binaries to install. Modules should append to this the path of any library binaries (.so, .dylib, .dll)
# that should be installed next to the executable.
set(TORQUE_ADDITIONAL_LIBRARY_BINARIES "")

# All compile definitions. Modules should append to this if there is any special defines needed.
set(TORQUE_COMPILE_DEFINITIONS ICE_NO_DLL PCRE_STATIC TORQUE_ADVANCED_LIGHTING TORQUE_SHADERGEN
							   TORQUE_OPCODE TORQUE_ASSIMP TORQUE_SDL TORQUE_COLLADA
							   TORQUE_UNICODE UNICODE _UNICODE)


if(NOT WIN32)
   set(WIN32 OFF CACHE BOOL "" FORCE)
endif()
mark_as_advanced(WIN32)

#general
advanced_option(TORQUE_MULTITHREAD "Multi Threading" ON)
advanced_option(TORQUE_DISABLE_MEMORY_MANAGER "Disable memory manager" ON)
set(TORQUE_ENTRY_FUNCTION "" CACHE STRING "Specify a console function to execute instead of looking for a main.tscript file")
mark_as_advanced(TORQUE_ENTRY_FUNCTION)

set(TORQUE_DTS_VERSION "29" CACHE STRING "Device Tree Source version")

set_property(CACHE TORQUE_DTS_VERSION PROPERTY STRINGS
    28 29
)

#fileIO
set(TORQUE_APP_PASSWORD "changeme" CACHE STRING "zip file password")
advanced_option(TORQUE_DISABLE_VIRTUAL_MOUNT_SYSTEM "Disable virtual mount system" OFF)
advanced_option(TORQUE_DISABLE_FIND_ROOT_WITHIN_ZIP "Disable reading root path from zip. Zips will be mounted in-place with file name as directory name." ON)
advanced_option(TORQUE_ZIP_DISK_LAYOUT "All zips must be placed in the executable directory and contain full paths to the files." OFF)
advanced_option(TORQUE_POSIX_PATH_CASE_INSENSITIVE "POSIX Pathing Case Insensitivity" ON)
advanced_option(TORQUE_ZIP_PATH_CASE_INSENSITIVE "ZIP Pathing Case Insensitivity" ON)
advanced_option(TORQUE_USE_ZENITY "use the Zenity backend for NFD" OFF)
advanced_option(TORQUE_SECURE_VFS "Secure VFS configuration. Arbitrary script access to file system will be heavily restricted." OFF)

#sfx
advanced_option(TORQUE_SFX_VORBIS "Vorbis Sound" ON)
advanced_option(TORQUE_THEORA "Theora Video Support" ON)
advanced_option(TORQUE_SFX_OPENAL "OpenAL Sound" ON)

#gfx
advanced_option(TORQUE_DEBUG_GFX_MODE "triggers graphics debug mode" OFF)
advanced_option(TORQUE_ADVANCED_LIGHTING "Advanced Lighting" ON)
advanced_option(TORQUE_BASIC_LIGHTING "Basic Lighting" ON)
advanced_option(TORQUE_OPENGL "Allow OpenGL render" ON) # we need OpenGL to render on Linux/Mac
if(WIN32)
	advanced_option(TORQUE_D3D11 "Allow Direct3D 11 render" ON)
	addDef(TORQUE_D3D11)
endif()

#mode
advanced_option(TORQUE_NO_DSO_GENERATION "skip storing compiled scripts" ON)
advanced_option(TORQUE_DYNAMIC_LIBRARY "Whether or not to build Torque as a dynamic library." OFF)
advanced_option(TORQUE_PLAYER "Playback only?" OFF)
advanced_option(TORQUE_DEBUG "T3D Debug mode" OFF)
#option(DEBUG_SPEW "more debug" OFF)
advanced_option(TORQUE_SHIPPING "T3D Shipping build?" OFF)
advanced_option(TORQUE_DEDICATED "Torque dedicated" OFF) # disables compiling in gfx and sfx frontend functionality

#tools
advanced_option(TORQUE_DEBUG_NET "debug network" OFF)
advanced_option(TORQUE_DEBUG_NET_MOVES "debug network moves" OFF)
advanced_option(TORQUE_ENABLE_ASSERTS "enables or disable asserts" OFF)
advanced_option(TORQUE_TOOLS "Enable or disable the tools" ON)
advanced_option(TORQUE_TOOLS_EXT_COMMANDS "Enable or disable some extended functionality like shell commands or free write access" OFF)
advanced_option(TORQUE_ENABLE_PROFILER "Enable or disable the profiler" OFF)
advanced_option(TORQUE_SHOW_LEGACY_FILE_FIELDS "If on, shows legacy direct file path fields in the inspector." OFF)
advanced_option(USE_TEMPLATE_MATRIX "Set to true to use the new templated matrix class(still in beta)." OFF)
#testing
advanced_option(TORQUE_TESTING "Unit test build" OFF)

setupVersionNumbers()
