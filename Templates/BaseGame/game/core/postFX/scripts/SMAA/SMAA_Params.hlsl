uniform float2 oneOverTargetSize;
uniform float2 targetSize;

#define SMAA_RT_METRICS float4(oneOverTargetSize, targetSize)


//Used for defining SMAA params
#define SMAA_HLSL_4 1
#define SMAA_PREDICATION 0

#include "SMAA.h"





