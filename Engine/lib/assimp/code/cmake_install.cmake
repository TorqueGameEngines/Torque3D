# Install script for directory: /Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/Users/ragora/Documents/Test")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
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

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/objdump")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xlibassimp5.2.0x" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/bin/libassimp.5.2.0.dylib"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/bin/libassimp.5.dylib"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.5.2.0.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.5.dylib"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -x "${file}")
      endif()
    endif()
  endforeach()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xlibassimp5.2.0x" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/bin/libassimp.dylib")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.dylib" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.dylib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -x "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.dylib")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xassimp-devx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp" TYPE FILE FILES
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/anim.h"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/aabb.h"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/ai_assert.h"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/camera.h"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/color4.h"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/color4.inl"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/config.h"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/ColladaMetaData.h"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/commonMetaData.h"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/defs.h"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/cfileio.h"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/light.h"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/material.h"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/material.inl"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/matrix3x3.h"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/matrix3x3.inl"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/matrix4x4.h"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/matrix4x4.inl"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/mesh.h"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/ObjMaterial.h"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/pbrmaterial.h"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/GltfMaterial.h"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/postprocess.h"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/quaternion.h"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/quaternion.inl"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/scene.h"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/metadata.h"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/texture.h"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/types.h"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/vector2.h"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/vector2.inl"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/vector3.h"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/vector3.inl"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/version.h"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/cimport.h"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/importerdesc.h"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/Importer.hpp"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/DefaultLogger.hpp"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/ProgressHandler.hpp"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/IOStream.hpp"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/IOSystem.hpp"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/Logger.hpp"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/LogStream.hpp"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/NullLogger.hpp"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/cexport.h"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/Exporter.hpp"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/DefaultIOStream.h"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/DefaultIOSystem.h"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/ZipArchiveIOSystem.h"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/SceneCombiner.h"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/fast_atof.h"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/qnan.h"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/BaseImporter.h"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/Hash.h"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/MemoryIOWrapper.h"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/ParsingUtils.h"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/StreamReader.h"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/StreamWriter.h"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/StringComparison.h"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/StringUtils.h"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/SGSpatialSort.h"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/GenericProperty.h"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/SpatialSort.h"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/SkeletonMeshBuilder.h"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/SmallVector.h"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/SmoothingGroups.h"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/SmoothingGroups.inl"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/StandardShapes.h"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/RemoveComments.h"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/Subdivision.h"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/Vertex.h"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/LineSplitter.h"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/TinyFormatter.h"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/Profiler.h"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/LogAux.h"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/Bitmap.h"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/XMLTools.h"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/IOStreamBuffer.h"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/CreateAnimMesh.h"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/XmlParser.h"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/BlobIOSystem.h"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/MathFunctions.h"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/Exceptional.h"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/ByteSwapper.h"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/Base64.hpp"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xassimp-devx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp/Compiler" TYPE FILE FILES
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/Compiler/pushpack1.h"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/Compiler/poppack1.h"
    "/Users/ragora/Documents/Projects/Torque3D/Engine/lib/assimp/code/../include/assimp/Compiler/pstdint.h"
    )
endif()

