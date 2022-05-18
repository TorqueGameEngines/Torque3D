# Ask CMake to perform builds in a temporary directory for all of these.
# We also use EXCLUDE_FROM_ALL to ensure we only build and install what we want
set(BUILD_SHARED_LIBS off CACHE STRING "")
add_subdirectory(assimp ${CMAKE_BINARY_DIR}/temp/assimp EXCLUDE_FROM_ALL)

add_subdirectory(sdl ${CMAKE_BINARY_DIR}/temp/sdl2 EXCLUDE_FROM_ALL)

# FIXME: For now we force-on Neon
set(PNG_ARM_NEON on CACHE STRING "")
set(PNG_STATIC on CACHE STRING "")
add_subdirectory(lpng ${CMAKE_BINARY_DIR}/temp/lpng EXCLUDE_FROM_ALL)

add_subdirectory(ljpeg ${CMAKE_BINARY_DIR}/temp/ljpeg EXCLUDE_FROM_ALL)
add_subdirectory(tinyxml ${CMAKE_BINARY_DIR}/temp/tinyxml EXCLUDE_FROM_ALL)

add_subdirectory(opcode ${CMAKE_BINARY_DIR}/temp/opcode EXCLUDE_FROM_ALL)

add_subdirectory(zlib ${CMAKE_BINARY_DIR}/temp/zlib EXCLUDE_FROM_ALL)
add_subdirectory(pcre ${CMAKE_BINARY_DIR}/temp/pcre EXCLUDE_FROM_ALL)
add_subdirectory(convexDecomp ${CMAKE_BINARY_DIR}/temp/convexDecomp EXCLUDE_FROM_ALL)
add_subdirectory(squish ${CMAKE_BINARY_DIR}/temp/squish EXCLUDE_FROM_ALL)
add_subdirectory(collada ${CMAKE_BINARY_DIR}/temp/collada EXCLUDE_FROM_ALL)
add_subdirectory(glad ${CMAKE_BINARY_DIR}/temp/glad EXCLUDE_FROM_ALL)
