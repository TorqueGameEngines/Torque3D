#pragma once
#include <arm_neon.h>

namespace
{
   typedef float32x4_t f32x4;

   //------------------------------------------------------
   // Load / Store
   //------------------------------------------------------
   inline f32x4 v_load(const float* p) { return vld1q_f32(p); }
   inline void v_store(float* dst, f32x4 v) { vst1q_f32(dst, v); }
   inline f32x4 v_set1(float s) { return vdupq_n_f32(s); }
   inline f32x4 v_zero() { return vdupq_n_f32(0.0f); }
   inline float v_extract0(f32x4 v) { return vgetq_lane_f32(v, 0); }

   //------------------------------------------------------
   // Mask helpers
   //------------------------------------------------------
   inline f32x4 v_mask_xyz()
   {
      // equivalent to [1,1,1,0]
      float32x4_t mask = {1.0f, 1.0f, 1.0f, 0.0f};
      return mask;
   }

   inline f32x4 v_preserve_w(f32x4 newv, f32x4 original)
   {
      float32x4_t mask = {0.0f, 0.0f, 0.0f, 1.0f};
      return vbslq_f32(vreinterpretq_u32_f32(mask), original, newv);
   }

   //------------------------------------------------------
   // Float3 helpers
   //------------------------------------------------------
   inline f32x4 v_load3_vec(const float* p) // w = 0
   {
      float tmp[4] = { p[0], p[1], p[2], 0.0f };
      return vld1q_f32(tmp);
   }

   inline f32x4 v_load3_pos(const float* p) // w = 1
   {
      float tmp[4] = { p[0], p[1], p[2], 1.0f };
      return vld1q_f32(tmp);
   }

   inline void v_store3(float* dst, f32x4 v)
   {
      float tmp[4];
      vst1q_f32(tmp, v);
      dst[0] = tmp[0];
      dst[1] = tmp[1];
      dst[2] = tmp[2];
   }

   //------------------------------------------------------
   // Simple Arithmetic
   //------------------------------------------------------
   inline f32x4 v_mul(f32x4 a, f32x4 b) { return vmulq_f32(a, b); }
   inline f32x4 v_div_exact(f32x4 a, f32x4 b) { return vdivq_f32(a, b); } // only NEON64
   inline f32x4 v_add(f32x4 a, f32x4 b) { return vaddq_f32(a, b); }
   inline f32x4 v_sub(f32x4 a, f32x4 b) { return vsubq_f32(a, b); }

   //------------------------------------------------------
   // Fast recip
   //------------------------------------------------------
   inline f32x4 v_rcp_nr(f32x4 b)
   {
      f32x4 r = vrecpeq_f32(b);
      r = vmulq_f32(r, vrecpsq_f32(b, r)); // Newton-Raphson
      r = vmulq_f32(r, vrecpsq_f32(b, r));
      return r;
   }

   inline f32x4 v_div(f32x4 a, f32x4 b)
   {
      return vmulq_f32(a, v_rcp_nr(b));
   }

   inline f32x4 v_rsqrt_nr(f32x4 x)
   {
      f32x4 r = vrsqrteq_f32(x);
      r = vmulq_f32(r, vrsqrtsq_f32(vmulq_f32(r,r), x)); // refine
      r = vmulq_f32(r, vrsqrtsq_f32(vmulq_f32(r,r), x));
      return r;
   }

   //------------------------------------------------------
   // Vector intrinsic functions
   //------------------------------------------------------
   inline f32x4 v_dot4(f32x4 a, f32x4 b)
   {
      f32x4 mul = vmulq_f32(a, b);
      float32x2_t sum2 = vpadd_f32(vget_low_f32(mul), vget_high_f32(mul));
      float sum = vget_lane_f32(sum2, 0) + vget_lane_f32(sum2, 1);
      return vdupq_n_f32(sum);
   }

   inline f32x4 v_dot3(f32x4 a, f32x4 b)
   {
      float32x4_t mask = {1.0f, 1.0f, 1.0f, 0.0f};
      f32x4 mul = vmulq_f32(a, b);
      mul = vmulq_f32(mul, mask);
      float32x2_t sum2 = vpadd_f32(vget_low_f32(mul), vget_high_f32(mul));
      float sum = vget_lane_f32(sum2, 0) + vget_lane_f32(sum2, 1);
      return vdupq_n_f32(sum);
   }

   inline f32x4 v_cross(f32x4 a, f32x4 b)
   {
      float32x4_t a_yzx = { vgetq_lane_f32(a,1), vgetq_lane_f32(a,2), vgetq_lane_f32(a,0), 0 };
      float32x4_t b_yzx = { vgetq_lane_f32(b,1), vgetq_lane_f32(b,2), vgetq_lane_f32(b,0), 0 };
      float32x4_t c = vsubq_f32(vmulq_f32(a, b_yzx), vmulq_f32(a_yzx, b));
      return (float32x4_t){ vgetq_lane_f32(c,2), vgetq_lane_f32(c,0), vgetq_lane_f32(c,1), 0 };
   }

   inline f32x4 v_normalize3(f32x4 v)
   {
      f32x4 inv = v_rsqrt_nr(v_dot3(v,v));
      return vmulq_f32(v, inv);
   }

   inline f32x4 v_hadd4(f32x4 a)
   {
      float32x2_t sum2 = vpadd_f32(vget_low_f32(a), vget_high_f32(a));
      float sum = vget_lane_f32(sum2,0) + vget_lane_f32(sum2,1);
      return vdupq_n_f32(sum);
   }
}
