set(LOCAL_ARCHIVE "$ENV{VCPKG_LIB_SOURCE_ROOT}/xiph-vorbis-v1.3.7.tar.gz")

vcpkg_extract_source_archive(
    SOURCE_PATH
    ARCHIVE "${LOCAL_ARCHIVE}"
    PATCHES
        0001-Dont-export-vorbisenc-functions.patch
        0002-Fixup-pkgconfig-libs.patch
        0003-def-mingw-compat.patch
        0004-ogg-find-dependency.patch
)

vcpkg_cmake_configure(
    SOURCE_PATH "${SOURCE_PATH}"
    OPTIONS
        -DCMAKE_POLICY_VERSION_MINIMUM=3.5 # https://github.com/xiph/vorbis/issues/113
    MAYBE_UNUSED_VARIABLES
        CMAKE_POLICY_VERSION_MINIMUM
)

vcpkg_cmake_install()
vcpkg_cmake_config_fixup(PACKAGE_NAME Vorbis CONFIG_PATH "lib/cmake/Vorbis")
vcpkg_fixup_pkgconfig()
vcpkg_copy_pdbs()

file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/debug/include")

file(INSTALL "${CMAKE_CURRENT_LIST_DIR}/usage" DESTINATION "${CURRENT_PACKAGES_DIR}/share/${PORT}")
file(INSTALL "${SOURCE_PATH}/COPYING" DESTINATION "${CURRENT_PACKAGES_DIR}/share/${PORT}" RENAME copyright)
