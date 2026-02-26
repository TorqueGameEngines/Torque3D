
#include "float4_dispatch.h"
#include <immintrin.h> // AVX/AVX2 intrinsics

namespace
{
   typedef __m128 f32x4;

   // Load 4 floats from memory into a SIMD register
   inline f32x4 v_load(const float* p) { return _mm_loadu_ps(p); }

   // Store 4 floats from SIMD register back to memory
   inline void v_store(float* dst, f32x4 v) { _mm_storeu_ps(dst, v); }

   // Broadcast a single float across all 4 lanes
   inline f32x4 v_set1(float s) { return _mm_set1_ps(s); }

   // Element-wise multiply
   inline f32x4 v_mul(f32x4 a, f32x4 b) { return _mm_mul_ps(a, b); }

   // Element-wise divide
   inline f32x4 v_div(f32x4 a, f32x4 b) { return _mm_div_ps(a, b); }

   // Element-wise add
   inline f32x4 v_add(f32x4 a, f32x4 b) { return _mm_add_ps(a, b); }

   // Element-wise subtract
   inline f32x4 v_sub(f32x4 a, f32x4 b) { return _mm_sub_ps(a, b); }

   // Horizontal sum of all 4 elements (for dot product, length, etc.)
   inline float v_hadd4(f32x4 a)
   {
      __m128 t1 = _mm_hadd_ps(a, a);  // sums pairs: [a0+a1, a2+a3, ...]
      __m128 t2 = _mm_hadd_ps(t1, t1); // sums again: first element = a0+a1+a2+a3
      return _mm_cvtss_f32(t2);       // extract first element
   }
}

#include "float4_impl.inl"

namespace math_backend::float4::dispatch
{
   // Install AVX2 backend
   void install_avx2()
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
      gFloat4.lerp         = float4_lerp_impl;
   }
}
