# Get nvcodec
vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO FFmpeg/nv-codec-headers
    REF 5ee2ae591f74f53bd6028344f8690f1558a1f17a # 10.0.26.0
    SHA512 f9d40a44f85016f0f76c7f630c3defb2e94858b43ae714adae546842c2801f51358b7c2b3326952e7aeb25f5b1611af4eee3024f495eaaaecbfd31851cc7edca
    HEAD_REF master
)

# ====================================================
# Install the pkgconfig info for the `nvcodec` package
# ====================================================

# Windows
if(VCPKG_TARGET_IS_WINDOWS)
    set(BUILD_SCRIPT ${CMAKE_CURRENT_LIST_DIR}\\build.sh)
    vcpkg_acquire_msys(MSYS_ROOT PACKAGES make pkg-config)
    set(BASH ${MSYS_ROOT}/usr/bin/bash.exe)

    message(STATUS "Building ${_csc_PROJECT_PATH} for Release")
    file(MAKE_DIRECTORY ${CURRENT_BUILDTREES_DIR}/${TARGET_TRIPLET})

    # Make and deploy the ffnvcodec.pc file using MSYS
    # (so that FFmpeg can find it in the MSYS rootfs)
    vcpkg_execute_required_process(
        COMMAND ${BASH} --noprofile --norc "${BUILD_SCRIPT}"
            "${SOURCE_PATH}"
            "${CURRENT_PACKAGES_DIR}"
        WORKING_DIRECTORY ${CURRENT_BUILDTREES_DIR}/${TARGET_TRIPLET}
        LOGNAME build-${TARGET_TRIPLET}
    )
    
    file(INSTALL ${SOURCE_PATH}/ffnvcodec.pc DESTINATION ${CURRENT_PACKAGES_DIR}/debug/lib/pkgconfig)

# Linux, etc.
else()
    FIND_PROGRAM(MAKE make)
    IF (NOT MAKE)
        MESSAGE(FATAL_ERROR "MAKE not found")
    ENDIF ()
    
    vcpkg_execute_required_process(
        COMMAND make PREFIX=$${CURRENT_PACKAGES_DIR}
        WORKING_DIRECTORY ${SOURCE_PATH}
        LOGNAME make-${TARGET_TRIPLET}
    )

    # FFmpeg uses pkgconfig to find ffnvcodec.pc, so install it where 
    # FFMpeg's call to pkgconfig expects to find it.
    file(INSTALL ${SOURCE_PATH}/ffnvcodec.pc DESTINATION ${CURRENT_PACKAGES_DIR}/lib/pkgconfig)
    file(INSTALL ${SOURCE_PATH}/ffnvcodec.pc DESTINATION ${CURRENT_PACKAGES_DIR}/debug/lib/pkgconfig)
endif()

# Install the files to their default vcpkg locations
file(INSTALL ${SOURCE_PATH}/include DESTINATION ${CURRENT_PACKAGES_DIR})
file(INSTALL ${CURRENT_PORT_DIR}/copyright DESTINATION ${CURRENT_PACKAGES_DIR}/share/${PORT})

vcpkg_fixup_pkgconfig()
