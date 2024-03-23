# - Find fftw3
# Find the native fftw3 includes and libraries
#
#  FFTW3_INCLUDE_DIRS - where to find fftw3.h, etc.
#  FFTW3_LIBRARIES    - List of libraries when using fftw3.
#  FFTW3_FOUND        - True if fftw3 found.

if(FFTW3_INCLUDE_DIR)
    # Already in cache, be silent
    set(FFTW3_FIND_QUIETLY TRUE)
endif(FFTW3_INCLUDE_DIR)

find_package (PkgConfig QUIET)
pkg_check_modules(PC_FFTW QUIET fftw3f)

find_path(FFTW3_INCLUDE_DIR fftw3.h HINTS ${PC_FFTW3_INCLUDEDIR} ${PC_FFTW3_INCLUDE_DIRS} ${FFTW3_ROOT} PATH_SUFFIXES include)
find_library(FFTW3_LIBRARY NAMES fftw3f HINTS ${PC_FFTW3_LIBDIR} ${PC_FFTW3_LIBRARY_DIRS} ${FFTW3_ROOT} PATH_SUFFIXES lib)
# Handle the QUIETLY and REQUIRED arguments and set FFTW3_FOUND
# to TRUE if all listed variables are TRUE.
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(FFTW3 REQUIRED_VARS FFTW3_INCLUDE_DIR FFTW3_LIBRARY)

if (FFTW3_FOUND)
	set (FFTW3_LIBRARIES ${FFTW3_LIBRARY})
	set (FFTW3_INCLUDE_DIRS ${FFTW3_INCLUDE_DIR})
endif (FFTW3_FOUND)

mark_as_advanced(FFTW3_INCLUDE_DIR FFTW3_LIBRARY)
