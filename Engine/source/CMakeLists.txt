project(${TORQUE_APP_NAME})

# Enable ObjectiveC compilation when compiling for Apple platforms
if (APPLE)
	enable_language(OBJC)
endif (APPLE)

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

################# Set Conditional Engine Defines ###################

if (TORQUE_OPENGL)
	set(TORQUE_COMPILE_DEFINITIONS ${TORQUE_COMPILE_DEFINITIONS} TORQUE_OPENGL)
endif (TORQUE_OPENGL)

if (TORQUE_D3D11)
	set(TORQUE_COMPILE_DEFINITIONS ${TORQUE_COMPILE_DEFINITIONS} TORQUE_D3D11)
endif (TORQUE_D3D11)

if (TORQUE_ADVANCED_LIGHTING)
	set(TORQUE_COMPILE_DEFINITIONS ${TORQUE_COMPILE_DEFINITIONS} TORQUE_ADVANCED_LIGHTING)
endif (TORQUE_ADVANCED_LIGHTING)

if (TORQUE_BASIC_LIGHTING)
	set(TORQUE_COMPILE_DEFINITIONS ${TORQUE_COMPILE_DEFINITIONS} TORQUE_BASIC_LIGHTING)
endif (TORQUE_BASIC_LIGHTING)

# On Windows we disable CRT Security warnings - this comes from recommendations to use non-portable functions.
if (WIN32)
	set(TORQUE_COMPILE_DEFINITIONS ${TORQUE_COMPILE_DEFINITIONS} _CRT_SECURE_NO_WARNINGS)
endif (WIN32)

################# Set Engine Linkages ###################

# When on Windows, we need to link against winsock and windows codecs
if (WIN32)
	set(TORQUE_LINK_LIBRARIES ${TORQUE_LINK_LIBRARIES} WS2_32.LIB windowscodecs.lib)
	set(TORQUE_SOURCE_FILES ${TORQUE_SOURCE_FILES} ${TORQUE_PLATFORM_WIN_SOURCES})
	
	if (TORQUE_D3D11)
		set(TORQUE_LINK_LIBRARIES ${TORQUE_LINK_LIBRARIES} dxguid.lib)
	endif (TORQUE_D3D11)
endif (WIN32)

# Only link Apple frameworks when on an Apple platform
if (APPLE)
	set(TORQUE_LINK_LIBRARIES ${TORQUE_LINK_LIBRARIES} "-framework Cocoa" "-framework AppKit" "-framework CoreData" "-framework Foundation")
endif (APPLE)

# Linux requires X11 & freetype
if (UNIX AND NOT APPLE)
	set(TORQUE_LINK_LIBRARIES ${TORQUE_LINK_LIBRARIES} "X11" "Xft" "dl" "pthread")
	set(TORQUE_SOURCE_FILES ${TORQUE_SOURCE_FILES} ${TORQUE_PLATFORM_X11_SOURCES})
  
	find_package(Freetype REQUIRED)
	set(TORQUE_INCLUDE_DIRECTORIES ${TORQUE_INCLUDE_DIRECTORIES} ${FREETYPE_INCLUDE_DIRS})
	set(TORQUE_LINK_LIBRARIES ${TORQUE_LINK_LIBRARIES} ${FREETYPE_LIBRARIES})
endif (UNIX AND NOT APPLE)

################# Collect Source Files ###################

set(TORQUE_SOURCE_FILES "main/main.cpp")

# Handle app
file(GLOB TORQUE_APP_SOURCES "app/*.cpp" "app/net/*.cpp")
set(TORQUE_SOURCE_FILES ${TORQUE_SOURCE_FILES} ${TORQUE_APP_SOURCES})

# Handle console
file(GLOB TORQUE_CONSOLE_SOURCES "console/*.cpp")
set(TORQUE_SOURCE_FILES ${TORQUE_SOURCE_FILES} ${TORQUE_CONSOLE_SOURCES})

# Handle Platform
file(GLOB TORQUE_PLATFORM_SOURCES "platform/*.cpp" "platform/threads/*.cpp" "platform/async/*.cpp"
                                  "platform/input/*.cpp" "platform/output/*.cpp")
set(TORQUE_SOURCE_FILES ${TORQUE_SOURCE_FILES} ${TORQUE_PLATFORM_SOURCES})

# Handle T3D
file(GLOB TORQUE_T3D_SOURCES "T3D/fps/*.cpp" "T3D/fx/*.cpp" "T3D/vehicles/*.cpp" "T3D/physics/*.cpp"
                              "T3D/decal/*.cpp" "T3D/sfx/*.cpp" "T3D/gameBase/*.cpp" "T3D/turret/*.cpp"
                              "T3D/lighting/*.cpp" "T3D/gameOBjects/*.cpp" "T3D/components/*.cpp"
                              "T3D/systems/*.cpp" "T3D/assets/*.cpp" "T3D/*.cpp" "T3D/gameBase/std/*.cpp")
set(TORQUE_SOURCE_FILES ${TORQUE_SOURCE_FILES} ${TORQUE_T3D_SOURCES})

# Handle TS
file(GLOB TORQUE_TS_SOURCES "ts/*.cpp" "ts/collada/*.cpp" "ts/assimp/*.cpp" "ts/loader/*.cpp" "ts/arch/*.cpp")
set(TORQUE_SOURCE_FILES ${TORQUE_SOURCE_FILES} ${TORQUE_TS_SOURCES})

# Handle SFX - OpenAL is handled as a module later on
file(GLOB TORQUE_SFX_SOURCES "sfx/*.cpp" "sfx/media/*.cpp" "sfx/null/*.cpp")
set(TORQUE_SOURCE_FILES ${TORQUE_SOURCE_FILES} ${TORQUE_SFX_SOURCES})

# Handle GFX
file(GLOB TORQUE_GFX_SOURCES "gfx/*.cpp" "gfx/Null/*.cpp" "gfx/test/*.cpp" "gfx/bitmap/*.cpp" "gfx/bitmap/loaders/*.cpp"
                             "gfx/util/*.cpp" "gfx/video/*.cpp" "gfx/sim/*.cpp" )

if (TORQUE_OPENGL)
	file(GLOB TORQUE_GFX_SOURCES_OPENGL "gfx/gl/*.cpp" "gfx/gl/sdl/*.cpp" "gfx/gl/tGL/*.cpp")
	set(TORQUE_GFX_SOURCES ${TORQUE_GFX_SOURCES} ${TORQUE_GFX_SOURCES_OPENGL})
endif (TORQUE_OPENGL)

if (WIN32 AND TORQUE_D3D11)
	file(GLOB TORQUE_GFX_SOURCES_D3D11 "gfx/D3D11/*.cpp")
	set(TORQUE_GFX_SOURCES ${TORQUE_GFX_SOURCES} ${TORQUE_GFX_SOURCES_D3D11})
endif (WIN32 AND TORQUE_D3D11)

set(TORQUE_SOURCE_FILES ${TORQUE_SOURCE_FILES} ${TORQUE_GFX_SOURCES})

# Handle core
file(GLOB TORQUE_CORE_SOURCES "core/*.cpp" "core/stream/*.cpp" "core/strings/*.cpp" "core/util/*.cpp"
                              "core/util/journal/*.cpp" "core/util/zip/*.cpp" "core/util/compressors/*.cpp")
set(TORQUE_SOURCE_FILES ${TORQUE_SOURCE_FILES} ${TORQUE_CORE_SOURCES})

# Handle GUI
file(GLOB TORQUE_GUI_SOURCES "gui/*.cpp" "gui/buttons/*.cpp" "gui/containers/*.cpp" "gui/controls/*.cpp" "gui/core/*.cpp"
                              "gui/game/*.cpp" "gui/shiny/*.cpp" "gui/utility/*.cpp" "gui/3d/*.cpp")
set(TORQUE_SOURCE_FILES ${TORQUE_SOURCE_FILES} ${TORQUE_GUI_SOURCES})

# Handle postFX
file(GLOB TORQUE_POSTFX_SOURCES "postFx/*.cpp")
set(TORQUE_SOURCE_FILES ${TORQUE_SOURCE_FILES} ${TORQUE_POSTFX_SOURCES})

# Handle Windowmanager
file(GLOB TORQUE_WINDOW_MANAGER_SOURCES "windowManager/*.cpp" "windowManager/torque/*.cpp" "windowManager/sdl/*.cpp")
set(TORQUE_SOURCE_FILES ${TORQUE_SOURCE_FILES} ${TORQUE_WINDOW_MANAGER_SOURCES})

# Handle scene
file(GLOB TORQUE_SCENE_SOURCES "scene/*.cpp" "scene/culling/*.cpp" "scene/zones/*.cpp" "scene/mixin/*.cpp")
set(TORQUE_SOURCE_FILES ${TORQUE_SOURCE_FILES} ${TORQUE_SCENE_SOURCES})

# Handle math
file(GLOB TORQUE_MATH_SOURCES "math/*.cpp" "math/util/*.cpp")
set(TORQUE_SOURCE_FILES ${TORQUE_SOURCE_FILES} ${TORQUE_MATH_SOURCES})

# Handle persistence
file(GLOB TORQUE_PERSISTENCE_SOURCES "persistence/taml/*.cpp" "persistence/taml/binary/*.cpp" "persistence/taml/xml/*.cpp")
set(TORQUE_SOURCE_FILES ${TORQUE_SOURCE_FILES} ${TORQUE_PERSISTENCE_SOURCES})

# Handle Cinterface
file(GLOB TORQUE_CINTERFACE_SOURCES "cinterface/*.cpp")
set(TORQUE_SOURCE_FILES ${TORQUE_SOURCE_FILES} ${TORQUE_CINTERFACE_SOURCES})

# Handle util
file(GLOB TORQUE_UTIL_SOURCES "util/*.cpp" "util/messaging/*.cpp")
set(TORQUE_SOURCE_FILES ${TORQUE_SOURCE_FILES} ${TORQUE_UTIL_SOURCES})

# Handle assets
file(GLOB TORQUE_ASSETS_SOURCES "assets/*.cpp")
set(TORQUE_SOURCE_FILES ${TORQUE_SOURCE_FILES} ${TORQUE_ASSETS_SOURCES})

# Handle Sim
file(GLOB TORQUE_SIM_SOURCES "sim/*.cpp")
set(TORQUE_SOURCE_FILES ${TORQUE_SOURCE_FILES} ${TORQUE_SIM_SOURCES})

# Handle module
file(GLOB TORQUE_MODULE_SOURCES "module/*.cpp")
set(TORQUE_SOURCE_FILES ${TORQUE_SOURCE_FILES} ${TORQUE_MODULE_SOURCES})

# Handle forest
file(GLOB TORQUE_FOREST_SOURCES "forest/*.cpp" "forest/ts/*.cpp")
set(TORQUE_SOURCE_FILES ${TORQUE_SOURCE_FILES} ${TORQUE_FOREST_SOURCES})

# Handle shadergen
file(GLOB TORQUE_SHADERGEN_SOURCES "shaderGen/*.cpp")

if (WIN32 AND TORQUE_D3D11)
	file(GLOB TORQUE_SHADERGEN_SOURCES_HLSL "shaderGen/HLSL/*.cpp")
	set(TORQUE_SHADERGEN_SOURCES ${TORQUE_SHADERGEN_SOURCES} ${TORQUE_SHADERGEN_SOURCES_HLSL})
endif (WIN32)

if (TORQUE_OPENGL)
	file(GLOB TORQUE_SHADERGEN_SOURCES_GLSL "shaderGen/GLSL/*.cpp")
	set(TORQUE_SHADERGEN_SOURCES ${TORQUE_SHADERGEN_SOURCES} ${TORQUE_SHADERGEN_SOURCES_GLSL})
endif (TORQUE_OPENGL)

set(TORQUE_SOURCE_FILES ${TORQUE_SOURCE_FILES} ${TORQUE_SHADERGEN_SOURCES})

# Handle terrain
file(GLOB TORQUE_TERRAIN_SOURCES "terrain/*.cpp")

if (WIN32 AND TORQUE_D3D11)
	file(GLOB TORQUE_TERRAIN_SOURCES_HLSL "terrain/hlsl/*.cpp")
	set(TORQUE_TERRAIN_SOURCES ${TORQUE_TERRAIN_SOURCES} ${TORQUE_TERRAIN_SOURCES_HLSL})
endif (WIN32 AND TORQUE_D3D11)

if (TORQUE_OPENGL)
	file(GLOB TORQUE_TERRAIN_SOURCES_GLSL "terrain/glsl/*.cpp")
	set(TORQUE_TERRAIN_SOURCES ${TORQUE_TERRAIN_SOURCES} ${TORQUE_TERRAIN_SOURCES_GLSL})
endif (TORQUE_OPENGL)

set(TORQUE_SOURCE_FILES ${TORQUE_SOURCE_FILES} ${TORQUE_TERRAIN_SOURCES})

# Handle Materials
file(GLOB TORQUE_MATERIALS_SOURCES "materials/*.cpp")
set(TORQUE_SOURCE_FILES ${TORQUE_SOURCE_FILES} ${TORQUE_MATERIALS_SOURCES})

# Handle collision
file(GLOB TORQUE_COLLISION_SOURCES "collision/*.cpp")
set(TORQUE_SOURCE_FILES ${TORQUE_SOURCE_FILES} ${TORQUE_COLLISION_SOURCES})

# Handle lighting
file(GLOB TORQUE_LIGHTING_SOURCES "lighting/*.cpp" "lighting/common/*.cpp"
                                   "lighting/shadowMap/*.cpp")

if (TORQUE_ADVANCED_LIGHTING)
	file(GLOB TORQUE_LIGHTING_SOURCES_ADVANCED "lighting/advanced/*.cpp")
	set(TORQUE_LIGHTING_SOURCES ${TORQUE_LIGHTING_SOURCES} ${TORQUE_LIGHTING_SOURCES_ADVANCED})
	
	if (WIN32 AND TORQUE_D3D11)
		file(GLOB TORQUE_LIGHTING_SOURCES_HLSL "lighting/advanced/hlsl/*.cpp")
		set(TORQUE_LIGHTING_SOURCES ${TORQUE_LIGHTING_SOURCES} ${TORQUE_LIGHTING_SOURCES_HLSL})
	endif (WIN32 AND TORQUE_D3D11)

	if (TORQUE_OPENGL)
		file(GLOB TORQUE_LIGHTING_SOURCES_GLSL "lighting/advanced/glsl/*.cpp")
		set(TORQUE_LIGHTING_SOURCES ${TORQUE_LIGHTING_SOURCES} ${TORQUE_LIGHTING_SOURCES_GLSL})
	endif (TORQUE_OPENGL)
endif (TORQUE_ADVANCED_LIGHTING)

if (TORQUE_BASIC_LIGHTING)
	file(GLOB TORQUE_LIGHTING_SOURCES_BASIC "lighting/basic/*.cpp" "lighting/basic/shadowMap/*.cpp")
	set(TORQUE_LIGHTING_SOURCES ${TORQUE_LIGHTING_SOURCES} ${TORQUE_LIGHTING_SOURCES_BASIC})
endif (TORQUE_BASIC_LIGHTING)

set(TORQUE_SOURCE_FILES ${TORQUE_SOURCE_FILES} ${TORQUE_LIGHTING_SOURCES})

# Handle environment
file(GLOB TORQUE_ENVIRONMENT_SOURCES "environment/*.cpp")
set(TORQUE_SOURCE_FILES ${TORQUE_SOURCE_FILES} ${TORQUE_ENVIRONMENT_SOURCES})

# Handle renderInstance
file(GLOB TORQUE_RENDERINSTANCE_SOURCES "renderInstance/*.cpp")
set(TORQUE_SOURCE_FILES ${TORQUE_SOURCE_FILES} ${TORQUE_RENDERINSTANCE_SOURCES})

# Handle i18n
file(GLOB TORQUE_I18N_SOURCES "i18n/*.cpp")
set(TORQUE_SOURCE_FILES ${TORQUE_SOURCE_FILES} ${TORQUE_I18N_SOURCES})

# Begin handling platform specific stuff
# Handle Platform POSIX
if (UNIX)
	file(GLOB TORQUE_PLATFORM_POSIX_SOURCES "platformPOSIX/*.cpp")

	if (TORQUE_CPU_X32 OR TORQUE_CPU_X64)
		file(GLOB TORQUE_PLATFORM_X86_UNIX_SOURCES "platformX86UNIX/*.cpp")
		set(TORQUE_PLATFORM_POSIX_SOURCES ${TORQUE_PLATFORM_POSIX_SOURCES} ${TORQUE_PLATFORM_X86_UNIX_SOURCES})
	endif (TORQUE_CPU_X32 OR TORQUE_CPU_X64)
	
	set(TORQUE_SOURCE_FILES ${TORQUE_SOURCE_FILES} ${TORQUE_PLATFORM_POSIX_SOURCES})
endif (UNIX)

# Handle platformMac
if (APPLE)
	file(GLOB TORQUE_PLATFORM_MAC_SOURCES "platformMac/*.mm")
	set(TORQUE_SOURCE_FILES ${TORQUE_SOURCE_FILES} ${TORQUE_PLATFORM_MAC_SOURCES})
endif (APPLE)

# Handle platformWin32
if (WIN32)
	file(GLOB TORQUE_PLATFORM_WIN_SOURCES "platformWin32/*.cpp" "platformWin32/videoInfo/*.cpp")
	set(TORQUE_SOURCE_FILES ${TORQUE_SOURCE_FILES} ${TORQUE_PLATFORM_WIN_SOURCES})
endif (WIN32)

# Handle platformSDL
file(GLOB TORQUE_PLATFORM_SDL_SOURCES "platformSDL/*.cpp" "platformSDL/threads/*.cpp")
set(TORQUE_SOURCE_FILES ${TORQUE_SOURCE_FILES} ${TORQUE_PLATFORM_SDL_SOURCES})

# Handle platformX11
if (UNIX AND NOT APPLE)
	file(GLOB TORQUE_PLATFORM_X11_SOURCES "platformX11/*.cpp")
	set(TORQUE_SOURCE_FILES ${TORQUE_SOURCE_FILES} ${TORQUE_PLATFORM_X11_SOURCES})
endif (UNIX AND NOT APPLE)

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

################# Engine Module Handling ###################

set(TORQUE_MODULE_PATHS "${CMAKE_SOURCE_DIR}/Tools/CMake/modules" "${TORQUE_APP_GAME_DIRECTORY}/data")
if (NOT "${TORQUE_MODULE_USER_PATH}" STREQUAL "")
	list(APPEND TORQUE_MODULE_PATHS "${TORQUE_MODULE_USER_PATH}")
endif()

foreach (TORQUE_MODULE_PATH ${TORQUE_MODULE_PATHS})
	# First find simple cmake scripts
	file(GLOB MODULE_SCRIPTS "${TORQUE_MODULE_PATH}/*.cmake")
	foreach (TORQUE_MODULE_SCRIPT ${MODULE_SCRIPTS})
		include(${TORQUE_MODULE_SCRIPT})
	endforeach()

	# Next find sub projects
	SUBDIRLIST(POSSIBLE_PROJECTS "${TORQUE_MODULE_PATH}")
	foreach (POSSIBLE_PROJECT ${POSSIBLE_PROJECTS})
		# Retrieve the absolute path of this possible project
		get_filename_component(POSSIBLE_PROJECT_ABSOLUTEPATH "${POSSIBLE_PROJECT}"
							   REALPATH BASE_DIR "${TORQUE_MODULE_PATH}")

		if (EXISTS "${POSSIBLE_PROJECT_ABSOLUTEPATH}/CMakeLists.txt")
			add_subdirectory("${POSSIBLE_PROJECT_ABSOLUTEPATH}" ${CMAKE_BINARY_DIR}/temp/${POSSIBLE_PROJECT} EXCLUDE_FROM_ALL)
		endif()
	endforeach()
endforeach()

################# Executable Generation ###################

if (APPLE)
	add_executable(${TORQUE_APP_NAME} MACOSX_BUNDLE ${TORQUE_SOURCE_FILES})
	set_target_properties(${TORQUE_APP_NAME} PROPERTIES MACOSX_BUNDLE_INFO_PLIST "${CMAKE_BINARY_DIR}/temp/Info.plist")

  # Ensure the shared libraries are actually referenced at the correct path
  add_custom_command(TARGET ${TORQUE_APP_NAME} POST_BUILD COMMAND install_name_tool -add_rpath "@executable_path/../Frameworks" ${TORQUE_APP_GAME_DIRECTORY}/${TORQUE_APP_NAME}.app/Contents/MacOS/${TORQUE_APP_NAME})

  # Clear the absolute rpath generated by default
  add_custom_command(TARGET ${TORQUE_APP_NAME} POST_BUILD COMMAND install_name_tool -delete_rpath "${TORQUE_APP_GAME_DIRECTORY}/${TORQUE_APP_NAME}.app/Contents/Frameworks" ${TORQUE_APP_GAME_DIRECTORY}/${TORQUE_APP_NAME}.app/Contents/MacOS/${TORQUE_APP_NAME})
elseif (WIN32)
	add_executable(${TORQUE_APP_NAME} WIN32 ${TORQUE_SOURCE_FILES})
	
	# NOTE: On Windows, /Zc:wchar_t- is necessary otherwise you get unicode errors
	set_target_properties(${TORQUE_APP_NAME} PROPERTIES COMPILE_FLAGS "/Zc:wchar_t-")
else()
	add_executable(${TORQUE_APP_NAME} ${TORQUE_SOURCE_FILES})
	
	# NOTE: On Linux, we set the rpath to ./ so that shared objects next to the executable are used
	set_target_properties(${TORQUE_APP_NAME} PROPERTIES LINK_FLAGS "-Wl,-rpath,./")
endif()

target_compile_definitions(${TORQUE_APP_NAME} PUBLIC ${TORQUE_COMPILE_DEFINITIONS})
target_link_libraries(${TORQUE_APP_NAME} ${TORQUE_LINK_LIBRARIES})
target_include_directories(${TORQUE_APP_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_BINARY_DIR}/temp" ${TORQUE_INCLUDE_DIRECTORIES})
target_compile_features(${TORQUE_APP_NAME} PRIVATE cxx_std_17)

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