vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO hyperrealm/libconfig
    REF v1.7.2
    SHA512 9df57355c2d08381b4a0a6366f0db3633fbe8f73c2bb8c370c040b0bae96ce89ee4ac6c17a5a247fed855d890fa383e5b70cb5573fc9cfc62194d5b94e161cee
    HEAD_REF master
)

if (NOT VCPKG_USE_HEAD_VERSION)
  message("If you would like to use cmake with the port, use `--head` option with vcpkg install.")
  file(COPY ${CMAKE_CURRENT_LIST_DIR}/CMakeLists.txt DESTINATION ${SOURCE_PATH})
endif()

if (NOT VCPKG_USE_HEAD_VERSION)
  vcpkg_configure_cmake(
      SOURCE_PATH ${SOURCE_PATH}
      PREFER_NINJA
      OPTIONS_DEBUG -DDISABLE_INSTALL_HEADERS=ON
  )
else()
  vcpkg_configure_cmake(
      SOURCE_PATH ${SOURCE_PATH}
      PREFER_NINJA
      OPTIONS
          -DBUILD_EXAMPLES=OFF
          -DBUILD_TESTS=OFF
  )
endif()

vcpkg_install_cmake()

vcpkg_copy_pdbs()

if (VCPKG_USE_HEAD_VERSION)
  file(REMOVE_RECURSE ${CURRENT_PACKAGES_DIR}/debug/include)
  vcpkg_fixup_cmake_targets(CONFIG_PATH lib/cmake/libconfig)
endif()

foreach(FILE ${CURRENT_PACKAGES_DIR}/include/libconfig.h++ ${CURRENT_PACKAGES_DIR}/include/libconfig.h)
  file(READ ${FILE} _contents)
  string(REPLACE "defined(LIBCONFIGXX_EXPORTS)" "0" _contents "${_contents}")
  string(REPLACE "defined(LIBCONFIG_EXPORTS)" "0" _contents "${_contents}")

  if(VCPKG_LIBRARY_LINKAGE STREQUAL dynamic)
    string(REPLACE "defined(LIBCONFIGXX_STATIC)" "0" _contents "${_contents}")
    string(REPLACE "defined(LIBCONFIG_STATIC)" "0" _contents "${_contents}")
  else()
    string(REPLACE "defined(LIBCONFIGXX_STATIC)" "1" _contents "${_contents}")
    string(REPLACE "defined(LIBCONFIG_STATIC)" "1" _contents "${_contents}")
  endif()
  file(WRITE ${FILE} "${_contents}")
endforeach()

file(INSTALL ${SOURCE_PATH}/LICENSE DESTINATION ${CURRENT_PACKAGES_DIR}/share/${PORT} RENAME copyright)
