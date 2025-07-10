set(GLAD_SOURCES
    src/gl.c
    src/gles1.c
    src/gles2.c
    src/vulkan.c
)

if(WIN32)
    list(APPEND GLAD_SOURCES src/wgl.c)
elseif(UNIX AND NOT APPLE)
    list(APPEND GLAD_SOURCES src/glx.c src/egl.c)
endif()


add_library(glad STATIC ${GLAD_SOURCES})
target_include_directories(glad PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

if(WIN32)
    target_link_libraries(glad PUBLIC opengl32)
endif()