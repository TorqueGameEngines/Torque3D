#include "neon_intrinsics.h"
#include "float4_dispatch.h"

#include "float4_impl.inl"

namespace math_backend::float4::dispatch
{
    // Install NEON64 backend
    void install_neon()
    {
        gFloat4.add          = float4_add_impl;
        gFloat4.sub          = float4_sub_impl;
        gFloat4.mul          = float4_mul_impl;
        gFloat4.mul_scalar   = float4_mul_scalar_impl;
        gFloat4.div          = float4_div_impl;
        gFloat4.div_scalar   = float4_div_scalar_impl;
        gFloat4.dot          = float4_dot_impl;
        gFloat4.length       = float4_length_impl;
        gFloat4.lengthSquared = float4_length_squared_impl;
        gFloat4.normalize    = float4_normalize_impl;
        gFloat4.normalize_mag = float4_normalize_mag_impl;
        gFloat4.lerp         = float4_lerp_impl;
        gFloat4.cross        = float4_cross_impl;
    }
}
