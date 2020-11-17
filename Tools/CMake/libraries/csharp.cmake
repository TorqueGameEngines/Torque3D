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
	MAP_IMPORTED_CONFIG_RELWITHDEBINFO Debug
	MAP_IMPORTED_CONFIG_DEBUG Debug
	)


