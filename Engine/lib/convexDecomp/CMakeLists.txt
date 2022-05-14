file(GLOB CONVEX_DECOMP_SOURCES "*.cpp")
add_library(convexDecomp ${CONVEX_DECOMP_SOURCES})
target_include_directories(convexDecomp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
