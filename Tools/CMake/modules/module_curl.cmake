# -----------------------------------------------------------------------------
# Copyright (c) 2015 GarageGames, LLC
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to
# deal in the Software without restriction, including without limitation the
# rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
# sell copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
# IN THE SOFTWARE.
# -----------------------------------------------------------------------------

option(TORQUE_NET_CURL "Use CURL and enable HTTPObject" OFF)
mark_as_advanced(TORQUE_NET_CURL)

if( NOT TORQUE_NET_CURL )
    return()
endif()

addDef( "TORQUE_NET_CURL" )

# curl
set(BUILD_CURL_EXE OFF CACHE INTERNAL "" FORCE)
set(CURL_CA_PATH "none" CACHE INTERNAL "" FORCE)
set(BUILD_TESTING OFF CACHE INTERNAL "" FORCE)
set(CMAKE_USE_LIBSSH2 OFF CACHE INTERNAL "" FORCE)
set(CURL_STATICLIB ON CACHE INTERNAL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE INTERNAL "" FORCE)
set(ENABLE_MANUAL OFF CACHE INTERNAL "" FORCE)
set(ENABLE_UNIX_SOCKETS OFF CACHE INTERNAL "" FORCE)
set(HTTP_ONLY ON CACHE INTERNAL "" FORCE)
set(PICKY_COMPILER ON CACHE INTERNAL "" FORCE)
if(WIN32)
    set(CURL_USE_SCHANNEL ON CACHE INTERNAL "" FORCE)
    set(CURL_STATIC_CRT ${TORQUE_STATIC} CACHE INTERNAL "" FORCE)
    set(ENABLE_INET_PTON ON CACHE INTERNAL "" FORCE)
elseif(APPLE)
    set(CURL_USE_OPENSSL OFF CACHE INTERNAL "" FORCE)
    set(CURL_USE_SECTRANSP ON CACHE INTERNAL "" FORCE)
endif()
add_subdirectory( ${libDir}/curl ${CMAKE_CURRENT_BINARY_DIR}/curl)

set(CURL_LIBRARIES libcurl)
set(CURL_INCLUDE_DIRS "${libDir}/curl/include")
set_property(TARGET libcurl APPEND PROPERTY INTERFACE_COMPILE_DEFINITIONS CURL_STATICLIB)

addLib(${CURL_LIBRARIES})
addInclude(${CURL_INCLUDE_DIRS})
