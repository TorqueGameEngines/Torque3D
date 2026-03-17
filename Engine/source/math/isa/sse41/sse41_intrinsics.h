#pragma once
#include <smmintrin.h>  // SSE4.1

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
   // Mask helpers
   //------------------------------------------------------

   inline f32x4 v_mask_xyz() { return _mm_blend_ps(_mm_set1_ps(0.0f), _mm_set1_ps(1.0f), 0b0111); }

   inline f32x4 v_swizzle_mask(f32x4 v, int x, int y, int z, int w)
   {
      alignas(16) float tmp[4];
      _mm_store_ps(tmp, v);

      return _mm_set_ps(
         tmp[w],
         tmp[z],
         tmp[y],
         tmp[x]
      );
   }

   inline f32x4 v_swizzle_singular_mask(f32x4 v, int x)
   {
      alignas(16) float tmp[4];
      _mm_store_ps(tmp, v);
      return _mm_set1_ps(tmp[x]);
   }

   inline f32x4 v_swizzle_lo(f32x4 v1)
   {
      return _mm_moveldup_ps(v1);
   }

   inline f32x4 v_swizzle_hi(f32x4 v1)
   {
      return _mm_movehdup_ps(v1);
   }

   inline f32x4 v_preserve_w(f32x4 newv, f32x4 original)
   {
      return _mm_blend_ps(newv, original, 0b1000);
   }

   //------------------------------------------------------
   // Shuffle helpers
   //------------------------------------------------------

   inline f32x4 v_shuffle_mask(f32x4 v1, f32x4 v2, int x, int y, int z, int w)
   {
      alignas(16) float a[4], b[4];
      _mm_store_ps(a, v1);
      _mm_store_ps(b, v2);

      return _mm_set_ps(
         b[w],
         b[z],
         a[y],
         a[x]
      );
   }

   inline f32x4 v_shuffle_hilo(f32x4 v1, f32x4 v2)
   {
      return _mm_movelh_ps(v1, v2);
   }

   inline f32x4 v_shuffle_lohi(f32x4 v1, f32x4 v2)
   {
      return _mm_movehl_ps(v2, v1);
   }


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

   inline f32x4 v_set(float x, float y, float z, float w)
   {
      return _mm_set_ps(w, z, y, x);
   }

   inline f32x4 v_insert_w(f32x4 v, f32x4 w)
   {
      return _mm_insert_ps(v, w, 0x30);
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
      r = _mm_sub_ps(_mm_add_ps(r, r), _mm_mul_ps(b, _mm_mul_ps(r, r)));
      return _mm_sub_ps(_mm_add_ps(r, r), _mm_mul_ps(b, _mm_mul_ps(r, r)));
   }

   // Divide fast ( b = recip eg 1/b)
   inline f32x4 v_div(f32x4 a, f32x4 b) { return _mm_mul_ps(a, v_rcp_nr(b)); }

   inline f32x4 v_rsqrt_nr(f32x4 x)
   {
      f32x4 half = _mm_set1_ps(0.5f);
      f32x4 three = _mm_set1_ps(3.0f);

      f32x4 r = _mm_rsqrt_ps(x);
      f32x4 nr = _mm_mul_ps(_mm_mul_ps(x, r), r);
      return _mm_mul_ps(_mm_mul_ps(half, r), _mm_sub_ps(three, nr));
   }

   //------------------------------------------------------
   // Vector intrinsic functions
   //------------------------------------------------------

   // full dot4
   inline f32x4 v_dot4(f32x4 a, f32x4 b)
   {
      return _mm_dp_ps(a, b, 0xFF); // f32x4, 4 lanes into lane 1
   }

   // dot3 (ignores w)
   inline f32x4 v_dot3(f32x4 a, f32x4 b)
   {
      return _mm_dp_ps(a, b, 0x7F); // f32x4, 3 last lanes into lane 1
   }

   // cross product xyz only.
   inline f32x4 v_cross(f32x4 a, f32x4 b)
   {
      f32x4 a_yzx = _mm_shuffle_ps(a, a, _MM_SHUFFLE(3, 0, 2, 1));
      f32x4 b_yzx = _mm_shuffle_ps(b, b, _MM_SHUFFLE(3, 0, 2, 1));

      f32x4 c = _mm_sub_ps(_mm_mul_ps(a, b_yzx), _mm_mul_ps(a_yzx, b));

      return _mm_shuffle_ps(c, c, _MM_SHUFFLE(3, 0, 2, 1));
   }

   inline f32x4 v_normalize3(f32x4 v)
   {
      const f32x4 zero     = _mm_setzero_ps();
      const f32x4 fallback = _mm_set_ps(0.0f, 1.0f, 0.0f, 0.0f); // {0,0,1,0}
      f32x4 dot = v_dot3(v, v);

      f32x4 inv = v_rsqrt_nr(dot);
      f32x4 isZero = _mm_cmpeq_ps(dot, zero);
      f32x4 norm = _mm_mul_ps(v, inv);

      return _mm_blendv_ps(norm, fallback, isZero);
   }

   // adds all 4 lanes together.
   inline f32x4 v_hadd4(f32x4 a)
   {
      // sum all 4 lanes in SSE41
      __m128 sum = _mm_hadd_ps(a, a);
      return _mm_hadd_ps(sum, sum);
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

   //------------------------------------------------------
   // Matrix Load / Store
   //------------------------------------------------------

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
      _mm_storeu_ps(dst + 0, m.r0);
      _mm_storeu_ps(dst + 4, m.r1);
      _mm_storeu_ps(dst + 8, m.r2);
      _mm_storeu_ps(dst + 12, m.r3);
   }

   inline f32x4x4 m_identity()
   {
      f32x4x4 m;
      m.r0 = _mm_set_ps(0, 0, 0, 1);
      m.r1 = _mm_set_ps(0, 0, 1, 0);
      m.r2 = _mm_set_ps(0, 1, 0, 0);
      m.r3 = _mm_set_ps(1, 0, 0, 0);
      return m;
   }

   inline f32x4x4 m_zero()
   {
      f32x4 z = v_zero();
      return { z, z, z, z };
   }

   //------------------------------------------------------
   // Matrix × Vector
   //------------------------------------------------------

   inline f32x4 m_mul_vec4(const f32x4x4& m, f32x4 v)
   {
      f32x4 x = v_dot4(m.r0, v);
      f32x4 y = v_dot4(m.r1, v);
      f32x4 z = v_dot4(m.r2, v);
      f32x4 w = v_dot4(m.r3, v);

      // combine to a vector
      return _mm_set_ps(_mm_cvtss_f32(w),
                        _mm_cvtss_f32(z),
                        _mm_cvtss_f32(y),
                        _mm_cvtss_f32(x));
   }

   inline f32x4 m_mul_vec3(const f32x4x4& m, f32x4 v)
   {
      f32x4 x = v_dot3(m.r0, v);
      f32x4 y = v_dot3(m.r1, v);
      f32x4 z = v_dot3(m.r2, v);

      // combine to a vector
      return _mm_set_ps(0.0f,
         _mm_cvtss_f32(z),
         _mm_cvtss_f32(y),
         _mm_cvtss_f32(x));
   }

   //------------------------------------------------------
   // Matrix × Matrix
   //------------------------------------------------------

   inline f32x4x4 m_mul(const f32x4x4& a, const f32x4x4& b)
   {
      // Transpose B once for dot products
      f32x4 b0 = b.r0;
      f32x4 b1 = b.r1;
      f32x4 b2 = b.r2;
      f32x4 b3 = b.r3;

      // Transpose (SSE2)
      _MM_TRANSPOSE4_PS(b0, b1, b2, b3);

      f32x4x4 C;

      auto mul_row = [&](f32x4 arow)
      {
         f32x4 x = v_dot4(arow, b0);
         f32x4 y = v_dot4(arow, b1);
         f32x4 z = v_dot4(arow, b2);
         f32x4 w = v_dot4(arow, b3);

         f32x4 xy = _mm_unpacklo_ps(x, y);
         f32x4 zw = _mm_unpacklo_ps(z, w);
         return _mm_movelh_ps(xy, zw);
      };

      C.r0 = mul_row(a.r0);
      C.r1 = mul_row(a.r1);
      C.r2 = mul_row(a.r2);
      C.r3 = mul_row(a.r3);

      return C;
   }

   //------------------------------------------------------
   // Transpose
   //------------------------------------------------------

   inline f32x4x4 m_transpose(const f32x4x4& m)
   {
      f32x4 r0 = m.r0;
      f32x4 r1 = m.r1;
      f32x4 r2 = m.r2;
      f32x4 r3 = m.r3;

      _MM_TRANSPOSE4_PS(r0, r1, r2, r3);

      return { r0, r1, r2, r3 };
   }

   inline void m_set3x3_transpose(float* dst, f32x4 c0, f32x4 c1, f32x4 c2)
   {
      dst[0] = v_extract0(c0);            // c0.x
      dst[1] = v_extract0(c1);            // c1.x
      dst[2] = v_extract0(c2);            // c2.x

      dst[4] = _mm_cvtss_f32(_mm_shuffle_ps(c0, c0, _MM_SHUFFLE(3, 3, 3, 1))); // c0.y
      dst[5] = _mm_cvtss_f32(_mm_shuffle_ps(c1, c1, _MM_SHUFFLE(3, 3, 3, 1))); // c1.y
      dst[6] = _mm_cvtss_f32(_mm_shuffle_ps(c2, c2, _MM_SHUFFLE(3, 3, 3, 1))); // c2.y

      dst[8] = _mm_cvtss_f32(_mm_shuffle_ps(c0, c0, _MM_SHUFFLE(3, 3, 3, 2))); // c0.z
      dst[9] = _mm_cvtss_f32(_mm_shuffle_ps(c1, c1, _MM_SHUFFLE(3, 3, 3, 2))); // c1.z
      dst[10] = _mm_cvtss_f32(_mm_shuffle_ps(c2, c2, _MM_SHUFFLE(3, 3, 3, 2))); // c2.z
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
      adj.r0 = _mm_mul_ps(c1, invDet);
      adj.r1 = _mm_mul_ps(c2, invDet);
      adj.r2 = _mm_mul_ps(c3, invDet);
      adj.r3 = _mm_mul_ps(c0, invDet);

      return m_transpose(adj);
   }

   inline f32x4x4 m_inverse_rigid(const f32x4x4& m)
   {
      f32x4x4 t = m_transpose(m);

      // Extract translation
      f32x4 T = v_set(
         _mm_cvtss_f32(_mm_shuffle_ps(m.r0, m.r0, _MM_SHUFFLE(3, 3, 3, 3))),
         _mm_cvtss_f32(_mm_shuffle_ps(m.r1, m.r1, _MM_SHUFFLE(3, 3, 3, 3))),
         _mm_cvtss_f32(_mm_shuffle_ps(m.r2, m.r2, _MM_SHUFFLE(3, 3, 3, 3))),
         0.0f
      );

      f32x4 newT = m_mul_vec4(t, T);
      newT = _mm_sub_ps(v_zero(), newT);

      t.r0 = v_preserve_w(t.r0, newT);
      t.r1 = v_preserve_w(t.r1, newT);
      t.r2 = v_preserve_w(t.r2, newT);
      t.r3 = v_set(0, 0, 0, 1);

      return t;
   }

   inline f32x4x4 m_inverse_affine(const f32x4x4& m)
   {
      // Extract upper 3x3 rows
      f32x4 r0 = m.r0;
      f32x4 r1 = m.r1;
      f32x4 r2 = m.r2;

      // Zero translation
      r0 = _mm_and_ps(r0, v_mask_xyz());
      r1 = _mm_and_ps(r1, v_mask_xyz());
      r2 = _mm_and_ps(r2, v_mask_xyz());

      // Compute cofactors via cross products
      f32x4 c0 = v_cross(r1, r2);
      f32x4 c1 = v_cross(r2, r0);
      f32x4 c2 = v_cross(r0, r1);

      // Determinant
      f32x4 det = v_dot3(r0, c0);

      // Reciprocal determinant
      f32x4 invDet = v_rcp_nr(det);

      // Inverse 3x3 (transpose of cofactor matrix)
      f32x4 i0 = _mm_mul_ps(c0, invDet);
      f32x4 i1 = _mm_mul_ps(c1, invDet);
      f32x4 i2 = _mm_mul_ps(c2, invDet);

      // Transpose 3x3
      f32x4 t0 = i0;
      f32x4 t1 = i1;
      f32x4 t2 = i2;
      f32x4 t3 = _mm_setzero_ps();

      _MM_TRANSPOSE4_PS(t0, t1, t2, t3);

      // Extract translation
      alignas(16) float tmp[4];
      tmp[0] = _mm_cvtss_f32(_mm_shuffle_ps(m.r0, m.r0, _MM_SHUFFLE(3, 3, 3, 3)));
      tmp[1] = _mm_cvtss_f32(_mm_shuffle_ps(m.r1, m.r1, _MM_SHUFFLE(3, 3, 3, 3)));
      tmp[2] = _mm_cvtss_f32(_mm_shuffle_ps(m.r2, m.r2, _MM_SHUFFLE(3, 3, 3, 3)));
      tmp[3] = 0.0f;

      f32x4 T = v_load(tmp);

      // New translation = -R' * T
      f32x4 newT = m_mul_vec4({ t0, t1, t2, t3 }, T);
      newT = _mm_sub_ps(v_zero(), newT);

      // Assemble final matrix
      f32x4x4 out;
      out.r0 = v_preserve_w(t0, newT);
      out.r1 = v_preserve_w(t1, newT);
      out.r2 = v_preserve_w(t2, newT);
      out.r3 = _mm_set_ps(1, 0, 0, 0);

      return out;
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

      f32x4 term0 = _mm_mul_ps(a, c0);
      f32x4 term1 = _mm_mul_ps(a, c1);
      f32x4 term2 = _mm_mul_ps(a, c2);

      f32x4 det = _mm_add_ps(term0, _mm_add_ps(term1, term2));

      return v_hadd4(det);
   }

   inline f32x4 m_determinant_affine(const f32x4x4& m)
   {
      f32x4 r0 = m.r0;
      f32x4 r1 = m.r1;
      f32x4 r2 = m.r2;

      r0 = _mm_and_ps(r0, v_mask_xyz());
      r1 = _mm_and_ps(r1, v_mask_xyz());
      r2 = _mm_and_ps(r2, v_mask_xyz());

      f32x4 c0 = v_cross(r1, r2);
      return v_dot3(r0, c0); // splatted determinant
   }

   //---------------------------------------------------------
   // BATCH INTRINSICS
   //---------------------------------------------------------

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

      r.x = _mm_set_ps(
         ptr[9], ptr[6], ptr[3], ptr[0]);

      r.y = _mm_set_ps(
         ptr[10], ptr[7], ptr[4], ptr[1]);

      r.z = _mm_set_ps(
         ptr[11], ptr[8], ptr[5], ptr[2]);

      if (fillW)
      {
         r.w = _mm_set1_ps(w);
      }

      return r;
   }

   // Store the result back out to a float array 4 at a time
   inline void store_f32x4(float* out, f32x4 v)
   {
      _mm_storeu_ps(out, v);
   }

   // Store the result back to a float3 array with size of 4
   inline void store_vec3_batch4(float* out, const vec4_batch4& v)
   {
      alignas(16) float xs[8];
      alignas(16) float ys[8];
      alignas(16) float zs[8];

      _mm_store_ps(xs, v.x);
      _mm_store_ps(ys, v.y);
      _mm_store_ps(zs, v.z);

      for (int i = 0; i < 4; ++i)
      {
         out[i * 3 + 0] = xs[i];
         out[i * 3 + 1] = ys[i];
         out[i * 3 + 2] = zs[i];
      }
   }

   inline f32x4 vec3_batch4_dot(const vec4_batch4& a, const vec4_batch4& b)
   {
      f32x4 mulx = _mm_mul_ps(a.x, b.x);
      f32x4 muly = _mm_mul_ps(a.y, b.y);
      f32x4 mulz = _mm_mul_ps(a.z, b.z);

      return _mm_add_ps(_mm_add_ps(mulx, muly), mulz);
   }

   // Batch 4 mul_Vec4.
   inline vec4_batch4 m_mul_pos3_batch4(const float* m, const vec4_batch4& v)
   {
      vec4_batch4 r;

      f32x4 m00 = _mm_set1_ps(m[0]);
      f32x4 m01 = _mm_set1_ps(m[1]);
      f32x4 m02 = _mm_set1_ps(m[2]);
      f32x4 m03 = _mm_set1_ps(m[3]);

      f32x4 m10 = _mm_set1_ps(m[4]);
      f32x4 m11 = _mm_set1_ps(m[5]);
      f32x4 m12 = _mm_set1_ps(m[6]);
      f32x4 m13 = _mm_set1_ps(m[7]);

      f32x4 m20 = _mm_set1_ps(m[8]);
      f32x4 m21 = _mm_set1_ps(m[9]);
      f32x4 m22 = _mm_set1_ps(m[10]);
      f32x4 m23 = _mm_set1_ps(m[11]);

      //
      // row0 dot
      //
      r.x = _mm_add_ps(
         _mm_add_ps(
            _mm_mul_ps(v.x, m00),
            _mm_mul_ps(v.y, m01)),
         _mm_add_ps(
            _mm_mul_ps(v.z, m02), m03));

      //
      // row1 dot
      //
      r.y = _mm_add_ps(
         _mm_add_ps(
            _mm_mul_ps(v.x, m10),
            _mm_mul_ps(v.y, m11)),
         _mm_add_ps(
            _mm_mul_ps(v.z, m12), m13));

      //
      // row2 dot
      //
      r.z = _mm_add_ps(
         _mm_add_ps(
            _mm_mul_ps(v.x, m20),
            _mm_mul_ps(v.y, m21)),
         _mm_add_ps(
            _mm_mul_ps(v.z, m22), m23));

      return r;
   }
}
