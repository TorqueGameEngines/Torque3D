#include "float4_dispatch.h"
#include <arm_neon.h>

namespace
{
    typedef float32x4_t f32x4;

    inline f32x4 v_load(const float* p)        { return vld1q_f32(p); }
    inline void  v_store(float* dst, f32x4 v)  { vst1q_f32(dst, v); }
    inline f32x4 v_set1(float s)               { return vdupq_n_f32(s); }

    inline f32x4 v_mul(f32x4 a, f32x4 b) { return vmulq_f32(a, b); }
    inline f32x4 v_add(f32x4 a, f32x4 b) { return vaddq_f32(a, b); }
    inline f32x4 v_sub(f32x4 a, f32x4 b) { return vsubq_f32(a, b); }

    // AArch64 native divide
    inline f32x4 v_div(f32x4 a, f32x4 b)
    {
        return vdivq_f32(a, b);
    }

    inline float v_hadd4(f32x4 a)
    {
        float32x2_t low  = vget_low_f32(a);
        float32x2_t high = vget_high_f32(a);
        float32x2_t sum  = vadd_f32(low, high);
        sum = vpadd_f32(sum, sum);
        return vget_lane_f32(sum, 0);
    }
}

#include "../../impl/float4_impl.inl"

namespace math_backend::float4::dispatch
{
    void install_neon()
    {
        gFloat4.add           = float4_add_impl;
        gFloat4.sub           = float4_sub_impl;
        gFloat4.mul           = float4_mul_impl;
        gFloat4.mul_scalar    = float4_mul_scalar_impl;
        gFloat4.div           = float4_div_impl;
        gFloat4.div_scalar    = float4_div_scalar_impl;
        gFloat4.dot           = float4_dot_impl;
        gFloat4.length        = float4_length_impl;
        gFloat4.lengthSquared = float4_length_squared_impl;
        gFloat4.normalize     = float4_normalize_impl;
        gFloat4.lerp          = float4_lerp_impl;
    }
}
