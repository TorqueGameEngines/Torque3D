vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO gabime/spdlog
    REF v1.8.5
    SHA512 77cc9df0c40bbdbfe1f3e5818dccf121918bfceac28f2608f39e5bf944968b7e8e24a6fc29f01bc58a9bae41b8892d49cfb59c196935ec9868884320b50f130c
    HEAD_REF v1.x
    PATCHES fix-mingw-build.patch
)

vcpkg_check_features(OUT_FEATURE_OPTIONS FEATURE_OPTIONS
    FEATURES
	benchmark SPDLOG_BUILD_BENCH
)

string(COMPARE EQUAL "${VCPKG_LIBRARY_LINKAGE}" "dynamic" SPDLOG_BUILD_SHARED)

vcpkg_cmake_configure(
    SOURCE_PATH ${SOURCE_PATH}
    OPTIONS
        ${FEATURE_OPTIONS}
        -DSPDLOG_FMT_EXTERNAL=ON
        -DSPDLOG_INSTALL=ON
        -DSPDLOG_BUILD_SHARED=${SPDLOG_BUILD_SHARED}
)

vcpkg_cmake_install()
vcpkg_cmake_config_fixup(CONFIG_PATH lib/cmake/spdlog)
vcpkg_fixup_pkgconfig()
vcpkg_copy_pdbs()

# use vcpkg-provided fmt library (see also option SPDLOG_FMT_EXTERNAL above)
file(REMOVE_RECURSE ${CURRENT_PACKAGES_DIR}/include/spdlog/fmt/bundled)

vcpkg_replace_string(${CURRENT_PACKAGES_DIR}/include/spdlog/fmt/fmt.h
    "#if !defined(SPDLOG_FMT_EXTERNAL)"
    "#if 0 // !defined(SPDLOG_FMT_EXTERNAL)"
)

vcpkg_replace_string(${CURRENT_PACKAGES_DIR}/include/spdlog/fmt/ostr.h
    "#if !defined(SPDLOG_FMT_EXTERNAL)"
    "#if 0 // !defined(SPDLOG_FMT_EXTERNAL)"
)

vcpkg_replace_string(${CURRENT_PACKAGES_DIR}/include/spdlog/fmt/chrono.h
    "#if !defined(SPDLOG_FMT_EXTERNAL)"
    "#if 0 // !defined(SPDLOG_FMT_EXTERNAL)"
)

file(REMOVE_RECURSE ${CURRENT_PACKAGES_DIR}/debug/include
                    ${CURRENT_PACKAGES_DIR}/debug/share)

# Handle copyright
file(INSTALL ${SOURCE_PATH}/LICENSE DESTINATION ${CURRENT_PACKAGES_DIR}/share/${PORT} RENAME copyright)
