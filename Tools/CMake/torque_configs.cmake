################# Initialize Common Variables ###################
if(NOT DEFINED ENV{VCPKG_ROOT})
    set(VCPKG_ROOT "${CMAKE_BINARY_DIR}/vcpkg" CACHE PATH "VCPKG Root")
    if(NOT EXISTS "${VCPKG_ROOT}")    
        message(STATUS "Bootstrapping vcpkg...")
        if (GIT_IN_USE)
            execute_process(
                COMMAND git clone https://github.com/microsoft/vcpkg.git "${VCPKG_ROOT}"
                WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")
        else()
            set(VCPKG_MANIFEST_MODE OFF CACHE BOOL "Disable vcpkg manifest mode" FORCE)
            set(VCPKG_ZIP_FILE "${CMAKE_BINARY_DIR}/vcpkg.zip")
            set(VCPKG_EXTRACT_DEST "${CMAKE_BINARY_DIR}/vcpkg-extracted-temp")

            # Use file(DOWNLOAD) to fetch the source archive
            if(NOT EXISTS "${VCPKG_ZIP_FILE}")
                message(STATUS "Downloading vcpkg source archive...")
                file(DOWNLOAD "https://github.com/microsoft/vcpkg/archive/refs/heads/master.zip" "${VCPKG_ZIP_FILE}"
                SHOW_PROGRESS)
                message(STATUS "Downloading vcpkg source archive... done")
            endif()

            # Use file(ARCHIVE_EXTRACT) to unzip the source
            if(NOT EXISTS "${VCPKG_EXTRACT_DEST}")
                message(STATUS "Extracting vcpkg archive...")
                file(ARCHIVE_EXTRACT INPUT "${VCPKG_ZIP_FILE}" DESTINATION "${VCPKG_EXTRACT_DEST}" )

                # Move the extracted content (which is in a directory like vcpkg-master)
                # to the desired VCPKG_ROOT path defined in your original script.
                file(GLOB VCPKG_SOURCE_DIR_TMP "${VCPKG_EXTRACT_DEST}/vcpkg-*")
                file(RENAME "${VCPKG_SOURCE_DIR_TMP}" "${VCPKG_ROOT}")
                message(STATUS "Extracting vcpkg archive... done")
            endif()
        endif()
        if(WIN32)
            execute_process(COMMAND "${VCPKG_ROOT}/bootstrap-vcpkg.bat")
        else()
            execute_process(COMMAND "${VCPKG_ROOT}/bootstrap-vcpkg.sh")
        endif()
	endif()
else()
	file(TO_CMAKE_PATH $ENV{VCPKG_ROOT} VCPKG_ROOT)
endif()
set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")
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

set(VCPKG_OVERLAY_TRIPLETS "${CMAKE_SOURCE_DIR}/Tools/CMake/vcpkg/triplets" CACHE STRING "")
set(VCPKG_OVERLAY_PORTS "${CMAKE_SOURCE_DIR}/Tools/CMake/vcpkg/ports" CACHE STRING "")
set(VCPKG_INSTALL_OPTIONS "--clean-after-build" CACHE STRING "")
set(ENV{VCPKG_LIB_SOURCE_ROOT} "${CMAKE_SOURCE_DIR}/Engine/lib")
set(ENV{VCPKG_KEEP_ENV_VARS} "VCPKG_LIB_SOURCE_ROOT")
# All include directories to search. Modules should append to this when they want includes to point
# into themselves.
set(TORQUE_INCLUDE_DIRECTORIES "")
if (NOT GIT_IN_USE)
    execute_process(
        COMMAND vcpkg install 
        --classic
        --triplet=${VCPKG_TARGET_TRIPLET}
        --overlay-ports=${VCPKG_OVERLAY_PORTS}
        --overlay-triplets=${VCPKG_OVERLAY_TRIPLETS}
        libflac libogg libsndfile[external-libs] libtheora libvorbis opus
        WORKING_DIRECTORY ${VCPKG_ROOT})
endif()
# All library binaries to install. Modules should append to this the path of any library binaries (.so, .dylib, .dll)
# that should be installed next to the executable.
set(TORQUE_ADDITIONAL_LIBRARY_BINARIES "")

# All compile definitions. Modules should append to this if there is any special defines needed.
set(TORQUE_COMPILE_DEFINITIONS ICE_NO_DLL PCRE_STATIC TORQUE_ADVANCED_LIGHTING TORQUE_SHADERGEN
							   TORQUE_OPCODE TORQUE_ASSIMP TORQUE_SDL TORQUE_COLLADA
							   TORQUE_UNICODE UNICODE _UNICODE)

# All link libraries. Modules should append to this the path to specify additional link libraries (.a, .lib, .dylib, .so)
set(TORQUE_LINK_LIBRARIES png_static tinyxml2 collada squish opcode assimp SDL2 glad pcre convexMath zlib)

if(TORQUE_TESTING)
set(TORQUE_LINK_LIBRARIES ${TORQUE_LINK_LIBRARIES} gtest gmock)
endif()

if(NOT WIN32)
   set(WIN32 OFF CACHE BOOL "" FORCE)
endif()
mark_as_advanced(WIN32)

#general
advanced_option(TORQUE_MULTITHREAD "Multi Threading" ON)
advanced_option(TORQUE_DISABLE_MEMORY_MANAGER "Disable memory manager" ON)
set(TORQUE_ENTRY_FUNCTION "" CACHE STRING "Specify a console function to execute instead of looking for a main.tscript file")
mark_as_advanced(TORQUE_ENTRY_FUNCTION)

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
