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
file(GLOB TORQUE_SFX_SOURCES "sfx/*.cpp" "sfx/media/*.cpp" "sfx/null/*.cpp" "sfx/openal/*.cpp" "sfx/openal/mac/*.cpp")

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
                          SDL2 glad pcre convexDecomp OpenAL)

# Only link Apple frameworks when on an Apple platform
if (APPLE)
  set(TORQUE_LINK_LIBRARIES ${TORQUE_LINK_LIBRARIES} "-framework Cocoa" "-framework AppKit" "-framework CoreData" "-framework Foundation")
endif (APPLE)

# Begin assembling source code payload
set (TORQUE_SOURCE_FILES "main/main.cpp"
                          ${TORQUE_APP_SOURCES} ${TORQUE_RENDERINSTANCE_SOURCES}
                          ${TORQUE_CINTERFACE_SOURCES} ${TORQUE_MATH_SOURCES}
                          ${TORQUE_PLATFORM_SOURCES} ${TORQUE_ASSETS_SOURCES} ${TORQUE_UTIL_SOURCES}
                          ${TORQUE_CORE_SOURCES} ${TORQUE_PERSISTENCE_SOURCES} ${TORQUE_MODULE_SOURCES}
                          ${TORQUE_PLATFORM_SDL_SOURCES} ${TORQUE_PLATFORM_MAC_SOURCES} ${TORQUE_PLATFORM_POSIX_SOURCES}
                          ${TORQUE_WINDOW_MANAGER_SOURCES} ${TORQUE_SCENE_SOURCES} ${TORQUE_COLLISION_SOURCES}
                          ${TORQUE_T3D_SOURCES} ${TORQUE_TS_SOURCES} ${TORQUE_SIM_SOURCES} ${TORQUE_MATERIALS_SOURCES}
                          ${TORQUE_SHADERGEN_SOURCES} ${TORQUE_LIGHTING_SOURCES} ${TORQUE_GUI_SOURCES}
                          ${TORQUE_ENVIRONMENT_SOURCES} ${TORQUE_TERRAIN_SOURCES} ${TORQUE_POSTFX_SOURCES}
                          ${TORQUE_I18N_SOURCES} ${TORQUE_CONSOLE_SOURCES} ${TORQUE_SFX_SOURCES} ${TORQUE_GFX_SOURCES})

# Search module directories
set(TORQUE_MODULE_PATHS "${CMAKE_SOURCE_DIR}/Tools/CMake/modules")
foreach (TORQUE_MODULE_PATH ${TORQUE_MODULE_PATHS})
  # First find simple cmake scripts
  file(GLOB MODULE_SCRIPTS "${TORQUE_MODULE_PATH}/*.cmake")

  message("Found Module Scripts" ${MODULE_SCRIPTS})
  foreach (TORQUE_MODULE_SCRIPT ${MODULE_SCRIPTS})
    message("Including Module Script: ${TORQUE_MODULE_SCRIPT}")
    include(${TORQUE_MODULE_SCRIPT})
  endforeach()
endforeach()

# Final executable
add_executable(Game MACOSX_BUNDLE ${TORQUE_SOURCE_FILES})

target_compile_definitions(Game PUBLIC ${TORQUE_COMPILE_DEFINITIONS})
target_link_libraries(Game ${TORQUE_LINK_LIBRARIES})
target_include_directories(Game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_BINARY_DIR}/temp")

set(EXECUTABLE_NAME "Game")
CONFIGURE_FILE("${CMAKE_SOURCE_DIR}/Tools/CMake/Info.plist.in" "${CMAKE_BINARY_DIR}/temp/Info.plist" COPYONLY)
set_target_properties(Game PROPERTIES MACOSX_BUNDLE_INFO_PLIST "${CMAKE_BINARY_DIR}/temp/Info.plist")

install(TARGETS Game
    BUNDLE DESTINATION game COMPONENT Runtime
    RUNTIME DESTINATION bin COMPONENT Runtime
)

# Note Mac specific extension .app
set(APPS "\${CMAKE_INSTALL_PREFIX}/game/Game.app")

# Directories to look for dependencies
# FIXME: Auto detect?
set(DIRS ${CMAKE_BINARY_DIR}/temp/sdl2 ${CMAKE_BINARY_DIR}/temp/openal-soft ${CMAKE_BINARY_DIR}/temp/assimp/bin)

install(CODE "include(BundleUtilities)
    fixup_bundle(\"${APPS}\" \"\" \"${DIRS}\")")
