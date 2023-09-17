# Navigation module
option(TORQUE_NAVIGATION "Enable Navigation module" ON)

if(TORQUE_NAVIGATION)
  message("Enabling Navigation Module")
  
  file(GLOB_RECURSE TORQUE_NAV_SOURCES "${CMAKE_SOURCE_DIR}/Engine/source/navigation/*.cpp" "${CMAKE_SOURCE_DIR}/Engine/source/navigation/*.h" )
  set(TORQUE_SOURCE_FILES ${TORQUE_SOURCE_FILES} ${TORQUE_NAV_SOURCES})
  set(TORQUE_LINK_LIBRARIES ${TORQUE_LINK_LIBRARIES} recast)
  set(TORQUE_COMPILE_DEFINITIONS ${TORQUE_COMPILE_DEFINITIONS} recast TORQUE_NAVIGATION_ENABLED)

  # Since recast lives elsewhere we need to ensure it is known to Torque when providing a link to it
  add_subdirectory("${CMAKE_SOURCE_DIR}/Engine/lib/recast" ${CMAKE_BINARY_DIR}/temp/recast EXCLUDE_FROM_ALL)
  source_group(TREE "${CMAKE_SOURCE_DIR}/Engine/source/navigation/" PREFIX "Modules/NAVIGATION" FILES ${TORQUE_NAV_SOURCES})
endif(TORQUE_NAVIGATION)
