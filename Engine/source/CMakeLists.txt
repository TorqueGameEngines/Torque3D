project(${TORQUE_APP_NAME})

# Enable ObjectiveC compilation when compiling for Apple platforms
if (APPLE)
	enable_language(OBJC)
endif (APPLE)

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

# Handle Platform
torqueAddSourceDirectories("platform" "platform/threads" "platform/async"
                                  "platform/input" "platform/output")

torqueAddSourceDirectories("platform/nativeDialogs")

# Handle T3D
torqueAddSourceDirectories("T3D/fps" "T3D/fx" "T3D/vehicles" "T3D/physics"
                              "T3D/decal" "T3D/sfx" "T3D/gameBase" "T3D/turret"
                              "T3D/lighting" "T3D/gameOBjects" "T3D/components"
                              "T3D/systems" "T3D/assets" "T3D" "T3D/gameBase/std")

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
torqueAddSourceDirectories("gfx" "gfx/Null" "gfx/test" "gfx/bitmap" "gfx/bitmap/loaders"
                             "gfx/util" "gfx/video" "gfx/sim" )

if (TORQUE_OPENGL)
  torqueAddSourceDirectories("gfx/gl" "gfx/gl/sdl" "gfx/gl/tGL")
endif (TORQUE_OPENGL)

if (WIN32 AND TORQUE_D3D11)
  torqueAddSourceDirectories("gfx/D3D11")
endif (WIN32 AND TORQUE_D3D11)

# Handle core
torqueAddSourceDirectories("core" "core/stream" "core/strings" "core/util"
                              "core/util/journal" "core/util/zip" "core/util/compressors")
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
torqueAddSourceDirectories("math" "math/util")

# Handle persistence
torqueAddSourceDirectories("persistence/taml" "persistence/taml/binary" "persistence/taml/xml")

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

	if (TORQUE_CPU_X32 OR TORQUE_CPU_X64)
    torqueAddSourceDirectories("platformX86UNIX")
	endif (TORQUE_CPU_X32 OR TORQUE_CPU_X64)
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

################# Engine Module Handling ###################

set(TORQUE_MODULE_PATHS "${CMAKE_SOURCE_DIR}/Tools/CMake/modules" "${TORQUE_APP_GAME_DIRECTORY}/data")
if (NOT "${TORQUE_MODULE_USER_PATH}" STREQUAL "")
	list(APPEND TORQUE_MODULE_PATHS "${TORQUE_MODULE_USER_PATH}")
endif()

# Before doing module scanning, store away the engine sources - we do this so that modules
# can be placed into the proper filters
set(TORQUE_SOURCE_FILES_TEMPORARY ${TORQUE_SOURCE_FILES})
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
	foreach (POSSIBLE_PROJECT ${POSSIBLE_PROJECTS})
		# Retrieve the absolute path of this possible project
		get_filename_component(POSSIBLE_PROJECT_ABSOLUTEPATH "${POSSIBLE_PROJECT}"
							   REALPATH BASE_DIR "${TORQUE_MODULE_PATH}")

		if (EXISTS "${POSSIBLE_PROJECT_ABSOLUTEPATH}/CMakeLists.txt")
			add_subdirectory("${POSSIBLE_PROJECT_ABSOLUTEPATH}" ${CMAKE_BINARY_DIR}/temp/${POSSIBLE_PROJECT} EXCLUDE_FROM_ALL)
            source_group(TREE "${POSSIBLE_PROJECT_ABSOLUTEPATH}" PREFIX "Modules/${POSSIBLE_PROJECT}" FILES ${TORQUE_SOURCE_FILES})

            set(TORQUE_SOURCE_FILES_TEMPORARY ${TORQUE_SOURCE_FILES_TEMPORARY} ${TORQUE_SOURCE_FILES})
            set(TORQUE_SOURCE_FILES "")
        elseif(NOT EXISTS "${POSSIBLE_PROJECT_ABSOLUTEPATH}/*.cmake")
            file(GLOB_RECURSE MODULE_SOURCE "${POSSIBLE_PROJECT_ABSOLUTEPATH}/source/*.h" "${POSSIBLE_PROJECT_ABSOLUTEPATH}/source/*.cpp")
            #message(STATUS "MODULE_SOURCE:${MODULE_SOURCE}")
            source_group(TREE "${POSSIBLE_PROJECT_ABSOLUTEPATH}" PREFIX "Modules/${POSSIBLE_PROJECT}/" FILES ${MODULE_SOURCE})
            set(TORQUE_SOURCE_FILES_TEMPORARY ${TORQUE_SOURCE_FILES_TEMPORARY} ${MODULE_SOURCE})
		endif()
	endforeach()
endforeach()

set(TORQUE_SOURCE_FILES ${TORQUE_SOURCE_FILES_TEMPORARY})

################# Library Post-build Handling ###################
set(TORQUE_LIBRARY_PATHS "${CMAKE_SOURCE_DIR}/Engine/lib" "${TORQUE_APP_GAME_DIRECTORY}/data")
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

	configure_file("${CMAKE_SOURCE_DIR}/Tools/CMake/torque-win.rc.in" "${CMAKE_BINARY_DIR}/temp/torque.rc")
	set(TORQUE_SOURCE_FILES ${TORQUE_SOURCE_FILES} "${CMAKE_BINARY_DIR}/temp/torque.rc")
endif (WIN32)

# Prepare OSX Plist
if (APPLE)
	set(TORQUE_SOURCE_FILES ${TORQUE_SOURCE_FILES} ${TORQUE_PLATFORM_MAC_SOURCES} "${CMAKE_SOURCE_DIR}/Tools/CMake/torque.icns")
	set_source_files_properties("${CMAKE_SOURCE_DIR}/Tools/CMake/torque.icns" PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")

	set(EXECUTABLE_NAME "${TORQUE_APP_NAME}")
	configure_file("${CMAKE_SOURCE_DIR}/Tools/CMake/Info.plist.in" "${CMAKE_BINARY_DIR}/temp/Info.plist" COPYONLY)
endif (APPLE)

addDef(TORQUE_DEBUG Debug)
addDef(TORQUE_RELEASE "RelWithDebInfo;Release")
addDef(TORQUE_ENABLE_ASSERTS "Debug;RelWithDebInfo")
addDef(TORQUE_DEBUG_GFX_MODE "RelWithDebInfo")
addDef(TORQUE_OGGVORBIS)

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

  # Build the main engine library
  add_library(TorqueEngine SHARED ${TORQUE_SOURCE_FILES})
  target_compile_definitions(TorqueEngine PUBLIC ${TORQUE_COMPILE_DEFINITIONS})
  target_link_libraries(TorqueEngine ${TORQUE_LINK_LIBRARIES})
  target_include_directories(TorqueEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_BINARY_DIR}/temp" ${TORQUE_INCLUDE_DIRECTORIES})
  target_compile_features(TorqueEngine PRIVATE cxx_std_20)

  set(TORQUE_SOURCE_FILES "main/main.cpp")
  set(TORQUE_LINK_LIBRARIES TorqueEngine)
else()
  if(NOT TORQUE_TESTING)
    set(TORQUE_SOURCE_FILES "main/main.cpp" ${TORQUE_SOURCE_FILES})
  endif()
endif (TORQUE_DYNAMIC_LIBRARY AND NOT TORQUE_TESTING)

if (APPLE)
	add_executable(${TORQUE_APP_NAME} MACOSX_BUNDLE ${TORQUE_SOURCE_FILES})
	set_target_properties(${TORQUE_APP_NAME} PROPERTIES MACOSX_BUNDLE_INFO_PLIST "${CMAKE_BINARY_DIR}/temp/Info.plist")

	# Ensure the shared libraries are actually referenced at the correct path
	set(CMAKE_XCODE_ATTRIBUTE_LD_RUNPATH_SEARCH_PATHS "@executable_path/../Frameworks")
elseif (WIN32)
	add_executable(${TORQUE_APP_NAME} WIN32 ${TORQUE_SOURCE_FILES})

    set(TORQUE_CXX_FLAGS_COMMON_DEFAULT "-DUNICODE -D_UNICODE -D_CRT_SECURE_NO_WARNINGS /MP /Ob2 /Oi /Ot /Oy /GT /Zi /W4 /nologo /GF /EHsc /GS- /Gy- /Qpar- /fp:precise /fp:except- /GR /Zc:wchar_t-" )
    if( TORQUE_CPU_X32 )
       set(TORQUE_CXX_FLAGS_COMMON_DEFAULT "${TORQUE_CXX_FLAGS_COMMON_DEFAULT} /arch:SSE2")
    endif()
    set(TORQUE_CXX_FLAGS_COMMON ${TORQUE_CXX_FLAGS_COMMON_DEFAULT} CACHE STRING "")
    mark_as_advanced(TORQUE_CXX_FLAGS_COMMON)

    set(TORQUE_CXX_FLAGS_EXECUTABLES "/wd4018 /wd4100 /wd4121 /wd4127 /wd4130 /wd4244 /wd4245 /wd4389 /wd4511 /wd4512 /wd4800 /wd4995" CACHE STRING "")
    mark_as_advanced(TORQUE_CXX_FLAGS_EXECUTABLES)

    set(TORQUE_CXX_FLAGS "${TORQUE_CXX_FLAGS_COMMON_DEFAULT} ${TORQUE_CXX_FLAGS_EXECUTABLES}" CACHE STRING "")
    mark_as_advanced(TORQUE_CXX_FLAGS)

	# NOTE: On Windows, /Zc:wchar_t- is necessary otherwise you get unicode errors
	set_target_properties(${TORQUE_APP_NAME} PROPERTIES COMPILE_FLAGS "${TORQUE_CXX_FLAGS}")
   if (TORQUE_DYNAMIC_LIBRARY AND NOT TORQUE_TESTING)
      set_target_properties(TorqueEngine PROPERTIES COMPILE_FLAGS "${TORQUE_CXX_FLAGS_COMMON_DEFAULT}")
   endif (TORQUE_DYNAMIC_LIBRARY AND NOT TORQUE_TESTING)
else()
	add_executable(${TORQUE_APP_NAME} ${TORQUE_SOURCE_FILES})

	# NOTE: On Linux, we set the rpath to ./ so that shared objects next to the executable are used
	set_target_properties(${TORQUE_APP_NAME} PROPERTIES LINK_FLAGS "-Wl,-rpath,./")
endif()


if(MSVC)
    # Match projectGenerator naming for executables
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
    # Set Visual Studio startup project
    set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${TORQUE_APP_NAME})
endif()

target_compile_definitions(${TORQUE_APP_NAME} PUBLIC ${TORQUE_COMPILE_DEFINITIONS})
target_link_libraries(${TORQUE_APP_NAME} ${TORQUE_LINK_LIBRARIES})
target_link_options(${TORQUE_APP_NAME} PUBLIC ${TORQUE_LINK_OPTIONS})
if (TORQUE_TARGET_PROPERTIES)
   set_target_properties(${TORQUE_APP_NAME} PROPERTIES ${TORQUE_TARGET_PROPERTIES})
endif (TORQUE_TARGET_PROPERTIES)
target_include_directories(${TORQUE_APP_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_BINARY_DIR}/temp" ${TORQUE_INCLUDE_DIRECTORIES})
target_compile_features(${TORQUE_APP_NAME} PRIVATE cxx_std_20)

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
    add_custom_command(TARGET ${TORQUE_APP_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${LIBRARY_BINARY} "${TORQUE_APP_GAME_DIRECTORY}/${TORQUE_APP_NAME}.app/Contents/Frameworks")
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
          set_target_properties(${GAME_LINK_LIBRARY} PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${TORQUE_APP_GAME_DIRECTORY}/${TORQUE_APP_NAME}.app/Contents/Frameworks")
        else()
          set_target_properties(${GAME_LINK_LIBRARY} PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${TORQUE_APP_GAME_DIRECTORY}")
        endif(APPLE)
		  endif()
	  endif()
	endforeach()
endif (UNIX)
