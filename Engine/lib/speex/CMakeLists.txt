cmake_minimum_required(VERSION 3.1)

project(speex VERSION 1.2.0 LANGUAGES C)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")

include(CheckIncludeFile)
include(CheckSymbolExists)
include(CheckLibraryExists)
include(CMakeDependentOption)
include(FeatureSummary)
include(TestVarArrays)
include(CheckCCompilerFlag)
include(GNUInstallDirs)
include(TestBigEndian)

test_big_endian(WORDS_BIGENDIAN)

check_include_file(inttypes.h HAVE_INTTYPES_H)
if(HAVE_INTTYPES_H)
	set(INCLUDE_STDINT "#include <inttypes.h>")
else()
	check_include_file(stdint.h HAVE_STDINT_H)
	if(HAVE_STDINT_H)
		set(INCLUDE_STDINT "#include <stdint.h>")
	else()
		check_include_file(sys/types.h INCLUDE_SYS_TYPES_H)
		if(HAVE_SYS_TYPES_H)
			set(INCLUDE_STDINT "#include <sys/types.h>")
		endif()
	endif()
endif()
set(SIZE16 int16_t)
set(USIZE16 uint16_t)
set(SIZE32 int32_t)
set(USIZE32 uint32_t)
set(SIZE64 int64_t)
configure_file(include/speex/speex_config_types.h.in include/speex/speex_config_types.h @ONLY)

test_vararrays(VAR_ARRAYS)
if(NOT VAR_ARRAYS)
	check_include_file(alloca.h HAVE_ALLOCA_H)
	if(WIN32)
		set(USE_ALLOCA 1)
	else()
		check_symbol_exists(alloca "stdlib.h;alloca.h"  USE_ALLOCA)
	endif()
endif()

option(ENABLE_FLOATING_POINT "Compile as floating-point" ON)
option(ENABLE_FIXED_POINT "Compile as fixed-point" OFF)


if(ENABLE_FLOATING_POINT AND ENABLE_FIXED_POINT)
	message(FATAL_ERROR "Select one of ENABLE_FLOATING_POINT of ENABLE_FIXED_POINT.")
endif()
if((NOT ENABLE_FLOATING_POINT) AND (NOT ENABLE_FIXED_POINT))
	message(FATAL_ERROR "Select one of ENABLE_FLOATING_POINT of ENABLE_FIXED_POINT.")
endif()

find_package(FFTW3)

cmake_dependent_option(USE_GPL_FFTW3 "Use FFTW3 for FFT" OFF "FFTW3_FOUND; ENABLE_FLOATING_POINT" OFF)

if(ENABLE_FLOATING_POINT)
	set(FLOATING_POINT 1)
	set(FIXED_POINT 0)
	set(USE_KISS_FFT 0)
	if(NOT USE_GPL_FFTW3)
		set(USE_SMALLFT 1)
	endif()
else()
	set(FLOATING_POINT 0)
	set(FIXED_POINT 1)
	set(USE_KISS_FFT 1)
	set(USE_SMALLFT 0)
	set(USE_GPL_FFTW3 0)
endif()

cmake_dependent_option(ENABLE_FIXED_POINT_DEBUG "Debug fixed-point implementation" OFF "ENABLE_FIXED_POINT" OFF)
set(FIXED_POINT_DEBUG ${ENABLE_FIXED_POINT_DEBUG})

option(DISABLE_FLOAT_API "Disable all parts of the API that are using floats" OFF)
option(DISABLE_VBR "Disable VBR and VAD from the codec" OFF)
cmake_dependent_option(ENABLE_VORBIS_PSY "Enable the Vorbis psy model" OFF "NOT ENABLE_FIXED_POINT;VAR_ARRAYS" OFF)
set(VORBIS_PSYCHO ${ENABLE_VORBIS_PSY})

if(CMAKE_SYSTEM_PROCESSOR MATCHES "(x86)|(X86)|(amd64)|(AMD64)")
    set(CPU_IS_X86 TRUE)
else()
    set(CPU_IS_X86 FALSE)
endif()
if(CPU_IS_X86)
	check_include_file(xmmintrin.h HAVE_XMMINTRIN_H)
endif()
cmake_dependent_option(ENABLE_SSE "Enable SSE support" ON "CPU_IS_X86;HAVE_XMMINTRIN_H;ENABLE_FLOATING_POINT" OFF)
if(ENABLE_SSE)
	set(_USE_SSE 1)
	check_c_compiler_flag("/arch:SSE" ARCH_SSE_FLAG)
	if(ARCH_SSE_FLAG)
		set(SSE_FLAGS "/arch:SSE")
	else()
		check_c_compiler_flag("-msse" MSSE_FLAG)
		if(MSSE_FLAG)
			set(SSE_FLAGS "-msse")
		endif()
	endif()
endif()

if (CMAKE_SYSTEM_PROCESSOR MATCHES "^arm")
	set(CPU_IS_ARM 1)
endif ()
cmake_dependent_option(ENABLE_ARM4_ASM "Make use of ARM4 assembly optimizations" OFF "CPU_IS_ARM;ENABLE_FIXED_POINT" OFF)
set(ARM4_ASM ${ENABLE_ARM4_ASM})
cmake_dependent_option(ENABLE_ARM5E_ASM "Make use of ARM5E assembly optimizations" OFF "CPU_IS_ARM;ENABLE_FIXED_POINT" OFF)
set(ARM5E_ASM ${ENABLE_ARM5E_ASM})
cmake_dependent_option(ENABLE_BLACKFIN_ASM "Make use of Blackfin assembly optimizations" OFF "NOT CPU_IS_X86;ENABLE_FIXED_POINT" OFF)
set(BFIN_ASM ${ENABLE_BLACKFIN_ASM})
cmake_dependent_option(ENABLE_TI_C55X "Enable support for TI C55X DSP" OFF "NOT CPU_IS_X86" OFF)
set(TI_C55X ${ENABLE_TI_C55X})

if(NOT WIN32)
	check_library_exists(m cos "" HAVE_LIBM)
	if(HAVE_LIBM)
		find_library(LIBM m)
	endif()
endif()

if(MSVC)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS -D_CRT_NONSTDC_NO_DEPRECATE)
endif(MSVC)

find_package(Ogg)
find_package(SpeexDsp)

cmake_dependent_option(USE_SPEEXDSP "Enable SpeexDSP library" ON "SpeexDsp_FOUND" OFF)
cmake_dependent_option(BUILD_PROGRAMS "Build the encoder and decoder programs, not only the library" ON "Ogg_FOUND" ON)

check_c_compiler_flag("-fvisibility=hidden" HAS_VISIBILITY)
if(HAS_VISIBILITY)
	SET(EXPORT "__attribute__((visibility(\"default\")))")
endif()

check_include_file(getopt.h HAVE_GETOPT_H)
if(HAVE_GETOPT_H)
	check_symbol_exists(getopt_long getopt.h HAVE_GETOPT_LONG)
endif()

option (ENABLE_PACKAGE_CONFIG "Generate and install package config file" ON)

set_package_properties(Ogg PROPERTIES TYPE RECOMMENDED
	URL "www.xiph.org/ogg/"
	DESCRIPTION "library for manipulating ogg bitstreams"
	PURPOSE "Required to build speexenc and speexdec tools")
set_package_properties(SpeexDsp PROPERTIES TYPE RECOMMENDED
	URL "https://speex.org/"
	DESCRIPTION "speech processing library that goes along with the Speex codec"
	PURPOSE "Enables speexenc tool preprocessing options")
set_package_properties(FFTW3 PROPERTIES TYPE OPTIONAL
	URL "http://www.fftw.org/"
	DESCRIPTION "fast Fourier transform library"
	PURPOSE "Enables use of FFTW3 for fast Fourier transforms")
add_feature_info(ENABLE_ALLOCA USE_ALLOCA "Make use of alloca function.")
add_feature_info(ENABLE_VAR_ARRAYS VAR_ARRAYS "Make use of variable-length arrays.")
add_feature_info(ENABLE_FLOATING_POINT ENABLE_FLOATING_POINT "compile as floating-point.")
add_feature_info(ENABLE_FIXED_POINT ENABLE_FIXED_POINT "compile as fixed-point.")
add_feature_info(ENABLE_FIXED_POINT_DEBUG ENABLE_FIXED_POINT_DEBUG "debug fixed-point implementation.")
add_feature_info(ENABLE_SSE ENABLE_SSE "enable SSE support.")
add_feature_info(ENABLE_ARM4_ASM ENABLE_ARM4_ASM "make use of ARM4 assembly optimizations.")
add_feature_info(ENABLE_ARM5E_ASM ENABLE_ARM5E_ASM "make use of ARM5E assembly optimizations.")
add_feature_info(ENABLE_BLACKFIN_ASM ENABLE_BLACKFIN_ASM "make use of Blackfin assembly optimizations.")
add_feature_info(ENABLE_TI_C55X ENABLE_TI_C55X "enable support for TI C55X DSP.")
add_feature_info(DISABLE_FLOAT_API DISABLE_FLOAT_API "disable all parts of the API that are using floats.")
add_feature_info(DISABLE_VBR DISABLE_VBR "disable VBR and VAD from the codec.")
add_feature_info(ENABLE_VORBIS_PSY ENABLE_VORBIS_PSY "enable the Vorbis psy model.")
add_feature_info(ENABLE_SPEEXDSP USE_SPEEXDSP "enable speexenc preprocessing options.")
add_feature_info(BUILD_BINARIES BUILD_BINARIES "build the encoder and decoder programs, not only the library.")
add_feature_info(ENABLE_PACKAGE_CONFIG ENABLE_PACKAGE_CONFIG "generate and install package config file")
add_feature_info(USE_GPL_FFTW3 USE_GPL_FFTW3 "Use FFTW3 library for fast Fourier transforms")
feature_summary(WHAT ALL)

configure_file(config.h.cmake config.h)

set(speex_PUBLIC_HEADERS
	include/speex/speex.h
	include/speex/speex_bits.h
	include/speex/speex_callbacks.h
	include/speex/speex_header.h
	include/speex/speex_stereo.h
	include/speex/speex_types.h
	${CMAKE_CURRENT_BINARY_DIR}/include/speex/speex_config_types.h)

set(speex_SOURCES
	libspeex/cb_search.c
	libspeex/exc_10_32_table.c
	libspeex/exc_8_128_table.c
	libspeex/filters.c
	libspeex/gain_table.c
	libspeex/hexc_table.c
	libspeex/high_lsp_tables.c
	libspeex/lsp.c
	libspeex/ltp.c
	libspeex/speex.c
	libspeex/stereo.c
	libspeex/vbr.c
	libspeex/vq.c
	libspeex/bits.c
	libspeex/exc_10_16_table.c
	libspeex/exc_20_32_table.c
	libspeex/exc_5_256_table.c
	libspeex/exc_5_64_table.c
	libspeex/gain_table_lbr.c
	libspeex/hexc_10_32_table.c
	libspeex/lpc.c
	libspeex/lsp_tables_nb.c
	libspeex/modes.c
	libspeex/modes_wb.c
	libspeex/nb_celp.c
	libspeex/quant_lsp.c
	libspeex/sb_celp.c
	libspeex/speex_callbacks.c
	libspeex/speex_header.c
	libspeex/window.c
	libspeex/arch.h
	libspeex/bfin.h
	libspeex/cb_search_arm4.h
	libspeex/cb_search_bfin.h
	libspeex/cb_search_sse.h
	libspeex/filters.h
	libspeex/filters_arm4.h
	libspeex/filters_bfin.h
	libspeex/filters_sse.h
	libspeex/fixed_arm4.h
	libspeex/fixed_arm5e.h
	libspeex/fixed_bfin.h
	libspeex/fixed_debug.h
	libspeex/lpc.h
	libspeex/lpc_bfin.h
	libspeex/ltp.h
	libspeex/ltp_arm4.h
	libspeex/ltp_sse.h
	libspeex/math_approx.h
	libspeex/misc_bfin.h
	libspeex/nb_celp.h
	libspeex/quant_lsp.h
	libspeex/sb_celp.h
	libspeex/stack_alloc.h
	libspeex/vbr.h
	libspeex/vq.h
	libspeex/vq_arm4.h
	libspeex/vq_bfin.h
	libspeex/vq_sse.h
	libspeex/cb_search.h
	libspeex/fftwrap.h
	libspeex/fftwrap.c
	libspeex/fixed_generic.h
	libspeex/lsp.h
	libspeex/lsp_bfin.h
	libspeex/ltp_bfin.h
	libspeex/modes.h
	libspeex/os_support.h
	libspeex/quant_lsp_bfin.h
	libspeex/smallft.h)

add_library(speex ${speex_PUBLIC_HEADERS} ${speex_SOURCES})
target_compile_definitions(speex
	PRIVATE -DHAVE_CONFIG_H)
target_include_directories(speex
	PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
	PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include/speex>
	PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	PUBLIC $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
if(USE_GPL_FFTW3)
	target_include_directories(speex
		PRIVATE $<BUILD_INTERFACE:${FFTW3_INCLUDE_DIRS}>)
	if(BUILD_SHARED_LIBS)
		target_link_libraries(speex PRIVATE ${FFTW3_LIBRARIES})
	else()
		target_link_libraries(speex PUBLIC ${FFTW3_LIBRARIES})
	endif()
endif()
if(HAVE_LIBM)
	if(BUILD_SHARED_LIBS)
		target_link_libraries(speex PRIVATE ${LIBM})
	else()
		target_link_libraries(speex PUBLIC ${LIBM})
	endif()
endif()
target_compile_options(speex PRIVATE ${SSE_FLAGS})
if(WIN32 AND BUILD_SHARED_LIBS)
	target_sources(speex PRIVATE win32/libspeex.def)
	set_target_properties (speex PROPERTIES OUTPUT_NAME "libspeex")
endif()
set_target_properties (speex PROPERTIES
		PUBLIC_HEADER "${speex_PUBLIC_HEADERS}"
		SOVERSION 1.5.1
		VERSION 1)
if(EXPORT AND BUILD_SHARED_LIBS)
	set_target_properties (speex PROPERTIES
			C_VISIBILITY_PRESET hidden)
endif()
if(USE_SMALLFT)
	target_sources(speex PRIVATE
		libspeex/smallft.c)
elseif(USE_KISS_FFT)
	target_sources(speex PRIVATE
		libspeex/kiss_fft.c
		libspeex/_kiss_fft_guts.h
		libspeex/kiss_fft.h
		libspeex/kiss_fftr.c
		libspeex/kiss_fftr.h)
endif()
if(VORBIS_PSYCHO)
	target_sources(speex PRIVATE
		libspeex/vorbis_psy.h
		libspeex/vorbis_psy.c)
endif()

# Programs

if(BUILD_BINARIES)

SET(speexenc_SOURCES
	src/speexenc.c
	src/wav_io.c
	src/skeleton.c)
add_executable(speexenc ${speexenc_SOURCES})
target_include_directories(speexenc
	PRIVATE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
		$<BUILD_INTERFACE:${SPEEXDSP_INCLUDE_DIRS}>)
target_link_libraries(speexenc
	PUBLIC speex Ogg::ogg ${SPEEXDSP_LIBRARIES})
if(WIN32)
	target_link_libraries(speexenc PRIVATE winmm.lib)
endif()
target_compile_definitions(speexenc
	PRIVATE -DHAVE_CONFIG_H)
if(NOT HAVE_GETOPT_LONG)
	target_sources(speexenc PRIVATE
		src/getopt.c
		src/getopt1.c
		src/wave_out.c)
endif()

SET(speexdec_SOURCES
	src/speexdec.c
	src/wav_io.c)
add_executable(speexdec ${speexdec_SOURCES})
target_include_directories(speexdec
	PRIVATE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
		$<BUILD_INTERFACE:${OGG_INCLUDE_DIRS}>)
target_link_libraries(speexdec PUBLIC speex ${OGG_LIBRARIES})
if(WIN32)
	target_link_libraries(speexdec PRIVATE winmm.lib)
endif()
target_compile_definitions(speexdec
	PRIVATE -DHAVE_CONFIG_H)
if(NOT HAVE_GETOPT_LONG)
	target_sources(speexdec PRIVATE
		src/getopt.c
		src/getopt1.c
		src/wave_out.c)
endif()

# Tests (no automatic checking supported)

add_executable(testenc libspeex/testenc.c)
target_include_directories(testenc
	PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>)
target_link_libraries(testenc
	PRIVATE ${LIBM}
	PUBLIC speex)
target_compile_definitions(testenc
	PRIVATE -DHAVE_CONFIG_H)
add_executable(testenc_wb libspeex/testenc_wb.c)
target_include_directories(testenc_wb
	PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>)
target_link_libraries(testenc_wb
	PRIVATE ${LIBM}
	PUBLIC speex)
target_compile_definitions(testenc_wb
	PRIVATE -DHAVE_CONFIG_H)
add_executable(testenc_uwb libspeex/testenc_uwb.c)
target_include_directories(testenc_uwb
	PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>)
target_link_libraries(testenc_uwb
	PRIVATE ${LIBM}
	PUBLIC speex)
target_compile_definitions(testenc_uwb
	PRIVATE -DHAVE_CONFIG_H)

endif()

# Installation

install(TARGETS speex
	EXPORT speex-targets
	RUNTIME	DESTINATION			${CMAKE_INSTALL_BINDIR}
	ARCHIVE DESTINATION			${CMAKE_INSTALL_LIBDIR}
	LIBRARY DESTINATION			${CMAKE_INSTALL_LIBDIR}
	PUBLIC_HEADER DESTINATION	${CMAKE_INSTALL_INCLUDEDIR}/speex)

if(BUILD_BINARIES)
	install(TARGETS speexdec speexenc RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
endif()

install(FILES doc/manual.pdf DESTINATION ${CMAKE_INSTALL_DOCDIR})
install(FILES src/speexenc.1 src/speexdec.1 DESTINATION ${CMAKE_INSTALL_MANDIR}/man1)
install(FILES speex.m4 DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/aclocal)

set(prefix ${CMAKE_INSTALL_PREFIX})
set(exec_prefix $\{prefix\})
set(libdir $\{exec_prefix\}/${CMAKE_INSTALL_LIBDIR})
set(includedir $\{prefix\}/${CMAKE_INSTALL_INCLUDEDIR})
set(SPEEX_VERSION ${PROJECT_VERSION})
if(HAVE_LIBM)
	set(LIBM -lm)
endif()
configure_file(speex.pc.in speex.pc @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/speex.pc DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)

set(PACKAGE ${PROJECT_NAME})
set(VERSION ${PROJECT_VERSION})
configure_file(Speex.spec.in Speex.spec @ONLY)

if (ENABLE_PACKAGE_CONFIG)
	include (CMakePackageConfigHelpers)
	write_basic_package_version_file (speex-config-version.cmake COMPATIBILITY SameMajorVersion)
	set(CMAKE_INSTALL_PACKAGEDIR ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})
	install(EXPORT speex-targets NAMESPACE Speex:: DESTINATION ${CMAKE_INSTALL_PACKAGEDIR})
	install(FILES ${CMAKE_CURRENT_BINARY_DIR}/speex-config-version.cmake DESTINATION ${CMAKE_INSTALL_PACKAGEDIR})
	install(FILES cmake/speex-config.cmake DESTINATION ${CMAKE_INSTALL_PACKAGEDIR})
endif()
