set(PORT_VERSION 6.1.0)

vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO CoolProp/CoolProp
    REF f5ebb4e655add4c23bb327ab5209f3dbf919bc6d # v6.4.1
    SHA512 916d00777fe56035171ed0a6cbe09b8d4487317772802e4fe9b43f5965f3212dcb3754e18fe1db9c748a4d17facbbe6cb2244451cf5cf66334465760fc1701b7
    HEAD_REF master
    PATCHES
        fmt-fix.patch
        fix-builderror.patch
        fix-dependency.patch
)

vcpkg_find_acquire_program(PYTHON2)
get_filename_component(PYTHON2_DIR ${PYTHON2} DIRECTORY)
vcpkg_add_to_path(${PYTHON2_DIR})

file(REMOVE_RECURSE ${SOURCE_PATH}/externals)

# Patch up the file locations
file(COPY
    ${CURRENT_INSTALLED_DIR}/include/catch.hpp
    DESTINATION ${SOURCE_PATH}/externals/Catch/single_include
)

file(COPY
    ${CURRENT_INSTALLED_DIR}/include/eigen3/Eigen
    DESTINATION ${SOURCE_PATH}/externals/Eigen
)
file(COPY
    ${CURRENT_INSTALLED_DIR}/include/eigen3/unsupported/Eigen
    DESTINATION ${SOURCE_PATH}/externals/Eigen/unsupported
)

file(COPY
    ${CURRENT_INSTALLED_DIR}/include/rapidjson
    DESTINATION ${SOURCE_PATH}/externals/rapidjson/include
)

file(COPY
    ${CURRENT_INSTALLED_DIR}/include/IF97.h
    DESTINATION ${SOURCE_PATH}/externals/IF97
)

file(COPY
    ${CURRENT_INSTALLED_DIR}/include/msgpack.h
    ${CURRENT_INSTALLED_DIR}/include/msgpack.hpp
    ${CURRENT_INSTALLED_DIR}/include/msgpack
    DESTINATION ${SOURCE_PATH}/externals/msgpack-c/include
)

file(COPY
    ${CURRENT_INSTALLED_DIR}/include/fmt
    DESTINATION ${SOURCE_PATH}/externals/cppformat
)

file(COPY
    ${CURRENT_INSTALLED_DIR}/include/REFPROP_lib.h
    DESTINATION ${SOURCE_PATH}/externals/REFPROP-headers/
)

# Use a nasty hack to include the correct header
file(APPEND
    ${SOURCE_PATH}/externals/msgpack-c/include/fmt/format.h
    "#include \"fmt/printf.h\""
)

string(COMPARE EQUAL "${VCPKG_LIBRARY_LINKAGE}" "dynamic" COOLPROP_SHARED_LIBRARY)
string(COMPARE EQUAL "${VCPKG_LIBRARY_LINKAGE}" "static" COOLPROP_STATIC_LIBRARY)

string(COMPARE EQUAL "${VCPKG_CRT_LINKAGE}" "dynamic" COOLPROP_MSVC_DYNAMIC)
string(COMPARE EQUAL "${VCPKG_CRT_LINKAGE}" "static" COOLPROP_MSVC_STATIC)

vcpkg_configure_cmake(
    SOURCE_PATH ${SOURCE_PATH}
    PREFER_NINJA
    OPTIONS
        -DCOOLPROP_SHARED_LIBRARY=${COOLPROP_SHARED_LIBRARY}
        -DCOOLPROP_STATIC_LIBRARY=${COOLPROP_STATIC_LIBRARY}
        -DCOOLPROP_MSVC_DYNAMIC=${COOLPROP_MSVC_DYNAMIC}
        -DCOOLPROP_MSVC_STATIC=${COOLPROP_MSVC_STATIC}
    OPTIONS_RELEASE
        -DCOOLPROP_INSTALL_PREFIX=${CURRENT_PACKAGES_DIR}
    OPTIONS_DEBUG
        -DCOOLPROP_INSTALL_PREFIX=${CURRENT_PACKAGES_DIR}/debug
)

vcpkg_install_cmake()
vcpkg_copy_pdbs()

if(VCPKG_LIBRARY_LINKAGE STREQUAL "dynamic")
    set(TARGET_FOLDER "shared_library")
else()
    set(TARGET_FOLDER "static_library")
endif()

file(GLOB_RECURSE COOLPROP_HEADERS "${CURRENT_PACKAGES_DIR}/${TARGET_FOLDER}/*.h")
file(INSTALL ${COOLPROP_HEADERS} DESTINATION ${CURRENT_PACKAGES_DIR}/include)

file(GLOB_RECURSE COOLPROP_LIBS "${CURRENT_PACKAGES_DIR}/${TARGET_FOLDER}/*.lib")
file(GLOB_RECURSE COOLPROP_DLLS "${CURRENT_PACKAGES_DIR}/${TARGET_FOLDER}/*.dll")

file(INSTALL ${COOLPROP_LIBS} DESTINATION ${CURRENT_PACKAGES_DIR}/lib)
if(COOLPROP_DLLS)
    file(INSTALL ${COOLPROP_DLLS} DESTINATION ${CURRENT_PACKAGES_DIR}/bin)
endif()

file(GLOB_RECURSE COOLPROP_DEBUG_LIBS "${CURRENT_PACKAGES_DIR}/debug/${TARGET_FOLDER}/*.lib")
file(GLOB_RECURSE COOLPROP_DEBUG_DLLS "${CURRENT_PACKAGES_DIR}/debug/${TARGET_FOLDER}/*.dll")

file(INSTALL ${COOLPROP_DEBUG_LIBS} DESTINATION ${CURRENT_PACKAGES_DIR}/debug/lib)
if(COOLPROP_DEBUG_DLLS)
    file(INSTALL ${COOLPROP_DEBUG_DLLS} DESTINATION ${CURRENT_PACKAGES_DIR}/debug/bin)
endif()

file(REMOVE_RECURSE ${CURRENT_PACKAGES_DIR}/debug/${TARGET_FOLDER} ${CURRENT_PACKAGES_DIR}/${TARGET_FOLDER})

# Handle copyright
file(INSTALL ${SOURCE_PATH}/LICENSE DESTINATION ${CURRENT_PACKAGES_DIR}/share/${PORT} RENAME copyright)
