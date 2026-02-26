#pragma once
#include <cmath>   // for sqrtf, etc.
#include "../mConstants.h"

namespace math_backend::float4
{

   //----------------------------------------------------------
   // Add two float4 vectors: r = a + b
   inline void float4_add_impl(const float* a, const float* b, float* r)
   {
      f32x4 va = v_load(a);
      f32x4 vb = v_load(b);
      f32x4 vr = v_add(va, vb);
      v_store(r, vr);
   }

   // Subtract: r = a - b
   inline void float4_sub_impl(const float* a, const float* b, float* r)
   {
      f32x4 va = v_load(a);
      f32x4 vb = v_load(b);
      f32x4 vr = v_sub(va, vb);
      v_store(r, vr);
   }

   // Multiply element-wise: r = a * b
   inline void float4_mul_impl(const float* a, const float* b, float* r)
   {
      f32x4 va = v_load(a);
      f32x4 vb = v_load(b);
      f32x4 vr = v_mul(va, vb);
      v_store(r, vr);
   }

   // Multiply by scalar: r = a * s
   inline void float4_mul_scalar_impl(const float* a, float s, float* r)
   {
      f32x4 va = v_load(a);
      f32x4 vs = v_set1(s);
      f32x4 vr = v_mul(va, vs);
      v_store(r, vr);
   }

   // Divide element-wise: r = a / b
   inline void float4_div_impl(const float* a, const float* b, float* r)
   {
      f32x4 va = v_load(a);
      f32x4 vb = v_load(b);
      f32x4 vr = v_div(va, vb);
      v_store(r, vr);
   }

   // Divide by scalar: r = a / s
   inline void float4_div_scalar_impl(const float* a, float s, float* r)
   {
      f32x4 va = v_load(a);
      f32x4 vs = v_set1(s);
      f32x4 vr = v_div(va, vs);
      v_store(r, vr);
   }

   // Dot product: returns scalar
   inline float float4_dot_impl(const float* a, const float* b)
   {
      f32x4 va = v_load(a);
      f32x4 vb = v_load(b);
      f32x4 vdot = v_dot4(va, vb);   // calls ISA-specific implementation
      return v_extract0(vdot);
   }

   // Length squared
   inline float float4_length_squared_impl(const float* a)
   {
      return float4_dot_impl(a, a);
   }

   // Length
   inline float float4_length_impl(const float* a)
   {
      return std::sqrt(float4_length_squared_impl(a));
   }

   // Normalize in-place
   inline void float4_normalize_impl(float* a)
   {
      f32x4 va = v_load(a);
      f32x4 invLen = v_rsqrt_nr(v_dot4(va, va)); // fully abstracted
      f32x4 vnorm = v_mul(va, invLen);
      v_store(a, vnorm);
   }

   // Normalize with magnitude: r = normalize(a) * r
   inline void float4_normalize_mag_impl(float* a, float r)
   {
      f32x4 va = v_load(a);

      // invLen = r / sqrt(dot(a,a)) = r * rsqrt(dot(a,a))
      f32x4 invLen = v_mul(v_set1(r), v_rsqrt_nr(v_dot4(va, va)));

      f32x4 vnorm = v_mul(va, invLen);
      v_store(a, vnorm);
   }

   // Linear interpolation: r = from + (to - from) * f
   inline void float4_lerp_impl(const float* from, const float* to, float f, float* r)
   {
      f32x4 vfrom = v_load(from);
      f32x4 vto = v_load(to);
      f32x4 vf = v_set1(f);
      f32x4 vr = v_add(vfrom, v_mul(vf, v_sub(vto, vfrom)));
      v_store(r, vr);
   }

   inline void float4_cross_impl(const float* a, const float* b, float* r)
   {
      f32x4 va = v_load(a);
      f32x4 vb = v_load(b);
      f32x4 vcross = v_cross(va, vb);
      v_store(r, vcross);
   }

} // namespace math_backend::float4
