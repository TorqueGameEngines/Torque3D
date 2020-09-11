#include "core/rendering/shaders/gl/torque.glsl"
#include "core/rendering/shaders/gl/hlslCompat.glsl"
#include "shadergen:/autogenConditioners.h"
#include "core/rendering/shaders/postFX/gl/postFX.glsl"

uniform sampler2D inputTex;

out vec4 OUT_col;

void main()
{
   OUT_col = hdrEncode( vec4(1,1,1,1) );
}
