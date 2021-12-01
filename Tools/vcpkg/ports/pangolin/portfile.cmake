vcpkg_fail_port_install(ON_TARGET "OSX" "UWP")

vcpkg_check_linkage(ONLY_STATIC_LIBRARY)

vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO stevenlovegrove/Pangolin
    REF v0.5
    SHA512 7ebeec108f33f1aa8b1ad08e3ca128a837b22d33e3fc580021f981784043b023a1bf563bbfa8b51d46863db770b336d24fc84ee3d836b85e0da1848281b2a5b2
    HEAD_REF master
    PATCHES
        deprecated_constants.patch # Change from upstream pangolin to address build failures from latest ffmpeg library
        fix-includepath-error.patch # include path has one more ../
        fix-dependency-python.patch
        add-definition.patch
        fix-cmake-version.patch
)

file(REMOVE ${SOURCE_PATH}/CMakeModules/FindGLEW.cmake)
file(REMOVE ${SOURCE_PATH}/CMakeModules/FindFFMPEG.cmake)

string(COMPARE EQUAL "${VCPKG_CRT_LINKAGE}" "static" MSVC_USE_STATIC_CRT)

vcpkg_configure_cmake(
    SOURCE_PATH ${SOURCE_PATH}
    PREFER_NINJA
    OPTIONS
        -DBUILD_EXTERN_GLEW=OFF
        -DBUILD_EXTERN_LIBPNG=OFF
        -DBUILD_EXTERN_LIBJPEG=OFF
        -DCMAKE_DISABLE_FIND_PACKAGE_PythonLibs=ON
        -DCMAKE_DISABLE_FIND_PACKAGE_TooN=ON
        -DCMAKE_DISABLE_FIND_PACKAGE_DC1394=ON
        -DCMAKE_DISABLE_FIND_PACKAGE_LibRealSense=ON
        -DCMAKE_DISABLE_FIND_PACKAGE_OpenNI=ON
        -DCMAKE_DISABLE_FIND_PACKAGE_OpenNI2=ON
        -DCMAKE_DISABLE_FIND_PACKAGE_uvc=ON
        -DCMAKE_DISABLE_FIND_PACKAGE_DepthSense=ON
        -DCMAKE_DISABLE_FIND_PACKAGE_TeliCam=ON
        -DCMAKE_DISABLE_FIND_PACKAGE_Pleora=ON
        -DCMAKE_DISABLE_FIND_PACKAGE_TIFF=ON
        -DCMAKE_DISABLE_FIND_PACKAGE_OpenEXR=ON
        -DMSVC_USE_STATIC_CRT=${MSVC_USE_STATIC_CRT}
)

vcpkg_install_cmake()

vcpkg_fixup_cmake_targets(CONFIG_PATH lib/cmake/Pangolin)

vcpkg_copy_pdbs()

file(REMOVE_RECURSE ${CURRENT_PACKAGES_DIR}/debug/include)

if(VCPKG_TARGET_IS_WINDOWS AND VCPKG_LIBRARY_LINKAGE STREQUAL "dynamic")
    file(GLOB EXE ${CURRENT_PACKAGES_DIR}/lib/*.dll)
    file(COPY ${EXE} DESTINATION ${CURRENT_PACKAGES_DIR}/bin)
    file(REMOVE ${EXE})

    file(GLOB DEBUG_EXE ${CURRENT_PACKAGES_DIR}/debug/lib/*.dll)
    file(COPY ${DEBUG_EXE} DESTINATION ${CURRENT_PACKAGES_DIR}/debug/bin)
    file(REMOVE ${DEBUG_EXE})

    vcpkg_replace_string(${CURRENT_PACKAGES_DIR}/share/pangolin/PangolinTargets-debug.cmake
        "lib/pangolin.dll" "bin/pangolin.dll"
    )
    vcpkg_replace_string(${CURRENT_PACKAGES_DIR}/share/pangolin/PangolinTargets-release.cmake
        "lib/pangolin.dll" "bin/pangolin.dll"
    )
endif()

if(VCPKG_TARGET_IS_WINDOWS)
    # Copy missing header file
    file(COPY ${CURRENT_BUILDTREES_DIR}/${TARGET_TRIPLET}-dbg/src/include/pangolin/pangolin_export.h DESTINATION ${CURRENT_PACKAGES_DIR}/include/pangolin)
endif()

# Put the license file where vcpkg expects it
file(COPY ${CURRENT_PORT_DIR}/usage DESTINATION ${CURRENT_PACKAGES_DIR}/share/${PORT}/)
file(INSTALL ${SOURCE_PATH}/LICENCE DESTINATION ${CURRENT_PACKAGES_DIR}/share/${PORT} RENAME copyright)
