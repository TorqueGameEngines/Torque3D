set(LOCAL_ARCHIVE "$ENV{VCPKG_LIB_SOURCE_ROOT}/xiph-theora-v1.2.0.tar.gz")

vcpkg_extract_source_archive(
    SOURCE_PATH
    ARCHIVE "${LOCAL_ARCHIVE}"
)

file(COPY "${CMAKE_CURRENT_LIST_DIR}/CMakeLists.txt" DESTINATION "${SOURCE_PATH}")
file(COPY "${CMAKE_CURRENT_LIST_DIR}/libtheora.def" DESTINATION "${SOURCE_PATH}")
file(COPY "${CMAKE_CURRENT_LIST_DIR}/unofficial-theora-config.cmake.in" DESTINATION "${SOURCE_PATH}")

if(VCPKG_TARGET_ARCHITECTURE STREQUAL "x86")
    set(THEORA_X86_OPT ON)
else()
    set(THEORA_X86_OPT OFF)
endif()

vcpkg_cmake_configure(
    SOURCE_PATH "${SOURCE_PATH}"
    OPTIONS
        "-DVERSION:STRING=${VERSION}"
        -DUSE_X86=${THEORA_X86_OPT}
)

vcpkg_cmake_install()
vcpkg_cmake_config_fixup(CONFIG_PATH "lib/unofficial-theora" PACKAGE_NAME "unofficial-theora")
vcpkg_fixup_pkgconfig()
vcpkg_copy_pdbs()

file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/debug/include")

vcpkg_install_copyright(FILE_LIST "${SOURCE_PATH}/COPYING" "${SOURCE_PATH}/LICENSE")
