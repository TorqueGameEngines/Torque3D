
# We use the release tarball from GitHub instead of the sources in the repo because:
#  - igraph will not compile from the git sources unless there is an actual git repository to back it. This is because it detects the version from git tags. The release tarball has the version hard-coded.
#  - The release tarball contains pre-generated parser sources, which eliminates the dependency on bison/flex.

vcpkg_download_distfile(ARCHIVE
    URLS "https://github.com/igraph/igraph/releases/download/0.9.3/igraph-0.9.3.tar.gz"
    FILENAME "igraph-0.9.3.tar.gz"
    SHA512 69c7a217a27a34763750fe1bb3a981d9ce5aceb9027fe98ebdd2b2cbf4558734f55128ff8d9e46d066020d5bc942f6df761861bf7b103025015d3f0e336a7e7c
)

vcpkg_extract_source_archive_ex(
    OUT_SOURCE_PATH SOURCE_PATH
    ARCHIVE ${ARCHIVE}
)

vcpkg_check_features(OUT_FEATURE_OPTIONS FEATURE_OPTIONS
  FEATURES
    graphml   IGRAPH_GRAPHML_SUPPORT
    openmp    IGRAPH_OPENMP_SUPPORT
)

# Allow cross-compilation. See https://igraph.org/c/doc/igraph-Installation.html#idm207877354096
set(ARITH_H "")
if (VCPKG_TARGET_IS_OSX)
    set(ARITH_H ${CURRENT_PORT_DIR}/arith_osx.h)
elseif (VCPKG_TARGET_IS_WINDOWS OR VCPKG_TARGET_IS_UWP)
    if (VCPKG_TARGET_ARCHITECTURE STREQUAL "x86" OR VCPKG_TARGET_ARCHITECTURE STREQUAL "arm")
        set(ARITH_H ${CURRENT_PORT_DIR}/arith_win32.h)
    elseif (VCPKG_TARGET_ARCHITECTURE STREQUAL "x64" OR VCPKG_TARGET_ARCHITECTURE STREQUAL "arm64")
        set(ARITH_H ${CURRENT_PORT_DIR}/arith_win64.h)
    endif()
endif()

vcpkg_configure_cmake(
    SOURCE_PATH ${SOURCE_PATH}
    PREFER_NINJA
    OPTIONS
        -DIGRAPH_ENABLE_LTO=AUTO
        # ARPACK not yet available in vcpkg.
        -DIGRAPH_USE_INTERNAL_ARPACK=ON
        # OpenBLAS provides BLAS/LAPACK but some tests fail with OpenBLAS on Windows.
        # See https://github.com/igraph/igraph/issues/1491
        -DIGRAPH_USE_INTERNAL_BLAS=ON
        -DIGRAPH_USE_INTERNAL_LAPACK=ON
        -DIGRAPH_USE_INTERNAL_CXSPARSE=OFF
        # GLPK is not yet available in vcpkg.
        -DIGRAPH_USE_INTERNAL_GLPK=ON
        # Currently, external GMP provides no performance of functionality benefits.
        -DIGRAPH_USE_INTERNAL_GMP=ON
        -DF2C_EXTERNAL_ARITH_HEADER=${ARITH_H}
        ${FEATURE_OPTIONS}
)

vcpkg_install_cmake()

vcpkg_copy_pdbs()

file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/debug/include")

vcpkg_fixup_cmake_targets(CONFIG_PATH lib/cmake/igraph)

file(INSTALL "${SOURCE_PATH}/COPYING" DESTINATION "${CURRENT_PACKAGES_DIR}/share/${PORT}" RENAME copyright)
