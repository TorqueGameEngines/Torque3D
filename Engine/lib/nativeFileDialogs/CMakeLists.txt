option(TORQUE_USE_ZENITY "Use Zenity" ON)

set(TORQUE_NFD_ROOT "${CMAKE_SOURCE_DIR}/Engine/lib/nativeFileDialogs")
set(TORQUE_NFD_COMMON_SOURCES "${TORQUE_NFD_ROOT}/nfd_common.c")
set(TORQUE_NFD_INCLUDE_DIRECTORIES "${TORQUE_NFD_ROOT}" "${TORQUE_NFD_ROOT}/include")

if (APPLE)
  set(TORQUE_NFD_SOURCES ${TORQUE_NFD_COMMON_SOURCES} "${TORQUE_NFD_ROOT}/nfd_cocoa.m")
elseif (UNIX)
  if (TORQUE_USE_ZENITY)
    set(TORQUE_NFD_SOURCES ${TORQUE_NFD_COMMON_SOURCES} "${TORQUE_NFD_ROOT}/nfd_zenity.c")
  else()
    set(TORQUE_NFD_SOURCES ${TORQUE_NFD_COMMON_SOURCES} "${TORQUE_NFD_ROOT}/nfd_gtk.c")
  endif()
  
elseif (WIN32)
  set(TORQUE_NFD_SOURCES ${TORQUE_NFD_COMMON_SOURCES} "${TORQUE_NFD_ROOT}/nfd_win.cpp")
endif(APPLE)

add_library(nativeFileDialogs STATIC ${TORQUE_NFD_SOURCES})
target_include_directories(nativeFileDialogs PUBLIC ${TORQUE_NFD_INCLUDE_DIRECTORIES})
