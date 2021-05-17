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

cmake_minimum_required(VERSION 3.14)
project(csharp)
include(FetchContent)

FetchContent_Declare(
	T3DSharp
	GIT_REPOSITORY "https://github.com/lukaspj/T3DSharp"
	GIT_TAG "origin/master"
)

FetchContent_MakeAvailable(T3DSharp)
mark_as_advanced(FETCHCONTENT_BASE_DIR)
mark_as_advanced(FETCHCONTENT_FULLY_DISCONNECTED)
mark_as_advanced(FETCHCONTENT_QUIET)
mark_as_advanced(FETCHCONTENT_SOURCE_DIR_T3DSHARP)
mark_as_advanced(FETCHCONTENT_UPDATES_DISCONNECTED)
mark_as_advanced(FETCHCONTENT_UPDATES_DISCONNECTED_T3DSHARP)

set(CSHARP_SOURCE_DIR "${t3dsharp_SOURCE_DIR}")
set(CSHARP_OUTPUT_DIR "${t3dsharp_SOURCE_DIR}")
set(CSHARP_SOLUTION_NAME "T3DSharpSolution")
set(CSHARP_SOLUTION_PATH "${CSHARP_SOURCE_DIR}/${CSHARP_SOLUTION_NAME}.sln")

# --------------------
# -- Solution 
# --------------------
if(NOT MSVC)
   FILE(REMOVE "${CSHARP_SOLUTION_PATH}")
   execute_process(
      COMMAND dotnet new sln --name ${CSHARP_SOLUTION_NAME}
      WORKING_DIRECTORY ${CSHARP_SOURCE_DIR}
   )
   add_custom_target(__T3DSHARP_SOLUTION ALL
      COMMAND dotnet build ${CSHARP_SOLUTION_PATH} -o ${projectOutDir}
   )
endif()

# --------------------
# -- Projects
# --------------------
macro(add_csproject name path)
   if(MSVC)
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
   else()
      execute_process(
         COMMAND dotnet sln ${CSHARP_SOLUTION_PATH} add ${path}
      )
   endif()
endmacro()

macro(set_relative_csharp_framework_path src_path)
	file(RELATIVE_PATH CSHARP_FRAMEWORK_REL_PATH ${src_path} "${CSHARP_FRAMEWORK_PATH}")
endmacro()

macro(configure_file_if_not_exists src_path tgt_path)
	if(NOT EXISTS ${tgt_path})
		configure_file(${src_path} ${tgt_path})
	endif()
endmacro()

option(TORQUE_CSHARP_FRAMEWORK_GENERATED_DIR "Directory of the generated engine layer" "${CSHARP_OUTPUT_DIR}/T3DSharpFramework/Generated")
mark_as_advanced(TORQUE_CSHARP_FRAMEWORK_GENERATED_DIR)
set(CSHARP_FRAMEWORK_GENERATED_DIR "${CSHARP_SOURCE_DIR}/T3DSharpFramework/Generated")

if (EXISTS "${TORQUE_CSHARP_FRAMEWORK_GENERATED_DIR}" AND IS_DIRECTORY "${TORQUE_CSHARP_FRAMEWORK_GENERATED_DIR}")
	set(CSHARP_FRAMEWORK_GENERATED_DIR TORQUE_CSHARP_FRAMEWORK_GENERATED_DIR)
endif()

configure_file(
	"${CSHARP_SOURCE_DIR}/T3DSharpFramework/T3DSharpFramework.csproj.in"
	"${CSHARP_OUTPUT_DIR}/T3DSharpFramework/T3DSharpFramework.csproj"
)
add_csproject(T3DSharpFramework "${CSHARP_OUTPUT_DIR}/T3DSharpFramework/T3DSharpFramework.csproj")
set(CSHARP_FRAMEWORK_PATH "${CSHARP_OUTPUT_DIR}/T3DSharpFramework/T3DSharpFramework.csproj")

set_relative_csharp_framework_path("${CSHARP_SOURCE_DIR}/T3DSharpGenerator")

configure_file(
	"${CSHARP_SOURCE_DIR}/T3DSharpGenerator/T3DSharpGenerator.csproj.in"
	"${CSHARP_OUTPUT_DIR}/T3DSharpGenerator/T3DSharpGenerator.csproj"
)
add_csproject(T3DSharpGenerator "${CSHARP_OUTPUT_DIR}/T3DSharpGenerator/T3DSharpGenerator.csproj")

#####
# Configure .csproj templates
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
	configure_file_if_not_exists(
		"${tmp_folder}/${tmp_file}"
		"${tmp_folder}/${tmp_target}"
	)
	add_csproject("${tmp_project_name}" "${tmp_folder}/${tmp_target}")
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
	string(REGEX REPLACE "(.*)\.csproj$" "\\1" tmp_project_name ${tmp_file})

	set_relative_csharp_framework_path("${tmp_folder}")
	add_csproject("${tmp_project_name}" "${tmp_folder}/${tmp_file}")
	LIST(APPEND CSPROJ_FILES "${tmp_folder}/${tmp_file}")
endforeach()

#####
# Add game
#####

foreach(f ${CSPROJ_FILES})
	file(RELATIVE_PATH tmp_rel_path "${CSHARP_OUTPUT_DIR}/T3DSharpGame" "${f}")
	set(GAME_INCLUDES "${GAME_INCLUDES} \n\
		  <ProjectReference Include=\"${tmp_rel_path}\"> \n\
			<Private>true</Private> \n\
		  </ProjectReference> \n\
	")
endforeach()

if(MSVC)
    # Match projectGenerator naming for executables
    set(OUTPUT_CONFIG DEBUG MINSIZEREL RELWITHDEBINFO)
    set(OUTPUT_SUFFIX DEBUG MINSIZE    OPTIMIZEDDEBUG)
	set(CSHARP_TORQUE_LIBRARIES_STATEMENTS "#if RELEASE \n\
            Windows32bit = \"${TORQUE_APP_NAME}.dll\", \n\
            Windows64bit = \"${TORQUE_APP_NAME}.dll\"  \n\
"	)
    foreach(INDEX RANGE 2)
        list(GET OUTPUT_CONFIG ${INDEX} CONF)
        list(GET OUTPUT_SUFFIX ${INDEX} SUFFIX)
		set(CSHARP_TORQUE_LIBRARIES_STATEMENTS "${CSHARP_TORQUE_LIBRARIES_STATEMENTS}\
            #elif ${CONF} \n\
            Windows32bit = \"${TORQUE_APP_NAME}_${SUFFIX}.dll\", \n\
            Windows64bit = \"${TORQUE_APP_NAME}_${SUFFIX}.dll\"  \n\
"		)
    endforeach()
	set(CSHARP_TORQUE_LIBRARIES_STATEMENTS "${CSHARP_TORQUE_LIBRARIES_STATEMENTS}\
            #endif"	)
endif()

foreach(c ${CMAKE_CONFIGURATION_TYPES})
string(TOUPPER ${c} tmp_c_upper)
set(CSHARP_DEFINE_CONSTANTS "${CSHARP_DEFINE_CONSTANTS} \n\
   <PropertyGroup Condition=\"\'\$(Configuration)'=='${c}'\">\n\
     <DefineConstants>${tmp_c_upper}</DefineConstants>\n\
   </PropertyGroup>\n\
")
endforeach()

configure_file_if_not_exists(
	"${CSHARP_SOURCE_DIR}/T3DSharpGame/Program.cs.in"
	"${projectOutDir}/Program.cs"
)

set_relative_csharp_framework_path("${CSHARP_OUTPUT_DIR}/T3DSharpGame")

configure_file(
	"${CSHARP_SOURCE_DIR}/T3DSharpGame/T3DSharpGame.csproj.in"
	"${CSHARP_OUTPUT_DIR}/T3DSharpGame/T3DSharpGame.csproj"
)

add_csproject(T3DSharpGame "${CSHARP_OUTPUT_DIR}/T3DSharpGame/T3DSharpGame.csproj")

if (MSVC)
   set_target_properties(T3DSharpGame PROPERTIES 
      MAP_IMPORTED_CONFIG_RELEASE Release
      MAP_IMPORTED_CONFIG_MINSIZEREL MinSizeRel
      MAP_IMPORTED_CONFIG_RELWITHDEBINFO RelWithDebInfo
      MAP_IMPORTED_CONFIG_DEBUG Debug
      )
endif()