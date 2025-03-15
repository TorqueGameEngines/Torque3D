if(TARGET opus)
  set(OPUS_FOUND TRUE)
  set(OPUS_INCLUDE_DIRS $<TARGET_PROPERTY:opus,INTERFACE_INCLUDE_DIRECTORIES>)
  set(OPUS_LIBRARIES opus)

  # Provide an alias for consistency with modern CMake
  if(NOT TARGET OPUS::OPUS)
    add_library(OPUS::OPUS ALIAS opus)
  endif()
else()
  set(OPUS_FOUND FALSE)
  message(FATAL_ERROR "Opus was not added with add_subdirectory before calling find_package(Opus).")
endif()