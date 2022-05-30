# OpenAL module
option(TORQUE_SFX_OPENAL "Use OpenAL SFX" ON)

if(TORQUE_SFX_OPENAL)
  message("Enabling OpenAL Module")

  file(GLOB TORQUE_OPENAL_SOURCES "${CMAKE_SOURCE_DIR}/Engine/source/sfx/openal/*.cpp")

  if (APPLE)
    file(GLOB TORQUE_OPENAL_MAC_SOURCES "${CMAKE_SOURCE_DIR}/Engine/source/sfx/openal/mac/*.cpp")
    set(TORQUE_OPENAL_SOURCES ${TORQUE_OPENAL_SOURCES} ${TORQUE_OPENAL_MAC_SOURCES})
  elseif (WIN32)
    file(GLOB TORQUE_OPENAL_WIN_SOURCES "${CMAKE_SOURCE_DIR}/Engine/source/sfx/openal/win32/*.cpp")
    set(TORQUE_OPENAL_SOURCES ${TORQUE_OPENAL_SOURCES} ${TORQUE_OPENAL_WIN_SOURCES})
  elseif (UNIX)
    file(GLOB TORQUE_OPENAL_LINUX_SOURCES "${CMAKE_SOURCE_DIR}/Engine/source/sfx/openal/linux/*.cpp")
    set(TORQUE_OPENAL_SOURCES ${TORQUE_OPENAL_SOURCES} ${TORQUE_OPENAL_LINUX_SOURCES})
  else()
    message(FATAL_ERROR "Unsupported OpenAL platform.")
  endif (APPLE)

  set(TORQUE_SOURCE_FILES ${TORQUE_SOURCE_FILES} ${TORQUE_OPENAL_SOURCES})
  set(TORQUE_LINK_LIBRARIES ${TORQUE_LINK_LIBRARIES} OpenAL)

  # Since OpenAL lives elsewhere we need to ensure it is known to Torque when providing a link to it
  set(ALSOFT_EXAMPLES OFF CACHE BOOL "OpenAL Examples" FORCE)
  set(ALSOFT_UPDATE_BUILD_VERSION OFF CACHE BOOL "Update build Version" UPDATE)

  add_subdirectory("${CMAKE_SOURCE_DIR}/Engine/lib/openal-soft" ${CMAKE_BINARY_DIR}/temp/openal-soft EXCLUDE_FROM_ALL)
endif(TORQUE_SFX_OPENAL)
