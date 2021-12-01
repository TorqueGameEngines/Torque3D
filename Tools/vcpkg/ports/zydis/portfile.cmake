vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO zyantific/zydis
    REF bfee99f49274a0eec3ffea16ede3a5bda9cda88f
    SHA512 de47c4a22d22e753b3d06cb6210a9df2f944b0828e49d573cadb9b0c37d590a44db74542e07eced4b0188a97b825f4990943bab1b14edfd58d80368de4299759
    HEAD_REF master
)

vcpkg_from_github(
    OUT_SOURCE_PATH ZYCORE_SOURCE_PATH
    REPO zyantific/zycore-c
    REF 3435866ecaa837376807ce934d2088ae46aa3fa3
    SHA512 7e25254a0c17158789a3eca417cea8abe6a938cdc91cb395bd0ce1d791c8bd6b4ee0c994ca6c8372e17c03abfb3653c9053c5d56e0a4641d765c8474fae771d2
    HEAD_REF master
)

if(VCPKG_LIBRARY_LINKAGE STREQUAL static)
    set(ZYDIS_BUILD_SHARED_LIB OFF)
else()
    set(ZYDIS_BUILD_SHARED_LIB ON)
endif()

vcpkg_configure_cmake(
    SOURCE_PATH ${SOURCE_PATH}
    PREFER_NINJA
    OPTIONS
    "-DZYDIS_BUILD_SHARED_LIB=${ZYDIS_BUILD_SHARED_LIB}"
    "-DZYDIS_ZYCORE_PATH=${ZYCORE_SOURCE_PATH}"
)

vcpkg_install_cmake()

vcpkg_configure_cmake(
    SOURCE_PATH ${ZYCORE_SOURCE_PATH}
    PREFER_NINJA
)

vcpkg_install_cmake()

file(REMOVE_RECURSE ${CURRENT_PACKAGES_DIR}/debug/include)
file(GLOB EXES ${CURRENT_PACKAGES_DIR}/bin/*.exe ${CURRENT_PACKAGES_DIR}/debug/bin/*.exe)
if(EXES)
    file(REMOVE ${EXES})
endif()

if(VCPKG_LIBRARY_LINKAGE STREQUAL static)
    file(REMOVE_RECURSE ${CURRENT_PACKAGES_DIR}/bin ${CURRENT_PACKAGES_DIR}/debug/bin)
endif()

vcpkg_copy_pdbs()

file(INSTALL ${SOURCE_PATH}/LICENSE DESTINATION ${CURRENT_PACKAGES_DIR}/share/${PORT} RENAME copyright)
