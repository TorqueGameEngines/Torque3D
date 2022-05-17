option(TORQUE_MULTITHREAD "Multi Threading" ON)
mark_as_advanced(TORQUE_MULTITHREAD)

option(TORQUE_POSIX_PATH_CASE_INSENSITIVE "POSIX Pathing Case Insensitivity" ON)
mark_as_advanced(TORQUE_POSIX_PATH_CASE_INSENSITIVE)

option(TORQUE_ZIP_PATH_CASE_INSENSITIVE "ZIP Pathing Case Insensitivity" ON)
mark_as_advanced(TORQUE_ZIP_PATH_CASE_INSENSITIVE)

option(TORQUE_DISABLE_MEMORY_MANAGER "Disable memory manager" ON)
mark_as_advanced(TORQUE_DISABLE_MEMORY_MANAGER)

option(TORQUE_DISABLE_VIRTUAL_MOUNT_SYSTEM "Disable virtual mount system" OFF)
mark_as_advanced(TORQUE_DISABLE_VIRTUAL_MOUNT_SYSTEM)

option(TORQUE_DISABLE_FIND_ROOT_WITHIN_ZIP "Disable reading root path from zip. Zips will be mounted in-place with file name as directory name." ON)
mark_as_advanced(TORQUE_DISABLE_FIND_ROOT_WITHIN_ZIP)

option(TORQUE_ZIP_DISK_LAYOUT "All zips must be placed in the executable directory and contain full paths to the files." OFF)
mark_as_advanced(TORQUE_ZIP_DISK_LAYOUT)

option(TORQUE_PLAYER "Playback only?" OFF)
mark_as_advanced(TORQUE_PLAYER)

option(TORQUE_TOOLS "Enable or disable the tools" ON)
mark_as_advanced(TORQUE_TOOLS)

option(TORQUE_ENABLE_PROFILER "Enable or disable the profiler" OFF)
mark_as_advanced(TORQUE_ENABLE_PROFILER)

option(TORQUE_DEBUG "T3D Debug mode" OFF)
mark_as_advanced(TORQUE_DEBUG)

option(TORQUE_SHIPPING "T3D Shipping build?" OFF)
mark_as_advanced(TORQUE_SHIPPING)

option(TORQUE_DEBUG_NET "debug network" OFF)
mark_as_advanced(TORQUE_DEBUG_NET)

option(TORQUE_DEBUG_NET_MOVES "debug network moves" OFF)
mark_as_advanced(TORQUE_DEBUG_NET_MOVES)

option(TORQUE_ENABLE_ASSERTS "enables or disable asserts" OFF)
mark_as_advanced(TORQUE_ENABLE_ASSERTS)

option(TORQUE_DEBUG_GFX_MODE "triggers graphics debug mode" OFF)
mark_as_advanced(TORQUE_DEBUG_GFX_MODE)

#option(DEBUG_SPEW "more debug" OFF)
set(TORQUE_NO_DSO_GENERATION ON)

if(NOT TORQUE_SCRIPT_EXTENSION)
    set(TORQUE_SCRIPT_EXTENSION "tscript" CACHE STRING "The default script extension to use for TorqueScript files")
endif()

mark_as_advanced(TORQUE_SCRIPT_EXTENSION)

option(TORQUE_USE_ZENITY "use the Zenity backend for NFD" OFF)
mark_as_advanced(TORQUE_USE_ZENITY)

option(TORQUE_SHOW_LEGACY_FILE_FIELDS "If on, shows legacy direct file path fields in the inspector." OFF)
mark_as_advanced(TORQUE_SHOW_LEGACY_FILE_FIELDS)

macro(setupVersionNumbers)
    set(TORQUE_APP_VERSION_MAJOR 1 CACHE STRING "")
    set(TORQUE_APP_VERSION_MINOR 0 CACHE STRING "")
    set(TORQUE_APP_VERSION_PATCH 0 CACHE STRING "")
    set(TORQUE_APP_VERSION_TWEAK 0 CACHE STRING "")
    mark_as_advanced(TORQUE_APP_VERSION_TWEAK)
    MATH(EXPR TORQUE_APP_VERSION "${TORQUE_APP_VERSION_MAJOR} * 1000 + ${TORQUE_APP_VERSION_MINOR} * 100 + ${TORQUE_APP_VERSION_PATCH} * 10 + ${TORQUE_APP_VERSION_TWEAK}")
    set(TORQUE_APP_VERSION_STRING "${TORQUE_APP_VERSION_MAJOR}.${TORQUE_APP_VERSION_MINOR}.${TORQUE_APP_VERSION_PATCH}.${TORQUE_APP_VERSION_TWEAK}")
    #message(STATUS "version numbers: ${TORQUE_APP_VERSION} / ${TORQUE_APP_VERSION_STRING}")
endmacro()
setupVersionNumbers()

# Generate torqueConfig.h in our temp directory
CONFIGURE_FILE("${CMAKE_SOURCE_DIR}/Tools/CMake/torqueConfig.h.in" "${CMAKE_BINARY_DIR}/temp/torqueConfig.h")

# Perform engine build. We do this initially as a lib for easier unit testing.
file(GLOB TORQUE_MAIN_SOURCES "main/*.cpp")
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
                             "gfx/util/*.cpp" "gfx/video/*.cpp" "gfx/sim/*.cpp" "gfx/gl/*.cpp" "gfx/gl/sdl/*.cpp"
                             "gfx/gl/tGL/*.cpp")

# Handle core
file(GLOB TORQUE_CORE_SOURCES "core/*.cpp" "core/stream/*.cpp" "core/strings/*.cpp" "core/util/*.cpp"
                              "core/util/journal/*.cpp" "core/util/zip/*.cpp" "core/util/compressors/*.cpp")

# Handle GUI
file(GLOB TORQUE_GUI_SOURCES "gui/*.cpp" "gui/buttons/*.cpp" "gui/containers/*.cpp" "gui/controls/*.cpp" "gui/core/*.cpp"
                              "gui/game/*.cpp" "gui/shiny/*.cpp" "gui/utility/*.cpp" "gui/3d/*.cpp" "gui/editor/*.cpp"
                              "gui/worldEditor/*.cpp" "gui/worldEditor/tools/*.cpp" "gui/editor/inspector/*.cpp")

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
#addPathRec("${srcDir}/persistence")

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
file(GLOB TORQUE_SHADERGEN_SOURCES "shaderGen/*.cpp" "shadergen/GLSL/*.cpp")

# Handle terrain
file(GLOB TORQUE_TERRAIN_SOURCES "terrain/*.cpp")

# Handle Materials
file(GLOB TORQUE_MATERIALS_SOURCES "materials/*.cpp")

# Handle collision
file(GLOB TORQUE_COLLISION_SOURCES "collision/*.cpp")

# Handle lighting
file(GLOB TORQUE_LIGHTING_SOURCES "lighting/*.cpp" "lighting/common/*.cpp"
                                  "lighting/advanced/*.cpp" "lighting/shadowMap/*.cpp"
                                  "lighting/advanced/glsl/*.cpp")

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
endif (UNIX)

# Handle platformMac
if (APPLE)
  file(GLOB TORQUE_PLATFORM_MAC_SOURCES "platformMac/*.mm")
endif (APPLE)

# Handle platformSDL
file(GLOB TORQUE_PLATFORM_SDL_SOURCES "platformSDL/*.cpp" "platformSDL/threads/*.cpp")

# Link generic libs
set(TORQUE_LINK_LIBRARIES ${TORQUE_LINK_LIBRARIES} png "-framework Cocoa" "-framework AppKit" "-framework CoreData" "-framework Foundation")
set(TORQUE_COMPILE_DEFINITIONS ICE_NO_DLL PCRE_STATIC TORQUE_ADVANCED_LIGHTING TORQUE_TOOLS TORQUE_SHADERGEN TORQUE_OPENGL TORQUE_OPCODE TORQUE_ASSIMP TORQUE_SDL TORQUE_COLLADA TORQUE_UNICODE)

################# Start building libs ###################

# Set common linkages
set(TORQUE_LINK_LIBRARIES tinyxml collada ljpeg squish png_static opcode assimp
                          SDL2 glad pcre convexDecomp "-framework Cocoa" "-framework AppKit"
                          "-framework CoreData" "-framework Foundation")


set(CPACK_BUNDLE_NAME "Game")
set(CPACK_BUNDLE_ICON "${CMAKE_SOURCE_DIR}/Tools/CMake/torque.icns")
set(CPACK_BUNDLE_PLIS "${CMAKE_SOURCE_DIR}/Tools/CMake/Info.plist.in")
set(CPACK_PACKAGE_EXECUTABLES "Game" "Game")

# Final executable
add_executable(Game MACOSX_BUNDLE "main/main.cpp"
                                  ${TORQUE_APP_SOURCES} ${TORQUE_RENDERINSTANCE_SOURCES}
                                  ${TORQUE_CINTERFACE_SOURCES} ${TORQUE_MATH_SOURCES}
                                  ${TORQUE_PLATFORM_SOURCES} ${TORQUE_ASSETS_SOURCES} ${TORQUE_UTIL_SOURCES}
                                  ${TORQUE_CORE_SOURCES} ${TORQUE_PERSISTENCE_SOURCES} ${TORQUE_MODULE_SOURCES}
                                  ${TORQUE_PLATFORM_SDL_SOURCES} ${TORQUE_PLATFORM_MAC_SOURCES} ${TORQUE_PLATFORM_POSIX_SOURCES}
                                  ${TORQUE_WINDOW_MANAGER_SOURCES} ${TORQUE_SFX_SOURCES} ${TORQUE_SCENE_SOURCES} ${TORQUE_COLLISION_SOURCES}
                                  ${TORQUE_T3D_SOURCES} ${TORQUE_TS_SOURCES} ${TORQUE_SIM_SOURCES} ${TORQUE_MATERIALS_SOURCES}
                                  ${TORQUE_SHADERGEN_SOURCES} ${TORQUE_LIGHTING_SOURCES} ${TORQUE_GUI_SOURCES}
                                  ${TORQUE_ENVIRONMENT_SOURCES} ${TORQUE_TERRAIN_SOURCES} ${TORQUE_POSTFX_SOURCES}
                                  ${TORQUE_I18N_SOURCES} ${TORQUE_CONSOLE_SOURCES} ${TORQUE_GFX_SOURCES})
target_compile_definitions(Game PUBLIC ${TORQUE_COMPILE_DEFINITIONS})
target_link_libraries(Game ${TORQUE_LINK_LIBRARIES})
target_include_directories(Game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_BINARY_DIR}/temp")

set(EXECUTABLE_NAME "Game")
CONFIGURE_FILE("${CMAKE_SOURCE_DIR}/Tools/CMake/Info.plist.in" "${CMAKE_BINARY_DIR}/temp/Info.plist" COPYONLY)
set_target_properties(Game PROPERTIES MACOSX_BUNDLE_INFO_PLIST "${CMAKE_BINARY_DIR}/temp/Info.plist")

install(TARGETS Game
    BUNDLE DESTINATION . COMPONENT Runtime
    RUNTIME DESTINATION bin COMPONENT Runtime
)

# Note Mac specific extension .app
set(APPS "\${CMAKE_INSTALL_PREFIX}/Game.app")

# Directories to look for dependencies
# FIXME: Auto detect?
set(DIRS ${CMAKE_BINARY_DIR}/temp/sdl2 ${CMAKE_BINARY_DIR}/temp/assimp/bin)

install(CODE "include(BundleUtilities)
    fixup_bundle(\"${APPS}\" \"\" \"${DIRS}\")")
