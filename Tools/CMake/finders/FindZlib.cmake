# Ensure zlib has been added before using this module
if(TARGET zlib)
  set(ZLIB_FOUND TRUE)
  set(ZLIB_INCLUDE_DIRS $<TARGET_PROPERTY:zlib,INTERFACE_INCLUDE_DIRECTORIES>)
  set(ZLIB_LIBRARIES zlib)
  message(STATUS "Using Torques build of zlib.")
  # Provide an alias for consistency with modern CMake
  if(NOT TARGET ZLIB::ZLIB)
    add_library(ZLIB::ZLIB ALIAS zlib)
  endif()
else()
  set(ZLIB_FOUND FALSE)
  message(FATAL_ERROR "Zlib was not added with add_subdirectory before calling find_package(ZLIB).")
endif()