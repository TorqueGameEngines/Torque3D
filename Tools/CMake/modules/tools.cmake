# Torque Tools module
option(TORQUE_TOOLS "Enable Torque Tools" ON)

if(TORQUE_TOOLS)
  message("Enabling Torque Tools Module")

  file(GLOB TORQUE_TOOLS_SOURCES "gui/editor/*.cpp" "gui/worldEditor/*.cpp" "gui/worldEditor/tools/*.cpp"
                                 "gui/editor/inspector/*.cpp")
  set(TORQUE_SOURCE_FILES ${TORQUE_SOURCE_FILES} ${TORQUE_TOOLS_SOURCES})
  set(TORQUE_COMPILE_DEFINITIONS ${TORQUE_COMPILE_DEFINITIONS} TORQUE_TOOLS)
endif(TORQUE_TOOLS)
