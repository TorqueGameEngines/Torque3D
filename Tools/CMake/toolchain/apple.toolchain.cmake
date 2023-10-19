cmake_minimum_required (VERSION 3.21.0)

project(${TORQUE_APP_NAME})

enable_language(OBJC)
enable_language(OBJCXX)

set(CMAKE_OSX_ARCHITECTURES "x86_64;arm64" CACHE INTERNAL "")
set(CMAKE_OSX_DEPLOYMENT_TARGET "10.13" CACHE INTERNAL "")

set(CMAKE_THREAD_LIBS_INIT "-lpthread")
set(CMAKE_HAVE_THREADS_LIBRARY 1)
set(CMAKE_USE_WIN32_THREADS_INIT 0)
set(CMAKE_USE_PTHREADS_INIT 1)
set(CMAKE_XCODE_ATTRIBUTE_CODE_SIGNING_REQUIRED "NO")
set(CMAKE_SHARED_LIBRARY_PREFIX "lib")
set(CMAKE_SHARED_LIBRARY_SUFFIX ".dylib")
set(CMAKE_SHARED_MODULE_PREFIX "lib")
set(CMAKE_SHARED_MODULE_SUFFIX ".so")
set(CMAKE_C_COMPILER_ABI ELF)
set(CMAKE_CXX_COMPILER_ABI ELF)
set(CMAKE_C_HAS_ISYSROOT 1)
set(CMAKE_CXX_HAS_ISYSROOT 1)
set(CMAKE_MODULE_EXISTS 1)
set(CMAKE_DL_LIBS "")
set(CMAKE_C_OSX_COMPATIBILITY_VERSION_FLAG "-compatibility_version ")
set(CMAKE_C_OSX_CURRENT_VERSION_FLAG "-current_version ")
set(CMAKE_CXX_OSX_COMPATIBILITY_VERSION_FLAG "${CMAKE_C_OSX_COMPATIBILITY_VERSION_FLAG}")
set(CMAKE_CXX_OSX_CURRENT_VERSION_FLAG "${CMAKE_C_OSX_CURRENT_VERSION_FLAG}")
set(CMAKE_MACOSX_BUNDLE YES)
set(OBJC_VARS "-fobjc-abi-version=2 -DOBJC_OLD_DISPATCH_PROTOTYPES=0")

set(CMAKE_OBJC_FLAGS "${C_TARGET_FLAGS} ${APPLE_TARGET_TRIPLE_FLAG} ${SDK_NAME_VERSION_FLAGS} ${BITCODE} ${VISIBILITY} ${FOBJC_ARC} ${OBJC_VARS} ${CMAKE_OBJC_FLAGS}")
set(CMAKE_OBJC_FLAGS_DEBUG "-O0 -g ${CMAKE_OBJC_FLAGS_DEBUG}")
set(CMAKE_OBJC_FLAGS_MINSIZEREL "-DNDEBUG -Os ${CMAKE_OBJC_FLAGS_MINSIZEREL}")
set(CMAKE_OBJC_FLAGS_RELWITHDEBINFO "-DNDEBUG -O2 -g ${CMAKE_OBJC_FLAGS_RELWITHDEBINFO}")
set(CMAKE_OBJC_FLAGS_RELEASE "-DNDEBUG -O3 ${CMAKE_OBJC_FLAGS_RELEASE}")
set(CMAKE_OBJCXX_FLAGS "${C_TARGET_FLAGS} ${APPLE_TARGET_TRIPLE_FLAG} ${SDK_NAME_VERSION_FLAGS} ${BITCODE} ${VISIBILITY} ${FOBJC_ARC} ${OBJC_VARS} ${CMAKE_OBJCXX_FLAGS}")
set(CMAKE_OBJCXX_FLAGS_DEBUG "-O0 -g ${CMAKE_OBJCXX_FLAGS_DEBUG}")
set(CMAKE_OBJCXX_FLAGS_MINSIZEREL "-DNDEBUG -Os ${CMAKE_OBJCXX_FLAGS_MINSIZEREL}")
set(CMAKE_OBJCXX_FLAGS_RELWITHDEBINFO "-DNDEBUG -O2 -g ${CMAKE_OBJCXX_FLAGS_RELWITHDEBINFO}")
set(CMAKE_OBJCXX_FLAGS_RELEASE "-DNDEBUG -O3 ${CMAKE_OBJCXX_FLAGS_RELEASE}")
set(CMAKE_OBJC_LINK_FLAGS "${C_TARGET_FLAGS} ${SDK_NAME_VERSION_FLAGS} -Wl,-search_paths_first ${CMAKE_OBJC_LINK_FLAGS}")
set(CMAKE_OBJCXX_LINK_FLAGS "${C_TARGET_FLAGS} ${SDK_NAME_VERSION_FLAGS} -Wl,-search_paths_first ${CMAKE_OBJCXX_LINK_FLAGS}")

set(CMAKE_PLATFORM_HAS_INSTALLNAME 1)
set(CMAKE_SHARED_LINKER_FLAGS "-rpath @executable_path/Frameworks -rpath @loader_path/Frameworks")
set(CMAKE_SHARED_LIBRARY_CREATE_C_FLAGS "-dynamiclib -Wl,-headerpad_max_install_names")
set(CMAKE_SHARED_MODULE_CREATE_C_FLAGS "-bundle -Wl,-headerpad_max_install_names")
set(CMAKE_SHARED_MODULE_LOADER_C_FLAG "-Wl,-bundle_loader,")
set(CMAKE_SHARED_MODULE_LOADER_CXX_FLAG "-Wl,-bundle_loader,")
set(CMAKE_FIND_LIBRARY_SUFFIXES ".tbd" ".dylib" ".so" ".a")
set(CMAKE_SHARED_LIBRARY_SONAME_C_FLAG "-install_name")

# Add our libs.
add_subdirectory(${TORQUE_LIB_ROOT_DIRECTORY}) 

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

set(TORQUE_COMPILE_DEFINITIONS ${TORQUE_COMPILE_DEFINITIONS} __MACOSX__)

################# Collect Source Files ###################

# Handle app
torqueToolchainSourceDirectories("app" "app/net")

# Handle console
torqueToolchainSourceDirectories("console")
torqueToolchainSourceDirectories("console/torquescript")

# Handle Platform
torqueToolchainSourceDirectories("platform" "platform/threads" "platform/async"
                                  "platform/input" "platform/output")

torqueToolchainSourceDirectories("platform/nativeDialogs")

# Handle T3D
torqueToolchainSourceDirectories("T3D/fps" "T3D/fx" "T3D/vehicles" "T3D/physics"
                              "T3D/decal" "T3D/sfx" "T3D/gameBase" "T3D/turret"
                              "T3D/lighting" "T3D/gameOBjects" "T3D/components"
                              "T3D/systems" "T3D/assets" "T3D" "T3D/gameBase/std")

# Handle TS
torqueToolchainSourceDirectories("ts" "ts/collada" "ts/assimp" "ts/loader" "ts/arch")

# Handle SFX - OpenAL is handled as a module later on
torqueToolchainSourceDirectories("sfx" "sfx/media" "sfx/null")
if(TORQUE_SFX_OPENAL AND NOT TORQUE_DEDICATED)
    torqueToolchainSourceDirectories("sfx/openal")
    torqueToolchainSourceDirectories("sfx/openal/mac")
endif()
# Handle GFX
torqueToolchainSourceDirectories("gfx" "gfx/Null" "gfx/test" "gfx/bitmap" "gfx/bitmap/loaders"
                             "gfx/util" "gfx/video" "gfx/sim" )

if (TORQUE_OPENGL)
    torqueToolchainSourceDirectories("gfx/gl" "gfx/gl/sdl" "gfx/gl/tGL")
endif (TORQUE_OPENGL)

# Handle core
torqueToolchainSourceDirectories("core" "core/stream" "core/strings" "core/util"
                              "core/util/journal" "core/util/zip" "core/util/compressors")
# Handle GUI
torqueToolchainSourceDirectories("gui" "gui/buttons" "gui/containers" "gui/controls" "gui/core"
                              "gui/game" "gui/shiny" "gui/utility" "gui/3d")

# Handle postFX
torqueToolchainSourceDirectories("postFx")

# Handle Windowmanager
torqueToolchainSourceDirectories("windowManager" "windowManager/torque" "windowManager/sdl")

# Handle scene
torqueToolchainSourceDirectories("scene" "scene/culling" "scene/zones" "scene/mixin")

# Handle math
torqueToolchainSourceDirectories("math" "math/util")

# Handle persistence
torqueToolchainSourceDirectories("persistence/taml" "persistence/taml/binary" "persistence/taml/xml")

# Handle Cinterface
torqueToolchainSourceDirectories("cinterface")

# Handle util
torqueToolchainSourceDirectories("util" "util/messaging")

# Handle assets
torqueToolchainSourceDirectories("assets")

# Handle Sim
torqueToolchainSourceDirectories("sim")

# Handle module
torqueToolchainSourceDirectories("module")

# Handle forest
torqueToolchainSourceDirectories("forest" "forest/ts")
if(TORQUE_OPENGL)
    torqueToolchainSourceDirectories("forest" "forest/glsl")
endif(TORQUE_OPENGL)

# Handle shadergen
torqueToolchainSourceDirectories("shaderGen")

if (TORQUE_OPENGL)
torqueToolchainSourceDirectories("shaderGen/GLSL")
endif (TORQUE_OPENGL)

# Handle terrain
torqueToolchainSourceDirectories("terrain")

if (TORQUE_OPENGL)
torqueToolchainSourceDirectories("terrain/glsl")
endif (TORQUE_OPENGL)

# Handle Materials
torqueToolchainSourceDirectories("materials")

# Handle collision
torqueToolchainSourceDirectories("collision")

# Handle lighting
torqueToolchainSourceDirectories("lighting" "lighting/common"
                                   "lighting/shadowMap")
if (TORQUE_ADVANCED_LIGHTING)
torqueToolchainSourceDirectories("lighting/advanced")
	if (TORQUE_OPENGL)
    torqueToolchainSourceDirectories("lighting/advanced/glsl")
	endif (TORQUE_OPENGL)
endif (TORQUE_ADVANCED_LIGHTING)

if (TORQUE_BASIC_LIGHTING)
torqueToolchainSourceDirectories("lighting/basic" "lighting/basic/shadowMap")
endif (TORQUE_BASIC_LIGHTING)

# Begin handling platform specific stuff
# Handle Platform POSIX
if (UNIX)
torqueToolchainSourceDirectories("platformPOSIX")

	if (TORQUE_CPU_X32 OR TORQUE_CPU_X64)
    torqueToolchainSourceDirectories("platformX86UNIX")
	endif (TORQUE_CPU_X32 OR TORQUE_CPU_X64)
endif (UNIX)

# Mac platform
torqueToolchainSourceDirectories("platformMac")

# Handle platformSDL
torqueToolchainSourceDirectories("platformSDL" "platformSDL/threads")

if(TORQUE_TESTING)
torqueToolchainSourceDirectories("testing")
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

set(TORQUE_SOURCE_FILES ${TORQUE_SOURCE_FILES} ${TORQUE_PLATFORM_MAC_SOURCES} "${CMAKE_SOURCE_DIR}/Tools/CMake/torque.icns")
set_source_files_properties("${CMAKE_SOURCE_DIR}/Tools/CMake/torque.icns" PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")

set(EXECUTABLE_NAME "${TORQUE_APP_NAME}")
configure_file("${CMAKE_SOURCE_DIR}/Tools/CMake/Info.plist.in" "${TORQUE_APP_ROOT_DIRECTORY}/source/Info.plist" COPYONLY)

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


add_executable(${TORQUE_APP_NAME} MACOSX_BUNDLE ${TORQUE_SOURCE_FILES})
set_target_properties(${TORQUE_APP_NAME} PROPERTIES 
    BUNDLE true
    MACOSX_BUNDLE_INFO_PLIST "${TORQUE_APP_ROOT_DIRECTORY}/source/Info.plist")

target_compile_definitions(${TORQUE_APP_NAME} PUBLIC ${TORQUE_COMPILE_DEFINITIONS})
target_link_libraries(${TORQUE_APP_NAME} ${TORQUE_LINK_LIBRARIES})
target_link_options(${TORQUE_APP_NAME} PUBLIC ${TORQUE_LINK_OPTIONS})
if (TORQUE_TARGET_PROPERTIES)
    set_target_properties(${TORQUE_APP_NAME} PROPERTIES ${TORQUE_TARGET_PROPERTIES})
endif (TORQUE_TARGET_PROPERTIES)
target_include_directories(${TORQUE_APP_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_BINARY_DIR}/temp" ${TORQUE_INCLUDE_DIRECTORIES})

append_defs()

foreach (LIBRARY_BINARY ${TORQUE_ADDITIONAL_LIBRARY_BINARIES})
    # For OSX, we want these binaries to be copied to the Frameworks directory
    add_custom_command(TARGET ${TORQUE_APP_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${LIBRARY_BINARY} "${TORQUE_APP_GAME_DIRECTORY}/${TORQUE_APP_NAME}.app/Contents/Frameworks")
endforeach()

# Ensure the shared libraries are actually referenced at the correct path
set(CMAKE_XCODE_ATTRIBUTE_LD_RUNPATH_SEARCH_PATHS "@executable_path/../Frameworks")

install(TARGETS ${APP_NAME}
          BUNDLE DESTINATION . COMPONENT Runtime
          RUNTIME DESTINATION bin COMPONENT Runtime
          LIBRARY DESTINATION lib
          ARCHIVE DESTINATION lib/static)

  # Note Mac specific extension .app
  set(APPS "\${TORQUE_APP_GAME_DIRECTORY}/${APP_NAME}.app")

  # Directories to look for dependencies
  set(DIRS ${CMAKE_BINARY_DIR})

  install(CODE "include(BundleUtilities)
    fixup_bundle(\"${APPS}\" \"\" \"${DIRS}\")")

  set(CPACK_GENERATOR "DRAGNDROP")
  include(CPack)


