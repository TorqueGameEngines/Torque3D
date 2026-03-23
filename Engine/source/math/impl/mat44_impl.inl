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
      f32x4 r0 = v_load3_vec(m + 0); // row0 xyz
      f32x4 r1 = v_load3_vec(m + 4); // row1 xyz
      f32x4 r2 = v_load3_vec(m + 8); // row2 xyz

      f32x4 c0 = v_cross(r1, r2);   // cofactor for row0
      f32x4 det = v_dot3(r0, c0);   // splatted determinant
      return v_extract0(det);
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

   inline void mat44_transform_plane_impl(const float* m, const float* s, const float* p, float* presult)
   {
      f32x4 scale = v_load3_pos(s);
      f32x4 invScale = v_div(v_set1(1.0f), scale);

      //--------------------------------------------------
      // Load affine 3x3 rows and translation
      //--------------------------------------------------
      f32x4 row0 = v_load3_vec(m + 0);
      f32x4 row1 = v_load3_vec(m + 4);
      f32x4 row2 = v_load3_vec(m + 8);
      f32x4 shear = v_set(m[3], m[7], m[11], 1.0);

      //--------------------------------------------------
      // Compute A, B, C = -dot(row, shear)
      //--------------------------------------------------
      f32x4 A = v_mul(v_dot3(row0, shear), v_set1(-1.0f));
      f32x4 B = v_mul(v_dot3(row1, shear), v_set1(-1.0f));
      f32x4 C = v_mul(v_dot3(row2, shear), v_set1(-1.0f));


      f32x4x4 invTrMatrix;
      invTrMatrix.r0 = v_set(m[0], m[1], m[2], v_extract0(A));
      invTrMatrix.r1 = v_set(m[4], m[5], m[6], v_extract0(B));
      invTrMatrix.r2 = v_set(m[8], m[9], m[10], v_extract0(C));
      invTrMatrix.r3 = v_set(0.0f, 0.0f, 0.0f, 1.0f);

      // Apply inverse scale to upper-left 3x3
      invTrMatrix.r0 = v_mul(invTrMatrix.r0, invScale);
      invTrMatrix.r1 = v_mul(invTrMatrix.r1, invScale);
      invTrMatrix.r2 = v_mul(invTrMatrix.r2, invScale);


      f32x4 normal = v_load3_pos(p);               // plane normal {x,y,z,1}
      f32x4 point = v_mul(normal, v_set1(-p[3])); // point = -d * normal

      // Apply transform to normal
      f32x4 normTransformed = m_mul_vec3(invTrMatrix, normal);
      normTransformed = v_normalize3(normTransformed);

      // transform point with original
      f32x4 scaleVec = v_load3_pos(s);            // scale vector
      f32x4 pointScaled = v_mul(point, scaleVec);

      pointScaled = v_insert_w(pointScaled, v_set1(1.0f));

      f32x4x4 M = m_load(m);
      // Transform point
      f32x4 pointTransformed = m_mul_vec4(M, pointScaled);

      //--------------------------------------------------
      // Compute plane d = -dot(normal, transformedPoint)
      //--------------------------------------------------
      f32x4 dp = v_dot3( pointTransformed, normTransformed);
      float planeD = -v_extract0(dp);

      presult[0] = v_extract0(normTransformed);
      presult[1] = v_extract0(v_swizzle_singular_mask(normTransformed, 1));
      presult[2] = v_extract0(v_swizzle_singular_mask(normTransformed, 2));
      presult[3] = planeD;
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

   // Vector Multiply: m * v (assume w = 0.0f)
   inline void mat44_mul_vec3_impl(const float* m, const float* v, float* r)
   {
      f32x4x4 ma = m_load(m);
      f32x4 va = v_load3_vec(v);
      f32x4 vr = m_mul_vec3(ma, va);
      v_store3(r, vr);
   }


   // Matrix Inverse
   inline void mat44_inverse_impl(float* m)
   {
      //// using Cramers Rule find the Inverse
      //// Minv = (1/det(M)) * adjoint(M)
      f32x4 r0 = v_load3_vec(m + 0);  // row 0: m00 m01 m02
      f32x4 r1 = v_load3_vec(m + 4);  // row 1: m10 m11 m12
      f32x4 r2 = v_load3_vec(m + 8);  // row 2: m20 m21 m22
      float det = mat44_get_determinant(m);
      f32x4 invDet = v_set1(1.0f / det);

      f32x4x4 temp;

      temp.r0 = v_set(
         (m[5] * m[10] - m[6] * m[9]),
         (m[9] * m[2] - m[10] * m[1]),
         (m[1] * m[6] - m[2] * m[5]),
         0
      );

      temp.r1 = v_set(
         (m[6] * m[8] - m[4] * m[10]),
         (m[10] * m[0] - m[8] * m[2]),
         (m[2] * m[4] - m[0] * m[6]),
         0
      );

      temp.r2 = v_set(
         (m[4] * m[9] - m[5] * m[8]),
         (m[8] * m[1] - m[9] * m[0]),
         (m[0] * m[5] - m[1] * m[4]),
         0
      );

      temp.r0 = v_mul(temp.r0, invDet);
      temp.r1 = v_mul(temp.r1, invDet);
      temp.r2 = v_mul(temp.r2, invDet);

      // Compute new translation: -R^-1 * T
      f32x4 t = v_set(m[3], m[7], m[11], 0.0f); // row-major: last element in row
      f32x4 t_new;

      t_new = v_set(
         -v_extract0(v_dot3(temp.r0, t)),
         -v_extract0(v_dot3(temp.r1, t)),
         -v_extract0(v_dot3(temp.r2, t)),
         0.0f
      );

      // Store back rotation
      m[0] = v_extract0(temp.r0); m[1] = v_extract0(v_swizzle_singular_mask(temp.r0, 1)); m[2] = v_extract0(v_swizzle_singular_mask(temp.r0, 2));
      m[4] = v_extract0(temp.r1); m[5] = v_extract0(v_swizzle_singular_mask(temp.r1, 1)); m[6] = v_extract0(v_swizzle_singular_mask(temp.r1, 2));
      m[8] = v_extract0(temp.r2); m[9] = v_extract0(v_swizzle_singular_mask(temp.r2, 1)); m[10] = v_extract0(v_swizzle_singular_mask(temp.r2, 2));

      // Store translation 
      m[3] = v_extract0(t_new);
      m[7] = v_extract0(v_swizzle_singular_mask(t_new, 1));
      m[11] = v_extract0(v_swizzle_singular_mask(t_new, 2));
   }

   // Matrix Inverse
   inline void mat44_inverse_to_impl(const float* m, float* d)
   {
      //// using Cramers Rule find the Inverse
      //// Minv = (1/det(M)) * adjoint(M)
      f32x4 r0 = v_load3_vec(m + 0);  // row 0: m00 m01 m02
      f32x4 r1 = v_load3_vec(m + 4);  // row 1: m10 m11 m12
      f32x4 r2 = v_load3_vec(m + 8);  // row 2: m20 m21 m22
      float det = mat44_get_determinant(m);
      f32x4 invDet = v_set1(1.0f / det);

      f32x4x4 temp;

      temp.r0 = v_set(
         (m[5] * m[10] - m[6] * m[9]),
         (m[9] * m[2] - m[10] * m[1]),
         (m[1] * m[6] - m[2] * m[5]),
         0
      );

      temp.r1 = v_set(
         (m[6] * m[8] - m[4] * m[10]),
         (m[10] * m[0] - m[8] * m[2]),
         (m[2] * m[4] - m[0] * m[6]),
         0
      );

      temp.r2 = v_set(
         (m[4] * m[9] - m[5] * m[8]),
         (m[8] * m[1] - m[9] * m[0]),
         (m[0] * m[5] - m[1] * m[4]),
         0
      );

      temp.r0 = v_mul(temp.r0, invDet);
      temp.r1 = v_mul(temp.r1, invDet);
      temp.r2 = v_mul(temp.r2, invDet);

      // Compute new translation: -R^-1 * T
      f32x4 t = v_set(m[3], m[7], m[11], 0.0f); // row-major: last element in row
      f32x4 t_new;

      t_new = v_set(
         -v_extract0(v_dot3(temp.r0, t)),
         -v_extract0(v_dot3(temp.r1, t)),
         -v_extract0(v_dot3(temp.r2, t)),
         0.0f
      );

      // Store back rotation
      d[0] = v_extract0(temp.r0); d[1] = v_extract0(v_swizzle_singular_mask(temp.r0, 1)); d[2] = v_extract0(v_swizzle_singular_mask(temp.r0, 2));
      d[4] = v_extract0(temp.r1); d[5] = v_extract0(v_swizzle_singular_mask(temp.r1, 1)); d[6] = v_extract0(v_swizzle_singular_mask(temp.r1, 2));
      d[8] = v_extract0(temp.r2); d[9] = v_extract0(v_swizzle_singular_mask(temp.r2, 1)); d[10] = v_extract0(v_swizzle_singular_mask(temp.r2, 2));

      // Store translation 
      d[3] = v_extract0(t_new);
      d[7] = v_extract0(v_swizzle_singular_mask(t_new, 1));
      d[11] = v_extract0(v_swizzle_singular_mask(t_new, 2));
      d[12] = m[12];
      d[13] = m[13];
      d[14] = m[14];
      d[15] = m[15];
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

   inline void mat44_normalize_impl(float* m)
   {
      // Load the matrix into SIMD registers
      f32x4x4 mat = m_load(m);

      // Transpose: now rows are columns
      mat = m_transpose(mat);

      // Extract columns (which are now rows)
      f32x4 col0 = mat.r0;
      f32x4 col1 = mat.r1;

      // Rebuild orthonormal basis
      f32x4 col2 = v_cross(col0, col1);
      col1 = v_cross(col2, col0);

      // Normalize columns
      col0 = v_normalize3(col0);
      col1 = v_normalize3(col1);
      col2 = v_normalize3(col2);

      // Write back directly into transposed matrix
      mat.r0 = col0;
      mat.r1 = col1;
      mat.r2 = col2;

      // Transpose back to row-major
      mat = m_transpose(mat);

      // Store back
      m_store(m, mat);
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

   //--------------------------------------------------
   // MATRIX BATCH FUNCTIONS
   //--------------------------------------------------

   inline void mat44_batch_mul_pos3(const float* m, const float* points, int count, float* result)
   {
      int i = 0;
      // AVX has 8 lanes to play with
#if defined(MATH_SIMD_AVX2) || defined(MATH_SIMD_AVX)
      // 8-wide AVX only
      for (; i + 8 <= count; i += 8)
      {
         vec4_batch8 va = load_vec3_batch8(&points[i*3], 1.0f, false);
         vec4_batch8 vr = m_mul_pos3_batch8(m, va);
         store_vec3_batch8(&result[i*3], vr);
      }
#endif // MATH_SIMD_AVX2 || MATH_SIMD_AVX

      // 4-wide
      for (; i + 4 <= count; i += 4)
      {
         vec4_batch4 va = load_vec3_batch4(&points[i * 3], 1.0f, false);
         vec4_batch4 vr = m_mul_pos3_batch4(m, va);
         store_vec3_batch4(&result[i * 3], vr);
      }

      for (; i < count; ++i)
      {
         size_t idx = i * 3;
         mat44_mul_pos3_impl(m, &points[idx], &result[idx]);
      }
   }

} // namespace math_backend::mat44
