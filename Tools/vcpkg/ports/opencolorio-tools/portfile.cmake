# Note: Should be maintained simultaneously with opencolorio!
SET(VCPKG_POLICY_EMPTY_PACKAGE enabled)

if(VCPKG_LIBRARY_LINKAGE STREQUAL static)
    set(_BUILD_SHARED OFF)
    set(_BUILD_STATIC ON)
else()
    set(_BUILD_SHARED ON)
    set(_BUILD_STATIC OFF)
endif()

vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO imageworks/OpenColorIO
    REF v1.1.1
    SHA512 bed722f9ddce1887d28aacef2882debccd7c3f3c0c708d2723fea58a097de9f02721af9e85453e089ffda5406aef593ab6536c6886307823c132aa787e492e33
    HEAD_REF master
    PATCHES
        0001-lcms-dependency-search.patch
        0002-msvc-cpluscplus.patch
        0003-osx-self-assign-field.patch
        0004-yaml-dependency-search.patch
        0005-tinyxml-dependency-search.patch
        0006-oiio-dependency-search.patch
)

vcpkg_find_acquire_program(PYTHON3)
get_filename_component(PYTHON3_PATH "${PYTHON3}" DIRECTORY)
vcpkg_add_to_path(PREPEND ${PYTHON3_PATH})

# TODO(theblackunknown) build additional targets based on feature

vcpkg_configure_cmake(
    SOURCE_PATH ${SOURCE_PATH}
    PREFER_NINJA
    OPTIONS
        -DOCIO_BUILD_APPS=ON
        -DOCIO_BUILD_SHARED:BOOL=${_BUILD_SHARED}
        -DOCIO_BUILD_STATIC:BOOL=${_BUILD_STATIC}
        -DOCIO_BUILD_TRUELIGHT:BOOL=OFF
        -DOCIO_BUILD_NUKE:BOOL=OFF
        -DOCIO_BUILD_DOCS:BOOL=OFF
        -DOCIO_BUILD_TESTS:BOOL=OFF
        -DOCIO_BUILD_PYGLUE:BOOL=OFF
        -DOCIO_BUILD_JNIGLUE:BOOL=OFF
        -DOCIO_STATIC_JNIGLUE:BOOL=OFF
        -DUSE_EXTERNAL_TINYXML:BOOL=ON
        -DUSE_EXTERNAL_YAML:BOOL=ON
)

vcpkg_install_cmake()

vcpkg_copy_pdbs()

vcpkg_copy_tools(TOOL_NAMES ociobakelut ociocheck)

# Clean redundant files
file(REMOVE_RECURSE
    ${CURRENT_PACKAGES_DIR}/debug
    ${CURRENT_PACKAGES_DIR}/include
    ${CURRENT_PACKAGES_DIR}/bin
    ${CURRENT_PACKAGES_DIR}/lib
    ${CURRENT_PACKAGES_DIR}/cmake
    ${CURRENT_PACKAGES_DIR}/share)

file(REMOVE ${CURRENT_PACKAGES_DIR}/OpenColorIOConfig.cmake)

file(INSTALL ${SOURCE_PATH}/LICENSE DESTINATION ${CURRENT_PACKAGES_DIR}/share/${PORT} RENAME copyright)
