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

setupVersionNumbers()

if(APPLE)
    advanced_option(AL_ALEXT_PROTOTYPES "Use Extended OpenAL options" OFF)
else()
    advanced_option(AL_ALEXT_PROTOTYPES "Use Extended OpenAL options" ON)
endif(APPLE)

if(AL_ALEXT_PROTOTYPES)
	addDef( "AL_ALEXT_PROTOTYPES" )
endif()

#hidden options
if(TORQUE_SFX_OPENAL)
    advanced_option(TORQUE_OGGVORBIS "Enable OGG Vorbis" ON)
    advanced_option(ALSOFT_EAX "Enable legacy EAX extensions" ${WIN32})
    advanced_option(ALSOFT_INSTALL_EXAMPLES "Install example programs (alplay, alstream, ...)" ON)
    advanced_option(ALSOFT_INSTALL_UTILS "Install utility programs (openal-info, alsoft-config, ...)" ON)
    advanced_option(ALSOFT_UPDATE_BUILD_VERSION "Update git build version info" ON)
    mark_as_advanced(ALSOFT_REQUIRE_OBOE)
    mark_as_advanced(ALSOFT_REQUIRE_PIPEWIRE)
    mark_as_advanced(ALSOFT_REQUIRE_RTKIT)
    mark_as_advanced(ALSOFT_REQUIRE_SSE3)
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