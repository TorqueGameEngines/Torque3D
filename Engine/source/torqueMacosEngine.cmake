
set(TORQUE_COMPILE_DEFINITIONS ${TORQUE_COMPILE_DEFINITIONS} __MACOSX__)

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
    torqueAddSourceDirectories("sfx/openal/mac")
endif()

# Handle GFX
torqueAddSourceDirectories("gfx" "gfx/Null" "gfx/test" "gfx/bitmap" "gfx/bitmap/loaders"
                             "gfx/util" "gfx/video" "gfx/sim" )

if (TORQUE_OPENGL)
  torqueAddSourceDirectories("gfx/gl" "gfx/gl/sdl" "gfx/gl/tGL")
endif (TORQUE_OPENGL)

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

# Handle shadergen
torqueAddSourceDirectories("shaderGen")

if (TORQUE_OPENGL)
  torqueAddSourceDirectories("shaderGen/GLSL")
endif (TORQUE_OPENGL)

# Handle terrain
torqueAddSourceDirectories("terrain")

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

# Handle posix
torqueAddSourceDirectories("platformPOSIX")
torqueAddSourceDirectories("platformMac")

# Handle platformSDL
torqueAddSourceDirectories("platformSDL" "platformSDL/threads")

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
################# Dynamic File Configuration ###################

set(MACOSX_RESOURCES "${CMAKE_SOURCE_DIR}/Tools/CMake/torque.icns" 
        "${TORQUE_APP_GAME_DIRECTORY}/data"
        "${TORQUE_APP_GAME_DIRECTORY}/core"
        "${TORQUE_APP_GAME_DIRECTORY}/tools"
        "${TORQUE_APP_GAME_DIRECTORY}/main.${TORQUE_SCRIPT_EXTENSION}")

set(TORQUE_SOURCE_FILES ${TORQUE_SOURCE_FILES} ${TORQUE_PLATFORM_MAC_SOURCES} ${MACOSX_RESOURCES})

source_group("Resources" FILES ${MACOSX_RESOURCES})

set_source_files_properties(${MACOSX_RESOURCES} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")

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
  MACOSX_BUNDLE_INFO_PLIST "${TORQUE_APP_ROOT_DIRECTORY}/source/Info.plist"
  XCODE_ATTRIBUTE_INSTALL_PATH "/Applications"
  XCODE_ATTRIBUTE_SKIP_INSTALL "No"
  MACOSX_RPATH TRUE)

  set_property(GLOBAL PROPERTY USE_FOLDERS ON)
foreach (TORQUE_LIBRARY ${TORQUE_LINK_LIBRARIES})
  set_target_properties(${TORQUE_LIBRARY} PROPERTIES
  FOLDER "Libraries")
endforeach()

target_compile_definitions(${TORQUE_APP_NAME} PUBLIC ${TORQUE_COMPILE_DEFINITIONS})
target_link_libraries(${TORQUE_APP_NAME} ${TORQUE_LINK_LIBRARIES} ${TORQUE_LINK_FRAMEWORKS})

target_link_options(${TORQUE_APP_NAME} PUBLIC ${TORQUE_LINK_OPTIONS})
if (TORQUE_TARGET_PROPERTIES)
   set_target_properties(${TORQUE_APP_NAME} PROPERTIES ${TORQUE_TARGET_PROPERTIES})
endif (TORQUE_TARGET_PROPERTIES)
target_include_directories(${TORQUE_APP_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_BINARY_DIR}/temp" ${TORQUE_INCLUDE_DIRECTORIES})

append_defs()

foreach (LIBRARY_BINARY ${TORQUE_ADDITIONAL_LIBRARY_BINARIES})
    add_custom_command(TARGET ${TORQUE_APP_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${LIBRARY_BINARY} "${TORQUE_APP_GAME_DIRECTORY}/${TORQUE_APP_NAME}.app/Contents/Frameworks/$(CONFIGURATION)")
endforeach()

get_target_property(GAME_LINK_LIBRARIES ${TORQUE_APP_NAME} LINK_LIBRARIES)
foreach (GAME_LINK_LIBRARY ${GAME_LINK_LIBRARIES})
    if (TARGET ${GAME_LINK_LIBRARY})
        get_target_property(LINK_LIBRARY_TYPE ${GAME_LINK_LIBRARY} TYPE)
        # Only pay attention to shared libraries and make them output to the app resources
        if ("${LINK_LIBRARY_TYPE}" STREQUAL "SHARED_LIBRARY")
            set_target_properties(${GAME_LINK_LIBRARY} PROPERTIES 
            XCODE_ATTRIBUTE_INSTALL_PATH "@rpath")
        endif()
    endif()
endforeach()

