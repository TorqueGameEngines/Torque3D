# - Find speexdsp
# Find the native speexdsp includes and libraries
#
#  SPEEXDSP_INCLUDE_DIRS - where to find speex_preprocess.h, etc.
#  SPEEXDSP_LIBRARIES    - List of libraries when using speexdsp.
#  SpeexDsp_FOUND        - True if speexdsp found.

if(SPEEXDSP_INCLUDE_DIR)
    # Already in cache, be silent
    set(SPEEXDSP_FIND_QUIETLY TRUE)
endif(SPEEXDSP_INCLUDE_DIR)

find_package (PkgConfig QUIET)
pkg_check_modules(PC_SPEEXDSP QUIET speexdsp)

find_path(SPEEXDSP_INCLUDE_DIR speex/speex_preprocess.h HINTS ${PC_SPEEXDSP_INCLUDEDIR} ${PC_SPEEXDSP_INCLUDE_DIRS} ${SPEEXDSP_ROOT} PATH_SUFFIXES include)
find_library(SPEEXDSP_LIBRARY NAMES speexdsp HINTS ${PC_SPEEXDSP_LIBDIR} ${PC_SPEEXDSP_LIBRARY_DIRS} ${SPEEXDSP_ROOT} PATH_SUFFIXES lib)
# Handle the QUIETLY and REQUIRED arguments and set SPEEXDSP_FOUND
# to TRUE if all listed variables are TRUE.
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(SpeexDsp DEFAULT_MSG SPEEXDSP_INCLUDE_DIR SPEEXDSP_LIBRARY)

if (SPEEXDSP_FOUND)
	set (SPEEXDSP_LIBRARIES ${SPEEXDSP_LIBRARY})
	set (SPEEXDSP_INCLUDE_DIRS ${SPEEXDSP_INCLUDE_DIR})
endif (SPEEXDSP_FOUND)

mark_as_advanced(SPEEXDSP_INCLUDE_DIR SPEEXDSP_LIBRARY)
