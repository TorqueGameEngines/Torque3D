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
# -- Projects
# --------------------

macro(add_csproject name path)

	include_external_msproject(
		${name} "${path}"
		TYPE FAE04EC0-301F-11D3-BF4B-00C04F79EFBC
		PLATFORM "Any CPU"
	)

	set_target_properties(${name} PROPERTIES 
		MAP_IMPORTED_CONFIG_RELEASE Release
		MAP_IMPORTED_CONFIG_MINSIZEREL Release
		MAP_IMPORTED_CONFIG_RELWITHDEBINFO Release
		MAP_IMPORTED_CONFIG_DEBUG Debug
		)
	
	set_target_properties(${name} PROPERTIES FOLDER "Managed")

endmacro()

macro(set_relative_csharp_framework_path src_path)
file(RELATIVE_PATH CSHARP_FRAMEWORK_REL_PATH ${src_path} "${CSHARP_FRAMEWORK_PATH}")

endmacro()

	
configure_file(
	"${libDir}/t3dsharp/T3DSharpFramework/T3DSharpFramework.csproj.in"
	"${CMAKE_CURRENT_BINARY_DIR}/t3dsharp/T3DSharpFramework/T3DSharpFramework.csproj"
)
add_csproject(T3DSharpFramework "${CMAKE_CURRENT_BINARY_DIR}/t3dsharp/T3DSharpFramework/T3DSharpFramework.csproj")
set(CSHARP_FRAMEWORK_PATH "${CMAKE_CURRENT_BINARY_DIR}/t3dsharp/T3DSharpFramework/T3DSharpFramework.csproj")

set_relative_csharp_framework_path("${CMAKE_CURRENT_BINARY_DIR}/t3dsharp/T3DSharpGenerator")
configure_file(
	"${libDir}/t3dsharp/T3DSharpGenerator/T3DSharpGenerator.csproj.in"
	"${CMAKE_CURRENT_BINARY_DIR}/t3dsharp/T3DSharpGenerator/T3DSharpGenerator.csproj"
)
add_csproject(T3DSharpGenerator "${CMAKE_CURRENT_BINARY_DIR}/t3dsharp/T3DSharpGenerator/T3DSharpGenerator.csproj")

#####
# Add .csproj templates
#####


set(tmp_files "")

file(GLOB_RECURSE tmp_files ${projectOutDir}/*.csproj.in)

foreach(entry ${BLACKLIST})
	list(REMOVE_ITEM tmp_files ${dir}/${entry})
endforeach()

foreach(f ${tmp_files})
string(REGEX REPLACE "(.*)/([^/]*)$" "\\1" tmp_folder ${f})
string(REGEX REPLACE "(.*)/([^/]*)$" "\\2" tmp_file ${f})
string(REGEX REPLACE "(.*)\.in$" "\\1" tmp_target ${tmp_file})
string(REGEX REPLACE "(.*)\.csproj\.in$" "\\1" tmp_project_name ${tmp_file})

set_relative_csharp_framework_path("${tmp_folder}")
configure_file(
	"${tmp_folder}/${tmp_file}"
	"${tmp_folder}/${tmp_target}"
)
add_csproject(${tmp_project_name} "${tmp_folder}/${tmp_target}")
LIST(APPEND TEMPLATED_CSPROJ_FILES "${tmp_folder}/${tmp_target}")
LIST(APPEND CSPROJ_FILES "${tmp_folder}/${tmp_target}")
endforeach()

#####
# Add .csproj
#####

set(tmp_files "")

file(GLOB_RECURSE tmp_files ${projectOutDir}/*.csproj)

foreach(entry ${BLACKLIST})
	list(REMOVE_ITEM tmp_files ${projectOutDir}/${entry})
endforeach()

foreach(entry ${TEMPLATED_CSPROJ_FILES})
	list(REMOVE_ITEM tmp_files ${entry})
endforeach()

foreach(f ${tmp_files})
string(REGEX REPLACE "(.*)/([^/]*)$" "\\1" tmp_folder ${f})
string(REGEX REPLACE "(.*)/([^/]*)$" "\\2" tmp_file ${f})

set_relative_csharp_framework_path("${tmp_folder}")
add_csproject(${tmp_project_name} "${tmp_folder}/${tmp_file}")
LIST(APPEND CSPROJ_FILES "${tmp_folder}/${tmp_target}")
endforeach()

#####
# Add game
#####

foreach(f ${CSPROJ_FILES})

file(RELATIVE_PATH tmp_rel_path "${CMAKE_CURRENT_BINARY_DIR}/t3dsharp/T3DSharpGame" "${f}")
set(GAME_INCLUDES "${GAME_INCLUDES} \n\
      <ProjectReference Include=\"${tmp_rel_path}\"> \n\
        <Private>true</Private> \n\
      </ProjectReference> \n\
")
endforeach()

set_relative_csharp_framework_path("${CMAKE_CURRENT_BINARY_DIR}/t3dsharp/T3DSharpGame")
configure_file(
	"${libDir}/t3dsharp/T3DSharpGame/T3DSharpGame.csproj.in"
	"${CMAKE_CURRENT_BINARY_DIR}/t3dsharp/T3DSharpGame/T3DSharpGame.csproj"
)
add_csproject(T3DSharpGame "${CMAKE_CURRENT_BINARY_DIR}/t3dsharp/T3DSharpGame/T3DSharpGame.csproj")