//-----------------------------------------------------------------------------
// Copyright (c) 2012 GarageGames, LLC
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//-----------------------------------------------------------------------------

#include "core/rendering/shaders/torque.hlsl"
#include "core/rendering/shaders/postFX/postFx.hlsl"

#if QUALITY == 3

static const int KERNEL_SAMPLES = 64;
static const float3 KERNEL[64] = {
	float3(0.015625, 0.000000, 0.017183),
	float3(-0.023043, 0.021109, 0.017183),
	float3(0.004098, -0.046696, 0.017183),
	float3(0.038027, 0.049600, 0.017183),
	float3(-0.076931, -0.013608, 0.017183),
	float3(0.079102, -0.050318, 0.017182),
	float3(-0.028394, 0.105625, 0.017182),
	float3(-0.057613, -0.110931, 0.017181),
	float3(0.132092, 0.048240, 0.017180),
	float3(-0.144429, 0.059618, 0.017178),
	float3(0.072849, -0.155673, 0.017175),
	float3(0.056116, 0.178906, 0.017172),
	float3(-0.175746, -0.101848, 0.017168),
	float3(0.213648, -0.046970, 0.017163),
	float3(-0.134796, 0.191733, 0.017157),
	float3(-0.032128, -0.247927, 0.017149),
	float3(0.203110, 0.171181, 0.017140),
	float3(-0.281010, 0.011621, 0.017129),
	float3(0.210434, -0.209410, 0.017116),
	float3(-0.014435, 0.312166, 0.017101),
	float3(-0.210233, -0.251929, 0.017084),
	float3(0.340680, 0.045838, 0.017063),
	float3(-0.294996, 0.205251, 0.017040),
	float3(0.082306, -0.365856, 0.017014),
	float3(0.194211, 0.338925, 0.016984),
	float3(-0.387031, -0.123474, 0.016951),
	float3(0.382974, -0.176944, 0.016913),
	float3(-0.168902, 0.403582, 0.016871),
	float3(-0.153361, -0.426383, 0.016825),
	float3(0.414933, 0.218077, 0.016773),
	float3(-0.468376, 0.123462, 0.016717),
	float3(0.270419, -0.420563, 0.016654),
	float3(0.087335, 0.508175, 0.016586),
	float3(-0.420019, -0.325286, 0.016512),
	float3(0.545008, -0.045153, 0.016431),
	float3(-0.381982, 0.412911, 0.016344),
	float3(0.002820, -0.578118, 0.016250),
	float3(0.398932, 0.439764, 0.016148),
	float3(-0.606775, -0.056236, 0.016038),
	float3(0.497850, -0.377850, 0.015921),
	float3(-0.114661, 0.630280, 0.015795),
	float3(-0.349522, -0.555426, 0.015661),
	float3(0.647981, 0.177585, 0.015518),
	float3(-0.611659, 0.313893, 0.015367),
	float3(0.244418, -0.659276, 0.015206),
	float3(0.270999, 0.665703, 0.015037),
	float3(-0.663622, -0.314503, 0.014857),
	float3(0.716710, -0.220969, 0.014669),
	float3(-0.387117, 0.660547, 0.014471),
	float3(-0.164025, -0.763837, 0.014263),
	float3(0.649650, 0.461481, 0.014045),
	float3(-0.806263, 0.100483, 0.013819),
	float3(0.536765, -0.630614, 0.013582),
	float3(0.030749, 0.843190, 0.013337),
	float3(-0.603207, -0.612100, 0.013082),
	float3(0.873858, 0.044681, 0.012818),
	float3(-0.686583, 0.567289, 0.012545),
	float3(0.125226, -0.897556, 0.012264),
	float3(0.522814, 0.759288, 0.011975),
	float3(-0.913626, -0.210223, 0.011678),
	float3(0.829278, -0.469836, 0.011373),
	float3(-0.298936, 0.921474, 0.011062),
	float3(-0.408505, -0.895610, 0.010745),
	float3(0.920579, 0.390557, 0.010422)
};

#elif QUALITY == 2

static const int KERNEL_SAMPLES = 32;
static const float3 KERNEL[32] = {
	float3(0.031250, 0.000000, 0.034485),
	float3(-0.046086, 0.042218, 0.034485),
	float3(0.008196, -0.093391, 0.034484),
	float3(0.076055, 0.099200, 0.034481),
	float3(-0.153861, -0.027216, 0.034475),
	float3(0.158204, -0.100637, 0.034464),
	float3(-0.056788, 0.211250, 0.034446),
	float3(-0.115227, -0.221862, 0.034418),
	float3(0.264184, 0.096480, 0.034378),
	float3(-0.288858, 0.119236, 0.034321),
	float3(0.145697, -0.311346, 0.034245),
	float3(0.112231, 0.357812, 0.034146),
	float3(-0.351492, -0.203697, 0.034019),
	float3(0.427296, -0.093940, 0.033859),
	float3(-0.269592, 0.383467, 0.033663),
	float3(-0.064255, -0.495854, 0.033424),
	float3(0.406220, 0.342362, 0.033139),
	float3(-0.562020, 0.023241, 0.032802),
	float3(0.420867, -0.418819, 0.032408),
	float3(-0.028870, 0.624333, 0.031952),
	float3(-0.420465, -0.503858, 0.031431),
	float3(0.681360, 0.091676, 0.030841),
	float3(-0.589992, 0.410501, 0.030178),
	float3(0.164611, -0.731713, 0.029439),
	float3(0.388423, 0.677849, 0.028625),
	float3(-0.774063, -0.246947, 0.027733),
	float3(0.765949, -0.353888, 0.026766),
	float3(-0.337803, 0.807164, 0.025725),
	float3(-0.306722, -0.852766, 0.024613),
	float3(0.829865, 0.436154, 0.023437),
	float3(-0.936752, 0.246925, 0.022202),
	float3(0.540838, -0.841127, 0.020916)
};

#elif QUALITY == 1

static const int KERNEL_SAMPLES = 16;
static const float3 KERNEL[16] = {
	float3(0.062500, 0.000000, 0.069464),
	float3(-0.092171, 0.084436, 0.069456),
	float3(0.016392, -0.186782, 0.069422),
	float3(0.152110, 0.198400, 0.069329),
	float3(-0.307723, -0.054432, 0.069134),
	float3(0.316408, -0.201273, 0.068781),
	float3(-0.113577, 0.422500, 0.068204),
	float3(-0.230454, -0.443724, 0.067328),
	float3(0.528368, 0.192959, 0.066073),
	float3(-0.577716, 0.238473, 0.064362),
	float3(0.291394, -0.622692, 0.062123),
	float3(0.224463, 0.715623, 0.059300),
	float3(-0.702984, -0.407394, 0.055864),
	float3(0.854591, -0.187880, 0.051818),
	float3(-0.539184, 0.766934, 0.047209),
	float3(-0.128511, -0.991708, 0.042133)
};

#elif QUALITY == 0

static const int KERNEL_SAMPLES = 9;
static const float3 KERNEL[9] = {
	float3( 0, 0, 0.25),
	float3( 1, 0, 0.125),
	float3( 0, 1, 0.125),
	float3(-1, 0, 0.125),
	float3( 0,-1, 0.125),
	float3( 0.707, 0.707, 0.0625),
	float3( 0.707,-0.707, 0.0625),
	float3(-0.707,-0.707, 0.0625),
	float3(-0.707, 0.707, 0.0625)
};

#endif

TORQUE_UNIFORM_SAMPLER2D(inputTex, 0);
uniform float blurRadius;
uniform int numSteps;
uniform float2 oneOverTargetSize;

float4 main(PFXVertToPix IN) : TORQUE_TARGET0
{
	float4 upSample = float4(0, 0, 0, 0);
	float radStep = blurRadius / float(numSteps);
	
	const float alpha = M_2PI_F / float(numSteps);
	
	[unroll]
	for (int i=0; i<KERNEL_SAMPLES; i++)
	{
		float3 offsetW = KERNEL[i];
		for (int j=0; j<numSteps; j++)
		{
			float angle = alpha * float(j);
			float2 angles = float2(cos(angle), sin(angle));
			float rad = radStep * float(j+1);
			float2 offset = float2(
				offsetW.x*angles.x - offsetW.y*angles.y,
				offsetW.x*angles.y + offsetW.y*angles.x
			) * oneOverTargetSize * rad;
			
			float4 sampleCol = TORQUE_TEX2D(inputTex, IN.uv0 + offset);
			upSample += sampleCol * offsetW.z;
		}
	}
	
	return upSample * (1.0f / float(numSteps));
}
