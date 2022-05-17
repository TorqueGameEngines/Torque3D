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
                             "gfx/util/*.cpp" "gfx/video/*.cpp" "gfx/sim/*.cpp")

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
set(TORQUE_LINK_LIBRARIES tinyxml collada ljpeg squish png opcode assimp
                          SDL2 glad pcre "-framework Cocoa" "-framework AppKit"
                          "-framework CoreData" "-framework Foundation")

# [[ SFX ]]
add_library(SFX STATIC ${TORQUE_SFX_SOURCES})
target_compile_definitions(SFX PUBLIC ICE_NO_DLL ${TORQUE_COMPILE_DEFINITIONS})
target_link_libraries(SFX PUBLIC ${TORQUE_LINK_LIBRARIES})
target_include_directories(SFX PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_BINARY_DIR}/temp")

# [[ GFX ]]
add_library(GFX STATIC ${TORQUE_GFX_SOURCES})
target_compile_definitions(GFX PUBLIC ICE_NO_DLL ${TORQUE_COMPILE_DEFINITIONS})
target_link_libraries(GFX PUBLIC ${TORQUE_LINK_LIBRARIES})
target_include_directories(GFX PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_BINARY_DIR}/temp")

# [[ Console ]]
add_library(Console STATIC ${TORQUE_CONSOLE_SOURCES})
target_compile_definitions(Console PUBLIC ICE_NO_DLL ${TORQUE_COMPILE_DEFINITIONS})
target_link_libraries(Console PUBLIC ${TORQUE_LINK_LIBRARIES})
target_include_directories(Console PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_BINARY_DIR}/temp")

# [[ Core ]]
add_library(Core STATIC ${TORQUE_CORE_SOURCES})
target_compile_definitions(Core PUBLIC ICE_NO_DLL ${TORQUE_COMPILE_DEFINITIONS})
target_link_libraries(Core PUBLIC ${TORQUE_LINK_LIBRARIES} Console)
target_include_directories(Core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_BINARY_DIR}/temp")

# [[ Util ]]
add_library(Util STATIC ${TORQUE_UTIL_SOURCES})
target_compile_definitions(Util PUBLIC ICE_NO_DLL ${TORQUE_COMPILE_DEFINITIONS})
target_link_libraries(Util PUBLIC ${TORQUE_LINK_LIBRARIES})
target_include_directories(Util PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_BINARY_DIR}/temp")

# [[ Math ]]
add_library(Math STATIC ${TORQUE_MATH_SOURCES})
target_compile_definitions(Math PUBLIC ${TORQUE_COMPILE_DEFINITIONS})
target_link_libraries(Math PUBLIC ${TORQUE_LINK_LIBRARIES})
target_include_directories(Math PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_BINARY_DIR}/temp")

# [[ Generic Platform ]]
add_library(Platform STATIC ${TORQUE_PLATFORM_SOURCES})
target_compile_definitions(Platform PUBLIC ${TORQUE_COMPILE_DEFINITIONS})
target_link_libraries(Platform PUBLIC ${TORQUE_LINK_LIBRARIES})
target_include_directories(Platform PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_BINARY_DIR}/temp")

# [[ SDL Platform ]]
add_library(PlatformSDL STATIC ${TORQUE_PLATFORM_SDL_SOURCES})
target_compile_definitions(PlatformSDL PUBLIC ${TORQUE_COMPILE_DEFINITIONS})
target_link_libraries(PlatformSDL PUBLIC ${TORQUE_LINK_LIBRARIES})
target_include_directories(PlatformSDL PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_BINARY_DIR}/temp")

# [[ App ]]
add_library(App STATIC ${TORQUE_APP_SOURCES})
target_compile_definitions(App PUBLIC ${TORQUE_COMPILE_DEFINITIONS})
target_link_libraries(App PUBLIC ${TORQUE_LINK_LIBRARIES})
target_include_directories(App PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_BINARY_DIR}/temp")

# [[ CInterface ]]
add_library(CInterface STATIC ${TORQUE_CINTERFACE_SOURCES})
target_compile_definitions(CInterface PUBLIC ${TORQUE_COMPILE_DEFINITIONS})
target_link_libraries(CInterface PUBLIC ${TORQUE_LINK_LIBRARIES})
target_include_directories(CInterface PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_BINARY_DIR}/temp")

# [[ Assets ]]
add_library(Assets STATIC ${TORQUE_ASSETS_SOURCES})
target_compile_definitions(Assets PUBLIC ${TORQUE_COMPILE_DEFINITIONS})
target_link_libraries(Assets PUBLIC ${TORQUE_LINK_LIBRARIES})
target_include_directories(Assets PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_BINARY_DIR}/temp")

# [[ Persistence ]]
add_library(Persistence STATIC ${TORQUE_PERSISTENCE_SOURCES})
target_compile_definitions(Persistence PUBLIC ${TORQUE_COMPILE_DEFINITIONS})
target_link_libraries(Persistence PUBLIC ${TORQUE_LINK_LIBRARIES})
target_include_directories(Persistence PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_BINARY_DIR}/temp")

# [[ TS ]]
add_library(TS STATIC ${TORQUE_TS_SOURCES})
target_compile_definitions(TS PUBLIC ${TORQUE_COMPILE_DEFINITIONS})
target_link_libraries(TS PUBLIC ${TORQUE_LINK_LIBRARIES})
target_include_directories(TS PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_BINARY_DIR}/temp")

# [[ Module ]]
add_library(Module STATIC ${TORQUE_MODULE_SOURCES})
target_compile_definitions(Module PUBLIC ${TORQUE_COMPILE_DEFINITIONS})
target_link_libraries(Module PUBLIC ${TORQUE_LINK_LIBRARIES})
target_include_directories(Module PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_BINARY_DIR}/temp")

# [[ T3D ]]
add_library(T3D STATIC ${TORQUE_T3D_SOURCES})
target_compile_definitions(T3D PUBLIC ${TORQUE_COMPILE_DEFINITIONS})
target_link_libraries(T3D PUBLIC ${TORQUE_LINK_LIBRARIES})
target_include_directories(T3D PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_BINARY_DIR}/temp")

# [[ Scene ]]
add_library(Scene STATIC ${TORQUE_SCENE_SOURCES})
target_compile_definitions(Scene PUBLIC ${TORQUE_COMPILE_DEFINITIONS})
target_link_libraries(Scene PUBLIC ${TORQUE_LINK_LIBRARIES})
target_include_directories(Scene PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_BINARY_DIR}/temp")

# [[ Collision ]]
add_library(Collision STATIC ${TORQUE_COLLISION_SOURCES})
target_compile_definitions(Collision PUBLIC ${TORQUE_COMPILE_DEFINITIONS})
target_link_libraries(Collision PUBLIC ${TORQUE_LINK_LIBRARIES})
target_include_directories(Collision PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_BINARY_DIR}/temp")

# [[ Window Manager ]]
add_library(WindowManager STATIC ${TORQUE_WINDOW_MANAGER_SOURCES})
target_compile_definitions(WindowManager PUBLIC ${TORQUE_COMPILE_DEFINITIONS})
target_link_libraries(WindowManager PUBLIC ${TORQUE_LINK_LIBRARIES})
target_include_directories(WindowManager PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_BINARY_DIR}/temp")

# [[ POSIX Platform ]]
add_library(PlatformPOSIX STATIC ${TORQUE_PLATFORM_POSIX_SOURCES})
target_compile_definitions(PlatformPOSIX PUBLIC ${TORQUE_COMPILE_DEFINITIONS})
target_link_libraries(PlatformPOSIX PUBLIC ${TORQUE_LINK_LIBRARIES})
target_include_directories(PlatformPOSIX PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_BINARY_DIR}/temp")

# [[ Sim ]]
add_library(Sim STATIC ${TORQUE_SIM_SOURCES})
target_compile_definitions(Sim PUBLIC ICE_NO_DLL ${TORQUE_COMPILE_DEFINITIONS})
target_link_libraries(Sim PUBLIC ${TORQUE_LINK_LIBRARIES})
target_include_directories(Sim PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_BINARY_DIR}/temp")

# [[ GUI ]]
add_library(GUI STATIC ${TORQUE_GUI_SOURCES})
target_compile_definitions(GUI PUBLIC ${TORQUE_COMPILE_DEFINITIONS})
target_link_libraries(GUI PUBLIC ${TORQUE_LINK_LIBRARIES})
target_include_directories(GUI PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_BINARY_DIR}/temp")

# [[ Terrain ]]
add_library(Terrain STATIC ${TORQUE_TERRAIN_SOURCES})
target_compile_definitions(Terrain PUBLIC ${TORQUE_COMPILE_DEFINITIONS})
target_link_libraries(Terrain PUBLIC ${TORQUE_LINK_LIBRARIES})
target_include_directories(Terrain PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_BINARY_DIR}/temp")

# [[ Lighting ]]
add_library(Lighting STATIC ${TORQUE_LIGHTING_SOURCES})
target_compile_definitions(Lighting PUBLIC ${TORQUE_COMPILE_DEFINITIONS})
target_link_libraries(Lighting PUBLIC ${TORQUE_LINK_LIBRARIES})
target_include_directories(Lighting PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_BINARY_DIR}/temp")

# [[ Shadergen ]]
add_library(Shadergen STATIC ${TORQUE_SHADERGEN_SOURCES})
target_compile_definitions(Shadergen PUBLIC ${TORQUE_COMPILE_DEFINITIONS})
target_link_libraries(Shadergen PUBLIC ${TORQUE_LINK_LIBRARIES})
target_include_directories(Shadergen PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_BINARY_DIR}/temp")

# [[ Materials ]]
add_library(Materials STATIC ${TORQUE_MATERIALS_SOURCES})
target_compile_definitions(Materials PUBLIC ${TORQUE_COMPILE_DEFINITIONS})
target_link_libraries(Materials PUBLIC ${TORQUE_LINK_LIBRARIES})
target_include_directories(Materials PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_BINARY_DIR}/temp")

# [[ MacOS Platform ]]
add_library(PlatformMac STATIC ${TORQUE_PLATFORM_MAC_SOURCES})
target_compile_definitions(PlatformMac PUBLIC ${TORQUE_COMPILE_DEFINITIONS})
target_link_libraries(PlatformMac PUBLIC ${TORQUE_LINK_LIBRARIES})
target_include_directories(PlatformMac PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_BINARY_DIR}/temp")

# [[ RenderInstance ]]
add_library(RenderInstance STATIC ${TORQUE_RENDERINSTANCE_SOURCES})
target_compile_definitions(RenderInstance PUBLIC ${TORQUE_COMPILE_DEFINITIONS})
target_link_libraries(RenderInstance PUBLIC ${TORQUE_LINK_LIBRARIES})
target_include_directories(RenderInstance PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_BINARY_DIR}/temp")

# [[ PostFX ]]
add_library(PostFX STATIC ${TORQUE_POSTFX_SOURCES})
target_compile_definitions(PostFX PUBLIC ${TORQUE_COMPILE_DEFINITIONS})
target_link_libraries(PostFX PUBLIC ${TORQUE_LINK_LIBRARIES})
target_include_directories(PostFX PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_BINARY_DIR}/temp")

# [[ i18n ]]
add_library(I18N STATIC ${TORQUE_I18N_SOURCES})
target_compile_definitions(I18N PUBLIC ${TORQUE_COMPILE_DEFINITIONS})
target_link_libraries(I18N PUBLIC ${TORQUE_LINK_LIBRARIES})
target_include_directories(I18N PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_BINARY_DIR}/temp")

# [[ Environment ]]
add_library(Environment STATIC ${TORQUE_ENVIRONMENT_SOURCES})
target_compile_definitions(Environment PUBLIC ${TORQUE_COMPILE_DEFINITIONS})
target_link_libraries(Environment PUBLIC ${TORQUE_LINK_LIBRARIES})
target_include_directories(Environment PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_BINARY_DIR}/temp")

# Final executable
add_executable(Game "main/main.cpp")
target_compile_definitions(Game PUBLIC ${TORQUE_COMPILE_DEFINITIONS})
target_link_libraries(Game ${TORQUE_LINK_LIBRARIES} App Assets Platform Math Console Util Core
                                                    CInterface Persistence Module PlatformSDL PlatformMac
                                                    PlatformPOSIX WindowManager GFX SFX Scene Collision T3D TS
                                                    Sim Materials Shadergen Lighting GUI Environment Terrain
                                                    RenderInstance PostFX I18N)
target_include_directories(Game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_BINARY_DIR}/temp")
