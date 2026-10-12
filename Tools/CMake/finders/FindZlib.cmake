# Ensure zlib has been added before using this module
if(TARGET ZLIB::ZLIB)
  # Already resolved by an earlier find_package(ZLIB) call this configure —
  # just reuse it, no extra work needed.
  set(ZLIB_FOUND TRUE)
  get_target_property(ZLIB_INCLUDE_DIRS ZLIB::ZLIB INTERFACE_INCLUDE_DIRECTORIES)
  set(ZLIB_LIBRARIES ZLIB::ZLIB)
else()
  # Not resolved yet 
  set(_torque_saved_module_path "${CMAKE_MODULE_PATH}")
  list(REMOVE_ITEM CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/Tools/CMake/finders")

  find_package(ZLIB MODULE REQUIRED)

  set(CMAKE_MODULE_PATH "${_torque_saved_module_path}")
  unset(_torque_saved_module_path)

  message(STATUS "Resolved zlib via vcpkg for: ${CMAKE_FIND_PACKAGE_NAME}")
endif()

if(NOT ZLIB_FOUND)
  message(FATAL_ERROR "Could not resolve zlib (expected it via vcpkg's ZLIB::ZLIB target).")
endif()