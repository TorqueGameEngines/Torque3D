#pragma once
#include <immintrin.h>  // AVX2

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

   inline f32x4 v_swizzle_mask(f32x4 v1,const int x, const int y, const int z, const int w)
   {
      __m128i idx = _mm_set_epi32(w, z, y, x);
      return _mm_permutevar_ps(v1, idx);
   }

   inline f32x4 v_swizzle_singular_mask(f32x4 v1, const int x)
   {
      __m128i idx = _mm_set1_epi32(x);
      return _mm_permutevar_ps(v1, idx);
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
      f32x4 lo = v1;
      f32x4 hi = v2;

      f32x4 combined_lo = _mm_permutevar_ps(lo, _mm_set_epi32(y, y, x, x));
      f32x4 combined_hi = _mm_permutevar_ps(hi, _mm_set_epi32(w, w, z, z));

      return _mm_movelh_ps(combined_lo, combined_hi);
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
      return _mm_dp_ps(a, b, 0xFF); // f32x4, 4 lanes into all lanes
   }

   // dot3 (ignores w)
   inline f32x4 v_dot3(f32x4 a, f32x4 b)
   {
      return _mm_dp_ps(a, b, 0x7F); // f32x4, 3 last lanes into all lanes
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
      v_store(dst + 0, m.r0);
      v_store(dst + 4, m.r1);
      v_store(dst + 8, m.r2);
      v_store(dst + 12, m.r3);
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
   typedef __m256 f32x8;

   struct vec4_batch8
   {
      f32x8 x;
      f32x8 y;
      f32x8 z;
      f32x8 w;
   };

   struct vec4_batch4
   {
      f32x4 x;
      f32x4 y;
      f32x4 z;
      f32x4 w;
   };

   inline vec4_batch8 load_vec3_batch8(const float* ptr, float w, bool fillW)
   {
      vec4_batch8 r;

      r.x = _mm256_set_ps(ptr[0], ptr[3], ptr[6], ptr[9],
         ptr[12], ptr[15], ptr[18], ptr[21]);
      r.y = _mm256_set_ps(ptr[1], ptr[4], ptr[7], ptr[10],
         ptr[13], ptr[16], ptr[19], ptr[22]);
      r.z = _mm256_set_ps(ptr[2], ptr[5], ptr[8], ptr[11],
         ptr[14], ptr[17], ptr[20], ptr[23]);

      if (fillW)
      {
         r.w = _mm256_set1_ps(w);
      }

      return r;
   }

   inline vec4_batch4 load_vec3_batch4(const float* ptr, float w, bool fillW)
   {
      vec4_batch4 r;

      r.x = _mm_set_ps(ptr[0], ptr[3], ptr[6], ptr[9]);
      r.y = _mm_set_ps(ptr[1], ptr[4], ptr[7], ptr[10]);
      r.z = _mm_set_ps(ptr[2], ptr[5], ptr[8], ptr[11]);

      if (fillW)
      {
         r.w = _mm_set1_ps(w);
      }

      return r;
   }

   // Store the result back out to a float array 8 at a time
   inline void store_f32x8(float* out, f32x8 v)
   {
      _mm256_storeu_ps(out, v);
   }

   // Store the result back out to a float array 4 at a time
   inline void store_f32x4(float* out, f32x4 v)
   {
      _mm_storeu_ps(out, v);
   }

   // Store the result back to a float3 array with size of 8
   inline void store_vec3_batch8(float* out, const vec4_batch8& v)
   {
      alignas(32) float xs[8];
      alignas(32) float ys[8];
      alignas(32) float zs[8];

      _mm256_store_ps(xs, v.x);
      _mm256_store_ps(ys, v.y);
      _mm256_store_ps(zs, v.z);

      for (int i = 0; i < 8; ++i)
      {
         out[i * 3 + 0] = xs[i];
         out[i * 3 + 1] = ys[i];
         out[i * 3 + 2] = zs[i];
      }
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

   inline f32x8 vec3_batch8_dot(const vec4_batch8& a, const vec4_batch8& b)
   {
      f32x8 mulx = _mm256_mul_ps(a.x, b.x);
      f32x8 muly = _mm256_mul_ps(a.y, b.y);
      f32x8 mulz = _mm256_mul_ps(a.z, b.z);

      return _mm256_add_ps(_mm256_add_ps(mulx, muly), mulz);
   }

   // Batch 8 mul_Vec4.
   inline vec4_batch8 m_mul_pos3_batch8(const float* m, const vec4_batch8& v)
   {
      vec4_batch8 r;

      __m256 m00 = _mm256_set1_ps(m[0]);
      __m256 m01 = _mm256_set1_ps(m[1]);
      __m256 m02 = _mm256_set1_ps(m[2]);
      __m256 m03 = _mm256_set1_ps(m[3]);

      __m256 m10 = _mm256_set1_ps(m[4]);
      __m256 m11 = _mm256_set1_ps(m[5]);
      __m256 m12 = _mm256_set1_ps(m[6]);
      __m256 m13 = _mm256_set1_ps(m[7]);

      __m256 m20 = _mm256_set1_ps(m[8]);
      __m256 m21 = _mm256_set1_ps(m[9]);
      __m256 m22 = _mm256_set1_ps(m[10]);
      __m256 m23 = _mm256_set1_ps(m[11]);

      //
      // row0 dot
      //
      r.x = _mm256_add_ps(
         _mm256_add_ps(
            _mm256_mul_ps(v.x, m00),
            _mm256_mul_ps(v.y, m01)),
         _mm256_add_ps(
            _mm256_mul_ps(v.z, m02), m03));

      //
      // row1 dot
      //
      r.y = _mm256_add_ps(
         _mm256_add_ps(
            _mm256_mul_ps(v.x, m10),
            _mm256_mul_ps(v.y, m11)),
         _mm256_add_ps(
            _mm256_mul_ps(v.z, m12), m13));

      //
      // row2 dot
      //
      r.z = _mm256_add_ps(
         _mm256_add_ps(
            _mm256_mul_ps(v.x, m20),
            _mm256_mul_ps(v.y, m21)),
         _mm256_add_ps(
            _mm256_mul_ps(v.z, m22), m23));

      return r;
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
