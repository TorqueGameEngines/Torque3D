file(GLOB LIBOGG_SOURCE_FILES "src/*.c")
add_library(libogg ${LIBOGG_SOURCE_FILES})
target_include_directories(libogg PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
