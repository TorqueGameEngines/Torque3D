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
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
    include_directories(${GTK3_INCLUDE_DIRS})
    link_directories(${GTK3_LIBRARY_DIRS})
    add_definitions(${GTK3_CFLAGS_OTHER})

    set(TORQUE_NFD_SOURCES ${TORQUE_NFD_COMMON_SOURCES} "${TORQUE_NFD_ROOT}/nfd_gtk.c")

  endif()
  
elseif (WIN32)
  set(TORQUE_NFD_SOURCES ${TORQUE_NFD_COMMON_SOURCES} "${TORQUE_NFD_ROOT}/nfd_win.cpp")
endif(APPLE)

add_library(nativeFileDialogs STATIC ${TORQUE_NFD_SOURCES})
target_include_directories(nativeFileDialogs PUBLIC ${TORQUE_NFD_INCLUDE_DIRECTORIES})

if(UNIX)
  target_link_libraries(nativeFileDialogs ${GTK3_LIBRARIES})
endif()
