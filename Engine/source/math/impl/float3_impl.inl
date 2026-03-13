#pragma once
#include <cmath>   // for sqrtf, etc.
#include "../mConstants.h"

// Safely loads a float3 -> simd 4 lane backend
namespace math_backend::float3
{
   //----------------------------------------------------------
   // Add two float4 vectors: r = a + b
   inline void float3_add_impl(const float* a, const float* b, float* r)
   {
      f32x4 va = v_load3_vec(a);
      f32x4 vb = v_load3_vec(b);
      f32x4 vr = v_add(va, vb);
      v_store3(r, vr);
   }

   // Subtract: r = a - b
   inline void float3_sub_impl(const float* a, const float* b, float* r)
   {
      f32x4 va = v_load3_vec(a);
      f32x4 vb = v_load3_vec(b);
      f32x4 vr = v_sub(va, vb);
      v_store3(r, vr);
   }

   // Multiply element-wise: r = a * b
   inline void float3_mul_impl(const float* a, const float* b, float* r)
   {
      f32x4 va = v_load3_vec(a);
      f32x4 vb = v_load3_vec(b);
      f32x4 vr = v_mul(va, vb);
      v_store3(r, vr);
   }

   // Multiply by scalar: r = a * s
   inline void float3_mul_scalar_impl(const float* a, float s, float* r)
   {
      f32x4 va = v_load3_vec(a);
      f32x4 vs = v_set1(s);
      f32x4 vr = v_mul(va, vs);
      v_store3(r, vr);
   }

   // Divide element-wise: r = a / b
   inline void float3_div_impl(const float* a, const float* b, float* r)
   {
      f32x4 va = v_load3_vec(a);
      f32x4 vb = v_load3_vec(b);
      f32x4 vr = v_div(va, vb);
      v_store3(r, vr);
   }

   // Divide by scalar: r = a / s
   inline void float3_div_scalar_impl(const float* a, float s, float* r)
   {
      f32x4 va = v_load3_vec(a);
      f32x4 vs = v_set1(s);
      f32x4 vr = v_div(va, vs);
      v_store3(r, vr);
   }

   // Dot product: returns scalar
   inline float float3_dot_impl(const float* a, const float* b)
   {
      f32x4 va = v_load3_vec(a);
      f32x4 vb = v_load3_vec(b);
      f32x4 vdot = v_dot3(va, vb);
      return v_extract0(vdot); // first lane is the sum of 3 elements
   }

   // Length squared
   inline float float3_length_squared_impl(const float* a)
   {
      return float3_dot_impl(a, a);
   }

   // Length
   inline float float3_length_impl(const float* a)
   {
      return std::sqrt(float3_length_squared_impl(a));
   }

   // Normalize in-place
   inline void float3_normalize_impl(float* a)
   {
      f32x4 va = v_load3_vec(a);
      f32x4 vr = v_normalize3(va);
      v_store3(a, vr);
   }

   // Normalize with magnitude: r = normalize(a) * r
   inline void float3_normalize_mag_impl(float* a, float r)
   {
      f32x4 va = v_load3_vec(a);

      // invLen = r / sqrt(dot(a,a)) = r * rsqrt(dot(a,a))
      f32x4 invLen = v_mul(v_set1(r), v_rsqrt_nr(v_dot3(va, va)));

      f32x4 vnorm = v_mul(va, invLen);
      v_store3(a, vnorm);
   }

   // Linear interpolation: r = from + (to - from) * f
   inline void float3_lerp_impl(const float* from, const float* to, float f, float* r)
   {
      f32x4 vfrom = v_load3_vec(from);
      f32x4 vto = v_load3_vec(to);
      f32x4 vf = v_set1(f);
      f32x4 vr = v_add(vfrom, v_mul(vf, v_sub(vto, vfrom)));
      v_store3(r, vr);
   }

   inline void float3_cross_impl(const float* a, const float* b, float* r)
   {
      f32x4 va = v_load3_vec(a);
      f32x4 vb = v_load3_vec(b);
      f32x4 vcross = v_cross(va, vb);
      v_store3(r, vcross);
   }

}
