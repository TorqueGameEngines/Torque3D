# Navigation module
option(TORQUE_NAVIGATION "Enable Navigation module" ON)

if(TORQUE_NAVIGATION)
  message("Enabling Navigation Module")

  torqueAddSourceDirectories("${CMAKE_SOURCE_DIR}/Engine/source/navigation")
  set(TORQUE_LINK_LIBRARIES ${TORQUE_LINK_LIBRARIES} recast)
  set(TORQUE_COMPILE_DEFINITIONS ${TORQUE_COMPILE_DEFINITIONS} recast TORQUE_NAVIGATION_ENABLED)

  # Since recast lives elsewhere we need to ensure it is known to Torque when providing a link to it
  add_subdirectory("${CMAKE_SOURCE_DIR}/Engine/lib/recast" ${CMAKE_BINARY_DIR}/temp/recast EXCLUDE_FROM_ALL)
endif(TORQUE_NAVIGATION)
