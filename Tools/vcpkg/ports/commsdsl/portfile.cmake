vcpkg_fail_port_install(ON_TARGET "uwp")
vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO commschamp/commsdsl
    REF v3.6.2
    SHA512 532da398b23773703bb9ade2a5fb58584d99f631b0f28c834caa4377fcc4388a748405f998b77076a732316848bb6bde9be147fd0048485be8cc6fc6cc380352
    HEAD_REF master
)

vcpkg_configure_cmake(
    SOURCE_PATH ${SOURCE_PATH}
    PREFER_NINJA
    OPTIONS
        -DCOMMSDSL_NO_COMMS_CHAMPION=ON
        -DCOMMSDSL_NO_TESTS=ON
        -DCOMMSDSL_NO_WARN_AS_ERR=ON # remove on next version or on next version of boost
)
vcpkg_install_cmake()

vcpkg_copy_tools(
    TOOL_NAMES commsdsl2comms
    SEARCH_DIR ${CURRENT_PACKAGES_DIR}/bin
    AUTO_CLEAN
)

vcpkg_fixup_cmake_targets(CONFIG_PATH lib/LibCommsdsl/cmake TARGET_PATH share/LibCommsdsl)
# after fixing the following dirs are empty
file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/debug/include")
file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/debug/lib/LibCommsdsl")
file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/lib/LibCommsdsl")

if(VCPKG_LIBRARY_LINKAGE STREQUAL "static")
    file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/bin" "${CURRENT_PACKAGES_DIR}/debug/bin")
endif()
# Handle copyright
file(INSTALL ${SOURCE_PATH}/LICENSE.txt DESTINATION ${CURRENT_PACKAGES_DIR}/share/${PORT} RENAME copyright)
