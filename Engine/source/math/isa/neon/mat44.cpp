#include "neon_intrinsics.h"
#include "mat44_dispatch.h"

#include "mat44_impl.inl"

namespace math_backend::mat44::dispatch
{
   void install_neon()
   {
      gMat44.transpose        = mat44_transpose_impl;
      gMat44.inverse          = mat44_inverse_impl;
      gMat44.inverse_to       = mat44_inverse_to_impl;
      gMat44.affine_inverse   = mat44_affine_inverse_impl;
      gMat44.mul_mat44        = mat44_mul_mat44_impl;
      gMat44.mul_pos3         = mat44_mul_pos3_impl;
      gMat44.mul_vec3         = mat44_mul_vec3_impl;
      gMat44.mul_float4       = mat44_mul_float4_impl;
      gMat44.scale            = mat44_scale_impl;
      gMat44.get_scale        = mat44_get_scale_impl;
      gMat44.normalize        = mat44_normalize_impl;
      gMat44.determinant      = mat44_get_determinant;
   }
}
