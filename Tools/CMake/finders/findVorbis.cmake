if(TARGET vorbis)
  set(VORBIS_FOUND TRUE)
  set(VORBIS_INCLUDE_DIRS $<TARGET_PROPERTY:vorbis,INTERFACE_INCLUDE_DIRECTORIES>)
  set(VORBIS_LIBRARIES vorbis)

  # Provide an alias for consistency with modern CMake
  if(NOT TARGET VORBIS::VORBIS)
    add_library(VORBIS::VORBIS ALIAS vorbis)
  endif()
else()
  set(VORBIS_FOUND FALSE)
  message(FATAL_ERROR "Vorbis was not added with add_subdirectory before calling find_package(Vorbis).")
endif()