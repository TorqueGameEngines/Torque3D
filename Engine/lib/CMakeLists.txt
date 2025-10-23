# Ask CMake to perform builds in a temporary directory for all of these.
# We also use EXCLUDE_FROM_ALL to ensure we only build and install what we want
execute_process( 
    COMMAND ${VCPKG_ROOT}/vcpkg remove --outdated
    --triplet ${VCPKG_TARGET_TRIPLET}
    --overlay-triplets "${VCPKG_OVERLAY_TRIPLETS}"
    RESULT_VARIABLE result
)

execute_process( 
    COMMAND ${VCPKG_ROOT}/vcpkg install 
    zlib pcre libogg libvorbis libflac opus libtheora libsndfile[core,external-libs] tinyxml2 assimp sdl2 openal-soft
    --triplet ${VCPKG_TARGET_TRIPLET}
    --overlay-triplets "${VCPKG_OVERLAY_TRIPLETS}"
    --overlay-ports "${VCPKG_OVERLAY_PORTS}"
    --clean-after-build
    RESULT_VARIABLE result
)

if(NOT result EQUAL 0)
    message(FATAL_ERROR "Failed to install required libraries with vcpkg")
endif()

add_subdirectory(nativeFileDialogs ${TORQUE_LIB_TARG_DIRECTORY}/nfd EXCLUDE_FROM_ALL)
add_subdirectory(convexMath ${TORQUE_LIB_TARG_DIRECTORY}/convexMath EXCLUDE_FROM_ALL)
add_subdirectory(opcode ${TORQUE_LIB_TARG_DIRECTORY}/opcode EXCLUDE_FROM_ALL)
add_subdirectory(squish ${TORQUE_LIB_TARG_DIRECTORY}/squish EXCLUDE_FROM_ALL)
add_subdirectory(collada ${TORQUE_LIB_TARG_DIRECTORY}/collada EXCLUDE_FROM_ALL)
add_subdirectory(glad ${TORQUE_LIB_TARG_DIRECTORY}/glad EXCLUDE_FROM_ALL)

if(TORQUE_TESTING)
    add_subdirectory(gtest ${TORQUE_LIB_TARG_DIRECTORY}/gtest EXCLUDE_FROM_ALL)
endif()

