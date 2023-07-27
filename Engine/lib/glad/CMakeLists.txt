file(GLOB GLAD_SOURCES "src/*.c")

# TODO EGL support if we ever use EGL instead of GLX
if (WIN32)
  file(GLOB GLAD_SOURCES_WGL "src/wgl/*.c")
  set(GLAD_SOURCES ${GLAD_SOURCES} ${GLAD_SOURCES_WGL})
elseif (UNIX AND NOT APPLE)
  file(GLOB GLAD_SOURCES_GLX "src/glx/*.c")
  set(GLAD_SOURCES ${GLAD_SOURCES} ${GLAD_SOURCES_GLX})
endif()

add_library(glad STATIC ${GLAD_SOURCES})
target_include_directories(glad PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
