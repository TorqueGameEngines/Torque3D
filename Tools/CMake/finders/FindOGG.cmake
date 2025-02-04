if(TARGET ogg)
  set(OGG_FOUND TRUE)
  set(OGG_INCLUDE_DIRS $<TARGET_PROPERTY:ogg,INTERFACE_INCLUDE_DIRECTORIES>)
  set(OGG_LIBRARIES ogg)

  # Provide an alias for consistency with modern CMake
  if(NOT TARGET OGG::OGG)
    add_library(OGG::OGG ALIAS ogg)
  endif()
else()
  set(OGG_FOUND FALSE)
  message(FATAL_ERROR "Ogg was not added with add_subdirectory before calling find_package(Ogg).")
endif()