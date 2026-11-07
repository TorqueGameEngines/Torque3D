file(GLOB GLAD_SOURCES "src/*.c")

# Linux no longer builds the GLX loader: GLX is an X11 extension, and Torque's
# Linux windowing is Wayland-only now. GL entry points (including extensions)
# are resolved generically from libGL.so regardless of whether the underlying
# context was created via GLX or EGL, so no platform GL-context-extension
# loader is required there.
if (WIN32)
  file(GLOB GLAD_SOURCES_WGL "src/wgl/*.c")
  set(GLAD_SOURCES ${GLAD_SOURCES} ${GLAD_SOURCES_WGL})
endif()

add_library(glad STATIC ${GLAD_SOURCES})
target_include_directories(glad PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
