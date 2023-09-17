# Torque Tools module
option(TORQUE_TOOLS "Enable Torque Tools" ON)

if(TORQUE_TOOLS)
  message("Enabling Torque Tools Module")

  file(GLOB_RECURSE TORQUE_TOOLS_SOURCES "gui/editor/*.cpp" "gui/worldEditor/*.cpp")
  set(TORQUE_SOURCE_FILES ${TORQUE_SOURCE_FILES} ${TORQUE_TOOLS_SOURCES})
  set(TORQUE_COMPILE_DEFINITIONS ${TORQUE_COMPILE_DEFINITIONS} TORQUE_TOOLS)
  source_group(TREE "${CMAKE_SOURCE_DIR}/Engine/source/gui/" PREFIX "Modules/TOOLS" FILES ${TORQUE_TOOLS_SOURCES})
endif(TORQUE_TOOLS)
