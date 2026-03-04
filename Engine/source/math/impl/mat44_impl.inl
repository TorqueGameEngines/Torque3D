#pragma once
#include <cmath>   // for sqrtf, etc.
#include "../mConstants.h"

namespace math_backend::mat44
{
   //------------------------------------------------------------------
   // Matrix Transpose
   inline void mat44_transpose_impl(float* m)
   {
      f32x4x4 ma = m_load(m);
      f32x4x4 mr = m_transpose(ma);
      m_store(m, mr);
   }

   inline float mat44_get_determinant(const float* m)
   {
      f32x4x4 ma = m_load(m);
      return v_extract0(m_determinant_affine(ma));
   }

   // Matrix Scale: Float3 (assume w = 1.0f)
   inline void mat44_scale_impl(float* m, const float* s)
   {
      f32x4x4 ma = m_load(m);
      f32x4 va = v_load3_pos(s);

      ma.r0 = v_mul(ma.r0, va);
      ma.r1 = v_mul(ma.r1, va);
      ma.r2 = v_mul(ma.r2, va);
      ma.r3 = v_mul(ma.r3, va);
      m_store(m, ma);
   }

   inline void mat44_get_scale_impl(const float* m, float* s)
   {
      f32x4x4 ma = m_load(m);

      // squared lengths
      f32x4 len2_x = v_dot3(ma.r0, ma.r0);
      f32x4 len2_y = v_dot3(ma.r1, ma.r1);
      f32x4 len2_z = v_dot3(ma.r2, ma.r2);

      // extract and sqrt
      s[0] = 1.0f / v_extract0(v_rsqrt_nr(len2_x));
      s[1] = 1.0f / v_extract0(v_rsqrt_nr(len2_y));
      s[2] = 1.0f / v_extract0(v_rsqrt_nr(len2_z));
   }

   // Matrix Scale Uniform: Float value (assume w = 1.0f)
   inline void mat44_scale_uniform(float* m, float s)
   {
      f32x4x4 ma = m_load(m);

      // (s, s, s, 1)
      f32x4 scale = v_set(s, s, s, 1.0f);

      // Scale only rotation rows (xyz part)
      ma.r0 = v_mul(ma.r0, scale);
      ma.r1 = v_mul(ma.r1, scale);
      ma.r2 = v_mul(ma.r2, scale);
      m_store(m, ma);
   }

   // Matrix Inverse
   inline void mat44_inverse_impl(float* m)
   {
      f32x4x4 ma = m_load(m);

      // Compute cofactors using cross products
      f32x4x4 mTemp;
      mTemp.r0 = v_cross(ma.r1, ma.r2);
      mTemp.r1 = v_cross(ma.r2, ma.r0);
      mTemp.r2 = v_cross(ma.r0, ma.r1);

      // Determinant = dot(ma.r0, c0)
      f32x4 det = v_dot3(ma.r0, mTemp.r0);
      f32x4 invDet = v_rcp_nr(det);

      // Scale cofactors
      mTemp.r0 = v_mul(mTemp.r0, invDet);
      mTemp.r1 = v_mul(mTemp.r1, invDet);
      mTemp.r2 = v_mul(mTemp.r2, invDet);

      // Store inverse 3x3 (transpose of cofactor matrix)

      mTemp = m_transpose(mTemp);
      mTemp.r3 = v_set(0, 0, 0, 1.0f);

      // ---- Translation ----

      // Load original translation
      f32x4 T = v_set(m[3], m[7], m[11], 0.0f);
      
      // Compute -(Tx*ma.r0 + Ty*ma.r1 + Tz*ma.r2)
      f32x4 result = v_mul(ma.r0, v_swizzle_singular_mask(T, 0));
      result = v_add(result, v_mul(ma.r1, v_swizzle_singular_mask(T, 1)));
      result = v_add(result, v_mul(ma.r2, v_swizzle_singular_mask(T, 2)));
      result = v_mul(result, v_set1(-1.0f));

      m_store(m, mTemp);

      // Store translation
      m[3] = v_extract0(result);
      m[7] = v_extract0(v_swizzle_singular_mask(result, 1));
      m[11] = v_extract0(v_swizzle_singular_mask(result, 2));
   }

   // Matrix Affine Inverse
   inline void mat44_affine_inverse_impl(float* m)
   {
      f32x4x4 ma = m_load(m);

      f32x4x4 mTemp = m_transpose(ma);
      mTemp.r3 = v_set(0, 0, 0, 1);

      // ---- Translation ----
      // Load original translation
      f32x4 T = v_set(m[3], m[7], m[11], 0.0f);

      // Compute -(Tx*ma.r0 + Ty*ma.r1 + Tz*ma.r2)
      f32x4 result = v_mul(ma.r0, v_swizzle_singular_mask(T, 0));
      result = v_add(result, v_mul(ma.r1, v_swizzle_singular_mask(T, 1)));
      result = v_add(result, v_mul(ma.r2, v_swizzle_singular_mask(T, 2)));
      result = v_mul(result, v_set1(-1.0f));

      m_store(m, mTemp);

      // Store translation
      m[3] = v_extract0(result);
      m[7] = v_extract0(v_swizzle_singular_mask(result, 1));
      m[11] = v_extract0(v_swizzle_singular_mask(result, 2));
   }

   inline void mat44_normalize_impl(float* a)
   {
      // Load the matrix
      f32x4x4 m = m_load(a);

      // Extract axes (rows 0-2), zero out w using v_mask_xyz
      f32x4 xaxis = v_mul(m.r0, v_mask_xyz());
      f32x4 yaxis = v_mul(m.r1, v_mask_xyz());
      f32x4 zaxis = v_mul(m.r2, v_mask_xyz());

      xaxis = v_normalize3(xaxis);

      float dotXY = v_extract0(v_hadd4(v_mul(xaxis, yaxis)));
      f32x4 projYonX = v_mul(v_set1(dotXY), xaxis);
      yaxis = v_normalize3(v_sub(yaxis, projYonX));

      zaxis = v_cross(xaxis, yaxis);

      // Store normalized axes back (preserve translation w)
      m.r0 = v_preserve_w(xaxis, m.r0);
      m.r1 = v_preserve_w(yaxis, m.r1);
      m.r2 = v_preserve_w(zaxis, m.r2);

      // Store back to memory
      m_store(a, m);
   }

   // Matrix Multiply: a * b
   inline void mat44_mul_mat44_impl(const float* a, const float* b, float* r)
   {
      f32x4x4 ma = m_load(a);
      f32x4x4 mb = m_load(b);

      f32x4x4 mr = m_mul(ma, mb);
      m_store(r, mr);
   }

   // Vector Multiply: m * p (assume w = 1.0f)
   inline void mat44_mul_pos3_impl(const float *m, const float *p, float* r)
   {
      f32x4x4 ma = m_load(m);
      f32x4 va = v_load3_pos(p);
      f32x4 vr = m_mul_vec4(ma, va);
      v_store3(r, vr);
   }

   // Vector Multiply: m * v (assume w = 0.0f)
   inline void mat44_mul_vec3_impl(const float* m, const float* v, float* r)
   {
      f32x4x4 ma = m_load(m);
      f32x4 va = v_load3_vec(v);
      f32x4 vr = m_mul_vec4(ma, va);
      v_store3(r, vr);
   }

   // Vector Multiply: m * p (full [4x4] * [1x4])
   inline void mat44_mul_float4_impl(const float* m, const float* p, float* r)
   {
      f32x4x4 ma = m_load(m);
      f32x4 va = v_load(p);
      f32x4 vr = m_mul_vec4(ma, va);
      v_store(r, vr);
   }

   //--------------------------------------------------
   // MATRIX ROTATION FUNCTIONS
   //--------------------------------------------------

   inline void mat44_rotation_x_impl(float* m, float angle)
   {
      float c = cosf(angle), s = sinf(angle);
      f32x4x4 mr = m_identity();
      mr.r1 = v_set(0, c, s, 0);
      mr.r2 = v_set(0, -s, c, 0);
      m_store(m, mr);
   }

   inline void mat44_rotation_y_impl(float* m, float angle)
   {
      float c = cosf(angle), s = sinf(angle);
      f32x4x4 mr = m_identity();
      mr.r0 = v_set(c, 0, -s, 0);
      mr.r2 = v_set(s, 0, c, 0);
      m_store(m, mr);
   }

   inline void mat44_rotation_z_impl(float* m, float angle)
   {
      float c = cosf(angle), s = sinf(angle);
      f32x4x4 mr = m_identity();
      mr.r0 = v_set(c, s, 0, 0);
      mr.r1 = v_set(-s, c, 0, 0);
      m_store(m, mr);
   }

   // Compose rotation from Euler angles (pitch=X, yaw=Y, roll=Z)
   inline void mat44_rotation_euler_impl(float* m, float pitch, float yaw, float roll)
   {
      f32x4x4 rx, ry, rz;
      mat44_rotation_x_impl((float*)&rx, pitch);
      mat44_rotation_y_impl((float*)&ry, yaw);
      mat44_rotation_z_impl((float*)&rz, roll);

      f32x4x4 r = m_mul(rz, m_mul(ry, rx));
      m_store(m, r);
   }

   inline void mat44_lookat_impl(float* m, const float* eye, const float* target, const float* up)
   {
      f32x4 vEye = v_load3_pos(eye);
      f32x4 vTarget = v_load3_pos(target);
      f32x4 vUp = v_load3_vec(up);

      // Forward (z+)
      f32x4 zaxis = v_normalize3(v_sub(vTarget, vEye));

      // Right (x+)
      f32x4 xaxis = v_normalize3(v_cross(vUp, zaxis));

      // Up (y+)
      f32x4 yaxis = v_cross(zaxis, xaxis);

      // Compute translation components: -dot(axis, eye)
      f32x4 t_x = v_mul(v_dot3(xaxis, vEye), v_set1(-1.0f));
      f32x4 t_y = v_mul(v_dot3(yaxis, vEye), v_set1(-1.0f));
      f32x4 t_z = v_mul(v_dot3(zaxis, vEye), v_set1(-1.0f));

      f32x4x4 view;
      view.r0 = v_insert_w(xaxis, t_x);
      view.r1 = v_insert_w(yaxis, t_y);
      view.r2 = v_insert_w(zaxis, t_z);
      view.r3 = v_set(0, 0, 0, 1.0f);

      m_store(m, view);
   }

   inline void mat44_perspective_impl(float* m, float fovY, float aspect, float znear, float zfar)
   {
      float f = 1.0f / tanf(fovY * 0.5f);
      float nf = 1.0f / (znear - zfar);

      f32x4x4 mp = m_zero();
      mp.r0 = v_set(f / aspect, 0, 0, 0);
      mp.r1 = v_set(0, f, 0, 0);
      mp.r2 = v_set(0, 0, (zfar + znear) * nf, 2 * zfar * znear * nf);
      mp.r3 = v_set(0, 0, -1, 0); // row-major projection
      m_store(m, mp);
   }

   inline void mat44_orthographic_impl(float* m, float left, float right, float bottom, float top, float znear, float zfar)
   {
      f32x4x4 mo = m_zero();
      mo.r0 = v_set(2.0f / (right - left), 0, 0, -(right + left) / (right - left));
      mo.r1 = v_set(0, 2.0f / (top - bottom), 0, -(top + bottom) / (top - bottom));
      mo.r2 = v_set(0, 0, -2.0f / (zfar - znear), -(zfar + znear) / (zfar - znear));
      mo.r3 = v_set(0, 0, 0, 1.0f);
      m_store(m, mo);
   }

} // namespace math_backend::mat44
