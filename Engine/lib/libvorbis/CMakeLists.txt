file(GLOB LIBVORBIS_SOURCE_FILES "lib/*.c")
add_library(libvorbis ${LIBVORBIS_SOURCE_FILES})
target_include_directories(libvorbis PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(libvorbis PUBLIC libogg)

if (UNIX)
	target_include_directories(libvorbis PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/lib")
endif (UNIX)