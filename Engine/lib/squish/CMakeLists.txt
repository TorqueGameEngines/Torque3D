file(GLOB SQUISH_SOURCES "*.cpp")

add_library(squish STATIC ${SQUISH_SOURCES})
target_include_directories(squish PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
