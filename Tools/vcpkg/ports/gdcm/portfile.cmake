vcpkg_fail_port_install(ON_TARGET "uwp")

vcpkg_check_linkage(ONLY_STATIC_LIBRARY)

vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO malaterre/GDCM
    REF c0824c0ae66e9f9e3c8bddba8b65238c1c28481d # v3.0.7
    SHA512 1889f18f7164e1395e2cf5fe29b6ccd615f9a31433d1a7bda19cac472b20bc52018ef45bd9d9ca72ecb248c9fd5d895b94bfd111157693f70e0b90cf7b582edd
    HEAD_REF master
    PATCHES
        use-openjpeg-config.patch
        fix-share-path.patch
        Fix-Cmake_DIR.patch
)

file(REMOVE ${SOURCE_PATH}/CMake/FindOpenJPEG.cmake)

if(VCPKG_LIBRARY_LINKAGE STREQUAL "dynamic")
  set(VCPKG_BUILD_SHARED_LIBS ON)
else()
  set(VCPKG_BUILD_SHARED_LIBS OFF)
endif()

vcpkg_configure_cmake(
    SOURCE_PATH ${SOURCE_PATH}
    PREFER_NINJA
    OPTIONS
        -DGDCM_BUILD_DOCBOOK_MANPAGES=OFF
        -DGDCM_BUILD_SHARED_LIBS=${VCPKG_BUILD_SHARED_LIBS}
        -DGDCM_INSTALL_INCLUDE_DIR=include
        -DGDCM_USE_SYSTEM_EXPAT=ON
        -DGDCM_USE_SYSTEM_ZLIB=ON
        -DGDCM_USE_SYSTEM_OPENJPEG=ON
        -DGDCM_BUILD_TESTING=OFF
)

vcpkg_install_cmake()
vcpkg_fixup_cmake_targets(CONFIG_PATH lib/gdcm)
vcpkg_copy_pdbs()

file(REMOVE_RECURSE
    ${CURRENT_PACKAGES_DIR}/debug/include
    ${CURRENT_PACKAGES_DIR}/debug/share
)

vcpkg_replace_string(${CURRENT_PACKAGES_DIR}/share/gdcm/GDCMTargets.cmake
    "set(CMAKE_IMPORT_FILE_VERSION 1)"
    "set(CMAKE_IMPORT_FILE_VERSION 1)
    find_package(OpenJPEG QUIET)"
)

if(VCPKG_LIBRARY_LINKAGE STREQUAL "static")
    file(REMOVE_RECURSE ${CURRENT_PACKAGES_DIR}/bin ${CURRENT_PACKAGES_DIR}/debug/bin)
endif()

file(INSTALL ${SOURCE_PATH}/Copyright.txt DESTINATION ${CURRENT_PACKAGES_DIR}/share/${PORT} RENAME copyright)