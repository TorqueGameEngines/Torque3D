set(VCPKG_TARGET_ARCHITECTURE arm64)

if(${PORT} MATCHES "sdl2|openal-soft|libsndfile")
	set(VCPKG_CRT_LINKAGE dynamic)
	set(VCPKG_LIBRARY_LINKAGE dynamic)
else()
    set(VCPKG_CRT_LINKAGE dynamic)
    set(VCPKG_LIBRARY_LINKAGE static)
endif()

set(VCPKG_CMAKE_SYSTEM_NAME Darwin)
set(VCPKG_OSX_ARCHITECTURES "arm64;x86_64")

set(VCPKG_CMAKE_SYSTEM_VERSION 11.0)
set(VCPKG_OSX_DEPLOYMENT_TARGET 11.0)
set(VCPKG_C_FLAGS -mmacosx-version-min=11.0)
set(VCPKG_CXX_FLAGS -mmacosx-version-min=11.0)
