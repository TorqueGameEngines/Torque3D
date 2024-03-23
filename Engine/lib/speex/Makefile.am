## Process this file with automake to produce Makefile.in. -*-Makefile-*-

# To disable automatic dependency tracking if using other tools than
# gcc and gmake, add the option 'no-dependencies'
AUTOMAKE_OPTIONS = 1.8
ACLOCAL_AMFLAGS = -I m4

m4datadir = $(datadir)/aclocal
m4data_DATA = speex.m4

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = speex.pc

EXTRA_DIST = Speex.spec Speex.spec.in Speex.kdevelop speex.m4 speex.pc.in \
	README.blackfin README.symbian README.TI-DSP CMakeLists.txt config.h.cmake \
	$(cmake_files) .appveyor.yml

cmake_files = cmake/FindOgg.cmake cmake/FindSpeexDsp.cmake \
	cmake/FindSpeexDsp.cmake cmake/speex-config.cmake cmake/TestVarArrays.cmake

#Fools KDevelop into including all files
SUBDIRS = libspeex include doc win32 symbian ti

if BUILD_BINARIES
SUBDIRS += src
endif

DIST_SUBDIRS = libspeex include src doc win32 symbian ti

rpm: dist
	rpmbuild -ta ${PACKAGE}-${VERSION}.tar.gz
