################# Initialize Common Variables ###################

# All include directories to search. Modules should append to this when they want includes to point
# into themselves.
set(TORQUE_INCLUDE_DIRECTORIES "")

# All library binaries to install. Modules should append to this the path of any library binaries (.so, .dylib, .dll)
# that should be installed next to the executable.
set(TORQUE_ADDITIONAL_LIBRARY_BINARIES "")

# All compile definitions. Modules should append to this if there is any special defines needed.
set(TORQUE_COMPILE_DEFINITIONS ICE_NO_DLL PCRE_STATIC TORQUE_ADVANCED_LIGHTING TORQUE_SHADERGEN
							   TORQUE_OPCODE TORQUE_ASSIMP TORQUE_SDL TORQUE_COLLADA
							   TORQUE_UNICODE UNICODE _UNICODE)

# All link libraries. Modules should append to this the path to specify additional link libraries (.a, .lib, .dylib, .so)
set(TORQUE_LINK_LIBRARIES tinyxml collada ljpeg squish png_static opcode assimp
                          SDL2 glad pcre convexDecomp zlib)

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
advanced_option(TORQUE_ENABLE_PROFILER "Enable or disable the profiler" OFF)
advanced_option(TORQUE_SHOW_LEGACY_FILE_FIELDS "If on, shows legacy direct file path fields in the inspector." OFF)

#testing
advanced_option(TORQUE_TESTING "Unit test build" OFF)

setupVersionNumbers()
