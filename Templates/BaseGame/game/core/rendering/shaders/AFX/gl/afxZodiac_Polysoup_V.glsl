
//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~~//
// Arcane-FX - VERTEX SHADER
//
// afxZodiac_Polysoup_V.glsl
//   This is the vertex shader for rendering zodiacs on polysoup models.
//   
// Copyright (C) Faust Logic, Inc.
//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~~//

#include "../../common/gl/hlslCompat.glsl"

uniform mat4 modelview;

out vec2 texCoord;

in vec4 vPosition;
in vec4 vColor;
in vec2 vTexCoord0;

//~~~~~~~~~~~~~~~~~~~~//

void main()
{
   texCoord = vTexCoord0.st;
   gl_Position = modelview * vPosition;
   correctSSP(gl_Position);
}

//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~~//
