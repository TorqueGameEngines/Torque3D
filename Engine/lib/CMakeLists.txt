# Ask CMake to perform builds in a temporary directory for all of these.
# We also use EXCLUDE_FROM_ALL to ensure we only build and install what we want
execute_process( 
    COMMAND ${VCPKG_ROOT}/vcpkg remove --outdated
    RESULT_VARIABLE result
)
if(WIN32)
execute_process( 
    COMMAND ${VCPKG_ROOT}/vcpkg install 
    zlib pcre libogg libvorbis libflac opus libtheora libsndfile[core,external-libs] tinyxml2 assimp sdl2 openal-soft
    --triplet ${VCPKG_TARGET_TRIPLET}
    --overlay-triplets "${VCPKG_OVERLAY_TRIPLETS}"
    RESULT_VARIABLE result
)
else()
execute_process( 
    COMMAND ${VCPKG_ROOT}/vcpkg install 
    zlib pcre libogg libvorbis libflac opus libtheora libsndfile[core,external-libs] tinyxml2 assimp sdl2 openal-soft
    RESULT_VARIABLE result
)
endif()
if(NOT result EQUAL 0)
    message(FATAL_ERROR "Failed to install required libraries with vcpkg")
endif()

if(TORQUE_SFX_OPENAL)
    advanced_option(TORQUE_OGGVORBIS "Enable OGG Vorbis" ON)
    advanced_option(ALSOFT_EAX "Enable legacy EAX extensions" ${WIN32})
    advanced_option(ALSOFT_UPDATE_BUILD_VERSION "Update git build version info" ON)
    mark_as_advanced(ALSOFT_BACKEND_COREAUDIO)
    advanced_option(ALSOFT_BACKEND_DSOUND "Enable DirectSound backend" OFF)    
    advanced_option(ALSOFT_BACKEND_JACK "Enable Jack backend" OFF)
    advanced_option(ALSOFT_BACKEND_OBOE "Enable OBOE backend" OFF)
    advanced_option(ALSOFT_BACKEND_OPENSL "Enable OpenSL backend" OFF)
    advanced_option(ALSOFT_BACKEND_PIPEWIRE "Enable PipeWire backend" OFF)
    advanced_option(ALSOFT_BACKEND_PORTAUDIO "Enable PortAudio backend" OFF)
    advanced_option(ALSOFT_BACKEND_PULSEAUDIO "Enable PulseAudio backend" OFF)
    advanced_option(ALSOFT_BACKEND_SDL2 "Use SDL2 Backend" ON)
    advanced_option(ALSOFT_BACKEND_WASAPI "Enable WASAPI backend" OFF)
    advanced_option(ALSOFT_BACKEND_WAVE "Enable Wave backend" OFF)
    advanced_option(ALSOFT_BACKEND_WINMM "Enable WinMM backend" OFF)
    mark_as_advanced(ALSOFT_BUILD_ROUTER)
    mark_as_advanced(ALSOFT_CPUEXT_NEON)
    mark_as_advanced(ALSOFT_CPUEXT_SSE)
    mark_as_advanced(ALSOFT_CPUEXT_SSE2)
    mark_as_advanced(ALSOFT_CPUEXT_SSE3)
    mark_as_advanced(ALSOFT_CPUEXT_SSE4_1)
    mark_as_advanced(ALSOFT_DLOPEN)
    mark_as_advanced(ALSOFT_EAX)
    advanced_option(ALSOFT_EMBED_HRTF_DATA "Embed the HRTF data files (increases library footprint)" OFF)
    advanced_option(ALSOFT_EXAMPLES  "Build example programs"  OFF)
    advanced_option(ALSOFT_INSTALL "Install OpenAL" OFF) # we move it ourselves
    advanced_option(ALSOFT_INSTALL_CONFIG "Install alsoft.conf sample configuration file" OFF)
    advanced_option(ALSOFT_INSTALL_HRTF_DATA "Install HRTF data files" OFF)
    advanced_option(ALSOFT_INSTALL_AMBDEC_PRESETS "Install AmbDec preset files" OFF)
    advanced_option(ALSOFT_INSTALL_EXAMPLES "Install example programs (alplay, alstream, ...)" OFF)
    advanced_option(ALSOFT_INSTALL_UTILS "Install utility programs (openal-info, alsoft-config, ...)" OFF)
    mark_as_advanced(ALSOFT_UPDATE_BUILD_VERSION)
    mark_as_advanced(ALSOFT_NO_CONFIG_UTIL)
    mark_as_advanced(ALSOFT_REQUIRE_COREAUDIO)
    mark_as_advanced(ALSOFT_REQUIRE_DSOUND)
    mark_as_advanced(ALSOFT_REQUIRE_JACK)
    mark_as_advanced(ALSOFT_REQUIRE_NEON)
    mark_as_advanced(ALSOFT_REQUIRE_OBOE)
    mark_as_advanced(ALSOFT_REQUIRE_OPENSL)
    mark_as_advanced(ALSOFT_REQUIRE_PIPEWIRE)
    mark_as_advanced(ALSOFT_REQUIRE_PORTAUDIO)
    mark_as_advanced(ALSOFT_REQUIRE_PULSEAUDIO)
    mark_as_advanced(ALSOFT_REQUIRE_SDL2)
    mark_as_advanced(ALSOFT_REQUIRE_SSE)
    mark_as_advanced(ALSOFT_REQUIRE_SSE2)
    mark_as_advanced(ALSOFT_REQUIRE_SSE3)
    mark_as_advanced(ALSOFT_REQUIRE_SSE4_1)
    mark_as_advanced(ALSOFT_REQUIRE_WASAPI)
    mark_as_advanced(ALSOFT_REQUIRE_WINMM)
    mark_as_advanced(ALSOFT_SEARCH_INSTALL_DATADIR)
    mark_as_advanced(ALSOFT_TESTS)
    mark_as_advanced(ALSOFT_UTILS)
    mark_as_advanced(ALSOFT_WERROR)
endif()


add_subdirectory(nativeFileDialogs ${TORQUE_LIB_TARG_DIRECTORY}/nfd EXCLUDE_FROM_ALL)
add_subdirectory(convexMath ${TORQUE_LIB_TARG_DIRECTORY}/convexMath EXCLUDE_FROM_ALL)
add_subdirectory(opcode ${TORQUE_LIB_TARG_DIRECTORY}/opcode EXCLUDE_FROM_ALL)
add_subdirectory(squish ${TORQUE_LIB_TARG_DIRECTORY}/squish EXCLUDE_FROM_ALL)
add_subdirectory(collada ${TORQUE_LIB_TARG_DIRECTORY}/collada EXCLUDE_FROM_ALL)
add_subdirectory(glad ${TORQUE_LIB_TARG_DIRECTORY}/glad EXCLUDE_FROM_ALL)

if(TORQUE_TESTING)
    add_subdirectory(gtest ${TORQUE_LIB_TARG_DIRECTORY}/gtest EXCLUDE_FROM_ALL)
endif()

