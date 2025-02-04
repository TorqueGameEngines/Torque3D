if(TARGET pcre)
  set(PCRE_FOUND TRUE)
  set(PCRE_INCLUDE_DIRS $<TARGET_PROPERTY:pcre,INTERFACE_INCLUDE_DIRECTORIES>)
  set(PCRE_LIBRARIES pcre)

  # Provide an alias for consistency with modern CMake
  if(NOT TARGET PCRE::PCRE)
    add_library(PCRE::PCRE ALIAS pcre)
  endif()
else()
  set(PCRE_FOUND FALSE)
  message(FATAL_ERROR "PCRE was not added with add_subdirectory before calling find_package(PCRE).")
endif()