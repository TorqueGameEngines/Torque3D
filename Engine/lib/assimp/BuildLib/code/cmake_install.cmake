# Install script for directory: F:/assimp/BLD/Engine/lib/assimp/code

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files/Assimp")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "F:/assimp/BLD/Engine/lib/assimp/BuildLib/code/Debug/assimp-vc140-mt.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "F:/assimp/BLD/Engine/lib/assimp/BuildLib/code/Release/assimp-vc140-mt.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "F:/assimp/BLD/Engine/lib/assimp/BuildLib/code/MinSizeRel/assimp-vc140-mt.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "F:/assimp/BLD/Engine/lib/assimp/BuildLib/code/RelWithDebInfo/assimp-vc140-mt.lib")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "F:/assimp/BLD/Engine/lib/assimp/BuildLib/code/Debug/assimp-vc140-mt.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "F:/assimp/BLD/Engine/lib/assimp/BuildLib/code/Release/assimp-vc140-mt.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "F:/assimp/BLD/Engine/lib/assimp/BuildLib/code/MinSizeRel/assimp-vc140-mt.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "F:/assimp/BLD/Engine/lib/assimp/BuildLib/code/RelWithDebInfo/assimp-vc140-mt.dll")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xassimp-devx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp" TYPE FILE FILES
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/anim.h"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/ai_assert.h"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/camera.h"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/color4.h"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/color4.inl"
    "F:/assimp/BLD/Engine/lib/assimp/BuildLib/code/../include/assimp/config.h"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/defs.h"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/Defines.h"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/cfileio.h"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/light.h"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/material.h"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/material.inl"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/matrix3x3.h"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/matrix3x3.inl"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/matrix4x4.h"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/matrix4x4.inl"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/mesh.h"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/pbrmaterial.h"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/postprocess.h"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/quaternion.h"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/quaternion.inl"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/scene.h"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/metadata.h"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/texture.h"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/types.h"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/vector2.h"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/vector2.inl"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/vector3.h"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/vector3.inl"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/version.h"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/cimport.h"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/importerdesc.h"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/Importer.hpp"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/DefaultLogger.hpp"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/ProgressHandler.hpp"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/IOStream.hpp"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/IOSystem.hpp"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/Logger.hpp"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/LogStream.hpp"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/NullLogger.hpp"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/cexport.h"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/Exporter.hpp"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/DefaultIOStream.h"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/DefaultIOSystem.h"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/SceneCombiner.h"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/fast_atof.h"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/qnan.h"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/BaseImporter.h"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/Hash.h"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/MemoryIOWrapper.h"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/ParsingUtils.h"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/StreamReader.h"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/StreamWriter.h"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/StringComparison.h"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/StringUtils.h"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/SGSpatialSort.h"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/GenericProperty.h"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/SpatialSort.h"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/SkeletonMeshBuilder.h"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/SmoothingGroups.h"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/SmoothingGroups.inl"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/StandardShapes.h"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/RemoveComments.h"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/Subdivision.h"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/Vertex.h"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/LineSplitter.h"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/TinyFormatter.h"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/Profiler.h"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/LogAux.h"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/Bitmap.h"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/XMLTools.h"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/IOStreamBuffer.h"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/CreateAnimMesh.h"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/irrXMLWrapper.h"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/BlobIOSystem.h"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/MathFunctions.h"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/Macros.h"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/Exceptional.h"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/ByteSwapper.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xassimp-devx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp/Compiler" TYPE FILE FILES
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/Compiler/pushpack1.h"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/Compiler/poppack1.h"
    "F:/assimp/BLD/Engine/lib/assimp/code/../include/assimp/Compiler/pstdint.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES "F:/assimp/BLD/Engine/lib/assimp/BuildLib/code/Debug/assimp-vc140-mt.pdb")
  endif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES "F:/assimp/BLD/Engine/lib/assimp/BuildLib/code/RelWithDebInfo/assimp-vc140-mt.pdb")
  endif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
endif()

