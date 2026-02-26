#pragma once
#include <emmintrin.h>  // SSE2
#include <xmmintrin.h>  // SSE

namespace
{
   typedef __m128 f32x4;

   //------------------------------------------------------
   // Load / Store
   //------------------------------------------------------

   // Load 4 floats from memory into a SIMD register
   inline f32x4 v_load(const float* p) { return _mm_loadu_ps(p); }

   inline void v_store(float* dst, f32x4 v) { _mm_storeu_ps(dst, v); }

   inline f32x4 v_set1(float s) { return _mm_set1_ps(s); }

   inline f32x4 v_zero() { return _mm_setzero_ps(); }

   inline float v_extract0(f32x4 v) { return _mm_cvtss_f32(v); }

   //------------------------------------------------------
   // Float3 helpers (safe loading into 4 lanes)
   //------------------------------------------------------

   inline f32x4 v_load3_vec(const float* p) // w = 0
   {
      return _mm_set_ps(0.0f, p[2], p[1], p[0]);
   }

   inline f32x4 v_load3_pos(const float* p) // w = 1
   {
      return _mm_set_ps(1.0f, p[2], p[1], p[0]);
   }

   inline void v_store3(float* dst, f32x4 v)
   {
      alignas(16) float tmp[4];   // temp storage
      _mm_store_ps(tmp, v);        // store all 4 lanes
      dst[0] = tmp[0];
      dst[1] = tmp[1];
      dst[2] = tmp[2];
   }

   //------------------------------------------------------
   // Mask helpers
   //------------------------------------------------------

   inline f32x4 v_mask_xyz() { return _mm_castsi128_ps(_mm_set_epi32(0, -1, -1, -1)); }

   inline f32x4 v_preserve_w(f32x4 newv, f32x4 original)
   {
      f32x4 mask = _mm_castsi128_ps(_mm_set_epi32(-1, 0, 0, 0));
      return _mm_or_ps(_mm_and_ps(mask, original), _mm_andnot_ps(mask, newv));
   }


   //------------------------------------------------------
   // Simple Arithmatic
   //------------------------------------------------------

   // Element-wise multiply
   inline f32x4 v_mul(f32x4 a, f32x4 b) { return _mm_mul_ps(a, b); }

   // Element-wise divide
   inline f32x4 v_div_exact(f32x4 a, f32x4 b) { return _mm_div_ps(a, b); }

   // Element-wise add
   inline f32x4 v_add(f32x4 a, f32x4 b) { return _mm_add_ps(a, b); }

   // Element-wise subtract
   inline f32x4 v_sub(f32x4 a, f32x4 b) { return _mm_sub_ps(a, b); }

   //------------------------------------------------------
   // Fast recip
   //------------------------------------------------------

   // Fast recip 1/b
   inline f32x4 v_rcp_nr(f32x4 b)
   {
      f32x4 r = _mm_rcp_ps(b);
      f32x4 two = _mm_set1_ps(2.0f);
      return _mm_mul_ps(r, _mm_sub_ps(two, _mm_mul_ps(b, r)));
   }

   // Divide fast ( b = recip eg 1/b)
   inline f32x4 v_div(f32x4 a, f32x4 b) { return _mm_mul_ps(a, v_rcp_nr(b)); }

   inline f32x4 v_rsqrt_nr(f32x4 x)
   {
      f32x4 r = _mm_rsqrt_ps(x);

      f32x4 half = _mm_set1_ps(0.5f);
      f32x4 three = _mm_set1_ps(3.0f);

      r = _mm_mul_ps(r, _mm_sub_ps(three, _mm_mul_ps(_mm_mul_ps(x, r), r)));

      return _mm_mul_ps(r, half);
   }

   //------------------------------------------------------
   // Vector intrinsic functions
   //------------------------------------------------------

   // full dot4
   inline f32x4 v_dot4(f32x4 a, f32x4 b)
   {
      f32x4 prod = _mm_mul_ps(a, b);           // multiply element-wise
      f32x4 shuf = _mm_shuffle_ps(prod, prod, _MM_SHUFFLE(2, 3, 0, 1));
      prod = _mm_add_ps(prod, shuf);
      shuf = _mm_shuffle_ps(prod, prod, _MM_SHUFFLE(1, 0, 3, 2));
      prod = _mm_add_ps(prod, shuf);
      return prod;                             // f32x4, all lanes = dot(a,b)
   }

   // dot3 (ignores w)
   inline f32x4 v_dot3(f32x4 a, f32x4 b)
   {
      f32x4 prod = _mm_mul_ps(a, b);
      prod = _mm_and_ps(prod, v_mask_xyz());    // zero w
      f32x4 shuf = _mm_shuffle_ps(prod, prod, _MM_SHUFFLE(2, 3, 0, 1));
      prod = _mm_add_ps(prod, shuf);
      shuf = _mm_shuffle_ps(prod, prod, _MM_SHUFFLE(1, 0, 3, 2));
      prod = _mm_add_ps(prod, shuf);
      return prod;                             // f32x4, all lanes = dot(a,b)
   }

   // cross product xyz only.
   inline f32x4 v_cross(f32x4 a, f32x4 b)
   {
      f32x4 a_yzx = _mm_shuffle_ps(a, a, _MM_SHUFFLE(3, 0, 2, 1));
      f32x4 b_yzx = _mm_shuffle_ps(b, b, _MM_SHUFFLE(3, 0, 2, 1));

      f32x4 c = _mm_sub_ps( _mm_mul_ps(a, b_yzx), _mm_mul_ps(a_yzx, b));

      return _mm_shuffle_ps(c, c, _MM_SHUFFLE(3, 0, 2, 1));
   }

   inline f32x4 v_normalize3(f32x4 v)
   {
      f32x4 inv = v_rsqrt_nr(v_dot3(v, v));
      return _mm_mul_ps(v, inv);
   }

   // adds all 4 lanes together.
   inline f32x4 v_hadd4(f32x4 a)
   {
      // sum all 4 lanes in SSE2
      __m128 shuf = _mm_shuffle_ps(a, a, _MM_SHUFFLE(2, 3, 0, 1)); // swap pairs
      __m128 sums = _mm_add_ps(a, shuf);
      shuf = _mm_shuffle_ps(sums, sums, _MM_SHUFFLE(1, 0, 3, 2));
      return _mm_add_ps(sums, shuf);
   }
}
