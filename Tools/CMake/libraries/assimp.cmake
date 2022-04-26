# -----------------------------------------------------------------------------
# Copyright (c) 2014 GarageGames, LLC
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

project(assimp)

addPathRec("${libDir}/assimp/code")
addPath("${libDir}/assimp/code/Importer")
addPath("${libDir}/assimp/contrib")
addPath("${libDir}/assimp/contrib/clipper")
addPath("${libDir}/assimp/contrib/irrXML")
addPath("${libDir}/assimp/contrib/Open3DGC")
addPath("${libDir}/assimp/contrib/openddlparser")
addPath("${libDir}/assimp/contrib/poly2tri")
#addPath("${libDir}/assimp/contrib/rapidjson")
#addPath("${libDir}/assimp/contrib/rapidjson/include")
#addPath("${libDir}/assimp/contrib/rapidjson/include/rapidjson")
addPath("${libDir}/assimp/contrib/unzip")
addPath("${libDir}/assimp/contrib/utf8cpp")
addPath("${libDir}/assimp/contrib/zip")
addPath("${libDir}/zlib") #use T3D's included

addDef(ASSIMP_BUILD_NO_OWN_ZLIB)

#   Disable all exporters, none should be needed but functionality
#   is there if needed later on in development
#   Specifically the export as DAE functionality already enabled in engine

addDef(ASSIMP_BUILD_NO_EXPORT)

#   Some Common file format imports NOT disabled
#addDef(ASSIMP_BUILD_NO_GLTF_IMPORTER)
#addDef(ASSIMP_BUILD_NO_FBX_IMPORTER)
#addDef(ASSIMP_BUILD_NO_MS3D_IMPORTER)
#addDef(ASSIMP_BUILD_NO_OBJ_IMPORTER)
#addDef(ASSIMP_BUILD_NO_LWO_IMPORTER)


#   List of Importers to enable imporing of a specific file type
#   add a # to comment out the line.
addDef(ASSIMP_BUILD_NO_3DS_IMPORTER)
addDef(ASSIMP_BUILD_NO_3MF_IMPORTER)
addDef(ASSIMP_BUILD_NO_AC_IMPORTER)
addDef(ASSIMP_BUILD_NO_AMF_IMPORTER)
addDef(ASSIMP_BUILD_NO_ASE_IMPORTER)
addDef(ASSIMP_BUILD_NO_ASSBIN_IMPORTER)
addDef(ASSIMP_BUILD_NO_B3D_IMPORTER)
addDef(ASSIMP_BUILD_NO_BLEND_IMPORTER)
addDef(ASSIMP_BUILD_NO_BVH_IMPORTER)
addDef(ASSIMP_BUILD_NO_C4D_IMPORTER)
addDef(ASSIMP_BUILD_NO_COB_IMPORTER)
#addDef(ASSIMP_BUILD_NO_COLLADA_IMPORTER)
addDef(ASSIMP_BUILD_NO_CSM_IMPORTER)
addDef(ASSIMP_BUILD_NO_DXF_IMPORTER)
addDef(ASSIMP_BUILD_NO_HMP_IMPORTER)
addDef(ASSIMP_BUILD_NO_IFC_IMPORTER)
addDef(ASSIMP_BUILD_NO_STEP_IMPORTER)
addDef(ASSIMP_BUILD_NO_IRR_IMPORTER)
addDef(ASSIMP_BUILD_NO_IRRMESH_IMPORTER)
addDef(ASSIMP_BUILD_NO_LWS_IMPORTER)
addDef(ASSIMP_BUILD_NO_M3D_IMPORTER)
addDef(ASSIMP_BUILD_NO_MD2_IMPORTER)
addDef(ASSIMP_BUILD_NO_MD3_IMPORTER)
addDef(ASSIMP_BUILD_NO_MD5_IMPORTER)
addDef(ASSIMP_BUILD_NO_MDC_IMPORTER)
addDef(ASSIMP_BUILD_NO_MDL_IMPORTER)
addDef(ASSIMP_BUILD_NO_MMD_IMPORTER)
addDef(ASSIMP_BUILD_NO_NDO_IMPORTER)
addDef(ASSIMP_BUILD_NO_NFF_IMPORTER)
addDef(ASSIMP_BUILD_NO_OFF_IMPORTER)
addDef(ASSIMP_BUILD_NO_OGRE_IMPORTER)
addDef(ASSIMP_BUILD_NO_OPENGEX_IMPORTER)
addDef(ASSIMP_BUILD_NO_PLY_IMPORTER)
addDef(ASSIMP_BUILD_NO_Q3BSP_IMPORTER)
addDef(ASSIMP_BUILD_NO_Q3D_IMPORTER)
addDef(ASSIMP_BUILD_NO_RAW_IMPORTER)
addDef(ASSIMP_BUILD_NO_SIB_IMPORTER)
addDef(ASSIMP_BUILD_NO_SMD_IMPORTER)
addDef(ASSIMP_BUILD_NO_STL_IMPORTER)
addDef(ASSIMP_BUILD_NO_TERRAGEN_IMPORTER)
addDef(ASSIMP_BUILD_NO_3D_IMPORTER)
addDef(ASSIMP_BUILD_NO_X_IMPORTER)
addDef(ASSIMP_BUILD_NO_X3D_IMPORTER)
addDef(ASSIMP_BUILD_NO_XGL_IMPORTER)

#   ALL exporters are disabled at the start of the definition blocks
#   if you want to disable only specific file types 
#   comment out the "addDef(ASSIMP_BUILD_NO_EXPORT)" higher in this text

#addDef(ASSIMP_BUILD_NO_3DS_EXPORTER)
#addDef(ASSIMP_BUILD_NO_3MF_EXPORTER)
#addDef(ASSIMP_BUILD_NO_ASSBIN_EXPORTER)
#addDef(ASSIMP_BUILD_NO_ASSJSON_EXPORTER)
#addDef(ASSIMP_BUILD_NO_ASSXML_EXPORTER)
addDef(ASSIMP_BUILD_NO_COLLADA_EXPORTER)
addDef(ASSIMP_BUILD_NO_FBX_EXPORTER)
addDef(ASSIMP_BUILD_NO_GLTF_EXPORTER)
#addDef(ASSIMP_BUILD_NO_M3D_EXPORTER)
#addDef(ASSIMP_BUILD_NO_OBJ_EXPORTER)
#addDef(ASSIMP_BUILD_NO_OPENGEX_EXPORTER)
#addDef(ASSIMP_BUILD_NO_PLY_EXPORTER)
#addDef(ASSIMP_BUILD_NO_STEP_EXPORTER)
#addDef(ASSIMP_BUILD_NO_STL_EXPORTER)
#addDef(ASSIMP_BUILD_NO_X_EXPORTER)
#addDef(ASSIMP_BUILD_NO_X3D_EXPORTER)

addDef(ASSIMP_IGNORE_GIT_HASH)
SET(GIT_COMMIT_HASH 0)
SET(GIT_BRANCH 0)
SET(ASSIMP_VERSION_MAJOR 5)
SET(ASSIMP_VERSION_MINOR 2)
SET(ASSIMP_VERSION_PATCH 3)
SET(ASSIMP_PACKAGE_VERSION "5_2_3")
CONFIGURE_FILE(
  ${libDir}/assimp/revision.h.in
  ${libDir}/assimp/revision.h
)

CONFIGURE_FILE(
  ${libDir}/assimp/include/assimp/config.h.in
  ${libDir}/assimp/include/assimp/config.h
)

addInclude(${libDir}/assimp)
addInclude(${libDir}/assimp/include/)
addInclude(${libDir}/assimp/include/assimp)
addInclude(${libDir}/assimp/contrib)
addInclude(${libDir}/assimp/contrib/clipper)
addInclude(${libDir}/assimp/contrib/irrXML)
addInclude(${libDir}/assimp/contrib/Open3DGC)
addInclude(${libDir}/assimp/contrib/openddlparser)
addInclude(${libDir}/assimp/contrib/poly2tri)
addInclude(${libDir}/assimp/contrib/pugixml/src)
addInclude(${libDir}/assimp/contrib/pugixml/contrib)
addInclude(${libDir}/assimp/contrib/rapidjson)
addInclude(${libDir}/assimp/contrib/rapidjson/include)
addInclude(${libDir}/assimp/contrib/unzip)
addInclude(${libDir}/assimp/contrib/utf8cpp)
addInclude(${libDir}/assimp/contrib/zip)
addInclude(${libDir}/zlib) #use T3D's included

finishLibrary()
