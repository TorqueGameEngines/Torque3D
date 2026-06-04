project(${TORQUE_APP_NAME})

# Enable ObjectiveC compilation when compiling for Apple platforms
if (APPLE)
	enable_language(OBJC)
endif (APPLE)

# ------------------------------------------------------------------
# Find all dependencies (using vcpkg's toolchain integration)
# ------------------------------------------------------------------
find_package(Ogg CONFIG REQUIRED)
find_package(Vorbis CONFIG REQUIRED)
find_package(FLAC CONFIG REQUIRED)
find_package(Opus CONFIG REQUIRED)
find_package(unofficial-theora CONFIG REQUIRED)
find_package(SndFile CONFIG REQUIRED)
set(TORQUE_LINK_THIRDPARTY ${TORQUE_LINK_THIRDPARTY}
    Ogg::ogg
    Vorbis::vorbis
    Vorbis::vorbisfile
    FLAC::FLAC
    Opus::opus
    unofficial::theora::theora unofficial::theora::theoradec unofficial::theora::theoraenc
    SndFile::sndfile
)
################# Helper Function Calls ###################
forwardDef(TORQUE_OPENGL)
forwardDef(TORQUE_D3D11)
forwardDef(TORQUE_ADVANCED_LIGHTING)
forwardDef(TORQUE_BASIC_LIGHTING)
set(TORQUE_SDL ON) # we need sdl to do our platform interop
forwardDef(TORQUE_SDL)

if(TORQUE_TESTING)
set(TORQUE_COMPILE_DEFINITIONS ${TORQUE_COMPILE_DEFINITIONS} TORQUE_TESTS_ENABLED)
set(TORQUE_COMPILE_DEFINITIONS ${TORQUE_COMPILE_DEFINITIONS} "_VARIADIC_MAX=10")
endif()

# On Windows we disable CRT Security warnings - this comes from recommendations to use non-portable functions.
if (WIN32)
	set(TORQUE_COMPILE_DEFINITIONS ${TORQUE_COMPILE_DEFINITIONS} _CRT_SECURE_NO_WARNINGS WIN32)
endif (WIN32)

if (APPLE)
  set(TORQUE_COMPILE_DEFINITIONS ${TORQUE_COMPILE_DEFINITIONS} __MACOSX__)
elseif (UNIX)
  set(TORQUE_COMPILE_DEFINITIONS ${TORQUE_COMPILE_DEFINITIONS} __linux__)
endif (APPLE)

################# Set Engine Linkages ###################

# When on Windows, we need to link against winsock and windows codecs
if (WIN32)
	set(TORQUE_SOURCE_FILES ${TORQUE_SOURCE_FILES} ${TORQUE_PLATFORM_WIN_SOURCES})
endif (WIN32)

# Linux requires X11 & freetype
if (UNIX AND NOT APPLE)
	set(TORQUE_SOURCE_FILES ${TORQUE_SOURCE_FILES} ${TORQUE_PLATFORM_X11_SOURCES})
	find_package(Freetype REQUIRED)
	set(TORQUE_INCLUDE_DIRECTORIES ${TORQUE_INCLUDE_DIRECTORIES} ${FREETYPE_INCLUDE_DIRS})
endif (UNIX AND NOT APPLE)

################# Collect Source Files ###################

# Handle app
torqueAddSourceDirectories("app" "app/net")

# Handle console
torqueAddSourceDirectories("console")
torqueAddSourceDirectories("console/torquescript")
set(TORQUE_INCLUDE_DIRECTORIES ${TORQUE_INCLUDE_DIRECTORIES} "ts/vhacd")
# Handle Platform
torqueAddSourceDirectories("platform" "platform/threads" "platform/async"
                                  "platform/input" "platform/output")

torqueAddSourceDirectories("platform/nativeDialogs")
# Handle T3D
torqueAddSourceDirectories( "T3D" "T3D/AI" "T3D/assets" "T3D/decal" "T3D/examples" "T3D/fps" "T3D/fx" 
                           "T3D/gameBase" "T3D/gameBase/std"
                           "T3D/lighting"
                           "T3D/physics"
#                          "T3D/components" "T3D/sceneComponent" "T3D/systems" "T3D/gameOBjects" 
                           "T3D/sfx" "T3D/turret" "T3D/vehicles")

# Handle TS
torqueAddSourceDirectories("ts" "ts/collada" "ts/assimp" "ts/loader" "ts/arch")

# Handle SFX - OpenAL is handled as a module later on
torqueAddSourceDirectories("sfx" "sfx/media" "sfx/null")
if(TORQUE_SFX_OPENAL AND NOT TORQUE_DEDICATED)
    torqueAddSourceDirectories("sfx/openal")
    if(WIN32)
      torqueAddSourceDirectories("sfx/openal/win32")
    elseif(UNIX AND NOT APPLE)
        torqueAddSourceDirectories("sfx/openal/linux")
    elseif(APPLE)
        torqueAddSourceDirectories("sfx/openal/mac")
    endif()
endif()
# Handle GFX
torqueAddSourceDirectories("gfx" "gfx/Null" "gfx/test" "gfx/bitmap" "gfx/bitmap/loaders" "gfx/bitmap/loaders/ies"
                             "gfx/util" "gfx/video" "gfx/sim" )

# add the stb headers
set(TORQUE_INCLUDE_DIRECTORIES ${TORQUE_INCLUDE_DIRECTORIES} "gfx/bitmap/loaders/stb")

if (TORQUE_OPENGL)
  torqueAddSourceDirectories("gfx/gl" "gfx/gl/sdl" "gfx/gl/tGL")
endif (TORQUE_OPENGL)

if (WIN32 AND TORQUE_D3D11)
  torqueAddSourceDirectories("gfx/D3D11")
endif (WIN32 AND TORQUE_D3D11)

# Handle core
torqueAddSourceDirectories("core" "core/stream" "core/strings" "core/util"
                              "core/util/journal" "core/util/zip" "core/util/zip/compressors")
# Handle GUI
torqueAddSourceDirectories("gui" "gui/buttons" "gui/containers" "gui/controls" "gui/core"
                              "gui/game" "gui/shiny" "gui/utility" "gui/3d")

# Handle postFX
torqueAddSourceDirectories("postFx")

# Handle Windowmanager
torqueAddSourceDirectories("windowManager" "windowManager/torque" "windowManager/sdl")

# Handle scene
torqueAddSourceDirectories("scene" "scene/culling" "scene/zones" "scene/mixin")

# Handle math
torqueAddSourceDirectories("math" "math/util" "math/public" "math/impl") # note impl must skip the .inl files, never use them in engine code.

# Handle persistence
set(TORQUE_INCLUDE_DIRECTORIES ${TORQUE_INCLUDE_DIRECTORIES} "persistence/rapidjson")
torqueAddSourceDirectories("persistence/taml" "persistence/taml/binary" "persistence/taml/xml" "persistence/taml/json")

# Handle Cinterface
torqueAddSourceDirectories("cinterface")

# Handle util
torqueAddSourceDirectories("util" "util/messaging")

# Handle assets
torqueAddSourceDirectories("assets")

# Handle Sim
torqueAddSourceDirectories("sim")

# Handle module
torqueAddSourceDirectories("module")

# Handle forest
torqueAddSourceDirectories("forest" "forest/ts")
if(TORQUE_OPENGL)
  torqueAddSourceDirectories("forest" "forest/glsl")
endif(TORQUE_OPENGL)
if(TORQUE_D3D11)
  torqueAddSourceDirectories("forest" "forest/hlsl")
endif(TORQUE_D3D11)

# Handle shadergen
torqueAddSourceDirectories("shaderGen")

if (WIN32 AND TORQUE_D3D11)
  torqueAddSourceDirectories("shaderGen/HLSL")
endif (WIN32 AND TORQUE_D3D11)

if (TORQUE_OPENGL)
  torqueAddSourceDirectories("shaderGen/GLSL")
endif (TORQUE_OPENGL)

# Handle terrain
torqueAddSourceDirectories("terrain")

# Handle theora
if (TORQUE_THEORA)
  torqueAddSourceDirectories("core/ogg")
  torqueAddSourceDirectories("gui/theora")
endif(TORQUE_THEORA)

if (WIN32 AND TORQUE_D3D11)
  torqueAddSourceDirectories("terrain/hlsl")
endif (WIN32 AND TORQUE_D3D11)

if (TORQUE_OPENGL)
  torqueAddSourceDirectories("terrain/glsl")
endif (TORQUE_OPENGL)

# Handle Materials
torqueAddSourceDirectories("materials")

# Handle collision
torqueAddSourceDirectories("collision")

# Handle lighting
torqueAddSourceDirectories("lighting" "lighting/common"
                                   "lighting/shadowMap")

if (TORQUE_ADVANCED_LIGHTING)
  torqueAddSourceDirectories("lighting/advanced")

	if (WIN32 AND TORQUE_D3D11)
    torqueAddSourceDirectories("lighting/advanced/hlsl")
	endif (WIN32 AND TORQUE_D3D11)

	if (TORQUE_OPENGL)
    torqueAddSourceDirectories("lighting/advanced/glsl")
	endif (TORQUE_OPENGL)
endif (TORQUE_ADVANCED_LIGHTING)

if (TORQUE_BASIC_LIGHTING)
  torqueAddSourceDirectories("lighting/basic" "lighting/basic/shadowMap")
endif (TORQUE_BASIC_LIGHTING)

# Handle environment
torqueAddSourceDirectories("environment")

# Handle renderInstance
torqueAddSourceDirectories("renderInstance")

# Handle i18n
torqueAddSourceDirectories("i18n")

# Begin handling platform specific stuff
# Handle Platform POSIX
if (UNIX)
	torqueAddSourceDirectories("platformPOSIX")

  if(NOT APPLE)
    if (TORQUE_CPU_X32 OR TORQUE_CPU_X64)
      torqueAddSourceDirectories("platformX86UNIX")
    endif (TORQUE_CPU_X32 OR TORQUE_CPU_X64)
  endif(NOT APPLE)
endif (UNIX)

# Handle platformMac
if (APPLE)
  torqueAddSourceDirectories("platformMac")
endif (APPLE)

# Handle platformWin32
if (WIN32)
	torqueAddSourceDirectories("platformWin32" "platformWin32/videoInfo")
endif (WIN32)

# Handle platformSDL
torqueAddSourceDirectories("platformSDL" "platformSDL/threads")

# Handle platformX11
if (UNIX AND NOT APPLE)
  torqueAddSourceDirectories("platformX11")
endif (UNIX AND NOT APPLE)

if(TORQUE_TESTING)
  torqueAddSourceDirectories("testing")
  set(TORQUE_COMPILE_DEFINITIONS ${TORQUE_COMPILE_DEFINITIONS} TORQUE_SHARED SDL_MAIN_HANDLED)
endif(TORQUE_TESTING)

# Add the collected files to our engine group
source_group(TREE "${CMAKE_SOURCE_DIR}/Engine/source" PREFIX "Engine" FILES ${TORQUE_SOURCE_FILES})
file(GLOB_RECURSE TORQUE_APP_GAME_SOURCES "${TORQUE_APP_ROOT_DIRECTORY}/source/*.cpp" "${TORQUE_APP_ROOT_DIRECTORY}/source/*.h")
source_group(TREE "${TORQUE_APP_ROOT_DIRECTORY}/source" PREFIX "Source Files" FILES ${TORQUE_APP_GAME_SOURCES})
set(TORQUE_INCLUDE_DIRECTORIES ${TORQUE_INCLUDE_DIRECTORIES} "${TORQUE_APP_ROOT_DIRECTORY}/source")

################# Engine Module Handling ###################

set(TORQUE_MODULE_PATHS "${CMAKE_SOURCE_DIR}/Tools/CMake/modules" "${TORQUE_APP_GAME_DIRECTORY}/data")
if (NOT "${TORQUE_MODULE_USER_PATH}" STREQUAL "")
	list(APPEND TORQUE_MODULE_PATHS "${TORQUE_MODULE_USER_PATH}")
endif()

################# MODULE LIBRARIES ###################
set(TORQUE_LIBRARY_BASE_PATH "${TORQUE_APP_GAME_DIRECTORY}/data")
message(STATUS "Checking base path: ${TORQUE_LIBRARY_BASE_PATH}")
set(MODULE_SUBDIRS_INCLUDED "")
if (EXISTS "${TORQUE_LIBRARY_BASE_PATH}")
    # List all immediate subdirectories of the base path for debugging
    file(GLOB MODULE_SUBDIRS "${TORQUE_LIBRARY_BASE_PATH}/*")
    foreach (MODULE_SUBDIR ${MODULE_SUBDIRS})
        if (EXISTS "${MODULE_SUBDIR}/source/libs/libs.cmake")
            message(STATUS "Adding subdirectory: ${MODULE_SUBDIR}/libs")
            # Handle spaces in paths (if needed)
            string(REPLACE " " "_" MODULE_BINARY_SUBDIR "${MODULE_SUBDIR}/libs")
            
            # Explicitly specify source and binary directories
            include("${MODULE_SUBDIR}/source/libs/libs.cmake")
            cmake_path(GET MODULE_SUBDIR STEM LAST_ONLY LAST_DIR_WORD)
            set(MODULE_SUBDIRS_INCLUDED ${MODULE_SUBDIRS_INCLUDED} ${LAST_DIR_WORD})
        endif()
    endforeach()
else()
    message(WARNING "Base path ${TORQUE_LIBRARY_BASE_PATH} does not exist.")
endif()

# Before doing module scanning, store away the engine sources - we do this so that modules
# can be placed into the proper filters
set(TORQUE_SOURCE_FILES_TEMPORARY ${TORQUE_SOURCE_FILES} ${TORQUE_APP_GAME_SOURCES})
set(TORQUE_SOURCE_FILES "")

foreach (TORQUE_MODULE_PATH ${TORQUE_MODULE_PATHS})
	# First find simple cmake scripts, mostly used for in-engine modules
	file(GLOB MODULE_SCRIPTS "${TORQUE_MODULE_PATH}/*.cmake")
	foreach (TORQUE_MODULE_SCRIPT ${MODULE_SCRIPTS})
		include(${TORQUE_MODULE_SCRIPT})

        # Add this script's collected files to our Engine group
        source_group(TREE "${CMAKE_SOURCE_DIR}/Engine" PREFIX "Engine" FILES ${TORQUE_SOURCE_FILES})

        set(TORQUE_SOURCE_FILES_TEMPORARY ${TORQUE_SOURCE_FILES_TEMPORARY} ${TORQUE_SOURCE_FILES})
        set(TORQUE_SOURCE_FILES "")
	endforeach()

	# Next find sub projects, these can introduce new source files
	SUBDIRLIST(POSSIBLE_PROJECTS "${TORQUE_MODULE_PATH}")
    set(FILTERED_PROJECTS ${POSSIBLE_PROJECTS})
	foreach (MODULE_INCLUDED ${MODULE_SUBDIRS_INCLUDED})
        list(FILTER FILTERED_PROJECTS EXCLUDE REGEX ${MODULE_INCLUDED})
	endforeach()
    
	foreach (POSSIBLE_PROJECT ${FILTERED_PROJECTS})
		# Retrieve the absolute path of this possible project
		get_filename_component(POSSIBLE_PROJECT_ABSOLUTEPATH "${POSSIBLE_PROJECT}"
							   REALPATH BASE_DIR "${TORQUE_MODULE_PATH}")

		if (EXISTS "${POSSIBLE_PROJECT_ABSOLUTEPATH}/source/CMakeLists.txt")
			add_subdirectory("${POSSIBLE_PROJECT_ABSOLUTEPATH}" ${CMAKE_BINARY_DIR}/temp/${POSSIBLE_PROJECT} EXCLUDE_FROM_ALL)
            source_group(TREE "${POSSIBLE_PROJECT_ABSOLUTEPATH}" PREFIX "Modules/${POSSIBLE_PROJECT}" FILES ${TORQUE_SOURCE_FILES})

            set(TORQUE_SOURCE_FILES_TEMPORARY ${TORQUE_SOURCE_FILES_TEMPORARY} ${TORQUE_SOURCE_FILES})
            set(TORQUE_SOURCE_FILES "")
        elseif(NOT EXISTS "${POSSIBLE_PROJECT_ABSOLUTEPATH}/source/*.cmake" AND NOT EXISTS "${POSSIBLE_PROJECT_ABSOLUTEPATH}/source/libs/*.cmake")
            file(GLOB_RECURSE MODULE_SOURCE "${POSSIBLE_PROJECT_ABSOLUTEPATH}/source/*.h" "${POSSIBLE_PROJECT_ABSOLUTEPATH}/source/*.cpp")
            #message(STATUS "MODULE_SOURCE:${MODULE_SOURCE}")
            source_group(TREE "${POSSIBLE_PROJECT_ABSOLUTEPATH}" PREFIX "Modules/${POSSIBLE_PROJECT}/" FILES ${MODULE_SOURCE})
            set(TORQUE_SOURCE_FILES_TEMPORARY ${TORQUE_SOURCE_FILES_TEMPORARY} ${MODULE_SOURCE})
		endif()
	endforeach()    
    
endforeach()

foreach (MODULE_INCLUDED ${MODULE_SUBDIRS_INCLUDED})
    set(WRAPPER_DIR ${TORQUE_LIBRARY_BASE_PATH}/${MODULE_INCLUDED}/source/wrappers)
    if (EXISTS ${WRAPPER_DIR})
        #message("including ${WRAPPER_DIR}")
            file(GLOB_RECURSE WRAPPER_SOURCE "${WRAPPER_DIR}/*.h" "${WRAPPER_DIR}/*.cpp")
            source_group(TREE "${WRAPPER_DIR}" PREFIX "Modules/${MODULE_INCLUDED}/" FILES ${WRAPPER_SOURCE})
            set(WRAPPER_FILES ${WRAPPER_FILES} ${WRAPPER_SOURCE})
        #message("including ${WRAPPER_FILES}")
        set(TORQUE_INCLUDE_DIRECTORIES ${TORQUE_INCLUDE_DIRECTORIES} ${WRAPPER_DIR})
    endif()
endforeach()

set(TORQUE_SOURCE_FILES ${TORQUE_SOURCE_FILES_TEMPORARY} ${WRAPPER_FILES})


################# Library Post-build Handling ###################
set(TORQUE_LIBRARY_PATHS "${CMAKE_SOURCE_DIR}/Engine/lib")
if (NOT "${TORQUE_LIBRARY_USER_PATH}" STREQUAL "")
	list(APPEND TORQUE_LIBRARY_PATHS "${TORQUE_LIBRARY_USER_PATH}")
endif()

foreach (TORQUE_LIBRARY_PATH ${TORQUE_LIBRARY_PATHS})
	# First find simple cmake scripts, mostly used for in-engine libraries
	file(GLOB_RECURSE LIBRARY_SCRIPTS "${TORQUE_LIBRARY_PATH}/*Torque_postBuild.cmake")
    #message(STATUS "LIBRARY_SCRIPTS:${LIBRARY_SCRIPTS}")
	foreach (TORQUE_LIBRARY_SCRIPT ${LIBRARY_SCRIPTS})
		include(${TORQUE_LIBRARY_SCRIPT})
	endforeach()
endforeach()
################# Dynamic File Configuration ###################

# Prepare Windows RC file
if (WIN32)
	set(APPLICATION_ICON_PATH "${CMAKE_SOURCE_DIR}/Tools/CMake/torque.ico")

	configure_file("${CMAKE_SOURCE_DIR}/Tools/CMake/torque-win.rc.in" "${TORQUE_APP_ROOT_DIRECTORY}/source/torque.rc")
	set(TORQUE_SOURCE_FILES ${TORQUE_SOURCE_FILES} "${TORQUE_APP_ROOT_DIRECTORY}/source/torque.rc")
endif (WIN32)

# Prepare OSX Plist
if (APPLE)
  set(MACOSX_RESOURCES
  "${TORQUE_APP_GAME_DIRECTORY}/data"
  "${TORQUE_APP_GAME_DIRECTORY}/core"
  "${TORQUE_APP_GAME_DIRECTORY}/tools"
  "${TORQUE_APP_GAME_DIRECTORY}/main.${TORQUE_SCRIPT_EXTENSION}"
  "${TORQUE_APP_GAME_DIRECTORY}/${TORQUE_APP_NAME}.torsion"
  "${TORQUE_APP_GAME_DIRECTORY}/Template.torsion.exports")

  if(TORQUE_TESTING)
    set(MACOSX_RESOURCES ${MACOSX_RESOURCES} "${TORQUE_APP_GAME_DIRECTORY}/runTests.${TORQUE_SCRIPT_EXTENSION}")
  endif()

	set(TORQUE_SOURCE_FILES ${TORQUE_SOURCE_FILES} ${TORQUE_PLATFORM_MAC_SOURCES} ${MACOSX_RESOURCES})

  source_group("Resources" FILES ${MACOSX_RESOURCES})

	set_source_files_properties(${MACOSX_RESOURCES} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")

	set(EXECUTABLE_NAME "${TORQUE_APP_NAME}")
	configure_file("${CMAKE_SOURCE_DIR}/Tools/CMake/Info.plist.in" "${TORQUE_APP_ROOT_DIRECTORY}/source/Info.plist" COPYONLY)
  file( COPY "${CMAKE_SOURCE_DIR}/Tools/CMake/app_assets/apple/App.xcassets" DESTINATION "${TORQUE_APP_ROOT_DIRECTORY}/source")
  
endif (APPLE)

addDef(TORQUE_DEBUG Debug)
addDef(TORQUE_RELEASE "RelWithDebInfo;Release")
addDef(TORQUE_ENABLE_ASSERTS "Debug;RelWithDebInfo")
addDef(TORQUE_DEBUG_GFX_MODE "RelWithDebInfo")
addDef(TORQUE_OGGVORBIS)

if (TORQUE_THEORA)
   addDef(TORQUE_OGGTHEORA)
endif(TORQUE_THEORA)

if(NOT TORQUE_SDL)
   filterOut("platform/nativeDialogs/fileDialog.cpp" )
endif()
if(NOT TORQUE_OPENGL)
  filterOut("platformSDL/sdlPlatformGL.cpp")
endif()
if (NOT TORQUE_NET_CURL)
  filterOut("app/net/httpObject.h" "app/net/httpObject.cpp")
endif()

################# Executable Generation ###################

if (TORQUE_DYNAMIC_LIBRARY AND NOT TORQUE_TESTING)
    set(TORQUE_COMPILE_DEFINITIONS ${TORQUE_COMPILE_DEFINITIONS} TORQUE_SHARED)
    add_library(TorqueEngine SHARED ${TORQUE_SOURCE_FILES})
    target_compile_definitions(TorqueEngine PUBLIC ${TORQUE_COMPILE_DEFINITIONS})
    target_link_libraries(TorqueEngine ${TORQUE_LINK_LIBRARIES} ${TORQUE_LINK_THIRDPARTY})
    target_include_directories(TorqueEngine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_BINARY_DIR}/temp" ${TORQUE_INCLUDE_DIRECTORIES})
    set(TORQUE_SOURCE_FILES "main/main.cpp")
    set(TORQUE_LINK_LIBRARIES TorqueEngine)
else()
    if(NOT TORQUE_TESTING)
        set(TORQUE_SOURCE_FILES "main/main.cpp" ${TORQUE_SOURCE_FILES})
    endif()
endif (TORQUE_DYNAMIC_LIBRARY AND NOT TORQUE_TESTING)
 
if (APPLE)
    add_executable(${TORQUE_APP_NAME} MACOSX_BUNDLE ${TORQUE_SOURCE_FILES})
 
    target_sources(${TORQUE_APP_NAME} PRIVATE "${TORQUE_APP_ROOT_DIRECTORY}/source/App.xcassets")
    set_source_files_properties("${TORQUE_APP_ROOT_DIRECTORY}/source/App.xcassets" PROPERTIES
        MACOSX_PACKAGE_LOCATION Resources)
 
    set_target_properties(${TORQUE_APP_NAME} PROPERTIES
        MACOSX_BUNDLE true
        MACOSX_BUNDLE_INFO_PLIST "${TORQUE_APP_ROOT_DIRECTORY}/source/Info.plist"
        XCODE_ATTRIBUTE_PRODUCT_BUNDLE_IDENTIFIER "com.torque3d.${TORQUE_APP_NAME}"
        INSTALL_RPATH "@executable_path/../Frameworks"
        XCODE_ATTRIBUTE_SKIP_INSTALL NO
        BUILD_WITH_INSTALL_RPATH ON
        XCODE_ATTRIBUTE_INSTALL_PATH "/Applications"
        XCODE_ATTRIBUTE_ASSETCATALOG_COMPILER_APPICON_NAME "AppIcon"
        XCODE_ATTRIBUTE_LINKER_DISPLAYS_MANGLED_NAMES[variant=Debug] YES
        XCODE_ATTRIBUTE_ONLY_ACTIVE_ARCH[variant=Debug] YES
        XCODE_ATTRIBUTE_ENABLE_TESTABILITY[variant=Debug] YES
        XCODE_ATTRIBUTE_SDL_FILE_DIR[variant=Debug] parent
        XCODE_ATTRIBUTE_SDL_FILE_DIR[variant=RelWithDebInfo] parent
        XCODE_ATTRIBUTE_SDL_FILE_DIR[variant=Release] resource)
 
elseif (WIN32)
    add_executable(${TORQUE_APP_NAME} WIN32 ${TORQUE_SOURCE_FILES})
else()
    add_executable(${TORQUE_APP_NAME} ${TORQUE_SOURCE_FILES})
    set_target_properties(${TORQUE_APP_NAME} PROPERTIES LINK_FLAGS "-Wl,-rpath,./")
endif()
 
################# Architecture Detection ###################

string(TOLOWER "${CMAKE_SYSTEM_PROCESSOR}" ARCH)

set(IS_X86 FALSE)
set(IS_ARM FALSE)

if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    # Use the CMAKE_OSX_ARCHITECTURES list for universal builds
    foreach(arch IN LISTS CMAKE_OSX_ARCHITECTURES)
        if(arch STREQUAL "x86_64")
            set(IS_X86 TRUE)
        elseif(arch STREQUAL "arm64")
            set(IS_ARM TRUE)
        endif()
    endforeach()
else()
    # Non-macOS detection
    if(ARCH MATCHES "arm64|aarch64")
      set(IS_ARM TRUE)
    endif()
    if(ARCH MATCHES "x86_64|amd64|i[3-6]86")
        set(IS_X86 TRUE)
    endif()
endif()

# always available
add_math_backend(scalar  MATH_SIMD_SCALAR)
message(STATUS "Processor: ${CMAKE_SYSTEM_PROCESSOR}")
message(STATUS "IS_X86=${IS_X86}")
message(STATUS "IS_ARM=${IS_ARM}")

# x86 family
if(IS_X86)
    add_math_backend(sse2  MATH_SIMD_SSE2)
    add_math_backend(sse41 MATH_SIMD_SSE41)
    add_math_backend(avx   MATH_SIMD_AVX)
    add_math_backend(avx2  MATH_SIMD_AVX2)
endif()

# ARM family
if(IS_ARM)
    add_math_backend(neon  MATH_SIMD_NEON)
endif()

if(MSVC)
    if(IS_X86)
        target_compile_options(${TORQUE_APP_NAME} PRIVATE
            /arch:SSE2  # Safe baseline for all configs - dispatch handles ISA upgrades at runtime
        )
    endif()
    if (TORQUE_DYNAMIC_LIBRARY AND NOT TORQUE_TESTING)
        if(IS_X86)
            target_compile_options(TorqueEngine PRIVATE
                /arch:SSE2
            )
        endif()
    endif()
endif()

################# Compile Flags ###################
# All flags use target_compile_options with generator expressions so they are
# per-configuration and never bleed across build types.  The old flat
# COMPILE_FLAGS string on the target has been removed entirely.
 
# ----- Windows (MSVC) -----
if (MSVC)
    # Warnings we suppress engine-wide - all pre-existing
    set(_TORQUE_MSVC_WARNINGS
        /wd4018   # signed/unsigned mismatch
        /wd4100   # unreferenced formal parameter
        /wd4121   # alignment sensitive to packing
        /wd4127   # conditional expression is constant
        /wd4130   # logical op on address of string literal
        /wd4244   # conversion, possible loss of data
        /wd4245   # signed/unsigned mismatch on return/init
        /wd4267   # conversion possible loss of data
        /wd4389   # signed/unsigned mismatch on comparison
        /wd4511   # copy constructor could not be generated
        /wd4512   # assignment operator could not be generated
        /wd4800   # forcing value to bool
        /wd4995   # deprecated function
    )
 
    # Flags that are correct for every configuration
    set(_TORQUE_MSVC_ALL
        /MP         # Parallel compilation - single biggest build speed win
        /FS         # Synchronous PDB writes - required when using /MP
        /nologo     # Suppress banner
        /W3         # Warning level 3  (W4 slows compilation noticeably)
        /WX-        # Warnings are not errors
        /EHsc       # Standard C++ exception handling only
        /GR         # RTTI - required for dynamic_cast throughout the engine
        /GF         # String pooling
        /Gy         # Function-level linking (dead-code stripping at link time)
        /Zc:wchar_t-  # Engine-wide ABI requirement
        /fp:precise   # Consistent FP across the codebase
        /fp:except-   # No FP exception overhead
        /bigobj       # >64k sections - consoleObject.h template depth needs this
        /Qpar-        # Disable auto-paralleliser (causes subtle correctness bugs)
        /NODEFAULTLIB
        ${_TORQUE_MSVC_WARNINGS}
    )
 
    # Debug - prioritise compilation speed and debuggability over all else
    set(_TORQUE_MSVC_DEBUG
        /Od     # No optimisation - fastest to compile, cleanest call stacks
        /Ob0    # No inlining - keeps debugger call stacks honest
        /RTCs   # Runtime checks: stack corruption + uninitialised variables
        /GS     # Buffer security checks
        /Zi     # Embed debug info in .obj - avoids PDB contention with /MP
        /MDd    # Debug CRT
    )
 
    # RelWithDebInfo - ship-like speed, but still inspectable in a debugger
    set(_TORQUE_MSVC_RELWITHDEBINFO
        /O2     # Maximise speed (implies /Ob2 /Oi /Ot)
        /Ob1    # Only inline functions explicitly marked - preserves some stack info
        /Oi     # Intrinsic replacements for common functions
        /Ot     # Favour fast code over small code
        /Gw     # Package global data for linker dead-stripping
        /GS-    # No buffer security checks
        /Zi     # Debug info in .obj (not a separate PDB) - safer with /MP
        /MD     # Release CRT
    )
 
    # Release - maximum runtime performance
    set(_TORQUE_MSVC_RELEASE
        /O2     # Maximise speed
        /Ob2    # Inline any suitable function
        /Oi     # Intrinsic functions
        /Ot     # Favour fast code
        /Oy     # Omit frame pointers (marginal perf gain; hurts external profiling)
        /Gw     # Package global data
        /GS-    # No buffer security checks
        /MD     # Release CRT
    )
 
    target_compile_options(${TORQUE_APP_NAME} PRIVATE
        ${_TORQUE_MSVC_ALL}
        $<$<CONFIG:Debug>:${_TORQUE_MSVC_DEBUG}>
        $<$<CONFIG:RelWithDebInfo>:${_TORQUE_MSVC_RELWITHDEBINFO}>
        $<$<CONFIG:Release>:${_TORQUE_MSVC_RELEASE}>
    )
 
    target_link_options(${TORQUE_APP_NAME} PRIVATE
        $<$<CONFIG:Debug>:/DEBUG:FASTLINK /INCREMENTAL>
        $<$<CONFIG:RelWithDebInfo>:/INCREMENTAL /DEBUG:FASTLINK /OPT:REF /OPT:ICF>
        $<$<CONFIG:Release>:/INCREMENTAL>
    )
 
    if (TORQUE_DYNAMIC_LIBRARY AND NOT TORQUE_TESTING)
        target_compile_options(TorqueEngine PRIVATE
            ${_TORQUE_MSVC_ALL}
            $<$<CONFIG:Debug>:${_TORQUE_MSVC_DEBUG}>
            $<$<CONFIG:RelWithDebInfo>:${_TORQUE_MSVC_RELWITHDEBINFO}>
            $<$<CONFIG:Release>:${_TORQUE_MSVC_RELEASE}>
        )
    endif()

endif (MSVC)
 
# ----- GCC / Clang  (Linux and macOS) -----
if (UNIX)
    # Flags correct for every configuration on GCC/Clang
    set(_TORQUE_UNIX_ALL
        -Wno-unused-parameter
        -Wno-sign-compare
        -Wno-reorder
        -fno-exceptions          # Engine does not use C++ exceptions
        -fmessage-length=0       # No line-wrapping in compiler messages
        -pipe                    # Use pipes instead of temp files - faster compilation
        -Wno-type-limits         # constant conditional expression
        -Wno-unused-value
        -Wno-deprecated-declarations
        -Wno-conversion          # possible loss of data
        -Wno-sign-conversion
        -Wno-old-style-cast      # if legacy codebase
        -Wno-invalid-offsetof    # offsetof non-standard-layout
    )
 
    # Debug
    set(_TORQUE_UNIX_DEBUG
        -O0                      # No optimisation - fastest to compile
        -g3                      # Maximum debug info (includes macros)
        -fno-omit-frame-pointer  # Keep frame pointers for sane stack traces
        -fno-inline              # No inlining - keeps call stacks clean
    )
 
    # RelWithDebInfo
    set(_TORQUE_UNIX_RELWITHDEBINFO
        -O2
        -g1                      # Minimal debug info - line numbers only
        -fno-omit-frame-pointer  # Keep frame pointers so profilers work
    )
 
    # Release
    set(_TORQUE_UNIX_RELEASE
        -O3
        -g0                      # No debug info
        -fomit-frame-pointer
        -DNDEBUG
    )
 
    # LTO in Release only - significantly extends link time so keep it out of Debug/RWD
    if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        list(APPEND _TORQUE_UNIX_ALL
            -Wno-shorten-64-to-32
            -Wno-implicit-int-conversion
            -Wno-implicit-float-conversion
            -Wno-nonportable-include-path
        )
        set(_TORQUE_UNIX_RELEASE_LINK -flto=thin)  # ThinLTO: much faster than full LTO, near-equivalent results
    else()
        set(_TORQUE_UNIX_RELEASE_LINK -flto)
    endif()
 
    target_compile_options(${TORQUE_APP_NAME} PRIVATE
        ${_TORQUE_UNIX_ALL}
        $<$<CONFIG:Debug>:${_TORQUE_UNIX_DEBUG}>
        $<$<CONFIG:RelWithDebInfo>:${_TORQUE_UNIX_RELWITHDEBINFO}>
        $<$<CONFIG:Release>:${_TORQUE_UNIX_RELEASE}>
    )
 
    target_link_options(${TORQUE_APP_NAME} PRIVATE
        $<$<CONFIG:Release>:${_TORQUE_UNIX_RELEASE_LINK}>
    )
 
    if (TORQUE_DYNAMIC_LIBRARY AND NOT TORQUE_TESTING)
        target_compile_options(TorqueEngine PRIVATE
            ${_TORQUE_UNIX_ALL}
            $<$<CONFIG:Debug>:${_TORQUE_UNIX_DEBUG}>
            $<$<CONFIG:RelWithDebInfo>:${_TORQUE_UNIX_RELWITHDEBINFO}>
            $<$<CONFIG:Release>:${_TORQUE_UNIX_RELEASE}>
        )
        target_link_options(TorqueEngine PRIVATE
            $<$<CONFIG:Release>:${_TORQUE_UNIX_RELEASE_LINK}>
        )
    endif()
endif (UNIX)
 
################# Output Naming (MSVC) ###################
 
if(MSVC)
    set(OUTPUT_CONFIG DEBUG MINSIZEREL RELWITHDEBINFO)
    set(OUTPUT_SUFFIX DEBUG MINSIZE    OPTIMIZEDDEBUG)
    foreach(INDEX RANGE 2)
        list(GET OUTPUT_CONFIG ${INDEX} CONF)
        list(GET OUTPUT_SUFFIX ${INDEX} SUFFIX)
        set_property(TARGET ${TORQUE_APP_NAME} PROPERTY OUTPUT_NAME_${CONF} ${TORQUE_APP_NAME}_${SUFFIX})
        if (TORQUE_DYNAMIC_LIBRARY AND NOT TORQUE_TESTING)
            set_property(TARGET TorqueEngine PROPERTY ${CONF}_POSTFIX "_${SUFFIX}")
            set_property(TARGET TorqueEngine PROPERTY ${CONF}_OUTPUT_NAME ${TORQUE_APP_NAME})
        endif (TORQUE_DYNAMIC_LIBRARY AND NOT TORQUE_TESTING)
    endforeach()
    set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${TORQUE_APP_NAME})
endif()
 
################# Folder Organisation ###################

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
foreach (TORQUE_LIBRARY ${TORQUE_LINK_LIBRARIES})
  # Skip if it's a raw library file instead of a target
  if(TORQUE_LIBRARY MATCHES "\\.(lib|a|so|dylib|dll)$")
    continue()
  endif()
  set_target_properties(${TORQUE_LIBRARY} PROPERTIES
  FOLDER "Libraries")
endforeach()

target_compile_definitions(${TORQUE_APP_NAME} PUBLIC ${TORQUE_COMPILE_DEFINITIONS})
target_link_libraries(${TORQUE_APP_NAME} ${TORQUE_LINK_LIBRARIES} ${TORQUE_LINK_THIRDPARTY})

if(APPLE)
  target_link_libraries(${TORQUE_APP_NAME} ${TORQUE_LINK_FRAMEWORKS})


endif(APPLE)

if(WIN32)
  target_link_libraries(${TORQUE_APP_NAME} ${TORQUE_LINK_WINDOWS})
endif(WIN32)

if(UNIX AND NOT APPLE)
  target_link_libraries(${TORQUE_APP_NAME} ${TORQUE_LINK_LINUX})
endif(UNIX AND NOT APPLE)

target_link_options(${TORQUE_APP_NAME} PUBLIC ${TORQUE_LINK_OPTIONS})
if (TORQUE_TARGET_PROPERTIES)
   set_target_properties(${TORQUE_APP_NAME} PROPERTIES ${TORQUE_TARGET_PROPERTIES})
endif (TORQUE_TARGET_PROPERTIES)
target_include_directories(${TORQUE_APP_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_BINARY_DIR}/temp" ${TORQUE_INCLUDE_DIRECTORIES})

target_precompile_headers(${TORQUE_APP_NAME} PRIVATE
    <vector>
    <string>
    <map>
    <memory>
    <algorithm>
    <type_traits>
    <cstring>
    <cstdlib>
    <cstdio>
    <cmath>
    <cstdint>
    <cmath>
)

if(TORQUE_TESTING)
  if(WIN32)
        target_link_options(${TORQUE_APP_NAME} PRIVATE "/SUBSYSTEM:CONSOLE")
        set_target_properties(gtest PROPERTIES COMPILE_FLAGS "/Zc:wchar_t-")
        set_target_properties(gmock PROPERTIES COMPILE_FLAGS "/Zc:wchar_t-")
    endif()
endif(TORQUE_TESTING)

append_defs()

# Process library binaries - these are coming from modules that are providing links to external, precompiled code that should be included
# with the executable. This is done because on Windows, the .lib is separate from the .dll so we can't automatically scan for shared
# objects in our link libraries in that case.
foreach (LIBRARY_BINARY ${TORQUE_ADDITIONAL_LIBRARY_BINARIES})
  if (APPLE)
    # For OSX, we want these binaries to be copied to the Frameworks directory
    add_custom_command(TARGET ${TORQUE_APP_NAME} POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E make_directory  "${TORQUE_APP_GAME_DIRECTORY}/${TORQUE_APP_NAME}.app/Contents/Frameworks"
    COMMAND ${CMAKE_COMMAND} -E copy ${LIBRARY_BINARY} "${TORQUE_APP_GAME_DIRECTORY}/${TORQUE_APP_NAME}.app/Contents/Frameworks/$(CONFIGURATION)")
  else()
    # All other platforms expect the file next to the executable
    add_custom_command(TARGET ${TORQUE_APP_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${LIBRARY_BINARY} "${TORQUE_APP_GAME_DIRECTORY}")
  endif (APPLE)
endforeach()

# Process link libraries for dynamic links - we do this on OSX/Linux to ensure the binaries end up in the correct App directory
# as in the root CMake we force everything to be in game. This is necessary because on these platforms these are considered "libraries"
# and not runtime binaries like we configure in the root CMake. We don't globally set library outputs to avoid outputting eg. a files to
# our game directory.
if (UNIX)
	get_target_property(GAME_LINK_LIBRARIES ${TORQUE_APP_NAME} LINK_LIBRARIES)
	foreach (GAME_LINK_LIBRARY ${GAME_LINK_LIBRARIES})
	  # For eg. OSX some links are not valid targets - for example frameworks provided by OS
	  if (TARGET ${GAME_LINK_LIBRARY})
		  get_target_property(LINK_LIBRARY_TYPE ${GAME_LINK_LIBRARY} TYPE)
		  # Only pay attention to shared libraries and make them output to the app resources
		  if ("${LINK_LIBRARY_TYPE}" STREQUAL "SHARED_LIBRARY")
        if (APPLE)
          set_target_properties(${GAME_LINK_LIBRARY} PROPERTIES 
          XCODE_ATTRIBUTE_SKIP_INSTALL YES
          )
          add_custom_command(TARGET ${TORQUE_APP_NAME} POST_BUILD 
          COMMAND ${CMAKE_COMMAND} -E make_directory  "${TORQUE_APP_GAME_DIRECTORY}/${TORQUE_APP_NAME}.app/Contents/Frameworks"
          COMMAND ${CMAKE_COMMAND} -E copy "$<TARGET_FILE:${GAME_LINK_LIBRARY}>" "${TORQUE_APP_GAME_DIRECTORY}/${TORQUE_APP_NAME}.app/Contents/Frameworks/$<TARGET_FILE_NAME:${GAME_LINK_LIBRARY}>"
          COMMAND ${CMAKE_COMMAND} -E create_symlink "$<TARGET_FILE:${GAME_LINK_LIBRARY}>" "${TORQUE_APP_GAME_DIRECTORY}/${TORQUE_APP_NAME}.app/Contents/Frameworks/$<TARGET_LINKER_FILE_NAME:${GAME_LINK_LIBRARY}>"
          COMMAND ${CMAKE_COMMAND} -E create_symlink "$<TARGET_FILE:${GAME_LINK_LIBRARY}>" "${TORQUE_APP_GAME_DIRECTORY}/${TORQUE_APP_NAME}.app/Contents/Frameworks/lib$<TARGET_LINKER_FILE_BASE_NAME:${GAME_LINK_LIBRARY}>.1.dylib"
          )
        else()
          set_target_properties(${GAME_LINK_LIBRARY} PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${TORQUE_APP_GAME_DIRECTORY}")
        endif(APPLE)
		  endif()
	  endif()
	endforeach()
endif (UNIX)
