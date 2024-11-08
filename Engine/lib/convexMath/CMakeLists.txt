file(GLOB CONVEX_DECOMP_SOURCES "*.cpp")
add_library(convexMath STATIC ${CONVEX_DECOMP_SOURCES})
target_include_directories(convexMath PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})