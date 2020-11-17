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

option(TORQUE_CSHARP "Enable C# Scripting" OFF)
if(TORQUE_CSHARP)
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
		LIST(APPEND ${PROJECT_NAME}_files "${tmp_files}")
		LIST(APPEND ${PROJECT_NAME}_paths "${dir}")
		#message(STATUS "addPath ${PROJECT_NAME} : ${tmp_files}")
	endmacro()

	# adds a file to the sources
	macro(csharp_addFile filename)
		LIST(APPEND ${PROJECT_NAME}_files "${filename}")
		#message(STATUS "addFile ${PROJECT_NAME} : ${filename}")
	endmacro()

	# finds and adds sources files in a folder recursively
	macro(csharp_addPathRec dir)
		csharp_addPath("${dir}" "REC")
	endmacro()
	
	macro(csharp_generateFilters relDir baseDir)
		foreach(f ${${PROJECT_NAME}_files})
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
	macro(csharp_finishLibrary)
		# more paths?
		if(${ARGC} GREATER 0)
			foreach(dir ${ARGV0})
				addPath("${dir}")
			endforeach()
		endif()
		# now inspect the paths we got
		set(firstDir "")
		foreach(dir ${${PROJECT_NAME}_paths})
			if("${firstDir}" STREQUAL "")
				set(firstDir "${dir}")
			endif()
		endforeach()

		# set per target compile flags
		add_library("${PROJECT_NAME}" SHARED ${${PROJECT_NAME}_files})
	endmacro()

	# --------------------
	# -- Projects
	# --------------------
	
	
    set(cached_project_name ${PROJECT_NAME})


	project(T3DSharpFramework VERSION 0.1.0 LANGUAGES CSharp)
	
	csharp_addPathRec("${libDir}/t3dsharp/T3DSharpFramework")
	csharp_generateFilters("${libDir}/t3dsharp/T3DSharpFramework" "Engine")
	csharp_finishLibrary()
	set_property(TARGET T3DSharpFramework PROPERTY VS_GLOBAL_TargetFramework "netcoreapp3.1")
	
	set_property(TARGET T3DSharpFramework PROPERTY VS_DOTNET_REFERENCES
		"Microsoft.CSharp"
	)
	#set_property(TARGET T3DSharpFramework PROPERTY VS_GLOBAL_AllowUnsafeBlocks "true")
	
	
	project(T3DSharpGenerator VERSION 0.1.0 LANGUAGES CSharp)
	
	csharp_addPathRec("${libDir}/t3dsharp/T3DSharpGenerator")
	csharp_generateFilters("${libDir}/t3dsharp/T3DSharpGenerator" "Engine")
	csharp_finishLibrary()
	set_property(TARGET T3DSharpGenerator PROPERTY VS_GLOBAL_TargetFramework "netcoreapp3.1")
	
	set_property(TARGET T3DSharpGenerator PROPERTY VS_DOTNET_REFERENCES
		"Microsoft.CSharp"
	)
	target_link_libraries(T3DSharpGenerator T3DSharpFramework)
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

	project(T3DSharpGame VERSION 0.1.0 LANGUAGES CSharp)
	
	csharp_addPathRec("${libDir}/t3dsharp/T3DSharpGame")
	csharp_generateFilters("${libDir}/t3dsharp/T3DSharpGame" "Engine")
	csharp_addPathRec("${projectOutDir}")
	csharp_generateFiltersForFiles("${projectOutDir}" "Game" "${tmp_files}")
	csharp_finishLibrary()
	target_link_libraries(T3DSharpGame T3DSharpFramework)
	set_property(TARGET T3DSharpGame PROPERTY VS_GLOBAL_TargetFramework "netcoreapp3.1")
	
	set(CMAKE_CSharp_FLAGS "/langversion:8")
	
	#configure_file(
#		"${libDir}/t3dsharp/T3DSharpGenerator/T3DSharpGenerator.csproj.in"
		#"${libDir}/t3dsharp/T3DSharpGenerator/T3DSharpGenerator.csproj"
	#)
	#include_external_msproject(
    #T3DSharpGenerator "${libDir}/t3dsharp/T3DSharpGenerator/T3DSharpGenerator.csproj"
    #TYPE FAE04EC0-301F-11D3-BF4B-00C04F79EFBC)
	
	#include_external_msproject(
    #T3DSharpFramework "${libDir}/t3dsharp/T3DSharpFramework/T3DSharpFramework.csproj"
    #TYPE FAE04EC0-301F-11D3-BF4B-00C04F79EFBC)
	
	#project(T3DSharpGame VERSION 0.1.0 LANGUAGES CSharp)
	
	#csharp_addPathRec("${libDir}/t3dsharp/T3DSharpGame")
	#csharp_finishLibrary()
	#target_link_libraries(${PROJECT_NAME} T3DSharpFramework)
	
	#configure_file("${libDir}/t3dsharp/T3DSharpGame/T3DSharpGame.csproj" T3DSharpGame.csproj)
	#include_external_msproject(
    #T3DSharpGame "${CMAKE_CURRENT_BINARY_DIR}/T3DSharpGame.csproj"
    #TYPE FAE04EC0-301F-11D3-BF4B-00C04F79EFBC)
	
	set(TORQUE_LIBRARY ON)
	project(${cached_project_name})
endif()
