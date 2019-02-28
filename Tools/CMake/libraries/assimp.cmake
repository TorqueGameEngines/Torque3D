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

addPath("${libDir}/assimp/code")
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

#addDef(ASSIMP_BUILD_NO_GLTF_IMPORTER)
addDef(ASSIMP_BUILD_NO_C4D_IMPORTER)
addDef(ASSIMP_BUILD_NO_IFC_IMPORTER)
addDef(ASSIMP_BUILD_NO_OPENGEX_IMPORTER)
addDef(ASSIMP_BUILD_NO_IRRMESH_IMPORTER)
addDef(ASSIMP_BUILD_NO_IRR_IMPORTER)
addDef(ASSIMP_BUILD_NO_OWN_ZLIB)

addInclude(${libDir}/assimp)
addInclude(${libDir}/assimp/include/)
addInclude(${libDir}/assimp/include/assimp)
addInclude(${libDir}/assimp/contrib)
addInclude(${libDir}/assimp/contrib/clipper)
addInclude(${libDir}/assimp/contrib/irrXML)
addInclude(${libDir}/assimp/contrib/Open3DGC)
addInclude(${libDir}/assimp/contrib/openddlparser)
addInclude(${libDir}/assimp/contrib/poly2tri)
addInclude(${libDir}/assimp/contrib/rapidjson)
addInclude(${libDir}/assimp/contrib/rapidjson/include)
addInclude(${libDir}/assimp/contrib/unzip)
addInclude(${libDir}/assimp/contrib/utf8cpp)
addInclude(${libDir}/assimp/contrib/zip)
addInclude(${libDir}/zlib) #use T3D's included

finishLibrary()
