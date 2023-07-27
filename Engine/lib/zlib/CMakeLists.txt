file(GLOB ZLIB_SOURCES "*.c")
add_library(zlib ${ZLIB_SOURCES})
target_include_directories(zlib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
