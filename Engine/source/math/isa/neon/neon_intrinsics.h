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

   inline f32x4 v_set(float x, float y, float z, float w)
   {
       return { x, y, z, w }; // lane0=x, lane1=y, lane2=z, lane3=w
   }

   inline f32x4 v_insert_w(f32x4 v, f32x4 w)
   {
       // extract scalar value from w lane0
       float w_val = vgetq_lane_f32(w, 0);

       // broadcast w_val to all lanes (we only need lane3 later)
       f32x4 w_broadcast = vdupq_n_f32(w_val);

       // mask to select only lane3
       uint32x4_t mask = {0, 0, 0, 0xFFFFFFFF};

       // vbslq: if mask bit=1, take from first argument, else take from second
       return vbslq_f32(mask, w_broadcast, v);
   }

   //------------------------------------------------------
   // Mask helpers
   //------------------------------------------------------
   inline f32x4 v_mask_xyz()
   {
       uint32x4_t mask = {
           0xFFFFFFFF,
           0xFFFFFFFF,
           0xFFFFFFFF,
           0x00000000
       };

       return vreinterpretq_f32_u32(mask);
   }

   inline f32x4 v_and(f32x4 a, f32x4 b)
   {
       return vreinterpretq_f32_u32(
           vandq_u32(
               vreinterpretq_u32_f32(a),
               vreinterpretq_u32_f32(b)
           )
       );
   }

   inline f32x4 v_swizzle_singular_mask(f32x4 v, int x)
   {
       // base byte index of the float lane
       uint8x16_t base = vdupq_n_u8((uint8_t)(x * 4));

       // byte offsets inside a float (0,1,2,3 repeated 4 times)
       const uint8x16_t offsets = {
           0,1,2,3,  0,1,2,3,
           0,1,2,3,  0,1,2,3
       };

       uint8x16_t idx = vaddq_u8(base, offsets);

       return vreinterpretq_f32_u8(
           vqtbl1q_u8(
               vreinterpretq_u8_f32(v),
               idx
           )
       );
   }

   inline f32x4 v_swizzle_lo(f32x4 v)
   {
       float32x4x2_t t = vzipq_f32(v, v);
       return t.val[0];   // [x, x, z, z]
   }

   inline f32x4 v_swizzle_hi(f32x4 v)
   {
       float32x4x2_t t = vzipq_f32(v, v);
       return t.val[1];   // [y, y, w, w]
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
      f32x4 a_yzx = { vgetq_lane_f32(a,1),
                    vgetq_lane_f32(a,2),
                    vgetq_lane_f32(a,0),
                    0.0f };

      f32x4 b_zxy = { vgetq_lane_f32(b,2),
                    vgetq_lane_f32(b,0),
                    vgetq_lane_f32(b,1),
                    0.0f };

      f32x4 a_zxy = { vgetq_lane_f32(a,2),
                    vgetq_lane_f32(a,0),
                    vgetq_lane_f32(a,1),
                    0.0f };

      f32x4 b_yzx = { vgetq_lane_f32(b,1),
                    vgetq_lane_f32(b,2),
                    vgetq_lane_f32(b,0),
                    0.0f };

      return vsubq_f32(
        vmulq_f32(a_yzx, b_zxy),
        vmulq_f32(a_zxy, b_yzx)
      );
   }

   inline f32x4 v_normalize3(f32x4 v)
   {
      const float32x4_t zero = vdupq_n_f32(0.0f);
      const float32x4_t fallback = {0.0f, 0.0f, 1.0f, 0.0f};

      f32x4 dot = v_dot3(v, v);

      // dot == 0?
      uint32x4_t isZero = vceqq_f32(dot, zero);

      f32x4 inv = v_rsqrt_nr(dot);
      f32x4 norm = vmulq_f32(v, inv);

      // Select fallback when zero
      return vbslq_f32(isZero, fallback, norm);
   }

   inline f32x4 v_hadd4(f32x4 a)
   {
      float32x2_t sum2 = vpadd_f32(vget_low_f32(a), vget_high_f32(a));
      float sum = vget_lane_f32(sum2,0) + vget_lane_f32(sum2,1);
      return vdupq_n_f32(sum);
   }


   //------------------------------------------------------
   // Matrix type (row-major 4x4)
   //------------------------------------------------------

   struct f32x4x4
   {
       f32x4 r0;
       f32x4 r1;
       f32x4 r2;
       f32x4 r3;
   };

   inline f32x4x4 m_load(const float* m) // expects 16 floats (row-major)
   {
       f32x4x4 out;
       out.r0 = v_load(m + 0);
       out.r1 = v_load(m + 4);
       out.r2 = v_load(m + 8);
       out.r3 = v_load(m + 12);
       return out;
   }

   inline void m_store(float* dst, const f32x4x4& m)
   {
       v_store(dst + 0,  m.r0);
       v_store(dst + 4,  m.r1);
       v_store(dst + 8,  m.r2);
       v_store(dst + 12, m.r3);
   }

   inline f32x4x4 m_identity()
   {
       f32x4x4 m;
       m.r0 = {1,0,0,0};
       m.r1 = {0,1,0,0};
       m.r2 = {0,0,1,0};
       m.r3 = {0,0,0,1};
       return m;
   }

   inline f32x4x4 m_zero()
   {
       f32x4 z = v_zero();
       return { z, z, z, z };
   }

   inline f32x4 m_mul_vec4(const f32x4x4& m, f32x4 v)
   {
       f32x4 x = v_dot4(m.r0, v);
       f32x4 y = v_dot4(m.r1, v);
       f32x4 z = v_dot4(m.r2, v);
       f32x4 w = v_dot4(m.r3, v);

       return {
           v_extract0(x),
           v_extract0(y),
           v_extract0(z),
           v_extract0(w)
       };
   }

   inline f32x4 m_mul_vec3(const f32x4x4& m, f32x4 v)
   {
       f32x4 x = v_dot3(m.r0, v);
       f32x4 y = v_dot3(m.r1, v);
       f32x4 z = v_dot3(m.r2, v);

       return {
           v_extract0(x),
           v_extract0(y),
           v_extract0(z),
           0.0f
       };
   }

   inline f32x4x4 m_transpose(const f32x4x4& m)
   {
       float32x4x2_t t0 = vtrnq_f32(m.r0, m.r1);
       float32x4x2_t t1 = vtrnq_f32(m.r2, m.r3);

       float32x2_t a0 = vget_low_f32(t0.val[0]);
       float32x2_t a1 = vget_high_f32(t0.val[0]);
       float32x2_t a2 = vget_low_f32(t1.val[0]);
       float32x2_t a3 = vget_high_f32(t1.val[0]);

       float32x2_t b0 = vget_low_f32(t0.val[1]);
       float32x2_t b1 = vget_high_f32(t0.val[1]);
       float32x2_t b2 = vget_low_f32(t1.val[1]);
       float32x2_t b3 = vget_high_f32(t1.val[1]);

       f32x4x4 out;

       out.r0 = vcombine_f32(a0, a2);
       out.r1 = vcombine_f32(b0, b2);
       out.r2 = vcombine_f32(a1, a3);
       out.r3 = vcombine_f32(b1, b3);

       return out;
   }

   inline f32x4x4 m_mul(const f32x4x4& a, const f32x4x4& b)
   {
       f32x4x4 bt = m_transpose(b);

       auto mul_row = [&](f32x4 row)
       {
           f32x4 x = v_dot4(row, bt.r0);
           f32x4 y = v_dot4(row, bt.r1);
           f32x4 z = v_dot4(row, bt.r2);
           f32x4 w = v_dot4(row, bt.r3);

           return f32x4{
               v_extract0(x),
               v_extract0(y),
               v_extract0(z),
               v_extract0(w)
           };
       };

       f32x4x4 C;
       C.r0 = mul_row(a.r0);
       C.r1 = mul_row(a.r1);
       C.r2 = mul_row(a.r2);
       C.r3 = mul_row(a.r3);

       return C;
   }

   inline f32x4 m_determinant(const f32x4x4& m)
   {
       f32x4 a = m.r0;
       f32x4 b = m.r1;
       f32x4 c = m.r2;
       f32x4 d = m.r3;

       f32x4 c0 = v_cross(c, d);
       f32x4 c1 = v_cross(d, b);
       f32x4 c2 = v_cross(b, c);

       f32x4 term0 = vmulq_f32(a, c0);
       f32x4 term1 = vmulq_f32(a, c1);
       f32x4 term2 = vmulq_f32(a, c2);

       f32x4 det = vaddq_f32(term0, vaddq_f32(term1, term2));

       return v_hadd4(det);
   }

   inline f32x4 m_determinant_affine(const f32x4x4& m)
   {
       f32x4 r0 = v_and(m.r0, v_mask_xyz());
       f32x4 r1 = v_and(m.r1, v_mask_xyz());
       f32x4 r2 = v_and(m.r2, v_mask_xyz());

       f32x4 c0 = v_cross(r1, r2);
       return v_dot3(r0, c0);
   }

   inline f32x4x4 m_inverse(const f32x4x4& m)
   {
       f32x4 a = m.r0;
       f32x4 b = m.r1;
       f32x4 c = m.r2;
       f32x4 d = m.r3;

       f32x4 c0 = v_cross(b, c);
       f32x4 c1 = v_cross(c, d);
       f32x4 c2 = v_cross(d, a);
       f32x4 c3 = v_cross(a, b);

       f32x4 det = v_dot4(a, c1);
       f32x4 invDet = v_rcp_nr(det);

       f32x4x4 adj;
       adj.r0 = vmulq_f32(c1, invDet);
       adj.r1 = vmulq_f32(c2, invDet);
       adj.r2 = vmulq_f32(c3, invDet);
       adj.r3 = vmulq_f32(c0, invDet);

       return m_transpose(adj);
   }

   struct vec4_batch4
   {
      f32x4 x;
      f32x4 y;
      f32x4 z;
      f32x4 w;
   };

   inline vec4_batch4 load_vec3_batch4(const float* ptr, float w, bool fillW)
   {
      vec4_batch4 r;

      r.x = (f32x4){ ptr[0], ptr[3], ptr[6], ptr[9] };
      r.y = (f32x4){ ptr[1], ptr[4], ptr[7], ptr[10] };
      r.z = (f32x4){ ptr[2], ptr[5], ptr[8], ptr[11] };

      if (fillW)
      {
         r.w = vdupq_n_f32(w);
      }

      return r;
   }

   inline void store_vec3_batch4(float* out, const vec4_batch4& v)
   {
      alignas(16) float xs[4];
      alignas(16) float ys[4];
      alignas(16) float zs[4];

      vst1q_f32(xs, v.x);
      vst1q_f32(ys, v.y);
      vst1q_f32(zs, v.z);

      for (int i = 0; i < 4; ++i)
      {
         out[i * 3 + 0] = xs[i];
         out[i * 3 + 1] = ys[i];
         out[i * 3 + 2] = zs[i];
      }
   }

   inline vec4_batch4 m_mul_pos3_batch4(const float* m, const vec4_batch4& v)
   {
      vec4_batch4 r;

      float32x4_t m00 = vdupq_n_f32(m[0]);
      float32x4_t m01 = vdupq_n_f32(m[1]);
      float32x4_t m02 = vdupq_n_f32(m[2]);
      float32x4_t m03 = vdupq_n_f32(m[3]);

      float32x4_t m10 = vdupq_n_f32(m[4]);
      float32x4_t m11 = vdupq_n_f32(m[5]);
      float32x4_t m12 = vdupq_n_f32(m[6]);
      float32x4_t m13 = vdupq_n_f32(m[7]);

      float32x4_t m20 = vdupq_n_f32(m[8]);
      float32x4_t m21 = vdupq_n_f32(m[9]);
      float32x4_t m22 = vdupq_n_f32(m[10]);
      float32x4_t m23 = vdupq_n_f32(m[11]);

      // row0 dot
      r.x = vaddq_f32(
         vaddq_f32(
            vmulq_f32(v.x, m00),
            vmulq_f32(v.y, m01)),
         vaddq_f32(
            vmulq_f32(v.z, m02),
            m03));

      // row1 dot
      r.y = vaddq_f32(
         vaddq_f32(
            vmulq_f32(v.x, m10),
            vmulq_f32(v.y, m11)),
         vaddq_f32(
            vmulq_f32(v.z, m12),
            m13));

      // row2 dot
      r.z = vaddq_f32(
         vaddq_f32(
            vmulq_f32(v.x, m20),
            vmulq_f32(v.y, m21)),
         vaddq_f32(
            vmulq_f32(v.z, m22),
            m23));

      return r;
   }

}
