#include "platform/platform.h"
#include "math/public/float4_dispatch.h"
#include "math/public/float3_dispatch.h"
#include "math/public/mat44_dispatch.h"
#include "math/mConstants.h"
#include "math/mMatrix.h"
#include <cmath>   // for sqrtf, etc.

namespace math_backend::float4::dispatch
{
   void install_scalar()
   {
      gFloat4.add = [](const float* a, const float* b, float* r) {
         for (int i = 0; i < 4; i++) r[i] = a[i] + b[i];
      };

      gFloat4.sub = [](const float* a, const float* b, float* r) {
         for (int i = 0; i < 4; i++) r[i] = a[i] - b[i];
      };

      gFloat4.mul = [](const float* a, const float* b, float* r) {
         for (int i = 0; i < 4; i++) r[i] = a[i] * b[i];
      };

      gFloat4.mul_scalar = [](const float* a, float s, float* r) {
         for (int i = 0; i < 4; i++) r[i] = a[i] * s;
      };

      gFloat4.div = [](const float* a, const float* b, float* r) {
         for (int i = 0; i < 4; i++) r[i] = a[i] / b[i];
      };

      gFloat4.div_scalar = [](const float* a, float s, float* r) {
         float denom = 1.0f / s;
         for (int i = 0; i < 4; i++) r[i] = a[i] * denom;
      };

      gFloat4.dot = [](const float* a, const float* b) {
         float sum = 0.f;
         for (int i = 0; i < 4; i++) sum += a[i] * b[i];
         return sum;
      };

      gFloat4.length = [](const float* a) {
         float sum = 0.f;
         for (int i = 0; i < 4; i++) sum += a[i] * a[i];
         return std::sqrt(sum);
      };

      gFloat4.lengthSquared = [](const float* a) {
         float sum = 0.f;
         for (int i = 0; i < 4; i++) sum += a[i] * a[i];
         return (sum);
      };

      gFloat4.normalize = [](float* a) {
         float len = gFloat4.length(a);
         if (len > POINT_EPSILON)
         {
            float denom = 1.0f / len;
            for (int i = 0; i < 4; i++)
               a[i] *= denom;
         }
         else
         {
            a[0] = 1.0f; a[1] = 0.0f; a[2] = 0.0f; a[3] = 0.0f;
         }
      };

      gFloat4.normalize_mag = [](float* a, float f) {
         float len = gFloat4.length(a);
         if (len > POINT_EPSILON)
         {
            float denom = f / len;
            for (int i = 0; i < 4; i++) a[i] *= denom;
         }
         else
         {
            a[0] = f; a[1] = 0.0f; a[2] = 0.0f; a[3] = 0.0f;
         }
      };

      gFloat4.lerp = [](const float* from, const float* to, float f, float* r) {
         for (int i = 0; i < 4; i++) r[i] = from[i] + (to[i] - from[i]) * f;
      };

      gFloat4.cross = [](const float* a, const float* b, float* r) {
         const float ax = a[0];
         const float ay = a[1];
         const float az = a[2];

         const float bx = b[0];
         const float by = b[1];
         const float bz = b[2];

         r[0] = ay * bz - az * by;
         r[1] = az * bx - ax * bz;
         r[2] = ax * by - ay * bx;
      };
   }
}

namespace math_backend::float3::dispatch
{
   void install_scalar()
   {
      gFloat3.add = [](const float* a, const float* b, float* r) {
         for (int i = 0; i < 3; i++) r[i] = a[i] + b[i];
      };

      gFloat3.sub = [](const float* a, const float* b, float* r) {
         for (int i = 0; i < 3; i++) r[i] = a[i] - b[i];
      };

      gFloat3.mul = [](const float* a, const float* b, float* r) {
         for (int i = 0; i < 3; i++) r[i] = a[i] * b[i];
      };

      gFloat3.mul_scalar = [](const float* a, float s, float* r) {
         for (int i = 0; i < 3; i++) r[i] = a[i] * s;
      };

      gFloat3.div = [](const float* a, const float* b, float* r) {
         for (int i = 0; i < 3; i++) r[i] = a[i] / b[i];
      };

      gFloat3.div_scalar = [](const float* a, float s, float* r) {
         float denom = 1.0f / s;
         for (int i = 0; i < 3; i++) r[i] = a[i] * denom;
      };

      gFloat3.dot = [](const float* a, const float* b) {
         float sum = 0.f;
         for (int i = 0; i < 3; i++) sum += a[i] * b[i];
         return sum;
      };

      gFloat3.length = [](const float* a) {
         float sum = 0.f;
         for (int i = 0; i < 3; i++) sum += a[i] * a[i];
         return std::sqrt(sum);
      };

      gFloat3.lengthSquared = [](const float* a) {
         float sum = 0.f;
         for (int i = 0; i < 3; i++) sum += a[i] * a[i];
         return (sum);
      };

      gFloat3.normalize = [](float* a) {
         float len = gFloat3.length(a);
         if (len > POINT_EPSILON)
         {
            float denom = 1.0f / len;
            for (int i = 0; i < 3; i++) a[i] *= denom;
         }
         else
         {
            a[0] = 1.0f; a[1] = 0.0f; a[2] = 0.0f;
         }
      };

      gFloat3.normalize_mag = [](float* a, float f) {
         float len = gFloat3.length(a);
         if (len > POINT_EPSILON)
         {
            float denom = f / len;
            for (int i = 0; i < 3; i++) a[i] *= denom;
         }
         else
         {
            a[0] = f; a[1] = 0.0f; a[2] = 0.0f;
         }
      };

      gFloat3.lerp = [](const float* from, const float* to, float f, float* r) {
         for (int i = 0; i < 3; i++) r[i] = from[i] + (to[i] - from[i]) * f;
      };

      gFloat3.cross = [](const float* a, const float* b, float* r) {
         const float ax = a[0];
         const float ay = a[1];
         const float az = a[2];

         const float bx = b[0];
         const float by = b[1];
         const float bz = b[2];

         r[0] = ay * bz - az * by;
         r[1] = az * bx - ax * bz;
         r[2] = ax * by - ay * bx;
      };
   }
}

inline void swap(float& a, float& b)
{
   float temp = a;
   a = b;
   b = temp;
}


namespace math_backend::mat44::dispatch
{
   void install_scalar()
   {
      gMat44.transpose = [](float* a) {
         swap(a[1], a[4]);
         swap(a[2], a[8]);
         swap(a[3], a[12]);
         swap(a[6], a[9]);
         swap(a[7], a[13]);
         swap(a[11], a[14]);
      };

      gMat44.determinant = [](const float* m) {
         return m[0] * (m[5] * m[10] - m[6] * m[9]) +
            m[4] * (m[2] * m[9] - m[1] * m[10]) +
            m[8] * (m[1] * m[6] - m[2] * m[5]);
      };

      gMat44.inverse = [](float* m) {
         // using Cramers Rule find the Inverse
         // Minv = (1/det(M)) * adjoint(M)
         float det = gMat44.determinant(m);
         AssertFatal(det != 0.0f, "MatrixF::inverse: non-singular matrix, no inverse.");
         float invDet = 1.0f / det;
         float temp[16];
         temp[0] = (m[5] * m[10] - m[6] * m[9]) * invDet;
         temp[1] = (m[9] * m[2] - m[10] * m[1]) * invDet;
         temp[2] = (m[1] * m[6] - m[2] * m[5]) * invDet;

         temp[4] = (m[6] * m[8] - m[4] * m[10]) * invDet;
         temp[5] = (m[10] * m[0] - m[8] * m[2]) * invDet;
         temp[6] = (m[2] * m[4] - m[0] * m[6]) * invDet;

         temp[8] = (m[4] * m[9] - m[5] * m[8]) * invDet;
         temp[9] = (m[8] * m[1] - m[9] * m[0]) * invDet;
         temp[10] = (m[0] * m[5] - m[1] * m[4]) * invDet;

         m[0] = temp[0];
         m[1] = temp[1];
         m[2] = temp[2];

         m[4] = temp[4];
         m[5] = temp[5];
         m[6] = temp[6];

         m[8] = temp[8];
         m[9] = temp[9];
         m[10] = temp[10];
         
         // invert the translation
         temp[0] = -m[3];
         temp[1] = -m[7];
         temp[2] = -m[11];
         gMat44.mul_vec3(m, temp, &temp[4]);
         m[3] = temp[4];
         m[7] = temp[5];
         m[11] = temp[6];

      };

      gMat44.inverse_to = [](const float* m, float* d) {
         // using Cramers Rule find the Inverse
         // Minv = (1/det(M)) * adjoint(M)
         F32 det = gMat44.determinant(m);
         AssertFatal(det != 0.0f, "MatrixF::inverse: non-singular matrix, no inverse.");

         F32 invDet = 1.0f / det;

         const F32 m0 = m[0], m1 = m[1], m2 = m[2];
         const F32 m4 = m[4], m5 = m[5], m6 = m[6];
         const F32 m8 = m[8], m9 = m[9], m10 = m[10];

         d[0] = (m5 * m10 - m6 * m9) * invDet;
         d[1] = (m9 * m2 - m10 * m1) * invDet;
         d[2] = (m1 * m6 - m2 * m5) * invDet;

         d[4] = (m6 * m8 - m4 * m10) * invDet;
         d[5] = (m10 * m0 - m8 * m2) * invDet;
         d[6] = (m2 * m4 - m0 * m6) * invDet;

         d[8] = (m4 * m9 - m5 * m8) * invDet;
         d[9] = (m8 * m1 - m9 * m0) * invDet;
         d[10] = (m0 * m5 - m1 * m4) * invDet;

         // invert the translation
         F32 temp[6];
         temp[0] = -m[3];
         temp[1] = -m[7];
         temp[2] = -m[11];
         gMat44.mul_vec3(d, temp, &temp[3]);
         d[3] = temp[3];
         d[7] = temp[4];
         d[11] = temp[5];
         d[12] = m[12];
         d[13] = m[13];
         d[14] = m[14];
         d[15] = m[15];
      };

      gMat44.affine_inverse = [](float* a) {
         F32 temp[16];
         dMemcpy(temp, a, 16 * sizeof(F32));

         // Transpose rotation
         a[1] = temp[4];
         a[4] = temp[1];
         a[2] = temp[8];
         a[8] = temp[2];
         a[6] = temp[9];
         a[9] = temp[6];

         a[3] = -(temp[0] * temp[3] + temp[4] * temp[7] + temp[8] * temp[11]);
         a[7] = -(temp[1] * temp[3] + temp[5] * temp[7] + temp[9] * temp[11]);
         a[11] = -(temp[2] * temp[3] + temp[6] * temp[7] + temp[10] * temp[11]);
      };

      gMat44.scale = [](float* a, const float* s) {
         // Note, doesn't allow scaling w...

         a[0] *= s[0];  a[1] *= s[1];  a[2] *= s[2];
         a[4] *= s[0];  a[5] *= s[1];  a[6] *= s[2];
         a[8] *= s[0];  a[9] *= s[1];  a[10] *= s[2];
         a[12] *= s[0];  a[13] *= s[1];  a[14] *= s[2];
      };

      gMat44.get_scale = [](const float* a, float* s) {
         // Note, doesn't allow scaling w...
         s[0] = std::sqrt(a[0] * a[0] + a[4] * a[4] + a[8] * a[8]);
         s[1] = std::sqrt(a[1] * a[1] + a[5] * a[5] + a[9] * a[9]);
         s[2] = std::sqrt(a[2] * a[2] + a[6] * a[6] + a[10] * a[10]);

         // If the determinant is negative, we have a reflection, so we need to negate one of the scales.
         if (gMat44.determinant(a) < 0.0f)
            s[0] = -s[0];
      };

      gMat44.mul_float4 = [](const float* a, const float* b, float* r) {
         AssertFatal(b != r, "Error, aliasing matrix mul pointers not allowed here!");
         const F32 b0 = b[0], b1 = b[1], b2 = b[2], b3 = b[3];
         r[0] = a[0] * b0 + a[1] * b1 + a[2] * b2 + a[3] * b3;
         r[1] = a[4] * b0 + a[5] * b1 + a[6] * b2 + a[7] * b3;
         r[2] = a[8] * b0 + a[9] * b1 + a[10] * b2 + a[11] * b3;
         r[3] = a[12] * b0 + a[13] * b1 + a[14] * b2 + a[15] * b3;
      };

      gMat44.mul_pos3 = [](const float* a, const float* b, float* r) {
             AssertFatal(b != r, "Error, aliasing matrix mul pointers not allowed here!");
             const F32 b0 = b[0], b1 = b[1], b2 = b[2];
             r[0] = a[0]*b0 + a[1]*b1 + a[2]*b2  + a[3];
             r[1] = a[4]*b0 + a[5]*b1 + a[6]*b2  + a[7];
             r[2] = a[8]*b0 + a[9]*b1 + a[10]*b2 + a[11];
      };

      gMat44.mul_vec3 = [](const float* a, const float* b, float* r) {
         AssertFatal(b != r, "Error, aliasing matrix mul pointers not allowed here!");
         const F32   v0 = b[0], v1 = b[1], v2 = b[2];
         const F32   m0 = a[0], m1 = a[1], m2 = a[2];
         const F32   m4 = a[4], m5 = a[5], m6 = a[6];
         const F32   m8 = a[8], m9 = a[9], m10 = a[10];

         r[0] = m0 * v0 + m1 * v1 + m2 * v2;
         r[1] = m4 * v0 + m5 * v1 + m6 * v2;
         r[2] = m8 * v0 + m9 * v1 + m10 * v2;
      };

      gMat44.mul_mat44 = [](const float* a, const float* b, float* mresult) {
         AssertFatal(mresult != a && mresult != b, "Error, aliasing matrix mul pointers not allowed here!");

         const F32 a0 = a[0], a1 = a[1], a2 = a[2], a3 = a[3];
         const F32 a4 = a[4], a5 = a[5], a6 = a[6], a7 = a[7];
         const F32 a8 = a[8], a9 = a[9], a10 = a[10], a11 = a[11];
         const F32 a12 = a[12], a13 = a[13], a14 = a[14], a15 = a[15];

         mresult[0] = a0*b[0] + a1*b[4] + a2*b[8]  + a3*b[12];
         mresult[1] = a0*b[1] + a1*b[5] + a2*b[9]  + a3*b[13];
         mresult[2] = a0*b[2] + a1*b[6] + a2*b[10] + a3*b[14];
         mresult[3] = a0*b[3] + a1*b[7] + a2*b[11] + a3*b[15];

         mresult[4] = a4*b[0] + a5*b[4] + a6*b[8]  + a7*b[12];
         mresult[5] = a4*b[1] + a5*b[5] + a6*b[9]  + a7*b[13];
         mresult[6] = a4*b[2] + a5*b[6] + a6*b[10] + a7*b[14];
         mresult[7] = a4*b[3] + a5*b[7] + a6*b[11] + a7*b[15];

         mresult[8] = a8*b[0] + a9*b[4] + a10*b[8] + a11*b[12];
         mresult[9] = a8*b[1] + a9*b[5] + a10*b[9] + a11*b[13];
         mresult[10]= a8*b[2] + a9*b[6] + a10*b[10]+ a11*b[14];
         mresult[11]= a8*b[3] + a9*b[7] + a10*b[11]+ a11*b[15];

         mresult[12]= a12*b[0]+ a13*b[4]+ a14*b[8] + a15*b[12];
         mresult[13]= a12*b[1]+ a13*b[5]+ a14*b[9] + a15*b[13];
         mresult[14]= a12*b[2]+ a13*b[6]+ a14*b[10]+ a15*b[14];
         mresult[15]= a12*b[3]+ a13*b[7]+ a14*b[11]+ a15*b[15];
      };

      gMat44.transform_plane = [](const F32* m, const F32* s, const F32* p, F32* presult) {
         // We take in a matrix, a scale factor, and a plane equation.  We want to output
         //  the resultant normal
         // We have T = m*s
         // To multiply the normal, we want Inv(Tr(m*s))
         //  Inv(Tr(ms)) = Inv(Tr(s) * Tr(m))
         //              = Inv(Tr(m)) * Inv(Tr(s))
         //
         //  Inv(Tr(s)) = Inv(s) = [ 1/x   0   0  0]
         //                        [   0 1/y   0  0]
         //                        [   0   0 1/z  0]
         //                        [   0   0   0  1]
         //
         // Since m is an affine matrix,
         //  Tr(m) = [ [       ] 0 ]
         //          [ [   R   ] 0 ]
         //          [ [       ] 0 ]
         //          [ [ x y z ] 1 ]
         //
         // Inv(Tr(m)) = [ [    -1 ] 0 ]
         //              [ [   R   ] 0 ]
         //              [ [       ] 0 ]
         //              [ [ A B C ] 1 ]
         // Where:
         //
         //  P = (x, y, z)
         //  A = -(Row(0, r) * P);
         //  B = -(Row(1, r) * P);
         //  C = -(Row(2, r) * P);

         AssertFatal(mFabs(s[0]) > POINT_EPSILON&& mFabs(s[1]) > POINT_EPSILON&& mFabs(s[2]) > POINT_EPSILON,
            "transform_plane: degenerate (near-zero) scale component");
         MatrixF invScale(true);
         F32* pScaleElems = invScale;
         pScaleElems[MatrixF::idx(0, 0)] = 1.0f / s[0];
         pScaleElems[MatrixF::idx(1, 1)] = 1.0f / s[1];
         pScaleElems[MatrixF::idx(2, 2)] = 1.0f / s[2];

         const Point3F shear(m[MatrixF::idx(3, 0)], m[MatrixF::idx(3, 1)], m[MatrixF::idx(3, 2)]);

         const Point3F row0(m[MatrixF::idx(0, 0)], m[MatrixF::idx(0, 1)], m[MatrixF::idx(0, 2)]);
         const Point3F row1(m[MatrixF::idx(1, 0)], m[MatrixF::idx(1, 1)], m[MatrixF::idx(1, 2)]);
         const Point3F row2(m[MatrixF::idx(2, 0)], m[MatrixF::idx(2, 1)], m[MatrixF::idx(2, 2)]);

         const F32 A = -mDot(row0, shear);
         const F32 B = -mDot(row1, shear);
         const F32 C = -mDot(row2, shear);

         MatrixF invTrMatrix(true);
         F32* destMat = invTrMatrix;
         destMat[MatrixF::idx(0, 0)] = m[MatrixF::idx(0, 0)];
         destMat[MatrixF::idx(1, 0)] = m[MatrixF::idx(1, 0)];
         destMat[MatrixF::idx(2, 0)] = m[MatrixF::idx(2, 0)];
         destMat[MatrixF::idx(0, 1)] = m[MatrixF::idx(0, 1)];
         destMat[MatrixF::idx(1, 1)] = m[MatrixF::idx(1, 1)];
         destMat[MatrixF::idx(2, 1)] = m[MatrixF::idx(2, 1)];
         destMat[MatrixF::idx(0, 2)] = m[MatrixF::idx(0, 2)];
         destMat[MatrixF::idx(1, 2)] = m[MatrixF::idx(1, 2)];
         destMat[MatrixF::idx(2, 2)] = m[MatrixF::idx(2, 2)];
         destMat[MatrixF::idx(0, 3)] = A;
         destMat[MatrixF::idx(1, 3)] = B;
         destMat[MatrixF::idx(2, 3)] = C;
         invTrMatrix.mul(invScale);

         Point3F norm(p[0], p[1], p[2]);
         Point3F point = norm * -p[3];
         invTrMatrix.mulP(norm);
         norm.normalize();

         MatrixF temp;
         dMemcpy(temp, m, sizeof(F32) * 16);
         point.x *= s[0];
         point.y *= s[1];
         point.z *= s[2];
         temp.mulP(point);

         PlaneF resultPlane(point, norm);
         presult[0] = resultPlane.x;
         presult[1] = resultPlane.y;
         presult[2] = resultPlane.z;
         presult[3] = resultPlane.d;

      };

      gMat44.normalize = [](float* a) {
         F32 col0[3], col1[3], col2[3];
         // extract columns 0 and 1
         col0[0] = a[0];
         col0[1] = a[4];
         col0[2] = a[8];

         col1[0] = a[1];
         col1[1] = a[5];
         col1[2] = a[9];

         col2[0] = a[2];
         col2[1] = a[6];
         col2[2] = a[10];

         math_backend::float3::dispatch::gFloat3.normalize(col0);
         math_backend::float3::dispatch::gFloat3.normalize(col1);
         math_backend::float3::dispatch::gFloat3.normalize(col2);

         // store the normalized columns
         a[0] = col0[0];
         a[4] = col0[1];
         a[8] = col0[2];

         a[1] = col1[0];
         a[5] = col1[1];
         a[9] = col1[2];

         a[2] = col2[0];
         a[6] = col2[1];
         a[10] = col2[2];

      };

      gMat44.batch_mul_pos3 = [](const float* m, const float* pts, int count, float* result_ptrs) {
         int i = 0;
         for (; i < count; i++)
         {
            int idx = i * 3;
            gMat44.mul_pos3(m, &pts[idx], &result_ptrs[idx]);
         }
      };
   }
}
