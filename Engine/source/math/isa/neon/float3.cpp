#include "neon_intrinsics.h"
#include "float3_dispatch.h"

#include "float3_impl.inl"

namespace math_backend::float3::dispatch
{
    // Install NEON backend
    void install_neon()
    {
        gFloat3.add = float3_add_impl;
        gFloat3.sub = float3_sub_impl;
        gFloat3.mul = float3_mul_impl;
        gFloat3.mul_scalar = float3_mul_scalar_impl;
        gFloat3.div = float3_div_impl;
        gFloat3.div_scalar = float3_div_scalar_impl;
        gFloat3.dot = float3_dot_impl;
        gFloat3.length = float3_length_impl;
        gFloat3.lengthSquared = float3_length_squared_impl;
        gFloat3.normalize = float3_normalize_impl;
        gFloat3.normalize_mag = float3_normalize_mag_impl;
        gFloat3.lerp = float3_lerp_impl;
        gFloat3.cross = float3_cross_impl;
    }
}
