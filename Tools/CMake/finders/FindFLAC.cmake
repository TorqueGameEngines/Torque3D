if(TARGET FLAC)
  set(FLAC_FOUND TRUE)
  set(FLAC_INCLUDE_DIRS $<TARGET_PROPERTY:FLAC,INTERFACE_INCLUDE_DIRECTORIES>)
  set(FLAC_LIBRARIES FLAC)

  # Provide an alias for consistency with modern CMake
  if(NOT TARGET FLAC::FLAC)
    add_library(FLAC::FLAC ALIAS FLAC)
  endif()
else()
  set(FLAC_FOUND FALSE)
  message(FATAL_ERROR "Flac was not added with add_subdirectory before calling find_package(FLAC).")
endif()