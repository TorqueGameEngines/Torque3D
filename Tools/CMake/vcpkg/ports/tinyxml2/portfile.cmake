set(LOCAL_ARCHIVE "${TORQUE_LIB_ROOT_DIRECTORY}/leethomason-tinyxml2-11.0.0.tar.gz")

vcpkg_extract_source_archive(
    SOURCE_PATH
    ARCHIVE "${LOCAL_ARCHIVE}"
    PATCHES
        0001-fix-do-not-force-export-the-symbols-when-building-st.patch
        0002-fix-check-for-TINYXML2_EXPORT-on-non-windows.patch
)

vcpkg_cmake_configure(
    SOURCE_PATH "${SOURCE_PATH}"
    OPTIONS
        -Dtinyxml2_BUILD_TESTING=OFF
)

vcpkg_cmake_install()

vcpkg_cmake_config_fixup(CONFIG_PATH lib/cmake/tinyxml2)
vcpkg_fixup_pkgconfig()

vcpkg_copy_pdbs()

file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/debug/include")

file(INSTALL "${SOURCE_PATH}/LICENSE.txt" DESTINATION "${CURRENT_PACKAGES_DIR}/share/${PORT}" RENAME copyright)
