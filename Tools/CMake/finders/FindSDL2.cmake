if(TARGET SDL2)
  set(SDL2_FOUND TRUE)
  set(SDL2_INCLUDE_DIRS $<TARGET_PROPERTY:SDL2,INTERFACE_INCLUDE_DIRECTORIES>)
  set(SDL2_LIBRARIES SDL2)

  # Provide a modern CMake alias
  if(NOT TARGET SDL2::SDL2)
    add_library(SDL2::SDL2 ALIAS SDL2)
  endif()
else()
  set(SDL2_FOUND FALSE)
  message(FATAL_ERROR "SDL2 was not added with add_subdirectory before calling find_package(SDL2).")
endif()