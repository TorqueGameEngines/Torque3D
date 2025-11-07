set(LOCAL_ARCHIVE "$ENV{VCPKG_LIB_SOURCE_ROOT}/xiph-flac-1.5.0.tar.gz")

vcpkg_extract_source_archive(
    SOURCE_PATH
    ARCHIVE "${LOCAL_ARCHIVE}"
    PATCHES
        android-cmake.diff
        fix-compile-options.patch
        fix-find-threads.patch
)

if("asm" IN_LIST FEATURES)
    vcpkg_find_acquire_program(NASM)
    get_filename_component(NASM_PATH "${NASM}" DIRECTORY)
    vcpkg_add_to_path("${NASM_PATH}")
endif()

vcpkg_check_features(OUT_FEATURE_OPTIONS FEATURE_OPTIONS
    FEATURES
        asm WITH_ASM
        stack-protector WITH_STACK_PROTECTOR
        multithreading ENABLE_MULTITHREADING
)

vcpkg_cmake_configure(
    SOURCE_PATH "${SOURCE_PATH}"
    OPTIONS
        ${FEATURE_OPTIONS}
        -DBUILD_PROGRAMS=OFF
        -DBUILD_EXAMPLES=OFF
        -DBUILD_DOCS=OFF
        -DBUILD_TESTING=OFF
        -DINSTALL_MANPAGES=OFF
)

vcpkg_cmake_install()

vcpkg_cmake_config_fixup(PACKAGE_NAME FLAC CONFIG_PATH lib/cmake/FLAC)

vcpkg_copy_pdbs()

file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/debug/include")
file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/debug/share")
file(REMOVE "${CURRENT_PACKAGES_DIR}/share/LICENSE")

if(VCPKG_LIBRARY_LINKAGE STREQUAL "dynamic")
    vcpkg_replace_string("${CURRENT_PACKAGES_DIR}/include/FLAC/export.h"
        "#if defined(FLAC__NO_DLL)"
        "#if 0"
    )
    vcpkg_replace_string("${CURRENT_PACKAGES_DIR}/include/FLAC++/export.h"
        "#if defined(FLAC__NO_DLL)"
        "#if 0"
    )
else()
    vcpkg_replace_string("${CURRENT_PACKAGES_DIR}/include/FLAC/export.h"
        "#if defined(FLAC__NO_DLL)"
        "#if 1"
    )
    vcpkg_replace_string("${CURRENT_PACKAGES_DIR}/include/FLAC++/export.h"
        "#if defined(FLAC__NO_DLL)"
        "#if 1"
    )
endif()

if(VCPKG_TARGET_IS_WINDOWS)
    vcpkg_replace_string("${CURRENT_PACKAGES_DIR}/lib/pkgconfig/flac.pc" " -lm" "")

    if(EXISTS "${CURRENT_PACKAGES_DIR}/debug/lib/pkgconfig/flac.pc")
        vcpkg_replace_string("${CURRENT_PACKAGES_DIR}/debug/lib/pkgconfig/flac.pc" " -lm" "")
    endif()
endif()

vcpkg_fixup_pkgconfig()

# This license (BSD) is relevant only for library - if someone would want to install
# FLAC cmd line tools as well additional license (GPL) should be included
vcpkg_install_copyright(FILE_LIST "${SOURCE_PATH}/COPYING.Xiph")

file(INSTALL "${CMAKE_CURRENT_LIST_DIR}/usage" DESTINATION "${CURRENT_PACKAGES_DIR}/share/${PORT}")
