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


#[[
addPathRec("${srcDir}/app")


addPath("${srcDir}/i18n")
addPath("${srcDir}/util")

addPath("${srcDir}/platform")
if(NOT TORQUE_SDL)
   set(BLACKLIST "fileDialog.cpp" )
endif()
addPath("${srcDir}/platform/nativeDialogs")
set(BLACKLIST "" )

if( NOT TORQUE_DEDICATED )
    addPath("${srcDir}/platform/menus")
endif()


addPath("${srcDir}/collision")
addPath("${srcDir}/materials")
addPath("${srcDir}/lighting")
addPath("${srcDir}/lighting/common")
addPath("${srcDir}/renderInstance")
addPath("${srcDir}/renderInstance/debug")
addPath("${srcDir}/shaderGen")
addPath("${srcDir}/terrain")
addPath("${srcDir}/environment")

addPath("${srcDir}/physics")

addPath("${srcDir}/postFx")

addPath("${srcDir}/T3D")
set(BLACKLIST "" )



addPath("${srcDir}/module")


addPathRec("${projectSrcDir}")
]]

# Perform engine build. We do this initially as a lib for easier unit testing.
file(GLOB TORQUE_MAIN_SOURCES "main/*.cpp")
file(GLOB TORQUE_APP_SOURCES "app/*.cpp")

# Handle Platform
file(GLOB TORQUE_PLATFORM_SOURCES "platform/threads/*.cpp" "platform/async/*.cpp" "platform/input/*.cpp" "platform/output/*.cpp")

# Handle T3D
file(GLOB TORQUE_3D_NEXT_SOURCES "T3D/fps/*.cpp")
file(GLOB TORQUE_T3D_SOURCES ${TORQUE_3D_NEXT_SOURCES})

file(GLOB TORQUE_3D_NEXT_SOURCES "T3D/fx/*.cpp")
file(GLOB TORQUE_T3D_SOURCES ${TORQUE_T3D_SOURCES} ${TORQUE_3D_NEXT_SOURCES})

file(GLOB TORQUE_3D_NEXT_SOURCES "T3D/vehicles/*.cpp")
file(GLOB TORQUE_T3D_SOURCES ${TORQUE_T3D_SOURCES} ${TORQUE_3D_NEXT_SOURCES})

file(GLOB TORQUE_3D_NEXT_SOURCES "T3D/physics/*.cpp")
file(GLOB TORQUE_T3D_SOURCES ${TORQUE_T3D_SOURCES} ${TORQUE_3D_NEXT_SOURCES})

file(GLOB TORQUE_3D_NEXT_SOURCES "T3D/decal/*.cpp")
file(GLOB TORQUE_T3D_SOURCES ${TORQUE_T3D_SOURCES} ${TORQUE_3D_NEXT_SOURCES})

file(GLOB TORQUE_3D_NEXT_SOURCES "T3D/sfx/*.cpp")
file(GLOB TORQUE_T3D_SOURCES ${TORQUE_T3D_SOURCES} ${TORQUE_3D_NEXT_SOURCES})

file(GLOB TORQUE_3D_NEXT_SOURCES "T3D/gameBase/*.cpp")
file(GLOB TORQUE_T3D_SOURCES ${TORQUE_T3D_SOURCES} ${TORQUE_3D_NEXT_SOURCES})

file(GLOB TORQUE_3D_NEXT_SOURCES "T3D/turret/*.cpp")
file(GLOB TORQUE_T3D_SOURCES ${TORQUE_T3D_SOURCES} ${TORQUE_3D_NEXT_SOURCES})

file(GLOB TORQUE_3D_NEXT_SOURCES "T3D/lighting/*.cpp")
file(GLOB TORQUE_T3D_SOURCES ${TORQUE_T3D_SOURCES} ${TORQUE_3D_NEXT_SOURCES})

file(GLOB TORQUE_3D_NEXT_SOURCES "T3D/gameOBjects/*.cpp")
file(GLOB TORQUE_T3D_SOURCES ${TORQUE_T3D_SOURCES} ${TORQUE_3D_NEXT_SOURCES})

file(GLOB TORQUE_3D_NEXT_SOURCES "T3D/components/*.cpp")
file(GLOB TORQUE_T3D_SOURCES ${TORQUE_T3D_SOURCES} ${TORQUE_3D_NEXT_SOURCES})

file(GLOB TORQUE_3D_NEXT_SOURCES "T3D/systems/*.cpp")
file(GLOB TORQUE_T3D_SOURCES ${TORQUE_T3D_SOURCES} ${TORQUE_3D_NEXT_SOURCES})

file(GLOB TORQUE_3D_NEXT_SOURCES "T3D/assets/*.cpp")
file(GLOB TORQUE_T3D_SOURCES ${TORQUE_T3D_SOURCES} ${TORQUE_3D_NEXT_SOURCES})

#message(FATAL_ERROR ${TORQUE_T3D_SOURCES})

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
                              "gui/game/*.cpp" "gui/shiny/*.cpp" "gui/utility/*.cpp" "gui/3d/*.cpp")

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

file(GLOB TORQUE_PERSISTENCE_SOURCES "persistence/taml/*.cpp")

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
file(GLOB TORQUE_SHADERGEN_SOURCES "shadergen/*.cpp")

# Handle terrain
file(GLOB TORQUE_TERRAIN_SOURCES "terrain/*.cpp")

# Handle Materials
file(GLOB TORQUE_MATERIALS_SOURCES "materals/*.cpp")

# Handle collision
file(GLOB TORQUE_COLLISION_SOURCES "collision/*.cpp")

# Begin handling platform specific stuff
# Handle Platform POSIX
if (UNIX)
  file(GLOB TORQUE_PLATFORM_POSIX_SOURCES "platformPOSIX/*.cpp")
endif (UNIX)

# Handle platformMac
if (APPLE)
  file(GLOB TORQUE_PLATFORM_MAC_SOURCES "platformMac/*.mm")
endif (APPLE)

# Link generic libs
set(TORQUE_LINK_LIBRARIES ${TORQUE_LINK_LIBRARIES} png "-framework Cocoa" "-framework AppKit" "-framework CoreData" "-framework Foundation")

# Final executable
add_executable(Game ${TORQUE_PLATFORM_SOURCES} ${TORQUE_UTIL_SOURCES} ${TORQUE_CORE_SOURCES}
                    ${TORQUE_T3D_SOURCES} ${TORQUE_SIM_SOURCES} ${TORQUE_SFX_SOURCES} ${TORQUE_APP_SOURCES} ${TORQUE_CONSOLE_SOURCES}
                    ${TORQUE_PERSISTENCE_SOURCES} ${TORQUE_PLATFORM_MAC_SOURCES} ${TORQUE_PLATFORM_POSIX_SOURCES}
                    ${TORQUE_GUI_SOURCES} ${TORQUE_GFX_SOURCES} ${TORQUE_APP_SOURCES} ${TORQUE_MATH_SOURCES}
                    ${TORQUE_PERSISTENCE_SOURCES} ${TORQUE_ASSETS_SOURCES} ${TORQUE_WINDOW_MANAGER_SOURCES}
                    ${TORQUE_TERRAIN_SOURCES} ${TORQUE_TS_SOURCES} ${TORQUE_CINTERFACE_SOURCES} ${TORQUE_COLLISION_SOURCES}
                    ${TORQUE_SCENE_SOURCES} ${TORQUE_MATERIALS_SOURCES} "main/main.cpp")

target_compile_definitions(Game PUBLIC ICE_NO_DLL TORQUE_OPCODE TORQUE_SDL TORQUE_COLLADA TORQUE_COLLADA TORQUE_UNICODE)
target_link_libraries(Game tinyxml collada ljpeg squish png assimp SDL2 "-framework Cocoa" "-framework AppKit" "-framework CoreData"
                      "-framework Foundation")
target_include_directories(Game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_BINARY_DIR}/temp")
