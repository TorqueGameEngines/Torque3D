# -----------------------------------------------------------------------------
# Copyright (c) 2020 Lukas Joergensen
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

project(csharp)

# --------------------
# -- Helper Macros
# --------------------

macro(csharp_addPath dir)
	set(tmp_files "")
	set(glob_config GLOB)
	if(${ARGC} GREATER 1 AND "${ARGV1}" STREQUAL "REC")
		set(glob_config GLOB_RECURSE)
	endif()
	file(${glob_config} tmp_files
			 ${dir}/*.cs
			 )
	foreach(entry ${BLACKLIST})
		list(REMOVE_ITEM tmp_files ${dir}/${entry})
	endforeach()
	LIST(APPEND ${CSHARP_LIBRARY_NAME}_files "${tmp_files}")
	LIST(APPEND ${CSHARP_LIBRARY_NAME}_paths "${dir}")
	#message(STATUS "addPath ${PROJECT_NAME} : ${tmp_files}")
endmacro()

# adds a file to the sources
macro(csharp_addFile filename)
	LIST(APPEND ${CSHARP_LIBRARY_NAME}_files "${filename}")
	#message(STATUS "addFile ${PROJECT_NAME} : ${filename}")
endmacro()

# finds and adds sources files in a folder recursively
macro(csharp_addPathRec dir)
	csharp_addPath("${dir}" "REC")
endmacro()

macro(csharp_generateFilters relDir baseDir)
	foreach(f ${${CSHARP_LIBRARY_NAME}_files})
		# Get the path of the file relative to ${DIRECTORY},
		# then alter it (not compulsory)
		file(RELATIVE_PATH SRCGR ${relDir} ${f})
		set(SRCGR "${baseDir}/${SRCGR}")
		# Extract the folder, ie remove the filename part
		string(REGEX REPLACE "(.*)(/[^/]*)$" "\\1" SRCGR ${SRCGR})
		# do not have any ../ dirs
		string(REPLACE "../" "" SRCGR ${SRCGR})
		# Source_group expects \\ (double antislash), not / (slash)
		string(REPLACE / \\ SRCGR ${SRCGR})
		#STRING(REPLACE "//" "/" SRCGR ${SRCGR})
		#message(STATUS "FILE: ${f} -> ${SRCGR}")
		source_group("${SRCGR}" FILES ${f})
	endforeach()
endmacro()


macro(csharp_generateFiltersForFiles relDir baseDir files)
	foreach(f ${files})
		# Get the path of the file relative to ${DIRECTORY},
		# then alter it (not compulsory)
		file(RELATIVE_PATH SRCGR ${relDir} ${f})
		set(SRCGR "${baseDir}/${SRCGR}")
		# Extract the folder, ie remove the filename part
		string(REGEX REPLACE "(.*)(/[^/]*)$" "\\1" SRCGR ${SRCGR})
		# do not have any ../ dirs
		string(REPLACE "../" "" SRCGR ${SRCGR})
		# Source_group expects \\ (double antislash), not / (slash)
		string(REPLACE / \\ SRCGR ${SRCGR})
		#STRING(REPLACE "//" "/" SRCGR ${SRCGR})
		#message(STATUS "FILE: ${f} -> ${SRCGR}")
		source_group("${SRCGR}" FILES ${f})
	endforeach()
endmacro()

# macro to add a static library
macro(csharp_addLibrary)
	# more paths?
	if(${ARGC} GREATER 0)
		foreach(dir ${ARGV0})
			addPath("${dir}")
		endforeach()
	endif()
	# now inspect the paths we got
	set(firstDir "")
	foreach(dir ${${CSHARP_LIBRARY_NAME}_paths})
		if("${firstDir}" STREQUAL "")
			set(firstDir "${dir}")
		endif()
	endforeach()

	# set per target compile flags
	add_library("${CSHARP_LIBRARY_NAME}" SHARED ${${CSHARP_LIBRARY_NAME}_files})
endmacro()

# --------------------
# -- Projects
# --------------------

#set(CSHARP_LIBRARY_NAME "T3DSharpFramework")
#csharp_addPathRec("${libDir}/t3dsharp/${CSHARP_LIBRARY_NAME}")
#csharp_generateFilters("${libDir}/t3dsharp/${CSHARP_LIBRARY_NAME}" "Engine")
#csharp_addLibrary()
#set_property(TARGET ${CSHARP_LIBRARY_NAME} PROPERTY VS_GLOBAL_TargetFramework "netcoreapp3.1")

#set_property(TARGET ${CSHARP_LIBRARY_NAME} PROPERTY VS_DOTNET_REFERENCES
#	"Microsoft.CSharp"
#)
#set_property(TARGET ${CSHARP_LIBRARY_NAME} PROPERTY VS_GLOBAL_AllowUnsafeBlocks "true")


#set(CSHARP_LIBRARY_NAME "T3DSharpGenerator")
#csharp_addPathRec("${libDir}/t3dsharp/${CSHARP_LIBRARY_NAME}")
#csharp_generateFilters("${libDir}/t3dsharp/${CSHARP_LIBRARY_NAME}" "Engine")
#csharp_addLibrary()
#set_property(TARGET ${CSHARP_LIBRARY_NAME} PROPERTY VS_GLOBAL_TargetFramework "netcoreapp3.1")

#set_property(TARGET ${CSHARP_LIBRARY_NAME} PROPERTY VS_DOTNET_REFERENCES
#	"Microsoft.CSharp"
#)
#target_link_libraries(${CSHARP_LIBRARY_NAME} T3DSharpFramework)
#"PresentationCore"
#"PresentationFramework"
#"System"
#"System.Core"
#"System.Data"
#"System.Data.DataSetExtensions"
#"System.Net.Http"
#"System.Xaml"
#"System.Xml"
#"System.Xml.Linq"
#"WindowsBase")

#set(CSHARP_LIBRARY_NAME "T3DSharpGame")
#csharp_addPathRec("${libDir}/t3dsharp/${CSHARP_LIBRARY_NAME}")
#csharp_generateFilters("${libDir}/t3dsharp/${CSHARP_LIBRARY_NAME}" "Engine")
#csharp_addPathRec("${projectOutDir}")
#csharp_generateFiltersForFiles("${projectOutDir}" "Game" "${tmp_files}")
#csharp_addLibrary()
#target_link_libraries(${CSHARP_LIBRARY_NAME} Framework)
#set_property(TARGET ${CSHARP_LIBRARY_NAME} PROPERTY VS_GLOBAL_TargetFramework "netcoreapp3.1")

#set(CMAKE_CSharp_FLAGS "/langversion:8")

configure_file(
	"${libDir}/t3dsharp/T3DSharpGenerator/T3DSharpGenerator.csproj.in"
	"${CMAKE_CURRENT_BINARY_DIR}/t3dsharp/T3DSharpGenerator/T3DSharpGenerator.csproj"
)
include_external_msproject(
T3DSharpGenerator "${CMAKE_CURRENT_BINARY_DIR}/t3dsharp/T3DSharpGenerator/T3DSharpGenerator.csproj"
TYPE FAE04EC0-301F-11D3-BF4B-00C04F79EFBC
PLATFORM "Any CPU")

set_target_properties(T3DSharpGenerator PROPERTIES 
	MAP_IMPORTED_CONFIG_RELEASE Release
	MAP_IMPORTED_CONFIG_MINSIZEREL Release
	MAP_IMPORTED_CONFIG_RELWITHDEBINFO Release
	MAP_IMPORTED_CONFIG_DEBUG Debug
	)
	
configure_file(
	"${libDir}/t3dsharp/T3DSharpFramework/T3DSharpFramework.csproj.in"
	"${CMAKE_CURRENT_BINARY_DIR}/t3dsharp/T3DSharpFramework/T3DSharpFramework.csproj"
)
include_external_msproject(
T3DSharpFramework "${CMAKE_CURRENT_BINARY_DIR}/t3dsharp/T3DSharpFramework/T3DSharpFramework.csproj"
TYPE FAE04EC0-301F-11D3-BF4B-00C04F79EFBC
PLATFORM "Any CPU")

set_target_properties(T3DSharpFramework PROPERTIES 
	MAP_IMPORTED_CONFIG_RELEASE Release
	MAP_IMPORTED_CONFIG_MINSIZEREL Release
	MAP_IMPORTED_CONFIG_RELWITHDEBINFO Release
	MAP_IMPORTED_CONFIG_DEBUG Debug
	)

configure_file(
	"${libDir}/t3dsharp/T3DSharpGame/T3DSharpGame.csproj.in"
	"${CMAKE_CURRENT_BINARY_DIR}/t3dsharp/T3DSharpGame/T3DSharpGame.csproj"
)
include_external_msproject(
T3DSharpGame "${CMAKE_CURRENT_BINARY_DIR}/t3dsharp/T3DSharpGame/T3DSharpGame.csproj"
TYPE FAE04EC0-301F-11D3-BF4B-00C04F79EFBC
PLATFORM "Any CPU")

set_target_properties(T3DSharpGame PROPERTIES 
	MAP_IMPORTED_CONFIG_RELEASE Release
	MAP_IMPORTED_CONFIG_MINSIZEREL Release
	MAP_IMPORTED_CONFIG_RELWITHDEBINFO Release
	MAP_IMPORTED_CONFIG_DEBUG Debug
	)

#project(T3DSharpGame VERSION 0.1.0 LANGUAGES CSharp)

#csharp_addPathRec("${libDir}/t3dsharp/T3DSharpGame")
#csharp_finishLibrary()
#target_link_libraries(${PROJECT_NAME} T3DSharpFramework)

#configure_file("${libDir}/t3dsharp/T3DSharpGame/T3DSharpGame.csproj" T3DSharpGame.csproj)
#include_external_msproject(
#T3DSharpGame "${CMAKE_CURRENT_BINARY_DIR}/T3DSharpGame.csproj"
#TYPE FAE04EC0-301F-11D3-BF4B-00C04F79EFBC)

