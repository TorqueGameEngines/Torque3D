# Ask CMake to perform builds in a temporary directory for all of these.
# We also use EXCLUDE_FROM_ALL to ensure we only build and install what we want
set(SDL_SHARED on CACHE BOOL "" FORCE)
add_subdirectory(sdl ${CMAKE_BINARY_DIR}/temp/sdl2 EXCLUDE_FROM_ALL)

# Png depends on zlib
add_subdirectory(zlib ${CMAKE_BINARY_DIR}/temp/zlib EXCLUDE_FROM_ALL)

# Assimp depends on zlib
set(BUILD_SHARED_LIBS off CACHE STRING "")
set(ASSIMP_BUILD_ZLIB off CACHE STRING "")
set(ASSIMP_HUNTER_ENABLED off CACHE STRING "")
add_subdirectory(assimp ${CMAKE_BINARY_DIR}/temp/assimp EXCLUDE_FROM_ALL)

if (TORQUE_CPU_ARM32 OR TORQUE_CPU_ARM64)
	set(PNG_ARM_NEON on CACHE BOOL "" FORCE)
endif (TORQUE_CPU_ARM32 OR TORQUE_CPU_ARM64)
set(PNG_STATIC on CACHE BOOL "" FORCE)
set(PNG_BUILD_ZLIB on CACHE BOOL "" FORCE)
set(PNG_TESTS off CACHE BOOL "" FORCE)
set(PNG_HARDWARE_OPTIMIZATIONS on CACHE BOOL "" FORCE)
get_filename_component(ZLIB_ROOT "zlib" REALPATH BASE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(ZLIB_ROOT "${ZLIB_ROOT}" CACHE STRING "ZLib root location" FORCE)
add_subdirectory(lpng ${CMAKE_BINARY_DIR}/temp/lpng EXCLUDE_FROM_ALL)

add_subdirectory(ljpeg ${CMAKE_BINARY_DIR}/temp/ljpeg EXCLUDE_FROM_ALL)
add_subdirectory(tinyxml ${CMAKE_BINARY_DIR}/temp/tinyxml EXCLUDE_FROM_ALL)
add_subdirectory(opcode ${CMAKE_BINARY_DIR}/temp/opcode EXCLUDE_FROM_ALL)
add_subdirectory(pcre ${CMAKE_BINARY_DIR}/temp/pcre EXCLUDE_FROM_ALL)
add_subdirectory(convexDecomp ${CMAKE_BINARY_DIR}/temp/convexDecomp EXCLUDE_FROM_ALL)
add_subdirectory(squish ${CMAKE_BINARY_DIR}/temp/squish EXCLUDE_FROM_ALL)
add_subdirectory(collada ${CMAKE_BINARY_DIR}/temp/collada EXCLUDE_FROM_ALL)
add_subdirectory(glad ${CMAKE_BINARY_DIR}/temp/glad EXCLUDE_FROM_ALL)
