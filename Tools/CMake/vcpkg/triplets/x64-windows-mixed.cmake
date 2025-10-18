set(VCPKG_TARGET_ARCHITECTURE x64)

if(${PORT} MATCHES "sdl2|openal-soft")
	set(VCPKG_CRT_LINKAGE dynamic)
	set(VCPKG_LIBRARY_LINKAGE dynamic)
else()
	set(VCPKG_CRT_LINKAGE dynamic)
	set(VCPKG_LIBRARY_LINKAGE static)
endif()

if(GIT_CI_BUILD)
set(VCPKG_BUILD_TYPE release)
endif()