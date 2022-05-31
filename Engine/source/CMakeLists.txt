project(${TORQUE_APP_NAME})

file(GLOB TORQUE_APP_SOURCES "app/*.cpp" "app/net/*.cpp")

# Handle Platform
file(GLOB TORQUE_PLATFORM_SOURCES "platform/*.cpp" "platform/threads/*.cpp" "platform/async/*.cpp"
                                  "platform/input/*.cpp" "platform/output/*.cpp")

# Handle T3D
file(GLOB TORQUE_T3D_SOURCES "T3D/fps/*.cpp" "T3D/fx/*.cpp" "T3D/vehicles/*.cpp" "T3D/physics/*.cpp"
                              "T3D/decal/*.cpp" "T3D/sfx/*.cpp" "T3D/gameBase/*.cpp" "T3D/turret/*.cpp"
                              "T3D/lighting/*.cpp" "T3D/gameOBjects/*.cpp" "T3D/components/*.cpp"
                              "T3D/systems/*.cpp" "T3D/assets/*.cpp" "T3D/*.cpp" "T3D/gameBase/std/*.cpp")

# Handle TS
file(GLOB TORQUE_TS_SOURCES "ts/*.cpp" "ts/collada/*.cpp" "ts/assimp/*.cpp" "ts/loader/*.cpp" "ts/arch/*.cpp")

# Handle SFX
file(GLOB TORQUE_SFX_SOURCES "sfx/*.cpp" "sfx/media/*.cpp" "sfx/null/*.cpp")

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

# Handle core
file(GLOB TORQUE_CORE_SOURCES "core/*.cpp" "core/stream/*.cpp" "core/strings/*.cpp" "core/util/*.cpp"
                              "core/util/journal/*.cpp" "core/util/zip/*.cpp" "core/util/compressors/*.cpp")

# Handle GUI
file(GLOB TORQUE_GUI_SOURCES "gui/*.cpp" "gui/buttons/*.cpp" "gui/containers/*.cpp" "gui/controls/*.cpp" "gui/core/*.cpp"
                              "gui/game/*.cpp" "gui/shiny/*.cpp" "gui/utility/*.cpp" "gui/3d/*.cpp")

# Handle postFX
file(GLOB TORQUE_POSTFX_SOURCES "postFx/*.cpp")

# Handle Windowmanager
file(GLOB TORQUE_WINDOW_MANAGER_SOURCES "windowManager/*.cpp" "windowManager/torque/*.cpp" "windowManager/sdl/*.cpp")

# Handle scene
file(GLOB TORQUE_SCENE_SOURCES "scene/*.cpp" "scene/culling/*.cpp" "scene/zones/*.cpp" "scene/mixin/*.cpp")

# Handle console
file(GLOB TORQUE_CONSOLE_SOURCES "console/*.cpp")

# Handle math
file(GLOB TORQUE_MATH_SOURCES "math/*.cpp" "math/util/*.cpp")

# Handle persistence
file(GLOB TORQUE_PERSISTENCE_SOURCES "persistence/taml/*.cpp" "persistence/taml/binary/*.cpp" "persistence/taml/xml/*.cpp")

# Handle Cinterface
file(GLOB TORQUE_CINTERFACE_SOURCES "cinterface/*.cpp")

# Handle app
file(GLOB TORQUE_APP_SOURCES "app/*.cpp" "app/net/*.cpp")

# Handle util
file(GLOB TORQUE_UTIL_SOURCES "util/*.cpp" "util/messaging/*.cpp")

# Handle assets
file(GLOB TORQUE_ASSETS_SOURCES "assets/*.cpp")

# Handle Sim
file(GLOB TORQUE_SIM_SOURCES "sim/*.cpp")

# Handle module
file(GLOB TORQUE_MODULE_SOURCES "module/*.cpp")

# Handle forest
file(GLOB TORQUE_FOREST_SOURCES "forest/*.cpp" "forest/ts/*.cpp")

# Handle shadergen
file(GLOB TORQUE_SHADERGEN_SOURCES "shaderGen/*.cpp" "shaderGen/GLSL/*.cpp")
if (WIN32 AND TORQUE_D3D11)
	file(GLOB TORQUE_SHADERGEN_SOURCES_HLSL "shaderGen/HLSL/*.cpp")
	set(TORQUE_SHADERGEN_SOURCES ${TORQUE_SHADERGEN_SOURCES} ${TORQUE_SHADERGEN_SOURCES_HLSL})
endif (WIN32)

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

# Handle Materials
file(GLOB TORQUE_MATERIALS_SOURCES "materials/*.cpp")

# Handle collision
file(GLOB TORQUE_COLLISION_SOURCES "collision/*.cpp")

# Handle lighting
file(GLOB TORQUE_LIGHTING_SOURCES "lighting/*.cpp" "lighting/common/*.cpp"
                                  "lighting/advanced/*.cpp" "lighting/shadowMap/*.cpp"
                                  "lighting/advanced/glsl/*.cpp")

if (WIN32 AND TORQUE_D3D11)
	file(GLOB TORQUE_LIGHTING_SOURCES_HLSL "lighting/advanced/hlsl/*.cpp")
	set(TORQUE_LIGHTING_SOURCES ${TORQUE_LIGHTING_SOURCES} ${TORQUE_LIGHTING_SOURCES_HLSL})
endif (WIN32 AND TORQUE_D3D11)

# Handle environment
file(GLOB TORQUE_ENVIRONMENT_SOURCES "environment/*.cpp")

# Handle renderInstance
file(GLOB TORQUE_RENDERINSTANCE_SOURCES "renderInstance/*.cpp")

# Handle i18n
file(GLOB TORQUE_I18N_SOURCES "i18n/*.cpp")

# Begin handling platform specific stuff
# Handle Platform POSIX
if (UNIX)
  file(GLOB TORQUE_PLATFORM_POSIX_SOURCES "platformPOSIX/*.cpp")

  if (TORQUE_CPU_X32 OR TORQUE_CPU_X64)
    file(GLOB TORQUE_PLATFORM_X86_UNIX_SOURCES "platformX86UNIX/*.cpp")
    set(TORQUE_PLATFORM_POSIX_SOURCES ${TORQUE_PLATFORM_POSIX_SOURCES} ${TORQUE_PLATFORM_X86_UNIX_SOURCES})
  endif (TORQUE_CPU_X32 OR TORQUE_CPU_X64)
endif (UNIX)

# Handle platformMac
if (APPLE)
  file(GLOB TORQUE_PLATFORM_MAC_SOURCES "platformMac/*.mm")
endif (APPLE)

# Handle platformWin32
if (WIN32)
  file(GLOB TORQUE_PLATFORM_WIN_SOURCES "platformWin32/*.cpp" "platformWin32/videoInfo/*.cpp")
endif (WIN32)

# Handle platformSDL
file(GLOB TORQUE_PLATFORM_SDL_SOURCES "platformSDL/*.cpp" "platformSDL/threads/*.cpp")

# Handle platformX11
if (UNIX AND NOT APPLE)
  file(GLOB TORQUE_PLATFORM_X11_SOURCES "platformX11/*.cpp")
endif (UNIX AND NOT APPLE)

################# Start building libs ###################

set(TORQUE_INCLUDE_DIRECTORIES "")
set(TORQUE_COMPILE_DEFINITIONS ICE_NO_DLL PCRE_STATIC TORQUE_ADVANCED_LIGHTING TORQUE_SHADERGEN
							   TORQUE_OPCODE TORQUE_ASSIMP TORQUE_SDL TORQUE_COLLADA
							   TORQUE_UNICODE UNICODE _UNICODE)

# Set common linkages
set(TORQUE_LINK_LIBRARIES tinyxml collada ljpeg squish png_static opcode assimp
                          SDL2 glad pcre convexDecomp zlib)

# Begin assembling source code payload
set (TORQUE_SOURCE_FILES "main/main.cpp"
                          ${TORQUE_APP_SOURCES} ${TORQUE_RENDERINSTANCE_SOURCES}
                          ${TORQUE_CINTERFACE_SOURCES} ${TORQUE_MATH_SOURCES}
                          ${TORQUE_PLATFORM_SOURCES} ${TORQUE_ASSETS_SOURCES} ${TORQUE_UTIL_SOURCES}
                          ${TORQUE_CORE_SOURCES} ${TORQUE_PERSISTENCE_SOURCES} ${TORQUE_MODULE_SOURCES}
                          ${TORQUE_PLATFORM_SDL_SOURCES} ${TORQUE_PLATFORM_POSIX_SOURCES}
                          ${TORQUE_WINDOW_MANAGER_SOURCES} ${TORQUE_SCENE_SOURCES} ${TORQUE_COLLISION_SOURCES}
                          ${TORQUE_T3D_SOURCES} ${TORQUE_TS_SOURCES} ${TORQUE_SIM_SOURCES} ${TORQUE_MATERIALS_SOURCES}
                          ${TORQUE_SHADERGEN_SOURCES} ${TORQUE_LIGHTING_SOURCES} ${TORQUE_GUI_SOURCES}
                          ${TORQUE_ENVIRONMENT_SOURCES} ${TORQUE_TERRAIN_SOURCES} ${TORQUE_POSTFX_SOURCES}
                          ${TORQUE_I18N_SOURCES} ${TORQUE_CONSOLE_SOURCES} ${TORQUE_SFX_SOURCES} ${TORQUE_GFX_SOURCES})

# When on Windows, we need to link against winsock and windows codecs
if (WIN32)
  set(TORQUE_LINK_LIBRARIES ${TORQUE_LINK_LIBRARIES} WS2_32.LIB windowscodecs.lib)
  set(TORQUE_SOURCE_FILES ${TORQUE_SOURCE_FILES} ${TORQUE_PLATFORM_WIN_SOURCES})
endif (WIN32)

if (WIN32 AND TORQUE_D3D11)
	set(TORQUE_LINK_LIBRARIES ${TORQUE_LINK_LIBRARIES} dxguid.lib)
	set(TORQUE_COMPILE_DEFINITIONS ${TORQUE_COMPILE_DEFINITIONS} TORQUE_D3D11)
endif (WIN32 AND TORQUE_D3D11)

# Only link Apple frameworks when on an Apple platform
if (APPLE)
  enable_language(OBJC)
  set(TORQUE_SOURCE_FILES ${TORQUE_SOURCE_FILES} ${TORQUE_PLATFORM_MAC_SOURCES})
  set(TORQUE_LINK_LIBRARIES ${TORQUE_LINK_LIBRARIES} "-framework Cocoa" "-framework AppKit" "-framework CoreData" "-framework Foundation")
endif (APPLE)

if (TORQUE_OPENGL)
  set(TORQUE_COMPILE_DEFINITIONS ${TORQUE_COMPILE_DEFINITIONS} TORQUE_OPENGL)
endif (TORQUE_OPENGL)

# Linux requires X11 & freetype
if (UNIX AND NOT APPLE)
  set(TORQUE_LINK_LIBRARIES ${TORQUE_LINK_LIBRARIES} "X11" "Xft" "dl" "pthread")
  set(TORQUE_SOURCE_FILES ${TORQUE_SOURCE_FILES} ${TORQUE_PLATFORM_X11_SOURCES})
  
  find_package(Freetype REQUIRED)
  set(TORQUE_INCLUDE_DIRECTORIES ${TORQUE_INCLUDE_DIRECTORIES} ${FREETYPE_INCLUDE_DIRS})
  set(TORQUE_LINK_LIBRARIES ${TORQUE_LINK_LIBRARIES} ${FREETYPE_LIBRARIES})
endif (UNIX AND NOT APPLE)

# Prepare Windows RC file
if (WIN32)
	set(APPLICATION_ICON_PATH "${CMAKE_SOURCE_DIR}/Tools/CMake/torque.ico")
	CONFIGURE_FILE("${CMAKE_SOURCE_DIR}/Tools/CMake/torque-win.rc.in" "${CMAKE_BINARY_DIR}/temp/torque.rc")
	set(TORQUE_SOURCE_FILES ${TORQUE_SOURCE_FILES} "${CMAKE_BINARY_DIR}/temp/torque.rc")
endif (WIN32)



# Search module directories
set(TORQUE_MODULE_PATHS "${CMAKE_SOURCE_DIR}/Tools/CMake/modules")

if (NOT "${TORQUE_MODULE_USER_PATH}" STREQUAL "")
  list(APPEND TORQUE_MODULE_PATHS "${TORQUE_MODULE_USER_PATH}")
endif()

foreach (TORQUE_MODULE_PATH ${TORQUE_MODULE_PATHS})
  # First find simple cmake scripts
  file(GLOB MODULE_SCRIPTS "${TORQUE_MODULE_PATH}/*.cmake")

  message("Found Module Scripts" ${MODULE_SCRIPTS})
  foreach (TORQUE_MODULE_SCRIPT ${MODULE_SCRIPTS})
    message("Including Module Script: ${TORQUE_MODULE_SCRIPT}")
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

if (APPLE)
  # Parameters used for the plist configuration
  set(EXECUTABLE_NAME "${TORQUE_APP_NAME}")

  CONFIGURE_FILE("${CMAKE_SOURCE_DIR}/Tools/CMake/Info.plist.in" "${CMAKE_BINARY_DIR}/temp/Info.plist" COPYONLY)
  set_target_properties(${TORQUE_APP_NAME} PROPERTIES MACOSX_BUNDLE_INFO_PLIST "${CMAKE_BINARY_DIR}/temp/Info.plist")
  
  # Next setup the icon for OSX
  set_source_files_properties("${CMAKE_SOURCE_DIR}/Tools/CMake/torque.icns" PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
endif (APPLE)

# Final executable
if (APPLE)
  add_executable(${TORQUE_APP_NAME} MACOSX_BUNDLE "${CMAKE_SOURCE_DIR}/Tools/CMake/torque.icns" ${TORQUE_SOURCE_FILES})
elseif (WIN32)
  add_executable(${TORQUE_APP_NAME} WIN32 ${TORQUE_SOURCE_FILES})
else()
  add_executable(${TORQUE_APP_NAME} ${TORQUE_SOURCE_FILES})
endif()

target_compile_definitions(${TORQUE_APP_NAME} PUBLIC ${TORQUE_COMPILE_DEFINITIONS})
target_link_libraries(${TORQUE_APP_NAME} ${TORQUE_LINK_LIBRARIES})
target_include_directories(${TORQUE_APP_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_BINARY_DIR}/temp" ${TORQUE_INCLUDE_DIRECTORIES})
target_compile_features(${TORQUE_APP_NAME} PRIVATE cxx_std_17)

if (WIN32)
  set_target_properties(${TORQUE_APP_NAME} PROPERTIES COMPILE_FLAGS "-D_CRT_SECURE_NO_WARNINGS /MP /Zc:wchar_t-")
endif (WIN32)

if (UNIX AND NOT APPLE)
  set_target_properties(${TORQUE_APP_NAME} PROPERTIES LINK_FLAGS "-Wl,-rpath,./")
endif (UNIX AND NOT APPLE)

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
				set_target_properties( ${GAME_LINK_LIBRARY} PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${TORQUE_APP_GAME_DIRECTORY}/${TORQUE_APP_NAME}.app/Resources")
			else()
				set_target_properties( ${GAME_LINK_LIBRARY} PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${TORQUE_APP_GAME_DIRECTORY}")
			endif(APPLE)
		  endif()
	  endif()
	endforeach()
endif (UNIX)