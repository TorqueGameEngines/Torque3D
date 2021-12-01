vcpkg_fail_port_install(ON_ARCH "arm" "arm64" ON_TARGET "UWP" "OSX" "Linux")

vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO Open-Cascade-SAS/OCCT
    REF 628c0211d53c7fe1036a85e7a7b2b067c9c50f7a #V7.5.0
    SHA512 8d946e971417642264b318353fb34ebabf214bff5c705c60818da9e56e9cd658ed15b76b73d7207edffa398c23ad9982f4e9656b218b5edada325ca05c1283bb
    HEAD_REF master
    PATCHES
        fix-pdb-find.patch
        fix-install-prefix-path.patch
        install-include-dir.patch
)

if (VCPKG_LIBRARY_LINKAGE STREQUAL dynamic)
    set(BUILD_TYPE "Shared")
else()
    set(BUILD_TYPE "Static")
endif()

vcpkg_check_features(OUT_FEATURE_OPTIONS FEATURE_OPTIONS
    "freeimage"  USE_FREEIMAGE
    "tbb"        USE_TBB
)

# VTK option in opencascade not currently supported because only 6.1.0 is supported but vcpkg has >= 9.0


# We turn off BUILD_MODULE_Draw as it requires TCL 8.6 and TK 8.6 specifically which conflicts with vcpkg only having TCL 9.0 
# And pre-built ActiveTCL binaries are behind a marketing wall :(
# We use the Unix install layout for Windows as it matches vcpkg
vcpkg_configure_cmake(
    SOURCE_PATH ${SOURCE_PATH}
    PREFER_NINJA
    OPTIONS ${FEATURE_OPTIONS}
        -DBUILD_LIBRARY_TYPE=${BUILD_TYPE}
        -DBUILD_MODULE_Draw=OFF
        -DINSTALL_DIR_LAYOUT=Unix
        -DBUILD_SAMPLES_MFC=OFF
        -DBUILD_SAMPLES_QT=OFF
        -DBUILD_DOC_Overview=OFF
        -DINSTALL_TEST_CASES=OFF
        -DINSTALL_SAMPLES=OFF
)

vcpkg_install_cmake()

vcpkg_fixup_cmake_targets(CONFIG_PATH lib/cmake/opencascade)

#make occt includes relative to source_file
list(APPEND ADDITIONAL_HEADERS 
      "ExprIntrp.tab.h"
	  "FlexLexer.h"
	  "glext.h"
	  "igesread.h"
	  "NCollection_Haft.h"
	  "OSD_PerfMeter.h"
	  "Standard_values.h"
    )

file(GLOB files "${CURRENT_PACKAGES_DIR}/include/opencascade/[a-zA-Z0-9_]*\.[hgl]xx")
foreach(file_name ${files})
	file(READ ${file_name} filedata)
	string(REGEX REPLACE "# *include \<([a-zA-Z0-9_]*\.[hgl]xx)\>" "#include \"\\1\"" filedata "${filedata}")
	foreach(extra_header ${ADDITIONAL_HEADERS})
		string(REGEX REPLACE "# *include \<${extra_header}\>" "#include \"${extra_header}\"" filedata "${filedata}")
	endforeach()
	file(WRITE ${file_name} "${filedata}")
endforeach()

# Remove libd to lib, libd just has cmake files we dont want too
file(REMOVE_RECURSE ${CURRENT_PACKAGES_DIR}/debug/lib)
file(RENAME ${CURRENT_PACKAGES_DIR}/debug/libd ${CURRENT_PACKAGES_DIR}/debug/lib)

file(REMOVE_RECURSE ${CURRENT_PACKAGES_DIR}/debug/include)
file(REMOVE_RECURSE ${CURRENT_PACKAGES_DIR}/debug/share)


if (VCPKG_LIBRARY_LINKAGE STREQUAL dynamic)
    # debug creates libd and bind directories that need moving
    file(REMOVE_RECURSE ${CURRENT_PACKAGES_DIR}/debug/bin)
    file(RENAME ${CURRENT_PACKAGES_DIR}/debug/bind ${CURRENT_PACKAGES_DIR}/debug/bin)
    
    # fix paths in target files
    list(APPEND TARGET_FILES 
        ${CURRENT_PACKAGES_DIR}/share/opencascade/OpenCASCADEApplicationFrameworkTargets-debug.cmake
        ${CURRENT_PACKAGES_DIR}/share/opencascade/OpenCASCADECompileDefinitionsAndFlags-debug.cmake
        ${CURRENT_PACKAGES_DIR}/share/opencascade/OpenCASCADEDataExchangeTargets-debug.cmake
        ${CURRENT_PACKAGES_DIR}/share/opencascade/OpenCASCADEFoundationClassesTargets-debug.cmake
        ${CURRENT_PACKAGES_DIR}/share/opencascade/OpenCASCADEModelingAlgorithmsTargets-debug.cmake
        ${CURRENT_PACKAGES_DIR}/share/opencascade/OpenCASCADEModelingDataTargets-debug.cmake
        ${CURRENT_PACKAGES_DIR}/share/opencascade/OpenCASCADEVisualizationTargets-debug.cmake
    )
    
    foreach(TARGET_FILE ${TARGET_FILES})
        file(READ ${TARGET_FILE} filedata)
        string(REGEX REPLACE "libd" "lib" filedata "${filedata}")
        string(REGEX REPLACE "bind" "bin" filedata "${filedata}")
        file(WRITE ${TARGET_FILE} ${filedata})
    endforeach()

    # the bin directory ends up with bat files that are noise, let's clean that up
    file(GLOB BATS ${CURRENT_PACKAGES_DIR}/bin/*.bat)
    file(REMOVE_RECURSE ${BATS})
else()
    # remove scripts in bin dir
    file(REMOVE_RECURSE ${CURRENT_PACKAGES_DIR}/bin ${CURRENT_PACKAGES_DIR}/debug/bin)
endif()

file(INSTALL ${SOURCE_PATH}/OCCT_LGPL_EXCEPTION.txt DESTINATION ${CURRENT_PACKAGES_DIR}/share/${PORT} RENAME copyright)
