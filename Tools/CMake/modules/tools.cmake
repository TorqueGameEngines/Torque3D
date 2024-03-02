# Torque Tools module
option(TORQUE_TOOLS "Enable Torque Tools" ON)

if(TORQUE_TOOLS)
  message("Enabling Torque Tools Module")

  file(GLOB_RECURSE TORQUE_TOOLS_SOURCES  "gui/editor/*.cpp" "gui/editor/*.h" "gui/worldEditor/*.cpp" "gui/worldEditor/*.h" "gui/shaderEditor/*.cpp" "gui/shaderEditor/*.h"
                                          "gui/shaderEditor/nodes/*.cpp" "gui/shaderEditor/nodes/*.h")
  file(GLOB_RECURSE TORQUE_TOOLS_SOURCES2 "environment/editors/*.cpp" "environment/editors/*.h")
  file(GLOB_RECURSE TORQUE_TOOLS_SOURCES3 "forest/editor/*.cpp" "forest/editor/*.h")
                                         
  set(TORQUE_SOURCE_FILES ${TORQUE_SOURCE_FILES} ${TORQUE_TOOLS_SOURCES} ${TORQUE_TOOLS_SOURCES2} ${TORQUE_TOOLS_SOURCES3})
  set(TORQUE_COMPILE_DEFINITIONS ${TORQUE_COMPILE_DEFINITIONS} TORQUE_TOOLS)
  #VS display
  source_group(TREE "${CMAKE_SOURCE_DIR}/Engine/source/gui/" PREFIX "Modules/TOOLS/gui" FILES ${TORQUE_TOOLS_SOURCES})  
  source_group(TREE "${CMAKE_SOURCE_DIR}/Engine/source/environment/editors/" PREFIX "Modules/TOOLS/environment" FILES ${TORQUE_TOOLS_SOURCES2})  
  source_group(TREE "${CMAKE_SOURCE_DIR}/Engine/source/forest/editor/" PREFIX "Modules/TOOLS/forest" FILES ${TORQUE_TOOLS_SOURCES3})
endif(TORQUE_TOOLS)
