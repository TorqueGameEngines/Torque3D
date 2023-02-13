
//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~~//
// Arcane-FX - PIXEL SHADER
//
// afxZodiac_Polysoup_P.glsl
//   This is the pixel shader for rendering zodiacs on polysoup models.
//   
// Copyright (C) Faust Logic, Inc.
//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~~//

uniform sampler2D zodiacMap;
uniform vec4 zodiacColor;

in vec4 hpos;
in vec2 texCoord;

out vec4 OUT_FragColor0;
//~~~~~~~~~~~~~~~~~~~~//

void main()
{
   OUT_FragColor0 = zodiacColor*texture(zodiacMap, texCoord);
}

//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~~//
